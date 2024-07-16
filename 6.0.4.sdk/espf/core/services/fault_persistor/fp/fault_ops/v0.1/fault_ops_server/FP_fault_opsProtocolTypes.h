/*!
********************************************************************************************
* @file FP_fault_opsProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface fault_ops v0.1
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

#ifndef __FP_FAULT_OPSPROTOCOLTYPES_H__
#define __FP_FAULT_OPSPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_FAULT_OPS ((uint16_t) (0x000000C8))

#define FAULT_OPS_GET_FAULT_INFO_FUNC_ID ((funcIdType_t) 0x00000000)
#define FAULT_OPS_READ_FAULT_BY_INDEX_RAW_FUNC_ID ((funcIdType_t) 0x00000001)
#define FAULT_OPS_CLEAR_ALL_FAULTS_FUNC_ID ((funcIdType_t) 0x00000002)
#define FAULT_OPS_SIMULATE_FAULT_FUNC_ID ((funcIdType_t) 0x00000003)
#define FAULT_OPS_READ_FAULT_BY_INDEX_FUNC_ID ((funcIdType_t) 0x00000004)
#define FAULT_OPS_GET_FAULT_INFO_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define FAULT_OPS_READ_FAULT_BY_INDEX_RAW_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define FAULT_OPS_CLEAR_ALL_FAULTS_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define FAULT_OPS_SIMULATE_FAULT_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define FAULT_OPS_READ_FAULT_BY_INDEX_FUNCRESP_ID ((funcIdType_t) 0x00000004)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
typedef struct {
    uint32_t u32R0;
    uint32_t u32R1;
    uint32_t u32R2;
    uint32_t u32R3;
    uint32_t u32R12;
    uint32_t u32Lr;
    uint32_t u32Pc;
    uint32_t u32Psr;
} PACKED_STRUCT FAULT_OPS_basic_x_frame_t;

typedef struct {
    FAULT_OPS_basic_x_frame_t sBasic_regs;
    uint32_t au32Fp_ext_reg_s[16];
    uint32_t u32Fpscr;
} PACKED_STRUCT FAULT_OPS_extended_x_frame_t;

typedef struct {
    uint32_t u32Record_type;
    uint8_t au8Reserved[4];
    uint32_t u32Rtc_timestamp;
    uint32_t u32Uptime;
} PACKED_STRUCT FAULT_OPS_x_header_t;

typedef struct {
    FAULT_OPS_x_header_t sHdr;
    uint32_t u32Cfsr;
    uint32_t u32Hfsr;
    uint32_t u32Mmfar;
    uint32_t u32Bfar;
    uint32_t u32Abfsr;
    uint32_t u32Sp;
    uint32_t u32Vtor;
    uint32_t u32Stack_frame_len;
    FAULT_OPS_extended_x_frame_t sStack_frame;
    uint32_t u32Crc;
} PACKED_STRUCT FAULT_OPS_x_frame_t;

#define FAULT_OPS_FAULTTYPE_USAGE_FAULT ((uint8_t) 0)
#define FAULT_OPS_FAULTTYPE_MEM_FAULT ((uint8_t) 1)
#define FAULT_OPS_FAULTTYPE_BUS_FAULT ((uint8_t) 2)
#define FAULT_OPS_FAULTTYPE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t FAULT_OPS_FaultType_t;


typedef struct {
    uint8_t u8Slot_id;
} PACKED_STRUCT fault_opsread_fault_by_index_rawRequestData_t;

typedef struct {
    FAULT_OPS_FaultType_t eFault_type;
} PACKED_STRUCT fault_opssimulate_faultRequestData_t;

typedef struct {
    uint8_t u8Slot_id;
} PACKED_STRUCT fault_opsread_fault_by_indexRequestData_t;


typedef struct {
    uint8_t u8Occupied_fault_slots;
    uint8_t u8Available_fault_slots;
} PACKED_STRUCT fault_opsget_fault_infoResponseData_t;

typedef struct {
    bool bIs_data_valid;
    uint8_t au8Exception_data_raw[152];
} PACKED_STRUCT fault_opsread_fault_by_index_rawResponseData_t;

typedef struct {
    bool bIs_clear_ok;
} PACKED_STRUCT fault_opsclear_all_faultsResponseData_t;

typedef struct {
    bool bIs_data_valid;
    FAULT_OPS_x_frame_t sException_data;
} PACKED_STRUCT fault_opsread_fault_by_indexResponseData_t;


#endif  // #ifndef __FP_FAULT_OPSPROTOCOLTYPES_H__

