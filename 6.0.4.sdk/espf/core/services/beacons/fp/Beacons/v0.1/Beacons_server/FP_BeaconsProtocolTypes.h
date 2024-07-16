/*!
********************************************************************************************
* @file FP_BeaconsProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface Beacons v0.1
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

#ifndef __FP_BEACONSPROTOCOLTYPES_H__
#define __FP_BEACONSPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_BEACONS ((uint16_t) (0x00000101))

#define BEACONS_GETBEACONGENERALCONFIG_FUNC_ID ((funcIdType_t) 0x00000000)
#define BEACONS_SETBEACONGENERALCONFIG_FUNC_ID ((funcIdType_t) 0x00000001)
#define BEACONS_GETBEACONPRESETCONFIG_FUNC_ID ((funcIdType_t) 0x00000002)
#define BEACONS_SETBEACONPRESETCONFIG_FUNC_ID ((funcIdType_t) 0x00000003)
#define BEACONS_SETACTIVEPRESET_FUNC_ID ((funcIdType_t) 0x00000004)
#define BEACONS_GETACTIVEPRESET_FUNC_ID ((funcIdType_t) 0x00000005)
#define BEACONS_RESTOREACTIVEPRESET_FUNC_ID ((funcIdType_t) 0x00000006)
#define BEACONS_GETBEACONGENERALCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define BEACONS_SETBEACONGENERALCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define BEACONS_GETBEACONPRESETCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define BEACONS_SETBEACONPRESETCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define BEACONS_SETACTIVEPRESET_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define BEACONS_GETACTIVEPRESET_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define BEACONS_RESTOREACTIVEPRESET_FUNCRESP_ID ((funcIdType_t) 0x00000006)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Standard result enumeration which can be used in most situations as a return code
*/
#define BEACONS_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define BEACONS_STANDARDRESULT_ERROR ((uint8_t) 1)
#define BEACONS_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define BEACONS_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define BEACONS_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t BEACONS_StandardResult_t;

/*
    Increased-Hamming-distance-version of the regular boolean type. Used to represent regular boolean values.
*/
#define BEACONS_SAFE_BOOL_SAFE_FALSE ((uint8_t) 0)
#define BEACONS_SAFE_BOOL_SAFE_TRUE ((uint8_t) 255)
#define BEACONS_SAFE_BOOL_MAX_CNT  ((uint8_t) 256)
typedef uint8_t BEACONS_safe_bool_t;

/*
    This type describes the radio beacon feature persistent configuration settings
*/
typedef struct {
    BEACONS_safe_bool_t eBeacons_en;
    BEACONS_safe_bool_t eChunk_based_transfer_en;
    uint32_t u32Bcn_tx_period;
    uint32_t u32Bcn_inter_frame_period;
} PACKED_STRUCT BEACONS_bcn_general_cfg_t;


typedef struct {
    BEACONS_bcn_general_cfg_t sCfg;
} PACKED_STRUCT BeaconssetBeaconGeneralConfigRequestData_t;

typedef struct {
    uint16_t au16Beacon_preset_cfg[80];
} PACKED_STRUCT BeaconssetBeaconPresetConfigRequestData_t;

typedef struct {
    uint8_t u8Req_active_preset;
} PACKED_STRUCT BeaconssetActivePresetRequestData_t;


typedef struct {
    BEACONS_bcn_general_cfg_t sCfg;
} PACKED_STRUCT BeaconsgetBeaconGeneralConfigResponseData_t;

typedef struct {
    BEACONS_StandardResult_t eRes;
} PACKED_STRUCT BeaconssetBeaconGeneralConfigResponseData_t;

typedef struct {
    uint8_t u8Slot_preset_cnt;
    uint8_t u8Max_bcn_msg_cnt;
    uint16_t au16Beacon_preset_cfg[80];
} PACKED_STRUCT BeaconsgetBeaconPresetConfigResponseData_t;

typedef struct {
    BEACONS_StandardResult_t eRes;
    uint8_t au8Preset_error_slot_index[4];
} PACKED_STRUCT BeaconssetBeaconPresetConfigResponseData_t;

typedef struct {
    BEACONS_StandardResult_t eRes;
    uint8_t u8Avail_presets_cnt;
} PACKED_STRUCT BeaconssetActivePresetResponseData_t;

typedef struct {
    uint8_t u8Active_preset_id;
} PACKED_STRUCT BeaconsgetActivePresetResponseData_t;

typedef struct {
    BEACONS_StandardResult_t eRes;
} PACKED_STRUCT BeaconsrestoreActivePresetResponseData_t;


#endif  // #ifndef __FP_BEACONSPROTOCOLTYPES_H__

