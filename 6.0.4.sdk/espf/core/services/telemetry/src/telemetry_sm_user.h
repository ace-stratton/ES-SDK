/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TELEMETRY_SM_USER_H
#define TELEMETRY_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum telemetry_sm_states
{
    STATE_ROOT,
    STATE_NOT_INIT,
    STATE_INIT,
    STATE_STARTED,
    STATE_STOPPED,
    STATE_MAX
};

// User state machine events
enum telemetry_sm_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_telemetry_sm_init,
    ev_telemetry_sm_start,
    ev_telemetry_sm_stop,
    evMAX
};

// State machine root object
extern sCompositeState_t state_telemetry_sm;

// Use this macro to access the SM instance instead of a direct reference to
// state_telemetry_sm variable
#define telemetry_sm_instance  HSM_UPCAST_STATE(&state_telemetry_sm)

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TELEMETRY_SM_USER_H