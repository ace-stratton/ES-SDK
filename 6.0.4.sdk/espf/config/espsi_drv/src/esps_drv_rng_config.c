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
 * @file     esps_drv_rng_config.c
 * @brief    RNG peripheral initialization
 *
 * @}
 */

#include "esps_drv_rng_config.h"

#include "esps_drv_stm32.h"

extern void Error_Handler();

/* RNG init function */
void MacCfg_RNG_Init(RNG_HandleTypeDef *fp_pHrng)
{
    // Initialise the hardware peripherial RNG
    // Take in account that the driver will load the random vector and then deinitialize it.

    fp_pHrng->Instance = RNG;
    if (HAL_RNG_Init(fp_pHrng) != HAL_OK)
    {
        Error_Handler();
    }
    return;
}

/* RNG deinit function */
void MacCfg_RNG_DeInit(RNG_HandleTypeDef *fp_pHrng)
{
    // Deinitialise the hardware peripheral RNG

    HAL_RNG_DeInit(fp_pHrng);

    return;
}
