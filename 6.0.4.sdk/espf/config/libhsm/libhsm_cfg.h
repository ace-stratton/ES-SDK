/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef LIBHSM_CFG_H
#define LIBHSM_CFG_H

#ifdef UTEST
#include <stdbool.h>
void test_assert(bool cond);
void test_trace(const char *msg, ...);

#define HSM_ASSERT(cond)                test_assert(cond)
#define HSM_TRACE_INFO(msg, ...)        test_trace(msg, ##__VA_ARGS__);
#define HSM_TRACE_DEBUG(msg, ...)       test_trace(msg, ##__VA_ARGS__);
#define HSM_TRACE_ERROR(msg, ...)       test_trace(msg, ##__VA_ARGS__);
#else
#include "main.h"
#include "trace.h"

#define HSM_ASSERT(cond)                { if (!(cond)) Error_Handler(); }

#if defined(DEBUG_TRACE_LIBHSM_ENABLED)
#define HSM_TRACE_INFO(msg, ...)        ES_TRACE_INFO(msg, ##__VA_ARGS__)
#define HSM_TRACE_DEBUG(msg, ...)       ES_TRACE_DEBUG(msg, ##__VA_ARGS__)
#define HSM_TRACE_ERROR(msg, ...)       ES_TRACE_ERROR(msg, ##__VA_ARGS__)
#else	// #if defined(DEBUG_TRACE_LIBHSM_ENABLED)
#define HSM_TRACE_INFO(msg, ...)
#define HSM_TRACE_DEBUG(msg, ...)
#define HSM_TRACE_ERROR(msg, ...)
#endif
#endif  // #ifdef UTEST

#endif  // #ifndef LIBHSM_CFG_H
