/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __SENSOR_MAG_INT_H__
#define __SENSOR_MAG_INT_H__

/**
 * @addtogroup sds
 * @{
 *
 * @file     sensor_mag_cfg.h
 * @brief    Magnetometer integration with the SDS header
 *
 * @}
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "if_sensor_data_service.h"

/**********************************************************************
 *
 * External type declarations
 *
 **********************************************************************/
extern sds_mag_data_if_t mag_data_prim_if;
extern sds_mag_data_if_t mag_data_sec_if;
extern sds_if_t prim_mag_base_if;
extern sds_if_t sec_mag_base_if;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SENSOR_MAG_INT_H__

