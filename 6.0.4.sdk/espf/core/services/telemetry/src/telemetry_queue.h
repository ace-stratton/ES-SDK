/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _TELEMETRY_QUEUE_H_
#define _TELEMETRY_QUEUE_H_

/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_queue.h
 *
 * @brief This is a basic telemetry buffers queue implementation
 *
 * The module provides functions to initialize the queue and push/pop telemetry
 * buffers to/from it. The queue is statically defined and its size can be
 * changed only at build time.
 * @note The queue is specifically designed for use by the telemetry
 * service implementation and is not meant to be shared with other components in
 * the system.
 *
 * @}
 */

#include "es_cdef.h"

#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus

typedef struct
{
    uint32_t msg_pushed_cnt;          /**< number of pushed messages since system boot */
    uint32_t msg_popped_cnt;          /**< number of popped messages since system boot */
    uint32_t free_bytes_min;          /**< minimum value reached for the free space in the queue */
    uint32_t discarded_messages_cnt;  /**< number of discarded messages due to lack of space in the queue */
    uint32_t max_number_of_batch_msg; /**< maximum number of messages processed in a batch on a single run */
    uint32_t active_slot_id;          /**< identifier of the active slot where telemetry is currently stored */
} tlm_queue_stats_t;

typedef enum
{
    TLM_STATS_ID_BATCH_COUNT,         /**< Used to report the number of telemetry frames transmitted in a single batch */
    TLM_STATS_ID_ACTIVE_SLOT,         /**< Used to report the ID of the currently active file slot in which telemetry gets stored on the SD card */
    TLM_STATS_MAX                     /**< Used to perform range-checking on the values of this enumeration type */
} tlm_queue_stats_id_t;

/** @brief Prepares the telemetry queue for usage */
void telemetry_queue_init(void);

/** @brief Pushes a new frame onto the queue
 *  @param[in] p_data a pointer to the user data
 *  @param[in] data_size size of the data pointed to by p_data
 *
 *  @return true: frame successfully pushed to the queue;
 *  		false: could not add frame to queue due to lack of space
 */
bool telemetry_queue_push(uint8_t * const p_data, const uint16_t data_size);

/** @brief Pops a frame from the queue
 *  @param[out] p_data_buf a pointer to a user buffer to receive the frame from the queue
 *  @param[in] buf_size size of the buffer pointed to by p_data_buf
 *
 *  @return number of bytes written to p_data_buf; 0 - if no frames are available in the queue
 */
uint16_t telemetry_queue_pop(uint8_t * const p_data_buf, const uint16_t buf_size);

/** @brief Provides the length of the next message in the queue without affecting the queue state.
 *  @return size in bytes of the next message that @ref telemetry_queue_pop will fetch if called
 */
uint16_t telemetry_queue_peek(void);

/** @brief Provides telemetry queue run-time statistics
 *  @param[in] p_user_buf a pointer to a user buffer to receive a copy of the accummulated stats
 */
void telemetry_queue_get_stats(tlm_queue_stats_t * const p_user_buf);

/** @brief Used to updates specific internal stat counters externally.
 *  @param[in] stat_id identifier of the stats parameter to update
 *  @param[in] value specific value to use for the specified stat counter
 *
 *  @note The function is provided as a helper to enable storage of stats information related to the queue
 *        in one place for convenience.
 */
void telemetry_queue_update_stats(const tlm_queue_stats_id_t stat_id, const uint32_t value);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif /* _TELEMETRY_QUEUE_H_ */
