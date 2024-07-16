/*!
********************************************************************************************
* @file FP_OBC_ES_ADCSProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_OBC_ES_ADCSPROTOCOLSERVER_H__
#define __FP_OBC_ES_ADCSPROTOCOLSERVER_H__

#include "FP_OBC_ES_ADCSProtocolTypes.h"

typedef void (*pfOBC_ES_ADCS_SET_OP_MODERequestHandler_t)(ReqContext_t *ctx, OBC_ES_ADCSSET_OP_MODERequestData_t *pRequestData);
typedef void (*pfOBC_ES_ADCS_GET_OP_MODERequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_SET_ESTIMATORSRequestHandler_t)(ReqContext_t *ctx, OBC_ES_ADCSSET_ESTIMATORSRequestData_t *pRequestData);
typedef void (*pfOBC_ES_ADCS_GET_ESTIMATORSRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_SET_CONTROLLERRequestHandler_t)(ReqContext_t *ctx, OBC_ES_ADCSSET_CONTROLLERRequestData_t *pRequestData);
typedef void (*pfOBC_ES_ADCS_GET_CONTROLLERRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_GET_STATUSRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandler_t)(ReqContext_t *ctx, OBC_ES_ADCSSET_CONTROLLER_BDOT_CONFIGRequestData_t *pRequestData);
typedef void (*pfOBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_SET_MAGNETOMETERRequestHandler_t)(ReqContext_t *ctx, OBC_ES_ADCSSET_MAGNETOMETERRequestData_t *pRequestData);
typedef void (*pfOBC_ES_ADCS_GET_MAGNETOMETERRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_SET_ADCS_CONFIGRequestHandler_t)(ReqContext_t *ctx, OBC_ES_ADCSSET_ADCS_CONFIGRequestData_t *pRequestData);
typedef void (*pfOBC_ES_ADCS_GET_ADCS_CONFIGRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfOBC_ES_ADCS_SET_OP_MODERequestHandler_t OBC_ES_ADCS_SET_OP_MODERequestHandler;
    pfOBC_ES_ADCS_GET_OP_MODERequestHandler_t OBC_ES_ADCS_GET_OP_MODERequestHandler;
    pfOBC_ES_ADCS_SET_ESTIMATORSRequestHandler_t OBC_ES_ADCS_SET_ESTIMATORSRequestHandler;
    pfOBC_ES_ADCS_GET_ESTIMATORSRequestHandler_t OBC_ES_ADCS_GET_ESTIMATORSRequestHandler;
    pfOBC_ES_ADCS_SET_CONTROLLERRequestHandler_t OBC_ES_ADCS_SET_CONTROLLERRequestHandler;
    pfOBC_ES_ADCS_GET_CONTROLLERRequestHandler_t OBC_ES_ADCS_GET_CONTROLLERRequestHandler;
    pfOBC_ES_ADCS_GET_STATUSRequestHandler_t OBC_ES_ADCS_GET_STATUSRequestHandler;
    pfOBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandler_t OBC_ES_ADCS_GET_STATUS_ESTIMATORSRequestHandler;
    pfOBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandler_t OBC_ES_ADCS_GET_STATUS_CONTROLLERRequestHandler;
    pfOBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandler_t OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGRequestHandler;
    pfOBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandler_t OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGRequestHandler;
    pfOBC_ES_ADCS_SET_MAGNETOMETERRequestHandler_t OBC_ES_ADCS_SET_MAGNETOMETERRequestHandler;
    pfOBC_ES_ADCS_GET_MAGNETOMETERRequestHandler_t OBC_ES_ADCS_GET_MAGNETOMETERRequestHandler;
    pfOBC_ES_ADCS_SET_ADCS_CONFIGRequestHandler_t OBC_ES_ADCS_SET_ADCS_CONFIGRequestHandler;
    pfOBC_ES_ADCS_GET_ADCS_CONFIGRequestHandler_t OBC_ES_ADCS_GET_ADCS_CONFIGRequestHandler;
    pfOBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandler_t OBC_ES_ADCS_SAVE_ADCS_CONFIGRequestHandler;
    pfOBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandler_t OBC_ES_ADCS_LOAD_ADCS_CONFIGRequestHandler;
} OBC_ES_ADCS_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_ES_ADCSProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void OBC_ES_ADCS_registerServerApi(OBC_ES_ADCS_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_OBC_ES_ADCSProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t OBC_ES_ADCS_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_OP_MODEResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_OP_MODEResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_OP_MODES_t eActiveMode,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_ESTIMATORSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_ESTIMATORSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator1,
                const OBC_ES_ADCS_ESTIMATOR_t eActiveEstimator2,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_CONTROLLERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_CONTROLLERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONTROLLER_t eActiveController,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_STATUSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_STATUS_t * const sCurrentStatus,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_STATUS_ESTIMATORSResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_ESTIMATOR_STATUS_t * const sCurrentStatusEstimators,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_STATUS_CONTROLLERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONTROLLER_STATUS_t * const sCurrentStatusController,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_CONTROLLER_BDOT_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_CONTROLLER_BDOT_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONTROLLER_BDOT_CONFIG_t * const sActiveBdotConfig,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_MAGNETOMETERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_MAGNETOMETERResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_USED_MAGNETOMETER_t eActiveMagnetometer,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_SET_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_GET_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_CONFIG_t * const sActiveConfig,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_SAVE_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ES_ADCS_LOAD_ADCS_CONFIGResp(
                RespContext_t* ctx,
                const OBC_ES_ADCS_RESULT_t eOpResult
);


#endif  // #ifndef __FP_OBC_ES_ADCSPROTOCOLSERVER_H__
