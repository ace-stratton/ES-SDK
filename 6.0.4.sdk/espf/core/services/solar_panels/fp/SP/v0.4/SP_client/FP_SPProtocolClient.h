/*!
********************************************************************************************
* @file FP_SPProtocolClient.h
* @brief ESSA Stack client-side public API declaration
********************************************************************************************
* @version           interface SP v0.4
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

#ifndef __FP_SPPROTOCOLCLIENT_H__
#define __FP_SPPROTOCOLCLIENT_H__

#include "FP_SPProtocolTypes.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef void (*pfSP_GetSoftwareVersionResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetSoftwareVersionResponseData_t *pResponseData);

typedef void (*pfSP_StartDeploymentResponseHandler_t)(RespContext_t *pRespCtx);

typedef void (*pfSP_GetDeploymentStatusResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetDeploymentStatusResponseData_t *pResponseData);

typedef void (*pfSP_GetUptimeResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetUptimeResponseData_t *pResponseData);

typedef void (*pfSP_GetTelemetryResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetTelemetryResponseData_t *pResponseData);

typedef void (*pfSP_GetMainGyroDataResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetMainGyroDataResponseData_t *pResponseData);

typedef void (*pfSP_GetExtGyroDataResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetExtGyroDataResponseData_t *pResponseData);

typedef void (*pfSP_WriteMainGyroRegisterResponseHandler_t)(RespContext_t *pRespCtx);

typedef void (*pfSP_WriteExtGyroRegisterResponseHandler_t)(RespContext_t *pRespCtx);

typedef void (*pfSP_GetMainGyroRegisterResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetMainGyroRegisterResponseData_t *pResponseData);

typedef void (*pfSP_GetExtGyroRegisterResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetExtGyroRegisterResponseData_t *pResponseData);

typedef void (*pfSP_RestartFMWResponseHandler_t)(RespContext_t *pRespCtx);

typedef void (*pfSP_WriteMTQParametersResponseHandler_t)(RespContext_t *pRespCtx,
              SPWriteMTQParametersResponseData_t *pResponseData);

typedef void (*pfSP_GetMTQParametersResponseHandler_t)(RespContext_t *pRespCtx,
              SPGetMTQParametersResponseData_t *pResponseData);


typedef struct {
    pfSP_GetSoftwareVersionResponseHandler_t SP_GetSoftwareVersionResponseHandler;
    pfSP_StartDeploymentResponseHandler_t SP_StartDeploymentResponseHandler;
    pfSP_GetDeploymentStatusResponseHandler_t SP_GetDeploymentStatusResponseHandler;
    pfSP_GetUptimeResponseHandler_t SP_GetUptimeResponseHandler;
    pfSP_GetTelemetryResponseHandler_t SP_GetTelemetryResponseHandler;
    pfSP_GetMainGyroDataResponseHandler_t SP_GetMainGyroDataResponseHandler;
    pfSP_GetExtGyroDataResponseHandler_t SP_GetExtGyroDataResponseHandler;
    pfSP_WriteMainGyroRegisterResponseHandler_t SP_WriteMainGyroRegisterResponseHandler;
    pfSP_WriteExtGyroRegisterResponseHandler_t SP_WriteExtGyroRegisterResponseHandler;
    pfSP_GetMainGyroRegisterResponseHandler_t SP_GetMainGyroRegisterResponseHandler;
    pfSP_GetExtGyroRegisterResponseHandler_t SP_GetExtGyroRegisterResponseHandler;
    pfSP_RestartFMWResponseHandler_t SP_RestartFMWResponseHandler;
    pfSP_WriteMTQParametersResponseHandler_t SP_WriteMTQParametersResponseHandler;
    pfSP_GetMTQParametersResponseHandler_t SP_GetMTQParametersResponseHandler;
} SP_ClientApi_t;

/**********************************************************************
 *
 *  Client protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_SPProtocolClientInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void SP_registerClientApi(SP_ClientApi_t *pCliApiHandlers);

// @deprecated - will be removed in the future - use FP_SPProtocolClientInfo directly
ESSA_pStack_FunctionProtocolInfo_t SP_getClientProtocolDescriptor(void);

ESSATMAC_ErrCodes SP_GetSoftwareVersionReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SP_StartDeploymentReq(
                ReqContext_t* ctx,
                const SP_DepCMD_t eDeployCommand
);

ESSATMAC_ErrCodes SP_GetDeploymentStatusReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SP_GetUptimeReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SP_GetTelemetryReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SP_GetMainGyroDataReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SP_GetExtGyroDataReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SP_WriteMainGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8WriteMainGyroRegisterAddress,
                const uint16_t u16WriteMainGyroRegisterValue
);

ESSATMAC_ErrCodes SP_WriteExtGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8WriteExtGyroRegisterAddress,
                const uint16_t u16WriteExtGyroRegisterValue
);

ESSATMAC_ErrCodes SP_GetMainGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8ReadMainGyroRegisterAdress
);

ESSATMAC_ErrCodes SP_GetExtGyroRegisterReq(
                ReqContext_t* ctx,
                const uint8_t u8ReadExtGyroRegisterAddress
);

ESSATMAC_ErrCodes SP_RestartFMWReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SP_WriteMTQParametersReq(
                ReqContext_t* ctx,
                const SP_MTQ_Mode_t eMode,
                const uint8_t u8WriteMTQDutyCycle
);

ESSATMAC_ErrCodes SP_GetMTQParametersReq(
                ReqContext_t* ctx);


#endif  // #ifndef __FP_SPPROTOCOLCLIENT_H__

