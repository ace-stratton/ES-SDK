/*!
********************************************************************************************
* @file FP_EPS1ProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface EPS1 v0.1
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

#ifndef __FP_EPS1PROTOCOLTYPES_H__
#define __FP_EPS1PROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_EPS1 ((uint16_t) (0x0000000A))

#define EPS1_GETSOFTWAREVERSION_FUNC_ID ((funcIdType_t) 0x00000000)
#define EPS1_GETBATTERYINFO_FUNC_ID ((funcIdType_t) 0x00000001)
#define EPS1_GETBUSESINFO_FUNC_ID ((funcIdType_t) 0x00000002)
#define EPS1_GETSOLARPANELSINFO_FUNC_ID ((funcIdType_t) 0x00000003)
#define EPS1_GETSTATISTICINFO_FUNC_ID ((funcIdType_t) 0x00000004)
#define EPS1_GETTEMPERATURESINFO_FUNC_ID ((funcIdType_t) 0x00000005)
#define EPS1_GETCONFIGURATIONINFO_FUNC_ID ((funcIdType_t) 0x00000006)
#define EPS1_QUERYCONTROLS_FUNC_ID ((funcIdType_t) 0x00000007)
#define EPS1_QUERYRBATRAW_FUNC_ID ((funcIdType_t) 0x00000008)
#define EPS1_QUERYDEFAULTS_FUNC_ID ((funcIdType_t) 0x00000009)
#define EPS1_QUERYLAUNCHSTATE_FUNC_ID ((funcIdType_t) 0x0000000A)
#define EPS1_QUERYWATCHDOG_FUNC_ID ((funcIdType_t) 0x0000000B)
#define EPS1_RESETWATCHDOG_FUNC_ID ((funcIdType_t) 0x0000000C)
#define EPS1_RESETPOWERSUPPLY_FUNC_ID ((funcIdType_t) 0x0000000D)
#define EPS1_SETSERIALNUMBER_FUNC_ID ((funcIdType_t) 0x0000000E)
#define EPS1_GETSERIALNUMBER_FUNC_ID ((funcIdType_t) 0x0000000F)
#define EPS1_HELLMODEREAD_FUNC_ID ((funcIdType_t) 0x00000010)
#define EPS1_HELLMODEWRITE_FUNC_ID ((funcIdType_t) 0x00000011)
#define EPS1_HEATERSSETTINGSREAD_FUNC_ID ((funcIdType_t) 0x00000012)
#define EPS1_HEATERSSETTINGSWRITE_FUNC_ID ((funcIdType_t) 0x00000013)
#define EPS1_TOGGLEOUTPUT_FUNC_ID ((funcIdType_t) 0x00000014)
#define EPS1_NOTIFICATIONSSETTINGS_FUNC_ID ((funcIdType_t) 0x00000015)
#define EPS1_GETTELEMETRYALTOGETHER_FUNC_ID ((funcIdType_t) 0x00000016)
#define EPS1_BLOAD_GETVERSION_FUNC_ID ((funcIdType_t) 0x10000000)
#define EPS1_BLOAD_ERASEFLASH_FUNC_ID ((funcIdType_t) 0x10000001)
#define EPS1_BLOAD_WRITEFLASH_FUNC_ID ((funcIdType_t) 0x10000002)
#define EPS1_BLOAD_EXECUTE_FUNC_ID ((funcIdType_t) 0x10000003)
#define EPS1_GETSOFTWAREVERSION_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define EPS1_GETBATTERYINFO_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define EPS1_GETBUSESINFO_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define EPS1_GETSOLARPANELSINFO_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define EPS1_GETSTATISTICINFO_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define EPS1_GETTEMPERATURESINFO_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define EPS1_GETCONFIGURATIONINFO_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define EPS1_QUERYCONTROLS_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define EPS1_QUERYRBATRAW_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define EPS1_QUERYDEFAULTS_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define EPS1_QUERYLAUNCHSTATE_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define EPS1_QUERYWATCHDOG_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define EPS1_RESETWATCHDOG_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define EPS1_RESETPOWERSUPPLY_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define EPS1_SETSERIALNUMBER_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define EPS1_GETSERIALNUMBER_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define EPS1_HELLMODEREAD_FUNCRESP_ID ((funcIdType_t) 0x00000010)
#define EPS1_HELLMODEWRITE_FUNCRESP_ID ((funcIdType_t) 0x00000011)
#define EPS1_HEATERSSETTINGSREAD_FUNCRESP_ID ((funcIdType_t) 0x00000012)
#define EPS1_HEATERSSETTINGSWRITE_FUNCRESP_ID ((funcIdType_t) 0x00000013)
#define EPS1_TOGGLEOUTPUT_FUNCRESP_ID ((funcIdType_t) 0x00000014)
#define EPS1_NOTIFICATIONSSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x00000015)
#define EPS1_GETTELEMETRYALTOGETHER_FUNCRESP_ID ((funcIdType_t) 0x00000016)
#define EPS1_BLOAD_GETVERSION_FUNCRESP_ID ((funcIdType_t) 0x10000000)
#define EPS1_BLOAD_ERASEFLASH_FUNCRESP_ID ((funcIdType_t) 0x10000001)
#define EPS1_BLOAD_WRITEFLASH_FUNCRESP_ID ((funcIdType_t) 0x10000002)
#define EPS1_BLOAD_EXECUTE_FUNCRESP_ID ((funcIdType_t) 0x10000003)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Helper from getSoftwareVersion, version variant
                          0xFF for development state
                          0x00 for release candidate
                          1..100 for major version number
                          101-254 reserved
*/
#define EPS1_VERSIONVARIANT_DevelopmentState ((uint8_t) 255)
#define EPS1_VERSIONVARIANT_ReleaseCandidate ((uint8_t) 0)
#define EPS1_VERSIONVARIANT_Release ((uint8_t) 1)
#define EPS1_VERSIONVARIANT_MAX_CNT  ((uint8_t) 256)
typedef uint8_t EPS1_VersionVariant_t;

