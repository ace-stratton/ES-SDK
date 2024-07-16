/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_GEN2_EVENTS_TYPES_H
#define CUBEADCS_GEN2_EVENTS_TYPES_H

/**
 * @addtogroup cubeadcs_gen2_events_types
 * @{
 *
 * @file     cubeadcs_gen2_events_types.h
 * @brief    Cubeadcs Generation 2 events types header. Types to be shared in the Gen2 service.
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

#define CUBEADCS_GEN2_EVENTS_ADCS_CONFIG_VALIDATION_ERROR_ID (134)
#define CUBEADCS_GEN2_EVENTS_NODE_SETUP_ERROR_ID             (144)
#define CUBEADCS_GEN2_EVENTS_NODE_JUMP_ERROR_ID              (145)
#define CUBEADCS_GEN2_EVENTS_MAG_DEPLOY_ERROR_ID             (149)
#define CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_FAILURE_ID         (150)
#define CUBEADCS_GEN2_EVENTS_NODE_FAILURE_ID                 (155)
#define CUBEADCS_GEN2_EVENTS_CONFIG_PERSIST_ERROR_ID         (251)
#define CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_WARNING_ID     (250)
#define CUBEADCS_GEN2_EVENTS_PORT_VALIDATION_ERROR_ID        (126)
#define CUBEADCS_GEN2_EVENTS_AUTO_DISCOVERY_ERROR_ID         (124)
#define CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_CRITICAL_ID        (151)
#define CUBEADCS_GEN2_EVENTS_GYRO_VOLTAGE_ERROR_ID           (152)
#define CUBEADCS_GEN2_EVENTS_GYRO_CRITICAL_ID                (154)
#define CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_ERROR_ID       (249)

/** @brief Events enum based on Gen2 documentation */
typedef enum
{
    CUBEADCS_GEN2_EVENTS_ADCS_CONFIG_VALIDATION_ERROR,
    CUBEADCS_GEN2_EVENTS_NODE_SETUP_ERROR,
    CUBEADCS_GEN2_EVENTS_NODE_JUMP_ERROR,
    CUBEADCS_GEN2_EVENTS_MAG_DEPLOY_ERROR,
    CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_FAILURE,
    CUBEADCS_GEN2_EVENTS_NODE_FAILURE,
    CUBEADCS_GEN2_EVENTS_CONFIG_PERSIST_ERROR,
    CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_WARNING,
    CUBEADCS_GEN2_EVENTS_PORT_VALIDATION_ERROR,
    CUBEADCS_GEN2_EVENTS_AUTO_DISCOVERY_ERROR,

    CUBEADCS_GEN2_EVENTS_CONTROL_LOOP_CRITICAL,
    CUBEADCS_GEN2_EVENTS_GYRO_VOLTAGE_ERROR,
    CUBEADCS_GEN2_EVENTS_GYRO_CRITICAL,
    CUBEADCS_GEN2_EVENTS_VIRTUAL_WATCHDOG_ERROR,

    CUBEADCS_GEN2_EVENTS_MAX

} cubeadcs_gen2_events_types_t;

/** @brief Events counters */
typedef struct
{
    uint16_t all_read_events[CUBEADCS_GEN2_EVENTS_MAX];
    uint16_t last_read_events[CUBEADCS_GEN2_EVENTS_MAX];
} PACKED cubeadcs_gen2_events_cnts_t;

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_GEN2_EVENTS_TYPES_H */

/* ******************************************************************************************* */
