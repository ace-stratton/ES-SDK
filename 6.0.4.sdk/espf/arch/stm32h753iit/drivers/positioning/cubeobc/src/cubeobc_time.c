/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "cubeObc/arch/cubeObc_time.h"
#include "cmsis_os2.h"


U32 cubeObc_time_getMs(void)
{
    return osKernelGetTickCount();
}


void cubeObc_time_delay(U32 ms)
{
    osDelay(ms);
}
