/*!
********************************************************************************************
* @file FP_EPSII_PDM_1ProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface EPSII_PDM_1 v1.0
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

#ifndef __FP_EPSII_PDM_1PROTOCOLTYPES_H__
#define __FP_EPSII_PDM_1PROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_EPSII_PDM_1 ((uint16_t) (0x00000014))

#define EPSII_PDM_1_GETDEVICEINFO_FUNC_ID ((funcIdType_t) 0x00000001)
#define EPSII_PDM_1_GETPOWERDISTRIBUTIONINFO_FUNC_ID ((funcIdType_t) 0x00000002)
#define EPSII_PDM_1_GETDEVICEHEALTHINFO_FUNC_ID ((funcIdType_t) 0x00000003)
#define EPSII_PDM_1_SETPC104GPIO_FUNC_ID ((funcIdType_t) 0x00000004)
#define EPSII_PDM_1_GETPC104GPIO_FUNC_ID ((funcIdType_t) 0x00000005)
#define EPSII_PDM_1_GETRAWSENSORS_FUNC_ID ((funcIdType_t) 0x00000006)
#define EPSII_PDM_1_SETPOWEROUTPUTS_FUNC_ID ((funcIdType_t) 0x00000007)
#define EPSII_PDM_1_GETPOWEROUTPUTS_FUNC_ID ((funcIdType_t) 0x00000008)
#define EPSII_PDM_1_SETBASICSETTINGS_FUNC_ID ((funcIdType_t) 0x00000009)
#define EPSII_PDM_1_GETBASICSETTINGS_FUNC_ID ((funcIdType_t) 0x0000000A)
#define EPSII_PDM_1_GETBASICAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x0000000B)
#define EPSII_PDM_1_GETBASICAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000000C)
#define EPSII_PDM_1_GETMAINAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x0000000D)
#define EPSII_PDM_1_GETMAINAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000000E)
#define EPSII_PDM_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000000F)
#define EPSII_PDM_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x00000010)
#define EPSII_PDM_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000011)
#define EPSII_PDM_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNC_ID ((funcIdType_t) 0x00000012)
#define EPSII_PDM_1_GETBULKTELEMETRY_FUNC_ID ((funcIdType_t) 0x00000013)
#define EPSII_PDM_1_RESETDEVICE_FUNC_ID ((funcIdType_t) 0x00000020)
#define EPSII_PDM_1_FORCEINSTALLMAINAPP_FUNC_ID ((funcIdType_t) 0x00000021)
#define EPSII_PDM_1_FORCEINSTALLBASICAPP_FUNC_ID ((funcIdType_t) 0x00000022)
#define EPSII_PDM_1_GETBOOTLOADERERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000023)
#define EPSII_PDM_1_RESETBOOTLDRERRCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000024)
#define EPSII_PDM_1_GETDEVICEINFO_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define EPSII_PDM_1_GETPOWERDISTRIBUTIONINFO_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define EPSII_PDM_1_GETDEVICEHEALTHINFO_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define EPSII_PDM_1_SETPC104GPIO_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define EPSII_PDM_1_GETPC104GPIO_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define EPSII_PDM_1_GETRAWSENSORS_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define EPSII_PDM_1_SETPOWEROUTPUTS_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define EPSII_PDM_1_GETPOWEROUTPUTS_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define EPSII_PDM_1_SETBASICSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define EPSII_PDM_1_GETBASICSETTINGS_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define EPSII_PDM_1_GETBASICAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define EPSII_PDM_1_GETBASICAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define EPSII_PDM_1_GETMAINAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define EPSII_PDM_1_GETMAINAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define EPSII_PDM_1_ONESCP_RESETMAINAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define EPSII_PDM_1_ONESCP_RESETMAINAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x00000010)
#define EPSII_PDM_1_ONESCP_RESETBASICAPPERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000011)
#define EPSII_PDM_1_ONESCP_RESETBASICAPPEXCEPTIONS_FUNCRESP_ID ((funcIdType_t) 0x00000012)
#define EPSII_PDM_1_GETBULKTELEMETRY_FUNCRESP_ID ((funcIdType_t) 0x00000013)
#define EPSII_PDM_1_RESETDEVICE_FUNCRESP_ID ((funcIdType_t) 0x00000020)
#define EPSII_PDM_1_FORCEINSTALLMAINAPP_FUNCRESP_ID ((funcIdType_t) 0x00000021)
#define EPSII_PDM_1_FORCEINSTALLBASICAPP_FUNCRESP_ID ((funcIdType_t) 0x00000022)
#define EPSII_PDM_1_GETBOOTLOADERERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000023)
#define EPSII_PDM_1_RESETBOOTLDRERRCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000024)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Units are signed mA, mV, mC, mT, etc.
*/
#define EPSII_PDM_1_ESEPSII_PDM_RESERVEDVALUES_ESEPSIISSVPDM_MAX_VAL ((uint32_t) 2147483632)
#define EPSII_PDM_1_ESEPSII_PDM_RESERVEDVALUES_ESEPSIISSVPDM_UNKNOWN_VAL ((uint32_t) 2147483647)
#define EPSII_PDM_1_ESEPSII_PDM_RESERVEDVALUES_ESEPSIISSVPDM_ERROR_VAL ((uint32_t) 2147483646)
#define EPSII_PDM_1_ESEPSII_PDM_RESERVEDVALUES_MAX_CNT  ((uint32_t) 2147483647)
typedef uint32_t EPSII_PDM_1_ESEPSII_PDM_ReservedValues_t;

