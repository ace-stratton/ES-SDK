/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __ESSA_STACKCONFIGTYPES_H__
#define __ESSA_STACKCONFIGTYPES_H__

/**
 * @addtogroup ESPS_I
 * @{
 *
 * @file    ESSA_Stack_ConfigTypes.h
 * @brief   ESPS Stack protocols configuration
 *
 * @}
 */

#pragma pack(push)
#pragma pack(1)

typedef enum
{
    ESSASNETT_INTERNAL = 0,
    ESSASNETT_AIR = 1,
    ESSASNETT_GS_MACFP_GW = 2,
    ESSASNETT_UART_BRIDGE = 3,
    ESSASNETT_UART_BRIDGE_LOCAL = 4,
#if defined(MICROPYTHON_SERVICE_ENABLED)
    ESSASNETT_MICROPYTHON_GW = 5,
#endif
    ESSASNETT_MAX
} ESSASNetType;
#pragma pack(pop)

#endif  // __ESSA_STACKCONFIGTYPES_H__
