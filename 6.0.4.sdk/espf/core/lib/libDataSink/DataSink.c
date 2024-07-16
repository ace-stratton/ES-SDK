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
 * @file DataSink.c
 * @brief Definitions to provide an interface to the Data Sink
 *
 * @}
 * @}
 */

#include <stdarg.h>
#include "DataSink.h"

static void append_formatted_buf_va(sUserResponseCtx_t * const pUserRespCtx, const char * format, va_list args)
{
    if (NULL != pUserRespCtx)
    {
        if (NULL != pUserRespCtx->pu8DataBuf)
        {
            int chCount;
            chCount = vsnprintf((char *) &pUserRespCtx->pu8DataBuf[pUserRespCtx->u32ResponseSize],
                                (size_t ) pUserRespCtx->u32MaxDataSize - pUserRespCtx->u32ResponseSize,
                                format,
                                args);

            if ((pUserRespCtx->u32ResponseSize + (uint32_t) chCount) <= pUserRespCtx->u32MaxDataSize)
            {
                pUserRespCtx->u32ResponseSize += (uint32_t) chCount;
            }
            else
            {
                pUserRespCtx->is_all_data_in_buf = false;
                pUserRespCtx->u32ResponseSize = pUserRespCtx->u32MaxDataSize;
            }
        }
    }
}

void notify_buf_complete(sUserResponseCtx_t * const pUserRespCtx)
{
    if (NULL != pUserRespCtx)
    {
        if (NULL != pUserRespCtx->onCmdResponseReady)
        {
            pUserRespCtx->onCmdResponseReady(pUserRespCtx->pUserCtx);
        }

        pUserRespCtx->pu8DataBuf = NULL;
    }
}

void append_formatted_buf(sUserResponseCtx_t * const pUserRespCtx, const char * format, ...)
{
    va_list args;

    va_start(args, format);

    append_formatted_buf_va(pUserRespCtx, format, args);

    va_end(args);
}

void append_buf(sUserResponseCtx_t * const pUserRespCtx, const uint8_t *buf, const uint32_t bufSize)
{
    if (pUserRespCtx != NULL)
    {
        if (NULL != pUserRespCtx->pu8DataBuf)
        {
            uint32_t remBufSize = pUserRespCtx->u32MaxDataSize - pUserRespCtx->u32ResponseSize;
            if (remBufSize >= bufSize)
            {
                (void) memcpy((char *) &pUserRespCtx->pu8DataBuf[pUserRespCtx->u32ResponseSize],
                              buf,
                              bufSize);

                pUserRespCtx->u32ResponseSize += bufSize;
            }
            else
            {
                (void) memcpy((char *) &pUserRespCtx->pu8DataBuf[pUserRespCtx->u32ResponseSize],
                              buf,
                              remBufSize);

                pUserRespCtx->is_all_data_in_buf = false;
                pUserRespCtx->u32ResponseSize = pUserRespCtx->u32MaxDataSize;
            }
        }
    }
}

void commit_buf(sUserResponseCtx_t * const pUserRespCtx, const uint8_t *buf, const uint32_t bufSize)
{
    if (pUserRespCtx != NULL)
    {
        pUserRespCtx->u32ResponseSize = 0U;
        append_buf(pUserRespCtx, buf, bufSize);
        notify_buf_complete(pUserRespCtx);
    }
}

// use when the buffer data is already transferred to the pUserRespCtx-supplied buffer
void commit_buf_direct(sUserResponseCtx_t * const pUserRespCtx, const uint32_t bufSize)
{
    if (pUserRespCtx != NULL)
    {
        pUserRespCtx->u32ResponseSize = bufSize;
        notify_buf_complete(pUserRespCtx);
    }
}

void commit_formatted_buf(sUserResponseCtx_t * const pUserRespCtx, const char * format, ...)
{
    va_list args;

    va_start(args, format);

    append_formatted_buf_va(pUserRespCtx, format, args);
    notify_buf_complete(pUserRespCtx);

    va_end(args);
}

void start_multi_buf_seq(sUserResponseCtx_t * const pUserRespCtx)
{
    if (NULL != pUserRespCtx)
    {
        pUserRespCtx->u32ResponseSize = 0U;
    }
}

void commit_multi_buf_seq(sUserResponseCtx_t * const pUserRespCtx)
{
    notify_buf_complete(pUserRespCtx);
}
