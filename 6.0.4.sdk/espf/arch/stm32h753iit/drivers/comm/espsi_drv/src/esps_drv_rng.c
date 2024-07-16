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
 * @file     esps_drv_rng.c
 * @brief    Random Number Generator implementation (relies on HW RNG module)
 *
 * @}
 */

#include "esps_drv_rng_config.h"

#include "esps_drv_cdef.h"
#include "esps_drv_rng.h"
#include "esps_drv_exeh.h"

#define EXEH_CURRENT_MODULE_ID      (eEXEHModuleID_MAC_RNG)
#define RAND_ARRAY_SIZE             ((uint8_t) 16)

/// RNG peripherial Handler
RNG_HandleTypeDef hrng;

/// Vector of random numbers to
static uint32_t u32RandVector[RAND_ARRAY_SIZE] = { (uint32_t) 0 };

/// Cyclic index used to access the next random value from the random-number vector
static uint32_t u8CurrentRandIndex = (uint8_t) 0;

/// initialize the vector with random values
static void fs_InitRandomVector(void);

/// initialize the Hardware RNG
void MAC_RNG_Init(void)
{

    MacCfg_RNG_Init(&hrng);

    fs_InitRandomVector();
    u8CurrentRandIndex = (uint8_t) 0;
}

/// De init the Hardware RNG
void MAC_RNG_DeInit(void)
{
    MacCfg_RNG_DeInit(&hrng);
}

/// Get a random generated number
uint32_t MAC_RNG_GetRandomNumberInRange(uint32_t fp_u32Range)
{
    u8CurrentRandIndex = (u8CurrentRandIndex + 1) % (CDEF_ELEMENT_COUNT(u32RandVector));

    return (uint32_t) (u32RandVector[u8CurrentRandIndex] % fp_u32Range);
}

static void fs_InitRandomVector(void)
{
    uint8_t i;

    for(i = 0; i < CDEF_ELEMENT_COUNT(u32RandVector); i++)
        if(HAL_ERROR == HAL_RNG_GenerateRandomNumber(&hrng, &u32RandVector[i]))
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal, eMACException_InvalidParameter);
        }

    // Deinit after generating the vector to minimise power consumption
    MAC_RNG_DeInit();
}
