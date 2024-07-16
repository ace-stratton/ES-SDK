/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup service_exeh
 * @{
 * @file es_exeh_cfg.c
 * @brief Implement custom exception handling for each type of exception in this file.
 * @}
 *
 */
#include "es_cdef.h"
#include "es_exeh_cfg.h"
#include "main.h"

// Called when handling a warning. Ignore warnings.
void EXEH_vHandleWarning(void)
{

}

// Called when handling errors. Ignore error.
void EXEH_vHandleError(void)
{

}

// Called when handling fatal exception. MCU Reset.
void EXEH_vHandleFatal(void)
{
    Error_Handler();
}
