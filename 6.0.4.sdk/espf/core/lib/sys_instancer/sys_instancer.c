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
 * @file    sys_instancer.c
 * @brief   This file has to define the logic of calling the initialisation (using the if_sys_mod.h)
 *
 * @}
 *
 */

#include "if_sys_instancer.h"
#include "if_sys_mod.h"

#include "if_sys_conf.h"
#include <cmsis_os.h>

/// Initialise the selected system level for all the active modules
bool sys_inst_init(sys_init_level_id_t level) {
    mod_op_status_id_t ret = STATUS_OK;

    // Iterate the g_p_if_sys_mod_list
    for (sys_module_id_t mod=0; mod < SYS_MODULE_ID_MAX; mod++)
    {
        if (sys_conf_is_module_active(mod))
        {
            // Make sure the instancer has a valid instance defined for the module
            if (g_p_modules_interface_list[mod] == NULL)
            {
                ret = STATUS_FAILED;
                break;
            }
            // Call the init method if it is not null
            if (g_p_modules_interface_list[mod]->init)
            {
                ret = g_p_modules_interface_list[mod]->init(level);
                if (ret == STATUS_FAILED)
                {
                    // Stop initialisation sequence
                    break;
                }
            }
        }
    }

    // Return true only if all the operations succeeded
    // NOTE: It is ok if a module doesn't support a level of initialisation
    return (ret != STATUS_FAILED);
}

/// Deinitialise the selected system level for all the modules
bool sys_inst_deinit(sys_init_level_id_t level){
    mod_op_status_id_t ret = STATUS_OK;

    // Iterate the g_pp_if_sys_mod_list
    for (sys_module_id_t mod=0; mod < SYS_MODULE_ID_MAX; mod++)
    {
        // Call the stop method
        if (g_p_modules_interface_list[mod]->stop)
        {
            ret = g_p_modules_interface_list[mod]->stop();
        }
        // Call the deinit method
        if (ret != STATUS_FAILED)
        {
            if (g_p_modules_interface_list[mod]->deinit)
            {
                // Keep the STATUS_FAILED if any module failed
                ret = g_p_modules_interface_list[mod]->deinit(level);
            }
        }
    }

    // Return true only if all the operations succeeded
    // NOTE: It is ok if a module doesn't support a level of deinitialisation
    return (ret != STATUS_FAILED);
}

/// Start the modules that are active in the configuration
bool sys_inst_run_instance(){
    mod_op_status_id_t ret = STATUS_OK;

    // Iterate the g_pp_if_sys_mod_list
    for (sys_module_id_t mod=0; mod < SYS_MODULE_ID_MAX; mod++)
    {
        if (sys_conf_is_module_active(mod))
        {
            // Continue only if everything is ok
            if(ret == STATUS_OK)
            {
                // Call the run method
                if (g_p_modules_interface_list[mod]->run)
                {
                    ret = g_p_modules_interface_list[mod]->run();
                }
            }
            else
            {
                break;
            }
        }
    }
    // Return true only if all the operations succeeded
    return (ret == STATUS_OK);
}
