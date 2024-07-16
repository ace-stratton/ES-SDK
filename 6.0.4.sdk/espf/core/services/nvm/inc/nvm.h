/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef NVM_PRIVATE_INC_NVM_H_
#define NVM_PRIVATE_INC_NVM_H_

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup Nvm
 * @{
 *
 * The service provides:
 * - A high-level abstraction over the persistent data store used in the system.
 * - Grouping of data in logical blocks with unique identifiers.
 * - Data integrity checking.
 * - Updating of block values with ROM defaults in case of integrity errors.
 * - Single/redundant block data management.
 *
 * @subsection nvm_usage NVM service initialization
 * The initialization of the NVM service is performed by calling the following functions in the
 * given sequence:
 * @n
 * @code {.c}
 * Nvm_Init();      // perform memory initialization
 * Nvm_Load();      // load persistent data to RAM mirrors
 * Nvm_TaskStart(); // activate the OS task which manages the updates of the RAM mirrors to the NVM
 * @endcode
 *
 * @emoji :information_source: The NVM service will make sure the underlying drivers for accessing the persistent storage are
 * also initialized.
 *
 * @subsection nvm_new_data_blocks Adding new data blocks to the NVM service
 * Blocks managed by the NVM service require the following assets for the NVM service to operate:
 * - A unique ID used as an internal handle passed to the `get/set` APIs.
 * - A user-defined data type used to describe the content of the NVM block.
 * - An NVM service control descriptor which specifies how exactly the block will be managed internally and
 * also provides information about the RAM mirror storage and default ROM values for the block.
 *
 * In the context of the OBC SDK, the NVM service has two sets of block identifiers which must be maintained:
 * - nvm_app_block_ids.h <i>(contains data block IDs specific to the OBC application)</i>
 * - nvm_boot_block_ids.h <i>(contains data block IDs shared between the application and the bootloader image)</i>
 *
 * Similarly, there are two files where block types are described (for the sake of consistency):
 * - nvm_app_types.h <i>(contains the definitions of the data blocks content for the application)</i>
 * - nvm_boot_types.h <i>(contains the definitions of the data blocks content for the shared blocks between bootloader and application)</i>
 *
 * The default values for each set of blocks is described in the following `.inc` files:
 * <i>(these files are still valid C files but contain only partial definitions and cannot be used alone)</i>:
 * - nvm_app_defs.inc
 * - nvm_boot_defs.inc
 *
 * Finally, the runtime descriptors for each set of blocks is described here:
 * <i>(these files are still valid C files but contain only partial definitions and cannot be used alone)</i>:
 * - nvm_app_blocks_init.inc
 * - nvm_bootshared_blocks_init.inc
 *
 * @emoji :heavy_exclamation_mark: Changing the latter requires updates in the bootloader project as well and is not recommended
 * unless you need to extend the bootloader's functionality to match your requirements.
 *
 * In the typical scenario, you would only need to update the nvm_app_*.h files. Let's take an example for the `I2C_CONFIG` block...
 * - Create a new block ID for your data in nvm_app_block_ids.h by extending the list of values:
 * @code {.c}
 * enum
 * {
 *	    NVM_RESERVED = NVM_BOOT_BLOCK_MAX_COUNT,
 *      ...
 *      // it is important to keep the block ordering as shown here and put your new blocks after the NVM_RESERVED entry and
 *      // before the NVM_BLOCK_MAX_COUNT entry
 *      NVM_BLOCK_I2C_CONFIG
 *      ...
 *	    NVM_BLOCK_MAX_COUNT
 * };
 * @endcode
 *
 * - Now that we have a block identifier, we must define the data content of our new block. Let's put the following code in the nvm_app_types.h file:
 * @code {.c}
 * // first define any specific types you will use as part of your block data
 * typedef struct
 * {
 *      bool pull_up_4k7;
 *      bool pull_up_10k;
 * } bus_pull_up_state_t;
 *
 * // define the NVM block data by using the following convention:
 * NVM_BLOCK_DEFINE_START(i2c_config_t)
 *      bus_pull_up_state_t i2c_pull_up_config[I2C_BUS_MAX];
 * NVM_BLOCK_DEFINE_END(i2c_config_t)
 * @endcode
 *
 * @emoji :heavy_exclamation_mark: Always use the `NVM_BLOCK_DEFINE_START()` and `NVM_BLOCK_DEFINE_END()` macros to define your block content.
 * This will ensure easier migration to new data structures used in the NVM service in the future.
 *
 * - As the block data is now clearly defined, we can provide the ROM defaults which will be used for the block in case of issues with
 * the stored data. Open the `nvm_app_defs.inc` file and put the following code there (usually at the end of the file):
 * @code {.c}
 * // !!! make sure to use the provided NVM_BLOCK_DEFAULTS_START(), NVM_BLOCK_DEFAULTS_END() and NVM_BLOCK_DECL() macros !!!
 * NVM_BLOCK_DEFAULTS_START(i2c_config, i2c_config_t)
 *     // I2C Pull-up configuration
 *     .i2c_pull_up_config =
 *     {
 *         // I2C_BUS_SYSTEM
 *         {
 *             .pull_up_4k7 = true,
 *             .pull_up_10k = false
 *         },
 *         // I2C_BUS_PAYLOAD
 *         {
 *             .pull_up_4k7 = true,
 *             .pull_up_10k = false
 *         }
 *     }
 * NVM_BLOCK_DEFAULTS_END(i2c_config, i2c_config_t)
 * NVM_BLOCK_DECL(i2c_config, i2c_config_t)
 * @endcode
 *
 * - We are almost finished but there is still one important step - the NVM block descriptor which glues together all the
 * structures that we already defined in the previous steps. Now open the `nvm_app_blocks_init.inc` file and put the following code inside:
 * @code {.c}
 *	{
 *      .u32Size = sizeof(i2c_config_t),
 *      .eBlockType = EBLOCKTYPE_REDUNDANT,
 *      .pRamMirrorBuf = (uint8_t * const) &i2c_config,
 *      .pBufDefaults = (const uint8_t * const) &NVM_BLOCK_DEFAULTS(i2c_config),
 *      .u16ConfigBitfield = BLKCFG_CRC_PROTECTED,
 *      .u32FixedAddress = 0x00000000
 *    },
 * @endcode
 *
 * @emoji :heavy_exclamation_mark: Make sure the code above is placed in the exact position defined by the `NVM_BLOCK_I2C_CONFIG` identifier you defined earlier.
 * In fact, this @a .inc file contains the initializer values for the NVM blocks array and indexing is performed by using the NVM block identifiers.
 *
 * @emoji :fireworks: With this step, your new NVM block is defined and you can start using it.
 *
 * @subsection nvm_block_usage How to use my new NVM block?
 * - Reading from the block
 * @code {.c}
 *  #include "nvm.h"
 *
 *  i2c_config_t i2c_config;  // define local storage for the block data
 *
 *  // get a copy of the NVM data
 *  Nvm_GetBlockById(NVM_BLOCK_I2C_CONFIG, &i2c_config);
 *
 *   // i2c_config now contains the block data...
 * @endcode
 *
 * - Writing to the block
 * @code {.c}
 * #include "nvm.h"
 *
 * i2c_config_t i2c_config;  // define local storage for the block data
 *
 * // make changes to the data before passing it to the NVM service...
 * i2c_config.i2c_pull_up_config[0].pull_up_4k7 = true;
 * i2c_config.i2c_pull_up_config[0].pull_up_10k = true;
 * i2c_config.i2c_pull_up_config[1].pull_up_4k7 = false;
 * i2c_config.i2c_pull_up_config[1].pull_up_10k = false;
 *
 * // update the data to NVM immediately...
 * Nvm_SetBlockById(NVM_BLOCK_I2C_CONFIG, &i2c_config, NVMSETBLOCK_STORE_IMMEDIATELY);
 * @endcode
 *
 * @file nvm.h
 * @brief NVM service public interface
 *
 * @}
 * @}
 *
 * @brief Non-volatile Memory storage service interface
 *
 */

