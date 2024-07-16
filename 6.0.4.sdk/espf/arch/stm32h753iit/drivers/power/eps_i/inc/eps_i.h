/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef EPS_I_H
#define EPS_I_H

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup eps_i EPS I Driver
 * @{
 *
 * Interact with the Endurosat [EPS I
 * module](https://endurosat.com/cubesat-store/cubesat-power-modules/eps-power-module/).
 * This module is connected to the OBC using the RS-485 bus and the ESPS I protocol.
 *
 * ### Usage
 * Telemetry:
 *
 * The telemetry is gathered from the EPS I and stored in the datacache structure `DATA_CACHE_EPS_0_t`.
 * The task `eps_i_task` takes care of updating this information periodically.
 *
 * Channel control:
 *
 * The OBC can send requests to the EPS I by using `eps_i_set_channel_output` or
 * `eps_i_get_channel_outputs`:
 * ```C
 * #include "eps_i.h"
 *
 * void my_func_calling_eps_i(){
 *
 *     EPS1_QueryControlsIndex_t channel = EPS1_QUERYCONTROLSINDEX_OUT1;
 *     EPS1_QueryState_t state = EPS1_QUERYSTATE_On;
 *
 *     bool b_res = eps_i_set_channel_output(channel, state);
 *
 *     if (b_res){
 *         // Set request was sent successfully
 *         b_res = eps_i_get_channel_outputs()
 *     }
 *     if(b_res){
 *         // Get request was sent successfully
 *         // Do something
 *     }
 * }
 * ```
 * Whenever a response arrives, the callback from the ESPS FP is called (FP_EPS1ClientApp.c).
 *
 * These two functions are sending an ESPS I requests to the EPS I module. You would need to take
 * care of processing the response in your application.
 *
 * @note The `eps_ctrl` service takes care of setting the channels of any EPS modules,
 * the drivers should not be called directly.
 *
 * @file     eps_i.h
 *
 * @brief    Driver for Endurosat Electric Power System I (EPS I)
 *
 * @}
 * @}
 *
 */

#include <main.h>
#include <if_sys_mod.h>
#include <sys_instancer_ct.h>
#include "fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolTypes.h"


/** Return bits of the getConfigurationInfo command (Output 1 and Output 2) */
typedef enum{
    EPS_I_OUT_1_SWSelfLock,
    EPS_I_OUT_1_VBATTEN   ,
    EPS_I_OUT_1_BCROutEN  ,
    EPS_I_OUT_1_SHD_3_3V  ,
    EPS_I_OUT_1_SHD_5V    ,
    EPS_I_OUT_1_RESERVED  ,
    EPS_I_OUT_1_RESERVED2 ,
    EPS_I_OUT_1_OUT1      ,
    EPS_I_OUT_1_OUT2      ,
    EPS_I_OUT_1_OUT3      ,
    EPS_I_OUT_1_OUT4      ,
    EPS_I_OUT_1_OUT5      ,
    EPS_I_OUT_1_OUT6      ,
    EPS_I_OUT_1_HEATER1   ,
    EPS_I_OUT_1_HEATER2   ,
    EPS_I_OUT_1_HEATER3   ,
    EPS_I_OUT_2_LUP_3V3   ,
    EPS_I_OUT_2_LUP_5V    ,
    EPS_I_OUT_2_SHDChrg   ,
    EPS_I_OUT_2_Chrg_I1   ,
    EPS_I_OUT_2_Chrg_I2   ,
    EPS_I_OUT_2_10KPULLUP ,
    EPS_I_OUT_2_4K7PULLUP ,
    EPS_I_OUT_2_R_TERMIN  ,
    EPS_I_OUT_2_OUT7      ,
    EPS_I_OUT_2_OUT8      ,
    EPS_I_OUT_NUMBER
} eps_config_info_outputs;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/
/** Configuration interface for the system instancer */
extern if_sys_mod_t eps_i_module_configuration;

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/

/** @brief system instancer init interface function
 *  @param level initialization level to initialize
 *
 *  @retval STATUS_FAILED: initialization went wrong
 *  @retval STATUS_OK: everything is initialized
 *  @retval STATUS_NOT_SUPPORTED: there is no such level of initialization for the module
 */
mod_op_status_id_t eps_i_init(sys_init_level_id_t level);

/** @brief system instancer run interface function
 *
 *  @retval STATUS_FAILED: failed to start the module
 *  @retval STATUS_OK: the module is running
 *  @retval STATUS_NOT_SUPPORTED: not implemented for this module
 */
mod_op_status_id_t eps_i_run(void);

/** @brief system instancer stop interface function
 *
 *  @retval STATUS_FAILED: failed to stop the module
 *  @retval STATUS_OK: module dependencies stopped
 *  @retval STATUS_NOT_SUPPORTED: not implemented for this module
 */
mod_op_status_id_t eps_i_stop(void);

/** @brief system instancer deinit interface function
 *  @param level initialization level to initialize
 *
 *  @retval STATUS_FAILED: deinitialization went wrong
 *  @retval STATUS_OK: everything is deinitialized
 *  @retval STATUS_NOT_SUPPORTED: there is no such level of initialization for the module
 */
mod_op_status_id_t eps_i_deinit(sys_init_level_id_t level);

/** @brief Write in to the datacache the information from the battery pack
 *  @param battery_info information obtained from the Battery Pack response
 */
void eps_i_info_to_datacache(const EPS1getBatteryInfoResponseData_t* battery_info);

/** @brief Send a request to set the channel outputs of the EPS I
 *  @param channel_mask channels to be set
 *  @param value new state of the channel
 *
 *  @retval false: wrong channel or failed to set
 *  @retval true: set channel request successfully sent
 */
bool eps_i_set_channel_output(EPS1_QueryControlsIndex_t channel, EPS1_QueryState_t state);

/** @brief Request to get the channel outputs status
 *  @retval false: wrong channel or failed to get
 *  @retval true: request successfully sent
 */
bool eps_i_get_channel_outputs(void);

/** @brief Return the value of the last pdm ESPS request sent
 *
 *  @retval false: wrong channel or failed to set
 *  @retval true: channel successfully set
 */
uint16_t eps_i_get_last_request_seq_id(void);

/** @brief For a given EPS1_QueryControlsIndex_t, return the corresponding index of the bit
 * 			in the bitfield result of a getConfigurationInfo response.
 *
 *  @return flag which is all 0bit except for the position where the channel is
 */
uint32_t eps_i_get_config_from_channel(EPS1_QueryControlsIndex_t channel);

#endif    /* EPS_I_H */
