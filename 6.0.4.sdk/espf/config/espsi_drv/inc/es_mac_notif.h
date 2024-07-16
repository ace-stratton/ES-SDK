/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ES_MAC_NOTIF_H
#define ES_MAC_NOTIF_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file    es_mac_notif.h
 * @brief   MAC driver notification interface
 *          All declarations here can be implemented externally to handle
 *          different types of notifications from the driver. If no
 *          implementation is provided, then weak callbacks are used by default.
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <esps_drv.h>

/******************************************************************************
 * Public Types
 *****************************************************************************/

typedef enum {
    EMACNOTIFICATION_ON_FP_REQ_RCVD,
    EMACNOTIFICATION_ON_TL_FRAME_RCVD,
    EMACNOTIFICATION_ON_GEN_FRAME_RCVD,
    EMACNOTIFICATION_MAX
} eMacNotification_t;

typedef const void *const eventData_t;

/******************************************************************************
 * Public Functions Declarations
 *****************************************************************************/
/**
 * @brief This callback provides basic MAC event information.
 *
 * @param[input]      eMacIf   : MAC interface for which the event occurred;
 * @param[input]      eMacEvent: Event ID;
 * @param[input]      evtData  : A pointer to any event-related data (if applicable);
 * @note              The evtData parameter provided here may not refer to valid data after
 *                    leaving the callback execution context, so please ensure that you copy
 *                    any data you need out of the callback context separately before
 *                    returning the control to the caller.
 */
void MAC__Notif_OnEvent_Cfg(const eMACInterface_t eMacIf,
                        const eMacNotification_t eMacEvent,
                        eventData_t evtData);
/**
 * @brief This callback is triggered from MAC__Notif_OnEvent_Cfg
 *
 * @param[input]      eMacIf   : MAC interface for which the event occurred;
 * @param[input]      eMacEvent: Event ID;
 * @param[input]      evtData  : A pointer to any event-related data (if applicable);
 */
void MAC__Notif_OnEvent(const eMACInterface_t eMacIf,
                        const eMacNotification_t eMacEvent,
                        eventData_t evtData);

#ifdef __cplusplus
};
#endif

#endif //ES_MAC_NOTIF_H
