/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPF_LIB_SYS_INSTANCER_IF_SYS_INSTANCER_H_
#define ESPF_LIB_SYS_INSTANCER_IF_SYS_INSTANCER_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup sys_instancer System Instancer
 * @{
 * The system instancer provides an interface to control several modules at the same time.
 * It allows to initialize different levels (peripherals, memory or OS) of the modules.
 * This way, depending on the application situation, the system can start or stop all
 * the peripherals, memory or OS dependencies in the modules as required.
 *
 * ### Sys Mod interface
 *
 * These functions are defined for each of the modules:
 *
 * - `init(level)`: Initialize a specific level of the module
 * - `run()`: Start any threads or OS dependencies (and start TaskMonitor monitoring)
 * - `stop()`: Pause any thread execution (and stop TaskMonitor from monitoring)
 * - `deinit(level)`: Deinitialize a specific level
 *
 * @note Not all the modules have all the interface functions defined but at least `init()` and `deinit()`
 *       are supported.
 *
 * All the modules will be initialized at the same time when using the sys_instancer:
 * ```C
 * my_user_function(){
 *
 *     // something critical just happened...
 *     // Deinitialize all the modules
 *     if(! sys_inst_deinit(INIT_MEM))
 *         Error_Handler();
 *     if(! sys_inst_deinit(INIT_HW))
 *         Error_Handler();
 *     if (! sys_inst_deinit(INIT_OS))
 *         Error_Handler();
 *
 *     // If we recovered, we can now initiailized everything
 *
 *     // MEMORY Initialization
 *     if(! sys_inst_init(INIT_MEM))
 *         Error_Handler();
 *
 *     // Initialize the gnss configuration if the GNSS module is active
 *     if(sys_conf_is_module_active(SYS_MODULE_ID_GNSS))
 *         gnss_config_init();
 *
 *     // HW (peripherals) Initialization
 *     if(! sys_inst_init(INIT_HW))
 *         Error_Handler();
 *
 *     // OS Initialization
 *     if (! sys_inst_init(INIT_OS))
 *         Error_Handler();
 *
 *     // Selectively initialize services depending on the active modules
 *     if (sys_conf_is_module_active(SYS_MODULE_ID_EPS_I)
 *      || sys_conf_is_module_active(SYS_MODULE_ID_EPS_II)
 *      || sys_conf_is_module_active(SYS_MODULE_ID_EPS_M))
 *     {
 *         eps_ctrl_init();
 *         task_mon_set_task_policy(TASK_EPS_CTRL, TASK_MON_POLICY_MONITOR);
 *     }
 *     if(sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
 *     {
 *         ADCS_TLM_TaskInit();
 *         task_mon_set_task_policy(TASK_ADCS_TLM, TASK_MON_POLICY_MONITOR);
 *     }
 * }
 * ```
 *
 * @note
 *     The function sys_conf_is_module_active() returns true if the module is active.
 *     This way you can implement module dependent code without recompiling the OBC.
 *
 * ### es-sys-config
 * __es-sys-config__ is a python tool that will help to flash the system configuration in the OBC
 *  flash. It is located in `other/scripts/sys_config_generation`. More information about the usage
 *  can be found there.
 *
 * For more information about the Runtime Configuration, refer to the OBC SDK documentation.
 *
 * @file    if_sys_instancer.h
 * @brief   sys instanscer public interface
 *
 * @}
 * @}
 *
 */

#include "if_sys_mod.h"
#include "sys_instancer_ct.h"

#include <es_cdef.h>

/** List of module interfaces */
extern if_sys_mod_t * g_p_modules_interface_list[SYS_MODULE_ID_MAX];

/** @brief Initialise the selected system level for all the active modules
 *  @param   level: initialization level
 *
 *  @return  true if every module initialized properly
 */
bool sys_inst_init(sys_init_level_id_t level);

/** @brief Deinitialise the selected system level
 *  @param   level: initialization level
 *
 *  @return  true if every module is deinitialized properly
 */
bool sys_inst_deinit(sys_init_level_id_t level);

/** @brief Start the modules that are active in the configuration
 *
 *  @return  true if every module is running
 */
bool sys_inst_run_instance();

#endif /* ESPF_LIB_SYS_INSTANCER_IF_SYS_INSTANCER_H_ */
