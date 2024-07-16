/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __ESCP_COMMANDS_LOCAL_CONF_H__
#define __ESCP_COMMANDS_LOCAL_CONF_H__

/**
 * @addtogroup cp
 * @{
 *
 * @file    ESCP_CommandsLocalConf.h
 * @brief   CP protocol ESPS Stack configuration
 *
 * @}
 */

#include "CP_SX_Band_Commands.h"
#include "S_X_Band_Trnsm.h"
#include "CP_CubeADCS_Gen2_Commands.h"
#include "CP_Fault_Commands.h"
#ifdef __CP_HANDLER_C__
#include "cp/cp_cmd_handler.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Local Command Protocol - Commands configuration file.
// This file has to be copied on every module firmware
// and should not be included anywhere, just copy it in project dir.
// Configuration should be made depending from module needs.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OnESCP_CommandReceived(uint64_t nCmdID, uint32_t nCmdType, uint8_t *pCMDPkt, uint32_t nCMDPktSize);
void OnESCP_CmdCancelRequest(uint64_t nCmdID, uint32_t nCmdType);

//------------------------------------------------------------------------------------------------------------
// Command Protocol Parameters
// For ESCP_MAX_IN_PACKET_SIZE, ensure we have min of 100 bytes more than what we need,
// so extensions to protocol headers can be handled correctly
#define ESCP_MAX_INOUT_PACKET_SIZE_DEFAULT       (1024)

// The in/out max packet size shall be able to accommodate S-/X-band gateway packet size
//  ignore the default size definition ESCP_MAX_INOUT_PACKET_SIZE_DEFAULT
#define ESCP_MAX_IN_PACKET_SIZE                 (S_X_BAND_TRNSM_TX_BUFF_SIZE)
#define ESCP_MAX_OUT_PACKET_SIZE                (S_X_BAND_TRNSM_RX_BUFF_SIZE)

//------------------------------------------------------------------------------------------------------------
// Command Identifiers
#define CP_CMD_FAULT_READ_ALL                    ((uint16_t) 1027)
// RESERVED - 1028
#define CP_CMD_SXBAND_GWSEND                     ((uint16_t) 1200)
#define CP_CMD_CUBEADCS_GWSEND                   ((uint16_t) 1202)
#define CP_CMD_MACFP_GWSEND                      ((uint16_t) 1212)
#define CP_CMD_DBG_DOWNLOADFILE                  ((uint16_t) 1450)
#if defined(SXBAND_SCHEDULER_ENABLED)
#define CP_CMD_SXBAND_SCHED_RUN                  ((uint16_t) 1451)
#define CP_CMD_SXBAND_SCHED_POLL                 ((uint16_t) 1452)
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)

#if defined(CUBEADCS_GEN2_ENABLED)
#define CP_CMD_CUBEADCS_GEN2_GWSEND              ((uint16_t) 2000)
#endif // #if defined(CUBEADCS_GEN2_ENABLED)


//------------------------------------------------------------------------------------------------------------
// Static configuration of supported commands, here configuration should be made

#ifdef __ESTL_CP_MOD_DRV_C__ // Do not remove

// To add new command need to use ESTL_CP_REGISTER_COMMAND(commandID, CmdReceivedCbk, CmdCancelCbk) macro
// between ESTL_CP_BEGIN_COMMAND_MAP() and ESTL_CP_END_COMMAND_MAP()

// ESTL_CP_BEGIN_COMMAND_MAP() has to be used without arguments

// ESTL_CP_REGISTER_COMMAND(commandID, CmdReceivedCbk, CmdCancelCbk) has to be used with 3 arguments:
// first is actual command type ID.
// second is callback that will be called on successfully command received
// third is callback that will be called on cancelled command

// ESTL_CP_END_COMMAND_MAP() has to be used without arguments

// IMPORTANT: Commands registered with ESTL_CP_REGISTER_COMMAND must be listed in ascending order by their command type IDs
// this is necessary, because commands are searched with binary search from an array, and if the array is not sorted, the search will fail.

// For reference see below:

ESTL_CP_BEGIN_COMMAND_MAP()
ESTL_CP_REGISTER_COMMAND(CP_CMD_FAULT_READ_ALL,                 OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
ESTL_CP_REGISTER_COMMAND(CP_CMD_SXBAND_GWSEND,                  OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
ESTL_CP_REGISTER_COMMAND(CP_CMD_CUBEADCS_GWSEND,                OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
ESTL_CP_REGISTER_COMMAND(CP_CMD_MACFP_GWSEND,                   OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
ESTL_CP_REGISTER_COMMAND(CP_CMD_DBG_DOWNLOADFILE,               OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
#if defined(SXBAND_SCHEDULER_ENABLED)
ESTL_CP_REGISTER_COMMAND(CP_CMD_SXBAND_SCHED_RUN,               OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
ESTL_CP_REGISTER_COMMAND(CP_CMD_SXBAND_SCHED_POLL,              OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
#endif     // #if defined(SXBAND_SCHEDULER_ENABLED)

#if defined(CUBEADCS_GEN2_ENABLED)
ESTL_CP_REGISTER_COMMAND(CP_CMD_CUBEADCS_GEN2_GWSEND,           OnESCP_CommandReceived, OnESCP_CmdCancelRequest)
#endif // #if defined(CUBEADCS_GEN2_ENABLED)
ESTL_CP_END_COMMAND_MAP()

#endif // __ESTL_CP_MOD_DRV_C__

#ifdef __CP_HANDLER_C__
// High-level CP dispatch configuration:
// For each command registered above, a corresponding handler is needed here

ESTL_CP_HANDLER_BEGIN_COMMAND_MAP()
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_FAULT_READ_ALL,                cp_fault_commands_read_all_faults)
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_SXBAND_GWSEND,                 CPCmdHandler_SXBand_GwSendCmd)
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_CUBEADCS_GWSEND,               cp_cmd_handler_cubeadcs_gw_send_cmd)
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_MACFP_GWSEND,                  cp_cmd_handler_mac_fp_gw_send_cmd)
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_DBG_DOWNLOADFILE,              cp_cmd_handler_download_file)
#if defined(SXBAND_SCHEDULER_ENABLED)
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_SXBAND_SCHED_RUN,              CPCmdHandler_SXBand_Sched_Run)
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_SXBAND_SCHED_POLL,             CPCmdHandler_SXBand_Sched_Poll)
#endif     // #if defined(SXBAND_SCHEDULER_ENABLED)

#ifdef CUBEADCS_GEN2_ENABLED
ESTL_CP_HANDLER_REGISTER_COMMAND(CP_CMD_CUBEADCS_GEN2_GWSEND,          CPCmdHandler_CubeADCS_Gen2_GwSendCmd)
#endif // CUBEADCS_GEN2_ENABLED

ESTL_CP_HANDLER_END_COMMAND_MAP()
#endif  // __CP_HANDLER_C__

// End of static configuration
//------------------------------------------------------------------------------------------------------------

#endif // __ESCP_COMMANDS_LOCAL_CONF_H__
