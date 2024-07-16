/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup app_conops
 * @{
 *
 * @file conops_payload.c
 * @brief Concept of operations payload source file
 *
 * @}
 *
 */

#if defined(OPMODES_ENABLED)

#include "conops_payload.h"
//#include "conops_cfg.h"
#include "conops.h"

#include "payload_scheduler.h"

#include "assertions.h"
#include "es_exeh.h"
#include "string.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/


/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

STATIC void fs_conops_payload_op_callback(payload_ctrl_event_t *p_event);

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

void conops_payload_trigger_event(uint8_t u8PaySchedId)
{
	CRIT_ASSERT(u8PaySchedId < PAYLOAD_COUNT);

	sConOps_pay_cfg_t sPayCfg;

	sPayCfg.payload_id = u8PaySchedId;
	memcpy(&sPayCfg.pointing_cfg, &conops_payload_flags[ u8PaySchedId ].sched_data.adcs_args, sizeof(record_adcs_t));
	sPayCfg.payload_args.flags = (uint8_t) conops_payload_flags[ u8PaySchedId ].sched_data.flags;
	memcpy(&sPayCfg.payload_args.pl_args, &conops_payload_flags[ u8PaySchedId ].sched_data.payload_args, sizeof(sPayCfg.payload_args.pl_args));

	if ( SCHED_STATE_ACTIVE_PAYLOAD == conops_payload_flags[ u8PaySchedId ].flag )
		conops_trigger_hsm(ev_conops_sm_payload_flag_set, &sPayCfg);
	else
		conops_trigger_hsm(ev_conops_sm_payload_flag_cleared, &sPayCfg);
}

void conops_payload_stop(uint8_t u8PayId, bool bEmergency)
{
	CRIT_ASSERT(u8PayId < PAYLOAD_COUNT);

	if ( true == bEmergency )
		(void)payload_ctrl_stop(u8PayId, PL_OP_STOP_MODE_EMERGENCY);
	else
		(void)payload_ctrl_stop(u8PayId, PL_OP_STOP_MODE_NORMAL);
}

void conops_payload_register_callback(void)
{
	payload_ctrl_subscribe_events(fs_conops_payload_op_callback);
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/**
* @brief Callback for payload errors
*
* @param[in] payload_ctrl_event_t *p_event - payload controller reported event
*/
STATIC void fs_conops_payload_op_callback(payload_ctrl_event_t *p_event)
{
	CRIT_ASSERT(NULL != p_event);

	/* Kick the SM on payload error */
	if ( PL_STATE_ERROR == p_event->op_state)
	{
		conops_set_logical_flag_value(eFLAG_PAYLOAD_ERR, true);

		conops_trigger_hsm(ev_conops_sm_payload_flag_cleared, NULL);
	}
	else
	{
		/* Kick the SM on an ADCS error in the ADCS system state configuration request */
		if ( PL_STATE_ADCS_TIMEOUT <= p_event->op_state )
		{
		    CONOPS_TRACE_DBG("[AAA DBG]: ----- PL_STATE_ERROR: %d ---------------------------------- \r", p_event->op_state);
			conops_set_logical_flag_value(eFLAG_ADCS_ERR, true);

			conops_trigger_hsm(eHSM_StdEvent_Periodic, NULL);
		}
	}
}

#endif /* OPMODES_ENABLED */
