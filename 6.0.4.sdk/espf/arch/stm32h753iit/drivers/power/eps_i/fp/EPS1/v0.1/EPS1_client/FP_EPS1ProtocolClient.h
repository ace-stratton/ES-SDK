/*!
********************************************************************************************
* @file FP_EPS1ProtocolClient.h
* @brief ESSA Stack client-side public API declaration
********************************************************************************************
* @version           interface EPS1 v0.1
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

#ifndef __FP_EPS1PROTOCOLCLIENT_H__
#define __FP_EPS1PROTOCOLCLIENT_H__

#include "FP_EPS1ProtocolTypes.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef void (*pfEPS1_getSoftwareVersionResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1getSoftwareVersionResponseData_t *pResponseData);

typedef void (*pfEPS1_getBatteryInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1getBatteryInfoResponseData_t *pResponseData);

typedef void (*pfEPS1_getBusesInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1getBusesInfoResponseData_t *pResponseData);

typedef void (*pfEPS1_getSolarPanelsInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1getSolarPanelsInfoResponseData_t *pResponseData);

typedef void (*pfEPS1_getStatisticInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1getStatisticInfoResponseData_t *pResponseData);

typedef void (*pfEPS1_getTemperaturesInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1getTemperaturesInfoResponseData_t *pResponseData);

typedef void (*pfEPS1_getConfigurationInfoResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1getConfigurationInfoResponseData_t *pResponseData);

typedef void (*pfEPS1_queryControlsResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1queryControlsResponseData_t *pResponseData);

typedef void (*pfEPS1_queryRBatRawResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1queryRBatRawResponseData_t *pResponseData);

typedef void (*pfEPS1_queryDefaultsResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1queryDefaultsResponseData_t *pResponseData);

typedef void (*pfEPS1_queryLaunchStateResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1queryLaunchStateResponseData_t *pResponseData);

typedef void (*pfEPS1_queryWatchdogResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1queryWatchdogResponseData_t *pResponseData);

typedef void (*pfEPS1_resetWatchdogResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1resetWatchdogResponseData_t *pResponseData);

typedef void (*pfEPS1_resetPowerSupplyResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1resetPowerSupplyResponseData_t *pResponseData);

typedef void (*pfEPS1_SetSerialNumberResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1SetSerialNumberResponseData_t *pResponseData);

typedef void (*pfEPS1_GetSerialNumberResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1GetSerialNumberResponseData_t *pResponseData);

typedef void (*pfEPS1_HellModeReadResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1HellModeReadResponseData_t *pResponseData);

typedef void (*pfEPS1_HellModeWriteResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1HellModeWriteResponseData_t *pResponseData);

typedef void (*pfEPS1_HeatersSettingsReadResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1HeatersSettingsReadResponseData_t *pResponseData);

typedef void (*pfEPS1_HeatersSettingsWriteResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1HeatersSettingsWriteResponseData_t *pResponseData);

typedef void (*pfEPS1_ToggleOutPutResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1ToggleOutPutResponseData_t *pResponseData);

typedef void (*pfEPS1_NotificationsSettingsResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1NotificationsSettingsResponseData_t *pResponseData);

typedef void (*pfEPS1_GetTelemetryAltogetherResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1GetTelemetryAltogetherResponseData_t *pResponseData);

typedef void (*pfEPS1_bload_getVersionResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1bload_getVersionResponseData_t *pResponseData);

typedef void (*pfEPS1_bload_eraseFlashResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1bload_eraseFlashResponseData_t *pResponseData);

typedef void (*pfEPS1_bload_writeFlashResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1bload_writeFlashResponseData_t *pResponseData);

typedef void (*pfEPS1_bload_executeResponseHandler_t)(RespContext_t *pRespCtx,
              EPS1bload_executeResponseData_t *pResponseData);


typedef struct {
    pfEPS1_getSoftwareVersionResponseHandler_t EPS1_getSoftwareVersionResponseHandler;
    pfEPS1_getBatteryInfoResponseHandler_t EPS1_getBatteryInfoResponseHandler;
    pfEPS1_getBusesInfoResponseHandler_t EPS1_getBusesInfoResponseHandler;
    pfEPS1_getSolarPanelsInfoResponseHandler_t EPS1_getSolarPanelsInfoResponseHandler;
    pfEPS1_getStatisticInfoResponseHandler_t EPS1_getStatisticInfoResponseHandler;
    pfEPS1_getTemperaturesInfoResponseHandler_t EPS1_getTemperaturesInfoResponseHandler;
    pfEPS1_getConfigurationInfoResponseHandler_t EPS1_getConfigurationInfoResponseHandler;
    pfEPS1_queryControlsResponseHandler_t EPS1_queryControlsResponseHandler;
    pfEPS1_queryRBatRawResponseHandler_t EPS1_queryRBatRawResponseHandler;
    pfEPS1_queryDefaultsResponseHandler_t EPS1_queryDefaultsResponseHandler;
    pfEPS1_queryLaunchStateResponseHandler_t EPS1_queryLaunchStateResponseHandler;
    pfEPS1_queryWatchdogResponseHandler_t EPS1_queryWatchdogResponseHandler;
    pfEPS1_resetWatchdogResponseHandler_t EPS1_resetWatchdogResponseHandler;
    pfEPS1_resetPowerSupplyResponseHandler_t EPS1_resetPowerSupplyResponseHandler;
    pfEPS1_SetSerialNumberResponseHandler_t EPS1_SetSerialNumberResponseHandler;
    pfEPS1_GetSerialNumberResponseHandler_t EPS1_GetSerialNumberResponseHandler;
    pfEPS1_HellModeReadResponseHandler_t EPS1_HellModeReadResponseHandler;
    pfEPS1_HellModeWriteResponseHandler_t EPS1_HellModeWriteResponseHandler;
    pfEPS1_HeatersSettingsReadResponseHandler_t EPS1_HeatersSettingsReadResponseHandler;
    pfEPS1_HeatersSettingsWriteResponseHandler_t EPS1_HeatersSettingsWriteResponseHandler;
    pfEPS1_ToggleOutPutResponseHandler_t EPS1_ToggleOutPutResponseHandler;
    pfEPS1_NotificationsSettingsResponseHandler_t EPS1_NotificationsSettingsResponseHandler;
    pfEPS1_GetTelemetryAltogetherResponseHandler_t EPS1_GetTelemetryAltogetherResponseHandler;
    pfEPS1_bload_getVersionResponseHandler_t EPS1_bload_getVersionResponseHandler;
    pfEPS1_bload_eraseFlashResponseHandler_t EPS1_bload_eraseFlashResponseHandler;
    pfEPS1_bload_writeFlashResponseHandler_t EPS1_bload_writeFlashResponseHandler;
    pfEPS1_bload_executeResponseHandler_t EPS1_bload_executeResponseHandler;
} EPS1_ClientApi_t;

/**********************************************************************
 *
 *  Client protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_EPS1ProtocolClientInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void EPS1_registerClientApi(EPS1_ClientApi_t *pCliApiHandlers);

// @deprecated - will be removed in the future - use FP_EPS1ProtocolClientInfo directly
ESSA_pStack_FunctionProtocolInfo_t EPS1_getClientProtocolDescriptor(void);

ESSATMAC_ErrCodes EPS1_getSoftwareVersionReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_getBatteryInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_getBusesInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_getSolarPanelsInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_getStatisticInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_getTemperaturesInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_getConfigurationInfoReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_queryControlsReq(
                ReqContext_t* ctx,
                const EPS1_QueryState_t * const aeRequested
);

ESSATMAC_ErrCodes EPS1_queryRBatRawReq(
                ReqContext_t* ctx,
                const uint8_t u8NewValue
);

ESSATMAC_ErrCodes EPS1_queryDefaultsReq(
                ReqContext_t* ctx,
                const EPS1_QueryState_t * const aeRequested,
                const uint8_t u8Reserved
);

ESSATMAC_ErrCodes EPS1_queryLaunchStateReq(
                ReqContext_t* ctx,
                const EPS1_QueryState_t eRequested,
                const uint8_t u8WriteDelayPeriod
);

ESSATMAC_ErrCodes EPS1_queryWatchdogReq(
                ReqContext_t* ctx,
                const uint8_t u8New_timer,
                const EPS1_WatchDogType_t eNew_type
);

ESSATMAC_ErrCodes EPS1_resetWatchdogReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_resetPowerSupplyReq(
                ReqContext_t* ctx,
                const uint8_t u8Security
);

ESSATMAC_ErrCodes EPS1_SetSerialNumberReq(
                ReqContext_t* ctx,
                char * const strDeviceSerialNumberWrite,
                const uint8_t u8DeviceSerialNumberWriteSize
);

ESSATMAC_ErrCodes EPS1_GetSerialNumberReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_HellModeReadReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_HellModeWriteReq(
                ReqContext_t* ctx,
                const uint8_t u8WriteEntryLevelVoltage,
                const uint8_t u8WriteExitLevelVoltage,
                const uint8_t u8WriteEntryLevelTemperature,
                const uint8_t u8WriteExitLevelTemperature
);

ESSATMAC_ErrCodes EPS1_HeatersSettingsReadReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_HeatersSettingsWriteReq(
                ReqContext_t* ctx,
                const int8_t * const ai8WriteLowBatTemperetureHeater,
                const uint8_t * const au8WriteHysteresisHeater
);

ESSATMAC_ErrCodes EPS1_ToggleOutPutReq(
                ReqContext_t* ctx,
                const EPS1_QueryControlsIndex_t eToggleOutput,
                const uint8_t u8TimeAtToggledState
);

ESSATMAC_ErrCodes EPS1_NotificationsSettingsReq(
                ReqContext_t* ctx,
                const uint8_t u8RepetitionsPeriod,
                const uint8_t u8NumberRepetitions
);

ESSATMAC_ErrCodes EPS1_GetTelemetryAltogetherReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_bload_getVersionReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes EPS1_bload_eraseFlashReq(
                ReqContext_t* ctx,
                const uint32_t u32ReqCode
);

ESSATMAC_ErrCodes EPS1_bload_writeFlashReq(
                ReqContext_t* ctx,
                const uint16_t u16Address,
                const uint8_t * const au8Data
);

ESSATMAC_ErrCodes EPS1_bload_executeReq(
                ReqContext_t* ctx,
                const uint32_t u32CRC32
);


#endif  // #ifndef __FP_EPS1PROTOCOLCLIENT_H__

