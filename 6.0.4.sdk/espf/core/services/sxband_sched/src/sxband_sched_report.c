/*
 * Copyright (c) 2022-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup es_sxband
 * @{
 *
 * @file sxband_sched_report.c
 *
 * @brief Command status reporting implementation
 *
 * The module provides operations related to the formatting and creation of
 * SXBand command list reports as a CSV file.
 *
 * @}
 */

#include <string.h>
#include "sxband_sched_report.h"
#include "SdMngr.h"
#include "es_exeh.h"
#include "es_sxband_config.h"
#include "assertions.h"
#include "S_X_Band_Trnsm.h"

#define TEMP_REPORT_FNAME           "SXB_REP.INP"
#define CSV_HEADER_COL_NAMES        "id,cmd,type,size,data,status\r\n"
#define ERROR_STR                   "Failed to fetch command output"
#define TIMEOUT_STR                 "SXBand driver timeout"
#define NO_FILES_STR                "File pattern did not match any file(s)"
#define EXEH_CURRENT_MODULE_ID      eEXEHModuleID_SXBAND_SCHED
#define SXBAND_LOG_COPY_BUF_SIZE    (50U)

typedef struct
{
    FIL rep_file_hnd;            /**< report file FS handle */
    bool file_opened;            /**< true - report file is already open */
    const char *p_actual_rep_fname;    /**< a pointer to the actual report file name buffer requested by the user */
} sxband_sched_report_ctx_t;

/** @brief Runtime context used by this module */
static sxband_sched_report_ctx_t report_rt_ctx;

static bool copy_sxband_status_to_report(FIL *report_file_hnd);
static inline bool write_and_verify(FIL *fhnd, const uint8_t *p_buf, const uint32_t buf_size);

/** @brief The function copies the SXBand status file to the report file
 *
 *     The SXBand driver outputs the last command status in a file named SX_BAND_FOUTPUT_NAME.
 *     This status could be longer that what we can accommodate in memory, thus the content must
 *     be transferred from this file to the report file in several chunks and this functions does
 *     exactly that.
 *
 *     @param[in] report_file_hnd an FS handle to the report file where to copy the content of the
 *                SX_BAND_FOUTPUT_NAME file (the handle must have been opened for writing before calling
 *                this function
 *
 *  @return true - copy operation went fine, otherwise - false
 */
static bool copy_sxband_status_to_report(FIL *report_file_hnd)
{
    bool res = true;

    if (report_rt_ctx.file_opened)
    {
        uint8_t copy_buf[SXBAND_LOG_COPY_BUF_SIZE];
        FIL sxband_log_hnd;
        FRESULT fres = SdMngr_f_open(&sxband_log_hnd, SX_BAND_FOUTPUT_NAME, FA_READ);
        UINT bytes_read = 0U;
        bool write_ok = false;

        if (FR_OK == fres)
        {
            fres = SdMngr_f_read(&sxband_log_hnd, copy_buf, sizeof(copy_buf), &bytes_read);

            if (FR_OK == fres)
            {
                while (bytes_read > 0U)
                {
                    write_ok = write_and_verify(report_file_hnd, copy_buf, bytes_read);

                    if (write_ok)
                    {
                        fres = SdMngr_f_read(&sxband_log_hnd, copy_buf, sizeof(copy_buf), &bytes_read);

                        if (FR_OK != fres)
                        {
                            bytes_read = 0;
                            res = false;
                        }
                    }
                    else
                    {
                        bytes_read = 0;
                        res = false;

                        EXEH_HANDLE(eEXEHSeverity_Error,
                                    (int32_t) EXEH_SXB_SCHED_REPORT_CANT_WRITE_FILE);
                    }
                }
            }
            else
            {
                EXEH_HANDLE(eEXEHSeverity_Error,
                            (int32_t) EXEH_SXB_SCHED_REPORT_SXB_LOG_READ_ERR);
            }
        }
        else
        {
            EXEH_HANDLE(eEXEHSeverity_Error,
                        (int32_t) EXEH_SXB_SCHED_REPORT_SXB_LOG_OPEN_ERR);
        }

        (void) SdMngr_f_close(&sxband_log_hnd);
    }
    else
    {
        CRIT_ASSERT(false);
    }

    return res;
}