/*
    Helper structure to hold pair voltage/current. The returned values correspond to raw values and shall be calibrated by the user through the following calibration coefficients and formulas (when applicable).
*/
typedef struct {
    uint16_t u16Volt;
    uint16_t u16Curr;
} PACKED_STRUCT EPS1_VA_Pair_t;

/*
    Helper structure to keep voltage, negative and positive current. The returned values correspond to raw values and shall be calibrated by the user through the following calibration coefficients and formulas (when applicable).
*/
typedef struct {
    uint16_t u16Volt;
    uint16_t u16Curr_neg;
    uint16_t u16Curr_pos;
} PACKED_STRUCT EPS1_VAA_Pack_t;

/*
    Helper structure to keep counters for "getStatisticInfo"
*/
typedef struct {
    uint32_t u32PowerOn;
    uint32_t u32ChargeCycle;
    uint32_t u32UnderVoltage;
    uint32_t u32ShortcutCircuit;
    uint32_t u32Overtemperature;
} PACKED_STRUCT EPS1_Statistic_Counters_t;

/*
    Helper description from "queryControls" and "queryDefaults"
*/
#define EPS1_QUERYSTATE_Ignored ((uint8_t) 0)
#define EPS1_QUERYSTATE_Off ((uint8_t) 1)
#define EPS1_QUERYSTATE_On ((uint8_t) 2)
#define EPS1_QUERYSTATE_Default ((uint8_t) 3)
#define EPS1_QUERYSTATE_ForceOff ((uint8_t) 5)
#define EPS1_QUERYSTATE_ForceOn ((uint8_t) 6)
#define EPS1_QUERYSTATE_ValueMask ((uint8_t) 15)
#define EPS1_QUERYSTATE_FlagsMask ((uint8_t) 192)
#define EPS1_QUERYSTATE_Reserved ((uint8_t) 64)
#define EPS1_QUERYSTATE_Mismatch ((uint8_t) 128)
#define EPS1_QUERYSTATE_MAX_CNT  ((uint8_t) 193)
typedef uint8_t EPS1_QueryState_t;

