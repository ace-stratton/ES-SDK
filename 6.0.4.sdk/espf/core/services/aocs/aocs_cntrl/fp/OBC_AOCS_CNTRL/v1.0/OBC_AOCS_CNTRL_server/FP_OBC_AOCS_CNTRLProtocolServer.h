/*!
********************************************************************************************
* @file FP_OBC_AOCS_CNTRLProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_OBC_AOCS_CNTRLPROTOCOLSERVER_H__
#define __FP_OBC_AOCS_CNTRLPROTOCOLSERVER_H__

#include "FP_OBC_AOCS_CNTRLProtocolTypes.h"

typedef void (*pfOBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandler_t)(ReqContext_t *ctx, OBC_AOCS_CNTRLsetMaxTimeForAutoLoggingRequestData_t *pRequestData);
typedef void (*pfOBC_AOCS_CNTRL_startLoggingRequestHandler_t)(ReqContext_t *ctx, OBC_AOCS_CNTRLstartLoggingRequestData_t *pRequestData);
typedef void (*pfOBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandler_t)(ReqContext_t *ctx, OBC_AOCS_CNTRLsetDataTypeForAssessmentRequestData_t *pRequestData);
typedef void (*pfOBC_AOCS_CNTRL_getThresholdLevelsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_setThresholdLevelsRequestHandler_t)(ReqContext_t *ctx, OBC_AOCS_CNTRLsetThresholdLevelsRequestData_t *pRequestData);
typedef void (*pfOBC_AOCS_CNTRL_getPMOutputRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_getConfigRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_getUpdateIntervalRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_setUpdateIntervalRequestHandler_t)(ReqContext_t *ctx, OBC_AOCS_CNTRLsetUpdateIntervalRequestData_t *pRequestData);
typedef void (*pfOBC_AOCS_CNTRL_getSamplesToSkipRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_AOCS_CNTRL_setSamplesToSkipRequestHandler_t)(ReqContext_t *ctx, OBC_AOCS_CNTRLsetSamplesToSkipRequestData_t *pRequestData);
typedef void (*pfOBC_AOCS_CNTRL_setAocsStateRequestHandler_t)(ReqContext_t *ctx, OBC_AOCS_CNTRLsetAocsStateRequestData_t *pRequestData);
typedef void (*pfOBC_AOCS_CNTRL_getAocsStateRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfOBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandler_t OBC_AOCS_CNTRL_resetAOCSPMbuffRequestHandler;
    pfOBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandler_t OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingRequestHandler;
    pfOBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandler_t OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingRequestHandler;
    pfOBC_AOCS_CNTRL_startLoggingRequestHandler_t OBC_AOCS_CNTRL_startLoggingRequestHandler;
    pfOBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandler_t OBC_AOCS_CNTRL_getDataTypeForAssessmentRequestHandler;
    pfOBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandler_t OBC_AOCS_CNTRL_setDataTypeForAssessmentRequestHandler;
    pfOBC_AOCS_CNTRL_getThresholdLevelsRequestHandler_t OBC_AOCS_CNTRL_getThresholdLevelsRequestHandler;
    pfOBC_AOCS_CNTRL_setThresholdLevelsRequestHandler_t OBC_AOCS_CNTRL_setThresholdLevelsRequestHandler;
    pfOBC_AOCS_CNTRL_getPMOutputRequestHandler_t OBC_AOCS_CNTRL_getPMOutputRequestHandler;
    pfOBC_AOCS_CNTRL_getConfigRequestHandler_t OBC_AOCS_CNTRL_getConfigRequestHandler;
    pfOBC_AOCS_CNTRL_getUpdateIntervalRequestHandler_t OBC_AOCS_CNTRL_getUpdateIntervalRequestHandler;
    pfOBC_AOCS_CNTRL_setUpdateIntervalRequestHandler_t OBC_AOCS_CNTRL_setUpdateIntervalRequestHandler;
    pfOBC_AOCS_CNTRL_getSamplesToSkipRequestHandler_t OBC_AOCS_CNTRL_getSamplesToSkipRequestHandler;
    pfOBC_AOCS_CNTRL_setSamplesToSkipRequestHandler_t OBC_AOCS_CNTRL_setSamplesToSkipRequestHandler;
    pfOBC_AOCS_CNTRL_setAocsStateRequestHandler_t OBC_AOCS_CNTRL_setAocsStateRequestHandler;
    pfOBC_AOCS_CNTRL_getAocsStateRequestHandler_t OBC_AOCS_CNTRL_getAocsStateRequestHandler;
} OBC_AOCS_CNTRL_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_AOCS_CNTRLProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void OBC_AOCS_CNTRL_registerServerApi(OBC_AOCS_CNTRL_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_OBC_AOCS_CNTRLProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t OBC_AOCS_CNTRL_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_resetAOCSPMbuffResp(
                RespContext_t* ctx);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getMaxTimeForAutoLoggingResp(
                RespContext_t* ctx,
                const uint32_t u32MaxTimeForAutoLogging
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setMaxTimeForAutoLoggingResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_startLoggingResp(
                RespContext_t* ctx);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getDataTypeForAssessmentResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_logDataTypes_t eDataType
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setDataTypeForAssessmentResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getThresholdLevelsResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_thresholdValues_t * const asThreshold
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setThresholdLevelsResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getPMOutputResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_PMoutput_t * const asOutput
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getConfigResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_Config_t * const sCurrent_config
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getUpdateIntervalResp(
                RespContext_t* ctx,
                const uint8_t u8Update_interval
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setUpdateIntervalResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getSamplesToSkipResp(
                RespContext_t* ctx,
                const uint16_t u16Samples_to_skip
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setSamplesToSkipResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_setAocsStateResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_AocsServiceError_t eOpResult
);

ESSATMAC_ErrCodes OBC_AOCS_CNTRL_getAocsStateResp(
                RespContext_t* ctx,
                const OBC_AOCS_CNTRL_AocsServiceError_t eOpResult,
                const OBC_AOCS_CNTRL_AocsState_t eAocsState,
                const OBC_AOCS_CNTRL_AocsStateReqState_t eReqState
);


#endif  // #ifndef __FP_OBC_AOCS_CNTRLPROTOCOLSERVER_H__
