/*!
********************************************************************************************
* @file FP_UHFClientApp.c
* @brief ClientApp implementation template generator
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

// @START_USER@ USER_INCLUDES

// @END_USER@ USER_INCLUDES

/**********************************************************************
 *
 *  Local methods declarations
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_DECL
// Place static function declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_FUNC_DECL

static void UHF_WriteSCWResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteSCWResponseData_t* pResponseData);

static void UHF_ReadSCWResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSCWResponseData_t* pResponseData);

static void UHF_WriteRfConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteRfConfigResponseData_t* pResponseData);

static void UHF_ReadRfConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadRfConfigResponseData_t* pResponseData);

static void UHF_ReadUpTimeResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadUpTimeResponseData_t* pResponseData);

static void UHF_ReadNumberOfTxPacketsResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadNumberOfTxPacketsResponseData_t* pResponseData);

static void UHF_ReadNumberOfRxPacketsResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadNumberOfRxPacketsResponseData_t* pResponseData);

static void UHF_ReadNumberOfRxPacketsCRCErrResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadNumberOfRxPacketsCRCErrResponseData_t* pResponseData);

static void UHF_WriteBeaconMessageTxPeriodCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteBeaconMessageTxPeriodCfgResponseData_t* pResponseData);

static void UHF_ReadBeaconMessageTxPeriodCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadBeaconMessageTxPeriodCfgResponseData_t* pResponseData);

static void UHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteBeaconMessageBetweeenTxPeriodConfigResponseData_t* pResponseData);

static void UHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadBeaconMessageBetweeenTxPeriodConfigResponseData_t* pResponseData);

static void UHF_RestoreDefaultConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFRestoreDefaultConfigResponseData_t* pResponseData);

static void UHF_WriteAntennaReleaseConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAntennaReleaseConfigResponseData_t* pResponseData);

static void UHF_ReadAntennaReleaseConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAntennaReleaseConfigResponseData_t* pResponseData);

static void UHF_WriteAntennaResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAntennaResponseData_t* pResponseData);

static void UHF_ReadAntennaResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAntennaResponseData_t* pResponseData);

static void UHF_EnterLPMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFEnterLPMResponseData_t* pResponseData);

static void UHF_ReadLPMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadLPMResponseData_t* pResponseData);

static void UHF_WriteDestCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteDestCallSignResponseData_t* pResponseData);

static void UHF_ReadDestCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadDestCallSignResponseData_t* pResponseData);

static void UHF_WriteSrcCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteSrcCallSignResponseData_t* pResponseData);

static void UHF_ReadSRCCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSRCCallSignResponseData_t* pResponseData);

static void UHF_WriteMorseCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteMorseCallSignResponseData_t* pResponseData);

static void UHF_ReadMorseCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadMorseCallSignResponseData_t* pResponseData);

static void UHF_WriteMIDIAudioBeaconResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteMIDIAudioBeaconResponseData_t* pResponseData);

static void UHF_ReadMIDIAudioBeaconResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadMIDIAudioBeaconResponseData_t* pResponseData);

static void UHF_ReadSWVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSWVersionResponseData_t* pResponseData);

static void UHF_ReadPayloadSizeResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadPayloadSizeResponseData_t* pResponseData);

static void UHF_WriteBeaconMessageContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteBeaconMessageContentCfgResponseData_t* pResponseData);

static void UHF_ReadBeaconMessageContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadBeaconMessageContentCfgResponseData_t* pResponseData);

static void UHF_WriteDeviceAddrConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteDeviceAddrConfigResponseData_t* pResponseData);

static void UHF_WriteFRAMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteFRAMResponseData_t* pResponseData);

static void UHF_ReadFRAMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadFRAMResponseData_t* pResponseData);

static void UHF_WriteTransPropertyResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteTransPropertyResponseData_t* pResponseData);

static void UHF_ReadTransPropertyResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadTransPropertyResponseData_t* pResponseData);

static void UHF_ReadTempResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadTempResponseData_t* pResponseData);

static void UHF_ReadRSSIResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadRSSIResponseData_t* pResponseData);

static void UHF_WriteRadioRawDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteRadioRawDataResponseData_t* pResponseData);

static void UHF_PingResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFPingResponseData_t* pResponseData);

static void UHF_ExBeaconSetSendResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFExBeaconSetSendResponseData_t* pResponseData);

static void UHF_WriteI2cConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteI2cConfigResponseData_t* pResponseData);

static void UHF_ReadI2cConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadI2cConfigResponseData_t* pResponseData);

static void UHF_WriteAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAntennaCfgResponseData_t* pResponseData);

static void UHF_ReadAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAntennaCfgResponseData_t* pResponseData);

static void UHF_WriteEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteEpsCfgResponseData_t* pResponseData);

static void UHF_ReadEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadEpsCfgResponseData_t* pResponseData);

static void UHF_WriteEpsConOpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteEpsConOpsCfgResponseData_t* pResponseData);

static void UHF_ReadEpsConOpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadEpsConOpsCfgResponseData_t* pResponseData);

static void UHF_WriteRs485ConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteRs485ConfigResponseData_t* pResponseData);

static void UHF_ReadRs485ConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadRs485ConfigResponseData_t* pResponseData);

static void UHF_WriteOBCConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteOBCConfigResponseData_t* pResponseData);

static void UHF_ReadOBCConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadOBCConfigResponseData_t* pResponseData);

static void UHF_WriteSatConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteSatConfigResponseData_t* pResponseData);

static void UHF_ReadSatConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSatConfigResponseData_t* pResponseData);

static void UHF_ReadEpsCfgOutResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadEpsCfgOutResponseData_t* pResponseData);

static void UHF_WriteEpsCfgOutResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteEpsCfgOutResponseData_t* pResponseData);

static void UHF_Write2UAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWrite2UAntennaCfgResponseData_t* pResponseData);

static void UHF_Read2UAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFRead2UAntennaCfgResponseData_t* pResponseData);

static void UHF_WriteAutomatedBeaconCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAutomatedBeaconCfgResponseData_t* pResponseData);

static void UHF_ReadAutomatedBeaconCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAutomatedBeaconCfgResponseData_t* pResponseData);

static void UHF_WriteOutputPowerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteOutputPowerCfgResponseData_t* pResponseData);

static void UHF_ReadOutputPowerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadOutputPowerCfgResponseData_t* pResponseData);

static void UHF_ReadCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadCountersResponseData_t* pResponseData);

static void UHF_WriteCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteCipherKeySlotResponseData_t* pResponseData);

static void UHF_ReadCipherKeySlotStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadCipherKeySlotStatusResponseData_t* pResponseData);

static void UHF_EraseCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFEraseCipherKeySlotResponseData_t* pResponseData);


/**********************************************************************
 *
 *  Local variables
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_VARS_DECL
// Place static variable declarations here to preserve them during merge!!!
// @END_USER@ USER_LOCAL_VARS_DECL

static UHF_ClientApi_t UHFClientApiCtx =
{
  .UHF_WriteSCWResponseHandler = (pfUHF_WriteSCWResponseHandler_t) UHF_WriteSCWResponseHandlerImpl,
  .UHF_ReadSCWResponseHandler = (pfUHF_ReadSCWResponseHandler_t) UHF_ReadSCWResponseHandlerImpl,
  .UHF_WriteRfConfigResponseHandler = (pfUHF_WriteRfConfigResponseHandler_t) UHF_WriteRfConfigResponseHandlerImpl,
  .UHF_ReadRfConfigResponseHandler = (pfUHF_ReadRfConfigResponseHandler_t) UHF_ReadRfConfigResponseHandlerImpl,
  .UHF_ReadUpTimeResponseHandler = (pfUHF_ReadUpTimeResponseHandler_t) UHF_ReadUpTimeResponseHandlerImpl,
  .UHF_ReadNumberOfTxPacketsResponseHandler = (pfUHF_ReadNumberOfTxPacketsResponseHandler_t) UHF_ReadNumberOfTxPacketsResponseHandlerImpl,
  .UHF_ReadNumberOfRxPacketsResponseHandler = (pfUHF_ReadNumberOfRxPacketsResponseHandler_t) UHF_ReadNumberOfRxPacketsResponseHandlerImpl,
  .UHF_ReadNumberOfRxPacketsCRCErrResponseHandler = (pfUHF_ReadNumberOfRxPacketsCRCErrResponseHandler_t) UHF_ReadNumberOfRxPacketsCRCErrResponseHandlerImpl,
  .UHF_WriteBeaconMessageTxPeriodCfgResponseHandler = (pfUHF_WriteBeaconMessageTxPeriodCfgResponseHandler_t) UHF_WriteBeaconMessageTxPeriodCfgResponseHandlerImpl,
  .UHF_ReadBeaconMessageTxPeriodCfgResponseHandler = (pfUHF_ReadBeaconMessageTxPeriodCfgResponseHandler_t) UHF_ReadBeaconMessageTxPeriodCfgResponseHandlerImpl,
  .UHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandler = (pfUHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandler_t) UHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandlerImpl,
  .UHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandler = (pfUHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandler_t) UHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandlerImpl,
  .UHF_RestoreDefaultConfigResponseHandler = (pfUHF_RestoreDefaultConfigResponseHandler_t) UHF_RestoreDefaultConfigResponseHandlerImpl,
  .UHF_WriteAntennaReleaseConfigResponseHandler = (pfUHF_WriteAntennaReleaseConfigResponseHandler_t) UHF_WriteAntennaReleaseConfigResponseHandlerImpl,
  .UHF_ReadAntennaReleaseConfigResponseHandler = (pfUHF_ReadAntennaReleaseConfigResponseHandler_t) UHF_ReadAntennaReleaseConfigResponseHandlerImpl,
  .UHF_WriteAntennaResponseHandler = (pfUHF_WriteAntennaResponseHandler_t) UHF_WriteAntennaResponseHandlerImpl,
  .UHF_ReadAntennaResponseHandler = (pfUHF_ReadAntennaResponseHandler_t) UHF_ReadAntennaResponseHandlerImpl,
  .UHF_EnterLPMResponseHandler = (pfUHF_EnterLPMResponseHandler_t) UHF_EnterLPMResponseHandlerImpl,
  .UHF_ReadLPMResponseHandler = (pfUHF_ReadLPMResponseHandler_t) UHF_ReadLPMResponseHandlerImpl,
  .UHF_WriteDestCallSignResponseHandler = (pfUHF_WriteDestCallSignResponseHandler_t) UHF_WriteDestCallSignResponseHandlerImpl,
  .UHF_ReadDestCallSignResponseHandler = (pfUHF_ReadDestCallSignResponseHandler_t) UHF_ReadDestCallSignResponseHandlerImpl,
  .UHF_WriteSrcCallSignResponseHandler = (pfUHF_WriteSrcCallSignResponseHandler_t) UHF_WriteSrcCallSignResponseHandlerImpl,
  .UHF_ReadSRCCallSignResponseHandler = (pfUHF_ReadSRCCallSignResponseHandler_t) UHF_ReadSRCCallSignResponseHandlerImpl,
  .UHF_WriteMorseCallSignResponseHandler = (pfUHF_WriteMorseCallSignResponseHandler_t) UHF_WriteMorseCallSignResponseHandlerImpl,
  .UHF_ReadMorseCallSignResponseHandler = (pfUHF_ReadMorseCallSignResponseHandler_t) UHF_ReadMorseCallSignResponseHandlerImpl,
  .UHF_WriteMIDIAudioBeaconResponseHandler = (pfUHF_WriteMIDIAudioBeaconResponseHandler_t) UHF_WriteMIDIAudioBeaconResponseHandlerImpl,
  .UHF_ReadMIDIAudioBeaconResponseHandler = (pfUHF_ReadMIDIAudioBeaconResponseHandler_t) UHF_ReadMIDIAudioBeaconResponseHandlerImpl,
  .UHF_ReadSWVersionResponseHandler = (pfUHF_ReadSWVersionResponseHandler_t) UHF_ReadSWVersionResponseHandlerImpl,
  .UHF_ReadPayloadSizeResponseHandler = (pfUHF_ReadPayloadSizeResponseHandler_t) UHF_ReadPayloadSizeResponseHandlerImpl,
  .UHF_WriteBeaconMessageContentCfgResponseHandler = (pfUHF_WriteBeaconMessageContentCfgResponseHandler_t) UHF_WriteBeaconMessageContentCfgResponseHandlerImpl,
  .UHF_ReadBeaconMessageContentCfgResponseHandler = (pfUHF_ReadBeaconMessageContentCfgResponseHandler_t) UHF_ReadBeaconMessageContentCfgResponseHandlerImpl,
  .UHF_WriteDeviceAddrConfigResponseHandler = (pfUHF_WriteDeviceAddrConfigResponseHandler_t) UHF_WriteDeviceAddrConfigResponseHandlerImpl,
  .UHF_WriteFRAMResponseHandler = (pfUHF_WriteFRAMResponseHandler_t) UHF_WriteFRAMResponseHandlerImpl,
  .UHF_ReadFRAMResponseHandler = (pfUHF_ReadFRAMResponseHandler_t) UHF_ReadFRAMResponseHandlerImpl,
  .UHF_WriteTransPropertyResponseHandler = (pfUHF_WriteTransPropertyResponseHandler_t) UHF_WriteTransPropertyResponseHandlerImpl,
  .UHF_ReadTransPropertyResponseHandler = (pfUHF_ReadTransPropertyResponseHandler_t) UHF_ReadTransPropertyResponseHandlerImpl,
  .UHF_ReadTempResponseHandler = (pfUHF_ReadTempResponseHandler_t) UHF_ReadTempResponseHandlerImpl,
  .UHF_ReadRSSIResponseHandler = (pfUHF_ReadRSSIResponseHandler_t) UHF_ReadRSSIResponseHandlerImpl,
  .UHF_WriteRadioRawDataResponseHandler = (pfUHF_WriteRadioRawDataResponseHandler_t) UHF_WriteRadioRawDataResponseHandlerImpl,
  .UHF_PingResponseHandler = (pfUHF_PingResponseHandler_t) UHF_PingResponseHandlerImpl,
  .UHF_ExBeaconSetSendResponseHandler = (pfUHF_ExBeaconSetSendResponseHandler_t) UHF_ExBeaconSetSendResponseHandlerImpl,
  .UHF_WriteI2cConfigResponseHandler = (pfUHF_WriteI2cConfigResponseHandler_t) UHF_WriteI2cConfigResponseHandlerImpl,
  .UHF_ReadI2cConfigResponseHandler = (pfUHF_ReadI2cConfigResponseHandler_t) UHF_ReadI2cConfigResponseHandlerImpl,
  .UHF_WriteAntennaCfgResponseHandler = (pfUHF_WriteAntennaCfgResponseHandler_t) UHF_WriteAntennaCfgResponseHandlerImpl,
  .UHF_ReadAntennaCfgResponseHandler = (pfUHF_ReadAntennaCfgResponseHandler_t) UHF_ReadAntennaCfgResponseHandlerImpl,
  .UHF_WriteEpsCfgResponseHandler = (pfUHF_WriteEpsCfgResponseHandler_t) UHF_WriteEpsCfgResponseHandlerImpl,
  .UHF_ReadEpsCfgResponseHandler = (pfUHF_ReadEpsCfgResponseHandler_t) UHF_ReadEpsCfgResponseHandlerImpl,
  .UHF_WriteEpsConOpsCfgResponseHandler = (pfUHF_WriteEpsConOpsCfgResponseHandler_t) UHF_WriteEpsConOpsCfgResponseHandlerImpl,
  .UHF_ReadEpsConOpsCfgResponseHandler = (pfUHF_ReadEpsConOpsCfgResponseHandler_t) UHF_ReadEpsConOpsCfgResponseHandlerImpl,
  .UHF_WriteRs485ConfigResponseHandler = (pfUHF_WriteRs485ConfigResponseHandler_t) UHF_WriteRs485ConfigResponseHandlerImpl,
  .UHF_ReadRs485ConfigResponseHandler = (pfUHF_ReadRs485ConfigResponseHandler_t) UHF_ReadRs485ConfigResponseHandlerImpl,
  .UHF_WriteOBCConfigResponseHandler = (pfUHF_WriteOBCConfigResponseHandler_t) UHF_WriteOBCConfigResponseHandlerImpl,
  .UHF_ReadOBCConfigResponseHandler = (pfUHF_ReadOBCConfigResponseHandler_t) UHF_ReadOBCConfigResponseHandlerImpl,
  .UHF_WriteSatConfigResponseHandler = (pfUHF_WriteSatConfigResponseHandler_t) UHF_WriteSatConfigResponseHandlerImpl,
  .UHF_ReadSatConfigResponseHandler = (pfUHF_ReadSatConfigResponseHandler_t) UHF_ReadSatConfigResponseHandlerImpl,
  .UHF_ReadEpsCfgOutResponseHandler = (pfUHF_ReadEpsCfgOutResponseHandler_t) UHF_ReadEpsCfgOutResponseHandlerImpl,
  .UHF_WriteEpsCfgOutResponseHandler = (pfUHF_WriteEpsCfgOutResponseHandler_t) UHF_WriteEpsCfgOutResponseHandlerImpl,
  .UHF_Write2UAntennaCfgResponseHandler = (pfUHF_Write2UAntennaCfgResponseHandler_t) UHF_Write2UAntennaCfgResponseHandlerImpl,
  .UHF_Read2UAntennaCfgResponseHandler = (pfUHF_Read2UAntennaCfgResponseHandler_t) UHF_Read2UAntennaCfgResponseHandlerImpl,
  .UHF_WriteAutomatedBeaconCfgResponseHandler = (pfUHF_WriteAutomatedBeaconCfgResponseHandler_t) UHF_WriteAutomatedBeaconCfgResponseHandlerImpl,
  .UHF_ReadAutomatedBeaconCfgResponseHandler = (pfUHF_ReadAutomatedBeaconCfgResponseHandler_t) UHF_ReadAutomatedBeaconCfgResponseHandlerImpl,
  .UHF_WriteOutputPowerCfgResponseHandler = (pfUHF_WriteOutputPowerCfgResponseHandler_t) UHF_WriteOutputPowerCfgResponseHandlerImpl,
  .UHF_ReadOutputPowerCfgResponseHandler = (pfUHF_ReadOutputPowerCfgResponseHandler_t) UHF_ReadOutputPowerCfgResponseHandlerImpl,
  .UHF_ReadCountersResponseHandler = (pfUHF_ReadCountersResponseHandler_t) UHF_ReadCountersResponseHandlerImpl,
  .UHF_WriteCipherKeySlotResponseHandler = (pfUHF_WriteCipherKeySlotResponseHandler_t) UHF_WriteCipherKeySlotResponseHandlerImpl,
  .UHF_ReadCipherKeySlotStatusResponseHandler = (pfUHF_ReadCipherKeySlotStatusResponseHandler_t) UHF_ReadCipherKeySlotStatusResponseHandlerImpl,
  .UHF_EraseCipherKeySlotResponseHandler = (pfUHF_EraseCipherKeySlotResponseHandler_t) UHF_EraseCipherKeySlotResponseHandlerImpl,
};

/**********************************************************************
 *
 *  Local methods implementation
 *
 **********************************************************************/
