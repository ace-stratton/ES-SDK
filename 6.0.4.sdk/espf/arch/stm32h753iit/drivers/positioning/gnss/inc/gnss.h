/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GNSS_H_
#define GNSS_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 * Provide an interface for the GNSS communication
 *
 * @file gnss.h
 *
 * @brief GNSS driver
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "gnss_types.h"
#include "if_sys_mod.h"
#include "sys_instancer_ct.h"


/** @brief Configuration interface for the system instancer */
extern if_sys_mod_t gnss_module_configuration;


/**
 * @brief Initialises the driver
 *
 * @param[in] level Not used
 *
 * @return @ref mod_op_status_id_t
 */
mod_op_status_id_t gnss_init(sys_init_level_id_t level);

/**
 * @brief De-Initialises the driver
 *
 * @param[in] level Not used
 *
 * @return @ref mod_op_status_id_t
 */
mod_op_status_id_t gnss_deinit(sys_init_level_id_t level);

/**
 * @brief Power on
 *
 * @return @ref mod_op_status_id_t
 */
mod_op_status_id_t gnss_run(void);

/**
 * @brief Power off
 *
 * @return @ref mod_op_status_id_t
 */
mod_op_status_id_t gnss_stop(void);

/**
 * @brief Check if the GNSS is powered on/off
 *
 * @retVal true  Power on
 * @retVal false Power off
 */
bool gnss_is_on(void);

/**
 * @brief
 *
 * @param[in] tim
 *
 * @retVal true  Success
 * @retVal false Failure
 */
bool gnss_is_tm_valid(const gnss_time_t* tim);


#ifdef __cplusplus
}
#endif

#endif /* GNSS_H_ */
