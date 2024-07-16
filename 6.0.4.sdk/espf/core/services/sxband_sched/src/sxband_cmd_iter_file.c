/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup es_sxband
 * @{
 *
 * @file     sxband_cmd_iter_file.c
 * @brief    S/X Band Command List File Iterator implementation
 *
 * Provides command list iteration from a file using the standard if_sxband_pl_ctrl_cmd_iter
 * interface.
 *
 * @}
 *
 */

#include "es_cdef.h"
#include <string.h>
#include "sxband_cmd_iter_file.h"
#include "sxband_cmd_iter_types.h"
#include "SdMngr.h"
#include "assertions.h"
#include "sxband_cmd_iter_cmn.h"

static inline uint32_t min(const uint32_t num1, const uint32_t num2);
static bool read_data_and_verify(sxband_cmd_file_iter_ctx_t * const p_file_ctx, void * const p_data, const uint32_t exp_size);

/**
 * @brief Returns the smaller of two integers
 *
 * @param[in] num1 first number to compare
 * @param[in] num2 second number to compare
 * @returns num1 if smaller, otherwise num2
 */
static inline uint32_t min(const uint32_t num1, const uint32_t num2)
{
    return (num1 <= num2) ? num1 : num2;
}

/**
 * @brief Triggers a read of a given amount of bytes from the file in the iterator context
 *           and checks whether the expected amount was successfully read.
 *
 * The function is used to improve readability by separating logic which repeats often.
 *
 * @param[in] p_file_ctx a pointer to a file iterator context structure
 * @param[in] p_data a pointer where to store the read data from the file
 * @param[in] exp_size expected amount of bytes to read
 * @return true - if the FS read operation succeeded and all bytes were read, otherwise - false
 */
static bool read_data_and_verify(sxband_cmd_file_iter_ctx_t * const p_file_ctx, void * const p_data, const uint32_t exp_size)
{
    uint32_t bytes_read = 0U;

    p_file_ctx->fs_last_res = SdMngr_f_read(&p_file_ctx->f_hnd, p_data, exp_size, (UINT *) &bytes_read);

    return (FR_OK == p_file_ctx->fs_last_res) && (bytes_read == exp_size);
}

sxband_cmd_iter_init_status_t sxband_cmd_iter_file_init_ctx(const char * const cmd_file_name, const uint8_t cmd_file_name_size, sxband_cmd_file_iter_ctx_t * const p_file_ctx)
{
    sxband_cmd_iter_init_status_t res = SXB_INIT_STATUS_MAX;

    CRIT_ASSERT(NULL != p_file_ctx);

    if (NULL != p_file_ctx)
    {
        // if the function is called twice, the file handle shall be closed before using it again
        (void) SdMngr_f_close(&p_file_ctx->f_hnd);

        (void) memset(p_file_ctx->cmd_file_name, 0, sizeof(p_file_ctx->cmd_file_name));
        (void) memcpy(p_file_ctx->cmd_file_name, cmd_file_name, min(cmd_file_name_size, sizeof(p_file_ctx->cmd_file_name)));
        p_file_ctx->cmd_file_name[sizeof(p_file_ctx->cmd_file_name) - 1] = '\0';

        p_file_ctx->fs_last_res = SdMngr_f_open(&p_file_ctx->f_hnd, p_file_ctx->cmd_file_name, FA_READ | FA_OPEN_EXISTING);

        if (FR_OK == p_file_ctx->fs_last_res)
        {
            if (read_data_and_verify(p_file_ctx, (void *) &p_file_ctx->cmd_list_hdr, sizeof(cmd_list_hdr_t)))
            {
                if (sxband_cmd_iter_cmn_verify_hdr(&p_file_ctx->cmd_list_hdr))
                {
                    res = SXB_INIT_STATUS_OK;
                }
                else
                {
                    res = SXB_INIT_STATUS_INVALID_FILE_FORMAT;
                }
            }
            else
            {
                res = SXB_INIT_STATUS_INVALID_FILE_FORMAT;
            }
        }
        else
        {
            res = SXB_INIT_STATUS_FS_ERROR;
        }
    }

    return res;
}

