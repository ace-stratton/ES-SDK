/*!
********************************************************************************************
* @file FP_EPSII_BP_1ProtocolClient.h
* @brief ESSA Stack client-side public API declaration
********************************************************************************************
* @version           interface EPSII_BP_1 v3.0
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

#ifndef __FP_EPSII_BP_1PROTOCOLCLIENT_H__
#define __FP_EPSII_BP_1PROTOCOLCLIENT_H__

#include "FP_EPSII_BP_1ProtocolTypes.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef void (*pfEPSII_BP_1_GetDeviceInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetDeviceInfoResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetRAWSensorsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetRAWSensorsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBatteryInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBatteryInfoResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetDeviceHealthInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetDeviceHealthInfoResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_SetBatHeaterSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1SetBatHeaterSettingsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBatHeaterSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBatHeaterSettingsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_SetBasicSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1SetBasicSettingsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBasicSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBasicSettingsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBasicAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBasicAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBasicAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBasicAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetMainAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetMainAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetMainAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetMainAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetMainAppErrCounters2ResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetMainAppErrCounters2ResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1OnESCP_ResetMainAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1OnESCP_ResetMainAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1OnESCP_ResetBasicAppErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1OnESCP_ResetBasicAppExceptionsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBalancerStatusResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBalancerStatusResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_ResetDeviceResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1ResetDeviceResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_ForceInstallMainAppResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1ForceInstallMainAppResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_ForceInstallBasicAppResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1ForceInstallBasicAppResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBootLoaderErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBootLoaderErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_ResetBootLdrErrCountersResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1ResetBootLdrErrCountersResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_SetChargerSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1SetChargerSettingsResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_SetRTCResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1SetRTCResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetRTCResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetRTCResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_LeaveNoHibModeResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1LeaveNoHibModeResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_RequestPowerDownResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1RequestPowerDownResponseData_t *pResponseData);

typedef void (*pfEPSII_BP_1_GetBpModeSmRollingTraceResponseHandler_t)(RespContext_t *pRespCtx,
              EPSII_BP_1GetBpModeSmRollingTraceResponseData_t *pResponseData);


typedef struct {
    pfEPSII_BP_1_GetDeviceInfoResponseHandler_t EPSII_BP_1_GetDeviceInfoResponseHandler;
    pfEPSII_BP_1_GetRAWSensorsResponseHandler_t EPSII_BP_1_GetRAWSensorsResponseHandler;
    pfEPSII_BP_1_GetBatteryInfoResponseHandler_t EPSII_BP_1_GetBatteryInfoResponseHandler;
    pfEPSII_BP_1_GetDeviceHealthInfoResponseHandler_t EPSII_BP_1_GetDeviceHealthInfoResponseHandler;
    pfEPSII_BP_1_SetBatHeaterSettingsResponseHandler_t EPSII_BP_1_SetBatHeaterSettingsResponseHandler;
    pfEPSII_BP_1_GetBatHeaterSettingsResponseHandler_t EPSII_BP_1_GetBatHeaterSettingsResponseHandler;
    pfEPSII_BP_1_SetBasicSettingsResponseHandler_t EPSII_BP_1_SetBasicSettingsResponseHandler;
    pfEPSII_BP_1_GetBasicSettingsResponseHandler_t EPSII_BP_1_GetBasicSettingsResponseHandler;
    pfEPSII_BP_1_GetBasicAppExceptionsResponseHandler_t EPSII_BP_1_GetBasicAppExceptionsResponseHandler;
    pfEPSII_BP_1_GetBasicAppErrCountersResponseHandler_t EPSII_BP_1_GetBasicAppErrCountersResponseHandler;
    pfEPSII_BP_1_GetMainAppExceptionsResponseHandler_t EPSII_BP_1_GetMainAppExceptionsResponseHandler;
    pfEPSII_BP_1_GetMainAppErrCountersResponseHandler_t EPSII_BP_1_GetMainAppErrCountersResponseHandler;
    pfEPSII_BP_1_GetMainAppErrCounters2ResponseHandler_t EPSII_BP_1_GetMainAppErrCounters2ResponseHandler;
    pfEPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandler_t EPSII_BP_1_OnESCP_ResetMainAppErrCountersResponseHandler;
    pfEPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandler_t EPSII_BP_1_OnESCP_ResetMainAppExceptionsResponseHandler;
    pfEPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandler_t EPSII_BP_1_OnESCP_ResetBasicAppErrCountersResponseHandler;
    pfEPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandler_t EPSII_BP_1_OnESCP_ResetBasicAppExceptionsResponseHandler;
    pfEPSII_BP_1_GetBalancerStatusResponseHandler_t EPSII_BP_1_GetBalancerStatusResponseHandler;
    pfEPSII_BP_1_ResetDeviceResponseHandler_t EPSII_BP_1_ResetDeviceResponseHandler;
    pfEPSII_BP_1_ForceInstallMainAppResponseHandler_t EPSII_BP_1_ForceInstallMainAppResponseHandler;
    pfEPSII_BP_1_ForceInstallBasicAppResponseHandler_t EPSII_BP_1_ForceInstallBasicAppResponseHandler;
    pfEPSII_BP_1_GetBootLoaderErrCountersResponseHandler_t EPSII_BP_1_GetBootLoaderErrCountersResponseHandler;
    pfEPSII_BP_1_ResetBootLdrErrCountersResponseHandler_t EPSII_BP_1_ResetBootLdrErrCountersResponseHandler;
    pfEPSII_BP_1_SetChargerSettingsResponseHandler_t EPSII_BP_1_SetChargerSettingsResponseHandler;
    pfEPSII_BP_1_SetRTCResponseHandler_t EPSII_BP_1_SetRTCResponseHandler;
    pfEPSII_BP_1_GetRTCResponseHandler_t EPSII_BP_1_GetRTCResponseHandler;
    pfEPSII_BP_1_LeaveNoHibModeResponseHandler_t EPSII_BP_1_LeaveNoHibModeResponseHandler;
    pfEPSII_BP_1_RequestPowerDownResponseHandler_t EPSII_BP_1_RequestPowerDownResponseHandler;
    pfEPSII_BP_1_GetBpModeSmRollingTraceResponseHandler_t EPSII_BP_1_GetBpModeSmRollingTraceResponseHandler;
} EPSII_BP_1_ClientApi_t;

/**********************************************************************
 *
 *  Client protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_EPSII_BP_1ProtocolClientInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void EPSII_BP_1_registerClientApi(EPSII_BP_1_ClientApi_t *pCliApiHandlers);

// @deprecated - will be removed in the future - use FP_EPSII_BP_1ProtocolClientInfo directly
ESSA_pStack_FunctionProtocolInfo_t EPSII_BP_1_getClientProtocolDescriptor(void);

ESSATMAC_ErrCodes EPSII_BP_1_GetDeviceInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetRAWSensorsReq(
                ReqContext_t* ctx,
                const uint32_t u32PktIDReq,
                const EPSII_BP_1_EPSIIT_SensorIDs_t * const aeSensorsIDs
);

ESSATMAC_ErrCodes EPSII_BP_1_GetBatteryInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetDeviceHealthInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_SetBatHeaterSettingsReq(
                ReqContext_t* ctx,
                const EPSII_BP_1_SBH_EnableBitmask_t eEnableBitmask,
                const int32_t i32NormalModeSetPointTemp,
                const int32_t i32HibModeSetPointTemp,
                const uint32_t u32PID_KP,
                const uint32_t u32PID_KI,
                const uint32_t u32PID_KD
);

ESSATMAC_ErrCodes EPSII_BP_1_GetBatHeaterSettingsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_SetBasicSettingsReq(
                ReqContext_t* ctx,
                const EPSII_BP_1_SBasicSettings_t * const sBasicSettings
);

ESSATMAC_ErrCodes EPSII_BP_1_GetBasicSettingsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetBasicAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetBasicAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetMainAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetMainAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetMainAppErrCounters2Req(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetMainAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetMainAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetBasicAppErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_OnESCP_ResetBasicAppExceptionsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetBalancerStatusReq(
                ReqContext_t* ctx,
                const uint8_t u8RequestSpecificRegNumber
);

ESSATMAC_ErrCodes EPSII_BP_1_ResetDeviceReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_ForceInstallMainAppReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_ForceInstallBasicAppReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetBootLoaderErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_ResetBootLdrErrCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_SetChargerSettingsReq(
                ReqContext_t* ctx,
                const EPSII_BP_1_ChargerSettings_t * const aeInChargers
);

ESSATMAC_ErrCodes EPSII_BP_1_SetRTCReq(
                ReqContext_t* ctx,
                const uint8_t u8In_hours,
                const uint8_t u8In_minutes,
                const uint8_t u8In_seconds,
                const uint8_t u8In_date,
                const uint8_t u8In_month,
                const uint16_t u16In_year
);

ESSATMAC_ErrCodes EPSII_BP_1_GetRTCReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_LeaveNoHibModeReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_RequestPowerDownReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPSII_BP_1_GetBpModeSmRollingTraceReq(
                ReqContext_t* ctx);


#endif  // #ifndef __FP_EPSII_BP_1PROTOCOLCLIENT_H__

