/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_sm_debug.h
 * @brief    State Machine debug definitions (Only debug purposes)
 *
 * @}
 */

#ifndef ESPS_DRV_SM_DEBUG_H
#define ESPS_DRV_SM_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esps_drv.h"
#include "esps_drv_def.h"

#ifdef ESPS_CONFIG_DEBUG_ENABLE

#include "esps_drv_ct.h"

#if (!defined(STATE_TYPE) || !defined(EVENT_TYPE) || !defined(INSTANCE_NAME))
#error "STATE_TYPE, EVENT_TYPE and INSTANCE_NAME preprocessor symbols must be defined to enable debug instrumentation!"
#else

// max 255 elements to match the uint8_t type used below
#define RUNTIMEINFO_ELEM_COUNT      (10U)

#if RUNTIMEINFO_ELEM_COUNT > 255
#error "RUNTIMEINFO_ELEM_COUNT must be 255 at maximum!"
#endif

typedef struct {
    uint8_t u8LastIndex;
    STATE_TYPE aeState[RUNTIMEINFO_ELEM_COUNT];
    EVENT_TYPE aeUnhandledEvent[RUNTIMEINFO_ELEM_COUNT];
    uint8_t au8NestLevel[RUNTIMEINFO_ELEM_COUNT];
} sUnHandledEventInfo_t;

typedef struct {
    uint8_t u8LastStateIndex;
    STATE_TYPE aeStateHistory[RUNTIMEINFO_ELEM_COUNT];
    STATE_TYPE aePrevStateHistory[RUNTIMEINFO_ELEM_COUNT];
    EVENT_TYPE aeTransEvent[RUNTIMEINFO_ELEM_COUNT];
    sUnHandledEventInfo_t unhandledEvents;
} sRuntimeStats_t;

STATIC sRuntimeStats_t INSTANCE_NAME[eMAC_Interface_Count] = {
    {
     .u8LastStateIndex = 0U,
     .aePrevStateHistory = {0U},
     .aeStateHistory = {0U},
     .unhandledEvents.aeState = {0U},
     .unhandledEvents.aeUnhandledEvent = {0U},
     .unhandledEvents.u8LastIndex = 0U}
};

#define RS_STORE_STATE(ifId, ps, s, evt)                              \
		    {   \
                INSTANCE_NAME[ifId].aePrevStateHistory[INSTANCE_NAME[ifId].u8LastStateIndex] = (ps); \
                INSTANCE_NAME[ifId].aeStateHistory[INSTANCE_NAME[ifId].u8LastStateIndex] = (s);      \
                INSTANCE_NAME[ifId].aeTransEvent[INSTANCE_NAME[ifId].u8LastStateIndex] = (evt);      \
                INSTANCE_NAME[ifId].u8LastStateIndex = (INSTANCE_NAME[ifId].u8LastStateIndex + 1) % sizeof(INSTANCE_NAME[ifId].aeStateHistory); \
            }

#define RS_STORE_UNHANDLED_EVENT(ifId, state, evt, nestLevel)    \
            {   \
                INSTANCE_NAME[ifId].unhandledEvents.aeState[INSTANCE_NAME[ifId].unhandledEvents.u8LastIndex] = (state);           \
                INSTANCE_NAME[ifId].unhandledEvents.aeUnhandledEvent[INSTANCE_NAME[ifId].unhandledEvents.u8LastIndex] = (evt);    \
                INSTANCE_NAME[ifId].unhandledEvents.au8NestLevel[INSTANCE_NAME[ifId].unhandledEvents.u8LastIndex] = (nestLevel);  \
                INSTANCE_NAME[ifId].unhandledEvents.u8LastIndex = (INSTANCE_NAME[ifId].unhandledEvents.u8LastIndex + 1) % sizeof(INSTANCE_NAME[ifId].unhandledEvents.aeState); \
            }
#endif // #ifndef STATE_TYPE
#else
#define RS_STORE_STATE(ifId, ps, s, evt)
#define RS_STORE_UNHANDLED_EVENT(ifId, state, evt, nestLevel)
#endif // #ifdef ESPS_CONFIG_DEBUG_ENABLE

#ifdef __cplusplus
}
#endif

#endif /* ESPS_DRV_SM_DEBUG_H */
