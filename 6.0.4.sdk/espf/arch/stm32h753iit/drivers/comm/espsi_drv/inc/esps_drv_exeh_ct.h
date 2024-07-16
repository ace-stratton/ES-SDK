/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_EXEH_CT_H
#define ESPS_DRV_EXEH_CT_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_exeh_ct.h
 * @brief    Exception used types definition
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Exception IDs for ESPS Driver
 */
typedef enum {
    eMACException_InvalidParameter, /**< Invalid parameter was given to a function. */
    eMACException_InitFailed,       /**< Initialization failed */
    eMACException_SystemCallFailed, /**< System call failed */
    eMACException_InvalidState,     /**< State is invalid */
    eMACException_InvalidEvent,     /**< Event is invalid for the state */
    eMACException_DispatcherBroken, /**< Dispatcher is broken */
    eMACException_NotProcessed,     /**< A received message was not processed */
    eMACException_CRCMismatch,      /**< CRC for a received message does not match */
    eMACException_TIM_NotImplemented, /**< Feature is not implemented */
    eMACException_TIMUsed,          /**< No more TIM instances available */
    eMACException_Count,
} eMACException_t;

#ifdef __cplusplus
}
#endif

#endif // ESPS_DRV_EXEH_CT_H
