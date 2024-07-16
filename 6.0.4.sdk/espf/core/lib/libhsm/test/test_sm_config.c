#include <stddef.h>
#include "libhsm.h"
#include "Test_SM_config_user.h"
#include "Test_SM_user.h"


static const sTransition_t tran_Initial_ev_start_Composite;
static const sTransition_t tran_Initial_ev_go_composite_history___history_Composite;
static const sTransition_t tran_Initial_ev_switch_to_idle_Idle;
static const sTransition_t tran_Initial_ev_go_sub2_Composite_Sub2;
static const sTransition_t tran_Initial_ev_go_sub3_Composite_Sub3;
static const sTransition_t tran_Initial_ev_trigger_regular_self_trans_Initial;
static const sTransition_t tran_Initial_ev_trigger_self_trans___self;
static const sTransition_t tran_Idle_ev_switch_to_initial_Initial;
static const sTransition_t tran_Composite_Sub1_ev_periodic_Composite_Sub2;
static const sTransition_t tran_Composite_Sub1_ev_go_to_initial_Initial;
static const sTransition_t tran_Composite_Sub2_ev_go_to_initial_Initial;
static const sTransition_t tran_Deep_Sub3_ev_go_to_initial_Initial;
static const sTransition_t tran_Deep_Sub3_ev_go_to_sub2_direct_Composite_Sub2;
static const sTransition_t tran_Deep_Sub4_ev_go_to_sub1_direct_Composite_Sub1;
static const sTransition_t tran_Composite_Sub3_ev_go_to_sub2_direct_Composite_Sub2;
static const sTransition_t tran_Composite_Sub3_ev_go_to_initial_Initial;


static const sTransition_t* trans_Initial[] =
{
    &tran_Initial_ev_start_Composite,
    &tran_Initial_ev_go_composite_history___history_Composite,
    &tran_Initial_ev_switch_to_idle_Idle,
    &tran_Initial_ev_go_sub2_Composite_Sub2,
    &tran_Initial_ev_go_sub3_Composite_Sub3,
    &tran_Initial_ev_trigger_regular_self_trans_Initial,
    &tran_Initial_ev_trigger_self_trans___self,
    NULL
};

static const sTransition_t* trans_Idle[] =
{
    &tran_Idle_ev_switch_to_initial_Initial,
    NULL
};


static const sTransition_t* trans_Composite_Sub1[] =
{
    &tran_Composite_Sub1_ev_periodic_Composite_Sub2,
    &tran_Composite_Sub1_ev_go_to_initial_Initial,
    NULL
};

static const sTransition_t* trans_Composite_Sub2[] =
{
    &tran_Composite_Sub2_ev_go_to_initial_Initial,
    NULL
};

static const sTransition_t* trans_Deep_Sub3[] =
{
    &tran_Deep_Sub3_ev_go_to_initial_Initial,
    &tran_Deep_Sub3_ev_go_to_sub2_direct_Composite_Sub2,
    NULL
};

static const sTransition_t* trans_Deep_Sub4[] =
{
    &tran_Deep_Sub4_ev_go_to_sub1_direct_Composite_Sub1,
    NULL
};

static const sTransition_t* trans_Composite_Sub3[] =
{
    &tran_Composite_Sub3_ev_go_to_sub2_direct_Composite_Sub2,
    &tran_Composite_Sub3_ev_go_to_initial_Initial,
    NULL
};


// Test_SM states forward declarations
static const sState_t state_Initial;
static const sState_t state_Idle;
static sCompositeState_t state_Composite;
static const sState_t state_Composite_Sub1;
static const sState_t state_Composite_Sub2;
static const sState_t state_Deep_Sub3;
static const sState_t state_Deep_Sub4;
static sCompositeState_t state_Composite_Sub3;

// Test_SM root state definition
sCompositeState_t state_Test_SM =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_Test_SM",
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
    HSM_UPCAST_STATE(&state_Initial),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Initial),
    // pActiveState
    HSM_UPCAST_STATE(&state_Test_SM)
};

static const sState_t state_Initial = 
{
    // state id
    STATE_INITIAL,
    // pName
    "state_Initial",
    // onEntryFunc
    &Test_SM_on_entry_Initial,
    // onExitFunc
    &Test_SM_on_exit_Initial,
    // pTransitionList
    trans_Initial,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Test_SM)
};


static const sState_t state_Idle = 
{
    // state id
    STATE_IDLE,
    // pName
    "state_Idle",
    // onEntryFunc
    &Test_SM_on_entry_Idle,
    // onExitFunc
    &Test_SM_on_exit_Idle,
    // pTransitionList
    trans_Idle,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Test_SM)
};


static sCompositeState_t state_Composite = 
{
    {
        // state id
        STATE_COMPOSITE,
        // pName
        "state_Composite",
        // onEntryFunc        
        &Test_SM_on_entry_Composite,
        // onExitFunc                
        &Test_SM_on_exit_Composite,
        // pTransitionList        
        NULL,
        // eType
        eHSM_StateType_Composite,
        // pParent
        HSM_UPCAST_STATE(&state_Test_SM)
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_Composite_Sub1),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Composite_Sub1),
    // pActiveState
    HSM_UPCAST_STATE(&state_Composite)
    };


static const sState_t state_Composite_Sub1 = 
{
    // state id
    STATE_COMPOSITE_SUB1,
    // pName
    "state_Composite_Sub1",
    // onEntryFunc
    &Test_SM_on_entry_Composite_Sub1,
    // onExitFunc
    &Test_SM_on_exit_Composite_Sub1,
    // pTransitionList
    trans_Composite_Sub1,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Composite)
};


