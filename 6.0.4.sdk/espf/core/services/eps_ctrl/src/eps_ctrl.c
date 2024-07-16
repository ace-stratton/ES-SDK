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
 * @file     eps_ctrl.c
 * @brief    EPS Control Service
 *
 * @}
 */

#include "cmsis_os.h"

#include "eps_ctrl.h"
#include "eps_ctrl_queue.h"
#include "eps_ctrl_cfg.h"
#include "eps_ctrl_sm_user.h"

#include "es_cdef.h"
#include "libhsm.h"
#include "TaskMonitor.h"
#include "es_exeh.h"

/*
***************************************************************************************************
* INTERNAL DEFINES
***************************************************************************************************
*/
#define EXEH_CURRENT_MODULE_ID            eEXEHModuleID_EPS_CTRL /**< Module ID used for this file to report error events in EXEH */

#define EPS_CTRL_TASK_PERIOD_MS           (300)                  /**< Period for the EPS control task */

/*
***************************************************************************************************
* INTERNAL TYPES DEFINITION
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DEFINITION
***************************************************************************************************
*/
/**
 * @brief OS event to block asynchronously the calls to set or get a power output
 */
osEventFlagsId_t eps_ctrl_request_evt;


/*
***************************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
***************************************************************************************************
*/

/**
 * @brief EPS control thread handler */
static osThreadId_t h_eps_ctrl_task = NULL;

/** EPS control thread attributes */
static const osThreadAttr_t eps_ctrl_task_attributes =
{
  .name = "eps_ctrl_task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1664
};

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
***************************************************************************************************
*/
static inline void trigger_hsm_event(const uint32_t event_id);
static void eps_ctrl_task(void *args);
static bool eps_ctrl_cancel_req_wait(const eps_ctrl_channels_t channel, const uint32_t wait_flag);

/*
***************************************************************************************************
* EXTERNAL (NON STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
bool eps_ctrl_init(void)
{
    bool res = true;

    // Initialize the requests queue
    if (EPS_CTRL_DONE != eps_ctrl_queue_init())
    {
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_EPS_CTRL_OS_ERROR);
        res = false;
    }

    // Initialize the eps_ctrl_config
    if (EPS_CTRL_DONE != eps_ctrl_cfg_init())
    {
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_EPS_CTRL_OS_ERROR);
        res = false;
    }

    // Initialize the event flag
    eps_ctrl_request_evt = osEventFlagsNew(NULL);
    if(NULL == eps_ctrl_request_evt)
    {
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_EPS_CTRL_OS_ERROR);
        res = false;
    }

    // Initialize the task
    h_eps_ctrl_task = osThreadNew(&eps_ctrl_task, NULL, &eps_ctrl_task_attributes);
    if(NULL == h_eps_ctrl_task)
    {
        EXEH_HANDLE(eEXEHSeverity_Error, eEXEH_EPS_CTRL_OS_ERROR);
        res = false;
    }

    task_mon_set_task_policy(TASK_EPS_CTRL, TASK_MON_POLICY_MONITOR);

    // Initialize the state machine
    trigger_hsm_event(eHSM_StdEvent_Reset);

    return res;
}


void eps_ctrl_deinit(void)
{
    // Stop monitoring the task
    task_mon_set_task_policy(TASK_EPS_CTRL, TASK_MON_POLICY_DONT_CARE);

    // Initialize the state machine
    trigger_hsm_event(eHSM_StdEvent_Reset);
}




eps_ctrl_result_t eps_ctrl_set_channel_output(eps_ctrl_channels_t channel, bool state)
{
    eps_ctrl_result_t res = EPS_CTRL_FAIL;
    uint32_t wait_flag = 0;

    // Protect the queue data structures
    res = eps_ctrl_queue_add(channel, state, EPS_CTRL_REQ_SET_CH, &wait_flag);

    if (EPS_CTRL_DONE == res)
    {
        // Send state machine event
        trigger_hsm_event(ev_eps_ctrl_sm_new_request);

        // Wait for the channel flag to be set from the ESPS response callback
        uint32_t wait_res = osEventFlagsWait(eps_ctrl_request_evt, wait_flag,
                                             osFlagsWaitAny, EPS_CTRL_REQ_TIMEOUT);

        // Check for os Errors
        if (osFlagsErrorTimeout == wait_res)
        {
            eps_ctrl_cancel_req_wait(channel, wait_flag);
            res = EPS_CTRL_TIMEOUT;
        }
        else if (osFlagsError == (osFlagsError & wait_res))
        {
            eps_ctrl_cancel_req_wait(channel, wait_flag);
            res = EPS_CTRL_FAIL;
        }
        else
        {
            // Check if the last operation failed
            bool dummy_state = false; // The SET commands don't return the current state
            bool b_success = eps_ctrl_cfg_get_last_req(channel, &dummy_state);
            if(false == b_success)
            {
                res = EPS_CTRL_FAIL;
            }
        }
    }
    return res;
}

eps_ctrl_result_t eps_ctrl_get_channel_output(eps_ctrl_channels_t channel, bool* p_state)
{
    eps_ctrl_result_t res = EPS_CTRL_FAIL;
    uint32_t wait_flag = 0;

    // Protect the queue data structures
    res = eps_ctrl_queue_add(channel, true, EPS_CTRL_REQ_GET_CH, &wait_flag);

    if (EPS_CTRL_DONE == res)
    {
        // Send state machine event
        trigger_hsm_event(ev_eps_ctrl_sm_new_request);

        // Wait for the channel flag to be set from the ESPS response callback
        uint32_t wait_res = osEventFlagsWait(eps_ctrl_request_evt, wait_flag,
                                             osFlagsWaitAll, EPS_CTRL_REQ_TIMEOUT);

        // Check for os Errors
        if (osFlagsErrorTimeout == wait_res)
        {
            eps_ctrl_cancel_req_wait(channel, wait_flag);
            res = EPS_CTRL_TIMEOUT;
        }
        else if (osFlagsError == (osFlagsError & wait_res))
        {
            eps_ctrl_cancel_req_wait(channel, wait_flag);
            res = EPS_CTRL_FAIL;
        }
        else
        {
            // Check if the last operation failed and update the p_state
            bool b_success = eps_ctrl_cfg_get_last_req(channel, p_state);
            if(false == b_success)
            {
                res = EPS_CTRL_FAIL;
            }
        }
    }
    return res;
}

void eps_ctrl_response_received_notif(void)
{
    trigger_hsm_event(ev_eps_ctrl_sm_response_received);
}

void eps_ctrl_unblock_user_thread(void)
{
    if (false != eps_ctrl_cfg_service_lock_get())
    {
        eps_ctrl_channels_t active_request_channel;
        uint32_t            active_wait_flag;

        if (false != eps_ctrl_cfg_get_channel_and_flag(&active_request_channel, &active_wait_flag))
        {
            const eps_ctrl_request_t* p_active_request = eps_ctrl_queue_find(active_request_channel, active_wait_flag);
            if ((NULL != p_active_request) && (false == p_active_request->wait_cancelled))
            {
                // Trigger the active request flag
                osEventFlagsSet(eps_ctrl_request_evt, active_wait_flag);
            }
            else
            {
                // There is no thread waiting on the currently processed flag with a request for the currently processed channel
            }
        }

        eps_ctrl_cfg_service_lock_free();
    }
}

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
/**
 * @brief Wrapper to trigger an event using the mutex
 *
 * @param event_id ID of an HSM transition
 */
