/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*
 * datapool_types.h
 *
 *  Created on: Jun 25, 2021
 *      Author: Ivan Petrov
 */

#ifndef NVM_INC_NVM_APP_TYPES_H_
#define NVM_INC_NVM_APP_TYPES_H_

#include "es_cdef.h"
#include "nvm_bootcfg/inc/nvm_boot_types.h"
#include "datacache.h"
#include "fp/ConOps/v0.2/ConOps_server/FP_ConOpsProtocolTypes.h"
#include "fp/time/v0.1/time_server/FP_timeProtocolTypes.h"
#include "es_adcs_types.h"
#include "es_coordsys_types.h"
#include "sds_events_types.h"
#include "adis16265_driver.h"
#include "aocs_pm.h"
#include "external/fatfs/ff.h"
#include "../../../arch/stm32h753iit/drivers/positioning/libcubeadcs/inc/cubeadcs_tc_tlm_descr.h"
#include "../../../arch/stm32h753iit/drivers/positioning/libcubeadcs/cfg/cubeadcs_sysstate_cfg.h"
#include "../../../core/services/aocs/cubeadcs_gen2/inc/cubeadcs_gen2_types.h"
#include "../../../core/services/aocs/cubeadcs_gen2/inc/cubeadcs_gen2_sys_states.h"
#include "../../../core/services/aocs/cubeadcs_gen2/inc/cubeadcs_gen2_tlm.h"
#include "../../../arch/stm32h753iit/drivers/arm_fault_handler/inc/arm_fault_handler.h"

#include "fp/nvm_bp/v0.1/nvm_bp_server/FP_nvm_bpProtocolTypes.h"

#define NVM_BLOCK_DEFINE_START(blockType)    typedef struct {
#define NVM_BLOCK_DEFINE_END(blockType)      uint32_t u32Crc; \
                                             } blockType;

#pragma pack(push)
#pragma pack(1)

/** @brief Number of allocated NVM fault blocks */
#define MAX_FAULT_BLOCKS_CNT (5U)

/** @brief Number of preallocated slots for beacon messages.
 *
 * A DataCache entry type can be associated to any of those slots for transmission inside beacon frames.
 */
#ifndef MAX_BEACON_MSG_SLOTS
#define MAX_BEACON_MSG_SLOTS            (20U)
#endif

/** @brief Maximum number of presets to keep as different becon slot configurations which can be changed
 *            at runtime. Usually this is tied to the operational modes but different naming is kept here for better
 *            abstraction.
 */
#ifndef BEACON_PRESETS_COUNT
#define BEACON_PRESETS_COUNT            (4U)
#endif

/** @brief This number denotes an invalid becaon slot assignment */
#define INVALID_BEACON_SLOT_ASSIGNMENT    (0xFFFFU)

/** @brief This number denotes an invalid telemetry slot assignment */
#define INVALID_TLM_SLOT_ASSIGNMENT        (0xFFFFU)

/** @brief Maximum number of presets to keep as different telemetry slot configurations which can be changed
 *            at runtime. Usually this is tied to the operational modes but different naming is kept here for better
 *            abstraction.
 */
#ifndef TELEMETRY_PRESETS_COUNT
#define TELEMETRY_PRESETS_COUNT                    (4U)
#endif

/** @brief Maximum number of configurable telemetry entries for each individual preset.
 */
#ifndef TELEMETRY_MAX_CONFIGURABLE_ENTRIES
#define TELEMETRY_MAX_CONFIGURABLE_ENTRIES      (10U)
#endif

typedef struct
{
    uint16_t data_id;        /**< DataCache-specified identifier */
    bool active;             /**< A flag indicating whether the data_id is part of the telemtry collection for this preset */
    uint16_t acq_period;    /**< data acquistion period from the DataCache in sec */
} tlm_preset_cfg_t;

typedef enum
{
    TLM_FILE_CFG_TYPE_SIZE_LIMIT,
    TLM_FILE_CFG_TYPE_TIME_LIMIT,
    TLM_FILE_CFG_TYPE_MAX
} tlm_file_cfg_type_t;

typedef struct
{
    bool pull_up_4k7;
    bool pull_up_10k;
} bus_pull_up_state_t;

typedef enum
{
    I2C_BUS_SYSTEM,
    I2C_BUS_PAYLOAD,
    I2C_BUS_MAX
} i2c_bus_t;

/** @brief MAC addresses for any external modules
 */

