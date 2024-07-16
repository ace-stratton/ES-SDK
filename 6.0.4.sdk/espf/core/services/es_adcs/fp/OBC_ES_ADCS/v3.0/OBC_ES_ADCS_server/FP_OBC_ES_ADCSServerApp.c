/*!
********************************************************************************************
* @file FP_OBC_ES_ADCSServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface OBC_ES_ADCS v3.0
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

#include "FP_OBC_ES_ADCSProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include "es_adcs.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void OBC_ES_ADCS_SET_OP_MODERequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_ADCSSET_OP_MODERequestData_t* pRequestData);

static void OBC_ES_ADCS_GET_OP_MODERequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_SET_ESTIMATORSRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_ADCSSET_ESTIMATORSRequestData_t* pRequestData);

static void OBC_ES_ADCS_GET_ESTIMATORSRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_SET_CONTROLLERRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_ADCSSET_CONTROLLERRequestData_t* pRequestData);

static void OBC_ES_ADCS_GET_CONTROLLERRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_GET_STATUSRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGRequestData_t* pRequestData);

static void OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_SET_MAGNETOMETERRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_ADCSSET_MAGNETOMETERRequestData_t* pRequestData);

static void OBC_ES_ADCS_GET_MAGNETOMETERRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_SET_ADCS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_ES_ADCSSET_ADCS_CONFIGRequestData_t* pRequestData);

static void OBC_ES_ADCS_GET_ADCS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static OBC_ES_ADCS_ServerApi_t OBC_ES_ADCSServerApiCtx =
{
  .OBC_ES_ADCS_SET_OP_MODERequestHandler = (pfOBC_ES_ADCS_SET_OP_MODERequestHandler_t) OBC_ES_ADCS_SET_OP_MODERequestHandlerImpl,
  .OBC_ES_ADCS_GET_OP_MODERequestHandler = (pfOBC_ES_ADCS_GET_OP_MODERequestHandler_t) OBC_ES_ADCS_GET_OP_MODERequestHandlerImpl,
  .OBC_ES_ADCS_SET_ESTIMATORSRequestHandler = (pfOBC_ES_ADCS_SET_ESTIMATORSRequestHandler_t) OBC_ES_ADCS_SET_ESTIMATORSRequestHandlerImpl,
  .OBC_ES_ADCS_GET_ESTIMATORSRequestHandler = (pfOBC_ES_ADCS_GET_ESTIMATORSRequestHandler_t) OBC_ES_ADCS_GET_ESTIMATORSRequestHandlerImpl,
  .OBC_ES_ADCS_SET_CONTROLLERRequestHandler = (pfOBC_ES_ADCS_SET_CONTROLLERRequestHandler_t) OBC_ES_ADCS_SET_CONTROLLERRequestHandlerImpl,
  .OBC_ES_ADCS_GET_CONTROLLERRequestHandler = (pfOBC_ES_ADCS_GET_CONTROLLERRequestHandler_t) OBC_ES_ADCS_GET_CONTROLLERRequestHandlerImpl,
  .OBC_ES_ADCS_GET_STATUSRequestHandler = (pfOBC_ES_ADCS_GET_STATUSRequestHandler_t) OBC_ES_ADCS_GET_STATUSRequestHandlerImpl,
  .OBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandler = (pfOBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandler_t) OBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandlerImpl,
  .OBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandler = (pfOBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandler_t) OBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandlerImpl,
  .OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandler = (pfOBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandler_t) OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandlerImpl,
  .OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandler = (pfOBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandler_t) OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandlerImpl,
  .OBC_ES_ADCS_SET_MAGNETOMETERRequestHandler = (pfOBC_ES_ADCS_SET_MAGNETOMETERRequestHandler_t) OBC_ES_ADCS_SET_MAGNETOMETERRequestHandlerImpl,
  .OBC_ES_ADCS_GET_MAGNETOMETERRequestHandler = (pfOBC_ES_ADCS_GET_MAGNETOMETERRequestHandler_t) OBC_ES_ADCS_GET_MAGNETOMETERRequestHandlerImpl,
  .OBC_ES_ADCS_SET_ADCS_CONFIGRequestHandler = (pfOBC_ES_ADCS_SET_ADCS_CONFIGRequestHandler_t) OBC_ES_ADCS_SET_ADCS_CONFIGRequestHandlerImpl,
  .OBC_ES_ADCS_GET_ADCS_CONFIGRequestHandler = (pfOBC_ES_ADCS_GET_ADCS_CONFIGRequestHandler_t) OBC_ES_ADCS_GET_ADCS_CONFIGRequestHandlerImpl,
  .OBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandler = (pfOBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandler_t) OBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandlerImpl,
  .OBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandler = (pfOBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandler_t) OBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method OBC_ES_ADCS::SET_OP_MODE (ID = 0x00000001)
static void OBC_ES_ADCS_SET_OP_MODERequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_ADCSSET_OP_MODERequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::SET_OP_MODE@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::SET_OP_MODE@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::SET_OP_MODE@
        
        es_adcs_set_op_mode(pRequestData->eDesiredMode);
        
        if (es_adcs_get_op_mode() == pRequestData->eDesiredMode)
        {
        	eOpResult = OBC_ES_ADCS_RESULT_OK;
        }
        else
        {
        	eOpResult = OBC_ES_ADCS_RESULT_FAIL;
        }

        // @USER_CODE_SECTION_END@OBC_ES_ADCS::SET_OP_MODE@

        respResult = OBC_ES_ADCS_SET_OP_MODEResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_SET_OP_MODE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::SET_OP_MODE (ID = 0x00000001)

// @START@ Request handler for method OBC_ES_ADCS::GET_OP_MODE (ID = 0x00000002)
static void OBC_ES_ADCS_GET_OP_MODERequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_OP_MODES_t eActiveMode;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_OP_MODE@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_OP_MODE@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_OP_MODE@
        
        eActiveMode = es_adcs_get_op_mode();
        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_OP_MODE@

        respResult = OBC_ES_ADCS_GET_OP_MODEResp(
                        &respCtx,
                        eActiveMode,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_OP_MODE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_OP_MODE (ID = 0x00000002)

// @START@ Request handler for method OBC_ES_ADCS::SET_ESTIMATORS (ID = 0x00000003)
static void OBC_ES_ADCS_SET_ESTIMATORSRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_ADCSSET_ESTIMATORSRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::SET_ESTIMATORS@
    es_adcs_estimator_t eActivatedEstimators[2];
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::SET_ESTIMATORS@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::SET_ESTIMATORS@
        
        es_adcs_set_estimator(
        		pRequestData->eDesiredEstimator1,
				pRequestData->eDesiredEstimator2
        		);
        
        es_adcs_get_estimator(eActivatedEstimators);

        if ((eActivatedEstimators[0] == pRequestData->eDesiredEstimator1) &&
            (eActivatedEstimators[1] == pRequestData->eDesiredEstimator2))
        {
        	eOpResult = OBC_ES_ADCS_RESULT_OK;
        }
        else
        {
        	eOpResult = OBC_ES_ADCS_RESULT_FAIL;
        }

        // @USER_CODE_SECTION_END@OBC_ES_ADCS::SET_ESTIMATORS@

        respResult = OBC_ES_ADCS_SET_ESTIMATORSResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_SET_ESTIMATORS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::SET_ESTIMATORS (ID = 0x00000003)

// @START@ Request handler for method OBC_ES_ADCS::GET_ESTIMATORS (ID = 0x00000004)
static void OBC_ES_ADCS_GET_ESTIMATORSRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator1;
    OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator2;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_ESTIMATORS@
    es_adcs_estimator_t eActivatedEstimators[2];
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_ESTIMATORS@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_ESTIMATORS@
        
        es_adcs_get_estimator(eActivatedEstimators);

        eActiveEstimator1 = eActivatedEstimators[0];
        eActiveEstimator2 = eActivatedEstimators[1];
        eOpResult = OBC_ES_ADCS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_ESTIMATORS@

        respResult = OBC_ES_ADCS_GET_ESTIMATORSResp(
                        &respCtx,
                        eActiveEstimator1,
                        eActiveEstimator2,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_ESTIMATORS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_ESTIMATORS (ID = 0x00000004)

// @START@ Request handler for method OBC_ES_ADCS::SET_CONTROLLER (ID = 0x00000005)
static void OBC_ES_ADCS_SET_CONTROLLERRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_ADCSSET_CONTROLLERRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::SET_CONTROLLER@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::SET_CONTROLLER@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::SET_CONTROLLER@
        
        es_adcs_set_controller(pRequestData->eDesiredController);

        if (es_adcs_get_controller() == pRequestData->eDesiredController)
        {
        	eOpResult = OBC_ES_ADCS_RESULT_OK;
        }
        else
        {
        	eOpResult = OBC_ES_ADCS_RESULT_FAIL;
        }
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::SET_CONTROLLER@

        respResult = OBC_ES_ADCS_SET_CONTROLLERResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_SET_CONTROLLER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::SET_CONTROLLER (ID = 0x00000005)

// @START@ Request handler for method OBC_ES_ADCS::GET_CONTROLLER (ID = 0x00000006)
static void OBC_ES_ADCS_GET_CONTROLLERRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_CONTROLLER_t eActiveController;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_CONTROLLER@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_CONTROLLER@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_CONTROLLER@
        
        eActiveController = es_adcs_get_controller();
        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_CONTROLLER@

        respResult = OBC_ES_ADCS_GET_CONTROLLERResp(
                        &respCtx,
                        eActiveController,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_CONTROLLER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_CONTROLLER (ID = 0x00000006)

// @START@ Request handler for method OBC_ES_ADCS::GET_STATUS (ID = 0x00000007)
static void OBC_ES_ADCS_GET_STATUSRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_STATUS_t sCurrentStatus;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_STATUS@
    es_adcs_status_t currentStatus;
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_STATUS@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_STATUS@
        
        currentStatus = es_adcs_get_status();

        sCurrentStatus.eEstimatorResult  = currentStatus.estimatorResult;
        sCurrentStatus.eControllerResult = currentStatus.controllerResult;
        sCurrentStatus.eActiveMode       = currentStatus.adcs_hsm_state;

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_STATUS@

        respResult = OBC_ES_ADCS_GET_STATUSResp(
                        &respCtx,
                        &sCurrentStatus,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_STATUS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_STATUS (ID = 0x00000007)

// @START@ Request handler for method OBC_ES_ADCS::GET_STATUS_ESTIMATORS (ID = 0x00000008)
static void OBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_ESTIMATOR_STATUS_t sCurrentStatusEstimators;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_STATUS_ESTIMATORS@
    es_adcs_estimator_status_t currentStatus;
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_STATUS_ESTIMATORS@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_STATUS_ESTIMATORS@
        
        currentStatus = es_adcs_get_status_estimator();

        sCurrentStatusEstimators.eLastWarningGeneral = currentStatus.lastWarningGeneral;
        sCurrentStatusEstimators.eLastErrorGeneral   = currentStatus.lastErrorGeneral;
        sCurrentStatusEstimators.asAlgoStatus[0].eLastWarningAlgo = currentStatus.algoStatus[0].lastWarningAlgo;
        sCurrentStatusEstimators.asAlgoStatus[0].eLastErrorAlgo   = currentStatus.algoStatus[0].lastErrorAlgo;
        sCurrentStatusEstimators.asAlgoStatus[1].eLastWarningAlgo = currentStatus.algoStatus[1].lastWarningAlgo;
        sCurrentStatusEstimators.asAlgoStatus[1].eLastErrorAlgo   = currentStatus.algoStatus[1].lastErrorAlgo;

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_STATUS_ESTIMATORS@

        respResult = OBC_ES_ADCS_GET_STATUS_ESTIMATORSResp(
                        &respCtx,
                        &sCurrentStatusEstimators,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_STATUS_ESTIMATORS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_STATUS_ESTIMATORS (ID = 0x00000008)

// @START@ Request handler for method OBC_ES_ADCS::GET_STATUS_CONTROLLER (ID = 0x00000009)
static void OBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_CONTROLLER_STATUS_t sCurrentStatusController;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_STATUS_CONTROLLER@
    es_adcs_controller_status_t currentStatus;
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_STATUS_CONTROLLER@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_STATUS_CONTROLLER@
        
        currentStatus = es_adcs_get_status_controller();

        sCurrentStatusController.eLastWarningGeneral          = currentStatus.lastWarningGeneral;
        sCurrentStatusController.eLastErrorGeneral            = currentStatus.lastErrorGeneral;
        sCurrentStatusController.sAlgoStatus.eLastWarningAlgo = currentStatus.algoStatus.lastWarningAlgo;
        sCurrentStatusController.sAlgoStatus.eLastErrorAlgo   = currentStatus.algoStatus.lastErrorAlgo;

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_STATUS_CONTROLLER@

        respResult = OBC_ES_ADCS_GET_STATUS_CONTROLLERResp(
                        &respCtx,
                        &sCurrentStatusController,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_STATUS_CONTROLLER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_STATUS_CONTROLLER (ID = 0x00000009)

// @START@ Request handler for method OBC_ES_ADCS::SET_CONTROLLER_BDOT_CONFIG (ID = 0x0000000A)
static void OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::SET_CONTROLLER_BDOT_CONFIG@
    es_adcs_controller_bdot_config_t desiredBdotConfig;
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::SET_CONTROLLER_BDOT_CONFIG@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::SET_CONTROLLER_BDOT_CONFIG@
        
        desiredBdotConfig.bdot_coefficient_X = pRequestData->sDesiredBdotConfig.dBdot_gain_coeff_X;
        desiredBdotConfig.bdot_coefficient_Y = pRequestData->sDesiredBdotConfig.dBdot_gain_coeff_Y;
        desiredBdotConfig.bdot_coefficient_Z = pRequestData->sDesiredBdotConfig.dBdot_gain_coeff_Z;

        /* Apply the config */
        es_adcs_set_controller_bdot_config(desiredBdotConfig);

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::SET_CONTROLLER_BDOT_CONFIG@

        respResult = OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::SET_CONTROLLER_BDOT_CONFIG (ID = 0x0000000A)

