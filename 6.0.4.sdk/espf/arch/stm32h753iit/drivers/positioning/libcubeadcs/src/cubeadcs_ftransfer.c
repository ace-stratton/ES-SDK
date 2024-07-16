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
 * @file     cubeadcs_ftransf.c
 * @brief    Implementation of the procedures for file downloads and file-list downloads.
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/

#include <string.h>
#include "SdMngr.h"

#include "../inc/cubeadcs_ftransfer.h"
#include "../inc/cubeadcs.h"
#include "../inc/cubeadcs_crc.h"

#include "assertions.h"


/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
/** @brief Size in bytes of the packets send during a file download */
#define CUBEADCS_FDWN_BURST_PACKET_SIZE     ((uint16_t)20)
/** @brief Maximum hole map count in a burst - 1024 means 1024 packets were not received */
#define CUBEADCS_FDWN_HOLE_MAP_MAX_CNT      ((uint16_t)1024)
/** @brief Maximum number of packets in a burst */
#define CUBEADCS_FDWN_MAX_PKT_CNT			CUBEADCS_FDWN_HOLE_MAP_MAX_CNT
/** @brief Size in bytes of a whole map section (there are a total of 8 hole map sections) */
#define CUBEADCS_FDWN_HOLE_MAP_BYTE_LEN     ((uint8_t)128)

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/** @brief Associate file types to file constants */
enum
{
	FILE_TYPE_TLM,
	FILE_TYPE_JPG,
	FILE_TYPE_BMP,
	FILE_TYPE_IND,

	FILE_TYPE_MAX

};

/** @brief File download operation parameters */
typedef struct tag_FDwn_OpParams
{
    char cFName[16];

    CubeADCS_TC_112_t FDwnBlock;

    uint32_t u32FPktCnt;

    uint8_t u8HoleMap [ CUBEADCS_FDWN_HOLE_MAP_BYTE_LEN ];

    CubeADCS_TC_119_t sDwnBurstCmd;

    uint32_t u32HoleMapCnt;
    uint16_t u16BurstHoleMapCnt;

    FSIZE_t  u32FileSize;

} FDwn_OpParams_t;

/** @brief Function pointer (immutable) type applicable for all the separate file download related functions */
typedef void (* const pFDownFunc)(void);
/** @brief Function pointer type applicable for all the separate file download related functions */
typedef void (* ppFDownFunc)(void);

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

/** @brief Local cache of the file download request */
static CubeADCS_FTransf_FDwn_t      sFileReqMsg;
/** @brief Local cache of the file upload request */
static CubeADCS_FTransf_FUp_t       sFileUpReqMsg;
/** @brief Local cache of the file-list download request */
static CubeADCS_FTransf_FListDwn_t  sFileListReqMsg;
/** @brief Local cache of all requests */
static CubeADCS_FTransf_t           sFTransfMsg = {
        .eReqType  = eCUBEADCS_FTRANSF_REQTYPE_NONE,
        .sFDwn     = &sFileReqMsg,
        .sFUp      = &sFileUpReqMsg,
        .sFListDwn = &sFileListReqMsg,
};

/** @brief Task handle */
static       osThreadId_t   CubeADCS_FTransf_TaskHandle;
/** @brief Task attributes */
static const osThreadAttr_t CubeADCS_FTransf_TaskAttr = {
  .name = "fs_CubeADCS_FTransfTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 4096
};

/** @brief File handling specific constants */
static const char *pccFTypes[FILE_TYPE_MAX] = {"Tlm",
                                  "Jpg",
                                  "Bmp",
                                  "Ind",
                                  };

/** @brief File extensions */
static const char *ccFTypeExt[] = {".txt",
                                   ".jpg",
                                   ".bmp",
                                   };

/** @brief File-list name as stored on the OBC SD-card */
static const char ccFListName[] = "CSFLIST.txt";

/** @brief File handling task state */
static eCubeADCS_FTransf_State_t eCubeADCS_FTransTaskState;

/** @brief File download transfer functions array and pointer to it */
static ppFDownFunc spFDownF;

/** @brief FileList download functions array and pointer to it */
static ppFDownFunc spDownFList;

/** @brief File download transfer operation parameters cache */
static FDwn_OpParams_t sFDwn_P;

/** @brief File Object cache */
static FIL sFDwnObj;

/** @brief Burst attempt counter during state poll dwn burst */
static uint8_t burstCnt;

/** @brief Stop requested cache used by the file transfers and user */
static bool is_ftransf_stop_requested;

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

static void                         fs_CubeADCS_FTransfer_FHandlTask(void *argument);
static void                         fs_CubeADCS_FTransfer_CreateFileName(char *pcFullFileName, const uint8_t buf_size);
static eCubeADCS_StdRply            fs_CubeADCS_FTransfer_CalcSavedBlockCRC16(uint16_t *pu16Cache, FIL *psFDwnObj, char * pcFName, uint32_t u32Len);

