/*!
********************************************************************************************
* @file datacache.c
* @brief Data Cache C implementation generator
********************************************************************************************
* @version           interface data_cache v0.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_DC v0.8
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "datacache.h"
#include "datacache_cfg.h"

/**********************************************************************
 *
 *  Internal macros and defines
 *
 **********************************************************************/
#ifdef DC_DATA_ACCESS_SYNC_ENABLED
#define DC_DATA_LOCK(data_id)   do { dc_cfg_lock_acquire(dc_data_rt[data_id].data_lock) } while (0U);
#define DC_DATA_UNLOCK(data_id) do { dc_cfg_lock_release(dc_data_rt[data_id].data_lock) } while (0U);
#else
#define DC_DATA_LOCK(data_id)   while (0U);
#define DC_DATA_UNLOCK(data_id) while (0U);
#endif

// special bool values are used here in order to increase the Hamming distance between the discrete values
#define FALSE   (0x00U)
#define TRUE    (0xFFU)

/**********************************************************************
 *
 *  Internal data types
 *
 **********************************************************************/

/** \struct dc_cfg_entry_immut_t
 *  \brief DC shall keep a static configuration for each data entry in FLASH ROM represented by the following data type:
*/
typedef struct
{
    const uint16_t data_id;       /**< internal data attribute ID as specified in the FIDL file */
    void * const p_data_raw;      /**< a pointer to the entry data buffer */
    const uint32_t data_size;     /**< in bytes */
    const uint32_t data_timeout;  /**< time before data status gets set to DC_DATA_STATUS_TOUT if no updates received */
} dc_cfg_entry_immut_t;

/** \struct dc_data_rtctx_t
 *  \brief DC shall keep runtime data context for each data entry in RAM represented by the following data type:
*/
typedef struct
{
    dc_data_input_t last_input_type;      /**< last input type used for this data */
    dc_data_status_t last_data_status;    /**< last DC-calculated data status */
    uint32_t last_update_tstamp;          /**< timestamp of last data update  */
#if defined(DC_DATA_ACCESS_SYNC_ENABLED)
    dc_cfg_lock_t data_lock;              /**< mutex or other handle to support data access synchronization */
#endif
} dc_data_rtctx_t;

typedef struct
{
    DATA_CACHE_OBC_0_t obc_0_data;
    DATA_CACHE_ADCS_0_t adcs_0_data;
    DATA_CACHE_ADCS_1_t adcs_1_data;
    DATA_CACHE_ADCS_2_t adcs_2_data;
    DATA_CACHE_EPS_0_t eps_0_data;
    DATA_CACHE_SSP_0_t ssp_0_data;
    DATA_CACHE_SSP_1_t ssp_1_data;
    DATA_CACHE_SSP_2_t ssp_2_data;
    DATA_CACHE_AOCS_CNTRL_TLM_t aocs_cntrl_tlm_data;
    DATA_CACHE_TaskStats_t os_task_data;
    DATA_CACHE_SSP_3_t ssp_3_data;
    DATA_CACHE_SENSOR_MAG_PRIMARY_t sensor_mag_primary_data;
    DATA_CACHE_SENSOR_MAG_SECONDARY_t sensor_mag_secondary_data;
    DATA_CACHE_SENSOR_GYRO_t sensor_gyro_data;
    DATA_CACHE_SENSOR_COARSE_SUN_t sensor_coarse_sun_data;
    DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t es_adcs_sensor_mag_primary_data;
    DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t es_adcs_sensor_mag_secondary_data;
    DATA_CACHE_ES_ADCS_SENSOR_GYRO_t es_adcs_sensor_gyro_data;
    DATA_CACHE_ES_ADCS_SENSOR_CSS_t es_adcs_sensor_css_data;
    DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t es_adcs_estimates_bdot_data;
    DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t es_adcs_control_values_mtq_data;
    DATA_CACHE_ConOpsFlags_t conopsflags_data;
    DATA_CACHE_AOCS_CNTRL_SYS_STATE_t aocs_cntrl_sys_state_data;
    DATA_CACHE_ADCS_3_t adcs_3_data;
    DATA_CACHE_ADCS_4_t adcs_4_data;
    DATA_CACHE_EPS_9_t eps_9_data;
    DATA_CACHE_EPS_10_t eps_10_data;
    DATA_CACHE_EPS_14_t eps_14_data;
    DATA_CACHE_SENSOR_ACC_PRIMARY_t sensor_acc_primary_data;
    DATA_CACHE_SENSOR_ACC_SECONDARY_t sensor_acc_secondary_data;
    DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t sensor_acc_primary_sat_frame_data;
    DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t sensor_acc_secondary_sat_frame_data;
    DATA_CACHE_SENSOR_PANEL_TEMP_t sensor_panel_temp_data;
    DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t sensor_panel_temp_sat_frame_data;
    DATA_CACHE_SENSOR_GYRO_TEMP_t sensor_gyro_temp_data;
    DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t sensor_gyro_temp_sat_frame_data;
    DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t cubeadcs_gen2_op_status_common_data;
    DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t cubeadcs_gen2_op_status_app_data;
    DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t aocs_cntrl_ref_params_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t cubeadcs_gen2_tlm_frame_166_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t cubeadcs_gen2_tlm_frame_167_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t cubeadcs_gen2_tlm_frame_168_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t cubeadcs_gen2_tlm_frame_169_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t cubeadcs_gen2_tlm_frame_170_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t cubeadcs_gen2_tlm_frame_171_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t cubeadcs_gen2_tlm_frame_172_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t cubeadcs_gen2_tlm_frame_173_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t cubeadcs_gen2_tlm_frame_174_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t cubeadcs_gen2_tlm_frame_175_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t cubeadcs_gen2_tlm_frame_176_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t cubeadcs_gen2_tlm_frame_177_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t cubeadcs_gen2_tlm_frame_178_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t cubeadcs_gen2_tlm_frame_179_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t cubeadcs_gen2_tlm_frame_180_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t cubeadcs_gen2_tlm_frame_203_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t cubeadcs_gen2_tlm_frame_204_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t cubeadcs_gen2_tlm_frame_205_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t cubeadcs_gen2_tlm_frame_206_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t cubeadcs_gen2_tlm_frame_207_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t cubeadcs_gen2_tlm_frame_208_1_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t cubeadcs_gen2_tlm_frame_208_2_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t cubeadcs_gen2_tlm_frame_209_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t cubeadcs_gen2_tlm_frame_210_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t cubeadcs_gen2_tlm_frame_211_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t cubeadcs_gen2_tlm_frame_212_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t cubeadcs_gen2_tlm_frame_213_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t cubeadcs_gen2_tlm_frame_214_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t cubeadcs_gen2_tlm_frame_216_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t cubeadcs_gen2_tlm_frame_217_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t cubeadcs_gen2_tlm_frame_218_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t cubeadcs_gen2_tlm_frame_225_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t cubeadcs_gen2_tlm_frame_226_data;
    DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t cubeadcs_gen2_tlm_frame_165_data;
    DATA_CACHE_GNSS_TIME_t gnss_time_data;
    DATA_CACHE_GNSS_BESTXYZ_t gnss_bestxyz_data;
    DATA_CACHE_EpsOverallBatteryInfoType_t epsoverallbatteryinfo_data;
    DATA_CACHE_Eps2Inst0BatteryInfoType_t eps2_bp_inst0_bp_info_data;
    DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t eps2_bp_inst0_device_health_info_data;
    DATA_CACHE_Eps2Inst0InaSensors1Type_t eps2_bp_inst0_ina_sensor1_data;
    DATA_CACHE_Eps2Inst0InaSensors2Type_t eps2_bp_inst0_ina_sensor2_data;
    DATA_CACHE_Eps2Inst0BalancerInfoType_t eps2_bp_inst0_balancer_info_data;
    DATA_CACHE_Eps2Inst0BalancerStatusType_t eps2_bp_inst0_balancer_status_data;
    DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t eps2_bp_inst0_balancer_cells_info_data;
    DATA_CACHE_Eps2Inst0ChargerXpType_t eps2_bp_inst0_charger_xp_data;
    DATA_CACHE_Eps2Inst0ChargerXrType_t eps2_bp_inst0_charger_xr_data;
    DATA_CACHE_Eps2Inst0ChargerYpType_t eps2_bp_inst0_charger_yp_data;
    DATA_CACHE_Eps2Inst0ChargerYrType_t eps2_bp_inst0_charger_yr_data;
    DATA_CACHE_Eps2Inst0ChargerZpType_t eps2_bp_inst0_charger_zp_data;
    DATA_CACHE_Eps2Inst0ChargerZrType_t eps2_bp_inst0_charger_zr_data;
    DATA_CACHE_Eps2Inst1BatteryInfoType_t eps2_bp_inst1_bp_info_data;
    DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t eps2_bp_inst1_device_health_info_data;
    DATA_CACHE_Eps2Inst1InaSensors1Type_t eps2_bp_inst1_ina_sensor1_data;
    DATA_CACHE_Eps2Inst1InaSensors2Type_t eps2_bp_inst1_ina_sensor2_data;
    DATA_CACHE_Eps2Inst1BalancerInfoType_t eps2_bp_inst1_balancer_info_data;
    DATA_CACHE_Eps2Inst1BalancerStatusType_t eps2_bp_inst1_balancer_status_data;
    DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t eps2_bp_inst1_balancer_cells_info_data;
    DATA_CACHE_Eps2Inst1ChargerXpType_t eps2_bp_inst1_charger_xp_data;
    DATA_CACHE_Eps2Inst1ChargerXrType_t eps2_bp_inst1_charger_xr_data;
    DATA_CACHE_Eps2Inst1ChargerYpType_t eps2_bp_inst1_charger_yp_data;
    DATA_CACHE_Eps2Inst1ChargerYrType_t eps2_bp_inst1_charger_yr_data;
    DATA_CACHE_Eps2Inst1ChargerZpType_t eps2_bp_inst1_charger_zp_data;
    DATA_CACHE_Eps2Inst1ChargerZrType_t eps2_bp_inst1_charger_zr_data;
    DATA_CACHE_Eps2Inst2BatteryInfoType_t eps2_bp_inst2_bp_info_data;
    DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t eps2_bp_inst2_device_health_info_data;
    DATA_CACHE_Eps2Inst2InaSensors1Type_t eps2_bp_inst2_ina_sensor1_data;
    DATA_CACHE_Eps2Inst2InaSensors2Type_t eps2_bp_inst2_ina_sensor2_data;
    DATA_CACHE_Eps2Inst2BalancerInfoType_t eps2_bp_inst2_balancer_info_data;
    DATA_CACHE_Eps2Inst2BalancerStatusType_t eps2_bp_inst2_balancer_status_data;
    DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t eps2_bp_inst2_balancer_cells_info_data;
    DATA_CACHE_Eps2Inst2ChargerXpType_t eps2_bp_inst2_charger_xp_data;
    DATA_CACHE_Eps2Inst2ChargerXrType_t eps2_bp_inst2_charger_xr_data;
    DATA_CACHE_Eps2Inst2ChargerYpType_t eps2_bp_inst2_charger_yp_data;
    DATA_CACHE_Eps2Inst2ChargerYrType_t eps2_bp_inst2_charger_yr_data;
    DATA_CACHE_Eps2Inst2ChargerZpType_t eps2_bp_inst2_charger_zp_data;
    DATA_CACHE_Eps2Inst2ChargerZrType_t eps2_bp_inst2_charger_zr_data;
} PACKED_STRUCT datacache_t;

