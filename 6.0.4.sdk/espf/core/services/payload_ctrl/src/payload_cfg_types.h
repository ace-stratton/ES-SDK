/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __PAYLOAD_CTRL_CFG_TYPES_H__
/**
 * @addtogroup payload_ctrl
 * @{
 *
 * @file payload_cfg_types.h
 * @brief Payload Controller user configuration header
 * @}
*/

#define __PAYLOAD_CTRL_CFG_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "if_payload_control.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/** @typedef payload_immutable_cfg_t
 *  @brief Payload configuration structure in FLASH
 */
typedef struct
{
    const pl_control_if_t * const p_pl_interface;    /**< a pointer to the payload manager interface */
    const pl_instance_id_t internal_inst_id;        /**< the internal id of the individual payload manager instance */
    const pl_config_t init_config;                    /**< payload-specific configuration data */
    const p_pl_event_notify_t p_pl_notif_cbk;         /**< a pointer to the payload instance notification callback */
} payload_immutable_cfg_t;

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

/**
 * @}
 * @}
 *
 */
#endif  // #ifndef __PAYLOAD_CTRL_CFG_TYPES_H__
