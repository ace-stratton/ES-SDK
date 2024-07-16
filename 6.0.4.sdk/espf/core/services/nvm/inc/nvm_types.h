/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*
 * nvm_type_defines.h
 *
 *  Created on: 21 Feb 2022
 *      Author: VStoev
 */

#ifndef NVM_INC_NVM_TYPE_DEFINES_H_
#define NVM_INC_NVM_TYPE_DEFINES_H_

#include "es_cdef.h"
#include "nvm_cfg_defines.h"

#define NVM_BLOCK_DEFINE_START(blockType)    typedef struct {
#define NVM_BLOCK_DEFINE_END(blockType)      uint32_t u32Crc; \
		                                     } blockType;

#define NVM_BLOCK_DEFAULTS_START(blockName, blockType)  const blockType blockName##Defaults = {
#define NVM_BLOCK_DEFAULTS_END(blockName, blockType)    , 0x00000000 };
#define NVM_BLOCK_DEFAULTS(blockName)    blockName##Defaults

#define NVM_BLOCK_DECL(blockName, blockType)   __attribute__((aligned (4))) blockType blockName;

typedef enum
{
    EBLOCKTYPE_SINGLE,
    EBLOCKTYPE_REDUNDANT,
    EBLOCKTYPE_MAX
} eBlockType_t;

// the following defines are bit masks for the sNvmBlockDescriptor_t::u16ConfigBitfield attribute
#define BLKCFG_CRC_PROTECTED    (0x01U)
#define BLKCFG_FIXED_ADDRESS    (0x02U)

typedef struct
{
    uint32_t u32Size;
    eBlockType_t eBlockType;
    uint8_t * const pRamMirrorBuf;
    const uint8_t * const pBufDefaults;
    uint32_t u32FixedAddress;
    uint16_t u16ConfigBitfield;
} sNvmBlockDescriptor_t;

typedef struct
{
    // contains the calculated start addresses for the specified block
    // (could be more than one if the block is redundant)
    uint32_t u32BlockAddress[REDUNDANT_BLOCKS_COUNT];
    // the flag indicates the default ROM values were restored for that block
    // because CRC failed for all redundant copies (if any)
    bool bDefaultsRestored;
    // indicates that the RAM mirror has been changed since last load
    bool bRamMirrorDirty;
    // the flag can be used when the layout version check fails but some of
    // the blocks shall not be forced to default values (e.g. when application
    // upgrades its layout but bootloader blocks shall be preserved)
    bool bOverrideForceDefaults;
} sNvmBlockDescriptorRunTime_t;

#endif /* NVM_INC_NVM_TYPE_DEFINES_H_ */
