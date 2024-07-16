/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TELEMETRY_FILE_SINK_SM_USER_H
#define TELEMETRY_FILE_SINK_SM_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// Stated identifiers
enum telemetry_file_sink_sm_states
{
    STATE_ROOT,
    STATE_NOT_INIT,
    STATE_INIT,
    STATE_WAIT_STORAGE,
    STATE_STARTED,
    STATE_STOPPED,
    STATE_MAX
};

// User state machine events
enum telemetry_file_sink_sm_events
{
    evStart = eHSM_StdEvent_UserEvStart,
    ev_telemetry_file_sink_sm_init,
    ev_telemetry_file_sink_sm_start,
    ev_telemetry_file_sink_sm_stop,
    ev_telemetry_file_sink_sm_restart,
    evMAX
};

// State machine root object
extern sCompositeState_t state_telemetry_file_sink_sm;

// Use this macro to access the SM instance instead of a direct reference to
// state_telemetry_file_sink_sm variable
#define telemetry_file_sink_sm_instance  HSM_UPCAST_STATE(&state_telemetry_file_sink_sm)

#ifdef __cplusplus
};
#endif

#endif  // #ifndef TELEMETRY_FILE_SINK_SM_USER_H