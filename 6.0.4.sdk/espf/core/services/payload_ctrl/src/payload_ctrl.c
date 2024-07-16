/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup payload_ctrl
 * @{
 *
 * @file payload_ctrl.c
 *
 * @brief Payload Controller main implementation.
 *
 * @}
 */

#include "es_cdef.h"
#include <string.h>
#include "payload_ctrl.h"
#include "cmsis_os2.h"
#include "es_exeh.h"
#include "TaskMonitor.h"
#include "timer.h"
#include "assertions.h"
#include "trace.h"
#include "payload_ctrl_sm_user.h"
#include "payload_ctrl_sm_types.h"

//
//    Internal preprocessor defines
//

/** @brief Module ID used for this file to report error events in EXEH */
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_PAYLOAD_CTRL

/** @brief activation flags to unblock the main OS task */
#define PAYLOAD_TASK_ACTIVATE_FLAGS        (0x01U)

//
//    Internal type definitions
//
typedef enum
{
    ERR_CANNOT_SPAWN_TASK
} exeh_error_codes_t;

//
//    Static variables
//

pl_ctrl_runtime_context_t pl_ctrl_runtime_context =
{
    .is_initialized = SAFE_FALSE,
    .os_task_hnd = NULL,
    .p_user_event_cbk = NULL
};

/** @brief Mutex to use for synchronizing access to the component structures */
osMutexDef(payload_ctrl_lock);

static const osMutexAttr_t payload_ctrl_lock_attr =
{
    "payload_ctrl_mutex", // human readable mutex name
    osMutexRecursive,     // attr_bits
    NULL,                 // memory for control block
    0U                    // size for control block
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t payload_ctrl_lock_id;

//
//    Static function declarations
//

/** @brief Payload monitoring OS task started after a call to @ref payload_ctrl_init
 *  @param p_task_arg a pointer to any task arguments provided at task creation
 *
 */
STATIC void payload_ctrl_task(void * p_task_arg);

/** @brief Sends an event to the internal HSM for processing but ensures locking of state
 *            via mutex.
 *  @param event_id HSM event id to process
 *
 */
STATIC void inline payload_ctrl_trigger_hsm(const uint32_t event_id);

//
//    Public function definitions
//

payload_ctrl_op_res_t payload_ctrl_init(void)
{
    STATIC const osThreadAttr_t task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "PayloadCtrlMainTask",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 3000        // TODO: Measure worst-case stack usage!
    };
    payload_ctrl_op_res_t res = PL_CTRL_OP_RES_FAILED;

    EXEH_INIT_MODULE_FILENAME();

    // call configured payload init functions...
    for (uint8_t pl_id = 0; pl_id < PAYLOAD_COUNT; pl_id++)
    {
        const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(pl_id);

        CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
        CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface);
        CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->init);

        pl_ctrl_runtime_context.state_mon_data[pl_id].last_reported_state = PL_STATE_NOT_INIT;
        timer_stop(&pl_ctrl_runtime_context.state_mon_data[pl_id].state_timer);
        pl_ctrl_runtime_context.state_mon_data[pl_id].pending_flags = PENDING_FLAG_CLEAR_ALL;
        pl_ctrl_runtime_context.point_target_pl_id = PAYLOAD_COUNT;

        p_pl_cfg->p_pl_interface->init(p_pl_cfg->internal_inst_id,
                                       (pl_config_t * const) &p_pl_cfg->init_config,
                                       p_pl_cfg->p_pl_notif_cbk);
    }

    payload_ctrl_trigger_hsm(eHSM_StdEvent_Reset);

    // create thread only if not already existing...
    if (NULL == pl_ctrl_runtime_context.os_task_hnd)
    {
        payload_ctrl_lock_id = osMutexNew(&payload_ctrl_lock_attr);

        CRIT_ASSERT(NULL != payload_ctrl_lock_id);

        pl_ctrl_runtime_context.os_task_hnd = osThreadNew(payload_ctrl_task,
                                                          (void *) NULL,
                                                          &task_attr);

        if (NULL == pl_ctrl_runtime_context.os_task_hnd)
        {
            EXEH_HANDLE(eEXEHSeverity_Fatal,
                        (int32_t) ERR_CANNOT_SPAWN_TASK);
        }
        else
        {
            TaskMonitor_TaskInitialized(TASK_MONITOR_PAYLOAD_CTRL);
            SET_TRUE(pl_ctrl_runtime_context.is_initialized);

            res = PL_CTRL_OP_RES_OK;
        }
    }

    return res;
}

payload_ctrl_op_res_t payload_ctrl_deinit(void)
{
    for (uint8_t pl_id = 0; pl_id < PAYLOAD_COUNT; pl_id++)
    {
        const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(pl_id);

        CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
        CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface);
        CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->deinit);

        pl_op_status_t res = p_pl_cfg->p_pl_interface->deinit(p_pl_cfg->internal_inst_id);

        (void) res;
        CRIT_ASSERT(PL_OP_STATUS_OK == res);
    }

    return PL_OP_STATUS_OK;
}

payload_ctrl_op_res_t payload_ctrl_start(const payload_ctrl_payload_t payload_id,
                                         payload_ctrl_start_cfg_t * const p_start_cfg)
{
    const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(payload_id);

    CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
    CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface);
    CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->start);

    pl_state_t pl_state = p_pl_cfg->p_pl_interface->get_state(p_pl_cfg->internal_inst_id);

    osMutexAcquire(payload_ctrl_lock_id, osWaitForever);

    switch (pl_state)
    {
        case PL_STATE_STOPPED:
        case PL_STATE_ERROR:
        {
            (void) memcpy((void * volatile) &pl_ctrl_runtime_context.state_mon_data[payload_id].start_cfg,
                          (const void * volatile) p_start_cfg,
                          sizeof(payload_ctrl_start_cfg_t));

            pl_ctrl_runtime_context.state_mon_data[payload_id].pending_flags |= PENDING_FLAG_START;

            uint32_t set_flags = osThreadFlagsSet(pl_ctrl_runtime_context.os_task_hnd, PAYLOAD_TASK_ACTIVATE_FLAGS);

            (void) set_flags;

            break;
        }

        default:
            break;
    }

    osMutexRelease(payload_ctrl_lock_id);

    return PL_CTRL_OP_RES_OK;
}

