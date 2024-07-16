/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_TIM_CONFIG_H
#define ESPS_DRV_TIM_CONFIG_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_tim_config.h
 * @brief    Timer peripheral function declarations for the ESPS I MAC Driver
 *
 * @}
 */

#include "esps_drv_stm32.h"
#include "esps_drv_def.h"

#include "esps_drv_tim_ct.h"

#define TIMER_ISR_PRIO  MAC_UART_ISR_PRIO

// requested value in microseconds to use for the timer-counter prescaler calculation for MAC driver usage
#define PRESCALER_CFG_VALUE_US  (1U)

// Timers used are 16-bit, hence max range is ~65 ms @ 1us/tick
#define MAX_TIMER_RANGE_US      ((uint32_t) 65535)

// Enumeration with all available TIMs
typedef enum
{
    eTIM_TIM16_ID,
    eTIM_TIM17_ID,
    eTIM_TIM_ID_Count
} eTIMTimerID_t;

extern struct sTIMTimerEntry_t TIM_CFG_asTimerEntries[eTIM_TIM_ID_Count];

/**
 * @brief Calculate the prescaler for a given timer to set it as 1ms per tick (1MHz)
 */
uint16_t MacCfg_TIM_u16CalculatePrescaler(sTIMTimerEntry_t *fp_psTIM);

#endif /* ESPS_DRV_TIM_CONFIG_H */
