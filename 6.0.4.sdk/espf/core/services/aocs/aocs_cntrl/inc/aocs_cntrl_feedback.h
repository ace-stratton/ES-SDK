/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef __ADCS_CNTRL_FEEDBACK_H__
#define __ADCS_CNTRL_FEEDBACK_H__

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup aocs_cntrl AOCS Control Feedback
 * @{
 * Service to report the status of a control request to the AOCS service
 *
 * @file     aocs_cntrl_feedback.h
 * @brief    AOCS Control feedback interface
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/** \typedef adcs_cntrl_result_t
 * 	@brief Indicates the result of the last requested ADCS control operation
 */
typedef enum
{
	ADCS_CNTRL_RESULT_SUCCESS,			/**< ADCS control action finished successfully */
	ADCS_CNTRL_RESULT_IN_PROGRESS,		/**< ADCS control action in progress */
	ADCS_CNTRL_RESULT_FAILED,			/**< ADCS control action failed */
	ADCS_CNTRL_RESULT_MAX,			    /**< used for range checking only */
} adcs_cntrl_result_t;

/** \typedef p_adcs_cntrl_event
 * 	@brief A notification function type used by the ADCS sub-sytem to notify users of an
 *         ADCS control event
 *
 * 	@param event	state change event id
 */
typedef void (*p_adcs_cntrl_event)(adcs_cntrl_result_t event);

/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/
/** @brief Provides a user notification function to receive ADCS control
 *         status updates from ADCS subsystem.
 *
 *  @param p_user_cb a pointer to an event notification function called when ADCS control state changes;
 *  					  if NULL specified, the subscription is removed
 *
 */
void aocs_cntrl_feedback_subscribe(p_adcs_cntrl_event const p_user_cb);

/** @brief Queries the status of the ADCS control sub-system
 *
 *	@return ADCS control status
 */
adcs_cntrl_result_t aocs_cntrl_get_status(void);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __ADCS_CNTRL_FEEDBACK_H__
