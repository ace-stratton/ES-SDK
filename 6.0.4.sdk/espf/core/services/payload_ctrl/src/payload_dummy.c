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
 * @file payload_dummy.c
 *
 * @brief Dummy payload interface implementation
 * @}
 *
 */

#include "es_cdef.h"
#include "if_payload_control.h"

p_pl_event_notify_t p_event_cbk = (p_pl_event_notify_t) NULL;
static pl_state_t current_state = PL_STATE_NOT_INIT;

static inline void fire_event(const pl_instance_id_t instance_id, pl_state_t to_state)
{
    if (NULL != p_event_cbk)
    {
        p_event_cbk(instance_id, to_state);
    }
}

static pl_op_status_t payload_dummy_init(const pl_instance_id_t instance_id,
                                      pl_config_t * const p_init_cfg,
                                      const p_pl_event_notify_t p_event_notify_cb)
{
	current_state = PL_STATE_STOPPED;
	(void) instance_id;
	(void) p_init_cfg;
	p_event_cbk = p_event_notify_cb;

	fire_event(instance_id, current_state);

	return PL_OP_STATUS_OK;
}

static pl_op_status_t payload_dummy_deinit(const pl_instance_id_t instance_id)
{
	current_state = PL_STATE_NOT_INIT;

	fire_event(instance_id, current_state);

	return PL_OP_STATUS_OK;
}

static pl_op_status_t payload_dummy_start(const pl_instance_id_t instance_id, pl_config_t * const p_start_cfg)
{
	current_state = PL_STATE_STARTED;

	fire_event(instance_id, current_state);

	return PL_OP_STATUS_OK;
}

static pl_op_status_t payload_dummy_stop(const pl_instance_id_t instance_id, const pl_op_stop_mode_t stop_mode)
{
	current_state = PL_STATE_STOPPED;

	fire_event(instance_id, current_state);

	return PL_OP_STATUS_OK;
}

static pl_state_t payload_dummy_get_active_state(const pl_instance_id_t instance_id)
{
	return current_state;
}

static uint32_t payload_dummy_get_last_error(const pl_instance_id_t instance_id)
{
	return 0;
}

const pl_control_if_t payload_dummy_if =
{
	.init = payload_dummy_init,
	.deinit = payload_dummy_deinit,
	.start = payload_dummy_start,
	.stop = payload_dummy_stop,
	.get_state = payload_dummy_get_active_state,
	.get_last_error = payload_dummy_get_last_error,
};