/*
    Helper enum for accessing "queryControls" elements by named index
*/
#define EPS1_QUERYCONTROLSINDEX_SWSelfLock ((uint8_t) 0)
#define EPS1_QUERYCONTROLSINDEX_VBattEn ((uint8_t) 1)
#define EPS1_QUERYCONTROLSINDEX_BCROutEn ((uint8_t) 2)
#define EPS1_QUERYCONTROLSINDEX_SHD_3v3 ((uint8_t) 3)
#define EPS1_QUERYCONTROLSINDEX_SHD_5v ((uint8_t) 4)
#define EPS1_QUERYCONTROLSINDEX_LUP3v3 ((uint8_t) 5)
#define EPS1_QUERYCONTROLSINDEX_LUP5v ((uint8_t) 6)
#define EPS1_QUERYCONTROLSINDEX_SHDChrg ((uint8_t) 7)
#define EPS1_QUERYCONTROLSINDEX_Chrg_I1 ((uint8_t) 8)
#define EPS1_QUERYCONTROLSINDEX_Chrg_I2 ((uint8_t) 9)
#define EPS1_QUERYCONTROLSINDEX_OUT1 ((uint8_t) 10)
#define EPS1_QUERYCONTROLSINDEX_OUT2 ((uint8_t) 11)
#define EPS1_QUERYCONTROLSINDEX_OUT3 ((uint8_t) 12)
#define EPS1_QUERYCONTROLSINDEX_OUT4_OBC ((uint8_t) 13)
#define EPS1_QUERYCONTROLSINDEX_OUT5 ((uint8_t) 14)
#define EPS1_QUERYCONTROLSINDEX_OUT6 ((uint8_t) 15)
#define EPS1_QUERYCONTROLSINDEX_Heater_1 ((uint8_t) 16)
#define EPS1_QUERYCONTROLSINDEX_Heater_2 ((uint8_t) 17)
#define EPS1_QUERYCONTROLSINDEX_Heater_3 ((uint8_t) 18)
#define EPS1_QUERYCONTROLSINDEX_I2C_10k_pu ((uint8_t) 19)
#define EPS1_QUERYCONTROLSINDEX_I2C_4k7_pu ((uint8_t) 20)
#define EPS1_QUERYCONTROLSINDEX_RS485_120R ((uint8_t) 21)
#define EPS1_QUERYCONTROLSINDEX_Reserved ((uint8_t) 22)
#define EPS1_QUERYCONTROLSINDEX_OUT7 ((uint8_t) 23)
#define EPS1_QUERYCONTROLSINDEX_OUT8 ((uint8_t) 24)
#define EPS1_QUERYCONTROLSINDEX_RESET_MPPT ((uint8_t) 25)
#define EPS1_QUERYCONTROLSINDEX_MAX_CNT  ((uint8_t) 26)
typedef uint8_t EPS1_QueryControlsIndex_t;

/*
    Helper enumeration for accessing "queryDefaults" elements by named index
*/
#define EPS1_QUERYDEFAULTSINDEX_LUP3v3 ((uint8_t) 0)
#define EPS1_QUERYDEFAULTSINDEX_LUP5v ((uint8_t) 1)
#define EPS1_QUERYDEFAULTSINDEX_Reserved1 ((uint8_t) 2)
#define EPS1_QUERYDEFAULTSINDEX_Chrg_I1 ((uint8_t) 3)
#define EPS1_QUERYDEFAULTSINDEX_Chrg_I2 ((uint8_t) 4)
#define EPS1_QUERYDEFAULTSINDEX_Reserved2 ((uint8_t) 5)
#define EPS1_QUERYDEFAULTSINDEX_Out_1 ((uint8_t) 6)
#define EPS1_QUERYDEFAULTSINDEX_Out_2 ((uint8_t) 7)
#define EPS1_QUERYDEFAULTSINDEX_Out_3 ((uint8_t) 8)
#define EPS1_QUERYDEFAULTSINDEX_Out_4_OBC ((uint8_t) 9)
#define EPS1_QUERYDEFAULTSINDEX_Out_5 ((uint8_t) 10)
#define EPS1_QUERYDEFAULTSINDEX_Out_6 ((uint8_t) 11)
#define EPS1_QUERYDEFAULTSINDEX_I2C_10k_pu ((uint8_t) 12)
#define EPS1_QUERYDEFAULTSINDEX_I2C_4k7_pu ((uint8_t) 13)
#define EPS1_QUERYDEFAULTSINDEX_RS485_120R ((uint8_t) 14)
#define EPS1_QUERYDEFAULTSINDEX_Out_7 ((uint8_t) 15)
#define EPS1_QUERYDEFAULTSINDEX_Out_8 ((uint8_t) 16)
#define EPS1_QUERYDEFAULTSINDEX_MAC_Driver ((uint8_t) 17)
#define EPS1_QUERYDEFAULTSINDEX_MAX_CNT  ((uint8_t) 18)
typedef uint8_t EPS1_QueryDefaultsIndex_t;

