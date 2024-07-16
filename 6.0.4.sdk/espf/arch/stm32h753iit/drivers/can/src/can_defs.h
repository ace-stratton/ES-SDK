/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CAN_DEFS_H_
#define CAN_DEFS_H_

#include "stm32h7xx_hal.h"


#define CANDEF_IRQ_PRIO                (5)
#define CANDEF_TIMEOUT                 (1000)
#define CANDEF_STATS_TRACE_PERIOD_MS   (30000)
#define CANDEF_DEFAULT_INIT_Q_SIZE     (10)
#define CANDEF_DEFAULT_TX_Q_SIZE       (10)
#define CANDEF_TX_RETRY_MAX            (3)
#define CANDEF_TX_RETRY_PERIOD_MS      (5)
#define CANDEF_FREE_LVL_MAX_COUNT      (100)
#define CANDEF_IT_GROUP                (FDCAN_IT_ERROR_PASSIVE | \
                                        FDCAN_IT_ERROR_WARNING | \
                                        FDCAN_IT_BUS_OFF | \
                                        FDCAN_IT_RAM_ACCESS_FAILURE | \
                                        FDCAN_IT_ERROR_LOGGING_OVERFLOW | \
                                        FDCAN_IT_RAM_WATCHDOG | \
                                        FDCAN_IT_ARB_PROTOCOL_ERROR | \
                                        FDCAN_IT_DATA_PROTOCOL_ERROR | \
                                        FDCAN_IT_RESERVED_ADDRESS_ACCESS | \
                                        FDCAN_IT_RX_FIFO0_MESSAGE_LOST | \
                                        FDCAN_IT_RX_FIFO0_FULL | \
                                        FDCAN_IT_RX_FIFO0_WATERMARK | \
                                        FDCAN_IT_RX_FIFO0_NEW_MESSAGE | \
                                        FDCAN_IT_TX_EVT_FIFO_ELT_LOST | \
                                        FDCAN_IT_TX_EVT_FIFO_FULL | \
                                        FDCAN_IT_TX_EVT_FIFO_WATERMARK | \
                                        FDCAN_IT_TX_EVT_FIFO_NEW_DATA)

#endif /* CAN_DEFS_H_ */
