NVM_BLOCK_DECL(NvMLayoutVersion, sNvmId_t)

NVM_BLOCK_DEFAULTS_START(BootData, boot_struct)
    0x00000000,  // bootData::Reserve1
    0x00000000,  // bootData::Mailbox
    0x00000000,  // bootData::RST_WWD
    0x00000000,  // bootData::RST_IWD
    0x00000000,  // bootData::RST_LPR
    0x00000000,  // bootData::RST_POR
    0x00000000,  // bootData::RST_RstPin
    0x00000000,  // bootData::RST_BOR
    0x00000000,  // bootData::RST_HardFault
    0x00000000,  // bootData::RST_MemFault
    0x00000000,  // bootData::RST_BusFault
    0x00000000,  // bootData::RST_UsageFault
    0x00000000,  // bootData::RST_ErrHandler
    0x00000000,  // bootData::RST_RebootRequest
    0x00000000   // bootData::Reserve3
NVM_BLOCK_DEFAULTS_END(BootData, boot_struct)
NVM_BLOCK_DECL(BootData, boot_struct)

NVM_BLOCK_DEFAULTS_START(ModuleId, sModuleIdPersistentSettings_t)
    0x0000,            // nModuleType
    0x0109,            // nModuleHWConfig
    0x0000,            // nModuleHwRevision
    "UNASSIGNED\0"     // szModuleSerial
NVM_BLOCK_DEFAULTS_END(ModuleId, sModuleIdPersistentSettings_t)
NVM_BLOCK_DECL(ModuleId, sModuleIdPersistentSettings_t)

#ifdef COMM_RS485_MAC_LAYER_ENABLED
NVM_BLOCK_DEFAULTS_START(MacConfig, sMacConfig_t)
    {
        0x00000000,  // macDrvConfig::u8MacBusTerminationBitField
        MAC_SYS1_ADDRESS_PRI, // macDrvConfig::u8MacAddress
    }
NVM_BLOCK_DEFAULTS_END(MacConfig, sMacConfig_t)
NVM_BLOCK_DECL(MacConfig, sMacConfig_t)
#endif      // #ifdef RS485_MAC_LAYER_ENABLED
