/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef PAYLOAD_SCHEDULER_H_
#define PAYLOAD_SCHEDULER_H_

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup payload_sched Payload Scheduler
 * @{
 *
 * The service provides:
 * - Basic payload start scheduling based on RTC date/time.
 * - Starting of payloads with specific arguments and ADCS-controlled orientation.
 * - Scheduling from a static file with a fixed number of entries.
 * - Addition of scheduling records upon request (e.g. via externally implemented user commands).
 *
 * @file payload_scheduler.h
 * @brief Basic payload scheduler service interface
 *
 * @}
 * @}
 *
 */

#include <stdint.h>
#include <TaskMonitor.h>
#include "payload_shared_types.h"

typedef uint32_t record_time_t;

/**
 * @brief Describes the states of the scheduler
 *
 */
typedef enum
{
    SCHED_STATE_IDLE,                 /**< The payload is inactive */
    SCHED_STATE_ACTIVE_PAYLOAD,       /**< The payload is active */
	SCHED_STATE_MAX                   /**< The value is used for range checking only and does not represent a state */
} PayloadScheduler_state_t;

/**
 * @brief Payload scheduler record
 *
 * Defines all relevant parameters used by the scheduler to exercise control of the paylaod.
 */
typedef struct
{
    uint8_t       payload_id;         /**< payload identifier as defined in the payload_cfg_user.h file */
    uint8_t       flags;              /**< payload-specific flags interpreted by the payload handler */
    uint32_t      time;               /**< UNIX-timestamp specifying when the payload shall be started */
    uint16_t      duration;           /**< duration in seconds before the payload is stopped by the scheduler */
    uint16_t      payload_boot_time;  /**< number of seconds for the payload to boot or initialize (used to start the payload ahead of time) */
    record_adcs_t adcs_args;          /**< ADCS pointing control parameters */
    uint8_t       payload_args[16];   /**< payload-specific arguments (could be a configuration file name or just a data structure interpreted by the payload handler */
} __attribute__((__packed__)) record_t;

/**
 * @brief Describes the data exchanged between the ConOps implementation and the Payload scheduler.
 *
 */
typedef struct
{
	PayloadScheduler_state_t flag;          /**< Identifies the payload scheduler state */
    record_t                 sched_data;    /**< Contains the current scheduling record executed for a given payload */
} __attribute__((__packed__)) payload_flag_t;

/**
 * @brief Payload array which keeps the current scheduling state for each payload in the system.
 *
 * @note This will be deprecated in future implementations in order to provide better encapsulation.
 *
 */
extern payload_flag_t conops_payload_flags[PAYLOAD_COUNT];

/**
 * @brief Performs basic initialization of the payload scheduler.
 *
 * Initializes memory structures of the payload scheduler and starts the respective OS task.
 */
void PayloadScheduler_Init(void);

/**
 * @brief Provides the activation status of a specific payload.
 *
 * @param[in] payload_id ID of the payload for which to obtain the scheduling status.
 * @return PayloadScheduler_state_t Payload activation status
 */
PayloadScheduler_state_t PayloadScheduler_getStatus(payload_ctrl_payload_t payload_id);

/**
 * @brief Adds a new scheduling record to the schedule table (if there are free slots available).
 *
 * @param[in] payload_id ID of the payload for which to add a scheduling entry
 * @param[in] time UNIX-timestamp specifying when the payload shall be started
 * @param[in] duration duration in seconds before the payload is stopped by the scheduler
 * @param[in] adcs_data ADCS pointing control parameters
 * @param[in] flags payload-specific flags interpreted by the payload handler
 * @param[in] pay_args a pointer to a buffer keeping payload-specific arguments (could be a configuration file name or just a data structure interpreted by the payload handler
 * @return true: the scheduling record was successfully added, otherwise false
 */
bool PayloadScheduler_addRecord(const uint8_t payload_id, const record_time_t time, const uint16_t duration, record_adcs_t *const adcs_data, const uint8_t flags, const uint8_t *const pay_args);

/**
 * @brief Triggers a reload of the scheduling data from the SD card
 *
 * The actual reload is performed in the OS task of the payload scheduler.
 * The function just sets a flag to indicate the operation is requested externally.
 *
 * @param[in] p_fname A pointer to the schedule file name to load
 */
void PayloadScheduler_Reload(const char *p_fname);

/**
 * @brief Clears all scheduling records and updates the status in the file on
 * the SD card.
 *
 */
void PayloadScheduler_clearRecords(void);

#endif /* PAYLOAD_SCHEDULER_H_ */