/**********************************************************************
 *
 *  Static variables
 *
 **********************************************************************/

static uint8_t dc_initialized = FALSE;

/** \brief Main DataCache instance in RAM */
static datacache_t dc_instance;

/** \brief Immutable Data Cache configuration */
static dc_data_rtctx_t dc_data_rt[DC_DID_MAX];

static const dc_cfg_entry_immut_t dc_data_cfg[DC_DID_MAX] =
{
    // obc_0_data
    {
        .data_id = DC_ATTR_ID_OBC_0_DATA,
        .p_data_raw = &dc_instance.obc_0_data,
        .data_size = sizeof(dc_instance.obc_0_data),
        .data_timeout = 5000U
    },
    // adcs_0_data
    {
        .data_id = DC_ATTR_ID_ADCS_0_DATA,
        .p_data_raw = &dc_instance.adcs_0_data,
        .data_size = sizeof(dc_instance.adcs_0_data),
        .data_timeout = 5000U
    },
    // adcs_1_data
    {
        .data_id = DC_ATTR_ID_ADCS_1_DATA,
        .p_data_raw = &dc_instance.adcs_1_data,
        .data_size = sizeof(dc_instance.adcs_1_data),
        .data_timeout = 5000U
    },
    // adcs_2_data
    {
        .data_id = DC_ATTR_ID_ADCS_2_DATA,
        .p_data_raw = &dc_instance.adcs_2_data,
        .data_size = sizeof(dc_instance.adcs_2_data),
        .data_timeout = 5000U
    },
    // eps_0_data
    {
        .data_id = DC_ATTR_ID_EPS_0_DATA,
        .p_data_raw = &dc_instance.eps_0_data,
        .data_size = sizeof(dc_instance.eps_0_data),
        .data_timeout = 5000U
    },
    // ssp_0_data
    {
        .data_id = DC_ATTR_ID_SSP_0_DATA,
        .p_data_raw = &dc_instance.ssp_0_data,
        .data_size = sizeof(dc_instance.ssp_0_data),
        .data_timeout = 5000U
    },
    // ssp_1_data
    {
        .data_id = DC_ATTR_ID_SSP_1_DATA,
        .p_data_raw = &dc_instance.ssp_1_data,
        .data_size = sizeof(dc_instance.ssp_1_data),
        .data_timeout = 5000U
    },
    // ssp_2_data
    {
        .data_id = DC_ATTR_ID_SSP_2_DATA,
        .p_data_raw = &dc_instance.ssp_2_data,
        .data_size = sizeof(dc_instance.ssp_2_data),
        .data_timeout = 5000U
    },
    // aocs_cntrl_tlm_data
    {
        .data_id = DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
        .p_data_raw = &dc_instance.aocs_cntrl_tlm_data,
        .data_size = sizeof(dc_instance.aocs_cntrl_tlm_data),
        .data_timeout = 5000U
    },
    // os_task_data
    {
        .data_id = DC_ATTR_ID_OS_TASK_DATA,
        .p_data_raw = &dc_instance.os_task_data,
        .data_size = sizeof(dc_instance.os_task_data),
        .data_timeout = 5000U
    },
    // ssp_3_data
    {
        .data_id = DC_ATTR_ID_SSP_3_DATA,
        .p_data_raw = &dc_instance.ssp_3_data,
        .data_size = sizeof(dc_instance.ssp_3_data),
        .data_timeout = 5000U
    },
    // sensor_mag_primary_data
    {
        .data_id = DC_ATTR_ID_SENSOR_MAG_PRIMARY_DATA,
        .p_data_raw = &dc_instance.sensor_mag_primary_data,
        .data_size = sizeof(dc_instance.sensor_mag_primary_data),
        .data_timeout = 5000U
    },
    // sensor_mag_secondary_data
    {
        .data_id = DC_ATTR_ID_SENSOR_MAG_SECONDARY_DATA,
        .p_data_raw = &dc_instance.sensor_mag_secondary_data,
        .data_size = sizeof(dc_instance.sensor_mag_secondary_data),
        .data_timeout = 5000U
    },
    // sensor_gyro_data
    {
        .data_id = DC_ATTR_ID_SENSOR_GYRO_DATA,
        .p_data_raw = &dc_instance.sensor_gyro_data,
        .data_size = sizeof(dc_instance.sensor_gyro_data),
        .data_timeout = 5000U
    },
    // sensor_coarse_sun_data
    {
        .data_id = DC_ATTR_ID_SENSOR_COARSE_SUN_DATA,
        .p_data_raw = &dc_instance.sensor_coarse_sun_data,
        .data_size = sizeof(dc_instance.sensor_coarse_sun_data),
        .data_timeout = 5000U
    },
    // es_adcs_sensor_mag_primary_data
    {
        .data_id = DC_ATTR_ID_ES_ADCS_SENSOR_MAG_PRIMARY_DATA,
        .p_data_raw = &dc_instance.es_adcs_sensor_mag_primary_data,
        .data_size = sizeof(dc_instance.es_adcs_sensor_mag_primary_data),
        .data_timeout = 5000U
    },
    // es_adcs_sensor_mag_secondary_data
    {
        .data_id = DC_ATTR_ID_ES_ADCS_SENSOR_MAG_SECONDARY_DATA,
        .p_data_raw = &dc_instance.es_adcs_sensor_mag_secondary_data,
        .data_size = sizeof(dc_instance.es_adcs_sensor_mag_secondary_data),
        .data_timeout = 5000U
    },
    // es_adcs_sensor_gyro_data
    {
        .data_id = DC_ATTR_ID_ES_ADCS_SENSOR_GYRO_DATA,
        .p_data_raw = &dc_instance.es_adcs_sensor_gyro_data,
        .data_size = sizeof(dc_instance.es_adcs_sensor_gyro_data),
        .data_timeout = 5000U
    },
    // es_adcs_sensor_css_data
    {
        .data_id = DC_ATTR_ID_ES_ADCS_SENSOR_CSS_DATA,
        .p_data_raw = &dc_instance.es_adcs_sensor_css_data,
        .data_size = sizeof(dc_instance.es_adcs_sensor_css_data),
        .data_timeout = 5000U
    },
    // es_adcs_estimates_bdot_data
    {
        .data_id = DC_ATTR_ID_ES_ADCS_ESTIMATES_BDOT_DATA,
        .p_data_raw = &dc_instance.es_adcs_estimates_bdot_data,
        .data_size = sizeof(dc_instance.es_adcs_estimates_bdot_data),
        .data_timeout = 5000U
    },
    // es_adcs_control_values_mtq_data
    {
        .data_id = DC_ATTR_ID_ES_ADCS_CONTROL_VALUES_MTQ_DATA,
        .p_data_raw = &dc_instance.es_adcs_control_values_mtq_data,
        .data_size = sizeof(dc_instance.es_adcs_control_values_mtq_data),
        .data_timeout = 5000U
    },
    // conopsflags_data
    {
        .data_id = DC_ATTR_ID_CONOPSFLAGS_DATA,
        .p_data_raw = &dc_instance.conopsflags_data,
        .data_size = sizeof(dc_instance.conopsflags_data),
        .data_timeout = 5000U
    },
    // aocs_cntrl_sys_state_data
    {
        .data_id = DC_ATTR_ID_AOCS_CNTRL_SYS_STATE_DATA,
        .p_data_raw = &dc_instance.aocs_cntrl_sys_state_data,
        .data_size = sizeof(dc_instance.aocs_cntrl_sys_state_data),
        .data_timeout = 5000U
    },
    // adcs_3_data
    {
        .data_id = DC_ATTR_ID_ADCS_3_DATA,
        .p_data_raw = &dc_instance.adcs_3_data,
        .data_size = sizeof(dc_instance.adcs_3_data),
        .data_timeout = 5000U
    },
    // adcs_4_data
    {
        .data_id = DC_ATTR_ID_ADCS_4_DATA,
        .p_data_raw = &dc_instance.adcs_4_data,
        .data_size = sizeof(dc_instance.adcs_4_data),
        .data_timeout = 5000U
    },
    // eps_9_data
    {
        .data_id = DC_ATTR_ID_EPS_9_DATA,
        .p_data_raw = &dc_instance.eps_9_data,
        .data_size = sizeof(dc_instance.eps_9_data),
        .data_timeout = 30000U
    },
    // eps_10_data
    {
        .data_id = DC_ATTR_ID_EPS_10_DATA,
        .p_data_raw = &dc_instance.eps_10_data,
        .data_size = sizeof(dc_instance.eps_10_data),
        .data_timeout = 30000U
    },
    // eps_14_data
    {
        .data_id = DC_ATTR_ID_EPS_14_DATA,
        .p_data_raw = &dc_instance.eps_14_data,
        .data_size = sizeof(dc_instance.eps_14_data),
        .data_timeout = 30000U
    },
    // sensor_acc_primary_data
    {
        .data_id = DC_ATTR_ID_SENSOR_ACC_PRIMARY_DATA,
        .p_data_raw = &dc_instance.sensor_acc_primary_data,
        .data_size = sizeof(dc_instance.sensor_acc_primary_data),
        .data_timeout = 5000U
    },
    // sensor_acc_secondary_data
    {
        .data_id = DC_ATTR_ID_SENSOR_ACC_SECONDARY_DATA,
        .p_data_raw = &dc_instance.sensor_acc_secondary_data,
        .data_size = sizeof(dc_instance.sensor_acc_secondary_data),
        .data_timeout = 5000U
    },
    // sensor_acc_primary_sat_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_acc_primary_sat_frame_data,
        .data_size = sizeof(dc_instance.sensor_acc_primary_sat_frame_data),
        .data_timeout = 5000U
    },
    // sensor_acc_secondary_sat_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_acc_secondary_sat_frame_data,
        .data_size = sizeof(dc_instance.sensor_acc_secondary_sat_frame_data),
        .data_timeout = 5000U
    },
    // sensor_panel_temp_data
    {
        .data_id = DC_ATTR_ID_SENSOR_PANEL_TEMP_DATA,
        .p_data_raw = &dc_instance.sensor_panel_temp_data,
        .data_size = sizeof(dc_instance.sensor_panel_temp_data),
        .data_timeout = 5000U
    },
    // sensor_panel_temp_sat_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_PANEL_TEMP_SAT_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_panel_temp_sat_frame_data,
        .data_size = sizeof(dc_instance.sensor_panel_temp_sat_frame_data),
        .data_timeout = 5000U
    },
    // sensor_gyro_temp_data
    {
        .data_id = DC_ATTR_ID_SENSOR_GYRO_TEMP_DATA,
        .p_data_raw = &dc_instance.sensor_gyro_temp_data,
        .data_size = sizeof(dc_instance.sensor_gyro_temp_data),
        .data_timeout = 5000U
    },
    // sensor_gyro_temp_sat_frame_data
    {
        .data_id = DC_ATTR_ID_SENSOR_GYRO_TEMP_SAT_FRAME_DATA,
        .p_data_raw = &dc_instance.sensor_gyro_temp_sat_frame_data,
        .data_size = sizeof(dc_instance.sensor_gyro_temp_sat_frame_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_op_status_common_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_op_status_common_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_op_status_common_data),
        .data_timeout = 10000U
    },
    // cubeadcs_gen2_op_status_app_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_APP_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_op_status_app_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_op_status_app_data),
        .data_timeout = 10000U
    },
    // aocs_cntrl_ref_params_data
    {
        .data_id = DC_ATTR_ID_AOCS_CNTRL_REF_PARAMS_DATA,
        .p_data_raw = &dc_instance.aocs_cntrl_ref_params_data,
        .data_size = sizeof(dc_instance.aocs_cntrl_ref_params_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_166_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_166_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_166_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_166_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_167_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_167_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_167_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_167_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_168_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_168_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_168_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_168_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_169_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_169_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_169_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_169_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_170_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_170_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_170_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_170_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_171_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_171_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_171_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_171_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_172_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_172_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_172_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_172_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_173_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_173_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_173_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_173_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_174_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_174_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_174_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_174_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_175_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_175_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_175_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_175_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_176_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_176_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_176_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_176_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_177_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_177_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_177_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_177_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_178_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_178_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_178_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_178_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_179_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_179_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_179_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_179_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_180_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_180_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_180_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_180_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_203_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_203_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_203_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_203_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_204_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_204_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_204_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_204_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_205_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_205_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_205_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_205_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_206_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_206_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_206_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_206_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_207_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_207_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_207_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_207_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_208_1_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_208_1_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_208_1_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_208_2_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_208_2_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_208_2_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_209_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_209_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_209_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_209_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_210_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_210_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_210_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_210_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_211_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_211_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_211_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_211_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_212_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_212_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_212_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_212_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_213_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_213_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_213_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_213_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_214_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_214_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_214_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_214_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_216_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_216_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_216_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_216_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_217_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_217_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_217_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_217_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_218_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_218_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_218_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_218_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_225_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_225_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_225_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_225_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_226_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_226_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_226_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_226_data),
        .data_timeout = 5000U
    },
    // cubeadcs_gen2_tlm_frame_165_data
    {
        .data_id = DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_165_DATA,
        .p_data_raw = &dc_instance.cubeadcs_gen2_tlm_frame_165_data,
        .data_size = sizeof(dc_instance.cubeadcs_gen2_tlm_frame_165_data),
        .data_timeout = 5000U
    },
    // gnss_time_data
    {
        .data_id = DC_ATTR_ID_GNSS_TIME_DATA,
        .p_data_raw = &dc_instance.gnss_time_data,
        .data_size = sizeof(dc_instance.gnss_time_data),
        .data_timeout = 5000U
    },
    // gnss_bestxyz_data
    {
        .data_id = DC_ATTR_ID_GNSS_BESTXYZ_DATA,
        .p_data_raw = &dc_instance.gnss_bestxyz_data,
        .data_size = sizeof(dc_instance.gnss_bestxyz_data),
        .data_timeout = 5000U
    },
    // epsoverallbatteryinfo_data
    {
        .data_id = DC_ATTR_ID_EPSOVERALLBATTERYINFO_DATA,
        .p_data_raw = &dc_instance.epsoverallbatteryinfo_data,
        .data_size = sizeof(dc_instance.epsoverallbatteryinfo_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_bp_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BP_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_bp_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_bp_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_device_health_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_device_health_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_device_health_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_ina_sensor1_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR1_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_ina_sensor1_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_ina_sensor1_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_ina_sensor2_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR2_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_ina_sensor2_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_ina_sensor2_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_balancer_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BALANCER_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_balancer_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_balancer_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_balancer_status_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BALANCER_STATUS_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_balancer_status_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_balancer_status_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_balancer_cells_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_balancer_cells_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_balancer_cells_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_xp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_xp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_xp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_xr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_xr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_xr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_yp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_yp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_yp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_yr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_yr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_yr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_zp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_zp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_zp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst0_charger_zr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst0_charger_zr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst0_charger_zr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_bp_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_BP_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_bp_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_bp_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_device_health_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_device_health_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_device_health_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_ina_sensor1_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_INA_SENSOR1_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_ina_sensor1_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_ina_sensor1_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_ina_sensor2_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_INA_SENSOR2_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_ina_sensor2_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_ina_sensor2_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_balancer_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_BALANCER_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_balancer_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_balancer_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_balancer_status_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_BALANCER_STATUS_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_balancer_status_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_balancer_status_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_balancer_cells_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_balancer_cells_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_balancer_cells_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_charger_xp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_CHARGER_XP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_charger_xp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_charger_xp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_charger_xr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_CHARGER_XR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_charger_xr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_charger_xr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_charger_yp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_CHARGER_YP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_charger_yp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_charger_yp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_charger_yr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_CHARGER_YR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_charger_yr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_charger_yr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_charger_zp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_CHARGER_ZP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_charger_zp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_charger_zp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst1_charger_zr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST1_CHARGER_ZR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst1_charger_zr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst1_charger_zr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_bp_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_BP_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_bp_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_bp_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_device_health_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_device_health_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_device_health_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_ina_sensor1_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_INA_SENSOR1_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_ina_sensor1_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_ina_sensor1_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_ina_sensor2_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_INA_SENSOR2_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_ina_sensor2_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_ina_sensor2_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_balancer_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_BALANCER_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_balancer_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_balancer_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_balancer_status_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_BALANCER_STATUS_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_balancer_status_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_balancer_status_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_balancer_cells_info_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_balancer_cells_info_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_balancer_cells_info_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_charger_xp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_CHARGER_XP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_charger_xp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_charger_xp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_charger_xr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_CHARGER_XR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_charger_xr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_charger_xr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_charger_yp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_CHARGER_YP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_charger_yp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_charger_yp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_charger_yr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_CHARGER_YR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_charger_yr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_charger_yr_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_charger_zp_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_CHARGER_ZP_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_charger_zp_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_charger_zp_data),
        .data_timeout = 30000U
    },
    // eps2_bp_inst2_charger_zr_data
    {
        .data_id = DC_ATTR_ID_EPS2_BP_INST2_CHARGER_ZR_DATA,
        .p_data_raw = &dc_instance.eps2_bp_inst2_charger_zr_data,
        .data_size = sizeof(dc_instance.eps2_bp_inst2_charger_zr_data),
        .data_timeout = 30000U
    }
};

