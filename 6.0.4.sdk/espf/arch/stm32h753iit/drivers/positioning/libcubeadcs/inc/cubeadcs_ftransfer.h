/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ADCS_CUBESPACE_CUBEADCS_FTRANSFER_H_
#define ADCS_CUBESPACE_CUBEADCS_FTRANSFER_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_ftransf.h
 * @brief    Interface for the file transfer logic. Facilitates the download of files and the dump of the file-list. Used internally.
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

#include "../cfg/cubeadcs_cfg.h"
#include "../cfg/cubeadcs_sysstate_cfg.h"

#include "GlobalConfig.h"
#include "cmsis_os2.h"
#include "TaskMonitor.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/
/** @brief Standard repeat count used during file transfers */
#define CUBEADCS_FTRANSF_FDWN_RPT           ((uint8_t)3)
/** @brief Repeat count used during the poll stage of the file download */
#define CUBEADCS_FTRANSF_FDWN_RPT_CNT_POLL  ((uint8_t)60)
/** @brief Repeat count used during the burst stage of the file download */
#define CUBEADCS_FTRANSF_FDWN_RPT_CNT_BURST ((uint8_t)20)
/** @brief Repeat count used during the crc check stage of the file download */
#define CUBEADCS_FTRANSF_FDWN_RPT_CRC_DIFF  ((uint8_t)3)
/** @brief Repeat count of a specific burst */
#define CUBEADCS_FTRANSG_FDWN_BURST_MAX_RETRY ((uint8_t)5)

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

/** @brief States of the file transfer state machine */
typedef enum tag_eCubeADCS_FTransf_State {
    eCUBEADCS_FTRANSF_STATE_IDLE,
    eCUBEADCS_FTRANSF_STATE_DWN,
    eCUBEADCS_FTRANSF_STATE_UP,
    eCUBEADCS_FTRANSF_STATE_DWN_LIST,


    eCUBEADCS_FTRANSF_STATE_CNT,

} eCubeADCS_FTransf_State_t;

/** @brief Request types that deal with file transfers */
typedef enum tag_eCubeADCS_FTransf_ReqType {
    eCUBEADCS_FTRANSF_REQTYPE_DWN,
    eCUBEADCS_FTRANSF_REQTYPE_UP,
    eCUBEADCS_FTRANSF_REQTYPE_DWN_LIST,
    eCUBEADCS_FTRANSF_REQTYPE_NONE,

    eCUBEADCS_FTRANSF_REQTYPE_CNT,

} eCubeADCS_FTransf_ReqType_t;

/** @brief Return type to a file request */
typedef enum tag_eCubeADCS_FTransf_Req {
    eCUBEADCS_FTRANSF_REQ_OK,
    eCUBEADCS_FTRANSF_REQ_FAIL_TRANSF_ONGOING,
    eCUBEADCS_FTRANSF_REQ_FAIL_BAD_REQ,
    eCUBEADCS_FTRANSF_REQ_FAIL_NO_ADCS,

    eCUBEADCS_FTRANSF_REQ_CNT,

} eCubeADCS_FTransf_Req_t;

/** @brief States of the file download state machine */
typedef enum tag_eCubeADCS_FTransf_FDwnState {
    eCUBEADCS_FTRANSF_FDWNSTATE_INIT,
    eCUBEADCS_FTRANSF_FDWNSTATE_CFG,
    eCUBEADCS_FTRANSF_FDWNSTATE_LOAD_FILE_DWN_BLOCK,
    eCUBEADCS_FTRANSF_FDWNSTATE_POLL_DWN_BLOCK_RDY,
    eCUBEADCS_FTRANSF_FDWNSTATE_START_DWN_BURST,
    eCUBEADCS_FTRANSF_FDWNSTATE_POLL_BURST_STATUS,
    eCUBEADCS_FTRANSF_FDWNSTATE_CHECK_FILE_TRANSFER_STATUS,
    eCUBEADCS_FTRANSF_FDWNSTATE_DONE,
    eCUBEADCS_FTRANSF_FDWNSTATE_ERR,
    eCUBEADCS_FTRANSF_FDWNSTATE_END,

    eCUBEADCS_FTRANSF_FDWNSTATE_CNT,

} eCubeADCS_FTransf_FDwnState_t;

/** @brief States of the file-list download state machine */
typedef enum tag_eCubeADCS_FTransf_DwnFListState {
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_INIT,
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_RST,
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_FILEINFO,
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_WAIT,
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_ADVANCE,
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_DONE,
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_ERR,
    eCUBEADCS_FTRANSF_DWNFLIST_STATE_END,

    eCUBEADCS_FTRANSF_DWNFLIST_CNT,

} eCubeADCS_FTransf_DwnFListState_t;

