/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _DATETIME_H_
#define _DATETIME_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup libdatetime Date and Time
 * @{
 *
 * Helper functions to correctly measure and keep track of the time across the system.
 *
 * @file datetime.h
 * @brief Date/time library public interface
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "es_cdef.h"


/** @brief Minimum year value used for date validity checks */
#define DATETIME_YEAR_MIN (2000)
/** @brief Maximum year value used for date validity checks */
#define DATETIME_YEAR_MAX (2099)


/**
 * @brief Enumeration with the days of the week
 */
typedef enum
{
    DATETIME_DOW_INVALID = 0,
    DATETIME_DOW_MONDAY,
    DATETIME_DOW_TUESDAY,
    DATETIME_DOW_WEDNESDAY,
    DATETIME_DOW_THURSDAY,
    DATETIME_DOW_FRIDAY,
    DATETIME_DOW_SATURDAY,
    DATETIME_DOW_SUNDAY,
    DATETIME_DOW_MAX
} datetime_dow_t;

/**
 * @brief Defines the structure used to report the date
 *
 */
typedef struct
{
    uint16_t year;
    uint8_t  mon;
    uint8_t  day;
    datetime_dow_t wday;
} PACKED datetime_date_t;

/**
 * @brief Defines the structure used to report the time
 *
 */
typedef struct
{
    uint8_t  hour;
    uint8_t  min;
    uint8_t  sec;
    uint16_t ms;
    uint16_t us;
} PACKED datetime_time_t;

/**
 * @brief Defines the structure used to report both date and time information
 *
 */
typedef struct
{
    datetime_date_t date;
    datetime_time_t time;
} PACKED datetime_stamp_t;

/**
 * @brief Defines the basic type used by libdatetime to represent UNIX timestamps.
 *
 */
typedef uint32_t unix_time_t;

/**
 * @brief Returns the day of the week for a given date
 *
 * @param [in] p_date User-specfied date structure
 * @return Day of week
 *          if p_date is invalid, DATETIME_DOW_INVALID is returned
 */
datetime_dow_t datetime_wday         (const datetime_date_t * const p_date);

/**
 * @brief Verifies whether a given date is valid
 *
 * @param [in] p_date User-specified date structure containing the date fields to be checked
 * @return `true` - the structure contains a valid date, `false` - otherwise
 */
bool           datetime_is_valid_date(const datetime_date_t * const p_date);

/**
 * @brief Verifies whether a given time structure contains a valid time
 *
 * @param [in] p_time User-specified time structure containing the time fields to be checked
 * @return `true` - the structure contains a valid time, `false` - otherwise
 */
bool           datetime_is_valid_time(const datetime_time_t * const p_time);

/**
 * @brief Returns the current date and time as maintained by the system
 *
 * @param [out] p_stamp A pointer to a structure to be initialized with the current date/time value
 *              On error p_tstamp is filled with 0's
 */
void           datetime_now          (datetime_stamp_t * const p_stamp);

/**
 * @brief Converts a date/time structure to a UNIX timestamp
 *
 * @param [out] p_stamp A pointer to a the user date/time structure to be converted
 * @return UNIX timestamp matching the provided user date/time values
 *              If p_stamp is invalid, 0 is returned
 */
unix_time_t    datetime_to_unix      (const datetime_stamp_t * const p_stamp);

/**
 * @brief Converts the current system date/time to a UNIX timestamp
 *
 * @return UNIX timestamp matching the system date/time setting when the function is called
 *              On error 0 is returned
 */
unix_time_t    datetime_to_unix_now  (void);

/**
 * @brief Converts the UNIX timestamp to a date/time structure
 *
 * @param [in] t UNIX timestamp. Must be >= 719561 (Jan 1, 1970)
 * @param [out] p_stamp A pointer to a the user date/time structure containing the result.
 *                      Filled 0s is something goes wrong.
 */
void datetime_unix_to_tstamp(unix_time_t t, datetime_stamp_t * const p_stamp);

/**
 * @brief decrements a datetime_time_t structure with one second
 *          if underflow happens (ie 00:00:00 => 23:59:59), decrement datetime_date_t with one day
 *
 * @param [inout] time pointer to a datetime_time_t structure, which will be decremented
 * @param [inout] date pointer to a datetime_date_t structure, which will be decremented
 *
 * @return `true` on success. `false` on error.
 *          Error may be due to NULL pointers, invalid time/date
 *          or underflow (going below the year DATETIME_YEAR_MIN).
 *          On error p_date and p_time remain unchanged.
 */
bool datetime_decrement_timestamp(datetime_date_t * p_date, datetime_time_t* p_time);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* _DATETIME_H_ */
