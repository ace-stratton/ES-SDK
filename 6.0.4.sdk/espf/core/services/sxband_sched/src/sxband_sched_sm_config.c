#include <stddef.h>
#include "libhsm.h"
#include "sxband_sched_sm_config_user.h"
#include "sxband_sched_sm_user.h"


static const sTransition_t tran_not_init_ev_init_init;
static const sTransition_t tran_idle_ev_start_in_progress;
static const sTransition_t tran_wait_file_tx_ev_cmd_confirmed_file_tx_finished;
static const sTransition_t tran_wait_file_tx_ev_periodic_file_tx_finished;
static const sTransition_t tran_file_tx_finished_ev_periodic_wait_file_tx;
static const sTransition_t tran_file_tx_finished_ev_periodic_prepare_cmd;
static const sTransition_t tran_file_tx_finished_ev_periodic_idle;
static const sTransition_t tran_prepare_cmd_ev_periodic_idle;
static const sTransition_t tran_prepare_cmd_ev_periodic_wait_cmd_result;
static const sTransition_t tran_prepare_cmd_ev_periodic_file_tx_in_progress;
static const sTransition_t tran_prepare_cmd_ev_periodic___self;
static const sTransition_t tran_wait_cmd_result_ev_cmd_confirmed_cmd_finished;
static const sTransition_t tran_wait_cmd_result_ev_periodic_cmd_finished;
static const sTransition_t tran_cmd_finished_ev_periodic_prepare_cmd;
static const sTransition_t tran_cmd_finished_ev_periodic_idle;
static const sTransition_t tran_in_progress_ev_stop_idle;
static const sTransition_t tran_in_progress_ev_failure_check_idle;


static const sTransition_t* trans_not_init[] =
{
    &tran_not_init_ev_init_init,
    NULL
};


static const sTransition_t* trans_idle[] =
{
    &tran_idle_ev_start_in_progress,
    NULL
};

static const sTransition_t* trans_wait_file_tx[] =
{
    &tran_wait_file_tx_ev_cmd_confirmed_file_tx_finished,
    &tran_wait_file_tx_ev_periodic_file_tx_finished,
    NULL
};

static const sTransition_t* trans_file_tx_finished[] =
{
    &tran_file_tx_finished_ev_periodic_wait_file_tx,
    &tran_file_tx_finished_ev_periodic_prepare_cmd,
    &tran_file_tx_finished_ev_periodic_idle,
    NULL
};


static const sTransition_t* trans_prepare_cmd[] =
{
    &tran_prepare_cmd_ev_periodic_idle,
    &tran_prepare_cmd_ev_periodic_wait_cmd_result,
    &tran_prepare_cmd_ev_periodic_file_tx_in_progress,
    &tran_prepare_cmd_ev_periodic___self,
    NULL
};

static const sTransition_t* trans_wait_cmd_result[] =
{
    &tran_wait_cmd_result_ev_cmd_confirmed_cmd_finished,
    &tran_wait_cmd_result_ev_periodic_cmd_finished,
    NULL
};

static const sTransition_t* trans_cmd_finished[] =
{
    &tran_cmd_finished_ev_periodic_prepare_cmd,
    &tran_cmd_finished_ev_periodic_idle,
    NULL
};

static const sTransition_t* trans_in_progress[] =
{
    &tran_in_progress_ev_stop_idle,
    &tran_in_progress_ev_failure_check_idle,
    NULL
};


// sxband_sched_sm states forward declarations
static const sState_t state_not_init;
static sCompositeState_t state_init;
static const sState_t state_idle;
static const sState_t state_wait_file_tx;
static const sState_t state_file_tx_finished;
static sCompositeState_t state_file_tx_in_progress;
static const sState_t state_prepare_cmd;
static const sState_t state_wait_cmd_result;
static const sState_t state_cmd_finished;
static sCompositeState_t state_in_progress;

// sxband_sched_sm root state definition
sCompositeState_t state_sxband_sched_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_sxband_sched_sm",
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
    HSM_UPCAST_STATE(&state_not_init),
    // pHistoryState
    HSM_UPCAST_STATE(&state_not_init),
    // pActiveState
    HSM_UPCAST_STATE(&state_sxband_sched_sm)
};

