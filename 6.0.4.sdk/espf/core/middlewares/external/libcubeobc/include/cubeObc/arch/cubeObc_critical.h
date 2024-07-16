/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CUBEOBC_CRITICAL__H
#define CUBEOBC_CRITICAL__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define CUBEOBC_CRITICAL_WAIT_FOREVER 0xFFFFFFFFU

/**
 * @brief Enter critical section.
 * @param timeout - Entering the critical section shall stop being attempted after this number of milliseconds
 * @retval true: Critical section successfully entered
 * @retval false: An error occurred when entering the critical section
 */
bool cubeObc_critical_enter(const uint32_t timeout);

/**
 * @brief Exit critical section.
 */
void cubeObc_critical_exit(void);


#ifdef __cplusplus
}
#endif
#endif /* CUBEOBC_CRITICAL__H */
