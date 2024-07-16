/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __SENSOR_ACC_INT_H__
#define __SENSOR_ACC_INT_H__

/**
 * @addtogroup sds
 * @{
 *
 * @file     sensor_acc_cfg.h
 * @brief    Accelerometer integration with the SDS header
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
extern sds_acc_data_if_t acc_data_prim_if;
extern sds_acc_data_if_t acc_data_sec_if;
extern sds_if_t prim_acc_base_if;
extern sds_if_t sec_acc_base_if;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SENSOR_ACC_INT_H__

