/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/** \file payload_cfg.c
 *
 * @brief Payload-specific configuration module used by the Payload Controller to manager the
 *           individual payloads.
 *
 * @copyright (C) Endurosat
 *            Contents and presentations are protected world-wide.
 *            Any kind of using, copying etc. is prohibited without prior permission.
 *            All rights - incl. industrial property rights - are reserved.
 */

#include "es_cdef.h"
#include "payload_ctrl.h"
#include "payload_cfg.h"
#include "payload_cfg_user.h"
#include "sxband_pl_ctrl.h"

static void payload_sxband_state_notify(const pl_instance_id_t instance_id, pl_state_t to_state);

static pl_op_status_t dummy_pl_init(const pl_instance_id_t instance_id,
                                      pl_config_t * const p_init_cfg,
                                      const p_pl_event_notify_t p_event_notify_cb);
static pl_op_status_t dummy_pl_deinit(const pl_instance_id_t instance_id);
static pl_op_status_t dummy_pl_start(const pl_instance_id_t instance_id, pl_config_t * const p_start_cfg);
static pl_op_status_t dummy_pl_stop(const pl_instance_id_t instance_id, const pl_op_stop_mode_t stop_mode);
static pl_state_t dummy_pl_get_active_state(const pl_instance_id_t instance_id);
static uint32_t dummy_pl_get_last_error(const pl_instance_id_t instance_id);

static pl_state_t dummy_payload_current_state = PL_STATE_NOT_INIT;

static void payload_sxband_state_notify(const pl_instance_id_t instance_id, pl_state_t to_state)
{
    payload_ctrl_event_notify(PAYLOAD_SX_BAND, to_state);
}

static const pl_control_if_t dummy_control_if =
{
     .init = dummy_pl_init,
     .deinit = dummy_pl_deinit,
     .start = dummy_pl_start,
     .stop = dummy_pl_stop,
     .get_state = dummy_pl_get_active_state,
     .get_last_error = dummy_pl_get_last_error,
};

const payload_immutable_cfg_t payload_cfg[PAYLOAD_COUNT] =
{
    // PAYLOAD_SX_BAND
    { .p_pl_interface = &sxband_pl_ctrl_if,
      .internal_inst_id = 0U,
      .init_config =
      {
          .p_config_data = NULL,
          .size = 0U
      },
      .p_pl_notif_cbk = &payload_sxband_state_notify
    },

    // PAYLOAD_DUMMY
    { .p_pl_interface = &dummy_control_if,
      .internal_inst_id = 0U,
      .init_config =
      {
          .p_config_data = NULL,
          .size = 0U
      },
      .p_pl_notif_cbk = NULL
    }
};

pl_op_status_t dummy_pl_init(const pl_instance_id_t instance_id,
                                      pl_config_t * const p_init_cfg,
                                      const p_pl_event_notify_t p_event_notify_cb)
{
    dummy_payload_current_state = PL_STATE_STOPPED;
    return PL_OP_STATUS_OK;
}

pl_op_status_t dummy_pl_deinit(const pl_instance_id_t instance_id)
{
    dummy_payload_current_state = PL_STATE_NOT_INIT;
    return PL_OP_STATUS_OK;
}

pl_op_status_t dummy_pl_start(const pl_instance_id_t instance_id, pl_config_t * const p_start_cfg)
{
    dummy_payload_current_state = PL_STATE_STARTED;
    return PL_OP_STATUS_OK;
}

pl_op_status_t dummy_pl_stop(const pl_instance_id_t instance_id, const pl_op_stop_mode_t stop_mode)
{
    dummy_payload_current_state = PL_STATE_STOPPED;
    return PL_OP_STATUS_OK;
}

pl_state_t dummy_pl_get_active_state(const pl_instance_id_t instance_id)
{
    return dummy_payload_current_state;
}

uint32_t dummy_pl_get_last_error(const pl_instance_id_t instance_id)
{
    return PL_OP_STATUS_OK;
}

