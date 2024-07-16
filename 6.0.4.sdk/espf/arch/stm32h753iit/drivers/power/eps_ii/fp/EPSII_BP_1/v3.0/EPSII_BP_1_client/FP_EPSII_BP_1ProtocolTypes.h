/*!
********************************************************************************************
* @file FP_EPSII_BP_1ProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface EPSII_BP_1 v3.0
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

#ifndef __FP_EPSII_BP_1PROTOCOLTYPES_H__
#define __FP_EPSII_BP_1PROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_EPSII_BP_1 ((uint16_t) (0x00000015))

#define EPSII_BP_1_GETDEVICEINFO_FUNC_ID ((funcIdType_t) 0x00000001)
#define EPSII_BP_1_GETRAWSENSORS_FUNC_ID ((funcIdType_t) 0x00000002)
#define EPSII_BP_1_GETBATTERYINFO_FUNC_ID ((funcIdType_t) 0x00000003)
#define EPSII_BP_1_GETDEVICEHEALTHINFO_FUNC_ID ((funcIdType_t) 0x00000004)
#define EPSII_BP_1_SETBATHEATERSETTINGS_FUNC_ID ((funcIdType_t) 0x00000005)
#define EPSII_BP_1_GETBATHEATERSETTINGS_FUNC_ID ((funcIdType_t) 0x00000006)
#define EPSII_BP_1_SETBASICSETTINGS_FUNC_ID ((funcIdType_t) 0x00000007)
#define EPSII_BP_1_GETBASICSETTINGS_FUNC_ID ((funcIdType_t) 0x00000008)
#define EPSII_BP_1_GETBASICAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x0000000B)
#define EPSII_BP_1_GETBASICAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000000C)
#define EPSII_BP_1_GETMAINAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x0000000D)
#define EPSII_BP_1_GETMAINAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000000E)
#define EPSII_BP_1_GETMAINAPPERRCOUNTERS2_FUNC_ID ((funcIdType_t) 0x00000030)
#define EPSII_BP_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000000F)
#define EPSII_BP_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x00000010)
#define EPSII_BP_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000011)
#define EPSII_BP_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x00000012)
#define EPSII_BP_1_GETBALANCERSTATUS_FUNC_ID ((funcIdType_t) 0x00000013)
#define EPSII_BP_1_RESETDEVICE_FUNC_ID ((funcIdType_t) 0x00000020)
#define EPSII_BP_1_FORCEINSTALLMAINAPP_FUNC_ID ((funcIdType_t) 0x00000021)
#define EPSII_BP_1_FORCEINSTALLBASICAPP_FUNC_ID ((funcIdType_t) 0x00000022)
#define EPSII_BP_1_GETBOOTLOADERERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000023)
#define EPSII_BP_1_RESETBOOTLDRERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000024)
#define EPSII_BP_1_SETCHARGERSETTINGS_FUNC_ID ((funcIdType_t) 0x00000025)
#define EPSII_BP_1_SETRTC_FUNC_ID ((funcIdType_t) 0x00000026)
#define EPSII_BP_1_GETRTC_FUNC_ID ((funcIdType_t) 0x00000027)
#define EPSII_BP_1_LEAVENOHIBMODE_FUNC_ID ((funcIdType_t) 0x00000028)
#define EPSII_BP_1_REQUESTPOWERDOWN_FUNC_ID ((funcIdType_t) 0x00000029)
#define EPSII_BP_1_GETBPMODESMROLLINGTRACE_FUNC_ID ((funcIdType_t) 0x00000031)
#define EPSII_BP_1_GETDEVICEINFO_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define EPSII_BP_1_GETRAWSENSORS_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define EPSII_BP_1_GETBATTERYINFO_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define EPSII_BP_1_GETDEVICEHEALTHINFO_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define EPSII_BP_1_SETBATHEATERSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define EPSII_BP_1_GETBATHEATERSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define EPSII_BP_1_SETBASICSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define EPSII_BP_1_GETBASICSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define EPSII_BP_1_GETBASICAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define EPSII_BP_1_GETBASICAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define EPSII_BP_1_GETMAINAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define EPSII_BP_1_GETMAINAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define EPSII_BP_1_GETMAINAPPERRCOUNTERS2_FUNCRESP_ID ((funcIdType_t) 0x00000030)
#define EPSII_BP_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define EPSII_BP_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x00000010)
#define EPSII_BP_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000011)
#define EPSII_BP_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x00000012)
#define EPSII_BP_1_GETBALANCERSTATUS_FUNCRESP_ID ((funcIdType_t) 0x00000013)
#define EPSII_BP_1_RESETDEVICE_FUNCRESP_ID ((funcIdType_t) 0x00000020)
#define EPSII_BP_1_FORCEINSTALLMAINAPP_FUNCRESP_ID ((funcIdType_t) 0x00000021)
#define EPSII_BP_1_FORCEINSTALLBASICAPP_FUNCRESP_ID ((funcIdType_t) 0x00000022)
#define EPSII_BP_1_GETBOOTLOADERERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000023)
#define EPSII_BP_1_RESETBOOTLDRERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000024)
#define EPSII_BP_1_SETCHARGERSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x00000025)
#define EPSII_BP_1_SETRTC_FUNCRESP_ID ((funcIdType_t) 0x00000026)
#define EPSII_BP_1_GETRTC_FUNCRESP_ID ((funcIdType_t) 0x00000027)
#define EPSII_BP_1_LEAVENOHIBMODE_FUNCRESP_ID ((funcIdType_t) 0x00000028)
#define EPSII_BP_1_REQUESTPOWERDOWN_FUNCRESP_ID ((funcIdType_t) 0x00000029)
#define EPSII_BP_1_GETBPMODESMROLLINGTRACE_FUNCRESP_ID ((funcIdType_t) 0x00000031)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Units are signed mA, mV, mC, mT etc
*/
#define EPSII_BP_1_EPSIIT_RESERVEDVALUES_ESEPSIISSVBP_MAX_VAL ((uint32_t) 2147483632)
#define EPSII_BP_1_EPSIIT_RESERVEDVALUES_ESEPSIISSVBP_UNKNOWN_VAL ((uint32_t) 2147483647)
#define EPSII_BP_1_EPSIIT_RESERVEDVALUES_ESEPSIISSVBP_ERROR_VAL ((uint32_t) 2147483646)
#define EPSII_BP_1_EPSIIT_RESERVEDVALUES_MAX_CNT  ((uint32_t) 2147483647)
typedef uint32_t EPSII_BP_1_EPSIIT_ReservedValues_t;

