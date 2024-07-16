/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "libhsm.h"
#include "beacons_sm_config_user.h"

// USER_CODE_START::@main@

/**
 * @addtogroup service_beacons
 * @{
 * @file beacons_sm_config_user.c
 * @brief The file implements the beacons service SM functions (e.g. @a guard, @a action and @a on_entry/on_exit handlers)
 * @}
 *
 */

#include "beacons_sm_user.h"
#include "assertions.h"

static inline uint32_t safe_decrease(const uint32_t num, const uint32_t decr_value)
{
    return (num >= decr_value) ? (num - decr_value) : (0U);
}

static inline void reset_internal_state(void)
{
    beacons_rt_context.next_beacon_slot_idx_to_send = 0U;
    timer_stop(&beacons_rt_context.send_timer);
    timer_stop(&beacons_rt_context.inter_frame_timer);
    timer_stop(&beacons_rt_context.sink_confirm_timer);
    timer_stop(&beacons_rt_context.reload_config_timer);
    SET_FALSE(beacons_rt_context.last_sink_frame_confirmed);
    SET_FALSE(beacons_rt_context.partial_msg_info.is_continuation_frame);
    beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send = 0U;
}
// USER_CODE_END::@main@

// Entry/Exit functions


// GEN_OBJ_START::beacons_sm_on_entry_Init
void beacons_sm_on_entry_Init(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Init

    timer_start(&beacons_rt_context.reload_config_timer);

    // USER_CODE_END::onEntry_Init
}
// GEN_OBJ_END::beacons_sm_on_entry_Init


// GEN_OBJ_START::beacons_sm_on_entry_Started
void beacons_sm_on_entry_Started(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Started

    reset_internal_state();

    timer_start(&beacons_rt_context.send_timer);

    // USER_CODE_END::onEntry_Started
}
// GEN_OBJ_END::beacons_sm_on_entry_Started

// GEN_OBJ_START::beacons_sm_on_exit_Started
void beacons_sm_on_exit_Started(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onExit_Started

    reset_internal_state();

    // USER_CODE_END::onExit_Started
}
// GEN_OBJ_END::beacons_sm_on_exit_Started


// GEN_OBJ_START::beacons_sm_on_entry_Beacon_Wait_Time
void beacons_sm_on_entry_Beacon_Wait_Time(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Beacon_Wait_Time

    // load NVM configuration only on entry to this state to provide more dynamic behavior
    // ...this results in the NVM configuration being changed on each new beacon burst sequence

    beacons_load_config();
    beacons_rt_context.active_preset_id = beacons_cfg_get_active_preset();
    SET_FALSE(beacons_rt_context.partial_msg_info.is_continuation_frame);
    beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send = 0U;

    CRIT_ASSERT(beacons_rt_context.active_preset_id <= BEACON_PRESETS_COUNT);

    beacons_rt_context.next_beacon_slot_idx_to_send = 0U;
    SET_TRUE(beacons_rt_context.more_messages_pending);

    // USER_CODE_END::onEntry_Beacon_Wait_Time
}
// GEN_OBJ_END::beacons_sm_on_entry_Beacon_Wait_Time



// GEN_OBJ_START::beacons_sm_on_entry_Stopped
void beacons_sm_on_entry_Stopped(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Stopped

    timer_start(&beacons_rt_context.reload_config_timer);

    // USER_CODE_END::onEntry_Stopped
}
// GEN_OBJ_END::beacons_sm_on_entry_Stopped



// Guard condition functions
// GEN_OBJ_START::beacons_sm_guard_can_stop_operation
bool beacons_sm_guard_can_stop_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_can_stop_operation
    const sState_t * p_hsm_state = HSM_GetActiveState(beacons_sm_instance);

    return (STATE_BEACON_WAIT_TIME == p_hsm_state->state_id);

    // USER_CODE_END::guard_can_stop_operation
}
// GEN_OBJ_END::beacons_sm_guard_can_stop_operation

