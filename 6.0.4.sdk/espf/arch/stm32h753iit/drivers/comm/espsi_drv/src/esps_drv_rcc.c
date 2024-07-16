/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_rcc.c
 * @brief    Reset and Clock Controller configuration
 *
 * @}
 */

// External imports
#include "esps_drv_stm32.h"

#include "esps_drv_rcc.h"

/// Enable the RCC peripheral
void MAC_RCC_vPeripheralClockEnable(eRCCPeripheralClock_t fp_eClock, uint32_t fp_u32EnableMask)
{
    switch (fp_eClock)
    {
    case (eRCCPeripheralClock_APB1):
        LL_APB1_GRP1_EnableClock(fp_u32EnableMask);
        break;

    case (eRCCPeripheralClock_APB2):
        LL_APB2_GRP1_EnableClock(fp_u32EnableMask);
        break;

    default:
        break;
    }
}

/// Disable the RCC peripheral
void MAC_RCC_vPeripheralClockDisable(eRCCPeripheralClock_t fp_eClock, uint32_t fp_u32DisableMask)
{
    switch (fp_eClock)
    {
    case (eRCCPeripheralClock_APB1):
        LL_APB1_GRP1_DisableClock(fp_u32DisableMask);
        break;

    case (eRCCPeripheralClock_APB2):
        LL_APB2_GRP1_DisableClock(fp_u32DisableMask);
        break;

    default:
        break;
    }
}
