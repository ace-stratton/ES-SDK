/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESSA_STACK_FACADE_H_
#define ESSA_STACK_FACADE_H_

/**
 * @addtogroup ESPS_I
 * @{
 *
 * @file    ESSA_Stack_Facade.h
 * @brief   Wrapper for the ESPS stack initialization declarations
 *
 * @}
 */

#include "es_cdef.h"

void ESSA_Stack_Facade_Init();
safe_bool_t ESSA_Stack_Facade_Is_Init(void);

#endif  // ESSA_STACK_FACADE_H_
