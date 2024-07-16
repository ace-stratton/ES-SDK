/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPF_CORE_SERVICES_EPS_CONTROL_INC_EPS_CONTROL_CT_H_
#define ESPF_CORE_SERVICES_EPS_CONTROL_INC_EPS_CONTROL_CT_H_

/**
 * @addtogroup eps_ctrl
 * @{
 *
 * @file     eps_ctrl_ct.h
 * @brief    EPS Control types
 *
 * @}
 */

#include "es_cdef.h"

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
/**
 * @brief Standard EPS channels for any Standard Platform
 */
typedef enum
{
    EPS_CTRL_CH_1,
    EPS_CTRL_CH_2,
    EPS_CTRL_CH_3,
    EPS_CTRL_CH_4,
    EPS_CTRL_CH_5,
    EPS_CTRL_CH_6,
    EPS_CTRL_CH_7,
    EPS_CTRL_CH_8,
    EPS_CTRL_CH_9,
    EPS_CTRL_CH_10,
    EPS_CTRL_CH_11,
    EPS_CTRL_CH_12,
    EPS_CTRL_CH_13,
    EPS_CTRL_CH_14,
    EPS_CTRL_CH_15,
    EPS_CTRL_CH_16,
    EPS_CTRL_CH_17,
    EPS_CTRL_CH_18,
    EPS_CTRL_CH_19,
    EPS_CTRL_CH_20,
    EPS_CTRL_CH_COUNT /**<  @note Maximum logic channels available is 20 (free bits in the event flag) */
} eps_ctrl_channels_t;

/**
 * @brief Return result from eps control operations
 */
typedef enum
{
    EPS_CTRL_FAIL,
    EPS_CTRL_DONE,
    EPS_CTRL_PENDING,
    EPS_CTRL_TIMEOUT,

    EPS_CTRL_COUNT
} eps_ctrl_result_t;

/**
 * @brief EPS Control request type (set or get requests)
 */
enum
{
    EPS_CTRL_REQ_INVALID,
    EPS_CTRL_REQ_SET_CH,
    EPS_CTRL_REQ_GET_CH,
};

/**
 * @brief Request
 */
typedef struct
{
    uint32_t            type;            /**< Set or get request */
    uint32_t            wait_flag;       /**< Flag for the user thread to wait for */
    eps_ctrl_channels_t channel;         /**< EPS channel */
    bool                state;           /**< ON (true) or OFF (false) */
    bool                wait_cancelled;  /**< Flag indicating if the requesting thread no longer waits for completion */
} eps_ctrl_request_t;

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

#endif /* ESPF_CORE_SERVICES_EPS_CONTROL_INC_EPS_CONTROL_CT_H_ */
