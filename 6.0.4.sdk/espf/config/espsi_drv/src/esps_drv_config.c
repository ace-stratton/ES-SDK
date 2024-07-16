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
 * @file     esps_drv_config.c
 * @brief    Configuration for the ESPS I MAC Driver
 *
 * @}
 */

#include <string.h>
#include <assert.h>

#include "esps_drv_config.h"
#include "esps_drv_dispatcher_thread.h"
#include "es_mac_notif.h"
#include "nvm/inc/nvm.h"
#include "FP_common/FP_BaseProtocolTypes.h"
#include "TaskMonitor.h"

#include "esps_drv_debug.h"
#include "esps_drv.h"
#include "assertions.h"

#define RS485_TX_Pin        GPIO_PIN_9
#define RS485_TX_GPIO_Port  GPIOA
#define RS485_RX_Pin        GPIO_PIN_10
#define RS485_RX_GPIO_Port  GPIOA
#define RS485_nRE_Pin       GPIO_PIN_11
#define RS485_nRE_GPIO_Port GPIOA
#define RS485_DE_Pin        GPIO_PIN_12
#define RS485_DE_GPIO_Port  GPIOA
#define RS485_TE_Pin        GPIO_PIN_12
#define RS485_TE_GPIO_Port  GPIOD

// Interrupt to MAC device mapping configuration
#define MAC_USART1_DEVICE            (eMAC_Interface_Primary)

static void fs_Uart1Init (struct sMACConfig_t *cfg);
static void fs_Uart1Deinit (struct sMACConfig_t *cfg);
static void fs_vRS485DriverEnable (void);
static void fs_vRS485DriverDisable (void);
static void fs_vRS485ReceptionEnable (void);
static void fs_vRS485ReceptionDisable (void);

static UART_HandleTypeDef huart1;

static const sMACInterfaceImmutableConfig_t fs_MacConfig[eMAC_Interface_Count]= {
    {
         .pfEnableTX = fs_vRS485DriverEnable,
         .pfDisableTX = fs_vRS485DriverDisable,
         .pfEnableRX = fs_vRS485ReceptionEnable,
         .pfDisableRX = fs_vRS485ReceptionDisable,
         .pfUartInit = fs_Uart1Init,
         .pfUartDeinit = fs_Uart1Deinit,
         .sHwConfig = {
             .psUART = USART1,
             .u32Baudrate = MAC_DEFAULT_BAUDRATE,
             .u16TQVal = MAC_DEFAULT_TQ,
             .u32NVICMask = USART1_IRQn,
             .u32RCCMask = RCC_APB2ENR_USART1EN,
             .eClockSource = eRCCPeripheralClock_APB2,
             .eTXTIMID = eTIM_TIM16_ID,
             .eRXTIMID = eTIM_TIM17_ID,
         }
     },
};

static sMACInterfaceState_t fs_asMACStates[eMAC_Interface_Count] = {
		{
				.macIfId = eMAC_Interface_Primary,
				.u16Address = MAC_DEFAULT_ADDRESS_PRI,
				.psCfg = &fs_MacConfig[eMAC_Interface_Primary],
				.bInitDone = false,
				.u8BasePrio = MAC_DEFAULT_BASEPRIO,
				.criticalSectionNestLevel = 0U
		},
};

// Return the MAC Interface for a given ESSA Stack ID
eMACInterface_t MacCfg_eGetMacDrvIf (uint8_t netIfId)
{
	eMACInterface_t macDrvIf;

	switch (netIfId)
    {
        case ESSASNI_SYS_PRI:
            macDrvIf = eMAC_Interface_Primary;
        break;

        default:
            macDrvIf = eMAC_Interface_Count;
        break;
	}

	return macDrvIf;
}

// Returns the ESSA Stack ID of the interface for a given MAC Interface
uint8_t MacCfg_u8GetStackIfId (eMACInterface_t macIf)
{
	uint8_t stackIfId;

	switch (macIf)
	{
	case eMAC_Interface_Primary:
		stackIfId = ESSASNI_SYS_PRI;
		break;

	default:
		stackIfId = 0xFF;
		break;
	}

	return stackIfId;
}

