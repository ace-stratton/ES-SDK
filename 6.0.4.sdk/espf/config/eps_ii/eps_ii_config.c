/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_ii
 * @{
 *
 * @file     eps_ii_config.c
 * @brief    EPS II drivers configuration
 *
 * @}
 */

#include "eps_ii_config.h"
#include "nvm.h"
#include <string.h>

void eps_ii_cfg_get_bp_mac_addresses(uint8_t * p_bp_address_book, uint8_t bp_count){

    mac_address_book_t addresses = {0};

    BREAK_ASSERT(bp_count == sizeof(addresses.a_eps_batterypack_addresses));

    // Read the NVM
    Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

    memcpy(p_bp_address_book, addresses.a_eps_batterypack_addresses, bp_count);

}

uint8_t eps_ii_cfg_get_pdm_mac_address(void){
    mac_address_book_t addresses = {0};

    // Read the NVM
    Nvm_GetBlockById(NVM_MAC_ADDRESS_BOOK, &addresses);

    return addresses.a_mac_address[MAC_ADDR_EPS_II_PDM];
}
