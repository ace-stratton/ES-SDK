/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
  * @addtogroup lib_debug
  * @{
  *
  * @file debug.c
  * @brief Common functions used for debugging and measurement sessions
  *
  * @}
  */

#include "debug.h"

#ifdef DEBUG_LIB_ENABLED
/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include <stdio.h>
#include <stdarg.h>
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "debug_cfg.h"
#include "assertions.h"

/*
********************************************************************************************
* INTERNAL DEFINES
********************************************************************************************
*/
/* No Internal defines */

/*
********************************************************************************************
* INTERNAL TYPES DEFINITION
********************************************************************************************
*/
/* No Internal types definition */

/*
********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
********************************************************************************************
*/
/* No External variables definition */

/**
* @brief Variable description
*/


/*
********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
********************************************************************************************
*/
/* No Internal variables definition/declaration */

/*
********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
********************************************************************************************
*/
/* No Internal routines declaration */

/*
********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
********************************************************************************************
*/

void _DBG_initTestPins(void)
{
    _DBG_setTestPin(eTEST_OUT_0, 0);
    _DBG_setTestPin(eTEST_OUT_1, 0);
}

void _DBG_setTestPin(tPinId pid, uint8_t state)
{
// There are currently no dedicated debug pins and this code must be
    switch (pid)
    {
        case eTEST_OUT_0:
            HAL_GPIO_WritePin(TEST_OUT_0_PORT, TEST_OUT_0_PIN, (state == 0) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET));
        break;

        case eTEST_OUT_1:
            HAL_GPIO_WritePin(TEST_OUT_1_PORT, TEST_OUT_1_PIN, (state == 0) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET));
        break;

        default:
        break;
    }
}

void _DBG_toggleTestPin(tPinId pid)
{
    GPIO_PinState pinState;

    switch (pid)
    {
        case eTEST_OUT_0:
            pinState = HAL_GPIO_ReadPin(TEST_OUT_0_PORT, TEST_OUT_0_PIN);

            HAL_GPIO_WritePin(TEST_OUT_0_PORT, TEST_OUT_0_PIN, (pinState == GPIO_PIN_RESET) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));
        break;

        case eTEST_OUT_1:
            pinState = HAL_GPIO_ReadPin(TEST_OUT_1_PORT, TEST_OUT_1_PIN);

            HAL_GPIO_WritePin(TEST_OUT_1_PORT, TEST_OUT_1_PIN, (pinState == GPIO_PIN_RESET) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));
        break;

        default:
        break;
    }
}

#ifdef USE_FULL_ASSERT
/*!
*********************************************************************************************
* @brief Reports the name of the source file and the source line number where the assert_param error has occurred.
* @note Used by STM32 HALs to report assertion failures.
*********************************************************************************************
* @param[input]      uint8_t* file - source file pointer, uint32_t line - source file line number
* @param[output]     none
* @return            none
* @note              !!! Stub method !!!
*********************************************************************************************
*/
void assert_failed(uint8_t * file, uint32_t line)
{
    CRIT_ASSERT(false);
}

#endif
/*
********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
********************************************************************************************
*/
/* No Internal routines definition */

/* ******************************************************************************************* */

#endif  // #ifdef DEBUG_LIB_ENABLED
