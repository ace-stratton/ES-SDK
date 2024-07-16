/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup cubeadcs_gen2
 * @{
 *
 * @file     cubeadcs_gen2_tlm.c
 * @brief    Cubeadcs Gen2 telemetry source.
 *
 * @}
 */

#include "cubeadcs_gen2_tlm.h"
#include "cubeadcs_gen2_gw.h"

#include "assertions.h"
#include "es_exeh.h"
#include "nvm.h"

#include "datacache.h"

/** @typedef p_tlm_api_handl_t
 *  @brief Function pointer to a telemetry frame API and handler
 */
typedef void(*p_tlm_api_handl_t)(void);

STATIC void fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubenode_pst3s(void);
STATIC void fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubemag_magnetometer(void);
STATIC void fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubesense_sun(void);
STATIC void fs_cubeadcs_gen2_tlm_get_torquer_current_measurements(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_cubesense_sun_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_external_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_controller_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_backup_estimator_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_models_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_gnss_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_hss_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_mag_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_fss_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_cubesense_earth_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_mag_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_css_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_gyr_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_rwl_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_css_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_gyr_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_str_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_rwl_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_main_estimator_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_main_estimator_high_resolution_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_gnss_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_pst3s_star_tracker_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_acp_execution_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_cubecomputer_health(void);
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubesense_earth(void);
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_reaction_wheels(void);
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubenode_nssrwl(void);
STATIC void fs_cubeadcs_gen2_tlm_get_raw_nssrwl_sensor_telemetry(void);
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubestar(void);

/** @brief 2D array of function pointers to telemetry frames */
const p_tlm_api_handl_t tlm_api_handl[CUBEADCS_GEN2_TLM_MASK_MAX][CUBEADCS_GEN2_TLM_MASK_BYTES_MAX] =
{
        // Mask Byte 0
        {
         fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubenode_pst3s,
         fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubemag_magnetometer,
         fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubesense_sun,
         fs_cubeadcs_gen2_tlm_get_torquer_current_measurements,
         fs_cubeadcs_gen2_tlm_get_raw_cubesense_sun_telemetry,
         fs_cubeadcs_gen2_tlm_get_raw_external_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_controller_telemetry,
         fs_cubeadcs_gen2_tlm_get_backup_estimator_telemetry,
        },
        // Mask Byte 1
        {
         fs_cubeadcs_gen2_tlm_get_models_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_gnss_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_hss_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_mag_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_fss_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_raw_cubesense_earth_telemetry,
         fs_cubeadcs_gen2_tlm_get_raw_mag_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_raw_css_sensor_telemetry,
        },
        // Mask Byte 2
        {
         fs_cubeadcs_gen2_tlm_get_raw_gyr_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_raw_rwl_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_css_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_gyr_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_str_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_calibrated_rwl_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_main_estimator_telemetry,
         fs_cubeadcs_gen2_tlm_get_main_estimator_high_resolution_telemetry,
        },
        // Mask Byte 3
        {
         fs_cubeadcs_gen2_tlm_get_raw_gnss_sensor_telemetry,
         fs_cubeadcs_gen2_tlm_get_raw_pst3s_star_tracker_telemetry,
         fs_cubeadcs_gen2_tlm_get_acp_execution_telemetry,
         fs_cubeadcs_gen2_tlm_get_cubecomputer_health,
         fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubesense_earth,
         fs_cubeadcs_gen2_tlm_get_health_telemetry_for_reaction_wheels,
         fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubenode_nssrwl,
         fs_cubeadcs_gen2_tlm_get_raw_nssrwl_sensor_telemetry,
        },
        // Mask Byte 4
        {
         fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubestar,
         NULL,
         NULL,
         NULL,
         NULL,
         NULL,
         NULL,
         NULL,
        }
};

void cubeadcs_gen2_tlm_get_tlm(void)
{
    cubeadcs_gen2_tlm_cfg_t tlm_cfg;

    Nvm_GetBlockById(NVM_BLOCK_CUBEADCS_GEN2_TLM_CFG, (void *)&tlm_cfg);

    for (uint8_t byte = 0; byte < CUBEADCS_GEN2_TLM_MASK_MAX; byte++)
    {
        for (uint8_t mask = 0; mask < CUBEADCS_GEN2_TLM_MASK_BYTES_MAX; mask++)
        {
            if ( (NULL != tlm_api_handl[byte][mask]) &&
                 (true == tlm_cfg.mask[byte][mask]))
            {
                tlm_api_handl[byte][mask]();
            }
        }
    }
}

/** @brief Getter for telemetry frame 166 - Health telemetry for CubeNode PST3S */
STATIC void fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubenode_pst3s(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmStrPst3sHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t));

    TctlmCubeComputerControlProgram8_TlmStrPst3sHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_166_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 167 - Health telemetry for CubeMag magnetometer */
