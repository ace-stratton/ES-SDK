/*
 * Endurosat Property
 *
 * This file provides needed implementation for micropython utime library.
 * Because the OBC is using CMSIS this interfaces are linked to the
 * proper realization from CMSIS
 */

#include "stdint.h"
#include "py/runtime.h"
#include "cmsis_os2.h"

#define MS_IN_1_SEC     (1000u)
#define US_IN_1_MS      (1000u)
#define US_IN_1_SEC     (1000000u)
#define NS_IN_1_SEC     (1000000000u)

#ifndef mp_hal_ticks_ms
mp_uint_t
mp_hal_ticks_ms(void)
{
    return (MS_IN_1_SEC * osKernelGetTickCount()) / osKernelGetSysTimerFreq();
}
#endif

#ifndef mp_hal_ticks_us
mp_uint_t
mp_hal_ticks_us(void)
{
    return ((US_IN_1_SEC * osKernelGetTickCount()) / osKernelGetSysTimerFreq());
}
#endif

#ifndef mp_hal_time_ns
uint64_t
mp_hal_time_ns(void)
{
    return ((NS_IN_1_SEC * osKernelGetTickCount()) / osKernelGetSysTimerFreq());
}
#endif

#ifndef mp_hal_delay_ms
void
mp_hal_delay_ms(mp_uint_t ms)
{
    osDelay(ms);
}
#endif

#ifndef mp_hal_delay_us
void
mp_hal_delay_us(mp_uint_t us)
{
    osDelay(us / US_IN_1_MS);
}
#endif

#ifndef mp_hal_ticks_cpu
mp_uint_t
mp_hal_ticks_cpu(void)
{
    return osKernelGetTickCount();
}
#endif
