/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_transmit_irq.c
 * @brief    MAC Driver TX Interrupt management implementation
 *
 * @}
 */

// External imports
#include "esps_drv_config.h"

#include "esps_drv_ct.h"
#include "esps_drv_tim.h"
#include "esps_drv_dispatcher.h"
#include "esps_drv_irq.h"
#include "esps_drv_pool.h"
#include "esps_drv_queue.h"
#include "esps_drv_rng.h"
#include "esps_drv_exeh.h"
#include "esps_drv_debug.h"

// Necessary definitions for esps_drv_sm_debug.h
#define STATE_TYPE      eMACTransmitState_t
#define EVENT_TYPE      eTXEvent_t
#define INSTANCE_NAME   MacTxRuntimeStats
#include "esps_drv_sm_debug.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_MAC_TRANSMIT_IRQ)
#define POST_TX_SM_EVENT(evt)       fp_psState->sTXCtx.eStateEvent = (evt)

/// Increase the priority of a message after several unsuccessful tries. @see fs_vIncDynPriority
STATIC uint16_t u16DynamicPriorityValue = (uint16_t) (RS485_INITIAL_PRIORITY);

/**
 * Initialise the dynamic priority of the Interface.
 */
STATIC inline void fs_vInitDynPriority(void);

/**
 * If we reach RS485_MAX_TX_WAIT_TIMEOUT without sending, we increase the priority of the interface until RS485_MINIMUM_PRIORITY
 */
STATIC inline void fs_vIncDynPriority(void);

/**
 * Wait priority timer callback.
 *
 * @param fp_eStatus - status of the timer (canceled/expired)
 * @param fp_pvData  - a pointer to user-provided data
 */
STATIC void fs_vTXWaitCallback(eTIMTimerStatus_t fp_eStatus, void *fp_pvData);

/**
 * Calculate TX priority time based on the time quantum and priorities.
 *
 * @param fp_psState - MAC interface state
 * @return U32: time in microseconds.
 */
STATIC uint32_t fs_u32CalcTXPrioTime(sMACInterfaceState_t * fp_psState);

/**
 * WaitPriority state processing function.
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vTXState_WaitPriority(sMACInterfaceState_t * fp_psState);

/**
 * Idle state processing function.
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vTXState_Idle(sMACInterfaceState_t * fp_psState);

/**
 * Active state processing function.
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vTXState_Active(sMACInterfaceState_t * fp_psState);

/**
 * ProcessNext state processing function.
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vTXState_ProcessNext(sMACInterfaceState_t * fp_psState);

/**
 * Retry state processing function.
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vTXState_Retry(sMACInterfaceState_t * fp_psState);

/**
 * Injects an event to the TX state machine and executes the respective
 * actions.
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vTXState_ProcessEvent(sMACInterfaceState_t * fp_psState);

/**
 * The function performs a full disable of the UART Tx function (e.g. RS485 driver,
 * transmitter and related interrupts)
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vFullTxDisable(sMACInterfaceState_t * fp_psState);

/**
 * The function performs a full enable of the UART RX function
 *
 * @param fp_psState - MAC interface state.
 */
STATIC void fs_vFullRxEnable(sMACInterfaceState_t * fp_psState);


