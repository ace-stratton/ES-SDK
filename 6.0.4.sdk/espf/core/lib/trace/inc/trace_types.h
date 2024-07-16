/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TRACE_TYPES_H_
#define TRACE_TYPES_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @addtogroup libtrace
 * @{
 * Provides a tracing functionality for software events
 *
 * @file trace_types.h
 * @brief Defines all types used by the trace library
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "cbuf.h"

/**
 * @addtogroup libtrace
 * @{
 */

/** @brief defines an abstraction lock type */
typedef void* trace_lock_t;

/**
 * @brief Interface for sending data to a channel
 *
 * @param data Data to be sent
 * @param data_sz Size of the data to be sent
 *
 * @return size of the successfully processes data
 */
typedef uint32_t(*trace_channel_data_send_clbk_t)(
        const uint8_t* data, const uint32_t data_sz);


/** @brief defines the interface to single user-defined 'channel' for data transmission */
typedef struct
{
    const char* name;                         /**< name/description of the channel */
    bool active;                              /**< channel status */
    const bool encoded;                       /**< channel encoding support */
    trace_lock_t lock;                        /**< individual channel lock */
    const trace_channel_data_send_clbk_t data_send; /**< function to call when sending data to the channel */
    cbuf_t cbuf;                              /**< circular buffer to store channel data */
    uint8_t* const buf;                       /**< working area for the circular buffer */
    const uint32_t buf_sz;                    /**< size of the working area */
    uint8_t levels;                           /**< bit mask storing the severity levels of trace entries allowed for this channel */
} trace_channel_t;

/** Severity level of a trace entry */
typedef enum
{
    TRACE_LVL_INFO,                           /**< used to trace important non-anomalous events, e.g. initialization stages, start of a service, etc. */
    TRACE_LVL_WARN,                           /**< used to trace anomalies that prevents proper operation, but is recoverable */
    TRACE_LVL_ERROR,                          /**< used to trace anomalies that are fatal to a functionality, but not to the system as a whole */
    TRACE_LVL_FATAL,                          /**< used to trace anomalies that are fatal to the system and require reset */
    TRACE_LVL_DEBUG,                          /**< used to output detailed information for testing and investigation purposes */
    TRACE_LVL_COUNT                           /**< number of severity levels, used for internal checks */
} trace_level_t;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* TRACE_TYPES_H_ */
