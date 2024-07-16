#include "libhsm.h"
#include "cubeadcs_gen2_sm_config_user.h"

// USER_CODE_START::@main@
static cubeadcs_gen2_sm_ctx_t cubeadcs_gen2_sm_ctx = {0};

static bool cubeadcs_gen2_sm_is_time_expired(const unix_time_t time_mark, const unix_time_t time_s)
{
    return (datetime_to_unix_now() - time_mark) >= time_s;
}

// USER_CODE_END::@main@

// Entry/Exit functions

// GEN_OBJ_START::cubeadcs_gen2_sm_on_entry_Backoff
void cubeadcs_gen2_sm_on_entry_Backoff(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Backoff

    cubeadcs_gen2_sm_ctx.backoff_time_mark = datetime_to_unix_now();

    // USER_CODE_END::onEntry_Backoff
}
// GEN_OBJ_END::cubeadcs_gen2_sm_on_entry_Backoff



// GEN_OBJ_START::cubeadcs_gen2_sm_on_entry_Idle
void cubeadcs_gen2_sm_on_entry_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Idle

    unix_time_t time_cache = datetime_to_unix_now();

    cubeadcs_gen2_sm_ctx.check_time_mark = time_cache;
    cubeadcs_gen2_sm_ctx.event_dwn_time_mark = time_cache;

    // USER_CODE_END::onEntry_Idle
}
// GEN_OBJ_END::cubeadcs_gen2_sm_on_entry_Idle



// GEN_OBJ_START::cubeadcs_gen2_sm_on_entry_EventDownload
void cubeadcs_gen2_sm_on_entry_EventDownload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_EventDownload

    // USER_CODE_END::onEntry_EventDownload
}
// GEN_OBJ_END::cubeadcs_gen2_sm_on_entry_EventDownload


// GEN_OBJ_START::cubeadcs_gen2_sm_on_entry_StateChange
void cubeadcs_gen2_sm_on_entry_StateChange(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_StateChange

    cubeadcs_gen2_state_change_init();

    // USER_CODE_END::onEntry_StateChange
}
// GEN_OBJ_END::cubeadcs_gen2_sm_on_entry_StateChange

// GEN_OBJ_START::cubeadcs_gen2_sm_on_exit_StateChange
void cubeadcs_gen2_sm_on_exit_StateChange(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onExit_StateChange

    // Your implementation goes here...

	if ( ev_cubeadcs_gen2_sm_state_change_completed == pEvent->id )
	{
		cubeadcs_gen2_set_sys_state_change_status(CUBEADCS_GEN2_SYS_STATE_CHANGE_SUCCESS);
	}
	else if ( ev_cubeadcs_gen2_sm_request_fdir == pEvent->id )
	{
		cubeadcs_gen2_set_sys_state_change_status(CUBEADCS_GEN2_SYS_STATE_CHANGE_ERROR);
	}
	else
	{
		EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS_GEN2, EXEH_CUBEADCS_GEN2_INVALID_SYS_STATE_EXIT)
	}

    // USER_CODE_END::onExit_StateChange
}
// GEN_OBJ_END::cubeadcs_gen2_sm_on_exit_StateChange




// Guard condition functions
// GEN_OBJ_START::cubeadcs_gen2_sm_guard_is_adcs_ready
bool cubeadcs_gen2_sm_guard_is_adcs_ready(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_adcs_ready

    bool do_trans = false;
    if (false != cubeadcs_gen2_sm_is_time_expired(cubeadcs_gen2_sm_ctx.backoff_time_mark, CUBEADCS_GEN2_SM_BACKOFF_TIME_S))
    {
        do_trans = cubeadcs_gen2_init_adcs_cfg_cache();
    }

    return do_trans;

    // USER_CODE_END::guard_is_adcs_ready
}
// GEN_OBJ_END::cubeadcs_gen2_sm_guard_is_adcs_ready

// GEN_OBJ_START::cubeadcs_gen2_sm_guard_is_time_to_check_expired
bool cubeadcs_gen2_sm_guard_is_time_to_check_expired(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_time_to_check_expired

    return cubeadcs_gen2_sm_is_time_expired(cubeadcs_gen2_sm_ctx.check_time_mark, CUABEADCS_GEN2_SM_CHECK_TIME_S);

    // USER_CODE_END::guard_is_time_to_check_expired
}
// GEN_OBJ_END::cubeadcs_gen2_sm_guard_is_time_to_check_expired

// GEN_OBJ_START::cubeadcs_gen2_sm_guard_is_time_to_event_download_expired
bool cubeadcs_gen2_sm_guard_is_time_to_event_download_expired(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_time_to_event_download_expired

    return cubeadcs_gen2_sm_is_time_expired(cubeadcs_gen2_sm_ctx.event_dwn_time_mark, CUBEADCS_GEN2_SM_EVENT_DWN_TIME_S);

    // USER_CODE_END::guard_is_time_to_event_download_expired
}
// GEN_OBJ_END::cubeadcs_gen2_sm_guard_is_time_to_event_download_expired

// GEN_OBJ_START::cubeadcs_gen2_sm_guard_is_state_change_valid
bool cubeadcs_gen2_sm_guard_is_state_change_valid(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_state_change_valid
    bool is_state_change_valid = true;
    
    sm_event_t event = *((const sm_event_t *)pEvent);

    if ( (true != cubeadcs_gen2_is_sys_state_combo_valid(event.event_ctx.sys_state.sys_state_core_cfg.cntrl_mode, event.event_ctx.sys_state.sys_state_core_cfg.est_mode_main)) ||
         (true != cubeadcs_gen2_is_sys_state_combo_valid(event.event_ctx.sys_state.sys_state_core_cfg.cntrl_mode, event.event_ctx.sys_state.sys_state_core_cfg.est_mode_backup)))
    {
        is_state_change_valid = false;
       
        EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS_GEN2, EXEH_CUBEADCS_GEN2_INVALID_SYS_STATE)

        CUBEADCS_GEN2_TRACE_INFO("%s: INVALID STATE REQUEST\r", CUBEADCS_GEN2_DBG_HEAD);
    }
    else
    {
        if ( (true != cubeadcs_gen2_set_sys_state(&event.event_ctx.sys_state)) ||
        	 (true != cubeadcs_gen2_set_sys_state_change_status(CUBEADCS_GEN2_SYS_STATE_CHANGE_IN_PROGRESS)))
        {
            is_state_change_valid = false;
        }
    }

    return is_state_change_valid;

    // USER_CODE_END::guard_is_state_change_valid
}
// GEN_OBJ_END::cubeadcs_gen2_sm_guard_is_state_change_valid


// Action handlers
// GEN_OBJ_START::cubeadcs_gen2_sm_action_notify_users
void cubeadcs_gen2_sm_action_notify_users(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_notify_users

    // Your implementation goes here...

    // USER_CODE_END::action_notify_users
}
// GEN_OBJ_END::cubeadcs_gen2_sm_action_notify_users
