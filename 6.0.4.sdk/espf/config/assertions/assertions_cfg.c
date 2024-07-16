/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup lib_assertions
 * @{
 *
 * @file    assertions_cfg.c
 * @brief   Part of the assertions functionality which is specific to platform or mission
 *
 * @}
 *
 */
#include "assertions_cfg.h"
#include "arm_fault_handler.h"
#include "main.h"

void assert_cfg_break(void)
{
    arm_fault_handler_bkpt_if_debug();
}

void assert_cfg_crit(void)
{
    Error_Handler();
}