static const sState_t state_not_init = 
{
    // state id
    STATE_NOT_INIT,
    // pName
    "state_not_init",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_not_init,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_sxband_sched_sm)
};


static sCompositeState_t state_init = 
{
    {
        // state id
        STATE_INIT,
        // pName
        "state_init",
        // onEntryFunc
        NULL,
        // onExitFunc
        NULL,
        // pTransitionList        
        NULL,
        // eType
        eHSM_StateType_Composite,
        // pParent
        HSM_UPCAST_STATE(&state_sxband_sched_sm)
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_idle),
    // pHistoryState
    HSM_UPCAST_STATE(&state_idle),
    // pActiveState
    HSM_UPCAST_STATE(&state_init)
    };


static const sState_t state_idle = 
{
    // state id
    STATE_IDLE,
    // pName
    "state_idle",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_idle,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_init)
};


static const sState_t state_wait_file_tx = 
{
    // state id
    STATE_WAIT_FILE_TX,
    // pName
    "state_wait_file_tx",
    // onEntryFunc
    &sxband_sched_sm_on_entry_wait_file_tx,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_wait_file_tx,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_file_tx_in_progress)
};


static const sState_t state_file_tx_finished = 
{
    // state id
    STATE_FILE_TX_FINISHED,
    // pName
    "state_file_tx_finished",
    // onEntryFunc
    &sxband_sched_sm_on_entry_file_tx_finished,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_file_tx_finished,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_file_tx_in_progress)
};


static sCompositeState_t state_file_tx_in_progress = 
{
    {
        // state id
        STATE_FILE_TX_IN_PROGRESS,
        // pName
        "state_file_tx_in_progress",
        // onEntryFunc
        NULL,
        // onExitFunc                
        &sxband_sched_sm_on_exit_file_tx_in_progress,
        // pTransitionList        
        NULL,
        // eType
        eHSM_StateType_Composite,
        // pParent
        HSM_UPCAST_STATE(&state_in_progress)
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_wait_file_tx),
    // pHistoryState
    HSM_UPCAST_STATE(&state_wait_file_tx),
    // pActiveState
    HSM_UPCAST_STATE(&state_file_tx_in_progress)
    };


static const sState_t state_prepare_cmd = 
{
    // state id
    STATE_PREPARE_CMD,
    // pName
    "state_prepare_cmd",
    // onEntryFunc
    &sxband_sched_sm_on_entry_prepare_cmd,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_prepare_cmd,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_in_progress)
};


static const sState_t state_wait_cmd_result = 
{
    // state id
    STATE_WAIT_CMD_RESULT,
    // pName
    "state_wait_cmd_result",
    // onEntryFunc
    NULL,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_wait_cmd_result,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_in_progress)
};


static const sState_t state_cmd_finished = 
{
    // state id
    STATE_CMD_FINISHED,
    // pName
    "state_cmd_finished",
    // onEntryFunc
    &sxband_sched_sm_on_entry_cmd_finished,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_cmd_finished,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_in_progress)
};


static sCompositeState_t state_in_progress = 
{
    {
        // state id
        STATE_IN_PROGRESS,
        // pName
        "state_in_progress",
        // onEntryFunc        
        &sxband_sched_sm_on_entry_in_progress,
        // onExitFunc                
        &sxband_sched_sm_on_exit_in_progress,
        // pTransitionList        
        trans_in_progress,
        // eType
        eHSM_StateType_Composite,
        // pParent
        HSM_UPCAST_STATE(&state_init)
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_prepare_cmd),
    // pHistoryState
    HSM_UPCAST_STATE(&state_prepare_cmd),
    // pActiveState
    HSM_UPCAST_STATE(&state_in_progress)
    };

static const sTransition_t tran_not_init_ev_init_init =
{
    // event
    ev_sxband_sched_sm_init,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_init),
    // action
    NULL
};

static const sTransition_t tran_idle_ev_start_in_progress =
{
    // event
    ev_sxband_sched_sm_start,
    // guard    
    &sxband_sched_sm_guard_is_valid_context,
    // target state
    HSM_UPCAST_STATE(&state_in_progress),
    // action
    &sxband_sched_sm_action_reset_cmd_iterator,
};

