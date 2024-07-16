/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_GEN2_EVENTS_H
#define CUBEADCS_GEN2_EVENTS_H

/**
 * @addtogroup cubeadcs_gen2_events
 * @{
 *
 * @file     cubeadcs_gen2_events.h
 * @brief    Cubeadcs Generation 2 events handler header
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include "es_cdef.h"
#include "cubeadcs_gen2_events_types.h"

/** @brief Clear only the last read events flag */
#define CUBEADCS_GEN2_EVENTS_CLEAR_LAST_READ_EVENTS (false)
/** @brief Clear all cached events */
#define CUBEADCS_GEN2_EVENTS_CLEAR_ALL_EVENTS (true)
/** @brief Maximum number of events to download */
#define CUBEADCS_GEN2_EVENTS_MAX_EVENTS_TO_DOWNLOAD (20)

/** @brief Cubeadcs gen2 events context */
typedef struct {
    uint32_t last_read_counter; /** @brief Counter value of the last read event */
    uint32_t last_crit_events_num; /** @brief Number of critical events read at last check */
    uint32_t last_major_events_num; /** @brief Number of major events read at last check */
    uint32_t events_to_download; /** @brief Number of events to download at this iteration */
    cubeadcs_gen2_events_cnts_t read_events; /** @brief Read events since last reset */

} cubeadcs_gen2_events_ctx_t;

typedef enum
{
    CUBEADCS_GEN2_EVENT_CLASS_INFO = 0,
    CUBEADCS_GEN2_EVENT_CLASS_MINOR,
    CUBEADCS_GEN2_EVENT_CLASS_MAJOR,
    CUBEADCS_GEN2_EVENT_CLASS_CRITICAL,

} cubeadcs_gen2_event_class_t;

typedef enum
{
    CUBEADCS_GEN2_ABSTRACT_NODE_INVALID = 0,
    CUBEADCS_GEN2_ABSTRACT_NODE_COMPUTER,
    CUBEADCS_GEN2_ABSTRACT_NODE_STR_0,
    CUBEADCS_GEN2_ABSTRACT_NODE_STR_1,
    CUBEADCS_GEN2_ABSTRACT_NODE_FSS_0,
    CUBEADCS_GEN2_ABSTRACT_NODE_FSS_1,
    CUBEADCS_GEN2_ABSTRACT_NODE_FSS_2,
    CUBEADCS_GEN2_ABSTRACT_NODE_FSS_3,
    CUBEADCS_GEN2_ABSTRACT_NODE_HSS_0,
    CUBEADCS_GEN2_ABSTRACT_NODE_HSS_1,
    CUBEADCS_GEN2_ABSTRACT_NODE_MAG_0,
    CUBEADCS_GEN2_ABSTRACT_NODE_MAG_1,
    CUBEADCS_GEN2_ABSTRACT_NODE_EXT_0,
    CUBEADCS_GEN2_ABSTRACT_NODE_EXT_1,
    CUBEADCS_GEN2_ABSTRACT_NODE_RWL_0,
    CUBEADCS_GEN2_ABSTRACT_NODE_RWL_1,
    CUBEADCS_GEN2_ABSTRACT_NODE_RWL_2,
    CUBEADCS_GEN2_ABSTRACT_NODE_RWL_3,
    CUBEADCS_GEN2_ABSTRACT_NODE_RWL_4,

    CUBEADCS_GEN2_ABSTRACT_NODE_MAX

} cubeadcs_gen2_abstract_node_t;

/** @brief CubeSpace Gen2 event identifier */
typedef struct
{
    uint16_t event_type: 9;
    cubeadcs_gen2_abstract_node_t abstract_node: 5;
    cubeadcs_gen2_event_class_t event_class: 2;

} PACKED cubeadcs_gen2_identifier_t;

/** @brief CubeSpace Gen2 event structure */
typedef struct
{
    uint32_t counter;
    uint32_t uptime;
    uint32_t unix_time;
    uint16_t milliseconds;
    cubeadcs_gen2_identifier_t identifier;
    uint8_t event_data[8];

} PACKED cubeadcs_gen2_event_t;

/** @brief Marker event download state machine states */
typedef enum
{
    CUBEADCS_GEN2_EVENT_DWN_IDLE,
    CUBEADCS_GEN2_EVENT_DWN_STARTED,
    CUBEADCS_GEN2_EVENT_DWN_POLL,
    CUBEADCS_GEN2_EVENT_DWN_FINISHED,

    CUBEADCS_GEN2_EVENT_DWN_MAX

} cubeadcs_gen2_event_dwn_progress_t;

/** @brief Critical events download state machine states */
typedef enum
{
    CUBEADCS_GEN2_EVENT_CRIT_IDLE,
    CUBEADCS_GEN2_EVENT_CRIT_CHECK,
    CUBEADCS_GEN2_EVENT_CRIT_START_DWN,
    CUBEADCS_GEN2_EVENT_CRIT_FINISHED,

    CUBEADCS_GEN2_EVENT_CRIT_MAX

} cubeadcs_gen2_event_crit_dwn_states_t;

/** @brief Initialise OS objects specific to the events logic */
void cubeadcs_gen2_events_init_os(void);

/** @brief CubeSpace Gen2 get the last event and use it as starting point for next periodic events checks
 * 
 *  @retval true     - on success
 *  @retval false    - on failure
 * 
 */
bool cubeadcs_gen2_events_get_marker(void);

/** @brief Check for a new event of severity - critical or major
 *
 *  @param[out] bool * const is_new_crit_events - result from the check
 *
 *  @retval true     - on successful check
 *  @retval false    - on failure to perform check
 *
 */
bool cubeadcs_gen2_events_check_for_new_crit_events(bool * const is_new_crit_events);

/** @brief Download critical events since last check
 *
 *  @retval true     - on successful download
 *  @retval false    - on failure to perform download
 *
 */
bool cubeadcs_gen2_events_dwn_new_crit_events(bool * const p_is_crit_evt);

/** @brief Get events statistics since last power-up
 *
 *  @param[out] cubeadcs_gen2_events_cnts_t * const p_ev_dst - events copy destination
 *
 *  @retval true     - on successful download
 *  @retval false    - on failure to perform download
 *
 */
bool cubeadcs_gen2_events_get_events_stats(cubeadcs_gen2_events_cnts_t * const p_ev_dst);

/** @brief Clear the read events statistics. If the clear all flag is NOT set, only the last read events will be cleared
 *
 *  @param[in] bool clr_all - clear all flag
 *
 *  @retval true     - on successful clean
 *  @retval false    - on failure to clean
 *
 */
bool cubeadcs_gen2_events_clear_event_stats(bool clr_all);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_GEN2_EVENTS_H */

/* ******************************************************************************************* */
