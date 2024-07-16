/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef DRV_IWDG_H_
#define DRV_IWDG_H_
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup drv_watchdog Internal Watchdog
 * @{
 *
 * Control the internal watchdog. This will be used for checks on all the running tasks.
 *
 * @file     drv_iwdg.h
 * @brief    Public interface for the watchdog driver
 *
 * @}
 * @}
 *
 */

#include <stdbool.h>
#include <stdint.h>


/**
 * @brief  Initialises IWDG.
 *
 * @param  timeout IWDG timeout in milliseconds
 *
 * @retval true : On success
 * @retval false: On failure
 */
bool drv_iwdg_init(uint32_t timeout);


/**
 * @brief  Get maximum IWDG timeout that can be used with @ref drv_iwdg_init().
 *
 * @return Maximum IWDG timeout (in milliseconds)
 */
uint32_t drv_iwdg_get_max_timeout(void);


/**
 * @brief  Get current IWDG timeout.
 *
 * @return Current IWDG timeout (in milliseconds) or 0 if not initialised.
 */
uint32_t drv_iwdg_get_current_timeout(void);


/**
 * @brief  Refresh (prevent system reset) IWDG.
 *
 * @return true  On success
 *         false On failure
 */
bool drv_iwdg_refresh(void);


#endif /* DRV_IWDG_H_ */
