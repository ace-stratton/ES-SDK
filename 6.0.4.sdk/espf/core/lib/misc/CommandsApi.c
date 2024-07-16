/*
* Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
*
* Contents and presentations are protected world-wide.
* Any kind of using, copying etc. is prohibited without prior permission.
*/
/**
 * @addtogroup misc
 * @{
 *
 * @file CommandsApi.c
 * @brief Implementation of the Commands API
 *
 * @}
 */

#include "es_cdef.h"
#include <CommandsApi.h>
#include "DAT_Inputs.h"
#include "main.h"
#include "TaskMonitor.h"
#include "nvm_resetcounters.h"
#include "nvm/inc/nvm.h"


//
//  Start of PC104 GPIO pin definitions
//
#define OBC_OUT1_Pin GPIO_PIN_15
#define OBC_OUT1_GPIO_Port GPIOB
#define OBC_OUT2_Pin GPIO_PIN_5
#define OBC_OUT2_GPIO_Port GPIOD
#define OBC_OUT3_Pin GPIO_PIN_4
#define OBC_OUT3_GPIO_Port GPIOD
#define OBC_OUT5_Pin GPIO_PIN_6
#define OBC_OUT5_GPIO_Port GPIOG
#define OBC_OUT4_6_Pin GPIO_PIN_0
#define OBC_OUT4_6_GPIO_Port GPIOD
#define OBC_OUT7_Pin GPIO_PIN_5
#define OBC_OUT7_GPIO_Port GPIOH
#define OBC_OUT8_Pin GPIO_PIN_15
#define OBC_OUT8_GPIO_Port GPIOH

// Note: Please update this function in case any of the above ports changes !!!
static void enable_gpio_port_clocks(void){
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
}

//
//	End of PC104 GPIO pin definitions
//

typedef struct
{
    GPIO_TypeDef *outPortAddr;
    uint16_t pinMask;
    MCU_Init_OutputsOrder_enum bitPos;	// bit position in the returned bit-field
} writeHandlerGpioConfig_t;

static const writeHandlerGpioConfig_t pinCfg[] =
{
    { .outPortAddr = OBC_OUT1_GPIO_Port,    .pinMask = OBC_OUT1_Pin,    .bitPos = MCU_INIT_OUT1   },
    { .outPortAddr = OBC_OUT2_GPIO_Port,    .pinMask = OBC_OUT2_Pin,    .bitPos = MCU_INIT_OUT2   },
    { .outPortAddr = OBC_OUT3_GPIO_Port,    .pinMask = OBC_OUT3_Pin,    .bitPos = MCU_INIT_OUT3   },
    { .outPortAddr = OBC_OUT5_GPIO_Port,    .pinMask = OBC_OUT5_Pin,    .bitPos = MCU_INIT_OUT5   },
    { .outPortAddr = OBC_OUT4_6_GPIO_Port,  .pinMask = OBC_OUT4_6_Pin,  .bitPos = MCU_INIT_OUT4_6 },
    { .outPortAddr = OBC_OUT7_GPIO_Port,    .pinMask = OBC_OUT7_Pin,    .bitPos = MCU_INIT_OUT7   },
    { .outPortAddr = OBC_OUT8_GPIO_Port,    .pinMask = OBC_OUT8_Pin,    .bitPos = MCU_INIT_OUT8   },
};


void CommandsApi_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    enable_gpio_port_clocks();

    // prepare common configuration for all ports
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    for (uint8_t idx = 0; idx < CDEF_ELEMENT_COUNT(pinCfg); idx++)
    {
        GPIO_InitStruct.Pin = pinCfg[idx].pinMask;
        HAL_GPIO_Init(pinCfg[idx].outPortAddr, &GPIO_InitStruct);
    }
}

GpioStat_t ReadHandler_GpOutputState(void)
{
    GpioStat_t retValue = { .gpioStatusBitField = 0x00 };

    retValue.gpioStatusBitField = 0U;

    for (uint8_t idx = 0; idx < CDEF_ELEMENT_COUNT(pinCfg); idx++)
    {
        retValue.gpioStatusBitField |=
                HAL_GPIO_ReadPin(pinCfg[idx].outPortAddr, pinCfg[idx].pinMask) << pinCfg[idx].bitPos;
    }

    return retValue;
}

HwRes_t WriteHandler_GpOutputState(uint8_t pin, uint8_t value)
{
    HwRes_t status = HWRES_ERROR;

    if (pin < CDEF_ELEMENT_COUNT(pinCfg))
    {
        if  ((GPIO_TypeDef *) NULL != pinCfg[pin].outPortAddr)
        {
            HAL_GPIO_WritePin(pinCfg[pin].outPortAddr, pinCfg[pin].pinMask, value);
            status = HWRES_SUCCESS;
        }
    }

    return status;
}

// This function should be deprecated but is still here until UHF Antenna management in OBC needs it!
void CommandsApi_Gpo_Set(const MCU_Init_OutStates_struct * const states)
{
    CommandsApi_GPIO_Init();

    for (uint8_t idx = 0; idx < CDEF_ELEMENT_COUNT(pinCfg); idx++)
    {
        if((states->OutToChange >> pinCfg[idx].bitPos) & 0x01)
        {
            HAL_GPIO_WritePin(pinCfg[idx].outPortAddr, pinCfg[idx].pinMask, (states->OutState >> pinCfg[idx].bitPos) & 0x01);
        }
    }
}

StdResult_t WriteHandler_ResetInBootOrAppMode(const AppMode_t appMode)
{
    StdResult_t res = STDRESULT_SUCCESS;
    boot_struct BootData;

    Nvm_GetBlockById(NVM_BLOCK_BOOTDATA, &BootData);
    switch (appMode)
    {
        case APPMODE_APPLICATION:
            BootData.Mailbox = MAILBOX_VAL_APPL;
        break;

        case APPMODE_BOOTLOADER:
            BootData.Mailbox = MAILBOX_VAL_BOOT;
        break;

        case APPMODE_AUTO_FW_UPDATE:
            BootData.Mailbox = MAILBOX_VAL_AUTO_FLASH;
        break;
        default:
            res = STDRESULT_INVALID_ARGS;
        break;
    }

    if(res == STDRESULT_SUCCESS)
    {
        NvmResetCounters_ClearCounter(RSTCOUNTERID_ALL);
        BootData.RebootRequest = pdTRUE;
        // set valid checksum for the RTC backup registers after changing the mailbox
        Nvm_SetBlockById(NVM_BLOCK_BOOTDATA, &BootData, NVMSETBLOCK_STORE_IMMEDIATELY);

        // Reset the OBC
        TaskMonitor_TriggerDelayedReset(1000U);
    }

    return res;
}
