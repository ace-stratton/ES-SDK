/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "libhsm.h"
#include "telemetry_sm_config_user.h"

// USER_CODE_START::@main@

// Keep this documentation here to preserve it during code generation!
/**
 * @addtogroup service_tlm
 * @{
 *
 * @file telemetry_sm_config_user.c
 *
 * @brief This file contains the Telemetry SM hook functions (e.g. on_entry/on_exit/actions and guards).
 *
 * The functions here are directly called by the libhsm engine based on the generated code from `telemetry_sm.yaml`.
 * @warning Pay attention to edit this file only between the `USER_CODE_START` and `USER_CODE_END` comment blocks in order to
 * ensure that the auto-merge function of the libhsm generator will preserve your changes!
 *
 * @}
*/

// Any code placed between these two tags will be preserved during code generation!
#include <string.h>
#include <limits.h>
#include "telemetry_types.h"
#include "assertions.h"
#include "conops.h"
#include "crc16-ccitt.h"
#include "datetime.h"
#include "cobs.h"
#include "telemetry_queue.h"
#include "datetime.h"

#define TLM_COLLECTION_PERIOD_MS    (1000U)

static uint32_t prepare_tlm_frame(const uint16_t data_id, uint8_t * const p_data_buf, const uint32_t data_buf_size)
{
    uint32_t frame_len = 0U;

    CRIT_ASSERT(NULL != p_data_buf);
    CRIT_ASSERT(data_buf_size > 0U);

    if (INVALID_TLM_SLOT_ASSIGNMENT != data_id)
    {
        dc_did_id dc_item_idx = dc_get_index_by_data_id(data_id);

        if (DC_DID_MAX != dc_item_idx)
        {
            uint32_t dc_data_size = dc_get_data_size(dc_item_idx);

            CRIT_ASSERT(dc_data_size <= TLM_BUF_SIZE);

            if (dc_data_size <= TLM_BUF_SIZE)
            {
                tlm_frame_hdr_t *p_frame_hdr = (tlm_frame_hdr_t *) p_data_buf;
                uint8_t *p_frame_data = &p_data_buf[sizeof(tlm_frame_hdr_t)];

                frame_len = sizeof(tlm_frame_hdr_t) + dc_data_size + sizeof(tlm_msg_footer_t);

                CRIT_ASSERT(sizeof(tlm_rt_context.tlm_msg_buffer) >= frame_len);

                p_frame_hdr->timestamp = datetime_to_unix_now();
                p_frame_hdr->rolling_cntr++;
                conops_get_hsm_active_state(&p_frame_hdr->obc_opmode);

                dc_data_status_t dc_status =
                        dc_get_raw_data(dc_item_idx,
                                        p_frame_data,
                                        sizeof(tlm_rt_context.tlm_msg_buffer),
                                        0U,
                                        dc_data_size);

                p_frame_hdr->msg_hdr.msg_type = data_id;
                p_frame_hdr->msg_hdr.tlm_data_status = dc_status;
                CRIT_ASSERT(dc_data_size <= UINT_MAX);
                p_frame_hdr->msg_hdr.data_len = (uint16_t) dc_data_size;

                p_frame_data += dc_data_size;

                ((tlm_msg_footer_t *) p_frame_data)->crc =
                        crc16_ccitt_table((const uint8_t *) p_frame_hdr, frame_len - sizeof(tlm_msg_footer_t));
            }
        }
    }

    return frame_len;
}
// USER_CODE_END::@main@

// Entry/Exit functions


// GEN_OBJ_START::telemetry_sm_on_entry_Init
void telemetry_sm_on_entry_Init(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Init

    telemetry_queue_init();

    // USER_CODE_END::onEntry_Init
}
// GEN_OBJ_END::telemetry_sm_on_entry_Init


// GEN_OBJ_START::telemetry_sm_on_entry_Started
void telemetry_sm_on_entry_Started(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Started

    timer_start(&tlm_rt_context.tlm_timer);

    // USER_CODE_END::onEntry_Started
}
// GEN_OBJ_END::telemetry_sm_on_entry_Started

// GEN_OBJ_START::telemetry_sm_on_exit_Started
void telemetry_sm_on_exit_Started(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onExit_Started

    timer_start(&tlm_rt_context.reload_config_timer);

    // USER_CODE_END::onExit_Started
}
// GEN_OBJ_END::telemetry_sm_on_exit_Started


// GEN_OBJ_START::telemetry_sm_on_entry_Stopped
void telemetry_sm_on_entry_Stopped(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Stopped

    timer_stop(&tlm_rt_context.tlm_timer);

    // USER_CODE_END::onEntry_Stopped
}
// GEN_OBJ_END::telemetry_sm_on_entry_Stopped



// Guard condition functions
// GEN_OBJ_START::telemetry_sm_guard_can_start_operation
bool telemetry_sm_guard_can_start_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_can_start_operation

    return (SAFE_TRUE == tlm_rt_context.gen_cfg.telemetry_en);

    // USER_CODE_END::guard_can_start_operation
}
// GEN_OBJ_END::telemetry_sm_guard_can_start_operation

