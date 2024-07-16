#ifndef _EPS_M_H_
#define _EPS_M_H_
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup eps_m EPS M Driver
 * @{
 *
 * This module is controlling a third party EPS. It contains an interface with the EPS Control
 * service that the third party EPS can use and it also contains the drivers to control the module.
 *
 * ### Usage
 * Telemetry:
 *
 * The telemetry is gathered from the EPS depending on the configuration:
 * - PDU (Power Distribution Unit) returns information for the `DATA_CACHE_EPS_0_t,
 *      `DATA_CACHE_EPS_2_t`
 * - PBU (Power Battery Unit) returns additional information for `DATA_CACHE_EPS_0_t`,
 *      `DATA_CACHE_EPS_1_t`, `DATA_CACHE_EPS_3_t`
 * - PCU (Power Conditioning Unit) returns additional information for `DATA_CACHE_EPS_4_t`
 *  and stored in the datacache structure `DATA_CACHE_EPS_0_t`.
 *
 *  The compile definition `ENABLE_PBU_AND_PCU_COMMUNICATION` should be active to communicate
 *   with the PBU and the PCU.
 *
 * The task `eps_m_task` takes care of updating this information periodically.
 *
 * Channel control:
 *
 * The OBC can send requests to the EPS M by using `eps_m_set_channel_output`
 *  or  `eps_m_get_channel_outputs`.
 *
 * ```C
 *
 * #include "eps_m.h"
 *
 * void my_func_calling_eps_m(){
 *
 *     uint16_t channel = 3;
 *     bool state = true;
 *
 *     bool b_res = eps_m_set_channel_output(channel, state);
 *
 *     if (b_res){
 *         // Set request was sent successfully
 *         b_res = eps_m_get_channel_outputs()
 *     }
 *     if(b_res){
 *         // Get request was sent successfully
 *         // Do something
 *     }
 * }
 *
 * ```
 *
 * @note The `eps_ctrl` service takes care of setting the channels of any EPS modules,
 *  the drivers should not be called directly.
 *
 * @file     eps_m.h
 *
 * @brief    Interface for a third party EPS module drivers
 *
 * @}
 * @}
 *
 */

#include <if_sys_mod.h>
#include <sys_instancer_ct.h>

/** Configuration interface for the system instancer */
extern if_sys_mod_t eps_m_module_configuration;

/** @brief system instancer init interface function
*  @param level initialization level to initialize
*
*  @retval STATUS_FAILED: initialization went wrong
*  @retval STATUS_OK: everything is initialized
*  @retval STATUS_NOT_SUPPORTED: there is no such level of initialization for the module
*/
mod_op_status_id_t eps_m_init(sys_init_level_id_t level);

/** @brief system instancer run interface function
*
*  @retval STATUS_FAILED: failed to start the module
*  @retval STATUS_OK: the module is running
*  @retval STATUS_NOT_SUPPORTED: not implemented for this module
*/
mod_op_status_id_t eps_m_run(void);

/** @brief system instancer stop interface function
*
*  @retval STATUS_FAILED: failed to stop the module
*  @retval STATUS_OK: module dependencies stopped
*  @retval STATUS_NOT_SUPPORTED: not implemented for this module
*/
mod_op_status_id_t eps_m_stop(void);

/** @brief system instancer deinit interface function
*  @param level initialization level to initialize
*
*  @retval STATUS_FAILED: deinitialization went wrong
*  @retval STATUS_OK: everything is deinitialized
*  @retval STATUS_NOT_SUPPORTED: there is no such level of initialization for the module
*/
mod_op_status_id_t eps_m_deinit(sys_init_level_id_t level);

/** @brief Send a request to set the power outputs of the third party EPS
 *  @param channel to be set
 *  @param new state of the channel
 *
 *  @retval false: failed to send the request
 *  @retval true: the request has been sent successfully
 */
bool eps_m_set_channel_output(uint8_t channel, bool state);

/** @brief Request to get the power outputs status from a third party EPS
 *
 *  @retval false: failed to send the request
 *  @retval true: the request has been sent successfully
 */
bool eps_m_get_channel_outputs(void);


#endif /* _EPS_M_H_ */