/*
    Telemetry sensors IDs
*/
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_NULL_ID ((uint16_t) 0)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_1_I_ID ((uint16_t) 1)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_1_U_ID ((uint16_t) 2)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_1_P_ID ((uint16_t) 3)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_1_T_ID ((uint16_t) 4)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_2_I_ID ((uint16_t) 5)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_2_U_ID ((uint16_t) 6)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_2_P_ID ((uint16_t) 7)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_INA_BAT_OUT_2_T_ID ((uint16_t) 8)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_U_ID ((uint16_t) 9)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_I_ID ((uint16_t) 10)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_P_ID ((uint16_t) 11)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_1_U_ID ((uint16_t) 12)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_2_U_ID ((uint16_t) 13)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_3_U_ID ((uint16_t) 14)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_4_U_ID ((uint16_t) 15)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_5_U_ID ((uint16_t) 16)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_6_U_ID ((uint16_t) 17)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_7_U_ID ((uint16_t) 18)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_CELL_8_U_ID ((uint16_t) 19)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_BAT_SUM_CELL_U_ID ((uint16_t) 20)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_INT_TEMP_ID ((uint16_t) 21)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_STATUS0_ID ((uint16_t) 22)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_STATUS1_ID ((uint16_t) 23)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_STATUS2_ID ((uint16_t) 24)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_STATUS3_ID ((uint16_t) 25)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_CONTROL0_ID ((uint16_t) 26)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_CONTROL1_ID ((uint16_t) 27)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_CONTROL2_ID ((uint16_t) 28)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BALANCER1_CONTROL3_ID ((uint16_t) 29)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_RESERVED_0_ID ((uint16_t) 30)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_RESERVED_1_ID ((uint16_t) 31)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_RESERVED_2_ID ((uint16_t) 32)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_RESERVED_3_ID ((uint16_t) 33)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_RESERVED_4_ID ((uint16_t) 34)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_STAT_CHARGER_ID ((uint16_t) 35)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_STAT_SYSTEM_ID ((uint16_t) 36)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_STAT_SUPPLY_ID ((uint16_t) 37)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_STAT_CHRG_FAULTS_ID ((uint16_t) 38)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_TBAT_ID ((uint16_t) 39)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_POUT_ID ((uint16_t) 40)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_PIN_ID ((uint16_t) 41)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_EFF_ID ((uint16_t) 42)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_IOUT_ID ((uint16_t) 43)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_IIN_ID ((uint16_t) 44)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_VBAT_ID ((uint16_t) 45)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_VIN_ID ((uint16_t) 46)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XP_TELE_VINR_ID ((uint16_t) 47)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_STAT_CHARGER_ID ((uint16_t) 48)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_STAT_SYSTEM_ID ((uint16_t) 49)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_STAT_SUPPLY_ID ((uint16_t) 50)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_STAT_CHRG_FAULTS_ID ((uint16_t) 51)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_TBAT_ID ((uint16_t) 52)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_POUT_ID ((uint16_t) 53)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_PIN_ID ((uint16_t) 54)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_EFF_ID ((uint16_t) 55)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_IOUT_ID ((uint16_t) 56)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_IIN_ID ((uint16_t) 57)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_VBAT_ID ((uint16_t) 58)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_VIN_ID ((uint16_t) 59)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_XR_TELE_VINR_ID ((uint16_t) 60)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_STAT_CHARGER_ID ((uint16_t) 61)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_STAT_SYSTEM_ID ((uint16_t) 62)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_STAT_SUPPLY_ID ((uint16_t) 63)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_STAT_CHRG_FAULTS_ID ((uint16_t) 64)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_TBAT_ID ((uint16_t) 65)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_POUT_ID ((uint16_t) 66)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_PIN_ID ((uint16_t) 67)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_EFF_ID ((uint16_t) 68)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_IOUT_ID ((uint16_t) 69)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_IIN_ID ((uint16_t) 70)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_VBAT_ID ((uint16_t) 71)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_VIN_ID ((uint16_t) 72)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YP_TELE_VINR_ID ((uint16_t) 73)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_STAT_CHARGER_ID ((uint16_t) 74)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_STAT_SYSTEM_ID ((uint16_t) 75)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_STAT_SUPPLY_ID ((uint16_t) 76)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_STAT_CHRG_FAULTS_ID ((uint16_t) 77)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_TBAT_ID ((uint16_t) 78)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_POUT_ID ((uint16_t) 79)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_PIN_ID ((uint16_t) 80)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_EFF_ID ((uint16_t) 81)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_IOUT_ID ((uint16_t) 82)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_IIN_ID ((uint16_t) 83)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_VBAT_ID ((uint16_t) 84)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_VIN_ID ((uint16_t) 85)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_YR_TELE_VINR_ID ((uint16_t) 86)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_STAT_CHARGER_ID ((uint16_t) 87)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_STAT_SYSTEM_ID ((uint16_t) 88)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_STAT_SUPPLY_ID ((uint16_t) 89)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_STAT_CHRG_FAULTS_ID ((uint16_t) 90)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_TBAT_ID ((uint16_t) 91)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_POUT_ID ((uint16_t) 92)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_PIN_ID ((uint16_t) 93)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_EFF_ID ((uint16_t) 94)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_IOUT_ID ((uint16_t) 95)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_IIN_ID ((uint16_t) 96)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_VBAT_ID ((uint16_t) 97)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_VIN_ID ((uint16_t) 98)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZP_TELE_VINR_ID ((uint16_t) 99)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_STAT_CHARGER_ID ((uint16_t) 100)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_STAT_SYSTEM_ID ((uint16_t) 101)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_STAT_SUPPLY_ID ((uint16_t) 102)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_STAT_CHRG_FAULTS_ID ((uint16_t) 103)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_TBAT_ID ((uint16_t) 104)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_POUT_ID ((uint16_t) 105)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_PIN_ID ((uint16_t) 106)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_EFF_ID ((uint16_t) 107)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_IOUT_ID ((uint16_t) 108)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_IIN_ID ((uint16_t) 109)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_VBAT_ID ((uint16_t) 110)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_VIN_ID ((uint16_t) 111)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_CHRG_ZR_TELE_VINR_ID ((uint16_t) 112)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BP_TEMPERATURE_PCB_1_ID ((uint16_t) 113)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BP_TEMPERATURE_PCB_2_ID ((uint16_t) 114)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_ADC_CPU_T_ID ((uint16_t) 115)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_ADC_CPU_AVCC_U_ID ((uint16_t) 116)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_ADC_BAT_TEMP_NTC1_ID ((uint16_t) 117)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_ADC_BAT_TEMP_NTC2_ID ((uint16_t) 118)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_ADC_RAD_FED_ID ((uint16_t) 119)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_HEATER_PWM_PERCENT_ID ((uint16_t) 120)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_HEATER_TARGET_TEMP_ID ((uint16_t) 121)
#define EPSII_BP_1_EPSIIT_SENSORIDS_EPSIIT_BAT_CHARGE_WH_ID ((uint16_t) 122)
#define EPSII_BP_1_EPSIIT_SENSORIDS_MAX_CNT  ((uint16_t) 123)
typedef uint16_t EPSII_BP_1_EPSIIT_SensorIDs_t;