/*
    Bootloader return codes
*/
#define EPS1_BLOAD_RETCODE_Success ((uint8_t) 0)
#define EPS1_BLOAD_RETCODE_Not_Erased ((uint8_t) 1)
#define EPS1_BLOAD_RETCODE_Not_Supported ((uint8_t) 2)
#define EPS1_BLOAD_RETCODE_Wrong_Addr ((uint8_t) 3)
#define EPS1_BLOAD_RETCODE_Verify_Failure ((uint8_t) 4)
#define EPS1_BLOAD_RETCODE_No_Data ((uint8_t) 5)
#define EPS1_BLOAD_RETCODE_Decode_Failure ((uint8_t) 6)
#define EPS1_BLOAD_RETCODE_MAX_CNT  ((uint8_t) 7)
typedef uint8_t EPS1_BLoad_RetCode_t;

/*
    Watchdog type
*/
#define EPS1_WATCHDOGTYPE_Ignored ((uint8_t) 0)
#define EPS1_WATCHDOGTYPE_Disabled ((uint8_t) 1)
#define EPS1_WATCHDOGTYPE_Payload_Auto ((uint8_t) 2)
#define EPS1_WATCHDOGTYPE_Payload_On ((uint8_t) 3)
#define EPS1_WATCHDOGTYPE_System_Auto ((uint8_t) 4)
#define EPS1_WATCHDOGTYPE_System_On ((uint8_t) 5)
#define EPS1_WATCHDOGTYPE_MAX_CNT  ((uint8_t) 6)
typedef uint8_t EPS1_WatchDogType_t;

/*
    Reset return codes
*/
#define EPS1_RESET_RETCODE_Success ((uint8_t) 0)
#define EPS1_RESET_RETCODE_Wrong_Sequrity ((uint8_t) 1)
#define EPS1_RESET_RETCODE_Busy ((uint8_t) 2)
#define EPS1_RESET_RETCODE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t EPS1_Reset_RetCode_t;

/*
    The EPS1 Response structure for Battery Info Request
*/
typedef struct {
    EPS1_VA_Pair_t sBatt;
    EPS1_VA_Pair_t sBcr;
    uint16_t u16Reserved;
} PACKED_STRUCT EPS1_BatteryInfo_t;

/*
    The EPS1 Response structure for Buses Info Request
*/
typedef struct {
    EPS1_VA_Pair_t sBus_3v3;
    EPS1_VA_Pair_t sBus_5v;
    uint16_t u16Lup_3v3_volt;
    uint16_t u16Lup_5v_volt;
} PACKED_STRUCT EPS1_BusesInfo_t;

/*
    The EPS1 Response structure for Solar Panels Info Request
*/
typedef struct {
    EPS1_VAA_Pack_t sX;
    EPS1_VAA_Pack_t sY;
    EPS1_VAA_Pack_t sZ;
} PACKED_STRUCT EPS1_SolarPanelsInfo_t;

/*
    The EPS1 Response structure for Statistic Info Request
*/
typedef struct {
    EPS1_Statistic_Counters_t sCounters;
    uint16_t au16MaxTemp[4];
    uint16_t au16MinTemp[4];
    uint16_t u16Rbat_initial;
    uint16_t u16Rbat_current;
    uint16_t u16Reserved;
    uint32_t u32Uptime;
} PACKED_STRUCT EPS1_StatisticInfo_t;

/*
    The EPS1 Response structure for Temperatures Info Request. The returned values correspond to raw values and shall be calibrated by the user through the calibration factors and formulas hereby presented.
*/
typedef struct {
    uint16_t u16Mcu;
    uint16_t au16Battery[8];
} PACKED_STRUCT EPS1_TemperatureInfo_t;