static void                         fs_CubeADCS_FTransfer_DownloadFile(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_Init(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_Cfg(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_LoadBlock(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_PollBlockRdy(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_StartDwnBurst(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_PollDwnBurst(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_CheckFTransfStatus(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_Done(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_Err(void);
static void                         fs_CubeADCS_FTransfer_DownloadFile_End(void);

static void                         fs_CubeADCS_FTransfer_DownloadFileList(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_Init(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_Rst(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_FileInfo(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_Wait(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_Advance(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_Done(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_Err(void);
static void                         fs_CubeADCS_FTransfer_DownloadFileList_End(void);

static eCubeADCS_StdRply            fs_CubeADCS_FTransfer_SendCmdWithRpt(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_CommReqType_t eCommReqType, uint8_t u8RptNumber);
static void                         fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCubeADCS_FTransf_Fhandl_t eNewStatus);
static void                         fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCubeADCS_FTransf_FDwnState_t eNewStatus);

static void                         fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCubeADCS_FTransf_DwnFListState_t eNewStatus);

/** @brief Array of function pointers to the separate file download steps */
static pFDownFunc scaFDownFArray[eCUBEADCS_FTRANSF_FDWNSTATE_CNT] = {
        fs_CubeADCS_FTransfer_DownloadFile_Init,
        fs_CubeADCS_FTransfer_DownloadFile_Cfg,
        fs_CubeADCS_FTransfer_DownloadFile_LoadBlock,
        fs_CubeADCS_FTransfer_DownloadFile_PollBlockRdy,
        fs_CubeADCS_FTransfer_DownloadFile_StartDwnBurst,
        fs_CubeADCS_FTransfer_DownloadFile_PollDwnBurst,
        fs_CubeADCS_FTransfer_DownloadFile_CheckFTransfStatus,
        fs_CubeADCS_FTransfer_DownloadFile_Done,
        fs_CubeADCS_FTransfer_DownloadFile_Err,
        fs_CubeADCS_FTransfer_DownloadFile_End};

/** @brief Array of function pointers to the separate file-list download steps */
static pFDownFunc scaDownFListArray[eCUBEADCS_FTRANSF_DWNFLIST_CNT] = {
        fs_CubeADCS_FTransfer_DownloadFileList_Init,
        fs_CubeADCS_FTransfer_DownloadFileList_Rst,
        fs_CubeADCS_FTransfer_DownloadFileList_FileInfo,
        fs_CubeADCS_FTransfer_DownloadFileList_Wait,
        fs_CubeADCS_FTransfer_DownloadFileList_Advance,
        fs_CubeADCS_FTransfer_DownloadFileList_Done,
        fs_CubeADCS_FTransfer_DownloadFileList_Err,
        fs_CubeADCS_FTransfer_DownloadFileList_End};

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void CubeADCS_FTransfer_TaskInit(void)
{
    /* Create the CubeADCS file centred task */
    CubeADCS_FTransf_TaskHandle = osThreadNew(fs_CubeADCS_FTransfer_FHandlTask, NULL, &CubeADCS_FTransf_TaskAttr);
    CRIT_ASSERT( CubeADCS_FTransf_TaskHandle );

    TaskMonitor_TaskInitialized(TASK_MONITOR_CUBEADCS_FHANDL);

    eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_IDLE;

    fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_INIT);

    fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_INIT);
}

osThreadId_t CubeADCS_FTransfer_GetThreadHandle(void)
{
    return CubeADCS_FTransf_TaskHandle;
}

eCubeADCS_FTransf_State_t CubeADCS_FTransfer_GetTaskState(void)
{
    return eCubeADCS_FTransTaskState;
}

CubeADCS_FTransf_t CubeADCS_FTransfer_GetFTransfReq(void)
{
    return sFTransfMsg;
}

void CubeADCS_FTransfer_StopOngoingFTransfer(void)
{
	is_ftransf_stop_requested = true;
}

eCubeADCS_FTransf_Req_t CubeADCS_FTransfer_SetFTransfReq(eCubeADCS_FTransf_ReqType_t eReqType, CubeADCS_FTransf_FDwn_t * psFDwnReq, CubeADCS_FTransf_FUp_t * psFUpReq, CubeADCS_FTransf_FListDwn_t * psFListDwnReq)
{
    eCubeADCS_FTransf_Req_t eReqStatus;

    eReqStatus = eCUBEADCS_FTRANSF_REQ_FAIL_TRANSF_ONGOING;

    if ( eCUBEADCS_FTRANSF_STATE_IDLE == CubeADCS_FTransfer_GetTaskState() )
    {
        if ( eCUBEADCS_MODE_INVALID != CubeADCS_GetNodeType() )
        {
            if ( (eCUBEADCS_FTRANSF_REQTYPE_DWN == eReqType) && (NULL != psFDwnReq) ) {
                *sFTransfMsg.sFDwn   = *psFDwnReq;
                sFTransfMsg.eReqType = eCUBEADCS_FTRANSF_REQTYPE_DWN;
                eReqStatus           = eCUBEADCS_FTRANSF_REQ_OK;
            }
            else if ( (eCUBEADCS_FTRANSF_REQTYPE_UP == eReqType) && (NULL != psFUpReq) ) {
                *sFTransfMsg.sFUp    = *psFUpReq;
                sFTransfMsg.eReqType = eCUBEADCS_FTRANSF_REQTYPE_UP;
                eReqStatus           = eCUBEADCS_FTRANSF_REQ_OK;
            }
            else if ( (eCUBEADCS_FTRANSF_REQTYPE_DWN_LIST == eReqType) && (NULL != psFListDwnReq) ) {
                *sFTransfMsg.sFListDwn = *psFListDwnReq;
                sFTransfMsg.eReqType   = eCUBEADCS_FTRANSF_REQTYPE_DWN_LIST;
                eReqStatus             = eCUBEADCS_FTRANSF_REQ_OK;
            }
            else
            {
            	eReqStatus = eCUBEADCS_FTRANSF_REQ_FAIL_BAD_REQ;
            }
        }
        else
        {
        	eReqStatus = eCUBEADCS_FTRANSF_REQ_FAIL_NO_ADCS;
        }
    }

    return eReqStatus;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/** @brief CubeADCS File Transfer Handle Task
 *
 * 	@param[in] the task arguments
 */
static void fs_CubeADCS_FTransfer_FHandlTask(void *arg)
{
    for(;;)
    {
        switch (eCubeADCS_FTransTaskState)
        {
            case eCUBEADCS_FTRANSF_STATE_IDLE:

                CUBEADCS_TRACE_DBG("eCUBEADCS_FTRANSF_STATE_IDLE\r");

                CubeADCS_DelayTask(CUBEADCS_TASK_IDLE_DELAY_MS); //todo VVS - this doesnt look right, task will be kicked along with the other one

                if ( eCUBEADCS_FTRANSF_REQTYPE_DWN == sFTransfMsg.eReqType )
                {
                	eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_DWN;
                }
                else if ( eCUBEADCS_FTRANSF_REQTYPE_UP == sFTransfMsg.eReqType )
                {
                	eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_UP;
                }
                else if ( eCUBEADCS_FTRANSF_REQTYPE_DWN_LIST == sFTransfMsg.eReqType )
                {
                	eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_DWN_LIST;
                }

                is_ftransf_stop_requested = false;

                break;

            case eCUBEADCS_FTRANSF_STATE_DWN:

                CUBEADCS_TRACE_DBG("eCUBEADCS_FTRANSF_STATE_DWN\r");

                fs_CubeADCS_FTransfer_DownloadFile();

                break;

            case eCUBEADCS_FTRANSF_STATE_UP:

                eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_IDLE;

                break;

            case eCUBEADCS_FTRANSF_STATE_DWN_LIST:

                fs_CubeADCS_FTransfer_DownloadFileList();

                break;

            default:
                EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS_FHANDL, eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR, __LINE__);

                eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_IDLE;

                break;
        }

        TaskMonitor_IamAlive(TASK_MONITOR_CUBEADCS_FHANDL);
        vApplicationLowStackCheck(TASK_MONITOR_CUBEADCS_FHANDL);
    }
}

/** @brief Invoke next file download step */
static void fs_CubeADCS_FTransfer_DownloadFile()
{
    (*spFDownF)();
}

/** @brief Initialisation sequence for File Transfers - Downloading file
 *
 *	@note No check whether there is enough space on the SD-Card is performed !
 */
static void fs_CubeADCS_FTransfer_DownloadFile_Init()
{
    CUBEADCS_TRACE_DBG("FDWN_________INIT\r");

    burstCnt = 0;

    sFDwn_P.FDwnBlock.u32Offset   = 0;
    sFDwn_P.u32HoleMapCnt         = 0;
    sFDwn_P.u32FPktCnt            = (sFTransfMsg.sFDwn->FDwnInfo.u32FileSize % CUBEADCS_FDWN_BURST_PACKET_SIZE) == 0 ?
                                    (sFTransfMsg.sFDwn->FDwnInfo.u32FileSize / CUBEADCS_FDWN_BURST_PACKET_SIZE) :
                                    (sFTransfMsg.sFDwn->FDwnInfo.u32FileSize / CUBEADCS_FDWN_BURST_PACKET_SIZE) + 1;

    fs_CubeADCS_FTransfer_CreateFileName(&sFDwn_P.cFName[0], sizeof(sFDwn_P.cFName));

    fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_BUSY);

    fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);

    if ( SDMNGR_CARD_STATE_READY == SdMngr_GetCardState()) {
    	if ( FR_OK == SdMngr_f_open(&sFDwnObj, &sFDwn_P.cFName[0], FA_WRITE | FA_CREATE_ALWAYS) ) {
    		(void)SdMngr_f_close(&sFDwnObj);
    		fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_CFG);
    	}
    	else {
    		fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
    	}
    }
    else {
    	fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
    }
}

/** @brief Configuration sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_Cfg()
{
    CUBEADCS_TRACE_DBG("FDWN_________CFG\r");

    /* Configure CubeADCS command */
    sFDwn_P.FDwnBlock.eFType      = sFTransfMsg.sFDwn->FDwnInfo.eFType;
    sFDwn_P.FDwnBlock.u8Counter   = sFTransfMsg.sFDwn->FDwnInfo.u8Cnt;
    sFDwn_P.FDwnBlock.u16BlockLen = 0x5000;     /* 1024 * 20 */

    /* Clear hole map */
    memset(&sFDwn_P.u8HoleMap[0], 0x00, CUBEADCS_FDWN_HOLE_MAP_BYTE_LEN);

    /* Set initial burst configuration */
    sFDwn_P.sDwnBurstCmd.MessageLen     = 0x14;
    sFDwn_P.sDwnBurstCmd.IgnoreHoleMap  = pdTRUE;

    fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_LOAD_FILE_DWN_BLOCK);
}

/** @brief Load File Download Block sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_LoadBlock()
{
    CUBEADCS_TRACE_DBG("FDWN_________LOAD_BLOCK\r");

    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmd_LoadFileDwnBlock;

    CubeADCS_PREPCmd(&sCmd_LoadFileDwnBlock, eCUBEADCS_CMD_ID_112, (uint8_t *)&sFDwn_P.FDwnBlock, sizeof(CubeADCS_TC_112_t), (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    if ( true == is_ftransf_stop_requested )
    {
    	fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_STOPPED);
    	fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_END);
    }
    else
    {

    	fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_POLL_DWN_BLOCK_RDY);

    	/* Perform 3 retries before giving up */
    	if ( eCUBEADCS_STDRPLY_OK != fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_LoadFileDwnBlock, eCUBEADCS_COMMREQTYPE_FETCH, CUBEADCS_FTRANSF_FDWN_RPT) )
    	{
    		fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
    		fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
    	}
    }
}

/** @brief Poll Download Block Ready sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_PollBlockRdy(void)
{
    CUBEADCS_TRACE_DBG("FDWN_________POLL\r");

    uint16_t u16CmdRspLen;

    eCubeADCS_TLM242_t sCmdRsp;

    CubeADCS_CmdCfg_t sCmd_PollDwnBlockRdy;

    CubeADCS_PREPCmd(&sCmd_PollDwnBlockRdy, eCUBEADCS_CMD_ID_242, NULL, 0, (void *)&sCmdRsp, CUBEADCS_TLM242_LEN, &u16CmdRspLen);

    for (uint8_t u8PollDwnRtrCnt = 0; u8PollDwnRtrCnt <= CUBEADCS_FTRANSF_FDWN_RPT_CNT_POLL; ++u8PollDwnRtrCnt )
    {
        CUBEADCS_TRACE_DBG("FDWN_________POLL____----%02X\r", u8PollDwnRtrCnt);

        if ( eCUBEADCS_STDRPLY_OK != fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_PollDwnBlockRdy, eCUBEADCS_COMMREQTYPE_FETCH, CUBEADCS_FTRANSF_FDWN_RPT) )
        {
            fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
            fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);

            break;
        }
        else
        {
            if ( pdTRUE == sCmdRsp.TLM242.Byte0.u8RawData ) {
                fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_START_DWN_BURST);

                sFDwn_P.u32FileSize  = sFDwn_P.FDwnBlock.u32Offset;

                break;
            }
            else
            {
                if ( u8PollDwnRtrCnt == CUBEADCS_FTRANSF_FDWN_RPT_CNT_POLL )
                {
                	fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
                }
                else
                {
                	osDelay(50);
                }
            }
        }
    }
}

/** @brief Start Download Burst sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_StartDwnBurst(void)
{
    CUBEADCS_TRACE_DBG("FDWN_________START_DWN\r");

    uint16_t u16CmdRspLen;

    eCubeADCS_TLM119_t sDwnBurstCmdRply;

    CubeADCS_CmdCfg_t sCmd_DwnBurstCmd;

    CubeADCS_PREPCmd(&sCmd_DwnBurstCmd, eCUBEADCS_CMD_ID_119, (uint8_t *)&sFDwn_P.sDwnBurstCmd, sizeof(CubeADCS_TC_119_t), (void *)&sDwnBurstCmdRply, sizeof(eCubeADCS_TLM119_t), &u16CmdRspLen);

    fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_POLL_BURST_STATUS);

    cubeadcs_driver_set_dma_cfg(true);
    cubeadcs_driver_init_uart();

    if ((++burstCnt > CUBEADCS_FTRANSG_FDWN_BURST_MAX_RETRY) ||
    		(eCUBEADCS_STDRPLY_OK != fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_DwnBurstCmd, eCUBEADCS_COMMREQTYPE_TX_ONLY, CUBEADCS_FTRANSF_FDWN_RPT)) ||
			(FR_OK != SdMngr_f_open(&sFDwnObj, &sFDwn_P.cFName[0], FA_WRITE | FA_OPEN_APPEND)))
    {
    	cubeadcs_driver_set_dma_cfg(false);
    	cubeadcs_driver_init_uart();

    	fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
    	fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
    }
}

/** @brief Poll Burst Status sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_PollDwnBurst(void)
{
	CUBEADCS_TRACE_DBG("FDWN_________------------------POLL_DWN_BURST\r");

	uint8_t           u8PktData[CUBEADCS_TLM255_LEN];
	uint32_t          u32WrtCnt;

	eCubeADCS_Comm_Status_t retStatus;
	CubeADCS_CmdCfg_t sCmd_DwnPkt;
	uint16_t          u16CmdRspLen;

	tQueue *p_cubeadcs_proc_queue;

	uint8_t const *p_base_address;

	CubeADCS_PREPCmd(&sCmd_DwnPkt, eCUBEADCS_CMD_ID_255_CUSTOM, NULL, 0, (void *)&u8PktData[0], CUBEADCS_TLM255_LEN, &u16CmdRspLen);

	for ( uint8_t rpt = 0; rpt < 3; ++rpt )
	{
		retStatus = CubeADCS_SendCmd(&sCmd_DwnPkt, eCUBEADCS_COMMREQTYPE_RX_FDWN);
		if ( (eCUBEADCS_COMM_OK == retStatus) || (eCUBEADCS_COMM_COMM_ERR == retStatus) )
		{
			break;
		}
	}

	CUBEADCS_TRACE_DBG("----RET_STATUS:%02X\r", retStatus);

	switch (retStatus)
	{
	case eCUBEADCS_COMM_ERR:
	case eCUBEADCS_COMM_LEN_WRT_ERR:
	case eCUBEADCS_COMM_CMD_ERR:
		fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);

		break;
	case eCUBEADCS_COMM_COMM_ERR:

		fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_START_DWN_BURST);

		break;

	case eCUBEADCS_COMM_OK:
	case eCUBEADCS_COMM_RX_TIMEOUT:

		if ( eCUBEADCS_COMM_RX_TIMEOUT == retStatus )
		{
			p_cubeadcs_proc_queue = cubeadcs_driver_get_buffer_in_use();
		}
		else
		{
			p_cubeadcs_proc_queue = cubeadcs_driver_get_buffer_not_in_use();
		}

		for (uint8_t pkt = 0; pkt < (p_cubeadcs_proc_queue->tail / CUBEADCS_TLM255_LEN) ; pkt++)
		{
			p_base_address = p_cubeadcs_proc_queue->data + (pkt * CUBEADCS_TLM255_LEN);

			/* Pkt number in burst */
			uint16_t u16Pkt = (uint16_t)(((uint16_t)(*(p_base_address + 2))) << 8) + *(p_base_address + 1);

			sFDwn_P.u8HoleMap[(uint8_t)(u16Pkt / 8)] |= 1 << (uint16_t)(u16Pkt % 8);

			/* Exit the file transfer sequence if the decoded packet number is invalid or if a file manager operation has failed */
			if ( (u16Pkt >= CUBEADCS_FDWN_MAX_PKT_CNT) ||
					(FR_OK != SdMngr_f_lseek(&sFDwnObj, (sFDwn_P.u32FileSize + ((FSIZE_t)u16Pkt * 0x14)))) ||
					((FR_OK != SdMngr_f_write(&sFDwnObj, (p_base_address + 3), 0x14, (UINT*)&u32WrtCnt)) || (u32WrtCnt != 0x14)) )
			{
				fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_START_DWN_BURST);

				break;
			}

			//todo VVS: there should be some logic here to escape the case when the pkt failure occurs ?
		}

		/* Exit the file transfer if a buffer full event occurs, but the current buffer has not yet been served. This indicates a file manager operation took too long to execute */
		if ( 0x00000001U == cubeadcs_driver_get_rx_event_status() )
		{
			fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_START_DWN_BURST);
		}

		if ( eCUBEADCS_COMM_RX_TIMEOUT == retStatus )
		{
			/* Get set bit count */
			sFDwn_P.u16BurstHoleMapCnt = 0;
			for (uint8_t u8Indx = 0; u8Indx < CUBEADCS_FDWN_HOLE_MAP_BYTE_LEN; ++u8Indx) {
				uint8_t u8NHole;
				u8NHole = sFDwn_P.u8HoleMap[u8Indx];
				while ( 0 != u8NHole ) {
					u8NHole &= (uint8_t)(u8NHole - 1);
					sFDwn_P.u16BurstHoleMapCnt++;
				}
			}

			fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_CHECK_FILE_TRANSFER_STATUS);
		}

		queue_quick_flush(p_cubeadcs_proc_queue);

		break;
	default:

		EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_CUBEADCS_FHANDL, eEXEH_CUBEADCS_EXCEPTION_RUNTIME_ERROR, __LINE__);

		break;
	}

	if ( spFDownF == scaFDownFArray[ eCUBEADCS_FTRANSF_FDWNSTATE_POLL_BURST_STATUS ] )
	{
		//Just do nothing for now
	}
	else if ( spFDownF == scaFDownFArray[ eCUBEADCS_FTRANSF_FDWNSTATE_START_DWN_BURST ] )
	{
		(void)SdMngr_f_close(&sFDwnObj);

		/* A single burst takes apprx. 5 seconds, give time for the burst to end before attempting a new one */
		osDelay(5000);
	}
	else
	{
		burstCnt = 0;

		cubeadcs_driver_set_dma_cfg(false);
		cubeadcs_driver_init_uart();

		if ( FR_OK != SdMngr_f_close(&sFDwnObj) )
		{
			fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
		}
	}
}

