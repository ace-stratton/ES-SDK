/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_RNG_CONFIG_H
#define ESPS_DRV_RNG_CONFIG_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_rng_config.h
 * @brief    RNG peripheral initialization declarations
 *
 * @}
 */

#include "esps_drv_stm32.h"

/**
 * @brief Initializer for the RNG Hardware peripheral
 */
void MacCfg_RNG_Init(RNG_HandleTypeDef* fp_pHrng);

/*
 * @brief Deinitializer for the RNG Hardware peripheral
 */
void MacCfg_RNG_DeInit(RNG_HandleTypeDef* fp_pHrng);

#endif /* ESPS_DRV_RNG_CONFIG_H */
