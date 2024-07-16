/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @defgroup service_tlm
 * @{
 *
 * @file telemetry_file_sink.c
 *
 * @brief Telemetry file sink implementation.
 *
 * The module implements the standard `if_telemetry_sink` interface and provides:
 * - File storage of telemetry frames on the SD card.
 * - Data distribution over multiple files according to the applied NVM configuration.
 *
 * @}
 */

#include <string.h>
#include "es_cdef.h"
#include "es_exeh.h"
#include "assertions.h"
#include "if_telemetry_sink.h"
#include "config/telemetry/telemetry_cfg_user.h"
#include "telemetry_file_sink_sm_user.h"
#include "telemetry_file_sink_sm_config_user.h"
#include "TaskMonitor.h"
#include "SdMngr.h"

/*
***************************************************************************************************
* INTERNAL DEFINES
***************************************************************************************************
*/
/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_SYS_STAT_AND_TLMTRY

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
***************************************************************************************************
*/
/** @brief Initialize the telemetry file sink */
static void telemetry_file_sink_init(void);

/** @brief Execute any pending external tasks which must be synchronous to the main task execution to
 *         avoid context corruption.
 */
static void telemetry_file_sink_exec_syncd_tasks(void);

/** @brief Execute a file sink command
 *
 *  @param[in] cmd command ID to execute
 */
static void telemetry_file_sink_adapter_cmd(const telemetry_sink_adapter_cmd_t cmd);

/** @brief Main telemetry file sink task function
 *
 *  @param p_task_arg a pointer to a task-specific context structure (if applicable)
 *
*/
static void telemetry_file_sink_task(void * p_task_arg);

/** @brief Trigger the telemetry file sink state machine
 *
 *  @param[in] event_id HSM event ID to send to the SM engine
 *
 *  @retval true: the event was processed by the HSM
 *  @retval false: the event wasn't processed by the HSM
*/
static bool inline telemetry_file_trigger_hsm(const uint32_t event_id);

/*
***************************************************************************************************
* INTERNAL TYPES DEFINITION
***************************************************************************************************
*/
/** @brief Component runtime context structure */
tlm_file_sink_rt_ctx_t tlm_filesink_rt_context =
{
    .os_task_hnd = NULL,
    .prev_cfg_type = TLM_FILE_CFG_TYPE_MAX,
    .current_idx = 0U,
    .max_file_size_bytes = 0U
};

telemetry_sink_if_t telemetry_file_sink_if =
{
    .cmd = telemetry_file_sink_adapter_cmd
};

static const osMutexAttr_t telemetry_file_lock_attr =
{
    "tlm_file_sink_mutex",
    osMutexRecursive,
    NULL,
    0U
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t telemetry_file_lock_id;

/*
***************************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
***************************************************************************************************
*/
static void telemetry_file_sink_init(void)
{
    static const osThreadAttr_t task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "Telemetry_File_Sink_Task",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 2500,
        .reserved = 0U,
        .tz_module = 0
    };

    for (uint8_t idx = 0; idx < TLM_FILE_SINK_OP_MAX; idx++)
    {
        tlm_filesink_rt_context.main_task_sync_op_flags[idx] = false;
    }

    CRIT_ASSERT(sizeof(TLM_FILE_SINK_EXT) <= 4U);

    (void) strcat(tlm_filesink_rt_context.wildcard, "*.");
    (void) strcat(tlm_filesink_rt_context.wildcard, TLM_FILE_SINK_EXT);

    if (NULL == telemetry_file_lock_id)
    {
        telemetry_file_lock_id = osMutexNew(&telemetry_file_lock_attr);
    }

    // create thread only if not already existing...
    if (NULL == tlm_filesink_rt_context.os_task_hnd)
    {
        tlm_filesink_rt_context.os_task_hnd = osThreadNew(telemetry_file_sink_task,
                                                          NULL,
                                                          &task_attr);

        if (NULL == tlm_filesink_rt_context.os_task_hnd)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal,
                        (int32_t) EXEH_TLM_FS_CANNOT_SPAWN_TASK);
        }
        else
        {
            TaskMonitor_TaskInitialized(TASK_TELEMETRY_FILE_SINK);
        }
    }
}

static void telemetry_file_sink_exec_syncd_tasks(void)
{
    for (uint8_t idx = 0; idx < (uint8_t) TLM_FILE_SINK_OP_MAX; idx++)
    {
        if (true == tlm_filesink_rt_context.main_task_sync_op_flags[idx])
        {
            if (idx == (uint8_t) TLM_FILE_SINK_OP_PAUSE)
            {
                (void) telemetry_file_trigger_hsm(ev_telemetry_file_sink_sm_stop);
            }

            if (idx == (uint8_t) TLM_FILE_SINK_OP_CFG_UPDATE)
            {
                (void) telemetry_file_trigger_hsm(ev_telemetry_file_sink_sm_restart);
            }

            if (idx == (uint8_t) TLM_FILE_SINK_OP_CLEAN)
            {
                telemetry_file_sink_clean();
            }

            tlm_filesink_rt_context.main_task_sync_op_flags[idx] = false;
        }
    }
}

static void telemetry_file_sink_adapter_cmd(const telemetry_sink_adapter_cmd_t cmd)
{
    switch (cmd)
    {
        case TELEMETRY_SINK_ADAPTER_CMD_INIT:
        {
            telemetry_file_sink_init();

            (void) telemetry_file_trigger_hsm(eHSM_StdEvent_Reset);
            (void) telemetry_file_trigger_hsm(ev_telemetry_file_sink_sm_init);
            break;
        }

        case TELEMETRY_SINK_ADAPTER_CMD_START:
        {
            (void) telemetry_file_trigger_hsm(ev_telemetry_file_sink_sm_start);

            break;
        }

        case TELEMETRY_SINK_ADAPTER_CMD_STOP:
        {
            (void) telemetry_file_trigger_hsm(ev_telemetry_file_sink_sm_stop);
            break;
        }

        default:
        {
            CRIT_ASSERT(false);
            break;
        }
    }
}

static void telemetry_file_sink_task(void * p_task_arg)
{
    (void) p_task_arg;

    while (true)
    {
        telemetry_file_sink_exec_syncd_tasks();

        (void) telemetry_file_trigger_hsm(eHSM_StdEvent_Periodic);

        osDelay(TLM_FILE_SINK_TASK_PERIOD_MS);

        TaskMonitor_IamAlive(TASK_TELEMETRY_FILE_SINK);
        vApplicationLowStackCheck(TASK_TELEMETRY_FILE_SINK);
    }
}

static bool inline telemetry_file_trigger_hsm(const uint32_t event_id)
{
    bool res = false;

    osMutexAcquire(telemetry_file_lock_id, osWaitForever);
    res = HSM_TriggerEvent(telemetry_file_sink_sm_instance, event_id);
    osMutexRelease(telemetry_file_lock_id);

    return res;
}

/*
***************************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
void telemetry_file_sink_pause(const uint32_t ms_before_resume)
{
    tlm_filesink_rt_context.auto_resume_period_ms = ms_before_resume;
    tlm_filesink_rt_context.main_task_sync_op_flags[TLM_FILE_SINK_OP_PAUSE] = true;
}

void telemetry_file_sink_syncd_clean(void)
{
    tlm_filesink_rt_context.main_task_sync_op_flags[TLM_FILE_SINK_OP_CLEAN] = true;
}

void telemetry_file_sink_config_update(void)
{
    tlm_filesink_rt_context.main_task_sync_op_flags[TLM_FILE_SINK_OP_CFG_UPDATE] = true;
}