// @START_USER@ USER_LOCAL_FUNC_IMPL
// Place static functions implementation here to preserve it during merge!!!
// @END_USER@ USER_LOCAL_FUNC_IMPL

// @START@ Response handler for method UHF::WriteSCW (ID = 0x00000001)
static void UHF_WriteSCWResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteSCWResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteSCW@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteSCW@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteSCW@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteSCW@
    }
}
// @END@ Response handler for method UHF::WriteSCW (ID = 0x00000001)

// @START@ Response handler for method UHF::ReadSCW (ID = 0x00000002)
static void UHF_ReadSCWResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSCWResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadSCW@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadSCW@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadSCW@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadSCW@
    }
}
// @END@ Response handler for method UHF::ReadSCW (ID = 0x00000002)

// @START@ Response handler for method UHF::WriteRfConfig (ID = 0x00000003)
static void UHF_WriteRfConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteRfConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteRfConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteRfConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteRfConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteRfConfig@
    }
}
// @END@ Response handler for method UHF::WriteRfConfig (ID = 0x00000003)

// @START@ Response handler for method UHF::ReadRfConfig (ID = 0x00000004)
static void UHF_ReadRfConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadRfConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadRfConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadRfConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadRfConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadRfConfig@
    }
}
// @END@ Response handler for method UHF::ReadRfConfig (ID = 0x00000004)