// GEN_OBJ_START::beacons_sm_guard_is_beacon_time_expired
bool beacons_sm_guard_is_beacon_time_expired(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_beacon_time_expired

    return (IS_TRUE(beacons_rt_context.send_timer.is_running)) &&
           (timer_is_elapsed(&beacons_rt_context.send_timer, beacons_rt_context.gen_cfg.bcn_tx_period));

    // USER_CODE_END::guard_is_beacon_time_expired
}
// GEN_OBJ_END::beacons_sm_guard_is_beacon_time_expired

// GEN_OBJ_START::beacons_sm_guard_all_beacons_transmitted
bool beacons_sm_guard_all_beacons_transmitted(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_all_beacons_transmitted
    bool all_beacons_transmitted = (IS_FALSE(beacons_rt_context.more_messages_pending) &&
                                    IS_TRUE(beacons_rt_context.last_sink_frame_confirmed));

    return all_beacons_transmitted;

    // USER_CODE_END::guard_all_beacons_transmitted
}
// GEN_OBJ_END::beacons_sm_guard_all_beacons_transmitted

// GEN_OBJ_START::beacons_sm_guard_is_sink_timeout_expired
bool beacons_sm_guard_is_sink_timeout_expired(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_is_sink_timeout_expired

    // Your implementation goes here...
    return (IS_TRUE(beacons_rt_context.sink_confirm_timer.is_running)) &&
            (timer_is_elapsed(&beacons_rt_context.sink_confirm_timer, BEACON_SINK_CONFIRM_TIMEOUT_MS));

    // USER_CODE_END::guard_is_sink_timeout_expired
}
// GEN_OBJ_END::beacons_sm_guard_is_sink_timeout_expired

// GEN_OBJ_START::beacons_sm_guard_can_continue_transmission
bool beacons_sm_guard_can_continue_transmission(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_can_continue_transmission

    return (IS_TRUE(beacons_rt_context.more_messages_pending) &&
            IS_TRUE(beacons_rt_context.last_sink_frame_confirmed) &&
           ((IS_TRUE(beacons_rt_context.inter_frame_timer.is_running) &&
            timer_is_elapsed(&beacons_rt_context.inter_frame_timer, beacons_rt_context.gen_cfg.bcn_inter_frame_period))));

    // USER_CODE_END::guard_can_continue_transmission
}
// GEN_OBJ_END::beacons_sm_guard_can_continue_transmission


// Action handlers
// GEN_OBJ_START::beacons_sm_action_reload_config
void beacons_sm_action_reload_config(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_reload_config

    if ((beacons_rt_context.reload_config_timer.is_running) &&
        (timer_is_elapsed(&beacons_rt_context.reload_config_timer, BCN_RELOAD_CFG_TIME_STOP_MODE_MS)))
    {
        // the reloaded configuration will be checked in the beacons service task
        beacons_load_config();

        timer_start(&beacons_rt_context.reload_config_timer);
    }

    // USER_CODE_END::action_reload_config
}
// GEN_OBJ_END::beacons_sm_action_reload_config

// GEN_OBJ_START::beacons_sm_action_start_beacon_burst
void beacons_sm_action_start_beacon_burst(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_start_beacon_burst

    timer_start(&beacons_rt_context.send_timer);
    beacons_sm_action_send_beacon(pSMRoot, pEvent);

    // USER_CODE_END::action_start_beacon_burst
}
// GEN_OBJ_END::beacons_sm_action_start_beacon_burst

// GEN_OBJ_START::beacons_sm_action_reset_send_state
void beacons_sm_action_reset_send_state(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_reset_send_state

    beacons_rt_context.next_beacon_slot_idx_to_send = 0U;
    timer_stop(&beacons_rt_context.inter_frame_timer);
    timer_stop(&beacons_rt_context.sink_confirm_timer);
    timer_stop(&beacons_rt_context.reload_config_timer);
    SET_FALSE(beacons_rt_context.last_sink_frame_confirmed);

    // USER_CODE_END::action_reset_send_state
}
// GEN_OBJ_END::beacons_sm_action_reset_send_state

