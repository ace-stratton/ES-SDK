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
 * @file     esps_drv_tim_config.c
 * @brief    Timer peripheral configuration for ESPS I MAC Driver
 *
 * @}
 */

#include <assert.h>

#include "esps_drv_tim_config.h"

sTIMTimerEntry_t TIM_CFG_asTimerEntries[] =
{
    // reserved for MAC UART1 (SYS1 RS485) Tx timing
    {
        .psTIM            = TIM16,
        .eClockSrc        = eRCCPeripheralClock_APB2,
        .u32ClockMask     = RCC_APB2ENR_TIM16EN,
        .u32NVICInterrupt = TIM16_IRQn,
        .bRunning         = false,
        .pfCallback       = NULL,
        .pvData           = NULL,
    },
    // reserved for MAC UART1 (SYS1 RS485) Rx timing
    {
        .psTIM            = TIM17,
        .eClockSrc        = eRCCPeripheralClock_APB2,
        .u32ClockMask     = RCC_APB2ENR_TIM17EN,
        .u32NVICInterrupt = TIM17_IRQn,
        .bRunning         = false,
        .pfCallback       = NULL,
        .pvData           = NULL,
    },
};

// Calculate the prescaler for a given timer to set it as 1ms per tick (1MHz)
uint16_t MacCfg_TIM_u16CalculatePrescaler(sTIMTimerEntry_t *fp_psTIM)
{
    uint16_t prescaler = 0U;
    uint32_t clkFreqHz = 0U;

    assert(fp_psTIM != NULL);

    switch (fp_psTIM->eClockSrc)
    {
        case eRCCPeripheralClock_APB1:
            // timer clocks are using 2x the frequency of APB1 domain
            clkFreqHz = HAL_RCC_GetPCLK1Freq() * 2;
        break;

        case eRCCPeripheralClock_APB2:
            // timer clocks are using 2x the frequency of APB2 domain
            clkFreqHz = HAL_RCC_GetPCLK2Freq() * 2;
        break;

        default:
        break;
    }

    prescaler = (uint16_t) ((uint32_t) (PRESCALER_CFG_VALUE_US * (clkFreqHz / 1000000U) - 1));

    return prescaler;
}
