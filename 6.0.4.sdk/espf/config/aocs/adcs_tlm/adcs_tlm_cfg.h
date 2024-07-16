/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/** @addtogroup service_adcs_tlm
  * @{
  *
  * @file adcs_tlm_cfg.h
  *
  * @brief The ADCS telemetry service configuration interface
  *
  * @}
 */
#ifndef ADCS_TLM_CFG_H_
#define ADCS_TLM_CFG_H_

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "adcs_tlm.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/
/** @brief Telemetry task period */
#define ADCS_TLM_TASK_PERIOD_MS 	3000
/** @brief Number of specific Data Cache entries populated by the CubeADCS */
#define ADCS_TLM_CUBE_ADCS_DC_NUM 	5

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/
/** @brief CubeADCS specific telemetry description */
extern sCubeADCS_TLM_t au8CubeADCS_TLM[ADCS_TLM_CUBE_ADCS_DC_NUM];

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/
/** @brief Update a specific data cache type with the relevant data
 *
 * @param[in] eDCType the data cache type to update
 * @param[in] pu8Src pointer to the data to be used to update the data cache type
 */
void ADCS_TLM_CFG_Update_DCache(dc_did_id eDCType, uint8_t *pu8Src);

#endif    /* ADCS_TLM_CFG_H_ */
/* ******************************************************************************************* */
