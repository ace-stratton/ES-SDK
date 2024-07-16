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
 * @file     esps_drv.c
 * @brief    MAC interface functions definition
 *
 * @}
 */

#include <string.h>
#include <assert.h>

// External imports
#include "esps_drv_config.h"
#include "esps_drv_esps_stack.h"

#include "crc16-ccitt.h"
#include "MACCRC32_Classic_Impl.h"
#include "esps_drv.h"
#include "esps_drv_dispatcher.h"
#include "esps_drv_irq.h"
#include "esps_drv_pool.h"
#include "esps_drv_queue.h"
#include "esps_drv_rng.h"
#include "esps_drv_exeh.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_MAC)

/**
 * Private function to initialize a MAC interface state.
 *
 * @param fp_psState    - reference to interface to initialize;
 * @param fp_eInterface - ID of the interface;
 * @param fp_eInitType     - type of init to be performed
 */
STATIC void fs_vInitInterface(sMACInterfaceState_t * fp_psState,
                              eMACInterface_t fp_eInterface, const eMAC_Interface_InitType_t fp_eInitType);

/**
 * Private function to de-initialize a MAC interface.
 *
 * @param fp_psState    - reference to interface to initialize.
 * @param fp_eInterface - ID of the interface.
 */
STATIC void fs_vDeinitInterface(sMACInterfaceState_t * fp_psState, eMACInterface_t fp_eInterface);

/**
 * Private function to enable reception for a USART/UART peripheral
 * described by the configuration in the MAC interface state.
 *
 * @param fp_psState - interface state to enable reception.
 */
STATIC void fs_vEnableReception(sMACInterfaceState_t * fp_psState);

/**
 * Callback function to make sure the timers are properly initialized
 *
 * @param fp_eStatus status of the expired timer
 * @param fp_pvData  callback to process the expired timer
 */
STATIC void fs_vTIMCallback(eTIMTimerStatus_t fp_eStatus, void *fp_pvData);

/**
 * Function to update the CRC in a MAC message. Calculates the CRC
 * and sets it in the message.
 *
 * @param fp_psEntry - the TX pool entry to update the CRC for.
 */
STATIC void fs_vUpdateCRC(sMACTXPoolEntry_t * fp_psEntry);

bool MAC_bCoreInit(void)
{
    MAC_RNG_Init();
    return MAC_TIM_bInit();
}

bool MAC_bCoreDeinit(void)
{
    MAC_RNG_DeInit();
    return MAC_TIM_bDeinit();
}

bool MAC_bStartAllIfs(const eMAC_Interface_InitType_t fp_eInitType)
{
    bool res = true;

    uint8_t i;

    MAC_bCoreInit();

    for(i = 0; i < eMAC_Interface_Count; i++)
    {
        MacCfg_vApplyMacAddrConfig((eMACInterface_t) i, MacCfg_u8GetMacAddress(i));
        res &= MAC_bStart(i, fp_eInitType);
    }

    return res;
}

bool MAC_bStopAllIfs(void)
{
    bool res = true;

    uint8_t i;

    for(i = 0; i < eMAC_Interface_Count; i++)
        res &= MAC_bStop(i);

    MAC_bCoreDeinit();

    return res;
}

bool MAC_bStart(eMACInterface_t fp_eInterface, const eMAC_Interface_InitType_t fp_eInitType)
{
    bool bStartOK = false;

    sMACInterfaceState_t *pMacIntf = NULL;

    if(fp_eInterface >= eMAC_Interface_Count)
    {
        EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        pMacIntf = MacCfg_sGetMacInterfaceById(fp_eInterface);

        assert(pMacIntf != NULL);

        fs_vInitInterface(pMacIntf, fp_eInterface, fp_eInitType);

        if(!pMacIntf->bInitDone)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_InitFailed);
        }
        else
        {
            // Enable the reception
            fs_vEnableReception(pMacIntf);
        }

        bStartOK = true;
    }

    return bStartOK;
}

