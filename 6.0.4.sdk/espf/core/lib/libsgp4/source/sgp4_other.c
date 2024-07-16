/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libsgp4
 * @{
 *
 * @file sgp4_other.c
 * @brief Helper methods for the SGP4 library
 *
 * @}
 */

#include "sgp4_propagator.h"
#include <stdint.h>

sgp4_t sgp4_julian_date(sgp4_t YY, sgp4_t MM, sgp4_t DD, sgp4_t H, sgp4_t M, sgp4_t S)
{
    return 1721013.5 +
           367.0 * YY -
           (sgp4_t)((int32_t)((7.0 / 4.0) * (YY + (sgp4_t)((int32_t)((MM + 9.0) / 12.0))))) +
           (sgp4_t)((int32_t)((275.0 * MM / 9.0))) +
           DD +
           (60.0 * H + M + S / 60.0) / 1440.0;
}
