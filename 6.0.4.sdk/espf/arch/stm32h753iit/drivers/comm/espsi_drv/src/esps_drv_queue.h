/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_QUEUE_H
#define ESPS_DRV_QUEUE_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_queue.h
 * @brief    MAC Message Queue interface
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "esps_drv_ct.h"

/**
 * Add a new entry to the transmission queue. The entries are sorted by
 * their priority.
 *
 * @param fp_psMACIntf - MAC interface to queue the message for.
 * @param fp_psEntry   - message entry to queue.
 */
bool MAC_QUEUE_vTXQueueAdd(sMACInterfaceState_t * fp_psMACIntf, sMACTXPoolEntry_t * fp_psEntry);

/**
 * Return the first transmission queue entry and remove it at the same time.
 *
 * @param fp_psMACIntf        - MAC interface to get the message entry from.
 * @return sMACTXPoolEntry_t* - The first message, NULL if empty.
 */
sMACTXPoolEntry_t *MAC_QUEUE_vTXQueuePop(sMACInterfaceState_t * fp_psMACIntf);

/**
 * Complete the transmission by unblocking the sending thread.
 * The entry contains the ID of the thread waiting for the completion, for
 * this to work, the wait should be done with MAC__bTXQueueWaitCompletion.
 *
 * @param fp_psEntry  - The entry to complete.
 * @param fp_bSuccess - Flag indication if the transmission was finished
 *                      successfully. This value is based to the waiting thread.
 */
void MAC_QUEUE_vTXQueueComplete(sMACTXPoolEntry_t * fp_psEntry, bool fp_bSuccess);

#ifdef __cplusplus
}
#endif

#endif //ESPS_DRV_QUEUE_H
