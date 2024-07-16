/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/** @file datetime_cfg.h
 *
 * @brief Time service configuration header
 *
 */

#ifndef __DATETIME_CFG_H__
#define __DATETIME_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "datetime.h"

/**
 * @brief Fills the structure pointed by p_sys_tstamp with the current RTC time
 *        On error p_sys_tstamp is filled with 0's
 */
void datetime_cfg_get_systime(datetime_stamp_t * const p_sys_tstamp);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __DATETIME_CFG_H__
