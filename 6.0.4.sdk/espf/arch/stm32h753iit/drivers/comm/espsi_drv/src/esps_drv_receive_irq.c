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
 * @file     esps_drv_receive_irq.c
 * @brief    MAC driver RX management implementation
 *
 * @}
 */

// External imports
#include "esps_drv_stm32.h"
#include "esps_drv_esps_stack.h"

#include "crc16-ccitt.h"
#include "esps_drv_dispatcher.h"
#include "esps_drv_irq.h"
#include "esps_drv_pool.h"
#include "esps_drv_tim.h"
#include "esps_drv_exeh.h"
#include "esps_drv_debug.h"

// Necessary definitions for esps_drv_sm_debug.h
#define STATE_TYPE      eMACReceiveState_t
#define EVENT_TYPE      eRXEvent_t
#define INSTANCE_NAME   MacRxRuntimeStats
#include "esps_drv_sm_debug.h"

/******************************************************************************
 * File Local Preprocessor Definitions
 *****************************************************************************/
#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_MAC_RECEIVE_IRQ)
#define POST_RX_SM_EVENT(evt)       fp_psState->sRXCtx.eStateEvent = (evt)

/******************************************************************************
 * File Local Function Prototypes
 *****************************************************************************/
/**
 * Timer callback used when waiting for reception.
 *
 * @param fp_eStatus - Status of the wait (canceled/expired)
 * @param fp_pvData  - The data delivered with the timer.
 */
STATIC void fs_vRXWaitCallback(eTIMTimerStatus_t fp_eStatus, void *fp_pvData);

/**
 * Calculate the reception timeout based on the amount of data expected to
 * be received.
 *
 * @param fp_psState     - MAC interface state.
 * @param fp_u32DataSize - Size of the data.
 * @return U32: Time in microseconds to wait for the data.
 */
STATIC uint32_t fs_u32CalcRXTimeout(sMACInterfaceState_t * fp_psState, uint32_t fp_u32DataSize);

/**
 * Idle state processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_Idle(sMACInterfaceState_t * fp_psState);

/**
 * NewMessage state processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_NewMessage(sMACInterfaceState_t * fp_psState);

/**
 * WaitAddress state processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_WaitAddress(sMACInterfaceState_t * fp_psState);

/**
 * ReadHeader state processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_ReadHeader(sMACInterfaceState_t * fp_psState);

/**
 * ReadData state processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_ReadData(sMACInterfaceState_t * fp_psState);

/**
 * ReadCRC state processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_ReadCRC(sMACInterfaceState_t * fp_psState);

/**
 * Checks if the MAC header CRC matches the received value
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC bool fs_isHeaderCrcValid(sMACInterfaceState_t * fp_psState);

/**
 * DispatchMessage state processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_DispatchMessage(sMACInterfaceState_t * fp_psState);

/**
 * State event processing function.
 *
 * @param fp_psState - MAC interface state reference.
 */
STATIC void fs_vRXState_ProcessEvent(sMACInterfaceState_t * fp_psState);

/// RX Indication in the UART bus
void MAC_IRQ_vRXIndication(sMACInterfaceState_t * fp_psState)
{
    sMACReceiveCmd_t *psCmd;

    TD_VOLATILE(uint16_t) u16Data = 0U;
    sMACRXPoolEntry_t *psMsg;

    if(fp_psState == NULL)
    {
        EXEH_HANDLE(eEXEHSeverity_Warning, eMACException_InvalidParameter);
        return;
    }

    psCmd = &fp_psState->sRXCtx.sRXCmd;
    psMsg = fp_psState->sRXCtx.psMsgEntry;

    u16Data = LL_USART_ReceiveData9(fp_psState->psCfg->sHwConfig.psUART) & 0x01FFU;

    if((u16Data & MAC_ADDRESS_MASK) == MAC_ADDRESS_MASK)
    {
        if(psMsg != NULL)
        {
            psMsg->sMessage.u8TargetAddr = (uint8_t) u16Data;

            MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_AddressReceived);
        }
    }
    else
    {
        if((fp_psState->sRXCtx.eState == eMACReceive_ReadHeader) ||
           (fp_psState->sRXCtx.eState == eMACReceive_ReadData) ||
           (fp_psState->sRXCtx.eState == eMACReceive_ReadCRC) || (psCmd->u32RXCount > (uint32_t) 0))
        {
            if(psCmd->u32RXCount < psCmd->u32RXSize)
            {
                psCmd->pu8RXData[psCmd->u32RXCount] = (uint8_t) u16Data;
                ++psCmd->u32RXCount;
            }

            if(psCmd->u32RXCount >= psCmd->u32RXSize)
                MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_ReceptionComplete);
        }
    }

    MAC_IRQ_vTXProcessEvent(fp_psState, eTXEvent_BusBusy);
}

