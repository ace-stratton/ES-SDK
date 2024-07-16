/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup Libraries
 * @{
 *
 * @addtogroup libdatasink
 * @{
 *
 * @file FileSink.c
 * @brief Definitions to provide an interface to the File Sink interface
 *
 * @}
 * @}
 */

#include <stdarg.h>
#include "FileSink.h"

static void fappend_formatted_buf_va(file_stream_fmt_ctx_t * const p_ctx, const char *format, va_list args)
{
    if (NULL != p_ctx)
    {
        int ch_count = vsnprintf((char *) p_ctx->p_data_buf,
                                 (size_t)(p_ctx->data_buf_size),
                                 format,
                                 args);

        p_ctx->fop_status_last = SdMngr_f_write(p_ctx->p_fhnd, p_ctx->p_data_buf, (UINT) ch_count, NULL);
    }
}

void fappend_formatted_buf(file_stream_fmt_ctx_t * const p_ctx, const char *format, ...)
{
    va_list args;

    va_start(args, format);

    fappend_formatted_buf_va(p_ctx, format, args);

    va_end(args);
}

void fcommit_formatted_buf(file_stream_fmt_ctx_t * const p_ctx, const char *format, ...)
{
    va_list args;

    va_start(args, format);

    fstart_multi_buf_seq(p_ctx);
    fappend_formatted_buf_va(p_ctx, format, args);
    fcommit_multi_buf_seq(p_ctx);

    va_end(args);
}

void fstart_multi_buf_seq(file_stream_fmt_ctx_t * const p_ctx)
{
    if (NULL != p_ctx)
    {
        p_ctx->fop_status_last = SdMngr_f_open(p_ctx->p_fhnd, p_ctx->file_name, FA_CREATE_ALWAYS | FA_WRITE);
    }
}

void fcommit_multi_buf_seq(file_stream_fmt_ctx_t * const p_ctx)
{
    if (NULL != p_ctx)
    {
        p_ctx->fop_status_last = SdMngr_f_close(p_ctx->p_fhnd);
    }
}
