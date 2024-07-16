/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry.c
 *
 * @brief Telemetry service core implementation
 *
 *
 * @}
 */

#include <string.h>
#include "telemetry.h"
#include "es_exeh.h"
#include "TaskMonitor.h"
#include "timer.h"
#include "assertions.h"
#include "telemetry_sm_user.h"
#include "telemetry_sm_config_user.h"
#include "config/telemetry/telemetry_cfg_user.h"
#include "telemetry_file_sink.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_TELEMETRY_FILESINK

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/

/** @brief Component runtime context structure */
tlm_runtime_context_t tlm_rt_context =
{
    .os_task_hnd = NULL,
    .tlm_timer = { .is_running = SAFE_FALSE },
	.rolling_cntr = 0U,
};

static const osMutexAttr_t telemetry_lock_attr =
{
    "tlm_mutex",             // human readable mutex name
    osMutexRecursive,     // attr_bits
    NULL,                 // memory for control block
    0U                    // size for control block
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t telemetry_lock_id;

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
static void telemetry_task(void * p_task_arg);

/** @brief Sends an event to the internal HSM for processing but ensures locking of state
 *            via mutex.
 *  @param event_id HSM event id to process
 *  @return true  - event was processed by the current state;
 *          false - event was ignored;
 *
 */
static bool inline telemetry_trigger_hsm(const uint32_t event_id);

/** @brief Initializes the telemetry service and prepares it for operation. */
void telemetry_init(void)
{
    EXEH_INIT_MODULE_FILENAME();

    tlm_rt_context.os_task_hnd = NULL;

    timer_stop(&tlm_rt_context.tlm_timer);

    if (NULL == telemetry_lock_id)
    {
        telemetry_lock_id = osMutexNew(&telemetry_lock_attr);
    }

    telemetry_trigger_hsm(eHSM_StdEvent_Reset);
    telemetry_trigger_hsm(ev_telemetry_sm_init);

    telemetry_file_sink_if.cmd(TELEMETRY_SINK_ADAPTER_CMD_INIT);
}

void telemetry_start(void)
{
    static const osThreadAttr_t task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "Telemetry_Service_Task",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 2500        // TODO: Measure worst-case stack usage!
    };

    // create thread only if not already existing...
    if (NULL == tlm_rt_context.os_task_hnd)
    {
        tlm_rt_context.os_task_hnd = osThreadNew(telemetry_task,
                                                 (void *) NULL,
                                                 &task_attr);

        if (NULL == tlm_rt_context.os_task_hnd)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal,
                        (int32_t) EXEH_TLM_CANNOT_SPAWN_TASK);
        }
        else
        {
            TaskMonitor_TaskInitialized(TASK_TELEMETRY);

            (void) telemetry_trigger_hsm(ev_telemetry_sm_start);

            telemetry_file_sink_if.cmd(TELEMETRY_SINK_ADAPTER_CMD_START);
        }
    }
}

void telemetry_stop(void)
{
    (void) telemetry_trigger_hsm(ev_telemetry_sm_stop);
    telemetry_file_sink_if.cmd(TELEMETRY_SINK_ADAPTER_CMD_STOP);
}

void telemetry_load_config(void)
{
    static uint8_t prev_preset_id = 0U;

    Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_GENERAL, &tlm_rt_context.gen_cfg);
    Nvm_GetBlockById(NVM_BLOCK_TELEMETRY_PRESETS, &tlm_rt_context.preset_cfg);
	tlm_rt_context.active_preset_id = telemetry_cfg_get_active_preset();

	if (prev_preset_id != tlm_rt_context.active_preset_id)
	{
	    // reset acquisition counters...
	    (void) memset(tlm_rt_context.tlm_message_acq_counters,
	                  0U,
	                  sizeof(tlm_rt_context.tlm_message_acq_counters));

	    prev_preset_id = tlm_rt_context.active_preset_id;
	}

	CRIT_ASSERT(tlm_rt_context.active_preset_id < TELEMETRY_PRESETS_COUNT);
}

//
//    Static function definitions
//
static void telemetry_task(void * p_task_arg)
{
    static safe_bool_t last_tlm_en_status = SAFE_FALSE;
    bool hsm_result = false;

    // currently unused
    (void) p_task_arg;

    telemetry_load_config();

    for (;;)
    {
        if (last_tlm_en_status != tlm_rt_context.gen_cfg.telemetry_en)
        {
            switch (tlm_rt_context.gen_cfg.telemetry_en)
            {
                case SAFE_TRUE:
                {
                    hsm_result = telemetry_trigger_hsm(ev_telemetry_sm_start);

                    break;
                }

                case SAFE_FALSE:
                {
                    hsm_result = telemetry_trigger_hsm(ev_telemetry_sm_stop);

                    break;
                }

                default:
                {
                    CRIT_ASSERT(false);
                    break;
                }
            }

            (void) hsm_result;
			last_tlm_en_status = tlm_rt_context.gen_cfg.telemetry_en;
        }

        // execute periodic SM activities...
        (void) telemetry_trigger_hsm(eHSM_StdEvent_Periodic);

        osDelay(TLM_TASK_PERIOD_MS);

        TaskMonitor_IamAlive(TASK_TELEMETRY);
        vApplicationLowStackCheck(TASK_TELEMETRY);
    }
}

static bool inline telemetry_trigger_hsm(const uint32_t event_id)
{
    bool res = false;

    osMutexAcquire(telemetry_lock_id, osWaitForever);
    res = HSM_TriggerEvent(telemetry_sm_instance, event_id);
    osMutexRelease(telemetry_lock_id);

    return res;
}