// @START@ Response handler for method UHF::ReadUpTime (ID = 0x00000005)
static void UHF_ReadUpTimeResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadUpTimeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadUpTime@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadUpTime@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadUpTime@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadUpTime@
    }
}
// @END@ Response handler for method UHF::ReadUpTime (ID = 0x00000005)

// @START@ Response handler for method UHF::ReadNumberOfTxPackets (ID = 0x00000006)
static void UHF_ReadNumberOfTxPacketsResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadNumberOfTxPacketsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadNumberOfTxPackets@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadNumberOfTxPackets@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadNumberOfTxPackets@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadNumberOfTxPackets@
    }
}
// @END@ Response handler for method UHF::ReadNumberOfTxPackets (ID = 0x00000006)

// @START@ Response handler for method UHF::ReadNumberOfRxPackets (ID = 0x00000007)
static void UHF_ReadNumberOfRxPacketsResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadNumberOfRxPacketsResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadNumberOfRxPackets@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadNumberOfRxPackets@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadNumberOfRxPackets@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadNumberOfRxPackets@
    }
}
// @END@ Response handler for method UHF::ReadNumberOfRxPackets (ID = 0x00000007)

// @START@ Response handler for method UHF::ReadNumberOfRxPacketsCRCErr (ID = 0x00000008)
static void UHF_ReadNumberOfRxPacketsCRCErrResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadNumberOfRxPacketsCRCErrResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadNumberOfRxPacketsCRCErr@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadNumberOfRxPacketsCRCErr@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadNumberOfRxPacketsCRCErr@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadNumberOfRxPacketsCRCErr@
    }
}
// @END@ Response handler for method UHF::ReadNumberOfRxPacketsCRCErr (ID = 0x00000008)