bool MAC_bStop(eMACInterface_t fp_eInterface)
{
    bool bDeinitOk = false;

    sMACInterfaceState_t *pMacIntf = NULL;

    if(fp_eInterface >= eMAC_Interface_Count)
    {
        EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_InvalidParameter);
    }
    else
    {
        pMacIntf = MacCfg_sGetMacInterfaceById(fp_eInterface);

        assert(pMacIntf != NULL);

        fs_vDeinitInterface(pMacIntf, fp_eInterface);

        bDeinitOk = true;
    }

    return bDeinitOk;
}

bool MAC_bProtocolProcessMessage(eMACInterface_t fp_eMACId, ESSATMAC_Message * fp_psMsg)
{
    ESSATMAC_Context MACContext;

    bool res = false;

    if((fp_eMACId < eMAC_Interface_Count) && (fp_psMsg != (ESSATMAC_Message *) NULL))
    {
        (void)memset((void *)&MACContext, (uint8_t) 0, sizeof(ESSATMAC_Context));

        // This is to be defined by the user in the configuration
        MacCfg_vHandleFrameNotifications(fp_eMACId, fp_psMsg);

        MACContext.nInterfaceNumber = MacCfg_u8GetStackIfId(fp_eMACId);
        MACContext.nPayloadProtocol = fp_psMsg->u8Protocol;
        MACContext.nSourceAddr = fp_psMsg->u8SourceAddr;
        MACContext.nTargetAddr = fp_psMsg->u8TargetAddr;
        MACContext.netType = ESSASNETT_INTERNAL;

#if defined(USE_CUSTOM_ESPS_MSG_DISPATCH_HANDLER)
        custom_esps_data_dispatch(&MACContext, fp_psMsg->au8Data, fp_psMsg->u8DataSize);
#else
        // This must be defined in the application. See ESSA_Stack.h
        ESSA_Stack_DataDispatch(&MACContext, fp_psMsg->au8Data, fp_psMsg->u8DataSize);
#endif

        res = true;
    }

    return res;
}

ESSATMAC_ErrCodes MAC_DrvEnqMessage(ESSATMAC_Context * fp_pMACContext, uint8_t * fp_pMsgData, uint8_t fp_nMsgDataSize)
{
    sMACInterfaceState_t *pMacIntf = NULL;

    sMACTXPoolEntry_t *psEntry;

    bool txQueueAddResult;

    ESSATMAC_ErrCodes result = ESSATMAC_EC_ERROR;

    eMACInterface_t drvIf;

    if((fp_pMACContext != NULL) && (fp_pMsgData != NULL) && (fp_nMsgDataSize > 0))
    {
        drvIf = MacCfg_eGetMacDrvIf(fp_pMACContext->nInterfaceNumber);

        if(drvIf >= eMAC_Interface_Count)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_InvalidParameter);
        }
        else
        {
            // Get the interface (which RS485 connection)
            pMacIntf = MacCfg_sGetMacInterfaceById(drvIf);
            assert(pMacIntf != NULL);

            psEntry = MAC_POOL_psPoolTXNew(pMacIntf);

            if(psEntry != NULL)
            {
                psEntry->nMsgID = fp_pMACContext->nMsgID;

                // prepare message header
                psEntry->sMessage.u8TargetAddr = fp_pMACContext->nTargetAddr;
                psEntry->sMessage.u8SourceAddr = (fp_pMACContext->netType != ESSASNETT_UART_BRIDGE) ?
                                                 ((uint8_t) pMacIntf->u16Address) :
                                                 ((uint8_t) fp_pMACContext->nSourceAddr);
                psEntry->sMessage.u8Protocol = fp_pMACContext->nPayloadProtocol;
                psEntry->sMessage.u8DataSize = fp_nMsgDataSize;
                psEntry->sMessage.uHdrCRC16 = crc16_ccitt_table((const uint8_t *)&psEntry->sMessage,
                                                                ESSATMAC_HEADER_SIZE -
                                                                sizeof(psEntry->sMessage.uHdrCRC16));

                (void)memcpy(psEntry->sMessage.au8Data, fp_pMsgData, fp_nMsgDataSize);

                psEntry->sPrio.u8BasePriority = pMacIntf->u8BasePrio;
                psEntry->sPrio.u8Priority = fp_pMACContext->nSendBasePriority;
                psEntry->pSendCallback = fp_pMACContext->pSendCallback;

                // Calculate the CRC prior to attempting to send.
                fs_vUpdateCRC(psEntry);

                // Queue the message for sending.
                txQueueAddResult = MAC_QUEUE_vTXQueueAdd(pMacIntf, psEntry);

                if(txQueueAddResult)
                {
                    // Indicate that a new message has been added to the queue
                    MAC_IRQ_vTXRequestIndication(pMacIntf);

                    result = ESSATMAC_EC_OK;
                }
                else
                    result = ESSATMAC_EC_Q_FULL;
            }
            else
            {
                MAC_Stats_triggerEvent(pMacIntf->macStats, eMACStatId_TxMsgBufUnavailCntr);
                result = ESSATMAC_EC_NO_MEM;
            }
        }
    }
    else
        result = ESSATMAC_EC_NULL;

    return result;
}

