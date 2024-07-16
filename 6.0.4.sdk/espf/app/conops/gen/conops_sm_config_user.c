#include "libhsm.h"
#include "conops_sm_config_user.h"

// USER_CODE_START::@main@
#include "conops.h"
#include "conops_payload.h"
#include "config/payload_ctrl/payload_cfg_user.h"
#include "cubeadcs.h"
#include "aocs_cntrl.h"

#include <string.h>

// USER_CODE_END::@main@

// Entry/Exit functions

// GEN_OBJ_START::conops_sm_on_entry_Safe
void conops_sm_on_entry_Safe(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Safe

	// Clear all internal flags
	for (uint8_t u8Err = 0; u8Err < eFLAG_MAX; u8Err++)
	{
		conops_set_logical_flag_value(u8Err, false);
	}

	// Emergency stop to all payloads
	for ( uint8_t u8Indx = 0; u8Indx < PAYLOAD_COUNT; u8Indx++)
	{
		conops_payload_stop(u8Indx, true);
	}

    // USER_CODE_END::onEntry_Safe
}
// GEN_OBJ_END::conops_sm_on_entry_Safe

// GEN_OBJ_START::conops_sm_on_exit_Safe
void conops_sm_on_exit_Safe(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onExit_Safe

    // Your implementation goes here...

    // USER_CODE_END::onExit_Safe
}
// GEN_OBJ_END::conops_sm_on_exit_Safe


// GEN_OBJ_START::conops_sm_on_entry_Idle
void conops_sm_on_entry_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Idle

    // Your implementation goes here...

    // USER_CODE_END::onEntry_Idle
}
// GEN_OBJ_END::conops_sm_on_entry_Idle

// GEN_OBJ_START::conops_sm_on_exit_Idle
void conops_sm_on_exit_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onExit_Idle

    // Change ADCS control mode
    if ( (conops_is_3axis_allowed()) && (!conops_is_error_flag_raised()) )
    {
        if ( true == conops_get_enable_sun_tracking_flag() )
        {
            conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_SUN_TRACKING, NULL);
        }
        else
        {
            conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_Y_MOMENTUM, NULL);
        }
    }
    else
    {
        conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING, NULL);
    }

    // USER_CODE_END::onExit_Idle
}
// GEN_OBJ_END::conops_sm_on_exit_Idle


// GEN_OBJ_START::conops_sm_on_entry_Detumbling
void conops_sm_on_entry_Detumbling(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Detumbling

	aocs_cntrl_sys_state_types_t aocs_state;
	aocs_cntrl_sys_state_req_state_t aocs_state_req_state;

	if ( (conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state)) &&
	     (AOCS_CNTRL_SYS_STATE_NO_CONTROL == aocs_state) &&
	     (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == aocs_state_req_state) )
	{
		conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING, NULL);
	}

    // USER_CODE_END::onEntry_Detumbling
}
// GEN_OBJ_END::conops_sm_on_entry_Detumbling

// GEN_OBJ_START::conops_sm_on_exit_Detumbling
void conops_sm_on_exit_Detumbling(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onExit_Detumbling
    aocs_cntrl_sys_state_types_t aocs_state;
    aocs_cntrl_sys_state_req_state_t aocs_state_req_state;
    if ( (conops_get_logical_flag(eFLAG_DETUMB_COMPLETED)) &&
         (conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state)) )
    {
        if ( (AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING == aocs_state ) || (AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING == aocs_state) )
        {
            aocs_cms_status_t eCmsStatus;
            if ( aocs_cntrl_get_cms_status(&eCmsStatus) && (CMS_COMPLETE == eCmsStatus) )
            {
                conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE, NULL);
            }
            else
            {
                conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_NO_CONTROL, NULL);
            }
        }
        else
        {
            conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_Y_THOMSON, NULL);
        }
    }
    else
    {
        conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_NO_CONTROL, NULL);
    }

    // USER_CODE_END::onExit_Detumbling
}
// GEN_OBJ_END::conops_sm_on_exit_Detumbling


// GEN_OBJ_START::conops_sm_on_entry_Payload
void conops_sm_on_entry_Payload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Payload

	const sConOps_event_t sEv = *((const sConOps_event_t * const)pEvent);

	payload_ctrl_start_cfg_t sPayStartCfg;

	memcpy(&sPayStartCfg.payload_args, &sEv.event_data.payload_args, sizeof(pl_args_t));
	memcpy(&sPayStartCfg.pointing_cfg, &sEv.event_data.pointing_cfg, sizeof(record_adcs_t));

	(void) payload_ctrl_start(sEv.event_data.payload_id, &sPayStartCfg);

    // USER_CODE_END::onEntry_Payload
}
// GEN_OBJ_END::conops_sm_on_entry_Payload

