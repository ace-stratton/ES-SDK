#ifndef ASSERTIONS_H
#define ASSERTIONS_H

/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup lib_assertions Assertions
 * @{
 *
 * This library provides:
 * - Assertion macros that stop at a breakpoint in debug configurations.
 * - Assertion macros that cause system reset in release configurations.
 *
 *
 * @file assertions.h
 * @brief Definitions of the assertion interfaces
 *
 * @}
 * @}
 */

#include <stdbool.h>

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/
/**
 * @brief Macro used to call an assertion that stops at breakpoint in debug configurations
 *
 * @param condition The condition evaluated in the assertion
 */
#ifdef DEBUG_ASSERTIONS
#define BREAK_ASSERT(condition) assert_break((bool)(condition)) // Breakpoint assertions can be stopped in debug configurations
#else
#define BREAK_ASSERT(condition)
#endif /* DEBUG_ASSERTIONS */

/**
 * @brief Macro used to call an assertion that resets the system in release configurations
 *
 * @param condition The condition evaluated in the assertion
 */
#define CRIT_ASSERT(condition) assert_crit((bool)(condition)) // Critical assertions should not be disabled

/*
***************************************************************************************************
* EXTERNAL TYPES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/
/**
 * @brief Assertion that stops at breakpoint in debug configurations
 *
 * @param condition The condition evaluated in the assertion
 *
 * @note This function should be invoked only through the BREAK_ASSERT macro
 */
void assert_break(const bool condition);

/**
 * @brief Critical assertion leading to software reset of the system
 *
 * @param condition The condition evaluated in the assertion
 *
 * @note This function should be invoked only through the CRIT_ASSERT macro
 */
void assert_crit(const bool condition);


#endif /* ASSERTIONS_H */
