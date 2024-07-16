/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TRACE_H_
#define TRACE_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @addtogroup libtrace
 * @{
 * Provides a tracing functionality for software events
 *
 * @file trace.h
 * @brief Provides user interface for interfacing with the library
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "trace_types.h"

/**
 * @addtogroup libtrace
 * @{
 */

#if defined(__GNUC__) && !defined(__clang__)
/**
 * @brief Helper macro to extract at compile time the file name from a given full path
 */
#define EXTRACT_FILENAME (__builtin_strrchr(__FILE__, '/') + 1) // GCC optimization - the builtin calculates pointer to substring at compile time.
#else
#include <string.h>

#define EXTRACT_FILENAME (strrchr(__FILE__, '/') + 1)           // __FILE__ returns a null-terminated string so strrchr is not
                                                                   // expected to read out of bounds
#endif // defined(__GNUC__) && !defined(__clang__)

#ifndef OPT_VA_ARGS
#define OPT_VA_ARGS(...), ##__VA_ARGS__
#endif  // #ifndef OPT_VA_ARGS

#ifdef ES_TRACE_ENABLED
/**
 * @brief Used to log entries of level ERROR
 */
#define ES_TRACE_ERROR(format, ...) trace(EXTRACT_FILENAME, __LINE__, TRACE_LVL_ERROR, format OPT_VA_ARGS(__VA_ARGS__))

/**
 * @brief Used to log entries of level WARNING
 */
#define ES_TRACE_WARN(format, ...) trace(EXTRACT_FILENAME, __LINE__, TRACE_LVL_WARN, format OPT_VA_ARGS(__VA_ARGS__))

/**
 * @brief Used to log entries of level INFO
 */
#define ES_TRACE_INFO(format, ...) trace(EXTRACT_FILENAME, __LINE__, TRACE_LVL_INFO, format OPT_VA_ARGS(__VA_ARGS__))

/**
 * @brief Used to log entries of level FATAL
 */
#define ES_TRACE_FATAL(format, ...) trace(EXTRACT_FILENAME, __LINE__, TRACE_LVL_FATAL, format OPT_VA_ARGS(__VA_ARGS__))

/**
 * @brief Used to log entries of level DEBUG
 */
#define ES_TRACE_DEBUG(format, ...) trace(EXTRACT_FILENAME, __LINE__, TRACE_LVL_DEBUG, format OPT_VA_ARGS(__VA_ARGS__))
#else
#define ES_TRACE_ERROR(format, ...)
#define ES_TRACE_WARN(format, ...)
#define ES_TRACE_INFO(format, ...)
#define ES_TRACE_FATAL(format, ...)
#define ES_TRACE_DEBUG(format, ...)
#endif // #ifndef TRACE_ENABLED


/**
 * @brief Initialises tracing
 */
void trace_init(void);

/**
 * @brief Logs data to active channel
 *
 * @param filename Name of the file where the data is logged. Module it is string with max size TRACE_HDR_FILE_SZ
 * @param line Number of the line where the data is logged
 * @param lvl Log level @ref logging_level
 * @param fmt Printf-like format string
 * @param ... Variable number of args to be used in the format string
 */
void trace(const char* const filename, const int32_t line, trace_level_t lvl, const char* fmt, ...);

/**
 * @brief
 */
void trace_serve_chan(const uint32_t channel, uint8_t* buf, const uint32_t buf_sz);

/**
 * @brief Check if logging channel number is active.
 *
 * @param channel Channel number to check
 *
 * @return logging channel status True = active
 */
bool trace_get_chan_active(const uint32_t channel);

/**
 * @brief Gets the logging channel name/description.
 *
 * @return Logging channel name/description
 */
const char* trace_get_chan_name(const uint32_t channel);


#ifdef __cplusplus
}
#endif

#endif /* TRACE_H_ */