/** @brief Check File Transfer Status sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_CheckFTransfStatus(void)
{
    CUBEADCS_TRACE_DBG("FDWN_________CHK_FTRANSF_STATUS\r");

    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;
    CubeADCS_CmdCfg_t sCmd_UpldHoleMap;

    static uint8_t u8CrcMismatchMaxCnt = 0;

    if ( ((sFDwn_P.u16BurstHoleMapCnt + sFDwn_P.u32HoleMapCnt) < sFDwn_P.u32FPktCnt ) && (sFDwn_P.u16BurstHoleMapCnt < CUBEADCS_FDWN_HOLE_MAP_MAX_CNT) )
    {
        for (uint8_t u8HMIndx = 0; u8HMIndx < 8; u8HMIndx++ )
        {
            fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_START_DWN_BURST);

            CubeADCS_PREPCmd(&sCmd_UpldHoleMap, (eCUBEADCS_CMD_ID_120 + u8HMIndx), &sFDwn_P.u8HoleMap[u8HMIndx * 16], sizeof(CubeADCS_TC_HoleMAP_t), (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

            if ( eCUBEADCS_STDRPLY_OK != fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_UpldHoleMap, eCUBEADCS_COMMREQTYPE_FETCH, CUBEADCS_FTRANSF_FDWN_RPT) )
            {
                fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
                fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);

                break;
            }
        }

        sFDwn_P.sDwnBurstCmd.IgnoreHoleMap  = pdFALSE;
    }
    else
    {
        /* Compare saved block checksum against expected */

        uint16_t u16CalcCRC;

        eCubeADCS_TLM242_t sCmdRsp;

        CubeADCS_CmdCfg_t sCmd_PollDwnBlockRdy;

        CubeADCS_PREPCmd(&sCmd_PollDwnBlockRdy, eCUBEADCS_CMD_ID_242, NULL, 0, (void *)&sCmdRsp, CUBEADCS_TLM242_LEN, &u16CmdRspLen);

        if ( eCUBEADCS_STDRPLY_OK != fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_PollDwnBlockRdy, eCUBEADCS_COMMREQTYPE_FETCH, CUBEADCS_FTRANSF_FDWN_RPT) )
        {
            fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
            fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
        }
        else
        {
        	if ( eCUBEADCS_STDRPLY_OK == fs_CubeADCS_FTransfer_CalcSavedBlockCRC16(&u16CalcCRC, &sFDwnObj, &sFDwn_P.cFName[0], sCmdRsp.TLM242.BlockLen) )
        	{
        		if ( u16CalcCRC == sCmdRsp.TLM242.Crc16 )
        		{
        			u8CrcMismatchMaxCnt = 0;

        			sFDwn_P.u32HoleMapCnt += sFDwn_P.u16BurstHoleMapCnt;

        			if (sFDwn_P.u32HoleMapCnt < sFDwn_P.u32FPktCnt) {

        				sFDwn_P.FDwnBlock.u32Offset += 0x00005000; /* 1024 * 20 */

        				fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_CFG);
        			}
        			else {
        				fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_DONE);

        				/* Truncate file size to match expected size */
        				if ( FR_OK == SdMngr_f_open(&sFDwnObj, &sFDwn_P.cFName[0], FA_WRITE | FA_READ) )
        				{	if ( FR_OK == SdMngr_f_lseek(&sFDwnObj, sFTransfMsg.sFDwn->FDwnInfo.u32FileSize ) )
        					{	if ( FR_OK == SdMngr_f_truncate(&sFDwnObj))
        						{
        							;
        						}
        					}
        				}
        				(void)SdMngr_f_close(&sFDwnObj);
        			}
        		}
        		else
        		{
        			CUBEADCS_TRACE_DBG("FDWN_________CRC_BLOCK_MISMATCH\r");

        			if ( u8CrcMismatchMaxCnt++ < CUBEADCS_FTRANSF_FDWN_RPT_CRC_DIFF)
        			{
        				fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_CFG);
        			}
        			else {
        				fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR_CRC);
        				fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
        			}
        		}
        	}
        	else
        	{
                fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
                fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_ERR);
        	}
        }
    }
}

