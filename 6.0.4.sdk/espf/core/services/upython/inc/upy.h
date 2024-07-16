/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef UPYTHON_H_
#define UPYTHON_H_

#include "sys_time.h"
#include "upy_obc_port.h"
#include "ffconf.h"
#include "timer.h"
#include "ESSA_Stack_TP_Layer.h"

#define INVALID_SCRIPT_ID ((uint8_t)0xFFU)

/**
 * @brief prototype of a function used for callback from Micropython after
 * script execution
 *
 * @param result Result of the script
 * @param DurationInMs
 * @param u8ScriptId
 */
typedef void (*pfMicropythonExecScript_Cbk_t)(eObcPortResult_t result,
                                              const uint32_t   DurationInMs,
                                              const uint8_t    u8ScriptId);

/**
 * @struct
 * @brief Used to store all information of a requested script
 */
typedef struct
{
    uint32_t                      u32TimeOut;
    pfMicropythonExecScript_Cbk_t pfOnSendResultCbk; // callback called after execution of the script
    uint32_t                      u32DurationInMs;
    sys_time_t                    sTimeRequested;
    sys_time_t                    sTimeStarted;
    eObcPortResult_t              eScriptStatus;
    char                          pName[FF_MAX_LFN];
} sScriptData_t;

/**
 * @struct
 * @brief Script descripor
 *
 */
typedef struct
{
    sScriptData_t sScriptData;
    uint8_t       u8ScriptId;
} sExecScriptDescription_t;

/**
 * @brief Initialization of Micropython environment
 *
 */
void upy_init(void);

/**
 * @fn void upy_task_start(void)
 * @brief function to initialize the data of upython module and create and
 * execute a task thread for micropython execution
 *
 */
void upy_task_start(void);

/**
 * uint32_t, pfMicropythonExecScript_Cbk_t, uint8_t* const)
 *
 * @brief This function is trying to execute existing script. The script can be
 * a module in the file system or frozen module hard coded in the obc
 *
 * @param p_script_name : The file name of the script. In case it's without the
 * path it will be searched in the default include paths
 *
 * @param name_length : Length of the script file name not including the null
 * terminator
 *
 * @param time_out : Timeout for the script. In case the
 * script execution time is bigger than this timeout the script will be
 * terminated.
 *
 * @param p_script_cbk : Pointer to function which will be called in
 * case the script finish its execution
 *
 * @param p_script_id : Out parameter. The id of the script. By this Id status
 * information of the script can be retrieved later.
 *
 * @return
 *          UPY_QUEUE_FULL : in case there is no more space in
 * the queue for script executions.
 *          UPY_OK : in case the script has been inserted in the queue
 *          UPY_ERROR: error with execution of the function
 */
eObcPortResult_t upy_req_script_execution(const char *const p_script_name, uint8_t name_length,
                                          uint32_t                      time_out,
                                          pfMicropythonExecScript_Cbk_t p_script_cbk,
                                          uint8_t *const                p_script_id);

/**
 * @brief Function which retrieves the status of script based on input script
 * identifier
 *
 * @param script_id - identifier of the script whcih we want to check
 * @param p_script_data - pointer to returned status data with sScriptData_t
 * type
 * @return
 * UPY_ERROR : in case of unknown problem with getting the script status
 * UPY_OK : on successful operation
 * UPY_SCRIPT_NOT_FOUND : in case the script is not found in the queue
 */
eObcPortResult_t upy_get_script_status(uint8_t script_id, sScriptData_t *const p_script_data);

/**
 * *const p_script_data)
 * @brief Function which updates the status of script based on input script
 * identifier
 *
 * @param script_id - identifier of the script whcih we want to check
 * @param p_script_data - pointer to returned status data with sScriptData_t
 * type
 * @return
 * UPY_ERROR : in case of unknown problem while setting the script status
 * UPY_OK : on successful operation
 * UPY_SCRIPT_NOT_FOUND : in case the script is not found in the queue
 */
eObcPortResult_t upy_set_script_status(uint8_t script_id, const sScriptData_t *const p_script_data);

/**
 * @brief API to provided to release the tread. Used together with
 * upy_prepare_thread_wait() and upy_thread_wait_for_event() APIs
 *
 */
void upy_release_thread_wait(void);

/**
 * @brief Blocks the thread until upy_release_thread_wait is invoked.
 *
 * @param time_out_ms Timeout time to wait until resuming the thread with error
 * @return
 */
eThreadBlockEvt_t upy_thread_wait_for_event(uint32_t time_out_ms);

/**
 * @brief This function is used to prepare the thread for blocking. This will
 * clear all needed flags. Must be invoked just before upy_thread_wait_for_event
 * API
 *
 */
void upy_prepare_thread_wait(void);

#endif /* UPYTHON_CFG_H_ */

/***end of file***/
