/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup lib_debug
 * @{
 *
 * @file debug_cfg.h
 * @brief Debug library configuration parameter settings
 *
 * @}
 */
#ifndef ESPF_CONFIG_LIBDEBUG_DEBUG_CFG_H_
#define ESPF_CONFIG_LIBDEBUG_DEBUG_CFG_H_

#include "stm32h7xx.h"

/** @name Test pins settings used by the `Debug` library
 * @{
 * Change these settings in order to modify the physical Debug library mapping for the test pins.
 */
#define TEST_OUT_0_PORT	GPIOB
#define TEST_OUT_0_PIN	GPIO_PIN_15

#define TEST_OUT_1_PORT	GPIOD
#define TEST_OUT_1_PIN	GPIO_PIN_4
/** @} */

/** @brief Size of the Debug library static printf buffer in bytes
 *  @note Must be increased if you need to print longer strings.
*/
#define DBG_PRINTF_BUF_SIZE         ((uint8_t) 70)

#endif /* ESPF_CONFIG_LIBDEBUG_DEBUG_CFG_H_ */