static inline void trigger_hsm_event(const uint32_t event_id)
{
    if (false != eps_ctrl_cfg_service_lock_get())
    {
        HSM_TriggerEvent(eps_ctrl_sm_instance, event_id);
        eps_ctrl_cfg_service_lock_free();
    }
}

/**
 * @brief  EPS Control task that triggers periodic SM events
 */
static void eps_ctrl_task(void * args)
{
    (void) args;
    // Loop triggering the periodic events in the state machine

    // Initialize the State Machine once the OS Kernel is initialized
    trigger_hsm_event(ev_eps_ctrl_sm_initialized);

    // Trigger new_request event if there are untreated requests in the queue
    if(false == eps_ctrl_queue_is_empty())
    {
        trigger_hsm_event(ev_eps_ctrl_sm_new_request);
    }

    for (;;)
    {
        // execute periodic SM activities...
        (void) trigger_hsm_event(eHSM_StdEvent_Periodic);

        osDelay(EPS_CTRL_TASK_PERIOD_MS);

        TaskMonitor_IamAlive(TASK_EPS_CTRL);
        vApplicationLowStackCheck(TASK_EPS_CTRL);
    }
}

/**
 * @brief  Marks a queued request that no notification is needed upon its completion.
 *
 * @param  channel   Channel for which the request has been sent. Part of the search "key" in the request queue
 * @param  wait_flag Wait event flag related to the request. Part of the search "key" in the request queue
 *
 * @note   This cancellation is needed for cases when the wait OS API returns unexpectedly
 *         (e.g. due to an error or timeout). If not done, completion notification logic will
 *         erroneously set an event which may be accepted as a valid one on later wait operations
 */
static bool eps_ctrl_cancel_req_wait(const eps_ctrl_channels_t channel, const uint32_t wait_flag)
{
    bool res = false;
    if (false != eps_ctrl_cfg_service_lock_get())
    {
        eps_ctrl_request_t* p_req = eps_ctrl_queue_find(channel, wait_flag);
        if (NULL != p_req)
        {
            p_req->wait_cancelled = true;
            // This is a robustness measure for the case when a notification is sent before the "cancelled"
            // flag for the request has been updated. In this case the requesting thread is no longer waiting
            // on the event which is already set
            (void)osEventFlagsClear(eps_ctrl_request_evt, wait_flag);

            res = true;
        }

        eps_ctrl_cfg_service_lock_free();
    }

    return res;
}