/*
    Telemetry sensors IDs
*/
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_NULL_ID ((uint16_t) 0)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1P_I_ID ((uint16_t) 1)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1P_U_ID ((uint16_t) 2)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1P_P_ID ((uint16_t) 3)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1P_T_ID ((uint16_t) 4)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1R_I_ID ((uint16_t) 5)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1R_U_ID ((uint16_t) 6)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1R_P_ID ((uint16_t) 7)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_1R_T_ID ((uint16_t) 8)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2P_I_ID ((uint16_t) 9)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2P_U_ID ((uint16_t) 10)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2P_P_ID ((uint16_t) 11)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2P_T_ID ((uint16_t) 12)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2R_I_ID ((uint16_t) 13)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2R_U_ID ((uint16_t) 14)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2R_P_ID ((uint16_t) 15)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_3V3_2R_T_ID ((uint16_t) 16)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1P_I_ID ((uint16_t) 17)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1P_U_ID ((uint16_t) 18)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1P_P_ID ((uint16_t) 19)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1P_T_ID ((uint16_t) 20)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1R_I_ID ((uint16_t) 21)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1R_U_ID ((uint16_t) 22)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1R_P_ID ((uint16_t) 23)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_1R_T_ID ((uint16_t) 24)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2P_I_ID ((uint16_t) 25)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2P_U_ID ((uint16_t) 26)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2P_P_ID ((uint16_t) 27)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2P_T_ID ((uint16_t) 28)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2R_I_ID ((uint16_t) 29)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2R_U_ID ((uint16_t) 30)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2R_P_ID ((uint16_t) 31)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_5V_2R_T_ID ((uint16_t) 32)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_P_I_ID ((uint16_t) 33)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_P_U_ID ((uint16_t) 34)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_P_P_ID ((uint16_t) 35)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_P_T_ID ((uint16_t) 36)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_R_I_ID ((uint16_t) 37)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_R_U_ID ((uint16_t) 38)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_R_P_ID ((uint16_t) 39)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_INA_LUP_IN_12V_R_T_ID ((uint16_t) 40)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_TEMPERATURE_PCB_1_ID ((uint16_t) 41)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_TEMPERATURE_PCB_2_ID ((uint16_t) 42)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_CPU_T_ID ((uint16_t) 43)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_CPU_AVCC_U_ID ((uint16_t) 44)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_SYS_BUS_V_IN_MON ((uint16_t) 45)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_BAT_RAW_V_OUT_MON ((uint16_t) 46)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_BAT_RAW_I_1_OUT_MON ((uint16_t) 47)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_BAT_RAW_I_2_OUT_MON ((uint16_t) 48)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_12V_OUT_MON ((uint16_t) 49)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_5V_OUT_MON_1 ((uint16_t) 50)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_5V_OUT_MON_2 ((uint16_t) 51)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_3V3_OUT_MON_1 ((uint16_t) 52)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_ESEPSIISSVPDM_ADC_3V3_OUT_MON_2 ((uint16_t) 53)
#define EPSII_PDM_1_ESEPSII_PDM_SENSORIDS_MAX_CNT  ((uint16_t) 54)
typedef uint16_t EPSII_PDM_1_ESEPSII_PDM_SensorIDs_t;

