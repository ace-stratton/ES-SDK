/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_DISPATCHER_H
#define ESPS_DRV_DISPATCHER_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_dispatcher.h
 * @brief    Dispatcher interface declaration
 *
 * @}
 */

#include "esps_drv.h"
#include "esps_drv_cdef.h"
#include "esps_drv_ct.h"

/******************************************************************************
 * Module Private Function Declaration
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add a received message to the dispatcher queue.
 *
 * @param fp_psDisp: reference to the dispatcher.
 * @param fp_psEntry:entry to add to the queue.
 */
void MAC_DISP_bDispatchQueueAdd(sMACDispatcher_t * fp_psDisp, sMACRXPoolEntry_t * fp_psEntry);

/**
 * Get the first message from the queue without removing it.
 *
 * @param fp_psDisp: reference to the dispatcher.
 * @return sMACRXPoolEntry_t*: reference to the message, NULL if empty.
 */
sMACRXPoolEntry_t *MAC_DISP_bDispatchQueueTop(sMACDispatcher_t * fp_psDisp);

/**
 * Remove the first element from the queue.
 *
 * @param fp_psDisp: reference to the dispatcher.
 */
void MAC_DISP_bDispatchQueuePop(sMACDispatcher_t * fp_psDisp);

/**
 * Initialize the dispatcher. Starts the dispatching thread.
 *
 * @param fp_psIntf: MAC interface reference to start dispatching.
 * @param fp_eInterface: The ID of the interface.
 */
void MAC_DISP_vDispatcherInit(sMACInterfaceState_t * fp_psIntf, eMACInterface_t fp_eInterface);

/**
 * Send a notification to whoever is listening that a message is ready to be dispatched
 *
 * @param fp_eInterface: interface to send the notification to
 */
void MAC_DISP_vDispatcherNotif(eMACInterface_t fp_eInterface);

/**
 * Process the messages in the RX queue.
 *
 * @param fp_psIntf: MAC interface reference to start dispatching.
 */
void MAC_DISP_vDispatchMessages(sMACInterfaceState_t * fp_psIntf);

#ifdef __cplusplus
}
#endif

#endif //ESPS_DRV_DISPATCHER_H
