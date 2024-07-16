/*!
********************************************************************************************
* @file FP_SBAND_TMTCProtocolClient.c
* @brief ESSA Stack client-side implementation
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

#include "FP_SBAND_TMTCProtocolClient.h"

#define SBAND_TMTC_PROTOCOL_VERSION_MAJOR   ((uint8_t) 1)
#define SBAND_TMTC_PROTOCOL_VERSION_MINOR   ((uint8_t) 1)

/**********************************************************************
 *
 *  Local type definitions
 *
 **********************************************************************/
typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetCapabilitiesProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetCapabilitiesResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetCapabilitiesProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadUpTimeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadUpTimeResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadUpTimeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadHWHealthProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadHWHealthResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadHWHealthProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadEpsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadEpsCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadEpsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteEpsCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteEpsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteEpsCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteEpsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadAutomatedBeaconsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadAutomatedBeaconsCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadAutomatedBeaconsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteAutomatedBeaconsCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteAutomatedBeaconsCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteAutomatedBeaconsCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteAutomatedBeaconsCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadErrorCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadErrorCountersResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadErrorCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadPipeModeCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadPipeModeCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadPipeModeCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWritePipeModeCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWritePipeModeCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWritePipeModeCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWritePipeModeCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadTxtBeaconContentCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadTxtBeaconContentCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadTxtBeaconContentCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteTxtBeaconContentCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteTxtBeaconContentCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteTxtBeaconContentCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteTxtBeaconContentCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadAx25CfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadAx25CfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadAx25CfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteAx25CfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteAx25CfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteAx25CfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteAx25CfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteCipherKeySlotRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteCipherKeySlotProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteCipherKeySlotResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteCipherKeySlotProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadCipherKeySlotStatusRequestData_t data;
} PACKED_STRUCT SBAND_TMTCReadCipherKeySlotStatusProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadCipherKeySlotStatusResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadCipherKeySlotStatusProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCEraseCipherKeySlotRequestData_t data;
} PACKED_STRUCT SBAND_TMTCEraseCipherKeySlotProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCEraseCipherKeySlotResponseData_t data;
} PACKED_STRUCT SBAND_TMTCEraseCipherKeySlotProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadConOps_HystCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadConOps_HystCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadConOps_HystCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteConOps_HystCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteConOps_HystCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteConOps_HystCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteConOps_HystCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadPortCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCReadPortCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadPortCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadPortCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWritePortCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWritePortCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWritePortCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWritePortCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadLoggerCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadLoggerCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadLoggerCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteLoggerCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteLoggerCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteLoggerCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteLoggerCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCTransmitDataRequestData_t data;
} PACKED_STRUCT SBAND_TMTCTransmitDataProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCTransmitDataResponseData_t data;
} PACKED_STRUCT SBAND_TMTCTransmitDataProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCLoadPresetCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCLoadPresetCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCLoadPresetCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCLoadPresetCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCPingRequestData_t data;
} PACKED_STRUCT SBAND_TMTCPingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCPingResponseData_t data;
} PACKED_STRUCT SBAND_TMTCPingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetDualPAModeRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetDualPAModeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetDualPAModeResponseData_t data;
} PACKED_STRUCT SBAND_TMTCSetDualPAModeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetDualPAModeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetDualPAModeResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetDualPAModeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetTestPacketStateRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetTestPacketStateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCSetTestPacketStateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadRfFreqCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadRfFreqCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadRfFreqCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteRfFreqCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteRfFreqCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteRfFreqCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteRfFreqCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCResetProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCResetResponseData_t data;
} PACKED_STRUCT SBAND_TMTCResetProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCResetErrorCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCResetErrorCountersResponseData_t data;
} PACKED_STRUCT SBAND_TMTCResetErrorCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadSatCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadSatCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadSatCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteSatCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteSatCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteSatCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteSatCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadTCProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadTCResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadTCProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCClearTCProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCClearTCResponseData_t data;
} PACKED_STRUCT SBAND_TMTCClearTCProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadTempSensorsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadTempSensorsResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadTempSensorsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCIgnore_PA_TSProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCIgnore_PA_TSResponseData_t data;
} PACKED_STRUCT SBAND_TMTCIgnore_PA_TSProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadRadioCRCCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadRadioCRCCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadRadioCRCCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteRadioCRCCfgRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteRadioCRCCfgProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteRadioCRCCfgResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteRadioCRCCfgProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteRadioPacketFecHdlcRequestData_t data;
} PACKED_STRUCT SBAND_TMTCWriteRadioPacketFecHdlcProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCWriteRadioPacketFecHdlcResponseData_t data;
} PACKED_STRUCT SBAND_TMTCWriteRadioPacketFecHdlcProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadRadioPacketFecHdlcProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadRadioPacketFecHdlcResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadRadioPacketFecHdlcProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetPacketCountersProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetPacketCountersResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetPacketCountersProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCReadRadioErrorsProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCReadRadioErrorsResponseData_t data;
} PACKED_STRUCT SBAND_TMTCReadRadioErrorsProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetModulationProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetModulationResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetModulationProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetModulationRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetModulationProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetModulationResponseData_t data;
} PACKED_STRUCT SBAND_TMTCSetModulationProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetBaudrateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetBaudrateResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetBaudrateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetBaudrateRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetBaudrateProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetBaudrateResponseData_t data;
} PACKED_STRUCT SBAND_TMTCSetBaudrateProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetFreqShapingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetFreqShapingResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetFreqShapingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetFreqShapingRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetFreqShapingProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetFreqShapingResponseData_t data;
} PACKED_STRUCT SBAND_TMTCSetFreqShapingProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetStreamModeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetStreamModeResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetStreamModeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetStreamModeRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetStreamModeProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetStreamModeResponseData_t data;
} PACKED_STRUCT SBAND_TMTCSetStreamModeProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetTargetPowerProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetTargetPowerResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetTargetPowerProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetTargetPowerRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetTargetPowerProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetTargetPowerResponseData_t data;
} PACKED_STRUCT SBAND_TMTCSetTargetPowerProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
} PACKED_STRUCT SBAND_TMTCGetPacketScramblerProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCGetPacketScramblerResponseData_t data;
} PACKED_STRUCT SBAND_TMTCGetPacketScramblerProtocolResponseData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetPacketScramblerRequestData_t data;
} PACKED_STRUCT SBAND_TMTCSetPacketScramblerProtocolRequestData_t;

