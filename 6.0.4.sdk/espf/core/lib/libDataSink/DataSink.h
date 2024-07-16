/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef DATA_SINK_H
#define DATA_SINK_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup libdatasink Gateway Sink Interfaces
 * @{
 *
 * @file DataSink.h
 * @brief Definitions to provide an interface to the Data Sink
 *
 * @}
 * @}
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** data-ready notification callback prototype */
typedef void (*pCbkOnCmdResponseReady_t)(void * const pUserCtx);

/** This structure is used to provide a binary or formatted data buffer to a client */
typedef struct
{
    uint8_t  *pu8DataBuf;        /**< buffer where the response shall be provided */
    uint32_t u32ResponseSize;    /**< actual number of bytes provided in pu8DataBuf as a response */
    uint32_t u32MaxDataSize;     /**< maximum size of the u8DataBuf field */
    void     *pUserCtx;          /**< user-context data pointer passed over to the notification callback */
    pCbkOnCmdResponseReady_t onCmdResponseReady; /**< user callback to invoke when the buffer data is ready */
    bool     is_all_data_in_buf; /**< true: the full data was accommodated in the response buffer;
                                      false: the response buffer cannot accommodate the full data */
} sUserResponseCtx_t;

/**
 * @brief The function is used to notify the user that the buffer is ready
 *
 * @param pUserRespCtx pointer to a user-provided context
 */
void notify_buf_complete(sUserResponseCtx_t * const pUserRespCtx);

/**
 * @brief Appends formatted data to the buffer specified by the user
 *
 * @param pUserRespCtx pointer to a user-provided context
 * @param format `printf`-like format string
 * @param ... variable list of arguments which match the given `format` string
 */
void append_formatted_buf(sUserResponseCtx_t * const pUserRespCtx, const char * format, ...);

/**
 * @brief Appends data to a user provided buffer
 *
 * @param pUserRespCtx pointer to a user-provided context
 * @param buf buffer data to append to the user buffer
 * @param bufSize buffer data size
 */
void append_buf(sUserResponseCtx_t * const pUserRespCtx, const uint8_t *buf, const uint32_t bufSize);

/**
 * @brief Places the provided data to the user buffer and notifies the user that the buffer is ready
 *
 * @param pUserRespCtx pointer to a user-provided context
 * @param buf buffer data to place in the user buffer
 * @param bufSize buffer data size
 */
void commit_buf(sUserResponseCtx_t * const pUserRespCtx, const uint8_t *buf, const uint32_t bufSize);

/**
 * @brief Directly notifies the user that the data is part of the buffer provided via the user context structure
 *
 * @param pUserRespCtx pointer to a user-provided context
 * @param bufSize size of the data which was already written to the user response buffer
 */
void commit_buf_direct(sUserResponseCtx_t * const pUserRespCtx, const uint32_t bufSize);

/**
 * @brief Adds formatted data to the user buffer and notifies the user that the
 * response buffer can be used
 *
 * @param pUserRespCtx pointer to a user-provided context
 * @param format `printf`-like format string
 * @param ... variable list of arguments which match the given `format` string
 */
void commit_formatted_buf(sUserResponseCtx_t * const pUserRespCtx, const char * format, ...);

/**
 * @brief Opens the user buffer for writing and the user will be notified when all data
 *        is appended when @ref commmit_multi_buf_seq is called
 *
 * @param pUserRespCtx pointer to a user-provided context
 */
void start_multi_buf_seq(sUserResponseCtx_t * const pUserRespCtx);

/**
 * @brief Notifies the user that the response buffer is ready to use. Used to finalize a
 *        data transaction started by @ref start_multi_buf_seq
 *
 * @param pUserRespCtx pointer to a user-provided context
 */
void commit_multi_buf_seq(sUserResponseCtx_t * const pUserRespCtx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    // DATA_SINK_H
