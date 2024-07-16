/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_ctrl
 * @{
 *
 * @file     eps_ctrl_cfg.c
 * @brief    EPS Control Service configuration
 *
 * @}
 */

#include "eps_ctrl_cfg.h"

#include "eps_i.h"
#include "eps_ii.h"
#include "eps_m.h"
#include "eps_ctrl.h"

#include "if_sys_conf.h"

/*
***************************************************************************************************
* INTERNAL DEFINES
***************************************************************************************************
*/
#if configUSE_16_BIT_TICKS == 1
#define EVENT_GROUP_SIZE 8
#else
#define EVENT_GROUP_SIZE 24
#endif // configUSE_16_BIT_TICKS

TODO(NOTICE! EPS channels to the modules shall be determined according to the mission requirements)

/*
***************************************************************************************************
* INTERNAL TYPES DEFINITION
***************************************************************************************************
*/
/** Channel information and request status (it will be extended with the eps i and the eps m) */
typedef struct
{
    eps_ctrl_channels_t       channel;        /**> Logic channel */
    EPS1_QueryControlsIndex_t channel_eps_i;  /**> Channel number of the eps i */
    eps_ii_ctrl_ch_t          channel_eps_ii; /**> Channel number of the eps ii */
    uint8_t                   channel_eps_m;  /**> Channel number of the third party eps */
} eps_conf_channel_info_t;

/** Keep track of the last request status */
typedef struct
{
    bool success; /**> The last request succeeded */
    bool state;   /**> Last known status */
} last_request_t;

/*
***************************************************************************************************
* EXTERNAL VARIABLES DEFINITION
***************************************************************************************************
*/

/*
***************************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
***************************************************************************************************
*/
/**
 * @brief Mutex to exclusively trigger events to the SM
 */
static const osMutexAttr_t channels_lock_attr =
{
    "eps_channels_mutex", /**> human readable mutex name */
    osMutexRecursive,     /**> attr_bits */
    NULL,                 /**> memory for control block */
    0U                    /**> size for control block*/
};

/**
 * @brief Mutex for the channels requests status
 */
static osMutexId_t channels_lock_id;    /**> */

/**
 * @brief List of the present output channels
 */
static const eps_conf_channel_info_t channel_outputs[EPS_CTRL_CH_COUNT] = CHANNEL_OUTPUTS_LIST;
static last_request_t ch_last_request[EPS_CTRL_CH_COUNT] = {0};

/**
 * @brief There can only be one active request being processed, the rest are waiting in the queue
 */
static eps_ctrl_channels_t active_request_channel = EPS_CTRL_CH_COUNT;

/**
 * @brief The ESPS request will have a sequence id that eps_ctrl uses to match with the right response
 */
static uint16_t active_request_seq_id = (uint16_t)-1;

/**
 * @brief Wait flag for the active request
 */
static uint32_t active_wait_flag = 0;

/**
 * @brief Mutex handle provided by the OS
 */
static osMutexId_t gh_eps_ctrl_cfg_service_lock;

/**
 * @brief Mutex to exclusively trigger events to the SM
 */
static const osMutexAttr_t g_eps_ctrl_cfg_service_lock_attr =
{
    .name = "eps_ctrl_mutex",
    .attr_bits = osMutexRecursive,
    .cb_mem = NULL,
    .cb_size = 0U                    // size for control block
};

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
***************************************************************************************************
*/
static inline void get_lock(void);
static inline void free_lock(void);

