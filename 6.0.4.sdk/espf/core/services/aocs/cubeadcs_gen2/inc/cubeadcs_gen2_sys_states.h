/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_GEN2_SYS_STATES_H
#define CUBEADCS_GEN2_SYS_STATES_H

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_sys_states.h
 * @brief    Cubeadcs Generation 2 system states header
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "cubeadcs_gen2_types.h"
#include "libhsm.h"

/** @brief Maximum number of estimation modes in Gen2 */
#define CUBEADCS_GEN2_MAX_NUM_OF_ESTIMATOR_MODES (8U)
/** @brief Maximum number of control modes in Gen2 */
#define CUBEADCS_GEN2_MAX_NUM_OF_CONTROL_MODES (28U)

/** @brief Check if the requested combination of estimator and controller is allowed 
 * 
 * @param[in] control_mode Control mode
 * @param[in] estimation_mdoe Estimation mode
 * 
 * @return true if the combination is allowed, false otherwise
 * 
*/
bool cubeadcs_gen2_is_sys_state_combo_valid(const TctlmCubeComputerControlProgram8_ConModeSelect control_mode, const TctlmCubeComputerControlProgram8_EstModeSelect estimation_mdoe);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_GEN2_SYS_STATES_H */

/* ******************************************************************************************* */
