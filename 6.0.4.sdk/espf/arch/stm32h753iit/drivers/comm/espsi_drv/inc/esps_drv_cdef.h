/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_CDEF_H
#define ESPS_DRV_CDEF_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file esps_drv_cdef.h
 * @brief    Global common type and macro definitions.
 *
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

// bool redefinition to enable compilation of legacy code which relies on BOOL
    typedef bool BOOL;

#ifndef WEAK_CBK
#define WEAK_CBK            __attribute__((weak))
#endif

// Array element count macro
#define CDEF_ELEMENT_COUNT(A)  ((uint32_t) sizeof(A) / sizeof(A[0]))

// redefine if necessary
#ifndef STATIC
#define STATIC static
#endif

#ifndef PACKED
#define PACKED __attribute__((__packed__))
#endif

// type declaration macros
#define TD_VOLATILE(type)           type volatile
#define TD_PTR_TO_VOLATILE(type)    type volatile *
#define TD_VOLPTR(type)             type *volatile
#define TD_VOLPTR_TO_VOLATILE(type) type *volatile *

/// STM32 default Error_Handler function
extern void Error_Handler(void);

#ifdef __cplusplus
}
#endif
#endif