// GEN_OBJ_START::conops_sm_on_exit_Payload
void conops_sm_on_exit_Payload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onExit_Payload

	const sConOps_event_t sEv = *((const sConOps_event_t * const)pEvent);

	conops_payload_stop((uint8_t)sEv.event_data.payload_id, false);

	if ( conops_is_3axis_allowed() )
	{
	    TODO(Maybe there should be an additional check for !conops_is_error_flag_raised())
		if ( conops_get_enable_sun_tracking_flag() )
		{
			conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_SUN_TRACKING, NULL);
		}
		else
		{
			conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_Y_MOMENTUM, NULL);
		}
	}
	else
	{
		conops_set_aocs_sys_state(AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING, NULL);
	}

    // USER_CODE_END::onExit_Payload
}
// GEN_OBJ_END::conops_sm_on_exit_Payload



// Guard condition functions
// GEN_OBJ_START::conops_sm_guard_Safe_periodic_Detumbling
bool conops_sm_guard_Safe_periodic_Detumbling(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_Safe_periodic_Detumbling

	CONOPS_TRACE_DBG("%s: SAFE [periodic] -> DETUMB: Enter\r", CONOPS_SM_GUARD_DBG);
    bool bRes = false;

    aocs_cntrl_sys_state_types_t aocs_state;
    aocs_cntrl_sys_state_req_state_t aocs_state_req_state;
    aocs_cms_status_t eCmsStatus;

    if ( (conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state)) &&
         (aocs_state != AOCS_CNTRL_SYS_STATE_UNDEFINED) &&
         (aocs_state_req_state == AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED) &&
         aocs_cntrl_get_cms_status(&eCmsStatus) )
    {


    	if ( conops_is_cbatt_above(CONOPS_THRESHOLDVALUETYPES_S_DET, PAYLOAD_COUNT) )
    	{
    		if ( ( conops_is_omega_above_thresh(aocs_state) )  &&
    				( CMS_COMPLETE == eCmsStatus ) )
    		{
    			bRes = true;
    		}
    		else
    		{
    			bRes = false;
    		}
    	}

    	if ( (AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING == aocs_state) &&
    			(CMS_COMPLETE == eCmsStatus) )
    	{
    		bRes = true;
    	}

    	if ( conops_is_fast_detumb_activated() )
    	{
    		bRes = true;
    	}

    	CONOPS_TRACE_DBG("%s: SAFE [periodic] -> DETUMB: %d : Exit\r", CONOPS_SM_GUARD_DBG, bRes);
    }
    else
    {
    	bRes = false;
    }
    return bRes;

    // USER_CODE_END::guard_Safe_periodic_Detumbling
}
// GEN_OBJ_END::conops_sm_guard_Safe_periodic_Detumbling

// GEN_OBJ_START::conops_sm_guard_Safe_idle_flag_set_Idle
bool conops_sm_guard_Safe_idle_flag_set_Idle(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_Safe_idle_flag_set_Idle

	CONOPS_TRACE_DBG("%s: SAFE [flag] -> IDLE: Enter\r", CONOPS_SM_GUARD_DBG);

	bool bRes;

	aocs_cntrl_sys_state_types_t aocs_state;
	aocs_cntrl_sys_state_req_state_t aocs_state_req_state;

	bRes = conops_is_cbatt_above(CONOPS_THRESHOLDVALUETYPES_S_SAFE, PAYLOAD_COUNT) &&
	       conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state) &&
	       (AOCS_CNTRL_SYS_STATE_UNDEFINED != aocs_state) &&
	       (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == aocs_state_req_state);

	if ( bRes == true )
	{
		if ( (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == aocs_state_req_state) &&
		     (AOCS_CNTRL_SYS_STATE_SUN_TRACKING != aocs_state) )
		{
			if ( (AOCS_CNTRL_SYS_STATE_Y_MOMENTUM == aocs_state) ||
				 (AOCS_CNTRL_SYS_STATE_Y_MOMENTUM_FULL_STATE_EKF == aocs_state)	||
				 (AOCS_CNTRL_SYS_STATE_3AXIS == aocs_state) )
			{
				bRes = true;
			}
			else
			{
				bRes = false;
			}
		}
	}

	CONOPS_TRACE_DBG("%s: SAFE [flag] -> IDLE: %d : Exit\r", CONOPS_SM_GUARD_DBG, bRes);

	return bRes;

    // USER_CODE_END::guard_Safe_idle_flag_set_Idle
}
// GEN_OBJ_END::conops_sm_guard_Safe_idle_flag_set_Idle

