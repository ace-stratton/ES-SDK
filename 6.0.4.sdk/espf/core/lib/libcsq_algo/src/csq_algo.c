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
  * @addtogroup libcsq_algo Cyclic Static Queue
  * @{
  * Provides a cyclic static queue generic operations implementation.
  *
  * @file csq_algo.c
  * @brief Simple cyclic static queue operations library implementation.
  *
  * @}
  * @}
  *
  */

#include "es_cdef.h"
#include "csq_algo.h"
#include "assertions.h"

/**
 * @brief Performs a cyclic overflow of the provided index
 * @param current_idx current queue index
 * @param max_elem_cnt maximum number of entries on the queue
 * @return next index after current_idx taking into account the queue is cyclic
*/
static inline uint32_t cyc_get_next_idx(const uint32_t current_idx, const uint32_t max_elem_cnt)
{
    return (current_idx + 1) % max_elem_cnt;
}

void csq_algo_clear(csq_algo_ctx_t* const p_ctx)
{
    if (NULL != p_ctx)
    {
        p_ctx->head = 0;
        p_ctx->tail = 0;
    }
}

bool csq_algo_push(csq_algo_ctx_t* const p_ctx, const void* const p_data)
{
    bool res = false;

    if (NULL != p_ctx)
    {
        if ((csq_algo_get_free(p_ctx) > 0) || (CSQ_ALGO_POLICY_OVERWRITE == p_ctx->user_params.algo_policy))
        {
            if (NULL != p_ctx->user_params.p_user_set_slot_data)
            {
                (*p_ctx->user_params.p_user_set_slot_data)(p_ctx->tail, p_data);
                p_ctx->tail = cyc_get_next_idx(p_ctx->tail, p_ctx->user_params.queue_size);

                if (p_ctx->slots_reserved < p_ctx->user_params.queue_size)
                {
                    p_ctx->slots_reserved++;
                }

                res = true;
            }
            else
            {
                CRIT_ASSERT(false);
            }
        }
    }

    return res;
}

bool csq_algo_pop(csq_algo_ctx_t* const p_ctx, void * const p_popped_data)
{
    bool res = false;

    if ((NULL != p_ctx) && (NULL != p_popped_data))
    {
        if ((csq_algo_get_free(p_ctx) != p_ctx->user_params.queue_size) && (p_ctx->slots_reserved > 0))
        {
            if (NULL != p_ctx->user_params.p_user_get_slot_data)
            {
                (*p_ctx->user_params.p_user_get_slot_data)(p_ctx->head, p_popped_data);
                p_ctx->head = cyc_get_next_idx(p_ctx->head, p_ctx->user_params.queue_size);

                p_ctx->slots_reserved--;

                res = true;
            }
        }
    }

    return res;
}

bool csq_algo_reserve(csq_algo_ctx_t* const p_ctx, uint32_t * const p_reserve_idx)
{
    bool res = false;

    if ((NULL != p_ctx) && (NULL != p_reserve_idx))
    {
        if ((csq_algo_get_free(p_ctx) > 0) || (CSQ_ALGO_POLICY_OVERWRITE == p_ctx->user_params.algo_policy))
        {
            *p_reserve_idx = p_ctx->tail;

            p_ctx->tail = cyc_get_next_idx(p_ctx->tail, p_ctx->user_params.queue_size);

            if (p_ctx->slots_reserved < p_ctx->user_params.queue_size)
            {
                p_ctx->slots_reserved++;
            }

            res = true;
        }
    }

    return res;
}

const void* const csq_algo_peek(const csq_algo_ctx_t* const p_ctx)
{
    const void* p_res = NULL;

    if (NULL != p_ctx)
    {
        if (NULL != p_ctx->user_params.p_user_peek_slot_data)
        {
            p_res = (*p_ctx->user_params.p_user_peek_slot_data)(p_ctx->head);
        }
    }

    return p_res;
}

uint32_t csq_algo_get_free(const csq_algo_ctx_t* const p_ctx)
{
    uint32_t free_slots = 0;

    if (NULL != p_ctx)
    {
        free_slots = p_ctx->user_params.queue_size - p_ctx->slots_reserved;
    }

    return free_slots;
}