/// RX start reception indication in the UART bus
void MAC_IRQ_vRXStartIndication(sMACInterfaceState_t * fp_psState)
{
    if(fp_psState != NULL)
    {
        LL_USART_DisableIT_IDLE(fp_psState->psCfg->sHwConfig.psUART);
        LL_USART_EnableIT_ERROR(fp_psState->psCfg->sHwConfig.psUART);
        MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_Activated);
    }
    else
        EXEH_HANDLE(eEXEHSeverity_Warning, eMACException_InvalidParameter);
}

/// Process a new event in the RX state machine
void MAC_IRQ_vRXProcessEvent(sMACInterfaceState_t * fp_psState, eRXEvent_t evt)
{
    if(fp_psState != NULL)
    {
        POST_RX_SM_EVENT(evt);
        fs_vRXState_ProcessEvent(fp_psState);
    }
    else
        EXEH_HANDLE(eEXEHSeverity_Warning, eMACException_InvalidParameter);
}

/******************************************************************************
 * File Local Function Definitions
 *****************************************************************************/
STATIC void fs_vRXWaitCallback(eTIMTimerStatus_t fp_eStatus, void *fp_pvData)
{
    sMACInterfaceState_t *psState = (sMACInterfaceState_t *) fp_pvData;

    MACDRV_DBG_ASSERT(fp_pvData != NULL);

    switch (fp_eStatus)
    {
    case (eTIMTimer_Expired):
        MAC_Stats_triggerEvent(psState->macStats, eMACStatId_RxTimeoutCntr);

        // Some operation has timed out, process the event.
        MAC_IRQ_vRXProcessEvent(psState, eRXEvent_WaitTimeout);
        break;

    case (eTIMTimer_Canceled):
        // Accumulate time for cancelled events because this means, reception occurred as expected
        psState->sRXCtx.u32RxTimeSingle += MAC_TIM_vMicroTimerGetElapsed(psState->psCfg->sHwConfig.eRXTIMID);
        break;

    default:
        MACDRV_DBG_ASSERT(false);
        break;
    }
}

STATIC void fs_vRXState_Idle(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    fp_psState->sRXCtx.psMsgEntry = NULL;
    POST_RX_SM_EVENT(eRXEvent_Activated);
}