/** @brief Type used to indicate current status of a file or file list download request */
typedef enum tage_eCubeADCS_FTransf_Fhandl_t {
    eCUBEADCS_FTRANSF_FHANDL_DONE,
    eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR,
    eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR_CRC,
    eCUBEADCS_FTRANSF_FHANDL_FTRANSF_ERR_SDCARD,
    eCUBEADCS_FTRANSF_FHANDL_BUSY,
	eCUBEADCS_FTRANSF_FHANDL_STOPPED,

	eCUBEADCS_FTRANSF_FHANDL_CNT

} eCubeADCS_FTransf_Fhandl_t;

/** @brief Type used to depict the file on the CubeADCS SD card */
typedef struct tag_CubeADCS_FDwnInfo //todo - align name with the rest
{
    eCubeADCS_FTypes_t eFType;
    uint8_t            u8Cnt;
    uint16_t           u16Crc16;
    uint32_t           u32FileSize;

} __attribute__((__packed__)) CubeADCS_FDwnInfo_t;

/** @brief File information for a file upload procedure */
typedef struct tag_CubeADCS_FTransf_FUpInfo
{
    char               acFName[16];

} __attribute__((__packed__)) CubeADCS_FTransf_FUpInfo_t;

/** @brief Aggregation of file download information and status of the file download request */
typedef struct tag_CubeADCS_FTransf_FDwn
{
    CubeADCS_FDwnInfo_t         FDwnInfo;
    eCubeADCS_FTransf_Fhandl_t eFDwnStatus;

} __attribute__((__packed__)) CubeADCS_FTransf_FDwn_t;

/** @brief Aggregation of file upload information and status of the file upload request */
typedef struct tag_CubeADCS_FTransf_FUp
{
    CubeADCS_FTransf_FUpInfo_t  FUpInfo;
    eCubeADCS_FTransf_Fhandl_t eFUpStatus;

} __attribute__((__packed__)) CubeADCS_FTransf_FUp_t;

/** @brief Aggregation of file-list download information and status of the file download request */
typedef struct tag_CubeADCS_FTransf_FListDwn
{
    eCubeADCS_FTransf_Fhandl_t eFListDwnStatus;

} __attribute__((__packed__)) CubeADCS_FTransf_FListDwn_t;

/** @brief Overall file transfer request status and type */
typedef struct tag_CubeADCS_FTransf
{    eCubeADCS_FTransf_ReqType_t   eReqType;
     CubeADCS_FTransf_FDwn_t     * sFDwn;
     CubeADCS_FTransf_FUp_t      * sFUp;
     CubeADCS_FTransf_FListDwn_t * sFListDwn;

} __attribute__((__packed__)) CubeADCS_FTransf_t;

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

/** @brief Initializes the CubeADCS file transfer task */
void CubeADCS_FTransfer_TaskInit(void);

/** @brief Return the file transfer task handle
 *
 *  @return id of the thread
 */
osThreadId_t CubeADCS_FTransfer_GetThreadHandle(void);

/** @brief Return the file transfer task current state
 *
 *  @return the state of the file transfer task
 */
eCubeADCS_FTransf_State_t CubeADCS_FTransfer_GetTaskState(void);

/** @brief Returns the file transfer current request state
 *
 *  @return the current request state
 */
CubeADCS_FTransf_t CubeADCS_FTransfer_GetFTransfReq(void);

/** @brief Set a new file transfer request
 *
 *  @param[in] eReqType file transfer request type
 *  @param[in] psFDwnReq pointer to file download context
 *  @param[in] psFUpReq pointer to file upload context
 *  @param[in] psFUpReq pointer to file-list download context
 *
 *  @return status of the request
 */
eCubeADCS_FTransf_Req_t CubeADCS_FTransfer_SetFTransfReq(eCubeADCS_FTransf_ReqType_t eReqType,
		CubeADCS_FTransf_FDwn_t     * psFDwnReq,
		CubeADCS_FTransf_FUp_t      * psFUpReq,
		CubeADCS_FTransf_FListDwn_t * psFListDwnReq);

/** @brief Request to stop an ongoing file transfer */
void CubeADCS_FTransfer_StopOngoingFTransfer(void);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* ADCS_CUBESPACE_CUBEADCS_FTRANSFER_H_ */
/* ******************************************************************************************* */