/// Interrupt callback for a transmission indication in the UART
void MAC_IRQ_vTXIndication(sMACInterfaceState_t * fp_psState)
{
    if(fp_psState == NULL)
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, eMACException_InvalidParameter);
        return;
    }
    #define _9_BIT_MASK   ((uint16_t) 0x01FFU)

    uint16_t u16CmdIdx;

    sMACTransmitCmd_t *psCmd;

    if(fp_psState == NULL)
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, eMACException_InvalidParameter);
        return;
    }

    fp_psState->sTXCtx.u32TxTimeSingle += MAC_TIM_vMicroTimerGetElapsed(fp_psState->psCfg->sHwConfig.eTXTIMID);

    u16CmdIdx = fp_psState->sTXCtx.u16TXCmdIdx;

    if(u16CmdIdx >= fp_psState->sTXCtx.u16TXCmdCount)
    {
        // Set the TC interrupt flag -> Disable the Tx (DE signal of the RS-485) from there
        LL_USART_EnableIT_TC(fp_psState->psCfg->sHwConfig.psUART);
    }
    else
    {
        psCmd = &fp_psState->sTXCtx.asTXCmds[u16CmdIdx];

        LL_USART_TransmitData9(fp_psState->psCfg->sHwConfig.psUART,
                               (uint16_t) (psCmd->pu8TXData[psCmd->u32TXCount] & _9_BIT_MASK));

        psCmd->u32TXCount++;

        if(psCmd->u32TXCount >= psCmd->u32TXSize)
            fp_psState->sTXCtx.u16TXCmdIdx++;
    }
}

/// Interrupt call for a finished transmission in the UART
void MAC_IRQ_vTXFinishedIndication(sMACInterfaceState_t * fp_psState)
{
    if(fp_psState != NULL)
    {
        // Store the interface stats
        MAC_Stats_triggerMultiEvent(fp_psState->macStats, eMACStatId_TotalTxBytes,
                                    ESSATMAC_HEADER_SIZE +
                                    fp_psState->sTXCtx.psMsgEntry->sMessage.u8DataSize +
                                    sizeof(fp_psState->sTXCtx.psMsgEntry->sMessage.u32CRC));

        MAC_Stats_storeEventMax(fp_psState->macStats, eMACStatId_MaxTxTime, fp_psState->sTXCtx.u32TxTimeSingle);
        MAC_Stats_triggerEvent(fp_psState->macStats, eMACStatId_TxFramesCntr);

        // Reset the dynamic priority and the timer since the interface managed to send a message
        fs_vInitDynPriority();
        fp_psState->sTXCtx.u32TxTimeSingle = 0U;
        fp_psState->sTXCtx.bSent = true;

        fs_vFullTxDisable(fp_psState);
        fs_vFullRxEnable(fp_psState);

        // Process the TX and RX events
        POST_TX_SM_EVENT(eTXEvent_MessageSendFinished);
        fs_vTXState_ProcessEvent(fp_psState);
        MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_TxOpFinished);
    }
    else
        EXEH_HANDLE(eEXEHSeverity_Warning, eMACException_InvalidParameter);
}

/// Process a new event with the RX state machine
void MAC_IRQ_vTXProcessEvent(sMACInterfaceState_t * fp_psState, eTXEvent_t fp_eEvent)
{
    if((fp_psState != NULL) && (fp_eEvent < eTXEvent_MAX))
    {
        POST_TX_SM_EVENT(fp_eEvent);
        fs_vTXState_ProcessEvent(fp_psState);
    }
    else
        EXEH_HANDLE(eEXEHSeverity_Warning, eMACException_InvalidParameter);
}

/// Interrupt for the Transfer request indication in the UART
void MAC_IRQ_vTXRequestIndication(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    // the critical section here is important due to the fact that this call comes from a task and
    // can easily be preempted by the UART or timer ISRs which also call fs_vTXState_ProcessEvent(), therefore
    // the probability to mangle the TX state increases quite a bit during active communication
    MAC_vEnterCriticalSection(fp_psState);

    if(fp_psState->sTXCtx.eState == eMACTransmit_Idle)
    {
        POST_TX_SM_EVENT(eTXEvent_NewMessage);
        fs_vTXState_ProcessEvent(fp_psState);
    }

    MAC_vLeaveCriticalSection(fp_psState);
}

/******************************************************************************
 * File Local Function Definitions
 *****************************************************************************/
STATIC inline void fs_vInitDynPriority(void)
{
    u16DynamicPriorityValue = (uint16_t) (ESSASMP_LOW);
}

