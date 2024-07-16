/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup cp
 * @{
 *
 * @file    CP_CubeADCS_Gen2_Commands.c
 * @brief   Command Protocol commands for the Gen2 CubeADCS
 *
 * @}
 */

#include "FP_BaseProtocolTypes.h"
#include "CP_CubeADCS_Gen2_Commands.h"
#include "ESCP_CommandsLocalConf.h"
#include "cubeadcs_gen2.h"
#include "cubeadcs_gen2_gw.h"
#include "trace.h"
#include "if_sys_conf.h"

/** @brief Handle to the ID of a CubeADCS Gen2 node from the service context. */
#define NODE_ID pSrvCtx->pu8CmdData[0]

/** @brief Size of the node ID. */
#define NODE_ID_SIZE sizeof(TctlmCommonFrameworkEnums_AbstractNode)

/** @brief Handle to the status of a CubeADCS Gen2 API method in the CP response buffer. */
#define API_STATUS *(ErrorCode*)&pSrvCtx->pu8ResponseBuf[0]

/** @brief Size of the status of a CubeADCS Gen2 API method. */
#define API_STATUS_SIZE sizeof(ErrorCode)

/** @brief Handle to the request parameters of a CubeADCS Gen2 API method in the CP request buffer. */
#define API_DATA_ADDRESS &pSrvCtx->pu8CmdData[NODE_ID_SIZE]

/** @brief Handle to the response parameters of a CubeADCS Gen2 API method in the CP response buffer. */
#define API_DATA_RESP_ADDRESS &pSrvCtx->pu8ResponseBuf[API_STATUS_SIZE]

/** @brief Offset of the FP header in the request bytes of a CP command. */
#define FP_HDR_OFFSET 1

/** @brief Size of the FP header embedded in a CP command. */
#define FP_HDR_SIZE sizeof(ESSA_Stack_FP_MsgHdr_t)

/** @brief Offset of the request parameters of a CubeADCS Gen2 API method in the CP request buffer. */
#define CMD_PARAMS_OFFSET (FP_HDR_OFFSET + FP_HDR_SIZE)

/** @brief Default value of protocol ID used to indicate invalid ID read from the FIDL. */
#define PROTOCOL_ID_INVALID (uint16_t)(-1)

// CUBE_ADCS_GEN_SECTION_START::DEFINES
/** @brief Protocol ID of the first generated FIDL for the CubeADCS Gen2.Used for calculating index in a dispatch table. */
#define PROTOCOL_ID_OFFSET 300U
// CUBE_ADCS_GEN_SECTION_END::DEFINES

/** @typedef fs_param_sizes_t
 *  @brief Sizes of the request and response data of a CP command.
 */
typedef struct
{
    uint16_t req_size;   /**< number of request data bytes */
    uint16_t resp_size;  /**< number of response data bytes */
} fs_param_sizes_t;

/** @typedef fs_iface_cmds_t
 *  @brief Descriptor of the request and response data sizes of the methods for an API interface module
 */
typedef struct
{
    const fs_param_sizes_t* const cmd_sizes; /**< pointer to the array of sizes for the interface methods */
    uint32_t num_methods;                    /**< number of methods defined in the interface */
} fs_iface_cmds_t;

/** @typedef p_gen2_srv_api_t
 *  @brief Function pointer to a CP handler function for a specific CubeADCS Gen2 API method.
 */
typedef eCPDispatchResult_t(*p_gen2_srv_api_t)(sCubeAdcsGen2SrvCtx_t * const pSrvCtx);

/** @brief Converts the generated protocol ID to an index in a dispatch table.
 *  @param proto_id_raw  Protocol ID from the generated FIDL.
 *
 *  @return Index in the dispatch table on interface level.
*/
static uint16_t fs_get_protocol_id(const uint16_t proto_id_raw);

/** @brief Retrieves the sizes of request and response data for a given method.
 *  @param proto_id  Protocol ID based on the generated FIDL.
 *  @param func_id   Method ID from the generated FIDL.
 *
 *  @return Byte numbers for the request and response data of the specified interface method.
*/
static fs_param_sizes_t fs_get_cmd_sizes(const uint16_t proto_id, const funcIdType_t func_id);

/** @brief Checks validity of request and response data sizes.
 *  @param param_sizes     Structure holding the request and response data sizes of an interface method.
 *  @param cmd_data_size   Number of bytes in the request data of the CP command.
 *  @param resp_buf_size   Number of bytes in the response buffer of the CP command.
 *
 *  @return Byte numbers for the request and response data of the specified interface method.
*/
static bool fs_are_sizes_valid(const fs_param_sizes_t* const param_sizes,
                               const uint32_t cmd_data_size,
                               const uint32_t resp_buf_size);

/** @brief Checks if an interface is compatible with an actual physical node type. The AbstractNode ID is used
 *  to search in a dynamically maintained mapping data structure coming from the CubeComputer.
 *  @param protocol_id     ID of the FIDL which defines the checked interface.
 *  @param node_id         AbstractNode ID of the node.
 *
 *  @return True if the interface is compatible with the node, false otherwise.
*/
static bool fs_check_node_compatibility(const uint16_t protocol_id,
                                        const TctlmCommonFrameworkEnums_AbstractNode node_id);

// CUBE_ADCS_GEN_SECTION_START::CONST_DATA
static const fs_param_sizes_t commonframework1_param_sizes[19] = {
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCommonFramework1_ResetVal), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_setReset
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCommonFramework1_UnixTime), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_setUnixTime
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCommonFramework1_ErrorLogIndex), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_setErrorLogIndex
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCommonFramework1_ErrorLogEntry), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_setErrorLogEntry
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_setErrorLogClear
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCommonFramework1_ErrorLogSettings), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_setErrorLogSettings
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_setConfigPersist
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_Identification) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getIdentification
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_SerialNumber) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getSerialNumber
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_ErrorLogIndex) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getErrorLogIndex
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_ErrorLogEntry) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getErrorLogEntry
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_ErrorLogSettings) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getErrorLogSettings
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_UnixTime) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getUnixTime
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_ConfigPersistDiagnostics) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getConfigPersistDiagnostics
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_CommsStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getCommsStatus
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_Version) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getVersion
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_BootStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getBootStatus
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_TelecommandAcknowledge) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getTelecommandAcknowledge
                                                                  {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFramework1_CommonErrorCodes) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonFramework1_getCommonErrorCodes
                                                                  };

static const fs_param_sizes_t commontransfer1_param_sizes[4] = {
                                                                {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U16), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonTransfer1_setTransferFrame
                                                                {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCommonTransfer1_Frame), sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonTransfer1_setFrame
                                                                {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonTransfer1_FrameInfo) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonTransfer1_getFrameInfo
                                                                {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonTransfer1_Frame) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CommonTransfer1_getFrame
                                                                };

static const fs_param_sizes_t cubecommonbasebootloader5_param_sizes[25] = {
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeCommonBaseBootloader5_ResetVal), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setReset
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setHalt
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeCommonBaseBootloader5_Config), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setConfig
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setDefaultAppTarget
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultApp
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToApp
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAddress
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetFileInfoIdx
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteFileSetup
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setDeleteFileEntry
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeCommonBaseBootloader5_WriteMemorySetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteMemorySetup
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeCommonBaseBootloader5_ReadMemorySetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setReadMemorySetup
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeCommonBaseBootloader5_EraseMemorySetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setEraseMemorySetup
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeCommonBaseBootloader5_OptionBytes), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setOptionBytes
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_setCommitOptionBytes
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_Identification) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getIdentification
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_SerialNumber) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getSerialNumber
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_Config) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getConfig
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_State) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getState
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_Errors) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getErrors
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_FileInfo) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getFileInfo
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(U8) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getDefaultAppTarget
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_OptionBytes) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getOptionBytes
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_CommsStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getCommsStatus
                                                                           {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeCommonBaseBootloader5_TelecommandAcknowledge) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeCommonBaseBootloader5_getTelecommandAcknowledge
                                                                           };

