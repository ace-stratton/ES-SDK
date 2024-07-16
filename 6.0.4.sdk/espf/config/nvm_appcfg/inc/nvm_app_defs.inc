// default telemetry logging period in seconds
#define TLM_LOG_PERIOD_DEF_SEC  (30U)
// individual file size limit for telemetry logging
#define TLM_FILE_SIZE_LIMIT_KB  (50U)
// maximum number of files to allocate for telemetry data
#define TLM_MAX_FILES_CNT       (20)

NVM_BLOCK_DEFAULTS_START(reserved_dummy, reserved_dummy_t)
    0U
NVM_BLOCK_DEFAULTS_END(reserved_dummy, reserved_dummy_t)
NVM_BLOCK_DECL(reserved_dummy, reserved_dummy_t)

NVM_BLOCK_DEFAULTS_START(beacons_cfg, beacons_cfg_t)
    SAFE_TRUE,         // beacons_en
    SAFE_TRUE,         // chunk_based_transfer_en
    30000U,            // bcn_tx_period (in ms)
    500U               // bcn_inter_frame_period (in ms)
NVM_BLOCK_DEFAULTS_END(beacons_cfg, beacons_cfg_t)
NVM_BLOCK_DECL(beacons_cfg, beacons_cfg_t)

NVM_BLOCK_DEFAULTS_START(beacons_presets_cfg, beacons_presets_cfg_t)
    {
        // preset #0 defaults (SAFE mode)
        {
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_OBC_0_DATA,
            DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_ADCS_2_DATA,
            DC_ATTR_ID_ADCS_1_DATA,
            DC_ATTR_ID_ADCS_0_DATA,
            DC_ATTR_ID_SSP_0_DATA,
            DC_ATTR_ID_SSP_1_DATA,
            DC_ATTR_ID_SSP_2_DATA,
            DC_ATTR_ID_OS_TASK_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT
        },
        // preset #1 defaults (IDLE mode)
        {
            DC_ATTR_ID_OBC_0_DATA,
            DC_ATTR_ID_ADCS_1_DATA,
            DC_ATTR_ID_ADCS_2_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_ADCS_0_DATA,
            DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_SSP_0_DATA,
            DC_ATTR_ID_SSP_1_DATA,
            DC_ATTR_ID_SSP_2_DATA,
            DC_ATTR_ID_OS_TASK_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT
        },
        // preset #2 defaults (DETUMBLING mode)
        {
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
            DC_ATTR_ID_ADCS_2_DATA,
            DC_ATTR_ID_OBC_0_DATA,
            DC_ATTR_ID_ADCS_1_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_ADCS_0_DATA,
            DC_ATTR_ID_SSP_0_DATA,
            DC_ATTR_ID_SSP_1_DATA,
            DC_ATTR_ID_SSP_2_DATA,
            DC_ATTR_ID_OS_TASK_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT
        },
        // preset #3 defaults (PAYLOAD mode)
        {
            DC_ATTR_ID_OBC_0_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_ADCS_0_DATA,
            DC_ATTR_ID_ADCS_2_DATA,
            DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
            DC_ATTR_ID_ADCS_1_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            DC_ATTR_ID_SSP_0_DATA,
            DC_ATTR_ID_SSP_1_DATA,
            DC_ATTR_ID_SSP_2_DATA,
            DC_ATTR_ID_OS_TASK_DATA,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT,
            INVALID_BEACON_SLOT_ASSIGNMENT
        },
    }   // beacons_presets_cfg[PRESETS_COUNT][MAX_BEACON_MSG_SLOTS]
NVM_BLOCK_DEFAULTS_END(beacons_presets_cfg, beacons_presets_cfg_t)
NVM_BLOCK_DECL(beacons_presets_cfg, beacons_presets_cfg_t)

