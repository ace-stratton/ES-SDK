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
 * @file    cp_cmd_handler.c
 * @brief   Command Protocol commands declarations
 *
 * @}
 */

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "cmsis_os2.h"
#include "ESSA_Stack_TP_Layer.h"
#include "cp_cmd_handler.h"

#include "cubeadcs_usercmds.h"
#include "CP_Handler.h"
#include "ESPLATFORM_NETWORK_STACK/ES_TL_LAYER/ES_TL_Layer.h"
#include "module_id.h"
#include "ESCP_CommandsLocalConf.h"
#include "es_exeh.h"
#include "FWUPD_Persistor.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_Stack.h"
#include "DataSink.h"
#include "FileManager.h"

/*
***************************************************************************************************
* INTERNAL DEFINES
***************************************************************************************************
*/
#define NULL_TERMINATOR_LEN           ((uint8_t)1)
#define SHORTEST_POSSIBLE_FNAME_LEN   ((uint8_t)1 + NULL_TERMINATOR_LEN)
#define MAX_FILE_PATH                 ((uint8_t)FF_LFN_BUF)
#define FILEDOWNLOAD_CRCREAD_BUF_SIZE ((uint16_t)512)

#define MACFPGW_RESPONSE_TIMEOUT_MS  ((uint32_t)4000)
#define CUBEADCS_RESPONSE_TIMEOUT_MS ((uint32_t)4000)

#define MACFPGW_IF_ID     (ESSASNI_PAY_PRI)
#define FILE_DW_ERROR_MSG "FILE DOWNLOAD ERROR"

/*
***************************************************************************************************
* INTERNAL TYPES DEFINITION
***************************************************************************************************
*/

typedef struct
{
    // size of GW frame which includes the MAC FP header and data payload
    uint8_t payload_size;
} PACKED mac_fp_gw_hdr_t;

typedef struct
{
    uint32_t file_offset;
    TCHAR    file_path[MAX_FILE_PATH];
} PACKED dw_file_by_chunks_in_args_t;

typedef struct
{
    const char             error_msg[sizeof(FILE_DW_ERROR_MSG)]; /**< Human readable error message to make it clear to the user that the operation failed and the returned content is not the real requested file */
    eFileManagerOpResult_t error;                                /**< File System Error ID */
    uint32_t               src_line_no;                          /**< Line number where the file system error was detected */
} PACKED dw_file_error_result_t;

/*
***************************************************************************************************
* EXTERNAL VARIABLES DEFINITION
***************************************************************************************************
*/

/*
***************************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
***************************************************************************************************
*/
// CP command GW response context (only one because only one CP command can be served at a time)
static sUserResponseCtx_t user_resp_ctx;

// static context for the CPCmdHandler_DownloadFileByChunks() handler which needs to
// exchange data with the dw_file_by_chunks_cbk callback
static dw_file_by_chunks_in_args_t dw_file_by_chunks_in_args = {
    .file_offset = 0,
    .file_path   = "\0"
};

static dw_file_error_result_t dw_file_error_result = {
    .error_msg   = FILE_DW_ERROR_MSG,
    .error       = FR_OK,
    .src_line_no = 0U
};

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
***************************************************************************************************
*/
static void        on_cmd_response_ready_cbk(void *const p_user_ctx);
static inline void dw_store_error_res(const eFileManagerOpResult_t error, const uint32_t src_line_no);
static uint8_t     dw_file_by_chunks_cbk(const uint64_t cmd_id,
                                         const uint32_t cmd_type,
                                         const uint32_t required_chunk_size,
                                         const uint32_t offset,
                                         uint8_t       *p_chunk);
static bool        b_calc_file_crc(const uint32_t file_offset, uint8_t *const p_buff, const uint32_t buff_size);

