/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef _ES_CDEF_H
#define _ES_CDEF_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup es_cdef Common type definitions
 * @{
 *
 * Common types to be used with the SW platform.
 *
 * @file    es_cdef.h
 * @brief   Global common type and macro definitions.
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

// NULL definiton
#include <stddef.h>
// stdint for numeric types
#include <stdint.h>
// stdbool for bool type
#include <stdbool.h>
// atomic types
#include <stdatomic.h>
#include <limits.h>

/** bool redefinition to enable compilation of legacy code which relies on BOOL */
typedef bool        BOOL;

/** Weak callback */
#ifndef WEAK_CBK
#define WEAK_CBK            __attribute__((weak))
#endif

/** Array element count macro */
#define CDEF_ELEMENT_COUNT(A)  ((uint32_t) sizeof(A) / sizeof(A[0]))

// Redefine if necessary
#ifndef STATIC
#define STATIC static
#endif

#ifndef PACKED
#define PACKED __attribute__((__packed__))
#endif

#ifndef NO_RETURN
#define NO_RETURN __attribute__((noreturn))
#endif

// type declaration macros
#define TD_VOLATILE(type)           type volatile
#define TD_PTR_TO_VOLATILE(type)    type volatile *
#define TD_VOLPTR(type)             type *volatile
#define TD_VOLPTR_TO_VOLATILE(type) type *volatile *

#ifndef ES_CDEF_UNUSED
#define ES_CDEF_UNUSED(x)     ((void) x)
#endif

extern void Error_Handler(void);

/**
 * The following constants are used for safer boolean value checking
 * because they have an increased Hamming distance and are less
 * susceptible to SEU (Single Event Upset) which may be caused by radiation
 *
 * Make sure that you use the following macros to set/check the value of a safe_boot_t type:
 *
 * SAFE_FALSE, SAFE_TRUE, IS_FALSE, IS_TRUE, SET_FALSE, SET_TRUE
 *
 */
typedef uint8_t safe_bool_t;
#define SAFE_FALSE  (0x00U)
#define SAFE_TRUE   (0xFFU)
#define IS_FALSE(safe_var)	(SAFE_FALSE == (uint8_t) (safe_var))
#define IS_TRUE(safe_var)	(SAFE_TRUE == (uint8_t) (safe_var))
#define SET_FALSE(safe_var)	{ (safe_var) = SAFE_FALSE; }
#define SET_TRUE(safe_var)	{ (safe_var) = SAFE_TRUE; }

/** Calculate the difference between two `osKernelGetTickCount()` values */
#define TICK_DIFF(END, START) ((END >= START) ? (END - START) : (END + ULONG_MAX - START))

/**
 * You can use the TODO(msg) macro to print TODO messages in your compilation output trace, e.g.
 *
 * TODO(I have to fix this someday!)
 *
 * @note Commas inside the TODO(...) are not allowed!
 */
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))


#if defined(__GNUC__) && (__GNUC__ >= 7)
    #define PRAGMA_DIAG_PUSH() \
        DO_PRAGMA(GCC diagnostic push)

    #define PRAGMA_DIAG_IGNORED(warn) \
        DO_PRAGMA(GCC diagnostic ignored #warn)

    #define PRAGMA_DIAG_POP() \
        DO_PRAGMA(GCC diagnostic pop)
#else
    #define PRAGMA_DIAG_PUSH() //this has to be defined for your compiler
    #define PRAGMA_DIAG_IGNORED(warn) //this has to be defined for your compiler
    #define PRAGMA_DIAG_POP() //this has to be defined for your compiler
#endif

#ifdef __cplusplus
}
#endif

#endif // _ES_CDEF_H
