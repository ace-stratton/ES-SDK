/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_CFG_H_
#define CUBEADCS_CFG_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_cfg.h
 * @brief    Configurations specific to the CubeADCS.
 *
 * @}
 */

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "trace.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

#define CUBEADCS_HEAD 		"[CUBEADCS]"
#define CUBEADCS_FTRANS_HEAD CUBEADCS##"[FTRANSF]"

#if defined(DEBUG_TRACE_CUBEADCS_ENABLED)
#define CUBEADCS_TRACE_INFO(msg, ...)        ES_TRACE_INFO(msg OPT_VA_ARGS(__VA_ARGS__))
#define CUBEADCS_TRACE_DBG(msg, ...)         ES_TRACE_DEBUG(msg OPT_VA_ARGS(__VA_ARGS__))
#else
#define CUBEADCS_TRACE_INFO(msg, ...)
#define CUBEADCS_TRACE_DBG(msg, ...)
#endif

/** @brief Y-Thomson mode upper angular velocity threshold
 *
 */
#define CUBEADCS_Y_THOMSON_POS_THRESH_MRAD_S  ((int16_t)0x0011)      /* ~ 1 deg/s, or 17 mRad/s */

/** @brief Y-Thomson mode lower angular velocity threshold
 *
 */
#define CUBEADCS_Y_THOMSON_NEG_THRESH_MRAD_S  ((int16_t)0xFFEF)     /* ~ -1 deg/s, or -17 mRad/s */

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


#endif	/* CUBEADCS_CFG_H_ */
/* ******************************************************************************************* */
