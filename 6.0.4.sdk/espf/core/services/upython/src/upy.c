/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup upython
 * @{
 *
 * @file upy.c
 * @brief upython service OS tasks implementation
 *
 * @}
 * @}
 */

#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "debug.h"

#include <string.h>

#include "queue.h"

#include "SdMngr.h"
#include "upy_obc_port.h"
#include "FP_obc_micropythonServerApp.h"
#include "timer.h"
#include "es_exeh.h"

#include <upy.h>
#include <upy_cfg.h>
#include <upy_scr_mgr.h>
#include <TaskMonitor.h>

#include "ESSA_Stack_TP_Layer.h"

#include "py/runtime.h"

#define UPY_UNBLOCK_THREAD_FLAG (1U)
#define UPY_MIN_TIMEOUT_MS      (1U)

typedef struct
{
    uint8_t       id;
    sScriptData_t data;
} processing_script_info_t;

const sSdMngr_rlf_cfg_t roll_file_name_cfg = {
    .u32MaxSizeInBytes = UPY_LOG_MAX_SIZE,
    .acNamePattern     = UPY_LOG_TEMPLATE,
    .u8MarkerPos       = UPY_LOG_MARKER_POS,
    .u8IndexPos        = UPY_LOG_INDEX_POS,
    .u8FilesCount      = UPY_LOG_SLOTS,
    .cActiveMarker     = UPY_LOG_ACTIVE_MARKER,
    .cInactiveMarker   = UPY_LOG_INACTIVE_MARKER
};

/** @brief Attributes used for creating the mutex "upy_lock_id"*/
const osMutexAttr_t upy_lock_attr = {
    "upy_mutex",      // human readable mutex name
    osMutexRecursive, // attr_bits
    NULL,             // memory for control block
    0U                // size for control block
};

// static memory allocation for timer and task objects.
StaticTimer_t timeout_timer_static_mem;
StaticTask_t  upy_task_static_mem;
uint8_t       upy_task_stack_static[UPY_STACK_SIZE];

const osTimerAttr_t upy_script_timeout_timer_attr = {
    .name      = "upy_scritp_timeout_timer",
    .attr_bits = 1,
    .cb_mem    = &timeout_timer_static_mem,
    .cb_size   = sizeof(timeout_timer_static_mem)
};

static sSdMngr_rlf_ctx_t roll_file_name_ctx = { .acFileName    = "",
                                                .psCfg         = &roll_file_name_cfg,
                                                .u8CurrentIdx  = 0,
                                                .bIsFileOpened = false };

static osThreadId_t h_upy_task = NULL;

static const osThreadAttr_t upy_task_attributes = {
    .name       = "upythonTask",
    .priority   = (osPriority_t)osPriorityNormal,
    .stack_size = UPY_STACK_SIZE,
    .cb_mem     = &upy_task_static_mem,
    .cb_size    = sizeof(upy_task_static_mem),
    .stack_mem  = &upy_task_stack_static,
    .stack_size = sizeof(upy_task_stack_static)
};

static StaticQueue_t script_queue_cb;

static uint8_t script_queue_data[UPY_SCRIPT_QUEUE_LEN];

static osTimerId_t timeout_timer_id;

static processing_script_info_t processsing_script_info = {
    .id = INVALID_SCRIPT_ID
};

/** @brief Queue used to organize the sequence of executing requested
 * micropython scripts*/
osMessageQueueId_t h_script_queue;

const osMessageQueueAttr_t script_queue_attr = { .name      = NULL,
                                                 .attr_bits = 0,
                                                 .mq_mem    = script_queue_data,
                                                 .mq_size =
                                                     sizeof(script_queue_data),
                                                 .cb_mem = &script_queue_cb,
                                                 .cb_size =
                                                     sizeof(script_queue_cb) };

osMutexId_t upy_lock_id;

static void upy_task(void *param);

/**
 * \brief Callback function to be called when the timer for monitoring the script execution is elapsed.
 *
 * \param argument - the argument is not used.
 */
static void timeout_callback(void *argument);

