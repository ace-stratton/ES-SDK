/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup rng
 * @{
 *
 * @file rng.c
 * @brief Random number generator service implementation
 *
 * This is a basic blocking random number generator service which relies on the
 * STM32 TRNG module. It is meant to abstract the random number generation for
 * other modules in the system in order to be more portable in the future or if
 * the HW does not support TRNG function.
 *
 * @}
*/

#include <string.h>
#include "rng.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_rng.h"
#include "assertions.h"
#include "trace.h"

/** Handle structure for the RNG HAL. */
static RNG_HandleTypeDef rng_hnd;

/** @brief Result from the last operation of the RNG HAL. */
static HAL_StatusTypeDef rng_res;

void rng_init(void)
{
    rng_hnd.Instance = RNG;

    rng_res = HAL_RNG_Init(&rng_hnd);

    if (HAL_OK != rng_res)
    {
        ES_TRACE_ERROR("RNG hardware init error: %d\n", rng_res);
    }
}

bool rng_fill(uint8_t * const p_buf, const uint32_t buf_size)
{
    bool res = false;

    CRIT_ASSERT(NULL != p_buf);
    CRIT_ASSERT(buf_size > 0);

    if ( (NULL == p_buf) || (0 == buf_size) )
    {
        ES_TRACE_ERROR("RNG wrong params error: %d, %d\n", p_buf, buf_size);
        return false;
    }

    if (HAL_OK != rng_res)
    {
        ES_TRACE_ERROR("RNG not initialized: %d\n", rng_res);
        return false;
    }

    uint32_t rand_word = 0U;
    uint32_t rn_cnt = 0;
    uint32_t *p_num = (uint32_t *) p_buf;
    uint32_t max_cnt = buf_size / sizeof(rand_word);
    bool err = false;

    while (rn_cnt < max_cnt)
    {
        rng_res = HAL_RNG_GenerateRandomNumber(&rng_hnd, &rand_word);

        if (HAL_OK == rng_res)
        {
            *(p_num++) = rand_word;
            rn_cnt++;
        }
        else
        {
            err = true;
            break;
        }
    }

    if (false == err)
    {
        // Fill any remaining bytes
        max_cnt = buf_size % sizeof(rand_word);

        if (max_cnt > 0)
        {
            rng_res = HAL_RNG_GenerateRandomNumber(&rng_hnd, &rand_word);

            if (HAL_OK == rng_res)
            {
                // Fill the remaining bytes from the generated 32-bit random number
                (void) memcpy(p_num, &rand_word, max_cnt);
            }
            else
            {
                err = true;
            }
        }
    }

    res = !err;

    if (false == res)
    {
        ES_TRACE_ERROR("RNG hardware generation error: %d\n", rng_res);
    }

    return res;
}
