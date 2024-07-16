/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CBUF_CONFIG_H_
#define CBUF_CONFIG_H_

/**
 * @addtogroup libcbuf
 * @{
 *
 * @file cbuf_config.h
 * @brief Provides necessary definitions for libcbuf
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "assertions.h"


#define CBUF_ASSERT(x) CRIT_ASSERT(x)


#ifdef __cplusplus
}
#endif

#endif /* CBUF_CONFIG_H_ */