sMACInterfaceState_t *MacCfg_sGetMacInterfaceById (const eMACInterface_t macId)
{
	if (macId < eMAC_Interface_Count)
		return &fs_asMACStates[macId];
	else
		return NULL;
}

static void fs_vRS485DriverEnable (void)
{
    // RTS ACTIVE (Driver Enable)
    HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_SET);
}

static void fs_vRS485DriverDisable (void)
{
    // RTS INACTIVE (Driver Disable)
    HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET);
}

static void fs_vRS485ReceptionEnable (void)
{
    // RE ACTIVE (Receive Enable)
    HAL_GPIO_WritePin (RS485_nRE_GPIO_Port, RS485_nRE_Pin, GPIO_PIN_RESET);
}

static void fs_vRS485ReceptionDisable (void)
{
    // RE INACTIVE (Receive Disable)
    HAL_GPIO_WritePin (RS485_nRE_GPIO_Port, RS485_nRE_Pin, GPIO_PIN_SET);
}

void MacCfg_vSetBusTerminationState(const eMACInterface_t eMacIf, const bool bNewState, const bool bPersistSetting)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    bool bSettingIsValid = true;

    switch (eMacIf)
    {
        case eMAC_Interface_Primary:
        {
            // - RS4xx_HS1_TE
            __HAL_RCC_GPIOD_CLK_ENABLE();

            /* Configure GPIO pin : RS485_TE_Pin */
            GPIO_InitStruct.Pin = RS485_TE_Pin;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
            HAL_GPIO_Init(RS485_TE_GPIO_Port, &GPIO_InitStruct);

            HAL_GPIO_WritePin(RS485_TE_GPIO_Port,
                              RS485_TE_Pin,
                              (bNewState) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));

            break;
        }
        default:
            bSettingIsValid = false;
            CRIT_ASSERT(false);
            break;
    }
#if defined(COMM_RS485_MAC_LAYER_ENABLED)
    if ((bSettingIsValid) && (bPersistSetting))
    {
        sMacConfig_t macNvmCfg;

        Nvm_GetBlockById(NVM_BLOCK_MACCONFIG, &macNvmCfg);

        if (bNewState)
            macNvmCfg.macDrvConfig.u8MacBusTerminationBitField |= (uint8_t) ((0x01U) << (uint8_t) eMacIf);
        else
            macNvmCfg.macDrvConfig.u8MacBusTerminationBitField &= (uint8_t) ~((0x01U) << (uint8_t) eMacIf);

        Nvm_SetBlockById(NVM_BLOCK_MACCONFIG, &macNvmCfg, NVMSETBLOCK_STORE_IMMEDIATELY);
    }
#endif
}

bool MacCfg_bGetBusTerminationState(const eMACInterface_t eMacIf, const bool bReadPersistentSetting)
{
    GPIO_PinState pinState;
    bool bBusTerminationState = false;

#if defined(COMM_RS485_MAC_LAYER_ENABLED)
    sMacConfig_t macNvmCfg;

    Nvm_GetBlockById(NVM_BLOCK_MACCONFIG, &macNvmCfg);

    switch (eMacIf)
    {
        case eMAC_Interface_Primary:
        {
            if (bReadPersistentSetting)
            {
                bBusTerminationState = (bool) \
                        (macNvmCfg.macDrvConfig.u8MacBusTerminationBitField >> ((uint8_t) eMAC_Interface_Primary)) & 0x01U;
            }
            else
            {
                pinState = HAL_GPIO_ReadPin(RS485_TE_GPIO_Port, RS485_TE_Pin);
                bBusTerminationState = (pinState == GPIO_PIN_SET) ? (true) : (false);
            }

            break;
        }
        default:
            CRIT_ASSERT(false);
            break;
    }
#endif

    return bBusTerminationState;
}

