#include <stddef.h>
#include "libhsm.h"
#include "es_adcs_op_modes_sm_config_user.h"
#include "es_adcs_op_modes_sm_user.h"


static const sTransition_t tran_ADCS_RUN_ev_run_to_idle_ADCS_IDLE;
static const sTransition_t tran_ADCS_RUN_ev_run_to_trigger_ADCS_TRIGGER;
static const sTransition_t tran_ADCS_TRIGGER_ev_trigger_to_idle_ADCS_IDLE;
static const sTransition_t tran_ADCS_IDLE_ev_idle_to_run_ADCS_RUN;
static const sTransition_t tran_ADCS_IDLE_ev_idle_to_trigger_ADCS_TRIGGER;
static const sTransition_t tran_ADCS_NOT_INIT_ev_start_ADCS_IDLE;


static const sTransition_t* trans_ADCS_RUN[] =
{
    &tran_ADCS_RUN_ev_run_to_idle_ADCS_IDLE,
    &tran_ADCS_RUN_ev_run_to_trigger_ADCS_TRIGGER,
    NULL
};

static const sTransition_t* trans_ADCS_TRIGGER[] =
{
    &tran_ADCS_TRIGGER_ev_trigger_to_idle_ADCS_IDLE,
    NULL
};

static const sTransition_t* trans_ADCS_IDLE[] =
{
    &tran_ADCS_IDLE_ev_idle_to_run_ADCS_RUN,
    &tran_ADCS_IDLE_ev_idle_to_trigger_ADCS_TRIGGER,
    NULL
};

static const sTransition_t* trans_ADCS_NOT_INIT[] =
{
    &tran_ADCS_NOT_INIT_ev_start_ADCS_IDLE,
    NULL
};


// es_adcs_op_modes_sm states forward declarations
static const sState_t state_ADCS_RUN;
static const sState_t state_ADCS_TRIGGER;
static const sState_t state_ADCS_IDLE;
static const sState_t state_ADCS_NOT_INIT;

// es_adcs_op_modes_sm root state definition
sCompositeState_t state_es_adcs_op_modes_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_es_adcs_op_modes_sm",
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
    HSM_UPCAST_STATE(&state_ADCS_NOT_INIT),
    // pHistoryState
    HSM_UPCAST_STATE(&state_ADCS_NOT_INIT),
    // pActiveState
    HSM_UPCAST_STATE(&state_es_adcs_op_modes_sm)
};

static const sState_t state_ADCS_RUN = 
{
    // state id
    STATE_ADCS_RUN,
    // pName
    "state_ADCS_RUN",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_ADCS_RUN,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_es_adcs_op_modes_sm)
};


static const sState_t state_ADCS_TRIGGER = 
{
    // state id
    STATE_ADCS_TRIGGER,
    // pName
    "state_ADCS_TRIGGER",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_ADCS_TRIGGER,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_es_adcs_op_modes_sm)
};


static const sState_t state_ADCS_IDLE = 
{
    // state id
    STATE_ADCS_IDLE,
    // pName
    "state_ADCS_IDLE",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_ADCS_IDLE,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_es_adcs_op_modes_sm)
};


static const sState_t state_ADCS_NOT_INIT = 
{
    // state id
    STATE_ADCS_NOT_INIT,
    // pName
    "state_ADCS_NOT_INIT",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_ADCS_NOT_INIT,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_es_adcs_op_modes_sm)
};

static const sTransition_t tran_ADCS_RUN_ev_run_to_idle_ADCS_IDLE =
{
    // event
    ev_es_adcs_op_modes_sm_run_to_idle,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_ADCS_IDLE),
    // action
    &es_adcs_op_modes_sm_action_prepare_idle_mode,
};

static const sTransition_t tran_ADCS_RUN_ev_run_to_trigger_ADCS_TRIGGER =
{
    // event
    ev_es_adcs_op_modes_sm_run_to_trigger,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_ADCS_TRIGGER),
    // action
    &es_adcs_op_modes_sm_action_prepare_trigger_mode,
};

static const sTransition_t tran_ADCS_TRIGGER_ev_trigger_to_idle_ADCS_IDLE =
{
    // event
    ev_es_adcs_op_modes_sm_trigger_to_idle,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_ADCS_IDLE),
    // action
    &es_adcs_op_modes_sm_action_prepare_idle_mode,
};

static const sTransition_t tran_ADCS_IDLE_ev_idle_to_run_ADCS_RUN =
{
    // event
    ev_es_adcs_op_modes_sm_idle_to_run,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_ADCS_RUN),
    // action
    &es_adcs_op_modes_sm_action_prepare_run_mode,
};

static const sTransition_t tran_ADCS_IDLE_ev_idle_to_trigger_ADCS_TRIGGER =
{
    // event
    ev_es_adcs_op_modes_sm_idle_to_trigger,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_ADCS_TRIGGER),
    // action
    &es_adcs_op_modes_sm_action_prepare_trigger_mode,
};

static const sTransition_t tran_ADCS_NOT_INIT_ev_start_ADCS_IDLE =
{
    // event
    ev_es_adcs_op_modes_sm_start,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_ADCS_IDLE),
    // action
    NULL
};

