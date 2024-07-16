#ifndef CONOPS_SM_CONFIG_USER_H
#define CONOPS_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
// USER_CODE_END::@main@

// Entry/Exit functions
void conops_sm_on_entry_Safe(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_on_exit_Safe(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_on_entry_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_on_exit_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_on_entry_Detumbling(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_on_exit_Detumbling(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_on_entry_Payload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_on_exit_Payload(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

// Guard condition functions
bool conops_sm_guard_Safe_periodic_Detumbling(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool conops_sm_guard_Safe_idle_flag_set_Idle(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool conops_sm_guard_Idle_periodic_Safe(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool conops_sm_guard_Idle_payload_flag_set_Payload(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool conops_sm_guard_Detumbling_periodic_Safe(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool conops_sm_guard_Payload_periodic_Safe(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);

// Action handlers
void conops_sm_action_detumb_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_action_idle_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void conops_sm_action_safe_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef CONOPS_SM_CONFIG_USER_H