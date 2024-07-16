/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_GEN2_COMM_H
#define CUBEADCS_GEN2_COMM_H

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_comm.h
 * @brief    Gen2 comm layer header
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "cubeadcs_gen2_comm_types.h"

/* @brief Callback to be used by low-level driver when a Gen2 event is received
 *
 * @param[in] const uint8_t * const p_event - pointer to the event data
 *
 */
void cubeadcs_gen2_comm_events_callback(const uint8_t * const p_event);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_GEN2_COMM_H */

/* ******************************************************************************************* */
