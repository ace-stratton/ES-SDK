/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef RNG_H
#define RNG_H

/**
 * @addtogroup rng
 * @{
 *
 * @file rng.h
 * @brief Random number generator service header
 * @}
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/** @brief Initializes the random number generator */
void rng_init(void);

/** @brief Generates a buffer of random values with the specified size
 *  @param[in] p_buf pointer to the buffer where the random bytes shall be stored
 *  @param[in] buf_size number of random bytes to generate
 *
 *  @return true: the random values were successfully generated;
 *          false: random values could not be generated
 */
bool rng_fill(uint8_t * const p_buf, const uint32_t buf_size);

#ifdef __cplusplus
};
#endif

#endif /* RNG_H */
