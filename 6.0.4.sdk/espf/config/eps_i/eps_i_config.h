/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPF_CONFIG_EPS_I_EPS_I_CONFIG_H_
#define ESPF_CONFIG_EPS_I_EPS_I_CONFIG_H_

/**
 * @addtogroup eps_i
 * @{
 *
 * @file     eps_i_config.h
 * @brief    EPS I drivers configuration
 *
 * @}
 */
#include "es_cdef.h"

/** Period for the eps i task */
#define EPS_I_TASK_PERIOD           (2000) // EPS I refreshes the data every 100 ms (vbat_ideal every 1s)

/** @brief Read the MAC EPS I address from the nvm MAC Address book.
 *
 *  @return MAC Address from nvm or default EPS_I_MAC_ADDRESS in case of error.
 */
uint8_t eps_i_cfg_get_mac_address(void);

#endif /* ESPF_CONFIG_EPS_I_EPS_I_CONFIG_H_ */
