/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef EPS_CONTROL_CONF_H_
#define EPS_CONTROL_CONF_H_
/**
 * @addtogroup eps_ctrl
 * @{
 *
 * @file     eps_ctrl_cfg.h
 * @brief    EPS Control Service configuration definitions
 *
 * @}
 */

#include "es_cdef.h"
#include "eps_ctrl_ct.h"
#include "eps_ii.h"
#include "fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolTypes.h"

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/
#define EPS_CTRL_REQ_TIMEOUT 5000      /**< Timeout for the blocking set or get request (5s = 10 retries) */

// Requests parameters
#define EPS_CTRL_MAX_QUEUE_REQUESTS 10  /**< Maximum number of queued requests. Depends on the implementation of
                                       the wait mechanism that blocks the requesting thread. Should be checked
                                       via static assertion */
#define EPS_CTRL_MAX_RETRIES  3        /**< Maximum retries to send a request to the EPS module */
#define EPS_CTRL_RESP_TIMEOUT 500      /**< Timeout to wait for a response in miliseconds */


// EPS I only has 8 GPIO to control the channel outputs.
// EPS II only has 8 GPIO and 16 power outputs to control.
// EPS M has 16 channels which are not only GPIO, they are power outputs
#define CHANNEL_OUTPUTS_LIST                                                                                \
{                                                                                                           \
    { EPS_CTRL_CH_1,    EPS1_QUERYCONTROLSINDEX_OUT1,     EPS_II_CTRL_DigOUT1,        1 }, \
    { EPS_CTRL_CH_2,    EPS1_QUERYCONTROLSINDEX_OUT2,     EPS_II_CTRL_DigOUT2,        2 }, \
    { EPS_CTRL_CH_3,    EPS1_QUERYCONTROLSINDEX_OUT3,     EPS_II_CTRL_DigOUT3,        3 }, \
    { EPS_CTRL_CH_4,    EPS1_QUERYCONTROLSINDEX_OUT4_OBC, EPS_II_CTRL_DigOUT4,        4 }, \
    { EPS_CTRL_CH_5,    EPS1_QUERYCONTROLSINDEX_OUT5,     EPS_II_CTRL_DigOUT5,        5 }, \
    { EPS_CTRL_CH_6,    EPS1_QUERYCONTROLSINDEX_OUT6,     EPS_II_CTRL_DigOUT6,        6 }, \
    { EPS_CTRL_CH_7,    EPS1_QUERYCONTROLSINDEX_OUT7,     EPS_II_CTRL_DigOUT7,        7 }, \
    { EPS_CTRL_CH_8,    EPS1_QUERYCONTROLSINDEX_OUT8,     EPS_II_CTRL_DigOUT8,        8 }, \
    { EPS_CTRL_CH_9,    EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_BBUS_RAWOutput, 9 }, \
    { EPS_CTRL_CH_10,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_12V_Master,     10}, \
    { EPS_CTRL_CH_11,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_12V_SP1_3,      11}, \
    { EPS_CTRL_CH_12,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_12V_SP1_4,      12}, \
    { EPS_CTRL_CH_13,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_12V_SP1_5,      13}, \
    { EPS_CTRL_CH_14,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_5V_Ch1_Master,  14}, \
    { EPS_CTRL_CH_15,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_5V_Ch1_SP2_3,   15}, \
    { EPS_CTRL_CH_16,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_5V_Ch1_SP2_4,   16}, \
    { EPS_CTRL_CH_17,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_5V_Ch2_Master,  0}, \
    { EPS_CTRL_CH_18,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_5V_Ch2_SP1_6,   0}, \
    { EPS_CTRL_CH_19,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_5V_Ch2_SP1_7,   0}, \
    { EPS_CTRL_CH_20,   EPS1_QUERYCONTROLSINDEX_MAX_CNT,  EPS_II_CTRL_3V3_Ch1_Master, 0}, \
}

#define EPSCTRL_POWER_OUT_X_BAND_EN     EPS_CTRL_CH_1
#define EPS_M_POWER_OUT_ADCS_3V3        EPS_CTRL_CH_1
#define EPS_M_POWER_OUT_ADCS_5V         EPS_CTRL_CH_1


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

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/
/**
 * @brief Initializes the necessary elements. Must be called at least once.
 *
 * @retval EPS_CTRL_DONE  Initialization done successfully
 * @retval EPS_CTRL_FAIL  Something went wrong
 */
eps_ctrl_result_t eps_ctrl_cfg_init(void);

/**
 * @brief Sends a request to set an EPS channel to a specific state
 * @param p_request Descriptor of the request to EPS
 *
 * @retval EPS_CTRL_DONE State of the request successfully received from the EPS
 * @retval EPS_CTRL_FAIL Something went wrong with the request
 */
eps_ctrl_result_t eps_ctrl_cfg_set_channel_output(const eps_ctrl_request_t * const p_request);

/**
 * @brief Sends a request to get the state of a specific channel
 * @param p_request Descriptor of the request to EPS
 *
 * @retval EPS_CTRL_DONE State of the request successfully received from the EPS
 * @retval EPS_CTRL_FAIL Something went wrong with the request
 */
eps_ctrl_result_t eps_ctrl_cfg_get_channel_output(const eps_ctrl_request_t * const p_request);

