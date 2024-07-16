/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TRACE_DEFS_H_
#define TRACE_DEFS_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @addtogroup libtrace
 * @{
 *
 * @file trace_defs.h
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define TRACE_LVL_ENABLE(lvl)       (1 << (uint8_t)(lvl))
#define TRACE_LVL_ENABLED(num, lvl) (0 != ((num) & (1 << (uint8_t)(lvl))))


#ifdef __cplusplus
}
#endif

#endif /* TRACE_DEFS_H_ */
