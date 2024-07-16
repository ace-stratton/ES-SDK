/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __PAYLOAD_CTRL_CFG_H__
#define __PAYLOAD_CTRL_CFG_H__

/**
 * @addtogroup payload_ctrl
 * @{
 *
 * @file payload_cfg.h
 * @brief Payload Controller configuration header
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "if_payload_control.h"
#include "payload_cfg_types.h"
#include "config/payload_ctrl/payload_cfg_user.h"

/**********************************************************************
 *
 *  Public preprocessor defines
 *
 **********************************************************************/

/** @brief Timeout in milliseconds after which the main task gets automatically unblocked if
 *         @ref PAYLOAD_TASK_ACTIVATE_FLAGS is not set
 */
#define PAYLOAD_TASK_TIMEOUT_MS            (1000U)

/** @brief Timeout after which a warning is raised if the payload is
 *		   still in starting or stopping state.
 */
#define PAYLOAD_TRANSIENT_STATE_TIMEOUT_MS (10000U)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/


/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
/** @brief Used to obtain the payload-specific configuration from FLASH.
 *  @param payload_id payload identifier
 *
 *  @return pointer to the payload configuration structure
*/
const payload_immutable_cfg_t * const payload_cfg_get(
        const payload_ctrl_payload_t payload_id);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus
#endif  // #ifndef __PAYLOAD_CTRL_CFG_H__
