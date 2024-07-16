#ifndef CONOPS_SM_USER_H
#define CONOPS_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum conops_sm_states
{
    STATE_ROOT,
    STATE_SAFE,
    STATE_IDLE,
    STATE_DETUMBLING,
    STATE_PAYLOAD,
    STATE_MAX
};

// User state machine events
enum conops_sm_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_conops_sm_idle_flag_set,
    ev_conops_sm_payload_flag_set,
    ev_conops_sm_payload_flag_cleared,
    evMAX
};

// State machine root object
extern sCompositeState_t state_conops_sm;

// Use this macro to access the SM instance instead of a direct reference to
// state_conops_sm variable
#define conops_sm_instance  HSM_UPCAST_STATE(&state_conops_sm)

#ifdef __cplusplus
};
#endif

#endif  // #ifndef CONOPS_SM_USER_H