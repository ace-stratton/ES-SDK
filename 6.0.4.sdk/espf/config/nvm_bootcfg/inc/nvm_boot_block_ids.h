/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef NVM_INC_NVM_BOOT_BLOCK_IDS_H_
#define NVM_INC_NVM_BOOT_BLOCK_IDS_H_

#define cu16NvmBlockLayoutVersion   ((uint16_t) 0x0001)

enum
{
	NVM_BLOCK_BOOTLAYOUTVERSION = 0U,
	NVM_BLOCK_BOOTDATA = 1U,
	NVM_BLOCK_MODULEID = 2U,
#ifdef COMM_RS485_MAC_LAYER_ENABLED
	NVM_BLOCK_MACCONFIG = 3U,
#endif  // #ifdef COMM_RS485_MAC_LAYER_ENABLED
	NVM_BOOT_BLOCK_MAX_COUNT
};

#endif /* NVM_INC_NVM_BOOT_BLOCK_IDS_H_ */
