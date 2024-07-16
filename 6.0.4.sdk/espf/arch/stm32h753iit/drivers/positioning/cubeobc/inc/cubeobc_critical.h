/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CUBEOBC_CRITICAL_H_
#define CUBEOBC_CRITICAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


/**
 * @brief Initializes the critical section used by CubeObcGen2
 * 
 * @return true Init complete
 * @return false init error
 */
bool cubeobc_critical_init(void);


#ifdef __cplusplus
}
#endif

#endif /* CUBEOBC_CRITICAL_H_ */
