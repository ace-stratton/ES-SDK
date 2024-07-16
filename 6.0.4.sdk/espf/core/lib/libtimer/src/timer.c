/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libtimer
 * @{
 *
 * @file    timer.c
 * @brief   Simple timer library
 *
 * @}
 *
 */

#include "timer.h"
#include "config/libtimer/timer_cfg.h"
#include "assertions.h"
#include <limits.h>

#define TIMER_STOP_VALUE    (ULONG_MAX)

static safe_bool_t is_initialized = SAFE_FALSE;

/** @brief Calculates the delta time since a given timer was started taking
 *         into account the possible timer overflow.
 *
 *  @param[in] p_handle handle of the timer to use as a basis for the calculation
 *
 *  @return milliseconds that passed since timer start
 */
static inline uint32_t calc_delta(timer_handle_t * const p_handle)
{
    CRIT_ASSERT(IS_TRUE(is_initialized));
    CRIT_ASSERT((timer_handle_t * const) NULL != p_handle);

    uint32_t delta = 0U;

    if (IS_TRUE(p_handle->is_running))
    {
        uint32_t curr_tick_count = timer_cfg_sys_get_tick_count();
        delta = (curr_tick_count >= p_handle->timestamp) ?
                (curr_tick_count - p_handle->timestamp) :
                (curr_tick_count + ULONG_MAX - p_handle->timestamp);
    }

    return delta;
}

void timer_init(void)
{
    timer_cfg_sys_time_init();

    SET_TRUE(is_initialized);
}

void timer_start(timer_handle_t * const p_handle)
{
    CRIT_ASSERT(IS_TRUE(is_initialized));
    CRIT_ASSERT((timer_handle_t * const) NULL != p_handle);

    p_handle->timestamp = timer_cfg_sys_get_tick_count();
    SET_TRUE(p_handle->is_running);
}

bool timer_is_elapsed(timer_handle_t * const p_handle, const uint32_t ms)
{
    CRIT_ASSERT(IS_TRUE(is_initialized));
    CRIT_ASSERT((timer_handle_t * const) NULL != p_handle);

    if (IS_TRUE(p_handle->is_running))
    {
        uint32_t delta = calc_delta(p_handle);

        return (delta >= ms);
    }
    else
    {
        return true;
    }
}

void timer_stop(timer_handle_t * const p_handle)
{
    CRIT_ASSERT(IS_TRUE(is_initialized));
    CRIT_ASSERT((timer_handle_t * const) NULL != p_handle);

    p_handle->timestamp = TIMER_STOP_VALUE;
    SET_FALSE(p_handle->is_running);
}

uint32_t timer_get_elapsed_time(timer_handle_t * const p_handle)
{
    CRIT_ASSERT(IS_TRUE(is_initialized));
    CRIT_ASSERT((timer_handle_t * const) NULL != p_handle);

    return calc_delta(p_handle);
}