// @START@ Response handler for method UHF::WriteBeaconMessageTxPeriodCfg (ID = 0x00000009)
static void UHF_WriteBeaconMessageTxPeriodCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteBeaconMessageTxPeriodCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteBeaconMessageTxPeriodCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteBeaconMessageTxPeriodCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteBeaconMessageTxPeriodCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteBeaconMessageTxPeriodCfg@
    }
}
// @END@ Response handler for method UHF::WriteBeaconMessageTxPeriodCfg (ID = 0x00000009)

// @START@ Response handler for method UHF::ReadBeaconMessageTxPeriodCfg (ID = 0x0000000A)
static void UHF_ReadBeaconMessageTxPeriodCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadBeaconMessageTxPeriodCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadBeaconMessageTxPeriodCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadBeaconMessageTxPeriodCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadBeaconMessageTxPeriodCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadBeaconMessageTxPeriodCfg@
    }
}
// @END@ Response handler for method UHF::ReadBeaconMessageTxPeriodCfg (ID = 0x0000000A)

// @START@ Response handler for method UHF::WriteBeaconMessageBetweeenTxPeriodConfig (ID = 0x0000000B)
static void UHF_WriteBeaconMessageBetweeenTxPeriodConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteBeaconMessageBetweeenTxPeriodConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteBeaconMessageBetweeenTxPeriodConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteBeaconMessageBetweeenTxPeriodConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteBeaconMessageBetweeenTxPeriodConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteBeaconMessageBetweeenTxPeriodConfig@
    }
}
// @END@ Response handler for method UHF::WriteBeaconMessageBetweeenTxPeriodConfig (ID = 0x0000000B)

