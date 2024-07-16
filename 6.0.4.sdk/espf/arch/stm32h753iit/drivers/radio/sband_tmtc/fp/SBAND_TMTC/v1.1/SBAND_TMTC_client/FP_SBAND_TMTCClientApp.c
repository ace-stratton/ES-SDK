/*!
********************************************************************************************
* @file FP_SBAND_TMTCClientApp.c
* @brief ClientApp implementation template generator
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

// @START_USER@ USER_INCLUDES
// Place user includes here to preserve them during merge!!!
#include "sband_tmtc.h"
// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL

static void SBAND_TMTC_GetCapabilitiesResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetCapabilitiesResponseData_t* pResponseData);

static void SBAND_TMTC_ReadUpTimeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadUpTimeResponseData_t* pResponseData);

static void SBAND_TMTC_ReadHWHealthResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadHWHealthResponseData_t* pResponseData);

static void SBAND_TMTC_ReadEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadEpsCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteEpsCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadAutomatedBeaconsCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteAutomatedBeaconsCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ReadErrorCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadErrorCountersResponseData_t* pResponseData);

static void SBAND_TMTC_ReadPipeModeCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadPipeModeCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WritePipeModeCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWritePipeModeCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ReadTxtBeaconContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadTxtBeaconContentCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteTxtBeaconContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteTxtBeaconContentCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ReadAx25CfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadAx25CfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteAx25CfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteAx25CfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteCipherKeySlotResponseData_t* pResponseData);

static void SBAND_TMTC_ReadCipherKeySlotStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadCipherKeySlotStatusResponseData_t* pResponseData);

static void SBAND_TMTC_EraseCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCEraseCipherKeySlotResponseData_t* pResponseData);

static void SBAND_TMTC_ReadConOps_HystCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadConOps_HystCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteConOps_HystCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteConOps_HystCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ReadPortCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadPortCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WritePortCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWritePortCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ReadLoggerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadLoggerCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteLoggerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteLoggerCfgResponseData_t* pResponseData);

static void SBAND_TMTC_TransmitDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCTransmitDataResponseData_t* pResponseData);

static void SBAND_TMTC_LoadPresetCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCLoadPresetCfgResponseData_t* pResponseData);

static void SBAND_TMTC_PingResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCPingResponseData_t* pResponseData);

static void SBAND_TMTC_SetDualPAModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetDualPAModeResponseData_t* pResponseData);

static void SBAND_TMTC_GetDualPAModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetDualPAModeResponseData_t* pResponseData);

static void SBAND_TMTC_SetTestPacketStateResponseHandlerImpl(RespContext_t* pRespCtx);

static void SBAND_TMTC_ReadRfFreqCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRfFreqCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteRfFreqCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteRfFreqCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ResetResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCResetResponseData_t* pResponseData);

static void SBAND_TMTC_ResetErrorCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCResetErrorCountersResponseData_t* pResponseData);

static void SBAND_TMTC_ReadSatCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadSatCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteSatCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteSatCfgResponseData_t* pResponseData);

static void SBAND_TMTC_ReadTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadTCResponseData_t* pResponseData);

static void SBAND_TMTC_ClearTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCClearTCResponseData_t* pResponseData);

static void SBAND_TMTC_ReadTempSensorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadTempSensorsResponseData_t* pResponseData);

static void SBAND_TMTC_Ignore_PA_TSResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCIgnore_PA_TSResponseData_t* pResponseData);

static void SBAND_TMTC_ReadRadioCRCCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRadioCRCCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteRadioCRCCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteRadioCRCCfgResponseData_t* pResponseData);

static void SBAND_TMTC_WriteRadioPacketFecHdlcResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteRadioPacketFecHdlcResponseData_t* pResponseData);

static void SBAND_TMTC_ReadRadioPacketFecHdlcResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRadioPacketFecHdlcResponseData_t* pResponseData);

static void SBAND_TMTC_GetPacketCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetPacketCountersResponseData_t* pResponseData);

static void SBAND_TMTC_ReadRadioErrorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRadioErrorsResponseData_t* pResponseData);

static void SBAND_TMTC_GetModulationResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetModulationResponseData_t* pResponseData);

static void SBAND_TMTC_SetModulationResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetModulationResponseData_t* pResponseData);

static void SBAND_TMTC_GetBaudrateResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetBaudrateResponseData_t* pResponseData);

static void SBAND_TMTC_SetBaudrateResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetBaudrateResponseData_t* pResponseData);

static void SBAND_TMTC_GetFreqShapingResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetFreqShapingResponseData_t* pResponseData);

static void SBAND_TMTC_SetFreqShapingResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetFreqShapingResponseData_t* pResponseData);

static void SBAND_TMTC_GetStreamModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetStreamModeResponseData_t* pResponseData);

static void SBAND_TMTC_SetStreamModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetStreamModeResponseData_t* pResponseData);

static void SBAND_TMTC_GetTargetPowerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetTargetPowerResponseData_t* pResponseData);

static void SBAND_TMTC_SetTargetPowerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetTargetPowerResponseData_t* pResponseData);

static void SBAND_TMTC_GetPacketScramblerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetPacketScramblerResponseData_t* pResponseData);

static void SBAND_TMTC_SetPacketScramblerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetPacketScramblerResponseData_t* pResponseData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static SBAND_TMTC_ClientApi_t SBAND_TMTCClientApiCtx =
{
  .SBAND_TMTC_GetCapabilitiesResponseHandler = (pfSBAND_TMTC_GetCapabilitiesResponseHandler_t) SBAND_TMTC_GetCapabilitiesResponseHandlerImpl,
  .SBAND_TMTC_ReadUpTimeResponseHandler = (pfSBAND_TMTC_ReadUpTimeResponseHandler_t) SBAND_TMTC_ReadUpTimeResponseHandlerImpl,
  .SBAND_TMTC_ReadHWHealthResponseHandler = (pfSBAND_TMTC_ReadHWHealthResponseHandler_t) SBAND_TMTC_ReadHWHealthResponseHandlerImpl,
  .SBAND_TMTC_ReadEpsCfgResponseHandler = (pfSBAND_TMTC_ReadEpsCfgResponseHandler_t) SBAND_TMTC_ReadEpsCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteEpsCfgResponseHandler = (pfSBAND_TMTC_WriteEpsCfgResponseHandler_t) SBAND_TMTC_WriteEpsCfgResponseHandlerImpl,
  .SBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandler = (pfSBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandler_t) SBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandler = (pfSBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandler_t) SBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandlerImpl,
  .SBAND_TMTC_ReadErrorCountersResponseHandler = (pfSBAND_TMTC_ReadErrorCountersResponseHandler_t) SBAND_TMTC_ReadErrorCountersResponseHandlerImpl,
  .SBAND_TMTC_ReadPipeModeCfgResponseHandler = (pfSBAND_TMTC_ReadPipeModeCfgResponseHandler_t) SBAND_TMTC_ReadPipeModeCfgResponseHandlerImpl,
  .SBAND_TMTC_WritePipeModeCfgResponseHandler = (pfSBAND_TMTC_WritePipeModeCfgResponseHandler_t) SBAND_TMTC_WritePipeModeCfgResponseHandlerImpl,
  .SBAND_TMTC_ReadTxtBeaconContentCfgResponseHandler = (pfSBAND_TMTC_ReadTxtBeaconContentCfgResponseHandler_t) SBAND_TMTC_ReadTxtBeaconContentCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteTxtBeaconContentCfgResponseHandler = (pfSBAND_TMTC_WriteTxtBeaconContentCfgResponseHandler_t) SBAND_TMTC_WriteTxtBeaconContentCfgResponseHandlerImpl,
  .SBAND_TMTC_ReadAx25CfgResponseHandler = (pfSBAND_TMTC_ReadAx25CfgResponseHandler_t) SBAND_TMTC_ReadAx25CfgResponseHandlerImpl,
  .SBAND_TMTC_WriteAx25CfgResponseHandler = (pfSBAND_TMTC_WriteAx25CfgResponseHandler_t) SBAND_TMTC_WriteAx25CfgResponseHandlerImpl,
  .SBAND_TMTC_WriteCipherKeySlotResponseHandler = (pfSBAND_TMTC_WriteCipherKeySlotResponseHandler_t) SBAND_TMTC_WriteCipherKeySlotResponseHandlerImpl,
  .SBAND_TMTC_ReadCipherKeySlotStatusResponseHandler = (pfSBAND_TMTC_ReadCipherKeySlotStatusResponseHandler_t) SBAND_TMTC_ReadCipherKeySlotStatusResponseHandlerImpl,
  .SBAND_TMTC_EraseCipherKeySlotResponseHandler = (pfSBAND_TMTC_EraseCipherKeySlotResponseHandler_t) SBAND_TMTC_EraseCipherKeySlotResponseHandlerImpl,
  .SBAND_TMTC_ReadConOps_HystCfgResponseHandler = (pfSBAND_TMTC_ReadConOps_HystCfgResponseHandler_t) SBAND_TMTC_ReadConOps_HystCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteConOps_HystCfgResponseHandler = (pfSBAND_TMTC_WriteConOps_HystCfgResponseHandler_t) SBAND_TMTC_WriteConOps_HystCfgResponseHandlerImpl,
  .SBAND_TMTC_ReadPortCfgResponseHandler = (pfSBAND_TMTC_ReadPortCfgResponseHandler_t) SBAND_TMTC_ReadPortCfgResponseHandlerImpl,
  .SBAND_TMTC_WritePortCfgResponseHandler = (pfSBAND_TMTC_WritePortCfgResponseHandler_t) SBAND_TMTC_WritePortCfgResponseHandlerImpl,
  .SBAND_TMTC_ReadLoggerCfgResponseHandler = (pfSBAND_TMTC_ReadLoggerCfgResponseHandler_t) SBAND_TMTC_ReadLoggerCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteLoggerCfgResponseHandler = (pfSBAND_TMTC_WriteLoggerCfgResponseHandler_t) SBAND_TMTC_WriteLoggerCfgResponseHandlerImpl,
  .SBAND_TMTC_TransmitDataResponseHandler = (pfSBAND_TMTC_TransmitDataResponseHandler_t) SBAND_TMTC_TransmitDataResponseHandlerImpl,
  .SBAND_TMTC_LoadPresetCfgResponseHandler = (pfSBAND_TMTC_LoadPresetCfgResponseHandler_t) SBAND_TMTC_LoadPresetCfgResponseHandlerImpl,
  .SBAND_TMTC_PingResponseHandler = (pfSBAND_TMTC_PingResponseHandler_t) SBAND_TMTC_PingResponseHandlerImpl,
  .SBAND_TMTC_SetDualPAModeResponseHandler = (pfSBAND_TMTC_SetDualPAModeResponseHandler_t) SBAND_TMTC_SetDualPAModeResponseHandlerImpl,
  .SBAND_TMTC_GetDualPAModeResponseHandler = (pfSBAND_TMTC_GetDualPAModeResponseHandler_t) SBAND_TMTC_GetDualPAModeResponseHandlerImpl,
  .SBAND_TMTC_SetTestPacketStateResponseHandler = (pfSBAND_TMTC_SetTestPacketStateResponseHandler_t) SBAND_TMTC_SetTestPacketStateResponseHandlerImpl,
  .SBAND_TMTC_ReadRfFreqCfgResponseHandler = (pfSBAND_TMTC_ReadRfFreqCfgResponseHandler_t) SBAND_TMTC_ReadRfFreqCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteRfFreqCfgResponseHandler = (pfSBAND_TMTC_WriteRfFreqCfgResponseHandler_t) SBAND_TMTC_WriteRfFreqCfgResponseHandlerImpl,
  .SBAND_TMTC_ResetResponseHandler = (pfSBAND_TMTC_ResetResponseHandler_t) SBAND_TMTC_ResetResponseHandlerImpl,
  .SBAND_TMTC_ResetErrorCountersResponseHandler = (pfSBAND_TMTC_ResetErrorCountersResponseHandler_t) SBAND_TMTC_ResetErrorCountersResponseHandlerImpl,
  .SBAND_TMTC_ReadSatCfgResponseHandler = (pfSBAND_TMTC_ReadSatCfgResponseHandler_t) SBAND_TMTC_ReadSatCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteSatCfgResponseHandler = (pfSBAND_TMTC_WriteSatCfgResponseHandler_t) SBAND_TMTC_WriteSatCfgResponseHandlerImpl,
  .SBAND_TMTC_ReadTCResponseHandler = (pfSBAND_TMTC_ReadTCResponseHandler_t) SBAND_TMTC_ReadTCResponseHandlerImpl,
  .SBAND_TMTC_ClearTCResponseHandler = (pfSBAND_TMTC_ClearTCResponseHandler_t) SBAND_TMTC_ClearTCResponseHandlerImpl,
  .SBAND_TMTC_ReadTempSensorsResponseHandler = (pfSBAND_TMTC_ReadTempSensorsResponseHandler_t) SBAND_TMTC_ReadTempSensorsResponseHandlerImpl,
  .SBAND_TMTC_Ignore_PA_TSResponseHandler = (pfSBAND_TMTC_Ignore_PA_TSResponseHandler_t) SBAND_TMTC_Ignore_PA_TSResponseHandlerImpl,
  .SBAND_TMTC_ReadRadioCRCCfgResponseHandler = (pfSBAND_TMTC_ReadRadioCRCCfgResponseHandler_t) SBAND_TMTC_ReadRadioCRCCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteRadioCRCCfgResponseHandler = (pfSBAND_TMTC_WriteRadioCRCCfgResponseHandler_t) SBAND_TMTC_WriteRadioCRCCfgResponseHandlerImpl,
  .SBAND_TMTC_WriteRadioPacketFecHdlcResponseHandler = (pfSBAND_TMTC_WriteRadioPacketFecHdlcResponseHandler_t) SBAND_TMTC_WriteRadioPacketFecHdlcResponseHandlerImpl,
  .SBAND_TMTC_ReadRadioPacketFecHdlcResponseHandler = (pfSBAND_TMTC_ReadRadioPacketFecHdlcResponseHandler_t) SBAND_TMTC_ReadRadioPacketFecHdlcResponseHandlerImpl,
  .SBAND_TMTC_GetPacketCountersResponseHandler = (pfSBAND_TMTC_GetPacketCountersResponseHandler_t) SBAND_TMTC_GetPacketCountersResponseHandlerImpl,
  .SBAND_TMTC_ReadRadioErrorsResponseHandler = (pfSBAND_TMTC_ReadRadioErrorsResponseHandler_t) SBAND_TMTC_ReadRadioErrorsResponseHandlerImpl,
  .SBAND_TMTC_GetModulationResponseHandler = (pfSBAND_TMTC_GetModulationResponseHandler_t) SBAND_TMTC_GetModulationResponseHandlerImpl,
  .SBAND_TMTC_SetModulationResponseHandler = (pfSBAND_TMTC_SetModulationResponseHandler_t) SBAND_TMTC_SetModulationResponseHandlerImpl,
  .SBAND_TMTC_GetBaudrateResponseHandler = (pfSBAND_TMTC_GetBaudrateResponseHandler_t) SBAND_TMTC_GetBaudrateResponseHandlerImpl,
  .SBAND_TMTC_SetBaudrateResponseHandler = (pfSBAND_TMTC_SetBaudrateResponseHandler_t) SBAND_TMTC_SetBaudrateResponseHandlerImpl,
  .SBAND_TMTC_GetFreqShapingResponseHandler = (pfSBAND_TMTC_GetFreqShapingResponseHandler_t) SBAND_TMTC_GetFreqShapingResponseHandlerImpl,
  .SBAND_TMTC_SetFreqShapingResponseHandler = (pfSBAND_TMTC_SetFreqShapingResponseHandler_t) SBAND_TMTC_SetFreqShapingResponseHandlerImpl,
  .SBAND_TMTC_GetStreamModeResponseHandler = (pfSBAND_TMTC_GetStreamModeResponseHandler_t) SBAND_TMTC_GetStreamModeResponseHandlerImpl,
  .SBAND_TMTC_SetStreamModeResponseHandler = (pfSBAND_TMTC_SetStreamModeResponseHandler_t) SBAND_TMTC_SetStreamModeResponseHandlerImpl,
  .SBAND_TMTC_GetTargetPowerResponseHandler = (pfSBAND_TMTC_GetTargetPowerResponseHandler_t) SBAND_TMTC_GetTargetPowerResponseHandlerImpl,
  .SBAND_TMTC_SetTargetPowerResponseHandler = (pfSBAND_TMTC_SetTargetPowerResponseHandler_t) SBAND_TMTC_SetTargetPowerResponseHandlerImpl,
  .SBAND_TMTC_GetPacketScramblerResponseHandler = (pfSBAND_TMTC_GetPacketScramblerResponseHandler_t) SBAND_TMTC_GetPacketScramblerResponseHandlerImpl,
  .SBAND_TMTC_SetPacketScramblerResponseHandler = (pfSBAND_TMTC_SetPacketScramblerResponseHandler_t) SBAND_TMTC_SetPacketScramblerResponseHandlerImpl,
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Response handler for method SBAND_TMTC::GetCapabilities (ID = 0x00000001)
static void SBAND_TMTC_GetCapabilitiesResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetCapabilitiesResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetCapabilities@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetCapabilities@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetCapabilities@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetCapabilities@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetCapabilities (ID = 0x00000001)

// @START@ Response handler for method SBAND_TMTC::ReadUpTime (ID = 0x00000002)
static void SBAND_TMTC_ReadUpTimeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadUpTimeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadUpTime@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadUpTime@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadUpTime@
        
    	sband_tmtc_uptime_response_handler(pRespCtx, pResponseData);

        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadUpTime@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadUpTime (ID = 0x00000002)

// @START@ Response handler for method SBAND_TMTC::ReadHWHealth (ID = 0x00000003)
static void SBAND_TMTC_ReadHWHealthResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadHWHealthResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadHWHealth@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadHWHealth@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadHWHealth@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadHWHealth@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadHWHealth (ID = 0x00000003)

// @START@ Response handler for method SBAND_TMTC::ReadEpsCfg (ID = 0x00000004)
static void SBAND_TMTC_ReadEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadEpsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadEpsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadEpsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadEpsCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadEpsCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadEpsCfg (ID = 0x00000004)

// @START@ Response handler for method SBAND_TMTC::WriteEpsCfg (ID = 0x00000005)
static void SBAND_TMTC_WriteEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteEpsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteEpsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteEpsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteEpsCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteEpsCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteEpsCfg (ID = 0x00000005)

// @START@ Response handler for method SBAND_TMTC::ReadAutomatedBeaconsCfg (ID = 0x00000006)
static void SBAND_TMTC_ReadAutomatedBeaconsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadAutomatedBeaconsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadAutomatedBeaconsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadAutomatedBeaconsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadAutomatedBeaconsCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadAutomatedBeaconsCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadAutomatedBeaconsCfg (ID = 0x00000006)

// @START@ Response handler for method SBAND_TMTC::WriteAutomatedBeaconsCfg (ID = 0x00000007)
static void SBAND_TMTC_WriteAutomatedBeaconsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteAutomatedBeaconsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteAutomatedBeaconsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteAutomatedBeaconsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteAutomatedBeaconsCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteAutomatedBeaconsCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteAutomatedBeaconsCfg (ID = 0x00000007)

// @START@ Response handler for method SBAND_TMTC::ReadErrorCounters (ID = 0x00000008)
static void SBAND_TMTC_ReadErrorCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadErrorCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadErrorCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadErrorCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadErrorCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadErrorCounters@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadErrorCounters (ID = 0x00000008)

// @START@ Response handler for method SBAND_TMTC::ReadPipeModeCfg (ID = 0x00000009)
static void SBAND_TMTC_ReadPipeModeCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadPipeModeCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadPipeModeCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadPipeModeCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadPipeModeCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadPipeModeCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadPipeModeCfg (ID = 0x00000009)

// @START@ Response handler for method SBAND_TMTC::WritePipeModeCfg (ID = 0x0000000A)
static void SBAND_TMTC_WritePipeModeCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWritePipeModeCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WritePipeModeCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WritePipeModeCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WritePipeModeCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WritePipeModeCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WritePipeModeCfg (ID = 0x0000000A)

// @START@ Response handler for method SBAND_TMTC::ReadTxtBeaconContentCfg (ID = 0x0000000B)
static void SBAND_TMTC_ReadTxtBeaconContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadTxtBeaconContentCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadTxtBeaconContentCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadTxtBeaconContentCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadTxtBeaconContentCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadTxtBeaconContentCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadTxtBeaconContentCfg (ID = 0x0000000B)

// @START@ Response handler for method SBAND_TMTC::WriteTxtBeaconContentCfg (ID = 0x0000000C)
static void SBAND_TMTC_WriteTxtBeaconContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteTxtBeaconContentCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteTxtBeaconContentCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteTxtBeaconContentCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteTxtBeaconContentCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteTxtBeaconContentCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteTxtBeaconContentCfg (ID = 0x0000000C)

// @START@ Response handler for method SBAND_TMTC::ReadAx25Cfg (ID = 0x0000000D)
static void SBAND_TMTC_ReadAx25CfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadAx25CfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadAx25Cfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadAx25Cfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadAx25Cfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadAx25Cfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadAx25Cfg (ID = 0x0000000D)

// @START@ Response handler for method SBAND_TMTC::WriteAx25Cfg (ID = 0x0000000E)
static void SBAND_TMTC_WriteAx25CfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteAx25CfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteAx25Cfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteAx25Cfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteAx25Cfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteAx25Cfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteAx25Cfg (ID = 0x0000000E)

// @START@ Response handler for method SBAND_TMTC::WriteCipherKeySlot (ID = 0x0000000F)
static void SBAND_TMTC_WriteCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteCipherKeySlotResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteCipherKeySlot@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteCipherKeySlot@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteCipherKeySlot@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteCipherKeySlot@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteCipherKeySlot (ID = 0x0000000F)

// @START@ Response handler for method SBAND_TMTC::ReadCipherKeySlotStatus (ID = 0x00000010)
static void SBAND_TMTC_ReadCipherKeySlotStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadCipherKeySlotStatusResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadCipherKeySlotStatus@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadCipherKeySlotStatus@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadCipherKeySlotStatus@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadCipherKeySlotStatus@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadCipherKeySlotStatus (ID = 0x00000010)

// @START@ Response handler for method SBAND_TMTC::EraseCipherKeySlot (ID = 0x00000011)
static void SBAND_TMTC_EraseCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCEraseCipherKeySlotResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::EraseCipherKeySlot@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::EraseCipherKeySlot@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::EraseCipherKeySlot@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::EraseCipherKeySlot@
    }
}
// @END@ Response handler for method SBAND_TMTC::EraseCipherKeySlot (ID = 0x00000011)

// @START@ Response handler for method SBAND_TMTC::ReadConOps_HystCfg (ID = 0x00000012)
static void SBAND_TMTC_ReadConOps_HystCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadConOps_HystCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadConOps_HystCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadConOps_HystCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadConOps_HystCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadConOps_HystCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadConOps_HystCfg (ID = 0x00000012)

// @START@ Response handler for method SBAND_TMTC::WriteConOps_HystCfg (ID = 0x00000013)
static void SBAND_TMTC_WriteConOps_HystCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteConOps_HystCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteConOps_HystCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteConOps_HystCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteConOps_HystCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteConOps_HystCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteConOps_HystCfg (ID = 0x00000013)

// @START@ Response handler for method SBAND_TMTC::ReadPortCfg (ID = 0x00000014)
static void SBAND_TMTC_ReadPortCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadPortCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadPortCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadPortCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadPortCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadPortCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadPortCfg (ID = 0x00000014)

// @START@ Response handler for method SBAND_TMTC::WritePortCfg (ID = 0x00000015)
static void SBAND_TMTC_WritePortCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWritePortCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WritePortCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WritePortCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WritePortCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WritePortCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WritePortCfg (ID = 0x00000015)

// @START@ Response handler for method SBAND_TMTC::ReadLoggerCfg (ID = 0x00000016)
static void SBAND_TMTC_ReadLoggerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadLoggerCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadLoggerCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadLoggerCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadLoggerCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadLoggerCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadLoggerCfg (ID = 0x00000016)

// @START@ Response handler for method SBAND_TMTC::WriteLoggerCfg (ID = 0x00000017)
static void SBAND_TMTC_WriteLoggerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteLoggerCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteLoggerCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteLoggerCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteLoggerCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteLoggerCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteLoggerCfg (ID = 0x00000017)

// @START@ Response handler for method SBAND_TMTC::TransmitData (ID = 0x00000018)
static void SBAND_TMTC_TransmitDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCTransmitDataResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::TransmitData@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::TransmitData@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::TransmitData@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::TransmitData@
    }
}
// @END@ Response handler for method SBAND_TMTC::TransmitData (ID = 0x00000018)

// @START@ Response handler for method SBAND_TMTC::LoadPresetCfg (ID = 0x00000019)
static void SBAND_TMTC_LoadPresetCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCLoadPresetCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::LoadPresetCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::LoadPresetCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::LoadPresetCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::LoadPresetCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::LoadPresetCfg (ID = 0x00000019)

// @START@ Response handler for method SBAND_TMTC::Ping (ID = 0x0000001A)
static void SBAND_TMTC_PingResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCPingResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::Ping@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::Ping@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::Ping@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::Ping@
    }
}
// @END@ Response handler for method SBAND_TMTC::Ping (ID = 0x0000001A)

// @START@ Response handler for method SBAND_TMTC::SetDualPAMode (ID = 0x0000001B)
static void SBAND_TMTC_SetDualPAModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetDualPAModeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetDualPAMode@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetDualPAMode@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetDualPAMode@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetDualPAMode@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetDualPAMode (ID = 0x0000001B)

// @START@ Response handler for method SBAND_TMTC::GetDualPAMode (ID = 0x0000001C)
static void SBAND_TMTC_GetDualPAModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetDualPAModeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetDualPAMode@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetDualPAMode@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetDualPAMode@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetDualPAMode@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetDualPAMode (ID = 0x0000001C)

// @START@ Response handler for method SBAND_TMTC::SetTestPacketState (ID = 0x0000001D)
static void SBAND_TMTC_SetTestPacketStateResponseHandlerImpl(RespContext_t* pRespCtx)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetTestPacketState@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetTestPacketState@

    if (pRespCtx != NULL)
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetTestPacketState@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetTestPacketState@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetTestPacketState (ID = 0x0000001D)

// @START@ Response handler for method SBAND_TMTC::ReadRfFreqCfg (ID = 0x0000001E)
static void SBAND_TMTC_ReadRfFreqCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRfFreqCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadRfFreqCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadRfFreqCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadRfFreqCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadRfFreqCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadRfFreqCfg (ID = 0x0000001E)

// @START@ Response handler for method SBAND_TMTC::WriteRfFreqCfg (ID = 0x0000001F)
static void SBAND_TMTC_WriteRfFreqCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteRfFreqCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteRfFreqCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteRfFreqCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteRfFreqCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteRfFreqCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteRfFreqCfg (ID = 0x0000001F)

// @START@ Response handler for method SBAND_TMTC::Reset (ID = 0x00000020)
static void SBAND_TMTC_ResetResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCResetResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::Reset@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::Reset@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::Reset@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::Reset@
    }
}
// @END@ Response handler for method SBAND_TMTC::Reset (ID = 0x00000020)

// @START@ Response handler for method SBAND_TMTC::ResetErrorCounters (ID = 0x00000021)
static void SBAND_TMTC_ResetErrorCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCResetErrorCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ResetErrorCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ResetErrorCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ResetErrorCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ResetErrorCounters@
    }
}
// @END@ Response handler for method SBAND_TMTC::ResetErrorCounters (ID = 0x00000021)

// @START@ Response handler for method SBAND_TMTC::ReadSatCfg (ID = 0x00000022)
static void SBAND_TMTC_ReadSatCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadSatCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadSatCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadSatCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadSatCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadSatCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadSatCfg (ID = 0x00000022)

// @START@ Response handler for method SBAND_TMTC::WriteSatCfg (ID = 0x00000023)
static void SBAND_TMTC_WriteSatCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteSatCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteSatCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteSatCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteSatCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteSatCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteSatCfg (ID = 0x00000023)

// @START@ Response handler for method SBAND_TMTC::ReadTC (ID = 0x00000024)
static void SBAND_TMTC_ReadTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadTCResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadTC@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadTC@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadTC@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadTC@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadTC (ID = 0x00000024)

// @START@ Response handler for method SBAND_TMTC::ClearTC (ID = 0x00000025)
static void SBAND_TMTC_ClearTCResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCClearTCResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ClearTC@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ClearTC@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ClearTC@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ClearTC@
    }
}
// @END@ Response handler for method SBAND_TMTC::ClearTC (ID = 0x00000025)

// @START@ Response handler for method SBAND_TMTC::ReadTempSensors (ID = 0x00000026)
static void SBAND_TMTC_ReadTempSensorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadTempSensorsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadTempSensors@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadTempSensors@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadTempSensors@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadTempSensors@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadTempSensors (ID = 0x00000026)

// @START@ Response handler for method SBAND_TMTC::Ignore_PA_TS (ID = 0x00000027)
static void SBAND_TMTC_Ignore_PA_TSResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCIgnore_PA_TSResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::Ignore_PA_TS@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::Ignore_PA_TS@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::Ignore_PA_TS@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::Ignore_PA_TS@
    }
}
// @END@ Response handler for method SBAND_TMTC::Ignore_PA_TS (ID = 0x00000027)

// @START@ Response handler for method SBAND_TMTC::ReadRadioCRCCfg (ID = 0x00000028)
static void SBAND_TMTC_ReadRadioCRCCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRadioCRCCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadRadioCRCCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadRadioCRCCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadRadioCRCCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadRadioCRCCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadRadioCRCCfg (ID = 0x00000028)

// @START@ Response handler for method SBAND_TMTC::WriteRadioCRCCfg (ID = 0x00000029)
static void SBAND_TMTC_WriteRadioCRCCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteRadioCRCCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteRadioCRCCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteRadioCRCCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteRadioCRCCfg@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteRadioCRCCfg@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteRadioCRCCfg (ID = 0x00000029)

// @START@ Response handler for method SBAND_TMTC::WriteRadioPacketFecHdlc (ID = 0x0000002A)
static void SBAND_TMTC_WriteRadioPacketFecHdlcResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCWriteRadioPacketFecHdlcResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::WriteRadioPacketFecHdlc@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::WriteRadioPacketFecHdlc@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::WriteRadioPacketFecHdlc@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::WriteRadioPacketFecHdlc@
    }
}
// @END@ Response handler for method SBAND_TMTC::WriteRadioPacketFecHdlc (ID = 0x0000002A)

// @START@ Response handler for method SBAND_TMTC::ReadRadioPacketFecHdlc (ID = 0x0000002B)
static void SBAND_TMTC_ReadRadioPacketFecHdlcResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRadioPacketFecHdlcResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadRadioPacketFecHdlc@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadRadioPacketFecHdlc@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadRadioPacketFecHdlc@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadRadioPacketFecHdlc@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadRadioPacketFecHdlc (ID = 0x0000002B)

// @START@ Response handler for method SBAND_TMTC::GetPacketCounters (ID = 0x0000002C)
static void SBAND_TMTC_GetPacketCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetPacketCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetPacketCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetPacketCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetPacketCounters@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetPacketCounters@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetPacketCounters (ID = 0x0000002C)

// @START@ Response handler for method SBAND_TMTC::ReadRadioErrors (ID = 0x0000002D)
static void SBAND_TMTC_ReadRadioErrorsResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCReadRadioErrorsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::ReadRadioErrors@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::ReadRadioErrors@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::ReadRadioErrors@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::ReadRadioErrors@
    }
}
// @END@ Response handler for method SBAND_TMTC::ReadRadioErrors (ID = 0x0000002D)

// @START@ Response handler for method SBAND_TMTC::GetModulation (ID = 0x0000002E)
static void SBAND_TMTC_GetModulationResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetModulationResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetModulation@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetModulation@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetModulation@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetModulation@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetModulation (ID = 0x0000002E)

// @START@ Response handler for method SBAND_TMTC::SetModulation (ID = 0x0000002F)
static void SBAND_TMTC_SetModulationResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetModulationResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetModulation@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetModulation@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetModulation@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetModulation@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetModulation (ID = 0x0000002F)

// @START@ Response handler for method SBAND_TMTC::GetBaudrate (ID = 0x00000030)
static void SBAND_TMTC_GetBaudrateResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetBaudrateResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetBaudrate@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetBaudrate@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetBaudrate@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetBaudrate@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetBaudrate (ID = 0x00000030)

// @START@ Response handler for method SBAND_TMTC::SetBaudrate (ID = 0x00000031)
static void SBAND_TMTC_SetBaudrateResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetBaudrateResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetBaudrate@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetBaudrate@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetBaudrate@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetBaudrate@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetBaudrate (ID = 0x00000031)

// @START@ Response handler for method SBAND_TMTC::GetFreqShaping (ID = 0x00000032)
static void SBAND_TMTC_GetFreqShapingResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetFreqShapingResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetFreqShaping@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetFreqShaping@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetFreqShaping@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetFreqShaping@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetFreqShaping (ID = 0x00000032)

// @START@ Response handler for method SBAND_TMTC::SetFreqShaping (ID = 0x00000033)
static void SBAND_TMTC_SetFreqShapingResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetFreqShapingResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetFreqShaping@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetFreqShaping@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetFreqShaping@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetFreqShaping@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetFreqShaping (ID = 0x00000033)

// @START@ Response handler for method SBAND_TMTC::GetStreamMode (ID = 0x00000034)
static void SBAND_TMTC_GetStreamModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetStreamModeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetStreamMode@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetStreamMode@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetStreamMode@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetStreamMode@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetStreamMode (ID = 0x00000034)

// @START@ Response handler for method SBAND_TMTC::SetStreamMode (ID = 0x00000035)
static void SBAND_TMTC_SetStreamModeResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetStreamModeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetStreamMode@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetStreamMode@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetStreamMode@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetStreamMode@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetStreamMode (ID = 0x00000035)

// @START@ Response handler for method SBAND_TMTC::GetTargetPower (ID = 0x00000036)
static void SBAND_TMTC_GetTargetPowerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetTargetPowerResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetTargetPower@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetTargetPower@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetTargetPower@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetTargetPower@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetTargetPower (ID = 0x00000036)

// @START@ Response handler for method SBAND_TMTC::SetTargetPower (ID = 0x00000037)
static void SBAND_TMTC_SetTargetPowerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetTargetPowerResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetTargetPower@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetTargetPower@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetTargetPower@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetTargetPower@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetTargetPower (ID = 0x00000037)

// @START@ Response handler for method SBAND_TMTC::GetPacketScrambler (ID = 0x00000038)
static void SBAND_TMTC_GetPacketScramblerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCGetPacketScramblerResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::GetPacketScrambler@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::GetPacketScrambler@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::GetPacketScrambler@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::GetPacketScrambler@
    }
}
// @END@ Response handler for method SBAND_TMTC::GetPacketScrambler (ID = 0x00000038)

// @START@ Response handler for method SBAND_TMTC::SetPacketScrambler (ID = 0x00000039)
static void SBAND_TMTC_SetPacketScramblerResponseHandlerImpl(RespContext_t* pRespCtx,
            const SBAND_TMTCSetPacketScramblerResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@SBAND_TMTC::SetPacketScrambler@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@SBAND_TMTC::SetPacketScrambler@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@SBAND_TMTC::SetPacketScrambler@
        
        // TODO: Put your implementation to handle the
        // received server response here!
        
        // @USER_CODE_SECTION_END@SBAND_TMTC::SetPacketScrambler@
    }
}
// @END@ Response handler for method SBAND_TMTC::SetPacketScrambler (ID = 0x00000039)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void SBAND_TMTCClientAppInit(void)
{
    SBAND_TMTC_registerClientApi(&SBAND_TMTCClientApiCtx);
}
