/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup ESPS_I
 * @{
 *
 * @file     ESSA_CommonUtils.c
 * @brief    ESPS stack common helper function definitions
 *
 * @}
 */

#include "ESSA_CommonUtils.h"
#include "stm32h7xx_hal.h"

static const char * const macErrors[] =
{
        "ESSATMAC_EC_OK",
        "ESSATMAC_EC_ERROR",
        "ESSATMAC_EC_NULL",
        "ESSATMAC_EC_BUSY",
        "ESSATMAC_EC_NO_MEM",
        "ESSATMAC_EC_Q_FULL",
        "ESSATMAC_EC_Q_NOT_EMPTY",
        "ESSATMAC_EC_RETRY_COUNT_LIMIT",
        "ESSATMAC_EC_TX_COLLISION",
        "ESSATMAC_EC_UNSUPPORTED_NET_TYPE",
        "ESSATMAC_EC_INVALID_PARAMS",
        "ESSATMAC_EC_BUS_BUSSY"
};

uint16_t ESSA_CommonUtils_getTickU16(void)
{
    return (uint16_t) HAL_GetTick();
}

const char * const GetMACErrAsString(ESSATMAC_ErrCodes errCode)
{
    if (((uint16_t) errCode) < (sizeof(macErrors) / sizeof(macErrors[0])))
        return macErrors[(uint16_t) errCode];
    else
        return "errCode out of range\0";
}
