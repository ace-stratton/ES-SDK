#include "libhsm.h"
#include "payload_ctrl_sm_config_user.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!

#include "payload_ctrl_sm_types.h"

#include "cubeadcs.h"
#include "conops_cfg.h"
#include "assertions.h"
#include "aocs_cntrl.h"
#include "aocs_cntrl_feedback.h"
#include "if_sys_mod.h"

struct
{
	timer_handle_t adcs_timer;
} pl_ctrl_sm_runtime;
// USER_CODE_END::@main@

// Entry/Exit functions

// GEN_OBJ_START::payload_ctrl_sm_on_entry_Pointing_Idle
void payload_ctrl_sm_on_entry_Pointing_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Pointing_Idle

	pl_ctrl_runtime_context.point_target_pl_id = PAYLOAD_COUNT;
	pl_ctrl_runtime_context.point_mode_timeout_ms = 0U;

    // USER_CODE_END::onEntry_Pointing_Idle
}
// GEN_OBJ_END::payload_ctrl_sm_on_entry_Pointing_Idle





// Guard condition functions
// GEN_OBJ_START::payload_ctrl_sm_guard_Pointing_Idle_periodic_Pointing_InProgress
bool payload_ctrl_sm_guard_Pointing_Idle_periodic_Pointing_InProgress(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_Pointing_Idle_periodic_Pointing_InProgress

	bool res = false;

    for (uint8_t pl_id = 0; pl_id < PAYLOAD_COUNT; pl_id++)
    {
    	if (pl_ctrl_runtime_context.state_mon_data[pl_id].pending_flags & PENDING_FLAG_START)
    	{
    		pl_ctrl_runtime_context.point_target_pl_id = pl_id;

    		res = true;
    		break;
    	}
    }

    return res;

    // USER_CODE_END::guard_Pointing_Idle_periodic_Pointing_InProgress
}
// GEN_OBJ_END::payload_ctrl_sm_guard_Pointing_Idle_periodic_Pointing_InProgress

// GEN_OBJ_START::payload_ctrl_sm_guard_is_point_mode_ready
bool payload_ctrl_sm_guard_is_point_mode_ready(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_point_mode_ready
	volatile adcs_cntrl_result_t adcs_res = aocs_cntrl_get_status();
	CONOPS_TRACE_DBG("%s: ----- POINT_MODE_READY_FEEDBACK(=0?): %d\r",CONOPS_AOCS_MODE_CHANGE, adcs_res);
	return (ADCS_CNTRL_RESULT_SUCCESS == adcs_res);

    // USER_CODE_END::guard_is_point_mode_ready
}
// GEN_OBJ_END::payload_ctrl_sm_guard_is_point_mode_ready

// GEN_OBJ_START::payload_ctrl_sm_guard_is_point_mode_failed
bool payload_ctrl_sm_guard_is_point_mode_failed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_point_mode_failed
	volatile adcs_cntrl_result_t adcs_res = aocs_cntrl_get_status();
	CONOPS_TRACE_DBG("%s: ----- POINT_MODE_FAIL__FEEDBACK(=2?): %d\r",CONOPS_AOCS_MODE_CHANGE, adcs_res);
	payload_ctrl_payload_t pl_id = pl_ctrl_runtime_context.point_target_pl_id;

	pl_ctrl_runtime_context.state_mon_data[pl_id].last_reported_state = PL_STATE_NOT_INIT;

	if (ADCS_CNTRL_RESULT_FAILED == adcs_res)
	{
		pl_ctrl_runtime_context.state_mon_data[pl_id].last_reported_state = PL_STATE_ADCS_ERROR;
	}
	else
	{
		if (timer_is_elapsed(&pl_ctrl_sm_runtime.adcs_timer, pl_ctrl_runtime_context.point_mode_timeout_ms))
		{
			pl_ctrl_runtime_context.state_mon_data[pl_id].last_reported_state = PL_STATE_ADCS_TIMEOUT;
		}
	}

	return (PL_STATE_NOT_INIT != pl_ctrl_runtime_context.state_mon_data[pl_id].last_reported_state);
    // USER_CODE_END::guard_is_point_mode_failed
}
// GEN_OBJ_END::payload_ctrl_sm_guard_is_point_mode_failed


// Action handlers
// GEN_OBJ_START::payload_ctrl_sm_action_prepare_pointing_mode
void payload_ctrl_sm_action_prepare_pointing_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_prepare_pointing_mode
    const record_adcs_t * start_cfg_adcs =
            &pl_ctrl_runtime_context.state_mon_data[pl_ctrl_runtime_context.point_target_pl_id].start_cfg.pointing_cfg;

    aocs_cntrl_reference_params_t aocs_ref =
    {
        .ref_param_1 = start_cfg_adcs->geo_coord.fGeoLon,  // Lon OR Roll
        .ref_param_2 = start_cfg_adcs->geo_coord.fGeoLat,  // Lat OR Pitch
        .ref_param_3 = start_cfg_adcs->geo_coord.fGeoAlt   // Alt OR Yaw
    };

    // trigger CubeADCS pointing...
    TODO(Status of the AOCS state request should be taken into account)
    (void)aocs_cntrl_request_aocs_state((const aocs_cntrl_sys_state_types_t)start_cfg_adcs->cntrl_mode,
                                   &aocs_ref);

	// convert time to milliseconds because it comes from the payload scheduler in seconds
	pl_ctrl_runtime_context.point_mode_timeout_ms = 1000U *
			(uint32_t) pl_ctrl_runtime_context.state_mon_data[pl_ctrl_runtime_context.point_target_pl_id].
			start_cfg.pointing_cfg.adcs_prep_time;

	timer_start(&pl_ctrl_sm_runtime.adcs_timer);
	CONOPS_TRACE_DBG("%s: ----- PREP_TIME: %5d\r", CONOPS_AOCS_MODE_CHANGE, pl_ctrl_runtime_context.point_mode_timeout_ms);

    // USER_CODE_END::action_prepare_pointing_mode
}
// GEN_OBJ_END::payload_ctrl_sm_action_prepare_pointing_mode

