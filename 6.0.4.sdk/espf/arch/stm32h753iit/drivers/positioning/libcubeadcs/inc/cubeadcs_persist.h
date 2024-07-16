/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_PERSIST_H_
#define CUBEADCS_PERSIST_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_persist.h
 * @brief    Interface for use of the nvm related functions. Used internally.
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/

#include "cubeadcs_common_types.h"
#include "nvm_app_types.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/
/** @brief Get the last status of CubeADCS as stored in the NVM
 *
 *	@param[out] psDst pointer to destination cache location
 */
void cubeadcs_persist_get_nvm_stored_status(CubeADCS_Status_t *psDst);

/** @brief Set the CubeADCS status in the NVM
 *
 *	@param[in] psSrc pointer to status to be written in NVM
 */
void cubeadcs_persist_set_nvm_stored_status(CubeADCS_Status_t *psSrc);

/** @brief Returns the status of the error handling logic
 *
 *	@retval true: the error handling logic is enabled
 *	@retval false: the error handling logic is disabled
 */
bool cubeadcs_persist_is_err_handl_en(void);

/** @brief Load the system configuration from the NVM this is used during the init of the cube adcs system
 *
 *	@param[out] psDst pointer to destination location
 */
void cubeadcs_persist_load_sys_state_cfg(CubeADCS_Cfg_t *psDst);

/** @brief Set the CubeADCS system state configuration in the NVM
 *
 *	@param[in] psSrc pointer to the system state configuration to be written in NVM
 *	@retval true: the write failed
 *	@retval false: the write was successful
 */
bool cubeadcs_persist_set_nvm_sys_state_cfg(cubeADCS_sys_state_cfg_t *psSrc);

/** @brief Get the system state configuration of CubeADCS stored in the NVM
 *
 *	@param[out] psDst pointer to destination cache location
 */
void cubeadcs_persist_get_nvm_sys_state_cfg(cubeADCS_sys_state_cfg_t *psDst);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_PERSIST_H_ */