#include "es_cdef.h"
#include "nvm/inc/nvm_data_types.h"
#include "nvm/inc/nvm_block_ids.h"

/** @brief Specifies the standard store procedure where only dirty blocks are updated in NVM
 *  @note To be used as an argument to the `Nvm_Store()` function
*/
#define NVMSTORE_STANDARD       (false)

/** @brief Specifies that all blocks are overwritten with default values
 *  @note To be used as an argument to the `Nvm_Store()` function
*/
#define NVMSTORE_FORCEDEFAULTS  (true)

/** @brief Indicates that the block update in NVM can be postponed until the next invocation of the Nvm service regular task function.
 *  @note Symbol to use with the `Nvm_SetBlockById::bStoreImmediately` parameter
 */
#define NVMSETBLOCK_STORE_POSTPONED     (false)

/** @brief Indicates that the block update in NVM shall take place immediately without waiting for the regular task function to be
 *         scheduled.
 *  @note Symbol to use with the `Nvm_SetBlockById::bStoreImmediately` parameter
 */
#define NVMSETBLOCK_STORE_IMMEDIATELY   (true)

/**
 * @brief Initializes the Nvm service for use.
 *
 * The function also takes care to initialize the underlying persistent storage (e.g. FRAM, SD card, etc.) drivers.
 *
 * @note Actual loading of data from the storage is not performed by this function.
 */
