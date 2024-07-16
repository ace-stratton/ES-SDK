/*!
********************************************************************************************
* @file FP_obc_micropythonProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_OBC_MICROPYTHONPROTOCOLSERVER_H__
#define __FP_OBC_MICROPYTHONPROTOCOLSERVER_H__

#include "FP_obc_micropythonProtocolTypes.h"

typedef void (*pfobc_micropython_RequestScriptExecutionRequestHandler_t)(ReqContext_t *ctx, obc_micropythonRequestScriptExecutionRequestData_t *pRequestData);
typedef void (*pfobc_micropython_GetScriptExecStatusRequestHandler_t)(ReqContext_t *ctx, obc_micropythonGetScriptExecStatusRequestData_t *pRequestData);

typedef struct {
    pfobc_micropython_RequestScriptExecutionRequestHandler_t obc_micropython_RequestScriptExecutionRequestHandler;
    pfobc_micropython_GetScriptExecStatusRequestHandler_t obc_micropython_GetScriptExecStatusRequestHandler;
} obc_micropython_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_obc_micropythonProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void obc_micropython_registerServerApi(obc_micropython_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_obc_micropythonProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t obc_micropython_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes obc_micropython_RequestScriptExecutionResp(
                RespContext_t* ctx,
                const uint8_t u8Script_id,
                const OBC_MICROPYTHON_Result_t eOp_result
);

ESSATMAC_ErrCodes obc_micropython_GetScriptExecStatusResp(
                RespContext_t* ctx,
                char * const strScript_full_name,
                const uint8_t u8Script_full_nameSize,
                const OBC_MICROPYTHON_Result_t eOp_result,
                const OBC_MICROPYTHON_stime_t * const sRequested_time,
                const OBC_MICROPYTHON_stime_t * const sTime_started,
                const uint32_t u32Duration_ms
);


#endif  // #ifndef __FP_OBC_MICROPYTHONPROTOCOLSERVER_H__