// @START@ Response handler for method UHF::ReadBeaconMessageBetweeenTxPeriodConfig (ID = 0x0000000C)
static void UHF_ReadBeaconMessageBetweeenTxPeriodConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadBeaconMessageBetweeenTxPeriodConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadBeaconMessageBetweeenTxPeriodConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadBeaconMessageBetweeenTxPeriodConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadBeaconMessageBetweeenTxPeriodConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadBeaconMessageBetweeenTxPeriodConfig@
    }
}
// @END@ Response handler for method UHF::ReadBeaconMessageBetweeenTxPeriodConfig (ID = 0x0000000C)

// @START@ Response handler for method UHF::RestoreDefaultConfig (ID = 0x0000000D)
static void UHF_RestoreDefaultConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFRestoreDefaultConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::RestoreDefaultConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::RestoreDefaultConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::RestoreDefaultConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::RestoreDefaultConfig@
    }
}
// @END@ Response handler for method UHF::RestoreDefaultConfig (ID = 0x0000000D)

// @START@ Response handler for method UHF::WriteAntennaReleaseConfig (ID = 0x0000000E)
static void UHF_WriteAntennaReleaseConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAntennaReleaseConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteAntennaReleaseConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteAntennaReleaseConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteAntennaReleaseConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteAntennaReleaseConfig@
    }
}
// @END@ Response handler for method UHF::WriteAntennaReleaseConfig (ID = 0x0000000E)

// @START@ Response handler for method UHF::ReadAntennaReleaseConfig (ID = 0x0000000F)
static void UHF_ReadAntennaReleaseConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAntennaReleaseConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadAntennaReleaseConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadAntennaReleaseConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadAntennaReleaseConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadAntennaReleaseConfig@
    }
}
// @END@ Response handler for method UHF::ReadAntennaReleaseConfig (ID = 0x0000000F)

// @START@ Response handler for method UHF::WriteAntenna (ID = 0x00000010)
static void UHF_WriteAntennaResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAntennaResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteAntenna@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteAntenna@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteAntenna@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteAntenna@
    }
}
// @END@ Response handler for method UHF::WriteAntenna (ID = 0x00000010)

// @START@ Response handler for method UHF::ReadAntenna (ID = 0x00000011)
static void UHF_ReadAntennaResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAntennaResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadAntenna@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadAntenna@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadAntenna@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadAntenna@
    }
}
// @END@ Response handler for method UHF::ReadAntenna (ID = 0x00000011)

// @START@ Response handler for method UHF::EnterLPM (ID = 0x00000012)
static void UHF_EnterLPMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFEnterLPMResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::EnterLPM@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::EnterLPM@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::EnterLPM@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::EnterLPM@
    }
}
// @END@ Response handler for method UHF::EnterLPM (ID = 0x00000012)

// @START@ Response handler for method UHF::ReadLPM (ID = 0x00000013)
static void UHF_ReadLPMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadLPMResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadLPM@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadLPM@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadLPM@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadLPM@
    }
}
// @END@ Response handler for method UHF::ReadLPM (ID = 0x00000013)

// @START@ Response handler for method UHF::WriteDestCallSign (ID = 0x00000014)
static void UHF_WriteDestCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteDestCallSignResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteDestCallSign@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteDestCallSign@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteDestCallSign@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteDestCallSign@
    }
}
// @END@ Response handler for method UHF::WriteDestCallSign (ID = 0x00000014)

// @START@ Response handler for method UHF::ReadDestCallSign (ID = 0x00000015)
static void UHF_ReadDestCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadDestCallSignResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadDestCallSign@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadDestCallSign@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadDestCallSign@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadDestCallSign@
    }
}
// @END@ Response handler for method UHF::ReadDestCallSign (ID = 0x00000015)

// @START@ Response handler for method UHF::WriteSrcCallSign (ID = 0x00000016)
static void UHF_WriteSrcCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteSrcCallSignResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteSrcCallSign@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteSrcCallSign@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteSrcCallSign@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteSrcCallSign@
    }
}
// @END@ Response handler for method UHF::WriteSrcCallSign (ID = 0x00000016)