/**********************************************************************
 *
 *  Public functions
 *
 **********************************************************************/

/*!
* @brief Init routine for the DataCache component
*/
void dc_init(void)
{
    // timestamps are assumed to be 32-bits in this code and if this conditions is not met,
    // that should be signalled to the user
    DC_ASSERT(sizeof(dc_data_rt[0U].last_update_tstamp) == 4U);

    for (uint16_t i = 0; i < DC_DID_MAX; i++)
    {
        dc_data_rt[i].last_input_type = DC_DATA_INPUT_INTERNAL;
        dc_data_rt[i].last_data_status = DC_NOT_INITIALIZED;
        dc_data_rt[i].last_update_tstamp = 0U;

#ifdef DC_DATA_ACCESS_SYNC_ENABLED
        char lock_name[16U];
        sprintf(lock_name, "dc_lock_%03d", i);
        dc_data_rt[i].data_lock = dc_cfg_lock_new(lock_name);
#endif
    }

    dc_initialized = TRUE;

    // call system-specific init to schedule the task execution...
    dc_cfg_init();
}

/*!
* @brief Main Data Cache task function
* @warning Should not be called too often because it locks the data in order to modify it and
*          could interfere with the set/get operations called by DC clients.
*/
void dc_task(void)
{
    if (TRUE == dc_initialized)
    {
        for (uint16_t i = 0U; i < sizeof(dc_data_rt) / sizeof(dc_data_rt[0]); i++)
        {
            // if timeout is 0, tracking is not performed at all
            if ((dc_data_cfg[i].data_timeout > 0U) &&
                (DC_DATA_STATUS_OK == dc_data_rt[i].last_data_status))
            {
                uint32_t current_tstamp = dc_cfg_get_sys_timestamp();
                uint32_t delta = 0U;

                DC_DATA_LOCK(i);

                if (current_tstamp >= dc_data_rt[i].last_update_tstamp)
                {
                    delta = current_tstamp - dc_data_rt[i].last_update_tstamp;
                }
                else
                {
                    // if the last_update_tstamp type size is changed, the UINT_MAX value below has to be updated to
                    // properly calculate roll-over deltas
                    delta = current_tstamp + (UINT_MAX - dc_data_rt[i].last_update_tstamp);
                }

                if (delta >= dc_data_cfg[i].data_timeout)
                    dc_data_rt[i].last_data_status = DC_DATA_STATUS_TOUT;

                DC_DATA_UNLOCK(i);
            }
        }
    }
}

