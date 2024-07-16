/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _TIMER_CFG_H_
#define _TIMER_CFG_H_

/**
 * @addtogroup libtimer
 * @{
 *
 * @file    timer_cfg.h
 * @brief   Timer library configuration header
 *
 * @}
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus

#include "cmsis_os2.h"

#ifndef timer_cfg_sys_get_tick_count
// hook to a system-specific tick count function which returns milliseconds from system start
#define timer_cfg_sys_get_tick_count()	osKernelGetTickCount()
#endif	// #ifndef sys_get_tick_count

#ifndef timer_cfg_sys_time_init
// hook to a system-specific time init function (if applicable for your system)
#define timer_cfg_sys_time_init()
#endif	// #ifndef timer_cfg_sys_time_init

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* _TIMER_CFG_H_ */