// @START@ Request handler for method OBC_ES_ADCS::GET_CONTROLLER_BDOT_CONFIG (ID = 0x0000000B)
static void OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_CONTROLLER_BDOT_CONFIG_t sActiveBdotConfig;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_CONTROLLER_BDOT_CONFIG@
    es_adcs_controller_bdot_config_t activeBdotConfig;
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_CONTROLLER_BDOT_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_CONTROLLER_BDOT_CONFIG@
        
        activeBdotConfig = es_adcs_get_controller_bdot_config();

        sActiveBdotConfig.dBdot_gain_coeff_X = activeBdotConfig.bdot_coefficient_X;
        sActiveBdotConfig.dBdot_gain_coeff_Y = activeBdotConfig.bdot_coefficient_Y;
        sActiveBdotConfig.dBdot_gain_coeff_Z = activeBdotConfig.bdot_coefficient_Z;

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_CONTROLLER_BDOT_CONFIG@

        respResult = OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGResp(
                        &respCtx,
                        &sActiveBdotConfig,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_CONTROLLER_BDOT_CONFIG (ID = 0x0000000B)

// @START@ Request handler for method OBC_ES_ADCS::SET_MAGNETOMETER (ID = 0x0000000C)
static void OBC_ES_ADCS_SET_MAGNETOMETERRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_ADCSSET_MAGNETOMETERRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::SET_MAGNETOMETER@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::SET_MAGNETOMETER@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::SET_MAGNETOMETER@
        
        es_adcs_set_used_magnetometer(pRequestData->eDesiredMagnetometer);

        if (es_adcs_get_used_magnetometer() == pRequestData->eDesiredMagnetometer)
        {
        	eOpResult = OBC_ES_ADCS_RESULT_OK;
        }
        else
        {
        	eOpResult = OBC_ES_ADCS_RESULT_FAIL;
        }
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::SET_MAGNETOMETER@

        respResult = OBC_ES_ADCS_SET_MAGNETOMETERResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_SET_MAGNETOMETER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::SET_MAGNETOMETER (ID = 0x0000000C)

// @START@ Request handler for method OBC_ES_ADCS::GET_MAGNETOMETER (ID = 0x0000000D)
static void OBC_ES_ADCS_GET_MAGNETOMETERRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_USED_MAGNETOMETER_t eActiveMagnetometer;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_MAGNETOMETER@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_MAGNETOMETER@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_MAGNETOMETER@
        
        eActiveMagnetometer = es_adcs_get_used_magnetometer();
        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_MAGNETOMETER@

        respResult = OBC_ES_ADCS_GET_MAGNETOMETERResp(
                        &respCtx,
                        eActiveMagnetometer,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_MAGNETOMETER_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_MAGNETOMETER (ID = 0x0000000D)

// @START@ Request handler for method OBC_ES_ADCS::SET_ADCS_CONFIG (ID = 0x0000000E)
static void OBC_ES_ADCS_SET_ADCS_CONFIGRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_ES_ADCSSET_ADCS_CONFIGRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::SET_ADCS_CONFIG@
    es_adcs_config_t desiredConfig;
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::SET_ADCS_CONFIG@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::SET_ADCS_CONFIG@
        
        desiredConfig.sEstimatorConfig.eActiveEstimators[0] = pRequestData->sDesiredConfig.sEstimatorConfig.aeActiveEstimators[0];
        desiredConfig.sEstimatorConfig.eActiveEstimators[1] = pRequestData->sDesiredConfig.sEstimatorConfig.aeActiveEstimators[1];

        desiredConfig.sControllerConfig.eActiveController              = pRequestData->sDesiredConfig.sControllerConfig.eActiveController;
        desiredConfig.sControllerConfig.sBdotConfig.bdot_coefficient_X = pRequestData->sDesiredConfig.sControllerConfig.sBdotConfig.dBdot_gain_coeff_X;
        desiredConfig.sControllerConfig.sBdotConfig.bdot_coefficient_Y = pRequestData->sDesiredConfig.sControllerConfig.sBdotConfig.dBdot_gain_coeff_Y;
        desiredConfig.sControllerConfig.sBdotConfig.bdot_coefficient_Z = pRequestData->sDesiredConfig.sControllerConfig.sBdotConfig.dBdot_gain_coeff_Z;

        desiredConfig.eUsedMagnetometer = pRequestData->sDesiredConfig.eUsedMagnetometer;

        /* Apply the config */
        es_adcs_set_config(desiredConfig);

        eOpResult = OBC_ES_ADCS_RESULT_OK;

        // @USER_CODE_SECTION_END@OBC_ES_ADCS::SET_ADCS_CONFIG@

        respResult = OBC_ES_ADCS_SET_ADCS_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_SET_ADCS_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::SET_ADCS_CONFIG (ID = 0x0000000E)

// @START@ Request handler for method OBC_ES_ADCS::GET_ADCS_CONFIG (ID = 0x0000000F)
static void OBC_ES_ADCS_GET_ADCS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_CONFIG_t sActiveConfig;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::GET_ADCS_CONFIG@
    es_adcs_config_t activeConfig;
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::GET_ADCS_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::GET_ADCS_CONFIG@
        
        activeConfig = es_adcs_get_config();

        sActiveConfig.sEstimatorConfig.aeActiveEstimators[0] = activeConfig.sEstimatorConfig.eActiveEstimators[0];
        sActiveConfig.sEstimatorConfig.aeActiveEstimators[1] = activeConfig.sEstimatorConfig.eActiveEstimators[1];

        sActiveConfig.sControllerConfig.eActiveController              = activeConfig.sControllerConfig.eActiveController;
        sActiveConfig.sControllerConfig.sBdotConfig.dBdot_gain_coeff_X = activeConfig.sControllerConfig.sBdotConfig.bdot_coefficient_X;
        sActiveConfig.sControllerConfig.sBdotConfig.dBdot_gain_coeff_Y = activeConfig.sControllerConfig.sBdotConfig.bdot_coefficient_Y;
        sActiveConfig.sControllerConfig.sBdotConfig.dBdot_gain_coeff_Z = activeConfig.sControllerConfig.sBdotConfig.bdot_coefficient_Z;

        sActiveConfig.eUsedMagnetometer = activeConfig.eUsedMagnetometer;

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::GET_ADCS_CONFIG@

        respResult = OBC_ES_ADCS_GET_ADCS_CONFIGResp(
                        &respCtx,
                        &sActiveConfig,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_GET_ADCS_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::GET_ADCS_CONFIG (ID = 0x0000000F)

// @START@ Request handler for method OBC_ES_ADCS::SAVE_ADCS_CONFIG (ID = 0x00000010)
static void OBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::SAVE_ADCS_CONFIG@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::SAVE_ADCS_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::SAVE_ADCS_CONFIG@
        
        es_adcs_save_config_to_NVM();

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::SAVE_ADCS_CONFIG@

        respResult = OBC_ES_ADCS_SAVE_ADCS_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_SAVE_ADCS_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::SAVE_ADCS_CONFIG (ID = 0x00000010)

// @START@ Request handler for method OBC_ES_ADCS::LOAD_ADCS_CONFIG (ID = 0x00000011)
static void OBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_ES_ADCS_RESULT_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_ES_ADCS::LOAD_ADCS_CONFIG@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_ES_ADCS::LOAD_ADCS_CONFIG@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_ES_ADCS::LOAD_ADCS_CONFIG@
        
        es_adcs_load_config_from_NVM();

        eOpResult = OBC_ES_ADCS_RESULT_OK;
        
        // @USER_CODE_SECTION_END@OBC_ES_ADCS::LOAD_ADCS_CONFIG@

        respResult = OBC_ES_ADCS_LOAD_ADCS_CONFIGResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_ES_ADCS, OBC_ES_ADCS_LOAD_ADCS_CONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_ES_ADCS::LOAD_ADCS_CONFIG (ID = 0x00000011)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void OBC_ES_ADCSServerAppInit(void)
{
    OBC_ES_ADCS_registerServerApi(&OBC_ES_ADCSServerApiCtx);
}
