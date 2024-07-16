/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
  * @addtogroup service_beacons
  * @{
  * @file beacons.c
  *
  * @brief Beacon service core implementation
  * @}
  */

#include "beacons.h"
#include "beacon_types.h"
#include "es_exeh.h"
#include "TaskMonitor.h"
#include "timer.h"
#include "assertions.h"
#include "if_beacons_sink.h"
#include "beacons_sm_user.h"
#include "beacons_sm_config_user.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_BEACONS

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/

/** @brief Component runtime context structure */
beacons_runtime_context_t beacons_rt_context =
{
	.os_task_hnd = NULL,
	.send_timer = { .is_running = SAFE_FALSE },
	.beacon_frame_rolling_cntr = 0U
};

/** @brief Mutex to use for synchronizing access to the component structures */
osMutexDef(beacons_lock);

static const osMutexAttr_t beacons_lock_attr =
{
    "beacons_mutex", 	  // human readable mutex name
    osMutexRecursive,     // attr_bits
    NULL,                 // memory for control block
    0U                    // size for control block
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t beacons_lock_id;

/**********************************************************************
 *
 * Static functions
 *
 **********************************************************************/

/** @brief Main beacons service task function
 *
 *  @param p_task_arg a pointer to a task-specific context structure (if applicable)
 *
*/
STATIC void beacons_task(void * p_task_arg);

/** @brief Sends an event to the internal HSM for processing but ensures locking of state
 * 		   via mutex.
 *  @param event_id HSM event id to process
 *  @return true  - event was processed by the current state;
 *  		false - event was ignored;
 *
 */
STATIC bool inline beacons_trigger_hsm(const uint32_t event_id);

/** @brief Initializes the beacon service and prepares it for operation. */
void beacons_init(void)
{
	EXEH_INIT_MODULE_FILENAME();

	beacons_rt_context.os_task_hnd = NULL;
	beacons_rt_context.beacon_frame_rolling_cntr = 0U;

	timer_stop(&beacons_rt_context.send_timer);

	if (NULL == beacons_lock_id)
	{
		beacons_lock_id = osMutexNew(&beacons_lock_attr);
	}

	beacons_sink.cmd(BEACONS_SINK_ADAPTER_CMD_INIT);

	beacons_trigger_hsm(eHSM_StdEvent_Reset);
	beacons_trigger_hsm(ev_beacons_sm_init);

	// this condition ensures that at least one byte of beacon data will be
	// transferable within the specified buffer size, otherwise, this
	// implementation does not make much sense for such a configuration and
	// the size of the active_beacon_frame buffer has to be increased
	CRIT_ASSERT((sizeof(beacons_rt_context.active_beacon_frame) >
		    	(sizeof(beacon_frame_hdr_t) +
				 sizeof(beacon_msg_hdr_t))));
}

/** @brief Starts regular beacon transmission */
void beacons_start(void)
{
    STATIC const osThreadAttr_t task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "Beacons_Service_Task",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 2500        // TODO: Measure worst-case stack usage!
    };

    // create thread only if not already existing...
    if (NULL == beacons_rt_context.os_task_hnd)
    {
    	beacons_rt_context.os_task_hnd = osThreadNew(beacons_task,
													 (void *) NULL,
                                                     &task_attr);

        if (NULL == beacons_rt_context.os_task_hnd)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal,
                        (int32_t) EXEH_BCN_CANNOT_SPAWN_TASK);
        }
        else
        {
            TaskMonitor_TaskInitialized(TASK_BEACONS);

            beacons_sink.cmd(BEACONS_SINK_ADAPTER_CMD_START);
        }
    }
}

/** @brief Ceases regular beacon transmission */
void beacons_stop(void)
{
	beacons_trigger_hsm(ev_beacons_sm_stop);
	beacons_sink.cmd(BEACONS_SINK_ADAPTER_CMD_STOP);
}

void beacons_confirm_sink_send(const uint8_t id, const bool is_successful_send)
{
	if ((is_successful_send) && (beacons_rt_context.last_sink_frame_id == id))
	{
		SET_TRUE(beacons_rt_context.last_sink_frame_confirmed);
	}
}

void beacons_load_config(void)
{
	Nvm_GetBlockById(NVM_BLOCK_BEACONS_GENERAL, &beacons_rt_context.gen_cfg);
	Nvm_GetBlockById(NVM_BLOCK_BEACONS_PRESETS, &beacons_rt_context.preset_cfg);
}

//
//    Static function definitions
//
STATIC void beacons_task(void * p_task_arg)
{
	static safe_bool_t last_beacon_en_status = SAFE_FALSE;
	bool hsm_result = false;

    // currently unused
    (void) p_task_arg;

    beacons_load_config();

    for (;;)
    {
    	// beacons_rt_context.gen_cfg will be refreshed as part of the HSM implementation
    	if (last_beacon_en_status != beacons_rt_context.gen_cfg.beacons_en)
    	{
    		switch (beacons_rt_context.gen_cfg.beacons_en)
    		{
    			case SAFE_TRUE:
    			{
    				hsm_result = beacons_trigger_hsm(ev_beacons_sm_start);

    				break;
    			}

    			case SAFE_FALSE:
    			{
    				hsm_result = beacons_trigger_hsm(ev_beacons_sm_stop);

    				break;
    			}

    			default:
    			{
    				CRIT_ASSERT(false);
    				break;
    			}
    		}

    		// make sure the HSM event will be fired until it gets processed by the HSM
    		if (hsm_result)
    		{
    			last_beacon_en_status = beacons_rt_context.gen_cfg.beacons_en;
    		}
    	}

		// execute periodic SM activities...
		(void) beacons_trigger_hsm(eHSM_StdEvent_Periodic);

        osDelay(BEACON_TASK_PERIOD_MS);

        TaskMonitor_IamAlive(TASK_BEACONS);
        vApplicationLowStackCheck(TASK_BEACONS);
    }
}

STATIC bool inline beacons_trigger_hsm(const uint32_t event_id)
{
	bool res = false;

    osMutexAcquire(beacons_lock_id, osWaitForever);
    res = HSM_TriggerEvent(beacons_sm_instance, event_id);
    osMutexRelease(beacons_lock_id);

    return res;
}