/*
    Structure for Voltage, Current, Power
*/
typedef struct {
    int32_t i32U;
    int32_t i32I;
    int32_t i32P;
} PACKED_STRUCT EPSII_PDM_1_ESEPSII_UIP_t;

/*
    List with error types
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
    uint16_t u16EDC_INIT_CONFIG_NVM_1_CORRUPTED;
    uint16_t u16EDC_INIT_CONFIG_NVM_2_CORRUPTED;
    uint16_t u16EDC_EXT_FRAM_PROBE_FAILED;
    uint16_t u16EDC_NVM_ALLOCATED_SIZE;
    uint16_t u16EDC_NVM_USED_SIZE;
    uint16_t u16EDC_BASIC_SETTINGS_NVM_CORRUPTED;
} PACKED_STRUCT EPSII_PDM_1_SDiagErrCounter_t;

/*
    Firmware types
*/
#define EPSII_PDM_1_ESDI_FIRMWARETYPE_ESDIFT_Production ((uint8_t) 0)
#define EPSII_PDM_1_ESDI_FIRMWARETYPE_ESDIFT_BasicApp ((uint8_t) 1)
#define EPSII_PDM_1_ESDI_FIRMWARETYPE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t EPSII_PDM_1_ESDI_FirmwareType_t;

/*
    Set/Get GPIO mask, use as bitmask
*/
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT1 ((uint8_t) 1)
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT2 ((uint8_t) 2)
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT3 ((uint8_t) 4)
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT4 ((uint8_t) 8)
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT5 ((uint8_t) 16)
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT6 ((uint8_t) 32)
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT7 ((uint8_t) 64)
#define EPSII_PDM_1_SGGPIO_BITMASK_SGGPIOBM_DigOUT8 ((uint8_t) 128)
#define EPSII_PDM_1_SGGPIO_BITMASK_MAX_CNT  ((uint8_t) 129)
typedef uint8_t EPSII_PDM_1_SGGPIO_Bitmask_t;

/*
    Set/Get GPIO mask, use as bitmask
*/
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT_OFF ((uint8_t) 0)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT1 ((uint8_t) 1)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT2 ((uint8_t) 2)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT3 ((uint8_t) 4)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT4 ((uint8_t) 8)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT5 ((uint8_t) 16)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT6 ((uint8_t) 32)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT7 ((uint8_t) 64)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_SGGPIOBM_DigOUT8 ((uint8_t) 128)
#define EPSII_PDM_1_SGGPIO_ONOFF_MASK_MAX_CNT  ((uint8_t) 129)
typedef uint8_t EPSII_PDM_1_SGGPIO_OnOff_mask_t;

/*
    Response error of SetPC104GPIO command
*/
#define EPSII_PDM_1_SGGPIO_SETERROR_SGGPIOE_SUCCESS ((uint8_t) 0)
#define EPSII_PDM_1_SGGPIO_SETERROR_SGGPIOE_BAD_STATE ((uint8_t) 1)
#define EPSII_PDM_1_SGGPIO_SETERROR_SGGPIOE_CHIP_ERR ((uint8_t) 2)
#define EPSII_PDM_1_SGGPIO_SETERROR_MAX_CNT  ((uint8_t) 3)
typedef uint8_t EPSII_PDM_1_SGGPIO_SetError_t;

/*
    Set/Get masks, use as bitmask
*/
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_BBUS_RAWOutputEnable ((uint32_t) 1)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_12V_MasterEnable ((uint32_t) 2)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_12V_SP1_3_Enable ((uint32_t) 4)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_12V_SP1_4_Enable ((uint32_t) 8)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_12V_SP1_5_Enable ((uint32_t) 16)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_5V_Ch1_MasterEnable ((uint32_t) 32)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_5V_Ch1_SP2_3_Enable ((uint32_t) 64)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_5V_Ch1_SP2_4_Enable ((uint32_t) 128)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_5V_Ch2_MasterEnable ((uint32_t) 256)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_5V_Ch2_SP1_6_Enable ((uint32_t) 512)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_5V_Ch2_SP1_7_Enable ((uint32_t) 1024)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_3V3_Ch1_MasterEnable ((uint32_t) 2048)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_3V3_Ch1_SP2_5_Enable ((uint32_t) 4096)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_3V3_Ch1_SP2_6_Enable ((uint32_t) 8192)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_3V3_Ch1_SP2_7_Enable ((uint32_t) 16384)
#define EPSII_PDM_1_SGPO_BITMASK_SGPOBM_3V3_Ch2_MasterEnable ((uint32_t) 32768)
#define EPSII_PDM_1_SGPO_BITMASK_MAX_CNT  ((uint32_t) 32769)
typedef uint32_t EPSII_PDM_1_SGPO_Bitmask_t;

