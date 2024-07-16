/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup es_sxband
 * @{
 *
 * @file     sxband_pl_ctrl.c
 * @brief    S/X Band payload controller interface implementation
 *
 * @}
 *
 */

#include "es_cdef.h"
#include "if_payload_control.h"
#include "payload_shared_types.h"
#include "trace.h"
#include "sxband_pl_ctrl.h"
#include "SdMngr.h"
#include "S_X_Band_Trnsm.h"
#include "eps_ctrl.h"
#include "eps_ctrl_cfg.h"

#if defined(SXBAND_SCHEDULER_ENABLED)
#include "sxband_sched.h"
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)

static pl_state_t sxband_state = PL_STATE_STOPPED;
static p_pl_event_notify_t p_sxband_state_notify = NULL;

static pl_op_status_t sxband_pl_ctrl_init(const pl_instance_id_t instance_id, pl_config_t * const p_init_cfg, const p_pl_event_notify_t p_event_notify_cb);
static pl_op_status_t sxband_pl_ctrl_deinit(const pl_instance_id_t instance_id);
static pl_op_status_t sxband_pl_ctrl_start(const pl_instance_id_t instance_id, pl_config_t * const p_start_cfg);
static pl_op_status_t sxband_pl_ctrl_stop(const pl_instance_id_t instance_id, const pl_op_stop_mode_t stop_mode);
static pl_state_t sxband_pl_ctrl_get_state(const pl_instance_id_t instance_id);
static uint32_t sxband_pl_ctrl_get_last_error(const pl_instance_id_t instance_id);
static void update_state_and_notify(const pl_instance_id_t instance_id, const pl_state_t new_state);
static bool is_valid_sxband_instance(const pl_instance_id_t instance_id);
#if defined(SXBAND_SCHEDULER_ENABLED)
static void on_sxband_notif(const sxband_sched_status_t status, const char * const p_summary_fname);
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)

static inline bool is_valid_sxband_instance(const pl_instance_id_t instance_id)
{
    return (0U == instance_id);
}

static void update_state_and_notify(const pl_instance_id_t instance_id, const pl_state_t new_state)
{
    sxband_state = new_state;

    if (p_sxband_state_notify != NULL)
    {
        (*p_sxband_state_notify)(instance_id, sxband_state);
    }
}

#if defined(SXBAND_SCHEDULER_ENABLED)
static void on_sxband_notif(const sxband_sched_status_t status, const char * const p_summary_fname)
{
    ES_TRACE_DEBUG("SXBand sched> finished with status: %d\r\n", status);

    if (NULL != p_summary_fname)
    {
        ES_TRACE_DEBUG("SXBand sched> summary file name: [%s]\r\n", p_summary_fname);
    }
}
#endif     // #if defined(SXBAND_SCHEDULER_ENABLED)

const pl_control_if_t sxband_pl_ctrl_if =
{
     .init = sxband_pl_ctrl_init,
     .deinit = sxband_pl_ctrl_deinit,
     .start = sxband_pl_ctrl_start,
     .stop = sxband_pl_ctrl_stop,
     .get_state = sxband_pl_ctrl_get_state,
     .get_last_error = sxband_pl_ctrl_get_last_error,
};

static pl_op_status_t sxband_pl_ctrl_init(const pl_instance_id_t instance_id, pl_config_t * const p_init_cfg, const p_pl_event_notify_t p_event_notify_cb)
{
    pl_op_status_t res = PL_OP_STATUS_REJECT;
    (void) p_init_cfg;

    if (is_valid_sxband_instance(instance_id))
    {
        p_sxband_state_notify = p_event_notify_cb;
        update_state_and_notify(instance_id, PL_STATE_STOPPED);
        res = PL_OP_STATUS_OK;
    }

    return res;
}

static pl_op_status_t sxband_pl_ctrl_deinit(const pl_instance_id_t instance_id)
{
    pl_op_status_t res = PL_OP_STATUS_REJECT;

    if (is_valid_sxband_instance(instance_id))
    {
        update_state_and_notify(instance_id, PL_STATE_NOT_INIT);

        p_sxband_state_notify = NULL;

        res = PL_OP_STATUS_OK;
    }

    return res;
}

static pl_op_status_t sxband_pl_ctrl_start(const pl_instance_id_t instance_id, pl_config_t * const p_start_cfg)
{
    pl_op_status_t res = PL_OP_STATUS_REJECT;

#if defined(SXBAND_SCHEDULER_ENABLED)
    if ((is_valid_sxband_instance(instance_id)) && (false == sxband_sched_is_file_seq_active()))
#else    // #if defined(SXBAND_SCHEDULER_ENABLED)
    if (is_valid_sxband_instance(instance_id))
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)
    {
        (void) eps_ctrl_set_channel_output(EPSCTRL_POWER_OUT_X_BAND_EN, true);

        update_state_and_notify(instance_id, PL_STATE_STARTED);

#if defined(SXBAND_SCHEDULER_ENABLED)
        const char *p_sched_file_name = NULL;

        // Note:
        // The scheduling args should contain a zero-terminated file name with SXBand commands to execute.
        // The file has to have been uploaded on the OBC SD card before starting the payload by the main scheduler.
        if (NULL != p_start_cfg)
        {
            p_sched_file_name = (char *) ((pl_args_t *)(p_start_cfg->p_config_data))->pl_args;
        }

        if ((NULL != p_sched_file_name) && ('\0' != p_sched_file_name[0U]))
        {
            sxband_sched_status_t seq_status = sxband_sched_start_file_seq(p_sched_file_name, strlen(p_sched_file_name) + 1, &on_sxband_notif);

            if (SXBAND_SCHED_STATUS_OK == seq_status)
            {
                res = PL_OP_STATUS_OK;
            }
        }
        else
        {
            // this is just a payload start without a schedule file
            res = PL_OP_STATUS_OK;
        }
#else    // #if defined(SXBAND_SCHEDULER_ENABLED)
        res = PL_OP_STATUS_OK;
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)
    }

    return res;
}

static pl_op_status_t sxband_pl_ctrl_stop(const pl_instance_id_t instance_id, const pl_op_stop_mode_t stop_mode)
{
    pl_op_status_t res = PL_OP_STATUS_REJECT;

    if (is_valid_sxband_instance(instance_id))
    {
        // stop the power regardless of the mode
        (void) stop_mode;

#if defined(SXBAND_SCHEDULER_ENABLED)
        sxband_sched_stop_file_seq();
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)

        sx_band_stop();
        (void) eps_ctrl_set_channel_output(EPSCTRL_POWER_OUT_X_BAND_EN, false);

        update_state_and_notify(instance_id, PL_STATE_STOPPED);

        res = PL_OP_STATUS_OK;
    }

    return res;
}

static pl_state_t sxband_pl_ctrl_get_state(const pl_instance_id_t instance_id)
{
    pl_state_t res = PL_STATE_NOT_INIT;

    if (is_valid_sxband_instance(instance_id))
    {
        res = sxband_state;
    }

    return res;
}

static uint32_t sxband_pl_ctrl_get_last_error(const pl_instance_id_t instance_id)
{
    // TODO: Try to obtain last error status from S_X_Band driver
    return is_valid_sxband_instance(instance_id) ? PL_OP_STATUS_OK : PL_OP_STATUS_REJECT;
}
