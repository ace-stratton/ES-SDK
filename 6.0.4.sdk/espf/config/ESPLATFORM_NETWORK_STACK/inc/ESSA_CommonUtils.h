/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPLATFORM_NETWORK_STACK_INC_ESSA_COMMONUTILS_H_
#define ESPLATFORM_NETWORK_STACK_INC_ESSA_COMMONUTILS_H_

/**
 * @addtogroup ESPS_I
 * @{
 *
 * @file    ESSA_CommonUtils.h
 * @brief   ESPS stack common helper function declarations
 *
 * @}
 */

#include "es_cdef.h"

#include "ESPLATFORM_NETWORK_STACK/ES_SAT_MAC/ES_SAT_MAC_Context.h"

#if !defined(TRACE)
    #if defined(ESSA_SP_DEBUG_ENABLED)
        #include "trace.h"

        #define TRACE(formatStr, ...)   ES_TRACE_DEBUG(formatStr OPT_VA_ARGS(__VA_ARGS__));
    #else   // #if defined(ESSA_SP_DEBUG_ENABLED)
        #define TRACE(formatStr, ...)
    #endif  // #if defined(ESSA_SP_DEBUG_ENABLED)
#endif

const char * const GetMACErrAsString(ESSATMAC_ErrCodes errCode);
uint16_t ESSA_CommonUtils_getTickU16(void);

#endif /* ESPLATFORM_NETWORK_STACK_INC_ESSA_COMMONUTILS_H_ */