NVM_BLOCK_DEFAULTS_START(OpModesConfig, ConOpsConfig_t)
        { // sConOpsConfig.cfg.
            0x0000AFC8, // sConOpsConfig.cfg.i32CSafe
            0x000005DC, // sConOpsConfig.cfg.i32SSafe
            0x000005DC, // sConOpsConfig.cfg.i32SDet
            {
                    0x00000672, // sConOpsConfig.cfg.i32SPay[ 0 ]
                    0x00000672, // sConOpsConfig.cfg.i32SPay[ 1 ]
                    0x00000672, // sConOpsConfig.cfg.i32SPay[ 2 ]
                    0x00000000, // sConOpsConfig.cfg.i32SPay[ 3 ]
                    0x00000000, // sConOpsConfig.cfg.i32SPay[ 4 ]
                    0x00000000, // sConOpsConfig.cfg.i32SPay[ 5 ]
                    0x00000000, // sConOpsConfig.cfg.i32SPay[ 6 ]
                    0x00000000, // sConOpsConfig.cfg.i32SPay[ 7 ]
                    0x00000000, // sConOpsConfig.cfg.i32SPay[ 8 ]
                    0x00000000, // sConOpsConfig.cfg.i32SPay[ 9 ]
            },
            0x000001F4, // sConOpsConfig.cfg.i32AngVelMax
            0x0000002B, // sConOpsConfig.cfg.i32AngVelLow
            {
                    0xFFFFFFDB, // sConOpsConfig.cfg.i32AngVelRange[ 0 ]
                    0xFFFFFFE0, // sConOpsConfig.cfg.i32AngVelRange[ 1 ]
            }
        }
NVM_BLOCK_DEFAULTS_END(OpModesConfig, ConOpsConfig_t)
NVM_BLOCK_DECL(OpModesConfig, ConOpsConfig_t)

NVM_BLOCK_DEFAULTS_START(conops_idle_pointreq_cfg, conops_idle_pointreq_cfg_t)
        SAFE_TRUE // Enable Sun-Tracking
NVM_BLOCK_DEFAULTS_END(conops_idle_pointreq_cfg, conops_idle_pointreq_cfg_t)
NVM_BLOCK_DECL(conops_idle_pointreq_cfg, conops_idle_pointreq_cfg_t)

NVM_BLOCK_DEFAULTS_START(telemetry_cfg, telemetry_cfg_t)
    SAFE_TRUE,         // telemetry_en
    SAFE_TRUE          // file_telemetry_en
NVM_BLOCK_DEFAULTS_END(telemetry_cfg, telemetry_cfg_t)
NVM_BLOCK_DECL(telemetry_cfg, telemetry_cfg_t)