// @START@ Response handler for method UHF::ReadSRCCallSign (ID = 0x00000017)
static void UHF_ReadSRCCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSRCCallSignResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadSRCCallSign@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadSRCCallSign@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadSRCCallSign@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadSRCCallSign@
    }
}
// @END@ Response handler for method UHF::ReadSRCCallSign (ID = 0x00000017)

// @START@ Response handler for method UHF::WriteMorseCallSign (ID = 0x00000018)
static void UHF_WriteMorseCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteMorseCallSignResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteMorseCallSign@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteMorseCallSign@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteMorseCallSign@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteMorseCallSign@
    }
}
// @END@ Response handler for method UHF::WriteMorseCallSign (ID = 0x00000018)

// @START@ Response handler for method UHF::ReadMorseCallSign (ID = 0x00000019)
static void UHF_ReadMorseCallSignResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadMorseCallSignResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadMorseCallSign@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadMorseCallSign@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadMorseCallSign@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadMorseCallSign@
    }
}
// @END@ Response handler for method UHF::ReadMorseCallSign (ID = 0x00000019)

// @START@ Response handler for method UHF::WriteMIDIAudioBeacon (ID = 0x0000001A)
static void UHF_WriteMIDIAudioBeaconResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteMIDIAudioBeaconResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteMIDIAudioBeacon@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteMIDIAudioBeacon@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteMIDIAudioBeacon@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteMIDIAudioBeacon@
    }
}
// @END@ Response handler for method UHF::WriteMIDIAudioBeacon (ID = 0x0000001A)

// @START@ Response handler for method UHF::ReadMIDIAudioBeacon (ID = 0x0000001B)
static void UHF_ReadMIDIAudioBeaconResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadMIDIAudioBeaconResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadMIDIAudioBeacon@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadMIDIAudioBeacon@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadMIDIAudioBeacon@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadMIDIAudioBeacon@
    }
}
// @END@ Response handler for method UHF::ReadMIDIAudioBeacon (ID = 0x0000001B)

// @START@ Response handler for method UHF::ReadSWVersion (ID = 0x0000001C)
static void UHF_ReadSWVersionResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSWVersionResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadSWVersion@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadSWVersion@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadSWVersion@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadSWVersion@
    }
}
// @END@ Response handler for method UHF::ReadSWVersion (ID = 0x0000001C)

// @START@ Response handler for method UHF::ReadPayloadSize (ID = 0x0000001D)
static void UHF_ReadPayloadSizeResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadPayloadSizeResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadPayloadSize@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadPayloadSize@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadPayloadSize@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadPayloadSize@
    }
}
// @END@ Response handler for method UHF::ReadPayloadSize (ID = 0x0000001D)

// @START@ Response handler for method UHF::WriteBeaconMessageContentCfg (ID = 0x0000001E)
static void UHF_WriteBeaconMessageContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteBeaconMessageContentCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteBeaconMessageContentCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteBeaconMessageContentCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteBeaconMessageContentCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteBeaconMessageContentCfg@
    }
}
// @END@ Response handler for method UHF::WriteBeaconMessageContentCfg (ID = 0x0000001E)

// @START@ Response handler for method UHF::ReadBeaconMessageContentCfg (ID = 0x0000001F)
static void UHF_ReadBeaconMessageContentCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadBeaconMessageContentCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadBeaconMessageContentCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadBeaconMessageContentCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadBeaconMessageContentCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadBeaconMessageContentCfg@
    }
}
// @END@ Response handler for method UHF::ReadBeaconMessageContentCfg (ID = 0x0000001F)

// @START@ Response handler for method UHF::WriteDeviceAddrConfig (ID = 0x00000020)
static void UHF_WriteDeviceAddrConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteDeviceAddrConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteDeviceAddrConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteDeviceAddrConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteDeviceAddrConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteDeviceAddrConfig@
    }
}
// @END@ Response handler for method UHF::WriteDeviceAddrConfig (ID = 0x00000020)

// @START@ Response handler for method UHF::WriteFRAM (ID = 0x00000021)
static void UHF_WriteFRAMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteFRAMResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteFRAM@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteFRAM@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteFRAM@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteFRAM@
    }
}
// @END@ Response handler for method UHF::WriteFRAM (ID = 0x00000021)

// @START@ Response handler for method UHF::ReadFRAM (ID = 0x00000022)
static void UHF_ReadFRAMResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadFRAMResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadFRAM@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadFRAM@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadFRAM@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadFRAM@
    }
}
// @END@ Response handler for method UHF::ReadFRAM (ID = 0x00000022)

// @START@ Response handler for method UHF::WriteTransProperty (ID = 0x00000023)
static void UHF_WriteTransPropertyResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteTransPropertyResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteTransProperty@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteTransProperty@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteTransProperty@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteTransProperty@
    }
}
// @END@ Response handler for method UHF::WriteTransProperty (ID = 0x00000023)

// @START@ Response handler for method UHF::ReadTransProperty (ID = 0x00000024)
static void UHF_ReadTransPropertyResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadTransPropertyResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadTransProperty@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadTransProperty@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadTransProperty@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadTransProperty@
    }
}
// @END@ Response handler for method UHF::ReadTransProperty (ID = 0x00000024)

// @START@ Response handler for method UHF::ReadTemp (ID = 0x00000025)
static void UHF_ReadTempResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadTempResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadTemp@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadTemp@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadTemp@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadTemp@
    }
}
// @END@ Response handler for method UHF::ReadTemp (ID = 0x00000025)

