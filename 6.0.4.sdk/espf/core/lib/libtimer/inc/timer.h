/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _TIMER_H_
#define _TIMER_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup libtimer Timer
 * @{
 * Functions and definitions to use timers for different purposes.
 *
 * @file timer.h
 * @brief Simple timer library interface
 *
 * @}
 * @}
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus

#include <es_cdef.h>

/** Handler for a timer instance */
typedef struct
{
	uint32_t timestamp;     /**< System tick count for a given time */
	safe_bool_t is_running; /**< Whether the timer is running or not  */
} timer_handle_t;

/**
* @brief Initialize the timer library
*/
void timer_init(void);

/**
* @brief Start counting the time for the given timer
* @param p_handle: handler (pointer) to the timer
*/
void timer_start(timer_handle_t * const p_handle);

/**
* @brief Check if a certain time has passed for a specific timer
* @param p_handle: handler (pointer) to the timer
* @param ms: time in milliseconds
*
* @retval true: the time has elapsed
* @retval false: the time has yet not elapsed
*/
bool timer_is_elapsed(timer_handle_t * const p_handle, const uint32_t ms);

/**
* @brief Stop counting the time for the given timer
* @param p_handle: handler (pointer) to the timer
*/
void timer_stop(timer_handle_t * const p_handle);

/**
* @brief Get the elapsed time since the timer started counting
* @param p_handle: handler (pointer) to the timer
*
* @return time in milliseconds
*/
uint32_t timer_get_elapsed_time(timer_handle_t * const p_handle);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* OBC_SDK_INFRASTRUCTURE_LIBTIMER_INC_TIMER_H_ */