/*
    Error Counter structure
*/
typedef struct {
    uint16_t u16EDC_NONE;
    uint16_t u16EDC_OSC_EXT_SINGLE_FAILED_CNTR;
    uint16_t u16EDC_OSC_EXT_PERMANENT_FAILED_CNTR;
    uint16_t u16EDC_LF_OSC_BACKUP_CNTR;
    uint16_t u16EDC_SYSSNIV__ACCTEIFG;
    uint16_t u16EDC_SYSSNIV__MPUSEGPIFG;
    uint16_t u16EDC_SYSSNIV__MPUSEGIIFG;
    uint16_t u16EDC_SYSSNIV__MPUSEG1IFG;
    uint16_t u16EDC_SYSSNIV__MPUSEG2IFG;
    uint16_t u16EDC_SYSSNIV__MPUSEG3IFG;
    uint16_t u16EDC_SYSSNIV__VMAIFG;
    uint16_t u16EDC_SYSSNIV__JMBINIFG;
    uint16_t u16EDC_SYSSNIV__JMBOUTIFG;
    uint16_t u16EDC_SYSSNIV__CBDIFG;
    uint16_t u16EDC_SYSSNIV__WPROT;
    uint16_t u16EDC_SYSSNIV__LEATO;
    uint16_t u16EDC_SYSSNIV__LEACMD;
    uint16_t u16EDC_ADC_REF_SETTLE_FAIL_CNTR;
    uint16_t u16EDC_ADC_CONV_TIMEOUT;
    uint16_t u16EDC_ADC_REF_BUSSY_CNTR;
    uint16_t u16EDC_ADC_STUCK_IN_PREV_CONV;
    uint16_t u16EDC_NVM_NO_FREE_MEMORY;
    uint16_t u16EDC_NVM_SEGMENT_NOT_FOUND;
    uint16_t u16EDC_BL_CHECKER_PART1_CORRUPTED;
    uint16_t u16EDC_BL_CHECKER_PART2_CORRUPTED;
    uint16_t u16EDC_BL_CHECKER_PART3_CORRUPTED;
    uint16_t u16EDC_BL_CHECKER_PART4_CORRUPTED;
    uint16_t u16EDC_BL_IMPLEMENTATION_PART1_CORRUPTED;
    uint16_t u16EDC_BL_IMPLEMENTATION_PART2_CORRUPTED;
    uint16_t u16EDC_NVM_HDR_PART1_CORRUPTED;
    uint16_t u16EDC_NVM_HDR_PART2_CORRUPTED;
    uint16_t u16EDC_NVM_PART1_CORRUPTED;
    uint16_t u16EDC_NVM_PART2_CORRUPTED;
    uint16_t u16EDC_EXT_BASICAPP_PART1_CORRUPTED;
    uint16_t u16EDC_EXT_BASICAPP_PART2_CORRUPTED;
    uint16_t u16EDC_EXT_BASICAPP_PART3_CORRUPTED;
    uint16_t u16EDC_EXT_MAINAPP_PART1_CORRUPTED;
    uint16_t u16EDC_EXT_MAINAPP_PART2_CORRUPTED;
    uint16_t u16EDC_EXT_MAINAPP_PART3_CORRUPTED;
    uint16_t u16EDC_CBDIFG_FRAM_CORRECTABLE_BIT;
    uint16_t u16EDC_RST_TOTAL;
    uint16_t u16EDC_RST_BROWNOUT;
    uint16_t u16EDC_RST_RSTIFG;
    uint16_t u16EDC_RST_PMMSWBOR;
    uint16_t u16EDC_RST_LPM_X_5_WAKE;
    uint16_t u16EDC_RST_SECURITY_VIOLATION;
    uint16_t u16EDC_RST_RES1;
    uint16_t u16EDC_RST_SVSHIFG;
    uint16_t u16EDC_RST_RES2;
    uint16_t u16EDC_RST_RES3;
    uint16_t u16EDC_RST_PMMSWPOR;
    uint16_t u16EDC_RST_WDTIFG;
    uint16_t u16EDC_RST_WDTPW;
    uint16_t u16EDC_RST_FRCTLPW;
    uint16_t u16EDC_RST_FRAM_BIT_ERR;
    uint16_t u16EDC_RST_PER_FETCH;
    uint16_t u16EDC_RST_PMMPW;
    uint16_t u16EDC_RST_MPUPW;
    uint16_t u16EDC_RST_CSPW;
    uint16_t u16EDC_RST_MPUSEGIPIFG;
    uint16_t u16EDC_RST_MPUSEGIIFG;
    uint16_t u16EDC_RST_MPUSEG1IFG;
    uint16_t u16EDC_RST_MPUSEG2IFG;
    uint16_t u16EDC_RST_MPUSEG3IFG;
    uint16_t u16EDC_BAL_CONFIG_INVALID;
    uint16_t u16EDC_CHRG_CONFIG_INVALID;
    uint16_t u16EDC_SUCCESSFULL_POWERDOWN_COUNTER;
    uint16_t u16EDC_CHRG_CANT_APPLY_CONFIG_2;
    uint16_t u16EDC_MAC_SYS1_TX_COLLISION;
    uint16_t u16EDC_MAC_SYS1_TX_TIMEOUT;
    uint16_t u16EDC_MAC_SYS1_RX_MSG_WITH_ZERRO_SIZE;
    uint16_t u16EDC_MAC_SYS1_RX_MSG_WITH_WRONG_HDR_CRC;
    uint16_t u16EDC_MAC_SYS1_RX_MSG_WITH_WRONG_MSG_CRC;
    uint16_t u16EDC_MAC_SYS1_RX_COLLISION;
    uint16_t u16EDC_MAC_SYS1_RX_MSG_MISS_NO_BUFFER;
    uint16_t u16EDC_MAC_SYS1_RX_TIMEOUT;
    uint16_t u16EDC_MAC_SYS1_RX_RESTARTED_MSGS;
    uint16_t u16EDC_MAC_SYS1_RX_INTER_BYTE_MAX_TIME;
    uint16_t u16EDC_MAC_SYS2_TX_COLLISION;
    uint16_t u16EDC_MAC_SYS2_TX_TIMEOUT;
    uint16_t u16EDC_MAC_SYS2_RX_MSG_WITH_ZERRO_SIZE;
    uint16_t u16EDC_MAC_SYS2_RX_MSG_WITH_WRONG_HDR_CRC;
    uint16_t u16EDC_MAC_SYS2_RX_MSG_WITH_WRONG_MSG_CRC;
    uint16_t u16EDC_MAC_SYS2_RX_COLLISION;
    uint16_t u16EDC_MAC_SYS2_RX_MSG_MISS_NO_BUFFER;
    uint16_t u16EDC_MAC_SYS2_RX_TIMEOUT;
    uint16_t u16EDC_MAC_SYS2_RX_RESTARTED_MSGS;
    uint16_t u16EDC_MAC_SYS2_RX_INTER_BYTE_MAX_TIME;
    uint16_t u16EDC_MAC_PAY1_TX_COLLISION;
    uint16_t u16EDC_MAC_PAY1_TX_TIMEOUT;
    uint16_t u16EDC_MAC_PAY1_RX_MSG_WITH_ZERRO_SIZE;
    uint16_t u16EDC_MAC_PAY1_RX_MSG_WITH_WRONG_HDR_CRC;
    uint16_t u16EDC_MAC_PAY1_RX_MSG_WITH_WRONG_MSG_CRC;
    uint16_t u16EDC_MAC_PAY1_RX_COLLISION;
    uint16_t u16EDC_MAC_PAY1_RX_MSG_MISS_NO_BUFFER;
    uint16_t u16EDC_MAC_PAY1_RX_TIMEOUT;
    uint16_t u16EDC_MAC_PAY1_RX_RESTARTED_MSGS;
    uint16_t u16EDC_MAC_PAY1_RX_INTER_BYTE_MAX_TIME;
    uint16_t u16EDC_MAC_PAY2_TX_COLLISION;
    uint16_t u16EDC_MAC_PAY2_TX_TIMEOUT;
    uint16_t u16EDC_MAC_PAY2_RX_MSG_WITH_ZERRO_SIZE;
    uint16_t u16EDC_MAC_PAY2_RX_MSG_WITH_WRONG_HDR_CRC;
    uint16_t u16EDC_MAC_PAY2_RX_MSG_WITH_WRONG_MSG_CRC;
    uint16_t u16EDC_MAC_PAY2_RX_COLLISION;
    uint16_t u16EDC_MAC_PAY2_RX_MSG_MISS_NO_BUFFER;
    uint16_t u16EDC_MAC_PAY2_RX_TIMEOUT;
    uint16_t u16EDC_MAC_PAY2_RX_RESTARTED_MSGS;
    uint16_t u16EDC_MAC_PAY2_RX_INTER_BYTE_MAX_TIME;
    uint16_t u16EDC_CPU_UP_TIME_LO;
    uint16_t u16EDC_CPU_UP_TIME_HI;
    uint16_t u16EDC_CPU_MAIN_LOOP_MAX_TIME;
    uint16_t u16EDC_BAL_ISL94202IRTZ_RE_APPLY_CNF_CNTR;
    uint16_t u16EDC_LT8491_FORCE_RE_APPLY_CNF_RAM_CNTR;
    uint16_t u16EDC_LT8491_FORCE_RE_APPLY_CNF_ROM_CNTR;
    uint16_t u16EDC_CONOPS_ENTER_IN_NOHIB_COUNTER;
    uint16_t u16EDC_LT8491_CHIP_RESET_DURING_EEPROMWRITE_CNTR;
    uint16_t u16EDC_INIT_CONFIG_NVM_1_CORRUPTED;
    uint16_t u16EDC_INIT_CONFIG_NVM_2_CORRUPTED;
    uint16_t u16EDC_EXT_FRAM_PROBE_FAILED;
    uint16_t u16EDC_NVM_ALLOCATED_SIZE;
    uint16_t u16EDC_NVM_USED_SIZE;
    uint16_t u16EDC_BASIC_SETTINGS_NVM_CORRUPTED;
    uint16_t u16EDC_CONOPS_ENTER_IN_BATTERY_COUNTER;
} PACKED_STRUCT EPSII_BP_1_SDiagErrCounter_t;