// GEN_OBJ_START::telemetry_sm_guard_can_stop_operation
bool telemetry_sm_guard_can_stop_operation(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_can_stop_operation

    return (SAFE_FALSE == tlm_rt_context.gen_cfg.telemetry_en);

    // USER_CODE_END::guard_can_stop_operation
}
// GEN_OBJ_END::telemetry_sm_guard_can_stop_operation

// GEN_OBJ_START::telemetry_sm_guard_periodic_timer_elapsed
bool telemetry_sm_guard_periodic_timer_elapsed(sState_t* const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::guard_periodic_timer_elapsed
    bool is_elapsed = (tlm_rt_context.tlm_timer.is_running) &&
                      (timer_is_elapsed(&tlm_rt_context.tlm_timer, TLM_COLLECTION_PERIOD_MS));

    if (is_elapsed)
    {
        timer_start(&tlm_rt_context.tlm_timer);
    }

    return is_elapsed;

    // USER_CODE_END::guard_periodic_timer_elapsed
}
// GEN_OBJ_END::telemetry_sm_guard_periodic_timer_elapsed


// Action handlers
// GEN_OBJ_START::telemetry_sm_action_prepare_tlm_collection
void telemetry_sm_action_prepare_tlm_collection(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_prepare_tlm_collection

    // reset acquisition counters...
    (void) memset(tlm_rt_context.tlm_message_acq_counters,
                  0U,
                  sizeof(tlm_rt_context.tlm_message_acq_counters));

    // USER_CODE_END::action_prepare_tlm_collection
}
// GEN_OBJ_END::telemetry_sm_action_prepare_tlm_collection

// GEN_OBJ_START::telemetry_sm_action_reload_config
void telemetry_sm_action_reload_config(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_reload_config

    if ((tlm_rt_context.reload_config_timer.is_running) &&
        (timer_is_elapsed(&tlm_rt_context.reload_config_timer, TLM_RELOAD_CFG_TIME_MS)))
    {
        telemetry_load_config();

        timer_start(&tlm_rt_context.reload_config_timer);
    }

    // USER_CODE_END::action_reload_config
}
// GEN_OBJ_END::telemetry_sm_action_reload_config

// GEN_OBJ_START::telemetry_sm_action_collect_telemetry
void telemetry_sm_action_collect_telemetry(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::action_collect_telemetry

    telemetry_load_config();

    for (uint8_t tlm_slot_idx = 0U; tlm_slot_idx < TELEMETRY_MAX_CONFIGURABLE_ENTRIES; tlm_slot_idx++)
    {
        tlm_preset_cfg_t tlm_entry = tlm_rt_context.preset_cfg.tlm_slots_setting[tlm_rt_context.active_preset_id][tlm_slot_idx];

        tlm_rt_context.tlm_message_acq_counters[tlm_slot_idx]++;

        // the following acquisition period check assumes the telemetry periodic collection happens on 1 sec;
        // if this is not the case, then the configuration settings will not lead to correct timings...
        CRIT_ASSERT(1000U == TLM_COLLECTION_PERIOD_MS);

        // has acquisition period elapsed?
        if ((tlm_entry.active) && (tlm_entry.acq_period > 0U))
        {
            if ((tlm_rt_context.tlm_message_acq_counters[tlm_slot_idx] % tlm_entry.acq_period) == 0U)
            {
                uint32_t frame_len = prepare_tlm_frame(tlm_entry.data_id, tlm_rt_context.tlm_msg_buffer, sizeof(tlm_rt_context.tlm_msg_buffer));

                if (frame_len > 0U)
                {
                    uint32_t cobs_frame_len = cobs_encode(tlm_rt_context.tlm_msg_buffer,
                                                          frame_len,
                                                          tlm_rt_context.tlm_msg_encode_buffer);

                    // the following check ensures there is room for the frame delimiter byte
                    CRIT_ASSERT((cobs_frame_len + 1U) <= sizeof(tlm_rt_context.tlm_msg_encode_buffer));

                    tlm_rt_context.tlm_msg_encode_buffer[cobs_frame_len++] = TLM_FRM_DELIMITER;

                    bool res = telemetry_queue_push(tlm_rt_context.tlm_msg_encode_buffer, cobs_frame_len);

                    (void) res;

                    // Note: Even if res is false, which means there was no space in the queue, we will
                    //       still continue with other slots because there may be enough space in the queue for them.
                }
                else
                {
                    // Invalid slot found -> this indicates the end of the configured telemetry message sequence.
                    break;
                }

                // reset acquisition time
                tlm_rt_context.tlm_message_acq_counters[tlm_slot_idx] = 0U;
            }
        }
    }

    // USER_CODE_END::action_collect_telemetry
}
// GEN_OBJ_END::telemetry_sm_action_collect_telemetry