STATIC void fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubemag_magnetometer(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmCubeMagHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t));

    TctlmCubeComputerControlProgram8_TlmCubeMagHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeMagHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_167_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 168 - Health telemetry for CubeSense Sun */
STATIC void fs_cubeadcs_gen2_tlm_get_health_tlm_for_cubesense_sun(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t));

    TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_168_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 169 - Torquer Current measurements */
STATIC void fs_cubeadcs_gen2_tlm_get_torquer_current_measurements(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmTorquerCurrents) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t));

    TctlmCubeComputerControlProgram8_TlmTorquerCurrents tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmTorquerCurrentsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_169_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 170 - Raw CubeSense Sun telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_cubesense_sun_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunRaw) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t));

    TctlmCubeComputerControlProgram8_TlmFssCubeSenseSunRaw tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmFssCubeSenseSunRawRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_170_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 171 - Raw external sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_external_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmExtSensorRaw) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t));

    TctlmCubeComputerControlProgram8_TlmExtSensorRaw tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmExtSensorRawRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_171_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 172 - Controller telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_controller_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmController) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t));

    TctlmCubeComputerControlProgram8_TlmController tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmControllerRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_172_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 173 - Backup estimator telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_backup_estimator_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorBackup) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t));

    TctlmCubeComputerControlProgram8_TlmEstimatorBackup tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorBackupRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_173_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 174 - Models telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_models_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmModels) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t));

    TctlmCubeComputerControlProgram8_TlmModels tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmModelsRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_174_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 175 - Calibrated GNSS sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_gnss_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalGnss) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t));

    TctlmCubeComputerControlProgram8_TlmSensorCalGnss tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGnssRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_175_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 176 - Calibrated HSS sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_hss_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalHss) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t));

    TctlmCubeComputerControlProgram8_TlmSensorCalHss tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalHssRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_176_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 177 - Calibrated MAG sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_mag_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalMag) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t));

    TctlmCubeComputerControlProgram8_TlmSensorCalMag tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalMagRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_177_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 178 - Calibrated FSS sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_fss_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalFss) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t));

    TctlmCubeComputerControlProgram8_TlmSensorCalFss tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalFssRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_178_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 179 - Raw CubeSense Earth telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_cubesense_earth_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthRaw) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t));

    TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthRaw tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthRawRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_179_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 180 - Raw MAG sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_mag_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawMag) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t));

    TctlmCubeComputerControlProgram8_TlmSensorRawMag tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawMagRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_180_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 203 - Raw CSS sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_css_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawCss) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t));

    TctlmCubeComputerControlProgram8_TlmSensorRawCss tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawCssRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_203_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 204 - Raw GYR sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_gyr_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawGyro) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t));

    TctlmCubeComputerControlProgram8_TlmSensorRawGyro tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawGyroRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_204_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 205 - Raw RWL sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_rwl_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorRawRwl) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t));

    TctlmCubeComputerControlProgram8_TlmSensorRawRwl tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorRawRwlRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_205_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 206 - Calibrated CSS sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_css_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalCss) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t));

    TctlmCubeComputerControlProgram8_TlmSensorCalCss tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalCssRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_206_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 207 - Calibrated GYR sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_gyr_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalGyro) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t));

    TctlmCubeComputerControlProgram8_TlmSensorCalGyro tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalGyroRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_207_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 208 - Calibrated STR sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_str_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalStr) == (sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t) + sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t)));

    TctlmCubeComputerControlProgram8_TlmSensorCalStr tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalStrRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_208_1_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t *)&tlm);

        dc_set_cubeadcs_gen2_tlm_frame_208_2_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t *)&tlm.str1MeasBodyVec0X);
    }
}

