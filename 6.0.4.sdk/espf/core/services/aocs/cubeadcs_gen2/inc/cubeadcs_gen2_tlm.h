/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_GEN2_TLM_H
#define CUBEADCS_GEN2_TLM_H

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_tlm.h
 * @brief    Cubeadcs Generation 2 telemetry
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"

/** @brief Telemetry mask */
#define CUBEADCS_GEN2_TLM_MASK_0 ((uint8_t) 0)
#define CUBEADCS_GEN2_TLM_MASK_1 ((uint8_t) 1)
#define CUBEADCS_GEN2_TLM_MASK_2 ((uint8_t) 2)
#define CUBEADCS_GEN2_TLM_MASK_3 ((uint8_t) 3)
#define CUBEADCS_GEN2_TLM_MASK_4 ((uint8_t) 4)
#define CUBEADCS_GEN2_TLM_MASK_MAX ((uint8_t) 5)
typedef uint8_t cubeadcs_gen2_tlm_masks_t;

/** @brief Telemetry bytes in a mask */
#define CUBEADCS_GEN2_TLM_MASK_BYTES_0 ((uint8_t) 0)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_1 ((uint8_t) 1)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_2 ((uint8_t) 2)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_3 ((uint8_t) 3)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_4 ((uint8_t) 4)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_5 ((uint8_t) 5)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_6 ((uint8_t) 6)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_7 ((uint8_t) 7)
#define CUBEADCS_GEN2_TLM_MASK_BYTES_MAX ((uint8_t) 8)
typedef uint8_t cubeadcs_gen2_tlm_mask_bytes_t;

/** @brief Telemetry timeout */
#define CUBEADCS_GEN2_TLM_TIMEOUT (500U)

/** @brief Get telemetry
 *
 *  @note This function collects the telemetry frames as configured in the NVM.
 */
void cubeadcs_gen2_tlm_get_tlm(void);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_GEN2_TLM_H */

/* ******************************************************************************************* */