void Nvm_Init(void);

/**
 * @brief Loads the NVM data from the persistent storage to the RAM mirror.
 *
 * The load procedure also performs block CRC checking and replacement with a secondary copy of the data in case of
 * redundant block configuration or with defaults in case the block has only one instance.
 * Another important point here is that the version layout of the Nvm structures is checked and if it doesn't match
 * the hardcoded version of the layout, defaults will be forced for all blocks.
 *
 * @note Default data is not replaced in the persistent storage - it is only copied to the NVM cache in RAM.
 */
void Nvm_Load(void);

/**
 * @brief Makes a copy of the stored data for a given NVM block to a user-specified buffer.
 *
 * @param[in] u16BlockId ID of the NVM block to read from (as specified in nvm_block_ids.h)
 * @param[out] pBlockBuffer A pointer to a user-provided buffer to receive a copy of the NVM data
 *
 * @warning You have to check the exact data type of the block referenced by @a u16BlockId because Nvm_GetBlockById() may
 * cause memory corruption. In future versions of this interface, we will have named functions per block so that
 * the compiler can enforce type-safety.
 *
 * @b Example:
 * @n
 * The following code reads NVM_BLOCK_I2C_CONFIG into the @a i2c_config_t structure because the NVM block defined in nvm_app_types.h
 * uses the same type:
 * @code {.c}
 * NVM_BLOCK_DEFINE_START(i2c_config_t)
       bus_pull_up_state_t i2c_pull_up_config[I2C_BUS_MAX];
 * NVM_BLOCK_DEFINE_END(i2c_config_t)
 * @endcode
 *
 * @emoji :information_source: As a rule of thumb, you can @a blockType provided as a parameter to `NVM_BLOCK_DEFINE_START(blockType)` as the type for reading and writing
 * NVM block data.
 *
 * @code {.c}
 *    i2c_config_t i2c_config;
 *    Nvm_GetBlockById(NVM_BLOCK_I2C_CONFIG, &i2c_config);
 * @endcode
 */
void Nvm_GetBlockById(uint16_t u16BlockId, void * const pBlockBuffer);

/**
 * @brief Updates the NVM block data to the persistent storage.
 *
 * @param[in] u16BlockId ID of the NVM block to write to (as specified in nvm_block_ids.h)
 * @param[in] pBlockBuffer A pointer to the user block data (@emoji :heavy_exclamation_mark: the size of this
 * buffer must match the actual size of the block)
 * @param[in] bStoreImmediately You can put here any of the `NVMSETBLOCK_STORE_*` macros to specify how the
 * data shall be written to the NVM.
 */
void Nvm_SetBlockById(uint16_t u16BlockId, void * const pBlockBuffer, const bool bStoreImmediately);

/**
 * @brief Updates all NVM blocks to the persistent storage using the current state of the RAM mirror.
 *
 * @param[in] bForceDefaults You can use here any of the `NVMSTORE_*` macros to specify whether to force-write
 * default values or not.
 */
void Nvm_Store(const bool bForceDefaults);

/**
 * @brief The functions overwrites the persistent storage for a given block with the ROM default values.
 *
 * @param[in] u16BlockId ID of the NVM block to restore defaults to (as specified in nvm_block_ids.h)
 */
void Nvm_RestoreBlockDefaults(const uint16_t u16BlockId);

/**
 * @brief Activates the NVM service main OS task.
 *
 * This is the second stage of the NVM service activation after calling
 * Nvm_Init() and Nvm_Load().
 *
 */
void Nvm_TaskStart(void);

/**
 * @}
 * @}
 *
 */
#endif /* NVM_PRIVATE_INC_NVM_H_ */
