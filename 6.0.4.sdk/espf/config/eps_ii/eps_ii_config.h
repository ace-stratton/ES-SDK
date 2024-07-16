/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPF_CONFIG_EPS_II_EPS_II_CONFIG_H_
#define ESPF_CONFIG_EPS_II_EPS_II_CONFIG_H_

/**
 * @addtogroup eps_ii
 * @{
 *
 * @file     eps_ii_config.h
 * @brief    EPS II drivers configuration
 *
 * @}
 */
#include "es_cdef.h"

//As the EPS devices have limited queues for receiving/transmitting messages(5 for RCV and 3 for TX)
//this delay need to be used after each 3 messages sent to the device.
#define EPS_II_NEEDED_DELAY_FOR_PROCESSING (3000) /**< Request for telemetry to EPS II device. Every 3s*/

/** @brief Read the MAC EPS II BP address from the nvm MAC Address book.
 *
 *  @return MAC Address from nvm or default EPS_II_BP_MAC_ADDRESS in case of error.
 */
void eps_ii_cfg_get_bp_mac_addresses(uint8_t * p_bp_address_book, uint8_t bp_count);

/** @brief Read the MAC EPS II PDM address from the nvm MAC Address book.
 *
 *  @return MAC Address from nvm.
 */
uint8_t eps_ii_cfg_get_pdm_mac_address(void);


#endif /* ESPF_CONFIG_EPS_II_EPS_II_CONFIG_H_ */