enum
{
    MAC_ADDR_EPS_I,
    MAC_ADDR_EPS_II_BP,
    MAC_ADDR_EPS_II_PDM,
    MAC_ADDR_UHF,
    MAC_ADDR_SBAND_TMTC,
    MAC_ADDR_SP1,
    MAC_ADDR_SP2,
    MAC_ADDR_SP3,
    MAC_ADDR_SP4,
    MAC_ADDR_PAYLOAD_1,
    MAC_ADDR_PAYLOAD_2,
    MAC_ADDR_RESERVED_1,
    MAC_ADDR_RESERVED_2,
    MAC_ADDR_RESERVED_3,
    MAC_ADDR_RESERVED_4,
    MAC_ADDR_BOOK_MAX
};

/** @brief Number of values defining the Y-Thomson range
 *
 */
#ifndef CONOPS_Y_THOMSON_RANGE
#define CONOPS_Y_THOMSON_RANGE            (2U)
#endif

// Note: ensure this parameter is aligned to the maximum value in FRESULT enum
#define FFAPIERR_MAX_CNT          (FR_INVALID_PARAMETER + 1)

TODO("This should come from the FP types")
#define OBC_CUBEADCS_GEN2_SYS_STATES_MAX (14)

NVM_BLOCK_DEFINE_START(reserved_dummy_t)
    uint8_t dummy;
NVM_BLOCK_DEFINE_END(reserved_dummy_t)

NVM_BLOCK_DEFINE_START(beacons_cfg_t)
    safe_bool_t beacons_en;
    safe_bool_t chunk_based_transfer_en;
    uint32_t bcn_tx_period;
    uint32_t bcn_inter_frame_period;
NVM_BLOCK_DEFINE_END(beacons_cfg_t)

NVM_BLOCK_DEFINE_START(beacons_presets_cfg_t)
    uint16_t beacon_slots_setting[BEACON_PRESETS_COUNT][MAX_BEACON_MSG_SLOTS];
NVM_BLOCK_DEFINE_END(beacons_presets_cfg_t)

NVM_BLOCK_DEFINE_START(ConOpsConfig_t)
    CONOPS_ThresholdValues_t cfg;
NVM_BLOCK_DEFINE_END(ConOpsConfig_t)

NVM_BLOCK_DEFINE_START(conops_idle_pointreq_cfg_t)
    safe_bool_t en_sun_tracking;
NVM_BLOCK_DEFINE_END(conops_idle_pointreq_cfg_t)

NVM_BLOCK_DEFINE_START(telemetry_cfg_t)
    safe_bool_t telemetry_en;
    safe_bool_t file_telemetry_en;
NVM_BLOCK_DEFINE_END(telemetry_cfg_t)

NVM_BLOCK_DEFINE_START(telemetry_preset_cfg_t)
    tlm_preset_cfg_t tlm_slots_setting[TELEMETRY_PRESETS_COUNT][TELEMETRY_MAX_CONFIGURABLE_ENTRIES];
NVM_BLOCK_DEFINE_END(telemetry_preset_cfg_t)

NVM_BLOCK_DEFINE_START(telemetry_file_cfg_t)
    tlm_file_cfg_type_t    cfg_type;    /**< Active configuration type for file-based storage of telemetry data */
    uint32_t size_limit_kb;            /**< Maximum size limit for all telemetry logged on the SD card */
    uint16_t max_log_files_cnt;        /**< Number of individual files to split the log to */
    uint32_t time_limit_sec;        /**< Maximum number of seconds of recent telemetry data to keep in the storage */
    uint16_t file_size_limit_kb;    /**< Maximum size of individual log files */
NVM_BLOCK_DEFINE_END(telemetry_file_cfg_t)

NVM_BLOCK_DEFINE_START(EPS_M_Config_t)
    safe_bool_t reserved1;
    safe_bool_t reserved2;
    safe_bool_t reserved3;
    safe_bool_t reserved4;
    safe_bool_t reserved5;
    safe_bool_t reserved6;
    int16_t     reserved7;
    safe_bool_t reserved8;
    safe_bool_t reserved9;
NVM_BLOCK_DEFINE_END(EPS_M_Config_t)

NVM_BLOCK_DEFINE_START(cubeadcs_err_handl_cfg_t)
    safe_bool_t en_cubeadcs_err_handl;
NVM_BLOCK_DEFINE_END(cubeadcs_err_handl_cfg_t)

NVM_BLOCK_DEFINE_START(cubeadcs_status_t)
    uint8_t   commissioning;
    uint8_t   node_status;
    uint16_t  runtime_latched_errors;
NVM_BLOCK_DEFINE_END(cubeadcs_status_t)

