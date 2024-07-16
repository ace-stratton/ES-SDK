/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef _CSQ_ALGO_H
#define _CSQ_ALGO_H

 /**
  * @addtogroup Libraries
  * @{
  *
  * @defgroup libcsq_algo Cyclic Static Queue
  * @{
  * Provides a cyclic static queue generic operations.
  *
  * @warning The library is reentrant but not thread-safe and special care must be taken to protect the queue instance
  * defined with the CSQ_ALGO_INSTANCE() macro from race conditions in a multi-threaded environment.
  *
  * @file csq_algo.h
  * @brief Simple cyclic static queue operations library.
  *
  * @}
  * @}
  *
  */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

    /**
     * @brief A pointer to a user function which updates the given queue slot with a copy of the data pointed to by p_data
     *
     * @param[in] slot_idx index of the queue to update
     * @param[in] p_data a pointer to the actual data to update (the user knows the exact type of the data and must dereference the pointer and
     *                   copy the data to the queue because the pointer may be rendered invalid after leaving this function
    */
    typedef void (*p_set_slot_data)(const uint32_t slot_idx, const void* const p_data);

    /**
     * @brief A pointer to a user function which retrieves the data at a given slot position in the queue
     *
     * @param[in] slot_idx index of the slot data to retrieve
     * @param[in] p_data_buf a buffer to receive the requested data slot
     * @return An untyped pointer to the data contained in the given position
    */
    typedef void (*p_get_slot_data)(const uint32_t slot_idx, void* const p_data_buf);

    /**
     * @brief A pointer to a user function which retrieves a pointer to the data at a given slot position in the queue
     *
     * @param[in] slot_idx index of the slot data to retrieve
     * @return An untyped pointer to the data contained in the given position
    */
    typedef void* const (*p_peek_slot_data)(const uint32_t slot_idx);

    /**
     * @brief Defines the types of overwrite policy supported by the algorithm
    */
    typedef enum
    {
        CSQ_ALGO_POLICY_NO_OVERWRITE,       /**< does not overwrite older entries when the queue gets full */
        CSQ_ALGO_POLICY_OVERWRITE,          /**< overwrites oldest unprocessed entries if the queue gets full */
        CSQ_ALGO_POLICY_MAX                 /**< used for range checking only */
    } csq_algo_policy_t;

    /**
     * @brief Defines the basic parameters of the static queue
     *
    */
    typedef struct
    {
        uint32_t queue_size;
        csq_algo_policy_t algo_policy;
        p_set_slot_data p_user_set_slot_data;
        p_get_slot_data p_user_get_slot_data;
        p_peek_slot_data p_user_peek_slot_data;
    } csq_algo_instance_params_t;

    /**
     * @brief Defines the runtime parameters of the static queue
    */
    typedef struct
    {
        const csq_algo_instance_params_t user_params;
        uint32_t head;
        uint32_t tail;
        uint32_t slots_reserved;
    } csq_algo_ctx_t;

    /** @brief Used to define a new instance of a circular static queue which can be used with the APIs in this module */
    #define CSQ_ALGO_INSTANCE(name, q_size, policy, p_set_slot_data, p_get_slot_data, p_peek_slot_data)  \
    csq_algo_ctx_t name =                                   \
    {                                                       \
        .user_params =                                      \
        {                                                   \
            .queue_size = q_size,                           \
            .algo_policy = policy,                          \
            .p_user_set_slot_data = p_set_slot_data,        \
            .p_user_get_slot_data = p_get_slot_data,        \
            .p_user_peek_slot_data = p_peek_slot_data        \
        },                                                  \
        .head = 0,                                          \
        .tail = 0,                                          \
        .slots_reserved = 0                                 \
    }

    /**
     * @brief Clears the queue
     * @param p_ctx a pointer to the queue instance
     *
     * @note The data in the queue is not cleared, only the operational parameters.
    */
    void csq_algo_clear(csq_algo_ctx_t* const p_ctx);

    /**
     * @brief Pushes a new entry to the static queue
     * @param p_ctx a pointer to the queue instance
     * @param p_data a pointer to the data to push (the data will be forwarded to a user-provided function to make
     *               the actual copy correctly)
     * @return true: data is pushed onto the queue; false - no space in the queue left and the queue policy does not allow overwrite
     *               of older entries
    */
    bool csq_algo_push(csq_algo_ctx_t* const p_ctx, const void* const p_data);

    /**
     * @brief Reserves the next free entry in the queue.
     *
     * The function can be used to avoid some intermediate copy operations for structures containing buffers to fill.
     * @param[in] a pointer to the queue instance
     * @param[out] p_push_idx the function will provide here the index of the reserved entry so that the user can
     *                           directly manipulate the entry in his static queue
     * @return true: the entry is successfully reserved; false: there is no space in the queue and the queue policy does not allow overwrite
     */
    bool csq_algo_reserve(csq_algo_ctx_t* const p_ctx, uint32_t * const p_reserve_idx);

    /**
     * @brief Pops an entry from the static queue
     * @param[in] p_ctx a pointer to the queue instance
     * @param[out] p_popped_data a user-provided buffer to receive the next data from the queue
     * @return true: an item was popped off the queue successfully; false: there are no items in the queue
    */
    bool csq_algo_pop(csq_algo_ctx_t* const p_ctx, void * const p_popped_data);

    /**
     * @brief Obtains a pointer to the next element on the queue without actually popping it
     * @param p_ctx a pointer to the queue instance
     * @return a pointer to the next data which will be popped from the queue after calling @reg csq_algo_pop
    */
    const void* const csq_algo_peek(const csq_algo_ctx_t* const p_ctx);

    /**
     * @brief Returns the number of free slots on the queue
     * @param p_ctx a pointer to the queue instance
     * @return number of free entries in the queue
    */
    uint32_t csq_algo_get_free(const csq_algo_ctx_t* const p_ctx);

#ifdef __cplusplus
}
#endif

#endif // _CSQ_ALGO_H