NVM_BLOCK_DEFAULTS_START(telemetry_preset_cfg, telemetry_preset_cfg_t)
    {
      // preset #0 defaults: SAFE mode
      {
          // [0]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [1]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [2]
          {
              DC_ATTR_ID_OBC_0_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [3]
          {
              DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [4]
          {
              DC_ATTR_ID_OS_TASK_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [5]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [6]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [7]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [8]
          {
              DC_ATTR_ID_ADCS_2_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [9]
          {
              DC_ATTR_ID_ADCS_1_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          }
      },
      // preset #1 defaults: IDLE mode
      {
          // [0]
          {
              DC_ATTR_ID_OBC_0_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [1]
          {
              DC_ATTR_ID_ADCS_1_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [2]
          {
              DC_ATTR_ID_ADCS_2_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [3]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [4]
          {
              DC_ATTR_ID_ADCS_0_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [5]
          {
              DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [6]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [7]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [8]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [9]
          {
              DC_ATTR_ID_OS_TASK_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          }
      },
      // preset #2 defaults: DETUMBLING mode
      {
          // [0]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [1]
          {
              DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [2]
          {
              DC_ATTR_ID_ADCS_2_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [3]
          {
              DC_ATTR_ID_OBC_0_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [4]
          {
              DC_ATTR_ID_ADCS_1_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [5]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [6]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [7]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [8]
          {
              DC_ATTR_ID_OS_TASK_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [9]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          }
      },
      // preset #3 defaults: PAYLOAD mode
      {
          // [0]
          {
              DC_ATTR_ID_OBC_0_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [1]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [2]
          {
              DC_ATTR_ID_ADCS_0_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [3]
          {
              DC_ATTR_ID_ADCS_2_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [4]
          {
              DC_ATTR_ID_AOCS_CNTRL_TLM_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [5]
          {
              DC_ATTR_ID_ADCS_1_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [6]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [7]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [8]
          {
              INVALID_TLM_SLOT_ASSIGNMENT,
              // active
              false,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          },
          // [9]
          {
              DC_ATTR_ID_OS_TASK_DATA,
              // active
              true,
              // acq_period in s
              TLM_LOG_PERIOD_DEF_SEC
          }
      },
    }                   // beacons_presets_cfg[PRESETS_COUNT][MAX_BEACON_MSG_SLOTS]
NVM_BLOCK_DEFAULTS_END(telemetry_preset_cfg, telemetry_preset_cfg_t)
NVM_BLOCK_DECL(telemetry_preset_cfg, telemetry_preset_cfg_t)

NVM_BLOCK_DEFAULTS_START(telemetry_file_cfg, telemetry_file_cfg_t)
    TLM_FILE_CFG_TYPE_SIZE_LIMIT,                          // cfg_type
    (TLM_MAX_FILES_CNT * TLM_FILE_SIZE_LIMIT_KB),          // size_limit_kb
    TLM_MAX_FILES_CNT,                                     // max_log_files_cnt
    3U * 3600U,                                            // time_limit_sec (last 3 hours)
    50U                                                    // file_size_limit_kb
NVM_BLOCK_DEFAULTS_END(telemetry_file_cfg, telemetry_file_cfg_t)
NVM_BLOCK_DECL(telemetry_file_cfg, telemetry_file_cfg_t)

NVM_BLOCK_DEFAULTS_START(EPSM_Config, EPS_M_Config_t)
    SAFE_TRUE,  //enableRtcAutoAjust;
    SAFE_TRUE,  //onlyIfRtcIsLost;
    SAFE_FALSE, //reserved1;
    SAFE_FALSE, //enableCapacityCalculation;
    SAFE_FALSE, //enableUsingPduBoardTemperature;
    SAFE_FALSE, //usedExactTemperatureEnable;
    2000,       //exactTemperature;
    SAFE_FALSE, //reserved2;
    SAFE_FALSE  //allowAutoEnableEpsOnPowerUP;
NVM_BLOCK_DEFAULTS_END(EPSM_Config, EPS_M_Config_t)
NVM_BLOCK_DECL(EPSM_Config, EPS_M_Config_t)

NVM_BLOCK_DEFAULTS_START(cubeadcs_err_handl_cfg, cubeadcs_err_handl_cfg_t)
       SAFE_TRUE // Enable error handling
NVM_BLOCK_DEFAULTS_END(cubeadcs_err_handl_cfg, cubeadcs_err_handl_cfg_t)
NVM_BLOCK_DECL(cubeadcs_err_handl_cfg, cubeadcs_err_handl_cfg_t)

NVM_BLOCK_DEFAULTS_START(cubeadcs_status, cubeadcs_status_t)
    0x00,                     // No commissioning
    0x00,                     // No faulty nodes detected
    0x0000                    // No errors
NVM_BLOCK_DEFAULTS_END(cubeadcs_status, cubeadcs_status_t)
NVM_BLOCK_DECL(cubeadcs_status, cubeadcs_status_t)

NVM_BLOCK_DEFAULTS_START(i2c_config, i2c_config_t)
    // I2C Pull-up configuration
    .i2c_pull_up_config =
    {
        // I2C_BUS_SYSTEM
        {
            .pull_up_4k7 = true,
            .pull_up_10k = false
        },
        // I2C_BUS_PAYLOAD
        {
            .pull_up_4k7 = true,
            .pull_up_10k = false
        }
    }
NVM_BLOCK_DEFAULTS_END(i2c_config, i2c_config_t)
NVM_BLOCK_DECL(i2c_config, i2c_config_t)

NVM_BLOCK_DEFAULTS_START(cubeadcs_angle_limits, cubeadcs_angle_limits_t)
    1000,                   // Angular position threshold (boundary) in millidegrees
     200                    // Angular velocity threshold (boundary) in millidegrees
NVM_BLOCK_DEFAULTS_END(cubeadcs_angle_limits, cubeadcs_angle_limits_t)
NVM_BLOCK_DECL(cubeadcs_angle_limits, cubeadcs_angle_limits_t)

NVM_BLOCK_DEFAULTS_START(aocs_pm_config, aocs_pm_config_t)
.parameters = {
	0x00000384,			// 480 seconds, duration of a pass
	0x04,				// 4 seconds is the default update interval
	0x00,				// EST_ATT_ANGL the default data type
	0x000A 				//samples to skip
}
NVM_BLOCK_DEFAULTS_END(aocs_pm_config, aocs_pm_config_t)
NVM_BLOCK_DECL(aocs_pm_config, aocs_pm_config_t)

NVM_BLOCK_DEFAULTS_START(aocs_pm_threshold, aocs_pm_thresholds_t)
.value[0] = {
	6.0,     //tolerance
	0.05     //safety factor of 50 in mili units
},
.value[1] = {
	6.0,     //tolerance
	0.05      //safety factor of 50 in mili units
},
.value[2] = {
	6.0,      //tolerance
	0.05       //safety factor of 50 in mili units
}
NVM_BLOCK_DEFAULTS_END(aocs_pm_threshold, aocs_pm_thresholds_t)
NVM_BLOCK_DECL(aocs_pm_threshold, aocs_pm_thresholds_t)

NVM_BLOCK_DEFAULTS_START(es_adcs_config, es_adcs_config_t)
.sEstimatorConfig =
    {
        .eActiveEstimators[0] = ES_ADCS_ESTIMATOR_ALGO_NONE,
        .eActiveEstimators[1] = ES_ADCS_ESTIMATOR_ALGO_NONE,
    },
.sControllerConfig =
    {
        .eActiveController    = ES_ADCS_CONTROLLER_ALGO_NONE,
        .sBdotConfig =
            {
                .bdot_coefficient_X = 1.0,
                .bdot_coefficient_Y = 1.0,
                .bdot_coefficient_Z = 1.0,
            }
    },
.eUsedMagnetometer = ES_ADCS_USED_MAGNETOMETER_PRIMARY

NVM_BLOCK_DEFAULTS_END(es_adcs_config, es_adcs_config_t)
NVM_BLOCK_DECL(es_adcs_config, es_adcs_config_t)

NVM_BLOCK_DEFAULTS_START(es_coordsys_frames, es_coordsys_frames_t)
.gyroscopeFrame =
    {
        .gyr1 = SAT_Z_AXIS_POSITIVE,
        .gyr2 = SAT_Y_AXIS_POSITIVE,
        .gyr3 = SAT_X_AXIS_POSITIVE
    },
.magnetometerFrame =
    {
        .mag_x = SAT_X_AXIS_POSITIVE,
        .mag_y = SAT_Y_AXIS_NEGATIVE,
        .mag_z = SAT_Z_AXIS_NEGATIVE
    },
.magnetorquerFrame =
    {
        .mtq1 = SAT_Z_AXIS_POSITIVE,
        .mtq2 = SAT_Y_AXIS_POSITIVE,
        .mtq3 = SAT_X_AXIS_POSITIVE
    },
.coarseSunSensorFrame =
    {
		.css1 = SAT_Y_AXIS_NEGATIVE,
		.css2 = SAT_X_AXIS_NEGATIVE,
		.css3 = SAT_Z_AXIS_NEGATIVE,
		.css4 = SAT_Z_AXIS_POSITIVE,
		.css5 = SAT_Y_AXIS_POSITIVE,
		.css6 = SAT_X_AXIS_POSITIVE
    },
.accelerometerFrame =
    {
		.acc_x = SAT_Y_AXIS_NEGATIVE,
		.acc_y = SAT_X_AXIS_NEGATIVE,
		.acc_z = SAT_Z_AXIS_NEGATIVE
    }
NVM_BLOCK_DEFAULTS_END(es_coordsys_frames, es_coordsys_frames_t)
NVM_BLOCK_DECL(es_coordsys_frames, es_coordsys_frames_t)

NVM_BLOCK_DEFAULTS_START(sds_sens_read_freq, sds_sens_read_freq_t)
	SAFE_FALSE,
	{
		{
				.freq_cfg = 10,	// Magnetometer sensor group read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_MTM,
		},
		{
				.freq_cfg = 10,	// Rate sensor group read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_GYRO,
		},
		{
				.freq_cfg = 10, // Coarse Sun sensor group read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_CSS,
		},
		{
				.freq_cfg = 10, // Accelerometer sensor group read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_ACC,
		},
		{
				.freq_cfg = 10, // Temperature (located on 1U panels) sensor group read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_TEMP,
		},
		{
				.freq_cfg = 2, // Rate sensor group temperature sensors read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_GYRO_TEMP,
		},
		{
				.freq_cfg = 0, // Reserved sensor group read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_RES_1,
		},
		{
				.freq_cfg = 0, // Reserved sensor group read frequency in [Hz]
				.event_cfg = SDS_THREAD_FLAGS_RES_2,
		}
	}
NVM_BLOCK_DEFAULTS_END(sds_sens_read_freq, sds_sens_read_freq_t)
NVM_BLOCK_DECL(sds_sens_read_freq, sds_sens_read_freq_t)

NVM_BLOCK_DEFAULTS_START(crypto_cfg, crypto_cfg_t)
    // AES invalid encryption key
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }
NVM_BLOCK_DEFAULTS_END(crypto_cfg, crypto_cfg_t)
NVM_BLOCK_DECL(crypto_cfg, crypto_cfg_t)

NVM_BLOCK_DEFAULTS_START(cubeadcs_sim_mode, cubeadcs_sim_mode_t)
    SAFE_FALSE                // Simulation mode
NVM_BLOCK_DEFAULTS_END(cubeadcs_sim_mode, cubeadcs_sim_mode_t)
NVM_BLOCK_DECL(cubeadcs_sim_mode, cubeadcs_sim_mode_t)

NVM_BLOCK_DEFAULTS_START(rtc_calib_data, rtc_calib_data_t)
    0,  // Calm default
    TIME_CALP_PULSES_RESET // Calp default
NVM_BLOCK_DEFAULTS_END(rtc_calib_data, rtc_calib_data_t)
NVM_BLOCK_DECL(rtc_calib_data, rtc_calib_data_t)

NVM_BLOCK_DEFAULTS_START(gyroscope_configs, gyroscope_configs_t)
.gyroscopeArray[0] =
    {
        .gyro_id = GYROSCOPE_1,
        .generalStatus = GYRO_NOT_INIT,
        .attachedPanel = PANEL_1,
        .satelliteAxis = PAN_X_P,
        .enabledFlag = ADIS16265_DISABLED
    },
.gyroscopeArray[1] =
    {
        .gyro_id = GYROSCOPE_2,
        .generalStatus = GYRO_NOT_INIT,
        .attachedPanel = PANEL_2,
        .satelliteAxis = PAN_Y_P,
        .enabledFlag = ADIS16265_DISABLED
    },
.gyroscopeArray[2] =
    {
        .gyro_id = GYROSCOPE_3,
        .generalStatus = GYRO_NOT_INIT,
        .attachedPanel = PANEL_3,
        .satelliteAxis = PAN_Z_P,
        .enabledFlag = ADIS16265_DISABLED
    }
NVM_BLOCK_DEFAULTS_END(gyroscope_configs, gyroscope_configs_t)
NVM_BLOCK_DECL(gyroscope_configs, gyroscope_configs_t)

NVM_BLOCK_DEFAULTS_START(ff_stats, ff_stats_t)
    .ff_api_err_counters =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    }
NVM_BLOCK_DEFAULTS_END(ff_stats, ff_stats_t)
NVM_BLOCK_DECL(ff_stats, ff_stats_t)

NVM_BLOCK_DEFAULTS_START(cubeADCS_sys_state_cfg, cubeADCS_sys_state_cfg_t)
{
			{eCUBEADCS_CFGTYPE_PWR_UP,
		        { .CubeControl_Signal = 1,
		    	  .CubeControl_Motor  = 1,
				  .CubeSense1 = 0,
		          .CubeSense2 = 0,
				  .CubeStar   = 0,
				  .CubeWheel1 = 0,
				  .CubeWheel2 = 0,
				  .CubeWheel3 = 0
		        },
		        eCUBE_ADCS_TC_13_CONTROLMODE_NO_CNTRL,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
			    eCUBE_ADCS_TC10_RUNMODE_ENABLED,
			    0,
		  },
		  {     eCUBEADCS_CFGTYPE_NORMAL_DETUMBLING,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 0,
				  .CubeSense2 = 0,
				  .CubeStar   = 0,
		          .CubeWheel1 = 0,
				  .CubeWheel2 = 0,
				  .CubeWheel3 = 0
		        },
		        eCUBE_ADCS_TC_13_CONTROLMODE_DETUMB_CNTRL,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
			    eCUBE_ADCS_TC10_RUNMODE_ENABLED,
			    0,
		  },
		  {   	eCUBEADCS_CFGTYPE_Y_THOMSON,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 0,
				  .CubeSense2 = 0,
				  .CubeStar   = 0,
		          .CubeWheel1 = 0,
				  .CubeWheel2 = 0,
				  .CubeWheel3 = 0
		        },
		        eCUBE_ADCS_TC_13_CONTROLMODE_Y_THOMPSON,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_Y_THOMSON_MEMS_RATE,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 0,
				  .CubeSense2 = 0,
				  .CubeStar   = 0,
		          .CubeWheel1 = 0,
				  .CubeWheel2 = 0,
				  .CubeWheel3 = 0
		        },
		        eCUBE_ADCS_TC_13_CONTROLMODE_Y_THOMPSON,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_FAST_DETUMBLING,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 0,
				  .CubeSense2 = 0,
				  .CubeStar   = 0,
		          .CubeWheel1 = 0,
				  .CubeWheel2 = 0,
				  .CubeWheel3 = 0
		        },
				eCUBE_ADCS_TC_13_CONTROLMODE_FAST_SPIN_DETUMB,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_VERY_FAST_DETUMBLING,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 0,
				  .CubeSense2 = 0,
				  .CubeStar   = 0,
		          .CubeWheel1 = 0,
				  .CubeWheel2 = 0,
				  .CubeWheel3 = 0
		        },
				eCUBE_ADCS_TC_13_CONTROLMODE_VERY_FAST_SPIN_DETUMB,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_Y_MOMENTUM,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 0,
				  .CubeSense2 = 0,
				  .CubeStar   = 0,
		          .CubeWheel1 = 0,
				  .CubeWheel2 = 1,
				  .CubeWheel3 = 0
		        },
				eCUBE_ADCS_TC_13_CONTROLMODE_Y_WHEEL_INITIAL,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_Y_MOMENTUM_FULL_STATE_EKF,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 1,
				  .CubeSense2 = 1,
				  .CubeStar   = 1,
		          .CubeWheel1 = 0,
				  .CubeWheel2 = 1,
				  .CubeWheel3 = 0
		        },
				eCUBE_ADCS_TC_13_CONTROLMODE_Y_WHEEL_STEADY,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_FULL_EKF,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_3AXIS,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 1,
				  .CubeSense2 = 1,
				  .CubeStar   = 1,
		          .CubeWheel1 = 1,
				  .CubeWheel2 = 1,
				  .CubeWheel3 = 1
		        },
				eCUBE_ADCS_TC_13_CONTROLMODE_XYZ_WHEEL_CNTRL,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_SUN_TRACKING,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 1,
				  .CubeSense2 = 1,
				  .CubeStar   = 1,
		          .CubeWheel1 = 1,
				  .CubeWheel2 = 1,
				  .CubeWheel3 = 1
		        },
				eCUBE_ADCS_TC_13_CONTROLMODE_RWHEEL_SUN_TRACKING,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
		  {   	eCUBEADCS_CFGTYPE_TARGET_TRACKING,
		        { .CubeControl_Signal = 1,
		          .CubeControl_Motor  = 1,
		          .CubeSense1 = 1,
				  .CubeSense2 = 1,
				  .CubeStar   = 1,
		          .CubeWheel1 = 1,
				  .CubeWheel2 = 1,
				  .CubeWheel3 = 1
		        },
				eCUBE_ADCS_TC_13_CONTROLMODE_RWHEEL_TARGET_TRACKING,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
		        eCUBE_ADCS_TC10_RUNMODE_ENABLED,
		        0,
		  },
          {     eCUBEADCS_CFGTYPE_NO_CONTROL,
                { .CubeControl_Signal = 1,
                  .CubeControl_Motor  = 1,
                  .CubeSense1 = 0,
                  .CubeSense2 = 0,
                  .CubeStar   = 0,
                  .CubeWheel1 = 0,
                  .CubeWheel2 = 0,
                  .CubeWheel3 = 0
                },
                eCUBE_ADCS_TC_13_CONTROLMODE_NO_CNTRL,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
                eCUBE_ADCS_TC10_RUNMODE_ENABLED,
                0,
          },
          {     eCUBEADCS_CFGTYPE_ATTITUDE_CHANGE,
                { .CubeControl_Signal = 1,
                  .CubeControl_Motor  = 1,
                  .CubeSense1 = 0,
                  .CubeSense2 = 0,
                  .CubeStar   = 0,
                  .CubeWheel1 = 0,
                  .CubeWheel2 = 0,
                  .CubeWheel3 = 0
                },
                eCUBE_ADCS_TC_13_CONTROLMODE_Y_THOMPSON,
				eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
                eCUBE_ADCS_TC10_RUNMODE_ENABLED,
                1,
          },
          {     eCUBEADCS_CFGTYPE_ORBITAL_CHANGE,
                { .CubeControl_Signal = 1,
                  .CubeControl_Motor  = 1,
                  .CubeSense1 = 1,
                  .CubeSense2 = 1,
                  .CubeStar   = 1,
                  .CubeWheel1 = 1,
                  .CubeWheel2 = 1,
                  .CubeWheel3 = 1
                },
                eCUBE_ADCS_TC_13_CONTROLMODE_XYZ_WHEEL_CNTRL,
                eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
                eCUBE_ADCS_TC10_RUNMODE_ENABLED,
                1,
          },
		  {     eCUBEADCS_CFGTYPE_GEO_TARGET_TRACKING,
				  { .CubeControl_Signal = 1,
					.CubeControl_Motor  = 1,
					.CubeSense1 = 1,
					.CubeSense2 = 1,
					.CubeStar   = 1,
					.CubeWheel1 = 1,
					.CubeWheel2 = 1,
					.CubeWheel3 = 1
				  },
				  eCUBE_ADCS_TC_13_CONTROLMODE_USER_MODE_1,
				  eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
				  eCUBE_ADCS_TC10_RUNMODE_ENABLED,
				  0,
		  }
}
NVM_BLOCK_DEFAULTS_END(cubeADCS_sys_state_cfg, cubeADCS_sys_state_cfg_t)
NVM_BLOCK_DECL(cubeADCS_sys_state_cfg, cubeADCS_sys_state_cfg_t)

// 0x00 is an invalid MAC Address
NVM_BLOCK_DEFAULTS_START(mac_address_book, mac_address_book_t)
    {
        0x99, // MAC_ADDR_EPS_I,
        0x00, // MAC_ADDR_RESERVED_5,
        0x00, // MAC_ADDR_EPS_II_PDM 0x00 means disabled
        0x11, // MAC_ADDR_UHF,
        0x44, // MAC_ADDR_SBAND_TMTC,
        0x51, // MAC_ADDR_SP1,
        0x52, // MAC_ADDR_SP2,
        0x53, // MAC_ADDR_SP3,
        0x54, // MAC_ADDR_SP4,
        0xC0, // MAC_ADDR_PAYLOAD_1,
        0xD0, // MAC_ADDR_PAYLOAD_2,
        0x00, // MAC_ADDR_RESERVED_1,
        0x00, // MAC_ADDR_RESERVED_2,
        0x00, // MAC_ADDR_RESERVED_3,
        0x00, // MAC_ADDR_RESERVED_4,
    },
    {
// begin EPS BP generated code
    
        0x00, // MAC_ADDR_EPS INST0  0x00 means disabled  
        0x00, // MAC_ADDR_EPS INST1  0x00 means disabled  
        0x00 // MAC_ADDR_EPS INST2   0x00 means disabled     
// end EPS BP generated code
    }
NVM_BLOCK_DEFAULTS_END(mac_address_book, mac_address_book_t)
NVM_BLOCK_DECL(mac_address_book, mac_address_book_t)


NVM_BLOCK_DEFAULTS_START(cubeadcs_gen2_sys_states_cfg, cubeadcs_gen2_sys_states_cfg_t)
// AOCS_CNTRL_SYS_STATE_NO_CONTROL
.sys_state_cfg[0] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_NONE,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
},
// AOCS_CNTRL_SYS_STATE_NORMAL_DETUMBLING
.sys_state_cfg[1] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_BDOT,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
},
// AOCS_CNTRL_SYS_STATE_Y_THOMSON
.sys_state_cfg[2] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YSPIN,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
},
// AOCS_CNTRL_SYS_STATE_Y_THOMSON_MEMS_RATE
.sys_state_cfg[3] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YSPIN,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
},
// AOCS_CNTRL_SYS_STATE_FAST_DETUMBLING
.sys_state_cfg[4] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_BDOT_3,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
},
// AOCS_CNTRL_SYS_STATE_VERY_FAST_DETUMBLING
.sys_state_cfg[5] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_DETUMBLE,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
},
// AOCS_CNTRL_SYS_STATE_Y_MOMENTUM
.sys_state_cfg[6] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YWHEEL_INIT,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO_EKF,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_FULL_EKF,
},
// AOCS_CNTRL_SYS_STATE_Y_MOMENTUM_FULL_STATE_EKF
.sys_state_cfg[7] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_YWHEEL_INIT,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_FULL_EKF,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO_EKF,
},
// AOCS_CNTRL_SYS_STATE_3AXIS
.sys_state_cfg[8] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_XYZWHEEL,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO_EKF,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_FULL_EKF,
},
// AOCS_CNTRL_SYS_STATE_SUN_TRACKING
.sys_state_cfg[9] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_SUN_TRACK,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO_EKF,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_FULL_EKF,
},
// AOCS_CNTRL_SYS_STATE_TARGET_TRACKING
.sys_state_cfg[10] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_TGT_TRACK,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO_EKF,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_FULL_EKF,
},
// AOCS_CNTRL_SYS_STATE_USER1
.sys_state_cfg[11] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_NONE,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
},
// AOCS_CNTRL_SYS_STATE_USER2
.sys_state_cfg[12] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_NONE,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
},
// AOCS_CNTRL_SYS_STATE_USER3
.sys_state_cfg[13] =
{
        .pwr_state = {
                .rwl0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .rwl3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .mag0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .mag1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .gyro0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_ON,
                .gyro1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss2Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .fss3Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .hss1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .str1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor0Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
                .extSensor1Power = TCTLM_CUBE_COMPUTER_COMMON_3__POWER_OFF,
        },
        .cntrl_mode = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__CON_NONE,
        .est_mode_main = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_GYRO,
        .est_mode_backup = TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__EST_MAG_RKF,
}
NVM_BLOCK_DEFAULTS_END(cubeadcs_gen2_sys_states_cfg, cubeadcs_gen2_sys_states_cfg_t)
NVM_BLOCK_DECL(cubeadcs_gen2_sys_states_cfg, cubeadcs_gen2_sys_states_cfg_t)

