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
 * @file     es_mac_notif.c
 * @brief    MAC driver notification interface default implementation
 *
 * @}
 */

#include <es_mac_notif.h>
#include "es_cdef.h"
#include "telemetry_file_sink.h"
#include "config/telemetry/telemetry_cfg_user.h"

// Implement in your own code to handle MAC driver events; this is just a default implementation for the
// linker to resolve missing references during build.
WEAK_CBK void MAC__Notif_OnEvent_Cfg(const eMACInterface_t eMacIf, const eMacNotification_t eMacEvent, eventData_t evtData)
{
    (void) eMacIf;
    (void) eMacEvent;
    (void) evtData;
}