// @START@ Response handler for method UHF::ReadRSSI (ID = 0x00000026)
static void UHF_ReadRSSIResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadRSSIResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadRSSI@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadRSSI@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadRSSI@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadRSSI@
    }
}
// @END@ Response handler for method UHF::ReadRSSI (ID = 0x00000026)

// @START@ Response handler for method UHF::WriteRadioRawData (ID = 0x00000027)
static void UHF_WriteRadioRawDataResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteRadioRawDataResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteRadioRawData@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteRadioRawData@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteRadioRawData@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteRadioRawData@
    }
}
// @END@ Response handler for method UHF::WriteRadioRawData (ID = 0x00000027)

// @START@ Response handler for method UHF::Ping (ID = 0x00000028)
static void UHF_PingResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFPingResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::Ping@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::Ping@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::Ping@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::Ping@
    }
}
// @END@ Response handler for method UHF::Ping (ID = 0x00000028)

// @START@ Response handler for method UHF::ExBeaconSetSend (ID = 0x00000029)
static void UHF_ExBeaconSetSendResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFExBeaconSetSendResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ExBeaconSetSend@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ExBeaconSetSend@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ExBeaconSetSend@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ExBeaconSetSend@
    }
}
// @END@ Response handler for method UHF::ExBeaconSetSend (ID = 0x00000029)

// @START@ Response handler for method UHF::WriteI2cConfig (ID = 0x0000002A)
static void UHF_WriteI2cConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteI2cConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteI2cConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteI2cConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteI2cConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteI2cConfig@
    }
}
// @END@ Response handler for method UHF::WriteI2cConfig (ID = 0x0000002A)

// @START@ Response handler for method UHF::ReadI2cConfig (ID = 0x0000002B)
static void UHF_ReadI2cConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadI2cConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadI2cConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadI2cConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadI2cConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadI2cConfig@
    }
}
// @END@ Response handler for method UHF::ReadI2cConfig (ID = 0x0000002B)

// @START@ Response handler for method UHF::WriteAntennaCfg (ID = 0x0000002C)
static void UHF_WriteAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAntennaCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteAntennaCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteAntennaCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteAntennaCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteAntennaCfg@
    }
}
// @END@ Response handler for method UHF::WriteAntennaCfg (ID = 0x0000002C)

// @START@ Response handler for method UHF::ReadAntennaCfg (ID = 0x0000002D)
static void UHF_ReadAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAntennaCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadAntennaCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadAntennaCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadAntennaCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadAntennaCfg@
    }
}
// @END@ Response handler for method UHF::ReadAntennaCfg (ID = 0x0000002D)

// @START@ Response handler for method UHF::WriteEpsCfg (ID = 0x0000002E)
static void UHF_WriteEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteEpsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteEpsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteEpsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteEpsCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteEpsCfg@
    }
}
// @END@ Response handler for method UHF::WriteEpsCfg (ID = 0x0000002E)

// @START@ Response handler for method UHF::ReadEpsCfg (ID = 0x0000002F)
static void UHF_ReadEpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadEpsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadEpsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadEpsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadEpsCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadEpsCfg@
    }
}
// @END@ Response handler for method UHF::ReadEpsCfg (ID = 0x0000002F)

// @START@ Response handler for method UHF::WriteEpsConOpsCfg (ID = 0x00000030)
static void UHF_WriteEpsConOpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteEpsConOpsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteEpsConOpsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteEpsConOpsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteEpsConOpsCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteEpsConOpsCfg@
    }
}
// @END@ Response handler for method UHF::WriteEpsConOpsCfg (ID = 0x00000030)

// @START@ Response handler for method UHF::ReadEpsConOpsCfg (ID = 0x00000031)
static void UHF_ReadEpsConOpsCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadEpsConOpsCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadEpsConOpsCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadEpsConOpsCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadEpsConOpsCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadEpsConOpsCfg@
    }
}
// @END@ Response handler for method UHF::ReadEpsConOpsCfg (ID = 0x00000031)

// @START@ Response handler for method UHF::WriteRs485Config (ID = 0x00000032)
static void UHF_WriteRs485ConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteRs485ConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteRs485Config@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteRs485Config@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteRs485Config@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteRs485Config@
    }
}
// @END@ Response handler for method UHF::WriteRs485Config (ID = 0x00000032)

// @START@ Response handler for method UHF::ReadRs485Config (ID = 0x00000033)
static void UHF_ReadRs485ConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadRs485ConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadRs485Config@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadRs485Config@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadRs485Config@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadRs485Config@
    }
}
// @END@ Response handler for method UHF::ReadRs485Config (ID = 0x00000033)

// @START@ Response handler for method UHF::WriteOBCConfig (ID = 0x00000034)
static void UHF_WriteOBCConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteOBCConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteOBCConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteOBCConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteOBCConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteOBCConfig@
    }
}
// @END@ Response handler for method UHF::WriteOBCConfig (ID = 0x00000034)

// @START@ Response handler for method UHF::ReadOBCConfig (ID = 0x00000035)
static void UHF_ReadOBCConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadOBCConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadOBCConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadOBCConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadOBCConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadOBCConfig@
    }
}
// @END@ Response handler for method UHF::ReadOBCConfig (ID = 0x00000035)

// @START@ Response handler for method UHF::WriteSatConfig (ID = 0x00000036)
static void UHF_WriteSatConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteSatConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteSatConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteSatConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteSatConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteSatConfig@
    }
}
// @END@ Response handler for method UHF::WriteSatConfig (ID = 0x00000036)

