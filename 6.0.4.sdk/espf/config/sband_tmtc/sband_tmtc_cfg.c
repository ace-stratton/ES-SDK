/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup sband_tmtc
 * @{
 *
 * @file     es_band_tmtc.c
 * @brief    S Band TMTC drivers configuration
 *
 * @}
 */

#include "sband_tmtc_cfg.h"
#include "nvm.h"

uint8_t sband_tmtc_cfg_get_mac_address(void){
	mac_address_book_t addresses = {0};

	// Read the NVM
	Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

	return addresses.a_mac_address[MAC_ADDR_SBAND_TMTC];
}