static const fs_param_sizes_t cubecomputercontrolprogram8_param_sizes[92] = {
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigDefaultModes), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigDefaultModes
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMount), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMount
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMag0OrbitCal), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag0OrbitCal
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMag1OrbitCal), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag1OrbitCal
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsController), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsController
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsEstimator), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsEstimator
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsSatellite), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsSatellite
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigOrbitSatParams), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitSatParams
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigOrbitTargetParams), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitTargetParams
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigNodeSelection), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigNodeSelection
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigActuatorRwl), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorRwl
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigActuatorMtq), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorMtq
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMagSensingElement), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMagSensingElement
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAsgp4), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAsgp4
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ConMode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setConMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_EstMode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setEstMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_OrbModeSelect), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setOrbMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_AdcsRunModeSelect), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsRunMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_AdcsOpStateSelect), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsOpState
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_SimSensorRaw), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setSimSensorRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandMtq), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandMtq
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandRwl), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandRwl
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandHxyzRW
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_ReferenceCommands), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommands
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_StrInstanceSelect), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setStrTctlmInstance
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_FssInstanceSelect), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setFssTctlmInstance
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_DeployCommandMag), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setDeployCommandMag
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_GnssSensorCmd), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setGnssSensorCmd
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerControlProgram8_FileTransferSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_setFileTransferSetup
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigDefaultModes) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigDefaultModes
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigMount) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMount
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigMag0OrbitCal) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag0OrbitCal
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigMag1OrbitCal) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag1OrbitCal
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsController) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsController
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsEstimator) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsEstimator
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsSatellite) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsSatellite
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigOrbitSatParams) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitSatParams
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigOrbitTargetParams) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitTargetParams
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigNodeSelection) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigNodeSelection
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigActuatorRwl) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorRwl
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigActuatorMtq) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorMtq
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigMagSensingElement) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMagSensingElement
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConfigAsgp4) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAsgp4
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ConMode) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getConMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_EstMode) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getEstMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_OrbModeSelect) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getOrbMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_AdcsRunModeSelect) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsRunMode
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_AdcsOpStateSelect) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsOpState
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_SimSensorRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getSimSensorRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandMtq) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandMtq
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandRwl) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandRwl
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandHxyzRW
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_ReferenceCommands) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommands
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmHil) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHil
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_AcpExecutionPoint) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExecutionPoint
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmNodeInitState) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNodeInitState
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_FileTransferSetup) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferSetup
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_FileTransferStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferStatus
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_FileInfo) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getFileInfo
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawCss) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawCss
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawMag) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawMag
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawGyro) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawGyro
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawRwl) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwl
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalFss) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalFss
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalCss) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalCss
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalMag) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalMag
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalGyro) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGyro
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalHss) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalHss
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalStr) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalStr
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalGnss) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGnss
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalRwl) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalRwl
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmModels) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmModels
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorMain) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMain
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorBackup) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorBackup
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorMainHighRes) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainHighRes
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmController) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmController
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmGnssRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmGnssRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmExtSensorRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExtSensorRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmStrPst3sRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmRwlNssRwlRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRaw
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmAcpExecution) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmAcpExecution
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmTorquerCurrents) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmTorquerCurrents
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmCubeComputerHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeComputerHealth
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunHealth
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthHealth
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmCubeMagHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeMagHealth
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmRwlHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlHealth
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmStrPst3sHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sHealth
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmNssRwlHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNssRwlHealth
                                                                             {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerControlProgram8_TlmStrHealth) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrHealth
                                                                             };

static const fs_param_sizes_t cubecomputercommon3_param_sizes[24] = {
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setPassThrough
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_PowerState), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setPowerState
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_ImageTransferSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setImageTransferSetup
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setImageFileInfoReset
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_PortMap), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setPortMap
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_EraseMagicNumbers), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setEraseLogData
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_EventLogFilterTransferSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setEventLogFilterTransferSetup
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_TelemetryLogTransferSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setTelemetryLogTransferSetup
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_DummyEvent), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setDummyEvent
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_UnsolicitedEventSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedEventSetup
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeComputerCommon3_UnsolicitedTlmSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedTlmSetup
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getPassThrough
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_PowerState) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getPowerState
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_PortDiagnostics) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getPortDiagnostics
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_PortMap) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getPortMap
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_ExpectedNodes) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getExpectedNodes
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_ImageTransferStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getImageTransferStatus
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_ImageFileInfo) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getImageFileInfo
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_ComponentErrorCodes) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getComponentErrorCodes
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_EventLogStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getEventLogStatus
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_TelemtryLogStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogStatus
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_UnsolicitedEventSetup) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedEventSetup
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_UnsolicitedTlmSetup) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedTlmSetup
                                                                     {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeComputerCommon3_TelemtryLogInclusionMasks) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogInclusionMasks
                                                                     };

static const fs_param_sizes_t cubeircontrolprogram1_param_sizes[11] = {
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeIrControlProgram1_Configuration), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_setConfiguration
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeIrControlProgram1_ImageTransferSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_setImageTransferSetup
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeIrControlProgram1_DeadPixels), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_setDeadPixels
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_setRequestDeadPixel
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeIrControlProgram1_MeasurementAndTrigger) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementAndTrigger
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeIrControlProgram1_Measurement) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_getMeasurement
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeIrControlProgram1_MeasurementMetadata) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementMetadata
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeIrControlProgram1_HealthTlm) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_getHealthTlm
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeIrControlProgram1_Configuration) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_getConfiguration
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeIrControlProgram1_ProfileTiming) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_getProfileTiming
                                                                       {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeIrControlProgram1_RequestedDeadPixel) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeIrControlProgram1_getRequestedDeadPixel
                                                                       };

static const fs_param_sizes_t cubemagcontrolprogramcommon1_param_sizes[12] = {
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeMagControlProgramCommon1_MmcConfig), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcConfig
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_setSamplePrimary
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeMagControlProgramCommon1_Config), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_setConfig
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeMagControlProgramCommon1_MmcCalibration), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcCalibration
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCommon1_MmcConfig) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcConfig
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCommon1_State) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getState
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurement) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurement
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurementRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRaw
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(F32) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagTemp
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCommon1_Config) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getConfig
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCommon1_PrimaryMagDiagnostics) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagDiagnostics
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCommon1_MmcCalibration) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcCalibration
                                                                              };

static const fs_param_sizes_t cubemagcontrolprogramcompact1_param_sizes[1] = {
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramCompact1_HealthTlm) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramCompact1_getHealthTlm
                                                                              };

static const fs_param_sizes_t cubemagcontrolprogramdeploy1_param_sizes[13] = {
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeMagControlProgramDeploy1_PniConfig), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniConfig
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_setSampleRed
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeMagControlProgramDeploy1_MagicDeploy), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeploy
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeMagControlProgramDeploy1_MagicDeployArm), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployArm
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeMagControlProgramDeploy1_PniCalibration), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniCalibration
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramDeploy1_HealthTlm) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getHealthTlm
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramDeploy1_PniConfig) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniConfig
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramDeploy1_RedMagMeasurement) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurement
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramDeploy1_RedMagMeasurementRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRaw
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(F32) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagTemp
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramDeploy1_DeploymentStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getDeploymentStatus
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramDeploy1_RedMagDiagnostics) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagDiagnostics
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeMagControlProgramDeploy1_PniCalibration) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniCalibration
                                                                              };

static const fs_param_sizes_t cubenodecontrolprogramnssrwl1_param_sizes[15] = {
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(Boolean), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNodeSvcSettings
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcSettings), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSvcSettings
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlActiveState), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlActiveStatus
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(F32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlWheelSpeedRef
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(F32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlTorque
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(F32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlMotorCurrent
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSoftwareReset
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(Boolean) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcSettings
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramNssrwl1_NodeSvcStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcStatus
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcSettings) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcSettings
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcStatus
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(F32) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlWheelSpeed
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmStandard) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmStandard
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmExtended) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmExtended
                                                                               {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmSystem) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmSystem
                                                                               };

