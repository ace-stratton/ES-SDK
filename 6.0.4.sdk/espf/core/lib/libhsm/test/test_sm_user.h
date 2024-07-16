#ifndef TEST_SM_USER_H
#define TEST_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum Test_SM_states
{
    STATE_ROOT,
    STATE_INITIAL,
    STATE_IDLE,
    STATE_COMPOSITE,
    STATE_COMPOSITE_SUB1,
    STATE_COMPOSITE_SUB2,
    STATE_DEEP_SUB3,
    STATE_DEEP_SUB4,
    STATE_COMPOSITE_SUB3,
    STATE___HISTORY_COMPOSITE,
    STATE_MAX
};

// User state machine events
enum Test_SM_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_Test_SM_start,
    ev_Test_SM_go_composite_history,
    ev_Test_SM_switch_to_idle,
    ev_Test_SM_go_sub2,
    ev_Test_SM_go_sub3,
    ev_Test_SM_trigger_regular_self_trans,
    ev_Test_SM_trigger_self_trans,
    ev_Test_SM_switch_to_initial,
    ev_Test_SM_go_to_initial,
    ev_Test_SM_go_to_sub2_direct,
    ev_Test_SM_go_to_sub1_direct,
    evMAX
};

// State machine root object
extern sCompositeState_t state_Test_SM;

// Use this macro to access the SM instance instead of a direct reference to
// state_Test_SM variable
#define Test_SM_instance  HSM_UPCAST_STATE(&state_Test_SM)

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TEST_SM_USER_H