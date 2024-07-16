#ifndef CUBEADCS_GEN2_SM_USER_H
#define CUBEADCS_GEN2_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum cubeadcs_gen2_sm_states
{
    STATE_ROOT,
    STATE_BACKOFF,
    STATE_EVENTMARKERACQUISITION,
    STATE_IDLE,
    STATE_CHECK,
    STATE_EVENTDOWNLOAD,
    STATE_STATECHANGE,
    STATE_FDIR,
    STATE_MAX
};

// User state machine events
enum cubeadcs_gen2_sm_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_cubeadcs_gen2_sm_event_marker_acquired,
    ev_cubeadcs_gen2_sm_request_a_state_change,
    ev_cubeadcs_gen2_sm_request_fdir,
    ev_cubeadcs_gen2_sm_check_completed,
    ev_cubeadcs_gen2_sm_event_download_completed,
    ev_cubeadcs_gen2_sm_state_change_completed,
    ev_cubeadcs_gen2_sm_fdir_completed,
    evMAX
};

// State machine root object
extern sCompositeState_t state_cubeadcs_gen2_sm;

// Use this macro to access the SM instance instead of a direct reference to
// state_cubeadcs_gen2_sm variable
#define cubeadcs_gen2_sm_instance  HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)

#ifdef __cplusplus
};
#endif

#endif  // #ifndef CUBEADCS_GEN2_SM_USER_H