bool MAC_bMessageInQueue(const eMACInterface_t fp_eMacInterfaceId)
{

    sMACInterfaceState_t *psInterfaceState;

    bool bIsPoolEmpty = true;

    // Get the RX pool
    psInterfaceState = MacCfg_sGetMacInterfaceById(fp_eMacInterfaceId);

    // Invalid Interface State
    if(psInterfaceState == NULL)
    {
        EXEH_HANDLE(eEXEHSeverity_Fatal, (int32_t) eMACException_InvalidState);
    }
    else
    {
        // Verify that there are messages in the dispatch queue
        if(psInterfaceState->sDisp.u32RxMsgCount == 0)
            bIsPoolEmpty = true;
        else
            bIsPoolEmpty = false;
    }
    return bIsPoolEmpty;
}

void MAC_vDispatchUARTEvent(sMACInterfaceState_t * fp_psState)
{
    if(LL_USART_IsEnabledIT_RXNE(fp_psState->psCfg->sHwConfig.psUART) &&
       LL_USART_IsActiveFlag_RXNE(fp_psState->psCfg->sHwConfig.psUART))
    {
        MAC_IRQ_vRXIndication(fp_psState);

        LL_USART_RequestRxDataFlush(fp_psState->psCfg->sHwConfig.psUART);
    }

    if(LL_USART_IsEnabledIT_TXE(fp_psState->psCfg->sHwConfig.psUART) &&
       LL_USART_IsActiveFlag_TXE(fp_psState->psCfg->sHwConfig.psUART))
    {
        MAC_IRQ_vTXIndication(fp_psState);
    }

    if(LL_USART_IsEnabledIT_TC(fp_psState->psCfg->sHwConfig.psUART) &&
       LL_USART_IsActiveFlag_TC(fp_psState->psCfg->sHwConfig.psUART))
    {
        LL_USART_ClearFlag_TC(fp_psState->psCfg->sHwConfig.psUART);
        MAC_IRQ_vTXFinishedIndication(fp_psState);
    }

    if(LL_USART_IsEnabledIT_PE(fp_psState->psCfg->sHwConfig.psUART) &&
       LL_USART_IsActiveFlag_PE(fp_psState->psCfg->sHwConfig.psUART))
    {
        LL_USART_ClearFlag_PE(fp_psState->psCfg->sHwConfig.psUART);
        MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_RxError);
    }

    if(LL_USART_IsEnabledIT_ERROR(fp_psState->psCfg->sHwConfig.psUART))
    {
        if(LL_USART_IsActiveFlag_NE(fp_psState->psCfg->sHwConfig.psUART))
        {
            LL_USART_ClearFlag_NE(fp_psState->psCfg->sHwConfig.psUART);
            MAC_IRQ_vTXProcessEvent(fp_psState, eTXEvent_CollisionDetected);
            MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_RxError);
        }

        if(LL_USART_IsActiveFlag_FE(fp_psState->psCfg->sHwConfig.psUART))
        {
            LL_USART_ClearFlag_FE(fp_psState->psCfg->sHwConfig.psUART);
            MAC_IRQ_vTXProcessEvent(fp_psState, eTXEvent_CollisionDetected);
            MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_RxError);
        }

        if(LL_USART_IsActiveFlag_ORE(fp_psState->psCfg->sHwConfig.psUART))
        {
            LL_USART_ClearFlag_ORE(fp_psState->psCfg->sHwConfig.psUART);
            MAC_IRQ_vTXProcessEvent(fp_psState, eTXEvent_CollisionDetected);
            MAC_IRQ_vRXProcessEvent(fp_psState, eRXEvent_RxError);
        }
    }

    if(LL_USART_IsActiveFlag_IDLE(fp_psState->psCfg->sHwConfig.psUART))
        LL_USART_ClearFlag_IDLE(fp_psState->psCfg->sHwConfig.psUART);
}

