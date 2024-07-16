/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ES_IF_DEBUG_H
#define ES_IF_DEBUG_H
/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup lib_debug Debug
 * @{
 *
 * This library provides:
 * - Basic message tracing macros to be used throughout the system.
 * - Basic test pin routines for easier intrumentation in the code.
 *
 *
 * @file debug.h
 * @brief Basic debug library public interface
 *
 * @}
 * @}
 */

#include <stdint.h>
#include <stdbool.h>
#include "sys_printf.h"

extern void Error_Handler(void);

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdio.h>

#ifndef OPT_VA_ARGS
#define OPT_VA_ARGS(...) , ##__VA_ARGS__
#endif  // #ifndef OPT_VA_ARGS

#ifdef DEBUG_LIB_ENABLED

/**
 * @name Macro function wrappers
 * @{
 *
 * Use these macros instead of directly calling the library functions because this library
 * will probably change in next versions of the SDK and it will be easier to switch to a new
 * version of it later.
 */
#define DBG_initTestPins()          _DBG_initTestPins()
#define DBG_setTestPin(pid, state)  _DBG_setTestPin(pid, state)
#define DBG_toggleTestPin(pid)      _DBG_toggleTestPin(pid)
/** @} */
#else
#define DBG_initTestPins()
#define DBG_setTestPin(pid, state)
#define DBG_toggleTestPin(pid)
#endif  // #ifdef DEBUG_LIB_ENABLED

#ifdef DEBUG_LIB_ENABLED
/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/
/**
 * @brief Defines the logical test pin identifiers used in the system
 */
typedef enum
{
    eTEST_OUT_0,    /**< mapped to TEST_OUT_0_PIN/PORT in debug_cfg.h */
    eTEST_OUT_1     /**< mapped to TEST_OUT_1_PIN/PORT in debug_cfg.h */
} tPinId;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/
/* No External variables declarations */

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/

/**
  * @brief Performs initialization of the test pins clock and state
  */
void _DBG_initTestPins(void);

/**
  * @brief Updates the state of a test pin as requested
  * @param[in] pid test pin logical identifier
  * @param[in] state requested pin state to set
  */
void _DBG_setTestPin(tPinId pid, uint8_t state);

/**
  * @brief Reads the current state of a test pin and toggles it
  * @param[in] pid test pin logical identifier
  */
void _DBG_toggleTestPin(tPinId pid);

#endif

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif    /* ES_IF_DEBUG_H */
/* ******************************************************************************************* */
