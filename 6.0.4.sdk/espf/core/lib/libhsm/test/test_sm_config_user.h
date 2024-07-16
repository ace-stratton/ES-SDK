#ifndef TEST_SM_CONFIG_USER_H
#define TEST_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// USER_CODE_START::@main@
// Any code placed between these two tags will be preserved during code generation!
// USER_CODE_END::@main@

// Entry/Exit functions
void Test_SM_on_entry_Initial(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Initial(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_entry_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Idle(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_entry_Composite(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Composite(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_entry_Composite_Sub1(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Composite_Sub1(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_entry_Composite_Sub2(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Composite_Sub2(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_entry_Deep_Sub3(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Deep_Sub3(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_entry_Deep_Sub4(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Deep_Sub4(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_entry_Composite_Sub3(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_on_exit_Composite_Sub3(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

// Guard condition functions
bool Test_SM_guard_start_conditions_met(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool Test_SM_guard_initial_cond_met(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool Test_SM_guard_entry_to_sub2_allowed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);

// Action handlers
void Test_SM_action_on_start_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_action_on_regular_self_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_action_on_self_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_action_on_initial_switch_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void Test_SM_action_composite_sub2_action(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TEST_SM_CONFIG_USER_H