/*
    Error Counter structure
*/
typedef struct {
    uint16_t u16EDC_CONOPS_ENTER_IN_PANEL_COUNTER;
    uint16_t u16EDC_CONOPS_ENTER_IN_HIB_COUNTER;
} PACKED_STRUCT EPSII_BP_1_SDiagErrCounter2_t;

/*
    Battery Pack mode type
*/
#define EPSII_BP_1_BP_MODE_TYPE_ROOT ((uint8_t) 0)
#define EPSII_BP_1_BP_MODE_TYPE_IDENTIFYPREVIOUSSTATE ((uint8_t) 1)
#define EPSII_BP_1_BP_MODE_TYPE_BATTERY_AVAILABLE ((uint8_t) 2)
#define EPSII_BP_1_BP_MODE_TYPE_BATTERY ((uint8_t) 3)
#define EPSII_BP_1_BP_MODE_TYPE_TRANSITION_TO_HIB ((uint8_t) 4)
#define EPSII_BP_1_BP_MODE_TYPE_NORMAL ((uint8_t) 5)
#define EPSII_BP_1_BP_MODE_TYPE_HIB ((uint8_t) 6)
#define EPSII_BP_1_BP_MODE_TYPE_NOHIB ((uint8_t) 7)
#define EPSII_BP_1_BP_MODE_TYPE_PANEL ((uint8_t) 8)
#define EPSII_BP_1_BP_MODE_TYPE____HISTORY_BATTERY_AVAILABLE ((uint8_t) 9)
#define EPSII_BP_1_BP_MODE_TYPE_MAX_CNT  ((uint8_t) 10)
typedef uint8_t EPSII_BP_1_BP_Mode_Type_t;