STATIC inline void fs_vIncDynPriority(void)
{
    // Reduce the value by 1TQ until we reach RS485_MINIMUM_PRIORITY
    if(u16DynamicPriorityValue > RS485_MINIMUM_PRIORITY)
        --u16DynamicPriorityValue;
    else
        u16DynamicPriorityValue = (uint16_t) RS485_MINIMUM_PRIORITY;
}

STATIC void fs_vTXWaitCallback(eTIMTimerStatus_t fp_eStatus, void *fp_pvData)
{
    sMACInterfaceState_t *psState = (sMACInterfaceState_t *) fp_pvData;

    MACDRV_DBG_ASSERT(fp_pvData != NULL);

    if(psState != NULL)
    {
        switch (fp_eStatus)
        {
        case (eTIMTimer_Expired):
            // Proceed to sending the message...
            psState->sTXCtx.eStateEvent = eTXEvent_PriorityWaitFinished;
            fs_vTXState_ProcessEvent(psState);
            break;

        case (eTIMTimer_Canceled):
            break;

        default:
            MACDRV_DBG_ASSERT(false);
            break;
        }
    }
    else
        MACDRV_DBG_ASSERT(false);
}

STATIC void fs_vTXState_WaitPriority(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    // check if we have a valid pending message, because subsequent actions cannot
    // be performed if the following condition is false
    if(fp_psState->sTXCtx.psMsgEntry != NULL)
    {
        // Make sure Tx is disabled during wait priority phase to not disturb any
        // ongoing communication on the RS485 bus; Tx will be started as soon as we enter
        // Active state
        fs_vFullTxDisable(fp_psState);
        fs_vFullRxEnable(fp_psState);

        MAC_TIM_vMicroTimerCancel(fp_psState->psCfg->sHwConfig.eTXTIMID, SUPPRESS_TIMER_CANCEL_CBK);

        MAC_TIM_vMicroTimerStart(fp_psState->psCfg->sHwConfig.eTXTIMID, fs_u32CalcTXPrioTime(fp_psState),
                                 fs_vTXWaitCallback, fp_psState);
    }
    else
    {
        MACDRV_DBG_ASSERT(false);
    }
}

STATIC void fs_vFullRxEnable(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    if(fp_psState->psCfg->pfEnableRX != NULL && !fp_psState->sRXCtx.bRS485BusReceiveEnabled)
    {
        fp_psState->psCfg->pfEnableRX();
        fp_psState->sRXCtx.bRS485BusReceiveEnabled = true;
    }
    LL_USART_EnableDirectionRx(fp_psState->psCfg->sHwConfig.psUART);
    LL_USART_EnableIT_RXNE(fp_psState->psCfg->sHwConfig.psUART);
}

STATIC void fs_vFullTxDisable(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    if(fp_psState->psCfg->pfDisableTX != NULL && fp_psState->sTXCtx.bRS485BusDriverEnabled)
    {
        fp_psState->psCfg->pfDisableTX();
        fp_psState->sTXCtx.bRS485BusDriverEnabled = false;
    }

    LL_USART_DisableIT_TXE(fp_psState->psCfg->sHwConfig.psUART);
}

STATIC void fs_vTXState_Idle(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    fs_vFullTxDisable(fp_psState);
    fs_vFullRxEnable(fp_psState);
}

