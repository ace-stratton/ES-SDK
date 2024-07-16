/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CONOPS_PAYLOAD_H_
#define CONOPS_PAYLOAD_H_

/**
 * @addtogroup app_conops
 * @{
 *
 * @file conops_payload.h
 * @brief Concept of operations payload related source file
 *
 * @}
 *
 */

#include "es_cdef.h"
#include "payload_ctrl.h"
#include "payload_shared_types.h"
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

typedef struct
{
	payload_ctrl_payload_t payload_id;
	record_adcs_t pointing_cfg;
	pl_args_t payload_args;
} sConOps_pay_cfg_t;

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

/**
 * @brief Request activation or deactivation of a payload
 * @param[input]      uint8_t u8PaySchedId - payload id as stored by the scheduler
 *
 * @note              To be called from one task only - preferably the payload scheduler
 */
void conops_payload_trigger_event(uint8_t u8PaySchedId);

/**
 * @brief Stop a payload
 * @param[input]      uint8_t u8PayId - payload ID
 *                    bool bEmergency - Invoke emergency stop procedure for a payload
 */
void conops_payload_stop(uint8_t u8PayId, bool bEmergency);

/**
* @brief Register callback to payload controller
*/
void conops_payload_register_callback(void);

#endif    /* CONOPS_PAYLOAD_H_ */
