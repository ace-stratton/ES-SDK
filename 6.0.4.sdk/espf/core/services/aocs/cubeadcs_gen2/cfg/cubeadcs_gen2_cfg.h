/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CUBEADCS_GEN2_CFG_H_
#define CUBEADCS_GEN2_CFG_H_

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file cubeadcs_gen2_cfg.h
 * @brief Cubeadcs gen2 configuration file
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
#include "cubeadcs_gen2_sm_user.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

#define CUBEADCS_GEN2_DBG_HEAD "[G2]"

#if defined(DEBUG_TRACE_CUBEADCS_ENABLED)
#define CUBEADCS_GEN2_TRACE_INFO(msg, ...)       ES_TRACE_INFO(msg OPT_VA_ARGS(__VA_ARGS__))
#define CUBEADCS_GEN2_TRACE_DBG(msg, ...)        ES_TRACE_DEBUG(msg OPT_VA_ARGS(__VA_ARGS__))
#else
#define CUBEADCS_GEN2_TRACE_INFO(msg, ...)
#define CUBEADCS_GEN2_TRACE_DBG(msg, ...)
#endif

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



#endif /* CUBEADCS_GEN2_CFG_H_ */
/* ******************************************************************************************* */
