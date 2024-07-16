/*!
********************************************************************************************
* @file FP_nvmProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface nvm v0.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __FP_NVMPROTOCOLTYPES_H__
#define __FP_NVMPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_NVM ((uint16_t) (0x00000103))

#define NVM_RESTORE_DEFAULTS_FUNC_ID ((funcIdType_t) 0x00000000)
#define NVM_RESTORE_DEFAULTS_FUNCRESP_ID ((funcIdType_t) 0x00000000)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define NVM_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define NVM_STANDARDRESULT_ERROR ((uint8_t) 1)
#define NVM_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define NVM_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define NVM_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t NVM_StandardResult_t;

#define NVM_BLOCKID_BOOTLAYOUTVERSION ((uint8_t) 0)
#define NVM_BLOCKID_BOOTDATA ((uint8_t) 1)
#define NVM_BLOCKID_MODULEID ((uint8_t) 2)
#define NVM_BLOCKID_MACCONFIG ((uint8_t) 3)
#define NVM_BLOCKID_RESERVED ((uint8_t) 4)
#define NVM_BLOCKID_BEACONS_GENERAL ((uint8_t) 5)
#define NVM_BLOCKID_BEACONS_PRESETS ((uint8_t) 6)
#define NVM_BLOCKID_BLOCK_CONOPS_CONFIG ((uint8_t) 7)
#define NVM_BLOCKID_BLOCK_CONOPS_IDLE_CONFIG ((uint8_t) 8)
#define NVM_BLOCKID_TELEMETRY_GENERAL ((uint8_t) 9)
#define NVM_BLOCKID_TELEMETRY_PRESETS ((uint8_t) 10)
#define NVM_BLOCKID_TELEMETRY_FILE_CFG ((uint8_t) 11)
#define NVM_BLOCKID_EPS_M_CONFIG ((uint8_t) 12)
#define NVM_BLOCKID_CUBEADCS_ERR_HANDL_CONFIG ((uint8_t) 13)
#define NVM_BLOCKID_CUBEADCS_STATUS ((uint8_t) 14)
#define NVM_BLOCKID_I2C_CONFIG ((uint8_t) 15)
#define NVM_BLOCKID_CUBEADCS_ANGLE_LIMITS ((uint8_t) 16)
#define NVM_BLOCKID_ES_ADCS_CONFIG ((uint8_t) 17)
#define NVM_BLOCKID_COORDINATE_FRAMES ((uint8_t) 18)
#define NVM_BLOCKID_SDS_READ_FREQ_CFG ((uint8_t) 19)
#define NVM_BLOCKID_CRYPTO_CFG ((uint8_t) 20)
#define NVM_BLOCKID_CUBEADCS_SIMULATION_MODE ((uint8_t) 21)
#define NVM_BLOCKID_RTC_CALIB_DATA ((uint8_t) 22)
#define NVM_BLOCKID_GYROSCOPE_CONFIG ((uint8_t) 23)
#define NVM_BLOCKID_FF_STATS ((uint8_t) 24)
#define NVM_BLOCKID_CUBEADCS_SYS_STATE_CFG ((uint8_t) 25)
#define NVM_BLOCKID_MAC_ADDRESS_BOOK ((uint8_t) 26)
#define NVM_BLOCKID_MAX_CNT  ((uint8_t) 27)
typedef uint8_t NVM_BlockId_t;


typedef struct {
    NVM_BlockId_t eBlock_id;
} PACKED_STRUCT nvmrestore_defaultsRequestData_t;


typedef struct {
    NVM_StandardResult_t eOp_result;
} PACKED_STRUCT nvmrestore_defaultsResponseData_t;


#endif  // #ifndef __FP_NVMPROTOCOLTYPES_H__

