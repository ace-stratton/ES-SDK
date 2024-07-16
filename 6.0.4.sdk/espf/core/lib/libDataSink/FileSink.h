/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef FILE_SINK_H
#define FILE_SINK_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @addtogroup libdatasink
 * @{
 *
 * @file FileSink.h
 * @brief Definitions to provide an interface to the File Sink interface
 *
 * This interface aims to create a single file and populate it with formatted
 * data. It more or less complies to the standard DataSink.h interface with some
 * minor exceptions.
 *
 * @}
 * @}
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stddef.h>
#include "SdMngr.h"

// clang-format off
/** This structure is used to provide a binary or formatted data buffer to a
 * client */
typedef struct
{
    uint8_t  *p_data_buf;         /**< buffer where buffer formatting will take place */
    uint32_t data_buf_size;       /**< maximum size of the u8DataBuf field */
    FIL      *p_fhnd;             /**< A pointer to a file handle */
    FRESULT  fop_status_last;     /**< status of the last file operation */
    TCHAR    *file_name;          /**< file name to use */
} file_stream_fmt_ctx_t;
// clang-format on

/**
 * @brief The function appends formatted data to a file described by the p_ctx
 * parameter
 *
 * @param p_ctx pointer to a file descriptor structure
 * @param format `printf`-like format string
 * @param ... variable list of arguments which match the given `format` string
 */
void fappend_formatted_buf(file_stream_fmt_ctx_t * const p_ctx, const char *format, ...);

/**
 * @brief Writes a formatted buffer to a file described by the p_ctx parameter
 *
 * @param p_ctx pointer to a file descriptor structure
 * @param format `printf`-like format string
 * @param ... variable list of arguments which match the given `format` string
 */
void fcommit_formatted_buf(file_stream_fmt_ctx_t * const p_ctx, const char *format, ...);

/**
 * @brief Opens a file for buffered data
 *
 * @param p_ctx pointer to a file descriptor structure
 */
void fstart_multi_buf_seq(file_stream_fmt_ctx_t * const p_ctx);

/**
 * @brief Closes the file opened by @ref fstart_multi_buf_seq
 *
 * @param p_ctx pointer to a file descriptor structure
 */
void fcommit_multi_buf_seq(file_stream_fmt_ctx_t * const p_ctx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // FILE_SINK_H
