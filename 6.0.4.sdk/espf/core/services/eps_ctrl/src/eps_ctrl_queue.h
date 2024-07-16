/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPF_CORE_SERVICES_EPS_CONTROL_EPS_CONTROL_QUEUE_H_
#define ESPF_CORE_SERVICES_EPS_CONTROL_EPS_CONTROL_QUEUE_H_

/**
 * @addtogroup eps_ctrl
 * @{
 *
 * @file     eps_ctrl_queue.h
 * @brief    Interface for the EPS requests queue
 *
 * @}
 */

#include "eps_ctrl_cfg.h"
#include "eps_ctrl.h"

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL TYPES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/
/**
 * @brief  Initialize the queue
 *
 * @retval EPS_CTRL_DONE Initialization was successful
 * @retval EPS_CTRL_FAIL Initialization of the queue mutex failed
 *
 * @note This function shall be called only by eps_ctrl_init
 */
eps_ctrl_result_t eps_ctrl_queue_init(void);

/**
 * @brief Adds a request at the end of the queue
 * @param ch Channel concerning the request
 * @param state State to be set
 * @param type Whether it is get or set request
 * @param p_req_flag Flag to be set when the request finishes
 *
 * @return result from the operation (DONE or FAIL)
 */
eps_ctrl_result_t eps_ctrl_queue_add(eps_ctrl_channels_t ch, bool state, uint32_t type, uint32_t * const p_req_flag);

/**
 * @brief Removes the first element of the queue
 */
void eps_ctrl_queue_pop(void);

/**
 * @brief Returns a pointer to the first element in the queue. For thread-safe usage of the
 *        returned element a copy is provided in the caller's stack
 *
 * @param p_copy Pointer to memory in the caller's stack that shall hold the copy of the queue head element
 *
 * @return Pointer to the current head of the queue (NULL if the queue us empty)
 *
 */
eps_ctrl_request_t* eps_ctrl_queue_head(eps_ctrl_request_t * const p_copy);

/**
 * @brief Checks if there are no more requests in the queue to be processed
 *
 * @retval true  There are no more requests to process
 * @retval false There are still requests to process
 */
bool eps_ctrl_queue_is_empty(void);

/**
 * @brief Searches for a specific request in the queue
 *
 * @param ch   The searched element must have this as its requested channel
 * @param flag The searched element must have this as its wait flag
 *
 * @return Pointer to the queue element that matches the search criteria
 *
 * @warning Although the queue access is thread-safe, this function returns a
 *          pointer, which in itself is not. Additional synchronization should
 *          be employed if the function is used
 */
eps_ctrl_request_t* eps_ctrl_queue_find(const eps_ctrl_channels_t ch, const uint32_t flag);

#endif /* ESPF_CORE_SERVICES_EPS_CONTROL_EPS_CONTROL_QUEUE_H_ */
