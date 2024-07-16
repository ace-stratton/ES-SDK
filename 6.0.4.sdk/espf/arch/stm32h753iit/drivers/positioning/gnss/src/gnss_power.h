/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GNSS_POWER_H_
#define GNSS_POWER_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_power.h
 *
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


/**
 * @brief Power on the GNSS
 */
void gnss_power_on(void);

/**
 * @brief Power off the GNSS
 */
void gnss_power_off(void);

/**
 * @brief Checks if power is on or off
 *
 * @retVal true  Power is on
 * @retVal false Power is off
 */
bool gnss_power_is_on(void);


#ifdef __cplusplus
}
#endif

#endif /* GNSS_POWER_H_ */