/** @brief DONE sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_Done(void)
{
    CUBEADCS_TRACE_DBG("FDWN_________DONE\r");

    uint16_t u16CalcCRC;

    if (FR_OK == SdMngr_f_open(&sFDwnObj, &sFDwn_P.cFName[0], FA_READ) )
    {
        (void)SdMngr_f_close(&sFDwnObj);

        for (uint8_t u8RtrCnt = 0; u8RtrCnt <= CUBEADCS_FTRANSF_FDWN_RPT; ++u8RtrCnt )
        {
            if ( eCUBEADCS_STDRPLY_OK == fs_CubeADCS_FTransfer_CalcSavedBlockCRC16(&u16CalcCRC, &sFDwnObj, &sFDwn_P.cFName[0], SdMngr_f_size(&sFDwnObj)) )
            {
                if ( u16CalcCRC == sFTransfMsg.sFDwn->FDwnInfo.u16Crc16 )
                {
                	fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_DONE);
                }
                else
                {
                	fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR_CRC);
                }

                break;
            }

            if ( u8RtrCnt == CUBEADCS_FTRANSF_FDWN_RPT )
            {
                fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
            }
        }
    }
    else {
        fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR_SDCARD);
    }

    fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_END);
}

/** @brief ERROR sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_Err(void)
{
    CUBEADCS_TRACE_DBG("FDWN_________ERR\r");

    /* A single burst takes apprx. 5 seconds, give time for burst to end in case an error has occurred */
    osDelay(5000);

    if ( eCUBEADCS_FTRANSF_FHANDL_BUSY == sFTransfMsg.sFDwn->eFDwnStatus)
    {
    	fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);
    }

    fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_END);
}

