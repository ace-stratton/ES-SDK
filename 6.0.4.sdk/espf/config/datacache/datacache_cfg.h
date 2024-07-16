/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*!
********************************************************************************************
* @file datacache_cfg.h
* @brief Data Cache Configuration Header Generator
********************************************************************************************
* @version           interface data_cache v0.1
*
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_DC v0.1
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as 
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __DATACACHE_CFG_H__
#define __DATACACHE_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>

#include "cmsis_os2.h"
#include "main.h"
#include "AppTasks.h"

/**********************************************************************
 *
 *  Implement these functions in your build to be able to link the Data Cache!
 *
 **********************************************************************/

// DC mutex type 
typedef void * dc_cfg_lock_t;

void dc_cfg_init(void);

#ifdef DC_DATA_ACCESS_SYNC_ENABLED
/* \brief A function which creates a system lock object, e.g., a mutex to synchronize access to the Data Cache items. */
dc_cfg_lock_t dc_cfg_lock_new(const char *p_lock_name);

#define dc_cfg_lock_acquire(lock) do { if (osMutexAcquire((lock), osWaitForever) != osOK) Error_Handler(); } while (0U);
#define dc_cfg_lock_release(lock) do { if (osMutexRelease(lock) != osOK) Error_Handler(); } while (0U);

#endif  // DC_DATA_ACCESS_SYNC_ENABLED

/* \brief Provides a tick count since the system was started. It is used to track internal status timeouts. */
// uint32_t dc_cfg_get_sys_timestamp(void);
#define dc_cfg_get_sys_timestamp()	osKernelGetTickCount()

#define DC_TASK_INTERVAL_MS		(1000U)

#ifndef PACKED_STRUCT
#define PACKED_STRUCT			__attribute__((__packed__))
#endif

#if defined(DEBUG_TRACE_DATACACHE_ENABLED)
#define DATACACHE_DBG_PRINT(formatStr, ...)   ES_TRACE_DEBUG(formatStr OPT_VA_ARGS(__VA_ARGS__));
#else
#define DATACACHE_DBG_PRINT(fmtString, ...)   asm("nop");
#endif

#ifndef DC_ASSERT
#define DC_ASSERT(cond)			if (0U == (cond)) Error_Handler();
#endif

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __DATACACHE_CFG_H__

