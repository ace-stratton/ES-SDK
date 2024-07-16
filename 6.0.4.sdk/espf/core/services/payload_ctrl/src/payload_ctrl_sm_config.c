#include <stddef.h>
#include "libhsm.h"
#include "payload_ctrl_sm_config_user.h"
#include "payload_ctrl_sm_user.h"


static const sTransition_t tran_Pointing_Idle_ev_periodic_Pointing_InProgress;
static const sTransition_t tran_Pointing_InProgress_ev_periodic_Pointing_Finished;
static const sTransition_t tran_Pointing_InProgress_ev_requesting_payload_off_Pointing_Idle;
static const sTransition_t tran_Pointing_InProgress_ev_periodic_Pointing_Idle;
static const sTransition_t tran_Pointing_Finished_ev_requesting_payload_off_Pointing_Idle;
static const sTransition_t tran_Pointing_Finished_ev_periodic_Pointing_Finished;


static const sTransition_t* trans_Pointing_Idle[] =
{
    &tran_Pointing_Idle_ev_periodic_Pointing_InProgress,
    NULL
};

static const sTransition_t* trans_Pointing_InProgress[] =
{
    &tran_Pointing_InProgress_ev_periodic_Pointing_Finished,
    &tran_Pointing_InProgress_ev_requesting_payload_off_Pointing_Idle,
    &tran_Pointing_InProgress_ev_periodic_Pointing_Idle,
    NULL
};

static const sTransition_t* trans_Pointing_Finished[] =
{
    &tran_Pointing_Finished_ev_requesting_payload_off_Pointing_Idle,
    &tran_Pointing_Finished_ev_periodic_Pointing_Finished,
    NULL
};


// payload_ctrl_sm states forward declarations
static const sState_t state_Pointing_Idle;
static const sState_t state_Pointing_InProgress;
static const sState_t state_Pointing_Finished;

// payload_ctrl_sm root state definition
sCompositeState_t state_payload_ctrl_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_payload_ctrl_sm",
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
    HSM_UPCAST_STATE(&state_Pointing_Idle),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Pointing_Idle),
    // pActiveState
    HSM_UPCAST_STATE(&state_payload_ctrl_sm)
};

static const sState_t state_Pointing_Idle = 
{
    // state id
    STATE_POINTING_IDLE,
    // pName
    "state_Pointing_Idle",
    // onEntryFunc
    &payload_ctrl_sm_on_entry_Pointing_Idle,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Pointing_Idle,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_payload_ctrl_sm)
};


static const sState_t state_Pointing_InProgress = 
{
    // state id
    STATE_POINTING_INPROGRESS,
    // pName
    "state_Pointing_InProgress",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Pointing_InProgress,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_payload_ctrl_sm)
};


static const sState_t state_Pointing_Finished = 
{
    // state id
    STATE_POINTING_FINISHED,
    // pName
    "state_Pointing_Finished",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_Pointing_Finished,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_payload_ctrl_sm)
};

static const sTransition_t tran_Pointing_Idle_ev_periodic_Pointing_InProgress =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &payload_ctrl_sm_guard_Pointing_Idle_periodic_Pointing_InProgress,
    // target state
    HSM_UPCAST_STATE(&state_Pointing_InProgress),
    // action
    &payload_ctrl_sm_action_prepare_pointing_mode,
};

static const sTransition_t tran_Pointing_InProgress_ev_periodic_Pointing_Finished =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &payload_ctrl_sm_guard_is_point_mode_ready,
    // target state
    HSM_UPCAST_STATE(&state_Pointing_Finished),
    // action
    &payload_ctrl_sm_action_start_payload,
};

static const sTransition_t tran_Pointing_InProgress_ev_requesting_payload_off_Pointing_Idle =
{
    // event
    ev_payload_ctrl_sm_requesting_payload_off,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Pointing_Idle),
    // action
    NULL
};

static const sTransition_t tran_Pointing_InProgress_ev_periodic_Pointing_Idle =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &payload_ctrl_sm_guard_is_point_mode_failed,
    // target state
    HSM_UPCAST_STATE(&state_Pointing_Idle),
    // action
    &payload_ctrl_sm_action_notify_adcs_timeout,
};

static const sTransition_t tran_Pointing_Finished_ev_requesting_payload_off_Pointing_Idle =
{
    // event
    ev_payload_ctrl_sm_requesting_payload_off,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Pointing_Idle),
    // action
    NULL
};

static const sTransition_t tran_Pointing_Finished_ev_periodic_Pointing_Finished =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Pointing_Finished),
    // action
    &payload_ctrl_sm_action_serve_additional_payloads,
};