/*
    Structure used for one trace record of BP mode change
*/
typedef struct {
    uint32_t u32Time_stamp;
    EPSII_BP_1_BP_Mode_Type_t eTarget_mode;
} PACKED_STRUCT EPSII_BP_1_SBpModeChangeInfo_t;

/*
    Firmware types
*/
#define EPSII_BP_1_ESDI_FIRMWARETYPE_ESDIFT_Production ((uint8_t) 0)
#define EPSII_BP_1_ESDI_FIRMWARETYPE_ESDIFT_BasicApp ((uint8_t) 1)
#define EPSII_BP_1_ESDI_FIRMWARETYPE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t EPSII_BP_1_ESDI_FirmwareType_t;

/*
    Status of chips as seen by CPU
*/
#define EPSII_BP_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_UNKNOWN ((uint8_t) 0)
#define EPSII_BP_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_ONLINE ((uint8_t) 1)
#define EPSII_BP_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_COM_ERR ((uint8_t) 2)
#define EPSII_BP_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_COM_TIMEOUT ((uint8_t) 3)
#define EPSII_BP_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_DRV_DISABLED ((uint8_t) 4)
#define EPSII_BP_1_EDHI_CHIPSTATUS_MAX_CNT  ((uint8_t) 5)
typedef uint8_t EPSII_BP_1_EDHI_ChipStatus_t;