void MacCfg_vApplyMacAddrConfig (const eMACInterface_t eMacIf, const uint8_t u8MacAddr)
{
	(void) eMacIf;              // provision in case different addresses will be needed in the future
	// apply change to all MAC interfaces
	for (uint8_t u8MacIfId = 0U; u8MacIfId < eMAC_Interface_Count; u8MacIfId++)
		fs_asMACStates[u8MacIfId].u16Address = (uint16_t) u8MacAddr;
}

bool MacCfg_bSetMacAddress(const eMACInterface_t eMacIf, const uint8_t u8MacAddr)
{
    bool bResult = false;
#if defined(COMM_RS485_MAC_LAYER_ENABLED)
    if ((eMacIf < eMAC_Interface_Count) &&
        (u8MacAddr != 0x00U) &&
        (u8MacAddr != ESSATMAC_ADDR_GATEWAY_DEV) &&
        (u8MacAddr != ESSATMAC_ADDR_BROADCAST))
    {
        if (u8MacAddr != MacCfg_u8GetMacAddress(eMacIf))
        {
            sMacConfig_t macNvmCfg;

            Nvm_GetBlockById(NVM_BLOCK_MACCONFIG, &macNvmCfg);
            macNvmCfg.macDrvConfig.u8MacAddress = u8MacAddr;
            Nvm_SetBlockById(NVM_BLOCK_MACCONFIG, &macNvmCfg, NVMSETBLOCK_STORE_IMMEDIATELY);
        }

        // the new setting will be taken into account after OBC reset
        bResult = true;
    }
#endif
    return bResult;
}

uint8_t MacCfg_u8GetMacAddress(const eMACInterface_t eMacIf)
{
#if defined(COMM_RS485_MAC_LAYER_ENABLED)
    sMacConfig_t macNvmCfg;

    Nvm_GetBlockById(NVM_BLOCK_MACCONFIG, &macNvmCfg);

    // if for some reason, the persisted address is missing or set to one of the
    // broadcast groups, then use the default MAC SYS1 address
    if ((macNvmCfg.macDrvConfig.u8MacAddress == 0xFFU) ||
        (macNvmCfg.macDrvConfig.u8MacAddress == 0x00U) ||
        (macNvmCfg.macDrvConfig.u8MacAddress == ESSATMAC_ADDR_GATEWAY_DEV) ||
        (macNvmCfg.macDrvConfig.u8MacAddress == ESSATMAC_ADDR_BROADCAST))
       return MAC_SYS1_ADDRESS_PRI;
    else
       return macNvmCfg.macDrvConfig.u8MacAddress;
#endif
}

