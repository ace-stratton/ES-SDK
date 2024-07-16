/*!
********************************************************************************************
* @file FP_UHFProtocolClient.h
* @brief ESSA Stack client-side public API declaration
********************************************************************************************
* @version           interface UHF v0.4
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

#ifndef __FP_UHFPROTOCOLCLIENT_H__
#define __FP_UHFPROTOCOLCLIENT_H__

#include "FP_UHFProtocolTypes.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef void (*pfUHF_WriteSCWResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteSCWResponseData_t *pResponseData);

typedef void (*pfUHF_ReadSCWResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadSCWResponseData_t *pResponseData);

typedef void (*pfUHF_WriteRfConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteRfConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadRfConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadRfConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadUpTimeResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadUpTimeResponseData_t *pResponseData);

typedef void (*pfUHF_ReadNumberOfTxPacketsResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadNumberOfTxPacketsResponseData_t *pResponseData);

typedef void (*pfUHF_ReadNumberOfRxPacketsResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadNumberOfRxPacketsResponseData_t *pResponseData);

typedef void (*pfUHF_ReadNumberOfRxPacketsCRCErrResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadNumberOfRxPacketsCRCErrResponseData_t *pResponseData);

typedef void (*pfUHF_WriteBeaconMessageTxPeriodCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteBeaconMessageTxPeriodCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadBeaconMessageTxPeriodCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadBeaconMessageTxPeriodCfgResponseData_t *pResponseData);

typedef void (*pfUHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteBeaconMessageBetweeenTxPeriodConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadBeaconMessageBetweeenTxPeriodConfigResponseData_t *pResponseData);

typedef void (*pfUHF_RestoreDefaultConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFRestoreDefaultConfigResponseData_t *pResponseData);

typedef void (*pfUHF_WriteAntennaReleaseConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteAntennaReleaseConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadAntennaReleaseConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadAntennaReleaseConfigResponseData_t *pResponseData);

typedef void (*pfUHF_WriteAntennaResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteAntennaResponseData_t *pResponseData);

typedef void (*pfUHF_ReadAntennaResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadAntennaResponseData_t *pResponseData);

typedef void (*pfUHF_EnterLPMResponseHandler_t)(RespContext_t *pRespCtx,
              UHFEnterLPMResponseData_t *pResponseData);

typedef void (*pfUHF_ReadLPMResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadLPMResponseData_t *pResponseData);

typedef void (*pfUHF_WriteDestCallSignResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteDestCallSignResponseData_t *pResponseData);

typedef void (*pfUHF_ReadDestCallSignResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadDestCallSignResponseData_t *pResponseData);

typedef void (*pfUHF_WriteSrcCallSignResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteSrcCallSignResponseData_t *pResponseData);

typedef void (*pfUHF_ReadSRCCallSignResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadSRCCallSignResponseData_t *pResponseData);

typedef void (*pfUHF_WriteMorseCallSignResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteMorseCallSignResponseData_t *pResponseData);

typedef void (*pfUHF_ReadMorseCallSignResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadMorseCallSignResponseData_t *pResponseData);

typedef void (*pfUHF_WriteMIDIAudioBeaconResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteMIDIAudioBeaconResponseData_t *pResponseData);

typedef void (*pfUHF_ReadMIDIAudioBeaconResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadMIDIAudioBeaconResponseData_t *pResponseData);

typedef void (*pfUHF_ReadSWVersionResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadSWVersionResponseData_t *pResponseData);

typedef void (*pfUHF_ReadPayloadSizeResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadPayloadSizeResponseData_t *pResponseData);

typedef void (*pfUHF_WriteBeaconMessageContentCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteBeaconMessageContentCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadBeaconMessageContentCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadBeaconMessageContentCfgResponseData_t *pResponseData);

typedef void (*pfUHF_WriteDeviceAddrConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteDeviceAddrConfigResponseData_t *pResponseData);

typedef void (*pfUHF_WriteFRAMResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteFRAMResponseData_t *pResponseData);

typedef void (*pfUHF_ReadFRAMResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadFRAMResponseData_t *pResponseData);

typedef void (*pfUHF_WriteTransPropertyResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteTransPropertyResponseData_t *pResponseData);

typedef void (*pfUHF_ReadTransPropertyResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadTransPropertyResponseData_t *pResponseData);

typedef void (*pfUHF_ReadTempResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadTempResponseData_t *pResponseData);

typedef void (*pfUHF_ReadRSSIResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadRSSIResponseData_t *pResponseData);

typedef void (*pfUHF_WriteRadioRawDataResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteRadioRawDataResponseData_t *pResponseData);

typedef void (*pfUHF_PingResponseHandler_t)(RespContext_t *pRespCtx,
              UHFPingResponseData_t *pResponseData);

typedef void (*pfUHF_ExBeaconSetSendResponseHandler_t)(RespContext_t *pRespCtx,
              UHFExBeaconSetSendResponseData_t *pResponseData);

typedef void (*pfUHF_WriteI2cConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteI2cConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadI2cConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadI2cConfigResponseData_t *pResponseData);

typedef void (*pfUHF_WriteAntennaCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteAntennaCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadAntennaCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadAntennaCfgResponseData_t *pResponseData);

typedef void (*pfUHF_WriteEpsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteEpsCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadEpsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadEpsCfgResponseData_t *pResponseData);

typedef void (*pfUHF_WriteEpsConOpsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteEpsConOpsCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadEpsConOpsCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadEpsConOpsCfgResponseData_t *pResponseData);

typedef void (*pfUHF_WriteRs485ConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteRs485ConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadRs485ConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadRs485ConfigResponseData_t *pResponseData);

typedef void (*pfUHF_WriteOBCConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteOBCConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadOBCConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadOBCConfigResponseData_t *pResponseData);

typedef void (*pfUHF_WriteSatConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteSatConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadSatConfigResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadSatConfigResponseData_t *pResponseData);

typedef void (*pfUHF_ReadEpsCfgOutResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadEpsCfgOutResponseData_t *pResponseData);

typedef void (*pfUHF_WriteEpsCfgOutResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteEpsCfgOutResponseData_t *pResponseData);

typedef void (*pfUHF_Write2UAntennaCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWrite2UAntennaCfgResponseData_t *pResponseData);

typedef void (*pfUHF_Read2UAntennaCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFRead2UAntennaCfgResponseData_t *pResponseData);

typedef void (*pfUHF_WriteAutomatedBeaconCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteAutomatedBeaconCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadAutomatedBeaconCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadAutomatedBeaconCfgResponseData_t *pResponseData);

typedef void (*pfUHF_WriteOutputPowerCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteOutputPowerCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadOutputPowerCfgResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadOutputPowerCfgResponseData_t *pResponseData);

typedef void (*pfUHF_ReadCountersResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadCountersResponseData_t *pResponseData);

typedef void (*pfUHF_WriteCipherKeySlotResponseHandler_t)(RespContext_t *pRespCtx,
              UHFWriteCipherKeySlotResponseData_t *pResponseData);

typedef void (*pfUHF_ReadCipherKeySlotStatusResponseHandler_t)(RespContext_t *pRespCtx,
              UHFReadCipherKeySlotStatusResponseData_t *pResponseData);

typedef void (*pfUHF_EraseCipherKeySlotResponseHandler_t)(RespContext_t *pRespCtx,
              UHFEraseCipherKeySlotResponseData_t *pResponseData);


typedef struct {
    pfUHF_WriteSCWResponseHandler_t UHF_WriteSCWResponseHandler;
    pfUHF_ReadSCWResponseHandler_t UHF_ReadSCWResponseHandler;
    pfUHF_WriteRfConfigResponseHandler_t UHF_WriteRfConfigResponseHandler;
    pfUHF_ReadRfConfigResponseHandler_t UHF_ReadRfConfigResponseHandler;
    pfUHF_ReadUpTimeResponseHandler_t UHF_ReadUpTimeResponseHandler;
    pfUHF_ReadNumberOfTxPacketsResponseHandler_t UHF_ReadNumberOfTxPacketsResponseHandler;
    pfUHF_ReadNumberOfRxPacketsResponseHandler_t UHF_ReadNumberOfRxPacketsResponseHandler;
    pfUHF_ReadNumberOfRxPacketsCRCErrResponseHandler_t UHF_ReadNumberOfRxPacketsCRCErrResponseHandler;
    pfUHF_WriteBeaconMessageTxPeriodCfgResponseHandler_t UHF_WriteBeaconMessageTxPeriodCfgResponseHandler;
    pfUHF_ReadBeaconMessageTxPeriodCfgResponseHandler_t UHF_ReadBeaconMessageTxPeriodCfgResponseHandler;
    pfUHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandler_t UHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandler;
    pfUHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandler_t UHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandler;
    pfUHF_RestoreDefaultConfigResponseHandler_t UHF_RestoreDefaultConfigResponseHandler;
    pfUHF_WriteAntennaReleaseConfigResponseHandler_t UHF_WriteAntennaReleaseConfigResponseHandler;
    pfUHF_ReadAntennaReleaseConfigResponseHandler_t UHF_ReadAntennaReleaseConfigResponseHandler;
    pfUHF_WriteAntennaResponseHandler_t UHF_WriteAntennaResponseHandler;
    pfUHF_ReadAntennaResponseHandler_t UHF_ReadAntennaResponseHandler;
    pfUHF_EnterLPMResponseHandler_t UHF_EnterLPMResponseHandler;
    pfUHF_ReadLPMResponseHandler_t UHF_ReadLPMResponseHandler;
    pfUHF_WriteDestCallSignResponseHandler_t UHF_WriteDestCallSignResponseHandler;
    pfUHF_ReadDestCallSignResponseHandler_t UHF_ReadDestCallSignResponseHandler;
    pfUHF_WriteSrcCallSignResponseHandler_t UHF_WriteSrcCallSignResponseHandler;
    pfUHF_ReadSRCCallSignResponseHandler_t UHF_ReadSRCCallSignResponseHandler;
    pfUHF_WriteMorseCallSignResponseHandler_t UHF_WriteMorseCallSignResponseHandler;
    pfUHF_ReadMorseCallSignResponseHandler_t UHF_ReadMorseCallSignResponseHandler;
    pfUHF_WriteMIDIAudioBeaconResponseHandler_t UHF_WriteMIDIAudioBeaconResponseHandler;
    pfUHF_ReadMIDIAudioBeaconResponseHandler_t UHF_ReadMIDIAudioBeaconResponseHandler;
    pfUHF_ReadSWVersionResponseHandler_t UHF_ReadSWVersionResponseHandler;
    pfUHF_ReadPayloadSizeResponseHandler_t UHF_ReadPayloadSizeResponseHandler;
    pfUHF_WriteBeaconMessageContentCfgResponseHandler_t UHF_WriteBeaconMessageContentCfgResponseHandler;
    pfUHF_ReadBeaconMessageContentCfgResponseHandler_t UHF_ReadBeaconMessageContentCfgResponseHandler;
    pfUHF_WriteDeviceAddrConfigResponseHandler_t UHF_WriteDeviceAddrConfigResponseHandler;
    pfUHF_WriteFRAMResponseHandler_t UHF_WriteFRAMResponseHandler;
    pfUHF_ReadFRAMResponseHandler_t UHF_ReadFRAMResponseHandler;
    pfUHF_WriteTransPropertyResponseHandler_t UHF_WriteTransPropertyResponseHandler;
    pfUHF_ReadTransPropertyResponseHandler_t UHF_ReadTransPropertyResponseHandler;
    pfUHF_ReadTempResponseHandler_t UHF_ReadTempResponseHandler;
    pfUHF_ReadRSSIResponseHandler_t UHF_ReadRSSIResponseHandler;
    pfUHF_WriteRadioRawDataResponseHandler_t UHF_WriteRadioRawDataResponseHandler;
    pfUHF_PingResponseHandler_t UHF_PingResponseHandler;
    pfUHF_ExBeaconSetSendResponseHandler_t UHF_ExBeaconSetSendResponseHandler;
    pfUHF_WriteI2cConfigResponseHandler_t UHF_WriteI2cConfigResponseHandler;
    pfUHF_ReadI2cConfigResponseHandler_t UHF_ReadI2cConfigResponseHandler;
    pfUHF_WriteAntennaCfgResponseHandler_t UHF_WriteAntennaCfgResponseHandler;
    pfUHF_ReadAntennaCfgResponseHandler_t UHF_ReadAntennaCfgResponseHandler;
    pfUHF_WriteEpsCfgResponseHandler_t UHF_WriteEpsCfgResponseHandler;
    pfUHF_ReadEpsCfgResponseHandler_t UHF_ReadEpsCfgResponseHandler;
    pfUHF_WriteEpsConOpsCfgResponseHandler_t UHF_WriteEpsConOpsCfgResponseHandler;
    pfUHF_ReadEpsConOpsCfgResponseHandler_t UHF_ReadEpsConOpsCfgResponseHandler;
    pfUHF_WriteRs485ConfigResponseHandler_t UHF_WriteRs485ConfigResponseHandler;
    pfUHF_ReadRs485ConfigResponseHandler_t UHF_ReadRs485ConfigResponseHandler;
    pfUHF_WriteOBCConfigResponseHandler_t UHF_WriteOBCConfigResponseHandler;
    pfUHF_ReadOBCConfigResponseHandler_t UHF_ReadOBCConfigResponseHandler;
    pfUHF_WriteSatConfigResponseHandler_t UHF_WriteSatConfigResponseHandler;
    pfUHF_ReadSatConfigResponseHandler_t UHF_ReadSatConfigResponseHandler;
    pfUHF_ReadEpsCfgOutResponseHandler_t UHF_ReadEpsCfgOutResponseHandler;
    pfUHF_WriteEpsCfgOutResponseHandler_t UHF_WriteEpsCfgOutResponseHandler;
    pfUHF_Write2UAntennaCfgResponseHandler_t UHF_Write2UAntennaCfgResponseHandler;
    pfUHF_Read2UAntennaCfgResponseHandler_t UHF_Read2UAntennaCfgResponseHandler;
    pfUHF_WriteAutomatedBeaconCfgResponseHandler_t UHF_WriteAutomatedBeaconCfgResponseHandler;
    pfUHF_ReadAutomatedBeaconCfgResponseHandler_t UHF_ReadAutomatedBeaconCfgResponseHandler;
    pfUHF_WriteOutputPowerCfgResponseHandler_t UHF_WriteOutputPowerCfgResponseHandler;
    pfUHF_ReadOutputPowerCfgResponseHandler_t UHF_ReadOutputPowerCfgResponseHandler;
    pfUHF_ReadCountersResponseHandler_t UHF_ReadCountersResponseHandler;
    pfUHF_WriteCipherKeySlotResponseHandler_t UHF_WriteCipherKeySlotResponseHandler;
    pfUHF_ReadCipherKeySlotStatusResponseHandler_t UHF_ReadCipherKeySlotStatusResponseHandler;
    pfUHF_EraseCipherKeySlotResponseHandler_t UHF_EraseCipherKeySlotResponseHandler;
} UHF_ClientApi_t;

/**********************************************************************
 *
 *  Client protocol ESSA descriptor
 *
 **********************************************************************/