NVM_BLOCK_DEFINE_START(i2c_config_t)
    /**< I2C resistor pull-ups configuration
     *      - each entry of the array corresponds to an I2C bus
     * */
    bus_pull_up_state_t i2c_pull_up_config[I2C_BUS_MAX];
NVM_BLOCK_DEFINE_END(i2c_config_t)

NVM_BLOCK_DEFINE_START(cubeadcs_angle_limits_t)
    int32_t   stable_pointing_threshold_angle; /* Value is in millidegrees to allow the use of integers for fine precision */
    int32_t   stable_pointing_threshold_angle_rate; /* Value is in millidegrees to allow to allow the use of integers for fine precision */
NVM_BLOCK_DEFINE_END(cubeadcs_angle_limits_t)

NVM_BLOCK_DEFINE_START(aocs_pm_config_t)
	aocs_pm_parameters_t parameters;
NVM_BLOCK_DEFINE_END(aocs_pm_config_t)

NVM_BLOCK_DEFINE_START(aocs_pm_thresholds_t)
	aocs_pm_threshold_values_t value[3];
NVM_BLOCK_DEFINE_END(aocs_pm_thresholds_t)

NVM_BLOCK_DEFINE_START(sds_sens_read_freq_t)
	safe_bool_t enable;
	sds_events_cfg_t sens_cfg[SDS_SENSTYPE_MAX_CNT];
NVM_BLOCK_DEFINE_END(sds_sens_read_freq_t)

#define AES_KEY_SIZE_BYTES  (32U)

NVM_BLOCK_DEFINE_START(crypto_cfg_t)
    uint8_t aes_key[AES_KEY_SIZE_BYTES];
NVM_BLOCK_DEFINE_END(crypto_cfg_t)

NVM_BLOCK_DEFINE_START(cubeadcs_sim_mode_t)
    safe_bool_t en_sim_mode;
NVM_BLOCK_DEFINE_END(cubeadcs_sim_mode_t)

NVM_BLOCK_DEFINE_START(rtc_calib_data_t)
    uint16_t calm;
    TIME_calp_pulses_t calp;
NVM_BLOCK_DEFINE_END(rtc_calib_data_t)

NVM_BLOCK_DEFINE_START(gyroscope_configs_t)
    gyroscope_t gyroscopeArray[3];
NVM_BLOCK_DEFINE_END(gyroscope_configs_t)

NVM_BLOCK_DEFINE_START(ff_stats_t)
    uint16_t ff_api_err_counters[FFAPIERR_MAX_CNT];
NVM_BLOCK_DEFINE_END(ff_stats_t)

NVM_BLOCK_DEFINE_START(cubeADCS_sys_state_cfg_t)
	CubeADCS_Cfg_t asCubeADCS_SysStates[eCUBEADCS_CFGTYPE_NUMBER];
NVM_BLOCK_DEFINE_END(cubeADCS_sys_state_cfg_t)

NVM_BLOCK_DEFINE_START(mac_address_book_t)
    uint8_t a_mac_address [MAC_ADDR_BOOK_MAX];
    uint8_t a_eps_batterypack_addresses[NVM_BP_EPSBPIDTYPE_MAX_CNT];
NVM_BLOCK_DEFINE_END(mac_address_book_t)

NVM_BLOCK_DEFINE_START(cubeadcs_gen2_sys_states_cfg_t)
    cubeadcs_gen2_sys_state_core_t sys_state_cfg[OBC_CUBEADCS_GEN2_SYS_STATES_MAX];
NVM_BLOCK_DEFINE_END(cubeadcs_gen2_sys_states_cfg_t)

NVM_BLOCK_DEFINE_START(cubeadcs_gen2_tlm_cfg_t)
    bool mask[CUBEADCS_GEN2_TLM_MASK_MAX][CUBEADCS_GEN2_TLM_MASK_BYTES_MAX];
NVM_BLOCK_DEFINE_END(cubeadcs_gen2_tlm_cfg_t)

NVM_BLOCK_DEFINE_START(adcs_cms_status_t)
    uint8_t cms_status;
NVM_BLOCK_DEFINE_END(adcs_cms_status_t)

NVM_BLOCK_DEFINE_START(fault_index_t)
uint8_t next_free_slot_index; /*<< Fault NVM block index to which the next write will take place */
uint8_t free_slots;           /*<< Number of free fault block slots available */
NVM_BLOCK_DEFINE_END(fault_index_t)

NVM_BLOCK_DEFINE_START(fault_block_t)
persisted_ram_x_frame_t x_frame; /*<< Exception frame data */
NVM_BLOCK_DEFINE_END(fault_block_t)

#pragma pack(pop)

#endif /* NVM_INC_NVM_APP_TYPES_H_ */
