/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __SENSOR_TEMP_INT_H__
#define __SENSOR_TEMP_INT_H__

/**
 * @addtogroup sds
 * @{
 *
 * @file     sensor_temp_cfg.h
 * @brief    Panel temperature sensors integration with the SDS
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
extern sds_panel_temp_data_if_t panel_temp_data_if;
extern sds_if_t panel_temp_base_if;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __SENSOR_TEMP_INT_H__

