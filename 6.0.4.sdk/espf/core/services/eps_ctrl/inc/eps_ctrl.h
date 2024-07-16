/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef EPS_CONTROL_H_
#define EPS_CONTROL_H_
/**
 * @addtogroup Services
 * @{
 *
 * @defgroup eps_ctrl EPS Control
 * @{
 * Service to process the requests to control the EPS channels.
 * ### Example of usage
 *
 * ```c
 * //
 * // Module Foo implementation (Foo.c)
 * //
 * #include "eps_ctrl.h"
 *
 * void foo_calling_eps_control_service(void)
 * {
 *
 *     // To Set the state of a channel output
 *     eps_ctrl_result_t res = eps_ctrl_set_channel_output(EPS_CTRL_CH_5V_Switch_I, true);
 *     if (EPS_CTRL_DONE == res)
 *     {
 *         // Everything was done successfully
 *     }
 *     else if (EPS_CTRL_TIMEOUT == res)
 *     {
 *         // The request timeout before receiving a valid response
 *     }
 *     else if (EPS_CTRL_FAIL == res)
 *     {
 *         // An error occured while trying to set the channel
 *     }
 *
 *     // To Get the state of a power output
 *     bool my_state = false;
 *     eps_ctrl_result_t res = eps_ctrl_get_channel_output(EPS_CTRL_CH_5V_Switch_I, &my_state);
 *     if (EPS_CTRL_DONE == res)
 *     {
 *         // Everything was done successfully
 *     }
 *     else if (EPS_CTRL_TIMEOUT == res)
 *     {
 *         // The request timeout before receiving a valid response
 *     }
 *     else if (EPS_CTRL_FAIL == res)
 *     {
 *         // An error occured while trying to set the channel
 *     }
 *
 * ```
 *
 * @file eps_ctrl.h
 * @brief EPS Control Service main interface
 *
 * @}
 * @}
 *
*/

#include "cmsis_os.h"
#include "es_cdef.h"
#include "eps_ctrl_ct.h"

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL TYPES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
***************************************************************************************************
*/
/** Event to be set on a completed set or get channel request */
extern osEventFlagsId_t eps_ctrl_request_evt;

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/
/**
 * @brief Initializes the EPS controller service and start of task monitoring
 *
 * @retval true Initialization was successful
 * @retval false Initialization failed and the service is not to be used */
bool eps_ctrl_init(void);

/**
 * @brief Deinitialization of the EPS control service and stop of task monitoring
 */
void eps_ctrl_deinit(void);

/**
 * @brief Blocking call to set a power output state
 *
 * @param channel Channel to set the state of
 * @param state   Target state for the channel
 *
 * @retval EPS_CTRL_DONE    Power output state is successfully set
 * @retval EPS_CTRL_FAIL    There was an error setting the power output state
 * @retval EPS_CTRL_TIMEOUT A timeout occurred while waiting for the EPS module to process the request
 */
eps_ctrl_result_t eps_ctrl_set_channel_output(eps_ctrl_channels_t channel, bool state);

/**
 * @brief Blocking call to get a power output state
 * @param channel Channel to get the state of
 * @param state   Retrieved state of the channel
 *
 * @retval EPS_CTRL_DONE    Power output state is successfully set
 * @retval EPS_CTRL_FAIL    There was an error setting the power output state
 * @retval EPS_CTRL_TIMEOUT A timeout occurred while waiting for the EPS module to process the request
 */
eps_ctrl_result_t eps_ctrl_get_channel_output(eps_ctrl_channels_t channel, bool* p_state);

/**
 * @brief Callback that a response has been received. Triggers the SM event.
 */
void eps_ctrl_response_received_notif(void);

/**
 * @brief Unblocks the thread which has issued the currently processed request
 *
 * @note  If the notification has been cancelled (i.e. the requesting thread is no longer waiting)
 *        no event will be set
 *
 * @warning This method is designed to be called from the eps_ctrl state machine when processing of the
 *          current request has finished. Do not attempt calling it from a different context!
 */
void eps_ctrl_unblock_user_thread(void);

#endif /* EPS_CONTROL_H_ */