dc_data_status_t dc_get_raw_data(const dc_did_id id,
                                 void * const p_data,
                                 const uint32_t user_buf_size,
                                 const uint32_t start_offset,
                                 const uint32_t bytes_to_read)
{
    dc_data_status_t res = DC_NOT_INITIALIZED;

    DC_ASSERT(TRUE == dc_initialized);
    DC_ASSERT(id < DC_DID_MAX);
    DC_ASSERT(user_buf_size >= bytes_to_read);
    DC_ASSERT(start_offset + bytes_to_read <= dc_data_cfg[id].data_size);

    DC_DATA_LOCK(id);

    // perform data copy
    (void) memcpy(p_data, &((const uint8_t *) dc_data_cfg[id].p_data_raw)[start_offset], bytes_to_read);

    res = dc_data_rt[id].last_data_status;

    DC_DATA_UNLOCK(id);

    return res;
}

void dc_set_raw_data(const dc_data_input_t input_type, const dc_did_id id, const void * const p_new_data, const uint32_t data_size)
{
    DC_ASSERT(TRUE == dc_initialized);
    DC_ASSERT(id < DC_DID_MAX);
    DC_ASSERT(input_type < DC_DATA_INPUT_MAX);
    DC_ASSERT(data_size == dc_data_cfg[id].data_size);

    // internal data cannot be fed while in sim mode
    if ((DC_DATA_INPUT_INTERNAL == input_type) && (DC_DATA_INPUT_EXTERNAL == dc_data_rt[id].last_input_type))
        return;

    DC_DATA_LOCK(id);

    // perform data copy to local buffer
    (void) memcpy(dc_data_cfg[id].p_data_raw, p_new_data, dc_data_cfg[id].data_size);
    // update local data_status and timestamp
    dc_data_rt[id].last_input_type = input_type;
    dc_data_rt[id].last_data_status = DC_DATA_STATUS_OK;
    dc_data_rt[id].last_update_tstamp = dc_cfg_get_sys_timestamp();

    DC_DATA_UNLOCK(id);
}