typedef struct {
    ESSA_Stack_FP_MsgHdr_t hdr;
    SBAND_TMTCSetPacketScramblerResponseData_t data;
} PACKED_STRUCT SBAND_TMTCSetPacketScramblerProtocolResponseData_t;


/**********************************************************************
 *
 *  Static methods declarations
 *
 **********************************************************************/
static bool fs_HandleData(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetCapabilitiesResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadUpTimeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadHWHealthResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadAutomatedBeaconsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteAutomatedBeaconsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadErrorCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadPipeModeCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WritePipeModeCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadTxtBeaconContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteTxtBeaconContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadAx25CfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteAx25CfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadCipherKeySlotStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_EraseCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadConOps_HystCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteConOps_HystCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadPortCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WritePortCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadLoggerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteLoggerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_TransmitDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_LoadPresetCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_PingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetDualPAModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetDualPAModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetTestPacketStateResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadRfFreqCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteRfFreqCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ResetResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ResetErrorCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadSatCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteSatCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ClearTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadTempSensorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_Ignore_PA_TSResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadRadioCRCCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteRadioCRCCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_WriteRadioPacketFecHdlcResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadRadioPacketFecHdlcResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetPacketCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_ReadRadioErrorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetModulationResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetModulationResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetBaudrateResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetBaudrateResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetFreqShapingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetFreqShapingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetStreamModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetStreamModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetTargetPowerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetTargetPowerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_GetPacketScramblerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);
static void fs_SetPacketScramblerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo);

/**********************************************************************
 *
 *  Public variable definitions
 *
 **********************************************************************/
const ESSA_Stack_FunctionProtocolInfo_t FP_SBAND_TMTCProtocolClientInfo = {
    .u16ProtocolId    = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC,
    .pfDataHandlerCbk = fs_HandleData
};

/**********************************************************************
 *
 *  Static variable definitions
 *
 **********************************************************************/
static SBAND_TMTC_ClientApi_t *pCliApiHnd = NULL;

