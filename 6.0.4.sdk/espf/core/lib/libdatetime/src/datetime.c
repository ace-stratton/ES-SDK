/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libdatetime
 * @{
 *
 * @file datetime.c
 * @brief Date/time utility library
 *
 * @}
 */

#include "datetime.h"
#include "config/libdatetime/datetime_cfg.h"
#include "assertions.h"
#include <time.h>


// represents Jan 1, 1970
#define UNIX_TIME_CONST   (719561U)
#define SECONDS_IN_1_HOUR (3600U)
#define SECONDS_IN_1_MIN  (60U)
#define DAYS_IN_SECONDS   (24U * SECONDS_IN_1_HOUR)


static bool datetime_is_leap_year(const uint16_t year)
{
    return (((0 == year % 4) && (0 != year % 100)) || (0 == year % 400));
}

static bool datetime_is_valid_month(const uint8_t month)
{
    return ((1 <= month) && (12 >= month));
}

static bool datetime_is_valid_year(const uint16_t year)
{
    return ((DATETIME_YEAR_MIN <= year) && (DATETIME_YEAR_MAX >= year));
}

static uint8_t datetime_days_in_month(const datetime_date_t * const p_date)
{
    static const uint8_t days_in_month[12] =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
      //Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec
    };

    CRIT_ASSERT(NULL != p_date);

    uint8_t days = 0;

    if (datetime_is_valid_year(p_date->year) &&
        datetime_is_valid_month(p_date->mon))
    {
        if (datetime_is_leap_year(p_date->year) && (2 == p_date->mon))
        {
            days = days_in_month[p_date->mon - 1] + 1;
        }
        else
        {
            days = days_in_month[p_date->mon - 1];
        }
    }

    return days;
}

bool datetime_is_valid_time(const datetime_time_t * const time)
{
    CRIT_ASSERT(NULL != time);

    return ((time->hour < 24) &&
            (time->min  < 60) &&
            (time->sec  < 60) &&
            (time->ms   < 1000U) &&
            (time->us   < 1000U));
}

bool datetime_is_valid_date(const datetime_date_t * const p_date)
{
    CRIT_ASSERT(NULL != p_date);

    bool valid = false;

    uint8_t days_in_month = datetime_days_in_month(p_date);
    if ((0 < p_date->day) && (days_in_month >= p_date->day))
    {
        valid = true;
    }

    return valid;
}

datetime_dow_t datetime_wday(const datetime_date_t * const p_date)
{
    CRIT_ASSERT(NULL != p_date);

    datetime_dow_t wd = DATETIME_DOW_INVALID;

    if (datetime_is_valid_date(p_date))
    {
        wd = (p_date->day + ((153 * (p_date->mon + 12 * ((14 - p_date->mon) / 12) - 3) + 2) / 5)
                           + (365 * (p_date->year + 4800 - ((14 - p_date->mon) / 12)))
                           + ((p_date->year + 4800 - ((14 - p_date->mon) / 12)) / 4)
                           - ((p_date->year + 4800 - ((14 - p_date->mon) / 12)) / 100)
                           + ((p_date->year + 4800 - ((14 - p_date->mon) / 12)) / 400)
                           - 32045) % 7;
        wd += 1;
    }

    return wd;
}

void datetime_now(datetime_stamp_t * const p_stamp)
{
    CRIT_ASSERT(NULL != p_stamp);

    datetime_cfg_get_systime(p_stamp);
}

unix_time_t datetime_to_unix(const datetime_stamp_t * const p_stamp)
{
    CRIT_ASSERT(NULL != p_stamp);

    uint16_t y;
    uint8_t m;
    uint8_t d;
    unix_time_t unix_tm_val = 0;

    if (datetime_is_valid_date(&p_stamp->date) &&
        datetime_is_valid_time(&p_stamp->time))
    {
        y = p_stamp->date.year;
        m = p_stamp->date.mon;
        d = p_stamp->date.day;

        // January and February are counted as months 13 and 14 of the previous year
        if (m <= 2)
        {
            m += 12;
            y -= 1;
        }

        // convert years to days
        unix_tm_val = (365 * y) + (y / 4) - (y / 100) + (y / 400);
        // convert months to days
        unix_tm_val += (30 * m) + (3 * (m + 1) / 5) + d;
        // Unix time starts on January 1st, 1970
        unix_tm_val -= UNIX_TIME_CONST;
        // convert days to seconds
        unix_tm_val *= DAYS_IN_SECONDS;
        //Add hours, minutes and seconds
        unix_tm_val += (SECONDS_IN_1_HOUR * p_stamp->time.hour) + (SECONDS_IN_1_MIN * p_stamp->time.min) + p_stamp->time.sec;
    }

    // return Unix time
    return unix_tm_val;
}

