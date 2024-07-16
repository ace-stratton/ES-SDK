/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CAN_H_
#define CAN_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup can
 * @{
 * Provide an interface for the CAN communication
 *
 * @file can.h
 *
 * @brief CAN driver
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


/** @brief Maximum size of a single CAN message data field */
#define CAN_MSG_DATA_SZ (8)

/** @brief CAN ID types */
typedef uint8_t can_id_t;
#define CAN_ID_STANDARD ((can_id_t)0)
#define CAN_ID_EXTENDED ((can_id_t)1)
#define CAN_ID_COUNT    ((can_id_t)2) /**< used for internal checks */


/** @brief CAN message type */
typedef struct
{
    uint8_t  data[CAN_MSG_DATA_SZ]; /**< message data */
    uint32_t id;                    /**< CAN ID of the message */
    can_id_t id_type;               /**< CAN ID type */
    uint8_t  data_sz;               /**< size of the message data */
} can_msg_t;


/**
 * @brief Type for the user defined RX function
 *
 * @param msg        The received message
 *
 * @retval true      Message is processed (won't be saved to the corresponding message queue)
 * @retval false     Message is not processed (will be saved to the corresponding message queue only if it exists)
 */
typedef bool(*can_rx_clbk_t)(const can_msg_t* const msg);


/**
 * @brief Register function as the RX callback for messages with extended or standard ID.
 *        Use only if you want to receive messages without polling.
 *
 * @note  Can be set only once
 * @note  The callback is executed from interrupt context
 *
 * @param type       register for messages with the give CAN ID
 * @param callback   callback function to be registered
 */
void can_reg_rx(const can_id_t type, can_rx_clbk_t callback);

/**
 * @brief Initialise CAN RX queue
 *
 * @note  The queue is created only once and its size remains fixed until reset
 *
 * @param type       the queue type to be initialised
 * @param sz         max size of the queue (if 0 the queue won't be created)
 *
 * @retval true      everything is initialised correctly
 * @retval false     error while initialising
 */
bool can_rxq_init(const can_id_t type, const uint32_t sz);

/**
 * @brief Initialise CAN TX queue
 *
 * @note  The queue is created only once and its size remains fixed until reset
 *
 * @param sz         max size of the queue (if 0 the queue will be created with default size)
 *
 * @retval true      everything is initialised correctly
 * @retval false     error while initialising
 */
bool can_txq_init(const uint32_t sz);


/**
 * @brief Initialisation CAN communication at 1Mbit speed
 *
 * @retval true      everything is initialised correctly
 * @retval false     error while initialising
 */
bool can_init(void);

/**
 * @brief DeInitialisation of the HW peripherals for CAN communication
 *
 * @retval true      disabled successfully
 * @retval false     error while stopping
 */
bool can_deinit(void);

/**
 * @brief ReInitialisation of the HW peripherals for CAN communication
 *
 * @retval true      successful
 * @retval false     error
 */
bool can_reinit(void);

/**
 * @brief Resets the specified RX queue
 *
 * @param type       the queue to reset
 *
 * @retval true      reset successfully
 * @retval false     error while resetting or queue doesn't exist
 */
bool can_rxq_reset(const can_id_t type);

/**
 * @brief Resets the TX queue
 *
 * @retval true      reset successfully
 * @retval false     error while resetting
 */
bool can_txq_reset(void);

/**
 * @brief Add a CAN message to the transmit queue
 *
 * @param msg        CAN message. The user is expected to set all fields.
 *
 * @retval true      message added successfully
 * @retval false     error while adding the message
 */
bool can_tx(const can_msg_t* const msg);

/**
 * @brief Attempt to receive a message from the corresponding receive queue
 *
 * @note  The corresponding receive queue must have been created with a call to @ref can_rxq_init()
 *
 * @param msg        the received message is stored here
 * @param type       the expected message id type
 *
 * @retval true      a message is read from the corresponding queue
 * @retval false     error, no message or queue doesn't exist
 */
bool can_rx(can_msg_t* const msg, const can_id_t type);

/**
 * @brief Process an interrupt in the CAN peripheral
 */
void can_irq_it0_handler(void);


#ifdef __cplusplus
}
#endif

#endif /* CAN_H_ */