static const ProtocolFuncArrayEntry_t fs_aFuncArray[] = {
    { SBAND_TMTC_GETCAPABILITIES_FUNCRESP_ID, fs_GetCapabilitiesResp },
    { SBAND_TMTC_READUPTIME_FUNCRESP_ID, fs_ReadUpTimeResp },
    { SBAND_TMTC_READHWHEALTH_FUNCRESP_ID, fs_ReadHWHealthResp },
    { SBAND_TMTC_READEPSCFG_FUNCRESP_ID, fs_ReadEpsCfgResp },
    { SBAND_TMTC_WRITEEPSCFG_FUNCRESP_ID, fs_WriteEpsCfgResp },
    { SBAND_TMTC_READAUTOMATEDBEACONSCFG_FUNCRESP_ID, fs_ReadAutomatedBeaconsCfgResp },
    { SBAND_TMTC_WRITEAUTOMATEDBEACONSCFG_FUNCRESP_ID, fs_WriteAutomatedBeaconsCfgResp },
    { SBAND_TMTC_READERRORCOUNTERS_FUNCRESP_ID, fs_ReadErrorCountersResp },
    { SBAND_TMTC_READPIPEMODECFG_FUNCRESP_ID, fs_ReadPipeModeCfgResp },
    { SBAND_TMTC_WRITEPIPEMODECFG_FUNCRESP_ID, fs_WritePipeModeCfgResp },
    { SBAND_TMTC_READTXTBEACONCONTENTCFG_FUNCRESP_ID, fs_ReadTxtBeaconContentCfgResp },
    { SBAND_TMTC_WRITETXTBEACONCONTENTCFG_FUNCRESP_ID, fs_WriteTxtBeaconContentCfgResp },
    { SBAND_TMTC_READAX25CFG_FUNCRESP_ID, fs_ReadAx25CfgResp },
    { SBAND_TMTC_WRITEAX25CFG_FUNCRESP_ID, fs_WriteAx25CfgResp },
    { SBAND_TMTC_WRITECIPHERKEYSLOT_FUNCRESP_ID, fs_WriteCipherKeySlotResp },
    { SBAND_TMTC_READCIPHERKEYSLOTSTATUS_FUNCRESP_ID, fs_ReadCipherKeySlotStatusResp },
    { SBAND_TMTC_ERASECIPHERKEYSLOT_FUNCRESP_ID, fs_EraseCipherKeySlotResp },
    { SBAND_TMTC_READCONOPS_HYSTCFG_FUNCRESP_ID, fs_ReadConOps_HystCfgResp },
    { SBAND_TMTC_WRITECONOPS_HYSTCFG_FUNCRESP_ID, fs_WriteConOps_HystCfgResp },
    { SBAND_TMTC_READPORTCFG_FUNCRESP_ID, fs_ReadPortCfgResp },
    { SBAND_TMTC_WRITEPORTCFG_FUNCRESP_ID, fs_WritePortCfgResp },
    { SBAND_TMTC_READLOGGERCFG_FUNCRESP_ID, fs_ReadLoggerCfgResp },
    { SBAND_TMTC_WRITELOGGERCFG_FUNCRESP_ID, fs_WriteLoggerCfgResp },
    { SBAND_TMTC_TRANSMITDATA_FUNCRESP_ID, fs_TransmitDataResp },
    { SBAND_TMTC_LOADPRESETCFG_FUNCRESP_ID, fs_LoadPresetCfgResp },
    { SBAND_TMTC_PING_FUNCRESP_ID, fs_PingResp },
    { SBAND_TMTC_SETDUALPAMODE_FUNCRESP_ID, fs_SetDualPAModeResp },
    { SBAND_TMTC_GETDUALPAMODE_FUNCRESP_ID, fs_GetDualPAModeResp },
    { SBAND_TMTC_SETTESTPACKETSTATE_FUNCRESP_ID, fs_SetTestPacketStateResp },
    { SBAND_TMTC_READRFFREQCFG_FUNCRESP_ID, fs_ReadRfFreqCfgResp },
    { SBAND_TMTC_WRITERFFREQCFG_FUNCRESP_ID, fs_WriteRfFreqCfgResp },
    { SBAND_TMTC_RESET_FUNCRESP_ID, fs_ResetResp },
    { SBAND_TMTC_RESETERRORCOUNTERS_FUNCRESP_ID, fs_ResetErrorCountersResp },
    { SBAND_TMTC_READSATCFG_FUNCRESP_ID, fs_ReadSatCfgResp },
    { SBAND_TMTC_WRITESATCFG_FUNCRESP_ID, fs_WriteSatCfgResp },
    { SBAND_TMTC_READTC_FUNCRESP_ID, fs_ReadTCResp },
    { SBAND_TMTC_CLEARTC_FUNCRESP_ID, fs_ClearTCResp },
    { SBAND_TMTC_READTEMPSENSORS_FUNCRESP_ID, fs_ReadTempSensorsResp },
    { SBAND_TMTC_IGNORE_PA_TS_FUNCRESP_ID, fs_Ignore_PA_TSResp },
    { SBAND_TMTC_READRADIOCRCCFG_FUNCRESP_ID, fs_ReadRadioCRCCfgResp },
    { SBAND_TMTC_WRITERADIOCRCCFG_FUNCRESP_ID, fs_WriteRadioCRCCfgResp },
    { SBAND_TMTC_WRITERADIOPACKETFECHDLC_FUNCRESP_ID, fs_WriteRadioPacketFecHdlcResp },
    { SBAND_TMTC_READRADIOPACKETFECHDLC_FUNCRESP_ID, fs_ReadRadioPacketFecHdlcResp },
    { SBAND_TMTC_GETPACKETCOUNTERS_FUNCRESP_ID, fs_GetPacketCountersResp },
    { SBAND_TMTC_READRADIOERRORS_FUNCRESP_ID, fs_ReadRadioErrorsResp },
    { SBAND_TMTC_GETMODULATION_FUNCRESP_ID, fs_GetModulationResp },
    { SBAND_TMTC_SETMODULATION_FUNCRESP_ID, fs_SetModulationResp },
    { SBAND_TMTC_GETBAUDRATE_FUNCRESP_ID, fs_GetBaudrateResp },
    { SBAND_TMTC_SETBAUDRATE_FUNCRESP_ID, fs_SetBaudrateResp },
    { SBAND_TMTC_GETFREQSHAPING_FUNCRESP_ID, fs_GetFreqShapingResp },
    { SBAND_TMTC_SETFREQSHAPING_FUNCRESP_ID, fs_SetFreqShapingResp },
    { SBAND_TMTC_GETSTREAMMODE_FUNCRESP_ID, fs_GetStreamModeResp },
    { SBAND_TMTC_SETSTREAMMODE_FUNCRESP_ID, fs_SetStreamModeResp },
    { SBAND_TMTC_GETTARGETPOWER_FUNCRESP_ID, fs_GetTargetPowerResp },
    { SBAND_TMTC_SETTARGETPOWER_FUNCRESP_ID, fs_SetTargetPowerResp },
    { SBAND_TMTC_GETPACKETSCRAMBLER_FUNCRESP_ID, fs_GetPacketScramblerResp },
    { SBAND_TMTC_SETPACKETSCRAMBLER_FUNCRESP_ID, fs_SetPacketScramblerResp }
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

static void fs_GetCapabilitiesResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetCapabilitiesProtocolResponseData_t *fullresponse = (SBAND_TMTCGetCapabilitiesProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetCapabilitiesResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetCapabilitiesProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetCapabilitiesResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetCapabilitiesResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetCapabilitiesResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadUpTimeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadUpTimeProtocolResponseData_t *fullresponse = (SBAND_TMTCReadUpTimeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadUpTimeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadUpTimeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadUpTimeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadUpTimeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadUpTimeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadHWHealthResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadHWHealthProtocolResponseData_t *fullresponse = (SBAND_TMTCReadHWHealthProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadHWHealthResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadHWHealthProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadHWHealthResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadHWHealthResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadHWHealthResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadEpsCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadEpsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadEpsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadEpsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadEpsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadEpsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadEpsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteEpsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteEpsCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteEpsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteEpsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteEpsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteEpsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteEpsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteEpsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadAutomatedBeaconsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadAutomatedBeaconsCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadAutomatedBeaconsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadAutomatedBeaconsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadAutomatedBeaconsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadAutomatedBeaconsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteAutomatedBeaconsCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteAutomatedBeaconsCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteAutomatedBeaconsCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteAutomatedBeaconsCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteAutomatedBeaconsCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteAutomatedBeaconsCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadErrorCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadErrorCountersProtocolResponseData_t *fullresponse = (SBAND_TMTCReadErrorCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadErrorCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadErrorCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadErrorCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadErrorCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadErrorCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadPipeModeCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadPipeModeCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadPipeModeCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadPipeModeCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadPipeModeCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadPipeModeCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadPipeModeCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadPipeModeCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WritePipeModeCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWritePipeModeCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWritePipeModeCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWritePipeModeCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWritePipeModeCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWritePipeModeCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WritePipeModeCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WritePipeModeCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadTxtBeaconContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadTxtBeaconContentCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadTxtBeaconContentCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadTxtBeaconContentCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadTxtBeaconContentCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadTxtBeaconContentCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadTxtBeaconContentCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadTxtBeaconContentCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteTxtBeaconContentCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteTxtBeaconContentCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteTxtBeaconContentCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteTxtBeaconContentCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteTxtBeaconContentCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteTxtBeaconContentCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteTxtBeaconContentCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteTxtBeaconContentCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadAx25CfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadAx25CfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadAx25CfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadAx25CfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadAx25CfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadAx25CfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadAx25CfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadAx25CfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteAx25CfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteAx25CfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteAx25CfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteAx25CfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteAx25CfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteAx25CfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteAx25CfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteAx25CfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteCipherKeySlotProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteCipherKeySlotProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteCipherKeySlotResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteCipherKeySlotProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteCipherKeySlotResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteCipherKeySlotResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteCipherKeySlotResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadCipherKeySlotStatusResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadCipherKeySlotStatusProtocolResponseData_t *fullresponse = (SBAND_TMTCReadCipherKeySlotStatusProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadCipherKeySlotStatusResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadCipherKeySlotStatusProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadCipherKeySlotStatusResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadCipherKeySlotStatusResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadCipherKeySlotStatusResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_EraseCipherKeySlotResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCEraseCipherKeySlotProtocolResponseData_t *fullresponse = (SBAND_TMTCEraseCipherKeySlotProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCEraseCipherKeySlotResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCEraseCipherKeySlotProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCEraseCipherKeySlotResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_EraseCipherKeySlotResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_EraseCipherKeySlotResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadConOps_HystCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadConOps_HystCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadConOps_HystCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadConOps_HystCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadConOps_HystCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadConOps_HystCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadConOps_HystCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadConOps_HystCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteConOps_HystCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteConOps_HystCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteConOps_HystCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteConOps_HystCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteConOps_HystCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteConOps_HystCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteConOps_HystCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteConOps_HystCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadPortCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadPortCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadPortCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadPortCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadPortCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadPortCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadPortCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadPortCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WritePortCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWritePortCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWritePortCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWritePortCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWritePortCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWritePortCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WritePortCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WritePortCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadLoggerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadLoggerCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadLoggerCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadLoggerCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadLoggerCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadLoggerCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadLoggerCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadLoggerCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteLoggerCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteLoggerCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteLoggerCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteLoggerCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteLoggerCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteLoggerCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteLoggerCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteLoggerCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_TransmitDataResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCTransmitDataProtocolResponseData_t *fullresponse = (SBAND_TMTCTransmitDataProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCTransmitDataResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCTransmitDataProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCTransmitDataResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_TransmitDataResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_TransmitDataResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_LoadPresetCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCLoadPresetCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCLoadPresetCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCLoadPresetCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCLoadPresetCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCLoadPresetCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_LoadPresetCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_LoadPresetCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_PingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCPingProtocolResponseData_t *fullresponse = (SBAND_TMTCPingProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCPingResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCPingProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCPingResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_PingResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_PingResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetDualPAModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetDualPAModeProtocolResponseData_t *fullresponse = (SBAND_TMTCSetDualPAModeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCSetDualPAModeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetDualPAModeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCSetDualPAModeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetDualPAModeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetDualPAModeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetDualPAModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetDualPAModeProtocolResponseData_t *fullresponse = (SBAND_TMTCGetDualPAModeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetDualPAModeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetDualPAModeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetDualPAModeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetDualPAModeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetDualPAModeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetTestPacketStateResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetTestPacketStateProtocolResponseData_t *fullresponse = (SBAND_TMTCSetTestPacketStateProtocolResponseData_t *) fp_DataInfo->pu8Data;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetTestPacketStateProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    // no out-arguments specified for response - simple acknowledge call
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetTestPacketStateResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetTestPacketStateResponseHandler(&responseCtx);
    }
}

static void fs_ReadRfFreqCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadRfFreqCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadRfFreqCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadRfFreqCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRfFreqCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadRfFreqCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadRfFreqCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadRfFreqCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteRfFreqCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteRfFreqCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteRfFreqCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteRfFreqCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteRfFreqCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteRfFreqCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteRfFreqCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteRfFreqCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ResetResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCResetProtocolResponseData_t *fullresponse = (SBAND_TMTCResetProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCResetResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCResetProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCResetResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ResetResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ResetResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ResetErrorCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCResetErrorCountersProtocolResponseData_t *fullresponse = (SBAND_TMTCResetErrorCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCResetErrorCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCResetErrorCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCResetErrorCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ResetErrorCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ResetErrorCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadSatCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadSatCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadSatCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadSatCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadSatCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadSatCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadSatCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadSatCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteSatCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteSatCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteSatCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteSatCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteSatCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteSatCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteSatCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteSatCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadTCProtocolResponseData_t *fullresponse = (SBAND_TMTCReadTCProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadTCResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadTCProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadTCResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadTCResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadTCResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ClearTCResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCClearTCProtocolResponseData_t *fullresponse = (SBAND_TMTCClearTCProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCClearTCResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCClearTCProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCClearTCResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ClearTCResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ClearTCResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadTempSensorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadTempSensorsProtocolResponseData_t *fullresponse = (SBAND_TMTCReadTempSensorsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadTempSensorsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadTempSensorsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadTempSensorsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadTempSensorsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadTempSensorsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_Ignore_PA_TSResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCIgnore_PA_TSProtocolResponseData_t *fullresponse = (SBAND_TMTCIgnore_PA_TSProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCIgnore_PA_TSResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCIgnore_PA_TSProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCIgnore_PA_TSResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_Ignore_PA_TSResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_Ignore_PA_TSResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadRadioCRCCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadRadioCRCCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCReadRadioCRCCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadRadioCRCCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRadioCRCCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadRadioCRCCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadRadioCRCCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadRadioCRCCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteRadioCRCCfgResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteRadioCRCCfgProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteRadioCRCCfgProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteRadioCRCCfgResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteRadioCRCCfgProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteRadioCRCCfgResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteRadioCRCCfgResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteRadioCRCCfgResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_WriteRadioPacketFecHdlcResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCWriteRadioPacketFecHdlcProtocolResponseData_t *fullresponse = (SBAND_TMTCWriteRadioPacketFecHdlcProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCWriteRadioPacketFecHdlcResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteRadioPacketFecHdlcProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCWriteRadioPacketFecHdlcResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_WriteRadioPacketFecHdlcResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_WriteRadioPacketFecHdlcResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadRadioPacketFecHdlcResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadRadioPacketFecHdlcProtocolResponseData_t *fullresponse = (SBAND_TMTCReadRadioPacketFecHdlcProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadRadioPacketFecHdlcResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRadioPacketFecHdlcProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadRadioPacketFecHdlcResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadRadioPacketFecHdlcResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadRadioPacketFecHdlcResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetPacketCountersResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetPacketCountersProtocolResponseData_t *fullresponse = (SBAND_TMTCGetPacketCountersProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetPacketCountersResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetPacketCountersProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetPacketCountersResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetPacketCountersResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetPacketCountersResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_ReadRadioErrorsResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCReadRadioErrorsProtocolResponseData_t *fullresponse = (SBAND_TMTCReadRadioErrorsProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCReadRadioErrorsResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRadioErrorsProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCReadRadioErrorsResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_ReadRadioErrorsResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_ReadRadioErrorsResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetModulationResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetModulationProtocolResponseData_t *fullresponse = (SBAND_TMTCGetModulationProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetModulationResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetModulationProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetModulationResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetModulationResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetModulationResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetModulationResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetModulationProtocolResponseData_t *fullresponse = (SBAND_TMTCSetModulationProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCSetModulationResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetModulationProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCSetModulationResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetModulationResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetModulationResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetBaudrateResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetBaudrateProtocolResponseData_t *fullresponse = (SBAND_TMTCGetBaudrateProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetBaudrateResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetBaudrateProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetBaudrateResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetBaudrateResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetBaudrateResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetBaudrateResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetBaudrateProtocolResponseData_t *fullresponse = (SBAND_TMTCSetBaudrateProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCSetBaudrateResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetBaudrateProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCSetBaudrateResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetBaudrateResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetBaudrateResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetFreqShapingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetFreqShapingProtocolResponseData_t *fullresponse = (SBAND_TMTCGetFreqShapingProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetFreqShapingResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetFreqShapingProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetFreqShapingResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetFreqShapingResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetFreqShapingResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetFreqShapingResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetFreqShapingProtocolResponseData_t *fullresponse = (SBAND_TMTCSetFreqShapingProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCSetFreqShapingResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetFreqShapingProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCSetFreqShapingResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetFreqShapingResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetFreqShapingResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetStreamModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetStreamModeProtocolResponseData_t *fullresponse = (SBAND_TMTCGetStreamModeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetStreamModeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetStreamModeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetStreamModeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetStreamModeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetStreamModeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetStreamModeResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetStreamModeProtocolResponseData_t *fullresponse = (SBAND_TMTCSetStreamModeProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCSetStreamModeResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetStreamModeProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCSetStreamModeResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetStreamModeResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetStreamModeResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetTargetPowerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetTargetPowerProtocolResponseData_t *fullresponse = (SBAND_TMTCGetTargetPowerProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetTargetPowerResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetTargetPowerProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetTargetPowerResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetTargetPowerResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetTargetPowerResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetTargetPowerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetTargetPowerProtocolResponseData_t *fullresponse = (SBAND_TMTCSetTargetPowerProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCSetTargetPowerResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetTargetPowerProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCSetTargetPowerResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetTargetPowerResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetTargetPowerResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_GetPacketScramblerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCGetPacketScramblerProtocolResponseData_t *fullresponse = (SBAND_TMTCGetPacketScramblerProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCGetPacketScramblerResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetPacketScramblerProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCGetPacketScramblerResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_GetPacketScramblerResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_GetPacketScramblerResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}

static void fs_SetPacketScramblerResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo)
{
    SBAND_TMTCSetPacketScramblerProtocolResponseData_t *fullresponse = (SBAND_TMTCSetPacketScramblerProtocolResponseData_t *) fp_DataInfo->pu8Data;
    SBAND_TMTCSetPacketScramblerResponseData_t *responsePayload = NULL;
    RespContext_t responseCtx;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetPacketScramblerProtocolResponseData_t);

    if ((fullresponse == NULL) || (pCliApiHnd == NULL) || (fp_DataInfo->u16DataSize != sizeof(*fullresponse)))
    {
        return;
    }
#ifndef BIG_ENDIAN_PLATFORM
    responsePayload = (SBAND_TMTCSetPacketScramblerResponseData_t *) &fullresponse->data;
#else   // #ifndef BIG_ENDIAN_PLATFORM
    // TBD: Deserialize response fields
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    if (pCliApiHnd->SBAND_TMTC_SetPacketScramblerResponseHandler != NULL)
    {
        responseCtx.nInterfaceNumber = fp_DataInfo->pMACContext->nInterfaceNumber;
        responseCtx.netType = fp_DataInfo->pMACContext->netType;
        responseCtx.nAddr = fp_DataInfo->pMACContext->nSourceAddr;
        responseCtx.seqId = fullresponse->hdr.seqId;

        pCliApiHnd->SBAND_TMTC_SetPacketScramblerResponseHandler(&responseCtx,
                                        ((fullresponse->hdr).errCode != ESSA_FP_ERRCODE_NOERROR) ? (NULL) : (responsePayload));
    }
}


/**********************************************************************
 *
 *  Public methods implementation
 *
 **********************************************************************/
void SBAND_TMTC_registerClientApi(SBAND_TMTC_ClientApi_t *pCliApiHandlers)
{
    pCliApiHnd = pCliApiHandlers;
}

ESSA_pStack_FunctionProtocolInfo_t SBAND_TMTC_getClientProtocolDescriptor(void)
{
    return (ESSA_pStack_FunctionProtocolInfo_t) &FP_SBAND_TMTCProtocolClientInfo;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetCapabilitiesReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetCapabilitiesProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetCapabilitiesProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetCapabilitiesProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETCAPABILITIES_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetCapabilitiesProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadUpTimeReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadUpTimeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadUpTimeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadUpTimeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READUPTIME_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadUpTimeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadHWHealthReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadHWHealthProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadHWHealthProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadHWHealthProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READHWHEALTH_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadHWHealthProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadEpsCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadEpsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadEpsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadEpsCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READEPSCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadEpsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteEpsCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sEpsCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteEpsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteEpsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteEpsCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITEEPSCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteEpsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadAutomatedBeaconsCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadAutomatedBeaconsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadAutomatedBeaconsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadAutomatedBeaconsCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READAUTOMATEDBEACONSCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadAutomatedBeaconsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteAutomatedBeaconsCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sAutoBeaconsCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteAutomatedBeaconsCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteAutomatedBeaconsCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteAutomatedBeaconsCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITEAUTOMATEDBEACONSCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteAutomatedBeaconsCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadErrorCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadErrorCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadErrorCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadErrorCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READERRORCOUNTERS_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadErrorCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadPipeModeCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadPipeModeCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadPipeModeCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadPipeModeCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READPIPEMODECFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadPipeModeCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WritePipeModeCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sPipeModeCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWritePipeModeCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWritePipeModeCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWritePipeModeCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITEPIPEMODECFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWritePipeModeCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadTxtBeaconContentCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadTxtBeaconContentCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadTxtBeaconContentCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadTxtBeaconContentCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READTXTBEACONCONTENTCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadTxtBeaconContentCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteTxtBeaconContentCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sTxtBeaconContentCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteTxtBeaconContentCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteTxtBeaconContentCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteTxtBeaconContentCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITETXTBEACONCONTENTCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteTxtBeaconContentCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadAx25CfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadAx25CfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadAx25CfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadAx25CfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READAX25CFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadAx25CfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteAx25CfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sAx25Cfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteAx25CfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteAx25CfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteAx25CfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITEAX25CFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteAx25CfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteCipherKeySlotReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sCipherKeySlot_t * const sSKeySlot
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteCipherKeySlotProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteCipherKeySlotProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteCipherKeySlotProtocolRequestData_t);

    if ((ctx != NULL) && (sSKeySlot != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITECIPHERKEYSLOT_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteCipherKeySlotProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadCipherKeySlotStatusReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eKeySlotID_t eSlotId
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadCipherKeySlotStatusProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadCipherKeySlotStatusProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadCipherKeySlotStatusProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READCIPHERKEYSLOTSTATUS_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eSlotId = eSlotId;
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
                                            sizeof(SBAND_TMTCReadCipherKeySlotStatusProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_EraseCipherKeySlotReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sCipherKeySlot_t * const sSKeySlot
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCEraseCipherKeySlotProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCEraseCipherKeySlotProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCEraseCipherKeySlotProtocolRequestData_t);

    if ((ctx != NULL) && (sSKeySlot != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_ERASECIPHERKEYSLOT_FUNC_ID;
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
                                            sizeof(SBAND_TMTCEraseCipherKeySlotProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadConOps_HystCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadConOps_HystCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadConOps_HystCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadConOps_HystCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READCONOPS_HYSTCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadConOps_HystCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteConOps_HystCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sConOps_Hysteresis_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteConOps_HystCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteConOps_HystCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteConOps_HystCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITECONOPS_HYSTCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteConOps_HystCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadPortCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_ePortID_t ePortID
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadPortCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadPortCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadPortCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READPORTCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.ePortID = ePortID;
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
                                            sizeof(SBAND_TMTCReadPortCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WritePortCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sCommPortCfgIn_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWritePortCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWritePortCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWritePortCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITEPORTCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWritePortCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadLoggerCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadLoggerCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadLoggerCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadLoggerCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READLOGGERCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadLoggerCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteLoggerCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sLogger_Cfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteLoggerCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteLoggerCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteLoggerCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITELOGGERCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteLoggerCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_TransmitDataReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sTxRadioMsg_t * const sMsg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCTransmitDataProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCTransmitDataProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCTransmitDataProtocolRequestData_t);

    if ((ctx != NULL) && (sMsg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_TRANSMITDATA_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sMsg != NULL)
        {
            requestParams.data.sMsg = *(sMsg);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sMsg,
                          0U,
                          sizeof(requestParams.data.sMsg));
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
                                            sizeof(SBAND_TMTCTransmitDataProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_LoadPresetCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_ePresetCfgType_t eCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCLoadPresetCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCLoadPresetCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCLoadPresetCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_LOADPRESETCFG_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eCfg = eCfg;
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
                                            sizeof(SBAND_TMTCLoadPresetCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_PingReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sPing_t * const sData
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCPingProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCPingProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCPingProtocolRequestData_t);

    if ((ctx != NULL) && (sData != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_PING_FUNC_ID;
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
                                            sizeof(SBAND_TMTCPingProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetDualPAModeReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_ePowerAmpControl_t eCtl
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetDualPAModeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetDualPAModeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetDualPAModeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETDUALPAMODE_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eCtl = eCtl;
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
                                            sizeof(SBAND_TMTCSetDualPAModeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetDualPAModeReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetDualPAModeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetDualPAModeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetDualPAModeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETDUALPAMODE_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetDualPAModeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetTestPacketStateReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sTestPacket_t * const sTp
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetTestPacketStateProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetTestPacketStateProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetTestPacketStateProtocolRequestData_t);

    if ((ctx != NULL) && (sTp != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETTESTPACKETSTATE_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        if (sTp != NULL)
        {
            requestParams.data.sTp = *(sTp);
        }
        else
        {
            (void) memset((void *) &requestParams.data.sTp,
                          0U,
                          sizeof(requestParams.data.sTp));
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
                                            sizeof(SBAND_TMTCSetTestPacketStateProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadRfFreqCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadRfFreqCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadRfFreqCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRfFreqCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READRFFREQCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadRfFreqCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteRfFreqCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sRfFreqCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteRfFreqCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteRfFreqCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteRfFreqCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITERFFREQCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteRfFreqCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ResetReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCResetProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCResetProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCResetProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_RESET_FUNC_ID;
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
                                            sizeof(SBAND_TMTCResetProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ResetErrorCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCResetErrorCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCResetErrorCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCResetErrorCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_RESETERRORCOUNTERS_FUNC_ID;
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
                                            sizeof(SBAND_TMTCResetErrorCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadSatCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadSatCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadSatCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadSatCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READSATCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadSatCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteSatCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sSatCfg_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteSatCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteSatCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteSatCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITESATCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteSatCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadTCReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadTCProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadTCProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadTCProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READTC_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadTCProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ClearTCReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCClearTCProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCClearTCProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCClearTCProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_CLEARTC_FUNC_ID;
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
                                            sizeof(SBAND_TMTCClearTCProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadTempSensorsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadTempSensorsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadTempSensorsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadTempSensorsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READTEMPSENSORS_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadTempSensorsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_Ignore_PA_TSReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCIgnore_PA_TSProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCIgnore_PA_TSProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCIgnore_PA_TSProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_IGNORE_PA_TS_FUNC_ID;
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
                                            sizeof(SBAND_TMTCIgnore_PA_TSProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadRadioCRCCfgReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadRadioCRCCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadRadioCRCCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRadioCRCCfgProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READRADIOCRCCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadRadioCRCCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteRadioCRCCfgReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_sRadioCRC_t * const sCfg
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteRadioCRCCfgProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteRadioCRCCfgProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteRadioCRCCfgProtocolRequestData_t);

    if ((ctx != NULL) && (sCfg != NULL))
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITERADIOCRCCFG_FUNC_ID;
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
                                            sizeof(SBAND_TMTCWriteRadioCRCCfgProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_WriteRadioPacketFecHdlcReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eOnOff_t eOnoff
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCWriteRadioPacketFecHdlcProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCWriteRadioPacketFecHdlcProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCWriteRadioPacketFecHdlcProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_WRITERADIOPACKETFECHDLC_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eOnoff = eOnoff;
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
                                            sizeof(SBAND_TMTCWriteRadioPacketFecHdlcProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadRadioPacketFecHdlcReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadRadioPacketFecHdlcProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadRadioPacketFecHdlcProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRadioPacketFecHdlcProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READRADIOPACKETFECHDLC_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadRadioPacketFecHdlcProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetPacketCountersReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetPacketCountersProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetPacketCountersProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetPacketCountersProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETPACKETCOUNTERS_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetPacketCountersProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_ReadRadioErrorsReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCReadRadioErrorsProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCReadRadioErrorsProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCReadRadioErrorsProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_READRADIOERRORS_FUNC_ID;
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
                                            sizeof(SBAND_TMTCReadRadioErrorsProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetModulationReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetModulationProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetModulationProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetModulationProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETMODULATION_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetModulationProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetModulationReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_Modulation_t eM
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetModulationProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetModulationProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetModulationProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETMODULATION_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eM = eM;
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
                                            sizeof(SBAND_TMTCSetModulationProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetBaudrateReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetBaudrateProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetBaudrateProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetBaudrateProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETBAUDRATE_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetBaudrateProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetBaudrateReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_Baudrate_t eB
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetBaudrateProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetBaudrateProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetBaudrateProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETBAUDRATE_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eB = eB;
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
                                            sizeof(SBAND_TMTCSetBaudrateProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetFreqShapingReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetFreqShapingProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetFreqShapingProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetFreqShapingProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETFREQSHAPING_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetFreqShapingProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetFreqShapingReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_Filtering_t eF
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetFreqShapingProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetFreqShapingProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetFreqShapingProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETFREQSHAPING_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eF = eF;
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
                                            sizeof(SBAND_TMTCSetFreqShapingProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetStreamModeReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetStreamModeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetStreamModeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetStreamModeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETSTREAMMODE_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetStreamModeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetStreamModeReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eOnOff_t eS
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetStreamModeProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetStreamModeProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetStreamModeProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETSTREAMMODE_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eS = eS;
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
                                            sizeof(SBAND_TMTCSetStreamModeProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetTargetPowerReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetTargetPowerProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetTargetPowerProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetTargetPowerProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETTARGETPOWER_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetTargetPowerProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetTargetPowerReq(
                ReqContext_t* ctx,
                const uint16_t u16Power
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetTargetPowerProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetTargetPowerProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetTargetPowerProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETTARGETPOWER_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.u16Power = u16Power;
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
                                            sizeof(SBAND_TMTCSetTargetPowerProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_GetPacketScramblerReq(
                ReqContext_t* ctx)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCGetPacketScramblerProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCGetPacketScramblerProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCGetPacketScramblerProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_GETPACKETSCRAMBLER_FUNC_ID;
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
                                            sizeof(SBAND_TMTCGetPacketScramblerProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}

ESSATMAC_ErrCodes SBAND_TMTC_SetPacketScramblerReq(
                ReqContext_t* ctx,
                const SBAND_TMTC_eOnOff_t eS
)
{
#ifndef BIG_ENDIAN_PLATFORM
    SBAND_TMTCSetPacketScramblerProtocolRequestData_t requestParams;
#else  // #ifndef BIG_ENDIAN_PLATFORM
    uint8_t requestParams[sizeof(SBAND_TMTCSetPacketScramblerProtocolRequestData_t)] = { 0 };
#endif  // #ifndef BIG_ENDIAN_PLATFORM

    ESSATMAC_ErrCodes sendResult = ESSATMAC_EC_NULL;

    STATIC_ASSERT_SIZE_CHECK(SBAND_TMTCSetPacketScramblerProtocolRequestData_t);

    if (ctx != NULL)
    {
#ifndef BIG_ENDIAN_PLATFORM
        // fill message header
        // RS485 wire protocol also uses LE byte order -> serialization of params is not needed
        requestParams.hdr.protoId = ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC;
        requestParams.hdr.funcId  = SBAND_TMTC_SETPACKETSCRAMBLER_FUNC_ID;
        requestParams.hdr.seqId   = FP_Helpers_GenMsgId();
        requestParams.hdr.errCode = ESSA_FP_ERRCODE_NOERROR;
        SET_REQUEST(requestParams.hdr);
        // Make seqId available to sender 
        ctx->seqId = requestParams.hdr.seqId;

        // fill message data
        requestParams.data.eS = eS;
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
                                            sizeof(SBAND_TMTCSetPacketScramblerProtocolRequestData_t),
                                            STACK_SENDFRAME_DEFAULT_PRIO,
                                            (ESSATMAC_DrvResult_Cbk_t) NULL,
                                            (uint32_t *) NULL);
    }

    return sendResult;
}


