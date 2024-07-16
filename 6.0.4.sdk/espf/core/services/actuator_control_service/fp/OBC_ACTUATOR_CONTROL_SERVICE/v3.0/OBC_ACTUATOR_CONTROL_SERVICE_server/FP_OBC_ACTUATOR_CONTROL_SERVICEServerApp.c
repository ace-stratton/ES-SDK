/*!
********************************************************************************************
* @file FP_OBC_ACTUATOR_CONTROL_SERVICEServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface OBC_ACTUATOR_CONTROL_SERVICE v3.0
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

#include "FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include <actuator_control_service.h>
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void OBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static OBC_ACTUATOR_CONTROL_SERVICE_ServerApi_t OBC_ACTUATOR_CONTROL_SERVICEServerApiCtx =
{
  .OBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandler = (pfOBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandler_t) OBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandlerImpl,
  .OBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandler = (pfOBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandler_t) OBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandlerImpl,
  .OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandler = (pfOBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandler_t) OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandlerImpl,
  .OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandler = (pfOBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandler_t) OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::START (ID = 0x00000001)
static void OBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::START@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::START@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::START@
        
        actuator_control_service_start();
        
        eOpResult = OBC_ACTUATOR_CONTROL_SERVICE_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::START@

        respResult = OBC_ACTUATOR_CONTROL_SERVICE_STARTResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE, OBC_ACTUATOR_CONTROL_SERVICE_START_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::START (ID = 0x00000001)

// @START@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::STOP (ID = 0x00000002)
static void OBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::STOP@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::STOP@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::STOP@
        
        actuator_control_service_stop();
        
        eOpResult = OBC_ACTUATOR_CONTROL_SERVICE_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::STOP@

        respResult = OBC_ACTUATOR_CONTROL_SERVICE_STOPResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE, OBC_ACTUATOR_CONTROL_SERVICE_STOP_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::STOP (ID = 0x00000002)

// @START@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::GET_STATUS (ID = 0x00000003)
static void OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ACTUATOR_CONTROL_SERVICE_STATUS_t sCurrentStatus;
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::GET_STATUS@
    actuator_control_service_status_t currentStatus;
    // @USER_VAR_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::GET_STATUS@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::GET_STATUS@
        
        currentStatus = actuator_control_service_get_status();
        
        sCurrentStatus.eActiveState = currentStatus.state;
        sCurrentStatus.eLastError   = currentStatus.lastError;

        eOpResult = OBC_ACTUATOR_CONTROL_SERVICE_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::GET_STATUS@

        respResult = OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSResp(
                        &respCtx,
                        &sCurrentStatus,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE, OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::GET_STATUS (ID = 0x00000003)

// @START@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::GET_LAST_MTQ_CONTROL (ID = 0x00000004)
static void OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ACTUATOR_CONTROL_SERVICE_LAST_MTQ_DATA_t sLastMagnetorquerValues;
    OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::GET_LAST_MTQ_CONTROL@
    int8_t lastMagnetorquerValues[MAGNETORQUER_QUANTITY];
    // @USER_VAR_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::GET_LAST_MTQ_CONTROL@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ACTUATOR_CONTROL_SERVICE::GET_LAST_MTQ_CONTROL@
        
        actuator_control_service_get_last_mtq_control(lastMagnetorquerValues);

        sLastMagnetorquerValues.i8MTQ_X = lastMagnetorquerValues[0];
        sLastMagnetorquerValues.i8MTQ_Y = lastMagnetorquerValues[1];
        sLastMagnetorquerValues.i8MTQ_Z = lastMagnetorquerValues[2];

        eOpResult = OBC_ACTUATOR_CONTROL_SERVICE_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ACTUATOR_CONTROL_SERVICE::GET_LAST_MTQ_CONTROL@

        respResult = OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLResp(
                        &respCtx,
                        &sLastMagnetorquerValues,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ACTUATOR_CONTROL_SERVICE, OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROL_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ACTUATOR_CONTROL_SERVICE::GET_LAST_MTQ_CONTROL (ID = 0x00000004)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void OBC_ACTUATOR_CONTROL_SERVICEServerAppInit(void)
{
    OBC_ACTUATOR_CONTROL_SERVICE_registerServerApi(&OBC_ACTUATOR_CONTROL_SERVICEServerApiCtx);
}
