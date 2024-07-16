#include <stddef.h>
#include "libhsm.h"
#include "telemetry_file_sink_sm_config_user.h"
#include "telemetry_file_sink_sm_user.h"


static const sTransition_t tran_Not_Init_ev_init_Init;
static const sTransition_t tran_Init_ev_start_Wait_Storage;
static const sTransition_t tran_Init_ev_periodic___self;
static const sTransition_t tran_Wait_Storage_ev_periodic_Started;
static const sTransition_t tran_Started_ev_stop_Stopped;
static const sTransition_t tran_Started_ev_periodic___self;
static const sTransition_t tran_Started_ev_periodic_Wait_Storage;
static const sTransition_t tran_Started_ev_restart_Wait_Storage;
static const sTransition_t tran_Stopped_ev_start_Wait_Storage;
static const sTransition_t tran_Stopped_ev_periodic_Wait_Storage;
static const sTransition_t tran_Stopped_ev_periodic___self;


static const sTransition_t* trans_Not_Init[] =
{
    &tran_Not_Init_ev_init_Init,
    NULL
};

static const sTransition_t* trans_Init[] =
{
    &tran_Init_ev_start_Wait_Storage,
    &tran_Init_ev_periodic___self,
    NULL
};

static const sTransition_t* trans_Wait_Storage[] =
{
    &tran_Wait_Storage_ev_periodic_Started,
    NULL
};

static const sTransition_t* trans_Started[] =
{
    &tran_Started_ev_stop_Stopped,
    &tran_Started_ev_periodic___self,
    &tran_Started_ev_periodic_Wait_Storage,
    &tran_Started_ev_restart_Wait_Storage,
    NULL
};

static const sTransition_t* trans_Stopped[] =
{
    &tran_Stopped_ev_start_Wait_Storage,
    &tran_Stopped_ev_periodic_Wait_Storage,
    &tran_Stopped_ev_periodic___self,
    NULL
};


// telemetry_file_sink_sm states forward declarations
static const sState_t state_Not_Init;
static const sState_t state_Init;
static const sState_t state_Wait_Storage;
static const sState_t state_Started;
static const sState_t state_Stopped;

// telemetry_file_sink_sm root state definition
sCompositeState_t state_telemetry_file_sink_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_telemetry_file_sink_sm",
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
    HSM_UPCAST_STATE(&state_telemetry_file_sink_sm)
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
    HSM_UPCAST_STATE(&state_telemetry_file_sink_sm)
};


static const sState_t state_Init =
{
    // state id
    STATE_INIT,
    // pName
    "state_Init",
    // onEntryFunc
    &telemetry_file_sink_sm_on_entry_Init,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Init,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_file_sink_sm)
};


static const sState_t state_Wait_Storage =
{
    // state id
    STATE_WAIT_STORAGE,
    // pName
    "state_Wait_Storage",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Wait_Storage,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_file_sink_sm)
};


static const sState_t state_Started =
{
    // state id
    STATE_STARTED,
    // pName
    "state_Started",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Started,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_file_sink_sm)
};


static const sState_t state_Stopped =
{
    // state id
    STATE_STOPPED,
    // pName
    "state_Stopped",
    // onEntryFunc
    &telemetry_file_sink_sm_on_entry_Stopped,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Stopped,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_telemetry_file_sink_sm)
};

static const sTransition_t tran_Not_Init_ev_init_Init =
{
    // event
    ev_telemetry_file_sink_sm_init,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Init),
    // action
    NULL
};

static const sTransition_t tran_Init_ev_start_Wait_Storage =
{
    // event
    ev_telemetry_file_sink_sm_start,
    // guard
    &telemetry_file_sink_sm_guard_can_start_operation,
    // target state
    HSM_UPCAST_STATE(&state_Wait_Storage),
    // action
    &telemetry_file_sink_sm_action_reload_config,
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
    &telemetry_file_sink_sm_action_reload_config,
};

static const sTransition_t tran_Wait_Storage_ev_periodic_Started =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard
    &telemetry_file_sink_sm_guard_is_storage_available,
    // target state
    HSM_UPCAST_STATE(&state_Started),
    // action
    &telemetry_file_sink_sm_action_perform_file_scan,
};

static const sTransition_t tran_Started_ev_stop_Stopped =
{
    // event
    ev_telemetry_file_sink_sm_stop,
    // guard
    &telemetry_file_sink_sm_guard_can_stop_operation,
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
    &telemetry_file_sink_sm_guard_is_storage_available,
    // target state
    NULL,
    // action
    &telemetry_file_sink_sm_action_store_telemetry,
};

static const sTransition_t tran_Started_ev_periodic_Wait_Storage =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard
    &telemetry_file_sink_sm_guard_is_storage_blocked,
    // target state
    HSM_UPCAST_STATE(&state_Wait_Storage),
    // action
    NULL
};

static const sTransition_t tran_Started_ev_restart_Wait_Storage =
{
    // event
    ev_telemetry_file_sink_sm_restart,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Wait_Storage),
    // action
    &telemetry_file_sink_sm_action_clean_and_reload_cfg,
};

static const sTransition_t tran_Stopped_ev_start_Wait_Storage =
{
    // event
    ev_telemetry_file_sink_sm_start,
    // guard
    &telemetry_file_sink_sm_guard_can_start_operation,
    // target state
    HSM_UPCAST_STATE(&state_Wait_Storage),
    // action
    NULL
};

static const sTransition_t tran_Stopped_ev_periodic_Wait_Storage =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard
    &telemetry_file_sink_sm_guard_is_auto_resume_timer_elapsed,
    // target state
    HSM_UPCAST_STATE(&state_Wait_Storage),
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
    &telemetry_file_sink_sm_action_reload_config,
};

