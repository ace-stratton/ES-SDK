#ifndef CUBEOBC_CONFIG_H_
#define CUBEOBC_CONFIG_H_

#include "if_sys_mod.h"

/** @brief Configuration interface for the system instancer */
extern if_sys_mod_t cube_adcs_g2_module_configuration;


/** @brief Configuration interface init implementation for the system instancer
 *
 *  @param[in] level the level of initialisation
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_g2_init(sys_init_level_id_t level);

/** @brief Configuration interface run implementation for the system instancer
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_g2_run(void);

/** @brief Configuration interface stop implementation for the system instancer
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_g2_stop(void);

/** @brief Configuration interface deinit implementation for the system instancer
 *
 *  @param[in] level the level of initialisation
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_g2_deinit(sys_init_level_id_t level);

#endif /* CUBEOBC_CONFIG_H_ */