STATIC void fs_vRXState_NewMessage(sMACInterfaceState_t * fp_psState)
{
    sMACRXPoolEntry_t *psNewMsg = (sMACRXPoolEntry_t *) NULL;

    MACDRV_DBG_ASSERT(fp_psState != NULL);

    psNewMsg = (fp_psState->sRXCtx.psMsgEntry != NULL) ?
        (fp_psState->sRXCtx.psMsgEntry) : (MAC_POOL_psPoolRXNew(fp_psState));

    if(psNewMsg == NULL)
    {
        MAC_Stats_triggerEvent(fp_psState->macStats, eMACStatId_RxMsgBufUnavailCntr);

        // start the timer to retry allocating a new message at a later time.
        MAC_TIM_vMicroTimerStart(fp_psState->psCfg->sHwConfig.eRXTIMID, MAC_WAIT_POOLMEMORY_TIME, fs_vRXWaitCallback,
                                 fp_psState);

        LL_USART_DisableDirectionRx(fp_psState->psCfg->sHwConfig.psUART);
        LL_USART_DisableIT_RXNE(fp_psState->psCfg->sHwConfig.psUART);
    }
    else
    {
        LL_USART_EnableDirectionRx(fp_psState->psCfg->sHwConfig.psUART);
        LL_USART_EnableIT_RXNE(fp_psState->psCfg->sHwConfig.psUART);

        fp_psState->sRXCtx.psMsgEntry = psNewMsg;
        POST_RX_SM_EVENT(eRXEvent_NewMessage);
        fp_psState->sRXCtx.sRXCmd.u32RXCount = (uint8_t) 0;
    }
}

STATIC void fs_vRXState_WaitAddress(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    // Make sure the reception is enabled
    if(fp_psState->psCfg->pfEnableRX == NULL)
        EXEH_HANDLE(eEXEHSeverity_Fatal, eMACException_InitFailed);
    if(!fp_psState->sRXCtx.bRS485BusReceiveEnabled)
    {
        fp_psState->psCfg->pfEnableRX();
        fp_psState->sRXCtx.bRS485BusReceiveEnabled = true;
    }

    fp_psState->sRXCtx.u32RxTimeSingle = 0U;
    fp_psState->sRXCtx.sRXCmd.u32RXCount = 0U;
}

STATIC void fs_vRXState_ReadHeader(sMACInterfaceState_t * fp_psState)
{
    ESSATMAC_Message *psMsg;

    uint32_t u32DataSize;

    uint32_t u32ReadTimeout;

    MACDRV_DBG_ASSERT(fp_psState != NULL);

    psMsg = &fp_psState->sRXCtx.psMsgEntry->sMessage;

    MACDRV_DBG_ASSERT(psMsg != NULL);

    // target address is received first and is not included in subsequently expected bytes to be received
    u32DataSize = ESSATMAC_HEADER_SIZE - sizeof(psMsg->u8TargetAddr);
    u32ReadTimeout = fs_u32CalcRXTimeout(fp_psState, u32DataSize);

    MAC_TIM_vMicroTimerCancel(fp_psState->psCfg->sHwConfig.eRXTIMID, CALL_TIMER_CANCEL_CBK);

    // Setup the RX command to read the header.
    fp_psState->sRXCtx.sRXCmd.u32RXCount = 0U;
    fp_psState->sRXCtx.sRXCmd.pu8RXData = (uint8_t *) & psMsg->u8SourceAddr;
    fp_psState->sRXCtx.sRXCmd.u32RXSize = u32DataSize;

    MAC_TIM_vMicroTimerStart(fp_psState->psCfg->sHwConfig.eRXTIMID, u32ReadTimeout, fs_vRXWaitCallback, fp_psState);
}

STATIC void fs_vRXState_ReadData(sMACInterfaceState_t * fp_psState)
{
    ESSATMAC_Message *psMsg;

    uint32_t u32DataSize;

    uint32_t u32ReadTimeout;

    MACDRV_DBG_ASSERT(fp_psState != NULL);

    psMsg = &fp_psState->sRXCtx.psMsgEntry->sMessage;

    MACDRV_DBG_ASSERT(psMsg != NULL);

    u32DataSize = psMsg->u8DataSize;
    u32ReadTimeout = fs_u32CalcRXTimeout(fp_psState, u32DataSize);

    MAC_TIM_vMicroTimerCancel(fp_psState->psCfg->sHwConfig.eRXTIMID, CALL_TIMER_CANCEL_CBK);

    // setup the RX command to read the data
    fp_psState->sRXCtx.sRXCmd.u32RXCount = 0U;
    fp_psState->sRXCtx.sRXCmd.pu8RXData = psMsg->au8Data;
    fp_psState->sRXCtx.sRXCmd.u32RXSize = u32DataSize;

    MAC_TIM_vMicroTimerStart(fp_psState->psCfg->sHwConfig.eRXTIMID, u32ReadTimeout, fs_vRXWaitCallback, fp_psState);
}