static const sState_t state_Composite_Sub2 = 
{
    // state id
    STATE_COMPOSITE_SUB2,
    // pName
    "state_Composite_Sub2",
    // onEntryFunc
    &Test_SM_on_entry_Composite_Sub2,
    // onExitFunc
    &Test_SM_on_exit_Composite_Sub2,
    // pTransitionList
    trans_Composite_Sub2,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Composite)
};


static const sState_t state_Deep_Sub3 = 
{
    // state id
    STATE_DEEP_SUB3,
    // pName
    "state_Deep_Sub3",
    // onEntryFunc
    &Test_SM_on_entry_Deep_Sub3,
    // onExitFunc
    &Test_SM_on_exit_Deep_Sub3,
    // pTransitionList
    trans_Deep_Sub3,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Composite_Sub3)
};


static const sState_t state_Deep_Sub4 = 
{
    // state id
    STATE_DEEP_SUB4,
    // pName
    "state_Deep_Sub4",
    // onEntryFunc
    &Test_SM_on_entry_Deep_Sub4,
    // onExitFunc
    &Test_SM_on_exit_Deep_Sub4,
    // pTransitionList
    trans_Deep_Sub4,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Composite_Sub3)
};


static sCompositeState_t state_Composite_Sub3 = 
{
    {
        // state id
        STATE_COMPOSITE_SUB3,
        // pName
        "state_Composite_Sub3",
        // onEntryFunc        
        &Test_SM_on_entry_Composite_Sub3,
        // onExitFunc                
        &Test_SM_on_exit_Composite_Sub3,
        // pTransitionList        
        trans_Composite_Sub3,
        // eType
        eHSM_StateType_Composite,
        // pParent
        HSM_UPCAST_STATE(&state_Composite)
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_Deep_Sub3),
    // pHistoryState
    HSM_UPCAST_STATE(&state_Deep_Sub3),
    // pActiveState
    HSM_UPCAST_STATE(&state_Composite_Sub3)
    };

static const sState_t state___history_Composite = 
{
    // state id
    STATE___HISTORY_COMPOSITE,
    // pName
    "state___history_Composite",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    NULL,
    // eType
    eHSM_StateType_History,
    // pParent
    HSM_UPCAST_STATE(&state_Composite)
};
static const sTransition_t tran_Initial_ev_start_Composite =
{
    // event
    ev_Test_SM_start,
    // guard    
    &Test_SM_guard_start_conditions_met,
    // target state
    HSM_UPCAST_STATE(&state_Composite),
    // action
    &Test_SM_action_on_start_action,
};

static const sTransition_t tran_Initial_ev_go_composite_history___history_Composite =
{
    // event
    ev_Test_SM_go_composite_history,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state___history_Composite),
    // action
    NULL
};

static const sTransition_t tran_Initial_ev_switch_to_idle_Idle =
{
    // event
    ev_Test_SM_switch_to_idle,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Idle),
    // action
    NULL
};

static const sTransition_t tran_Initial_ev_go_sub2_Composite_Sub2 =
{
    // event
    ev_Test_SM_go_sub2,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Composite_Sub2),
    // action
    NULL
};

static const sTransition_t tran_Initial_ev_go_sub3_Composite_Sub3 =
{
    // event
    ev_Test_SM_go_sub3,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Composite_Sub3),
    // action
    NULL
};

static const sTransition_t tran_Initial_ev_trigger_regular_self_trans_Initial =
{
    // event
    ev_Test_SM_trigger_regular_self_trans,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Initial),
    // action
    &Test_SM_action_on_regular_self_action,
};

static const sTransition_t tran_Initial_ev_trigger_self_trans___self =
{
    // event
    ev_Test_SM_trigger_self_trans,
    // guard
    NULL,
    // target state
    NULL,
    // action
    &Test_SM_action_on_self_action,
};

static const sTransition_t tran_Idle_ev_switch_to_initial_Initial =
{
    // event
    ev_Test_SM_switch_to_initial,
    // guard    
    &Test_SM_guard_initial_cond_met,
    // target state
    HSM_UPCAST_STATE(&state_Initial),
    // action
    &Test_SM_action_on_initial_switch_action,
};

static const sTransition_t tran_Composite_Sub1_ev_periodic_Composite_Sub2 =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &Test_SM_guard_entry_to_sub2_allowed,
    // target state
    HSM_UPCAST_STATE(&state_Composite_Sub2),
    // action
    &Test_SM_action_composite_sub2_action,
};

static const sTransition_t tran_Composite_Sub1_ev_go_to_initial_Initial =
{
    // event
    ev_Test_SM_go_to_initial,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Initial),
    // action
    NULL
};

static const sTransition_t tran_Composite_Sub2_ev_go_to_initial_Initial =
{
    // event
    ev_Test_SM_go_to_initial,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Initial),
    // action
    NULL
};

static const sTransition_t tran_Deep_Sub3_ev_go_to_initial_Initial =
{
    // event
    ev_Test_SM_go_to_initial,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Initial),
    // action
    NULL
};

static const sTransition_t tran_Deep_Sub3_ev_go_to_sub2_direct_Composite_Sub2 =
{
    // event
    ev_Test_SM_go_to_sub2_direct,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Composite_Sub2),
    // action
    NULL
};

static const sTransition_t tran_Deep_Sub4_ev_go_to_sub1_direct_Composite_Sub1 =
{
    // event
    ev_Test_SM_go_to_sub1_direct,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Composite_Sub1),
    // action
    NULL
};

static const sTransition_t tran_Composite_Sub3_ev_go_to_sub2_direct_Composite_Sub2 =
{
    // event
    ev_Test_SM_go_to_sub2_direct,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Composite_Sub2),
    // action
    NULL
};

static const sTransition_t tran_Composite_Sub3_ev_go_to_initial_Initial =
{
    // event
    ev_Test_SM_go_to_initial,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_Initial),
    // action
    NULL
};