STATIC void fs_vTXState_Active(sMACInterfaceState_t * fp_psState)
{
    ESSATMAC_Message *psMsg;

    // Disable nRE Signal from the RS485 transceiver to avoid receiving echo from the RS-485 transceiver
    if(fp_psState->psCfg->pfDisableRX != NULL)
    {
        fp_psState->psCfg->pfDisableRX();
        fp_psState->sRXCtx.bRS485BusReceiveEnabled = false;
    }

    MACDRV_DBG_ASSERT(fp_psState != NULL);

    psMsg = &fp_psState->sTXCtx.psMsgEntry->sMessage;

    MACDRV_DBG_ASSERT(psMsg != NULL);

    MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_TxOpStarted);

    fp_psState->sTXCtx.asTXCmds[0U].pu8TXData = &psMsg->u8SourceAddr;
    fp_psState->sTXCtx.asTXCmds[0U].u32TXSize = ESSATMAC_HEADER_SIZE - sizeof(psMsg->u8TargetAddr);
    fp_psState->sTXCtx.asTXCmds[0U].u32TXCount = 0U;
    fp_psState->sTXCtx.asTXCmds[1U].pu8TXData = psMsg->au8Data;
    fp_psState->sTXCtx.asTXCmds[1U].u32TXSize = psMsg->u8DataSize;
    fp_psState->sTXCtx.asTXCmds[1U].u32TXCount = 0U;
    fp_psState->sTXCtx.asTXCmds[2U].pu8TXData = (uint8_t *) & psMsg->u32CRC;
    fp_psState->sTXCtx.asTXCmds[2U].u32TXSize = sizeof(psMsg->u32CRC);
    fp_psState->sTXCtx.asTXCmds[2U].u32TXCount = 0U;
    fp_psState->sTXCtx.u16TXCmdCount = 3U;
    fp_psState->sTXCtx.u16TXCmdIdx = 0U;
    fp_psState->sTXCtx.u32TxTimeSingle = 0U;

    // Enable USART interrupts and reset flags
    LL_USART_EnableDirectionTx(fp_psState->psCfg->sHwConfig.psUART);
    LL_USART_EnableIT_TXE(fp_psState->psCfg->sHwConfig.psUART);

    // Enable the DE signal
    if(fp_psState->psCfg->pfEnableTX != NULL)
    {
        fp_psState->psCfg->pfEnableTX();
        fp_psState->sTXCtx.bRS485BusDriverEnabled = true;
    }

    // Start the transmission by sending the destination address
    LL_USART_TransmitData9(fp_psState->psCfg->sHwConfig.psUART, (psMsg->u8TargetAddr | MAC_ADDRESS_MASK));
}

STATIC void fs_vTXState_ProcessNext(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    // Clear the message we just processed
    if(fp_psState->sTXCtx.psMsgEntry != NULL)
    {
        MAC_QUEUE_vTXQueueComplete(fp_psState->sTXCtx.psMsgEntry, fp_psState->sTXCtx.bSent);
        MAC_POOL_vPoolTXFree(fp_psState, fp_psState->sTXCtx.psMsgEntry);
    }

    // Get the next message from the queue
    fp_psState->sTXCtx.psMsgEntry = MAC_QUEUE_vTXQueuePop(fp_psState);

    if(fp_psState->sTXCtx.psMsgEntry == NULL)
    {
        POST_TX_SM_EVENT(eTXEvent_QueueEmptied);
    }
    else
    {
        fp_psState->sTXCtx.bSent = false;
        POST_TX_SM_EVENT(eTXEvent_NewMessage);
    }
}

STATIC void fs_vTXState_Retry(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    // If the max TX timeouts, increase priority of the interface by 1TQ
    if((HAL_GetTick() - fp_psState->sTXCtx.u32TxWaitTimeout) >= RS485_MAX_TX_WAIT_TIMEOUT)
    {
        MAC_Stats_triggerEvent(fp_psState->macStats, eMACStatId_TxTimeoutCntr);

        if(fp_psState->sTXCtx.u16TxRetries < RS485_MAX_TX_RETRY_COUNT)
        {
            // Increse dynamic priority by 1TQ
            fs_vIncDynPriority();

            // Keep count of the retries
            fp_psState->sTXCtx.u16TxRetries++;

            // Restart global Tx timeout tracking
            fp_psState->sTXCtx.u32TxWaitTimeout = (uint32_t) HAL_GetTick();

            // Retry Event
            POST_TX_SM_EVENT(eTXEvent_Retry);

        }
        else                    // Message transmission didn't succeed and all retries were exhausted
        {
            // Set the failure flag.
            fp_psState->sTXCtx.bSent = false;

            // Process the next message.
            POST_TX_SM_EVENT(eTXEvent_NewMessage);
        }
    }
    else
    {
        // Tx global timeout hasn't yet elapsed, hence continue sending
        POST_TX_SM_EVENT(eTXEvent_Retry);
    }
}

