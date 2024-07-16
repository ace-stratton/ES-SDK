/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*!
********************************************************************************************
* @file datacache_cfg.h
* @brief Data Cache Configuration Implementation
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

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>

#include "cmsis_os2.h"
#include <main.h>
#include "datacache_cfg.h"
#include "TaskMonitor.h"
#include "datacache.h"

static void dc_cfg_task(void * fp_pvArg);

void dc_cfg_init(void)
{
    static const osThreadAttr_t dc_task_descriptor =
    {
        .attr_bits = osThreadDetached,
        .name      = "DataCacheTask",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 2500      // worst-case measured value is ~1500 bytes
    };

    osThreadId_t task_hnd = osThreadNew(dc_cfg_task,
										(void *) NULL,
										&dc_task_descriptor);

	if (task_hnd == NULL)
	{
		DC_ASSERT(0U);
	}
	else
		TaskMonitor_TaskInitialized(TASK_DATACACHE);
}

static void dc_cfg_task(void * fp_pvArg)
{
	while (1U)
	{
		dc_task();

		osDelay(DC_TASK_INTERVAL_MS);

        TaskMonitor_IamAlive(TASK_DATACACHE);
        vApplicationLowStackCheck(TASK_DATACACHE);
	}

	osThreadExit();
}

#ifdef DC_DATA_ACCESS_SYNC_ENABLED
/* \brief A function which creates a system lock object, e.g., a mutex to synchronize access to the Data Cache items. */
dc_cfg_lock_t dc_cfg_lock_new(const char *p_lock_name)
{
	osMutexAttr_t mid_data_id_attr = { p_lock_name , osMutexRecursive | osMutexPrioInherit, NULL, 0U};
	return osMutexNew(&mid_data_id_attr);
}

#if 0
	void dc_cfg_lock_acquire(dc_cfg_lock_t lock)
	{
		if (osMutexAcquire(lock, osWaitForever) != osOK)
			Error_Handler();
	}

	void dc_cfg_lock_release(dc_cfg_lock_t lock)
	{
		if (osMutexRelease(lock) != osOK)
			Error_Handler();
	}
#endif

#endif  // DC_DATA_ACCESS_SYNC_ENABLED
