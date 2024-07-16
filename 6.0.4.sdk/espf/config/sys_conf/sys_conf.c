/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup sys_instancer
 * @{
 *
 * @file    sys_conf.c
 * @brief   Runtime configuration verification
 *
 * @}
 *
 */

#include <string.h>

#include "if_sys_conf.h"

#include <main.h>
#include <MACCRC32_Classic_Impl.h>

/*
 * Static variables and definitions
 */

/** Seed for the CRC calculation */
#define CRC32_SEED ((uint32_t) 0xFFFFFFFF)

/** Memory address from where to read the configuration (defined in the linker script) */
extern int __MODULE_CONFIG_START;

/** Configuration structure read from memory */
const instance_cfg_t * const p_system_configuration = (const instance_cfg_t * const) (void*)&__MODULE_CONFIG_START;

/** Configuration ASCII signature */
const char CONFIG_SIGNATURE[5] = "MCFG";

static bool sys_conf_error_flag = false;

/** Verify that the configuration is compatible with the HW peripherals */
static bool module_compatibility_check(void);
static bool eps_compatibility_check(const safe_bool_t * p_modules);
static bool adcs_compatibility_check(const safe_bool_t * p_modules);

/** Set the configuration error flag */
static inline void set_error_flag(void);


/*
 * PUBLIC FUNCTIONS
 ******************/
void sys_conf_init(void) {

    // Calculate the CRC of the configuration data
    uint32_t calculated_crc32 = MACCRC32_Calc32((unsigned char*)&p_system_configuration->data,
                                                (uint32_t)p_system_configuration->size,
                                                CRC32_SEED);
    // Exit if the CRC doesn't match
    if (calculated_crc32 != p_system_configuration->crc)
    {
        set_error_flag();
        return;
    }

    // Verify the signature byte by byte
    for(uint32_t i = 0; i < CDEF_ELEMENT_COUNT(CONFIG_SIGNATURE); i++)
    {
        if (p_system_configuration->sig[i] != CONFIG_SIGNATURE[i])
        {
            set_error_flag();
            return;
        }
    }

    // Possible version checks
    const uint16_t minimum_version = 0x0002;
    if (p_system_configuration->version < minimum_version)
    {
        set_error_flag();
        return;
    }

    // Perform the module compatibility checks
    if(!module_compatibility_check())
    {
        set_error_flag();
    }

    return;
}

bool sys_conf_is_module_active(sys_module_id_t id) {
    bool b_is_active = false;
    // If there is no error validating the configuration and the module flag is set in the configuration
    if (sys_conf_is_valid() && IS_TRUE(p_system_configuration->data.mod_activation_state[id]))
    {
        b_is_active = true;
    }

    return b_is_active;

}

bool sys_conf_is_valid(void){
    // Conf is valid if there is no error flag
    return !sys_conf_error_flag;
}

/*
 * STATIC FUNCTIONS
 ******************/

// There should be a function for every kind of requirement or the if/else nesting will get too complex to follow
static bool module_compatibility_check(void) {
    // IMPORTANT: All checks should be done with IS_TRUE so in case of a single event upset (SEU)
    //      we don't assume a module is connected.
    //  i.e. if a value is set to safe true (0xFF), if a SEU changed bit, would return false
    //      on a IS_TRUE check. The safe assumption is to fall to false in case of doubt
    bool b_compatible = true;

    // Verify that the configuration is compatible
    const safe_bool_t* p_modules = p_system_configuration->data.mod_activation_state;

    //If the ES_ADCS is active, the EPS_I must be connected too.
    if(    b_compatible
        && IS_TRUE(p_system_configuration->data.mod_activation_state[SYS_MODULE_ID_ES_ADCS])
        && (!IS_TRUE(p_system_configuration->data.mod_activation_state[SYS_MODULE_ID_EPS_I])))
    {
            b_compatible = false;
    }
    // Verify the EPS modules compatibility
    if(b_compatible)
    {
        b_compatible = eps_compatibility_check(p_modules);
    }

    // Verify the ADCS modules compatibility
    if(b_compatible){
        b_compatible = adcs_compatibility_check(p_modules);
    }

    return b_compatible;
}

// Example of a compatibility check: have one, but only one, type of EPS
static bool eps_compatibility_check(const safe_bool_t* p_modules){
    // IMPORTANT: All checks should be done with IS_TRUE so in case of a single event upset (SEU)
    //      we don't assume a module is connected.
    //  i.e. if a value is set to safe true (0xFF), if a SEU changed bit, would return false
    //      on a IS_TRUE check. The safe assumption is to fall to false in case of doubt

    bool b_compatible = true;

    if (IS_TRUE(p_modules[SYS_MODULE_ID_EPS_I]))
    {
        if ( IS_TRUE(p_modules[SYS_MODULE_ID_EPS_II]) || IS_TRUE(p_modules[SYS_MODULE_ID_EPS_M]) )
        {
            b_compatible = false; // We already have EPS I active
        }
    }
    else // EPS I not active
    {
        if (IS_TRUE(p_modules[SYS_MODULE_ID_EPS_II]))
        {
            if (IS_TRUE(p_modules[SYS_MODULE_ID_EPS_M]))
            {
                b_compatible = false; // EPS II is active already
            }
        }
        else // None EPS I and EPS II are active
        {
            if (IS_TRUE(p_modules[SYS_MODULE_ID_EPS_M]))
            {
                b_compatible = true; // Only third party EPS is active
            }
            else
            {
                b_compatible = false; // No EPS module active
            }
        }
    }

    return b_compatible;
}

static bool adcs_compatibility_check(const safe_bool_t * p_modules){
    // IMPORTANT: All checks should be done with IS_TRUE so in case of a single event upset (SEU)
    //      we don't assume a module is connected.
    //  i.e. if a value is set to safe true (0xFF), if a SEU changed bit, would return false
    //      on a IS_TRUE check. The safe assumption is to fall to false in case of doubt

    bool b_compatible = true;

    if (IS_TRUE(p_modules[SYS_MODULE_ID_ES_ADCS]))
    {
        if (IS_TRUE(p_modules[SYS_MODULE_ID_CUBE_ADCS]) || IS_TRUE(p_modules[SYS_MODULE_ID_CUBE_ADCS_GEN2]))
        {
            b_compatible = false; // ES ADCS is already active
        }
    } else if (IS_TRUE(p_modules[SYS_MODULE_ID_CUBE_ADCS]) && IS_TRUE(p_modules[SYS_MODULE_ID_CUBE_ADCS_GEN2]))
    {
        b_compatible = false; // We cannot have both Gen1 and Gen2 CubeADCS modules active
    }
    else
    {
        // ADCS configuration is consistent
    }

    return b_compatible;
}

static inline void set_error_flag(void){
    sys_conf_error_flag = true;
}
