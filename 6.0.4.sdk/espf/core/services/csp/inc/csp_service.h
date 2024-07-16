/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CSP_SERVICE_H_
#define CSP_SERVICE_H_

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup csp_service
 * @{
 *
 * @file csp_service.h
 *
 * @brief Initialisation of the CSP stack (router task, ping handler, default route, etc.)
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


/**
 * @brief Initialises the CSP stack.
 *
 * @retval true  Initialisation complete
 * @retval false Initialisation error
 */
bool csp_service_init(void);


#ifdef __cplusplus
}
#endif

#endif /* CSP_SERVICE_H_ */