// @START@ Response handler for method UHF::ReadSatConfig (ID = 0x00000037)
static void UHF_ReadSatConfigResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadSatConfigResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadSatConfig@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadSatConfig@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadSatConfig@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadSatConfig@
    }
}
// @END@ Response handler for method UHF::ReadSatConfig (ID = 0x00000037)

// @START@ Response handler for method UHF::ReadEpsCfgOut (ID = 0x00000038)
static void UHF_ReadEpsCfgOutResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadEpsCfgOutResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadEpsCfgOut@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadEpsCfgOut@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadEpsCfgOut@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadEpsCfgOut@
    }
}
// @END@ Response handler for method UHF::ReadEpsCfgOut (ID = 0x00000038)

// @START@ Response handler for method UHF::WriteEpsCfgOut (ID = 0x00000039)
static void UHF_WriteEpsCfgOutResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteEpsCfgOutResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteEpsCfgOut@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteEpsCfgOut@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteEpsCfgOut@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteEpsCfgOut@
    }
}
// @END@ Response handler for method UHF::WriteEpsCfgOut (ID = 0x00000039)

// @START@ Response handler for method UHF::Write2UAntennaCfg (ID = 0x0000003A)
static void UHF_Write2UAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWrite2UAntennaCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::Write2UAntennaCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::Write2UAntennaCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::Write2UAntennaCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::Write2UAntennaCfg@
    }
}
// @END@ Response handler for method UHF::Write2UAntennaCfg (ID = 0x0000003A)

// @START@ Response handler for method UHF::Read2UAntennaCfg (ID = 0x0000003B)
static void UHF_Read2UAntennaCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFRead2UAntennaCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::Read2UAntennaCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::Read2UAntennaCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::Read2UAntennaCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::Read2UAntennaCfg@
    }
}
// @END@ Response handler for method UHF::Read2UAntennaCfg (ID = 0x0000003B)

// @START@ Response handler for method UHF::WriteAutomatedBeaconCfg (ID = 0x0000003C)
static void UHF_WriteAutomatedBeaconCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteAutomatedBeaconCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteAutomatedBeaconCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteAutomatedBeaconCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteAutomatedBeaconCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteAutomatedBeaconCfg@
    }
}
// @END@ Response handler for method UHF::WriteAutomatedBeaconCfg (ID = 0x0000003C)

// @START@ Response handler for method UHF::ReadAutomatedBeaconCfg (ID = 0x0000003D)
static void UHF_ReadAutomatedBeaconCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadAutomatedBeaconCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadAutomatedBeaconCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadAutomatedBeaconCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadAutomatedBeaconCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadAutomatedBeaconCfg@
    }
}
// @END@ Response handler for method UHF::ReadAutomatedBeaconCfg (ID = 0x0000003D)

// @START@ Response handler for method UHF::WriteOutputPowerCfg (ID = 0x0000003E)
static void UHF_WriteOutputPowerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteOutputPowerCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteOutputPowerCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteOutputPowerCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteOutputPowerCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteOutputPowerCfg@
    }
}
// @END@ Response handler for method UHF::WriteOutputPowerCfg (ID = 0x0000003E)

// @START@ Response handler for method UHF::ReadOutputPowerCfg (ID = 0x0000003F)
static void UHF_ReadOutputPowerCfgResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadOutputPowerCfgResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadOutputPowerCfg@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadOutputPowerCfg@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadOutputPowerCfg@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadOutputPowerCfg@
    }
}
// @END@ Response handler for method UHF::ReadOutputPowerCfg (ID = 0x0000003F)

// @START@ Response handler for method UHF::ReadCounters (ID = 0x00000040)
static void UHF_ReadCountersResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadCountersResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadCounters@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadCounters@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadCounters@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadCounters@
    }
}
// @END@ Response handler for method UHF::ReadCounters (ID = 0x00000040)

// @START@ Response handler for method UHF::WriteCipherKeySlot (ID = 0x00000041)
static void UHF_WriteCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFWriteCipherKeySlotResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::WriteCipherKeySlot@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::WriteCipherKeySlot@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::WriteCipherKeySlot@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::WriteCipherKeySlot@
    }
}
// @END@ Response handler for method UHF::WriteCipherKeySlot (ID = 0x00000041)

// @START@ Response handler for method UHF::ReadCipherKeySlotStatus (ID = 0x00000042)
static void UHF_ReadCipherKeySlotStatusResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFReadCipherKeySlotStatusResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::ReadCipherKeySlotStatus@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::ReadCipherKeySlotStatus@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::ReadCipherKeySlotStatus@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::ReadCipherKeySlotStatus@
    }
}
// @END@ Response handler for method UHF::ReadCipherKeySlotStatus (ID = 0x00000042)

// @START@ Response handler for method UHF::EraseCipherKeySlot (ID = 0x00000043)
static void UHF_EraseCipherKeySlotResponseHandlerImpl(RespContext_t* pRespCtx,
            const UHFEraseCipherKeySlotResponseData_t* pResponseData)
{
    // @USER_VAR_SECTION_START@UHF::EraseCipherKeySlot@
    // Put your local variables in this section to preserve during merge!
    // @USER_VAR_SECTION_END@UHF::EraseCipherKeySlot@

    if ((pRespCtx != NULL) && (pResponseData != NULL))
    {
        // @USER_CODE_SECTION_START@UHF::EraseCipherKeySlot@

        // TODO: Put your implementation to handle the
        // received server response here!

        // @USER_CODE_SECTION_END@UHF::EraseCipherKeySlot@
    }
}
// @END@ Response handler for method UHF::EraseCipherKeySlot (ID = 0x00000043)


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
void UHFClientAppInit(void)
{
    UHF_registerClientApi(&UHFClientApiCtx);
}
