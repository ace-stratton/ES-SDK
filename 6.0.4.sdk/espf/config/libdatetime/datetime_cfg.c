/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/** @file datetime_cfg.c
 * 
 * @brief Date/time user configuration
 *
 * @copyright (C) Endurosat
 *            Contents and presentations are protected world-wide.
 *            Any kind of using, copying etc. is prohibited without prior permission.
 *            All rights - incl. industrial property rights - are reserved.
 */

#include "datetime_cfg.h"
#include "assertions.h"
#include "sys_time.h"
#include <string.h>

void datetime_cfg_get_systime(datetime_stamp_t * const p_sys_tstamp)
{
	CRIT_ASSERT(NULL != p_sys_tstamp);

    (void) memset((void *) p_sys_tstamp, 0U, sizeof(datetime_stamp_t));

    sys_time_get_stamp(&p_sys_tstamp->date, &p_sys_tstamp->time);
}
