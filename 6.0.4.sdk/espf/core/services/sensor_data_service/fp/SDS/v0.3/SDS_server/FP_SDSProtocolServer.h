/*!
********************************************************************************************
* @file FP_SDSProtocolServer.h
* @brief ESSA Stack server-side public API declaration
********************************************************************************************
* @version           interface SDS v0.3
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

#ifndef __FP_SDSPROTOCOLSERVER_H__
#define __FP_SDSPROTOCOLSERVER_H__

#include "FP_SDSProtocolTypes.h"

typedef void (*pfSDS_setSensReadFreqRequestHandler_t)(ReqContext_t *ctx, SDSsetSensReadFreqRequestData_t *pRequestData);
typedef void (*pfSDS_getSensReadFreqRequestHandler_t)(ReqContext_t *ctx);
typedef void (*pfSDS_getSensStateRequestHandler_t)(ReqContext_t *ctx, SDSgetSensStateRequestData_t *pRequestData);
typedef void (*pfSDS_getSensErrRequestHandler_t)(ReqContext_t *ctx, SDSgetSensErrRequestData_t *pRequestData);
typedef void (*pfSDS_getSensRegRequestHandler_t)(ReqContext_t *ctx, SDSgetSensRegRequestData_t *pRequestData);
typedef void (*pfSDS_setSensRegRequestHandler_t)(ReqContext_t *ctx, SDSsetSensRegRequestData_t *pRequestData);

typedef struct {
    pfSDS_setSensReadFreqRequestHandler_t SDS_setSensReadFreqRequestHandler;
    pfSDS_getSensReadFreqRequestHandler_t SDS_getSensReadFreqRequestHandler;
    pfSDS_getSensStateRequestHandler_t SDS_getSensStateRequestHandler;
    pfSDS_getSensErrRequestHandler_t SDS_getSensErrRequestHandler;
    pfSDS_getSensRegRequestHandler_t SDS_getSensRegRequestHandler;
    pfSDS_setSensRegRequestHandler_t SDS_setSensRegRequestHandler;
} SDS_ServerApi_t;

/**********************************************************************
 *
 *  Server protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_SDSProtocolServerInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void SDS_registerServerApi(SDS_ServerApi_t *pSrvApiHandlers);

// @deprecated - will be removed in the future - use FP_SDSProtocolServerInfo directly
ESSA_pStack_FunctionProtocolInfo_t SDS_getServerProtocolDescriptor(void);

ESSATMAC_ErrCodes SDS_setSensReadFreqResp(
                RespContext_t* ctx,
                const SDS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes SDS_getSensReadFreqResp(
                RespContext_t* ctx,
                const SDS_SafeBool_t eEnable,
                const uint16_t u16SensMTM,
                const uint16_t u16SensGyro,
                const uint16_t u16SensCSS,
                const uint16_t u16SensACC,
                const uint16_t u16SensPANEL_TEMP,
                const uint16_t u16SensGYRO_TEMP,
                const uint16_t u16SensRES_0,
                const uint16_t u16SensRES_1,
                const SDS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes SDS_getSensStateResp(
                RespContext_t* ctx,
                const SDS_SensorState_t eSensState,
                const SDS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes SDS_getSensErrResp(
                RespContext_t* ctx,
                const uint8_t u8SensErr,
                const uint8_t u8X_AXIS,
                const uint8_t u8Y_AXIS,
                const uint8_t u8Z_AXIS,
                const SDS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes SDS_getSensRegResp(
                RespContext_t* ctx,
                const uint32_t u32RespBytes,
                const SDS_StandardResult_t eOpResult
);

ESSATMAC_ErrCodes SDS_setSensRegResp(
                RespContext_t* ctx,
                const SDS_StandardResult_t eOpResult
);


#endif  // #ifndef __FP_SDSPROTOCOLSERVER_H__