/*
    Set/Get masks, use as bitmask
*/
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_Switch_OFF ((uint32_t) 0)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_BBUS_RAWOutputEnable ((uint32_t) 1)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_MasterEnable ((uint32_t) 2)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_SP1_3_Enable ((uint32_t) 4)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_SP1_4_Enable ((uint32_t) 8)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_12V_SP1_5_Enable ((uint32_t) 16)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch1_MasterEnable ((uint32_t) 32)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch1_SP2_3_Enable ((uint32_t) 64)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch1_SP2_4_Enable ((uint32_t) 128)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch2_MasterEnable ((uint32_t) 256)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch2_SP1_6_Enable ((uint32_t) 512)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_5V_Ch2_SP1_7_Enable ((uint32_t) 1024)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_MasterEnable ((uint32_t) 2048)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_SP2_5_Enable ((uint32_t) 4096)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_SP2_6_Enable ((uint32_t) 8192)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch1_SP2_7_Enable ((uint32_t) 16384)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_SGPOBM_3V3_Ch2_MasterEnable ((uint32_t) 32768)
#define EPSII_PDM_1_SGPO_ON_OFF_BITMASK_MAX_CNT  ((uint32_t) 32769)
typedef uint32_t EPSII_PDM_1_SGPO_ON_Off_Bitmask_t;

/*
    Set power outputs error codes
*/
#define EPSII_PDM_1_SGPO_SETERROR_SGPOSE_SUCCESS ((uint8_t) 0)
#define EPSII_PDM_1_SGPO_SETERROR_SGPOSE_BAD_STATE ((uint8_t) 1)
#define EPSII_PDM_1_SGPO_SETERROR_SGPOSE_CHIP_ERR ((uint8_t) 2)
#define EPSII_PDM_1_SGPO_SETERROR_MAX_CNT  ((uint8_t) 3)
typedef uint8_t EPSII_PDM_1_SGPO_SetError_t;

/*
    Use as bitmask
*/
#define EPSII_PDM_1_SBSED_BITMASK_SBSEDBM_DiSABLED ((uint8_t) 0)
#define EPSII_PDM_1_SBSED_BITMASK_SBSEDBM_PHOENIX_MODE ((uint8_t) 2)
#define EPSII_PDM_1_SBSED_BITMASK_SBSEDBM_NORMAL_MODE ((uint8_t) 4)
#define EPSII_PDM_1_SBSED_BITMASK_SBSEDBM_PHOENIX_MODE_AND_NORMAL ((uint8_t) 6)
#define EPSII_PDM_1_SBSED_BITMASK_MAX_CNT  ((uint8_t) 7)
typedef uint8_t EPSII_PDM_1_SBSED_Bitmask_t;

/*
    Use as enum
*/
#define EPSII_PDM_1_SBSEDE_CONOPSMODE_SBSEDE_HELL_MODE ((uint8_t) 1)
#define EPSII_PDM_1_SBSEDE_CONOPSMODE_SBSEDE_OVH_MODE ((uint8_t) 2)
#define EPSII_PDM_1_SBSEDE_CONOPSMODE_SBSEDE_PHOENIX_MODE ((uint8_t) 3)
#define EPSII_PDM_1_SBSEDE_CONOPSMODE_SBSEDE_NORMAL_MODE ((uint8_t) 4)
#define EPSII_PDM_1_SBSEDE_CONOPSMODE_MAX_CNT  ((uint8_t) 5)
typedef uint8_t EPSII_PDM_1_SBSEDE_ConOpsMode_t;