/**
 * @brief Gets the value of the last requested state for a channel
 * @param channel Logic channel to be set
 * @param state   Last known state (only valid if return is true)
 *
 * @retval true    Last request to this channel succeeded
 * @retval false   Last request to this channel failed
 */
bool eps_ctrl_cfg_get_last_req(eps_ctrl_channels_t channel, bool * p_state);

/**
 * @brief Notifies eps_ctrl that a response to a set channel request has been received from EPS I
 *
 * @param seq_id Sequence id of the ESPS response. It must match the seq_id of the request
 */
void eps_ctrl_cfg_set_ch_notif_eps_i(uint16_t seq_id);

/**
 * @brief Notifies eps_ctrl that a response to a get channel request has been received from EPS I
 *
 * @param seq_id     Sequence id of the ESPS response. It must match the seq_id of the request
 * @param io_config  Received EPS I configuration information from the ESPS response
 */
void eps_ctrl_cfg_get_ch_notif_eps_i(uint16_t seq_id, EPS1_ConfigurationInfo_t io_config);

/**
 * @brief Notifies eps_ctrl that a response to a set channel request has been received from EPS II
 *
 * @param seq_id  Sequence id of the ESPS response. It must match the seq_id of the request
 * @param success Indicates if the set request was successful or not
 */
void eps_ctrl_cfg_set_ch_notif_eps_ii(uint16_t seq_id, bool success);

/**
 * @brief Notifies eps_ctrl that a response to a get channel (GPIO) request has been received
 *
 * @param seq_id     Sequence id of the ESPS response. It must match the seq_id of the request
 * @param state_mask Received state mask from the ESPS response
 */
void eps_ctrl_cfg_get_ch_notif_eps_ii_gpio(uint16_t seq_id, EPSII_PDM_1_SGGPIO_Bitmask_t state_mask);

/**
 * @brief Notifies eps_ctrl that a response to a get channel (Power Output) request has been received
 *
 * @param seq_id     Sequence id of the ESPS response. It must match the seq_id of the request.
 * @param state_mask Received state mask from the ESPS response
 */
void eps_ctrl_cfg_get_ch_notif_eps_ii_sgpo(uint16_t seq_id, EPSII_PDM_1_SGPO_Bitmask_t state_mask);

/**
 * @brief Notifies eps_ctrl that a response to a set channel request has been received from EPS M
 *
 * @param seq_id sequence id of the ESPS response. It must match the seq_id of the request.
 * @param success indicates if the set request was successful or not
 *
 * @note Third Party EPS:
 *       The calls to this particular EPS are blocking. So the notification will be called
 *       even before the user thread is blocked by the event queue. The expected behaviour
 *       is that the user thread continues straight away.
 *       There is a timeout in the EPS M drivers that should be considered when implementing
 *       this specific EPS model. @see EPS_M_TIME_WAIT_SENDING
 */
void eps_ctrl_cfg_set_ch_notif_eps_m(uint16_t seq_id, bool success);

/**
 * @brief Notifies eps_ctrl that a response to a get channel request has been received from EPS M
 *
 * @param seq_id     Sequence id of the ESPS response. It must match the seq_id of the request.
 * @param state_mask Received state mask from the ESPS response
 *
 * @note Third Party EPS:
 *       The calls to this particular EPS are blocking. So the notification will be called
 *       even before the user thread is blocked by the event queue. The expected behaviour
 *       is that the user thread continues straight away.
 *       There is a timeout in the EPS M drivers that should be considered when implementing
 *       this specific EPS model. @see EPS_M_TIME_WAIT_SENDING
 */
void eps_ctrl_cfg_get_ch_notif_eps_m(uint16_t seq_id, uint16_t state_mask);

/**
 * @brief Notifies that the maximum number of retries has been reached
 */
void eps_ctrl_cfg_max_retries_notification(void);

/**
 * @brief Calculates the wait event flag for a request based on an index in the request queue
 *
 * @param wait_idx    Index in the request queue
 * @param p_wait_flag Calculated flag
 *
 * @retval true Calculation was successful and the calculated flag is valid
 * @retval false Something went wrong and the calculated flag should not be used
 */
bool eps_ctrl_cfg_get_wait_flag(const uint32_t wait_idx, uint32_t * const p_wait_flag);

/**
 * @brief Entry point of the critical section for generic synchronization with the eps_ctrl service
 *
 * @retval true  Critical section entered successfully
 * @retval false Failure in acquiring the OS object that realizes the critical section
 */
bool eps_ctrl_cfg_service_lock_get(void);

/**
 * @brief Exit point of the critical section for generic synchronization with the eps_ctrl service
 *
 * @note This function should be called only if previous call to eps_ctrl_cfg_service_lock_get was successful
 */
void eps_ctrl_cfg_service_lock_free(void);

/**
 * @brief Retrieves the channel ID and wait flag of the currently processed request.
 *
 * @param p_req_channel Target for the channel ID
 * @param p_wait_flag   Target for the wait flag
 *
 * @retval true ID and wait flag retrieved successfully
 * @retval false Some error occurred and the output values are not to be trusted
 */
bool eps_ctrl_cfg_get_channel_and_flag(eps_ctrl_channels_t * const p_req_channel, uint32_t * const p_wait_flag);

#endif /* EPS_CONTROL_CONF_H_ */