void MAC_vEnterCriticalSection(sMACInterfaceState_t * const fp_psIntf)
{
    if(fp_psIntf != NULL)
    {
        if(fp_psIntf->criticalSectionNestLevel == 0U)
        {
            // This must be compatible with the hardware configuration of the MAC driver
            NVIC_DisableIRQ(fp_psIntf->psCfg->sHwConfig.u32NVICMask);
            MAC_TIM_vSetTimerIsrStateById(fp_psIntf->psCfg->sHwConfig.eTXTIMID, false);
            MAC_TIM_vSetTimerIsrStateById(fp_psIntf->psCfg->sHwConfig.eRXTIMID, false);
        }

        if(fp_psIntf->criticalSectionNestLevel < 255)
            fp_psIntf->criticalSectionNestLevel++;
    }
}

void MAC_vLeaveCriticalSection(sMACInterfaceState_t * const fp_psIntf)
{
    if(fp_psIntf != NULL)
    {
        if(fp_psIntf->criticalSectionNestLevel > 0U)
            fp_psIntf->criticalSectionNestLevel--;

        if(fp_psIntf->criticalSectionNestLevel == 0U)
        {
            // This must be compatible with the hardware configuration of the MAC driver
            NVIC_EnableIRQ(fp_psIntf->psCfg->sHwConfig.u32NVICMask);
            MAC_TIM_vSetTimerIsrStateById(fp_psIntf->psCfg->sHwConfig.eTXTIMID, true);
            MAC_TIM_vSetTimerIsrStateById(fp_psIntf->psCfg->sHwConfig.eRXTIMID, true);
        }
    }
}

/******************************************************************************
 * File Local Function Definitions
 *****************************************************************************/
STATIC void fs_vInitInterface(sMACInterfaceState_t * fp_psState,
                              eMACInterface_t fp_eInterface, const eMAC_Interface_InitType_t fp_eInitType)
{
    if((!fp_psState->bInitDone) || (fp_eInitType == MACIF_INITTYPE_FULL))
    {
        // Set the queue head
        fp_psState->sTXCtx.psQueue = NULL;
        fp_psState->sTXCtx.u32QueueElementsCount = 0U;

        // Initialize the uart. This calls fs_Uart1Init, previously set in esps_drv_config.c
        if(fp_psState->psCfg->pfUartInit != NULL)
            (*fp_psState->psCfg->pfUartInit) ((struct sMACConfig_t *)(&fp_psState->psCfg->sHwConfig));

        // Enable the clock to the peripheral.
        MAC_RCC_vPeripheralClockEnable(fp_psState->psCfg->sHwConfig.eClockSource,
                                       fp_psState->psCfg->sHwConfig.u32RCCMask);

        // initialize the memory pool
        fp_psState->bInitDone = MAC_POOL_bPoolInit(fp_psState);

        if((fp_psState->psCfg->sHwConfig.u32Baudrate != 0) && (fp_psState->bInitDone))
        {
            // Set the initial state of the MAC interface
            fp_psState->sTXCtx.eState = eMACTransmit_Idle;
            fp_psState->sTXCtx.ePrevState = eMACTransmit_Off;
            fp_psState->sTXCtx.u8NestLevel = 0U;
            fp_psState->sRXCtx.eState = eMACReceive_Idle;
            fp_psState->sRXCtx.ePrevState = eMACReceive_Off;
            fp_psState->sRXCtx.u8NestLevel = 0U;

            // Reset to 0 the values of the TX/RX stats
            MAC_Stats_resetEventCounters(fp_psState->macStats);

            // initialize the dispatcher pool to 0
            MAC_DISP_vDispatcherInit(fp_psState, fp_eInterface);

            fp_psState->criticalSectionNestLevel = 0U;

            // Enable UART global interrupt
            NVIC_EnableIRQ(fp_psState->psCfg->sHwConfig.u32NVICMask);

            // Enable the UART
            LL_USART_Enable(fp_psState->psCfg->sHwConfig.psUART);
        }
    }
    else
    {
        // This branch gets executed upon re-initialization after sleep
        if(fp_psState->psCfg->pfUartInit != NULL)
            (*fp_psState->psCfg->pfUartInit) ((struct sMACConfig_t *)(&fp_psState->psCfg->sHwConfig));

        // Enable the clock to the peripheral.
        MAC_RCC_vPeripheralClockEnable(fp_psState->psCfg->sHwConfig.eClockSource,
                                       fp_psState->psCfg->sHwConfig.u32RCCMask);

        // Set the initial state of the MAC interface
        fp_psState->sTXCtx.eState = eMACTransmit_Idle;
        fp_psState->sTXCtx.ePrevState = eMACTransmit_Off;
        fp_psState->sTXCtx.u8NestLevel = 0U;
        fp_psState->sRXCtx.eState = eMACReceive_Idle;
        fp_psState->sRXCtx.ePrevState = eMACReceive_Off;
        fp_psState->sRXCtx.u8NestLevel = 0U;

        fp_psState->criticalSectionNestLevel = 0U;
        // Enable UART global interrupt.
        NVIC_EnableIRQ(fp_psState->psCfg->sHwConfig.u32NVICMask);

        // Enable the UART
        LL_USART_Enable(fp_psState->psCfg->sHwConfig.psUART);
    }
}