/*
    Basic settings fields
*/
typedef struct {
    EPSII_PDM_1_SBSEDE_ConOpsMode_t eNConOpsStartMode;
    EPSII_PDM_1_SBSED_Bitmask_t eNBBUS_RAWOutputEnable;
    int32_t i32N12V_Voltage;
    int32_t i32N12V_CurrentLimit;
    EPSII_PDM_1_SBSED_Bitmask_t eN12V_MasterEnable;
    EPSII_PDM_1_SBSED_Bitmask_t eN12V_SP1_3_Enable;
    EPSII_PDM_1_SBSED_Bitmask_t eN12V_SP1_4_Enable;
    EPSII_PDM_1_SBSED_Bitmask_t eN12V_SP1_5_Enable;
    int32_t i32N5V_Ch1_CurrentLimit;
    EPSII_PDM_1_SBSED_Bitmask_t eN5V_Ch1_MasterEnable;
    EPSII_PDM_1_SBSED_Bitmask_t eN5V_Ch1_SP2_3_Enable;
    EPSII_PDM_1_SBSED_Bitmask_t eN5V_Ch1_SP2_4_Enable;
    int32_t i32N5V_Ch2_CurrentLimit;
    EPSII_PDM_1_SBSED_Bitmask_t eN5V_Ch2_MasterEnable;
    EPSII_PDM_1_SBSED_Bitmask_t eN5V_Ch2_SP1_6_Enable;
    EPSII_PDM_1_SBSED_Bitmask_t eN5V_Ch2_SP1_7_Enable;
    int32_t i32N3V3_Ch1_CurrentLimit;
    EPSII_PDM_1_SBSED_Bitmask_t eN3V3_Ch1_MasterEnable;
    EPSII_PDM_1_SBSED_Bitmask_t eN3V3_Ch1_SP2_5_Enable;
    EPSII_PDM_1_SBSED_Bitmask_t eN3V3_Ch1_SP2_6_Enable;
    EPSII_PDM_1_SBSED_Bitmask_t eN3V3_Ch1_SP2_7_Enable;
    int32_t i32N3V3_Ch2_CurrentLimit;
    EPSII_PDM_1_SBSED_Bitmask_t eN3V3_Ch2_MasterEnable;
    uint16_t u16NPC104_GPIO_InversedBitmask;
    uint16_t u16NPC104_GPIO_NormalModeValueBitmask;
    uint16_t u16NPC104_GPIO_PhoenixModeValueBitmask;
    uint16_t u16NPC104_GPIO_OvhModeValueBitmask;
} PACKED_STRUCT EPSII_PDM_1_SBasicSettings_t;

/*
    SetBasicSettings command error codes
*/
#define EPSII_PDM_1_SBS_SETERROR_SBSSE_SUCCESS ((uint8_t) 0)
#define EPSII_PDM_1_SBS_SETERROR_SBSSE_BAD_PARAMS ((uint8_t) 1)
#define EPSII_PDM_1_SBS_SETERROR_MAX_CNT  ((uint8_t) 2)
typedef uint8_t EPSII_PDM_1_SBS_SetError_t;

/*
    Error returned for GetBasicSettings command
*/
#define EPSII_PDM_1_SBS_GETERROR_SBSGE_SUCCESS ((uint8_t) 0)
#define EPSII_PDM_1_SBS_GETERROR_SBSGE_NVM_ERR ((uint8_t) 1)
#define EPSII_PDM_1_SBS_GETERROR_SBSGE_CONFIG_NOT_SET ((uint8_t) 2)
#define EPSII_PDM_1_SBS_GETERROR_MAX_CNT  ((uint8_t) 3)
typedef uint8_t EPSII_PDM_1_SBS_GetError_t;

typedef struct {
    int32_t i32In_SysBUS_Voltage;
    EPSII_PDM_1_ESEPSII_UIP_t sOut_BatRAW_Output_Sense;
    EPSII_PDM_1_ESEPSII_UIP_t sOut_12V_Output_Sense;
    int32_t i32Out_12V_Output_ILimit;
    EPSII_PDM_1_ESEPSII_UIP_t sOut_5V_Output1_Sense;
    int32_t i32Out_5V_Output1_ILimit;
    EPSII_PDM_1_ESEPSII_UIP_t sOut_5V_Output2_Sense;
    int32_t i32Out_5V_Output2_ILimit;
    EPSII_PDM_1_ESEPSII_UIP_t sOut_3V3_Output1_Sense;
    int32_t i32Out_3V3_Output1_ILimit;
    EPSII_PDM_1_ESEPSII_UIP_t sOut_3V3_Output2_Sense;
    int32_t i32Out_3V3_Output2_ILimit;
} PACKED_STRUCT EPSII_PDM_1_SPowerDistributionInfo_t;