extern const ESSA_Stack_FunctionProtocolInfo_t FP_UHFProtocolClientInfo;

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
void UHF_registerClientApi(UHF_ClientApi_t *pCliApiHandlers);

// @deprecated - will be removed in the future - use FP_UHFProtocolClientInfo directly
ESSA_pStack_FunctionProtocolInfo_t UHF_getClientProtocolDescriptor(void);

ESSATMAC_ErrCodes UHF_WriteSCWReq(
                ReqContext_t* ctx,
                const UHF_StatusControlWord_t * const sScw
);

ESSATMAC_ErrCodes UHF_ReadSCWReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteRfConfigReq(
                ReqContext_t* ctx,
                const UHF_sRFConfig_t * const sRfConfig
);

ESSATMAC_ErrCodes UHF_ReadRfConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadUpTimeReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadNumberOfTxPacketsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadNumberOfRxPacketsReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadNumberOfRxPacketsCRCErrReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteBeaconMessageTxPeriodCfgReq(
                ReqContext_t* ctx,
                const UHF_sBeaconMessageTxPeriodCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadBeaconMessageTxPeriodCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteBeaconMessageBetweeenTxPeriodConfigReq(
                ReqContext_t* ctx,
                const UHF_sBeaconMessageBetweenTxPeriodCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadBeaconMessageBetweeenTxPeriodConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_RestoreDefaultConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteAntennaReleaseConfigReq(
                ReqContext_t* ctx,
                const UHF_sAntennaReleaseCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadAntennaReleaseConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteAntennaReq(
                ReqContext_t* ctx,
                const uint8_t u8Algorithm
);

ESSATMAC_ErrCodes UHF_ReadAntennaReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_EnterLPMReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadLPMReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteDestCallSignReq(
                ReqContext_t* ctx,
                const UHF_sCallSign_t * const sCallSign
);

ESSATMAC_ErrCodes UHF_ReadDestCallSignReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteSrcCallSignReq(
                ReqContext_t* ctx,
                const UHF_sCallSign_t * const sCallSign
);

ESSATMAC_ErrCodes UHF_ReadSRCCallSignReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteMorseCallSignReq(
                ReqContext_t* ctx,
                const UHF_sMorseCallSign_t * const sMorseCallSign
);

ESSATMAC_ErrCodes UHF_ReadMorseCallSignReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteMIDIAudioBeaconReq(
                ReqContext_t* ctx,
                const UHF_sMidiAudioBeacon_t * const sMidi
);

ESSATMAC_ErrCodes UHF_ReadMIDIAudioBeaconReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadSWVersionReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadPayloadSizeReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteBeaconMessageContentCfgReq(
                ReqContext_t* ctx,
                const UHF_sBeaconMessageContentCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadBeaconMessageContentCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteDeviceAddrConfigReq(
                ReqContext_t* ctx,
                const UHF_sAddrCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_WriteFRAMReq(
                ReqContext_t* ctx,
                const UHF_sFramData_t * const sFramWriteReq
);

ESSATMAC_ErrCodes UHF_ReadFRAMReq(
                ReqContext_t* ctx,
                const uint32_t u32Addr
);

ESSATMAC_ErrCodes UHF_WriteTransPropertyReq(
                ReqContext_t* ctx,
                const UHF_sTransceiverProperty_t * const sProperty
);

ESSATMAC_ErrCodes UHF_ReadTransPropertyReq(
                ReqContext_t* ctx,
                const UHF_sReadTransceiverProperty_t * const sProperty
);

ESSATMAC_ErrCodes UHF_ReadTempReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadRSSIReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteRadioRawDataReq(
                ReqContext_t* ctx,
                const UHF_sRadioRawData_t * const sData
);

ESSATMAC_ErrCodes UHF_PingReq(
                ReqContext_t* ctx,
                const UHF_sPing_t * const sData
);

ESSATMAC_ErrCodes UHF_ExBeaconSetSendReq(
                ReqContext_t* ctx,
                const UHF_sExBeacon_t * const sData
);

ESSATMAC_ErrCodes UHF_WriteI2cConfigReq(
                ReqContext_t* ctx,
                const UHF_sI2cCfg_t * const sData
);

ESSATMAC_ErrCodes UHF_ReadI2cConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteAntennaCfgReq(
                ReqContext_t* ctx,
                const UHF_sAntennaCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadAntennaCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteEpsCfgReq(
                ReqContext_t* ctx,
                const UHF_sEpsCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadEpsCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteEpsConOpsCfgReq(
                ReqContext_t* ctx,
                const UHF_sEpsConOpsCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadEpsConOpsCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteRs485ConfigReq(
                ReqContext_t* ctx,
                const UHF_sRS485Cfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadRs485ConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteOBCConfigReq(
                ReqContext_t* ctx,
                const UHF_sObcCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadOBCConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteSatConfigReq(
                ReqContext_t* ctx,
                const UHF_sSatCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadSatConfigReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadEpsCfgOutReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteEpsCfgOutReq(
                ReqContext_t* ctx,
                const UHF_sEpsOutCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_Write2UAntennaCfgReq(
                ReqContext_t* ctx,
                const UHF_s2UAntennaCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_Read2UAntennaCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteAutomatedBeaconCfgReq(
                ReqContext_t* ctx,
                const UHF_sAutomatedBeaconCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadAutomatedBeaconCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteOutputPowerCfgReq(
                ReqContext_t* ctx,
                const UHF_sOutputPowerCfg_t * const sCfg
);

ESSATMAC_ErrCodes UHF_ReadOutputPowerCfgReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_ReadCountersReq(
                ReqContext_t* ctx);

ESSATMAC_ErrCodes UHF_WriteCipherKeySlotReq(
                ReqContext_t* ctx,
                const UHF_sCipherKeySlot_t * const sSKeySlot
);

ESSATMAC_ErrCodes UHF_ReadCipherKeySlotStatusReq(
                ReqContext_t* ctx,
                const uint8_t u8SlotId
);

ESSATMAC_ErrCodes UHF_EraseCipherKeySlotReq(
                ReqContext_t* ctx,
                const UHF_sCipherKeySlot_t * const sSKeySlot
);


#endif  // #ifndef __FP_UHFPROTOCOLCLIENT_H__