void upy_init(void)
{
    upy_lock_id = osMutexNew(&upy_lock_attr);
    upy_scr_mgr_init(upy_lock_id);
    h_script_queue = osMessageQueueNew(UPY_SCRIPT_QUEUE_LEN, sizeof(uint8_t),
                                       &script_queue_attr);

    if (NULL == h_script_queue)
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_UPYTHON,
                       EXEH_UPYTHON_CANT_CREATE_QUEUE)
    }

    timeout_timer_id = osTimerNew(&timeout_callback, osTimerOnce, NULL, &upy_script_timeout_timer_attr);
    if (NULL == timeout_timer_id)
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_UPYTHON,
                       EXEH_UPYTHON_CANT_CREATE_QUEUE)
    }

    TaskMonitor_TaskInitialized(TASK_MONITOR_UPYTHON);
    task_mon_set_task_policy(TASK_MONITOR_UPYTHON, TASK_MON_POLICY_DONT_CARE);

    upy_task_start();
}

void upy_task_start(void)
{
    h_upy_task = osThreadNew((osThreadFunc_t)upy_task, NULL, &upy_task_attributes);
    if (NULL == h_upy_task)
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_UPYTHON,
                       EXEH_UPYTHON_CANT_FIND_SCRIPT_CONTEXT)
    }
}

eObcPortResult_t upy_req_script_execution(const char *const p_script_name, uint8_t name_length,
                                          uint32_t                      time_out,
                                          pfMicropythonExecScript_Cbk_t p_script_cbk,
                                          uint8_t *const                p_script_id)
{
    eObcPortResult_t result = UPY_QUEUE_FULL;
    *p_script_id            = INVALID_SCRIPT_ID;

    if (osOK == osMutexAcquire(upy_lock_id, osWaitForever))
    {
        uint32_t u32QueueSpace = osMessageQueueGetSpace(h_script_queue);

        // if we have place in the queue
        if (0 < u32QueueSpace)
        {
            upy_scr_mgr_return_t upy_scr_mgr_res =
                upy_scr_mgr_add(p_script_name, name_length, time_out,
                                p_script_cbk, p_script_id);

            if (UPY_SCR_MGR_OK == upy_scr_mgr_res)
            {
                osStatus_t QueueRes = osMessageQueuePut(
                    h_script_queue, (const void *)p_script_id, 0U, 0U);
                if (osOK == QueueRes)
                {
                    result = UPY_OK;
                }
            }
            else
            {
                result = UPY_ERROR;
            }
        }

        osMutexRelease(upy_lock_id);
    }
    else
    {
        result = UPY_ERROR;
    }

    return result;
}

eObcPortResult_t upy_get_script_status(uint8_t script_id, sScriptData_t *const p_script_data)
{
    eObcPortResult_t     res = UPY_ERROR;
    upy_scr_mgr_return_t upy_mgr_scr_res = upy_scr_mgr_get_status(script_id, p_script_data);
    if (UPY_SCR_MGR_OK == upy_mgr_scr_res)
    {
        res = UPY_OK;
    }
    else
    {
        if (UPY_SCR_MGR_SCRIPT_NOT_FOUND == upy_mgr_scr_res)
        {
            res = UPY_SCRIPT_NOT_FOUND;
        }
        else
        {
            EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_UPYTHON,
                           EXEH_UPYTHON_ERROR)
        }
    }

    return res;
}

eObcPortResult_t upy_set_script_status(uint8_t script_id, const sScriptData_t *const p_script_data)
{
    eObcPortResult_t     res = UPY_ERROR;
    upy_scr_mgr_return_t upy_mgr_scr_res = upy_scr_mgr_set_status(script_id, p_script_data);
    if (UPY_SCR_MGR_OK == upy_mgr_scr_res)
    {
        res = UPY_OK;
    }
    else
    {
        if (UPY_SCR_MGR_SCRIPT_NOT_FOUND == upy_mgr_scr_res)
        {
            res = UPY_SCRIPT_NOT_FOUND;
        }
        else
        {
            EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_UPYTHON,
                           EXEH_UPYTHON_ERROR)
        }
    }

    return res;
}

/*-------------------  static function implementation ------------------------*/

