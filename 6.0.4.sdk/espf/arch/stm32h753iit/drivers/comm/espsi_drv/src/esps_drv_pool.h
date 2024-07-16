/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_POOL_H
#define ESPS_DRV_POOL_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_pool.h
 * @brief    MAC Message Pools interface
 *
 * @}
 */

#include "esps_drv_ct.h"

/******************************************************************************
 * Private Function Prototypes
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the memory pools for a certain interface.
 *
 * @param fp_psMACIntf: interface to initialize
 * @retval true: initialization is OK
 * @retval false: something went wrong
 */
    bool MAC_POOL_bPoolInit(sMACInterfaceState_t * fp_psMACIntf);

/**
 * Allocate a new entry from the transmission pool.
 *
 * @param fp_psMACIntf - MAC interface reference.
 * @return sMACTXPoolEntry_t*: reference to the new pool entry, NULL if full.
 */
    sMACTXPoolEntry_t *MAC_POOL_psPoolTXNew(sMACInterfaceState_t * fp_psMACIntf);

/**
 * Allocate a new entry from the reception pool.
 *
 * @param fp_psMACIntf - MAC interface reference.
 * @return sMACRXPoolEntry_t*: reference to the new pool entry, NULL if full.
 */
    sMACRXPoolEntry_t *MAC_POOL_psPoolRXNew(sMACInterfaceState_t * fp_psMACIntf);

/**
 * Release/Free a transmission pool entry.
 *
 * @param fp_psMACIntf - MAC interface reference.
 * @param fp_psEntry   - the entry to release/free.
 */
    void MAC_POOL_vPoolTXFree(sMACInterfaceState_t * fp_psMACIntf, sMACTXPoolEntry_t * fp_psEntry);

/**
 * Release/Free a reception pool entry.
 *
 * @param fp_psMACIntf - MAC interface reference.
 * @param fp_psEntry   - the entry to release/free.
 */
    void MAC_POOL_vPoolRXFree(sMACInterfaceState_t * fp_psMACIntf, sMACRXPoolEntry_t * fp_psEntry);

#ifdef __cplusplus
};                              //extern "C" {
#endif

#endif //ESPS_DRV_POOL_H
