/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef INC_APPLICATION_ESPS_DRV_H_
#define INC_APPLICATION_ESPS_DRV_H_

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_dispatcher_thread.h
 * @brief    ESPS I Driver message dispatcher thread
 *
 * @}
 */

#include "esps_drv_def.h"

/**
 * @brief Initialise the message dispatcher
 * @param fp_eInterface: MAC interface
 */
void DISP_vThreadInit(eMACInterface_t fp_eInterface);

/**
 * @brief Trigger the event to to force the dispatcher loop to run
 * @param fp_eInterface: MAC interface
 */
void DISP_vActivateDispatcherThread(eMACInterface_t fp_eInterface);

#endif /* INC_APPLICATION_ESPS_DRV_H_ */