STATIC void fs_vDeinitInterface(sMACInterfaceState_t * fp_psState, eMACInterface_t fp_eInterface)
{
    if(fp_psState->psCfg->pfUartDeinit != NULL)
        (*fp_psState->psCfg->pfUartDeinit) ((struct sMACConfig_t *)(&fp_psState->psCfg->sHwConfig));

    MAC_RCC_vPeripheralClockDisable(fp_psState->psCfg->sHwConfig.eClockSource, fp_psState->psCfg->sHwConfig.u32RCCMask);

    MAC_DISP_vDispatcherInit(fp_psState, fp_eInterface);
    NVIC_DisableIRQ(fp_psState->psCfg->sHwConfig.u32NVICMask);
    LL_USART_Disable(fp_psState->psCfg->sHwConfig.psUART);
}

STATIC void fs_vTIMCallback(eTIMTimerStatus_t fp_eStatus, void *fp_pvData)
{
    if(fp_pvData != NULL)
    {
        // Enable reception and the Received Data Ready interrupt
        MAC_IRQ_vRXStartIndication((sMACInterfaceState_t *) fp_pvData);
    }
}

STATIC void fs_vEnableReception(sMACInterfaceState_t * fp_psState)
{
    if(!fp_psState->bInitDone)
    {
        EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eMACException_InvalidState);
    }
    else
    {
        // ipetrov: Currently, for some unknown reason, Tx and Rx timers
        // require one single run before they start
        // to elapse correctly. Otherwise, first timer shot elapses
        // prematurely and this could lead to first
        // RX message discarded and first Tx message sent with an
        // incorrect priority wait time.
        MAC_TIM_vMicroTimerStart(fp_psState->psCfg->sHwConfig.eRXTIMID, (uint32_t) 5, fs_vTIMCallback, fp_psState);
        MAC_TIM_vMicroTimerStart(fp_psState->psCfg->sHwConfig.eTXTIMID, (uint32_t) 5, fs_vTIMCallback, NULL);
    }
}

STATIC void fs_vUpdateCRC(sMACTXPoolEntry_t * fp_psEntry)
{
    uint32_t u32CRC =
        MACCRC32_Calc32((const uint8_t *)&fp_psEntry->sMessage, ESSATMAC_HEADER_SIZE + fp_psEntry->sMessage.u8DataSize,
                        CRC32_INIT_VALUE);

    fp_psEntry->sMessage.u32CRC = u32CRC;
}
