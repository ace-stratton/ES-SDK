/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_TIM_H
#define ESPS_DRV_TIM_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_tim.h
 * @brief    Timer helper interface for MAC layer
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

// External imports
#include "esps_drv_tim_config.h"
#include "esps_drv_tim_ct.h"

#include "esps_drv_cdef.h"

#define SUPPRESS_TIMER_CANCEL_CBK   ((bool) true)
#define CALL_TIMER_CANCEL_CBK       ((bool) false)

/** Handle type for timer in order to operate with the timer */
struct sTIMTimerEntry_t;

/**
 * Initialize the TIM module.
 *
 * @return only if initialization passes it resets the OBC otherwise
 */
bool MAC_TIM_bInit(void);

/**
 * Deinitialize the TIM module.
 *
 * @return only if initialization passes it resets the OBC otherwise
 */
bool MAC_TIM_bDeinit(void);

/**
 * Schedule a callback to be called after microseconds ammount of time.
 *
 * @param fp_eTIM: timer to be used
 * @param fp_u32Timeout: timeout in microseconds.
 * @param fp_pfCallback: callback to call upon timeout or cancelation of the timer
 * @param fp_pvData: data to deliver to the timer uppon expiration or cancelation
 */
void MAC_TIM_vMicroTimerStart(eTIMTimerID_t fp_eTIM,
                              uint32_t fp_u32Timeout, pfTIMCallback_t fp_pfCallback, void *fp_pvData);

/**
 * Cancel a running timer.
 *
 * @param fp_eTIM: timer handle to cancel.
 * @param fp_bSuppressCancelCbk: if true, the cancel callback is not invoked after timer cancellation
 */
void MAC_TIM_vMicroTimerCancel(eTIMTimerID_t fp_eTIM, bool fp_bSuppressCancelCbk);

/**
 * IRQ handler to be called by in the compiler interrupt routine implemented
 * in the client module
 *
 * @param fp_psTimBase: pointer to Timer base register as defined in HAL LL headers
 * @param fp_eTimId: timer identifier used to access the timer configuration in the driver
*/
void MAC_TIM_IRQ_Handler_Generic(TIM_TypeDef * fp_psTimBase, eTIMTimerID_t fp_eTimId);

/**
 * Returns the last elapsed timer counter value in microseconds
 *
 * @param fp_eTIM: pointer to Timer base register as defined in HAL LL headers
 * @return last elapsed counter value in microseconds
*/
uint32_t MAC_TIM_vMicroTimerGetElapsed(eTIMTimerID_t fp_eTIM);

/**
 * Enables or disables the Timer ISR for a given timer ID
 *
 * @param fp_eTIM: pointer to Timer base register as defined in HAL LL headers
 * @param fp_bEnabled: if true, the respective timer ISR is enabled
*/
void MAC_TIM_vSetTimerIsrStateById(eTIMTimerID_t fp_eTIM, bool fp_bEnabled);

/**
 * Retrieves the Timer ISR state for a given timer ID
 *
 * @param fp_eTIM: pointer to Timer base register as defined in HAL LL headers
 * @return bool: true - ISR enabled / false - otherwise
*/
bool MAC_TIM_vGetTimerIsrStateById(eTIMTimerID_t fp_eTIM);

#ifdef __cplusplus
}
#endif

#endif //ESPS_DRV_TIM_H
