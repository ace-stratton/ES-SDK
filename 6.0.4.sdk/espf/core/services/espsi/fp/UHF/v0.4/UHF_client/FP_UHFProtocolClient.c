/*!
********************************************************************************************
* @file FP_UHFProtocolClient.c
* @brief ESSA Stack client-side implementation
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

#include "FP_UHFProtocolClient.h"

#define UHF_PROTOCOL_VERSION_MAJOR   ((uint8_t) 0)
#define UHF_PROTOCOL_VERSION_MINOR   ((uint8_t) 4)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteSCWRequestData_t data;
} PACKED_STRUCT UHFWriteSCWProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteSCWResponseData_t data;
} PACKED_STRUCT UHFWriteSCWProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadSCWProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadSCWResponseData_t data;
} PACKED_STRUCT UHFReadSCWProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteRfConfigRequestData_t data;
} PACKED_STRUCT UHFWriteRfConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteRfConfigResponseData_t data;
} PACKED_STRUCT UHFWriteRfConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadRfConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadRfConfigResponseData_t data;
} PACKED_STRUCT UHFReadRfConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadUpTimeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadUpTimeResponseData_t data;
} PACKED_STRUCT UHFReadUpTimeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadNumberOfTxPacketsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadNumberOfTxPacketsResponseData_t data;
} PACKED_STRUCT UHFReadNumberOfTxPacketsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadNumberOfRxPacketsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadNumberOfRxPacketsResponseData_t data;
} PACKED_STRUCT UHFReadNumberOfRxPacketsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadNumberOfRxPacketsCRCErrProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadNumberOfRxPacketsCRCErrResponseData_t data;
} PACKED_STRUCT UHFReadNumberOfRxPacketsCRCErrProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteBeaconMessageTxPeriodCfgRequestData_t data;
} PACKED_STRUCT UHFWriteBeaconMessageTxPeriodCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteBeaconMessageTxPeriodCfgResponseData_t data;
} PACKED_STRUCT UHFWriteBeaconMessageTxPeriodCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadBeaconMessageTxPeriodCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadBeaconMessageTxPeriodCfgResponseData_t data;
} PACKED_STRUCT UHFReadBeaconMessageTxPeriodCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteBeaconMessageBetweeenTxPeriodConfigRequestData_t data;
} PACKED_STRUCT UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteBeaconMessageBetweeenTxPeriodConfigResponseData_t data;
} PACKED_STRUCT UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadBeaconMessageBetweeenTxPeriodConfigResponseData_t data;
} PACKED_STRUCT UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFRestoreDefaultConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFRestoreDefaultConfigResponseData_t data;
} PACKED_STRUCT UHFRestoreDefaultConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAntennaReleaseConfigRequestData_t data;
} PACKED_STRUCT UHFWriteAntennaReleaseConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAntennaReleaseConfigResponseData_t data;
} PACKED_STRUCT UHFWriteAntennaReleaseConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadAntennaReleaseConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadAntennaReleaseConfigResponseData_t data;
} PACKED_STRUCT UHFReadAntennaReleaseConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAntennaRequestData_t data;
} PACKED_STRUCT UHFWriteAntennaProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAntennaResponseData_t data;
} PACKED_STRUCT UHFWriteAntennaProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadAntennaProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadAntennaResponseData_t data;
} PACKED_STRUCT UHFReadAntennaProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFEnterLPMProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFEnterLPMResponseData_t data;
} PACKED_STRUCT UHFEnterLPMProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadLPMProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadLPMResponseData_t data;
} PACKED_STRUCT UHFReadLPMProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteDestCallSignRequestData_t data;
} PACKED_STRUCT UHFWriteDestCallSignProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteDestCallSignResponseData_t data;
} PACKED_STRUCT UHFWriteDestCallSignProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadDestCallSignProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadDestCallSignResponseData_t data;
} PACKED_STRUCT UHFReadDestCallSignProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteSrcCallSignRequestData_t data;
} PACKED_STRUCT UHFWriteSrcCallSignProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteSrcCallSignResponseData_t data;
} PACKED_STRUCT UHFWriteSrcCallSignProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadSRCCallSignProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadSRCCallSignResponseData_t data;
} PACKED_STRUCT UHFReadSRCCallSignProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteMorseCallSignRequestData_t data;
} PACKED_STRUCT UHFWriteMorseCallSignProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteMorseCallSignResponseData_t data;
} PACKED_STRUCT UHFWriteMorseCallSignProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadMorseCallSignProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadMorseCallSignResponseData_t data;
} PACKED_STRUCT UHFReadMorseCallSignProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteMIDIAudioBeaconRequestData_t data;
} PACKED_STRUCT UHFWriteMIDIAudioBeaconProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteMIDIAudioBeaconResponseData_t data;
} PACKED_STRUCT UHFWriteMIDIAudioBeaconProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadMIDIAudioBeaconProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadMIDIAudioBeaconResponseData_t data;
} PACKED_STRUCT UHFReadMIDIAudioBeaconProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadSWVersionProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadSWVersionResponseData_t data;
} PACKED_STRUCT UHFReadSWVersionProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadPayloadSizeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadPayloadSizeResponseData_t data;
} PACKED_STRUCT UHFReadPayloadSizeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteBeaconMessageContentCfgRequestData_t data;
} PACKED_STRUCT UHFWriteBeaconMessageContentCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteBeaconMessageContentCfgResponseData_t data;
} PACKED_STRUCT UHFWriteBeaconMessageContentCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadBeaconMessageContentCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadBeaconMessageContentCfgResponseData_t data;
} PACKED_STRUCT UHFReadBeaconMessageContentCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteDeviceAddrConfigRequestData_t data;
} PACKED_STRUCT UHFWriteDeviceAddrConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteDeviceAddrConfigResponseData_t data;
} PACKED_STRUCT UHFWriteDeviceAddrConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteFRAMRequestData_t data;
} PACKED_STRUCT UHFWriteFRAMProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteFRAMResponseData_t data;
} PACKED_STRUCT UHFWriteFRAMProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadFRAMRequestData_t data;
} PACKED_STRUCT UHFReadFRAMProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadFRAMResponseData_t data;
} PACKED_STRUCT UHFReadFRAMProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteTransPropertyRequestData_t data;
} PACKED_STRUCT UHFWriteTransPropertyProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteTransPropertyResponseData_t data;
} PACKED_STRUCT UHFWriteTransPropertyProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadTransPropertyRequestData_t data;
} PACKED_STRUCT UHFReadTransPropertyProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadTransPropertyResponseData_t data;
} PACKED_STRUCT UHFReadTransPropertyProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadTempProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadTempResponseData_t data;
} PACKED_STRUCT UHFReadTempProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadRSSIProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadRSSIResponseData_t data;
} PACKED_STRUCT UHFReadRSSIProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteRadioRawDataRequestData_t data;
} PACKED_STRUCT UHFWriteRadioRawDataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteRadioRawDataResponseData_t data;
} PACKED_STRUCT UHFWriteRadioRawDataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFPingRequestData_t data;
} PACKED_STRUCT UHFPingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFPingResponseData_t data;
} PACKED_STRUCT UHFPingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFExBeaconSetSendRequestData_t data;
} PACKED_STRUCT UHFExBeaconSetSendProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFExBeaconSetSendResponseData_t data;
} PACKED_STRUCT UHFExBeaconSetSendProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteI2cConfigRequestData_t data;
} PACKED_STRUCT UHFWriteI2cConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteI2cConfigResponseData_t data;
} PACKED_STRUCT UHFWriteI2cConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadI2cConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadI2cConfigResponseData_t data;
} PACKED_STRUCT UHFReadI2cConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAntennaCfgRequestData_t data;
} PACKED_STRUCT UHFWriteAntennaCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAntennaCfgResponseData_t data;
} PACKED_STRUCT UHFWriteAntennaCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadAntennaCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadAntennaCfgResponseData_t data;
} PACKED_STRUCT UHFReadAntennaCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteEpsCfgRequestData_t data;
} PACKED_STRUCT UHFWriteEpsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteEpsCfgResponseData_t data;
} PACKED_STRUCT UHFWriteEpsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadEpsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadEpsCfgResponseData_t data;
} PACKED_STRUCT UHFReadEpsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteEpsConOpsCfgRequestData_t data;
} PACKED_STRUCT UHFWriteEpsConOpsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteEpsConOpsCfgResponseData_t data;
} PACKED_STRUCT UHFWriteEpsConOpsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadEpsConOpsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadEpsConOpsCfgResponseData_t data;
} PACKED_STRUCT UHFReadEpsConOpsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteRs485ConfigRequestData_t data;
} PACKED_STRUCT UHFWriteRs485ConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteRs485ConfigResponseData_t data;
} PACKED_STRUCT UHFWriteRs485ConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadRs485ConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadRs485ConfigResponseData_t data;
} PACKED_STRUCT UHFReadRs485ConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteOBCConfigRequestData_t data;
} PACKED_STRUCT UHFWriteOBCConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteOBCConfigResponseData_t data;
} PACKED_STRUCT UHFWriteOBCConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadOBCConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadOBCConfigResponseData_t data;
} PACKED_STRUCT UHFReadOBCConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteSatConfigRequestData_t data;
} PACKED_STRUCT UHFWriteSatConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteSatConfigResponseData_t data;
} PACKED_STRUCT UHFWriteSatConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadSatConfigProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadSatConfigResponseData_t data;
} PACKED_STRUCT UHFReadSatConfigProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadEpsCfgOutProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadEpsCfgOutResponseData_t data;
} PACKED_STRUCT UHFReadEpsCfgOutProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteEpsCfgOutRequestData_t data;
} PACKED_STRUCT UHFWriteEpsCfgOutProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteEpsCfgOutResponseData_t data;
} PACKED_STRUCT UHFWriteEpsCfgOutProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWrite2UAntennaCfgRequestData_t data;
} PACKED_STRUCT UHFWrite2UAntennaCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWrite2UAntennaCfgResponseData_t data;
} PACKED_STRUCT UHFWrite2UAntennaCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFRead2UAntennaCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFRead2UAntennaCfgResponseData_t data;
} PACKED_STRUCT UHFRead2UAntennaCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAutomatedBeaconCfgRequestData_t data;
} PACKED_STRUCT UHFWriteAutomatedBeaconCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteAutomatedBeaconCfgResponseData_t data;
} PACKED_STRUCT UHFWriteAutomatedBeaconCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadAutomatedBeaconCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadAutomatedBeaconCfgResponseData_t data;
} PACKED_STRUCT UHFReadAutomatedBeaconCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteOutputPowerCfgRequestData_t data;
} PACKED_STRUCT UHFWriteOutputPowerCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteOutputPowerCfgResponseData_t data;
} PACKED_STRUCT UHFWriteOutputPowerCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadOutputPowerCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadOutputPowerCfgResponseData_t data;
} PACKED_STRUCT UHFReadOutputPowerCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT UHFReadCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadCountersResponseData_t data;
} PACKED_STRUCT UHFReadCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteCipherKeySlotRequestData_t data;
} PACKED_STRUCT UHFWriteCipherKeySlotProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFWriteCipherKeySlotResponseData_t data;
} PACKED_STRUCT UHFWriteCipherKeySlotProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadCipherKeySlotStatusRequestData_t data;
} PACKED_STRUCT UHFReadCipherKeySlotStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFReadCipherKeySlotStatusResponseData_t data;
} PACKED_STRUCT UHFReadCipherKeySlotStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFEraseCipherKeySlotRequestData_t data;
} PACKED_STRUCT UHFEraseCipherKeySlotProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    UHFEraseCipherKeySlotResponseData_t data;
} PACKED_STRUCT UHFEraseCipherKeySlotProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteSCWResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadSCWResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteRfConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadRfConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadUpTimeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadNumberOfTxPacketsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadNumberOfRxPacketsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadNumberOfRxPacketsCRCErrResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteBeaconMessageTxPeriodCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadBeaconMessageTxPeriodCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteBeaconMessageBetweeenTxPeriodConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadBeaconMessageBetweeenTxPeriodConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_RestoreDefaultConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteAntennaReleaseConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadAntennaReleaseConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteAntennaResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadAntennaResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_EnterLPMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadLPMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteDestCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadDestCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteSrcCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadSRCCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteMorseCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadMorseCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteMIDIAudioBeaconResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadMIDIAudioBeaconResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadSWVersionResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadPayloadSizeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteBeaconMessageContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadBeaconMessageContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteDeviceAddrConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteFRAMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadFRAMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteTransPropertyResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadTransPropertyResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadTempResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadRSSIResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteRadioRawDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_PingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ExBeaconSetSendResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteI2cConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadI2cConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteEpsConOpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadEpsConOpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteRs485ConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadRs485ConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteOBCConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadOBCConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteSatConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadSatConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadEpsCfgOutResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteEpsCfgOutResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_Write2UAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_Read2UAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteAutomatedBeaconCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadAutomatedBeaconCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteOutputPowerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadOutputPowerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadCipherKeySlotStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_EraseCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_UHFProtocolClientInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_UHF,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static UHF_ClientApi_t *pCliApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { UHF_WRITESCW_FUNCRESP_ID, fs_WriteSCWResp },
    { UHF_READSCW_FUNCRESP_ID, fs_ReadSCWResp },
    { UHF_WRITERFCONFIG_FUNCRESP_ID, fs_WriteRfConfigResp },
    { UHF_READRFCONFIG_FUNCRESP_ID, fs_ReadRfConfigResp },
    { UHF_READUPTIME_FUNCRESP_ID, fs_ReadUpTimeResp },
    { UHF_READNUMBEROFTXPACKETS_FUNCRESP_ID, fs_ReadNumberOfTxPacketsResp },
    { UHF_READNUMBEROFRXPACKETS_FUNCRESP_ID, fs_ReadNumberOfRxPacketsResp },
    { UHF_READNUMBEROFRXPACKETSCRCERR_FUNCRESP_ID, fs_ReadNumberOfRxPacketsCRCErrResp },
    { UHF_WRITEBEACONMESSAGETXPERIODCFG_FUNCRESP_ID, fs_WriteBeaconMessageTxPeriodCfgResp },
    { UHF_READBEACONMESSAGETXPERIODCFG_FUNCRESP_ID, fs_ReadBeaconMessageTxPeriodCfgResp },
    { UHF_WRITEBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNCRESP_ID, fs_WriteBeaconMessageBetweeenTxPeriodConfigResp },
    { UHF_READBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNCRESP_ID, fs_ReadBeaconMessageBetweeenTxPeriodConfigResp },
    { UHF_RESTOREDEFAULTCONFIG_FUNCRESP_ID, fs_RestoreDefaultConfigResp },
    { UHF_WRITEANTENNARELEASECONFIG_FUNCRESP_ID, fs_WriteAntennaReleaseConfigResp },
    { UHF_READANTENNARELEASECONFIG_FUNCRESP_ID, fs_ReadAntennaReleaseConfigResp },
    { UHF_WRITEANTENNA_FUNCRESP_ID, fs_WriteAntennaResp },
    { UHF_READANTENNA_FUNCRESP_ID, fs_ReadAntennaResp },
    { UHF_ENTERLPM_FUNCRESP_ID, fs_EnterLPMResp },
    { UHF_READLPM_FUNCRESP_ID, fs_ReadLPMResp },
    { UHF_WRITEDESTCALLSIGN_FUNCRESP_ID, fs_WriteDestCallSignResp },
    { UHF_READDESTCALLSIGN_FUNCRESP_ID, fs_ReadDestCallSignResp },
    { UHF_WRITESRCCALLSIGN_FUNCRESP_ID, fs_WriteSrcCallSignResp },
    { UHF_READSRCCALLSIGN_FUNCRESP_ID, fs_ReadSRCCallSignResp },
    { UHF_WRITEMORSECALLSIGN_FUNCRESP_ID, fs_WriteMorseCallSignResp },
    { UHF_READMORSECALLSIGN_FUNCRESP_ID, fs_ReadMorseCallSignResp },
    { UHF_WRITEMIDIAUDIOBEACON_FUNCRESP_ID, fs_WriteMIDIAudioBeaconResp },
    { UHF_READMIDIAUDIOBEACON_FUNCRESP_ID, fs_ReadMIDIAudioBeaconResp },
    { UHF_READSWVERSION_FUNCRESP_ID, fs_ReadSWVersionResp },
    { UHF_READPAYLOADSIZE_FUNCRESP_ID, fs_ReadPayloadSizeResp },
    { UHF_WRITEBEACONMESSAGECONTENTCFG_FUNCRESP_ID, fs_WriteBeaconMessageContentCfgResp },
    { UHF_READBEACONMESSAGECONTENTCFG_FUNCRESP_ID, fs_ReadBeaconMessageContentCfgResp },
    { UHF_WRITEDEVICEADDRCONFIG_FUNCRESP_ID, fs_WriteDeviceAddrConfigResp },
    { UHF_WRITEFRAM_FUNCRESP_ID, fs_WriteFRAMResp },
    { UHF_READFRAM_FUNCRESP_ID, fs_ReadFRAMResp },
    { UHF_WRITETRANSPROPERTY_FUNCRESP_ID, fs_WriteTransPropertyResp },
    { UHF_READTRANSPROPERTY_FUNCRESP_ID, fs_ReadTransPropertyResp },
    { UHF_READTEMP_FUNCRESP_ID, fs_ReadTempResp },
    { UHF_READRSSI_FUNCRESP_ID, fs_ReadRSSIResp },
    { UHF_WRITERADIORAWDATA_FUNCRESP_ID, fs_WriteRadioRawDataResp },
    { UHF_PING_FUNCRESP_ID, fs_PingResp },
    { UHF_EXBEACONSETSEND_FUNCRESP_ID, fs_ExBeaconSetSendResp },
    { UHF_WRITEI2CCONFIG_FUNCRESP_ID, fs_WriteI2cConfigResp },
    { UHF_READI2CCONFIG_FUNCRESP_ID, fs_ReadI2cConfigResp },
    { UHF_WRITEANTENNACFG_FUNCRESP_ID, fs_WriteAntennaCfgResp },
    { UHF_READANTENNACFG_FUNCRESP_ID, fs_ReadAntennaCfgResp },
    { UHF_WRITEEPSCFG_FUNCRESP_ID, fs_WriteEpsCfgResp },
    { UHF_READEPSCFG_FUNCRESP_ID, fs_ReadEpsCfgResp },
    { UHF_WRITEEPSCONOPSCFG_FUNCRESP_ID, fs_WriteEpsConOpsCfgResp },
    { UHF_READEPSCONOPSCFG_FUNCRESP_ID, fs_ReadEpsConOpsCfgResp },
    { UHF_WRITERS485CONFIG_FUNCRESP_ID, fs_WriteRs485ConfigResp },
    { UHF_READRS485CONFIG_FUNCRESP_ID, fs_ReadRs485ConfigResp },
    { UHF_WRITEOBCCONFIG_FUNCRESP_ID, fs_WriteOBCConfigResp },
    { UHF_READOBCCONFIG_FUNCRESP_ID, fs_ReadOBCConfigResp },
    { UHF_WRITESATCONFIG_FUNCRESP_ID, fs_WriteSatConfigResp },
    { UHF_READSATCONFIG_FUNCRESP_ID, fs_ReadSatConfigResp },
    { UHF_READEPSCFGOUT_FUNCRESP_ID, fs_ReadEpsCfgOutResp },
    { UHF_WRITEEPSCFGOUT_FUNCRESP_ID, fs_WriteEpsCfgOutResp },
    { UHF_WRITE2UANTENNACFG_FUNCRESP_ID, fs_Write2UAntennaCfgResp },
    { UHF_READ2UANTENNACFG_FUNCRESP_ID, fs_Read2UAntennaCfgResp },
    { UHF_WRITEAUTOMATEDBEACONCFG_FUNCRESP_ID, fs_WriteAutomatedBeaconCfgResp },
    { UHF_READAUTOMATEDBEACONCFG_FUNCRESP_ID, fs_ReadAutomatedBeaconCfgResp },
    { UHF_WRITEOUTPUTPOWERCFG_FUNCRESP_ID, fs_WriteOutputPowerCfgResp },
    { UHF_READOUTPUTPOWERCFG_FUNCRESP_ID, fs_ReadOutputPowerCfgResp },
    { UHF_READCOUNTERS_FUNCRESP_ID, fs_ReadCountersResp },
    { UHF_WRITECIPHERKEYSLOT_FUNCRESP_ID, fs_WriteCipherKeySlotResp },
    { UHF_READCIPHERKEYSLOTSTATUS_FUNCRESP_ID, fs_ReadCipherKeySlotStatusResp },
    { UHF_ERASECIPHERKEYSLOT_FUNCRESP_ID, fs_EraseCipherKeySlotResp }
};

/**********************************************************************
 *
 *  Static methods implementation
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    ESSA_Stack_FP_MsgHdr_t *pHdr = NULL;
    bool bIsFuncSupported = false;
    uint8_t i;

    // Basic header validity check
    if ((fp_DataInfo == NULL) ||
        (fp_DataInfo->u16DataSize < sizeof(ESSA_Stack_FP_MsgHdr_t)) ||
        (fp_DataInfo->pu8Data == NULL))
    {
        return false;
    }

    pHdr = (ESSA_Stack_FP_MsgHdr_t *) fp_DataInfo->pu8Data;

    if (IS_RESPONSE(*pHdr))
    {
        pHdr->funcId = GET_FUNC_ID(*pHdr);

        for (i = 0; i < COUNT_OF(fs_aFuncArray); i++)
        {
            if (fs_aFuncArray[i].funcId == pHdr->funcId)
            {
                if (fs_aFuncArray[i].pfFunc != NULL)
                {
                    fs_aFuncArray[i].pfFunc(fp_DataInfo);

                    bIsFuncSupported = true;
                }

                break;
            }
        }
    }

    return bIsFuncSupported;
}

static void fs_WriteSCWResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteSCWProtocolResponseData_t *fullresponse = (UHFWriteSCWProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteSCWResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteSCWProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteSCWResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteSCWResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteSCWResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadSCWResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadSCWProtocolResponseData_t *fullresponse = (UHFReadSCWProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadSCWResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSCWProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadSCWResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadSCWResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadSCWResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteRfConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteRfConfigProtocolResponseData_t *fullresponse = (UHFWriteRfConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteRfConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteRfConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteRfConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteRfConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteRfConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadRfConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadRfConfigProtocolResponseData_t *fullresponse = (UHFReadRfConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadRfConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadRfConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadRfConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadRfConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadRfConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadUpTimeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadUpTimeProtocolResponseData_t *fullresponse = (UHFReadUpTimeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadUpTimeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadUpTimeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadUpTimeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadUpTimeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadUpTimeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadNumberOfTxPacketsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadNumberOfTxPacketsProtocolResponseData_t *fullresponse = (UHFReadNumberOfTxPacketsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadNumberOfTxPacketsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadNumberOfTxPacketsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadNumberOfTxPacketsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadNumberOfTxPacketsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadNumberOfTxPacketsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadNumberOfRxPacketsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadNumberOfRxPacketsProtocolResponseData_t *fullresponse = (UHFReadNumberOfRxPacketsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadNumberOfRxPacketsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadNumberOfRxPacketsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadNumberOfRxPacketsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadNumberOfRxPacketsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadNumberOfRxPacketsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadNumberOfRxPacketsCRCErrResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadNumberOfRxPacketsCRCErrProtocolResponseData_t *fullresponse = (UHFReadNumberOfRxPacketsCRCErrProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadNumberOfRxPacketsCRCErrResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadNumberOfRxPacketsCRCErrProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadNumberOfRxPacketsCRCErrResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadNumberOfRxPacketsCRCErrResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadNumberOfRxPacketsCRCErrResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteBeaconMessageTxPeriodCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteBeaconMessageTxPeriodCfgProtocolResponseData_t *fullresponse = (UHFWriteBeaconMessageTxPeriodCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteBeaconMessageTxPeriodCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteBeaconMessageTxPeriodCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteBeaconMessageTxPeriodCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteBeaconMessageTxPeriodCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteBeaconMessageTxPeriodCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadBeaconMessageTxPeriodCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadBeaconMessageTxPeriodCfgProtocolResponseData_t *fullresponse = (UHFReadBeaconMessageTxPeriodCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadBeaconMessageTxPeriodCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadBeaconMessageTxPeriodCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadBeaconMessageTxPeriodCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadBeaconMessageTxPeriodCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadBeaconMessageTxPeriodCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteBeaconMessageBetweeenTxPeriodConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t *fullresponse = (UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteBeaconMessageBetweeenTxPeriodConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteBeaconMessageBetweeenTxPeriodConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadBeaconMessageBetweeenTxPeriodConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t *fullresponse = (UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadBeaconMessageBetweeenTxPeriodConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadBeaconMessageBetweeenTxPeriodConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_RestoreDefaultConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFRestoreDefaultConfigProtocolResponseData_t *fullresponse = (UHFRestoreDefaultConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFRestoreDefaultConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFRestoreDefaultConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFRestoreDefaultConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_RestoreDefaultConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_RestoreDefaultConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteAntennaReleaseConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteAntennaReleaseConfigProtocolResponseData_t *fullresponse = (UHFWriteAntennaReleaseConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteAntennaReleaseConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAntennaReleaseConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteAntennaReleaseConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteAntennaReleaseConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteAntennaReleaseConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadAntennaReleaseConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadAntennaReleaseConfigProtocolResponseData_t *fullresponse = (UHFReadAntennaReleaseConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadAntennaReleaseConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAntennaReleaseConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadAntennaReleaseConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadAntennaReleaseConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadAntennaReleaseConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteAntennaResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteAntennaProtocolResponseData_t *fullresponse = (UHFWriteAntennaProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteAntennaResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAntennaProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteAntennaResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteAntennaResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteAntennaResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadAntennaResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadAntennaProtocolResponseData_t *fullresponse = (UHFReadAntennaProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadAntennaResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAntennaProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadAntennaResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadAntennaResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadAntennaResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_EnterLPMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFEnterLPMProtocolResponseData_t *fullresponse = (UHFEnterLPMProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFEnterLPMResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFEnterLPMProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFEnterLPMResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_EnterLPMResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_EnterLPMResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadLPMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadLPMProtocolResponseData_t *fullresponse = (UHFReadLPMProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadLPMResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadLPMProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadLPMResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadLPMResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadLPMResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteDestCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteDestCallSignProtocolResponseData_t *fullresponse = (UHFWriteDestCallSignProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteDestCallSignResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteDestCallSignProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteDestCallSignResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteDestCallSignResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteDestCallSignResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadDestCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadDestCallSignProtocolResponseData_t *fullresponse = (UHFReadDestCallSignProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadDestCallSignResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadDestCallSignProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadDestCallSignResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadDestCallSignResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadDestCallSignResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteSrcCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteSrcCallSignProtocolResponseData_t *fullresponse = (UHFWriteSrcCallSignProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteSrcCallSignResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteSrcCallSignProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteSrcCallSignResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteSrcCallSignResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteSrcCallSignResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadSRCCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadSRCCallSignProtocolResponseData_t *fullresponse = (UHFReadSRCCallSignProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadSRCCallSignResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSRCCallSignProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadSRCCallSignResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadSRCCallSignResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadSRCCallSignResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteMorseCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteMorseCallSignProtocolResponseData_t *fullresponse = (UHFWriteMorseCallSignProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteMorseCallSignResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteMorseCallSignProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteMorseCallSignResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteMorseCallSignResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteMorseCallSignResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadMorseCallSignResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadMorseCallSignProtocolResponseData_t *fullresponse = (UHFReadMorseCallSignProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadMorseCallSignResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadMorseCallSignProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadMorseCallSignResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadMorseCallSignResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadMorseCallSignResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteMIDIAudioBeaconResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteMIDIAudioBeaconProtocolResponseData_t *fullresponse = (UHFWriteMIDIAudioBeaconProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteMIDIAudioBeaconResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteMIDIAudioBeaconProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteMIDIAudioBeaconResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteMIDIAudioBeaconResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteMIDIAudioBeaconResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadMIDIAudioBeaconResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadMIDIAudioBeaconProtocolResponseData_t *fullresponse = (UHFReadMIDIAudioBeaconProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadMIDIAudioBeaconResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadMIDIAudioBeaconProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadMIDIAudioBeaconResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadMIDIAudioBeaconResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadMIDIAudioBeaconResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadSWVersionResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadSWVersionProtocolResponseData_t *fullresponse = (UHFReadSWVersionProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadSWVersionResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSWVersionProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadSWVersionResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadSWVersionResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadSWVersionResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadPayloadSizeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadPayloadSizeProtocolResponseData_t *fullresponse = (UHFReadPayloadSizeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadPayloadSizeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadPayloadSizeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadPayloadSizeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadPayloadSizeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadPayloadSizeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteBeaconMessageContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteBeaconMessageContentCfgProtocolResponseData_t *fullresponse = (UHFWriteBeaconMessageContentCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteBeaconMessageContentCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteBeaconMessageContentCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteBeaconMessageContentCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteBeaconMessageContentCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteBeaconMessageContentCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadBeaconMessageContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadBeaconMessageContentCfgProtocolResponseData_t *fullresponse = (UHFReadBeaconMessageContentCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadBeaconMessageContentCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadBeaconMessageContentCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadBeaconMessageContentCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadBeaconMessageContentCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadBeaconMessageContentCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteDeviceAddrConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteDeviceAddrConfigProtocolResponseData_t *fullresponse = (UHFWriteDeviceAddrConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteDeviceAddrConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteDeviceAddrConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteDeviceAddrConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteDeviceAddrConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteDeviceAddrConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteFRAMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteFRAMProtocolResponseData_t *fullresponse = (UHFWriteFRAMProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteFRAMResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteFRAMProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteFRAMResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteFRAMResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteFRAMResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadFRAMResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadFRAMProtocolResponseData_t *fullresponse = (UHFReadFRAMProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadFRAMResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadFRAMProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadFRAMResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadFRAMResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadFRAMResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteTransPropertyResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteTransPropertyProtocolResponseData_t *fullresponse = (UHFWriteTransPropertyProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteTransPropertyResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteTransPropertyProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteTransPropertyResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteTransPropertyResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteTransPropertyResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadTransPropertyResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadTransPropertyProtocolResponseData_t *fullresponse = (UHFReadTransPropertyProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadTransPropertyResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadTransPropertyProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadTransPropertyResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadTransPropertyResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadTransPropertyResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadTempResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadTempProtocolResponseData_t *fullresponse = (UHFReadTempProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadTempResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadTempProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadTempResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadTempResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadTempResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadRSSIResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadRSSIProtocolResponseData_t *fullresponse = (UHFReadRSSIProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadRSSIResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadRSSIProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadRSSIResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadRSSIResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadRSSIResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteRadioRawDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteRadioRawDataProtocolResponseData_t *fullresponse = (UHFWriteRadioRawDataProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteRadioRawDataResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteRadioRawDataProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteRadioRawDataResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteRadioRawDataResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteRadioRawDataResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_PingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFPingProtocolResponseData_t *fullresponse = (UHFPingProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFPingResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFPingProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFPingResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_PingResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_PingResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ExBeaconSetSendResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFExBeaconSetSendProtocolResponseData_t *fullresponse = (UHFExBeaconSetSendProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFExBeaconSetSendResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFExBeaconSetSendProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFExBeaconSetSendResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ExBeaconSetSendResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ExBeaconSetSendResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteI2cConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteI2cConfigProtocolResponseData_t *fullresponse = (UHFWriteI2cConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteI2cConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteI2cConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteI2cConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteI2cConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteI2cConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadI2cConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadI2cConfigProtocolResponseData_t *fullresponse = (UHFReadI2cConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadI2cConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadI2cConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadI2cConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadI2cConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadI2cConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteAntennaCfgProtocolResponseData_t *fullresponse = (UHFWriteAntennaCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteAntennaCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAntennaCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteAntennaCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteAntennaCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteAntennaCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadAntennaCfgProtocolResponseData_t *fullresponse = (UHFReadAntennaCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadAntennaCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAntennaCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadAntennaCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadAntennaCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadAntennaCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteEpsCfgProtocolResponseData_t *fullresponse = (UHFWriteEpsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteEpsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteEpsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteEpsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteEpsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteEpsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadEpsCfgProtocolResponseData_t *fullresponse = (UHFReadEpsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadEpsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadEpsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadEpsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadEpsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadEpsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteEpsConOpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteEpsConOpsCfgProtocolResponseData_t *fullresponse = (UHFWriteEpsConOpsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteEpsConOpsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteEpsConOpsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteEpsConOpsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteEpsConOpsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteEpsConOpsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadEpsConOpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadEpsConOpsCfgProtocolResponseData_t *fullresponse = (UHFReadEpsConOpsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadEpsConOpsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadEpsConOpsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadEpsConOpsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadEpsConOpsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadEpsConOpsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteRs485ConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteRs485ConfigProtocolResponseData_t *fullresponse = (UHFWriteRs485ConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteRs485ConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteRs485ConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteRs485ConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteRs485ConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteRs485ConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadRs485ConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadRs485ConfigProtocolResponseData_t *fullresponse = (UHFReadRs485ConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadRs485ConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadRs485ConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadRs485ConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadRs485ConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadRs485ConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteOBCConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteOBCConfigProtocolResponseData_t *fullresponse = (UHFWriteOBCConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteOBCConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteOBCConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteOBCConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteOBCConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteOBCConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadOBCConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadOBCConfigProtocolResponseData_t *fullresponse = (UHFReadOBCConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadOBCConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadOBCConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadOBCConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadOBCConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadOBCConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteSatConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteSatConfigProtocolResponseData_t *fullresponse = (UHFWriteSatConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteSatConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteSatConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteSatConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteSatConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteSatConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadSatConfigResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadSatConfigProtocolResponseData_t *fullresponse = (UHFReadSatConfigProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadSatConfigResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSatConfigProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadSatConfigResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadSatConfigResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadSatConfigResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadEpsCfgOutResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadEpsCfgOutProtocolResponseData_t *fullresponse = (UHFReadEpsCfgOutProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadEpsCfgOutResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadEpsCfgOutProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadEpsCfgOutResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadEpsCfgOutResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadEpsCfgOutResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteEpsCfgOutResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteEpsCfgOutProtocolResponseData_t *fullresponse = (UHFWriteEpsCfgOutProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteEpsCfgOutResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteEpsCfgOutProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteEpsCfgOutResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteEpsCfgOutResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteEpsCfgOutResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_Write2UAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWrite2UAntennaCfgProtocolResponseData_t *fullresponse = (UHFWrite2UAntennaCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWrite2UAntennaCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWrite2UAntennaCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWrite2UAntennaCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_Write2UAntennaCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_Write2UAntennaCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_Read2UAntennaCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFRead2UAntennaCfgProtocolResponseData_t *fullresponse = (UHFRead2UAntennaCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFRead2UAntennaCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFRead2UAntennaCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFRead2UAntennaCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_Read2UAntennaCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_Read2UAntennaCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteAutomatedBeaconCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteAutomatedBeaconCfgProtocolResponseData_t *fullresponse = (UHFWriteAutomatedBeaconCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteAutomatedBeaconCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAutomatedBeaconCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteAutomatedBeaconCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteAutomatedBeaconCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteAutomatedBeaconCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadAutomatedBeaconCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadAutomatedBeaconCfgProtocolResponseData_t *fullresponse = (UHFReadAutomatedBeaconCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadAutomatedBeaconCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAutomatedBeaconCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadAutomatedBeaconCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadAutomatedBeaconCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadAutomatedBeaconCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteOutputPowerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteOutputPowerCfgProtocolResponseData_t *fullresponse = (UHFWriteOutputPowerCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteOutputPowerCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteOutputPowerCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteOutputPowerCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteOutputPowerCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteOutputPowerCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadOutputPowerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadOutputPowerCfgProtocolResponseData_t *fullresponse = (UHFReadOutputPowerCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadOutputPowerCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadOutputPowerCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadOutputPowerCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadOutputPowerCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadOutputPowerCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadCountersProtocolResponseData_t *fullresponse = (UHFReadCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFWriteCipherKeySlotProtocolResponseData_t *fullresponse = (UHFWriteCipherKeySlotProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFWriteCipherKeySlotResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteCipherKeySlotProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFWriteCipherKeySlotResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_WriteCipherKeySlotResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_WriteCipherKeySlotResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadCipherKeySlotStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFReadCipherKeySlotStatusProtocolResponseData_t *fullresponse = (UHFReadCipherKeySlotStatusProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFReadCipherKeySlotStatusResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFReadCipherKeySlotStatusProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFReadCipherKeySlotStatusResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_ReadCipherKeySlotStatusResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_ReadCipherKeySlotStatusResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_EraseCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    UHFEraseCipherKeySlotProtocolResponseData_t *fullresponse = (UHFEraseCipherKeySlotProtocolResponseData_t *) fp_DataInfo->pu8Data;
    UHFEraseCipherKeySlotResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(UHFEraseCipherKeySlotProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (UHFEraseCipherKeySlotResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->UHF_EraseCipherKeySlotResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->UHF_EraseCipherKeySlotResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void UHF_registerClientApi(UHF_ClientApi_t *pCliApiHandlers)
{
    pCliApiHnd = pCliApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t UHF_getClientProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_UHFProtocolClientInfo;
}

ESSATMAC_ErrCodes UHF_WriteSCWReq(
                ReqContext_t* ctx,
                const UHF_StatusControlWord_t * const sScw
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteSCWProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteSCWProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteSCWProtocolRequestData_t);

    if ((ctx != NULL) && (sScw != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITESCW_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sScw != NULL)
        {
            requestParams.data.sScw = *(sScw);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sScw,
                          0U,
                          sizeof(requestParams.data.sScw));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteSCWProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadSCWReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadSCWProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadSCWProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSCWProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READSCW_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadSCWProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteRfConfigReq(
                ReqContext_t* ctx,
                const UHF_sRFConfig_t * const sRfConfig
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteRfConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteRfConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteRfConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sRfConfig != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITERFCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sRfConfig != NULL)
        {
            requestParams.data.sRfConfig = *(sRfConfig);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sRfConfig,
                          0U,
                          sizeof(requestParams.data.sRfConfig));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteRfConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadRfConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadRfConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadRfConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadRfConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READRFCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadRfConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadUpTimeReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadUpTimeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadUpTimeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadUpTimeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READUPTIME_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadUpTimeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadNumberOfTxPacketsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadNumberOfTxPacketsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadNumberOfTxPacketsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadNumberOfTxPacketsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READNUMBEROFTXPACKETS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadNumberOfTxPacketsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadNumberOfRxPacketsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadNumberOfRxPacketsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadNumberOfRxPacketsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadNumberOfRxPacketsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READNUMBEROFRXPACKETS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadNumberOfRxPacketsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadNumberOfRxPacketsCRCErrReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadNumberOfRxPacketsCRCErrProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadNumberOfRxPacketsCRCErrProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadNumberOfRxPacketsCRCErrProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READNUMBEROFRXPACKETSCRCERR_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadNumberOfRxPacketsCRCErrProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteBeaconMessageTxPeriodCfgReq(
                ReqContext_t* ctx,
                const UHF_sBeaconMessageTxPeriodCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteBeaconMessageTxPeriodCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteBeaconMessageTxPeriodCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteBeaconMessageTxPeriodCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEBEACONMESSAGETXPERIODCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteBeaconMessageTxPeriodCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadBeaconMessageTxPeriodCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadBeaconMessageTxPeriodCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadBeaconMessageTxPeriodCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadBeaconMessageTxPeriodCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READBEACONMESSAGETXPERIODCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadBeaconMessageTxPeriodCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteBeaconMessageBetweeenTxPeriodConfigReq(
                ReqContext_t* ctx,
                const UHF_sBeaconMessageBetweenTxPeriodCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadBeaconMessageBetweeenTxPeriodConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadBeaconMessageBetweeenTxPeriodConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_RestoreDefaultConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFRestoreDefaultConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFRestoreDefaultConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFRestoreDefaultConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_RESTOREDEFAULTCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFRestoreDefaultConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteAntennaReleaseConfigReq(
                ReqContext_t* ctx,
                const UHF_sAntennaReleaseCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteAntennaReleaseConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteAntennaReleaseConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAntennaReleaseConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEANTENNARELEASECONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteAntennaReleaseConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadAntennaReleaseConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadAntennaReleaseConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadAntennaReleaseConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAntennaReleaseConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READANTENNARELEASECONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadAntennaReleaseConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteAntennaReq(
                ReqContext_t* ctx,
                const uint8_t u8Algorithm
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteAntennaProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteAntennaProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAntennaProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEANTENNA_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8Algorithm = u8Algorithm;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteAntennaProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadAntennaReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadAntennaProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadAntennaProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAntennaProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READANTENNA_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadAntennaProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_EnterLPMReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFEnterLPMProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFEnterLPMProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFEnterLPMProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_ENTERLPM_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFEnterLPMProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadLPMReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadLPMProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadLPMProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadLPMProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READLPM_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadLPMProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteDestCallSignReq(
                ReqContext_t* ctx,
                const UHF_sCallSign_t * const sCallSign
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteDestCallSignProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteDestCallSignProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteDestCallSignProtocolRequestData_t);

    if ((ctx != NULL) && (sCallSign != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEDESTCALLSIGN_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCallSign != NULL)
        {
            requestParams.data.sCallSign = *(sCallSign);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCallSign,
                          0U,
                          sizeof(requestParams.data.sCallSign));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteDestCallSignProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadDestCallSignReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadDestCallSignProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadDestCallSignProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadDestCallSignProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READDESTCALLSIGN_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadDestCallSignProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteSrcCallSignReq(
                ReqContext_t* ctx,
                const UHF_sCallSign_t * const sCallSign
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteSrcCallSignProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteSrcCallSignProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteSrcCallSignProtocolRequestData_t);

    if ((ctx != NULL) && (sCallSign != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITESRCCALLSIGN_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCallSign != NULL)
        {
            requestParams.data.sCallSign = *(sCallSign);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCallSign,
                          0U,
                          sizeof(requestParams.data.sCallSign));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteSrcCallSignProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadSRCCallSignReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadSRCCallSignProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadSRCCallSignProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSRCCallSignProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READSRCCALLSIGN_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadSRCCallSignProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteMorseCallSignReq(
                ReqContext_t* ctx,
                const UHF_sMorseCallSign_t * const sMorseCallSign
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteMorseCallSignProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteMorseCallSignProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteMorseCallSignProtocolRequestData_t);

    if ((ctx != NULL) && (sMorseCallSign != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEMORSECALLSIGN_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sMorseCallSign != NULL)
        {
            requestParams.data.sMorseCallSign = *(sMorseCallSign);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sMorseCallSign,
                          0U,
                          sizeof(requestParams.data.sMorseCallSign));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteMorseCallSignProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadMorseCallSignReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadMorseCallSignProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadMorseCallSignProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadMorseCallSignProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READMORSECALLSIGN_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadMorseCallSignProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteMIDIAudioBeaconReq(
                ReqContext_t* ctx,
                const UHF_sMidiAudioBeacon_t * const sMidi
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteMIDIAudioBeaconProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteMIDIAudioBeaconProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteMIDIAudioBeaconProtocolRequestData_t);

    if ((ctx != NULL) && (sMidi != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEMIDIAUDIOBEACON_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sMidi != NULL)
        {
            requestParams.data.sMidi = *(sMidi);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sMidi,
                          0U,
                          sizeof(requestParams.data.sMidi));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteMIDIAudioBeaconProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadMIDIAudioBeaconReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadMIDIAudioBeaconProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadMIDIAudioBeaconProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadMIDIAudioBeaconProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READMIDIAUDIOBEACON_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadMIDIAudioBeaconProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadSWVersionReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadSWVersionProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadSWVersionProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSWVersionProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READSWVERSION_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadSWVersionProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadPayloadSizeReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadPayloadSizeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadPayloadSizeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadPayloadSizeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READPAYLOADSIZE_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadPayloadSizeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteBeaconMessageContentCfgReq(
                ReqContext_t* ctx,
                const UHF_sBeaconMessageContentCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteBeaconMessageContentCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteBeaconMessageContentCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteBeaconMessageContentCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEBEACONMESSAGECONTENTCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteBeaconMessageContentCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadBeaconMessageContentCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadBeaconMessageContentCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadBeaconMessageContentCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadBeaconMessageContentCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READBEACONMESSAGECONTENTCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadBeaconMessageContentCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteDeviceAddrConfigReq(
                ReqContext_t* ctx,
                const UHF_sAddrCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteDeviceAddrConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteDeviceAddrConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteDeviceAddrConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEDEVICEADDRCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteDeviceAddrConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteFRAMReq(
                ReqContext_t* ctx,
                const UHF_sFramData_t * const sFramWriteReq
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteFRAMProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteFRAMProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteFRAMProtocolRequestData_t);

    if ((ctx != NULL) && (sFramWriteReq != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEFRAM_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sFramWriteReq != NULL)
        {
            requestParams.data.sFramWriteReq = *(sFramWriteReq);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sFramWriteReq,
                          0U,
                          sizeof(requestParams.data.sFramWriteReq));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteFRAMProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadFRAMReq(
                ReqContext_t* ctx,
                const uint32_t u32Addr
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadFRAMProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadFRAMProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadFRAMProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READFRAM_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u32Addr = u32Addr;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadFRAMProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteTransPropertyReq(
                ReqContext_t* ctx,
                const UHF_sTransceiverProperty_t * const sProperty
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteTransPropertyProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteTransPropertyProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteTransPropertyProtocolRequestData_t);

    if ((ctx != NULL) && (sProperty != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITETRANSPROPERTY_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sProperty != NULL)
        {
            requestParams.data.sProperty = *(sProperty);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sProperty,
                          0U,
                          sizeof(requestParams.data.sProperty));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteTransPropertyProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadTransPropertyReq(
                ReqContext_t* ctx,
                const UHF_sReadTransceiverProperty_t * const sProperty
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadTransPropertyProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadTransPropertyProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadTransPropertyProtocolRequestData_t);

    if ((ctx != NULL) && (sProperty != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READTRANSPROPERTY_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sProperty != NULL)
        {
            requestParams.data.sProperty = *(sProperty);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sProperty,
                          0U,
                          sizeof(requestParams.data.sProperty));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadTransPropertyProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadTempReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadTempProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadTempProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadTempProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READTEMP_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadTempProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadRSSIReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadRSSIProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadRSSIProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadRSSIProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READRSSI_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadRSSIProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteRadioRawDataReq(
                ReqContext_t* ctx,
                const UHF_sRadioRawData_t * const sData
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteRadioRawDataProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteRadioRawDataProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteRadioRawDataProtocolRequestData_t);

    if ((ctx != NULL) && (sData != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITERADIORAWDATA_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sData != NULL)
        {
            requestParams.data.sData = *(sData);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sData,
                          0U,
                          sizeof(requestParams.data.sData));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteRadioRawDataProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_PingReq(
                ReqContext_t* ctx,
                const UHF_sPing_t * const sData
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFPingProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFPingProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFPingProtocolRequestData_t);

    if ((ctx != NULL) && (sData != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_PING_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sData != NULL)
        {
            requestParams.data.sData = *(sData);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sData,
                          0U,
                          sizeof(requestParams.data.sData));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFPingProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ExBeaconSetSendReq(
                ReqContext_t* ctx,
                const UHF_sExBeacon_t * const sData
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFExBeaconSetSendProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFExBeaconSetSendProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFExBeaconSetSendProtocolRequestData_t);

    if ((ctx != NULL) && (sData != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_EXBEACONSETSEND_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sData != NULL)
        {
            requestParams.data.sData = *(sData);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sData,
                          0U,
                          sizeof(requestParams.data.sData));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFExBeaconSetSendProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteI2cConfigReq(
                ReqContext_t* ctx,
                const UHF_sI2cCfg_t * const sData
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteI2cConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteI2cConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteI2cConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sData != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEI2CCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sData != NULL)
        {
            requestParams.data.sData = *(sData);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sData,
                          0U,
                          sizeof(requestParams.data.sData));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteI2cConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadI2cConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadI2cConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadI2cConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadI2cConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READI2CCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadI2cConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteAntennaCfgReq(
                ReqContext_t* ctx,
                const UHF_sAntennaCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteAntennaCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteAntennaCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAntennaCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEANTENNACFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteAntennaCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadAntennaCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadAntennaCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadAntennaCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAntennaCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READANTENNACFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadAntennaCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteEpsCfgReq(
                ReqContext_t* ctx,
                const UHF_sEpsCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteEpsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteEpsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteEpsCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEEPSCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteEpsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadEpsCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadEpsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadEpsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadEpsCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READEPSCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadEpsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteEpsConOpsCfgReq(
                ReqContext_t* ctx,
                const UHF_sEpsConOpsCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteEpsConOpsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteEpsConOpsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteEpsConOpsCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEEPSCONOPSCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteEpsConOpsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadEpsConOpsCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadEpsConOpsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadEpsConOpsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadEpsConOpsCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READEPSCONOPSCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadEpsConOpsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteRs485ConfigReq(
                ReqContext_t* ctx,
                const UHF_sRS485Cfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteRs485ConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteRs485ConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteRs485ConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITERS485CONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteRs485ConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadRs485ConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadRs485ConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadRs485ConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadRs485ConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READRS485CONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadRs485ConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteOBCConfigReq(
                ReqContext_t* ctx,
                const UHF_sObcCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteOBCConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteOBCConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteOBCConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEOBCCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteOBCConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadOBCConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadOBCConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadOBCConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadOBCConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READOBCCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadOBCConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteSatConfigReq(
                ReqContext_t* ctx,
                const UHF_sSatCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteSatConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteSatConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteSatConfigProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITESATCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteSatConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadSatConfigReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadSatConfigProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadSatConfigProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadSatConfigProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READSATCONFIG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadSatConfigProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadEpsCfgOutReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadEpsCfgOutProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadEpsCfgOutProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadEpsCfgOutProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READEPSCFGOUT_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadEpsCfgOutProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteEpsCfgOutReq(
                ReqContext_t* ctx,
                const UHF_sEpsOutCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteEpsCfgOutProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteEpsCfgOutProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteEpsCfgOutProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEEPSCFGOUT_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteEpsCfgOutProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_Write2UAntennaCfgReq(
                ReqContext_t* ctx,
                const UHF_s2UAntennaCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWrite2UAntennaCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWrite2UAntennaCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWrite2UAntennaCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITE2UANTENNACFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWrite2UAntennaCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_Read2UAntennaCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFRead2UAntennaCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFRead2UAntennaCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFRead2UAntennaCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READ2UANTENNACFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFRead2UAntennaCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteAutomatedBeaconCfgReq(
                ReqContext_t* ctx,
                const UHF_sAutomatedBeaconCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteAutomatedBeaconCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteAutomatedBeaconCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteAutomatedBeaconCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEAUTOMATEDBEACONCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteAutomatedBeaconCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadAutomatedBeaconCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadAutomatedBeaconCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadAutomatedBeaconCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadAutomatedBeaconCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READAUTOMATEDBEACONCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadAutomatedBeaconCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteOutputPowerCfgReq(
                ReqContext_t* ctx,
                const UHF_sOutputPowerCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteOutputPowerCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteOutputPowerCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteOutputPowerCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITEOUTPUTPOWERCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sCfg != NULL)
        {
            requestParams.data.sCfg = *(sCfg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sCfg,
                          0U,
                          sizeof(requestParams.data.sCfg));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteOutputPowerCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadOutputPowerCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadOutputPowerCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadOutputPowerCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadOutputPowerCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READOUTPUTPOWERCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadOutputPowerCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READCOUNTERS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_WriteCipherKeySlotReq(
                ReqContext_t* ctx,
                const UHF_sCipherKeySlot_t * const sSKeySlot
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFWriteCipherKeySlotProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFWriteCipherKeySlotProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFWriteCipherKeySlotProtocolRequestData_t);

    if ((ctx != NULL) && (sSKeySlot != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_WRITECIPHERKEYSLOT_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sSKeySlot != NULL)
        {
            requestParams.data.sSKeySlot = *(sSKeySlot);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sSKeySlot,
                          0U,
                          sizeof(requestParams.data.sSKeySlot));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFWriteCipherKeySlotProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_ReadCipherKeySlotStatusReq(
                ReqContext_t* ctx,
                const uint8_t u8SlotId
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFReadCipherKeySlotStatusProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFReadCipherKeySlotStatusProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFReadCipherKeySlotStatusProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_READCIPHERKEYSLOTSTATUS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u8SlotId = u8SlotId;
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFReadCipherKeySlotStatusProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes UHF_EraseCipherKeySlotReq(
                ReqContext_t* ctx,
                const UHF_sCipherKeySlot_t * const sSKeySlot
)
{
#ifndef BIG_ENDIAN_PLATFORM
    UHFEraseCipherKeySlotProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(UHFEraseCipherKeySlotProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(UHFEraseCipherKeySlotProtocolRequestData_t);

    if ((ctx != NULL) && (sSKeySlot != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_UHF;
        requestParams.hdr.funcId  = UHF_ERASECIPHERKEYSLOT_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sSKeySlot != NULL)
        {
            requestParams.data.sSKeySlot = *(sSKeySlot);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sSKeySlot,
                          0U,
                          sizeof(requestParams.data.sSKeySlot));
        }
#else // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Serialize request fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

        sendResult = ESSA_Stack_SendFrameEx((ESSASNetInterface) ctx->nInterfaceNumber,
                                            ctx->netType,
                                            ctx->nAddr,
                                            ES_SAT_MAC_PROTOCOL_ID_FP_LAYER,
#ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) &requestParams,
#else // #ifndef BIG_ENDIAN_PLATFORM
                                            (uint8_t *) requestParams,
#endif // #ifndef BIG_ENDIAN_PLATFORM
                                            sizeof(UHFEraseCipherKeySlotProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