/*
    The EPS1 Response structure for Configuration Info Request
*/
typedef struct {
    uint16_t u16InputConditions;
    uint16_t au16OutputConditions[2];
    uint16_t au16DefaultOutputs[2];
} PACKED_STRUCT EPS1_ConfigurationInfo_t;


typedef struct {
    EPS1_QueryState_t aeRequested[26];
} PACKED_STRUCT EPS1queryControlsRequestData_t;

typedef struct {
    uint8_t u8NewValue;
} PACKED_STRUCT EPS1queryRBatRawRequestData_t;

typedef struct {
    EPS1_QueryState_t aeRequested[17];
    uint8_t u8Reserved;
} PACKED_STRUCT EPS1queryDefaultsRequestData_t;

typedef struct {
    EPS1_QueryState_t eRequested;
    uint8_t u8WriteDelayPeriod;
} PACKED_STRUCT EPS1queryLaunchStateRequestData_t;

typedef struct {
    uint8_t u8New_timer;
    EPS1_WatchDogType_t eNew_type;
} PACKED_STRUCT EPS1queryWatchdogRequestData_t;

typedef struct {
    uint8_t u8Security;
} PACKED_STRUCT EPS1resetPowerSupplyRequestData_t;

typedef struct {
    uint8_t u8DeviceSerialNumberWriteSize;
    char strDeviceSerialNumberWrite[32];
} PACKED_STRUCT EPS1SetSerialNumberRequestData_t;

typedef struct {
    uint8_t u8WriteEntryLevelVoltage;
    uint8_t u8WriteExitLevelVoltage;
    uint8_t u8WriteEntryLevelTemperature;
    uint8_t u8WriteExitLevelTemperature;
} PACKED_STRUCT EPS1HellModeWriteRequestData_t;

typedef struct {
    int8_t ai8WriteLowBatTemperetureHeater[3];
    uint8_t au8WriteHysteresisHeater[3];
} PACKED_STRUCT EPS1HeatersSettingsWriteRequestData_t;

typedef struct {
    EPS1_QueryControlsIndex_t eToggleOutput;
    uint8_t u8TimeAtToggledState;
} PACKED_STRUCT EPS1ToggleOutPutRequestData_t;

typedef struct {
    uint8_t u8RepetitionsPeriod;
    uint8_t u8NumberRepetitions;
} PACKED_STRUCT EPS1NotificationsSettingsRequestData_t;

typedef struct {
    uint32_t u32ReqCode;
} PACKED_STRUCT EPS1bload_eraseFlashRequestData_t;

typedef struct {
    uint16_t u16Address;
    uint8_t au8Data[128];
} PACKED_STRUCT EPS1bload_writeFlashRequestData_t;

typedef struct {
    uint32_t u32CRC32;
} PACKED_STRUCT EPS1bload_executeRequestData_t;


typedef struct {
    EPS1_VersionVariant_t eVer_variant;
    uint16_t u16Ver_number;
    uint8_t u8BuildDateSize;
    char strBuildDate[12];
    uint8_t u8BuildTimeSize;
    char strBuildTime[9];
} PACKED_STRUCT EPS1getSoftwareVersionResponseData_t;

typedef struct {
    EPS1_BatteryInfo_t sBattery;
} PACKED_STRUCT EPS1getBatteryInfoResponseData_t;

typedef struct {
    EPS1_BusesInfo_t sBuses;
} PACKED_STRUCT EPS1getBusesInfoResponseData_t;

typedef struct {
    EPS1_SolarPanelsInfo_t sSolar;
} PACKED_STRUCT EPS1getSolarPanelsInfoResponseData_t;

typedef struct {
    EPS1_StatisticInfo_t sStatistics;
} PACKED_STRUCT EPS1getStatisticInfoResponseData_t;

typedef struct {
    EPS1_TemperatureInfo_t sTemperatures;
} PACKED_STRUCT EPS1getTemperaturesInfoResponseData_t;

typedef struct {
    EPS1_ConfigurationInfo_t sConfig;
} PACKED_STRUCT EPS1getConfigurationInfoResponseData_t;

