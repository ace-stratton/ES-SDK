/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup payload_ctrl
 * @{
 *
 * @file payload_cfg.c
 *
 * @brief Payload-specific configuration module used by the Payload Controller to manager the
 *           individual payloads.
 * @}
 */

#include "es_cdef.h"
#include "payload_cfg.h"
#include "assertions.h"

const payload_immutable_cfg_t * const payload_cfg_get(const payload_ctrl_payload_t payload_id)
{
    CRIT_ASSERT(payload_id < PAYLOAD_COUNT);

    return (const payload_immutable_cfg_t * const)
            (payload_id < PAYLOAD_COUNT) ?
            (&payload_cfg[payload_id]) :
            NULL;
}
