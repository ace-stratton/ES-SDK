/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __PAYLOAD_SHARED_TYPES_H__
/**
 * @addtogroup payload_ctrl
 * @{
 *
 * @file payload_shared_types.h
 * @brief Payload shared types header
 * @}
*/

#define __PAYLOAD_SHARED_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"
#include "payload_cfg.h"
#include "ffconf.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef struct
{
	float fGeoLon;
	float fGeoLat;
	float fGeoAlt;
} PACKED target_ref_t;

typedef struct
{
	uint16_t adcs_prep_time;	// in seconds
	uint8_t cntrl_mode;
	target_ref_t geo_coord;
} PACKED record_adcs_t;

typedef struct
{
	uint8_t flags;
	uint8_t pl_args[FF_LFN_BUF];
} pl_args_t;

/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/


#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef __PAYLOAD_SHARED_TYPES_H__