static const fs_param_sizes_t cubenodecontrolprogrampst3s1_param_sizes[23] = {
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sNumberNavigationStars
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sExposure
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sFourStarSearchThreshold
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSecondCalibration
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sTrackingModeThreshold
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sQuaternionFilteringSetState), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sQuaternionFiltering
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSystemReset
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sActiveStatus), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sActiveStatus
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sImageFixedThreshold
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sSvcSettings), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSvcSettings
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(Boolean), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setNodeSvcSettings
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sSaaWorkingMode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaMode
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaThreshold
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sDynamicModeEnum), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sDynamicMode
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sEdacOff
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sSvcStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcStatus
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sTlm) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sTlm
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sAttitude) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sAttitude
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sHousekeeping) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sHousekeeping
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sConfig) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sConfig
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sSvcSettings) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcSettings
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeControlProgramPst3s1_NodeSvcStatus) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcStatus
                                                                              {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(Boolean) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcSettings
                                                                              };

static const fs_param_sizes_t cubenodecommon1_param_sizes[3] = {
                                                                {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeNodeCommon1_SwitchState), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeCommon1_setPowerSwitchState
                                                                {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeCommon1_HealthTlm) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeCommon1_getHealthTlm
                                                                {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeNodeCommon1_SwitchState) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeNodeCommon1_getPowerSwitchState
                                                                };

static const fs_param_sizes_t cubesensecontrolprogram5_param_sizes[18] = {
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeSenseControlProgram5_CamLensDistortion), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setCamLensDistortion
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setCaptureDetect
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setDetect
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setClearOvercurrentFlags
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeSenseControlProgram5_LocSelection), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setImageCapture
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeSenseControlProgram5_ImageTransferSetup), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setImageTransferSetup
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeSenseControlProgram5_CamBoresight), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setCamBoresight
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeSenseControlProgram5_CamMask), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setCamMask
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setCamThreshold
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(U8), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_setDetectionAreaRowSelect
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseControlProgram5_SensorResultsTimestamp) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsTimestamp
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseControlProgram5_CamLensDistortion) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getCamLensDistortion
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseControlProgram5_CamMasks) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getCamMasks
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseControlProgram5_SensorResults) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResults
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseControlProgram5_SensorResultTrigger) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultTrigger
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseControlProgram5_AutoCamSensorRaw) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getAutoCamSensorRaw
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), 25 + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getDetectionAreaRow
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseControlProgram5_CamBoresight) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseControlProgram5_getCamBoresight
                                                                          };

static const fs_param_sizes_t cubesensecommon1_param_sizes[4] = {
                                                                 {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(Boolean), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseCommon1_setCamAutoAdjust
                                                                 {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeSenseCommon1_CamSettings), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseCommon1_setCamSettings
                                                                 {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseCommon1_Config) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseCommon1_getConfig
                                                                 {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeSenseCommon1_HealthTlm) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeSenseCommon1_getHealthTlm
                                                                 };

static const fs_param_sizes_t cubewheelcontrolprogram3_param_sizes[20] = {
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(F32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setWheelSpeedRef
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(F32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setWheelDuty
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(Boolean), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setBackupWheelMode
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setClearErrors
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeWheelControlProgram3_MainGain), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setMainGain
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(TctlmCubeWheelControlProgram3_BackupGain), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setBackupGain
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(F32), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setPWMGain
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode) + sizeof(Boolean), sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_setMotorPower
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeWheelControlProgram3_BackupGain) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getBackupGain
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeWheelControlProgram3_MainGain) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getMainGain
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(F32) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getPWMGain
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeWheelControlProgram3_StatusErrorFlags) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getStatusErrorFlags
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeWheelControlProgram3_WheelData) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getWheelData
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(F32) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDuty
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeWheelControlProgram3_HealthTlm) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getHealthTlm
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(F32) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRef
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeWheelControlProgram3_WheelSpeed) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeed
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(Boolean) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getMotorPower
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(TctlmCubeWheelControlProgram3_ControlModeVal) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getControlMode
                                                                          {sizeof(TctlmCommonFrameworkEnums_AbstractNode), sizeof(Boolean) + sizeof(ErrorCode)},    //CubeADCS_Gen2_CubeWheelControlProgram3_getBackupWheelMode
                                                                          };

static const fs_iface_cmds_t fs_iface_commands[15] = {
                                                       {commonframework1_param_sizes, 19},
                                                       {commontransfer1_param_sizes, 4},
                                                       {cubecommonbasebootloader5_param_sizes, 25},
                                                       {cubecomputercontrolprogram8_param_sizes, 92},
                                                       {cubecomputercommon3_param_sizes, 24},
                                                       {cubeircontrolprogram1_param_sizes, 11},
                                                       {cubemagcontrolprogramcommon1_param_sizes, 12},
                                                       {cubemagcontrolprogramcompact1_param_sizes, 1},
                                                       {cubemagcontrolprogramdeploy1_param_sizes, 13},
                                                       {cubenodecontrolprogramnssrwl1_param_sizes, 15},
                                                       {cubenodecontrolprogrampst3s1_param_sizes, 23},
                                                       {cubenodecommon1_param_sizes, 3},
                                                       {cubesensecontrolprogram5_param_sizes, 18},
                                                       {cubesensecommon1_param_sizes, 4},
                                                       {cubewheelcontrolprogram3_param_sizes, 20},
                                                       };

static const p_gen2_srv_api_t fs_invoke_commonframework1_method[19] = {
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setReset,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setUnixTime,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogIndex,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogEntry,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogClear,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogSettings,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setConfigPersist,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getIdentification,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getSerialNumber,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogIndex,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogEntry,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogSettings,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getUnixTime,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getConfigPersistDiagnostics,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getCommsStatus,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getVersion,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getBootStatus,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getTelecommandAcknowledge,
                                                                       CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getCommonErrorCodes,
                                                                       };

static const p_gen2_srv_api_t fs_invoke_commontransfer1_method[4] = {
                                                                     CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_setTransferFrame,
                                                                     CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_setFrame,
                                                                     CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_getFrameInfo,
                                                                     CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_getFrame,
                                                                     };

static const p_gen2_srv_api_t fs_invoke_cubecommonbasebootloader5_method[25] = {
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setReset,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setHalt,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setConfig,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setDefaultAppTarget,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultApp,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToApp,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAddress,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetFileInfoIdx,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteFileSetup,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setDeleteFileEntry,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteMemorySetup,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setReadMemorySetup,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setEraseMemorySetup,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setOptionBytes,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setCommitOptionBytes,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getIdentification,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getSerialNumber,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getConfig,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getState,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getErrors,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getFileInfo,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getDefaultAppTarget,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getOptionBytes,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getCommsStatus,
                                                                                CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getTelecommandAcknowledge,
                                                                                };

static const p_gen2_srv_api_t fs_invoke_cubecomputercontrolprogram8_method[92] = {
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigDefaultModes,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMount,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag0OrbitCal,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag1OrbitCal,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsController,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsEstimator,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsSatellite,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitSatParams,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitTargetParams,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigNodeSelection,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorRwl,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorMtq,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMagSensingElement,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAsgp4,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setEstMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOrbMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsRunMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsOpState,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setSimSensorRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandMtq,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandRwl,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandHxyzRW,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommands,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setStrTctlmInstance,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setFssTctlmInstance,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setDeployCommandMag,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setGnssSensorCmd,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setFileTransferSetup,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigDefaultModes,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMount,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag0OrbitCal,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag1OrbitCal,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsController,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsEstimator,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsSatellite,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitSatParams,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitTargetParams,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigNodeSelection,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorRwl,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorMtq,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMagSensingElement,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAsgp4,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getEstMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOrbMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsRunMode,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsOpState,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getSimSensorRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandMtq,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandRwl,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandHxyzRW,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommands,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHil,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExecutionPoint,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNodeInitState,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferSetup,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferStatus,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileInfo,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawCss,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawMag,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawGyro,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwl,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalFss,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalCss,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalMag,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGyro,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalHss,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalStr,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGnss,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalRwl,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmModels,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMain,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorBackup,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainHighRes,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmController,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmGnssRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExtSensorRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRaw,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmAcpExecution,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmTorquerCurrents,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeComputerHealth,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunHealth,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthHealth,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeMagHealth,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlHealth,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sHealth,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNssRwlHealth,
                                                                                  CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrHealth,
                                                                                  };

