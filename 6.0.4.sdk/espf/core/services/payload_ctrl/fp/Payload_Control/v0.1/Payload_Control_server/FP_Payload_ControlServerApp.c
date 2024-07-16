/*!
********************************************************************************************
* @file FP_Payload_ControlServerApp.c
* @brief ServerApp implementation template generator
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

#include "FP_Payload_ControlProtocolServer.h"

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "payload_ctrl.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void Payload_Control_startPayloadRequestHandlerImpl(ReqContext_t* pReqCtx,
            const Payload_ControlstartPayloadRequestData_t* pRequestData);

static void Payload_Control_stopPayloadRequestHandlerImpl(ReqContext_t* pReqCtx,
            const Payload_ControlstopPayloadRequestData_t* pRequestData);

static void Payload_Control_getPayloadInfoRequestHandlerImpl(ReqContext_t* pReqCtx,
            const Payload_ControlgetPayloadInfoRequestData_t* pRequestData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static Payload_Control_ServerApi_t Payload_ControlServerApiCtx =
{
  .Payload_Control_startPayloadRequestHandler = (pfPayload_Control_startPayloadRequestHandler_t) Payload_Control_startPayloadRequestHandlerImpl,
  .Payload_Control_stopPayloadRequestHandler = (pfPayload_Control_stopPayloadRequestHandler_t) Payload_Control_stopPayloadRequestHandlerImpl,
  .Payload_Control_getPayloadInfoRequestHandler = (pfPayload_Control_getPayloadInfoRequestHandler_t) Payload_Control_getPayloadInfoRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method Payload_Control::startPayload (ID = 0x00000000)
static void Payload_Control_startPayloadRequestHandlerImpl(ReqContext_t *pReqCtx,
            const Payload_ControlstartPayloadRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    PAYLOAD_CONTROL_payload_op_result_t eOp_result;

    // @USER_VAR_SECTION_START@Payload_Control::startPayload@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Payload_Control::startPayload@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Payload_Control::startPayload@

        if (pRequestData->u8Payload_id < PAYLOAD_COUNT)
        {
            payload_ctrl_start_cfg_t start_cfg =
            {
                .payload_args =
                {
                    .pl_args = { 0U },
                    .flags = 0U
                },
                .pointing_cfg =
                {
                    .adcs_prep_time = pRequestData->u16Adcs_prep_time,
                    .cntrl_mode = pRequestData->u8Cntrl_mode
                }
            };

            eOp_result = (PAYLOAD_CONTROL_payload_op_result_t)
                    payload_ctrl_start((payload_ctrl_payload_t) pRequestData->u8Payload_id, &start_cfg);
        }
        else
        {
            eOp_result = PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_INVALID_PL_ID;
        }

        // @USER_CODE_SECTION_END@Payload_Control::startPayload@

        respResult = Payload_Control_startPayloadResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_PAYLOAD_CONTROL, PAYLOAD_CONTROL_STARTPAYLOAD_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Payload_Control::startPayload (ID = 0x00000000)

// @START@ Request handler for method Payload_Control::stopPayload (ID = 0x00000001)
static void Payload_Control_stopPayloadRequestHandlerImpl(ReqContext_t *pReqCtx,
            const Payload_ControlstopPayloadRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    PAYLOAD_CONTROL_payload_op_result_t eOp_result;

    // @USER_VAR_SECTION_START@Payload_Control::stopPayload@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@Payload_Control::stopPayload@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Payload_Control::stopPayload@

        if (pRequestData->u8Payload_id < PAYLOAD_COUNT)
        {
            eOp_result = (PAYLOAD_CONTROL_payload_op_result_t)
                    payload_ctrl_stop(pRequestData->u8Payload_id, (pl_op_stop_mode_t) pRequestData->eReq_stop_mode);
        }
        else
        {
            eOp_result = PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_INVALID_PL_ID;
        }

        // @USER_CODE_SECTION_END@Payload_Control::stopPayload@

        respResult = Payload_Control_stopPayloadResp(
                        &respCtx,
                        eOp_result
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_PAYLOAD_CONTROL, PAYLOAD_CONTROL_STOPPAYLOAD_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Payload_Control::stopPayload (ID = 0x00000001)

// @START@ Request handler for method Payload_Control::getPayloadInfo (ID = 0x00000002)
static void Payload_Control_getPayloadInfoRequestHandlerImpl(ReqContext_t *pReqCtx,
            const Payload_ControlgetPayloadInfoRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    PAYLOAD_CONTROL_payload_info_t sInfo;

    // @USER_VAR_SECTION_START@Payload_Control::getPayloadInfo@
    uint32_t last_error_code = 0U;
    // @USER_VAR_SECTION_END@Payload_Control::getPayloadInfo@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@Payload_Control::getPayloadInfo@

        if (pRequestData->u8Payload_id < PAYLOAD_COUNT)
        {
            payload_ctrl_get_state(pRequestData->u8Payload_id,
                                   (pl_state_t *) &sInfo.ePl_state,
                                   &last_error_code);

            // this assignment is here to avoid passing a pointer to a member of a packed structure above
            sInfo.u32Last_error_code = last_error_code;
        }
        else
        {
            sInfo.ePl_state = PAYLOAD_CONTROL_PAYLOAD_STATE_ERROR;
            sInfo.u32Last_error_code = 0xFFFFFFFFU;
        }

        // @USER_CODE_SECTION_END@Payload_Control::getPayloadInfo@

        respResult = Payload_Control_getPayloadInfoResp(
                        &respCtx,
                        &sInfo
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_PAYLOAD_CONTROL, PAYLOAD_CONTROL_GETPAYLOADINFO_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method Payload_Control::getPayloadInfo (ID = 0x00000002)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void Payload_ControlServerAppInit(void)
{
    Payload_Control_registerServerApi(&Payload_ControlServerApiCtx);
}
