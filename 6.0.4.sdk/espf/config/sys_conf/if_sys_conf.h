/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPF_CONFIG_SYS_CONF_IF_SYS_CONF_H_
#define ESPF_CONFIG_SYS_CONF_IF_SYS_CONF_H_

/**
 * @addtogroup sys_instancer
 * @{
 *
 * @file    if_sys_conf.h
 * @brief   Types and declarations of the runtime configuration checks
 *
 * @}
 *
 */

#include "es_cdef.h"

/** Signature precedes the configuration information */
extern const char CONFIG_SIGNATURE[5];

/** List of modules for the Standard Platform */
typedef enum
{
    SYS_MODULE_ID_EPS_I,
    SYS_MODULE_ID_EPS_II,
    SYS_MODULE_ID_EPS_M,
    SYS_MODULE_ID_ES_ADCS,
    SYS_MODULE_ID_CUBE_ADCS,
    SYS_MODULE_ID_GNSS,
    SYS_MODULE_ID_SX_BAND,
    SYS_MODULE_ID_SP,
    SYS_MODULE_ID_CUBE_ADCS_GEN2,
    SYS_MODULE_ID_MAX
} sys_module_id_t;

/** List of bool corresponding to the different modules, determining if the are active or inactive */
typedef struct
{
    safe_bool_t mod_activation_state[SYS_MODULE_ID_MAX];      // activation states for the individual modules
} instance_cfg_payload_t;

/** Configuration binary structure */
typedef struct
{
    const char sig[5];              /**> Configuration ASCII signature set to "MCFG\0" */
    uint16_t version;               /**> MSB: major, LSB: minor version of this structure; always kept as first field */
    uint16_t size;                  /**> Size of the following bytes excluding crc field */
    instance_cfg_payload_t data;    /**> Configuration payload data */
    uint32_t crc;                   /**> CRC32-ISO3309 */
} PACKED instance_cfg_t;

/*
 * PUBLIC INTERFACE
 ******************/

/** @brief Read and verify the system configuration binary
*/
void sys_conf_init(void);

/** @brief Determine if a module is active in the binary configuration
 *  @param   Module id @see sys_module_id_t
 *
 *  @return  true if it is active, false if it is not
 */
bool sys_conf_is_module_active(sys_module_id_t id);

/** @brief check that the configuration binary is valid (CRC, module compatibility, version...)
 *
 *  @return  true if the configuration passed all the checks
 */
bool sys_conf_is_valid(void);

#endif /* ESPF_CONFIG_SYS_CONF_IF_SYS_CONF_H_ */
