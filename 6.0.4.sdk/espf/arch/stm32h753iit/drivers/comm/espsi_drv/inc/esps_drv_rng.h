/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_RNG_H
#define ESPS_DRV_RNG_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_rng.h
 * @brief    Random Number Generator interface
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

    // External imports
#include "esps_drv_config.h"
#include "esps_drv_rng_config.h"

extern RNG_HandleTypeDef hrng;

/**
 * @brief Enable the RNG peripheral
 */
void MAC_RNG_Init(void);

/**
 * @brief Deinit the RNG peripheral
 */
void MAC_RNG_DeInit(void);

/**
 * @brief Get a random number between 0 and a given range
 * @param fp_u32Range max value
 */
uint32_t MAC_RNG_GetRandomNumberInRange(uint32_t fp_u32Range);

#ifdef __cplusplus
}
#endif
#endif                          //ESPS_DRV_RNG_H
