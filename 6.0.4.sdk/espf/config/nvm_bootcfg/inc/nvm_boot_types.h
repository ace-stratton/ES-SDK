/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef NVM_INC_NVM_BOOT_TYPES_H_
#define NVM_INC_NVM_BOOT_TYPES_H_

#include "es_cdef.h"
#include "ESPLATFORM_NETWORK_STACK/ES_SAT_API/include/ESSA_ServiceProtocol_Types.h"
#include "nvm_types.h"

#pragma pack(push)
#pragma pack(1)

// Magic values used for boot_struct::Mailbox data exchange between Application and Bootloader instances
#define MAILBOX_VAL_BOOT        (0xB007B007)
#define MAILBOX_VAL_APPL        (0xA552A552)
#define MAILBOX_VAL_AUTO_FLASH  (0x2AA52AAF)

#define BOOTLDR_AUTOFLASH_FILE_PATH "OBC_img.bin"   /**< Name of the file which BL uses for automatic flashing after reboot */

typedef struct
{
    // starting from LSB, each bit represents the bus termination resistor state
    // for the MAC interface corresponding to that bit (mapped to value in eMACInterface_t type)
    // e.g.: bit 0 --> eMAC_Interface_Primary
    uint8_t u8MacBusTerminationBitField;
    uint8_t u8MacAddress;
} sMacDrvSettings_t;

NVM_BLOCK_DEFINE_START(sNvmId_t)
    uint16_t sharedDataLayoutVersion;
NVM_BLOCK_DEFINE_END(sNvmId_t)

NVM_BLOCK_DEFINE_START(boot_struct)
    uint32_t Reserve1;
    uint32_t Mailbox;          /* Keeps magic number giving info for last run SW and reset reason */

    uint32_t RST_WWD;          /* WINDOW_WATCHDOG_RESET */
    uint32_t RST_IWD;          /* INDEPENDENT_WATCHDOG_RESET */
    uint32_t RST_LPR;          /* LOW_POWER_RESET */
    uint32_t RST_POR;          /* POWER-ON_RESET (POR) / POWER-DOWN_RESET (PDR) */
    uint32_t RST_RstPin;       /* EXTERNAL_RESET_PIN_RESET */
    uint32_t RST_BOR;          /* BROWNOUT_RESET (BOR) */

    uint32_t RST_HardFault;    /* HardFault_Handler()  */
    uint32_t RST_MemFault;     /* MemManage_Handler()  */
    uint32_t RST_BusFault;     /* BusFault_Handler()   */
    uint32_t RST_UsageFault;   /* UsageFault_Handler() */

    uint32_t RST_ErrHandler;   /* UsageFault_Handler() */

    uint32_t RebootRequest;    /* reserved */
    uint32_t Reserve3;         /* reserved */
NVM_BLOCK_DEFINE_END(boot_struct)

NVM_BLOCK_DEFINE_START(sMacConfig_t)
    sMacDrvSettings_t macDrvConfig;
NVM_BLOCK_DEFINE_END(sMacConfig_t)

NVM_BLOCK_DEFINE_START(sModuleIdPersistentSettings_t)
    uint16_t nModuleType;                               // or DevName. From ESPLATFORM_COMMON\ESSAT_ModuleTypes.h
    uint16_t nModuleHWConfig;                           // Device specific, use 0 if not used
    uint16_t nModuleHWRevision;                         // Device specific, use 0 if not used
    char szModuleSerial[ESSASP_DEV_SERIAL_MAX_SIZE];
NVM_BLOCK_DEFINE_END(sModuleIdPersistentSettings_t)

#pragma pack(pop)

#endif /* NVM_INC_NVM_BOOT_TYPES_H_ */