static void upy_task(void *param) // NOSONAR
{
    (void)param;

    while (true)
    {
        while (osOK == osMessageQueueGet(h_script_queue, &processsing_script_info.id, NULL,
                                         UPY_TASK_PERIOD_MS))
        {
            eObcPortResult_t res = upy_get_script_status(processsing_script_info.id, &processsing_script_info.data);

            // ensure we always have a non-zero timeout value
            if (0 == processsing_script_info.data.u32TimeOut)
            {
                processsing_script_info.data.u32TimeOut = UPY_MIN_TIMEOUT_MS;
            }

            if (UPY_OK == res)
            {
                eObcPortResult_t result = UPY_ERROR;
                (void)sys_time_get(&processsing_script_info.data.sTimeStarted);

                if (SDMNGR_CARD_STATE_READY ==
                    SdMngr_GetCardState())
                {
                    (void)SdMngr_rlf_open(&roll_file_name_ctx);
                    processsing_script_info.data.eScriptStatus = UPY_PROCESSING;

                    res = upy_set_script_status(processsing_script_info.id, &processsing_script_info.data);

                    if (UPY_OK == res)
                    {
                        osStatus_t timeout_timer_status = osTimerStart(
                            timeout_timer_id,
                            pdMS_TO_TICKS(processsing_script_info.data.u32TimeOut)); // start timeout for execution
                                                                                     // of this script

                        if (osOK != timeout_timer_status)
                        {
                            processsing_script_info.data.eScriptStatus = UPY_ERROR;
                            res                                        = upy_set_script_status(processsing_script_info.id, &processsing_script_info.data);

                            EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_UPYTHON,
                                           EXEH_UPYTHON_ERROR)
                        }
                        else
                        {
                            timer_handle_t h_timer;
                            timer_start(&h_timer);

                            result =
                                uPyRun(processsing_script_info.data.pName,
                                       (uint8_t)strnlen(processsing_script_info.data.pName, FF_MAX_LFN));
                            osTimerStop(timeout_timer_id); // the timeout is stopped because the
                                                           // operation is successful
                            uint32_t u32Duration = timer_get_elapsed_time(&h_timer);
                            processsing_script_info.data.pfOnSendResultCbk(result, u32Duration,
                                                                           processsing_script_info.id);
                        }
                    }
                    (void)SdMngr_rlf_close(&roll_file_name_ctx);
                }
                else
                {
                    processsing_script_info.data.eScriptStatus = UPY_ERROR;
                    res                                        = upy_set_script_status(processsing_script_info.id, &processsing_script_info.data);

                    EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_UPYTHON,
                                   EXEH_UPYTHON_SDCARD_NOT_READY)
                }
            }

            if (UPY_SCRIPT_NOT_FOUND == res)
            {
                EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_UPYTHON,
                               EXEH_UPYTHON_CANT_FIND_SCRIPT_CONTEXT)
            }
            else if (UPY_OK != res)
            {
                EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_UPYTHON,
                               EXEH_UPYTHON_ERROR)
            }
        }
        vApplicationLowStackCheck(TASK_MONITOR_UPYTHON);
        processsing_script_info.id = INVALID_SCRIPT_ID;
    }
}

static void timeout_callback(void *argument) // NOSONAR
{
    (void)argument;

    ES_TRACE_WARN("[Python VM abort signal]");
    mp_sched_vm_abort();

    if (INVALID_SCRIPT_ID != processsing_script_info.id)
    {
        processsing_script_info.data.pfOnSendResultCbk(UPY_SCRIPT_TIMED_OUT, processsing_script_info.data.u32TimeOut,
                                                       processsing_script_info.id);
    }
}

FRESULT upy_write_line_to_file(const char *const line)
{
    UINT    bytesWritten = 0U;
    FRESULT res          = SdMngr_rlf_write(&roll_file_name_ctx, line, strlen(line),
                                            &bytesWritten);

    return res;
}

void upy_prepare_thread_wait(void)
{
    (void)osThreadFlagsClear(UPY_UNBLOCK_THREAD_FLAG);
}

eThreadBlockEvt_t upy_thread_wait_for_event(uint32_t time_out_ms)
{
    eThreadBlockEvt_t result = THREADBLOCKEVT_ERROR;

    uint32_t os_thread_flags_result =
        osThreadFlagsWait(UPY_UNBLOCK_THREAD_FLAG, osFlagsWaitAll, time_out_ms);

    if ((os_thread_flags_result & UPY_UNBLOCK_THREAD_FLAG) ==
        UPY_UNBLOCK_THREAD_FLAG)
    {
        result = THREADBlOCKEVT_WAITFINISHED;
    }
    else if ((osStatus_t)os_thread_flags_result == osErrorTimeout)
    {
        result = THREADBLOCKEVT_WAITTIMEOUT;
    }

    return result;
}

void upy_release_thread_wait(void)
{
    (void)osThreadFlagsSet(h_upy_task, UPY_UNBLOCK_THREAD_FLAG);
}

/***end of file***/
