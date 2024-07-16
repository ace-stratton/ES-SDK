/*!
********************************************************************************************
* @file FP_ConOpsProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface ConOps v0.2
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

#ifndef __FP_CONOPSPROTOCOLSERVER_H__
#define __FP_CONOPSPROTOCOLSERVER_H__

#include "FP_ConOpsProtocolTypes.h"

typedef void (*pfConOps_sendNewEventRequestHandler_t)(ReqContext_t *ctx, ConOpssendNewEventRequestData_t *pRequestData);
typedef void (*pfConOps_getOpModeRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfConOps_setThreshValRequestHandler_t)(ReqContext_t *ctx, ConOpssetThreshValRequestData_t *pRequestData);
typedef void (*pfConOps_getThreshValRequestHandler_t)(ReqContext_t *ctx, ConOpsgetThreshValRequestData_t *pRequestData);
typedef void (*pfConOps_setAllThreshValRequestHandler_t)(ReqContext_t *ctx, ConOpssetAllThreshValRequestData_t *pRequestData);
typedef void (*pfConOps_getAllThreshValRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfConOps_addNewScheduleRecordRequestHandler_t)(ReqContext_t *ctx, ConOpsaddNewScheduleRecordRequestData_t *pRequestData);
typedef void (*pfConOps_clearScheduleRecordsRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfConOps_setEnableSunTrackingFlagRequestHandler_t)(ReqContext_t *ctx, ConOpssetEnableSunTrackingFlagRequestData_t *pRequestData);
typedef void (*pfConOps_getEnableSunTrackingFlagRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfConOps_sendNewEventRequestHandler_t ConOps_sendNewEventRequestHandler;
    pfConOps_getOpModeRequestHandler_t ConOps_getOpModeRequestHandler;
    pfConOps_setThreshValRequestHandler_t ConOps_setThreshValRequestHandler;
    pfConOps_getThreshValRequestHandler_t ConOps_getThreshValRequestHandler;
    pfConOps_setAllThreshValRequestHandler_t ConOps_setAllThreshValRequestHandler;
    pfConOps_getAllThreshValRequestHandler_t ConOps_getAllThreshValRequestHandler;
    pfConOps_addNewScheduleRecordRequestHandler_t ConOps_addNewScheduleRecordRequestHandler;
    pfConOps_clearScheduleRecordsRequestHandler_t ConOps_clearScheduleRecordsRequestHandler;
    pfConOps_setEnableSunTrackingFlagRequestHandler_t ConOps_setEnableSunTrackingFlagRequestHandler;
    pfConOps_getEnableSunTrackingFlagRequestHandler_t ConOps_getEnableSunTrackingFlagRequestHandler;
} ConOps_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_ConOpsProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void ConOps_registerServerApi(ConOps_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_ConOpsProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t ConOps_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes ConOps_sendNewEventResp(
                RespContext_t* ctx,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_getOpModeResp(
                RespContext_t* ctx,
                const CONOPS_OpModes_t eOpModeNum,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_setThreshValResp(
                RespContext_t* ctx,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_getThreshValResp(
                RespContext_t* ctx,
                const int32_t i32ThreshValue,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_setAllThreshValResp(
                RespContext_t* ctx,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_getAllThreshValResp(
                RespContext_t* ctx,
                const CONOPS_ThresholdValues_t * const sThreshVals,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_addNewScheduleRecordResp(
                RespContext_t* ctx,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_clearScheduleRecordsResp(
                RespContext_t* ctx,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_setEnableSunTrackingFlagResp(
                RespContext_t* ctx,
                const CONOPS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes ConOps_getEnableSunTrackingFlagResp(
                RespContext_t* ctx,
                const CONOPS_SafeBool_t eEnFlag,
                const CONOPS_StandardResult_t eOpResult
);


#endif  // #ifndef __FP_CONOPSPROTOCOLSERVER_H__
