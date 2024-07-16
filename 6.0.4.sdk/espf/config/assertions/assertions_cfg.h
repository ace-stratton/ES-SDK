#ifndef ASSERTIONS_CFG_H
#define ASSERTIONS_CFG_H

/*
 * Copyright (c) 2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup lib_assertions
 * @{
 *
 * @file    assertions_cfg.h
 * @brief   Assertion library configuration header
 *
 * @}
 *
 */

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL TYPES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/
/**
 * @brief Cause the system to stop at breakpoint. System specific
 */
void assert_cfg_break(void);

/**
 * @brief Causes software reset of the system. System specific
 */
void assert_cfg_crit(void);

#endif /* ASSERTIONS_CFG_H */
