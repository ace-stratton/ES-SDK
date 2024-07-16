/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TRACE_CONFIG_H_
#define TRACE_CONFIG_H_

/**
 * @addtogroup libtrace
 * @{
 *
 * @file trace_config.h
 * @brief `trace` configuration public interface
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdarg.h>
#include "trace_types.h"

/**
 * @addtogroup libtrace
 * @{
 */

/**
 * @brief Initialises the `trace` library
 *
 * @param[out] chan_list Pointer to a list of user channels. Used by the core 'trace' component.
 * @param[out] chan_list_sz Size of the channels list. Used by the core 'trace' component.
 *
 */
void trace_config_init(trace_channel_t** const chan_list, uint32_t* const chan_list_sz);

/**
 * @brief Abstraction for user-implemented assertion. Asserts when condition is false.
 *
 * @param condition Parameter to be checked
 */
void trace_assert(bool condition);

/**
 * @brief Abstraction for user-implemented lock mechanism creation.
 *
 * @return NULL when lock creation fails or a valid pointer
 */
trace_lock_t trace_lock_new(void);

/**
 * @brief Abstraction for user-implemented lock mechanism acquire.
 *
 * @param lock Valid lock pointer
 */
void trace_lock_acquire(trace_lock_t lock);

/**
 * @brief Abstraction for user-implemented lock mechanism release.
 *
 * @return lock Valid lock pointer
 */
void trace_lock_release(trace_lock_t lock);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* TRACE_CONFIG_H_ */
