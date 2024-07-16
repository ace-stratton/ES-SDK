/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_STM32_H
#define ESPS_DRV_STM32_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_stm32.h
 * @brief    Add all the headers related to the MCU used for the drivers.
 *
 * @}
 */

// Needed headers from the STM32Fxx for the drivers to work
#include "stm32h7xx_hal.h"

#include "stm32h753xx.h"
#include "stm32h7xx.h"

#include "stm32h7xx_ll_tim.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_usart.h"

#endif // ESPS_DRV_STM32_H