/*
    Status of chips as seen by CPU
*/
#define EPSII_PDM_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_UNKNOWN ((uint8_t) 0)
#define EPSII_PDM_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_ONLINE ((uint8_t) 1)
#define EPSII_PDM_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_COM_ERR ((uint8_t) 2)
#define EPSII_PDM_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_COM_TIMEOUT ((uint8_t) 3)
#define EPSII_PDM_1_EDHI_CHIPSTATUS_EDHICS_EMDCS_DRV_DISABLED ((uint8_t) 4)
#define EPSII_PDM_1_EDHI_CHIPSTATUS_MAX_CNT  ((uint8_t) 5)
typedef uint8_t EPSII_PDM_1_EDHI_ChipStatus_t;

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
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_3V3_1P;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_3V3_1R;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_3V3_2P;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_3V3_2R;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_5V_1P;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_5V_1R;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_5V_2P;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_5V_2R;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_12V_P;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_LUP_12V_R;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_OUTU_12V_P;
    EPSII_PDM_1_EDHI_ChipStatus_t eDPOT_MCP4562_OUTU_12V_R;
    EPSII_PDM_1_EDHI_ChipStatus_t eGPIO_PCA9538_U1001;
    EPSII_PDM_1_EDHI_ChipStatus_t eGPIO_PCA9538_U1000;
    EPSII_PDM_1_EDHI_ChipStatus_t eGPIO_PCA9538_U1004;
    EPSII_PDM_1_EDHI_ChipStatus_t eGPIO_PCA9538_U1011;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_3V3_1P;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_3V3_1R;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_3V3_2P;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_3V3_2R;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_5V_1P;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_5V_1R;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_5V_2P;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_5V_2R;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_12V_P;
    EPSII_PDM_1_EDHI_ChipStatus_t eINA_LUP_IN_12V_R;
    EPSII_PDM_1_EDHI_ChipStatus_t eTMP117_U1014;
    EPSII_PDM_1_EDHI_ChipStatus_t eTMP117_U1031;
} PACKED_STRUCT EPSII_PDM_1_SGetDeviceHealthInfo_t;

typedef struct {
    uint16_t u16C_app_restart_errors;
    uint8_t u8G_pAppCyclesErrors;
    uint8_t u8Reserved;
    uint16_t u16G_pIntegrityCheckStates;
} PACKED_STRUCT EPSII_PDM_1_SResetBootLdrErrCounters_t;

/*
    Structure of the data about the exceptions
*/
typedef struct {
    uint16_t u16M_nFileID;
    uint16_t u16M_nLineNum;
} PACKED_STRUCT EPSII_PDM_1_SMSP_Exception_t;


typedef struct {
    EPSII_PDM_1_SGGPIO_Bitmask_t eFilterMask;
    EPSII_PDM_1_SGGPIO_OnOff_mask_t eValuesMaskReq;
} PACKED_STRUCT EPSII_PDM_1SetPC104GPIORequestData_t;

typedef struct {
    uint32_t u32PktIDReq;
    EPSII_PDM_1_ESEPSII_PDM_SensorIDs_t aeSensorsIDs[50];
} PACKED_STRUCT EPSII_PDM_1GetRAWSensorsRequestData_t;

typedef struct {
    EPSII_PDM_1_SGPO_Bitmask_t eFilterMask;
    EPSII_PDM_1_SGPO_ON_Off_Bitmask_t eValuesMask;
} PACKED_STRUCT EPSII_PDM_1SetPowerOutputsRequestData_t;

typedef struct {
    EPSII_PDM_1_SBasicSettings_t sBasicSettings;
} PACKED_STRUCT EPSII_PDM_1SetBasicSettingsRequestData_t;


typedef struct {
    uint16_t u16ModuleTypeID;
    uint8_t u8ModuleTypeSize;
    char strModuleType[20];
    uint16_t u16ModuleHWVersion;
    uint8_t u8DeviceSerialNumberSize;
    char strDeviceSerialNumber[30];
    EPSII_PDM_1_ESDI_FirmwareType_t eFWTypeID;
    uint8_t u8FWTypeSize;
    char strFWType[20];
    uint16_t u16FWVersionMaj;
    uint16_t u16FWVersionMin;
} PACKED_STRUCT EPSII_PDM_1GetDeviceInfoResponseData_t;

