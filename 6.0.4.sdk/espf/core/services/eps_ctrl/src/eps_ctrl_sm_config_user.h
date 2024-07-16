/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef EPS_CTRL_SM_CONFIG_USER_H
#define EPS_CTRL_SM_CONFIG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libhsm.h"

// USER_CODE_START::@main@
/**
 * @addtogroup eps_ctrl
 * @{
 *
 * @file     eps_ctrl_sm_config_user.h
 * @brief    Generated EPS Control libhsm main header
 *
 * @}
 */
// USER_CODE_END::@main@

// Entry/Exit functions
void eps_ctrl_sm_on_exit_off(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void eps_ctrl_sm_on_entry_active_request(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void eps_ctrl_sm_on_entry_retry_request(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);
void eps_ctrl_sm_on_entry_finish_request(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent);

// Guard condition functions
bool eps_ctrl_sm_guard_response_timeout_elapsed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool eps_ctrl_sm_guard_retries_left(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool eps_ctrl_sm_guard_max_retries(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool eps_ctrl_sm_guard_queue_not_empty(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);
bool eps_ctrl_sm_guard_queue_empty(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent);

// Action handlers

#ifdef __cplusplus
};
#endif

#endif  // #ifndef EPS_CTRL_SM_CONFIG_USER_H