// GEN_OBJ_START::conops_sm_guard_Idle_periodic_Safe
bool conops_sm_guard_Idle_periodic_Safe(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_Idle_periodic_Safe

	CONOPS_TRACE_DBG("%s: IDLE [periodic] -> SAFE: Enter\r", CONOPS_SM_GUARD_DBG);

	bool bRes;
	aocs_cntrl_sys_state_types_t aocs_state;
	aocs_cntrl_sys_state_req_state_t aocs_state_req_state;

	bRes = false;
	if ( (conops_is_cbatt_below(CONOPS_THRESHOLDVALUETYPES_DEFAULT, PAYLOAD_COUNT)) ||
	     (conops_is_error_flag_raised()) )
	{
		bRes = true;
	}

	if ((conops_get_aocs_sys_state(&aocs_state, &aocs_state_req_state)) &&
	    (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == aocs_state_req_state) &&
        (AOCS_CNTRL_SYS_STATE_SUN_TRACKING != aocs_state) &&
		(AOCS_CNTRL_SYS_STATE_Y_MOMENTUM != aocs_state) &&
		(AOCS_CNTRL_SYS_STATE_Y_MOMENTUM_FULL_STATE_EKF != aocs_state) &&
		(AOCS_CNTRL_SYS_STATE_3AXIS != aocs_state) )
	{
			bRes = true;
	}

	CONOPS_TRACE_DBG("%s: IDLE [periodic] -> SAFE: %d : Exit\r", CONOPS_SM_GUARD_DBG, bRes);

	return bRes;

    // USER_CODE_END::guard_Idle_periodic_Safe
}
// GEN_OBJ_END::conops_sm_guard_Idle_periodic_Safe

// GEN_OBJ_START::conops_sm_guard_Idle_payload_flag_set_Payload
bool conops_sm_guard_Idle_payload_flag_set_Payload(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_Idle_payload_flag_set_Payload

	CONOPS_TRACE_DBG("%s: IDLE [flag] -> PAY: Enter\r", CONOPS_SM_GUARD_DBG);

	bool bRes;

	const sConOps_event_t sEv = *((const sConOps_event_t * const)pEvent);

	bRes = conops_is_cbatt_above(CONOPS_THRESHOLDVALUETYPES_S_PAY, (uint8_t)sEv.event_data.payload_id);

	CONOPS_TRACE_DBG("%s: IDLE [flag] -> PAY: %d : Exit\r", CONOPS_SM_GUARD_DBG, bRes);

	return bRes;

    // USER_CODE_END::guard_Idle_payload_flag_set_Payload
}
// GEN_OBJ_END::conops_sm_guard_Idle_payload_flag_set_Payload

// GEN_OBJ_START::conops_sm_guard_Detumbling_periodic_Safe
bool conops_sm_guard_Detumbling_periodic_Safe(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_Detumbling_periodic_Safe

	CONOPS_TRACE_DBG("%s: DETUMB [periodic] -> SAFE: Enter\r", CONOPS_SM_GUARD_DBG);

	bool bRes;

	bRes = false;

	if ( (conops_is_cbatt_below(CONOPS_THRESHOLDVALUETYPES_DEFAULT, PAYLOAD_COUNT)) ||
		 (conops_is_error_flag_raised()) ||
		 (conops_is_detumb_completed())				 )
	{
		bRes = true;
	}

	CONOPS_TRACE_DBG("%s: DETUMB [periodic] -> SAFE: %d : Exit\r", CONOPS_SM_GUARD_DBG, bRes);

    return bRes;

    // USER_CODE_END::guard_Detumbling_periodic_Safe
}
// GEN_OBJ_END::conops_sm_guard_Detumbling_periodic_Safe

// GEN_OBJ_START::conops_sm_guard_Payload_periodic_Safe
bool conops_sm_guard_Payload_periodic_Safe(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_Payload_periodic_Safe

	CONOPS_TRACE_DBG("%s: PAY -> SAFE: Enter\r", CONOPS_SM_GUARD_DBG);

	bool bRes = false;

	if ( (conops_is_cbatt_below(CONOPS_THRESHOLDVALUETYPES_DEFAULT, PAYLOAD_COUNT)) ||
	     (conops_is_error_flag_raised()) )
	{
		bRes = true;
	}

	CONOPS_TRACE_DBG("%s: PAY -> SAFE: %d : Exit\r", CONOPS_SM_GUARD_DBG, bRes);

	return bRes;

    // USER_CODE_END::guard_Payload_periodic_Safe
}
// GEN_OBJ_END::conops_sm_guard_Payload_periodic_Safe


// Action handlers
// GEN_OBJ_START::conops_sm_action_detumb_action
void conops_sm_action_detumb_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_detumb_action



    // USER_CODE_END::action_detumb_action
}
// GEN_OBJ_END::conops_sm_action_detumb_action

// GEN_OBJ_START::conops_sm_action_idle_action
void conops_sm_action_idle_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_idle_action

    // Your implementation goes here...

    // USER_CODE_END::action_idle_action
}
// GEN_OBJ_END::conops_sm_action_idle_action

// GEN_OBJ_START::conops_sm_action_safe_action
void conops_sm_action_safe_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_safe_action



    // USER_CODE_END::action_safe_action
}
// GEN_OBJ_END::conops_sm_action_safe_action
