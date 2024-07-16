/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_DEBUG_H
#define ESPS_DRV_DEBUG_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_debug.h
 * @brief    Debug Definitions Configuration
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

// External imports
#include <esps_drv_debug_config.h>

// This macros should be defined in the debug configuration file

#ifndef MACDRV_DBG_PRINT
#define MACDRV_DBG_PRINT(fmtString, ...)   asm("nop");
#endif

#ifndef MACDRV_DBG_ASSERT
#define MACDRV_DBG_ASSERT(condition)
#endif

#ifdef __cplusplus
}
#endif

#endif //ESPS_DRV_DEBUG_H
