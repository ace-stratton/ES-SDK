    {
            .u32Size = sizeof(NvMLayoutVersion),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &NvMLayoutVersion,
            .pBufDefaults = (const uint8_t * const) NULL,
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED | BLKCFG_FIXED_ADDRESS,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(BootData),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &BootData,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(BootData),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
    {
            .u32Size = sizeof(sModuleIdPersistentSettings_t),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &ModuleId,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(ModuleId),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
#ifdef COMM_RS485_MAC_LAYER_ENABLED
    {
            .u32Size = sizeof(MacConfig),
            .eBlockType = EBLOCKTYPE_REDUNDANT,
            .pRamMirrorBuf = (uint8_t * const) &MacConfig,
            .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(MacConfig),
            .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
            .u32FixedAddress = 0x00000000
    },
#endif      // #ifdef COMM_RS485_MAC_LAYER_ENABLED
