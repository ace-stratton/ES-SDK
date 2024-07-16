/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_STATS_H
#define ESPS_DRV_STATS_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_stats.h
 * @brief    MAC driver statistics interface
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "esps_drv_cdef.h"

/******************************************************************************
 * Public Types
 *****************************************************************************/
/// the following fp_sStats are kept for each MAC interface instance since last reset
typedef enum {
    eMACStatId_TotalRxBytes,        /**> bytes received */
    eMACStatId_TotalTxBytes,        /**> bytes transmitted */
    eMACStatId_TxCollisionCntr,     /**> collisions during attempts to transmit a message */
    eMACStatId_TxTimeoutCntr,       /**> elapsed global Tx timeouts */
    eMACStatId_IncorrectCrcMsgCntr, /**< number of messages received with an incorrect CRC */
    eMACStatId_TxMsgBufUnavailCntr, /**< Tx message buffer unavailability events */
    eMACStatId_RxMsgBufUnavailCntr, /**< Rx message buffer unavailability events */
    eMACStatId_RxTimeoutCntr,       /**< timeouts which occurred during reception (in any state) */
    eMACStatId_RxValidFramesCntr,   /**< received valid MAC frames on the bus */
    eMACStatId_TxFramesCntr,        /**< sent MAC frames on the bus */
    eMACStatId_MaxRxSlotsOccupied,  /**< max number of occupied Rx message buffers at one time*/
    eMACStatId_MaxTxSlotsOccupied,  /**< max number of occupied Tx message buffers at one time */
    eMACStatId_MaxRxTime,           /**< max time in uS for reception of a single message */
    eMACStatId_MaxTxTime,           /**< max time in uS for transmission of a single message */
    eMACStatId_InvalidHeaderCRCCntr,/**< invalid MAC frame header CRC events */
    eMACStatId_MAX
} eMACStatId_t;

/** To store the values of the fp_sStats */
typedef uint32_t macStats_t[eMACStatId_MAX];

/******************************************************************************
 * Public Functions Declarations
 *****************************************************************************/

/**
 * @brief Reset the counters
 * @param fp_sStats fp_sStats structure to reset
 */
void MAC_Stats_resetEventCounters(macStats_t fp_sStats);

/**
 * @brief Trigger an event to be saved
 * @param fp_sStats: structure
 * @param fp_eEvtId: event to be stored
 */
void MAC_Stats_triggerEvent(macStats_t fp_sStats, eMACStatId_t fp_eEvtId);

/**
 * @brief Trigger more than one event to be saved
 * @param fp_sStats: structure
 * @param fp_eEvtId: event to be stored
 * @param fp_u32CounterValue: value to be stored
 */
void MAC_Stats_triggerMultiEvent(macStats_t fp_sStats, eMACStatId_t fp_eEvtId, const uint32_t fp_u32CounterValue);

/**
 * @brief Store the minimum possible value for an event
 *
 * @param fp_sStats: structure
 * @param fp_eEvtId: event to be stored
 * @param fp_u32CurrentValue: value
 */
void MAC_Stats_storeEventMin(macStats_t fp_sStats, eMACStatId_t fp_eEvtId, const uint32_t fp_u32CurrentValue);

/**
 * @brief Store the maximum possible value for an event
 *
 * @param fp_sStats: structure
 * @param fp_eEvtId: event to be stored
 * @param fp_u32CurrentValue: value
 */
void MAC_Stats_storeEventMax(macStats_t fp_sStats, eMACStatId_t fp_eEvtId, const uint32_t fp_u32CurrentValue);
/**
 * @brief Retrieve the counter for an specific event
 * @param fp_sStats: structure
 * @param fp_eEvtId: event
 */
uint32_t MAC_Stats_getEventCounter(macStats_t fp_sStats, eMACStatId_t fp_eEvtId);

#ifdef __cplusplus
};
#endif

#endif // ESPS_DRV_STATS_H
