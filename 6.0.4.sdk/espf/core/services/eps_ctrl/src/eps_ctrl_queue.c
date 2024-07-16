/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_ctrl
 * @{
 *
 * @file     eps_ctrl_queue.c
 * @brief    Queue to keep the requests for the EPS Control service
 *
 * @}
 */

#include "eps_ctrl_queue.h"
#include "es_exeh.h"

/*
***************************************************************************************************
* INTERNAL DEFINES
***************************************************************************************************
*/
#define QUEUE_CRITICAL_START if (osOK == osMutexAcquire(gh_eps_ctrl_queue_mutex, osWaitForever)){
#define QUEUE_CRITICAL_END osMutexRelease(gh_eps_ctrl_queue_mutex);}

#define EPS_CTRL_QUEUE_BUF_LEN (EPS_CTRL_MAX_QUEUE_REQUESTS + 1) /**< Size in number of elements of the requests queue.
                                                                      It is +1 because of the detection logic for a full
                                                                      queue (tail and head elements are one apart) */

/*
***************************************************************************************************
* INTERNAL TYPES DEFINITION
***************************************************************************************************
*/
/**
 * @brief Type representing the queue instance
 */
typedef struct
{
    eps_ctrl_request_t* buffer;
    uint8_t head_idx;
    uint8_t tail_idx;
    bool queue_full;
} queue_ctx_t;

/*
***************************************************************************************************
* EXTERNAL VARIABLES DEFINITION
***************************************************************************************************
*/
/* No External variables definition */

/*
***************************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
***************************************************************************************************
*/
/**
 * @brief Buffer for the queue
 */
static eps_ctrl_request_t queue_buffer[EPS_CTRL_QUEUE_BUF_LEN] = {0};

/**
 * @brief Instance of the queue
 */
static queue_ctx_t queue_ctx =
{
    .buffer    = queue_buffer,
    .head_idx  = 0,
    .tail_idx  = 0,
    .queue_full = false
};

/**
 * @brief Mutex to exclusively access the queue
 */
static osMutexId_t gh_eps_ctrl_queue_mutex;

/**
 * @brief Mutex attributes
 */
static const osMutexAttr_t g_eps_ctrl_queue_lock_attr =
{
    .name = "eps_ctrl_queue_mutex",
    .attr_bits = osMutexRecursive,
    .cb_mem = NULL,
    .cb_size = 0U
};
/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
***************************************************************************************************
*/
static inline uint8_t   next_idx(uint8_t idx);  /**< Move the idx one position ahead */
static inline bool      is_full(void);          /**< True if the head and tail are only one position apart */
static inline bool      is_empty(void);         /**< True if the head and tail are are the same value */

