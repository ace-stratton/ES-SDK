/*!
********************************************************************************************
* @file FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServer.h
* @brief ESSA Stack server-side public API declaration
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

#ifndef __FP_OBC_ACTUATOR_CONTROL_SERVICEPROTOCOLSERVER_H__
#define __FP_OBC_ACTUATOR_CONTROL_SERVICEPROTOCOLSERVER_H__

#include "FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolTypes.h"

typedef void (*pfOBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfOBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandler_t)(ReqContext_t *ctx);

typedef struct {
    pfOBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandler_t OBC_ACTUATOR_CONTROL_SERVICE_STARTRequestHandler;
    pfOBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandler_t OBC_ACTUATOR_CONTROL_SERVICE_STOPRequestHandler;
    pfOBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandler_t OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSRequestHandler;
    pfOBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandler_t OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLRequestHandler;
} OBC_ACTUATOR_CONTROL_SERVICE_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void OBC_ACTUATOR_CONTROL_SERVICE_registerServerApi(OBC_ACTUATOR_CONTROL_SERVICE_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_OBC_ACTUATOR_CONTROL_SERVICEProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t OBC_ACTUATOR_CONTROL_SERVICE_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_STARTResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_STOPResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_GET_STATUSResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_STATUS_t * const sCurrentStatus,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
);

ESSATMAC_ErrCodes OBC_ACTUATOR_CONTROL_SERVICE_GET_LAST_MTQ_CONTROLResp(
                RespContext_t* ctx,
                const OBC_ACTUATOR_CONTROL_SERVICE_LAST_MTQ_DATA_t * const sLastMagnetorquerValues,
                const OBC_ACTUATOR_CONTROL_SERVICE_RESULT_t eOpResult
);


#endif  // #ifndef __FP_OBC_ACTUATOR_CONTROL_SERVICEPROTOCOLSERVER_H__
