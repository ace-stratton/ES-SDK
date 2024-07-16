/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_m
 * @{
 *
 * @file     eps_m.c
 * @brief    Interface for a third party EPS module drivers
 *
 * @}
 */
#include "eps_m.h"
#include "eps_ctrl_cfg.h"
#include "debug.h"
#include "es_cdef.h"


if_sys_mod_t eps_m_module_configuration =
{
    .init   = eps_m_init,
    .run    = eps_m_run,
    .stop   = eps_m_stop,
    .deinit = eps_m_deinit,
};


mod_op_status_id_t eps_m_init(sys_init_level_id_t level)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}

mod_op_status_id_t eps_m_run(void)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}

mod_op_status_id_t eps_m_stop(void)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}

mod_op_status_id_t eps_m_deinit(sys_init_level_id_t level)
{
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}

bool eps_m_set_channel_output(uint8_t channel, bool state)
{
    return false;
}

bool eps_m_get_channel_outputs(void)
{
    return false;
}
