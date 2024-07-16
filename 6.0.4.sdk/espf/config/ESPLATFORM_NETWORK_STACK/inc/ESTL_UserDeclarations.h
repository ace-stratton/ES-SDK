/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPLATFORM_NETWORK_STACK_INC_ESTL_USERDECLARATIONS_H_
#define ESPLATFORM_NETWORK_STACK_INC_ESTL_USERDECLARATIONS_H_

/**
 * @addtogroup tp
 * @{
 *
 * @file     ESTL_UserDeclarations.h
 * @brief    Transport Layer user configuration definitions
 *
 * @}
 */

#define ESTL_UTILS_CRC32_ROM_TABLE

#include "ffconf.h"

/*
 * Firmware Updates TL configuration
 */
// this define determines the maximum number of TL buffers which can be kept in the flat FW update buffer before
// FW update packets stop to be confirmed; this is needed because FW update will arrive in bursts and processing of
// received chunks cannot be immediately performed in the TL callback but has to be delegated to an OS task;
// writing to the SD card shall be possible while at the same time FW update chunks are arriving on the bus
#define MAX_NUMBER_OF_TL_BUF_PACKETS     ((uint32_t) 40)

// defines the chunk size used when writing FW update data to the SD card
#define STORAGE_COMMIT_BUF_SIZE          ((uint32_t) FF_MAX_SS)

// number of events which can be received in the state machine processing queue
#define SM_EVENT_QUEUE_SIZE              ((uint32_t) 200)

#endif /* ESPLATFORM_NETWORK_STACK_INC_ESTL_USERDECLARATIONS_H_ */
