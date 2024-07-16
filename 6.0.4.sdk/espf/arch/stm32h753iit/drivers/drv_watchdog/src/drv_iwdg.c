/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup drv_watchdog
 * @{
 *
 * @file     drv_iwdg.c
 * @brief    Watchdog driver
 *
 * @}
 *
 */

#include "../inc/drv_iwdg.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_iwdg.h"
#include <math.h>

#define FS_WINDOW_MAX                            0x0FFF
#define FS_RELOAD_MAX                            0x0FFF
#define FS_CALC_RELOAD(time, freq, prescaler)    ((time * freq) / (4000 * pow(2, prescaler)) - 1)
#define FS_CALC_TIMEOUT(reload, freq, prescaler) (((reload + 1) * (4000 * pow(2, prescaler))) / freq)


static IWDG_HandleTypeDef fs_hiwdg;
static uint32_t fs_current_timeout_ms = 0;


bool drv_iwdg_init(uint32_t timeout)
{
#ifdef DEBUG_ENABLED
    __HAL_DBGMCU_FREEZE_IWDG1();
#endif

	if (0 == timeout)
	{
		return false;
	}

    if (FS_CALC_TIMEOUT(FS_RELOAD_MAX, LSI_VALUE, IWDG_PRESCALER_256) < timeout)
    {
    	timeout = FS_CALC_TIMEOUT(FS_RELOAD_MAX, LSI_VALUE, IWDG_PRESCALER_256);
    }

    fs_hiwdg.Instance       = IWDG1;
    fs_hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
    fs_hiwdg.Init.Window    = FS_WINDOW_MAX;
    fs_hiwdg.Init.Reload    = FS_CALC_RELOAD(timeout, LSI_VALUE, IWDG_PRESCALER_256);

    if (FS_RELOAD_MAX < fs_hiwdg.Init.Reload)
    {
    	fs_hiwdg.Init.Reload = FS_RELOAD_MAX;
    	fs_current_timeout_ms = FS_CALC_TIMEOUT(FS_RELOAD_MAX, LSI_VALUE, IWDG_PRESCALER_256);
    }
    else
    {
    	fs_current_timeout_ms = timeout;
    }

    if (HAL_OK != HAL_IWDG_Init(&fs_hiwdg))
    {
        return false;
    }

	return true;
}


uint32_t drv_iwdg_get_max_timeout(void)
{
    return FS_CALC_TIMEOUT(FS_RELOAD_MAX, LSI_VALUE, IWDG_PRESCALER_256);
}


uint32_t drv_iwdg_get_current_timeout(void)
{
	return fs_current_timeout_ms;
}


bool drv_iwdg_refresh(void)
{
    if (HAL_OK != HAL_IWDG_Refresh(&fs_hiwdg))
    {
        return false;
    }

	return true;
}