payload_ctrl_op_res_t payload_ctrl_stop(const payload_ctrl_payload_t payload_id,
                                        const pl_op_stop_mode_t stop_mode)
{
    pl_op_status_t paylod_result = PL_OP_STATUS_FAILURE;

    const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(payload_id);

    CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
    CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface);
    CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->stop);

    paylod_result = p_pl_cfg->p_pl_interface->stop(p_pl_cfg->internal_inst_id, stop_mode);

    if (payload_id == pl_ctrl_runtime_context.point_target_pl_id)
    {
        payload_ctrl_trigger_hsm(ev_payload_ctrl_sm_requesting_payload_off);
    }

    return (PL_OP_STATUS_OK == paylod_result) ? (PL_CTRL_OP_RES_OK) : (PL_CTRL_OP_RES_FAILED);
}

void payload_ctrl_subscribe_events(p_payload_event const p_evt_callback)
{
    pl_ctrl_runtime_context.p_user_event_cbk = p_evt_callback;
}

payload_ctrl_op_res_t payload_ctrl_get_state(const payload_ctrl_payload_t payload_id,
                                        pl_state_t * p_state,
                                        uint32_t * const p_error_code)
{
    CRIT_ASSERT(NULL != p_state);

    const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(payload_id);

    CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
    CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface);
    CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->get_state);

    *p_state = p_pl_cfg->p_pl_interface->get_state(p_pl_cfg->internal_inst_id);

    if (NULL != p_error_code)
    {
        *p_error_code = p_pl_cfg->p_pl_interface->get_last_error(p_pl_cfg->internal_inst_id);
    }

    return PL_CTRL_OP_RES_OK;
}

void payload_ctrl_event_notify(const payload_ctrl_payload_t payload_id, pl_state_t to_state)
{
    pl_ctrl_runtime_context.state_mon_data[payload_id].last_reported_state = to_state;

    if ((payload_id == pl_ctrl_runtime_context.point_target_pl_id) &&
        ((PL_STATE_STOPPED == to_state) || (PL_STATE_ERROR == to_state)))
    {
        payload_ctrl_trigger_hsm(ev_payload_ctrl_sm_requesting_payload_off);
    }

    switch (to_state)
    {
        case PL_STATE_STARTING:
        case PL_STATE_STOPPING:
        {
            // start tracking payload transient state time...
            timer_start(&pl_ctrl_runtime_context.state_mon_data[payload_id].state_timer);
            break;
        }

        default:
        {
            timer_stop(&pl_ctrl_runtime_context.state_mon_data[payload_id].state_timer);
            break;
        }
    }

    if (NULL != pl_ctrl_runtime_context.p_user_event_cbk)
    {
        const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(payload_id);

        CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
        CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface);
        CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->get_state);

        payload_ctrl_event_t pl_event =
        {
            .payload_id = payload_id,
            .op_state = to_state,
        };

        pl_event.error_code = p_pl_cfg->p_pl_interface->get_last_error(p_pl_cfg->internal_inst_id);

        pl_ctrl_runtime_context.p_user_event_cbk(&pl_event);
    }
}

//
//    Static function definitions
//
STATIC void payload_ctrl_task(void * p_task_arg)
{
    CRIT_ASSERT(IS_TRUE(pl_ctrl_runtime_context.is_initialized));

    // currently unused
    (void) p_task_arg;

    for (;;)
    {
        volatile uint32_t task_flag_status = osThreadFlagsWait(PAYLOAD_TASK_ACTIVATE_FLAGS,
                                                               osFlagsWaitAny,
                                                               PAYLOAD_TASK_TIMEOUT_MS);

        (void) task_flag_status;

        // execute periodic SM activities...
        payload_ctrl_trigger_hsm(eHSM_StdEvent_Periodic);

        //
        for (uint8_t pl_id = 0; pl_id < PAYLOAD_COUNT; pl_id++)
        {
            if (pl_ctrl_runtime_context.state_mon_data[pl_id].state_timer.is_running)
            {
                if (timer_is_elapsed(&pl_ctrl_runtime_context.state_mon_data[pl_id].state_timer, PAYLOAD_TRANSIENT_STATE_TIMEOUT_MS))
                {
                    timer_stop(&pl_ctrl_runtime_context.state_mon_data[pl_id].state_timer);

                    ES_TRACE_WARN("WARN: Payload '%d' is staying in a transient state '%d' for too long.",
                              pl_id,
                              pl_ctrl_runtime_context.state_mon_data[pl_id].last_reported_state);
                }
            }
        }

        TaskMonitor_IamAlive(TASK_MONITOR_PAYLOAD_CTRL);
        vApplicationLowStackCheck(TASK_MONITOR_PAYLOAD_CTRL);
    }
}

STATIC void inline payload_ctrl_trigger_hsm(const uint32_t event_id)
{
    osMutexAcquire(payload_ctrl_lock_id, osWaitForever);
    (void) HSM_TriggerEvent(payload_ctrl_sm_instance, event_id);
    osMutexRelease(payload_ctrl_lock_id);
}

/**
 * @}
 * @}
 *
 */
