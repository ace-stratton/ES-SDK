/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_queue.c
 *
 * @brief Telemetry cyclic data queue implementation
 *
 * @}
 */

#include <limits.h>
#include <string.h>
#include "es_cdef.h"
#include "telemetry_queue.h"
#include "config/telemetry/telemetry_cfg_user.h"
#include "cmsis_os2.h"
#include "assertions.h"

#define TLM_QUEUE_LOCK()        do { osMutexAcquire(tlm_queue_lock_id, osWaitForever); } while (0);
#define TLM_QUEUE_UNLOCK()      do { osMutexRelease(tlm_queue_lock_id); } while (0);

/** @brief Queue runtime context data */
typedef struct
{
    uint16_t head_idx;                /**< index of the queue head, where next message will be read from */
    uint16_t tail_idx;                /**< index of the queue tail, where next message will be written to */
    uint16_t free_bytes;              /**< number of free bytes remaining in the queue */
    uint8_t qbuf[TLM_QUEUE_SIZE];     /**< queue internal data buffer */
    tlm_queue_stats_t stats;          /**< queue run-time statistics */
} tlm_queue_rt_t;

/** @brief OS Mutex configuration structure */
static const osMutexAttr_t tlm_queue_lock_attr =
{
    "tlm_queue_mutex",    /**< Human readable mutex name */
    osMutexRecursive,     /**< Mutex attributes\ref osMutexAttr_t */
    NULL,                 /**< Memory for the mutex control block */
    0U                    /**< Size for the control block */
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t tlm_queue_lock_id;

static tlm_queue_rt_t queue_rt =
{
    .head_idx = 0U,
    .tail_idx = 0U,
    .free_bytes = TLM_QUEUE_SIZE,
    .stats.msg_popped_cnt = 0U,
    .stats.msg_pushed_cnt = 0U,
    .stats.free_bytes_min = TLM_QUEUE_SIZE,
    .stats.discarded_messages_cnt = 0U,
    .stats.max_number_of_batch_msg = 0U,
};

void telemetry_queue_init(void)
{
    queue_rt.head_idx = 0U;
    queue_rt.tail_idx = 0U;
    queue_rt.free_bytes = TLM_QUEUE_SIZE;
    queue_rt.stats.msg_pushed_cnt = 0U;
    queue_rt.stats.msg_popped_cnt = 0U;
    queue_rt.stats.free_bytes_min = TLM_QUEUE_SIZE;
    queue_rt.stats.discarded_messages_cnt = 0U;
    queue_rt.stats.max_number_of_batch_msg = 0U;
    queue_rt.stats.active_slot_id = 0U;

    if (NULL == tlm_queue_lock_id)
    {
        tlm_queue_lock_id = osMutexNew(&tlm_queue_lock_attr);
    }
}

bool telemetry_queue_push(uint8_t * const p_data, const uint16_t data_size)
{
    bool success = false;

    CRIT_ASSERT(data_size <= sizeof(queue_rt.qbuf));

    if (data_size < queue_rt.free_bytes)
    {
        TLM_QUEUE_LOCK();

        uint8_t *p_queue_pos = &queue_rt.qbuf[queue_rt.tail_idx];
        volatile uint16_t queue_idx = queue_rt.tail_idx;
        uint8_t *p_data_pos = p_data;
        uint16_t bytes_written = 0U;

        while (bytes_written < data_size)
        {
            *p_queue_pos = *p_data_pos++;

            queue_idx = (queue_idx + 1) % TLM_QUEUE_SIZE;
            p_queue_pos = &queue_rt.qbuf[queue_idx];

            bytes_written++;

            // did we end up at the first message to be read?
            if (((queue_idx + 1U) % TLM_QUEUE_SIZE) == queue_rt.head_idx)
            {
                break;
            }
        }

        queue_rt.free_bytes -= bytes_written;

        if (queue_rt.stats.free_bytes_min > queue_rt.free_bytes)
        {
            queue_rt.stats.free_bytes_min = queue_rt.free_bytes;
        }

        queue_rt.tail_idx = (queue_rt.tail_idx + bytes_written) % TLM_QUEUE_SIZE;
        success = true;

        if (queue_rt.stats.msg_pushed_cnt < ULONG_MAX)
        {
        	queue_rt.stats.msg_pushed_cnt++;
        }

        TLM_QUEUE_UNLOCK();
    }

    if ((!success) && (queue_rt.stats.discarded_messages_cnt < ULONG_MAX))
    {
        queue_rt.stats.discarded_messages_cnt++;
    }

    return success;
}

uint16_t telemetry_queue_pop(uint8_t * const p_data_buf, const uint16_t buf_size)
{
    uint16_t bytes_written = 0U;

    // are there any messages in the queue?
    if (queue_rt.free_bytes < TLM_QUEUE_SIZE)
    {
        TLM_QUEUE_LOCK();

        uint8_t *p_queue_pos = &queue_rt.qbuf[queue_rt.head_idx];
        uint16_t queue_idx = queue_rt.head_idx;
        uint8_t *p_data_pos = p_data_buf;

        while ((bytes_written < buf_size) &&
               (TLM_FRM_DELIMITER != *p_queue_pos))
        {
            *p_data_pos++ = *p_queue_pos;
            *p_queue_pos = TLM_FRM_DELIMITER;
            queue_idx = (queue_idx + 1) % TLM_QUEUE_SIZE;
            p_queue_pos = &queue_rt.qbuf[queue_idx];

            bytes_written++;
        }

        // did we actually reach the end of a frame?
        if (TLM_FRM_DELIMITER != *p_queue_pos)
        {
            // no, probably some invalid data was placed in the queue
            bytes_written = 0U;
        }
        else
        {
            *p_data_pos++ = *p_queue_pos;
            bytes_written++;

            queue_rt.free_bytes += bytes_written;
            queue_rt.head_idx = (queue_rt.head_idx + bytes_written) % TLM_QUEUE_SIZE;

            if (queue_rt.stats.msg_popped_cnt < ULONG_MAX)
            {
            	queue_rt.stats.msg_popped_cnt++;
            }
        }

        TLM_QUEUE_UNLOCK();
    }

    return bytes_written;
}

uint16_t telemetry_queue_peek(void)
{
    uint16_t bytes_read = 0U;

    if (queue_rt.free_bytes < TLM_QUEUE_SIZE)
    {
        TLM_QUEUE_LOCK();

        uint8_t *p_queue_pos = &queue_rt.qbuf[queue_rt.head_idx];
        uint16_t queue_idx = queue_rt.head_idx;

        while ((queue_idx != queue_rt.tail_idx) &&
               (TLM_FRM_DELIMITER != *p_queue_pos))
        {
            queue_idx = (queue_idx + 1) % TLM_QUEUE_SIZE;
            p_queue_pos = &queue_rt.qbuf[queue_idx];

            bytes_read++;
        }

        // did we actually reach the end of a frame?
        if (TLM_FRM_DELIMITER != *p_queue_pos)
        {
            // no, probably some invalid data was placed in the queue
            bytes_read = 0U;
        }
        else
        {
            bytes_read++;
        }

        TLM_QUEUE_UNLOCK();
    }

    return bytes_read;
}

void telemetry_queue_get_stats(tlm_queue_stats_t * const p_user_buf)
{
    TLM_QUEUE_LOCK();

    if (NULL != p_user_buf)
    {
        (void) memcpy(p_user_buf, &queue_rt.stats, sizeof(queue_rt.stats));
    }

    TLM_QUEUE_UNLOCK();
}

void telemetry_queue_update_stats(const tlm_queue_stats_id_t stat_id, const uint32_t value)
{
    TLM_QUEUE_LOCK();

    switch (stat_id)
    {
        case TLM_STATS_ID_BATCH_COUNT:
        {
            if (queue_rt.stats.max_number_of_batch_msg < value)
            {
                queue_rt.stats.max_number_of_batch_msg = value;
            }

            break;
        }

        case TLM_STATS_ID_ACTIVE_SLOT:
        {
            queue_rt.stats.active_slot_id = value;
            break;
        }

        default:
        {
            CRIT_ASSERT(false);
            break;
        }
    }

    TLM_QUEUE_UNLOCK();
}