/**
 * @brief Writes a buffer to a file and verifies whether the expected amount of bytes was written.
 *
 * It is used as a helper function to improve readability.
 *
 * @param[in] fhnd file handle which should have been already opened for writing before using this function
 * @param[in] p_buf a pointer to the data buffer to write to the file
 * @param[in] buf_size size of the data pointed to by @ref p_buf argument
 *
 * @return true - the write was successful and the expected amount of bytes were written, otherwise - false
 */
static inline bool write_and_verify(FIL *fhnd, const uint8_t *p_buf, const uint32_t buf_size)
{
    UINT bytes_written;
    FRESULT fres = SdMngr_f_write(fhnd, (const void *) p_buf, (UINT) buf_size, &bytes_written);

    return (FR_OK == fres) && (bytes_written == buf_size);
}

void sxband_sched_report_open(const char * const p_fname)
{
    report_rt_ctx.file_opened = false;

    CRIT_ASSERT(NULL != p_fname);

    // remove temporary report if it exists
    (void) SdMngr_f_unlink(TEMP_REPORT_FNAME);
    report_rt_ctx.p_actual_rep_fname = p_fname;

    FRESULT fres = SdMngr_f_open(&report_rt_ctx.rep_file_hnd, TEMP_REPORT_FNAME, FA_CREATE_ALWAYS | FA_WRITE);

    if (FR_OK == fres)
    {
        UINT bytes_written = 0U;

        fres = SdMngr_f_write(&report_rt_ctx.rep_file_hnd, CSV_HEADER_COL_NAMES, sizeof(CSV_HEADER_COL_NAMES) - 1U, &bytes_written);

        if ((FR_OK == fres) && (bytes_written == sizeof(CSV_HEADER_COL_NAMES) - 1U))
        {
            report_rt_ctx.file_opened = true;
        }
        else
        {
            (void) SdMngr_f_close(&report_rt_ctx.rep_file_hnd);

            EXEH_HANDLE(eEXEHSeverity_Error,
                        (int32_t) EXEH_SXB_SCHED_REPORT_CANT_WRITE_FILE);
        }
    }
    else
    {
        EXEH_HANDLE(eEXEHSeverity_Error,
                    (int32_t) EXEH_SXB_SCHED_REPORT_CANT_OPEN_FILE);
    }
}