typedef struct {
    EPS1_QueryState_t aeReported[26];
} PACKED_STRUCT EPS1queryControlsResponseData_t;

typedef struct {
    uint8_t u8CurrentValue;
} PACKED_STRUCT EPS1queryRBatRawResponseData_t;

typedef struct {
    EPS1_QueryState_t aeReported[17];
    uint8_t u8Reserved;
} PACKED_STRUCT EPS1queryDefaultsResponseData_t;

typedef struct {
    EPS1_QueryState_t eReported;
    uint8_t u8ReadDelayPeriod;
} PACKED_STRUCT EPS1queryLaunchStateResponseData_t;

typedef struct {
    uint8_t u8Remaining_time;
    EPS1_WatchDogType_t eType;
} PACKED_STRUCT EPS1queryWatchdogResponseData_t;

typedef struct {
    EPS1_WatchDogType_t eType;
    uint8_t u8Timer;
} PACKED_STRUCT EPS1resetWatchdogResponseData_t;

typedef struct {
    EPS1_Reset_RetCode_t eResult;
} PACKED_STRUCT EPS1resetPowerSupplyResponseData_t;

typedef struct {
    uint8_t u8DeviceSerialNumberReadSize;
    char strDeviceSerialNumberRead[32];
} PACKED_STRUCT EPS1SetSerialNumberResponseData_t;

typedef struct {
    uint8_t u8DeviceSerialNumberSize;
    char strDeviceSerialNumber[32];
} PACKED_STRUCT EPS1GetSerialNumberResponseData_t;

typedef struct {
    uint8_t u8EntryLevelVoltage;
    uint8_t u8ExitLevelVoltage;
    uint8_t u8EntryLevelTemperature;
    uint8_t u8ExitLevelTemperature;
} PACKED_STRUCT EPS1HellModeReadResponseData_t;

typedef struct {
    uint8_t u8ReadEntryLevelVoltage;
    uint8_t u8ReadExitLevelVoltage;
    uint8_t u8ReadEntryLevelTemperature;
    uint8_t u8ReadExitLevelTemperature;
} PACKED_STRUCT EPS1HellModeWriteResponseData_t;

typedef struct {
    int8_t ai8LowBatTemperetureHeater[3];
    uint8_t au8HysteresisHeater[3];
} PACKED_STRUCT EPS1HeatersSettingsReadResponseData_t;

typedef struct {
    int8_t ai8ReadLowBatTemperetureHeater[3];
    uint8_t au8ReadHysteresisHeater[3];
} PACKED_STRUCT EPS1HeatersSettingsWriteResponseData_t;

typedef struct {
    bool bRequestStatus;
    uint8_t u8ActualTimeAtToggledState;
} PACKED_STRUCT EPS1ToggleOutPutResponseData_t;

typedef struct {
    uint8_t u8ActualRepetitionsPeriod;
    uint8_t u8ActualNumberRepetitions;
} PACKED_STRUCT EPS1NotificationsSettingsResponseData_t;

typedef struct {
    EPS1_BatteryInfo_t sBattery;
    EPS1_BusesInfo_t sBuses;
    EPS1_SolarPanelsInfo_t sSolar;
    EPS1_TemperatureInfo_t sTemperatures;
    EPS1_ConfigurationInfo_t sConfig;
    uint8_t u8RBatRaw_currentValue;
} PACKED_STRUCT EPS1GetTelemetryAltogetherResponseData_t;

typedef struct {
    uint8_t u8Revison;
    uint8_t u8Supported;
} PACKED_STRUCT EPS1bload_getVersionResponseData_t;

typedef struct {
    EPS1_BLoad_RetCode_t eRetCode;
} PACKED_STRUCT EPS1bload_eraseFlashResponseData_t;

typedef struct {
    EPS1_BLoad_RetCode_t eRetCode;
} PACKED_STRUCT EPS1bload_writeFlashResponseData_t;

typedef struct {
    EPS1_BLoad_RetCode_t eRetCode;
} PACKED_STRUCT EPS1bload_executeResponseData_t;


#endif  // #ifndef __FP_EPS1PROTOCOLTYPES_H__