typedef struct {
    EPSII_PDM_1_SPowerDistributionInfo_t sPowerDistributionInfo;
} PACKED_STRUCT EPSII_PDM_1GetPowerDistributionInfoResponseData_t;

typedef struct {
    EPSII_PDM_1_SGetDeviceHealthInfo_t sGetDeviceHealthInfo;
} PACKED_STRUCT EPSII_PDM_1GetDeviceHealthInfoResponseData_t;

typedef struct {
    EPSII_PDM_1_SGGPIO_SetError_t eErr;
} PACKED_STRUCT EPSII_PDM_1SetPC104GPIOResponseData_t;

typedef struct {
    uint8_t u8CurrentValues;
} PACKED_STRUCT EPSII_PDM_1GetPC104GPIOResponseData_t;

typedef struct {
    uint32_t u32PktID;
    int32_t ai32SensorValues[50];
} PACKED_STRUCT EPSII_PDM_1GetRAWSensorsResponseData_t;

typedef struct {
    EPSII_PDM_1_SGPO_SetError_t eErr;
} PACKED_STRUCT EPSII_PDM_1SetPowerOutputsResponseData_t;

typedef struct {
    uint32_t u32ValuesMask;
} PACKED_STRUCT EPSII_PDM_1GetPowerOutputsResponseData_t;

typedef struct {
    EPSII_PDM_1_SBS_SetError_t eErr;
} PACKED_STRUCT EPSII_PDM_1SetBasicSettingsResponseData_t;

typedef struct {
    EPSII_PDM_1_SBS_GetError_t eErr;
    EPSII_PDM_1_SBasicSettings_t sBasicSettings;
} PACKED_STRUCT EPSII_PDM_1GetBasicSettingsResponseData_t;

typedef struct {
    EPSII_PDM_1_SMSP_Exception_t asExceptions[16];
} PACKED_STRUCT EPSII_PDM_1GetBasicAppExceptionsResponseData_t;

typedef struct {
    EPSII_PDM_1_SDiagErrCounter_t sErrorCounters;
} PACKED_STRUCT EPSII_PDM_1GetBasicAppErrCountersResponseData_t;

typedef struct {
    EPSII_PDM_1_SMSP_Exception_t asExceptions[16];
} PACKED_STRUCT EPSII_PDM_1GetMainAppExceptionsResponseData_t;

typedef struct {
    EPSII_PDM_1_SDiagErrCounter_t sErrorCounters;
} PACKED_STRUCT EPSII_PDM_1GetMainAppErrCountersResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetMainAppErrCountersResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetMainAppExceptionsResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetBasicAppErrCountersResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_PDM_1OnESCP_ResetBasicAppExceptionsResponseData_t;

typedef struct {
    uint8_t u8ConOpsMode;
    uint8_t u8GPIOStates;
    uint32_t u32PowerOutputsStates;
    EPSII_PDM_1_SPowerDistributionInfo_t sPowerDistributionInfo;
    EPSII_PDM_1_SGetDeviceHealthInfo_t sGetDeviceHealthInfo;
    EPSII_PDM_1_SResetBootLdrErrCounters_t sResetBootLdrErrCounters;
} PACKED_STRUCT EPSII_PDM_1GetBulkTelemetryResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_PDM_1ResetDeviceResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_PDM_1ForceInstallMainAppResponseData_t;

typedef struct {
    bool bResult;
} PACKED_STRUCT EPSII_PDM_1ForceInstallBasicAppResponseData_t;

typedef struct {
    EPSII_PDM_1_SResetBootLdrErrCounters_t sResetBootLdrErrCounters;
} PACKED_STRUCT EPSII_PDM_1GetBootLoaderErrCountersResponseData_t;

typedef struct {
    EPSII_PDM_1_SResetBootLdrErrCounters_t sResetBootLdrErrCounters;
} PACKED_STRUCT EPSII_PDM_1ResetBootLdrErrCountersResponseData_t;


#endif  // #ifndef __FP_EPSII_PDM_1PROTOCOLTYPES_H__