STATIC void fs_vTXState_ProcessEvent(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    fp_psState->sTXCtx.u8NestLevel++;

    while(fp_psState->sTXCtx.eStateEvent != eTXEvent_None)
    {
        switch (fp_psState->sTXCtx.eState)
        {
        case (eMACTransmit_Off):
            fs_vInitDynPriority();
            break;

        case (eMACTransmit_Idle):
            if(fp_psState->sTXCtx.eStateEvent == eTXEvent_NewMessage)
            {
                fp_psState->sTXCtx.eState = eMACTransmit_ProcessNext;
            }

            break;

        case (eMACTransmit_WaitPriority):
            if((fp_psState->sTXCtx.eStateEvent == eTXEvent_BusBusy) ||
               (fp_psState->sTXCtx.eStateEvent == eTXEvent_CollisionDetected))
            {
                if(fp_psState->sTXCtx.psMsgEntry != NULL)
                {
                    MAC_TIM_vMicroTimerCancel(fp_psState->psCfg->sHwConfig.eTXTIMID, CALL_TIMER_CANCEL_CBK);

                    fp_psState->sTXCtx.eState = eMACTransmit_Retry;
                }
                else
                    fp_psState->sTXCtx.eState = eMACTransmit_Idle;
            }
            else if(fp_psState->sTXCtx.eStateEvent == eTXEvent_PriorityWaitFinished)
            {
                // Priority wait finished but we may have already started receiving some message...
                if((fp_psState->sRXCtx.eState != eMACReceive_ReadHeader)
                   && (fp_psState->sRXCtx.eState != eMACReceive_ReadData)
                   && (fp_psState->sRXCtx.eState != eMACReceive_ReadCRC))
                    fp_psState->sTXCtx.eState = eMACTransmit_Active;
                else
                {
                    fp_psState->sTXCtx.eState = eMACTransmit_Retry;
                }
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sTXCtx.eState,
                                         fp_psState->sTXCtx.eStateEvent, fp_psState->sTXCtx.u8NestLevel);

            break;

        case (eMACTransmit_Active):
            if(fp_psState->sTXCtx.eStateEvent == eTXEvent_CollisionDetected)
            {
                // Something interrupted the transfer, we may need to reactivate the RX
                MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_TxOpFinished);
                fp_psState->sTXCtx.eState = eMACTransmit_Retry;
            }
            else if(fp_psState->sTXCtx.eStateEvent == eTXEvent_MessageSendFinished)
            {
                // Reset global TX timeout and retries when a new transfer is about to start
                fp_psState->sTXCtx.u32TxWaitTimeout = (uint32_t) HAL_GetTick();
                fp_psState->sTXCtx.u16TxRetries = (uint16_t) 0;

                fp_psState->sTXCtx.eState = eMACTransmit_ProcessNext;
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sTXCtx.eState,
                                         fp_psState->sTXCtx.eStateEvent, fp_psState->sTXCtx.u8NestLevel);

            break;

        case (eMACTransmit_ProcessNext):
            if(fp_psState->sTXCtx.eStateEvent == eTXEvent_QueueEmptied)
            {
                fp_psState->sTXCtx.eState = eMACTransmit_Idle;
            }
            else if((fp_psState->sTXCtx.eStateEvent == eTXEvent_NewMessage)
                    || (fp_psState->sTXCtx.eStateEvent == eTXEvent_BusBusy)
                    || (fp_psState->sTXCtx.eStateEvent == eTXEvent_CollisionDetected))
            {
                fp_psState->sTXCtx.eState = eMACTransmit_WaitPriority;
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sTXCtx.eState,
                                         fp_psState->sTXCtx.eStateEvent, fp_psState->sTXCtx.u8NestLevel);

            break;

        case (eMACTransmit_Retry):
            if(fp_psState->sTXCtx.eStateEvent == eTXEvent_Retry)
            {
                fp_psState->sTXCtx.eState = eMACTransmit_WaitPriority;
            }
            else if(fp_psState->sTXCtx.eStateEvent == eTXEvent_NewMessage)
            {
                fp_psState->sTXCtx.eState = eMACTransmit_ProcessNext;
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sTXCtx.eState,
                                         fp_psState->sTXCtx.eStateEvent, fp_psState->sTXCtx.u8NestLevel);

            break;

        default:
            MACDRV_DBG_ASSERT(false);

            break;
        }

        RS_STORE_STATE(fp_psState->macIfId, fp_psState->sTXCtx.ePrevState,
                       fp_psState->sTXCtx.eState, fp_psState->sTXCtx.eStateEvent);

        fp_psState->sTXCtx.eStateEvent = eTXEvent_None;

        if(fp_psState->sTXCtx.ePrevState != fp_psState->sTXCtx.eState)
        {
            // After transition to the state, do the corresponding state processing
            switch (fp_psState->sTXCtx.eState)
            {
            case (eMACTransmit_Off):
                break;

            case (eMACTransmit_Idle):
                fs_vTXState_Idle(fp_psState);
                break;

            case (eMACTransmit_WaitPriority):
                fs_vTXState_WaitPriority(fp_psState);
                break;

            case (eMACTransmit_Active):
                fs_vTXState_Active(fp_psState);
                break;

            case (eMACTransmit_ProcessNext):
                fs_vTXState_ProcessNext(fp_psState);
                break;

            case (eMACTransmit_Retry):
                fs_vTXState_Retry(fp_psState);
                break;

            default:
                MACDRV_DBG_ASSERT(false);
                break;
            }

            fp_psState->sTXCtx.ePrevState = fp_psState->sTXCtx.eState;
        }
    }

    if(fp_psState->sTXCtx.u8NestLevel > 0U)
        --fp_psState->sTXCtx.u8NestLevel;
}

