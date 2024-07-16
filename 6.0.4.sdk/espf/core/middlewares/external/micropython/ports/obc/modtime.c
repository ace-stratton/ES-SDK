/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <string.h>

#include "sys_time.h"

#include "py/obj.h"
#include "shared/timeutils/timeutils.h"

/// \module time - time related functions
///
/// The `time` module provides functions for getting the current time and date,
/// and for sleeping.

// Return the localtime as an 8-tuple.
mp_obj_t mp_time_localtime_get(void)
{
    // get current date and time
    sys_time_t time;
    sys_date_t date;
    (void)sys_time_get(&time);
    (void)sys_time_get_date(&date);

    mp_obj_t tuple[8] = {
        mp_obj_new_int(date.year),
        mp_obj_new_int(date.mon),
        mp_obj_new_int(date.day),
        mp_obj_new_int(time.hour),
        mp_obj_new_int(time.min),
        mp_obj_new_int(time.sec),
        mp_obj_new_int(date.wday - 1),
        mp_obj_new_int(
            timeutils_year_day(date.year, date.mon, date.day)),
    };

    return mp_obj_new_tuple(8, tuple);
}

/// Returns the number of seconds, as an integer, since 1/1/2000.
mp_obj_t mp_time_time_get(void)
{
    // get date and time
    sys_time_t time;
    sys_date_t date;

    (void)sys_time_get(&time);
    (void)sys_time_get_date(&date);

    return mp_obj_new_int(timeutils_seconds_since_epoch(
        date.year, date.mon, date.day, time.hour, time.min, time.sec));
}