void sxband_sched_report_append(const sxband_sched_cmd_t * const p_cmd, const sxband_sched_cmd_status_id cmd_user_status)
{
    char format_buf[8U];    /**< temporary buffer used for string formatting of numbers */
    uint8_t size = 0U;        /**< variable to keep size of the formatted buffer after snprintf call */
    bool write_success = false;        /**< true - all write operations succeeded, otherwise - false */

    CRIT_ASSERT(NULL != p_cmd);

    if (report_rt_ctx.file_opened)
    {
        // format command index
        (void) memset(format_buf, 0U, sizeof(format_buf));
        size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "%ld,", p_cmd->cmd_idx);

        write_success = write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);

        // format command id
        (void) memset(format_buf, 0U, sizeof(format_buf));
        size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "0x%02x,", p_cmd->p_cmd_hdr->cmd);

        write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);

        // format type 'R'/'W'
        (void) memset(format_buf, 0U, sizeof(format_buf));
        size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "%c,", p_cmd->p_cmd_hdr->type);

        write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);

        // format size
        (void) memset(format_buf, 0U, sizeof(format_buf));
        size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "%d,", p_cmd->p_cmd_hdr->size);

        write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);

        if (S_X_BAND_TRNSM_GW_CMD_ID_UPLOAD_FILE == p_cmd->p_cmd_hdr->cmd)
        {
            // add opening quote only if there are command args
            if (p_cmd->p_cmd_hdr->size > 0U)
            {
                (void) memset(format_buf, 0U, sizeof(format_buf));
                size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "'");

                write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);
            }

            // format data bytes
            (void) memset(format_buf, 0U, sizeof(format_buf));

            for (uint8_t data_idx = 0U; data_idx < p_cmd->p_cmd_hdr->size; data_idx++)
            {
                if ('\0' != p_cmd->p_data[data_idx])
                {
                    (void) memset(format_buf, 0U, sizeof(format_buf));
                    size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "%c", p_cmd->p_data[data_idx]);

                    write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);
                }
            }

            // add closing quote only if there are command args
            if (p_cmd->p_cmd_hdr->size > 0U)
            {
                (void) memset(format_buf, 0U, sizeof(format_buf));
                size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "'");

                write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);
            }
        }
        else
        {
            // add opening quote only if there are command args
            if (p_cmd->p_cmd_hdr->size > 0U)
            {
                (void) memset(format_buf, 0U, sizeof(format_buf));
                size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "hex('");

                write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);
            }

            // format data bytes
            (void) memset(format_buf, 0U, sizeof(format_buf));

            for (uint8_t data_idx = 0U; data_idx < p_cmd->p_cmd_hdr->size; data_idx++)
            {
                (void) memset(format_buf, 0U, sizeof(format_buf));
                size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "%02x", p_cmd->p_data[data_idx]);

                write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);
            }

            // add closing quote only if there are command args
            if (p_cmd->p_cmd_hdr->size > 0U)
            {
                (void) memset(format_buf, 0U, sizeof(format_buf));
                size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), "')");

                write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);
            }
        }

        // add comma (', ') after data field
        (void) memset(format_buf, 0U, sizeof(format_buf));
        size = (uint8_t) snprintf((char *) format_buf, sizeof(format_buf), ",");

        write_success = write_success && write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t *) format_buf, size);

        // put double quotes to open the 'status' column of the CSV file
        (void) write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t * const) "\"", 1U);

        switch (cmd_user_status)
        {
            case SXBAND_SCHED_CMD_STATUS_TIMEDOUT:
            {
                (void) SdMngr_f_write(&report_rt_ctx.rep_file_hnd, TIMEOUT_STR, sizeof(TIMEOUT_STR) - 1U, NULL);

                break;
            }

            case SXBAND_SCHED_CMD_STATUS_NO_FILES:
            {
                (void) SdMngr_f_write(&report_rt_ctx.rep_file_hnd, NO_FILES_STR, sizeof(NO_FILES_STR) - 1U, NULL);

                break;
            }

            case SXBAND_SCHED_CMD_STATUS_DEFAULT:
            default:
            {
                if (!copy_sxband_status_to_report(&report_rt_ctx.rep_file_hnd))
                {
                    // if copying of SXBand command output failed for some reason, put a general error message in the report
                    (void) SdMngr_f_write(&report_rt_ctx.rep_file_hnd, ERROR_STR, sizeof(ERROR_STR) - 1U, NULL);
                }

                break;
            }
        }

        // put an ending double quotes a new line to the status column in the CSV file to end the current command record
        (void) write_and_verify(&report_rt_ctx.rep_file_hnd, (const uint8_t * const) "\"\n\r", 2U);

        // explicitly flush buffered record to storage
        SdMngr_f_sync(&report_rt_ctx.rep_file_hnd);

        if (!write_success)
        {
            EXEH_HANDLE(eEXEHSeverity_Error,
                        (int32_t) EXEH_SXB_SCHED_REPORT_CANT_WRITE_FILE);
        }
    }
    else
    {
        CRIT_ASSERT(false);
    }
}

void sxband_sched_report_append_free_text(const char * const p_text, const uint16_t text_size)
{
    CRIT_ASSERT(NULL != p_text);
    CRIT_ASSERT(text_size > 0);

    if (report_rt_ctx.file_opened)
    {
        (void) SdMngr_f_write(&report_rt_ctx.rep_file_hnd, p_text, text_size, NULL);
    }
}

void sxband_sched_report_close(void)
{
    if (report_rt_ctx.file_opened)
    {
        (void) SdMngr_f_close(&report_rt_ctx.rep_file_hnd);

        // delete any previous report with the same name if it exists
        (void) SdMngr_f_unlink(report_rt_ctx.p_actual_rep_fname);

        // rename the temporary report to the actual name requested by the user
        if (FR_OK != SdMngr_f_rename(TEMP_REPORT_FNAME, report_rt_ctx.p_actual_rep_fname))
        {
            EXEH_HANDLE(eEXEHSeverity_Warning,
                        (int32_t) EXEH_SXB_SCHED_REPORT_SXB_LOG_RENAME_ERR);
        }
    }
}
