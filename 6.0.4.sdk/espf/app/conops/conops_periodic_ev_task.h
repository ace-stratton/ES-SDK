/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CONOPS_PERIODIC_EV_TASK_H_
#define CONOPS_PERIODIC_EV_TASK_H_

/**
 * @addtogroup app_conops
 * @{
 *
 * @file conops_periodic_ev_task.h
 * @brief ConOps periodic events task header
 *
 * @}
 *
 */

#include "cmsis_os2.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

#define CONOPS_PER_EV_TASK_PERIOD (10000U)

/**
 * @brief Initialises the ConOps periodic event task
 */
void conops_p_ev_init(void);

#endif    /* CONOPS_PERIODIC_EV_TASK_H_ */
/* ******************************************************************************************* */
