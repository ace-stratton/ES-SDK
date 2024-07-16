/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef BEACONS_SM_USER_H
#define BEACONS_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum beacons_sm_states
{
    STATE_ROOT,
    STATE_NOT_INIT,
    STATE_INIT,
    STATE_STARTED,
    STATE_BEACON_WAIT_TIME,
    STATE_BEACON_TRANSMISSION,
    STATE_STOPPED,
    STATE_MAX
};

// User state machine events
enum beacons_sm_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_beacons_sm_init,
    ev_beacons_sm_start,
    ev_beacons_sm_stop,
    evMAX
};

// State machine root object
extern sCompositeState_t state_beacons_sm;

// Use this macro to access the SM instance instead of a direct reference to
// state_beacons_sm variable
#define beacons_sm_instance  HSM_UPCAST_STATE(&state_beacons_sm)

#ifdef __cplusplus
};
#endif
#endif  // #ifndef BEACONS_SM_USER_H