static const sTransition_t tran_wait_file_tx_ev_cmd_confirmed_file_tx_finished =
{
    // event
    ev_sxband_sched_sm_cmd_confirmed,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_file_tx_finished),
    // action
    &sxband_sched_sm_action_update_cmd_status,
};

static const sTransition_t tran_wait_file_tx_ev_periodic_file_tx_finished =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_is_cmd_timeout_elapsed,
    // target state
    HSM_UPCAST_STATE(&state_file_tx_finished),
    // action
    &sxband_sched_sm_action_update_cmd_status_timeout,
};

static const sTransition_t tran_file_tx_finished_ev_periodic_wait_file_tx =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_has_more_files,
    // target state
    HSM_UPCAST_STATE(&state_wait_file_tx),
    // action
    &sxband_sched_sm_action_send_next_file_cmd,
};

static const sTransition_t tran_file_tx_finished_ev_periodic_prepare_cmd =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_more_cmd_to_process,
    // target state
    HSM_UPCAST_STATE(&state_prepare_cmd),
    // action
    &sxband_sched_sm_action_load_next_cmd,
};

static const sTransition_t tran_file_tx_finished_ev_periodic_idle =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_no_more_commands,
    // target state
    HSM_UPCAST_STATE(&state_idle),
    // action
    &sxband_sched_sm_action_deinit_sm_context,
};

static const sTransition_t tran_prepare_cmd_ev_periodic_idle =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_no_more_commands,
    // target state
    HSM_UPCAST_STATE(&state_idle),
    // action
    &sxband_sched_sm_action_deinit_sm_context,
};

static const sTransition_t tran_prepare_cmd_ev_periodic_wait_cmd_result =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_is_regular_cmd,
    // target state
    HSM_UPCAST_STATE(&state_wait_cmd_result),
    // action
    &sxband_sched_sm_action_send_next_cmd,
};

static const sTransition_t tran_prepare_cmd_ev_periodic_file_tx_in_progress =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_can_iterate_files_with_pattern,
    // target state
    HSM_UPCAST_STATE(&state_file_tx_in_progress),
    // action
    &sxband_sched_sm_action_send_first_file_cmd,
};

static const sTransition_t tran_prepare_cmd_ev_periodic___self =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_empty_pattern,
    // target state
    NULL,
    // action
    &sxband_sched_sm_action_load_next_cmd_empty_pattern,
};

static const sTransition_t tran_wait_cmd_result_ev_cmd_confirmed_cmd_finished =
{
    // event
    ev_sxband_sched_sm_cmd_confirmed,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_cmd_finished),
    // action
    &sxband_sched_sm_action_update_cmd_status,
};

static const sTransition_t tran_wait_cmd_result_ev_periodic_cmd_finished =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_is_cmd_timeout_elapsed,
    // target state
    HSM_UPCAST_STATE(&state_cmd_finished),
    // action
    &sxband_sched_sm_action_update_cmd_status_timeout,
};

static const sTransition_t tran_cmd_finished_ev_periodic_prepare_cmd =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_has_more_commands,
    // target state
    HSM_UPCAST_STATE(&state_prepare_cmd),
    // action
    &sxband_sched_sm_action_load_next_cmd,
};

static const sTransition_t tran_cmd_finished_ev_periodic_idle =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &sxband_sched_sm_guard_no_more_commands,
    // target state
    HSM_UPCAST_STATE(&state_idle),
    // action
    &sxband_sched_sm_action_deinit_sm_context,
};

static const sTransition_t tran_in_progress_ev_stop_idle =
{
    // event
    ev_sxband_sched_sm_stop,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_idle),
    // action
    &sxband_sched_sm_action_deinit_sm_context_stop,
};

static const sTransition_t tran_in_progress_ev_failure_check_idle =
{
    // event
    ev_sxband_sched_sm_failure_check,
    // guard    
    &sxband_sched_sm_guard_general_failure,
    // target state
    HSM_UPCAST_STATE(&state_idle),
    // action
    &sxband_sched_sm_action_deinit_sm_context_fail,
};