// GEN_OBJ_START::payload_ctrl_sm_action_start_payload
void payload_ctrl_sm_action_start_payload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_start_payload

	timer_stop(&pl_ctrl_sm_runtime.adcs_timer);

	CRIT_ASSERT(PAYLOAD_COUNT != pl_ctrl_runtime_context.point_target_pl_id);

	// variable created for brevity
	payload_ctrl_payload_t pl_id = pl_ctrl_runtime_context.point_target_pl_id;

	const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(pl_id);

	CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
	CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->start);

	pl_config_t start_cfg = {
		.p_config_data = &pl_ctrl_runtime_context.state_mon_data[pl_id].start_cfg.payload_args,
		.size = sizeof(pl_ctrl_runtime_context.state_mon_data[pl_id].start_cfg.payload_args)
	};

	pl_ctrl_runtime_context.state_mon_data[pl_id].pending_flags &= (uint8_t) (~PENDING_FLAG_START);

	(void) p_pl_cfg->p_pl_interface->start(p_pl_cfg->internal_inst_id,
										   &start_cfg);
    // USER_CODE_END::action_start_payload
}
// GEN_OBJ_END::payload_ctrl_sm_action_start_payload

// GEN_OBJ_START::payload_ctrl_sm_action_notify_adcs_timeout
void payload_ctrl_sm_action_notify_adcs_timeout(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_notify_adcs_timeout
	payload_ctrl_payload_t pl_id = pl_ctrl_runtime_context.point_target_pl_id;

	timer_stop(&pl_ctrl_sm_runtime.adcs_timer);
	pl_ctrl_runtime_context.state_mon_data[pl_id].pending_flags &= (uint8_t) (~PENDING_FLAG_START);
	// last_reported_state is used here because it has already been set in the is_point_mode_failed() guard;
	// if the payload should set it later, it will just overwrite the current value which will only be used
	// as a temporary storage for the ADCS status notification in case of error or timeout
	payload_ctrl_event_notify(pl_id, pl_ctrl_runtime_context.state_mon_data[pl_id].last_reported_state);
    // USER_CODE_END::action_notify_adcs_timeout
}
// GEN_OBJ_END::payload_ctrl_sm_action_notify_adcs_timeout

// GEN_OBJ_START::payload_ctrl_sm_action_serve_additional_payloads
void payload_ctrl_sm_action_serve_additional_payloads(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_serve_additional_payloads

    for (uint8_t pl_id = 0; pl_id < PAYLOAD_COUNT; pl_id++)
    {
    	if (pl_ctrl_runtime_context.state_mon_data[pl_id].pending_flags & PENDING_FLAG_START)
    	{
    		// if pointing mode is compatible to the currently active one, activate the payload, otherwise ignore
    		if (pl_ctrl_runtime_context.state_mon_data[pl_id].start_cfg.pointing_cfg.cntrl_mode ==
    				pl_ctrl_runtime_context.state_mon_data[pl_ctrl_runtime_context.point_target_pl_id].start_cfg.pointing_cfg.cntrl_mode)
    		{
				const payload_immutable_cfg_t *p_pl_cfg = payload_cfg_get(pl_id);

				CRIT_ASSERT((const payload_immutable_cfg_t *) NULL != p_pl_cfg);
				CRIT_ASSERT(NULL != p_pl_cfg->p_pl_interface->start);

				pl_config_t start_cfg = {
					.p_config_data = &pl_ctrl_runtime_context.state_mon_data[pl_id].start_cfg.payload_args,
					.size = sizeof(pl_ctrl_runtime_context.state_mon_data[pl_id].start_cfg.payload_args)
				};

				pl_ctrl_runtime_context.state_mon_data[pl_id].pending_flags &= (uint8_t) (~PENDING_FLAG_START);

				(void) p_pl_cfg->p_pl_interface->start(p_pl_cfg->internal_inst_id,
													   &start_cfg);

				break;
    		}
    		else
    		{
    			pl_ctrl_runtime_context.state_mon_data[pl_id].pending_flags &= (uint8_t) (~PENDING_FLAG_START);
    		}
    	}
    }

    // USER_CODE_END::action_serve_additional_payloads
}
// GEN_OBJ_END::payload_ctrl_sm_action_serve_additional_payloads