// GEN_OBJ_START::beacons_sm_action_log_sink_timeout_error
void beacons_sm_action_log_sink_timeout_error(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_log_sink_timeout_error

    EXEH_vException(eEXEHSeverity_Warning, eEXEHModuleID_BEACONS, EXEH_BCN_SINK_ADAPTER_TIMEOUT, __LINE__);

    // USER_CODE_END::action_log_sink_timeout_error
}
// GEN_OBJ_END::beacons_sm_action_log_sink_timeout_error

// GEN_OBJ_START::beacons_sm_action_send_beacon
void beacons_sm_action_send_beacon(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_send_beacon
    uint8_t beacon_slot_idx;    // this is used to enumerate the beacon slot indices in the active beacon preset slot
    uint8_t *p_frame_pos = (uint8_t *) &beacons_rt_context.active_beacon_frame[0U];
    uint8_t *p_flags_pos = (uint8_t *) &(((beacon_frame_hdr_t *) p_frame_pos)->flags);
    uint16_t rem_bytes_in_frame = BEACON_FRAME_SIZE_BYTES;

    // initialize beacon buffer...
    (void) memset(p_frame_pos, INVALID_BEACON_SLOT_ASSIGNMENT, rem_bytes_in_frame);

    // prepare beacon frame header...
    ((beacon_frame_hdr_t *) p_frame_pos)->rolling_cntr = beacons_rt_context.beacon_frame_rolling_cntr++;
    ((beacon_frame_hdr_t *) p_frame_pos)->obc_opmode = beacons_get_op_mode();
    ((beacon_frame_hdr_t *) p_frame_pos)->flags = FRAME_HDR_FLAGS_INIT;

    rem_bytes_in_frame = safe_decrease(rem_bytes_in_frame, sizeof(beacon_frame_hdr_t));
    p_frame_pos += sizeof(beacon_frame_hdr_t);

    // start filling-in individual beacon messages from the currently active preset...
    for (beacon_slot_idx = beacons_rt_context.next_beacon_slot_idx_to_send;
         beacon_slot_idx < MAX_BEACON_MSG_SLOTS;
         beacon_slot_idx++)
    {
        // obtain the next beacon message type from the presets configuration...
        uint16_t beacon_type = INVALID_BEACON_SLOT_ASSIGNMENT;
        dc_did_id dc_data_idx = DC_DID_MAX;

        if ((beacon_slot_idx < MAX_BEACON_MSG_SLOTS) &&
        	(beacons_rt_context.active_preset_id < BEACON_PRESETS_COUNT))
        {
            beacon_type = beacons_rt_context.preset_cfg.beacon_slots_setting[beacons_rt_context.active_preset_id][beacon_slot_idx];
            dc_data_idx = dc_get_index_by_data_id(beacon_type);
        }

        if ((INVALID_BEACON_SLOT_ASSIGNMENT != beacon_type) &&
            (DC_DID_MAX != dc_data_idx))
        {
            uint32_t bcn_msg_size = dc_get_data_size(dc_data_idx);

            CRIT_ASSERT(bcn_msg_size <= BEACON_MSG_MAX_SIZE_BYTES);

            bool can_package_msg_in_frame = IS_TRUE(beacons_rt_context.gen_cfg.chunk_based_transfer_en) ||
         		   (IS_FALSE(beacons_rt_context.gen_cfg.chunk_based_transfer_en) &&
                     (bcn_msg_size <=
                            (sizeof(beacons_rt_context.active_beacon_frame) -
                             sizeof(beacon_frame_hdr_t) -
                             sizeof(beacon_msg_hdr_t))));

            // if message splitting is not configured, then any beacon message shall fit inside the
            // provided buffer otherwise it will never be able to get sent...
            CRIT_ASSERT(can_package_msg_in_frame);

            // this check is here to serve the case when CRIT_ASSERT() is empty and will not be
            // evaluated and the configuration of presets does not allow to package the current frame due
            // to its bigger size
            if (!can_package_msg_in_frame)
            	continue;

            // save data status position for later
            uint8_t * p_beacon_data_status_pos = &(((beacon_msg_hdr_t *) p_frame_pos)->beacon_data_status);

            ((beacon_msg_hdr_t *) p_frame_pos)->beacon_type = beacon_type;
            ((beacon_msg_hdr_t *) p_frame_pos)->beacon_data_status = 0U;

            beacons_rt_context.next_beacon_slot_idx_to_send = beacon_slot_idx;

            // the full beacon message fits in the current frame?
            if ((rem_bytes_in_frame >= (sizeof(beacon_msg_hdr_t) + bcn_msg_size)) &&
                (IS_FALSE(beacons_rt_context.gen_cfg.chunk_based_transfer_en) ||
                 IS_FALSE(beacons_rt_context.partial_msg_info.is_continuation_frame)))
            {
                ((beacon_msg_hdr_t *) p_frame_pos)->data_len = bcn_msg_size;

                // jump over individual beacon message header
                rem_bytes_in_frame = safe_decrease(rem_bytes_in_frame, sizeof(beacon_msg_hdr_t));
                p_frame_pos += sizeof(beacon_msg_hdr_t);

                // copy data to beacon buffer...
                *((uint8_t *) p_beacon_data_status_pos) =
                        (uint8_t) dc_get_raw_data(dc_data_idx, p_frame_pos, rem_bytes_in_frame, 0U, bcn_msg_size);

                // jump over data field to next free position...
                rem_bytes_in_frame = safe_decrease(rem_bytes_in_frame, bcn_msg_size);
                p_frame_pos += bcn_msg_size;
            }
            else    // the beacon message doesn't fit in the remaining buffer space or this is a continuation from previous frame
            {
                // the algorithm will try to split the frame only if the feature is configured and
                // in case there is not enough space in the remaining buffer to fully accommodate at least
                // the beacon message header + 1 more byte (headers do not get split - sorry!)
                if (IS_TRUE(beacons_rt_context.gen_cfg.chunk_based_transfer_en) &&
                   (rem_bytes_in_frame > sizeof(beacon_msg_hdr_t)))
                {
                    // mark frame as continuation frame
                    *p_flags_pos = (*p_flags_pos) | FRAME_HDR_FLAGS_CONTINUATION;

                    if (IS_FALSE(beacons_rt_context.partial_msg_info.is_continuation_frame))
                    {
                        // first part of a continuation frame...
                        SET_TRUE(beacons_rt_context.partial_msg_info.is_continuation_frame);

                        // this field indicates the actual remaining number of bytes to be sent across all frames until end of
                        // the message
                        ((beacon_msg_hdr_t *) p_frame_pos)->data_len = bcn_msg_size;
                        /*
                         * | beacon_msg_hdr_t |         bytes_until_end_of_frame           |<---- rem_msg_bytes_to_send ---->|
                         * |<------------------- rem_bytes_in_frame --------------------->|
                         *                       |<--------------------------------- bcn_msg_size ---------------------------->|
                         *
                         * The actual number of bytes that will be sent with this frame is:
                         * bytes_until_end_of_frame = rem_bytes_in_frame - sizeof(beacon_msg_hdr_t)
                         *
                         * ...then the actual remaining number of bytes from the message are:
                         * rem_msg_bytes_to_send = bcn_msg_size - bytes_until_end_of_frame
                         */

                        uint32_t bytes_until_end_of_frame = rem_bytes_in_frame - sizeof(beacon_msg_hdr_t);
                        beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send = bcn_msg_size - bytes_until_end_of_frame;

                        // jump over individual beacon message header
                        rem_bytes_in_frame = safe_decrease(rem_bytes_in_frame, sizeof(beacon_msg_hdr_t));
                        p_frame_pos += sizeof(beacon_msg_hdr_t);

                        // copy data to beacon buffer...
                        *((uint8_t *) p_beacon_data_status_pos) =
                                (uint8_t) dc_get_raw_data(dc_data_idx,
                                                          p_frame_pos,
                                                          bytes_until_end_of_frame,
                                                          0U,
                                                          bytes_until_end_of_frame);

                        break;
                    }
                    else
                    {
                        // subsequent continuation frames...
                        uint32_t bytes_until_end_of_frame = rem_bytes_in_frame - sizeof(beacon_msg_hdr_t);

                        ((beacon_msg_hdr_t *) p_frame_pos)->data_len = beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send;

                        // jump over individual beacon message header
                        rem_bytes_in_frame = safe_decrease(rem_bytes_in_frame, sizeof(beacon_msg_hdr_t));
                        p_frame_pos += sizeof(beacon_msg_hdr_t);

                        // would message fit this time?
                        if (beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send <= bytes_until_end_of_frame)
                        {
                            // copy data to beacon buffer...
                            *((uint8_t *) p_beacon_data_status_pos) =
                                    (uint8_t) dc_get_raw_data(dc_data_idx,
                                                              p_frame_pos,
                                                              bytes_until_end_of_frame,
                                                              bcn_msg_size - beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send,
                                                              beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send);

                            // jump over data field to next free position...
                            rem_bytes_in_frame = safe_decrease(rem_bytes_in_frame, beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send);
                            p_frame_pos += beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send;

                            SET_FALSE(beacons_rt_context.partial_msg_info.is_continuation_frame);
                            beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send = 0U;
                        }
                        else    // message still doesn't fit, hence package as many bytes as possible and send frame
                        {
                            // copy data to beacon buffer...
                            *((uint8_t *) p_beacon_data_status_pos) =
                                    (uint8_t) dc_get_raw_data(dc_data_idx,
                                                              p_frame_pos,
                                                              bytes_until_end_of_frame,
                                                              bcn_msg_size - beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send,
                                                              rem_bytes_in_frame);

                            beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send =
                                    safe_decrease(beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send, rem_bytes_in_frame);

                            break;
                        }
                    }
                }
                else    // no message splitting, just leave this message for next frame...
                {
                    SET_FALSE(beacons_rt_context.partial_msg_info.is_continuation_frame);
                    beacons_rt_context.partial_msg_info.rem_msg_bytes_to_send = 0U;

                    // initialize rest of the frame data to invalid values
                    (void) memset(p_frame_pos, INVALID_BEACON_SLOT_ASSIGNMENT, rem_bytes_in_frame);

                    break;
                }
            }
        }
        else
        {
            SET_FALSE(beacons_rt_context.more_messages_pending);

            break;
        }
    }

    if (MAX_BEACON_MSG_SLOTS == beacon_slot_idx)
    {
    	SET_FALSE(beacons_rt_context.more_messages_pending);
    }

    // start sink confirmation timeout tracking...
    timer_start(&beacons_rt_context.inter_frame_timer);

    SET_FALSE(beacons_rt_context.last_sink_frame_confirmed);

    bool bSendConfirmed = beacons_sink.send(&beacons_rt_context.active_beacon_frame[0U],
                                            sizeof(beacons_rt_context.active_beacon_frame),
                                            &beacons_rt_context.last_sink_frame_id);

    if (bSendConfirmed)
    {
        SET_TRUE(beacons_rt_context.last_sink_frame_confirmed);
    }
    else
    {
        // start sink confirmation timeout tracking...
        timer_start(&beacons_rt_context.sink_confirm_timer);
    }

    // USER_CODE_END::action_send_beacon
}
// GEN_OBJ_END::beacons_sm_action_send_beacon