pl_ctrl_iter_status_t file_iter_reset(void * const p_ctx)
{
    pl_ctrl_iter_status_t res = PL_CTRL_ITER_STATUS_NOK;

    CRIT_ASSERT(NULL != p_ctx);

    if (NULL != p_ctx)
    {
        sxband_cmd_file_iter_ctx_t *p_file_ctx = (sxband_cmd_file_iter_ctx_t *) p_ctx;

        // skip file header and position on the first command entry
        p_file_ctx->fs_last_res = SdMngr_f_lseek(&p_file_ctx->f_hnd, sizeof(cmd_list_hdr_t));

        p_file_ctx->cmd_idx = 0U;

        res = PL_CTRL_ITER_STATUS_OK;
    }

    return res;
}

bool file_iter_has_next(void * const p_ctx)
{
    bool has_next = false;

    CRIT_ASSERT(NULL != p_ctx);

    if (NULL != p_ctx)
    {
        const sxband_cmd_file_iter_ctx_t *p_file_ctx = (sxband_cmd_file_iter_ctx_t *) p_ctx;

        has_next = (FR_OK == p_file_ctx->fs_last_res) ?
                   (SdMngr_f_tell(&p_file_ctx->f_hnd) < SdMngr_f_size(&p_file_ctx->f_hnd)) : false;
    }

    return has_next;
}

pl_ctrl_iter_status_t file_iter_next(void * const p_ctx, sxband_sched_cmd_t * const p_cmd)
{
    pl_ctrl_iter_status_t res = PL_CTRL_ITER_STATUS_NOK;

    CRIT_ASSERT(NULL != p_ctx);
    CRIT_ASSERT(NULL != p_cmd);

    p_cmd->p_cmd_hdr = NULL;
    p_cmd->p_data = NULL;

    if ((NULL != p_ctx) && (NULL != p_cmd))
    {
        sxband_cmd_file_iter_ctx_t *p_file_ctx = (sxband_cmd_file_iter_ctx_t *) p_ctx;

        // perform all reads regardless of status to ensure that the file position offset will be updated and iteration can
        // continue to the end of the file even if there are invalid commands inside
        bool read_ok = read_data_and_verify(p_file_ctx, (void *) &p_file_ctx->iter_cmd_entry.hdr, sizeof(cmd_list_command_hdr_t));
        read_ok = read_ok && read_data_and_verify(p_file_ctx, (void *) &p_file_ctx->iter_cmd_entry.data, p_file_ctx->iter_cmd_entry.hdr.size);
        read_ok = read_ok && read_data_and_verify(p_file_ctx, (void *) &p_file_ctx->iter_cmd_entry.footer, sizeof(cmd_list_command_footer_t));

        if (read_ok && (sxband_cmd_iter_cmn_verify_cmd(&p_file_ctx->iter_cmd_entry.hdr, p_file_ctx->iter_cmd_entry.data, p_file_ctx->iter_cmd_entry.footer.cmd_crc)))
        {
            p_cmd->cmd_idx = p_file_ctx->cmd_idx++;
            p_cmd->p_cmd_hdr = &p_file_ctx->iter_cmd_entry.hdr;
            p_cmd->p_data = p_file_ctx->iter_cmd_entry.data;

            res = PL_CTRL_ITER_STATUS_OK;
        }
        else
        {
            if (FR_OK == p_file_ctx->fs_last_res)
            {
            	res = PL_CTRL_ITER_REACHED_END;
            }
        }
    }

    return res;
}

const if_sxband_cmd_iter_t sxband_cmd_iter_file =
{
    .p_reset = &file_iter_reset,
    .p_has_next = &file_iter_has_next,
    .p_next = &file_iter_next
};
