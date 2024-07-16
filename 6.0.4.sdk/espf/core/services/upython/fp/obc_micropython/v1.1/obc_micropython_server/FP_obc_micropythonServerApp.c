/*!
********************************************************************************************
* @file FP_obc_micropythonServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface obc_micropython v1.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#include "FP_obc_micropythonProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include "ffconf.h"
#include "trace.h"
#include "es_exeh.h"
#include "assertions.h"

#include "upy.h"
#include "upy_obc_port.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
static void on_send_result_cbk(eObcPortResult_t result, const uint32_t duration_in_ms,
                               const uint8_t script_id);
// @END_USER@ USER_LOCAL_FUNC_DECL
static void obc_micropython_RequestScriptExecutionRequestHandlerImpl(ReqContext_t* pReqCtx,
            const obc_micropythonRequestScriptExecutionRequestData_t* pRequestData);

static void obc_micropython_GetScriptExecStatusRequestHandlerImpl(ReqContext_t* pReqCtx,
            const obc_micropythonGetScriptExecStatusRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!

const OBC_MICROPYTHON_Result_t aResultMap[UPY_CNT] = {
    OBC_MICROPYTHON_RESULT_OK,                 // UPY_OK
    OBC_MICROPYTHON_RESULT_FAIL,               // UPY_ERROR
    OBC_MICROPYTHON_RESULT_QUEUE_FULL,         // UPY_QUEUE_FULL
    OBC_MICROPYTHON_RESULT_FAIL,               // UPY_WRONG_PARAMS
    OBC_MICROPYTHON_RESULT_PROCESSING,         // UPY_PROCESSING
    OBC_MICROPYTHON_RESULT_PENDING,            // UPY_PENDING
    OBC_MICROPYTHON_RESULT_NOT_FOUND_IN_QUEUE, // UPY_SCRIPT_NOT_FOUND
    OBC_MICROPYTHON_RESULT_TIMED_OUT           // UPY_SCRIPT_TIMED_OUT
};
// @END_USER@ USER_LOCAL_VARS_DECL

static obc_micropython_ServerApi_t obc_micropythonServerApiCtx =
{
  .obc_micropython_RequestScriptExecutionRequestHandler = (pfobc_micropython_RequestScriptExecutionRequestHandler_t) obc_micropython_RequestScriptExecutionRequestHandlerImpl,
  .obc_micropython_GetScriptExecStatusRequestHandler = (pfobc_micropython_GetScriptExecStatusRequestHandler_t) obc_micropython_GetScriptExecStatusRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL

static void on_send_result_cbk(eObcPortResult_t result, const uint32_t duration_in_ms,
                               const uint8_t script_id)
{
    sScriptData_t script_data;

    eObcPortResult_t res = upy_get_script_status(script_id, &script_data);
    // update the status if the element is still in the status array
    if (UPY_OK == res)
    {
        script_data.eScriptStatus   = result;
        script_data.u32DurationInMs = duration_in_ms;

        res = upy_set_script_status(script_id, &script_data);
    }

    if (UPY_OK != res)
    {
        if (UPY_SCRIPT_NOT_FOUND == res)
        {
            // status is ignored as the element in the script array is already
            // overwritten
            EXEH_HANDLE_EX(eEXEHSeverity_Warning, eEXEHModuleID_UPYTHON,
                        EXEH_UPYTHON_CANT_FIND_SCRIPT_CONTEXT)

            ES_TRACE_DEBUG("Script not found ScriptID = %d", script_id);
        }
        else
        {
            EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_UPYTHON,
                        EXEH_UPYTHON_ERROR)
            ES_TRACE_DEBUG(
                "Error Getting/Setting the status of a script. ScriptID = %d, "
                "ErrorID "
                "= %d",
                script_id, res);
        }
    }
}
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method obc_micropython::RequestScriptExecution (ID = 0x00000001)
static void obc_micropython_RequestScriptExecutionRequestHandlerImpl(ReqContext_t *pReqCtx,
            const obc_micropythonRequestScriptExecutionRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Script_id;
    OBC_MICROPYTHON_Result_t eOp_result;

    // @USER_VAR_SECTION_START@obc_micropython::RequestScriptExecution@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@obc_micropython::RequestScriptExecution@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@obc_micropython::RequestScriptExecution@

        // check if the fidl command size is correct(equal to FATFS configuration for the system)
        static_assert(FF_MAX_LFN == sizeof(pRequestData->strScript_full_name));

        // cast of script file name length is ok because it shall be within
        // FF_MAX_LFN which is one byte
        eObcPortResult_t res = upy_req_script_execution(
            pRequestData->strScript_full_name,
            (uint8_t)strnlen(pRequestData->strScript_full_name, FF_MAX_LFN), pRequestData->u32Timeout_ms,
            &on_send_result_cbk, &u8Script_id);

        eOp_result = aResultMap[res];

        // @USER_CODE_SECTION_END@obc_micropython::RequestScriptExecution@

        respResult = obc_micropython_RequestScriptExecutionResp(
                        &respCtx,
                        u8Script_id,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_MICROPYTHON, OBC_MICROPYTHON_REQUESTSCRIPTEXECUTION_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method obc_micropython::RequestScriptExecution (ID = 0x00000001)

// @START@ Request handler for method obc_micropython::GetScriptExecStatus (ID = 0x00000002)
static void obc_micropython_GetScriptExecStatusRequestHandlerImpl(ReqContext_t *pReqCtx,
            const obc_micropythonGetScriptExecStatusRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    char strScript_full_name[47];
    uint8_t u8Script_full_nameSize;
    OBC_MICROPYTHON_Result_t eOp_result;
    OBC_MICROPYTHON_stime_t sRequested_time;
    OBC_MICROPYTHON_stime_t sTime_started;
    uint32_t u32Duration_ms;

    // @USER_VAR_SECTION_START@obc_micropython::GetScriptExecStatus@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@obc_micropython::GetScriptExecStatus@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@obc_micropython::GetScriptExecStatus@

        sScriptData_t script_data;

        eObcPortResult_t res = upy_get_script_status(pRequestData->u8Script_id, &script_data);

        // check if the fidl command size is correct(equal to FATFS configuration for the system)
        static_assert(FF_MAX_LFN == sizeof(strScript_full_name));

        if (UPY_OK == res)
        {
            eOp_result = aResultMap[script_data.eScriptStatus];

            uint32_t name_length = strnlen(script_data.pName, FF_MAX_LFN);

            CRIT_ASSERT(name_length < UINT8_MAX);
            u8Script_full_nameSize = (uint8_t)name_length;

            memset(strScript_full_name, '\0', sizeof(strScript_full_name));
            strncpy(strScript_full_name, script_data.pName, FF_MAX_LFN); // NOSONAR src will never be longer than dest

            static_assert(sizeof(sys_time_t) == sizeof(OBC_MICROPYTHON_stime_t));

            memcpy(&sRequested_time, &script_data.sTimeRequested, sizeof(OBC_MICROPYTHON_stime_t));
            memcpy(&sTime_started, &script_data.sTimeStarted, sizeof(OBC_MICROPYTHON_stime_t));
            u32Duration_ms = script_data.u32DurationInMs;
        }
        else
        {
            eOp_result             = OBC_MICROPYTHON_RESULT_NOT_FOUND_IN_QUEUE;
            strScript_full_name[0] = '\0';
            u8Script_full_nameSize = 1;
            memset(&sRequested_time, 0, sizeof(OBC_MICROPYTHON_stime_t));
            memset(&sTime_started, 0, sizeof(OBC_MICROPYTHON_stime_t));
            u32Duration_ms = 0;
        }

        // @USER_CODE_SECTION_END@obc_micropython::GetScriptExecStatus@

        respResult = obc_micropython_GetScriptExecStatusResp(
                        &respCtx,
                        strScript_full_name,
                        u8Script_full_nameSize,
                        eOp_result,
                        &sRequested_time,
                        &sTime_started,
                        u32Duration_ms
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_MICROPYTHON, OBC_MICROPYTHON_GETSCRIPTEXECSTATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method obc_micropython::GetScriptExecStatus (ID = 0x00000002)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void obc_micropythonServerAppInit(void)
{
    obc_micropython_registerServerApi(&obc_micropythonServerApiCtx);
}