uint32_t dc_get_data_size(const dc_did_id id)
{
    DC_ASSERT(TRUE == dc_initialized);
    DC_ASSERT(id < DC_DID_MAX);

    return dc_data_cfg[id].data_size;
}

dc_did_id dc_get_index_by_data_id(const uint16_t data_id)
{
    dc_did_id int_id = DC_DID_MAX;

    for (uint16_t idx = 0U; idx < DC_DID_MAX; idx++)
    {
        if (data_id == dc_data_cfg[idx].data_id)
        {
            int_id = idx;
            break;
        }
    }

    return int_id;
}

void dc_set_input_mode(const dc_did_id id, dc_data_input_t input_type)
{
    DC_ASSERT(id < DC_DID_MAX);
    DC_ASSERT(input_type < DC_DATA_INPUT_MAX);

    switch (id)
    {
        case DC_DID_MAX:
        {
            for (uint8_t idx = 0U; idx < DC_DID_MAX; idx++)
            {
                dc_data_rt[idx].last_input_type = input_type;
            }

            break;
        }

        default:
        {
            dc_data_rt[id].last_input_type = input_type;

            break;
        }
    }
}

dc_data_status_t dc_get_obc_0_data(DATA_CACHE_OBC_0_t * const p_data)
{
    return dc_get_raw_data(DC_DID_OBC_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_OBC_0_t),
                           0U,
                           sizeof(DATA_CACHE_OBC_0_t));
}

void dc_set_obc_0_data(DATA_CACHE_OBC_0_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_OBC_0_DATA, p_new_data, sizeof(DATA_CACHE_OBC_0_t));
}

dc_data_status_t dc_get_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_0_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_0_t));
}

void dc_set_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_0_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_0_t));
}

dc_data_status_t dc_get_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_1_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_1_t));
}

void dc_set_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_1_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_1_t));
}

dc_data_status_t dc_get_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_2_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_2_t));
}

void dc_set_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_2_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_2_t));
}

dc_data_status_t dc_get_eps_0_data(DATA_CACHE_EPS_0_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_0_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_0_t));
}

void dc_set_eps_0_data(DATA_CACHE_EPS_0_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_0_DATA, p_new_data, sizeof(DATA_CACHE_EPS_0_t));
}

dc_data_status_t dc_get_ssp_0_data(DATA_CACHE_SSP_0_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_0_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_0_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_0_t));
}

void dc_set_ssp_0_data(DATA_CACHE_SSP_0_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_0_DATA, p_new_data, sizeof(DATA_CACHE_SSP_0_t));
}

