/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef SBAND_TMTC_CFG_H
#define SBAND_TMTC_CFG_H

/**
 * @addtogroup sband_tmtc
 * @{
 *
 * @file     es_band_tmtc.h
 * @brief    S Band TMTC drivers configuration
 *
 * @}
 */
#include "es_cdef.h"

/** Timeout for waiting for a response from the S Band module */
#define SBAND_TMTC_RESP_TIMEOUT     (5)

/** @brief Read the SBand TMTC MAC address from the nvm MAC Address book.
 *
 *  @return MAC Address from nvm.
 */
uint8_t sband_tmtc_cfg_get_mac_address(void);

#endif /* SBAND_TMTC_CFG_H */
