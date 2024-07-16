/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_TIM_CT_H
#define ESPS_DRV_TIM_CT_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_tim_ct.h
 * @brief    Timer helper interface for MAC layer MAC Timers context types
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "esps_drv_cdef.h"

#include "esps_drv_rcc.h"

/** Type for timer status */
typedef enum {
    eTIMTimer_Expired,
    eTIMTimer_Canceled,
} eTIMTimerStatus_t;

/** Type for the Timer callback */
typedef void (*pfTIMCallback_t) (eTIMTimerStatus_t fp_eStatus, void *fp_pvData);

/** TIM pool entry. */
typedef struct sTIMTimerEntry_t {
    TIM_TypeDef *psTIM;                 /**< Pointer to the TIM register base */
    eRCCPeripheralClock_t eClockSrc;    /**< The clock source for the TIM instance. */
    uint32_t u32ClockMask;              /**< APB(1/2) clock enable/disable mask. */
    uint32_t u16Prescaler;              /**< Prescaler value for the Timer. */
    uint32_t u32NVICInterrupt;          /**< NVIC Interrupt */
    pfTIMCallback_t pfCallback;         /**< Event flags to set on expiration. */
    void *pvData;                       /**< Data to deliver to the callback upon expiration or timeout */
    bool bRunning;                      /**< Running or not flag */
    bool bUsed;                         /**< Used or not flag */
} sTIMTimerEntry_t;

#ifdef __cplusplus
}
#endif

#endif //ESPS_DRV_TIM_CT_H
