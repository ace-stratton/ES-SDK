/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup service_beacons
 * @{
 *
 * @file beacons_cfg_user.c
 *
 * @brief Beacon service user configuration main implementation
 *
 * This file describes the set of beacons that need to be transmitted by the beacon service.
 *
 * @}
 */

#include "beacon_cfg_types.h"
#include "nvm_appcfg/inc/nvm_app_types.h"
#include "datacache.h"
#include "conops.h"
#include "fp/ConOps/v0.2/ConOps_server/FP_ConOpsProtocolTypes.h"


/**********************************************************************
 *
 * Internal type definitions
 *
 **********************************************************************/
typedef struct
{
    safe_bool_t sim_mode_active;    /**< indicates whether sim mode is activated */
    uint8_t req_preset_id;            /**< requested preset id in simulation mode */
} sim_mode_t;

/**********************************************************************
 *
 * Internal data definitions
 *
 **********************************************************************/

static sim_mode_t sim_mode_ctx =
{
    .sim_mode_active = SAFE_FALSE,
    .req_preset_id = 0U
};

uint8_t beacons_get_op_mode(void)
{
	uint8_t state_id = 0xFF;

	conops_get_hsm_active_state(&state_id);

	return state_id;
}

uint8_t beacons_cfg_get_active_preset(void)
{
    uint8_t conops_preset_id = 0U;

    if (IS_TRUE(sim_mode_ctx.sim_mode_active))
    {
        if (sim_mode_ctx.req_preset_id >= BEACON_PRESETS_COUNT)
        {
            sim_mode_ctx.req_preset_id = 0U;
        }

        conops_preset_id = sim_mode_ctx.req_preset_id;
    }
    else
    {
        uint8_t state_id = 0U;

        conops_get_hsm_active_state(&state_id);

        switch (state_id)
        {
            case CONOPS_OPMODES_STATE_SAFE:
            {
            	conops_preset_id = 0U;

            	break;
            }

            case CONOPS_OPMODES_STATE_IDLE:
            {
            	conops_preset_id = 1U;

            	break;
            }

            case CONOPS_OPMODES_STATE_DETUMBLING:
            {
            	conops_preset_id = 2U;

            	break;
            }

            case CONOPS_OPMODES_STATE_PAYLOAD:
            {
            	conops_preset_id = 3U;

            	break;
            }

            default:
            {
                break;
            }
        }

    }

    return conops_preset_id;
}

void beacons_cfg_restore_active_preset(void)
{
    SET_FALSE(sim_mode_ctx.sim_mode_active);
    sim_mode_ctx.req_preset_id = 0U;
}

bool beacons_cfg_set_active_preset(uint8_t preset_id)
{
    bool valid_cfg = false;

    if (preset_id < BEACON_PRESETS_COUNT)
    {
        sim_mode_ctx.req_preset_id = preset_id;
        SET_TRUE(sim_mode_ctx.sim_mode_active);

        valid_cfg = true;
    }

    return valid_cfg;
}
