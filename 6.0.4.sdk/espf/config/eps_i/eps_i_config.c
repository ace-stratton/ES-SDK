/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_i
 * @{
 *
 * @file     eps_i_config.c
 * @brief    EPS I drivers configuration
 *
 * @}
 */

#include "eps_i_config.h"
#include "nvm.h"

uint8_t eps_i_cfg_get_mac_address(void){
	mac_address_book_t addresses = {0};

	// Read the NVM
	Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

    return addresses.a_mac_address[MAC_ADDR_EPS_I];
}
