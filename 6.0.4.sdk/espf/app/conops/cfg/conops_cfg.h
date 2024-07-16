/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CONOPS_CFG_CONOPS_CFG_H_
#define CONOPS_CFG_CONOPS_CFG_H_

/**
 * @addtogroup app_conops
 * @{
 *
 * @file conops_cfg.h
 * @brief Concept of operations configuration header
 *
 * @}
 *
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "trace.h"
#include "conops_sm_user.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

#define CONOPS_SM_GUARD_DBG "[GUARD_DBG]"
#define CONOPS_SM_TEST_COND "[TEST_COND]"
#define CONOPS_SM_LOGIC_COND "[LOGICAL_FLAG]"

#define CONOPS_SM_STT_DBG "[STT_DBG]"

#define CONOPS_AOCS_MODE_CHANGE "[AOCS_DBG]"

#if defined(DEBUG_TRACE_OP_MODES_ENABLED)
#define CONOPS_TRACE_INFO(msg, ...)       ES_TRACE_INFO(msg OPT_VA_ARGS(__VA_ARGS__))
#define CONOPS_TRACE_DBG(msg, ...)        ES_TRACE_DEBUG(msg OPT_VA_ARGS(__VA_ARGS__))
#else
#define CONOPS_TRACE_INFO(msg, ...)
#define CONOPS_TRACE_DBG(msg, ...)
#endif

// Hook the SM instance here
#define CONOPS_SM_INSTANCE				(conops_sm_instance)

#define CONOPS_TRIGGER_HSM(id) 			(HSM_TriggerEvent_raw(CONOPS_SM_INSTANCE, id))
#define CONOPS_GET_HSM_ACTIVE_STATE()	(HSM_GetActiveState(CONOPS_SM_INSTANCE))

/** @brief Raw/Pitch/Yaw in [mdeg] threshold (positive/negative)
 *
 * Used in the sun-tracking sequence logic
 *
 */
#define CONOPS_RPY_MDEG_THRESH			(10000)

/** @brief Y Wheel RPM threshold
 *
 * Used in the sun-tracking sequence logic
 *
 */
#define CONOPS_Y_WHEEL_RPM_THRESH		(1000)


/** @brief Single axis angular velocity safety threshold allowing the activation of 3-Axis control modes
 *
 * The value defines the following range [-39, +39] mrad/s. If the estimators indicate that the angular velocity
 * for each axis is within this range, then the activation of a 3-Axis (or Y-Momentum) mode is safe.
 *
 * Note that this value depends on the used reaction wheel, the current value is indicative for medium wheels.
 *
 */
#define CONOPS_3AXIS_CONTROL_ANG_VEL_SAFETY_THRESH		((int32_t)39)

/** @brief Y-Thomson mode upper angular velocity threshold
 *
 */
#define CONOPS_ADCS_Y_THOMSON_POS_THRESH_MRAD_S  ((int16_t)0x0011)      /* ~ 1 deg/s, or 17 mRad/s */

/** @brief Y-Thomson mode lower angular velocity threshold
 *
 */
#define CONOPS_ADCS_Y_THOMSON_NEG_THRESH_MRAD_S  ((int16_t)0xFFEF)     /* ~ -1 deg/s, or -17 mRad/s */

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

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/



#endif /* CONOPS_CFG_CONOPS_CFG_H_ */
/* ******************************************************************************************* */