STATIC void fs_vRXState_ReadCRC(sMACInterfaceState_t * fp_psState)
{
    ESSATMAC_Message *psMsg;

    uint32_t u32DataSize;

    uint32_t u32ReadTimeout;

    MACDRV_DBG_ASSERT(fp_psState != NULL);

    psMsg = &fp_psState->sRXCtx.psMsgEntry->sMessage;

    MACDRV_DBG_ASSERT(psMsg != NULL);

    u32DataSize = sizeof(psMsg->u32CRC);
    u32ReadTimeout = fs_u32CalcRXTimeout(fp_psState, u32DataSize);

    // Cancel the timer.
    MAC_TIM_vMicroTimerCancel(fp_psState->psCfg->sHwConfig.eRXTIMID, CALL_TIMER_CANCEL_CBK);

    // Prepare the command list to read the header
    fp_psState->sRXCtx.sRXCmd.u32RXCount = 0U;
    fp_psState->sRXCtx.sRXCmd.pu8RXData = (uint8_t *) & psMsg->u32CRC;
    fp_psState->sRXCtx.sRXCmd.u32RXSize = u32DataSize;

    // Start the timer
    MAC_TIM_vMicroTimerStart(fp_psState->psCfg->sHwConfig.eRXTIMID, u32ReadTimeout, fs_vRXWaitCallback, fp_psState);
}

STATIC bool fs_isHeaderCrcValid(sMACInterfaceState_t * fp_psState)
{
    uint16_t u16HdrCRC;

    MACDRV_DBG_ASSERT(fp_psState != NULL);

    u16HdrCRC = crc16_ccitt_table((const uint8_t *)&fp_psState->sRXCtx.psMsgEntry->sMessage,
                                  ESSATMAC_HEADER_SIZE - sizeof(fp_psState->sRXCtx.psMsgEntry->sMessage.uHdrCRC16));

    return (u16HdrCRC == fp_psState->sRXCtx.psMsgEntry->sMessage.uHdrCRC16);
}

/// DispatchMessage state.
STATIC void fs_vRXState_DispatchMessage(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    MAC_TIM_vMicroTimerCancel(fp_psState->psCfg->sHwConfig.eRXTIMID, CALL_TIMER_CANCEL_CBK);

    MAC_Stats_storeEventMax(fp_psState->macStats, eMACStatId_MaxRxTime, fp_psState->sRXCtx.u32RxTimeSingle);
    fp_psState->sRXCtx.u32RxTimeSingle = 0U;

    // sanity check -> process only messages which are not sent by this module
    if(fp_psState->sRXCtx.psMsgEntry->sMessage.u8SourceAddr != fp_psState->u16Address)
    {
        MAC_Stats_triggerMultiEvent(fp_psState->macStats,
                                    eMACStatId_TotalRxBytes,
                                    ESSATMAC_HEADER_SIZE +
                                    fp_psState->sRXCtx.psMsgEntry->sMessage.u8DataSize +
                                    sizeof(fp_psState->sRXCtx.psMsgEntry->sMessage.u32CRC));

        MAC_DISP_bDispatchQueueAdd(&fp_psState->sDisp, fp_psState->sRXCtx.psMsgEntry);
    }
    else
    {
        // ensure that RX memory pool for the discarded message is released
        MAC_POOL_vPoolRXFree(fp_psState, fp_psState->sRXCtx.psMsgEntry);
    }

    fp_psState->sRXCtx.psMsgEntry = NULL;
    fp_psState->sRXCtx.sRXCmd.pu8RXData = NULL;
    fp_psState->sRXCtx.sRXCmd.u32RXCount = 0U;
    fp_psState->sRXCtx.sRXCmd.u32RXSize = 0U;

    POST_RX_SM_EVENT(eRXEvent_MessageDispatched);
}