/** @brief END sequence for File Transfers - Downloading file */
static void fs_CubeADCS_FTransfer_DownloadFile_End(void)
{
    CUBEADCS_TRACE_DBG("FDWN_________END\r");

    // Try to close the file regardless of previous attempt result
    (void)SdMngr_f_close(&sFDwnObj);

    eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_IDLE;
    sFTransfMsg.eReqType      = eCUBEADCS_FTRANSF_REQTYPE_NONE;

    fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCUBEADCS_FTRANSF_FDWNSTATE_INIT);
}

/** @brief Invoke the file-list download procedure step */
static void fs_CubeADCS_FTransfer_DownloadFileList(void)
{
    (*spDownFList)();
}

/** @brief Initialisation sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_Init(void)
{
    FIL sFListObj;

    fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_BUSY);

    fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_ERR);

    if ( SDMNGR_CARD_STATE_READY == SdMngr_GetCardState())
    {
        if ( FR_OK == SdMngr_f_open(&sFListObj, &ccFListName[0], FA_WRITE | FA_CREATE_ALWAYS) ) {

            f_printf(&sFListObj, "CubeADCS File List\r\n--------------------------------------------\r\n");
            f_printf(&sFListObj, "FileType (s|d)\t Size\t CRC\t Time\t Ctr\r\n\r\n");

            if ( FR_OK == SdMngr_f_close(&sFListObj) )
            {
            	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_RST);
            }
        }
    }
}

/** @brief Reset sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_Rst(void)
{
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmd_RstFileListReadPointer;

    CubeADCS_PREPCmd(&sCmd_RstFileListReadPointer, eCUBEADCS_CMD_ID_118, NULL, CUBEADCS_TC_118_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    if ( eCUBEADCS_STDRPLY_OK == fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_RstFileListReadPointer, eCUBEADCS_COMMREQTYPE_FETCH, CUBEADCS_FTRANSF_FDWN_RPT) )
    {
    	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_FILEINFO);
    }
    else
    {
    	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_ERR);
    }
}

/** @brief File Info sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_FileInfo(void)
{
    FIL sFListObj;

    uint16_t u16CmdRspLen;

    CubeADCS_TLM243_t sCmdRsp;

    CubeADCS_CmdCfg_t sCmd_GetFileInformation;

    CubeADCS_PREPCmd(&sCmd_GetFileInformation, eCUBEADCS_CMD_ID_243, NULL, 0, (void *)&sCmdRsp, CUBEADCS_TLM243_LEN, &u16CmdRspLen);

    if ( eCUBEADCS_STDRPLY_OK == fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_GetFileInformation, eCUBEADCS_COMMREQTYPE_FETCH, CUBEADCS_FTRANSF_FDWN_RPT) )
    {
    	if ( sCmdRsp.TLM243.Byte0.Data.busy )
        {
        	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_WAIT);
        }
        else
        {
            if (  (sCmdRsp.TLM243.DateTime == 0) && (sCmdRsp.TLM243.Size == 0) )
            {
            	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_DONE);
            }
            else
            {
                fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_ADVANCE);

                if ( FR_OK == SdMngr_f_open(&sFListObj, &ccFListName[0], FA_WRITE | FA_OPEN_APPEND) )
                {
                    if ( FR_OK == SdMngr_f_lseek(&sFListObj, SdMngr_f_size(&sFListObj) ) )
                    {
                        const char * pcFType;

                        if ( 2 == sCmdRsp.TLM243.Byte0.Data.fileType )
                        {
                        	pcFType = pccFTypes[FILE_TYPE_TLM];
                        }
                        else if ( 3 == sCmdRsp.TLM243.Byte0.Data.fileType )
                        {
                        	pcFType = pccFTypes[FILE_TYPE_JPG];
                        }
                        else if ( 4 == sCmdRsp.TLM243.Byte0.Data.fileType )
                        {
                        	pcFType = pccFTypes[FILE_TYPE_BMP];
                        }
                        else
                        {
                        	pcFType = pccFTypes[FILE_TYPE_IND];
                        }

                        f_printf(&sFListObj, "%s | %d\t 0x%08lX\t 0x%04X\t %02d/%02d/%04d %02d:%02d:%02d\t %03d\r\n", pcFType, sCmdRsp.TLM243.Byte0.Data.fileType,
                                                                         sCmdRsp.TLM243.Size,
                                                                         sCmdRsp.TLM243.CRC16,
                                                                         (sCmdRsp.TLM243.DateTime >> 16) & 0x1f,
                                                                         (sCmdRsp.TLM243.DateTime >> 21) & 0x0f,
                                                                         (sCmdRsp.TLM243.DateTime >> 25) + 1980,
                                                                         (sCmdRsp.TLM243.DateTime >> 11) & 0x1f,
                                                                         (sCmdRsp.TLM243.DateTime >> 5)  & 0x3f,
                                                                         (sCmdRsp.TLM243.DateTime & 0x1f) << 1,
                                                                         sCmdRsp.TLM243.Counter);
                    }
                }

                (void)SdMngr_f_close(&sFListObj);
            }
        }
    }
    else
    {
    	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_ERR);
    }
}

/** @brief Wait sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_Wait(void)
{
    osDelay(10);

    fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_FILEINFO);
}

/** @brief Advance sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_Advance(void)
{
    uint16_t u16CmdRsp;
    uint16_t u16CmdRspLen;

    CubeADCS_CmdCfg_t sCmd_AdvancePtr;

    CubeADCS_PREPCmd(&sCmd_AdvancePtr, eCUBEADCS_CMD_ID_113, NULL, CUBEADCS_TC_113_BYTE_LEN, (void *)&u16CmdRsp, CUBEADCS_TC_LEN, &u16CmdRspLen);

    if ( eCUBEADCS_STDRPLY_OK == fs_CubeADCS_FTransfer_SendCmdWithRpt(&sCmd_AdvancePtr, eCUBEADCS_COMMREQTYPE_FETCH, CUBEADCS_FTRANSF_FDWN_RPT) )
    {
    	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_FILEINFO);
    }
    else
    {
    	fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_ERR);
    }
}

/** @brief Done sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_Done(void)
{
    fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_DONE);

    fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_END);
}

/** @brief Err sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_Err(void)
{
    fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR);

    fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_END);
}

/** @brief End sequence for File Transfers - Download file list */
static void fs_CubeADCS_FTransfer_DownloadFileList_End(void)
{
    eCubeADCS_FTransTaskState = eCUBEADCS_FTRANSF_STATE_IDLE;
    sFTransfMsg.eReqType      = eCUBEADCS_FTRANSF_REQTYPE_NONE;

    fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCUBEADCS_FTRANSF_DWNFLIST_STATE_INIT);
}

