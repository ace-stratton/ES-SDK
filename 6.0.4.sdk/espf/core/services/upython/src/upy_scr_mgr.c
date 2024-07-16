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
 * @file upy_scr.c
 * @brief upython script management implementation
 *
 * @}
 * @}
 */

#include "cmsis_os2.h"
#include <string.h>

#include "debug.h"
#include "es_exeh.h"

#include "upy.h"
#include "upy_cfg.h"
#include "upy_scr_mgr.h"

#define SYS_TIME_INIT \
    {                 \
        0, 0, 0, 0    \
    }

#define SCRIPT_DATA_INIT                                              \
    {                                                                 \
        (uint32_t)0, NULL, (uint32_t)0, SYS_TIME_INIT, SYS_TIME_INIT, \
            UPY_ERROR, ""                                             \
    }

static sExecScriptDescription_t ScriptHndls[UPY_SCRIPT_QUEUE_LEN] = {
    {SCRIPT_DATA_INIT,  INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID},
    { SCRIPT_DATA_INIT, INVALID_SCRIPT_ID}
};

static uint8_t g_current_script_id = 0;

/** @brief Mutex handle provided by the OS. Used for synchronization of
 * adding/removing micropython scritps for execution from different contexts */
osMutexId_t upy_scr_lock_id;

upy_scr_mgr_return_t upy_scr_mgr_add(const char *const p_name, uint8_t len, uint32_t time_out,
                                     pfMicropythonExecScript_Cbk_t p_on_send_result_cbk,
                                     uint8_t *const                p_script_id)
{
    upy_scr_mgr_return_t result = UPY_SCR_MGR_ERROR;
    sys_time_t           time_of_request;

    if ((NULL != p_name) && (NULL != p_script_id) &&
        (NULL != p_on_send_result_cbk))
    {
        g_current_script_id += 1;

        // make sure invalid script id is not used.
        if (INVALID_SCRIPT_ID == g_current_script_id)
        {
            g_current_script_id = 0;
        }

        (void)sys_time_get(&time_of_request);

        uint8_t script_idx = g_current_script_id % UPY_SCRIPT_QUEUE_LEN;

        osStatus_t eMutexRes = osMutexAcquire(upy_scr_lock_id, osWaitForever);

        if (osOK == eMutexRes)
        {
            sScriptData_t *const psScriptData =
                &ScriptHndls[script_idx].sScriptData;
            if (0 < len)
            {
                memcpy(psScriptData->pName, p_name, len);
                psScriptData->pName[len] = '\0';
            }

            ScriptHndls[script_idx].u8ScriptId = g_current_script_id;
            psScriptData->u32TimeOut           = time_out;
            psScriptData->pfOnSendResultCbk    = p_on_send_result_cbk;
            psScriptData->eScriptStatus        = UPY_PENDING;
            psScriptData->u32DurationInMs      = 0;

            memcpy(&psScriptData->sTimeRequested, &time_of_request,
                   sizeof(sys_time_t));
            memset(&psScriptData->sTimeStarted, 0, sizeof(sys_time_t));

            osMutexRelease(upy_scr_lock_id);
            *p_script_id = g_current_script_id;
            result       = UPY_SCR_MGR_OK;
        }
        else
        {
            g_current_script_id = INVALID_SCRIPT_ID;
            result              = UPY_SCR_MGR_MUTEX_ERROR;
        }
    }
    else
    {
        result = UPY_SCR_MGR_WRONG_PARAMS;
    }

    return result;
}

upy_scr_mgr_return_t upy_scr_mgr_get_status(uint8_t script_id, sScriptData_t *const p_script_data)
{
    upy_scr_mgr_return_t res         = UPY_SCR_MGR_ERROR;
    uint8_t              u8ScriptIdx = script_id % UPY_SCRIPT_QUEUE_LEN;

    if (NULL != p_script_data)
    {
        osStatus_t eMutexRes = osMutexAcquire(upy_scr_lock_id, osWaitForever);

        if (osOK == eMutexRes)
        {
            // make sure that the element in the array is still not overwritten
            // by new element
            if (ScriptHndls[u8ScriptIdx].u8ScriptId == script_id)
            {
                memcpy(p_script_data, &ScriptHndls[u8ScriptIdx].sScriptData,
                       sizeof(sScriptData_t));
                res = UPY_SCR_MGR_OK;
            }
            else
            {
                res = UPY_SCR_MGR_SCRIPT_NOT_FOUND;
            }

            osMutexRelease(upy_scr_lock_id);
        }
        else
        {
            res = UPY_SCR_MGR_MUTEX_ERROR;
        }
    }
    else
    {
        res = UPY_SCR_MGR_WRONG_PARAMS;
    }

    return res;
}

upy_scr_mgr_return_t upy_scr_mgr_set_status(uint8_t                    script_id,
                                            const sScriptData_t *const p_new_script_data)
{
    upy_scr_mgr_return_t res         = UPY_SCR_MGR_ERROR;
    uint8_t              u8ScriptIdx = script_id % UPY_SCRIPT_QUEUE_LEN;

    if (NULL != p_new_script_data)
    {
        osStatus_t eMutexRes = osMutexAcquire(upy_scr_lock_id, osWaitForever);

        if (osOK == eMutexRes)
        {
            // make sure that the element in the array is still not overwritten
            // by new element
            if (ScriptHndls[u8ScriptIdx].u8ScriptId == script_id)
            {
                memcpy(&ScriptHndls[u8ScriptIdx].sScriptData, p_new_script_data,
                       sizeof(sScriptData_t));
                res = UPY_SCR_MGR_OK;
            }
            else
            {
                res = UPY_SCR_MGR_SCRIPT_NOT_FOUND;
            }

            osMutexRelease(upy_scr_lock_id);
        }
        else
        {
            res = UPY_SCR_MGR_MUTEX_ERROR;
        }
    }
    else
    {
        res = UPY_SCR_MGR_WRONG_PARAMS;
    }

    return res;
}

void upy_scr_mgr_init(osMutexId_t mutex_id)
{
    upy_scr_lock_id = mutex_id;

    if (NULL == mutex_id)
    {
        EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_UPYTHON,
                       EXEH_UPYTHON_NO_VALID_MUTEX)
    }
}
