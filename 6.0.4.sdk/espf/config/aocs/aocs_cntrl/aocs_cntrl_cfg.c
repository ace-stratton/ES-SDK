/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup aocs_cntrl
 * @{
 *
 * @file     aocs_cntrl_cfg.c
 * @brief    Attitude and Orbit Control System configuration source
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "aocs_cntrl_cfg.h"
#include "if_aocs_cntrl.h"

#include "debug.h"
#include "if_sys_conf.h"

#include "aocs_cntrl_cubeadcs_int.h"
#if defined(CUBEADCS_GEN2_ENABLED)
#include "aocs_cntrl_cubeadcs_gen2_int.h"
#endif
#include "aocs_cntrl_esadcs_int.h"

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
const aocs_cntrl_base_cfg_t aocs_cntrl_cfg[AOCS_CNTRL_TYPE_MAX] =
{
		{.aocs_if = &aocs_cntrl_cubeadcs_int},
#if defined(CUBEADCS_GEN2_ENABLED)
		{.aocs_if = &aocs_cntrl_cubeadcs_gen2_int},
#endif
		{.aocs_if = &aocs_cntrl_esadcs_int},
};

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
aocs_cntrl_types_t get_enabled_aocs_type(void)
{
	aocs_cntrl_types_t active_aocs = AOCS_CNTRL_TYPE_MAX;

	/* Which ADCS is active? */
	if ( false != sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS) )
	{
		active_aocs = AOCS_CNTRL_TYPE_CUBEADCS;
	}
#if defined(CUBEADCS_GEN2_ENABLED)
	else if (false != sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
    {
        active_aocs = AOCS_CNTRL_TYPE_CUBEADCS_GEN2;
    }
#endif
	else if ( false != sys_conf_is_module_active(SYS_MODULE_ID_ES_ADCS) )
	{
		active_aocs = AOCS_CNTRL_TYPE_ESADCS;
	}
	else
	{
	    /* Sadly, there is no active ADCS module. */
	}

	return active_aocs;
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