/** @brief Send command and repeat if it fails
 *
 *  @param[in] sCmd pointer to command details (context)
 *  @param[in] eCommReqType command request type
 *  @param[in] u8RptNumber number of repeat requests to perform
 *
 *  @return result from the operation
 *
 */
static eCubeADCS_StdRply fs_CubeADCS_FTransfer_SendCmdWithRpt(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_CommReqType_t eCommReqType, uint8_t u8RptNumber)
{
    eCubeADCS_StdRply eRetStatus;

    eRetStatus = eCUBEADCS_STDRPLY_ERR;

    /* Perform X retries before giving up */
    for (uint8_t u8RptCnt = 0; u8RptCnt < u8RptNumber; ++u8RptCnt )
    {
        if ( eCUBEADCS_COMM_OK == CubeADCS_SendCmd(sCmd, eCommReqType) )
        {
            eRetStatus = eCUBEADCS_STDRPLY_OK;

            break;
        }
    }

    return eRetStatus;
}

/** @brief Update the file download handling procedure status
 *
 *	@param[in] eNewStatus the new status
 */
static void fs_CubeADCS_FTransfer_UpdateReqHandlStatus(eCubeADCS_FTransf_Fhandl_t eNewStatus)
{
    eCubeADCS_FTransf_State_t eTaskState;

    eTaskState = CubeADCS_FTransfer_GetTaskState();

    if ( eCUBEADCS_FTRANSF_STATE_DWN == eTaskState )
    {
    	sFTransfMsg.sFDwn->eFDwnStatus = eNewStatus;
    }

    if ( eCUBEADCS_FTRANSF_STATE_UP == eTaskState )
    {
    	sFTransfMsg.sFUp->eFUpStatus = eNewStatus;
    }

    if ( eCUBEADCS_FTRANSF_STATE_DWN_LIST == eTaskState )
    {
    	sFTransfMsg.sFListDwn->eFListDwnStatus = eNewStatus;
    }
}

