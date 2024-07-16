/*!
********************************************************************************************
* @file FP_OBC_AOCS_CNTRLServerApp.c
* @brief ServerApp implementation template generator
********************************************************************************************
* @version           interface OBC_AOCS_CNTRL v1.0
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

#include "FP_OBC_AOCS_CNTRLProtocolServer.h"

// @START_USER@ USER_INCLUDES
#include <assert.h>
#include "aocs_pm.h"
#include "aocs_pm_types.h"
#include "aocs_cntrl.h"
// Place user includes here to preserve them during merge!!!
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL
static void OBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingRequestData_t* pRequestData);

static void OBC_AOCS_CNTRL_startLoggingRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_AOCS_CNTRLstartLoggingRequestData_t* pRequestData);

static void OBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_AOCS_CNTRLsetDataTypeForAssessmentRequestData_t* pRequestData);

static void OBC_AOCS_CNTRL_getThresholdLevelsRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_setThresholdLevelsRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_AOCS_CNTRLsetThresholdLevelsRequestData_t* pRequestData);

static void OBC_AOCS_CNTRL_getPMOutputRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_getConfigRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_getUpdateIntervalRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_setUpdateIntervalRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_AOCS_CNTRLsetUpdateIntervalRequestData_t* pRequestData);

static void OBC_AOCS_CNTRL_getSamplesToSkipRequestHandlerImpl(ReqContext_t* pReqCtx);

static void OBC_AOCS_CNTRL_setSamplesToSkipRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_AOCS_CNTRLsetSamplesToSkipRequestData_t* pRequestData);

static void OBC_AOCS_CNTRL_setAocsStateRequestHandlerImpl(ReqContext_t* pReqCtx,
            const OBC_AOCS_CNTRLsetAocsStateRequestData_t* pRequestData);

static void OBC_AOCS_CNTRL_getAocsStateRequestHandlerImpl(ReqContext_t* pReqCtx);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static OBC_AOCS_CNTRL_ServerApi_t OBC_AOCS_CNTRLServerApiCtx =
{
  .OBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandler = (pfOBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandler_t) OBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandler = (pfOBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandler_t) OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandlerImpl,
  .OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandler = (pfOBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandler_t) OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandlerImpl,
  .OBC_AOCS_CNTRL_startLoggingRequestHandler = (pfOBC_AOCS_CNTRL_startLoggingRequestHandler_t) OBC_AOCS_CNTRL_startLoggingRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandler = (pfOBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandler_t) OBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandlerImpl,
  .OBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandler = (pfOBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandler_t) OBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getThresholdLevelsRequestHandler = (pfOBC_AOCS_CNTRL_getThresholdLevelsRequestHandler_t) OBC_AOCS_CNTRL_getThresholdLevelsRequestHandlerImpl,
  .OBC_AOCS_CNTRL_setThresholdLevelsRequestHandler = (pfOBC_AOCS_CNTRL_setThresholdLevelsRequestHandler_t) OBC_AOCS_CNTRL_setThresholdLevelsRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getPMOutputRequestHandler = (pfOBC_AOCS_CNTRL_getPMOutputRequestHandler_t) OBC_AOCS_CNTRL_getPMOutputRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getConfigRequestHandler = (pfOBC_AOCS_CNTRL_getConfigRequestHandler_t) OBC_AOCS_CNTRL_getConfigRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getUpdateIntervalRequestHandler = (pfOBC_AOCS_CNTRL_getUpdateIntervalRequestHandler_t) OBC_AOCS_CNTRL_getUpdateIntervalRequestHandlerImpl,
  .OBC_AOCS_CNTRL_setUpdateIntervalRequestHandler = (pfOBC_AOCS_CNTRL_setUpdateIntervalRequestHandler_t) OBC_AOCS_CNTRL_setUpdateIntervalRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getSamplesToSkipRequestHandler = (pfOBC_AOCS_CNTRL_getSamplesToSkipRequestHandler_t) OBC_AOCS_CNTRL_getSamplesToSkipRequestHandlerImpl,
  .OBC_AOCS_CNTRL_setSamplesToSkipRequestHandler = (pfOBC_AOCS_CNTRL_setSamplesToSkipRequestHandler_t) OBC_AOCS_CNTRL_setSamplesToSkipRequestHandlerImpl,
  .OBC_AOCS_CNTRL_setAocsStateRequestHandler = (pfOBC_AOCS_CNTRL_setAocsStateRequestHandler_t) OBC_AOCS_CNTRL_setAocsStateRequestHandlerImpl,
  .OBC_AOCS_CNTRL_getAocsStateRequestHandler = (pfOBC_AOCS_CNTRL_getAocsStateRequestHandler_t) OBC_AOCS_CNTRL_getAocsStateRequestHandlerImpl
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Request handler for method OBC_AOCS_CNTRL::resetAOCSPMbuff (ID = 0x00000000)
static void OBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::resetAOCSPMbuff@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::resetAOCSPMbuff@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::resetAOCSPMbuff@
        aocs_pm_reset();
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::resetAOCSPMbuff@

        respResult = OBC_AOCS_CNTRL_resetAOCSPMbuffResp(
                        &respCtx
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_RESETAOCSPMBUFF_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::resetAOCSPMbuff (ID = 0x00000000)

// @START@ Request handler for method OBC_AOCS_CNTRL::getMaxTimeForAutoLogging (ID = 0x00000001)
static void OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint32_t u32MaxTimeForAutoLogging;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getMaxTimeForAutoLogging@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getMaxTimeForAutoLogging@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getMaxTimeForAutoLogging@
        
        u32MaxTimeForAutoLogging = aocs_pm_get_max_time_for_auto_logging();
        
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getMaxTimeForAutoLogging@

        respResult = OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingResp(
                        &respCtx,
                        u32MaxTimeForAutoLogging
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETMAXTIMEFORAUTOLOGGING_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getMaxTimeForAutoLogging (ID = 0x00000001)

// @START@ Request handler for method OBC_AOCS_CNTRL::setMaxTimeForAutoLogging (ID = 0x00000002)
static void OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::setMaxTimeForAutoLogging@
    uint8_t res = 0;
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::setMaxTimeForAutoLogging@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::setMaxTimeForAutoLogging@
        res = aocs_pm_set_max_time_for_auto_logging((uint32_t)pRequestData->u32MaxTimeForAutoLogging);

		if(res)
		{
			eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_ERROR;
		}
		else
		{
			eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_SUCCESS;
		}
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::setMaxTimeForAutoLogging@

        respResult = OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_SETMAXTIMEFORAUTOLOGGING_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::setMaxTimeForAutoLogging (ID = 0x00000002)

// @START@ Request handler for method OBC_AOCS_CNTRL::startLogging (ID = 0x00000003)
static void OBC_AOCS_CNTRL_startLoggingRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_AOCS_CNTRLstartLoggingRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::startLogging@

    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::startLogging@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::startLogging@
        aocs_pm_start_logging((uint32_t) pRequestData->u32TimeWindowForLogging);
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::startLogging@

        respResult = OBC_AOCS_CNTRL_startLoggingResp(
                        &respCtx
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_STARTLOGGING_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::startLogging (ID = 0x00000003)

// @START@ Request handler for method OBC_AOCS_CNTRL::getDataTypeForAssessment (ID = 0x00000004)
static void OBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_logDataTypes_t eDataType;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getDataTypeForAssessment@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getDataTypeForAssessment@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getDataTypeForAssessment@
        eDataType = aocs_pm_get_data_type_for_assessment();
        
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getDataTypeForAssessment@

        respResult = OBC_AOCS_CNTRL_getDataTypeForAssessmentResp(
                        &respCtx,
                        eDataType
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETDATATYPEFORASSESSMENT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getDataTypeForAssessment (ID = 0x00000004)

// @START@ Request handler for method OBC_AOCS_CNTRL::setDataTypeForAssessment (ID = 0x00000005)
static void OBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_AOCS_CNTRLsetDataTypeForAssessmentRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::setDataTypeForAssessment@
    uint8_t res;
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::setDataTypeForAssessment@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::setDataTypeForAssessment@
        res = aocs_pm_set_data_type_for_assessment((aocs_log_data_types_t)pRequestData->eDataType);
        if(res == 0)
        	eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_SUCCESS;
        else
        	eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_ERROR;
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::setDataTypeForAssessment@

        respResult = OBC_AOCS_CNTRL_setDataTypeForAssessmentResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_SETDATATYPEFORASSESSMENT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::setDataTypeForAssessment (ID = 0x00000005)

// @START@ Request handler for method OBC_AOCS_CNTRL::getThresholdLevels (ID = 0x00000006)
static void OBC_AOCS_CNTRL_getThresholdLevelsRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_thresholdValues_t asThreshold[3];

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getThresholdLevels@
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getThresholdLevels@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getThresholdLevels@
        for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
        {
        	aocs_pm_get_threshold((aocs_pm_threshold_values_t*)&asThreshold[i],i);
        }

        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getThresholdLevels@

        respResult = OBC_AOCS_CNTRL_getThresholdLevelsResp(
                        &respCtx,
                        asThreshold
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETTHRESHOLDLEVELS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getThresholdLevels (ID = 0x00000006)

// @START@ Request handler for method OBC_AOCS_CNTRL::setThresholdLevels (ID = 0x00000007)
static void OBC_AOCS_CNTRL_setThresholdLevelsRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_AOCS_CNTRLsetThresholdLevelsRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::setThresholdLevels@
    aocs_pm_threshold_values_t th;
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::setThresholdLevels@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::setThresholdLevels@
        eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_SUCCESS;
        for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
        {
        	aocs_pm_set_thresholds_to_nvm((aocs_pm_threshold_values_t*)&pRequestData->asThreshold[i],i);
        }
        for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
        {
        	aocs_pm_get_threshold(&th, i);
        	if(memcmp(&th,&pRequestData->asThreshold[i],sizeof(OBC_AOCS_CNTRL_thresholdValues_t)))
        	{
        		eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_ERROR;
        	}
        }
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::setThresholdLevels@

        respResult = OBC_AOCS_CNTRL_setThresholdLevelsResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_SETTHRESHOLDLEVELS_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::setThresholdLevels (ID = 0x00000007)

// @START@ Request handler for method OBC_AOCS_CNTRL::getPMOutput (ID = 0x00000008)
static void OBC_AOCS_CNTRL_getPMOutputRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_PMoutput_t asOutput[3];

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getPMOutput@
    aocs_pm_output_t temp;
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getPMOutput@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getPMOutput@
        for(int i = 0; i < NUM_OF_VALUES_TO_EVALUATE; i++)
        {
        	aocs_pm_get_output((aocs_pm_output_t*)&temp,i);
        	asOutput[i].u8LongTermMetric = temp.u8_stability_measure;
        	asOutput[i].u16EncodedStability = temp.u16_encoded_history;
        }
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getPMOutput@

        respResult = OBC_AOCS_CNTRL_getPMOutputResp(
                        &respCtx,
                        asOutput
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETPMOUTPUT_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getPMOutput (ID = 0x00000008)

// @START@ Request handler for method OBC_AOCS_CNTRL::getConfig (ID = 0x00000009)
static void OBC_AOCS_CNTRL_getConfigRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_Config_t sCurrent_config;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getConfig@
    aocs_pm_parameters_t params;
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getConfig@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getConfig@
        
        aocs_pm_get_config_form_nvm(&params);
        sCurrent_config.eData_type = params.data_type;
        sCurrent_config.u32Max_time_for_logging = params.u32_max_time_for_auto_log;
        sCurrent_config.u16Samples_to_skip = params.u16_samples_to_skip;
        sCurrent_config.u8Update_interval = params.u8_update_interval;
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getConfig@

        respResult = OBC_AOCS_CNTRL_getConfigResp(
                        &respCtx,
                        &sCurrent_config
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETCONFIG_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getConfig (ID = 0x00000009)

// @START@ Request handler for method OBC_AOCS_CNTRL::getUpdateInterval (ID = 0x0000000A)
static void OBC_AOCS_CNTRL_getUpdateIntervalRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint8_t u8Update_interval;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getUpdateInterval@

    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getUpdateInterval@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getUpdateInterval@
        u8Update_interval = aocs_pm_get_update_interval();
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getUpdateInterval@

        respResult = OBC_AOCS_CNTRL_getUpdateIntervalResp(
                        &respCtx,
                        u8Update_interval
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETUPDATEINTERVAL_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getUpdateInterval (ID = 0x0000000A)

// @START@ Request handler for method OBC_AOCS_CNTRL::setUpdateInterval (ID = 0x0000000B)
static void OBC_AOCS_CNTRL_setUpdateIntervalRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_AOCS_CNTRLsetUpdateIntervalRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::setUpdateInterval@
    uint8_t res;
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::setUpdateInterval@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::setUpdateInterval@
        res = aocs_pm_set_update_interval(pRequestData->u8Update_interval);
        if(res)
        	eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_ERROR;
        else
        	eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_SUCCESS;

        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::setUpdateInterval@

        respResult = OBC_AOCS_CNTRL_setUpdateIntervalResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_SETUPDATEINTERVAL_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::setUpdateInterval (ID = 0x0000000B)

// @START@ Request handler for method OBC_AOCS_CNTRL::getSamplesToSkip (ID = 0x0000000C)
static void OBC_AOCS_CNTRL_getSamplesToSkipRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    uint16_t u16Samples_to_skip;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getSamplesToSkip@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getSamplesToSkip@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getSamplesToSkip@
        u16Samples_to_skip = aocs_pm_get_samples_to_skip();
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getSamplesToSkip@

        respResult = OBC_AOCS_CNTRL_getSamplesToSkipResp(
                        &respCtx,
                        u16Samples_to_skip
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETSAMPLESTOSKIP_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getSamplesToSkip (ID = 0x0000000C)

// @START@ Request handler for method OBC_AOCS_CNTRL::setSamplesToSkip (ID = 0x0000000D)
static void OBC_AOCS_CNTRL_setSamplesToSkipRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_AOCS_CNTRLsetSamplesToSkipRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_StandardResult_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::setSamplesToSkip@
    uint8_t res;
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::setSamplesToSkip@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::setSamplesToSkip@
        res = aocs_pm_set_samples_to_skip(pRequestData->u16Samples_to_skip);
        if(res)
        	eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_ERROR;
        else
        	eOpResult = OBC_AOCS_CNTRL_STANDARDRESULT_SUCCESS;
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::setSamplesToSkip@

        respResult = OBC_AOCS_CNTRL_setSamplesToSkipResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_SETSAMPLESTOSKIP_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::setSamplesToSkip (ID = 0x0000000D)

// @START@ Request handler for method OBC_AOCS_CNTRL::setAocsState (ID = 0x0000000E)
static void OBC_AOCS_CNTRL_setAocsStateRequestHandlerImpl(ReqContext_t *pReqCtx,
            const OBC_AOCS_CNTRLsetAocsStateRequestData_t* pRequestData)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_AocsServiceError_t eOpResult;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::setAocsState@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::setAocsState@

    if ((pReqCtx != NULL) && (pRequestData != NULL))
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::setAocsState@
        static_assert(sizeof(pRequestData->eAocsState) == sizeof(aocs_cntrl_sys_state_types_t));
        static_assert(sizeof(pRequestData->sRefParams) == sizeof(aocs_cntrl_reference_params_t));
        static_assert(sizeof(eOpResult) == sizeof(aocs_cntrl_err_status));

        eOpResult = (OBC_AOCS_CNTRL_AocsServiceError_t)aocs_cntrl_request_aocs_state((const aocs_cntrl_sys_state_types_t)pRequestData->eAocsState,
                                                                                     (const aocs_cntrl_reference_params_t * const)&pRequestData->sRefParams);
        
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::setAocsState@

        respResult = OBC_AOCS_CNTRL_setAocsStateResp(
                        &respCtx,
                        eOpResult
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_SETAOCSSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::setAocsState (ID = 0x0000000E)

// @START@ Request handler for method OBC_AOCS_CNTRL::getAocsState (ID = 0x0000000F)
static void OBC_AOCS_CNTRL_getAocsStateRequestHandlerImpl(ReqContext_t* pReqCtx)
{
    ESSATMAC_ErrCodes respResult;
    RespContext_t respCtx;
    OBC_AOCS_CNTRL_AocsServiceError_t eOpResult;
    OBC_AOCS_CNTRL_AocsState_t eAocsState;
    OBC_AOCS_CNTRL_AocsStateReqState_t eReqState;

    // @USER_VAR_SECTION_START@OBC_AOCS_CNTRL::getAocsState@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@OBC_AOCS_CNTRL::getAocsState@

    if (pReqCtx != NULL)
    {
        respCtx.nInterfaceNumber = pReqCtx->nInterfaceNumber;
        respCtx.netType = pReqCtx->netType;
        respCtx.nAddr = pReqCtx->nAddr;
        respCtx.seqId = pReqCtx->seqId;

        // @USER_CODE_SECTION_START@OBC_AOCS_CNTRL::getAocsState@
        static_assert(sizeof(eAocsState) == sizeof(aocs_cntrl_sys_state_types_t));
        static_assert(sizeof(eReqState) == sizeof(aocs_cntrl_sys_state_req_state_t));
        static_assert(sizeof(eOpResult) == sizeof(aocs_cntrl_err_status));
        
        eOpResult = (OBC_AOCS_CNTRL_AocsServiceError_t)aocs_cntrl_get_aocs_state((aocs_cntrl_sys_state_types_t * const)&eAocsState,
                                                                                 (aocs_cntrl_sys_state_req_state_t * const)&eReqState);
        
        // @USER_CODE_SECTION_END@OBC_AOCS_CNTRL::getAocsState@

        respResult = OBC_AOCS_CNTRL_getAocsStateResp(
                        &respCtx,
                        eOpResult,
                        eAocsState,
                        eReqState
                     );

        if (respResult != ESSATMAC_EC_OK)
            TRACE_ERROR(ES_SAT_FUNC_PROTOCOL_ID_OBC_AOCS_CNTRL, OBC_AOCS_CNTRL_GETAOCSSTATE_FUNCRESP_ID, respResult);
    }
}
// @END@ Request handler for method OBC_AOCS_CNTRL::getAocsState (ID = 0x0000000F)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void OBC_AOCS_CNTRLServerAppInit(void)
{
    OBC_AOCS_CNTRL_registerServerApi(&OBC_AOCS_CNTRLServerApiCtx);
}