/*
    Heaters enable mask in different Battery Pack modes
*/
#define EPSII_BP_1_SBH_ENABLEBITMASK_SBHEB_ALL_MODES_DISABLE ((uint8_t) 0)
#define EPSII_BP_1_SBH_ENABLEBITMASK_SBHEB_NORMAL_MODE_ONLY ((uint8_t) 1)
#define EPSII_BP_1_SBH_ENABLEBITMASK_SBHEB_HIB_MODE_ONLY ((uint8_t) 2)
#define EPSII_BP_1_SBH_ENABLEBITMASK_SBHEB_HIB_AND_NORMAL ((uint8_t) 3)
#define EPSII_BP_1_SBH_ENABLEBITMASK_MAX_CNT  ((uint8_t) 4)
typedef uint8_t EPSII_BP_1_SBH_EnableBitmask_t;

/*
    SetBatHeaterSettings command error codes
*/
#define EPSII_BP_1_SBH_SETERROR_SBHSE_SUCCESS ((uint8_t) 0)
#define EPSII_BP_1_SBH_SETERROR_SBHSE_BAD_PARAMS ((uint8_t) 1)
#define EPSII_BP_1_SBH_SETERROR_SBHSE_NVM_ERR ((uint8_t) 2)
#define EPSII_BP_1_SBH_SETERROR_MAX_CNT  ((uint8_t) 3)
typedef uint8_t EPSII_BP_1_SBH_SetError_t;

/*
    Common Driver operation result
*/
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_SUCCESS ((uint8_t) 0)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_IN_PROGRESS ((uint8_t) 1)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_BUSY ((uint8_t) 2)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_OFFLINE ((uint8_t) 3)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_COM_ERR ((uint8_t) 4)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_COM_TIMEOUT ((uint8_t) 5)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_WRC_ERR ((uint8_t) 6)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_GENERAL_ERR ((uint8_t) 7)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_EMDOR_DRV_DISABLED ((uint8_t) 8)
#define EPSII_BP_1_EMDRVOPERATIONRESULT_MAX_CNT  ((uint8_t) 9)
typedef uint8_t EPSII_BP_1_EMDrvOperationResult_t;

#define EPSII_BP_1_LEAVENOHIBMODERESULT_SUCCESS ((uint8_t) 0)
#define EPSII_BP_1_LEAVENOHIBMODERESULT_DEVICE_NOT_IN_NOHIB_MODE ((uint8_t) 1)
#define EPSII_BP_1_LEAVENOHIBMODERESULT_FAIL ((uint8_t) 2)
#define EPSII_BP_1_LEAVENOHIBMODERESULT_MAX_CNT  ((uint8_t) 3)
typedef uint8_t EPSII_BP_1_LeaveNoHibModeResult_t;

/*
    Limits and settings for one Battery pack mode
*/
typedef struct {
    int64_t i64EnterThreshold;
    int64_t i64ExitThreshold;
    int64_t i64NLowTemperature;
    int64_t i64NLowTemperatureRestore;
    uint8_t u8NMaximumHeatersPower;
} PACKED_STRUCT EPSII_BP_1_SBS_BpHibSetting_t;

/*
    SBasicSettings structure to get/set
*/
typedef struct {
    uint8_t u8BroadcastInterval;
    uint16_t u16HibModeTimeout;
    uint16_t u16HealthyBpCheckTime;
    EPSII_BP_1_SBS_BpHibSetting_t sBpHibModeSettings;
    uint16_t u16ChargeCurrentLimit;
} PACKED_STRUCT EPSII_BP_1_SBasicSettings_t;

/*
    Error returned for SetBasicSettings command
*/
#define EPSII_BP_1_SBS_SETERROR_SBSSE_SUCCESS ((uint8_t) 0)
#define EPSII_BP_1_SBS_SETERROR_SBSSE_NVM_ERR ((uint8_t) 1)
#define EPSII_BP_1_SBS_SETERROR_SBSSE_BAD_PARAMS ((uint8_t) 2)
#define EPSII_BP_1_SBS_SETERROR_SBSSE_REG_TYPE_NOT_SUPP ((uint8_t) 3)
#define EPSII_BP_1_SBS_SETERROR_MAX_CNT  ((uint8_t) 4)
typedef uint8_t EPSII_BP_1_SBS_SetError_t;

/*
    Error returned for GetBasicSettings command
*/
#define EPSII_BP_1_SBS_GETERROR_SBSGE_SUCCESS ((uint8_t) 0)
#define EPSII_BP_1_SBS_GETERROR_SBSGE_NVM_ERR ((uint8_t) 1)
#define EPSII_BP_1_SBS_GETERROR_SBSGE_CONFIG_NOT_SET ((uint8_t) 2)
#define EPSII_BP_1_SBS_GETERROR_MAX_CNT  ((uint8_t) 3)
typedef uint8_t EPSII_BP_1_SBS_GetError_t;

