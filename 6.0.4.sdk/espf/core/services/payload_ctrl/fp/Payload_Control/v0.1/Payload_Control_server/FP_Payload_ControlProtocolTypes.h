/*!
********************************************************************************************
* @file FP_Payload_ControlProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface Payload_Control v0.1
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

#ifndef __FP_PAYLOAD_CONTROLPROTOCOLTYPES_H__
#define __FP_PAYLOAD_CONTROLPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_PAYLOAD_CONTROL ((uint16_t) (0x0000006F))

#define PAYLOAD_CONTROL_STARTPAYLOAD_FUNC_ID ((funcIdType_t) 0x00000000)
#define PAYLOAD_CONTROL_STOPPAYLOAD_FUNC_ID ((funcIdType_t) 0x00000001)
#define PAYLOAD_CONTROL_GETPAYLOADINFO_FUNC_ID ((funcIdType_t) 0x00000002)
#define PAYLOAD_CONTROL_STARTPAYLOAD_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define PAYLOAD_CONTROL_STOPPAYLOAD_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define PAYLOAD_CONTROL_GETPAYLOADINFO_FUNCRESP_ID ((funcIdType_t) 0x00000002)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_NOT_INIT ((uint8_t) 0)
#define PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_INVALID_PL_ID ((uint8_t) 1)
#define PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_REFUSE_CMD ((uint8_t) 2)
#define PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_FAILED ((uint8_t) 3)
#define PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_OK ((uint8_t) 4)
#define PAYLOAD_CONTROL_PAYLOAD_OP_RESULT_MAX_CNT  ((uint8_t) 5)
typedef uint8_t PAYLOAD_CONTROL_payload_op_result_t;

#define PAYLOAD_CONTROL_PAYLOAD_STATE_NOT_INIT ((uint8_t) 0)
#define PAYLOAD_CONTROL_PAYLOAD_STATE_STOPPED ((uint8_t) 1)
#define PAYLOAD_CONTROL_PAYLOAD_STATE_STARTED ((uint8_t) 2)
#define PAYLOAD_CONTROL_PAYLOAD_STATE_STARTING ((uint8_t) 3)
#define PAYLOAD_CONTROL_PAYLOAD_STATE_STOPPING ((uint8_t) 4)
#define PAYLOAD_CONTROL_PAYLOAD_STATE_ERROR ((uint8_t) 5)
#define PAYLOAD_CONTROL_PAYLOAD_STATE_MAX_CNT  ((uint8_t) 6)
typedef uint8_t PAYLOAD_CONTROL_payload_state_t;

#define PAYLOAD_CONTROL_STOP_MODE_NORMAL ((uint8_t) 0)
#define PAYLOAD_CONTROL_STOP_MODE_EMERGENCY ((uint8_t) 255)
#define PAYLOAD_CONTROL_STOP_MODE_MAX_CNT  ((uint8_t) 256)
typedef uint8_t PAYLOAD_CONTROL_stop_mode_t;

typedef struct {
    PAYLOAD_CONTROL_payload_state_t ePl_state;
    uint32_t u32Last_error_code;
} PACKED_STRUCT PAYLOAD_CONTROL_payload_info_t;


typedef struct {
    uint8_t u8Payload_id;
    uint16_t u16Adcs_prep_time;
    uint8_t u8Cntrl_mode;
} PACKED_STRUCT Payload_ControlstartPayloadRequestData_t;

typedef struct {
    uint8_t u8Payload_id;
    PAYLOAD_CONTROL_stop_mode_t eReq_stop_mode;
} PACKED_STRUCT Payload_ControlstopPayloadRequestData_t;

typedef struct {
    uint8_t u8Payload_id;
} PACKED_STRUCT Payload_ControlgetPayloadInfoRequestData_t;


typedef struct {
    PAYLOAD_CONTROL_payload_op_result_t eOp_result;
} PACKED_STRUCT Payload_ControlstartPayloadResponseData_t;

typedef struct {
    PAYLOAD_CONTROL_payload_op_result_t eOp_result;
} PACKED_STRUCT Payload_ControlstopPayloadResponseData_t;

typedef struct {
    PAYLOAD_CONTROL_payload_info_t sInfo;
} PACKED_STRUCT Payload_ControlgetPayloadInfoResponseData_t;


#endif  // #ifndef __FP_PAYLOAD_CONTROLPROTOCOLTYPES_H__

