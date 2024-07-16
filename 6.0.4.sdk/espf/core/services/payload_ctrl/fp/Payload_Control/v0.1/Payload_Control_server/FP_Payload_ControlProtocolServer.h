/*!
********************************************************************************************
* @file FP_Payload_ControlProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface Payload_Control v0.1
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

#ifndef __FP_PAYLOAD_CONTROLPROTOCOLSERVER_H__
#define __FP_PAYLOAD_CONTROLPROTOCOLSERVER_H__

#include "FP_Payload_ControlProtocolTypes.h"

typedef void (*pfPayload_Control_startPayloadRequestHandler_t)(ReqContext_t *ctx, Payload_ControlstartPayloadRequestData_t *pRequestData);
typedef void (*pfPayload_Control_stopPayloadRequestHandler_t)(ReqContext_t *ctx, Payload_ControlstopPayloadRequestData_t *pRequestData);
typedef void (*pfPayload_Control_getPayloadInfoRequestHandler_t)(ReqContext_t *ctx, Payload_ControlgetPayloadInfoRequestData_t *pRequestData);

typedef struct {
    pfPayload_Control_startPayloadRequestHandler_t Payload_Control_startPayloadRequestHandler;
    pfPayload_Control_stopPayloadRequestHandler_t Payload_Control_stopPayloadRequestHandler;
    pfPayload_Control_getPayloadInfoRequestHandler_t Payload_Control_getPayloadInfoRequestHandler;
} Payload_Control_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_Payload_ControlProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void Payload_Control_registerServerApi(Payload_Control_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_Payload_ControlProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t Payload_Control_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes Payload_Control_startPayloadResp(
                RespContext_t* ctx,
                const PAYLOAD_CONTROL_payload_op_result_t eOp_result
);

ESSATMAC_ErrCodes Payload_Control_stopPayloadResp(
                RespContext_t* ctx,
                const PAYLOAD_CONTROL_payload_op_result_t eOp_result
);

ESSATMAC_ErrCodes Payload_Control_getPayloadInfoResp(
                RespContext_t* ctx,
                const PAYLOAD_CONTROL_payload_info_t * const sInfo
);


#endif  // #ifndef __FP_PAYLOAD_CONTROLPROTOCOLSERVER_H__
