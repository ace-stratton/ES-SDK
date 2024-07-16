#include <stddef.h>
#include "libhsm.h"
#include "conops_sm_config_user.h"
#include "conops_sm_user.h"


static const sTransition_t tran_Safe_ev_periodic_Detumbling;
static const sTransition_t tran_Safe_ev_idle_flag_set_Idle;
static const sTransition_t tran_Idle_ev_periodic_Safe;
static const sTransition_t tran_Idle_ev_payload_flag_set_Payload;
static const sTransition_t tran_Detumbling_ev_periodic_Safe;
static const sTransition_t tran_Payload_ev_payload_flag_cleared_Idle;
static const sTransition_t tran_Payload_ev_periodic_Safe;


static const sTransition_t* trans_Safe[] =
{
    &tran_Safe_ev_periodic_Detumbling,
    &tran_Safe_ev_idle_flag_set_Idle,
    NULL
};

static const sTransition_t* trans_Idle[] =
{
    &tran_Idle_ev_periodic_Safe,
    &tran_Idle_ev_payload_flag_set_Payload,
    NULL
};

static const sTransition_t* trans_Detumbling[] =
{
    &tran_Detumbling_ev_periodic_Safe,
    NULL
};

static const sTransition_t* trans_Payload[] =
{
    &tran_Payload_ev_payload_flag_cleared_Idle,
    &tran_Payload_ev_periodic_Safe,
    NULL
};


// conops_sm states forward declarations
static const sState_t state_Safe;
static const sState_t state_Idle;
static const sState_t state_Detumbling;
static const sState_t state_Payload;

// conops_sm root state definition
sCompositeState_t state_conops_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_conops_sm",
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
    HSM_UPCAST_STATE(&state_Safe),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Safe),
    // pActiveState
    HSM_UPCAST_STATE(&state_conops_sm)
};

static const sState_t state_Safe = 
{
    // state id
    STATE_SAFE,
    // pName
    "state_Safe",
    // onEntryFunc
    &conops_sm_on_entry_Safe,
    // onExitFunc
    &conops_sm_on_exit_Safe,
    // pTransitionList
    trans_Safe,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_conops_sm)
};


static const sState_t state_Idle = 
{
    // state id
    STATE_IDLE,
    // pName
    "state_Idle",
    // onEntryFunc
    &conops_sm_on_entry_Idle,
    // onExitFunc
    &conops_sm_on_exit_Idle,
    // pTransitionList
    trans_Idle,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_conops_sm)
};


static const sState_t state_Detumbling = 
{
    // state id
    STATE_DETUMBLING,
    // pName
    "state_Detumbling",
    // onEntryFunc
    &conops_sm_on_entry_Detumbling,
    // onExitFunc
    &conops_sm_on_exit_Detumbling,
    // pTransitionList
    trans_Detumbling,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_conops_sm)
};


static const sState_t state_Payload = 
{
    // state id
    STATE_PAYLOAD,
    // pName
    "state_Payload",
    // onEntryFunc
    &conops_sm_on_entry_Payload,
    // onExitFunc
    &conops_sm_on_exit_Payload,
    // pTransitionList
    trans_Payload,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_conops_sm)
};

static const sTransition_t tran_Safe_ev_periodic_Detumbling =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &conops_sm_guard_Safe_periodic_Detumbling,
    // target state
    HSM_UPCAST_STATE(&state_Detumbling),
    // action
    &conops_sm_action_detumb_action,
};

static const sTransition_t tran_Safe_ev_idle_flag_set_Idle =
{
    // event
    ev_conops_sm_idle_flag_set,
    // guard    
    &conops_sm_guard_Safe_idle_flag_set_Idle,
    // target state
    HSM_UPCAST_STATE(&state_Idle),
    // action
    &conops_sm_action_idle_action,
};

static const sTransition_t tran_Idle_ev_periodic_Safe =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &conops_sm_guard_Idle_periodic_Safe,
    // target state
    HSM_UPCAST_STATE(&state_Safe),
    // action
    &conops_sm_action_safe_action,
};

static const sTransition_t tran_Idle_ev_payload_flag_set_Payload =
{
    // event
    ev_conops_sm_payload_flag_set,
    // guard    
    &conops_sm_guard_Idle_payload_flag_set_Payload,
    // target state
    HSM_UPCAST_STATE(&state_Payload),
    // action
    NULL
};

static const sTransition_t tran_Detumbling_ev_periodic_Safe =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &conops_sm_guard_Detumbling_periodic_Safe,
    // target state
    HSM_UPCAST_STATE(&state_Safe),
    // action
    &conops_sm_action_safe_action,
};

static const sTransition_t tran_Payload_ev_payload_flag_cleared_Idle =
{
    // event
    ev_conops_sm_payload_flag_cleared,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Idle),
    // action
    &conops_sm_action_idle_action,
};

static const sTransition_t tran_Payload_ev_periodic_Safe =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &conops_sm_guard_Payload_periodic_Safe,
    // target state
    HSM_UPCAST_STATE(&state_Safe),
    // action
    &conops_sm_action_safe_action,
};

