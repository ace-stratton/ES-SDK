/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup payload_ctrl
 * @{
 *
 * @file payload_ctrl_sm_types.h
 *
 * @brief Specific types shared between the SM-generated code and the payload_ctr.c
 * @}
 */

#ifndef _PAYLOAD_CTRL_SM_TYPES_H_
#define _PAYLOAD_CTRL_SM_TYPES_H_

#include "libhsm.h"
#include "timer.h"
#include "if_payload_control.h"
#include "cmsis_os2.h"
#include "payload_ctrl.h"

#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus

/** @brief Flag values used with @ref pl_state_mon_t::pending_flags field */
enum
{
	PENDING_FLAG_CLEAR_ALL = 0x00U,
	PENDING_FLAG_START = 0x01U
};

/**	@typedef pl_state_mon_t
 *  @brief State monitoring data structure
 *
 */
typedef struct
{
	pl_state_t last_reported_state;		/**< last reported payload state */
	timer_handle_t state_timer;			/**< timer handle used to detect payload operation timeouts */
	uint8_t pending_flags;				/**< flags indicating that there is a pending operation */
	payload_ctrl_start_cfg_t start_cfg; /**< start configuration data provided with the \ref payload_ctrl_start request */
} pl_state_mon_t;

/**	@typedef pl_ctrl_runtime_context_t
 *  @brief Runtime context of the payload controller
 *
 */
typedef struct
{
	safe_bool_t  is_initialized;						/**< set to True on a call to \ref payload_ctrl_init() */
	osThreadId_t os_task_hnd;							/**< OS task handle */
	p_payload_event p_user_event_cbk;					/**< user event callback for payload events */
	pl_state_mon_t state_mon_data[PAYLOAD_COUNT];		/**< state monitoring data set for all configured payloads */
    uint32_t point_mode_timeout_ms;                      /**< time to wait for the pointing to finish */
	payload_ctrl_payload_t point_target_pl_id;			/**< payload id which requested pointing procedure */
} pl_ctrl_runtime_context_t;

extern pl_ctrl_runtime_context_t pl_ctrl_runtime_context;

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif /* _PAYLOAD_CTRL_SM_TYPES_H_ */
