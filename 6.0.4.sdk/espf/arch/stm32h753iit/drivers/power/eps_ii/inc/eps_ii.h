/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef EPS_II_H_
#define EPS_II_H_
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup eps_ii EPS II Driver
 * @{
 *
 * Interact with the Endurosat [EPS II
 * module](https://endurosat.com/cubesat-store/cubesat-power-modules/eps-power-module-ii/).
 * This module is connected to the OBC using the RS-485 bus and the ESPS I protocol.
 *
 * ## Usage
 *
 * ### Channel control
 *
 * The OBC can send requests to the PDM (Power Distribution Module) by using `eps_ii_set_channel_output`
 *  or  `eps_ii_get_channel_output`.
 *
 * ```C
 * #include "eps_ii.h"
 *
 * void my_func_calling_eps_ii(){
 *
 *     eps_ii_ctrl_ch_t channel = EPS_II_CTRL_5V_Ch2_Master;
 *     bool state = true;
 *
 *     bool b_res = eps_ii_set_channel_output(channel, state);
 *
 *     if (b_res){
 *         // Set request was sent successfully
 *         b_res = eps_ii_get_channel_output()
 *     }
 *     if(b_res){
 *         // Get request was sent successfully
 *         // Do something
 *     }
 * }
 * ```
 * Whenever a response arrives, the callback from the ESPS FP is called (FP_EPSII_PDM_1ClientApp.c).
 *
 * These two functions are sending an ESPS I requests to the PDM EPS II module. You would need to
 * take care of processing the response in your application.
 *
 * ## EPS Control integration
 * The enumeration type `eps_ii_ctrl_ch_t` holds all the controllable values of the EPS II module.
 *  This type is used by the @ref eps_ctrl service to set and get the status from the EPS II instead of
 *  calling separately the GPIOs and the Power Outputs.
 *
 * @note The @ref eps_ctrl service takes care of setting the channels of any EPS modules,
 *  the drivers should not be called directly.
 *
 * @file     eps_ii.h
 *
 * @brief    Driver for EnduroSat Electric Power System II (EPS II)
 *
 * @}
 * @}
 *
 */
/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include <if_sys_mod.h>
#include <sys_instancer_ct.h>

#include "fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolTypes.h"
#include "fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolTypes.h"

/** Enum type to group all the controllable outputs of the EPS II */
typedef enum {
    // GPIOs (EPSII_PDM_1_SGGPIO_OnOff_mask_t)
    EPS_II_CTRL_DigOUT1,
    EPS_II_CTRL_DigOUT2,
    EPS_II_CTRL_DigOUT3,
    EPS_II_CTRL_DigOUT4,
    EPS_II_CTRL_DigOUT5,
    EPS_II_CTRL_DigOUT6,
    EPS_II_CTRL_DigOUT7,
    EPS_II_CTRL_DigOUT8,
    EPS_II_CTRL_GPIO_MAX,
    // Power Outputs (EPSII_PDM_1_SGPO_ON_Off_Bitmask_t)
    EPS_II_CTRL_BBUS_RAWOutput,
    EPS_II_CTRL_12V_Master,
    EPS_II_CTRL_12V_SP1_3,
    EPS_II_CTRL_12V_SP1_4,
    EPS_II_CTRL_12V_SP1_5,
    EPS_II_CTRL_5V_Ch1_Master,
    EPS_II_CTRL_5V_Ch1_SP2_3,
    EPS_II_CTRL_5V_Ch1_SP2_4,
    EPS_II_CTRL_5V_Ch2_Master,
    EPS_II_CTRL_5V_Ch2_SP1_6,
    EPS_II_CTRL_5V_Ch2_SP1_7,
    EPS_II_CTRL_3V3_Ch1_Master,
    EPS_II_CTRL_3V3_Ch1_SP2_5,
    EPS_II_CTRL_3V3_Ch1_SP2_6,
    EPS_II_CTRL_3V3_Ch1_SP2_7,
    EPS_II_CTRL_3V3_Ch2_Master,
    EPS_II_CTRL_MAX
} eps_ii_ctrl_ch_t;

/** Configuration interface for the system instancer */
extern if_sys_mod_t eps_ii_module_configuration;

/*
 * EXTERNAL ROUTINES DECLARATIONS
 ********************************/

/** @brief system instancer init interface function
*  @param level initialization level to initialize
*
*  @retval STATUS_FAILED: initialization went wrong
*  @retval STATUS_OK: everything is initialized
*  @retval STATUS_NOT_SUPPORTED: there is no such level of initialization for the module
*/
mod_op_status_id_t eps_ii_init(sys_init_level_id_t level);

/** @brief system instancer run interface function
*
*  @retval STATUS_FAILED: failed to start the module
*  @retval STATUS_OK: the module is running
*  @retval STATUS_NOT_SUPPORTED: not implemented for this module
*/
mod_op_status_id_t eps_ii_run(void);

/** @brief system instancer stop interface function
*
*  @retval STATUS_FAILED: failed to stop the module
*  @retval STATUS_OK: module dependencies stopped
*  @retval STATUS_NOT_SUPPORTED: not implemented for this module
*/
mod_op_status_id_t eps_ii_stop(void);

/** @brief system instancer deinit interface function
*  @param level initialization level to initialize
*
*  @retval STATUS_FAILED: deinitialization went wrong
*  @retval STATUS_OK: everything is deinitialized
*  @retval STATUS_NOT_SUPPORTED: there is no such level of initialization for the module
*/
mod_op_status_id_t eps_ii_deinit(sys_init_level_id_t level);

/** @brief Write in to the datacache the information from the battery pack
 *  @param battery_info information obtained from the Battery Pack response
 *
 *  @warning The values for the battery current, voltage and temperature are truncated
 *              from int64 to int32
 */
void eps_ii_info_to_datacache(const EPSII_BP_1GetBatteryInfoResponseData_t* battery_info);

/** @brief Send a request to set the channel outputs of the EPS II
 *  @param channel_mask channels to be set
 *  @param state new state of the channel
 *
 *  @retval false: failed to send the request
 *  @retval true: the request has been sent successfully
 */
bool eps_ii_set_channel_output(eps_ii_ctrl_ch_t channel, bool state);

/** @brief Request to get the status of a channel output
 *
 *  @retval false: failed to send the request
 *  @retval true: the request has been sent successfully
 */
bool eps_ii_get_channel_output(eps_ii_ctrl_ch_t channel);

/** @brief Return the value of the last request sent to the pdm
 *
 *  @return value of the sequence id
 */
uint16_t eps_ii_last_pdm_request_seq_id(void);

/** @brief Convert control channel type to SGPO value mask
 * @param ch control type value to be converted
 *
 *  @return value of the sequence id
 */
EPSII_PDM_1_SGGPIO_OnOff_mask_t eps_ii_channel_to_gpio(eps_ii_ctrl_ch_t ch);

/** @brief Convert control channel type to SGPO value mask
 * @param ch control type value to be converted
 *
 *  @return value of the sequence id
 */
EPSII_PDM_1_SGPO_ON_Off_Bitmask_t eps_ii_channel_to_sgpo(eps_ii_ctrl_ch_t ch);

#endif    /* EPS_II_H_ */
