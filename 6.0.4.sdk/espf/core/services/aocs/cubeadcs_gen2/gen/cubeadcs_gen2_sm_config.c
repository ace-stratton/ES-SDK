#include <stddef.h>
#include "libhsm.h"
#include "cubeadcs_gen2_sm_config_user.h"
#include "cubeadcs_gen2_sm_user.h"


static const sTransition_t tran_Backoff_ev_periodic_EventMarkerAcquisition;
static const sTransition_t tran_EventMarkerAcquisition_ev_event_marker_acquired_Check;
static const sTransition_t tran_Idle_ev_periodic_Check;
static const sTransition_t tran_Idle_ev_periodic_EventDownload;
static const sTransition_t tran_Idle_ev_request_a_state_change_StateChange;
static const sTransition_t tran_Check_ev_request_fdir_FDIR;
static const sTransition_t tran_Check_ev_check_completed_Idle;
static const sTransition_t tran_EventDownload_ev_event_download_completed_Idle;
static const sTransition_t tran_EventDownload_ev_request_fdir_FDIR;
static const sTransition_t tran_StateChange_ev_request_fdir_FDIR;
static const sTransition_t tran_StateChange_ev_state_change_completed_Idle;
static const sTransition_t tran_FDIR_ev_fdir_completed_Idle;


static const sTransition_t* trans_Backoff[] =
{
    &tran_Backoff_ev_periodic_EventMarkerAcquisition,
    NULL
};

static const sTransition_t* trans_EventMarkerAcquisition[] =
{
    &tran_EventMarkerAcquisition_ev_event_marker_acquired_Check,
    NULL
};

static const sTransition_t* trans_Idle[] =
{
    &tran_Idle_ev_periodic_Check,
    &tran_Idle_ev_periodic_EventDownload,
    &tran_Idle_ev_request_a_state_change_StateChange,
    NULL
};

static const sTransition_t* trans_Check[] =
{
    &tran_Check_ev_request_fdir_FDIR,
    &tran_Check_ev_check_completed_Idle,
    NULL
};

static const sTransition_t* trans_EventDownload[] =
{
    &tran_EventDownload_ev_event_download_completed_Idle,
    &tran_EventDownload_ev_request_fdir_FDIR,
    NULL
};

static const sTransition_t* trans_StateChange[] =
{
    &tran_StateChange_ev_request_fdir_FDIR,
    &tran_StateChange_ev_state_change_completed_Idle,
    NULL
};

static const sTransition_t* trans_FDIR[] =
{
    &tran_FDIR_ev_fdir_completed_Idle,
    NULL
};


// cubeadcs_gen2_sm states forward declarations
static const sState_t state_Backoff;
static const sState_t state_EventMarkerAcquisition;
static const sState_t state_Idle;
static const sState_t state_Check;
static const sState_t state_EventDownload;
static const sState_t state_StateChange;
static const sState_t state_FDIR;

// cubeadcs_gen2_sm root state definition
sCompositeState_t state_cubeadcs_gen2_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_cubeadcs_gen2_sm",
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
    HSM_UPCAST_STATE(&state_Backoff),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Backoff),
    // pActiveState
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};

static const sState_t state_Backoff = 
{
    // state id
    STATE_BACKOFF,
    // pName
    "state_Backoff",
    // onEntryFunc
    &cubeadcs_gen2_sm_on_entry_Backoff,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Backoff,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};


static const sState_t state_EventMarkerAcquisition = 
{
    // state id
    STATE_EVENTMARKERACQUISITION,
    // pName
    "state_EventMarkerAcquisition",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_EventMarkerAcquisition,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};


static const sState_t state_Idle = 
{
    // state id
    STATE_IDLE,
    // pName
    "state_Idle",
    // onEntryFunc
    &cubeadcs_gen2_sm_on_entry_Idle,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Idle,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};


static const sState_t state_Check = 
{
    // state id
    STATE_CHECK,
    // pName
    "state_Check",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Check,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};


static const sState_t state_EventDownload = 
{
    // state id
    STATE_EVENTDOWNLOAD,
    // pName
    "state_EventDownload",
    // onEntryFunc
    &cubeadcs_gen2_sm_on_entry_EventDownload,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_EventDownload,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};


static const sState_t state_StateChange = 
{
    // state id
    STATE_STATECHANGE,
    // pName
    "state_StateChange",
    // onEntryFunc
    &cubeadcs_gen2_sm_on_entry_StateChange,
    // onExitFunc
    &cubeadcs_gen2_sm_on_exit_StateChange,
    // pTransitionList
    trans_StateChange,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};


static const sState_t state_FDIR = 
{
    // state id
    STATE_FDIR,
    // pName
    "state_FDIR",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_FDIR,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_cubeadcs_gen2_sm)
};

static const sTransition_t tran_Backoff_ev_periodic_EventMarkerAcquisition =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &cubeadcs_gen2_sm_guard_is_adcs_ready,
    // target state
    HSM_UPCAST_STATE(&state_EventMarkerAcquisition),
    // action
    NULL
};

static const sTransition_t tran_EventMarkerAcquisition_ev_event_marker_acquired_Check =
{
    // event
    ev_cubeadcs_gen2_sm_event_marker_acquired,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Check),
    // action
    NULL
};

static const sTransition_t tran_Idle_ev_periodic_Check =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &cubeadcs_gen2_sm_guard_is_time_to_check_expired,
    // target state
    HSM_UPCAST_STATE(&state_Check),
    // action
    NULL
};

static const sTransition_t tran_Idle_ev_periodic_EventDownload =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &cubeadcs_gen2_sm_guard_is_time_to_event_download_expired,
    // target state
    HSM_UPCAST_STATE(&state_EventDownload),
    // action
    NULL
};

static const sTransition_t tran_Idle_ev_request_a_state_change_StateChange =
{
    // event
    ev_cubeadcs_gen2_sm_request_a_state_change,
    // guard    
    &cubeadcs_gen2_sm_guard_is_state_change_valid,
    // target state
    HSM_UPCAST_STATE(&state_StateChange),
    // action
    NULL
};

static const sTransition_t tran_Check_ev_request_fdir_FDIR =
{
    // event
    ev_cubeadcs_gen2_sm_request_fdir,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_FDIR),
    // action
    NULL
};

static const sTransition_t tran_Check_ev_check_completed_Idle =
{
    // event
    ev_cubeadcs_gen2_sm_check_completed,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Idle),
    // action
    NULL
};

static const sTransition_t tran_EventDownload_ev_event_download_completed_Idle =
{
    // event
    ev_cubeadcs_gen2_sm_event_download_completed,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Idle),
    // action
    NULL
};

static const sTransition_t tran_EventDownload_ev_request_fdir_FDIR =
{
    // event
    ev_cubeadcs_gen2_sm_request_fdir,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_FDIR),
    // action
    NULL
};

static const sTransition_t tran_StateChange_ev_request_fdir_FDIR =
{
    // event
    ev_cubeadcs_gen2_sm_request_fdir,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_FDIR),
    // action
    NULL
};

static const sTransition_t tran_StateChange_ev_state_change_completed_Idle =
{
    // event
    ev_cubeadcs_gen2_sm_state_change_completed,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Idle),
    // action
    NULL
};

static const sTransition_t tran_FDIR_ev_fdir_completed_Idle =
{
    // event
    ev_cubeadcs_gen2_sm_fdir_completed,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Idle),
    // action
    &cubeadcs_gen2_sm_action_notify_users,
};

