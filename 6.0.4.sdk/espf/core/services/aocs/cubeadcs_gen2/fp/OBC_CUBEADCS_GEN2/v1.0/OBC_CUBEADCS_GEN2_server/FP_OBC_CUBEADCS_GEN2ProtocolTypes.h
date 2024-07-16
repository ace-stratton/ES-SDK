/*!
********************************************************************************************
* @file FP_OBC_CUBEADCS_GEN2ProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface OBC_CUBEADCS_GEN2 v1.0
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

#ifndef __FP_OBC_CUBEADCS_GEN2PROTOCOLTYPES_H__
#define __FP_OBC_CUBEADCS_GEN2PROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC_CUBEADCS_GEN2 ((uint16_t) (0x00000021))

#define OBC_CUBEADCS_GEN2_REQSTATEMACHINESTATECHANGE_FUNC_ID ((funcIdType_t) 0x0000000A)
#define OBC_CUBEADCS_GEN2_GETSTATEMACHINESTATE_FUNC_ID ((funcIdType_t) 0x0000000B)
#define OBC_CUBEADCS_GEN2_GETOPSTATUS_FUNC_ID ((funcIdType_t) 0x0000000C)
#define OBC_CUBEADCS_GEN2_REQSOFTRESETANDMODE_FUNC_ID ((funcIdType_t) 0x0000000D)
#define OBC_CUBEADCS_GEN2_GET_EVENTS_SINCE_LAST_POWER_UP_FUNC_ID ((funcIdType_t) 0x0000000E)
#define OBC_CUBEADCS_GEN2_CLEAR_EVENTS_SINCE_LAST_POWER_UP_FUNC_ID ((funcIdType_t) 0x0000000F)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_FUNC_ID ((funcIdType_t) 0x00000010)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_STATUS_FUNC_ID ((funcIdType_t) 0x00000011)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_FUNC_ID ((funcIdType_t) 0x00000012)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_STATUS_FUNC_ID ((funcIdType_t) 0x00000013)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_FUNC_ID ((funcIdType_t) 0x00000014)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_STATUS_FUNC_ID ((funcIdType_t) 0x00000015)
#define OBC_CUBEADCS_GEN2_GET_FDIR_UNRECOVARABLE_ERRORS_FUNC_ID ((funcIdType_t) 0x00000018)
#define OBC_CUBEADCS_GEN2_CLEAR_FDIR_UNRECOVARABLE_ERRORS_FUNC_ID ((funcIdType_t) 0x00000019)
#define OBC_CUBEADCS_GEN2_GET_FDIR_STATS_FUNC_ID ((funcIdType_t) 0x0000001A)
#define OBC_CUBEADCS_GEN2_CLEAR_FDIR_STATS_FUNC_ID ((funcIdType_t) 0x0000001B)
#define OBC_CUBEADCS_GEN2_GET_COMMISSIONING_STATUS_FUNC_ID ((funcIdType_t) 0x0000001C)
#define OBC_CUBEADCS_GEN2_SET_COMMISSIONING_STATUS_FUNC_ID ((funcIdType_t) 0x0000001D)
#define OBC_CUBEADCS_GEN2_GET_TLM_CFG_FUNC_ID ((funcIdType_t) 0x0000001E)
#define OBC_CUBEADCS_GEN2_SET_TLM_CFG_FUNC_ID ((funcIdType_t) 0x0000001F)
#define OBC_CUBEADCS_GEN2_GET_NVM_SYSTEM_STATES_CFG_FUNC_ID ((funcIdType_t) 0x00000020)
#define OBC_CUBEADCS_GEN2_SET_NVM_SYSTEM_STATES_CFG_FUNC_ID ((funcIdType_t) 0x00000021)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_FUNC_ID ((funcIdType_t) 0x00000022)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_STATUS_FUNC_ID ((funcIdType_t) 0x00000023)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_FUNC_ID ((funcIdType_t) 0x00000024)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_STATUS_FUNC_ID ((funcIdType_t) 0x00000025)
#define OBC_CUBEADCS_GEN2_REQSTATEMACHINESTATECHANGE_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define OBC_CUBEADCS_GEN2_GETSTATEMACHINESTATE_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define OBC_CUBEADCS_GEN2_GETOPSTATUS_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define OBC_CUBEADCS_GEN2_REQSOFTRESETANDMODE_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define OBC_CUBEADCS_GEN2_GET_EVENTS_SINCE_LAST_POWER_UP_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define OBC_CUBEADCS_GEN2_CLEAR_EVENTS_SINCE_LAST_POWER_UP_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_FUNCRESP_ID ((funcIdType_t) 0x00000010)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_EVT_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000011)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_FUNCRESP_ID ((funcIdType_t) 0x00000012)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_TLM_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000013)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_FUNCRESP_ID ((funcIdType_t) 0x00000014)
#define OBC_CUBEADCS_GEN2_DOWNLOAD_IMG_STORED_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000015)
#define OBC_CUBEADCS_GEN2_GET_FDIR_UNRECOVARABLE_ERRORS_FUNCRESP_ID ((funcIdType_t) 0x00000018)
#define OBC_CUBEADCS_GEN2_CLEAR_FDIR_UNRECOVARABLE_ERRORS_FUNCRESP_ID ((funcIdType_t) 0x00000019)
#define OBC_CUBEADCS_GEN2_GET_FDIR_STATS_FUNCRESP_ID ((funcIdType_t) 0x0000001A)
#define OBC_CUBEADCS_GEN2_CLEAR_FDIR_STATS_FUNCRESP_ID ((funcIdType_t) 0x0000001B)
#define OBC_CUBEADCS_GEN2_GET_COMMISSIONING_STATUS_FUNCRESP_ID ((funcIdType_t) 0x0000001C)
#define OBC_CUBEADCS_GEN2_SET_COMMISSIONING_STATUS_FUNCRESP_ID ((funcIdType_t) 0x0000001D)
#define OBC_CUBEADCS_GEN2_GET_TLM_CFG_FUNCRESP_ID ((funcIdType_t) 0x0000001E)
#define OBC_CUBEADCS_GEN2_SET_TLM_CFG_FUNCRESP_ID ((funcIdType_t) 0x0000001F)
#define OBC_CUBEADCS_GEN2_GET_NVM_SYSTEM_STATES_CFG_FUNCRESP_ID ((funcIdType_t) 0x00000020)
#define OBC_CUBEADCS_GEN2_SET_NVM_SYSTEM_STATES_CFG_FUNCRESP_ID ((funcIdType_t) 0x00000021)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_FUNCRESP_ID ((funcIdType_t) 0x00000022)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_COMPUTER_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000023)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_FUNCRESP_ID ((funcIdType_t) 0x00000024)
#define OBC_CUBEADCS_GEN2_FW_UPDATE_CUBE_NODE_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000025)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL_200MS ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL1S ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL2S ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL3S ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL4S ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL5S ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL_10S ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL_20S ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL_50S ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_TCTLM_CUBE_COMPUTER_COMMON_3__INTERVAL_100S ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGRETURNINTERVALVALUES_MAX_CNT  ((uint8_t) 10)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TlmLogReturnIntervalValues_t;

#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_LOGREADFILTERTYPE_TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_NONE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_LOGREADFILTERTYPE_TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_TIME_SPAN ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_LOGREADFILTERTYPE_TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_TIME_NEXT_X ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_LOGREADFILTERTYPE_TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_FIRST_X ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_LOGREADFILTERTYPE_TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_LAST_X ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_LOGREADFILTERTYPE_TCTLM_CUBE_COMPUTER_COMMON_3__FILTER_COUNTER_NEXT_X ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_LOGREADFILTERTYPE_MAX_CNT  ((uint8_t) 6)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_LogReadFilterType_t;

#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_EVENTREADQUEUESTATE_TCTLM_CUBE_COMPUTER_COMMON_3__EVT_READ_QIDLE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_EVENTREADQUEUESTATE_TCTLM_CUBE_COMPUTER_COMMON_3__EVT_READ_QDOWNLOAD ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_EVENTREADQUEUESTATE_TCTLM_CUBE_COMPUTER_COMMON_3__EVT_READ_QERASE ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_EVENTREADQUEUESTATE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_EventReadQueueState_t;

#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGREADQUEUESTATE_TCTLM_CUBE_COMPUTER_COMMON_3__TLM_READ_QIDLE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGREADQUEUESTATE_TCTLM_CUBE_COMPUTER_COMMON_3__TLM_READ_QDOWNLOAD ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGREADQUEUESTATE_TCTLM_CUBE_COMPUTER_COMMON_3__TLM_READ_QERASE ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_TLMLOGREADQUEUESTATE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TlmLogReadQueueState_t;

#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_IMAGETRANSFERSTATE_TCTLM_CUBE_COMPUTER_COMMON_3__STATE_IDLE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_IMAGETRANSFERSTATE_TCTLM_CUBE_COMPUTER_COMMON_3__STATE_BUSY_STORE ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_IMAGETRANSFERSTATE_TCTLM_CUBE_COMPUTER_COMMON_3__STATE_BUSY_DOWNLOAD ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCOMMON3_IMAGETRANSFERSTATE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_ImageTransferState_t;

#define OBC_CUBEADCS_GEN2_COMMISSIONINGSTATUS_CMS_STATUS_NOT_DONE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_COMMISSIONINGSTATUS_CMS_STATUS_COMPLETE ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_COMMISSIONINGSTATUS_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_CUBEADCS_GEN2_CommissioningStatus_t;

#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__UPGRADE_IDLE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__UPGRADE_INIT ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__UPGRADE_TRANS ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__UPGRADE_INIT_BIN ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__UPGRADE_INIT_CFG ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__UPGRADE_BUSY_BIN ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__UPGRADE_BUSY_CFG ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPUPGRADESTATE_MAX_CNT  ((uint8_t) 7)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCubeComputerControlProgram8_FtpUpgradeState_t;

#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPSTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__IDLE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPSTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__INIT ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPSTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__BUSY ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPSTATE_TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__LOCKED ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_TCTLMCUBECOMPUTERCONTROLPROGRAM8_FTPSTATE_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCubeComputerControlProgram8_FtpState_t;

#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_INVALID ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_SENSE ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_WHEEL ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_IR ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_MAG_DEPLOY ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_MAG_COMPACT ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_STAR ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_AURIGA ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_NODE ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_NODE_SLT ((uint8_t) 10)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_NODE_PST3S ((uint8_t) 11)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_NODE_NSSRWL ((uint8_t) 12)
#define OBC_CUBEADCS_GEN2_TCTLMCOMMONFRAMEWORKENUMS_NODETYPE_MAX_CNT  ((uint8_t) 13)
typedef uint8_t OBC_CUBEADCS_GEN2_TctlmCommonFrameworkEnums_NodeType_t;

typedef struct {
    uint8_t au8Name[47];
} PACKED_STRUCT OBC_CUBEADCS_GEN2_FName_t;

typedef struct {
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_LogReadFilterType_t eFilterType;
    uint32_t u32StartTimeUnix;
    uint32_t u32EndTimeUnix;
    uint32_t u32NumEntries;
    uint32_t u32WriteCounter;
    bool bIncludeClassCritical;
    bool bIncludeClassMajorWarning;
    bool bIncludeClassMinorWarning;
    bool bIncludeClassInfo;
    bool bIncludeSourceCubeComputer;
    bool bIncludeSourceRwl0;
    bool bIncludeSourceRwl1;
    bool bIncludeSourceRwl2;
    bool bIncludeSourceRwl3;
    bool bIncludeSourceFss0;
    bool bIncludeSourceFss1;
    bool bIncludeSourceFss2;
    bool bIncludeSourceFss3;
    bool bIncludeSourceHss0;
    bool bIncludeSourceHss1;
    bool bIncludeSourceStr0;
    bool bIncludeSourceStr1;
    bool bIncludeSourceMag0;
    bool bIncludeSourceMag1;
    bool bIncludeSourceExt0;
    bool bIncludeSourceExt1;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_EventLogFilterTransferSetup_t;

typedef struct {
    uint16_t u16NumberOfEntriesQueued;
    uint16_t u16NumberOfEntriesBuffered;
    uint32_t u32NumberOfEntries;
    uint32_t u32NumberOfEmptyEntries;
    uint32_t u32OldestEntryUnix;
    uint32_t u32LatestEntryUnix;
    uint32_t u32NumberOfCriticalEvents;
    uint32_t u32NumberOfMajorWarningEvents;
    uint32_t u32NumberOfMinorWarningEvents;
    uint32_t u32NumberOfInfoEvents;
    uint32_t u32WriteCounter;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_EventReadQueueState_t eReadQueueState;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_EventLogStatus_t;

typedef struct {
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_LogReadFilterType_t eFilterType;
    uint32_t u32StartTimeUnix;
    uint32_t u32EndTimeUnix;
    uint32_t u32NumEntries;
    uint32_t u32WriteCounter;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TlmLogReturnIntervalValues_t eTlmLogReturnInterval;
    uint8_t au8LogIdBitmask[5];
} PACKED_STRUCT OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TelemetryLogTransferSetup_t;

typedef struct {
    uint8_t u8NumberOfEntriesQueued;
    uint8_t u8NumberOfTlmIterations;
    uint32_t u32NumberOfEntries;
    uint32_t u32OldestEntryUnix;
    uint32_t u32LatestEntryUnix;
    uint32_t u32WriteCounter;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TlmLogReadQueueState_t eReadQueueState;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TelemtryLogStatus_t;

typedef struct {
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_ImageTransferState_t eTransfer_state;
    uint32_t u32ErrorCode;
    uint32_t u32TransferSize;
    uint32_t u32DataRemain;
    bool bInvalidNodeError;
    bool bTimeoutError;
    bool bCaptureError;
    bool bSetupError;
    bool bFileOpenReadError;
    bool bFileOpenWriteError;
    bool bFileReadError;
    bool bFileWriteError;
    bool bBusyError;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_ImageTransferStatus_t;

/*
    Errors message structure. Error information of the application
*/
typedef struct {
    uint32_t u32Result;
    uint32_t u32HalInit;
    uint32_t u32FlashInit;
    uint32_t u32Uart1Init;
    uint32_t u32Uart2Init;
    uint32_t u32Can1Init;
    uint32_t u32Can2Init;
    uint32_t u32I2cInit;
    bool bConfigInit;
    bool bTimeout;
    bool bOverrun;
    bool bErasePage;
    bool bWrite;
    bool bFileCrc;
    bool bCommitFileTable;
    bool bCommitConfigTable;
    bool bJumpTarget;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_TctlmCubeCommonBaseBootloader5_Errors_t;

/*
    File Transfer Status message structure. File Transfer Status
*/
typedef struct {
    OBC_CUBEADCS_GEN2_TctlmCubeComputerControlProgram8_FtpState_t eFtp_state;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerControlProgram8_FtpUpgradeState_t eUpgradeState;
    uint32_t u32DataRemain;
    uint32_t u32ErrorCode;
    bool bBusyError;
    bool bFileMetaError;
    bool bVersionError;
    bool bNodeExistError;
    bool bNodeExpectError;
    bool bFileCrcError;
    bool bFileSizeError;
    bool bFileError;
    bool bFileInvalidError;
    bool bFileFullError;
    bool bFileEmptyError;
    bool bReadError;
    bool bWriteError;
    bool bEraseError;
    bool bFrameSizeError;
    bool bTimeoutError;
    bool bNodeCommsError;
    bool bNodeUsedError;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_TctlmCubeComputerControlProgram8_FileTransferStatus_t;

/*
    event download status
*/
typedef struct {
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_EventLogFilterTransferSetup_t sSetup;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_EventLogStatus_t sStatus;
    OBC_CUBEADCS_GEN2_FName_t sFile_name;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_download_event_status_t;

/*
    telemetry download status
*/
typedef struct {
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TelemetryLogTransferSetup_t sSetup;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TelemtryLogStatus_t sStatus;
    OBC_CUBEADCS_GEN2_FName_t sFile_name;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_download_telemetry_status_t;

/*
    image download status
*/
typedef struct {
    uint32_t u32Err;
    uint32_t u32Setup;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_ImageTransferStatus_t sStatus;
    OBC_CUBEADCS_GEN2_FName_t sFile_name;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_download_image_stored_status_t;

/*
    cube computer control program update status
*/
typedef struct {
    uint32_t u32Err_code;
    bool bForce;
    OBC_CUBEADCS_GEN2_TctlmCubeCommonBaseBootloader5_Errors_t sStatus;
    OBC_CUBEADCS_GEN2_FName_t sControl_program_file_name;
    OBC_CUBEADCS_GEN2_FName_t sConfiguration_file_name;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_cube_computer_fw_update_status_t;

/*
    cube node control program update status
*/
typedef struct {
    uint32_t u32Err_code;
    bool bForce;
    OBC_CUBEADCS_GEN2_TctlmCommonFrameworkEnums_NodeType_t eNode_type;
    uint32_t u32Serial_int;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerControlProgram8_FileTransferStatus_t sStatus;
    OBC_CUBEADCS_GEN2_FName_t sControl_program_file_name;
    OBC_CUBEADCS_GEN2_FName_t sConfiguration_file_name;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_cube_node_fw_update_status_t;

#define OBC_CUBEADCS_GEN2_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_STANDARDRESULT_ERROR ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_CUBEADCS_GEN2_StandardResult_t;

#define OBC_CUBEADCS_GEN2_SAFEBOOL_FALSE ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_SAFEBOOL_TRUE ((uint8_t) 255)
#define OBC_CUBEADCS_GEN2_SAFEBOOL_MAX_CNT  ((uint8_t) 256)
typedef uint8_t OBC_CUBEADCS_GEN2_SafeBool_t;

/*
    State machine events.
*/
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_RESET ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_PERIODIC ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_EVENT_MARKER_ACQUIRED ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_REQUEST_STATE_CHANGE ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_REQUEST_FDIR ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_CHECK_COMPLETED ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_EVENT_DOWNLOAD_COMPLETED ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_STATE_CHANGE_COMPLETED ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_FDIR_COMPLETED ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_STATEMACHINEEVENTS_MAX_CNT  ((uint8_t) 10)
typedef uint8_t OBC_CUBEADCS_GEN2_StateMachineEvents_t;

/*
    State machine states.
*/
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_ROOT ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_BACKOFF ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_EVENT_MARKER_ACQUISITION ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_IDLE ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_CHECK ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_EVENT_DOWNLOAD ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_STATE_CHANGE ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_FDIR ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_STATEMACHINESTATES_MAX_CNT  ((uint8_t) 8)
typedef uint8_t OBC_CUBEADCS_GEN2_StateMachineStates_t;

/*
    Available control modes
*/
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_NO_CONTROL ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_1_AXIS_BDOT ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_Y_THOMSON ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_3_AXIS_BDOT ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_3_AXIS_LOW_POWER ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_SUN_Y_AXIS_SPIN_DETUMB ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_Z_THOMSON ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_SUN_Z_AXIS_SPIN_DETUMB ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_MAG_CNTRL_GG_BOOM_AND_YAW ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_MAG_CNTRL_GG_BOOM_AND_Z ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_INITIAL_Y_WHEEL_RAMP_UP ((uint8_t) 10)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_INITIAL_Y_WHEEL_PITCH_CNTRL ((uint8_t) 11)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_3_AXIS ((uint8_t) 12)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_SUN_TRACKING ((uint8_t) 13)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_EO_TARGET_TRACKING ((uint8_t) 14)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_EARTH_TARGET_STEERING ((uint8_t) 15)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_GS_TARGET_TRACKING ((uint8_t) 16)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_INERTIAL_TARGET_TRACKING ((uint8_t) 17)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_MOON_TRACKING ((uint8_t) 18)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_RW_SAT_TARGET_TRACKING ((uint8_t) 19)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_NADIR_AND_YAW_TO_SUN ((uint8_t) 20)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_NADIR_AND_YAW_TO_GROUND_TARGET ((uint8_t) 21)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_VELOCITY_AND_ROLL_TO_SUN ((uint8_t) 22)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_VELOCITY_AND_ROLL_TO_GROUND_TARGET ((uint8_t) 23)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_NADIR_AND_YAW_BEST_TO_GS ((uint8_t) 24)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_STOP_RW_CONTROLLED ((uint8_t) 50)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_OPEN_LOOP_RW ((uint8_t) 51)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_CNTRL_USER ((uint8_t) 100)
#define OBC_CUBEADCS_GEN2_CONTROLMODES_MAX_CNT  ((uint8_t) 101)
typedef uint8_t OBC_CUBEADCS_GEN2_ControlModes_t;

/*
    Available estimation modes
*/
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_NO_ESIMATOR ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_GYRO_MEASURED_RATES ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_MAG_EST_RATES ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_MAG_EST_RATES_WITH_PITCH_EST ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_TRIAD ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_FULL_STATE_EKF ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_GYRO_EKF ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_EST_USER ((uint8_t) 100)
#define OBC_CUBEADCS_GEN2_ESTIMATIONMODES_MAX_CNT  ((uint8_t) 101)
typedef uint8_t OBC_CUBEADCS_GEN2_EstimationModes_t;

/*
    Node power states
*/
#define OBC_CUBEADCS_GEN2_NODEPOWERSTATE_OFF ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_NODEPOWERSTATE_ON ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_NODEPOWERSTATE_NO_CHANGE ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_NODEPOWERSTATE_AUTO ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_NODEPOWERSTATE_POWER_ON_PASS ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_NODEPOWERSTATE_MAX_CNT  ((uint8_t) 5)
typedef uint8_t OBC_CUBEADCS_GEN2_NodePowerState_t;

/*
    ADCS Boot State
*/
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderRunning ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderBackoff ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderPortValidation ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderAutoDiscover ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderHalt ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderJump ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderExitError ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_ApplicationRunning ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderCfgUnlock ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderBootPinEn ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderBootPinDis ((uint8_t) 10)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderWrpClear ((uint8_t) 11)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderCfgUnlockError ((uint8_t) 12)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderBootPinEnError ((uint8_t) 13)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderBootPinDisError ((uint8_t) 14)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderWrpClearError ((uint8_t) 15)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderAutoDiscoverError ((uint8_t) 16)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderBankSyncError ((uint8_t) 17)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_BootloaderHaltReset ((uint8_t) 18)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_AssertError ((uint8_t) 19)
#define OBC_CUBEADCS_GEN2_BOOTSTATE_MAX_CNT  ((uint8_t) 20)
typedef uint8_t OBC_CUBEADCS_GEN2_BootState_t;

/*
    ADCS Reset Reason
*/
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetUnknown ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetFirewall ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetObl ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetExtPin ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetBrownOut ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetSoft ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetWatchdog ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetLowPower ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetEnterBootloader ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetCfgUnlock ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetBootPinEn ((uint8_t) 10)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetBootPinDis ((uint8_t) 11)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetWrpClearAll ((uint8_t) 12)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetCfgUnlockErr ((uint8_t) 13)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetBootPinEnErr ((uint8_t) 14)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetBootPinDisErr ((uint8_t) 15)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetWrpClearAllErr ((uint8_t) 16)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetBootloaderExitErr ((uint8_t) 17)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetBootloaderBankSyncErr ((uint8_t) 18)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_ResetAssertErr ((uint8_t) 19)
#define OBC_CUBEADCS_GEN2_BOOTRESETREASON_MAX_CNT  ((uint8_t) 20)
typedef uint8_t OBC_CUBEADCS_GEN2_BootResetReason_t;

/*
    ADCS Run Mode
*/
#define OBC_CUBEADCS_GEN2_ADCSRUNMODE_AdcsOff ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_ADCSRUNMODE_AdcsEnabled ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_ADCSRUNMODE_AdcsTriggered ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_ADCSRUNMODE_AdcsSimulation ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_ADCSRUNMODE_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_CUBEADCS_GEN2_AdcsRunMode_t;

/*
    ADCS Operational State
*/
#define OBC_CUBEADCS_GEN2_ADCSOPSTATE_OpStateManual ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_ADCSOPSTATE_OpStateAuto ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_ADCSOPSTATE_OpStateSafe ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_ADCSOPSTATE_OpStateFault ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_ADCSOPSTATE_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_CUBEADCS_GEN2_AdcsOpState_t;

/*
    ADCS Control Program Type
*/
#define OBC_CUBEADCS_GEN2_ADCSPROGTYPE_BOOTLOADER ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_ADCSPROGTYPE_APPLICATION ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_ADCSPROGTYPE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_CUBEADCS_GEN2_AdcsProgType_t;

/*
    Power state of all nodes
*/
typedef struct {
    OBC_CUBEADCS_GEN2_NodePowerState_t eRwl0;
    OBC_CUBEADCS_GEN2_NodePowerState_t eRwl1;
    OBC_CUBEADCS_GEN2_NodePowerState_t eRwl2;
    OBC_CUBEADCS_GEN2_NodePowerState_t eRwl3;
    OBC_CUBEADCS_GEN2_NodePowerState_t eMag0;
    OBC_CUBEADCS_GEN2_NodePowerState_t eMag1;
    OBC_CUBEADCS_GEN2_NodePowerState_t eGyro0;
    OBC_CUBEADCS_GEN2_NodePowerState_t eGyro1;
    OBC_CUBEADCS_GEN2_NodePowerState_t eFss0;
    OBC_CUBEADCS_GEN2_NodePowerState_t eFss1;
    OBC_CUBEADCS_GEN2_NodePowerState_t eFss2;
    OBC_CUBEADCS_GEN2_NodePowerState_t eFss3;
    OBC_CUBEADCS_GEN2_NodePowerState_t eHss0;
    OBC_CUBEADCS_GEN2_NodePowerState_t eHss1;
    OBC_CUBEADCS_GEN2_NodePowerState_t eStr0;
    OBC_CUBEADCS_GEN2_NodePowerState_t eStr1;
    OBC_CUBEADCS_GEN2_NodePowerState_t eExtSensor0;
    OBC_CUBEADCS_GEN2_NodePowerState_t eExtSensor1;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_PowerState_t;

/*
    Reference parameters for some control modes
*/
typedef struct {
    float fRef_param1;
    float fRef_param2;
    float fRef_param3;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_RefParams_t;

/*
    State change core arguments
*/
typedef struct {
    OBC_CUBEADCS_GEN2_ControlModes_t eControl_mode;
    OBC_CUBEADCS_GEN2_EstimationModes_t eEstimation_mode_main;
    OBC_CUBEADCS_GEN2_EstimationModes_t eEstimation_mode_backup;
    OBC_CUBEADCS_GEN2_PowerState_t sNodes_pwr_states;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_state_change_core_args_t;

/*
    State change arguments associated to the state change event type
*/
typedef struct {
    OBC_CUBEADCS_GEN2_state_change_core_args_t sCore_args;
    OBC_CUBEADCS_GEN2_RefParams_t sRef_params;
    uint8_t u8Req_state_id;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_state_change_args_t;

/*
    Boot status
*/
typedef struct {
    OBC_CUBEADCS_GEN2_BootState_t eState;
    OBC_CUBEADCS_GEN2_BootResetReason_t eResetReason;
    bool bSharedParamsError;
    bool bPortValidationError;
    bool bPortDiscoveryError;
    bool bOtpSerialError;
    bool bCfgSerialError;
    bool bSerialMismatchError;
    bool bConfigInvalidError;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_BootStatus_t;

/*
    Component Error Codes
*/
typedef struct {
    uint32_t u32MasterSvc;
    uint32_t u32FramFsSvc;
    uint32_t u32EventLogSvc;
    uint32_t u32ImgLogSvc;
    uint32_t u32TlmLogSvc;
    uint32_t u32ImuSvc;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_CompErrCodes_t;

/*
    Control mode configuration
*/
typedef struct {
    OBC_CUBEADCS_GEN2_ControlModes_t eControl_mode;
    uint16_t u16Timeout;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_ControlModeConfig_t;

/*
    Estimation mode configuration
*/
typedef struct {
    OBC_CUBEADCS_GEN2_EstimationModes_t eMain;
    OBC_CUBEADCS_GEN2_EstimationModes_t eBackup;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_EstModeConfig_t;

/*
    Common operational status telemetry for the ADCS
*/
typedef struct {
    OBC_CUBEADCS_GEN2_BootStatus_t sBoot_status;
    OBC_CUBEADCS_GEN2_PowerState_t sPower_state;
    OBC_CUBEADCS_GEN2_CompErrCodes_t sComp_err_codes;
    bool bIs_valid;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_OpStatusCommon_t;

/*
    Application operational status telemetry for the ADCS
*/
typedef struct {
    OBC_CUBEADCS_GEN2_AdcsRunMode_t eRun_mode;
    OBC_CUBEADCS_GEN2_ControlModeConfig_t sControl_mode;
    OBC_CUBEADCS_GEN2_EstModeConfig_t sEstimation_mode;
    OBC_CUBEADCS_GEN2_AdcsOpState_t eOp_state;
    bool bIs_valid;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_OpStatusApp_t;

/*
    Events counters for major and critical events.
*/
typedef struct {
    uint16_t u16Adcs_config_validation_error;
    uint16_t u16Node_setup_error;
    uint16_t u16Node_jump_error;
    uint16_t u16Mag_deploy_error;
    uint16_t u16Control_loop_failure;
    uint16_t u16Node_failure;
    uint16_t u16Config_persist_error;
    uint16_t u16Virtual_watchdog_warning;
    uint16_t u16Port_validation_error;
    uint16_t u16Auto_discovery_error;
    uint16_t u16Control_loop_critical;
    uint16_t u16Gyro_voltage_error;
    uint16_t u16Gyro_critical;
    uint16_t u16Virtual_watchdog_error;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_events_t;

/*
    Critical and Major events enumeration. Check documentation for further information.
*/
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_ADCS_CONFIG_VALIDATION_ERROR ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_NODE_SETUP_ERROR ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_NODE_JUMP_ERROR ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_MAG_DEPLOY_ERROR ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_CONTROL_LOOP_FAILURE ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_NODE_FAILURE ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_CONFIG_PERSIST_ERROR ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_VIRTUAL_WATCHDOG_WARNING ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_PORT_VALIDATION_ERROR ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_AUTO_DISCOVERY_ERROR ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_CONTROL_LOOP_CRITICAL ((uint8_t) 10)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_GYRO_VOLTAGE_ERROR ((uint8_t) 11)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_GYRO_CRITICAL ((uint8_t) 12)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_VIRTUAL_WATCHDOG_ERROR ((uint8_t) 13)
#define OBC_CUBEADCS_GEN2_EVENTS_ENUM_MAX_CNT  ((uint8_t) 14)
typedef uint8_t OBC_CUBEADCS_GEN2_events_enum_t;

/*
    FDIR stats
*/
typedef struct {
    OBC_CUBEADCS_GEN2_events_enum_t eEvent_type;
    uint8_t u8Event_fdir_execution_num;
    bool abEvent_fdir_execution_res[1];
} PACKED_STRUCT OBC_CUBEADCS_GEN2_fdir_stat_t;

/*
    Unrecovarable errors
*/
#define OBC_CUBEADCS_GEN2_UNRECOVARABLE_ERRORS_NO_ERRORS ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_UNRECOVARABLE_ERRORS_CONTROL_COMPROMISED ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_UNRECOVARABLE_ERRORS_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_CUBEADCS_GEN2_unrecovarable_errors_t;

/*
    Telemetry mask 0 of loggable frames - Check CubeSpace documentation for further information
*/
typedef struct {
    bool bEn_get_health_tlm_for_cubenode_pst3s;
    bool bEn_get_health_tlm_for_cubemag_magnetometer;
    bool bEn_get_health_tlm_for_cubesense_sun;
    bool bEn_get_torquer_current_measurements;
    bool bEn_get_raw_cubesense_sun_telemetry;
    bool bEn_get_raw_external_sensor_telemetry;
    bool bEn_get_controller_telemetry;
    bool bEn_get_backup_estimator_telemetry;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_telemetry_mask_0_t;

/*
    Telemetry mask 1 of loggable frames - Check CubeSpace documentation for further information
*/
typedef struct {
    bool bEn_get_models_telemetry;
    bool bEn_get_calibrated_gnss_sensor_telemetry;
    bool bEn_get_calibrated_hss_sensor_telemetry;
    bool bEn_get_calibrated_mag_sensor_telemetry;
    bool bEn_get_calibrated_fss_sensor_telemetry;
    bool bEn_get_raw_cubesense_earth_telemetry;
    bool bEn_get_raw_mag_sensor_telemetry;
    bool bEn_get_raw_css_sensor_telemetry;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_telemetry_mask_1_t;

/*
    Telemetry mask 2 of loggable frames - Check CubeSpace documentation for further information
*/
typedef struct {
    bool bEn_get_raw_gyr_sensor_telemetry;
    bool bEn_get_raw_rwl_sensor_telemetry;
    bool bEn_get_calibrated_css_sensor_telemetry;
    bool bEn_get_calibrated_gyr_sensor_telemetry;
    bool bEn_get_calibrated_str_sensor_telemetry;
    bool bEn_get_calibrated_rwl_sensor_telemetry;
    bool bEn_get_main_estimator_telemetry;
    bool bEn_get_main_estimator_high_resolution_telemetry;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_telemetry_mask_2_t;

/*
    Telemetry mask 3 of loggable frames - Check CubeSpace documentation for further information
*/
typedef struct {
    bool bEn_get_raw_gnss_sensor_telemetry;
    bool bEn_get_raw_pst3s_star_tracker_telemetry;
    bool bEn_get_acp_execution_telemetry;
    bool bEn_get_cubecomputer_health;
    bool bEn_get_health_telemetry_for_cubesense_earth;
    bool bEn_get_health_telemetry_for_reaction_wheels;
    bool bEn_get_health_telemetry_for_cubenode_nssrwl;
    bool bEn_get_raw_nssrwl_sensor_telemetry;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_telemetry_mask_3_t;

/*
    Telemetry mask 4 of loggable frames - Check CubeSpace documentation for further information
*/
typedef struct {
    bool bEn_get_health_telemetry_for_cubestar;
    bool bReserved_0;
    bool bReserved_1;
    bool bReserved_2;
    bool bReserved_3;
    bool bReserved_4;
    bool bReserved_5;
    bool bReserved_6;
} PACKED_STRUCT OBC_CUBEADCS_GEN2_telemetry_mask_4_t;

/*
    Predefined system states of Gen2
*/
#define OBC_CUBEADCS_GEN2_SYS_STATES_NO_CONTROL ((uint8_t) 0)
#define OBC_CUBEADCS_GEN2_SYS_STATES_NORMAL_DETUMBLING ((uint8_t) 1)
#define OBC_CUBEADCS_GEN2_SYS_STATES_Y_THOMSON ((uint8_t) 2)
#define OBC_CUBEADCS_GEN2_SYS_STATES_Y_THOMSON_MEMS_RATE ((uint8_t) 3)
#define OBC_CUBEADCS_GEN2_SYS_STATES_FAST_DETUMBLING ((uint8_t) 4)
#define OBC_CUBEADCS_GEN2_SYS_STATES_VERY_FAST_DETUMBLING ((uint8_t) 5)
#define OBC_CUBEADCS_GEN2_SYS_STATES_Y_MOMENTUM ((uint8_t) 6)
#define OBC_CUBEADCS_GEN2_SYS_STATES_Y_MOMENTUM_FULL_STATE_EKF ((uint8_t) 7)
#define OBC_CUBEADCS_GEN2_SYS_STATES_THREE_AXIS ((uint8_t) 8)
#define OBC_CUBEADCS_GEN2_SYS_STATES_SUN_TRACKING ((uint8_t) 9)
#define OBC_CUBEADCS_GEN2_SYS_STATES_TARGET_TRACKING ((uint8_t) 10)
#define OBC_CUBEADCS_GEN2_SYS_STATES_USER1 ((uint8_t) 11)
#define OBC_CUBEADCS_GEN2_SYS_STATES_USER2 ((uint8_t) 12)
#define OBC_CUBEADCS_GEN2_SYS_STATES_USER3 ((uint8_t) 13)
#define OBC_CUBEADCS_GEN2_SYS_STATES_MAX_CNT  ((uint8_t) 14)
typedef uint8_t OBC_CUBEADCS_GEN2_sys_states_t;


typedef struct {
    OBC_CUBEADCS_GEN2_StateMachineEvents_t eSm_event;
    OBC_CUBEADCS_GEN2_state_change_args_t sState_change_event_args;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqStateMachineStateChangeRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_AdcsProgType_t eProg_type;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqSoftResetAndModeRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_FName_t sFile_name;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_EventLogFilterTransferSetup_t sSetup;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_evtRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_FName_t sFile_name;
    OBC_CUBEADCS_GEN2_TctlmCubeComputerCommon3_TelemetryLogTransferSetup_t sSetup;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_tlmRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_FName_t sFile_name;
    uint32_t u32File_handle;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_img_storedRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_CommissioningStatus_t eStatus;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_commissioning_statusRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_telemetry_mask_0_t sMask_0;
    OBC_CUBEADCS_GEN2_telemetry_mask_1_t sMask_1;
    OBC_CUBEADCS_GEN2_telemetry_mask_2_t sMask_2;
    OBC_CUBEADCS_GEN2_telemetry_mask_3_t sMask_3;
    OBC_CUBEADCS_GEN2_telemetry_mask_4_t sMask_4;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_tlm_cfgRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_sys_states_t eSys_state_to_get;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_nvm_system_states_cfgRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_state_change_core_args_t sSys_states_cfg;
    OBC_CUBEADCS_GEN2_sys_states_t eSys_state_to_set;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_nvm_system_states_cfgRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_FName_t sControl_program_file_name;
    OBC_CUBEADCS_GEN2_FName_t sConfiguration_file_name;
    bool bForce;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_computerRequestData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_FName_t sControl_program_file_name;
    OBC_CUBEADCS_GEN2_FName_t sConfiguration_file_name;
    bool bForce;
    OBC_CUBEADCS_GEN2_TctlmCommonFrameworkEnums_NodeType_t eNode_type;
    uint32_t u32Serial_int;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_nodeRequestData_t;


typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqStateMachineStateChangeResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StateMachineStates_t eSm_state;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2getStateMachineStateResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_OpStatusCommon_t sOp_status_common;
    OBC_CUBEADCS_GEN2_OpStatusApp_t sOp_status_app;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2getOpStatusResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2reqSoftResetAndModeResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_events_t sAll_events;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_events_since_last_power_upResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_events_since_last_power_upResponseData_t;

typedef struct {
    uint32_t u32Err;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_evtResponseData_t;

typedef struct {
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_download_event_status_t sStatus;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_evt_statusResponseData_t;

typedef struct {
    uint32_t u32Err;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_tlmResponseData_t;

typedef struct {
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_download_telemetry_status_t sStatus;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_tlm_statusResponseData_t;

typedef struct {
    uint32_t u32Err;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_img_storedResponseData_t;

typedef struct {
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_download_image_stored_status_t sStatus;
} PACKED_STRUCT OBC_CUBEADCS_GEN2download_img_stored_statusResponseData_t;

typedef struct {
    uint32_t u32Errors;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_fdir_unrecovarable_errorsResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_fdir_unrecovarable_errorsResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_fdir_stat_t asFdir_logic[14];
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_fdir_statsResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2clear_fdir_statsResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_CommissioningStatus_t eStatus;
    OBC_CUBEADCS_GEN2_StandardResult_t eOpResult;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_commissioning_statusResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOpResult;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_commissioning_statusResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_telemetry_mask_0_t sMask_0;
    OBC_CUBEADCS_GEN2_telemetry_mask_1_t sMask_1;
    OBC_CUBEADCS_GEN2_telemetry_mask_2_t sMask_2;
    OBC_CUBEADCS_GEN2_telemetry_mask_3_t sMask_3;
    OBC_CUBEADCS_GEN2_telemetry_mask_4_t sMask_4;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_tlm_cfgResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_tlm_cfgResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_state_change_core_args_t sSys_states_cfg;
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2get_nvm_system_states_cfgResponseData_t;

typedef struct {
    OBC_CUBEADCS_GEN2_StandardResult_t eOp_result;
} PACKED_STRUCT OBC_CUBEADCS_GEN2set_nvm_system_states_cfgResponseData_t;

typedef struct {
    uint32_t u32Err;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_computerResponseData_t;

typedef struct {
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_cube_computer_fw_update_status_t sStatus;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_computer_statusResponseData_t;

typedef struct {
    uint32_t u32Err;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_nodeResponseData_t;

typedef struct {
    uint32_t u32Err;
    OBC_CUBEADCS_GEN2_cube_node_fw_update_status_t sStatus;
} PACKED_STRUCT OBC_CUBEADCS_GEN2fw_update_cube_node_statusResponseData_t;


#endif  // #ifndef __FP_OBC_CUBEADCS_GEN2PROTOCOLTYPES_H__

