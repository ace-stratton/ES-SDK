/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_ii
 * @{
 *
 * @file     eps_ii.c
 * @brief    Driver for Endurosat Electric Power System II (EPS II)
 *
 * @}
 */

#include "eps_ii.h"
#include "eps_ii_telemetry.h"
#include "eps_ii_config.h"

#include "assertions.h"
#include "cmsis_os.h"
#include "TaskMonitor.h"

#include "fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolClient.h"
#include "fp/EPSII_PDM_1/v1.0/EPSII_PDM_1_client/FP_EPSII_PDM_1ProtocolTypes.h"
#include "fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolClient.h"
#include "fp/EPSII_BP_1/v3.0/EPSII_BP_1_client/FP_EPSII_BP_1ProtocolTypes.h"
#include "fp/data_cache/v0.1/data_cache_server/FP_data_cacheProtocolTypes.h"

/*
 * ESPS I LOCAL DEFINITIONS
 **************************/
/// ESPS I - FP request Context
static ReqContext_t fp_pdm_context = {
    .nInterfaceNumber = ESSASNI_SYS_PRI,
    .seqId = 0, // Value to be updated by the ESPS Stack once the request is sent
    .netType = ESSASNETT_INTERNAL
};

/*
 * EPS CONTROL DECLARATIONS
 *************************/
static bool eps_ii_set_gpio(EPSII_PDM_1_SGGPIO_Bitmask_t channel_mask, bool state);
static bool eps_ii_get_gpio(void);
static bool eps_ii_set_sgpo(EPSII_PDM_1_SGPO_Bitmask_t channel_mask, bool state);
static bool eps_ii_get_sgpo(void);

/*
 * SYS INSTANCER DEFINITIONS
 ***************************/
static void eps_ii_init_memory(void);
static void eps_ii_init_hw(void);
static void eps_ii_init_os(void);

// Configuration interface for the system instancer
if_sys_mod_t eps_ii_module_configuration = {
    .init = eps_ii_init,
    .run = eps_ii_run,
    .stop = eps_ii_stop,
    .deinit = eps_ii_deinit,
};

/*
 * SYS INSTANCER FUNCTIONS
 *************************/
// System module interface functions
mod_op_status_id_t eps_ii_init(sys_init_level_id_t level){
    mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

    // Eventually, to split the initialisation into the different levels
    switch (level){
    case INIT_MEM:
        eps_ii_init_memory();
        ret = STATUS_OK;
        break;
    case INIT_HW:
        eps_ii_init_hw();
        ret = STATUS_OK;
        break;
    case INIT_OS:
        eps_ii_init_os();
        ret = STATUS_OK;
        break;
    default:
        ret = STATUS_NOT_SUPPORTED;
        break;
    }

    return ret;
}
mod_op_status_id_t eps_ii_run(void){
    // To be used by the system instancer
    return STATUS_NOT_SUPPORTED;
}
mod_op_status_id_t eps_ii_stop(void){
    // To be used by the system instancer
    return STATUS_NOT_SUPPORTED;
}
mod_op_status_id_t eps_ii_deinit(sys_init_level_id_t level){
    if (INIT_OS == level){
        task_mon_set_task_policy(TASK_EPS_II, TASK_MON_POLICY_DONT_CARE);
    }
    return STATUS_OK;
}

/*
********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
********************************************************************************************
*/

/*
 * EPS CONTROL
 *************/
bool eps_ii_set_channel_output(eps_ii_ctrl_ch_t channel, bool state){
    bool res = false;

    // Set a GPIO
    if (EPS_II_CTRL_GPIO_MAX > channel){
        // call set gpio
        res = eps_ii_set_gpio(eps_ii_channel_to_gpio(channel), state);
    }
    // Set a Power Output
    else if (EPS_II_CTRL_MAX > channel){
        // call set power output
        res = eps_ii_set_sgpo(eps_ii_channel_to_sgpo(channel), state);
    }
    //
    else{
        CRIT_ASSERT(false); // Catch this error while in debug
        res = false;
    }

    return res;
}
bool eps_ii_get_channel_output(eps_ii_ctrl_ch_t channel){
    (void) channel; // The EPS II request does not need the channel
    bool res = false;

    // Set a GPIO
    if (EPS_II_CTRL_GPIO_MAX > channel){
        // call get gpio
        res = eps_ii_get_gpio();
    }
    // Set a Power Output
    else if (EPS_II_CTRL_MAX > channel){
        // call get sgpo
        res = eps_ii_get_sgpo();
    }
    else{
        CRIT_ASSERT(false); // Catch this error while in debug
        res = false;
    }

    return res;
}

// Return the last FP request seqId to be able to match it with the ESPS response
uint16_t eps_ii_last_pdm_request_seq_id(void){
    return fp_pdm_context.seqId;
}

