/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_usercmds.c
 * @brief    Implementation of the different commands exposed through the FP layer.
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "assertions.h"
#include "../inc/cubeadcs_usercmds.h"
#include "../cfg/cubeadcs_version.h"
#include "../inc/cubeadcs_errhandl.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
/** @brief Local pointer to user command response context */
static sUserResponseCtx_t *psGSCmdCntx;

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
/*------------------------------------------------------------------------------ */
/*-------------------------- User Commands ---------- -------------------------- */
/*------------------------------------------------------------------------------ */

static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_Generic                     (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_Reset                       (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrErrFlags                 (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_DownloadFileList            (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_PollFileListTransferStatus  (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_StartFileTransfer           (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_PollFileTransferStatus      (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrOBCErrCounters           (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetOBCErrCounters           (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrOBCErrHandlCounters      (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetOBCErrHandlCounters      (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrRunTimeLatchedErrs       (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetRunTimeLatchedErrs       (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrFaultyNode               (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetFaultyNode               (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetOpStatus                 (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetSysState                 (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_SetSysState                 (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetUnixTime                 (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_SetUnixTime                 (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_StopFileTransfer            (CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx);

/** @brief Local array of the commands description - type and function */
static CubeADCS_UsrCmd_CmdDescr aUsrCmdFuncList[] = {
        {.eCmdType = eCUBEADCS_USR_CMDS_GENERIC,                 .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_Generic                      },
        {.eCmdType = eCUBEADCS_USR_CMDS_RESET,                   .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_Reset                        },
        {.eCmdType = eCUBEADCS_USR_CMDS_CLR_LATCHED_ERR_FLAGS,   .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_ClrErrFlags                  },
        {.eCmdType = eCUBEADCS_USR_CMDS_START_FILE_LIST_TRANSFER,.pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_DownloadFileList             },
        {.eCmdType = eCUBEADCS_USR_CMDS_POLL_FILE_LIST_TRANSFER, .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_PollFileListTransferStatus   },
        {.eCmdType = eCUBEADCS_USR_CMDS_START_FILE_TRANSFER,     .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_StartFileTransfer            },
        {.eCmdType = eCUBEADCS_USR_CMDS_POLL_FILE_TRANSFER,      .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_PollFileTransferStatus       },
        {.eCmdType = eCUBEADCS_USR_CMDS_CLR_OBC_ERR_COUNTERS,    .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_ClrOBCErrCounters            },
        {.eCmdType = eCUBEADCS_USR_CMDS_GET_OBC_ERR_COUNTERS,    .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_GetOBCErrCounters            },
        {.eCmdType = eCUBEADCS_USR_CMDS_CLR_FLAG_ERR_COUNTERS,   .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_ClrOBCErrHandlCounters       },
        {.eCmdType = eCUBEADCS_USR_CMDS_GET_FLAG_ERR_COUNTERS,   .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_GetOBCErrHandlCounters       },
        {.eCmdType = eCUBEADCS_USR_CMDS_CLR_RUNTIME_LATCHED_ERR, .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_ClrRunTimeLatchedErrs        },
        {.eCmdType = eCUBEADCS_USR_CMDS_GET_RUNTIME_LATCHED_ERR, .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_GetRunTimeLatchedErrs        },
        {.eCmdType = eCUBEADCS_USR_CMDS_CLR_FAULTY_NODE,         .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_ClrFaultyNode                },
        {.eCmdType = eCUBEADCS_USR_CMDS_GET_FAULTY_NODE,         .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_GetFaultyNode                },
        {.eCmdType = eCUBEADCS_USR_CMDS_GET_OP_STATUS,           .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_GetOpStatus                  },
        {.eCmdType = eCUBEADCS_USR_CMDS_GET_SYSSTATE,            .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_GetSysState                  },
        {.eCmdType = eCUBEADCS_USR_CMDS_SET_SYSSTATE,            .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_SetSysState                  },
        {.eCmdType = eCUBEADCS_USR_CMDS_GET_UNIXTIME,            .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_GetUnixTime                  },
        {.eCmdType = eCUBEADCS_USR_CMDS_SET_UNIXTIME,            .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_SetUnixTime                  },
        {.eCmdType = eCUBEADCS_USR_CMDS_STOP_FILE_TRANSFER,      .pfUsrCmdTypeFunc = fs_CubeADCS_UsrCmd_StopFileTransfer             },
};

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

eCubeADCS_ReqCmd_Status_t CubeADCS_UsrCmd_CmdHandler(eCubeADCS_UsrCmds_Cmds_t eUsrCmd, CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *pUserRespCtx)
{
    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    if ( eCUBEADCS_USR_CMDS_NUMBER > eUsrCmd )
    {
        eRetExecStatus = (*aUsrCmdFuncList[ eUsrCmd ].pfUsrCmdTypeFunc)(sCmd, pUserRespCtx);
    }
    else
    {
    	eRetExecStatus = eCUBEADCS_REQCMD_CMD_ID_ERROR;
    }

    return eRetExecStatus;
}

sUserResponseCtx_t * CubeADCS_UsrCmd_GetContext(void)
{
    return psGSCmdCntx;
}

void CubeADCS_UsrCmd_SetContext(sUserResponseCtx_t *psNewCntx)
{
    psGSCmdCntx = psNewCntx;
}
/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief User command: Generic
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 *
 * @note Used to send a generic command to the CubeADCS
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_Generic(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eCubeADCS_Comm_Status_t eComm;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_ERROR;

    if ( (eCUBEADCS_STATE_IDLE == CubeADCS_GetState() ) &&
            (eCUBEADCS_FTRANSF_STATE_IDLE == CubeADCS_FTransfer_GetTaskState() ) )
    {

        if ( eCUBEADCS_COMM_OK == ( eComm = CubeADCS_SendCmd(sCmd, eCUBEADCS_COMMREQTYPE_FETCH) ) )
        {
        	eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;
        }
    }
    else
    {
        *sCmd->u16CmdResSize = 0x0000;
    }


    if ( NULL != psCntx )
    {
    	commit_buf_direct(psCntx, (uint32_t)(*sCmd->u16CmdResSize));
    }

    return eRetExecStatus;
}

/** @brief User command: Reset
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 *
 * @note Resets the CubeADCS in the requested mode and changes the state of the main CubeADCS task
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_Reset(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

	uint8_t u8Mode;

	eCubeADCS_ReqCmd_Status_t eRetExecStatus;

	u8Mode = *(sCmd->pu8CmdData);

	if ( (eCUBEADCS_MODE_APPLICATION != u8Mode) && (eCUBEADCS_MODE_BOOTLOADER != u8Mode) )
	{
		eRetExecStatus = eCUBEADCS_REQCMD_STATUS_INVALID_ARGS;
	}
	else
	{
		if ( true == cubeadcs_reset(u8Mode) )
		{
			eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;
		}
		else
		{
			eRetExecStatus = eCUBEADCS_REQCMD_STATUS_ERROR;
		}
	}

	return eRetExecStatus;
}

/** @brief User command: Clear Error Flags
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrErrFlags(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    CubeADCS_ClrErrFlags();

    return eCUBEADCS_REQCMD_STATUS_SUCCESS;
}

/** @brief User command: Starts the download of the file list from the CubeADCS OBC SD-card
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_DownloadFileList(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    CubeADCS_FTransf_FListDwn_t sFListDwnReq;

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_ERROR;

    sFListDwnReq.eFListDwnStatus = eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR;

    if ( eCUBEADCS_FTRANSF_REQ_OK == CubeADCS_FTransfer_SetFTransfReq(eCUBEADCS_FTRANSF_REQTYPE_DWN_LIST, NULL, NULL, &sFListDwnReq) )
    {
        osThreadFlagsSet(CubeADCS_FTransfer_GetThreadHandle(), 0x00000001);

        eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;
    }

    return eRetExecStatus;
}

/** @brief User command: Poll file list transfer status
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_PollFileListTransferStatus(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    *((uint8_t *)sCmd->pvCmdResDst) = (uint8_t)CubeADCS_FTransfer_GetFTransfReq().sFListDwn->eFListDwnStatus;

    return eRetExecStatus;
}

/** @brief User command: Start a file transfer between CubeADCS's OBC and Platform OBC
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_StartFileTransfer(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    CubeADCS_FTransf_FDwn_t sFDwnReq;

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_ERROR;

    sFDwnReq.FDwnInfo    = *((CubeADCS_FDwnInfo_t *)sCmd->pu8CmdData);
    sFDwnReq.eFDwnStatus = eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR;

    if ( eCUBEADCS_FTRANSF_REQ_OK == CubeADCS_FTransfer_SetFTransfReq(eCUBEADCS_FTRANSF_REQTYPE_DWN, &sFDwnReq, NULL, NULL) )
    {
        osThreadFlagsSet(CubeADCS_FTransfer_GetThreadHandle(), 0x00000001);

        eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;
    }

    return eRetExecStatus;
}

/** @brief User command: Poll file transfer status
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_PollFileTransferStatus(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    *((uint8_t *)sCmd->pvCmdResDst) = (uint8_t)CubeADCS_FTransfer_GetFTransfReq().sFDwn->eFDwnStatus;

    return eRetExecStatus;
}

/** @brief User command: Clear OBC CubeADCS error counters
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrOBCErrCounters(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    uint8_t u8BaseCntr;
    uint8_t u8TopCntr;

    u8BaseCntr       = *(sCmd->pu8CmdData);
    u8TopCntr        = *(++sCmd->pu8CmdData);

    if ( u8BaseCntr <= u8TopCntr )
    {
        if ( u8TopCntr > (eCUBEADCS_COMMON_DIAG_CNTS_NUMBER - 1) )
        {
        	u8TopCntr = (eCUBEADCS_COMMON_DIAG_CNTS_NUMBER - 1);
        }

        for ( ; u8BaseCntr <= u8TopCntr; ++u8BaseCntr)
        {
        	CubeADCS_Err_Cnts[u8BaseCntr].u16Value = 0;
        }
    }
    else
    {
    	eRetExecStatus = eCUBEADCS_REQCMD_STATUS_INVALID_ARGS;
    }


    return eRetExecStatus;
}

/** @brief User command: Get OBC CubeADCS error counter
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetOBCErrCounters(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    uint16_t *p_dst;

    p_dst  = (uint16_t *)sCmd->pvCmdResDst;

    if ( sCmd->u16CmdResDstSize >= (eCUBEADCS_COMMON_DIAG_CNTS_NUMBER * sizeof(uint16_t)) )
    {
        for (uint8_t u8Indx = 0; u8Indx < eCUBEADCS_COMMON_DIAG_CNTS_NUMBER; ++u8Indx)
        {
            *(p_dst + u8Indx) = CubeADCS_Err_Cnts[u8Indx].u16Value;
        }
    }
    else
    {
        eRetExecStatus = eCUBEADCS_REQCMD_STATUS_INVALID_ARGS;
    }

    return eRetExecStatus;
}

/** @brief User command: Clear OBC Error Handling Counters
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrOBCErrHandlCounters(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    uint8_t u8BaseCntr;
    uint8_t u8TopCntr;

    u8BaseCntr       = *(sCmd->pu8CmdData);
    u8TopCntr        = *(++sCmd->pu8CmdData);

    if ( u8BaseCntr <= u8TopCntr )
    {
        if ( u8TopCntr > (CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM - 1) )
        {
        	u8TopCntr = (CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM - 1);
        }

        for ( ; u8BaseCntr <= u8TopCntr; ++u8BaseCntr)
        {
            CubeADCS_ErrHandl_ClrErrHandlCntrActivCnt(u8BaseCntr);
        }
    }
    else
    {
    	eRetExecStatus = eCUBEADCS_REQCMD_STATUS_INVALID_ARGS;
    }

    return eRetExecStatus;
}

/** @brief User command: Get high severity error flag counters
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetOBCErrHandlCounters(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    uint8_t   u8CntDataSize;
    uint8_t  *u8DstPtr;

    u8DstPtr      = (uint8_t *)sCmd->pvCmdResDst;
    u8CntDataSize = sizeof(uint8_t);

    if ( sCmd->u16CmdResDstSize >= (CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM * u8CntDataSize ) )
    {
        for (uint8_t u8Indx = 0; u8Indx < CUBEADCS_DIAG_ERR_HANDL_CNTS_NUM; ++u8Indx) {
            memcpy(u8DstPtr, CubeADCS_ErrHandl_GetErrHandlCntrActivCnt(u8Indx), u8CntDataSize);
            u8DstPtr += u8CntDataSize;
        }
    }
    else
    {
    	eRetExecStatus = eCUBEADCS_REQCMD_STATUS_INVALID_ARGS;
    }

    return eRetExecStatus;
}

/** @brief User command: Clear runtime latched errors
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrRunTimeLatchedErrs(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    uint16_t deferr = 0x0000;

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    CubeADCS_Status_t sTmpAdcsStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    cubeadcs_persist_get_nvm_stored_status(&sTmpAdcsStatus);

    sTmpAdcsStatus.RunTimeLatchedErrors.u16RawData = deferr;

    if (true != cubeadcs_set_latched_err(&deferr))
    {
    	eRetExecStatus = eCUBEADCS_REQCMD_STATUS_ERROR;
    }

    cubeadcs_persist_set_nvm_stored_status(&sTmpAdcsStatus);

    return eRetExecStatus;
}

/** @brief User command: Get runtime latched errors
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetRunTimeLatchedErrs(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    CubeADCS_Status_t sTmpAdcsStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    cubeadcs_persist_get_nvm_stored_status(&sTmpAdcsStatus);

    *((uint16_t *)sCmd->pvCmdResDst) = sTmpAdcsStatus.RunTimeLatchedErrors.u16RawData;

    return eRetExecStatus;
}

/** @brief User command: Clear faulty node status byte
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_ClrFaultyNode(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    CubeADCS_Status_t sTmpAdcsStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    cubeadcs_persist_get_nvm_stored_status(&sTmpAdcsStatus);

    sTmpAdcsStatus.NodeStatus.u8RawData = 0x00;

    cubeadcs_persist_set_nvm_stored_status(&sTmpAdcsStatus);

    return eRetExecStatus;
}

/** @brief User command: Get faulty node status byte
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetFaultyNode(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    CubeADCS_Status_t sTmpAdcsStatus;

    cubeadcs_persist_get_nvm_stored_status(&sTmpAdcsStatus);

    *((uint8_t *)sCmd->pvCmdResDst) = sTmpAdcsStatus.NodeStatus.u8RawData;

    return eRetExecStatus;
}

/** @brief User command: Get the CubeADCS operational status
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetOpStatus(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    CubeADCS_Op_Status_t sTmpOpsStatus;

    eCubeADCS_ReqCmd_Status_t eRetExecStatus;

    eRetExecStatus = eCUBEADCS_REQCMD_STATUS_ERROR;

    if ( true == cubeadcs_get_op_status(&sTmpOpsStatus) )
    {
        memcpy(sCmd->pvCmdResDst, (void *)&sTmpOpsStatus, sizeof(sTmpOpsStatus));
        eRetExecStatus = eCUBEADCS_REQCMD_STATUS_SUCCESS;
    }

    return eRetExecStatus;
}

/** @brief User command: Get the current system state
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetSysState(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    cubeadcs_get_adcs_state_cfg((CubeADCS_SysSCfg_t *)sCmd->pvCmdResDst);

    return eCUBEADCS_REQCMD_STATUS_SUCCESS;
}

/** @brief User command: Set a new system state
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_SetSysState(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_CfgType eNewCfg;

    eNewCfg = *sCmd->pu8CmdData;

    cubeadcs_set_state_cfg(eNewCfg, CUBEADCS_EXEC_STATE_REQ);

    return eCUBEADCS_REQCMD_STATUS_SUCCESS;
}

/** @brief User command: Get current UNIX time
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_GetUnixTime(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRet;

    eRet = eCUBEADCS_REQCMD_STATUS_ERROR;

    if ( eCUBEADCS_STDRPLY_OK == cubeadcs_get_unix_time((CubeADCS_UnixTime_t *)sCmd->pvCmdResDst))
    {
    	eRet = eCUBEADCS_REQCMD_STATUS_SUCCESS;
    }

    return eRet;

}

/** @brief User command: Set new UNIX time
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_SetUnixTime(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
	CRIT_ASSERT(NULL != sCmd);

    eCubeADCS_ReqCmd_Status_t eRet;

    eRet = eCUBEADCS_REQCMD_STATUS_ERROR;

    if ( eCUBEADCS_STDRPLY_OK == cubeadcs_update_unix_time((CubeADCS_UnixTime_t *)sCmd->pu8CmdData))
    {
    	eRet = eCUBEADCS_REQCMD_STATUS_SUCCESS;
    }

    return eRet;
}

/** @brief User command: Stop ongoing file transfer
 *
 * @param[in] sCmd pointer to command details (context)
 * @param[in] psCntx pointer to response context (ESPS)
 *
 * @return command request status after execution
 */
static eCubeADCS_ReqCmd_Status_t fs_CubeADCS_UsrCmd_StopFileTransfer(CubeADCS_CmdCfg_t *sCmd, sUserResponseCtx_t *psCntx)
{
    eCubeADCS_ReqCmd_Status_t eRet;

    CubeADCS_FTransfer_StopOngoingFTransfer();

    eRet = eCUBEADCS_REQCMD_STATUS_SUCCESS;

    return eRet;
}

/* ******************************************************************************************* */
