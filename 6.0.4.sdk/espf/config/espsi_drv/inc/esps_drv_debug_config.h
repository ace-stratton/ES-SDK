/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef DEBUG_H
#define DEBUG_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_debug_config.h
 * @brief    Definitions for the debug options
 *
 * @}
 */

#include <stdint.h>
#include <stdbool.h>

void Error_Handler(void);

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus
/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include <stdio.h>

#include <debug.h>
#include "esps_drv_def.h"

/*
********************************************************************************************
* ESPS driver debug definitions
********************************************************************************************
*/

#ifdef ESPS_CONFIG_DEBUG_ENABLE

#ifndef OPT_VA_ARGS
#define OPT_VA_ARGS(...) , ##__VA_ARGS__
#endif  // #ifndef OPT_VA_ARGS

// Setup the Debug print of the ESPS driver as TRACE_DBG (from the OBC configuration)
#ifdef ESPS_CONFIG_DEBUG_TRACE_ENABLE
#define MACDRV_DBG_PRINT(formatStr, ...)   ES_TRACE_DEBUG(formatStr OPT_VA_ARGS(__VA_ARGS__));
#endif

// Use the OBC debug configuration
#define MACDRV_DBG_ASSERT(condition) DBG_ASSERT(condition)

#endif //ESPS_CONFIG_DEBUG_ENABLE

#endif    /* DEBUG_H */
/* ******************************************************************************************* */
