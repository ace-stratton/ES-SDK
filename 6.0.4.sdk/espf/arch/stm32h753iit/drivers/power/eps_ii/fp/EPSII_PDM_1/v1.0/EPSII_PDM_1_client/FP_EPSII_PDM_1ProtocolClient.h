/*!
********************************************************************************************
* @file FP_EPSII_PDM_1ProtocolClient.h
* @brief ESSA Stack client-side public API declaration
********************************************************************************************
* @version           interface EPSII_PDM_1 v1.0
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

#ifndef __FP_EPSII_PDM_1PROTOCOLCLIENT_H__
#define __FP_EPSII_PDM_1PROTOCOLCLIENT_H__

#include "FP_EPSII_PDM_1ProtocolTypes.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef void (*pfEPSII_PDM_1_GetDeviceInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetDeviceInfoResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetPowerDistributionInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetPowerDistributionInfoResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetDeviceHealthInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetDeviceHealthInfoResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_SetPC104GPIOResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1SetPC104GPIOResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetPC104GPIOResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetPC104GPIOResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetRAWSensorsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetRAWSensorsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_SetPowerOutputsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1SetPowerOutputsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetPowerOutputsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetPowerOutputsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_SetBasicSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1SetBasicSettingsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetBasicSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetBasicSettingsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetBasicAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetBasicAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetBasicAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetBasicAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetMainAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetMainAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetMainAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetMainAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1OnESCP_ResetMainAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1OnESCP_ResetMainAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1OnESCP_ResetBasicAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1OnESCP_ResetBasicAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetBulkTelemetryResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetBulkTelemetryResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_ResetDeviceResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1ResetDeviceResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_ForceInstallMainAppResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1ForceInstallMainAppResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_ForceInstallBasicAppResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1ForceInstallBasicAppResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_GetBootLoaderErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1GetBootLoaderErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_PDM_1_ResetBootLdrErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_PDM_1ResetBootLdrErrCountersResponseData_t *pResponseData);


typedef struct {
    pfEPSII_PDM_1_GetDeviceInfoResponseHandler_t EPSII_PDM_1_GetDeviceInfoResponseHandler;
    pfEPSII_PDM_1_GetPowerDistributionInfoResponseHandler_t EPSII_PDM_1_GetPowerDistributionInfoResponseHandler;
    pfEPSII_PDM_1_GetDeviceHealthInfoResponseHandler_t EPSII_PDM_1_GetDeviceHealthInfoResponseHandler;
    pfEPSII_PDM_1_SetPC104GPIOResponseHandler_t EPSII_PDM_1_SetPC104GPIOResponseHandler;
    pfEPSII_PDM_1_GetPC104GPIOResponseHandler_t EPSII_PDM_1_GetPC104GPIOResponseHandler;
    pfEPSII_PDM_1_GetRAWSensorsResponseHandler_t EPSII_PDM_1_GetRAWSensorsResponseHandler;
    pfEPSII_PDM_1_SetPowerOutputsResponseHandler_t EPSII_PDM_1_SetPowerOutputsResponseHandler;
    pfEPSII_PDM_1_GetPowerOutputsResponseHandler_t EPSII_PDM_1_GetPowerOutputsResponseHandler;
    pfEPSII_PDM_1_SetBasicSettingsResponseHandler_t EPSII_PDM_1_SetBasicSettingsResponseHandler;
    pfEPSII_PDM_1_GetBasicSettingsResponseHandler_t EPSII_PDM_1_GetBasicSettingsResponseHandler;
    pfEPSII_PDM_1_GetBasicAppExceptionsResponseHandler_t EPSII_PDM_1_GetBasicAppExceptionsResponseHandler;
    pfEPSII_PDM_1_GetBasicAppErrCountersResponseHandler_t EPSII_PDM_1_GetBasicAppErrCountersResponseHandler;
    pfEPSII_PDM_1_GetMainAppExceptionsResponseHandler_t EPSII_PDM_1_GetMainAppExceptionsResponseHandler;
    pfEPSII_PDM_1_GetMainAppErrCountersResponseHandler_t EPSII_PDM_1_GetMainAppErrCountersResponseHandler;
    pfEPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandler_t EPSII_PDM_1_OnESCP_ResetMainAppErrCountersResponseHandler;
    pfEPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandler_t EPSII_PDM_1_OnESCP_ResetMainAppExceptionsResponseHandler;
    pfEPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandler_t EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersResponseHandler;
    pfEPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandler_t EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsResponseHandler;
    pfEPSII_PDM_1_GetBulkTelemetryResponseHandler_t EPSII_PDM_1_GetBulkTelemetryResponseHandler;
    pfEPSII_PDM_1_ResetDeviceResponseHandler_t EPSII_PDM_1_ResetDeviceResponseHandler;
    pfEPSII_PDM_1_ForceInstallMainAppResponseHandler_t EPSII_PDM_1_ForceInstallMainAppResponseHandler;
    pfEPSII_PDM_1_ForceInstallBasicAppResponseHandler_t EPSII_PDM_1_ForceInstallBasicAppResponseHandler;
    pfEPSII_PDM_1_GetBootLoaderErrCountersResponseHandler_t EPSII_PDM_1_GetBootLoaderErrCountersResponseHandler;
    pfEPSII_PDM_1_ResetBootLdrErrCountersResponseHandler_t EPSII_PDM_1_ResetBootLdrErrCountersResponseHandler;
} EPSII_PDM_1_ClientApi_t;

/**********************************************************************
 *
 *  Client protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_EPSII_PDM_1ProtocolClientInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void EPSII_PDM_1_registerClientApi(EPSII_PDM_1_ClientApi_t *pCliApiHandlers);

// @deprecated - will be removed in the future - use FP_EPSII_PDM_1ProtocolClientInfo directly
ESSA_pStack_FunctionProtocolInfo_t EPSII_PDM_1_getClientProtocolDescriptor(void);

ESSATMAC_ErrCodes EPSII_PDM_1_GetDeviceInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetPowerDistributionInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetDeviceHealthInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_SetPC104GPIOReq(
                ReqContext_t* ctx,
                const EPSII_PDM_1_SGGPIO_Bitmask_t eFilterMask,
                const EPSII_PDM_1_SGGPIO_OnOff_mask_t eValuesMaskReq
);

ESSATMAC_ErrCodes EPSII_PDM_1_GetPC104GPIOReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetRAWSensorsReq(
                ReqContext_t* ctx,
                const uint32_t u32PktIDReq,
                const EPSII_PDM_1_ESEPSII_PDM_SensorIDs_t * const aeSensorsIDs
);

ESSATMAC_ErrCodes EPSII_PDM_1_SetPowerOutputsReq(
                ReqContext_t* ctx,
                const EPSII_PDM_1_SGPO_Bitmask_t eFilterMask,
                const EPSII_PDM_1_SGPO_ON_Off_Bitmask_t eValuesMask
);

ESSATMAC_ErrCodes EPSII_PDM_1_GetPowerOutputsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_SetBasicSettingsReq(
                ReqContext_t* ctx,
                const EPSII_PDM_1_SBasicSettings_t * const sBasicSettings
);

ESSATMAC_ErrCodes EPSII_PDM_1_GetBasicSettingsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetBasicAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetBasicAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetMainAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetMainAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetMainAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetMainAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetBasicAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_OnESCP_ResetBasicAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetBulkTelemetryReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_ResetDeviceReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_ForceInstallMainAppReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_ForceInstallBasicAppReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_GetBootLoaderErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_PDM_1_ResetBootLdrErrCountersReq(
                ReqContext_t* ctx);


#endif  // #ifndef __FP_EPSII_PDM_1PROTOCOLCLIENT_H__

