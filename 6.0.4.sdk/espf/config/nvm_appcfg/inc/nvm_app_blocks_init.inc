    // reserved block to make sure app blocks always start from a fixed index in NVM block list
    {
            .u32Size = sizeof(reserved_dummy_t),
            .eBlockType = EBLOCKTYPE_SINGLE,
            .pRamMirrorBuf = (uint8_t * const) &reserved_dummy,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(reserved_dummy),
            .u16ConfigBitfield = 0U,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(beacons_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &beacons_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(beacons_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(beacons_presets_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &beacons_presets_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(beacons_presets_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(ConOpsConfig_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &OpModesConfig,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(OpModesConfig),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(conops_idle_pointreq_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &conops_idle_pointreq_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(conops_idle_pointreq_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(telemetry_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &telemetry_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(telemetry_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(telemetry_preset_cfg),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &telemetry_preset_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(telemetry_preset_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(telemetry_file_cfg),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &telemetry_file_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(telemetry_file_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(EPS_M_Config_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &EPSM_Config,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(EPSM_Config),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(cubeadcs_err_handl_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &cubeadcs_err_handl_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(cubeadcs_err_handl_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(cubeadcs_status_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &cubeadcs_status,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(cubeadcs_status),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(i2c_config_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &i2c_config,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(i2c_config),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(cubeadcs_angle_limits_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &cubeadcs_angle_limits,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(cubeadcs_angle_limits),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(es_adcs_config_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &es_adcs_config,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(es_adcs_config),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(aocs_pm_config_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &aocs_pm_config,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(aocs_pm_config),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(aocs_pm_thresholds_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &aocs_pm_threshold,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(aocs_pm_threshold),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(es_coordsys_frames_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &es_coordsys_frames,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(es_coordsys_frames),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(sds_sens_read_freq_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &sds_sens_read_freq,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(sds_sens_read_freq),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(crypto_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &crypto_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(crypto_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(cubeadcs_sim_mode_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &cubeadcs_sim_mode,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(cubeadcs_sim_mode),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(rtc_calib_data_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &rtc_calib_data,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(rtc_calib_data),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(gyroscope_configs_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &gyroscope_configs,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(gyroscope_configs),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(ff_stats_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &ff_stats,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(ff_stats),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
	{
			.u32Size = sizeof(cubeADCS_sys_state_cfg_t),
			.eBlockType = EBLOCKTYPE_REDUNDANT,
			.pRamMirrorBuf = (uint8_t * const) &cubeADCS_sys_state_cfg,
			.pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(cubeADCS_sys_state_cfg),
			.u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
			.u32FixedAddress = 0x00000000
	},
	{
			.u32Size = sizeof(mac_address_book_t),
			.eBlockType = EBLOCKTYPE_REDUNDANT,
			.pRamMirrorBuf = (uint8_t * const) &mac_address_book,
			.pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(mac_address_book),
			.u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
			.u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(cubeadcs_gen2_sys_states_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &cubeadcs_gen2_sys_states_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(cubeadcs_gen2_sys_states_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(cubeadcs_gen2_tlm_cfg_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &cubeadcs_gen2_tlm_cfg,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(cubeadcs_gen2_tlm_cfg),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(adcs_cms_status_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &adcs_cms_status,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(adcs_cms_status),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(fault_index_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &fault_index,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(fault_index),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(fault_block_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &fault_block_0,
            .pBufDefaults = (const uint8_t * const) NULL,
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(fault_block_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &fault_block_1,
            .pBufDefaults = (const uint8_t * const) NULL,
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(fault_block_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &fault_block_2,
            .pBufDefaults = (const uint8_t * const) NULL,
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(fault_block_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &fault_block_3,
            .pBufDefaults = (const uint8_t * const) NULL,
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(fault_block_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &fault_block_4,
            .pBufDefaults = (const uint8_t * const) NULL,
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
