/*
 * Copyright (c) 2022-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup service_sxband_sched
 * @{
 *
 * @file sxband_sched.c
 *
 * @brief SX-Band Basic Sequential Command Scheduler
 *
 *
 * @}
 */

#include <string.h>
#include "es_exeh.h"
#include "TaskMonitor.h"
#include "timer.h"
#include "assertions.h"
#include "sxband_sched.h"
#include "sxband_sched_cfg.h"
#include "sxband_sched_sm_user.h"
#include "sxband_sched_sm_config_user.h"
#include "sxband_cmd_iter_file.h"

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_SXBAND_SCHED
#define DEFAULT_SUMMARY_FILE_NAME         "SXB_RPT.LOG"

/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/

/** @brief Component runtime context structure */
sxband_sched_rt_ctx_t sxband_sched_rt_context =
{
    .os_task_hnd = NULL,
    .p_sched_notif = NULL,
    .file_iter_status = SXB_INIT_STATUS_MAX,
};

static const osMutexAttr_t sxband_sched_lock_attr =
{
    "sxband_sched_mutex", // human readable mutex name
    osMutexRecursive,     // attr_bits
    NULL,                 // memory for control block
    0U                    // size for control block
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t sxband_sched_lock_id;

/**********************************************************************
 *
 * Static functions
 *
 **********************************************************************/

/** @brief Main SXBand scheduler service task function
 *
 *  @param p_task_arg a pointer to a task-specific context structure (if applicable)
 *
*/
STATIC void sxband_sched_task(void * p_task_arg);

/** @brief Sends an event to the internal HSM for processing but ensures locking of state
 *            via mutex.
 *  @param event_id HSM event id to process
 *  @return true  - event was processed by the current state;
 *          false - event was ignored;
 *
 */
STATIC bool inline sxband_sched_trigger_hsm(const uint32_t event_id);

void sxband_sched_init(void)
{
    EXEH_INIT_MODULE_FILENAME();

    sxband_sched_rt_context.os_task_hnd = NULL;

    if (NULL == sxband_sched_lock_id)
    {
        sxband_sched_lock_id = osMutexNew(&sxband_sched_lock_attr);
    }
}

void sxband_sched_deinit(void)
{
    task_mon_set_task_policy(TASK_SXBAND_SCHED, TASK_MON_POLICY_DONT_CARE);
}

void sxband_sched_start(void)
{
    STATIC const osThreadAttr_t task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "SXBand_Sched_Task",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 2500,        // TODO: Measure worst-case stack usage!
        .tz_module = 0U,
        .reserved = 0U
    };

    (void) sxband_sched_trigger_hsm(eHSM_StdEvent_Reset);

    // create thread only if not already existing...
    if (NULL == sxband_sched_rt_context.os_task_hnd)
    {
        sxband_sched_rt_context.os_task_hnd = osThreadNew(sxband_sched_task,
                                                 NULL,
                                                 &task_attr);

        if (NULL == sxband_sched_rt_context.os_task_hnd)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal,
                        (int32_t) EXEH_SXB_SCHED_CANT_SPAWN_TASK);
        }
        else
        {
            TaskMonitor_TaskInitialized(TASK_SXBAND_SCHED);
        }
    }

    (void) sxband_sched_trigger_hsm(ev_sxband_sched_sm_init);
}

