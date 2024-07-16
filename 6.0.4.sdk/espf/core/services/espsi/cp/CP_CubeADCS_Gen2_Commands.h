/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CP_CUBEADCS_GEN2_COMMANDS_H_
#define CP_CUBEADCS_GEN2_COMMANDS_H_
/**
 * @addtogroup cp
 * @{
 *
 * @file    CP_CubeADCS_Gen2_Commands.h
 * @brief   Declarations of Command Protocol commands for the Gen2 CubeADCS
 *
 * @}
 */

#include "CP_Handler.h"

/** @typedef sCubeAdcsGen2SrvCtx_t
 *  @brief Dispatch context data that is passed to the Gen2 service gateway API.
 */
typedef struct
{
    const uint8_t *pu8CmdData; /**< pointer to the command data payload */
    uint32_t u32CmdDataSize; /**< size of the command data payload buffer */
    uint8_t *pu8ResponseBuf; /**< response to the received command */
    uint32_t u32ResponseActualSize; /**< actual size of the payload written in pu8ResponseBuf */
} sCubeAdcsGen2SrvCtx_t;

/** @brief Dispatches a CP gateway command to the appropriate handler for a CubeADCS Gen2 API method call.
 *  @param psDispCtx Dispatch context for the CP gateway command.
 *
 *  @return Status of the dispatch operation.
*/
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_GwSendCmd(sCPDispatchContext_t * const psDispCtx);

// CUBE_ADCS_GEN_SECTION_START
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setUnixTime(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogIndex(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogEntry(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogClear(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setConfigPersist(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getIdentification(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getSerialNumber(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogIndex(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogEntry(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getUnixTime(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getConfigPersistDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getCommsStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getVersion(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getBootStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getTelecommandAcknowledge(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getCommonErrorCodes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_setTransferFrame(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_setFrame(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_getFrameInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_getFrame(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setHalt(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setDefaultAppTarget(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultApp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToApp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAddress(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetFileInfoIdx(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteFileSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setDeleteFileEntry(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteMemorySetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setReadMemorySetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setEraseMemorySetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setOptionBytes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setCommitOptionBytes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getIdentification(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getSerialNumber(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getErrors(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getFileInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getDefaultAppTarget(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getOptionBytes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getCommsStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getTelecommandAcknowledge(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigDefaultModes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMount(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag0OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag1OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsController(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsEstimator(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsSatellite(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitSatParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitTargetParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigNodeSelection(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMagSensingElement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAsgp4(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setEstMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOrbMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsRunMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsOpState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setSimSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandHxyzRW(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommands(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setStrTctlmInstance(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setFssTctlmInstance(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setDeployCommandMag(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setGnssSensorCmd(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setFileTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigDefaultModes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMount(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag0OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag1OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsController(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsEstimator(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsSatellite(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitSatParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitTargetParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigNodeSelection(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMagSensingElement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAsgp4(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getEstMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOrbMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsRunMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsOpState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getSimSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandHxyzRW(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommands(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHil(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExecutionPoint(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNodeInitState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawCss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawMag(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawGyro(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalFss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalCss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalMag(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGyro(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalHss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalStr(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGnss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmModels(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorBackup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainHighRes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmController(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmGnssRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExtSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmAcpExecution(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmTorquerCurrents(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeComputerHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeMagHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNssRwlHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPassThrough(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPowerState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setImageTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setImageFileInfoReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPortMap(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setEraseLogData(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setEventLogFilterTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setTelemetryLogTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setDummyEvent(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedEventSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedTlmSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPassThrough(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPowerState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPortDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPortMap(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getExpectedNodes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getImageTransferStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getImageFileInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getComponentErrorCodes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getEventLogStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedEventSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedTlmSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogInclusionMasks(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setConfiguration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setImageTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setDeadPixels(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setRequestDeadPixel(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementAndTrigger(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementMetadata(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getConfiguration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getProfileTiming(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getRequestedDeadPixel(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setSamplePrimary(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagTemp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCompact1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setSampleRed(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeploy(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployArm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagTemp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getDeploymentStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlActiveStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlWheelSpeedRef(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlTorque(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlMotorCurrent(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSoftwareReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlWheelSpeed(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmStandard(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmExtended(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmSystem(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sNumberNavigationStars(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sExposure(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sFourStarSearchThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSecondCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sTrackingModeThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sQuaternionFiltering(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSystemReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sActiveStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sImageFixedThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sDynamicMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sEdacOff(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sAttitude(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sHousekeeping(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_setPowerSwitchState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_getPowerSwitchState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamLensDistortion(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCaptureDetect(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setDetect(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setClearOvercurrentFlags(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setImageCapture(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setImageTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamBoresight(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamMask(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setDetectionAreaRowSelect(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsTimestamp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamLensDistortion(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamMasks(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResults(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultTrigger(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getAutoCamSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getDetectionAreaRow(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamBoresight(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_setCamAutoAdjust(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_setCamSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_getConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setWheelSpeedRef(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setWheelDuty(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setBackupWheelMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setClearErrors(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setMainGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setBackupGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setPWMGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setMotorPower(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getBackupGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getMainGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getPWMGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getStatusErrorFlags(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelData(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDuty(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRef(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeed(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getMotorPower(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getControlMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getBackupWheelMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);
// CUBE_ADCS_GEN_SECTION_END

#endif // CP_CUBEADCS_GEN2_COMMANDS_H_
