/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/** @addtogroup service_adcs_tlm
  * @{
  *
  * @file adcs_tlm_cfg.c
  * @brief The ADCS telemetry service configuration sources
  *
  * @}
  */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "adcs_tlm_cfg.h"

#include "es_cdef.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
#ifndef COUNT_OF
/** @brief Macro to return the size of an array of maximum element count 255 */
#define COUNT_OF(x) ((uint8_t) (sizeof(x) / sizeof(x[0])))
#endif  // #ifndef COUNT_OF

#define SIZE_M0 (1U)
#define SIZE_M1 (4U)
#define SIZE_M2	(1U)
#define SIZE_M3	(4U)
#define SIZE_M4	(1U)

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/
/* No Internal types definition */

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/
/** @brief Specific CubeADCS telemetry description */
STATIC const sCubeADCS_TLMType_Desc_t TLM_M0[SIZE_M0] = { {191, 0x49} };
/** @brief Specific CubeADCS telemetry description */
STATIC const sCubeADCS_TLMType_Desc_t TLM_M1[SIZE_M1] = { {218, 0x07}, {147, 0x07}, {199, 0x07}, {155, 0x07} };
/** @brief Specific CubeADCS telemetry description */
STATIC const sCubeADCS_TLMType_Desc_t TLM_M2[SIZE_M2] = { {132, 0x07} };
/** @brief Specific CubeADCS telemetry description */
STATIC const sCubeADCS_TLMType_Desc_t TLM_M3[SIZE_M3] = { {146, 0x07}, {193, 0x2B}, {229, 0x07}, {230, 0x07} };
/** @brief Specific CubeADCS telemetry description */
STATIC const sCubeADCS_TLMType_Desc_t TLM_M4[SIZE_M4] = { {195, 0x27} };

sCubeADCS_TLM_t au8CubeADCS_TLM[ADCS_TLM_CUBE_ADCS_DC_NUM] = {
		{.pu8CmdList = &TLM_M0[0], .u8CmdListSize = COUNT_OF(TLM_M0), .eDCacheType = DC_DID_ADCS_0_DATA},
		{.pu8CmdList = &TLM_M1[0], .u8CmdListSize = COUNT_OF(TLM_M1), .eDCacheType = DC_DID_ADCS_1_DATA},
		{.pu8CmdList = &TLM_M2[0], .u8CmdListSize = COUNT_OF(TLM_M2), .eDCacheType = DC_DID_ADCS_2_DATA},
		{.pu8CmdList = &TLM_M3[0], .u8CmdListSize = COUNT_OF(TLM_M3), .eDCacheType = DC_DID_ADCS_3_DATA},
		{.pu8CmdList = &TLM_M4[0], .u8CmdListSize = COUNT_OF(TLM_M4), .eDCacheType = DC_DID_ADCS_4_DATA},
};



/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
/* No Static variables definition/declarations */

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
/* No Static routines declarations */

/*
*********************************************************************************************
* EXTERNAL (NON-STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
void ADCS_TLM_CFG_Update_DCache(dc_did_id eDCType, uint8_t *pu8Src)
{
	switch (eDCType)
	{
	case DC_DID_ADCS_0_DATA:
		dc_set_adcs_0_data((DATA_CACHE_ADCS_0_t *)pu8Src);
		break;
	case DC_DID_ADCS_1_DATA:
		dc_set_adcs_1_data((DATA_CACHE_ADCS_1_t *)pu8Src);
		break;
	case DC_DID_ADCS_2_DATA:
		dc_set_adcs_2_data((DATA_CACHE_ADCS_2_t *)pu8Src);
		break;
	case DC_DID_ADCS_3_DATA:
		dc_set_adcs_3_data((DATA_CACHE_ADCS_3_t *)pu8Src);
		break;
	case DC_DID_ADCS_4_DATA:
		dc_set_adcs_4_data((DATA_CACHE_ADCS_4_t *)pu8Src);
		break;
	default:
		break;
	}
}


/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/* No static routines definitions */

/* ******************************************************************************************* */