/*
***************************************************************************************************
* EXTERNAL (NON STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
eps_ctrl_result_t eps_ctrl_queue_init(void)
{
    eps_ctrl_result_t res = EPS_CTRL_FAIL;

    gh_eps_ctrl_queue_mutex = osMutexNew(&g_eps_ctrl_queue_lock_attr);
    if (NULL != gh_eps_ctrl_queue_mutex)
    {
        // Reset the values for the queue
        queue_ctx.buffer = queue_buffer;
        queue_ctx.head_idx = 0;
        queue_ctx.tail_idx = 0;
        queue_ctx.queue_full = false;

        res = EPS_CTRL_DONE;
    }

    return res;
}

eps_ctrl_result_t eps_ctrl_queue_add(eps_ctrl_channels_t ch, bool state, uint32_t type, uint32_t * const p_req_flag)
{
    eps_ctrl_result_t res = EPS_CTRL_DONE;
    uint32_t tmp_flag;

    QUEUE_CRITICAL_START
    // Verify that the queue is not full
    if ((true == is_full()) || (false == eps_ctrl_cfg_get_wait_flag(queue_ctx.tail_idx, &tmp_flag)))
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_EPS_CTRL, eEXEH_EPS_CTRL_QUEUE_FULL, __LINE__);
        res = EPS_CTRL_FAIL;
    }

    if (EPS_CTRL_DONE == res){
        // Add the request to the queue
        queue_buffer[queue_ctx.tail_idx].wait_flag = tmp_flag;
        queue_buffer[queue_ctx.tail_idx].channel = ch;
        queue_buffer[queue_ctx.tail_idx].type = type;
        queue_buffer[queue_ctx.tail_idx].state = state;
        queue_buffer[queue_ctx.tail_idx].wait_cancelled = false;

        *p_req_flag = queue_buffer[queue_ctx.tail_idx].wait_flag;

        // Increase the tail
        queue_ctx.tail_idx = next_idx(queue_ctx.tail_idx);
    }
    QUEUE_CRITICAL_END

    return res;
}

void eps_ctrl_queue_pop(void)
{
    QUEUE_CRITICAL_START
    if(false == is_empty())
    {
        // Reset the values of the request
        queue_buffer[queue_ctx.head_idx].channel = EPS_CTRL_CH_COUNT;
        queue_buffer[queue_ctx.head_idx].type = EPS_CTRL_REQ_INVALID;

        queue_ctx.head_idx = next_idx(queue_ctx.head_idx);
    }
    QUEUE_CRITICAL_END
}

eps_ctrl_request_t* eps_ctrl_queue_find(const eps_ctrl_channels_t ch, const uint32_t flag)
{
    eps_ctrl_request_t* res = NULL;
    uint32_t idx = queue_ctx.head_idx;
    uint32_t end_idx = queue_ctx.tail_idx;
    const uint32_t upper = CDEF_ELEMENT_COUNT(queue_buffer) - 1;
    bool rollover = false;

    QUEUE_CRITICAL_START

    while ((idx != end_idx) && (NULL == res))
    {
        if (idx > upper)
        {
            // Index is out of the queue buffer's upper bound. Perform a roll-over in
            // hope that the tail index of the queue is somewhere between 0 and the head one
            if (false == rollover)
            {
                // This is the first time the index rolls over the buffer size.
                // Continue searching for the tail index
                rollover = true;
                idx = 0;
            }
            else
            {
                // This is the second time the index rolls over the buffer size.
                // Tail index is probably corrupted and the search shall be aborted
                break;
            }
        }

        if ((queue_buffer[idx].channel == ch) && (queue_buffer[idx].wait_flag == flag))
        {
            res = &queue_buffer[idx];
        }

        idx++;
    }
    QUEUE_CRITICAL_END

    return res;
}

eps_ctrl_request_t* eps_ctrl_queue_head(eps_ctrl_request_t * const p_copy)
{
    if (NULL == p_copy)
    {
        return NULL;
    }
    else
    {
        eps_ctrl_request_t* p_res = NULL;

        QUEUE_CRITICAL_START
        p_res = &queue_buffer[queue_ctx.head_idx];
        *p_copy = *p_res;
        QUEUE_CRITICAL_END

        return p_res;
    }
}

bool eps_ctrl_queue_is_empty(void)
{
    bool res = false;

    QUEUE_CRITICAL_START
    res = is_empty();
    QUEUE_CRITICAL_END

    return res;
}

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
/**
 * @brief Calculates the next index of a given one
 *
 * @param idx Current index
 *
 * @return Calculated next index
 */
static inline uint8_t next_idx(uint8_t idx)
{
    return (idx + 1) % EPS_CTRL_QUEUE_BUF_LEN;
}

/**
 * @brief Checks if the queue is empty. That is if head and tail are only one position apart
 *
 * @retval true  The queue is full
 * @retval false The queue is not full
 */
static inline bool is_full(void)
{
    return (next_idx(queue_ctx.tail_idx) == queue_ctx.head_idx);
}

/**
 * @brief Checks if the queue is empty. That is if the head and tail are are the same value
 *
 * @retval true  The queue is empty
 * @retval false The queue is not empty
 */
static inline bool is_empty(void)
{
    return (queue_ctx.head_idx == queue_ctx.tail_idx);
}