dc_data_status_t dc_get_ssp_1_data(DATA_CACHE_SSP_1_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_1_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_1_t));
}

void dc_set_ssp_1_data(DATA_CACHE_SSP_1_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_1_DATA, p_new_data, sizeof(DATA_CACHE_SSP_1_t));
}

dc_data_status_t dc_get_ssp_2_data(DATA_CACHE_SSP_2_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_2_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_2_t));
}

void dc_set_ssp_2_data(DATA_CACHE_SSP_2_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_2_DATA, p_new_data, sizeof(DATA_CACHE_SSP_2_t));
}

dc_data_status_t dc_get_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_data)
{
    return dc_get_raw_data(DC_DID_AOCS_CNTRL_TLM_DATA,
                           p_data,
                           sizeof(DATA_CACHE_AOCS_CNTRL_TLM_t),
                           0U,
                           sizeof(DATA_CACHE_AOCS_CNTRL_TLM_t));
}

void dc_set_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_AOCS_CNTRL_TLM_DATA, p_new_data, sizeof(DATA_CACHE_AOCS_CNTRL_TLM_t));
}

dc_data_status_t dc_get_os_task_data(DATA_CACHE_TaskStats_t * const p_data)
{
    return dc_get_raw_data(DC_DID_OS_TASK_DATA,
                           p_data,
                           sizeof(DATA_CACHE_TaskStats_t),
                           0U,
                           sizeof(DATA_CACHE_TaskStats_t));
}

void dc_set_os_task_data(DATA_CACHE_TaskStats_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_OS_TASK_DATA, p_new_data, sizeof(DATA_CACHE_TaskStats_t));
}

dc_data_status_t dc_get_ssp_3_data(DATA_CACHE_SSP_3_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SSP_3_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SSP_3_t),
                           0U,
                           sizeof(DATA_CACHE_SSP_3_t));
}

void dc_set_ssp_3_data(DATA_CACHE_SSP_3_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SSP_3_DATA, p_new_data, sizeof(DATA_CACHE_SSP_3_t));
}

dc_data_status_t dc_get_sensor_mag_primary_data(DATA_CACHE_SENSOR_MAG_PRIMARY_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_MAG_PRIMARY_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_t));
}

void dc_set_sensor_mag_primary_data(DATA_CACHE_SENSOR_MAG_PRIMARY_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_MAG_PRIMARY_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_MAG_PRIMARY_t));
}

dc_data_status_t dc_get_sensor_mag_secondary_data(DATA_CACHE_SENSOR_MAG_SECONDARY_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_MAG_SECONDARY_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_t));
}

void dc_set_sensor_mag_secondary_data(DATA_CACHE_SENSOR_MAG_SECONDARY_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_MAG_SECONDARY_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_MAG_SECONDARY_t));
}

dc_data_status_t dc_get_sensor_gyro_data(DATA_CACHE_SENSOR_GYRO_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_GYRO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_GYRO_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_GYRO_t));
}

void dc_set_sensor_gyro_data(DATA_CACHE_SENSOR_GYRO_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_GYRO_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_GYRO_t));
}

dc_data_status_t dc_get_sensor_coarse_sun_data(DATA_CACHE_SENSOR_COARSE_SUN_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_COARSE_SUN_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_COARSE_SUN_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_COARSE_SUN_t));
}

void dc_set_sensor_coarse_sun_data(DATA_CACHE_SENSOR_COARSE_SUN_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_COARSE_SUN_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_COARSE_SUN_t));
}

dc_data_status_t dc_get_es_adcs_sensor_mag_primary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ES_ADCS_SENSOR_MAG_PRIMARY_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t),
                           0U,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t));
}

void dc_set_es_adcs_sensor_mag_primary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ES_ADCS_SENSOR_MAG_PRIMARY_DATA, p_new_data, sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t));
}

dc_data_status_t dc_get_es_adcs_sensor_mag_secondary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ES_ADCS_SENSOR_MAG_SECONDARY_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t),
                           0U,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t));
}

void dc_set_es_adcs_sensor_mag_secondary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ES_ADCS_SENSOR_MAG_SECONDARY_DATA, p_new_data, sizeof(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t));
}

dc_data_status_t dc_get_es_adcs_sensor_gyro_data(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ES_ADCS_SENSOR_GYRO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t),
                           0U,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t));
}

void dc_set_es_adcs_sensor_gyro_data(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ES_ADCS_SENSOR_GYRO_DATA, p_new_data, sizeof(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t));
}

dc_data_status_t dc_get_es_adcs_sensor_css_data(DATA_CACHE_ES_ADCS_SENSOR_CSS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ES_ADCS_SENSOR_CSS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_CSS_t),
                           0U,
                           sizeof(DATA_CACHE_ES_ADCS_SENSOR_CSS_t));
}

void dc_set_es_adcs_sensor_css_data(DATA_CACHE_ES_ADCS_SENSOR_CSS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ES_ADCS_SENSOR_CSS_DATA, p_new_data, sizeof(DATA_CACHE_ES_ADCS_SENSOR_CSS_t));
}

dc_data_status_t dc_get_es_adcs_estimates_bdot_data(DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ES_ADCS_ESTIMATES_BDOT_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t),
                           0U,
                           sizeof(DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t));
}

void dc_set_es_adcs_estimates_bdot_data(DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ES_ADCS_ESTIMATES_BDOT_DATA, p_new_data, sizeof(DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t));
}

dc_data_status_t dc_get_es_adcs_control_values_mtq_data(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ES_ADCS_CONTROL_VALUES_MTQ_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t),
                           0U,
                           sizeof(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t));
}

void dc_set_es_adcs_control_values_mtq_data(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ES_ADCS_CONTROL_VALUES_MTQ_DATA, p_new_data, sizeof(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t));
}

dc_data_status_t dc_get_conopsflags_data(DATA_CACHE_ConOpsFlags_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CONOPSFLAGS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ConOpsFlags_t),
                           0U,
                           sizeof(DATA_CACHE_ConOpsFlags_t));
}

void dc_set_conopsflags_data(DATA_CACHE_ConOpsFlags_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CONOPSFLAGS_DATA, p_new_data, sizeof(DATA_CACHE_ConOpsFlags_t));
}

dc_data_status_t dc_get_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_data)
{
    return dc_get_raw_data(DC_DID_AOCS_CNTRL_SYS_STATE_DATA,
                           p_data,
                           sizeof(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t),
                           0U,
                           sizeof(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t));
}

void dc_set_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_AOCS_CNTRL_SYS_STATE_DATA, p_new_data, sizeof(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t));
}

dc_data_status_t dc_get_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_3_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_3_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_3_t));
}

void dc_set_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_3_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_3_t));
}

dc_data_status_t dc_get_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_data)
{
    return dc_get_raw_data(DC_DID_ADCS_4_DATA,
                           p_data,
                           sizeof(DATA_CACHE_ADCS_4_t),
                           0U,
                           sizeof(DATA_CACHE_ADCS_4_t));
}

void dc_set_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_ADCS_4_DATA, p_new_data, sizeof(DATA_CACHE_ADCS_4_t));
}

dc_data_status_t dc_get_eps_9_data(DATA_CACHE_EPS_9_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_9_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_9_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_9_t));
}

