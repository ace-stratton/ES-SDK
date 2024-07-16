/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup eps_i
 * @{
 *
 * @file     eps_i.c
 * @brief    Driver for Endurosat Electric Power System I (EPS I).
 *
 * @}
 */

#include "eps_i.h"
#include "eps_i_config.h"

#include "assertions.h"
#include "cmsis_os.h"
#include "TaskMonitor.h"
#include "ESSA_Stack_Facade.h"
#include "datacache.h"

#include "fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolClient.h"
#include "fp/EPS1/v0.1/EPS1_client/FP_EPS1ProtocolTypes.h"
#include "fp/data_cache/v0.1/data_cache_server/FP_data_cacheProtocolTypes.h"

/*
 * CONVERSION DATA
 *****************/
/// Values to multiply the raw data obtained from the EPS I to get the real voltage and current
static const float conv_batt_volt_mv = 2.3394775;     // EPS_I_BatInfo.sBatt.u16Volt
static const float conv_batt_curr_ma = 3.0517578;     // EPS_I_BatInfo.sBatt.u16Curr

/*
 * ESPS I LOCAL DEFINITIONS
 **************************/

/// ESPS I - FP request Context
static ReqContext_t fp_context = {
    .nInterfaceNumber = ESSASNI_SYS_PRI,
    .seqId = 0, // Value to be updated by the ESPS Stack once the request is sent
    .netType = ESSASNETT_INTERNAL
};

/*
 * EPS I TASK DEFINITIONS
 *************************/
/// Main task
static void eps_i_task(void * args);
/// eps i thread handler
static osThreadId_t eps_i_task_handle = NULL;
/// eps i thread atributes
static const osThreadAttr_t eps_i_task_attributes =
{
  .name = "EPS_I_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024
};

/*
 * SYS INSTANCER DEFINITIONS
 ***************************/
static void eps_i_init_memory(void);
static void eps_i_init_hw(void);
static void eps_i_init_os(void);

// Configuration interface for the system instancer
if_sys_mod_t eps_i_module_configuration = {
    .init = eps_i_init,
    .run = eps_i_run,
    .stop = eps_i_stop,
    .deinit = eps_i_deinit,
};

/*
 * SYS INSTANCER FUNCTIONS
 *************************/
// System module interface functions
mod_op_status_id_t eps_i_init(sys_init_level_id_t level){
    mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

    // Eventually, to split the initialisation into the different levels
    switch (level){
    case INIT_MEM:
        eps_i_init_memory();
        ret = STATUS_OK;
        break;
    case INIT_HW:
        eps_i_init_hw();
        ret = STATUS_OK;
        break;
    case INIT_OS:
        eps_i_init_os();
        ret = STATUS_OK;
        break;
    default:
        ret = STATUS_NOT_SUPPORTED;;
    }
    return ret;
}
mod_op_status_id_t eps_i_run(void){
    // To be used by the system instancer
    return STATUS_NOT_SUPPORTED;
}
mod_op_status_id_t eps_i_stop(void){
    // To be used by the system instancer
    return STATUS_NOT_SUPPORTED;
}
mod_op_status_id_t eps_i_deinit(sys_init_level_id_t level){
    // To be used by the system instancer
    if (INIT_OS == level){
        task_mon_set_task_policy(TASK_EPS_I, TASK_MON_POLICY_DONT_CARE);
    }
    return STATUS_OK;
}

/*
 * EPS CONTROL
 *************/
// Request EPS I module to switch on or off a channel
bool eps_i_set_channel_output(EPS1_QueryControlsIndex_t channel, EPS1_QueryState_t state){

    // Channel mask should be a valid value from the enum type
    if(EPS1_QUERYCONTROLSINDEX_MAX_CNT <= channel)
    {
        CRIT_ASSERT(false); // Catch this error while in debug
        return false;
    }

    // Initialize the input to 0
    EPS1_QueryState_t req_data [EPS1_QUERYCONTROLSINDEX_MAX_CNT] = {0};

    // Populate the request information
    req_data[channel] = state;

    // This is the esps request
    return (ESSATMAC_EC_OK == EPS1_queryControlsReq(&fp_context, req_data));

}

// Request EPS I to get the power output values
bool eps_i_get_channel_outputs(void){
    // Send the ESPS request to the EPS I module
    return (ESSATMAC_EC_OK == EPS1_getConfigurationInfoReq(&fp_context));
}

// Return the last FP request seqId to be able to match it with the ESPS response
uint16_t eps_i_get_last_request_seq_id(void){
    return fp_context.seqId;
}