NVM_BLOCK_DEFAULTS_START(cubeadcs_gen2_tlm_cfg, cubeadcs_gen2_tlm_cfg_t)
    .mask[CUBEADCS_GEN2_TLM_MASK_0] = {false, false, false, false, false, false, false, false},
    .mask[CUBEADCS_GEN2_TLM_MASK_1] = {false, false, false, false, false, false, false, false},
    .mask[CUBEADCS_GEN2_TLM_MASK_2] = {false, false, false, false, false, false, false, false},
    .mask[CUBEADCS_GEN2_TLM_MASK_3] = {false, false, false, false, false, false, false, false},
    .mask[CUBEADCS_GEN2_TLM_MASK_4] = {false, false, false, false, false, false, false, false}
NVM_BLOCK_DEFAULTS_END(cubeadcs_gen2_tlm_cfg, cubeadcs_gen2_tlm_cfg_t)
NVM_BLOCK_DECL(cubeadcs_gen2_tlm_cfg, cubeadcs_gen2_tlm_cfg_t)

NVM_BLOCK_DEFAULTS_START(adcs_cms_status, adcs_cms_status_t)
    .cms_status = 0
NVM_BLOCK_DEFAULTS_END(adcs_cms_status, adcs_cms_status_t)
NVM_BLOCK_DECL(adcs_cms_status, adcs_cms_status_t)

NVM_BLOCK_DEFAULTS_START(fault_index, fault_index_t)
    0,                    // next_free_slot_index
    MAX_FAULT_BLOCKS_CNT  // free_slots (must match the number of fault_block_x blocks reserved for fault storage
NVM_BLOCK_DEFAULTS_END(fault_index, fault_index_t)
NVM_BLOCK_DECL(fault_index, fault_index_t)

NVM_BLOCK_DECL(fault_block_0, fault_block_t)
NVM_BLOCK_DECL(fault_block_1, fault_block_t)
NVM_BLOCK_DECL(fault_block_2, fault_block_t)
NVM_BLOCK_DECL(fault_block_3, fault_block_t)
NVM_BLOCK_DECL(fault_block_4, fault_block_t)
