/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_EXEH_H
#define ESPS_DRV_EXEH_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_exeh.h
 * @brief    Exception Handling definitions
 *
 * @}
 */

// External imports
#include <esps_drv_exeh_config.h>

// This macros should be defined in the exception handling configuration
#ifndef EXEH_HANDLE_EX
#define EXEH_HANDLE_EX(LEVEL, MOD, EXC)
#endif // EXEH_HANDLE_EX

#ifndef EXEH_HANDLE
#define EXEH_HANDLE(LEVEL, EXC)
#endif // EXEH_HANDLE

#endif //ESPS_DRV_EXEH_H