unix_time_t datetime_to_unix_now(void)
{
    datetime_stamp_t tstamp;
    datetime_cfg_get_systime(&tstamp);
    return datetime_to_unix(&tstamp);
}

void datetime_unix_to_tstamp(unix_time_t t, datetime_stamp_t * const p_stamp)
{
    CRIT_ASSERT(NULL != p_stamp);

    struct tm tt;
    time_t ut = (time_t)t;

    if (t >= UNIX_TIME_CONST)
    {
    	localtime_r(&ut, &tt);
        p_stamp->time.us   = 0;
        p_stamp->time.ms   = 0;
        p_stamp->time.sec  = tt.tm_sec;
        p_stamp->time.min  = tt.tm_min;
        p_stamp->time.hour = tt.tm_hour;
        p_stamp->date.year = tt.tm_year + 1900;
        p_stamp->date.mon  = tt.tm_mon + 1;
        p_stamp->date.day  = tt.tm_mday;
        p_stamp->date.wday = datetime_wday(&p_stamp->date);
    }
    else
    {
        p_stamp->time.us   = 0;
        p_stamp->time.ms   = 0;
        p_stamp->time.sec  = 0;
        p_stamp->time.min  = 0;
        p_stamp->time.hour = 0;
        p_stamp->date.year = 0;
        p_stamp->date.mon  = 0;
        p_stamp->date.day  = 0;
        p_stamp->date.wday = DATETIME_DOW_INVALID;
    }
}

bool datetime_decrement_timestamp(datetime_date_t * p_date, datetime_time_t* p_time)
{
    datetime_date_t temp_date;
    datetime_time_t temp_time;
    if ((NULL == p_date) || (NULL == p_time))
    {
        return false;
    }

    if ((false == datetime_is_valid_time(p_time)) || (false == datetime_is_valid_date(p_date)))
    {
        return false;
    }

    temp_time = *p_time;

    if (0 < temp_time.sec)
    {
        temp_time.sec--;
        if (false == datetime_is_valid_time(&temp_time))
        {
            return false;
        }
        *p_time = temp_time;
        return true;
    }
    temp_time.sec = 59;

    if (0 < temp_time.min)
    {
        temp_time.min--;
        if (false == datetime_is_valid_time(&temp_time))
        {
            return false;
        }
        *p_time = temp_time;
        return true;
    }
    temp_time.min = 59;

    if (0 < temp_time.hour)
    {
        temp_time.hour--;
        if (false == datetime_is_valid_time(&temp_time))
        {
            return false;
        }
        *p_time = temp_time;
        return true;
    }
    temp_time.hour = 23;
    if (false == datetime_is_valid_time(&temp_time))
    {
        return false;
    }

    temp_date = *p_date;

    if (1 < temp_date.day)
    {
        temp_date.day--;
        temp_date.wday = datetime_wday(&temp_date);
        if (DATETIME_DOW_INVALID == temp_date.wday)
        {
            return false;
        }
        *p_time = temp_time;
        *p_date = temp_date;
        return true;
    }

    if (1 < temp_date.mon)
    {
        temp_date.mon--;
        temp_date.day = datetime_days_in_month(&temp_date);
        temp_date.wday = datetime_wday(&temp_date);
        if (DATETIME_DOW_INVALID == temp_date.wday)
        {
            return false;
        }
        *p_time = temp_time;
        *p_date = temp_date;
        return true;
    }

    if (DATETIME_YEAR_MIN >= temp_date.year)
    {
        return false;
    }
    temp_date.mon = 12;
    temp_date.year--;
    temp_date.day = datetime_days_in_month(&temp_date);
    temp_date.wday = datetime_wday(&temp_date);
    if (DATETIME_DOW_INVALID == temp_date.wday)
    {
        return false;
    }
    *p_time = temp_time;
    *p_date = temp_date;
    return true;
}
