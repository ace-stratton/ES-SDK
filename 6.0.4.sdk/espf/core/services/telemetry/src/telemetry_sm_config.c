/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include <stddef.h>
#include "libhsm.h"
#include "telemetry_sm_config_user.h"
#include "telemetry_sm_user.h"


static const sTransition_t tran_Not_Init_ev_init_Init;
static const sTransition_t tran_Init_ev_start_Started;
static const sTransition_t tran_Init_ev_periodic___self;
static const sTransition_t tran_Started_ev_stop_Stopped;
static const sTransition_t tran_Started_ev_periodic___self;
static const sTransition_t tran_Stopped_ev_start_Started;
static const sTransition_t tran_Stopped_ev_periodic___self;


static const sTransition_t* trans_Not_Init[] =
{
    &tran_Not_Init_ev_init_Init,
    NULL
};

static const sTransition_t* trans_Init[] =
{
    &tran_Init_ev_start_Started,
    &tran_Init_ev_periodic___self,
    NULL
};

static const sTransition_t* trans_Started[] =
{
    &tran_Started_ev_stop_Stopped,
    &tran_Started_ev_periodic___self,
    NULL
};

static const sTransition_t* trans_Stopped[] =
{
    &tran_Stopped_ev_start_Started,
    &tran_Stopped_ev_periodic___self,
    NULL
};


// telemetry_sm states forward declarations
static const sState_t state_Not_Init;
static const sState_t state_Init;
static const sState_t state_Started;
static const sState_t state_Stopped;

// telemetry_sm root state definition
sCompositeState_t state_telemetry_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_telemetry_sm",
        // onEntryFunc
        NULL,
        // onExitFunc
        NULL,
        // pTransitionList
        NULL,
        // eType
        eHSM_StateType_Composite,
        // pParent
        NULL
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_Not_Init),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Not_Init),
    // pActiveState
    HSM_UPCAST_STATE(&state_telemetry_sm)
};

static const sState_t state_Not_Init = 
{
    // state id
    STATE_NOT_INIT,
    // pName
    "state_Not_Init",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Not_Init,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_sm)
};


static const sState_t state_Init = 
{
    // state id
    STATE_INIT,
    // pName
    "state_Init",
    // onEntryFunc
    &telemetry_sm_on_entry_Init,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Init,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_sm)
};


static const sState_t state_Started = 
{
    // state id
    STATE_STARTED,
    // pName
    "state_Started",
    // onEntryFunc
    &telemetry_sm_on_entry_Started,
    // onExitFunc
    &telemetry_sm_on_exit_Started,
    // pTransitionList
    trans_Started,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_sm)
};


static const sState_t state_Stopped = 
{
    // state id
    STATE_STOPPED,
    // pName
    "state_Stopped",
    // onEntryFunc
    &telemetry_sm_on_entry_Stopped,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Stopped,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_sm)
};

static const sTransition_t tran_Not_Init_ev_init_Init =
{
    // event
    ev_telemetry_sm_init,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Init),
    // action
    NULL
};

static const sTransition_t tran_Init_ev_start_Started =
{
    // event
    ev_telemetry_sm_start,
    // guard    
    &telemetry_sm_guard_can_start_operation,
    // target state
    HSM_UPCAST_STATE(&state_Started),
    // action
    &telemetry_sm_action_prepare_tlm_collection,
};

static const sTransition_t tran_Init_ev_periodic___self =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard
    NULL,
    // target state
    NULL,
    // action
    &telemetry_sm_action_reload_config,
};

static const sTransition_t tran_Started_ev_stop_Stopped =
{
    // event
    ev_telemetry_sm_stop,
    // guard    
    &telemetry_sm_guard_can_stop_operation,
    // target state
    HSM_UPCAST_STATE(&state_Stopped),
    // action
    NULL
};

static const sTransition_t tran_Started_ev_periodic___self =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &telemetry_sm_guard_periodic_timer_elapsed,
    // target state
    NULL,
    // action
    &telemetry_sm_action_collect_telemetry,
};

static const sTransition_t tran_Stopped_ev_start_Started =
{
    // event
    ev_telemetry_sm_start,
    // guard    
    &telemetry_sm_guard_can_start_operation,
    // target state
    HSM_UPCAST_STATE(&state_Started),
    // action
    &telemetry_sm_action_prepare_tlm_collection,
};

static const sTransition_t tran_Stopped_ev_periodic___self =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard
    NULL,
    // target state
    NULL,
    // action
    &telemetry_sm_action_reload_config,
};

