/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ADCS_TLM_H_
#define ADCS_TLM_H_

/** @addtogroup Services
  * @{
  *
  * @defgroup service_adcs_tlm adcs_tlm
  * @{
  * @file     adcs_tlm.h
  * @brief    The ADCS telemetry service - periodically collect and update the ADCS relevant Data Cache entries
  *
  * @}
  * @}
  */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "datacache.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/
/** @brief List of ADCS generic telemetry types */
typedef enum
{
	eADCS_GENERIC_TLM_ADCS_ERR_FLAGS,

	eADCS_GENERIC_TLM_MAX

} eAdcs_tlm_g_t; //todo - move to configuration

/** @brief Generic type used to describe ADCS telemetry and link to specific Data Cache id */
typedef struct
{
	const eAdcs_tlm_g_t eTlm_type;
	const dc_did_id eDc_id;
} sGeneric_adcs_tlm_t;

/** @brief Type used to describe CubeADCS telemetry */
typedef struct
{
	const uint8_t u8ID;		/** @brief ID of telemetry type as per the Firmware Reference Manual of CubeSpace */
	const uint8_t u8Size;   /** @brief Size of telemetry type + 1 byte (header of every telemetry request reply) */
} sCubeADCS_TLMType_Desc_t;

/** @brief Type used to describe CubeADCS telemetry and link to specific Data Cache id */
typedef struct
{
	const sCubeADCS_TLMType_Desc_t *pu8CmdList;
	uint8_t u8CmdListSize;
	dc_did_id eDCacheType;
} sCubeADCS_TLM_t;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/

/** @brief Initialise the ADCS Telemetry Task */
void ADCS_TLM_TaskInit(void);
/** @brief Deinitialise (stop monitoring) the ADCS Telemetry Task */
void ADCS_TLM_TaskDeInit(void);

#endif    /* ADCS_TLM_H_ */
/* ******************************************************************************************* */
