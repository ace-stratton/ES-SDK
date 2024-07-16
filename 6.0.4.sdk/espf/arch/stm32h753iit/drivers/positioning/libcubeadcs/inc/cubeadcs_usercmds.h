/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CUBEADCS_USER_CMDS_H_
#define CUBEADCS_USER_CMDS_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_usercmds.h
 * @brief    Interface for the user commands. Used internally by the CubeADCS logic.
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "cubeadcs.h"
#include "DataSink.h"
/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/
/** @brief Enumeration of the user commands. These are commands exposed through a dedicated fidl file
 *
 *  @note Order is important! Do not change it, just extend.
 */
typedef enum tag_eCubeADCS_UsrCmds_Cmds
{
    eCUBEADCS_USR_CMDS_GENERIC,
    eCUBEADCS_USR_CMDS_RESET,
    eCUBEADCS_USR_CMDS_CLR_LATCHED_ERR_FLAGS,
    eCUBEADCS_USR_CMDS_START_FILE_LIST_TRANSFER,
    eCUBEADCS_USR_CMDS_POLL_FILE_LIST_TRANSFER,
    eCUBEADCS_USR_CMDS_START_FILE_TRANSFER,
    eCUBEADCS_USR_CMDS_POLL_FILE_TRANSFER,
    eCUBEADCS_USR_CMDS_CLR_OBC_ERR_COUNTERS,
    eCUBEADCS_USR_CMDS_GET_OBC_ERR_COUNTERS,
    eCUBEADCS_USR_CMDS_CLR_FLAG_ERR_COUNTERS,
    eCUBEADCS_USR_CMDS_GET_FLAG_ERR_COUNTERS,
    eCUBEADCS_USR_CMDS_CLR_RUNTIME_LATCHED_ERR,
    eCUBEADCS_USR_CMDS_GET_RUNTIME_LATCHED_ERR,
    eCUBEADCS_USR_CMDS_CLR_FAULTY_NODE,
    eCUBEADCS_USR_CMDS_GET_FAULTY_NODE,
    eCUBEADCS_USR_CMDS_GET_OP_STATUS,
	eCUBEADCS_USR_CMDS_GET_SYSSTATE,
	eCUBEADCS_USR_CMDS_SET_SYSSTATE,
	eCUBEADCS_USR_CMDS_GET_UNIXTIME,
	eCUBEADCS_USR_CMDS_SET_UNIXTIME,
	eCUBEADCS_USR_CMDS_STOP_FILE_TRANSFER,
    eCUBEADCS_USR_CMDS_NUMBER,

} eCubeADCS_UsrCmds_Cmds_t;

/** @brief Function pointer to a user command implementation
 *
 *  @param[in/out] command details, destination pointers, etc.
 *  @param[in] reply context (ESPS)
 *
 *  @return command request status after execution
 */
typedef eCubeADCS_ReqCmd_Status_t (*UsrCmdTypeFuncPtr)(CubeADCS_CmdCfg_t *, sUserResponseCtx_t *);

/** @brief Command description type, contains command type and pointer to actual command implementation
 */
typedef struct tag_CubeADCS_UsrCmds_CmdDescr {
    eCubeADCS_UsrCmds_Cmds_t eCmdType;
    UsrCmdTypeFuncPtr pfUsrCmdTypeFunc;
} __attribute__((__packed__)) CubeADCS_UsrCmd_CmdDescr;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/
/** @brief Command handler of the user commands
 *
 *  @param[in] eUsrCmd command type
 *  @param[in] sCmd pointer to command details (context)
 *  @param[in] pUserRespCtx pointer to response context (ESPS)
 *
 *  @return command request status after execution
 */
eCubeADCS_ReqCmd_Status_t CubeADCS_UsrCmd_CmdHandler(eCubeADCS_UsrCmds_Cmds_t eUsrCmd, CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *pUserRespCtx);

/** @brief Get user command context
 *
 *  @return command context
 */
sUserResponseCtx_t *CubeADCS_UsrCmd_GetContext(void);

/** @brief Set user command context
 *
 *	@param[in] psNewCntx the new user command context
 */
void CubeADCS_UsrCmd_SetContext(sUserResponseCtx_t *psNewCntx);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif    /* CUBEADCS_USER_CMDS_H_ */
/* ******************************************************************************************* */