static const p_gen2_srv_api_t fs_invoke_cubecomputercommon3_method[24] = {
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPassThrough,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPowerState,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setImageTransferSetup,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setImageFileInfoReset,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPortMap,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setEraseLogData,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setEventLogFilterTransferSetup,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setTelemetryLogTransferSetup,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setDummyEvent,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedEventSetup,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedTlmSetup,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPassThrough,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPowerState,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPortDiagnostics,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPortMap,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getExpectedNodes,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getImageTransferStatus,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getImageFileInfo,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getComponentErrorCodes,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getEventLogStatus,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogStatus,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedEventSetup,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedTlmSetup,
                                                                          CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogInclusionMasks,
                                                                          };

static const p_gen2_srv_api_t fs_invoke_cubeircontrolprogram1_method[11] = {
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setConfiguration,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setImageTransferSetup,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setDeadPixels,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setRequestDeadPixel,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementAndTrigger,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurement,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementMetadata,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getHealthTlm,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getConfiguration,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getProfileTiming,
                                                                            CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getRequestedDeadPixel,
                                                                            };

static const p_gen2_srv_api_t fs_invoke_cubemagcontrolprogramcommon1_method[12] = {
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcConfig,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setSamplePrimary,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setConfig,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcCalibration,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcConfig,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getState,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurement,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRaw,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagTemp,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getConfig,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagDiagnostics,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcCalibration,
                                                                                   };

static const p_gen2_srv_api_t fs_invoke_cubemagcontrolprogramcompact1_method[1] = {
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCompact1_getHealthTlm,
                                                                                   };

static const p_gen2_srv_api_t fs_invoke_cubemagcontrolprogramdeploy1_method[13] = {
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniConfig,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setSampleRed,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeploy,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployArm,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniCalibration,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getHealthTlm,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniConfig,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurement,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRaw,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagTemp,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getDeploymentStatus,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagDiagnostics,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniCalibration,
                                                                                   };

static const p_gen2_srv_api_t fs_invoke_cubenodecontrolprogramnssrwl1_method[15] = {
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNodeSvcSettings,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSvcSettings,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlActiveStatus,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlWheelSpeedRef,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlTorque,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlMotorCurrent,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSoftwareReset,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcSettings,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcStatus,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcSettings,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcStatus,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlWheelSpeed,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmStandard,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmExtended,
                                                                                    CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmSystem,
                                                                                    };

static const p_gen2_srv_api_t fs_invoke_cubenodecontrolprogrampst3s1_method[23] = {
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sNumberNavigationStars,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sExposure,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sFourStarSearchThreshold,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSecondCalibration,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sTrackingModeThreshold,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sQuaternionFiltering,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSystemReset,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sActiveStatus,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sImageFixedThreshold,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSvcSettings,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setNodeSvcSettings,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaMode,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaThreshold,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sDynamicMode,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sEdacOff,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcStatus,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sTlm,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sAttitude,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sHousekeeping,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sConfig,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcSettings,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcStatus,
                                                                                   CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcSettings,
                                                                                   };

static const p_gen2_srv_api_t fs_invoke_cubenodecommon1_method[3] = {
                                                                     CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_setPowerSwitchState,
                                                                     CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_getHealthTlm,
                                                                     CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_getPowerSwitchState,
                                                                     };

static const p_gen2_srv_api_t fs_invoke_cubesensecontrolprogram5_method[18] = {
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamLensDistortion,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCaptureDetect,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setDetect,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setClearOvercurrentFlags,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setImageCapture,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setImageTransferSetup,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamBoresight,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamMask,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamThreshold,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setDetectionAreaRowSelect,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsTimestamp,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamLensDistortion,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamMasks,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResults,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultTrigger,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getAutoCamSensorRaw,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getDetectionAreaRow,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamBoresight,
                                                                               };

static const p_gen2_srv_api_t fs_invoke_cubesensecommon1_method[4] = {
                                                                      CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_setCamAutoAdjust,
                                                                      CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_setCamSettings,
                                                                      CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_getConfig,
                                                                      CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_getHealthTlm,
                                                                      };

static const p_gen2_srv_api_t fs_invoke_cubewheelcontrolprogram3_method[20] = {
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setWheelSpeedRef,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setWheelDuty,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setBackupWheelMode,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setClearErrors,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setMainGain,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setBackupGain,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setPWMGain,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setMotorPower,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getBackupGain,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getMainGain,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getPWMGain,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getStatusErrorFlags,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelData,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDuty,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getHealthTlm,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRef,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeed,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getMotorPower,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getControlMode,
                                                                               CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getBackupWheelMode,
                                                                               };

static const p_gen2_srv_api_t* fs_invoke_method[15] = {
                                                       fs_invoke_commonframework1_method,
                                                       fs_invoke_commontransfer1_method,
                                                       fs_invoke_cubecommonbasebootloader5_method,
                                                       fs_invoke_cubecomputercontrolprogram8_method,
                                                       fs_invoke_cubecomputercommon3_method,
                                                       fs_invoke_cubeircontrolprogram1_method,
                                                       fs_invoke_cubemagcontrolprogramcommon1_method,
                                                       fs_invoke_cubemagcontrolprogramcompact1_method,
                                                       fs_invoke_cubemagcontrolprogramdeploy1_method,
                                                       fs_invoke_cubenodecontrolprogramnssrwl1_method,
                                                       fs_invoke_cubenodecontrolprogrampst3s1_method,
                                                       fs_invoke_cubenodecommon1_method,
                                                       fs_invoke_cubesensecontrolprogram5_method,
                                                       fs_invoke_cubesensecommon1_method,
                                                       fs_invoke_cubewheelcontrolprogram3_method,
                                                       };

