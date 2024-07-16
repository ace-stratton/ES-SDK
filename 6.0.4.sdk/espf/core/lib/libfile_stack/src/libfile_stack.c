/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libfile_stack Utilities
 * @{
 *
 * @file libfile_stack.c
 * @brief Simple file stack utility library
 *
 * The library creates a binary file with the given name to temporarily store record entries of a specified size.
 * The file is just composed of records with the given user size and does not contain a header or footer.
 * The actual stack metadata is stored only in RAM because this data is a few bytes and doesn't need to be
 * written to the storage. Moreover the file is just temporary and will be deleted after use.
 *
 * @}
 */

#include <string.h>
#include "libfile_stack.h"
#include "debug.h"

file_stack_res_t file_stack_open(file_stack_ctx_t * const p_ctx, const TCHAR * const p_stack_fname, const uint32_t stack_elem_size)
{
    file_stack_res_t res = FR_INVALID_PARAMETER;

    if (NULL != p_ctx)
    {
        p_ctx->stack_elem_size = stack_elem_size;
        (void) strncpy(p_ctx->stack_file_name, p_stack_fname, FF_LFN_BUF);
        p_ctx->stack_file_name[FF_LFN_BUF - 1] = '\0';
        p_ctx->stack_elem_cnt = 0U;

        res = SdMngr_f_open(&p_ctx->stack_file_hnd, p_ctx->stack_file_name, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
    }

    return res;
}

file_stack_res_t file_stack_push(file_stack_ctx_t * const p_ctx, const void * const p_elem)
{
    file_stack_res_t res = FR_INVALID_PARAMETER;

    if ((NULL == p_ctx) || (NULL == p_elem))
    {
        return res;
    }

    uint32_t push_pos = p_ctx->stack_elem_size * p_ctx->stack_elem_cnt;
    res = SdMngr_f_lseek(&p_ctx->stack_file_hnd, push_pos);

    if (FR_OK == res)
    {
        UINT bytes_written = 0U;
        res = SdMngr_f_write(&p_ctx->stack_file_hnd, p_elem, p_ctx->stack_elem_size, &bytes_written);

        if ((FR_OK == res) && (bytes_written == p_ctx->stack_elem_size))
        {
            ++(p_ctx->stack_elem_cnt);
        }
    }

    return res;
}

file_stack_res_t file_stack_pop(file_stack_ctx_t * const p_ctx, void * const p_elem)
{
    file_stack_res_t res = FR_INVALID_PARAMETER;

    if ((NULL == p_ctx) || (NULL == p_elem) || (0 == p_ctx->stack_elem_cnt))
    {
        return res;
    }

    uint32_t pop_pos = (p_ctx->stack_elem_cnt - 1) * p_ctx->stack_elem_size;

    res = SdMngr_f_lseek(&p_ctx->stack_file_hnd, pop_pos);

    if (FR_OK == res)
    {
        UINT bytes_read = 0U;
        res = SdMngr_f_read(&p_ctx->stack_file_hnd, p_elem, p_ctx->stack_elem_size, &bytes_read);

        if ((FR_OK == res) && (bytes_read == p_ctx->stack_elem_size))
        {
            --(p_ctx->stack_elem_cnt);
        }
    }

    return res;
}

file_stack_res_t file_stack_close(file_stack_ctx_t * const p_ctx, const bool perform_cleanup)
{
    file_stack_res_t res = FR_INVALID_PARAMETER;

    if (NULL != p_ctx)
    {
        (void) SdMngr_f_close(&p_ctx->stack_file_hnd);

        if (perform_cleanup)
        {
            res = SdMngr_f_unlink(p_ctx->stack_file_name);
        }
    }

    return res;
}

uint32_t file_stack_get_elem_cnt(const file_stack_ctx_t * const p_ctx)
{
    return (NULL != p_ctx) ? p_ctx->stack_elem_cnt : 0;
}
