/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef LIBFILE_STACK_H
#define LIBFILE_STACK_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup libfile_stack Utilities
 * @{
 *
 * The module provides a basic stack implementation using a physical file. It is useful when
 * you need to process a list of items in a LIFO fashion which cannot potentially fit in the
 * available RAM.
 *
 * @file libfile_stack.h
 * @brief File stack library public interface
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "es_cdef.h"
#include "SdMngr.h"

/** @brief File stack library user context */
typedef struct
{
    FIL stack_file_hnd;                 /**< handle to the stack file */
    uint32_t stack_elem_cnt;            /**< number of elements on the stack */
    uint32_t stack_elem_size;           /**< size in bytes of a single element on the stack */
    TCHAR stack_file_name[FF_LFN_BUF];  /**< name of the stack file to create */
} file_stack_ctx_t;

/** @brief General return result used by the file stack library APIs */
typedef FRESULT file_stack_res_t;

/** @brief The function is responsible to create an empty file and initialize its
 *         header.
 *
 *  @param[out] p_ctx User-provided context to manage the stack. It will be
 *              initialized by the function.
 *  @param[in] p_stack_fname The name of the file to use as a temporary stack
 *  @param[in] stack_elem_size Size in bytes of a single stack element
 *
 *  @return see @ref file_stack_res_t for details on possible error codes
 */
file_stack_res_t file_stack_open(file_stack_ctx_t * const p_ctx, const TCHAR * const p_stack_fname, const uint32_t stack_elem_size);

/** @brief Pushes an element on top of the stack
 *
 *  @param[in] p_ctx User-provided context to manage the stack. It must have been
 *              initialized by the @ref file_stack_open function before use.
 *  @param[in] p_elem A pointer to the user element to copy on the file stack. It must be
 *                    of the size, specified in @ref file_stack_ctx_t::stack_elem_size.
 *
 *  @return see @ref file_stack_res_t for details on possible error codes
 */
file_stack_res_t file_stack_push(file_stack_ctx_t * const p_ctx, const void * const p_elem);

/** @brief Pops an element off the stack
 *
 *  @param[in]  p_ctx User-provided context to manage the stack. It must have been
 *                    initialized by the @ref file_stack_open function before use.
 *  @param[out] p_elem A pointer to the user buffer which will receive a copy of the element
 *                     on top of the stack
 *
 *  @return see @ref file_stack_res_t for details on possible error codes
 */
file_stack_res_t file_stack_pop(file_stack_ctx_t * const p_ctx, void * const p_elem);

/** @brief Provides the number of elements on the stack
 *
 *  @param[in]  p_ctx User-provided context to manage the stack. It must have been
 *                    initialized by the @ref file_stack_open function before use.
 *  @return number of elements on the stack
 */
uint32_t file_stack_get_elem_cnt(const file_stack_ctx_t * const p_ctx);

/** @brief The function frees all resources taken by the file stack operations and
 *         deletes the created stack file.
 *
 *  @param[out] p_ctx User-provided context to manage the stack. It will be
 *              initialized by the function.
 *  @param[in]  perform_cleanup Instructs the function to delete any temporary files it
 *              created (could be useful for debugging purposes)
 *
 *  @return see @ref file_stack_res_t for details on possible error codes
 */
file_stack_res_t file_stack_close(file_stack_ctx_t * const p_ctx, const bool perform_cleanup);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* LIBFILE_STACK_H */