/** @brief Getter for telemetry frame 209 - Calibrated RWL sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_calibrated_rwl_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmSensorCalRwl) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t));

    TctlmCubeComputerControlProgram8_TlmSensorCalRwl tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmSensorCalRwlRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_209_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 210 - Main estimator telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_main_estimator_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorMain) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t));

    TctlmCubeComputerControlProgram8_TlmEstimatorMain tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_210_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 211 - Main estimator high-resolution telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_main_estimator_high_resolution_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmEstimatorMainHighRes) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t));

    TctlmCubeComputerControlProgram8_TlmEstimatorMainHighRes tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmEstimatorMainHighResRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_211_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 212 - Raw GNSS sensor telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_gnss_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmGnssRaw) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t));

    TctlmCubeComputerControlProgram8_TlmGnssRaw tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmGnssRawRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_212_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 213 - Raw PST3S star tracker telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_raw_pst3s_star_tracker_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmStrPst3sRaw) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t));

    TctlmCubeComputerControlProgram8_TlmStrPst3sRaw tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrPst3sRawRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_213_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 214 - ACP execution telemetry */
STATIC void fs_cubeadcs_gen2_tlm_get_acp_execution_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmAcpExecution) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t));

    TctlmCubeComputerControlProgram8_TlmAcpExecution tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmAcpExecutionRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_214_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 216 - CubeComputer Health */
STATIC void fs_cubeadcs_gen2_tlm_get_cubecomputer_health(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmCubeComputerHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t));

    TctlmCubeComputerControlProgram8_TlmCubeComputerHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmCubeComputerHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_216_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 217 - Health telemetry for CubeSense Earth */
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubesense_earth(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t));

    TctlmCubeComputerControlProgram8_TlmHssCubeSenseEarthHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmHssCubeSenseEarthHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_217_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 218 - Health telemetry for Reaction Wheels */
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_reaction_wheels(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmRwlHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t));

    TctlmCubeComputerControlProgram8_TlmRwlHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_218_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 225 - Health telemetry for CubeNode NSSRWL*/
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubenode_nssrwl(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmNssRwlHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t));

    TctlmCubeComputerControlProgram8_TlmNssRwlHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmNssRwlHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_225_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 226 - Raw NSSRWL sensor telemetry*/
STATIC void fs_cubeadcs_gen2_tlm_get_raw_nssrwl_sensor_telemetry(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmRwlNssRwlRaw) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t));

    TctlmCubeComputerControlProgram8_TlmRwlNssRwlRaw tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmRwlNssRwlRawRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_226_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t *)&tlm);
    }
}

/** @brief Getter for telemetry frame 165 - Health telemetry for CubeStar*/
STATIC void fs_cubeadcs_gen2_tlm_get_health_telemetry_for_cubestar(void)
{
    static_assert(sizeof(TctlmCubeComputerControlProgram8_TlmStrHealth) == sizeof(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t));

    TctlmCubeComputerControlProgram8_TlmStrHealth tlm;

    if (CUBEOBC_ERROR_OK == CubeADCS_Gen2_CubeComputerControlProgram8_getTlmStrHealthRequestGw(TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &tlm, CUBEADCS_GEN2_TLM_TIMEOUT))
    {
        dc_set_cubeadcs_gen2_tlm_frame_165_data((DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t *)&tlm);
    }
}