// Convert control types into EPS II actual types
EPSII_PDM_1_SGGPIO_OnOff_mask_t eps_ii_channel_to_gpio(eps_ii_ctrl_ch_t ch){
    switch (ch){
    case EPS_II_CTRL_DigOUT1: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT1;
    case EPS_II_CTRL_DigOUT2: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT2;
    case EPS_II_CTRL_DigOUT3: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT3;
    case EPS_II_CTRL_DigOUT4: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT4;
    case EPS_II_CTRL_DigOUT5: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT5;
    case EPS_II_CTRL_DigOUT6: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT6;
    case EPS_II_CTRL_DigOUT7: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT7;
    case EPS_II_CTRL_DigOUT8: return EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT8;
    default:
        CRIT_ASSERT(false);
        return EPSII_PDM_1_SGGPIO_ONOFF_MASK_MAX_CNT;
    }
}
EPSII_PDM_1_SGPO_ON_Off_Bitmask_t eps_ii_channel_to_sgpo(eps_ii_ctrl_ch_t ch){
    switch (ch){
    case EPS_II_CTRL_BBUS_RAWOutput: return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_BBUS_RAWOutputEnable;
    case EPS_II_CTRL_12V_Master:     return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_MasterEnable;
    case EPS_II_CTRL_12V_SP1_3:      return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_SP1_3_Enable;
    case EPS_II_CTRL_12V_SP1_4:      return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_SP1_4_Enable;
    case EPS_II_CTRL_12V_SP1_5:      return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_SP1_5_Enable;
    case EPS_II_CTRL_5V_Ch1_Master:  return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch1_MasterEnable;
    case EPS_II_CTRL_5V_Ch1_SP2_3:   return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch1_SP2_3_Enable;
    case EPS_II_CTRL_5V_Ch1_SP2_4:   return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch1_SP2_4_Enable;
    case EPS_II_CTRL_5V_Ch2_Master:  return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch2_MasterEnable;
    case EPS_II_CTRL_5V_Ch2_SP1_6:   return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch2_SP1_6_Enable;
    case EPS_II_CTRL_5V_Ch2_SP1_7:   return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch2_SP1_7_Enable;
    case EPS_II_CTRL_3V3_Ch1_Master: return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_MasterEnable;
    case EPS_II_CTRL_3V3_Ch1_SP2_5:  return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_SP2_5_Enable;
    case EPS_II_CTRL_3V3_Ch1_SP2_6:  return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_SP2_6_Enable;
    case EPS_II_CTRL_3V3_Ch1_SP2_7:  return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_SP2_7_Enable;
    case EPS_II_CTRL_3V3_Ch2_Master: return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch2_MasterEnable;
    default:
        CRIT_ASSERT(false);
        return EPSII_PDM_1_SGPO_ON_OFF_BITMASK_MAX_CNT;
    }
}

/*
********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
********************************************************************************************
*/

/** @brief Memory initialisation for the EPS II module
 */
static void eps_ii_init_memory(void)
{
    /* SYS INIT MEMORY LEVEL */
    // Read the MAC address from the NVM
	fp_pdm_context.nAddr = eps_ii_cfg_get_pdm_mac_address();
	eps_ii_tlm_init_memory();
}
/** @brief HW initialisation for the EPS II module
 */
static void eps_ii_init_hw(void){
    /* SYS INIT HW LEVEL */
    // Also RS-485 bus is initialized separately in the espsi_drv module
    // Nothing to initialize
}
/** @brief OS initialisation for the EPS II module
 */
static void eps_ii_init_os(void){

    // Init telemetry task
    eps_ii_tlm_init_os();
}

// EPS II channel control
// Request EPS II module to switch on or off a channel
/** @brief Request EPS II module to set a GPIO channel on or off
 * @var
 */
static bool eps_ii_set_gpio(EPSII_PDM_1_SGGPIO_Bitmask_t channel_mask, bool state){

    // Channel mask should be a valid value from the enum type
    if (EPSII_PDM_1_SGGPIO_BITMASK_MAX_CNT <= channel_mask)
    {
        CRIT_ASSERT(false); // Catch this error while in debug
        return false;
    }

    // Assign the value mask the same value as the channel mask or 0
    EPSII_PDM_1_SGGPIO_OnOff_mask_t values_mask = state ? channel_mask : (uint8_t) 0U;

    // Send ESPS request
    ESSATMAC_ErrCodes resp = EPSII_PDM_1_SetPC104GPIOReq(&fp_pdm_context, channel_mask, values_mask);
    return (bool)(ESSATMAC_EC_OK == resp);

}

// Request EPS II to get the power output values
static bool eps_ii_get_gpio(void){
    // Send the ESPS request to the EPS II module
    ESSATMAC_ErrCodes resp = EPSII_PDM_1_GetPC104GPIOReq(&fp_pdm_context);
    return (bool)(ESSATMAC_EC_OK == resp);
}

// Request EPS II module to switch on or off a power channel
static bool eps_ii_set_sgpo(EPSII_PDM_1_SGPO_Bitmask_t channel_mask, bool state){

    // Channel mask should be a valid value from the enum type
    if (EPSII_PDM_1_SGPO_ON_OFF_BITMASK_MAX_CNT <= channel_mask)
    {
        CRIT_ASSERT(false); // Catch this error while in debug
        return false;
    }

    // Assign the value mask the same value as the channel mask or 0
    EPSII_PDM_1_SGPO_ON_Off_Bitmask_t values_mask = state ? channel_mask : (uint8_t) 0U;

    // Send ESPS request
    ESSATMAC_ErrCodes resp = EPSII_PDM_1_SetPowerOutputsReq(&fp_pdm_context, channel_mask, values_mask);
    return (bool)(ESSATMAC_EC_OK == resp);
}

// Request EPS II to get the power output values
static bool eps_ii_get_sgpo(void){
    // Send the ESPS request to the EPS II module
    ESSATMAC_ErrCodes resp = EPSII_PDM_1_GetPowerOutputsReq(&fp_pdm_context);
    return (bool)(ESSATMAC_EC_OK == resp);
}