static void fs_Uart1Init (struct sMACConfig_t *cfg)
{
	assert(cfg != NULL);

	GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /**USART1 GPIO Configuration
    PA9    ------> USART1_TX
    PA10   ------> USART1_RX
    PA12   ------> USART1_DE (RTS)
    */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = ((sMACConfig_t *) cfg)->u32Baudrate;
    huart1.Init.WordLength = UART_WORDLENGTH_9B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if (HAL_UART_Init (&huart1) != HAL_OK)
    {
        Error_Handler ();
    }

    GPIO_InitStruct.Pin = RS485_TX_Pin | RS485_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RS485_TE_GPIO_Port, RS485_TE_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RS485_nRE_GPIO_Port, RS485_nRE_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = RS485_DE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (RS485_DE_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : RS485_TE_Pin */
    GPIO_InitStruct.Pin = RS485_TE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(RS485_TE_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : RS485_nRE_Pin */
    GPIO_InitStruct.Pin = RS485_nRE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(RS485_nRE_GPIO_Port, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, MAC_UART_ISR_PRIO, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    // Receive Enable ACTIVE
    fs_vRS485ReceptionEnable();

	// Termination Enable ACTIVE
	MacCfg_vSetBusTerminationState(eMAC_Interface_Primary, MacCfg_bGetBusTerminationState(eMAC_Interface_Primary, true), true);

	// Start with a disabled communication driver...
	fs_vRS485DriverDisable();
}

static void fs_Uart1Deinit (struct sMACConfig_t *cfg)
{
	(void) cfg;
	__HAL_RCC_USART1_CLK_DISABLE ();
	// RS485_TX_GPIO_Port and RS485_RX_GPIO_Port are the same, GPIOA
	HAL_GPIO_DeInit(GPIOA, RS485_TX_Pin|RS485_RX_Pin);
	HAL_NVIC_DisableIRQ(USART1_IRQn);
}

// Overriding STM32f startup Exception handler
void USART1_IRQHandler(void);
void USART1_IRQHandler (void)
{
	MAC_vDispatchUARTEvent (&fs_asMACStates[MAC_USART1_DEVICE]);
}

// Overriding STM32f startup Exception handler
void TIM16_IRQHandler (void)
{
	MAC_TIM_IRQ_Handler_Generic(TIM16, eTIM_TIM16_ID);
}

// Overriding STM32f startup Exception handler
void TIM17_IRQHandler (void)
{
	MAC_TIM_IRQ_Handler_Generic(TIM17, eTIM_TIM17_ID);
}


// Callback after a received frame ready to dispatch
void MacCfg_vDispatcherNotifCallback(eMACInterface_t fp_eMACId)
{
    // USER CODE
    DISP_vActivateDispatcherThread(fp_eMACId);

    // END OF USER CODE
    return;
}

//  Called from MAC_bProtocolProcessMessage to be notified on a received frame
void MacCfg_vHandleFrameNotifications (eMACInterface_t fp_eMACId, ESSATMAC_Message * fp_psMsg)
{
	// USER CODE
    switch (fp_psMsg->u8Protocol)
    {
        case ES_SAT_MAC_PROTOCOL_ID_FP_LAYER:
        {
#ifndef BIG_ENDIAN_PLATFORM
            ESSA_Stack_FP_MsgHdr_t *pFPHeader = (ESSA_Stack_FP_MsgHdr_t *) fp_psMsg->au8Data;
#else
#error Big-endian encoding of the header is not supported currently!
#endif

            // we are interested only in request FP frames
            if (pFPHeader != NULL)
                if (IS_REQUEST(*pFPHeader))
                    MAC__Notif_OnEvent_Cfg(fp_eMACId,
                                       EMACNOTIFICATION_ON_FP_REQ_RCVD,
                                       (eventData_t) fp_psMsg);
            break;
        }

        case ES_SAT_MAC_PROTOCOL_ID_TRANSPORT_LAYER:
        {
            MAC__Notif_OnEvent_Cfg(fp_eMACId,
                               EMACNOTIFICATION_ON_TL_FRAME_RCVD,
                               (eventData_t) fp_psMsg);
            break;
        }

        default:
            MAC__Notif_OnEvent_Cfg(fp_eMACId,
                               EMACNOTIFICATION_ON_GEN_FRAME_RCVD,
                               (eventData_t) fp_psMsg);
        break;
    }
	// END OF USER CODE
	return;
}

void MAC__Stats_getEventsBuffer(eMACInterface_t fp_eMACId,
                                uint8_t * const pu8UserBuf,
                                uint32_t u32UserBufSize,
                                uint32_t * const pu32ResponseSize,
                                uint32_t * const pu32EventsCount)
{
    if ((pu8UserBuf != NULL) &&
        (u32UserBufSize > 0U) &&
        (pu32EventsCount != NULL) &&
        (pu32ResponseSize != NULL) &&
        (fp_eMACId < eMAC_Interface_Count))
    {
        if (u32UserBufSize >= sizeof(macStats_t))
            u32UserBufSize = sizeof(macStats_t);

        *pu32EventsCount = eMACStatId_MAX;

        taskENTER_CRITICAL();

        (void) memcpy(pu8UserBuf, (const void *) fs_asMACStates[fp_eMACId].macStats, u32UserBufSize);

        taskEXIT_CRITICAL();

        // size contains also the event count which is part of the returned buffer
        *pu32ResponseSize = sizeof(uint32_t) + sizeof(fs_asMACStates[fp_eMACId].macStats);
    }
}
