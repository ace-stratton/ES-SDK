/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_ctrl
 * @{
 *
 * @file     eps_ctrl_sm_config.c
 * @brief    Generated EPS Control libhsm configuration
 *
 * @}
 */
#include <stddef.h>
#include "libhsm.h"
#include "eps_ctrl_sm_config_user.h"
#include "eps_ctrl_sm_user.h"


static const sTransition_t tran_off_ev_initialized_idle;
static const sTransition_t tran_idle_ev_new_request_active_request;
static const sTransition_t tran_active_request_ev_periodic_retry_request;
static const sTransition_t tran_active_request_ev_response_received_finish_request;
static const sTransition_t tran_retry_request_ev_periodic_active_request;
static const sTransition_t tran_retry_request_ev_periodic_finish_request;
static const sTransition_t tran_finish_request_ev_periodic_active_request;
static const sTransition_t tran_finish_request_ev_periodic_idle;


static const sTransition_t* trans_off[] =
{
    &tran_off_ev_initialized_idle,
    NULL
};

static const sTransition_t* trans_idle[] =
{
    &tran_idle_ev_new_request_active_request,
    NULL
};

static const sTransition_t* trans_active_request[] =
{
    &tran_active_request_ev_periodic_retry_request,
    &tran_active_request_ev_response_received_finish_request,
    NULL
};

static const sTransition_t* trans_retry_request[] =
{
    &tran_retry_request_ev_periodic_active_request,
    &tran_retry_request_ev_periodic_finish_request,
    NULL
};

static const sTransition_t* trans_finish_request[] =
{
    &tran_finish_request_ev_periodic_active_request,
    &tran_finish_request_ev_periodic_idle,
    NULL
};


// eps_ctrl_sm states forward declarations
static const sState_t state_off;
static const sState_t state_idle;
static const sState_t state_active_request;
static const sState_t state_retry_request;
static const sState_t state_finish_request;

// eps_ctrl_sm root state definition
sCompositeState_t state_eps_ctrl_sm =
{
    {
        // state id
        STATE_ROOT,
        // pName
        "state_eps_ctrl_sm",
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
    HSM_UPCAST_STATE(&state_off),
    // pHistoryState
    HSM_UPCAST_STATE(&state_off),
    // pActiveState
    HSM_UPCAST_STATE(&state_eps_ctrl_sm)
};

static const sState_t state_off = 
{
    // state id
    STATE_OFF,
    // pName
    "state_off",
    // onEntryFunc
    NULL,
    // onExitFunc
    &eps_ctrl_sm_on_exit_off,
    // pTransitionList
    trans_off,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_eps_ctrl_sm)
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
    HSM_UPCAST_STATE(&state_eps_ctrl_sm)
};


static const sState_t state_active_request = 
{
    // state id
    STATE_ACTIVE_REQUEST,
    // pName
    "state_active_request",
    // onEntryFunc
    &eps_ctrl_sm_on_entry_active_request,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_active_request,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_eps_ctrl_sm)
};


static const sState_t state_retry_request = 
{
    // state id
    STATE_RETRY_REQUEST,
    // pName
    "state_retry_request",
    // onEntryFunc
    &eps_ctrl_sm_on_entry_retry_request,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_retry_request,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_eps_ctrl_sm)
};


static const sState_t state_finish_request = 
{
    // state id
    STATE_FINISH_REQUEST,
    // pName
    "state_finish_request",
    // onEntryFunc
    &eps_ctrl_sm_on_entry_finish_request,
    // onExitFunc
    NULL,
    // pTransitionList
    trans_finish_request,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_eps_ctrl_sm)
};

static const sTransition_t tran_off_ev_initialized_idle =
{
    // event
    ev_eps_ctrl_sm_initialized,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_idle),
    // action
    NULL
};

static const sTransition_t tran_idle_ev_new_request_active_request =
{
    // event
    ev_eps_ctrl_sm_new_request,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_active_request),
    // action
    NULL
};

static const sTransition_t tran_active_request_ev_periodic_retry_request =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &eps_ctrl_sm_guard_response_timeout_elapsed,
    // target state
    HSM_UPCAST_STATE(&state_retry_request),
    // action
    NULL
};

static const sTransition_t tran_active_request_ev_response_received_finish_request =
{
    // event
    ev_eps_ctrl_sm_response_received,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_finish_request),
    // action
    NULL
};

static const sTransition_t tran_retry_request_ev_periodic_active_request =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &eps_ctrl_sm_guard_retries_left,
    // target state
    HSM_UPCAST_STATE(&state_active_request),
    // action
    NULL
};

static const sTransition_t tran_retry_request_ev_periodic_finish_request =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &eps_ctrl_sm_guard_max_retries,
    // target state
    HSM_UPCAST_STATE(&state_finish_request),
    // action
    NULL
};

static const sTransition_t tran_finish_request_ev_periodic_active_request =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &eps_ctrl_sm_guard_queue_not_empty,
    // target state
    HSM_UPCAST_STATE(&state_active_request),
    // action
    NULL
};

static const sTransition_t tran_finish_request_ev_periodic_idle =
{
    // event
    eHSM_StdEvent_Periodic,
    // guard    
    &eps_ctrl_sm_guard_queue_empty,
    // target state
    HSM_UPCAST_STATE(&state_idle),
    // action
    NULL
};