/** @brief Update the file download function pointer
 *
 *	@param[in] eNewStatus the next file download step
 */
static void fs_CubeADCS_FTransfer_UpdateFDwnFPtr(eCubeADCS_FTransf_FDwnState_t eNewStatus)
{
    spFDownF  = scaFDownFArray[ eNewStatus ];
}

/** @brief Update the file list download function pointer
 *
 *	@param[in] eNewStatus the next file list download step
 */
static void fs_CubeADCS_FTransfer_UpdateDwnFListPtr(eCubeADCS_FTransf_DwnFListState_t eNewStatus)
{
    spDownFList = scaDownFListArray[ eNewStatus ];
}

/** @brief Make new file name by concatenating given information
 *
 *  @param[in] uint8_t buf_size - storage location size in bytes
 *
 *	@param[out] pcFullFileName pointer to file name storage location
 *
 *	@note File types are limited to 4. Implementation is not flexible.
 */
static void fs_CubeADCS_FTransfer_CreateFileName(char *pcFullFileName, const uint8_t buf_size)
{
	CRIT_ASSERT(NULL != pcFullFileName);
	CRIT_ASSERT(0 < buf_size);

    uint8_t u8Indx = 2;
    uint8_t u8FCnt = sFTransfMsg.sFDwn->FDwnInfo.u8Cnt;
    char    au8FCntRepr[4] = {'0', '0', '0', '\0'};
    char    au8FExt[5]     = {'0', '0', '0', '0', '\0'};

    /* Clear the array before use as otherwise memory corruption will occur*/
    (void)memset(pcFullFileName, '\0', buf_size);

    /* Add filetype number */
    do {
        au8FCntRepr[u8Indx--] = u8FCnt % 10 + '0';
    } while ((u8FCnt /= 10) > 0);

    strncat(pcFullFileName, &au8FCntRepr[0], 4);

    /* Add file group identifier*/
    strncat(pcFullFileName, "CS", 3);

    /* Add file type */
    if ( eCUBEADCS_FTYPES_TLM_LOG == sFTransfMsg.sFDwn->FDwnInfo.eFType ) {
        strncat(pcFullFileName, pccFTypes[0], 4);
        strncpy(au8FExt, ccFTypeExt[0], 5);
    }
    else if ( eCUBEADCS_FTYPES_JPG_IMG == sFTransfMsg.sFDwn->FDwnInfo.eFType ) {
        strncat(pcFullFileName, pccFTypes[1], 4);
        strncpy(au8FExt, ccFTypeExt[1], 5);
    }
    else if ( eCUBEADCS_FTYPES_BMP_IMG == sFTransfMsg.sFDwn->FDwnInfo.eFType ) {
        strncat(pcFullFileName, pccFTypes[2], 4);
        strncpy(au8FExt, ccFTypeExt[2], 5);
    }
    else {
        strncat(pcFullFileName, pccFTypes[3], 4);
    }

    /* Add filetype extension */
    strncat(pcFullFileName, &au8FExt[0], 5);
}