void dc_set_eps_9_data(DATA_CACHE_EPS_9_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_9_DATA, p_new_data, sizeof(DATA_CACHE_EPS_9_t));
}

dc_data_status_t dc_get_eps_10_data(DATA_CACHE_EPS_10_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_10_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_10_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_10_t));
}

void dc_set_eps_10_data(DATA_CACHE_EPS_10_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_10_DATA, p_new_data, sizeof(DATA_CACHE_EPS_10_t));
}

dc_data_status_t dc_get_eps_14_data(DATA_CACHE_EPS_14_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS_14_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EPS_14_t),
                           0U,
                           sizeof(DATA_CACHE_EPS_14_t));
}

void dc_set_eps_14_data(DATA_CACHE_EPS_14_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS_14_DATA, p_new_data, sizeof(DATA_CACHE_EPS_14_t));
}

dc_data_status_t dc_get_sensor_acc_primary_data(DATA_CACHE_SENSOR_ACC_PRIMARY_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_ACC_PRIMARY_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_t));
}

void dc_set_sensor_acc_primary_data(DATA_CACHE_SENSOR_ACC_PRIMARY_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_ACC_PRIMARY_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_t));
}

dc_data_status_t dc_get_sensor_acc_secondary_data(DATA_CACHE_SENSOR_ACC_SECONDARY_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_ACC_SECONDARY_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_t));
}

void dc_set_sensor_acc_secondary_data(DATA_CACHE_SENSOR_ACC_SECONDARY_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_ACC_SECONDARY_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_t));
}

dc_data_status_t dc_get_sensor_acc_primary_sat_frame_data(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t));
}

void dc_set_sensor_acc_primary_sat_frame_data(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t));
}

dc_data_status_t dc_get_sensor_acc_secondary_sat_frame_data(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t));
}

void dc_set_sensor_acc_secondary_sat_frame_data(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t));
}

dc_data_status_t dc_get_sensor_panel_temp_data(DATA_CACHE_SENSOR_PANEL_TEMP_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_PANEL_TEMP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_t));
}

void dc_set_sensor_panel_temp_data(DATA_CACHE_SENSOR_PANEL_TEMP_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_PANEL_TEMP_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_t));
}

dc_data_status_t dc_get_sensor_panel_temp_sat_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_PANEL_TEMP_SAT_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t));
}

void dc_set_sensor_panel_temp_sat_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_PANEL_TEMP_SAT_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t));
}

dc_data_status_t dc_get_sensor_gyro_temp_data(DATA_CACHE_SENSOR_GYRO_TEMP_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_GYRO_TEMP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_t));
}

void dc_set_sensor_gyro_temp_data(DATA_CACHE_SENSOR_GYRO_TEMP_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_GYRO_TEMP_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_t));
}

dc_data_status_t dc_get_sensor_gyro_temp_sat_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_SENSOR_GYRO_TEMP_SAT_FRAME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t),
                           0U,
                           sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t));
}

void dc_set_sensor_gyro_temp_sat_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_SENSOR_GYRO_TEMP_SAT_FRAME_DATA, p_new_data, sizeof(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t));
}

void dc_set_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t));
}

void dc_set_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t));
}

dc_data_status_t dc_get_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_data)
{
    return dc_get_raw_data(DC_DID_AOCS_CNTRL_REF_PARAMS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t),
                           0U,
                           sizeof(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t));
}

void dc_set_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_AOCS_CNTRL_REF_PARAMS_DATA, p_new_data, sizeof(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_166_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_166_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_167_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_167_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_168_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_168_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_169_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_169_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_170_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_170_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_171_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_171_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_172_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_172_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_173_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_173_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_174_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_174_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_175_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_175_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_176_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_176_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_177_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_177_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_178_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_178_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_179_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_179_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_180_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_180_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_203_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_203_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_204_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_204_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_205_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_205_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_206_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_206_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_207_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_207_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_209_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_209_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_210_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_210_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_211_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_211_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_212_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_212_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_213_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_213_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_214_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_214_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_216_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_216_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_217_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_217_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_218_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_218_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_225_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_225_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_226_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_226_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t));
}

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_data)
{
    return dc_get_raw_data(DC_DID_CUBEADCS_GEN2_TLM_FRAME_165_DATA,
                           p_data,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t),
                           0U,
                           sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t));
}

void dc_set_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_CUBEADCS_GEN2_TLM_FRAME_165_DATA, p_new_data, sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t));
}

dc_data_status_t dc_get_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_data)
{
    return dc_get_raw_data(DC_DID_GNSS_TIME_DATA,
                           p_data,
                           sizeof(DATA_CACHE_GNSS_TIME_t),
                           0U,
                           sizeof(DATA_CACHE_GNSS_TIME_t));
}

void dc_set_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_GNSS_TIME_DATA, p_new_data, sizeof(DATA_CACHE_GNSS_TIME_t));
}

dc_data_status_t dc_get_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_data)
{
    return dc_get_raw_data(DC_DID_GNSS_BESTXYZ_DATA,
                           p_data,
                           sizeof(DATA_CACHE_GNSS_BESTXYZ_t),
                           0U,
                           sizeof(DATA_CACHE_GNSS_BESTXYZ_t));
}

void dc_set_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_GNSS_BESTXYZ_DATA, p_new_data, sizeof(DATA_CACHE_GNSS_BESTXYZ_t));
}

dc_data_status_t dc_get_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPSOVERALLBATTERYINFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_EpsOverallBatteryInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_EpsOverallBatteryInfoType_t));
}

void dc_set_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPSOVERALLBATTERYINFO_DATA, p_new_data, sizeof(DATA_CACHE_EpsOverallBatteryInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BP_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BatteryInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BatteryInfoType_t));
}

void dc_set_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BP_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BatteryInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t));
}

void dc_set_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors1Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors1Type_t));
}

void dc_set_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0InaSensors1Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors2Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0InaSensors2Type_t));
}

void dc_set_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0InaSensors2Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerInfoType_t));
}

void dc_set_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BalancerInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerStatusType_t));
}

void dc_set_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BalancerStatusType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t));
}

void dc_set_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXpType_t));
}

void dc_set_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerXpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerXrType_t));
}

void dc_set_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerXrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYpType_t));
}

void dc_set_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerYpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerYrType_t));
}

void dc_set_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerYrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZpType_t));
}

void dc_set_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerZpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst0ChargerZrType_t));
}

void dc_set_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst0ChargerZrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_bp_info_data(DATA_CACHE_Eps2Inst1BatteryInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_BP_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1BatteryInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1BatteryInfoType_t));
}

void dc_set_eps2_bp_inst1_bp_info_data(DATA_CACHE_Eps2Inst1BatteryInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_BP_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1BatteryInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_device_health_info_data(DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t));
}

void dc_set_eps2_bp_inst1_device_health_info_data(DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_ina_sensor1_data(DATA_CACHE_Eps2Inst1InaSensors1Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_INA_SENSOR1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1InaSensors1Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1InaSensors1Type_t));
}

void dc_set_eps2_bp_inst1_ina_sensor1_data(DATA_CACHE_Eps2Inst1InaSensors1Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_INA_SENSOR1_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1InaSensors1Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_ina_sensor2_data(DATA_CACHE_Eps2Inst1InaSensors2Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_INA_SENSOR2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1InaSensors2Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1InaSensors2Type_t));
}

