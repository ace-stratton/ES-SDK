/*!
********************************************************************************************
* @file FP_SBAND_TMTCProtocolClient.h
* @brief ESSA Stack client-side public API declaration
********************************************************************************************
* @version           interface SBAND_TMTC v1.1
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

#ifndef __FP_SBAND_TMTCPROTOCOLCLIENT_H__
#define __FP_SBAND_TMTCPROTOCOLCLIENT_H__

#include "FP_SBAND_TMTCProtocolTypes.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef void (*pfSBAND_TMTC_GetCapabilitiesResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetCapabilitiesResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadUpTimeResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadUpTimeResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadHWHealthResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadHWHealthResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadEpsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadEpsCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteEpsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteEpsCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadAutomatedBeaconsCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteAutomatedBeaconsCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadErrorCountersResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadErrorCountersResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadPipeModeCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadPipeModeCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WritePipeModeCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWritePipeModeCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadTxtBeaconContentCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadTxtBeaconContentCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteTxtBeaconContentCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteTxtBeaconContentCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadAx25CfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadAx25CfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteAx25CfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteAx25CfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteCipherKeySlotResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteCipherKeySlotResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadCipherKeySlotStatusResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadCipherKeySlotStatusResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_EraseCipherKeySlotResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCEraseCipherKeySlotResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadConOps_HystCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadConOps_HystCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteConOps_HystCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteConOps_HystCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadPortCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadPortCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WritePortCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWritePortCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadLoggerCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadLoggerCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteLoggerCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteLoggerCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_TransmitDataResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCTransmitDataResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_LoadPresetCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCLoadPresetCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_PingResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCPingResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetDualPAModeResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCSetDualPAModeResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetDualPAModeResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetDualPAModeResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetTestPacketStateResponseHandler_t)(RespContext_t *pRespCtx);

typedef void (*pfSBAND_TMTC_ReadRfFreqCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadRfFreqCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteRfFreqCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteRfFreqCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ResetResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCResetResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ResetErrorCountersResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCResetErrorCountersResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadSatCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadSatCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteSatCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteSatCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadTCResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadTCResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ClearTCResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCClearTCResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadTempSensorsResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadTempSensorsResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_Ignore_PA_TSResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCIgnore_PA_TSResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadRadioCRCCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadRadioCRCCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteRadioCRCCfgResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteRadioCRCCfgResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_WriteRadioPacketFecHdlcResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCWriteRadioPacketFecHdlcResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadRadioPacketFecHdlcResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadRadioPacketFecHdlcResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetPacketCountersResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetPacketCountersResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_ReadRadioErrorsResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCReadRadioErrorsResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetModulationResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetModulationResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetModulationResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCSetModulationResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetBaudrateResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetBaudrateResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetBaudrateResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCSetBaudrateResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetFreqShapingResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetFreqShapingResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetFreqShapingResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCSetFreqShapingResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetStreamModeResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetStreamModeResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetStreamModeResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCSetStreamModeResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetTargetPowerResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetTargetPowerResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetTargetPowerResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCSetTargetPowerResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_GetPacketScramblerResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCGetPacketScramblerResponseData_t *pResponseData);

typedef void (*pfSBAND_TMTC_SetPacketScramblerResponseHandler_t)(RespContext_t *pRespCtx,
              SBAND_TMTCSetPacketScramblerResponseData_t *pResponseData);


typedef struct {
    pfSBAND_TMTC_GetCapabilitiesResponseHandler_t SBAND_TMTC_GetCapabilitiesResponseHandler;
    pfSBAND_TMTC_ReadUpTimeResponseHandler_t SBAND_TMTC_ReadUpTimeResponseHandler;
    pfSBAND_TMTC_ReadHWHealthResponseHandler_t SBAND_TMTC_ReadHWHealthResponseHandler;
    pfSBAND_TMTC_ReadEpsCfgResponseHandler_t SBAND_TMTC_ReadEpsCfgResponseHandler;
    pfSBAND_TMTC_WriteEpsCfgResponseHandler_t SBAND_TMTC_WriteEpsCfgResponseHandler;
    pfSBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandler_t SBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandler;
    pfSBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandler_t SBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandler;
    pfSBAND_TMTC_ReadErrorCountersResponseHandler_t SBAND_TMTC_ReadErrorCountersResponseHandler;
    pfSBAND_TMTC_ReadPipeModeCfgResponseHandler_t SBAND_TMTC_ReadPipeModeCfgResponseHandler;
    pfSBAND_TMTC_WritePipeModeCfgResponseHandler_t SBAND_TMTC_WritePipeModeCfgResponseHandler;
    pfSBAND_TMTC_ReadTxtBeaconContentCfgResponseHandler_t SBAND_TMTC_ReadTxtBeaconContentCfgResponseHandler;
    pfSBAND_TMTC_WriteTxtBeaconContentCfgResponseHandler_t SBAND_TMTC_WriteTxtBeaconContentCfgResponseHandler;
    pfSBAND_TMTC_ReadAx25CfgResponseHandler_t SBAND_TMTC_ReadAx25CfgResponseHandler;
    pfSBAND_TMTC_WriteAx25CfgResponseHandler_t SBAND_TMTC_WriteAx25CfgResponseHandler;
    pfSBAND_TMTC_WriteCipherKeySlotResponseHandler_t SBAND_TMTC_WriteCipherKeySlotResponseHandler;
    pfSBAND_TMTC_ReadCipherKeySlotStatusResponseHandler_t SBAND_TMTC_ReadCipherKeySlotStatusResponseHandler;
    pfSBAND_TMTC_EraseCipherKeySlotResponseHandler_t SBAND_TMTC_EraseCipherKeySlotResponseHandler;
    pfSBAND_TMTC_ReadConOps_HystCfgResponseHandler_t SBAND_TMTC_ReadConOps_HystCfgResponseHandler;
    pfSBAND_TMTC_WriteConOps_HystCfgResponseHandler_t SBAND_TMTC_WriteConOps_HystCfgResponseHandler;
    pfSBAND_TMTC_ReadPortCfgResponseHandler_t SBAND_TMTC_ReadPortCfgResponseHandler;
    pfSBAND_TMTC_WritePortCfgResponseHandler_t SBAND_TMTC_WritePortCfgResponseHandler;
    pfSBAND_TMTC_ReadLoggerCfgResponseHandler_t SBAND_TMTC_ReadLoggerCfgResponseHandler;
    pfSBAND_TMTC_WriteLoggerCfgResponseHandler_t SBAND_TMTC_WriteLoggerCfgResponseHandler;
    pfSBAND_TMTC_TransmitDataResponseHandler_t SBAND_TMTC_TransmitDataResponseHandler;
    pfSBAND_TMTC_LoadPresetCfgResponseHandler_t SBAND_TMTC_LoadPresetCfgResponseHandler;
    pfSBAND_TMTC_PingResponseHandler_t SBAND_TMTC_PingResponseHandler;
    pfSBAND_TMTC_SetDualPAModeResponseHandler_t SBAND_TMTC_SetDualPAModeResponseHandler;
    pfSBAND_TMTC_GetDualPAModeResponseHandler_t SBAND_TMTC_GetDualPAModeResponseHandler;
    pfSBAND_TMTC_SetTestPacketStateResponseHandler_t SBAND_TMTC_SetTestPacketStateResponseHandler;
    pfSBAND_TMTC_ReadRfFreqCfgResponseHandler_t SBAND_TMTC_ReadRfFreqCfgResponseHandler;
    pfSBAND_TMTC_WriteRfFreqCfgResponseHandler_t SBAND_TMTC_WriteRfFreqCfgResponseHandler;
    pfSBAND_TMTC_ResetResponseHandler_t SBAND_TMTC_ResetResponseHandler;
    pfSBAND_TMTC_ResetErrorCountersResponseHandler_t SBAND_TMTC_ResetErrorCountersResponseHandler;
    pfSBAND_TMTC_ReadSatCfgResponseHandler_t SBAND_TMTC_ReadSatCfgResponseHandler;
    pfSBAND_TMTC_WriteSatCfgResponseHandler_t SBAND_TMTC_WriteSatCfgResponseHandler;
    pfSBAND_TMTC_ReadTCResponseHandler_t SBAND_TMTC_ReadTCResponseHandler;
    pfSBAND_TMTC_ClearTCResponseHandler_t SBAND_TMTC_ClearTCResponseHandler;
    pfSBAND_TMTC_ReadTempSensorsResponseHandler_t SBAND_TMTC_ReadTempSensorsResponseHandler;
    pfSBAND_TMTC_Ignore_PA_TSResponseHandler_t SBAND_TMTC_Ignore_PA_TSResponseHandler;
    pfSBAND_TMTC_ReadRadioCRCCfgResponseHandler_t SBAND_TMTC_ReadRadioCRCCfgResponseHandler;
    pfSBAND_TMTC_WriteRadioCRCCfgResponseHandler_t SBAND_TMTC_WriteRadioCRCCfgResponseHandler;
    pfSBAND_TMTC_WriteRadioPacketFecHdlcResponseHandler_t SBAND_TMTC_WriteRadioPacketFecHdlcResponseHandler;
    pfSBAND_TMTC_ReadRadioPacketFecHdlcResponseHandler_t SBAND_TMTC_ReadRadioPacketFecHdlcResponseHandler;
    pfSBAND_TMTC_GetPacketCountersResponseHandler_t SBAND_TMTC_GetPacketCountersResponseHandler;
    pfSBAND_TMTC_ReadRadioErrorsResponseHandler_t SBAND_TMTC_ReadRadioErrorsResponseHandler;
    pfSBAND_TMTC_GetModulationResponseHandler_t SBAND_TMTC_GetModulationResponseHandler;
    pfSBAND_TMTC_SetModulationResponseHandler_t SBAND_TMTC_SetModulationResponseHandler;
    pfSBAND_TMTC_GetBaudrateResponseHandler_t SBAND_TMTC_GetBaudrateResponseHandler;
    pfSBAND_TMTC_SetBaudrateResponseHandler_t SBAND_TMTC_SetBaudrateResponseHandler;
    pfSBAND_TMTC_GetFreqShapingResponseHandler_t SBAND_TMTC_GetFreqShapingResponseHandler;
    pfSBAND_TMTC_SetFreqShapingResponseHandler_t SBAND_TMTC_SetFreqShapingResponseHandler;
    pfSBAND_TMTC_GetStreamModeResponseHandler_t SBAND_TMTC_GetStreamModeResponseHandler;
    pfSBAND_TMTC_SetStreamModeResponseHandler_t SBAND_TMTC_SetStreamModeResponseHandler;
    pfSBAND_TMTC_GetTargetPowerResponseHandler_t SBAND_TMTC_GetTargetPowerResponseHandler;
    pfSBAND_TMTC_SetTargetPowerResponseHandler_t SBAND_TMTC_SetTargetPowerResponseHandler;
    pfSBAND_TMTC_GetPacketScramblerResponseHandler_t SBAND_TMTC_GetPacketScramblerResponseHandler;
    pfSBAND_TMTC_SetPacketScramblerResponseHandler_t SBAND_TMTC_SetPacketScramblerResponseHandler;
} SBAND_TMTC_ClientApi_t;

/**********************************************************************
 *
 *  Client protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_SBAND_TMTCProtocolClientInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void SBAND_TMTC_registerClientApi(SBAND_TMTC_ClientApi_t *pCliApiHandlers);

// @deprecated - will be removed in the future - use FP_SBAND_TMTCProtocolClientInfo directly
ESSA_pStack_FunctionProtocolInfo_t SBAND_TMTC_getClientProtocolDescriptor(void);

ESSATMAC_ErrCodes SBAND_TMTC_GetCapabilitiesReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadUpTimeReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadHWHealthReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadEpsCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteEpsCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sEpsCfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadAutomatedBeaconsCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteAutomatedBeaconsCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sAutoBeaconsCfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadErrorCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadPipeModeCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WritePipeModeCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sPipeModeCfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadTxtBeaconContentCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteTxtBeaconContentCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sTxtBeaconContentCfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadAx25CfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteAx25CfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sAx25Cfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_WriteCipherKeySlotReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sCipherKeySlot_t * const sSKeySlot
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadCipherKeySlotStatusReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eKeySlotID_t eSlotId
);

ESSATMAC_ErrCodes SBAND_TMTC_EraseCipherKeySlotReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sCipherKeySlot_t * const sSKeySlot
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadConOps_HystCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteConOps_HystCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sConOps_Hysteresis_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadPortCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_ePortID_t ePortID
);

ESSATMAC_ErrCodes SBAND_TMTC_WritePortCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sCommPortCfgIn_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadLoggerCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteLoggerCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sLogger_Cfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_TransmitDataReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sTxRadioMsg_t * const sMsg
);

ESSATMAC_ErrCodes SBAND_TMTC_LoadPresetCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_ePresetCfgType_t eCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_PingReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sPing_t * const sData
);

ESSATMAC_ErrCodes SBAND_TMTC_SetDualPAModeReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_ePowerAmpControl_t eCtl
);

ESSATMAC_ErrCodes SBAND_TMTC_GetDualPAModeReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_SetTestPacketStateReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sTestPacket_t * const sTp
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadRfFreqCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteRfFreqCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sRfFreqCfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ResetReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ResetErrorCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadSatCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteSatCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sSatCfg_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadTCReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ClearTCReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadTempSensorsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_Ignore_PA_TSReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadRadioCRCCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_WriteRadioCRCCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sRadioCRC_t * const sCfg
);

ESSATMAC_ErrCodes SBAND_TMTC_WriteRadioPacketFecHdlcReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eOnOff_t eOnoff
);

ESSATMAC_ErrCodes SBAND_TMTC_ReadRadioPacketFecHdlcReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_GetPacketCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_ReadRadioErrorsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_GetModulationReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_SetModulationReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_Modulation_t eM
);

ESSATMAC_ErrCodes SBAND_TMTC_GetBaudrateReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_SetBaudrateReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_Baudrate_t eB
);

ESSATMAC_ErrCodes SBAND_TMTC_GetFreqShapingReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_SetFreqShapingReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_Filtering_t eF
);

ESSATMAC_ErrCodes SBAND_TMTC_GetStreamModeReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_SetStreamModeReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eOnOff_t eS
);

ESSATMAC_ErrCodes SBAND_TMTC_GetTargetPowerReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_SetTargetPowerReq(
                ReqContext_t* ctx,
                const uint16_t u16Power
);

ESSATMAC_ErrCodes SBAND_TMTC_GetPacketScramblerReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes SBAND_TMTC_SetPacketScramblerReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eOnOff_t eS
);


#endif  // #ifndef __FP_SBAND_TMTCPROTOCOLCLIENT_H__