/** @brief Calculate block checksum as saved in OBC sd-card
 *
 *	@param[out] pu16Cache pointer to destination cache location
 *	@param[in] psFDwnObj pointer to the file object
 *	@param[in] pcFName pointer to file name
 *	@param[in] u32Len size in bytes for which to perform the calculation
 *
 *	@return The calculated CRC16 checksum
 */
static eCubeADCS_StdRply fs_CubeADCS_FTransfer_CalcSavedBlockCRC16(uint16_t *pu16Cache, FIL *psFDwnObj, char *pcFName, uint32_t u32Len)
{
    uint8_t  u8ReadData;

    uint32_t uintReadBytes;

    uint16_t u16CalcCRC = 0;

    eCubeADCS_StdRply eRetStatus = eCUBEADCS_STDRPLY_ERR;

    FRESULT eFRes;

    FSIZE_t fBurstBaseByteCnt;

    if (FR_OK == SdMngr_f_open(psFDwnObj, pcFName, FA_READ) )
    {
    	eRetStatus = eCUBEADCS_STDRPLY_OK;

    	(void)SdMngr_f_close(psFDwnObj);

    	if ( SdMngr_f_size(psFDwnObj) != u32Len )
    	{
    		fBurstBaseByteCnt = SdMngr_f_size(psFDwnObj) - ( (u32Len % 20 == 0) ? (FSIZE_t)u32Len : ((FSIZE_t)u32Len + (20 - u32Len % 20)) );
    	}
    	else
    	{
    		fBurstBaseByteCnt = 0;
    	}

    	if ( FR_OK == ( eFRes = SdMngr_f_open(psFDwnObj, pcFName, FA_OPEN_EXISTING | FA_READ) ) )
    	{
    		for (uint32_t u32Indx = 0; u32Indx < u32Len; ++u32Indx)
    		{
    			if ( FR_OK == ( eFRes = SdMngr_f_lseek(psFDwnObj, fBurstBaseByteCnt + u32Indx) ) )
    			{
    				(void)SdMngr_f_read(psFDwnObj,
    						(void *)&u8ReadData,
							1,
							(UINT*)&uintReadBytes);

    				u16CalcCRC = CubeADCS_Calculate_Single_CRC_16(u16CalcCRC, u8ReadData);

    				if (uintReadBytes != sizeof(u8ReadData)) {
    					eRetStatus = eCUBEADCS_STDRPLY_ERR;
    					break;
    				}
    			}
    			else {
    				eRetStatus = eCUBEADCS_STDRPLY_ERR;
    				break;
    			}
    		}
    	}
    	else
    	{
    		eRetStatus = eCUBEADCS_STDRPLY_ERR;
    	}

    	(void)SdMngr_f_close(psFDwnObj);
    }

    *pu16Cache = u16CalcCRC;

    CUBEADCS_TRACE_DBG("%02X, ---STATUS\r", eRetStatus);

    return eRetStatus;
}

/* ******************************************************************************************* */
