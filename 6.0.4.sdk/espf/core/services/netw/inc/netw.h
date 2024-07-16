/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef NETW_H
#define NETW_H

/**
 * @addtogroup Networking
 * @{
 *
 * @file netw.h
 * @brief Networking service public interface
 * @}
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/** @brief Initializes the networking services */
void netw_init(void);

#ifdef __cplusplus
};
#endif

#endif /* NETW_H */
