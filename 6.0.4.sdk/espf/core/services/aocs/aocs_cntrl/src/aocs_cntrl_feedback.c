/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup adcs_cntrl_fb
 * @{
 *
 * @file     aocs_cntrl_feedback.c
 * @brief    ADCS Control feedback source
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "../inc/aocs_cntrl_feedback.h"

#include "datacache.h"
#include "aocs_cntrl_types.h"

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

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
void aocs_cntrl_feedback_subscribe(p_adcs_cntrl_event const p_user_cb)
{

	// To be implemented

	(void)p_user_cb;

	return;
}

adcs_cntrl_result_t aocs_cntrl_get_status(void)
{

    adcs_cntrl_result_t eStateChangeOperationResult;

    /* Retrieve the current ADCS system state configuration */
    DATA_CACHE_AOCS_CNTRL_SYS_STATE_t sADCSData;
    aocs_cntrl_sys_state_req_state_t eCurrentSysStateCfgStatus = AOCS_CNTRL_SYS_STATE_STATE_MAX;

    if ( (DC_NOT_INITIALIZED != dc_get_aocs_cntrl_sys_state_data(&sADCSData)) &&
         (sADCSData.u8AdcsSysStateStatus < AOCS_CNTRL_SYS_STATE_STATE_MAX ) )
    {
        eCurrentSysStateCfgStatus = (aocs_cntrl_sys_state_req_state_t)sADCSData.u8AdcsSysStateStatus;
    }

    /* Return state change operation status based on system state configuration status variable */
    if (AOCS_CNTRL_SYS_STATE_STATE_REQ_COMPLETED == eCurrentSysStateCfgStatus)
    {
        eStateChangeOperationResult = ADCS_CNTRL_RESULT_SUCCESS;
    }
    else if (AOCS_CNTRL_SYS_STATE_STATE_REQ_FAILED == eCurrentSysStateCfgStatus)
    {
        eStateChangeOperationResult = ADCS_CNTRL_RESULT_FAILED;
    }
    else
    {
        /* If the system state configuration status is not OK or ERROR, then */
        /* it is either attempting to change or custom logic is being executed. */
        /* Either of those means that the system state change operation is in progress */
        eStateChangeOperationResult = ADCS_CNTRL_RESULT_IN_PROGRESS;
    }

    return eStateChangeOperationResult;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/* ******************************************************************************************* */
