/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*!
********************************************************************************************
* @file payload_ctrl_cfg_user.h
* @brief Payload Controller user configuration header
********************************************************************************************
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
********************************************************************************************
*/

#ifndef __PAYLOAD_CTRL_CFG_USER_H__
#define __PAYLOAD_CTRL_CFG_USER_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "if_payload_control.h"
#include "payload_cfg_types.h"

#define PAYLOAD_EMPTY_RECORD 255

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef enum
{
	PAYLOAD_SX_BAND,
    PAYLOAD_DUMMY,
    PAYLOAD_COUNT
} payload_ctrl_payload_t;

extern const payload_immutable_cfg_t payload_cfg[];

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __PAYLOAD_CTRL_CFG_USER_H__