static const bool fs_fidl_allowed_for_node_type[15][13] = {
                                                           {true, true, true, true, true, true, true, false, false, false, false, true, true},    // CubeADCS_Gen2_CommonFramework1.fidl
                                                           {true, true, true, false, true, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CommonTransfer1.fidl
                                                           {true, false, false, false, false, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeCommonBaseBootloader5.fidl
                                                           {true, true, false, false, false, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeComputerControlProgram8.fidl
                                                           {true, true, false, false, false, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeComputerCommon3.fidl
                                                           {true, false, false, false, true, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeIrControlProgram1.fidl
                                                           {true, false, false, false, false, true, true, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeMagControlProgramCommon1.fidl
                                                           {true, false, false, false, false, false, true, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeMagControlProgramCompact1.fidl
                                                           {true, false, false, false, false, true, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeMagControlProgramDeploy1.fidl
                                                           {true, false, false, false, false, false, false, false, false, false, false, false, true},    // CubeADCS_Gen2_CubeNodeControlProgramNssrwl1.fidl
                                                           {true, false, false, false, false, false, false, false, false, false, false, true, false},    // CubeADCS_Gen2_CubeNodeControlProgramPst3s1.fidl
                                                           {true, false, false, false, false, false, false, false, false, false, false, true, true},    // CubeADCS_Gen2_CubeNodeCommon1.fidl
                                                           {true, false, true, false, false, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeSenseControlProgram5.fidl
                                                           {true, false, true, false, false, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeSenseCommon1.fidl
                                                           {true, false, false, true, false, false, false, false, false, false, false, false, false},    // CubeADCS_Gen2_CubeWheelControlProgram3.fidl
                                                           };

// CUBE_ADCS_GEN_SECTION_END::CONST_DATA

static uint16_t fs_get_protocol_id(const uint16_t proto_id_raw)
{
    return proto_id_raw >= PROTOCOL_ID_OFFSET ? (uint16_t)(proto_id_raw - PROTOCOL_ID_OFFSET) : PROTOCOL_ID_INVALID;
}

static fs_param_sizes_t fs_get_cmd_sizes(const uint16_t proto_id, const funcIdType_t func_id)
{
    fs_param_sizes_t res = {0,0};

    if ( (proto_id <= sizeof(fs_iface_commands)/sizeof(fs_iface_commands[0])) && (func_id < fs_iface_commands[proto_id].num_methods))
    {
        res = fs_iface_commands[proto_id].cmd_sizes[func_id];
    }

    return res;
}

static bool fs_are_sizes_valid(const fs_param_sizes_t* const param_sizes,
                               const uint32_t cmd_data_size,
                               const uint32_t resp_buf_size)
{
    bool res = false;

    if (    (param_sizes->req_size > 0)
         && (param_sizes->resp_size > 0)
         && (cmd_data_size > CMD_PARAMS_OFFSET)
         && (resp_buf_size > CMD_PARAMS_OFFSET)
         && (param_sizes->req_size <= cmd_data_size - CMD_PARAMS_OFFSET)
         && (param_sizes->resp_size <= resp_buf_size - CMD_PARAMS_OFFSET) )
    {
        res = true;
    }

    return res;
}

static bool fs_check_node_compatibility(const uint16_t protocol_id, const TctlmCommonFrameworkEnums_AbstractNode node_id)
{
    bool result = false;

    if (protocol_id < CDEF_ELEMENT_COUNT(fs_fidl_allowed_for_node_type))
    {
        if (TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER == node_id)
        {
            // CubeComputer is not present in the expected nodes configuration, but is always present in the system
            result = fs_fidl_allowed_for_node_type[protocol_id][TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER];
        }
        else
        {
            const TctlmCommonFrameworkEnums_NodeType node_type = cubeadcs_gen2_get_node_type(node_id);
            result                                             = fs_fidl_allowed_for_node_type[protocol_id][node_type];
        }
    }

    return result;
}

eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_GwSendCmd(sCPDispatchContext_t * const psDispCtx)
{
    eCPDispatchResult_t res = ECPDISPATCHRESULT_ERROR;

    if (    (false != sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
         && (false != CPCmdHandler_IsDispContextValid(psDispCtx, CP_CMD_CUBEADCS_GEN2_GWSEND)) )
    {
        // Set default response status to error
        psDispCtx->u32ResponseActualSize = 0U;
        psDispCtx->u8TLError = EESTL_SFERR_BAD_CMD_PARAMS;

        if (psDispCtx->u32CmdDataSize >= FP_HDR_SIZE)
        {
            const ESSA_Stack_FP_MsgHdr_t* const p_fp_hdr = (const ESSA_Stack_FP_MsgHdr_t* const)(&psDispCtx->pu8CmdData[FP_HDR_OFFSET]);
            // Check the size of the actual command
            const uint16_t proto_id = fs_get_protocol_id(p_fp_hdr->protoId);
            const fs_param_sizes_t cmd_sizes = fs_get_cmd_sizes(proto_id, p_fp_hdr->funcId);

            if ( false != fs_are_sizes_valid(&cmd_sizes, psDispCtx->u32CmdDataSize, psDispCtx->u32ResponseBufSize) )
            {
                sCubeAdcsGen2SrvCtx_t srv_ctx = {
                        .pu8CmdData = &psDispCtx->pu8CmdData[CMD_PARAMS_OFFSET],
                        .pu8ResponseBuf = &psDispCtx->pu8ResponseBuf[FP_HDR_SIZE],
                        .u32CmdDataSize = cmd_sizes.req_size,
                        .u32ResponseActualSize = 0         // This will be set by the invoked service method
                };
                // Check if the actual physical type of the target node can execute methods of the FIDL interface
                if (false != fs_check_node_compatibility(proto_id, srv_ctx.pu8CmdData[0]))
                {
                    res = fs_invoke_method[proto_id][p_fp_hdr->funcId](&srv_ctx); // Range checks are already covered by fs_are_sizes_valid

                    // Pass response parameters from the service context to the dispatch context
                    psDispCtx->u32ResponseActualSize = FP_HDR_SIZE + srv_ctx.u32ResponseActualSize;
                }
                else
                {
                    psDispCtx->u32ResponseActualSize = FP_HDR_SIZE + cmd_sizes.resp_size;
                    psDispCtx->pu8ResponseBuf[FP_HDR_SIZE] = CUBEOBC_ERROR_NODE_TYPE;
                    res = ECPDISPATCHRESULT_RESULT_OK; // We need the result as OK so that we can return the node type error to GS.
                }
                psDispCtx->u8TLError = EESTL_SFERR_SUCCESS;

                // Construct the response FP header
                ESSA_Stack_FP_MsgHdr_t* const p_fp_resp_hdr = (ESSA_Stack_FP_MsgHdr_t* const)(psDispCtx->pu8ResponseBuf);
                p_fp_resp_hdr->protoId = p_fp_hdr->protoId;
                p_fp_resp_hdr->funcId = p_fp_hdr->funcId;
                SET_RESPONSE(*p_fp_resp_hdr);
                p_fp_resp_hdr->seqId = p_fp_hdr->seqId;
                p_fp_resp_hdr->errCode = ESSA_FP_ERRCODE_NOERROR;
            }
        }
    }

    return res;
}


// CUBE_ADCS_GEN_SECTION_START::HNDL_CODE
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_setResetRequestGw(NODE_ID, *((TctlmCommonFramework1_ResetVal*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setUnixTime(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_setUnixTimeRequestGw(NODE_ID, (TctlmCommonFramework1_UnixTime*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogIndex(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_setErrorLogIndexRequestGw(NODE_ID, (TctlmCommonFramework1_ErrorLogIndex*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogEntry(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_setErrorLogEntryRequestGw(NODE_ID, (TctlmCommonFramework1_ErrorLogEntry*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogClear(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_setErrorLogClearRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setErrorLogSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_setErrorLogSettingsRequestGw(NODE_ID, (TctlmCommonFramework1_ErrorLogSettings*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_setConfigPersist(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_setConfigPersistRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getIdentification(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getIdentificationRequestGw(NODE_ID, (TctlmCommonFramework1_Identification*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_Identification);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getSerialNumber(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getSerialNumberRequestGw(NODE_ID, (TctlmCommonFramework1_SerialNumber*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_SerialNumber);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogIndex(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getErrorLogIndexRequestGw(NODE_ID, (TctlmCommonFramework1_ErrorLogIndex*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_ErrorLogIndex);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogEntry(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getErrorLogEntryRequestGw(NODE_ID, (TctlmCommonFramework1_ErrorLogEntry*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_ErrorLogEntry);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getErrorLogSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getErrorLogSettingsRequestGw(NODE_ID, (TctlmCommonFramework1_ErrorLogSettings*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_ErrorLogSettings);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getUnixTime(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getUnixTimeRequestGw(NODE_ID, (TctlmCommonFramework1_UnixTime*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_UnixTime);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getConfigPersistDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getConfigPersistDiagnosticsRequestGw(NODE_ID, (TctlmCommonFramework1_ConfigPersistDiagnostics*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_ConfigPersistDiagnostics);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getCommsStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getCommsStatusRequestGw(NODE_ID, (TctlmCommonFramework1_CommsStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_CommsStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getVersion(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getVersionRequestGw(NODE_ID, (TctlmCommonFramework1_Version*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_Version);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getBootStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getBootStatusRequestGw(NODE_ID, (TctlmCommonFramework1_BootStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_BootStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getTelecommandAcknowledge(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getTelecommandAcknowledgeRequestGw(NODE_ID, (TctlmCommonFramework1_TelecommandAcknowledge*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_TelecommandAcknowledge);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonFramework1_getCommonErrorCodes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonFramework1_getCommonErrorCodesRequestGw(NODE_ID, (TctlmCommonFramework1_CommonErrorCodes*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFramework1_CommonErrorCodes);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_setTransferFrame(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonTransfer1_setTransferFrameRequestGw(NODE_ID, *((U16*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_setFrame(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonTransfer1_setFrameRequestGw(NODE_ID, (TctlmCommonTransfer1_Frame*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_getFrameInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonTransfer1_getFrameInfoRequestGw(NODE_ID, (TctlmCommonTransfer1_FrameInfo*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonTransfer1_FrameInfo);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CommonTransfer1_getFrame(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CommonTransfer1_getFrameRequestGw(NODE_ID, (TctlmCommonTransfer1_Frame*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonTransfer1_Frame);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetRequestGw(NODE_ID, *((TctlmCubeCommonBaseBootloader5_ResetVal*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setHalt(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setHaltRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setConfigRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_Config*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setDefaultAppTarget(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setDefaultAppTargetRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultApp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultAppRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToApp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAppRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAddress(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToAddressRequestGw(NODE_ID, *((U32*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetFileInfoIdx(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setResetFileInfoIdxRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteFileSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteFileSetupRequestGw(NODE_ID, *((U8**)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setDeleteFileEntry(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setDeleteFileEntryRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteMemorySetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setWriteMemorySetupRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_WriteMemorySetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setReadMemorySetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setReadMemorySetupRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_ReadMemorySetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setEraseMemorySetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setEraseMemorySetupRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_EraseMemorySetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setOptionBytes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setOptionBytesRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_OptionBytes*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_setCommitOptionBytes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_setCommitOptionBytesRequestGw(NODE_ID, *((U32*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getIdentification(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getIdentificationRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_Identification*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_Identification);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getSerialNumber(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getSerialNumberRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_SerialNumber*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_SerialNumber);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getConfigRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_Config*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_Config);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getStateRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_State*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_State);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getErrors(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getErrorsRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_Errors*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_Errors);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getFileInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getFileInfoRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_FileInfo*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_FileInfo);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getDefaultAppTarget(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getDefaultAppTargetRequestGw(NODE_ID, (U8*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(U8);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getOptionBytes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getOptionBytesRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_OptionBytes*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_OptionBytes);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getCommsStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getCommsStatusRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_CommsStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_CommsStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeCommonBaseBootloader5_getTelecommandAcknowledge(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeCommonBaseBootloader5_getTelecommandAcknowledgeRequestGw(NODE_ID, (TctlmCubeCommonBaseBootloader5_TelecommandAcknowledge*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeCommonBaseBootloader5_TelecommandAcknowledge);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigDefaultModes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigDefaultModesRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigDefaultModes*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMount(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMountRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMount*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag0OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag0OrbitCalRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMag0OrbitCal*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag1OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMag1OrbitCalRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMag1OrbitCal*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsController(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsControllerRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAdcsController*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsEstimator(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsEstimatorRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAdcsEstimator*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsSatellite(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAdcsSatelliteRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAdcsSatellite*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitSatParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitSatParamsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigOrbitSatParams*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitTargetParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigOrbitTargetParamsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigOrbitTargetParams*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigNodeSelection(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigNodeSelectionRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigNodeSelection*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorRwlRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigActuatorRwl*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigActuatorMtqRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigActuatorMtq*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMagSensingElement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigMagSensingElementRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMagSensingElement*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAsgp4(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConfigAsgp4RequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAsgp4*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setConMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setConModeRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConMode*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setEstMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setEstModeRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_EstMode*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOrbMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setOrbModeRequestGw(NODE_ID, *((TctlmCubeComputerControlProgram8_OrbModeSelect*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsRunMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsRunModeRequestGw(NODE_ID, *((TctlmCubeComputerControlProgram8_AdcsRunModeSelect*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsOpState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setAdcsOpStateRequestGw(NODE_ID, *((TctlmCubeComputerControlProgram8_AdcsOpStateSelect*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setSimSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setSimSensorRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_SimSensorRaw*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandMtqRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_OpenLoopCommandMtq*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandRwlRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_OpenLoopCommandRwl*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandHxyzRW(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setOpenLoopCommandHxyzRWRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommands(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setReferenceCommandsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ReferenceCommands*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setStrTctlmInstance(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setStrTctlmInstanceRequestGw(NODE_ID, *((TctlmCubeComputerControlProgram8_StrInstanceSelect*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setFssTctlmInstance(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setFssTctlmInstanceRequestGw(NODE_ID, *((TctlmCubeComputerControlProgram8_FssInstanceSelect*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setDeployCommandMag(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setDeployCommandMagRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_DeployCommandMag*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setGnssSensorCmd(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setGnssSensorCmdRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_GnssSensorCmd*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_setFileTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_setFileTransferSetupRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_FileTransferSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigDefaultModes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigDefaultModesRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigDefaultModes*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigDefaultModes);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMount(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMountRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMount*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMount);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag0OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag0OrbitCalRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMag0OrbitCal*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMag0OrbitCal);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag1OrbitCal(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMag1OrbitCalRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMag1OrbitCal*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMag1OrbitCal);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsController(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsControllerRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAdcsController*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsController);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsEstimator(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsEstimatorRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAdcsEstimator*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsEstimator);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsSatellite(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAdcsSatelliteRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAdcsSatellite*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAdcsSatellite);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitSatParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitSatParamsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigOrbitSatParams*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigOrbitSatParams);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitTargetParams(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigOrbitTargetParamsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigOrbitTargetParams*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigOrbitTargetParams);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigNodeSelection(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigNodeSelectionRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigNodeSelection*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigNodeSelection);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorRwlRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigActuatorRwl*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigActuatorRwl);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigActuatorMtqRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigActuatorMtq*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigActuatorMtq);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMagSensingElement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigMagSensingElementRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigMagSensingElement*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigMagSensingElement);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAsgp4(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConfigAsgp4RequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConfigAsgp4*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConfigAsgp4);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getConMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getConModeRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ConMode*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ConMode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getEstMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getEstModeRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_EstMode*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_EstMode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOrbMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getOrbModeRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_OrbModeSelect*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_OrbModeSelect);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsRunMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsRunModeRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_AdcsRunModeSelect*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_AdcsRunModeSelect);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsOpState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getAdcsOpStateRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_AdcsOpStateSelect*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_AdcsOpStateSelect);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getSimSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getSimSensorRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_SimSensorRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_SimSensorRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandMtq(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandMtqRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_OpenLoopCommandMtq*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandMtq);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandRwlRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_OpenLoopCommandRwl*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandRwl);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandHxyzRW(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getOpenLoopCommandHxyzRWRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_OpenLoopCommandHxyzRW);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommands(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getReferenceCommandsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_ReferenceCommands*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_ReferenceCommands);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHil(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHilRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmHil*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmHil);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExecutionPoint(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExecutionPointRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_AcpExecutionPoint*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_AcpExecutionPoint);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNodeInitState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNodeInitStateRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmNodeInitState*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmNodeInitState);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferSetupRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_FileTransferSetup*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_FileTransferSetup);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getFileTransferStatusRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_FileTransferStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_FileTransferStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getFileInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getFileInfoRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_FileInfo*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_FileInfo);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawCss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawCssRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorRawCss*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawCss);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawMag(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawMagRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorRawMag*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawMag);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawGyro(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawGyroRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorRawGyro*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawGyro);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwlRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorRawRwl*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawRwl);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalFss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalFssRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalFss*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalFss);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalCss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalCssRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalCss*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalCss);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalMag(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalMagRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalMag*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalMag);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGyro(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGyroRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalGyro*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalGyro);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalHss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalHssRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalHss*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalHss);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalStr(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalStrRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalStr*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalStr);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGnss(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGnssRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalGnss*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalGnss);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalRwl(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalRwlRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmSensorCalRwl*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalRwl);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmModels(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmModelsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmModels*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmModels);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmEstimatorMain*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorMain);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorBackup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorBackupRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmEstimatorBackup*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorBackup);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainHighRes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainHighResRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmEstimatorMainHighRes*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorMainHighRes);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmController(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmControllerRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmController*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmController);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmGnssRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmGnssRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmGnssRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmGnssRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExtSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExtSensorRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmExtSensorRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmExtSensorRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmStrPst3sRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmStrPst3sRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRawRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmRwlNssRwlRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmRwlNssRwlRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmAcpExecution(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmAcpExecutionRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmAcpExecution*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmAcpExecution);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmTorquerCurrents(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmTorquerCurrentsRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmTorquerCurrents*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmTorquerCurrents);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeComputerHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeComputerHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmCubeComputerHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmCubeComputerHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeMagHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeMagHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmCubeMagHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmCubeMagHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmRwlHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmRwlHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmStrPst3sHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmStrPst3sHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNssRwlHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNssRwlHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmNssRwlHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmNssRwlHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrHealth(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrHealthRequestGw(NODE_ID, (TctlmCubeComputerControlProgram8_TlmStrHealth*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerControlProgram8_TlmStrHealth);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPassThrough(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setPassThroughRequestGw(NODE_ID, *((TctlmCommonFrameworkEnums_AbstractNode*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPowerState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setPowerStateRequestGw(NODE_ID, (TctlmCubeComputerCommon3_PowerState*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setImageTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setImageTransferSetupRequestGw(NODE_ID, (TctlmCubeComputerCommon3_ImageTransferSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setImageFileInfoReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setImageFileInfoResetRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setPortMap(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setPortMapRequestGw(NODE_ID, (TctlmCubeComputerCommon3_PortMap*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setEraseLogData(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setEraseLogDataRequestGw(NODE_ID, *((TctlmCubeComputerCommon3_EraseMagicNumbers*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setEventLogFilterTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setEventLogFilterTransferSetupRequestGw(NODE_ID, (TctlmCubeComputerCommon3_EventLogFilterTransferSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setTelemetryLogTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setTelemetryLogTransferSetupRequestGw(NODE_ID, (TctlmCubeComputerCommon3_TelemetryLogTransferSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setDummyEvent(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setDummyEventRequestGw(NODE_ID, (TctlmCubeComputerCommon3_DummyEvent*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedEventSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedEventSetupRequestGw(NODE_ID, (TctlmCubeComputerCommon3_UnsolicitedEventSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedTlmSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_setUnsolicitedTlmSetupRequestGw(NODE_ID, (TctlmCubeComputerCommon3_UnsolicitedTlmSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPassThrough(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getPassThroughRequestGw(NODE_ID, (TctlmCommonFrameworkEnums_AbstractNode*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCommonFrameworkEnums_AbstractNode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPowerState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getPowerStateRequestGw(NODE_ID, (TctlmCubeComputerCommon3_PowerState*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_PowerState);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPortDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getPortDiagnosticsRequestGw(NODE_ID, (TctlmCubeComputerCommon3_PortDiagnostics*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_PortDiagnostics);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getPortMap(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getPortMapRequestGw(NODE_ID, (TctlmCubeComputerCommon3_PortMap*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_PortMap);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getExpectedNodes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getExpectedNodesRequestGw(NODE_ID, (TctlmCubeComputerCommon3_ExpectedNodes*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_ExpectedNodes);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getImageTransferStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getImageTransferStatusRequestGw(NODE_ID, (TctlmCubeComputerCommon3_ImageTransferStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_ImageTransferStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getImageFileInfo(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getImageFileInfoRequestGw(NODE_ID, (TctlmCubeComputerCommon3_ImageFileInfo*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_ImageFileInfo);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getComponentErrorCodes(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getComponentErrorCodesRequestGw(NODE_ID, (TctlmCubeComputerCommon3_ComponentErrorCodes*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_ComponentErrorCodes);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getEventLogStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getEventLogStatusRequestGw(NODE_ID, (TctlmCubeComputerCommon3_EventLogStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_EventLogStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogStatusRequestGw(NODE_ID, (TctlmCubeComputerCommon3_TelemtryLogStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_TelemtryLogStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedEventSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedEventSetupRequestGw(NODE_ID, (TctlmCubeComputerCommon3_UnsolicitedEventSetup*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_UnsolicitedEventSetup);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedTlmSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getUnsolicitedTlmSetupRequestGw(NODE_ID, (TctlmCubeComputerCommon3_UnsolicitedTlmSetup*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_UnsolicitedTlmSetup);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogInclusionMasks(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeComputerCommon3_getTelemtryLogInclusionMasksRequestGw(NODE_ID, (TctlmCubeComputerCommon3_TelemtryLogInclusionMasks*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeComputerCommon3_TelemtryLogInclusionMasks);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setConfiguration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_setConfigurationRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_Configuration*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setImageTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_setImageTransferSetupRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_ImageTransferSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setDeadPixels(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_setDeadPixelsRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_DeadPixels*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_setRequestDeadPixel(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_setRequestDeadPixelRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementAndTrigger(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementAndTriggerRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_MeasurementAndTrigger*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeIrControlProgram1_MeasurementAndTrigger);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_Measurement*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeIrControlProgram1_Measurement);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementMetadata(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_getMeasurementMetadataRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_MeasurementMetadata*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeIrControlProgram1_MeasurementMetadata);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_getHealthTlmRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_HealthTlm*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeIrControlProgram1_HealthTlm);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getConfiguration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_getConfigurationRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_Configuration*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeIrControlProgram1_Configuration);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getProfileTiming(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_getProfileTimingRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_ProfileTiming*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeIrControlProgram1_ProfileTiming);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeIrControlProgram1_getRequestedDeadPixel(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeIrControlProgram1_getRequestedDeadPixelRequestGw(NODE_ID, (TctlmCubeIrControlProgram1_RequestedDeadPixel*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeIrControlProgram1_RequestedDeadPixel);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcConfigRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_MmcConfig*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setSamplePrimary(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_setSamplePrimaryRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_setConfigRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_Config*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_setMmcCalibrationRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_MmcCalibration*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcConfigRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_MmcConfig*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCommon1_MmcConfig);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getStateRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_State*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCommon1_State);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurement*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurement);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagMeasurementRawRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurementRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCommon1_PrimaryMagMeasurementRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagTemp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagTempRequestGw(NODE_ID, (F32*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(F32);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getConfigRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_Config*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCommon1_Config);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getPrimaryMagDiagnosticsRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_PrimaryMagDiagnostics*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCommon1_PrimaryMagDiagnostics);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCommon1_getMmcCalibrationRequestGw(NODE_ID, (TctlmCubeMagControlProgramCommon1_MmcCalibration*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCommon1_MmcCalibration);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramCompact1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramCompact1_getHealthTlmRequestGw(NODE_ID, (TctlmCubeMagControlProgramCompact1_HealthTlm*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramCompact1_HealthTlm);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniConfigRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_PniConfig*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setSampleRed(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_setSampleRedRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeploy(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployRequestGw(NODE_ID, *((TctlmCubeMagControlProgramDeploy1_MagicDeploy*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployArm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_setDeployArmRequestGw(NODE_ID, *((TctlmCubeMagControlProgramDeploy1_MagicDeployArm*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_setPniCalibrationRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_PniCalibration*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getHealthTlmRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_HealthTlm*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramDeploy1_HealthTlm);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniConfigRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_PniConfig*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramDeploy1_PniConfig);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurement(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_RedMagMeasurement*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramDeploy1_RedMagMeasurement);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagMeasurementRawRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_RedMagMeasurementRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramDeploy1_RedMagMeasurementRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagTemp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagTempRequestGw(NODE_ID, (F32*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(F32);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getDeploymentStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getDeploymentStatusRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_DeploymentStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramDeploy1_DeploymentStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagDiagnostics(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getRedMagDiagnosticsRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_RedMagDiagnostics*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramDeploy1_RedMagDiagnostics);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeMagControlProgramDeploy1_getPniCalibrationRequestGw(NODE_ID, (TctlmCubeMagControlProgramDeploy1_PniCalibration*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeMagControlProgramDeploy1_PniCalibration);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNodeSvcSettingsRequestGw(NODE_ID, *((Boolean*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSvcSettingsRequestGw(NODE_ID, (TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcSettings*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlActiveStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlActiveStatusRequestGw(NODE_ID, *((TctlmCubeNodeControlProgramNssrwl1_NssRwlActiveState*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlWheelSpeedRef(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    F32 tmp_set_val;
    memcpy(&tmp_set_val, (F32*)API_DATA_ADDRESS, sizeof(F32));
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlWheelSpeedRefRequestGw(NODE_ID, tmp_set_val, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlTorque(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    F32 tmp_set_val;
    memcpy(&tmp_set_val, (F32*)API_DATA_ADDRESS, sizeof(F32));
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlTorqueRequestGw(NODE_ID, tmp_set_val, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlMotorCurrent(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    F32 tmp_set_val;
    memcpy(&tmp_set_val, (F32*)API_DATA_ADDRESS, sizeof(F32));
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlMotorCurrentRequestGw(NODE_ID, tmp_set_val, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSoftwareReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_setNssRwlSoftwareResetRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcSettingsRequestGw(NODE_ID, (Boolean*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(Boolean);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNodeSvcStatusRequestGw(NODE_ID, (TctlmCubeNodeControlProgramNssrwl1_NodeSvcStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NodeSvcStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcSettingsRequestGw(NODE_ID, (TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcSettings*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcSettings);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlSvcStatusRequestGw(NODE_ID, (TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlSvcStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlWheelSpeed(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlWheelSpeedRequestGw(NODE_ID, (F32*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(F32);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmStandard(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmStandardRequestGw(NODE_ID, (TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmStandard*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmStandard);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmExtended(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmExtendedRequestGw(NODE_ID, (TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmExtended*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmExtended);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmSystem(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramNssrwl1_getNssRwlTlmSystemRequestGw(NODE_ID, (TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmSystem*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramNssrwl1_NssRwlTlmSystem);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sNumberNavigationStars(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sNumberNavigationStarsRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sExposure(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sExposureRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sFourStarSearchThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sFourStarSearchThresholdRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSecondCalibration(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSecondCalibrationRequestGw(NODE_ID, *((U32*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sTrackingModeThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sTrackingModeThresholdRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sQuaternionFiltering(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sQuaternionFilteringRequestGw(NODE_ID, *((TctlmCubeNodeControlProgramPst3s1_Pst3sQuaternionFilteringSetState*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSystemReset(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSystemResetRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sActiveStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sActiveStatusRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sActiveStatus*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sImageFixedThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sImageFixedThresholdRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSvcSettingsRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sSvcSettings*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setNodeSvcSettingsRequestGw(NODE_ID, *((Boolean*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaModeRequestGw(NODE_ID, *((TctlmCubeNodeControlProgramPst3s1_Pst3sSaaWorkingMode*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sSaaThresholdRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sDynamicMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sDynamicModeRequestGw(NODE_ID, *((TctlmCubeNodeControlProgramPst3s1_Pst3sDynamicModeEnum*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sEdacOff(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_setPst3sEdacOffRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcStatusRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sSvcStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sSvcStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sTlmRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sTlm*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sTlm);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sAttitude(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sAttitudeRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sAttitude*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sAttitude);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sHousekeeping(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sHousekeepingRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sHousekeeping*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sHousekeeping);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sConfigRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sConfig*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sConfig);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getPst3sSvcSettingsRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_Pst3sSvcSettings*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramPst3s1_Pst3sSvcSettings);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcStatus(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcStatusRequestGw(NODE_ID, (TctlmCubeNodeControlProgramPst3s1_NodeSvcStatus*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeControlProgramPst3s1_NodeSvcStatus);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeControlProgramPst3s1_getNodeSvcSettingsRequestGw(NODE_ID, (Boolean*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(Boolean);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_setPowerSwitchState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeCommon1_setPowerSwitchStateRequestGw(NODE_ID, *((TctlmCubeNodeCommon1_SwitchState*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeCommon1_getHealthTlmRequestGw(NODE_ID, (TctlmCubeNodeCommon1_HealthTlm*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeCommon1_HealthTlm);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeNodeCommon1_getPowerSwitchState(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeNodeCommon1_getPowerSwitchStateRequestGw(NODE_ID, (TctlmCubeNodeCommon1_SwitchState*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeNodeCommon1_SwitchState);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamLensDistortion(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setCamLensDistortionRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_CamLensDistortion*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCaptureDetect(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setCaptureDetectRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setDetect(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setDetectRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setClearOvercurrentFlags(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setClearOvercurrentFlagsRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setImageCapture(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setImageCaptureRequestGw(NODE_ID, *((TctlmCubeSenseControlProgram5_LocSelection*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setImageTransferSetup(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setImageTransferSetupRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_ImageTransferSetup*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamBoresight(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setCamBoresightRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_CamBoresight*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamMask(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setCamMaskRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_CamMask*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setCamThreshold(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setCamThresholdRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_setDetectionAreaRowSelect(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_setDetectionAreaRowSelectRequestGw(NODE_ID, *((U8*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsTimestamp(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsTimestampRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_SensorResultsTimestamp*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseControlProgram5_SensorResultsTimestamp);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamLensDistortion(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getCamLensDistortionRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_CamLensDistortion*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseControlProgram5_CamLensDistortion);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamMasks(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getCamMasksRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_CamMasks*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseControlProgram5_CamMasks);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResults(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultsRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_SensorResults*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseControlProgram5_SensorResults);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultTrigger(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getSensorResultTriggerRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_SensorResultTrigger*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseControlProgram5_SensorResultTrigger);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getAutoCamSensorRaw(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getAutoCamSensorRawRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_AutoCamSensorRaw*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseControlProgram5_AutoCamSensorRaw);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getDetectionAreaRow(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getDetectionAreaRowRequestGw(NODE_ID, API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + (uint32_t)25;
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseControlProgram5_getCamBoresight(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseControlProgram5_getCamBoresightRequestGw(NODE_ID, (TctlmCubeSenseControlProgram5_CamBoresight*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseControlProgram5_CamBoresight);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_setCamAutoAdjust(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseCommon1_setCamAutoAdjustRequestGw(NODE_ID, *((Boolean*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_setCamSettings(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseCommon1_setCamSettingsRequestGw(NODE_ID, (TctlmCubeSenseCommon1_CamSettings*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_getConfig(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseCommon1_getConfigRequestGw(NODE_ID, (TctlmCubeSenseCommon1_Config*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseCommon1_Config);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeSenseCommon1_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeSenseCommon1_getHealthTlmRequestGw(NODE_ID, (TctlmCubeSenseCommon1_HealthTlm*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeSenseCommon1_HealthTlm);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setWheelSpeedRef(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    F32 tmp_set_val;
    memcpy(&tmp_set_val, (F32*)API_DATA_ADDRESS, sizeof(F32));
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setWheelSpeedRefRequestGw(NODE_ID, tmp_set_val, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setWheelDuty(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    F32 tmp_set_val;
    memcpy(&tmp_set_val, (F32*)API_DATA_ADDRESS, sizeof(F32));
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setWheelDutyRequestGw(NODE_ID, tmp_set_val, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setBackupWheelMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setBackupWheelModeRequestGw(NODE_ID, *((Boolean*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setClearErrors(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setClearErrorsRequestGw(NODE_ID, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setMainGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setMainGainRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_MainGain*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setBackupGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setBackupGainRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_BackupGain*)API_DATA_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setPWMGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    F32 tmp_set_val;
    memcpy(&tmp_set_val, (F32*)API_DATA_ADDRESS, sizeof(F32));
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setPWMGainRequestGw(NODE_ID, tmp_set_val, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_setMotorPower(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_setMotorPowerRequestGw(NODE_ID, *((Boolean*)API_DATA_ADDRESS), CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getBackupGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getBackupGainRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_BackupGain*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeWheelControlProgram3_BackupGain);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getMainGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getMainGainRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_MainGain*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeWheelControlProgram3_MainGain);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getPWMGain(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getPWMGainRequestGw(NODE_ID, (F32*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(F32);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getStatusErrorFlags(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getStatusErrorFlagsRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_StatusErrorFlags*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeWheelControlProgram3_StatusErrorFlags);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelData(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDataRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_WheelData*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeWheelControlProgram3_WheelData);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDuty(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getWheelDutyRequestGw(NODE_ID, (F32*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(F32);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getHealthTlm(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getHealthTlmRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_HealthTlm*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeWheelControlProgram3_HealthTlm);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRef(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRefRequestGw(NODE_ID, (F32*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(F32);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeed(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getWheelSpeedRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_WheelSpeed*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeWheelControlProgram3_WheelSpeed);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getMotorPower(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getMotorPowerRequestGw(NODE_ID, (Boolean*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(Boolean);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getControlMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getControlModeRequestGw(NODE_ID, (TctlmCubeWheelControlProgram3_ControlModeVal*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(TctlmCubeWheelControlProgram3_ControlModeVal);
    return ECPDISPATCHRESULT_RESULT_OK;
}
eCPDispatchResult_t CPCmdHandler_CubeADCS_Gen2_CubeWheelControlProgram3_getBackupWheelMode(sCubeAdcsGen2SrvCtx_t * const pSrvCtx)
{
    API_STATUS = CubeADCS_Gen2_CubeWheelControlProgram3_getBackupWheelModeRequestGw(NODE_ID, (Boolean*)API_DATA_RESP_ADDRESS, CUBEADCS_GEN2_DEFAULT_CRIT_SECTION_TIMEOUT);
    pSrvCtx->u32ResponseActualSize = sizeof(ErrorCode) + sizeof(Boolean);
    return ECPDISPATCHRESULT_RESULT_OK;
}
// CUBE_ADCS_GEN_SECTION_END::HNDL_CODE
