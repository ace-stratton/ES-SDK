/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef LIBHSM_CFG_H
#define LIBHSM_CFG_H

/**
 * @addtogroup libhsm
 * @{
 *
 * @file libhsm_cfg.h
 * @brief Configuration definitions of the HSM library
 *
 * @}
 */

#ifdef UTEST
#include <stdbool.h>
void test_assert(bool cond);
void test_trace(const char *msg, ...);

#define HSM_ASSERT(cond)                test_assert(cond)
#define HSM_TRACE_INFO(msg, ...)        test_trace(msg, ##__VA_ARGS__);
#define HSM_TRACE_DEBUG(msg, ...)       test_trace(msg, ##__VA_ARGS__);
#define HSM_TRACE_ERROR(msg, ...)       test_trace(msg, ##__VA_ARGS__);
#else
#include <assert.h>

#define HSM_ASSERT(cond)                assert(cond)
#define HSM_TRACE_INFO(msg, ...)        trace(msg, ##__VA_ARGS__);
#define HSM_TRACE_DEBUG(msg, ...)       trace(msg, ##__VA_ARGS__);
#define HSM_TRACE_ERROR(msg, ...)       trace(msg, ##__VA_ARGS__);
#endif  // #ifdef UTEST

#endif  // #ifndef LIBHSM_CFG_H
