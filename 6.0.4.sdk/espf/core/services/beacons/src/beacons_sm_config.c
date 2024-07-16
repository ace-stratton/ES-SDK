/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include <stddef.h>
#include "libhsm.h"
#include "beacons_sm_config_user.h"
#include "beacons_sm_user.h"


static const sTransition_t tran_Not_Init_ev_init_Init;
static const sTransition_t tran_Init_ev_start_Started;
static const sTransition_t tran_Init_ev_periodic___self;
static const sTransition_t tran_Started_ev_stop_Stopped;
static const sTransition_t tran_Beacon_Wait_Time_ev_periodic_Beacon_Transmission;
static const sTransition_t tran_Beacon_Transmission_ev_periodic_Beacon_Wait_Time;
static const sTransition_t tran_Beacon_Transmission_ev_periodic_Beacon_Wait_Time_1;
static const sTransition_t tran_Beacon_Transmission_ev_periodic___self;
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
    NULL
};

static const sTransition_t* trans_Beacon_Wait_Time[] =
{
    &tran_Beacon_Wait_Time_ev_periodic_Beacon_Transmission,
    NULL
};

static const sTransition_t* trans_Beacon_Transmission[] =
{
    &tran_Beacon_Transmission_ev_periodic_Beacon_Wait_Time,
    &tran_Beacon_Transmission_ev_periodic_Beacon_Wait_Time_1,
    &tran_Beacon_Transmission_ev_periodic___self,
    NULL
};

static const sTransition_t* trans_Stopped[] =
{
    &tran_Stopped_ev_start_Started,
    &tran_Stopped_ev_periodic___self,
    NULL
};


// beacons_sm states forward declarations
static const sState_t state_Not_Init;
static const sState_t state_Init;
static sCompositeState_t state_Started;
static const sState_t state_Beacon_Wait_Time;
static const sState_t state_Beacon_Transmission;
static const sState_t state_Stopped;

// beacons_sm root state definition
sCompositeState_t state_beacons_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_beacons_sm",
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
    HSM_UPCAST_STATE(&state_beacons_sm)
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
    HSM_UPCAST_STATE(&state_beacons_sm)
};


static const sState_t state_Init = 
{
    // state id
    STATE_INIT,
    // pName
    "state_Init",
    // onEntryFunc
    &beacons_sm_on_entry_Init,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Init,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_beacons_sm)
};


static sCompositeState_t state_Started = 
{
    {
        // state id
        STATE_STARTED,
        // pName
        "state_Started",
        // onEntryFunc        
        &beacons_sm_on_entry_Started,
        // onExitFunc                
        &beacons_sm_on_exit_Started,
        // pTransitionList        
        trans_Started,
        // eType
        eHSM_StateType_Composite,
        // pParent
        HSM_UPCAST_STATE(&state_beacons_sm)
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_Beacon_Wait_Time),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Beacon_Wait_Time),
    // pActiveState
    HSM_UPCAST_STATE(&state_Started)
    };


static const sState_t state_Beacon_Wait_Time = 
{
    // state id
    STATE_BEACON_WAIT_TIME,
    // pName
    "state_Beacon_Wait_Time",
    // onEntryFunc
    &beacons_sm_on_entry_Beacon_Wait_Time,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Beacon_Wait_Time,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Started)
};


static const sState_t state_Beacon_Transmission = 
{
    // state id
    STATE_BEACON_TRANSMISSION,
    // pName
    "state_Beacon_Transmission",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Beacon_Transmission,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Started)
};


static const sState_t state_Stopped = 
{
    // state id
    STATE_STOPPED,
    // pName
    "state_Stopped",
    // onEntryFunc
    &beacons_sm_on_entry_Stopped,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Stopped,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_beacons_sm)
};

static const sTransition_t tran_Not_Init_ev_init_Init =
{
    // event
    ev_beacons_sm_init,
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
    ev_beacons_sm_start,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Started),
    // action
    NULL
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
    &beacons_sm_action_reload_config,
};

static const sTransition_t tran_Started_ev_stop_Stopped =
{
    // event
    ev_beacons_sm_stop,
    // guard    
    &beacons_sm_guard_can_stop_operation,
    // target state
    HSM_UPCAST_STATE(&state_Stopped),
    // action
    NULL
};

static const sTransition_t tran_Beacon_Wait_Time_ev_periodic_Beacon_Transmission =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &beacons_sm_guard_is_beacon_time_expired,
    // target state
    HSM_UPCAST_STATE(&state_Beacon_Transmission),
    // action
    &beacons_sm_action_start_beacon_burst,
};

static const sTransition_t tran_Beacon_Transmission_ev_periodic_Beacon_Wait_Time =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &beacons_sm_guard_all_beacons_transmitted,
    // target state
    HSM_UPCAST_STATE(&state_Beacon_Wait_Time),
    // action
    &beacons_sm_action_reset_send_state,
};

static const sTransition_t tran_Beacon_Transmission_ev_periodic_Beacon_Wait_Time_1 =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &beacons_sm_guard_is_sink_timeout_expired,
    // target state
    HSM_UPCAST_STATE(&state_Beacon_Wait_Time),
    // action
    &beacons_sm_action_log_sink_timeout_error,
};

static const sTransition_t tran_Beacon_Transmission_ev_periodic___self =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &beacons_sm_guard_can_continue_transmission,
    // target state
    NULL,
    // action
    &beacons_sm_action_send_beacon,
};

static const sTransition_t tran_Stopped_ev_start_Started =
{
    // event
    ev_beacons_sm_start,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Started),
    // action
    NULL
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
    &beacons_sm_action_reload_config,
};

