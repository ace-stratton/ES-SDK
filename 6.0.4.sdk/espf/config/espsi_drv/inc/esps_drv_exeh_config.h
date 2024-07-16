/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_EXEH_CONFIG_H
#define ESPS_DRV_EXEH_CONFIG_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_exeh_config.h
 * @brief    Exception storage and handling. Used for storing and reporting
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif


// Take the definitions from the OBC
#include <es_exeh_cfg.h>
#include <es_exeh.h>

#include <esps_drv_cdef.h>
#include <esps_drv_exeh_ct.h>

#ifdef __cplusplus
}
#endif

#endif // ESPS_DRV_EXEH_CONFIG_H
