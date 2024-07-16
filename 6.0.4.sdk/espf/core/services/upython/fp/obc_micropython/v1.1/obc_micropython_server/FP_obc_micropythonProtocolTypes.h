/*!
********************************************************************************************
* @file FP_obc_micropythonProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface obc_micropython v1.1
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

#ifndef __FP_OBC_MICROPYTHONPROTOCOLTYPES_H__
#define __FP_OBC_MICROPYTHONPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC_MICROPYTHON ((uint16_t) (0x00000045))

#define OBC_MICROPYTHON_REQUESTSCRIPTEXECUTION_FUNC_ID ((funcIdType_t) 0x00000001)
#define OBC_MICROPYTHON_GETSCRIPTEXECSTATUS_FUNC_ID ((funcIdType_t) 0x00000002)
#define OBC_MICROPYTHON_REQUESTSCRIPTEXECUTION_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define OBC_MICROPYTHON_GETSCRIPTEXECSTATUS_FUNCRESP_ID ((funcIdType_t) 0x00000002)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define OBC_MICROPYTHON_RESULT_OK ((uint8_t) 0)
#define OBC_MICROPYTHON_RESULT_PROCESSING ((uint8_t) 1)
#define OBC_MICROPYTHON_RESULT_QUEUE_FULL ((uint8_t) 2)
#define OBC_MICROPYTHON_RESULT_PENDING ((uint8_t) 3)
#define OBC_MICROPYTHON_RESULT_FAIL ((uint8_t) 4)
#define OBC_MICROPYTHON_RESULT_TIMED_OUT ((uint8_t) 5)
#define OBC_MICROPYTHON_RESULT_NOT_FOUND_IN_QUEUE ((uint8_t) 6)
#define OBC_MICROPYTHON_RESULT_MAX_CNT  ((uint8_t) 7)
typedef uint8_t OBC_MICROPYTHON_Result_t;

/*
    Time as returned by the OBC
*/
typedef struct {
    uint8_t u8Hour;
    uint8_t u8Min;
    uint8_t u8Sec;
    uint16_t u16Ms;
    uint16_t u16Us;
} PACKED_STRUCT OBC_MICROPYTHON_stime_t;


typedef struct {
    uint8_t u8Script_full_nameSize;
    char strScript_full_name[47];
    uint32_t u32Timeout_ms;
} PACKED_STRUCT obc_micropythonRequestScriptExecutionRequestData_t;

typedef struct {
    uint8_t u8Script_id;
} PACKED_STRUCT obc_micropythonGetScriptExecStatusRequestData_t;


typedef struct {
    uint8_t u8Script_id;
    OBC_MICROPYTHON_Result_t eOp_result;
} PACKED_STRUCT obc_micropythonRequestScriptExecutionResponseData_t;

typedef struct {
    uint8_t u8Script_full_nameSize;
    char strScript_full_name[47];
    OBC_MICROPYTHON_Result_t eOp_result;
    OBC_MICROPYTHON_stime_t sRequested_time;
    OBC_MICROPYTHON_stime_t sTime_started;
    uint32_t u32Duration_ms;
} PACKED_STRUCT obc_micropythonGetScriptExecStatusResponseData_t;


#endif  // #ifndef __FP_OBC_MICROPYTHONPROTOCOLTYPES_H__