/*
    Structure of the data about the exceptions
*/
typedef struct {
    uint16_t u16M_nFileID;
    uint16_t u16M_nLineNum;
} PACKED_STRUCT EPSII_BP_1_SMSP_Exception_t;

/*
    chargers statuses
*/
#define EPSII_BP_1_CHARGERSETTINGS_READ_STAT ((uint8_t) 0)
#define EPSII_BP_1_CHARGERSETTINGS_ENABLE_CFG_PRYMARY ((uint8_t) 1)
#define EPSII_BP_1_CHARGERSETTINGS_ENABLE_CFG_SECONDARY ((uint8_t) 2)
#define EPSII_BP_1_CHARGERSETTINGS_ENABLE_CFG_AUTO ((uint8_t) 3)
#define EPSII_BP_1_CHARGERSETTINGS_MAX_CNT  ((uint8_t) 4)
typedef uint8_t EPSII_BP_1_ChargerSettings_t;


typedef struct {
    uint32_t u32PktIDReq;
    EPSII_BP_1_EPSIIT_SensorIDs_t aeSensorsIDs[50];
} PACKED_STRUCT EPSII_BP_1GetRAWSensorsRequestData_t;

typedef struct {
    EPSII_BP_1_SBH_EnableBitmask_t eEnableBitmask;
    int32_t i32NormalModeSetPointTemp;
    int32_t i32HibModeSetPointTemp;
    uint32_t u32PID_KP;
    uint32_t u32PID_KI;
    uint32_t u32PID_KD;
} PACKED_STRUCT EPSII_BP_1SetBatHeaterSettingsRequestData_t;

typedef struct {
    EPSII_BP_1_SBasicSettings_t sBasicSettings;
} PACKED_STRUCT EPSII_BP_1SetBasicSettingsRequestData_t;

typedef struct {
    uint8_t u8RequestSpecificRegNumber;
} PACKED_STRUCT EPSII_BP_1GetBalancerStatusRequestData_t;

typedef struct {
    EPSII_BP_1_ChargerSettings_t aeInChargers[3];
} PACKED_STRUCT EPSII_BP_1SetChargerSettingsRequestData_t;

typedef struct {
    uint8_t u8In_hours;
    uint8_t u8In_minutes;
    uint8_t u8In_seconds;
    uint8_t u8In_date;
    uint8_t u8In_month;
    uint16_t u16In_year;
} PACKED_STRUCT EPSII_BP_1SetRTCRequestData_t;


typedef struct {
    uint16_t u16ModuleTypeID;
    uint8_t u8ModuleTypeSize;
    char strModuleType[20];
    uint16_t u16ModuleHWVersion;
    uint8_t u8DeviceSerialNumberSize;
    char strDeviceSerialNumber[30];
    EPSII_BP_1_ESDI_FirmwareType_t eFWTypeID;
    uint8_t u8FWTypeSize;
    char strFWType[20];
    uint16_t u16FWVersionMaj;
    uint16_t u16FWVersionMin;
    uint8_t u8BLVersionMaj;
    uint8_t u8BLVersionMin;
} PACKED_STRUCT EPSII_BP_1GetDeviceInfoResponseData_t;

typedef struct {
    uint32_t u32PktID;
    int32_t ai32SensorValues[50];
} PACKED_STRUCT EPSII_BP_1GetRAWSensorsResponseData_t;

typedef struct {
    EPSII_BP_1_BP_Mode_Type_t eBp_mode;
    int64_t i64BattEnergy;
    int64_t i64BattCharge;
    int64_t i64BattChargeCapacity;
    int64_t i64BattPercent;
    int64_t i64BattVoltage;
    int64_t i64BattCurrent;
    int64_t i64BattTemperature;
} PACKED_STRUCT EPSII_BP_1GetBatteryInfoResponseData_t;

typedef struct {
    int32_t i32ActiveCPU_RunningTime;
    int32_t i32ActiveCPU_Voltage;
    int32_t i32ActiveCPU_Temperature;
    int32_t i32PCB_Temperature_1;
    int32_t i32PCB_Temperature_2;
    int32_t i32NVM_AllocatedSize;
    int32_t i32NVM_UsedSize;
    int32_t i32Stack_AllocatedSize;
    int32_t i32Stack_UsedSize;
    EPSII_BP_1_EDHI_ChipStatus_t eBALANCER_CHIP_1;
    EPSII_BP_1_EDHI_ChipStatus_t eBALANCER_CHIP_2;
    EPSII_BP_1_EDHI_ChipStatus_t eLT8491_IC_XP;
    EPSII_BP_1_EDHI_ChipStatus_t eLT8491_IC_XR;
    EPSII_BP_1_EDHI_ChipStatus_t eLT8491_IC_YP;
    EPSII_BP_1_EDHI_ChipStatus_t eLT8491_IC_YR;
    EPSII_BP_1_EDHI_ChipStatus_t eLT8491_IC_ZP;
    EPSII_BP_1_EDHI_ChipStatus_t eLT8491_IC_ZR;
    EPSII_BP_1_EDHI_ChipStatus_t eINA_BAT_OUT_1;
    EPSII_BP_1_EDHI_ChipStatus_t eINA_BAT_OUT_2;
    EPSII_BP_1_EDHI_ChipStatus_t eTMP117_U810;
    EPSII_BP_1_EDHI_ChipStatus_t eTMP117_U811;
    EPSII_BP_1_EDHI_ChipStatus_t eGPIO_PCA9538_U2001;
    EPSII_BP_1_EDHI_ChipStatus_t eGPIO_PCA9538_U2002;
    EPSII_BP_1_EDHI_ChipStatus_t eDPOT_MCP4562_CURRENT_LIMMITER;
} PACKED_STRUCT EPSII_BP_1GetDeviceHealthInfoResponseData_t;

