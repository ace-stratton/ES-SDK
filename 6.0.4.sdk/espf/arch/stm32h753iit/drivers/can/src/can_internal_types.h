/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CAN_INTERNAL_TYPES_H_
#define CAN_INTERNAL_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include "cmsis_os2.h"


typedef uint8_t can_request_t;
#define CAN_REQUEST_INIT    ((can_request_t)1)
#define CAN_REQUEST_DEINIT  ((can_request_t)2)
#define CAN_REQUEST_REINIT  ((can_request_t)3)


/**< @brief CAN RX context */
typedef struct
{
    osMessageQueueId_t q;                 /**< message queue */
    bool               user_callback_set; /**< RX handler set flag */
    can_rx_clbk_t      user_callback;     /**< Handler for RX messages */
} can_rx_ctx_t;


#endif /* CAN_INTERNAL_TYPES_H_ */