/*
***************************************************************************************************
* EXTERNAL (NON STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
void cp_cmd_handler_init(void)
{
    // Will probably do something meaningful in the future...
    return;
}

// this function will be called by the ESSA Stack when the FP layer replies back to the received CP request
ESSATMAC_ErrCodes cp_cmd_handler_mac_fp_gw_enq_message(ESSATMAC_Context *p_mac_ctx, uint8_t *p_msg_data, uint8_t msg_data_sz)
{
    ESSATMAC_ErrCodes result = ESSATMAC_EC_ERROR;

    if ((p_mac_ctx != NULL) && (p_msg_data != NULL) && (msg_data_sz >= sizeof(mac_fp_gw_hdr_t)))
    {
        if ((p_mac_ctx->netType == ESSASNETT_GS_MACFP_GW) &&
            (p_mac_ctx->nInterfaceNumber == MACFPGW_IF_ID) &&
            (p_mac_ctx->nPayloadProtocol == ES_SAT_MAC_PROTOCOL_ID_FP_LAYER) &&
            (user_resp_ctx.pu8DataBuf != NULL) &&
            (user_resp_ctx.u32MaxDataSize >= msg_data_sz))
        {
            // transfer message data back to CP buffer
            (void)memcpy(user_resp_ctx.pu8DataBuf, p_msg_data, msg_data_sz);

            // store actual data size for CP command reply dispatch in cp_cmd_handler_mac_fp_gw_send_cmd(...)
            user_resp_ctx.u32ResponseSize = msg_data_sz;

            ESSA_Stack_TP_Layer_ReleaseThreadWait();

            result = ESSATMAC_EC_OK;
        }
        else
        {
            result = ESSATMAC_EC_INVALID_PARAMS;
        }
    }

    return result;
}

eCPDispatchResult_t cp_cmd_handler_mac_fp_gw_send_cmd(sCPDispatchContext_t *const p_disp_ctx)
{
    if (!CPCmdHandler_IsDispContextValid(p_disp_ctx, CP_CMD_MACFP_GWSEND))
    {
        return ECPDISPATCHRESULT_ERROR;
    }

    ESSATMAC_Context       mac_ctx;
    const mac_fp_gw_hdr_t *p_fp_gw_hdr = (const mac_fp_gw_hdr_t *)p_disp_ctx->pu8CmdData;

    if (p_disp_ctx->u32CmdDataSize >= p_fp_gw_hdr->payload_size)
    {
        (void)memset((void *)&mac_ctx, (uint8_t)0, sizeof(ESSATMAC_Context));

        // setup response buffer for ESSA Stack
        user_resp_ctx.pu8DataBuf         = p_disp_ctx->pu8ResponseBuf;
        user_resp_ctx.u32MaxDataSize     = p_disp_ctx->u32ResponseBufSize;
        user_resp_ctx.u32ResponseSize    = 0U;
        user_resp_ctx.onCmdResponseReady = NULL;
        user_resp_ctx.pUserCtx           = NULL;

        mac_ctx.nInterfaceNumber = MACFPGW_IF_ID;
        mac_ctx.nPayloadProtocol = ES_SAT_MAC_PROTOCOL_ID_FP_LAYER;
        mac_ctx.nSourceAddr      = 0x00U;
        mac_ctx.nTargetAddr      = 0x00U;
        mac_ctx.netType          = ESSASNETT_GS_MACFP_GW;

        ESSA_Stack_TP_Layer_PrepareThreadWait();

        // inject message to ESSA Stack for FP dispatching...
        ESSA_Stack_DataDispatch(&mac_ctx,
                                (uint8_t *)&p_disp_ctx->pu8CmdData[sizeof(mac_fp_gw_hdr_t)],
                                p_fp_gw_hdr->payload_size);

        // wait for cp_cmd_handler_mac_fp_gw_enq_message() to be called or timeout...
        eThreadBlockEvt_t waitResult = ESSA_Stack_TP_Layer_ThreadWaitForEvent(MACFPGW_RESPONSE_TIMEOUT_MS);

        if (waitResult == THREADBlOCKEVT_WAITFINISHED)
        {
            if (p_disp_ctx->u32ResponseBufSize >= sizeof(ESSA_Stack_FP_MsgHdr_t))
            {
                // user-data is already written in the response buffer
                p_disp_ctx->u32ResponseActualSize = user_resp_ctx.u32ResponseSize;
                p_disp_ctx->u8TLError             = EESTL_SFERR_SUCCESS;
            }
            else
            {
                p_disp_ctx->u32ResponseActualSize = 0U;
                p_disp_ctx->u8TLError             = EESTL_SFERR_OUT_OF_MEM;
            }
        }
        else if (waitResult == THREADBLOCKEVT_WAITTIMEOUT)
        {
            p_disp_ctx->u32ResponseActualSize = 0U;
            p_disp_ctx->u8TLError             = EESTL_SFERR_RECEIVE_TIMEOUT;
        }
        else
        {
            (void)memcpy(p_disp_ctx->pu8ResponseBuf, &waitResult, sizeof(waitResult));
            p_disp_ctx->u32ResponseActualSize = sizeof(waitResult);
            p_disp_ctx->u8TLError             = EESTL_SFERR_UNKNOWN;
        }
    }
    else
    {
        p_disp_ctx->u32ResponseActualSize = 0U;
        p_disp_ctx->u8TLError             = EESTL_SFERR_BAD_CMD_PARAMS;
    }

    return ECPDISPATCHRESULT_RESULT_OK;
}

eCPDispatchResult_t cp_cmd_handler_cubeadcs_gw_send_cmd(sCPDispatchContext_t *const p_disp_ctx)
{
    if (!CPCmdHandler_IsDispContextValid(p_disp_ctx, CP_CMD_CUBEADCS_GWSEND))
    {
        return ECPDISPATCHRESULT_ERROR;
    }

    p_disp_ctx->u32ResponseActualSize = 0U;

    if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
    {
        bool bSendCmdStatus = true;

        CubeADCS_CmdCfg_t sCmd;

        sCmd.u8CmdID = p_disp_ctx->pu8CmdData[0];

        sCmd.u16CmdDataSize = (uint16_t)(p_disp_ctx->u32CmdDataSize - sizeof(sCmd.u8CmdID));

        if (p_disp_ctx->u32CmdDataSize == sizeof(sCmd.u8CmdID))
        {
            sCmd.pu8CmdData = NULL;
        }
        else
        {
            sCmd.pu8CmdData = (uint8_t *)&p_disp_ctx->pu8CmdData[sizeof(sCmd.u8CmdID)];
        }

        if (p_disp_ctx->u32CmdDataSize >= sCmd.u16CmdDataSize + sizeof(sCmd.u8CmdID))
        {
            user_resp_ctx.pu8DataBuf         = p_disp_ctx->pu8ResponseBuf;
            user_resp_ctx.u32MaxDataSize     = p_disp_ctx->u32ResponseBufSize;
            user_resp_ctx.u32ResponseSize    = 0U;
            user_resp_ctx.onCmdResponseReady = on_cmd_response_ready_cbk;
            user_resp_ctx.pUserCtx           = (void *)&user_resp_ctx;

            sCmd.pvCmdResDst      = (void *)user_resp_ctx.pu8DataBuf;
            sCmd.u16CmdResDstSize = (uint16_t)user_resp_ctx.u32MaxDataSize;
            sCmd.u16CmdResSize    = (uint16_t *)&p_disp_ctx->u32ResponseActualSize;

            ESSA_Stack_TP_Layer_PrepareThreadWait();

            bSendCmdStatus = CubeADCS_UsrCmd_CmdHandler(eCUBEADCS_USR_CMDS_GENERIC, &sCmd, &user_resp_ctx);

            if (!bSendCmdStatus)
            {
                // block here to wait answer from CUBE_ADCS...
                eThreadBlockEvt_t waitResult = ESSA_Stack_TP_Layer_ThreadWaitForEvent(CUBEADCS_RESPONSE_TIMEOUT_MS);

                if (waitResult == THREADBlOCKEVT_WAITFINISHED)
                {
                    if (!bSendCmdStatus)
                    {
                        if (user_resp_ctx.u32ResponseSize <= p_disp_ctx->u32ResponseBufSize)
                        {
                            // user-data is already written in the response buffer which was passed before the call to
                            // CubeADCS_UsrCmd_CmdHandler(...)
                            p_disp_ctx->u32ResponseActualSize = user_resp_ctx.u32ResponseSize;
                            p_disp_ctx->u8TLError             = EESTL_SFERR_SUCCESS;
                        }
                        else
                        {
                            p_disp_ctx->u8TLError = EESTL_SFERR_OUT_OF_MEM;
                        }
                    }
                }
                else if (waitResult == THREADBLOCKEVT_WAITTIMEOUT)
                {
                    p_disp_ctx->u8TLError = EESTL_SFERR_RECEIVE_TIMEOUT;
                }
                else
                {
                    (void)memcpy(p_disp_ctx->pu8ResponseBuf, &waitResult, sizeof(waitResult));
                    p_disp_ctx->u32ResponseActualSize = sizeof(waitResult);
                    p_disp_ctx->u8TLError             = EESTL_SFERR_UNKNOWN;
                }
            }
            else
            {
                p_disp_ctx->u8TLError = EESTL_SFERR_BAD_CMD_PARAMS;
            }
        }
        else
        {
            p_disp_ctx->u8TLError = EESTL_SFERR_BAD_CMD_PARAMS;
        }
    }
    else // not SYS_MODULE_ID_CUBE_ADCS
    {
        p_disp_ctx->u8TLError = EESTL_SFERR_CMD_NOT_SUPP;
    }

    return ECPDISPATCHRESULT_RESULT_OK;
}

//
//  File-commands section
//

eCPDispatchResult_t cp_cmd_handler_download_file(sCPDispatchContext_t *const p_disp_ctx)
{
    eCPDispatchResult_t res       = ECPDISPATCHRESULT_ERROR;
    uint32_t            file_size = 0U;

    if (CPCmdHandler_IsDispContextValid(p_disp_ctx, CP_CMD_DBG_DOWNLOADFILE))
    {
        // 4 bytes for file_offset parameter and a valid file name(1 symbol and Null terminator)
        if (p_disp_ctx->u32CmdDataSize >=
            sizeof(dw_file_by_chunks_in_args.file_offset) + SHORTEST_POSSIBLE_FNAME_LEN)
        {
            dw_file_by_chunks_in_args = *((dw_file_by_chunks_in_args_t *)p_disp_ctx->pu8CmdData);

            // clear any pending errors
            dw_file_error_result.error       = FR_OK;
            dw_file_error_result.src_line_no = 0U;

            eFileManagerOpResult_t fres = fileManager_FGetSize(dw_file_by_chunks_in_args.file_path,
                                                               &file_size);
            if (FR_OK == fres)
            {
                if (file_size > dw_file_by_chunks_in_args.file_offset)
                {
                    file_size -= dw_file_by_chunks_in_args.file_offset;
                    // does the file fit in a single response buffer?
                    if (file_size <= p_disp_ctx->u32ResponseBufSize)
                    {
                        // file fits, just read it in the current buffer and respond back
                        // NOTE:
                        //      Ensure that dw_file_by_chunks_in_args already contains the file path information
                        //      because the following function doesn't accept a context parameter and shall somehow
                        //      know which file to attempt to read
                        uint8_t cbk_res = dw_file_by_chunks_cbk(0U,
                                                                CP_CMD_DBG_DOWNLOADFILE,
                                                                file_size,
                                                                dw_file_by_chunks_in_args.file_offset,
                                                                p_disp_ctx->pu8ResponseBuf);

                        if (cbk_res == EESTL_SFERR_SUCCESS)
                        {
                            p_disp_ctx->u32ResponseActualSize = file_size;
                            p_disp_ctx->u8TLError             = EESTL_SFERR_SUCCESS;
                            res                               = ECPDISPATCHRESULT_RESULT_OK;
                        }
                    }
                    else
                    { // file doesn't fit, therefore request chunk-based transfer to GS
                        // prepare file CRC before triggering chunk-based transfer
                        uint8_t crc_tmp_buff[FILEDOWNLOAD_CRCREAD_BUF_SIZE];
                        if (b_calc_file_crc(dw_file_by_chunks_in_args.file_offset, crc_tmp_buff, sizeof(crc_tmp_buff)))
                        {
                            p_disp_ctx->pChunkRequestCbk      = dw_file_by_chunks_cbk;
                            p_disp_ctx->u32ResponseActualSize = file_size;
                            p_disp_ctx->u8TLError             = EESTL_SFERR_SUCCESS;
                            res                               = ECPDISPATCHRESULT_RESULT_BY_CHUNKS;
                        }
                    }
                }
                else
                {
                    p_disp_ctx->u32ResponseActualSize = 0;
                    p_disp_ctx->u8TLError             = EESTL_SFERR_SUCCESS;
                    res                               = ECPDISPATCHRESULT_RESULT_OK;
                }
            }
            else
            {
                dw_store_error_res(fres, __LINE__);
            }
        }
        else
        {
            p_disp_ctx->u32ResponseActualSize = 0U;
            p_disp_ctx->u8TLError             = EESTL_SFERR_BAD_CMD_PARAMS;
            res                               = ECPDISPATCHRESULT_SIMPLERESULT_OK;
        }
    }

    if (ECPDISPATCHRESULT_ERROR == res)
    {
        // attempt to make a human-readable error message
        int32_t ch_count = (int32_t)snprintf((char *volatile)p_disp_ctx->pu8ResponseBuf,
                                             (size_t)(p_disp_ctx->u32ResponseBufSize),
                                             "%s: %d @ line: %lu\n",
                                             FILE_DW_ERROR_MSG,
                                             dw_file_error_result.error,
                                             dw_file_error_result.src_line_no);

        if (ch_count > 0)
        {
            p_disp_ctx->u32ResponseActualSize = (uint32_t)ch_count;
        }
        else
        {
            (void)memcpy(p_disp_ctx->pu8ResponseBuf, &dw_file_error_result, sizeof(dw_file_error_result));
            p_disp_ctx->u32ResponseActualSize = sizeof(dw_file_error_result);
        }

        p_disp_ctx->u8TLError = EESTL_SFERR_SUCCESS;
        res                   = ECPDISPATCHRESULT_RESULT_OK;
    }

    return res;
}

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/

static void on_cmd_response_ready_cbk(void *const p_user_ctx)
{
    ESSA_Stack_TP_Layer_ReleaseThreadWait();

    (void)p_user_ctx;
}

static inline void dw_store_error_res(const eFileManagerOpResult_t error, const uint32_t src_line_no)
{
    dw_file_error_result.error       = error;
    dw_file_error_result.src_line_no = src_line_no;
}

static uint8_t dw_file_by_chunks_cbk(const uint64_t cmd_id,
                                     const uint32_t cmd_type,
                                     const uint32_t required_chunk_size,
                                     const uint32_t offset,
                                     uint8_t       *p_chunk)
{
    uint8_t         res = EESTL_SFERR_UNKNOWN;
    FileManagerFHnd h_file;

    (void)cmd_id;
    (void)cmd_type;

    eFileManagerOpResult_t fres = fileManager_FOpen(dw_file_by_chunks_in_args.file_path,
                                                    eFileManagerFileModeId_OPEN_EXISTING | eFileManagerFileModeId_READ,
                                                    &h_file);

    if (fres == FR_OK)
    {
        uint32_t bytes_read = 0U;

        fres = fileManager_FRead(h_file, dw_file_by_chunks_in_args.file_offset + offset, p_chunk, required_chunk_size, &bytes_read);

        if ((fres == FR_OK) && (bytes_read == required_chunk_size))
        {
            res = EESTL_SFERR_SUCCESS;
        }
        else
        {
            dw_store_error_res(fres, __LINE__);
        }

        (void)fileManager_FClose(h_file);
    }
    else
    {
        dw_store_error_res(fres, __LINE__);
    }

    return res;
}

static bool b_calc_file_crc(const uint32_t file_offset, uint8_t *const p_buff, const uint32_t buff_size)
{
    uint32_t        offset        = file_offset;
    uint32_t        bytes_read    = 0U;
    bool            b_first_block = true;
    bool            b_success     = true;
    FileManagerFHnd h_file;

    eFileManagerOpResult_t fres = fileManager_FOpen(dw_file_by_chunks_in_args.file_path,
                                                    eFileManagerFileModeId_OPEN_EXISTING | eFileManagerFileModeId_READ,
                                                    &h_file);

    if (fres == FR_OK)
    {
        do
        {
            fres = fileManager_FRead(h_file, offset, p_buff, buff_size, &bytes_read);

            if (fres == FR_OK)
            {
                ESCP_ModDrv_CalcBlockCRC(p_buff, bytes_read, b_first_block);

                b_first_block = false;

                offset += bytes_read;
            }
            else
            {
                dw_store_error_res(fres, __LINE__);
                b_success = false;
                break;
            }
        } while (bytes_read > 0U);

        (void)fileManager_FClose(h_file);
    }
    else
    {
        dw_store_error_res(fres, __LINE__);
    }

    return b_success;
}
