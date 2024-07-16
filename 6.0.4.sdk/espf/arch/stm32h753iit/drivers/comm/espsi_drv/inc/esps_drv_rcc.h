/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_RCC_H
#define ESPS_DRV_RCC_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_rcc.h
 * @brief    Reset and Clock Controller definitions
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "esps_drv_cdef.h"

/** Enumeration with possible peripheral clock sources */
typedef enum {
    eRCCPeripheralClock_APB1,
    eRCCPeripheralClock_APB2
} eRCCPeripheralClock_t;

/**
 * @brief Enable the RCC peripheral
 * @param fp_eClock
 * @param fp_u32EnableMask
 */
void MAC_RCC_vPeripheralClockEnable(eRCCPeripheralClock_t fp_eClock, uint32_t fp_u32EnableMask);

/**
 * @brief Disable the RCC peripheral
 * @param fp_eClock
 * @param fp_u32DisableMask
 */
void MAC_RCC_vPeripheralClockDisable(eRCCPeripheralClock_t fp_eClock, uint32_t fp_u32DisableMask);

#ifdef __cplusplus
}
#endif

#endif /* ESPS_DRV_RCC_H */
