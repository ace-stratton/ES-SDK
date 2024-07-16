/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_stats.c
 * @brief    Handles MAC driver run-time statistics
 *
 * @}
 */

#include <string.h>

#include "esps_drv_cdef.h"
#include "esps_drv_stats.h"

/// Reset the counters
void MAC_Stats_resetEventCounters(macStats_t fp_sStats)
{
    if(fp_sStats != NULL)
        (void)memset((void *)fp_sStats, (uint32_t) 0, sizeof(macStats_t));

    // !!! Ensure that slots where MAC_Stats_storeEventMin() function will be used
    // are initialized with 0xFFFFFFFF to be able to store minimum values
    // Currently there are no such values!
}

/// Trigger an event to be saved
void MAC_Stats_triggerEvent(macStats_t fp_sStats, eMACStatId_t fp_sEvtId)
{
    if((fp_sEvtId < eMACStatId_MAX) && (fp_sStats != NULL))
        ++fp_sStats[(uint8_t) fp_sEvtId];
}

/// Trigger more than one event to be saved
void MAC_Stats_triggerMultiEvent(macStats_t fp_sStats, eMACStatId_t fp_sEvtId, const uint32_t fp_u32CounterValue)
{
    if((fp_sEvtId < eMACStatId_MAX) && (fp_sStats != NULL))
        fp_sStats[(uint8_t) fp_sEvtId] += fp_u32CounterValue;
}

/// Storing the minimum possible value for a parameter
void MAC_Stats_storeEventMin(macStats_t fp_sStats, eMACStatId_t fp_sEvtId, const uint32_t fp_u32CurrentValue)
{
    if((fp_sEvtId < eMACStatId_MAX) && (fp_sStats != NULL))
    {
        if(fp_sStats[(uint8_t) fp_sEvtId] > fp_u32CurrentValue)
            fp_sStats[(uint8_t) fp_sEvtId] = fp_u32CurrentValue;
    }
}

/// Store the maximum possible value for an event
void MAC_Stats_storeEventMax(macStats_t fp_sStats, eMACStatId_t fp_sEvtId, const uint32_t fp_u32CurrentValue)
{
    if((fp_sEvtId < eMACStatId_MAX) && (fp_sStats != NULL))
    {
        if(fp_sStats[(uint8_t) fp_sEvtId] < fp_u32CurrentValue)
            fp_sStats[(uint8_t) fp_sEvtId] = fp_u32CurrentValue;
    }
}

/// Retrieve the counter for an specific event
uint32_t MAC_Stats_getEventCounter(macStats_t fp_sStats, eMACStatId_t fp_sEvtId)
{
    return ((fp_sEvtId < eMACStatId_MAX) && (fp_sStats != NULL)) ? (fp_sStats[(uint8_t) fp_sEvtId]) : ((uint32_t) 0);
}