void dc_set_eps2_bp_inst1_ina_sensor2_data(DATA_CACHE_Eps2Inst1InaSensors2Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_INA_SENSOR2_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1InaSensors2Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_balancer_info_data(DATA_CACHE_Eps2Inst1BalancerInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_BALANCER_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1BalancerInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1BalancerInfoType_t));
}

void dc_set_eps2_bp_inst1_balancer_info_data(DATA_CACHE_Eps2Inst1BalancerInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_BALANCER_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1BalancerInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_balancer_status_data(DATA_CACHE_Eps2Inst1BalancerStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_BALANCER_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1BalancerStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1BalancerStatusType_t));
}

void dc_set_eps2_bp_inst1_balancer_status_data(DATA_CACHE_Eps2Inst1BalancerStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_BALANCER_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1BalancerStatusType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_balancer_cells_info_data(DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t));
}

void dc_set_eps2_bp_inst1_balancer_cells_info_data(DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_charger_xp_data(DATA_CACHE_Eps2Inst1ChargerXpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_CHARGER_XP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerXpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerXpType_t));
}

void dc_set_eps2_bp_inst1_charger_xp_data(DATA_CACHE_Eps2Inst1ChargerXpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_XP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1ChargerXpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_charger_xr_data(DATA_CACHE_Eps2Inst1ChargerXrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_CHARGER_XR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerXrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerXrType_t));
}

void dc_set_eps2_bp_inst1_charger_xr_data(DATA_CACHE_Eps2Inst1ChargerXrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_XR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1ChargerXrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_charger_yp_data(DATA_CACHE_Eps2Inst1ChargerYpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_CHARGER_YP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerYpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerYpType_t));
}

void dc_set_eps2_bp_inst1_charger_yp_data(DATA_CACHE_Eps2Inst1ChargerYpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_YP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1ChargerYpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_charger_yr_data(DATA_CACHE_Eps2Inst1ChargerYrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_CHARGER_YR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerYrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerYrType_t));
}

void dc_set_eps2_bp_inst1_charger_yr_data(DATA_CACHE_Eps2Inst1ChargerYrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_YR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1ChargerYrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_charger_zp_data(DATA_CACHE_Eps2Inst1ChargerZpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_CHARGER_ZP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerZpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerZpType_t));
}

void dc_set_eps2_bp_inst1_charger_zp_data(DATA_CACHE_Eps2Inst1ChargerZpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_ZP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1ChargerZpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst1_charger_zr_data(DATA_CACHE_Eps2Inst1ChargerZrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST1_CHARGER_ZR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerZrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst1ChargerZrType_t));
}

void dc_set_eps2_bp_inst1_charger_zr_data(DATA_CACHE_Eps2Inst1ChargerZrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST1_CHARGER_ZR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst1ChargerZrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_bp_info_data(DATA_CACHE_Eps2Inst2BatteryInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_BP_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2BatteryInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2BatteryInfoType_t));
}

void dc_set_eps2_bp_inst2_bp_info_data(DATA_CACHE_Eps2Inst2BatteryInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_BP_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2BatteryInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_device_health_info_data(DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t));
}

void dc_set_eps2_bp_inst2_device_health_info_data(DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_ina_sensor1_data(DATA_CACHE_Eps2Inst2InaSensors1Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_INA_SENSOR1_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2InaSensors1Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2InaSensors1Type_t));
}

void dc_set_eps2_bp_inst2_ina_sensor1_data(DATA_CACHE_Eps2Inst2InaSensors1Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_INA_SENSOR1_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2InaSensors1Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_ina_sensor2_data(DATA_CACHE_Eps2Inst2InaSensors2Type_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_INA_SENSOR2_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2InaSensors2Type_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2InaSensors2Type_t));
}

void dc_set_eps2_bp_inst2_ina_sensor2_data(DATA_CACHE_Eps2Inst2InaSensors2Type_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_INA_SENSOR2_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2InaSensors2Type_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_balancer_info_data(DATA_CACHE_Eps2Inst2BalancerInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_BALANCER_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2BalancerInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2BalancerInfoType_t));
}

void dc_set_eps2_bp_inst2_balancer_info_data(DATA_CACHE_Eps2Inst2BalancerInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_BALANCER_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2BalancerInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_balancer_status_data(DATA_CACHE_Eps2Inst2BalancerStatusType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_BALANCER_STATUS_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2BalancerStatusType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2BalancerStatusType_t));
}

void dc_set_eps2_bp_inst2_balancer_status_data(DATA_CACHE_Eps2Inst2BalancerStatusType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_BALANCER_STATUS_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2BalancerStatusType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_balancer_cells_info_data(DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t));
}

void dc_set_eps2_bp_inst2_balancer_cells_info_data(DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_charger_xp_data(DATA_CACHE_Eps2Inst2ChargerXpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_CHARGER_XP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerXpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerXpType_t));
}

void dc_set_eps2_bp_inst2_charger_xp_data(DATA_CACHE_Eps2Inst2ChargerXpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_XP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2ChargerXpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_charger_xr_data(DATA_CACHE_Eps2Inst2ChargerXrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_CHARGER_XR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerXrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerXrType_t));
}

void dc_set_eps2_bp_inst2_charger_xr_data(DATA_CACHE_Eps2Inst2ChargerXrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_XR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2ChargerXrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_charger_yp_data(DATA_CACHE_Eps2Inst2ChargerYpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_CHARGER_YP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerYpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerYpType_t));
}

void dc_set_eps2_bp_inst2_charger_yp_data(DATA_CACHE_Eps2Inst2ChargerYpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_YP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2ChargerYpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_charger_yr_data(DATA_CACHE_Eps2Inst2ChargerYrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_CHARGER_YR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerYrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerYrType_t));
}

void dc_set_eps2_bp_inst2_charger_yr_data(DATA_CACHE_Eps2Inst2ChargerYrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_YR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2ChargerYrType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_charger_zp_data(DATA_CACHE_Eps2Inst2ChargerZpType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_CHARGER_ZP_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerZpType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerZpType_t));
}

void dc_set_eps2_bp_inst2_charger_zp_data(DATA_CACHE_Eps2Inst2ChargerZpType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_ZP_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2ChargerZpType_t));
}

dc_data_status_t dc_get_eps2_bp_inst2_charger_zr_data(DATA_CACHE_Eps2Inst2ChargerZrType_t * const p_data)
{
    return dc_get_raw_data(DC_DID_EPS2_BP_INST2_CHARGER_ZR_DATA,
                           p_data,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerZrType_t),
                           0U,
                           sizeof(DATA_CACHE_Eps2Inst2ChargerZrType_t));
}

void dc_set_eps2_bp_inst2_charger_zr_data(DATA_CACHE_Eps2Inst2ChargerZrType_t * const p_new_data)
{
    dc_set_raw_data(DC_DATA_INPUT_INTERNAL, DC_DID_EPS2_BP_INST2_CHARGER_ZR_DATA, p_new_data, sizeof(DATA_CACHE_Eps2Inst2ChargerZrType_t));
}