sxband_sched_status_t sxband_sched_start_file_seq(const char * const p_fname, const uint8_t fname_size, sxband_sched_notif_t p_sched_notif)
{
    sxband_sched_status_t res = SXBAND_SCHED_STATUS_FAILED;
    const sState_t *p_hsm_active_state = HSM_GetActiveState(sxband_sched_sm_instance);

    CRIT_ASSERT(NULL != p_hsm_active_state);

    sxband_sched_rt_context.file_iter_status = SXB_INIT_STATUS_MAX;

    if (STATE_IDLE == p_hsm_active_state->state_id)
    {
        sxband_sched_rt_context.file_iter_status = sxband_cmd_iter_file_init_ctx(p_fname, fname_size, &sxband_sched_rt_context.file_iter_ctx);

        if (SXB_INIT_STATUS_OK == sxband_sched_rt_context.file_iter_status)
        {
            sxband_sched_rt_context.p_sched_notif = p_sched_notif;
            sxband_sched_rt_context.final_sched_status = SXBAND_SCHED_STATUS_OK;

            res = SXBAND_SCHED_STATUS_OK;

            (void) sxband_sched_trigger_hsm(ev_sxband_sched_sm_start);
        }
        else
        {
            if (NULL != p_sched_notif)
            {
                FIL def_fhnd;
                char err_buf[50U];

                uint8_t char_count = (uint8_t) snprintf(err_buf, sizeof(err_buf), "SXBand command iterator init error: %d\r\n", (uint16_t) sxband_sched_rt_context.file_iter_status);

                // attempt to write an error report because the iterator context could not be initialized for some reason
                // we don't care about the result of this operation as this is only an emergency measure and we just hope the file
                // can be written but there is no recovery if it failed for some reason
                (void) SdMngr_f_open(&def_fhnd, DEFAULT_SUMMARY_FILE_NAME, FA_CREATE_ALWAYS | FA_WRITE);
                (void) SdMngr_f_write(&def_fhnd, err_buf, char_count, NULL);
                (void) SdMngr_f_close(&def_fhnd);

                // usually the report file name comes from the commands file as a configuration parameter but we use default file name for reporting here
                // because the file iterator could not parse the commands file for some reason
                (*p_sched_notif)(SXBAND_SCHED_STATUS_FAILED, DEFAULT_SUMMARY_FILE_NAME);
            }
        }
    }
    else
    {
        // only one sequence can be executed at a time - no buffering of user requests is performed
        res = SXBAND_SCHED_STATUS_IN_PROGRESS;
    }

    return res;
}

void sxband_sched_stop_file_seq(void)
{

    sxband_sched_rt_context.final_sched_status = SXBAND_SCHED_STATUS_INTERRUPTED;
    (void) sxband_sched_trigger_hsm(ev_sxband_sched_sm_stop);
}

void sxband_sched_on_cmd_complete(void * const p_user_ctx)
{
    (void) p_user_ctx;

    sxband_sched_rt_context.sxband_result_notified = true;
}

bool sxband_sched_is_file_seq_active(void)
{
    return sxband_sched_rt_context.is_file_seq_in_progress;
}

//
//    Static function definitions
//
STATIC void sxband_sched_task(void * p_task_arg)
{
    // currently unused
    (void) p_task_arg;

    for (;;)
    {
        osDelay(SXBAND_SCHED_TASK_PERIOD_MS);

		(void) sxband_sched_trigger_hsm(ev_sxband_sched_sm_failure_check);

        (void) sxband_sched_trigger_hsm(eHSM_StdEvent_Periodic);

        // the flag is used here to prevent corrupting the HSM context if
        // the SXBand driver calls the callback function while the HSM engine
        // hasn't yet finished with the action function execution
        if (sxband_sched_rt_context.sxband_result_notified)
        {
            (void) sxband_sched_trigger_hsm(ev_sxband_sched_sm_cmd_confirmed);
            sxband_sched_rt_context.sxband_result_notified = false;
        }

        TaskMonitor_IamAlive(TASK_SXBAND_SCHED);
        vApplicationLowStackCheck(TASK_SXBAND_SCHED);
    }
}

STATIC bool inline sxband_sched_trigger_hsm(const uint32_t event_id)
{
    bool res = false;

    osMutexAcquire(sxband_sched_lock_id, osWaitForever);
    res = HSM_TriggerEvent(sxband_sched_sm_instance, event_id);
    osMutexRelease(sxband_sched_lock_id);

    return res;
}