/*
***************************************************************************************************
* EXTERNAL (NON STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
eps_ctrl_result_t eps_ctrl_cfg_init(void)
{
    eps_ctrl_result_t res = EPS_CTRL_DONE;
    // Initialize the channels request mutex
    if (NULL == channels_lock_id)
    {
        channels_lock_id = osMutexNew(&channels_lock_attr);
        if (NULL == channels_lock_id)
        {
            res = EPS_CTRL_FAIL;
        }
    }

    // Initialize the EPS control service mutex
    gh_eps_ctrl_cfg_service_lock = osMutexNew(&g_eps_ctrl_cfg_service_lock_attr);
    if(NULL == gh_eps_ctrl_cfg_service_lock)
    {
        res = EPS_CTRL_FAIL;
    }

    return res;
}

eps_ctrl_result_t eps_ctrl_cfg_set_channel_output(const eps_ctrl_request_t * const p_request)
{
    eps_ctrl_result_t res = EPS_CTRL_FAIL;
    // Verify the request is for a valid channel
    if (p_request->channel >= EPS_CTRL_CH_COUNT)
    {
        return EPS_CTRL_FAIL;
    }

    get_lock();
    active_request_seq_id = 0;
    active_request_channel = p_request->channel;
    active_wait_flag = p_request->wait_flag;
    free_lock();

    // EPS I
    if (sys_conf_is_module_active(SYS_MODULE_ID_EPS_I))
    {
        EPS1_QueryState_t eps_i_state = p_request->state ? EPS1_QUERYSTATE_On : EPS1_QUERYSTATE_Off;

        if (eps_i_set_channel_output(channel_outputs[p_request->channel].channel_eps_i, eps_i_state))
        {
            get_lock();
            active_request_seq_id = eps_i_get_last_request_seq_id();
            // Reset the value of the last sent request (for that channel)
            ch_last_request[p_request->channel].success = false;
            ch_last_request[p_request->channel].state = p_request->state;
            free_lock();

            res = EPS_CTRL_DONE;
        }
    }
    // EPS II
    else if ( (sys_conf_is_module_active(SYS_MODULE_ID_EPS_II))
        && (eps_ii_set_channel_output(channel_outputs[p_request->channel].channel_eps_ii, p_request->state)) )
    {
        get_lock();
        active_request_seq_id = eps_ii_last_pdm_request_seq_id();
        // Reset the value of the last sent request (for that channel)
        ch_last_request[p_request->channel].success = false;
        ch_last_request[p_request->channel].state = p_request->state;
        free_lock();

        res = EPS_CTRL_DONE;
    }
    // EPS M
    else if ( (sys_conf_is_module_active(SYS_MODULE_ID_EPS_M))
        && (eps_m_set_channel_output(channel_outputs[p_request->channel].channel_eps_m, p_request->state)) )
    {
        get_lock();
        // Reset the value of the last sent request (for that channel)
        ch_last_request[p_request->channel].success = false;
        ch_last_request[p_request->channel].state = p_request->state;
        free_lock();

        res = EPS_CTRL_DONE;
    }
    else
    {
        res = EPS_CTRL_FAIL;
    }
    return res;
}

eps_ctrl_result_t eps_ctrl_cfg_get_channel_output(const eps_ctrl_request_t * const p_request)
{
    eps_ctrl_result_t res = EPS_CTRL_FAIL;

    get_lock();
    active_request_seq_id = 0;
    active_request_channel = p_request->channel;
    active_wait_flag = p_request->wait_flag;
    free_lock();

    // EPS I
    if ( (sys_conf_is_module_active(SYS_MODULE_ID_EPS_I))
        && (true == eps_i_get_channel_outputs()) )
    {
        get_lock();
        // Keep track of the request sequence ID
        active_request_seq_id = eps_i_get_last_request_seq_id();
        // Reset the value of the last sent request (for that channel)
        ch_last_request[p_request->channel].success = false;
        free_lock();

        res = EPS_CTRL_DONE;
    }
    // EPS II
    else if ( (sys_conf_is_module_active(SYS_MODULE_ID_EPS_II))
        && (true == eps_ii_get_channel_output(channel_outputs[p_request->channel].channel_eps_ii)) )
    {
        get_lock();
        // Keep track of the request sequence ID
        active_request_seq_id = eps_ii_last_pdm_request_seq_id();
        // Reset the value of the last sent request (for that channel)
        ch_last_request[p_request->channel].success = false;
        free_lock();

        res = EPS_CTRL_DONE;
    }
    // Third Party EPS
    else if (sys_conf_is_module_active(SYS_MODULE_ID_EPS_M)
        && eps_m_get_channel_outputs())
    {
        get_lock();
        // Reset the value of the last sent request (for that channel)
        ch_last_request[p_request->channel].success = false;
        free_lock();

        res = EPS_CTRL_DONE;
    }
    else
    {
        res = EPS_CTRL_FAIL;
    }
    return res;
}

bool eps_ctrl_cfg_get_last_req(eps_ctrl_channels_t channel, bool * p_state)
{
    bool res = false;
    if (channel < EPS_CTRL_CH_COUNT)
    {
        get_lock();
        *p_state = ch_last_request[channel].state;
        res = ch_last_request[channel].success;
        free_lock();
    }
    return res;
}

// EPS I
void eps_ctrl_cfg_set_ch_notif_eps_i(uint16_t seq_id)
{
    // Verify that the channel had a response pending

    get_lock();
    if (active_request_seq_id == seq_id)
    {
        // EPS 1 returns the requested value together with the EPS1_QUERYSTATE_Mismatch bit if
        //  the current value is not the same as requested.
        // Just the fact that the response was received means that the request is being processed by the EPS 1

        // Store the value of the request
        ch_last_request[active_request_channel].success = true;

        // Trigger the state machine event
        eps_ctrl_response_received_notif();
    }
    free_lock();
}

void eps_ctrl_cfg_get_ch_notif_eps_i(uint16_t seq_id, EPS1_ConfigurationInfo_t io_config)
{
    // Verify that the channel had a response pending
    get_lock();
    if (active_request_seq_id == seq_id)
    {
        // Indicate that a request was received
        ch_last_request[active_request_channel].success = true;

        // Filter the received state mask with the mask of the channel (stored in channel_number)
        // Outputs come as two uint16 join to one uint32
        uint32_t config_info_outputs = (uint32_t)io_config.au16OutputConditions[1] << 16 | (uint32_t)io_config.au16OutputConditions[0];

        // Get the corresponding index from the outputs bitfield
        uint32_t config_index_flag = eps_i_get_config_from_channel(channel_outputs[active_request_channel].channel_eps_i);

        // Return the value received that corresponds to the desired value
        ch_last_request[active_request_channel].state = (config_info_outputs & config_index_flag);

        // Trigger the state machine event
        eps_ctrl_response_received_notif();
    }
    free_lock();
}

// EPS II
void eps_ctrl_cfg_set_ch_notif_eps_ii(uint16_t seq_id, bool success)
{
    // Verify that the channel had a response pending

    get_lock();
    if (active_request_seq_id == seq_id)
    {
        // Store the value of the request
        ch_last_request[active_request_channel].success = success;

        // Notify state machine
        eps_ctrl_response_received_notif();
    }
    free_lock();
}

void eps_ctrl_cfg_get_ch_notif_eps_ii_gpio(uint16_t seq_id, EPSII_PDM_1_SGGPIO_Bitmask_t state_mask)
{
    // Verify that the channel had a response pending
    get_lock();
    if (active_request_seq_id == seq_id) {
        // Indicate that a request was received
        ch_last_request[active_request_channel].success = true;

        // Convert the channel type to GPIO mask
        EPSII_PDM_1_SGGPIO_OnOff_mask_t ch_mask =
            eps_ii_channel_to_gpio(channel_outputs[active_request_channel].channel_eps_ii);

        // Filter the received state mask with the mask of the channel (stored in channel_number)
        ch_last_request[active_request_channel].state = (state_mask & ch_mask);

        // Notify state machine
        eps_ctrl_response_received_notif();
    }
    free_lock();
}

void eps_ctrl_cfg_get_ch_notif_eps_ii_sgpo(uint16_t seq_id, EPSII_PDM_1_SGPO_Bitmask_t state_mask)
{
    // Verify that the channel had a response pending
    get_lock();
    if (active_request_seq_id == seq_id)
    {
        // Indicate that a request was received
        ch_last_request[active_request_channel].success = true;

        // Convert the channel type to SGPO mask
        EPSII_PDM_1_SGPO_ON_Off_Bitmask_t ch_mask =
            eps_ii_channel_to_sgpo(channel_outputs[active_request_channel].channel_eps_ii);

        // Filter the received state mask with the mask of the channel (stored in channel_number)
        ch_last_request[active_request_channel].state = (state_mask & ch_mask);

        // Notify state machine
        eps_ctrl_response_received_notif();
    }
    free_lock();
}

void eps_ctrl_cfg_set_ch_notif_eps_m(uint16_t seq_id, bool success)
{

    (void) seq_id;

    get_lock();

    // Indicate that a request was received
    ch_last_request[active_request_channel].success = success;

    // Notify state machine
    eps_ctrl_response_received_notif();

    free_lock();
}

void eps_ctrl_cfg_get_ch_notif_eps_m(uint16_t seq_id, uint16_t state_mask)
{
    (void) seq_id;

    get_lock();

    // Indicate that a request was received
    ch_last_request[active_request_channel].success = true;

    // Filter the received state mask with the mask of the channel (stored in channel_number)
    ch_last_request[active_request_channel].state = \
            (state_mask >> channel_outputs[active_request_channel].channel_eps_m) & 0x01;

    // Notify state machine
    eps_ctrl_response_received_notif();

    free_lock();
}

void eps_ctrl_cfg_max_retries_notification(void)
{
    // Trigger the event queue to unblock the user thread
    get_lock();

    // Set the last request as failed
    ch_last_request[active_request_channel].success = false;

    free_lock();
}

bool eps_ctrl_cfg_get_wait_flag(const uint32_t wait_idx, uint32_t * const p_wait_flag)
{
    bool op_res = false;

    if (NULL != p_wait_flag)
    {
        //This static assertion can be moved, but must be present always
        static_assert(EPS_CTRL_MAX_QUEUE_REQUESTS < EVENT_GROUP_SIZE);

        *p_wait_flag = (uint32_t)(1 << wait_idx);
        op_res = true;
    }

    return op_res;
}

bool eps_ctrl_cfg_service_lock_get(void)
{
    return (osOK == osMutexAcquire(gh_eps_ctrl_cfg_service_lock, osWaitForever));
}

void eps_ctrl_cfg_service_lock_free(void)
{
    osMutexRelease(gh_eps_ctrl_cfg_service_lock);
}

bool eps_ctrl_cfg_get_channel_and_flag(eps_ctrl_channels_t * const p_req_channel, uint32_t * const p_wait_flag)
{
    bool res = false;

    if ((NULL != p_req_channel) && (NULL != p_wait_flag))
    {
        get_lock();
        *p_req_channel = active_request_channel;
        *p_wait_flag   = active_wait_flag;
        free_lock();

        res = true;
    }

    return res;
}

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
/**
 * @brief Acquires the mutex for the eps_ctrl variables
 */
static inline void get_lock(void)
{
    osMutexAcquire(channels_lock_id, osWaitForever);
}

/**
 * @brief Releases the mutex for the eps_ctrl variables
 */
static inline void free_lock(void)
{
    osMutexRelease(channels_lock_id);
}
