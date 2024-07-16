#ifndef PAYLOAD_CTRL_SM_USER_H
#define PAYLOAD_CTRL_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum payload_ctrl_sm_states
{
    STATE_ROOT,
    STATE_POINTING_IDLE,
    STATE_POINTING_INPROGRESS,
    STATE_POINTING_FINISHED,
    STATE_MAX
};

// User state machine events
enum payload_ctrl_sm_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_payload_ctrl_sm_requesting_payload_off,
    evMAX
};

// State machine root object
extern sCompositeState_t state_payload_ctrl_sm;

// Use this macro to access the SM instance instead of a direct reference to
// state_payload_ctrl_sm variable
#define payload_ctrl_sm_instance  HSM_UPCAST_STATE(&state_payload_ctrl_sm)

#ifdef __cplusplus
};
#endif

#endif  // #ifndef PAYLOAD_CTRL_SM_USER_H