/// UART event processing function without recursion.
STATIC void fs_vRXState_ProcessEvent(sMACInterfaceState_t * fp_psState)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    fp_psState->sRXCtx.u8NestLevel++;

    while(fp_psState->sRXCtx.eStateEvent != eRXEvent_None)
    {
        switch (fp_psState->sRXCtx.eState)
        {
        case eMACReceive_Off:
            break;

        case (eMACReceive_Idle):
            if(fp_psState->sRXCtx.eStateEvent == eRXEvent_Activated)
            {
                fp_psState->sRXCtx.eState = eMACReceive_NewMessage;
            }
            break;

        case (eMACReceive_NewMessage):
            if(fp_psState->sRXCtx.eStateEvent == eRXEvent_NewMessage)
            {
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_WaitTimeout)
            {
                fp_psState->sRXCtx.eState = eMACReceive_NewMessage;

                // call state function explicitly because there is no state change in this case
                fs_vRXState_NewMessage(fp_psState);
            }
            else
            {
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sRXCtx.eState,
                                         fp_psState->sRXCtx.eStateEvent, fp_psState->sRXCtx.u8NestLevel);

                fp_psState->sRXCtx.eState = eMACReceive_NewMessage;

                // call state function explicitly because there is no state change in this case
                fs_vRXState_NewMessage(fp_psState);
            }

            break;

        case (eMACReceive_WaitAddress):
            if(fp_psState->sRXCtx.eStateEvent == eRXEvent_AddressReceived)
            {
                if((fp_psState->sRXCtx.psMsgEntry->sMessage.u8TargetAddr == fp_psState->u16Address)
                   || (fp_psState->sRXCtx.psMsgEntry->sMessage.u8TargetAddr == ESSATMAC_ADDR_BROADCAST)
                   || (fp_psState->sRXCtx.psMsgEntry->sMessage.u8TargetAddr == ESSATMAC_ADDR_GATEWAY_DEV))
                {
                    fp_psState->sRXCtx.eState = eMACReceive_ReadHeader;
                }
            }
            else if((fp_psState->sRXCtx.eStateEvent == eRXEvent_TxOpStarted)
                    || (fp_psState->sRXCtx.eStateEvent == eRXEvent_TxOpFinished))
            {
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;

                // Call state function explicitly because there is no state change in this case
                fs_vRXState_WaitAddress(fp_psState);
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sRXCtx.eState,
                                         fp_psState->sRXCtx.eStateEvent, fp_psState->sRXCtx.u8NestLevel);

            break;

        case (eMACReceive_ReadHeader):
            if(fp_psState->sRXCtx.eStateEvent == eRXEvent_ReceptionComplete)
            {
                if(fs_isHeaderCrcValid(fp_psState))
                    fp_psState->sRXCtx.eState = eMACReceive_ReadData;
                else            // if header CRC is invalid, then reset state machine back to WaitAddress state
                {
                    MAC_Stats_triggerEvent(fp_psState->macStats, eMACStatId_InvalidHeaderCRCCntr);

                    fp_psState->sRXCtx.psMsgEntry->sMessage.u8TargetAddr = (uint8_t) 0;
                    fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
                }
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_WaitTimeout)
            {
                fp_psState->sRXCtx.psMsgEntry->sMessage.u8TargetAddr = (uint8_t) 0;
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_AddressReceived)
            {
                fp_psState->sRXCtx.eState = eMACReceive_ReadHeader;

                // re-arm timers here since state doesn't actually change
                fs_vRXState_ReadHeader(fp_psState);
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_RxError)
            {
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sRXCtx.eState,
                                         fp_psState->sRXCtx.eStateEvent, fp_psState->sRXCtx.u8NestLevel);

            break;

        case (eMACReceive_ReadData):
            if(fp_psState->sRXCtx.eStateEvent == eRXEvent_ReceptionComplete)
            {
                fp_psState->sRXCtx.eState = eMACReceive_ReadCRC;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_WaitTimeout)
            {
                fp_psState->sRXCtx.psMsgEntry->sMessage.u8TargetAddr = (uint8_t) 0;
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_AddressReceived)
            {
                fp_psState->sRXCtx.eState = eMACReceive_ReadHeader;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_RxError)
            {
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sRXCtx.eState,
                                         fp_psState->sRXCtx.eStateEvent, fp_psState->sRXCtx.u8NestLevel);

            break;

        case (eMACReceive_ReadCRC):
            if(fp_psState->sRXCtx.eStateEvent == eRXEvent_ReceptionComplete)
            {
                fp_psState->sRXCtx.eState = eMACReceive_DispatchMessage;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_WaitTimeout)
            {
                fp_psState->sRXCtx.psMsgEntry->sMessage.u8TargetAddr = (uint8_t) 0;
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_AddressReceived)
            {
                fp_psState->sRXCtx.eState = eMACReceive_ReadHeader;
            }
            else if(fp_psState->sRXCtx.eStateEvent == eRXEvent_RxError)
            {
                fp_psState->sRXCtx.eState = eMACReceive_WaitAddress;
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sRXCtx.eState,
                                         fp_psState->sRXCtx.eStateEvent, fp_psState->sRXCtx.u8NestLevel);

            break;

        case (eMACReceive_DispatchMessage):
            if(fp_psState->sRXCtx.eStateEvent == eRXEvent_MessageDispatched)
            {
                fp_psState->sRXCtx.eState = eMACReceive_NewMessage;
            }
            else
                RS_STORE_UNHANDLED_EVENT(fp_psState->macIfId,
                                         fp_psState->sRXCtx.eState,
                                         fp_psState->sRXCtx.eStateEvent, fp_psState->sRXCtx.u8NestLevel);
            break;

        default:
            MACDRV_DBG_ASSERT(false);
            break;
        }

        RS_STORE_STATE(fp_psState->macIfId,
                       fp_psState->sRXCtx.ePrevState, fp_psState->sRXCtx.eState, fp_psState->sRXCtx.eStateEvent);

        POST_RX_SM_EVENT(eRXEvent_None);

        if(fp_psState->sRXCtx.ePrevState != fp_psState->sRXCtx.eState)
        {
            // Execute state on-entry functions...
            switch (fp_psState->sRXCtx.eState)
            {
            case (eMACReceive_Off):
                break;

            case (eMACReceive_Idle):
                fs_vRXState_Idle(fp_psState);
                break;

            case (eMACReceive_NewMessage):
                fs_vRXState_NewMessage(fp_psState);
                break;

            case (eMACReceive_WaitAddress):
                fs_vRXState_WaitAddress(fp_psState);
                break;

            case (eMACReceive_ReadHeader):
                fs_vRXState_ReadHeader(fp_psState);
                break;

            case (eMACReceive_ReadData):
                fs_vRXState_ReadData(fp_psState);
                break;

            case (eMACReceive_ReadCRC):
                fs_vRXState_ReadCRC(fp_psState);
                break;

            case (eMACReceive_DispatchMessage):
                fs_vRXState_DispatchMessage(fp_psState);
                break;

            default:
                MACDRV_DBG_ASSERT(false);
                break;
            }

            fp_psState->sRXCtx.ePrevState = fp_psState->sRXCtx.eState;
        }
    }
    if(fp_psState->sRXCtx.u8NestLevel > 0U)
        --fp_psState->sRXCtx.u8NestLevel;
}

/// Calculate RX timeout based on expected data and the time quantum.
STATIC uint32_t fs_u32CalcRXTimeout(sMACInterfaceState_t * fp_psState, uint32_t fp_u32DataSize)
{
    MACDRV_DBG_ASSERT(fp_psState != NULL);

    return (fp_u32DataSize * fp_psState->psCfg->sHwConfig.u16TQVal);
}
