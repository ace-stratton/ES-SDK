#ifndef PAYLOAD_CTRL_SM_CONFIG_USER_H
#define PAYLOAD_CTRL_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
// USER_CODE_END::@main@

// Entry/Exit functions
void payload_ctrl_sm_on_entry_Pointing_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

// Guard condition functions
bool payload_ctrl_sm_guard_Pointing_Idle_periodic_Pointing_InProgress(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool payload_ctrl_sm_guard_is_point_mode_ready(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool payload_ctrl_sm_guard_is_point_mode_failed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);

// Action handlers
void payload_ctrl_sm_action_prepare_pointing_mode(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void payload_ctrl_sm_action_start_payload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void payload_ctrl_sm_action_notify_adcs_timeout(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void payload_ctrl_sm_action_serve_additional_payloads(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef PAYLOAD_CTRL_SM_CONFIG_USER_H