STATIC uint32_t fs_u32CalcTXPrioTime(sMACInterfaceState_t * fp_psState)
{
    uint32_t u32Time = MAC_PRIORITY_INVALID;

    sMACTXPoolEntry_t *psMsg;

    uint16_t u16ActualMsgPriority = (uint16_t) 0;

    MACDRV_DBG_ASSERT(fp_psState != NULL);

    psMsg = fp_psState->sTXCtx.psMsgEntry;

    MACDRV_DBG_ASSERT(psMsg != NULL);

    // If the calculated dynamic priority value is lower than the message priority value,
    // use the higher priority to improve bus throughput (lower value means higher priority)
    u16ActualMsgPriority = (u16DynamicPriorityValue < (uint16_t) psMsg->sPrio.u8Priority) ?
        u16DynamicPriorityValue : (uint16_t) psMsg->sPrio.u8Priority;

    uint32_t u32RandomTime =
        MAC_RNG_GetRandomNumberInRange(RS485_MAX_RND_TIME_VALUE * (uint32_t) fp_psState->psCfg->sHwConfig.u16TQVal);

    u32Time = (uint32_t) psMsg->sPrio.u8BasePriority * (uint32_t) fp_psState->psCfg->sHwConfig.u16TQVal +
        (uint32_t) u16ActualMsgPriority *(uint32_t) fp_psState->psCfg->sHwConfig.u16TQVal + u32RandomTime;

    return u32Time;
}