typedef struct {
    EPSII_BP_1_SBH_SetError_t eErr;
} PACKED_STRUCT EPSII_BP_1SetBatHeaterSettingsResponseData_t;

typedef struct {
    EPSII_BP_1_SBH_EnableBitmask_t eEnableBitmask;
    int32_t i32NormalModeSetPointTemp;
    int32_t i32HibModeSetPointTemp;
    uint32_t u32PID_KP;
    uint32_t u32PID_KI;
    uint32_t u32PID_KD;
} PACKED_STRUCT EPSII_BP_1GetBatHeaterSettingsResponseData_t;

typedef struct {
    EPSII_BP_1_SBS_SetError_t eErr;
} PACKED_STRUCT EPSII_BP_1SetBasicSettingsResponseData_t;

typedef struct {
    EPSII_BP_1_SBS_GetError_t eErr;
    EPSII_BP_1_SBasicSettings_t sBasicSettings;
} PACKED_STRUCT EPSII_BP_1GetBasicSettingsResponseData_t;

typedef struct {
    EPSII_BP_1_SMSP_Exception_t asExceptions[16];
} PACKED_STRUCT EPSII_BP_1GetBasicAppExceptionsResponseData_t;

typedef struct {
    EPSII_BP_1_SDiagErrCounter_t sErrorCounters;
} PACKED_STRUCT EPSII_BP_1GetBasicAppErrCountersResponseData_t;

typedef struct {
    EPSII_BP_1_SMSP_Exception_t asExceptions[16];
} PACKED_STRUCT EPSII_BP_1GetMainAppExceptionsResponseData_t;

typedef struct {
    EPSII_BP_1_SDiagErrCounter_t sErrorCounters;
} PACKED_STRUCT EPSII_BP_1GetMainAppErrCountersResponseData_t;

typedef struct {
    EPSII_BP_1_SDiagErrCounter2_t sErrorCounters2;
} PACKED_STRUCT EPSII_BP_1GetMainAppErrCounters2ResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetMainAppErrCountersResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetMainAppExceptionsResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetBasicAppErrCountersResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_BP_1OnESCP_ResetBasicAppExceptionsResponseData_t;

typedef struct {
    EPSII_BP_1_EDHI_ChipStatus_t eResult;
    uint8_t u8Status_register_0;
    uint8_t u8Status_register_1;
    uint8_t u8Status_register_2;
    uint8_t u8Status_register_3;
    int32_t i32Ntc_resistance_1;
    int32_t i32Ntc_resistance_2;
    int16_t i16Requested_register_value;
} PACKED_STRUCT EPSII_BP_1GetBalancerStatusResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_BP_1ResetDeviceResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_BP_1ForceInstallMainAppResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_BP_1ForceInstallBasicAppResponseData_t;

typedef struct {
    uint16_t u16C_app_restart_errors;
    uint8_t u8G_pAppCyclesErrors;
    uint8_t u8Reserved;
    uint16_t u16G_pIntegrityCheckStates;
} PACKED_STRUCT EPSII_BP_1GetBootLoaderErrCountersResponseData_t;

typedef struct {
    uint16_t u16C_app_restart_errors;
    uint8_t u8G_pAppCyclesErrors;
    uint8_t u8Reserved;
    uint16_t u16G_pIntegrityCheckStates;
} PACKED_STRUCT EPSII_BP_1ResetBootLdrErrCountersResponseData_t;

typedef struct {
    EPSII_BP_1_ChargerSettings_t aeOutChargers[3];
} PACKED_STRUCT EPSII_BP_1SetChargerSettingsResponseData_t;

typedef struct {
    uint8_t u8Out_hours;
    uint8_t u8Out_minutes;
    uint8_t u8Out_seconds;
    uint8_t u8Out_day;
    uint8_t u8Out_month;
    uint16_t u16Out_year;
} PACKED_STRUCT EPSII_BP_1SetRTCResponseData_t;

typedef struct {
    uint8_t u8Out_hours;
    uint8_t u8Out_minutes;
    uint8_t u8Out_seconds;
    uint8_t u8Out_day;
    uint8_t u8Out_month;
    uint16_t u16Out_year;
} PACKED_STRUCT EPSII_BP_1GetRTCResponseData_t;

typedef struct {
    EPSII_BP_1_LeaveNoHibModeResult_t eResult;
} PACKED_STRUCT EPSII_BP_1LeaveNoHibModeResponseData_t;

typedef struct {
    EPSII_BP_1_EMDrvOperationResult_t eResult;
} PACKED_STRUCT EPSII_BP_1RequestPowerDownResponseData_t;

typedef struct {
    uint8_t u8Current_index;
    EPSII_BP_1_SBpModeChangeInfo_t asChange_info[20];
} PACKED_STRUCT EPSII_BP_1GetBpModeSmRollingTraceResponseData_t;


#endif  // #ifndef __FP_EPSII_BP_1PROTOCOLTYPES_H__

