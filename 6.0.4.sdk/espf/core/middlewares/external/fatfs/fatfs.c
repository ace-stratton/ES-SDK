/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "fatfs.h"
#include "sys_time.h"

// http://elm-chan.org/fsw/ff/doc/sfileinfo.html
#define DAY_BITMASK                     (0x1F)
#define MONTH_BITMASK                   (0x0F)
#define YEAR_BITMASK                    (0x7F)
#define DAY_BIT_POS                     (0)
#define MONTH_BIT_POS                   (5)
#define YEAR_BIT_POS                    (9)
#define HOUR_BITMASK                    (0x1F)
#define HOUR_BIT_POS                    (11)
#define MIN_BITMASK                     (0x3F)
#define MIN_BIT_POS                     (5)
#define SEC_BITMASK                     (0x3F)
#define SEC_BIT_POS                     (0)
#define GET_FATTIME_DATE_BASE_BIT_POS   (16)
#define FATFS_START_YEAR_OFFSET         (1980)
FATFS SDFatFS;    /* File system object for SD logical drive */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  (void)FATFS_LinkDriver(&SD_Driver, &SDFatFS);

}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
    DWORD fattime = 0;

    sys_time_t tm = { .hour = 0, .min = 0, .sec = 0, .ms = 0 };
    bool is_time_valid = sys_time_get(&tm);

    sys_date_t dt = { .day = 0, .mon = 0, .wday = 0, .year = 0 };
    bool is_date_valid = sys_time_get_date(&dt);

    if (is_time_valid && is_date_valid)
    {
        // year origin is counted from 1980 by FatFS (http://elm-chan.org/fsw/ff/doc/fattime.html)
        fattime = (DWORD) (((dt.year - FATFS_START_YEAR_OFFSET) & YEAR_BITMASK) << (GET_FATTIME_DATE_BASE_BIT_POS + YEAR_BIT_POS)) |
                  (DWORD) ((dt.mon & MONTH_BITMASK) << (GET_FATTIME_DATE_BASE_BIT_POS + MONTH_BIT_POS)) |
                  (DWORD) ((dt.day & DAY_BITMASK) << GET_FATTIME_DATE_BASE_BIT_POS) |
                  (DWORD) ((tm.hour & HOUR_BITMASK) << HOUR_BIT_POS) |
                  (DWORD) ((tm.min & MIN_BITMASK) << MIN_BIT_POS) |
                  (DWORD) ((tm.sec & SEC_BITMASK) << SEC_BIT_POS);
    }

    return fattime;
}

unix_time_t fattime_to_unix(const WORD fdate, const WORD ftime)
{
    datetime_stamp_t fat_ts;

    fat_ts.date.day = (fdate >> DAY_BIT_POS) & DAY_BITMASK;
    fat_ts.date.mon = (fdate >> MONTH_BIT_POS) & MONTH_BITMASK;
    fat_ts.date.year = ((fdate >> YEAR_BIT_POS) & YEAR_BITMASK) + FATFS_START_YEAR_OFFSET;
    fat_ts.date.wday = 0;

    fat_ts.time.hour = (ftime >> HOUR_BIT_POS) & HOUR_BITMASK;
    fat_ts.time.min = (ftime >> MIN_BIT_POS) & MIN_BITMASK;
    fat_ts.time.sec = (ftime >> SEC_BIT_POS) & SEC_BITMASK;
    fat_ts.time.ms = 0;

    return datetime_to_unix(&fat_ts);
}