uint32_t eps_i_get_config_from_channel(EPS1_QueryControlsIndex_t channel){
    static uint8_t ch_conf_dict[EPS1_QUERYCONTROLSINDEX_MAX_CNT] = {
        EPS_I_OUT_1_SWSelfLock, // EPS1_QUERYCONTROLSINDEX_SWSelfLock
        EPS_I_OUT_1_VBATTEN,    // EPS1_QUERYCONTROLSINDEX_VBattEn
        EPS_I_OUT_1_BCROutEN,   // EPS1_QUERYCONTROLSINDEX_BCROutEn
        EPS_I_OUT_1_SHD_3_3V,   // EPS1_QUERYCONTROLSINDEX_SHD_3v3
        EPS_I_OUT_1_SHD_5V,     // EPS1_QUERYCONTROLSINDEX_SHD_5v
        EPS_I_OUT_2_LUP_3V3,    // EPS1_QUERYCONTROLSINDEX_LUP3v3
        EPS_I_OUT_2_LUP_5V,     // EPS1_QUERYCONTROLSINDEX_LUP5v0
        EPS_I_OUT_2_SHDChrg,    // EPS1_QUERYCONTROLSINDEX_SHDChrg
        EPS_I_OUT_2_Chrg_I1,    // EPS1_QUERYCONTROLSINDEX_Chrg_I1
        EPS_I_OUT_2_Chrg_I2,    // EPS1_QUERYCONTROLSINDEX_Chrg_I2
        EPS_I_OUT_1_OUT1,       // EPS1_QUERYCONTROLSINDEX_OUT1
        EPS_I_OUT_1_OUT2,       // EPS1_QUERYCONTROLSINDEX_OUT2
        EPS_I_OUT_1_OUT3,       // EPS1_QUERYCONTROLSINDEX_OUT3
        EPS_I_OUT_1_OUT4,       // EPS1_QUERYCONTROLSINDEX_OUT4_OBC
        EPS_I_OUT_1_OUT5,       // EPS1_QUERYCONTROLSINDEX_OUT5
        EPS_I_OUT_1_OUT6,       // EPS1_QUERYCONTROLSINDEX_OUT6
        EPS_I_OUT_1_HEATER1,    // EPS1_QUERYCONTROLSINDEX_Heater_1
        EPS_I_OUT_1_HEATER2,    // EPS1_QUERYCONTROLSINDEX_Heater_2
        EPS_I_OUT_1_HEATER3,    // EPS1_QUERYCONTROLSINDEX_Heater_3
        EPS_I_OUT_2_10KPULLUP,  // EPS1_QUERYCONTROLSINDEX_I2C_10k_pu
        EPS_I_OUT_2_4K7PULLUP,  // EPS1_QUERYCONTROLSINDEX_I2C_4k7_pu
        EPS_I_OUT_2_R_TERMIN,   // EPS1_QUERYCONTROLSINDEX_RS485_120R
        EPS_I_OUT_1_RESERVED,   // EPS1_QUERYCONTROLSINDEX_Reserved
        EPS_I_OUT_2_OUT7,       // EPS1_QUERYCONTROLSINDEX_OUT7
        EPS_I_OUT_2_OUT8,       // EPS1_QUERYCONTROLSINDEX_OUT8
        EPS_I_OUT_1_RESERVED2   // EPS1_QUERYCONTROLSINDEX_RESET_MPPT
    };
    return (uint32_t) (1 << ch_conf_dict[channel]);

}

/*
 * TELEMETRY (DATACACHE)
 ***********************/
// Process response GetDistributionInfo
void eps_i_info_to_datacache(const EPS1getBatteryInfoResponseData_t* battery_info){
    static DATA_CACHE_EPS_0_t eps_0_data = {0};

    // Convert the raw value from the EPS 1 into human readable values (mv, ma)
    int32_t batt_voltage =  conv_batt_volt_mv * (int32_t) battery_info->sBattery.sBatt.u16Volt;
    int32_t batt_current =  conv_batt_curr_ma * (int32_t) battery_info->sBattery.sBatt.u16Curr;

    // We cannot obtain all the values from the EPS I, some of them must be estimated somewhere else
    // Populate the DATA_CACHE_EPS_0_t struct
    eps_0_data.i64BattEnergy = (int64_t) 0x0;
    eps_0_data.i64BattCharge = (int64_t) 0x0;
    eps_0_data.i64BattChargeCapacity = (int64_t) 0x0;
    eps_0_data.i64BattPercent = (int64_t) 0x0;
    eps_0_data.i32BattVoltage = batt_voltage;
    eps_0_data.i32BattCurrent = batt_current;
    eps_0_data.i32BattTemperature = (int32_t) 0x0;

    // Update the datacache
    dc_set_eps_0_data(&eps_0_data);
}

/**
* @brief Initialization related to the HW peripherals
*
* @return   none
* @note     If the initialization fails the OBC will try to restart
*/
static void eps_i_init_memory(void)
{
    /* SYS INIT MEMORY LEVEL */
    // Initialize the MAC Address from NVM
	fp_context.nAddr = eps_i_cfg_get_mac_address();
}
/**
* @brief Initialization related to the HW peripherals
*
* @return   none
* @note     If the initialization fails the OBC will try to restart
*/

static void eps_i_init_hw(void){
    /* SYS INIT HW LEVEL */
    // Also RS-485 bus is initialized separately in the espsi_drv module
    // Nothing to initialize
}
/**
* @brief Initialization related to the OS (RTOS)
*
* @return   none
* @note     If the initialization fails the OBC will try to restart
*/
static void eps_i_init_os(void){
    eps_i_task_handle = osThreadNew(eps_i_task, NULL, &eps_i_task_attributes);
    CRIT_ASSERT(eps_i_task_handle);

    // Notify TaskMonitor
    task_mon_set_task_policy(TASK_EPS_I, TASK_MON_POLICY_MONITOR);
    TaskMonitor_TaskInitialized(TASK_EPS_I);
}

/**
* @brief Main EPS I task. Periodically requests the EPS I Battery status
*
* @return   none
*/
static void eps_i_task(void * args){
    (void)args;

    for(;;) {
        if (SAFE_TRUE == ESSA_Stack_Facade_Is_Init())
        {
            // Send request to the EPS I
            EPS1_getBatteryInfoReq(&fp_context);
        }

        osDelay(EPS_I_TASK_PERIOD);

        TaskMonitor_IamAlive(TASK_EPS_I);
        vApplicationLowStackCheck(TASK_EPS_I);
    }
}
