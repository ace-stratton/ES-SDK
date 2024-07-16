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
 * @file    CP_SX_Band_Commands.c
 * @brief   Command Protocol S/X Band commands
 *
 * @}
 */

#include "es_cdef.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "cmsis_os2.h"
#include "ESSA_Stack_TP_Layer.h"
#include "ESPLATFORM_NETWORK_STACK/ES_TL_LAYER/ES_TL_Layer.h"
#include "ESCP_CommandsLocalConf.h"
#include "es_exeh.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_Stack.h"
#include "DataSink.h"
#include "CP_SX_Band_Commands.h"
#include "if_sys_conf.h"
#include "es_sxband_config.h"
#include "SdMngr.h"
#if defined(SXBAND_SCHEDULER_ENABLED)
#include "sxband_sched.h"
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)
#include "sxband_pl_ctrl.h"

#include "S_X_Band_Trnsm.h"

#define SXBAND_RESPONSE_TIMEOUT_MS      ((uint32_t) 1 * 60 * 1000)  // 1 minutes
#define SXBAND_FNAME_SIZE               (30U)    /**< max size of the file names used by the SXBand scheduler implementation */

static const osMutexAttr_t sxband_cp_lock_attr =
{
    "sxband_cp_mutex",
    osMutexRecursive,
    NULL,
    0U
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t sxband_cp_lock_id;

// CP command GW response context (only one because only one CP command can be served at a time)
static sUserResponseCtx_t userRespCtx;

static void OnCmdResponseReadyCbk(void * const pUserCtx)
{
    ESSA_Stack_TP_Layer_ReleaseThreadWait();

    (void) pUserCtx;
}

eCPDispatchResult_t CPCmdHandler_SXBand_GwSendCmd(sCPDispatchContext_t * const psDispCtx)
{
    const sSXBandGwCmdHdr_t * pCmdHdr = NULL;
    eThreadBlockEvt_t waitResult = THREADBLOCKEVT_ERROR;
    static const char data_too_big_hdr[] = " >>";
    static char data_too_big_msg[sizeof(data_too_big_hdr) + sizeof(SX_BAND_FOUTPUT_NAME) - 1U];
    static bool is_msg_initialized = false;
    uint32_t cmd_timeout_ms = SXBAND_RESPONSE_TIMEOUT_MS;

    if (!is_msg_initialized)
    {
        (void) snprintf(data_too_big_msg, sizeof(data_too_big_msg), "%s%s", data_too_big_hdr, SX_BAND_FOUTPUT_NAME);

        is_msg_initialized = true;
    }

    if (sys_conf_is_module_active(SYS_MODULE_ID_SX_BAND))
    {
        if (CPCmdHandler_IsDispContextValid(psDispCtx, CP_CMD_SXBAND_GWSEND))
        {
            pCmdHdr = (const sSXBandGwCmdHdr_t *) psDispCtx->pu8CmdData;
            if (psDispCtx->u32CmdDataSize >= sizeof(sSXBandGwCmdHdr_t) + pCmdHdr->u8Size)
            {
                userRespCtx.pu8DataBuf = psDispCtx->pu8ResponseBuf;
                userRespCtx.u32MaxDataSize = psDispCtx->u32ResponseBufSize;
                userRespCtx.u32ResponseSize = 0U;
                userRespCtx.onCmdResponseReady = OnCmdResponseReadyCbk;
                userRespCtx.pUserCtx = (void *) &userRespCtx;
                // assume that all SXBand response data can fit in the response buffer;
                // the flag will be set to false in case the response is bigger than the CP output buffer
                userRespCtx.is_all_data_in_buf = true;

                ESSA_Stack_TP_Layer_PrepareThreadWait();

                S_X_BAND_TRNSM_ESTTC_StartCmd(pCmdHdr->Identifier,
                                              pCmdHdr->Cmd,
                                              pCmdHdr->Type,
                                              pCmdHdr->u8Size,
                                              (pCmdHdr->u8Size > 0U) ?
                                              &psDispCtx->pu8CmdData[sizeof(sSXBandGwCmdHdr_t)] : NULL,
                                              &userRespCtx,
                                              &cmd_timeout_ms);

                // block here to wait answer from SXBand... (not the full timeout reported by the SXBand driver is waited here because
                // this may keep the GS communication thread blocked for too long and other commands would not be executable, hence
                // there is a limit (the full timeout is accounted for only by the SXBand command scheduler)
                waitResult = ESSA_Stack_TP_Layer_ThreadWaitForEvent((cmd_timeout_ms > SXBAND_RESPONSE_TIMEOUT_MS) ? SXBAND_RESPONSE_TIMEOUT_MS : cmd_timeout_ms);

                if (waitResult == THREADBlOCKEVT_WAITFINISHED)
                {
                    if (0U == userRespCtx.u32ResponseSize)
                    {
                        psDispCtx->u32ResponseActualSize = 0U;
                        psDispCtx->u8TLError = EESTL_SFERR_SEND_TIMEOUT;
                    }
                    else
                    {
                        if (userRespCtx.u32ResponseSize > psDispCtx->u32ResponseBufSize)
                        {
                            userRespCtx.u32ResponseSize = psDispCtx->u32ResponseBufSize;
                        }

                        psDispCtx->u32ResponseActualSize = userRespCtx.u32ResponseSize;
                        psDispCtx->u8TLError = EESTL_SFERR_SUCCESS;

                        // user-data is already written in the response buffer which was passed before the call to
                        // S_X_BAND_TRNSM_ESTTC_StartCmd_Generic;
                        // in case the SXBand response was bigger than what we can accommodate, we provide a hint to the
                        // user at the end of the response buffer that the full output is available in the SXBAND.LOG file
                        // on the OBC SD card
                        if (!userRespCtx.is_all_data_in_buf)
                        {
                            if (userRespCtx.u32ResponseSize >= sizeof(data_too_big_msg))
                            {
                                (void) memcpy((void *) &psDispCtx->pu8ResponseBuf[userRespCtx.u32ResponseSize - sizeof(data_too_big_msg)],
                                              data_too_big_msg,
                                              sizeof(data_too_big_msg));
                            }
                            else
                            {
                                // directly fail because there is no room in the buffer to even accommodate the message
                                // hinting the user to check the SXBAND.LOG file for the full command output
                                psDispCtx->u32ResponseActualSize = 0U;
                                psDispCtx->u8TLError = EESTL_SFERR_OUT_OF_MEM;
                            }
                        }
                    }
                }
                else
                    if (waitResult == THREADBLOCKEVT_WAITTIMEOUT)
                    {
                        psDispCtx->u32ResponseActualSize = 0U;
                        psDispCtx->u8TLError = EESTL_SFERR_RECEIVE_TIMEOUT;
                    }
                    else
                    {
                        (void) memcpy(psDispCtx->pu8ResponseBuf, &waitResult, sizeof(waitResult));
                        psDispCtx->u32ResponseActualSize = sizeof(waitResult);
                        psDispCtx->u8TLError = EESTL_SFERR_UNKNOWN;
                    }
            }
            else
            {
                psDispCtx->u32ResponseActualSize = 0U;
                psDispCtx->u8TLError = EESTL_SFERR_BAD_CMD_PARAMS;
            }
        }
    }
    else
    {
        psDispCtx->u32ResponseActualSize = 0U;
        psDispCtx->u8TLError = EESTL_SFERR_MODULE_NOT_OPERATIONAL;
    }

    return (0U == psDispCtx->u32ResponseActualSize) ? ECPDISPATCHRESULT_SIMPLERESULT_OK : ECPDISPATCHRESULT_RESULT_OK;
}

#if defined(SXBAND_SCHEDULER_ENABLED)
/**
 * @brief Input arguments for the SXBand Schedule Run CP command
 *
 * The CP buffer is expected to contain a valid SXBand schedule file. The only difference lies in this
 * structure which serves as a CP command header specifying the schedule file name to use for storing the data on the SD card.
 * The maximum file size which can be uploaded with this CP command is limited to the size of the CP buffer
 * configured in the system. The advantage however is that the file is written and executed with a single command.
 */
typedef struct
{
    bool reset_pwr_before_sched_start;        /**< requests the SXBand module to be power-reset before starting the command file */
    bool run_from_existing_file;              /**< tells the scheduler to search for an existing file instead of writing the CP buffer content onto the storage */
    char file_name[SXBAND_FNAME_SIZE];        /**< ASCIIZ name of the schedule file to copy the received content to */
} PACKED sxband_sched_cp_in_args_t;

/**
 * @brief Output arguments for the SXBand schedule run CP command
 */
typedef struct
{
    uint8_t file_op_res;                   /**< result from the last file operation (maps to FatFS FRESULT type */
    uint32_t bytes_written;                /**< number of bytes from the buffer which were written to the file */
    uint8_t sched_status;                  /**< status of the sxband schedule request (maps to sxband_sched_status_t type) */
} PACKED sxband_sched_cp_out_args_t;

/**
 * @brief Poll status for the SXBand schedule run CP command
 */
typedef struct
{
    uint8_t sched_status;                       /**< status of the sxband schedule request (maps to sxband_sched_status_t type) */
    char summary_f_name[SXBAND_FNAME_SIZE];     /**< name of the produced report file */
} sxband_sched_cp_out_poll_t;

static sxband_sched_cp_out_poll_t sxband_sched_poll_status;

static void on_sxband_sched_notif(const sxband_sched_status_t status, const char * const p_summary_fname)
{



    osMutexAcquire(sxband_cp_lock_id, osWaitForever);
    sxband_sched_poll_status.sched_status = (uint8_t) status;

    (void) strncpy(sxband_sched_poll_status.summary_f_name, p_summary_fname, sizeof(sxband_sched_poll_status.summary_f_name));

    sxband_sched_poll_status.summary_f_name[sizeof(sxband_sched_poll_status.summary_f_name) - 1] = '\0';

    osMutexRelease(sxband_cp_lock_id);
}

eCPDispatchResult_t CPCmdHandler_SXBand_Sched_Run(sCPDispatchContext_t * const psDispCtx)
{
    const sxband_sched_cp_in_args_t * pCmdHdr = NULL;
    sxband_sched_cp_out_args_t out_args =
    {
        .bytes_written = 0U,
        .file_op_res = (uint8_t) FR_OK,
        .sched_status = (uint8_t) SXBAND_SCHED_STATUS_FAILED
    };

    if (sys_conf_is_module_active(SYS_MODULE_ID_SX_BAND))
    {
        if (CPCmdHandler_IsDispContextValid(psDispCtx, CP_CMD_SXBAND_SCHED_RUN))
        {
            if (NULL == sxband_cp_lock_id)
            {
                sxband_cp_lock_id = osMutexNew(&sxband_cp_lock_attr);
            }

            pCmdHdr = (const sxband_sched_cp_in_args_t *) psDispCtx->pu8CmdData;

            if (psDispCtx->u32CmdDataSize >= sizeof(sxband_sched_cp_in_args_t))
            {
                if (!pCmdHdr->run_from_existing_file)
                {
                    FIL fhnd;
                    UINT bw;

                    out_args.file_op_res = (uint8_t) SdMngr_f_open(&fhnd, (const TCHAR *) pCmdHdr->file_name, FA_WRITE | FA_CREATE_ALWAYS);
                    out_args.bytes_written = 0U;

                    if (FR_OK == out_args.file_op_res)
                    {
                        out_args.file_op_res = (uint8_t) SdMngr_f_write(&fhnd, &psDispCtx->pu8CmdData[sizeof(sxband_sched_cp_in_args_t)], psDispCtx->u32CmdDataSize - sizeof(sxband_sched_cp_in_args_t), &bw);
                        out_args.bytes_written = (uint32_t) bw;

                        out_args.file_op_res = (uint8_t) SdMngr_f_close(&fhnd);
                    }
                }

                if (true == pCmdHdr->reset_pwr_before_sched_start)
                {
                    // perform OBC SXBand driver logical state reset, UART peripheral reset and
                    // power reset of the SXBand module
                    sxband_pl_ctrl_if.stop(0, PL_OP_STOP_MODE_EMERGENCY);
                    sx_band_deinit(INIT_HW);
                    sx_band_init(INIT_MEM);
                    sx_band_init(INIT_HW);
                    sxband_pl_ctrl_if.start(0, NULL);
                }

                osMutexAcquire(sxband_cp_lock_id, osWaitForever);
                // initialize poll status before triggering the asynchronous file command sequence
                sxband_sched_poll_status.sched_status = SXBAND_SCHED_STATUS_IN_PROGRESS;
                (void) memset(sxband_sched_poll_status.summary_f_name, 0, sizeof(sxband_sched_poll_status.summary_f_name));
                osMutexRelease(sxband_cp_lock_id);

                out_args.sched_status = (uint8_t) sxband_sched_start_file_seq(pCmdHdr->file_name, (uint8_t) strlen((const char *) pCmdHdr->file_name) + 1, &on_sxband_sched_notif);

                psDispCtx->u32ResponseActualSize = sizeof(out_args);
                (void) memcpy(psDispCtx->pu8ResponseBuf, &out_args, sizeof(out_args));

                psDispCtx->u8TLError = EESTL_SFERR_SUCCESS;
            }
            else
            {
                psDispCtx->u32ResponseActualSize = 0U;
                psDispCtx->u8TLError = EESTL_SFERR_BAD_CMD_PARAMS;
            }
        }
    }
    else
    {
        psDispCtx->u32ResponseActualSize = 0U;
        psDispCtx->u8TLError = EESTL_SFERR_MODULE_NOT_OPERATIONAL;
    }

    return (0U == psDispCtx->u32ResponseActualSize) ? ECPDISPATCHRESULT_SIMPLERESULT_OK : ECPDISPATCHRESULT_RESULT_OK;
}

eCPDispatchResult_t CPCmdHandler_SXBand_Sched_Poll(sCPDispatchContext_t * const psDispCtx)
{
    if (sys_conf_is_module_active(SYS_MODULE_ID_SX_BAND))
    {
        if (CPCmdHandler_IsDispContextValid(psDispCtx, CP_CMD_SXBAND_SCHED_POLL))
        {
            if (0U == psDispCtx->u32CmdDataSize)
            {
                psDispCtx->u32ResponseActualSize = sizeof(sxband_sched_poll_status);
                (void) memcpy(psDispCtx->pu8ResponseBuf, &sxband_sched_poll_status, sizeof(sxband_sched_poll_status));

                psDispCtx->u8TLError = EESTL_SFERR_SUCCESS;
            }
            else
            {
                psDispCtx->u32ResponseActualSize = 0U;
                psDispCtx->u8TLError = EESTL_SFERR_BAD_CMD_PARAMS;
            }
        }
    }
    else
    {
        psDispCtx->u32ResponseActualSize = 0U;
        psDispCtx->u8TLError = EESTL_SFERR_MODULE_NOT_OPERATIONAL;
    }

    return (0U == psDispCtx->u32ResponseActualSize) ? ECPDISPATCHRESULT_SIMPLERESULT_OK : ECPDISPATCHRESULT_RESULT_OK;
}
#endif    // #if defined(SXBAND_SCHEDULER_ENABLED)
