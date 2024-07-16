/*!
********************************************************************************************
* @file datacache.h
* @brief Data Cache public header generator
********************************************************************************************
* @version           interface data_cache v0.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_DC v0.8
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __DATACACHE_H__
#define __DATACACHE_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include "datacache_cfg.h"

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/

typedef enum
{
    DC_NOT_INITIALIZED = 0,       // DC has not yet been initialised, so the data provided may not be relevant
    DC_DATA_STATUS_OK = 1,        // the data has been updated by its producer in the configured time period
    DC_DATA_STATUS_INIT = 2,      // the data is initialised with ROM values by DC and has not yet been updated
    DC_DATA_STATUS_TOUT = 3       // the data expected update period has not been respected
} dc_data_status_t;

typedef enum
{
    DC_DATA_INPUT_INTERNAL,       // data is fed to the DataCache by internal components
    DC_DATA_INPUT_EXTERNAL,       // data is fed to the DataCache externally, e.g. simulation interface
    DC_DATA_INPUT_MAX
} dc_data_input_t;

// Define internal data attribute ID as specified in the FIDL file 
#define DC_ATTR_ID_OBC_0_DATA 0x00000010
#define DC_ATTR_ID_ADCS_0_DATA 0x00000011
#define DC_ATTR_ID_ADCS_1_DATA 0x00000012
#define DC_ATTR_ID_ADCS_2_DATA 0x00000013
#define DC_ATTR_ID_EPS_0_DATA 0x00000014
#define DC_ATTR_ID_SSP_0_DATA 0x00000015
#define DC_ATTR_ID_SSP_1_DATA 0x00000016
#define DC_ATTR_ID_SSP_2_DATA 0x00000017
#define DC_ATTR_ID_AOCS_CNTRL_TLM_DATA 0x00000019
#define DC_ATTR_ID_OS_TASK_DATA 0x00000020
#define DC_ATTR_ID_SSP_3_DATA 0x00000021
#define DC_ATTR_ID_SENSOR_MAG_PRIMARY_DATA 0x00000022
#define DC_ATTR_ID_SENSOR_MAG_SECONDARY_DATA 0x00000023
#define DC_ATTR_ID_SENSOR_GYRO_DATA 0x00000024
#define DC_ATTR_ID_SENSOR_COARSE_SUN_DATA 0x00000025
#define DC_ATTR_ID_ES_ADCS_SENSOR_MAG_PRIMARY_DATA 0x00000026
#define DC_ATTR_ID_ES_ADCS_SENSOR_MAG_SECONDARY_DATA 0x00000027
#define DC_ATTR_ID_ES_ADCS_SENSOR_GYRO_DATA 0x00000028
#define DC_ATTR_ID_ES_ADCS_SENSOR_CSS_DATA 0x00000029
#define DC_ATTR_ID_ES_ADCS_ESTIMATES_BDOT_DATA 0x00000030
#define DC_ATTR_ID_ES_ADCS_CONTROL_VALUES_MTQ_DATA 0x00000031
#define DC_ATTR_ID_CONOPSFLAGS_DATA 0x00000032
#define DC_ATTR_ID_AOCS_CNTRL_SYS_STATE_DATA 0x00000033
#define DC_ATTR_ID_ADCS_3_DATA 0x00000034
#define DC_ATTR_ID_ADCS_4_DATA 0x00000035
#define DC_ATTR_ID_EPS_9_DATA 0x00000038
#define DC_ATTR_ID_EPS_10_DATA 0x00000039
#define DC_ATTR_ID_EPS_14_DATA 0x00000043
#define DC_ATTR_ID_SENSOR_ACC_PRIMARY_DATA 0x00000044
#define DC_ATTR_ID_SENSOR_ACC_SECONDARY_DATA 0x00000045
#define DC_ATTR_ID_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA 0x00000046
#define DC_ATTR_ID_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA 0x00000047
#define DC_ATTR_ID_SENSOR_PANEL_TEMP_DATA 0x00000048
#define DC_ATTR_ID_SENSOR_PANEL_TEMP_SAT_FRAME_DATA 0x00000049
#define DC_ATTR_ID_SENSOR_GYRO_TEMP_DATA 0x0000004A
#define DC_ATTR_ID_SENSOR_GYRO_TEMP_SAT_FRAME_DATA 0x0000004B
#define DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA 0x0000004C
#define DC_ATTR_ID_CUBEADCS_GEN2_OP_STATUS_APP_DATA 0x0000004D
#define DC_ATTR_ID_AOCS_CNTRL_REF_PARAMS_DATA 0x0000004E
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_166_DATA 0x0000004F
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_167_DATA 0x00000050
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_168_DATA 0x00000051
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_169_DATA 0x00000052
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_170_DATA 0x00000053
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_171_DATA 0x00000054
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_172_DATA 0x00000055
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_173_DATA 0x00000056
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_174_DATA 0x00000057
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_175_DATA 0x00000058
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_176_DATA 0x00000059
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_177_DATA 0x0000005A
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_178_DATA 0x0000005B
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_179_DATA 0x0000005C
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_180_DATA 0x0000005D
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_203_DATA 0x0000005E
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_204_DATA 0x0000005F
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_205_DATA 0x00000060
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_206_DATA 0x00000061
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_207_DATA 0x00000062
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA 0x00000063
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA 0x00000064
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_209_DATA 0x00000065
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_210_DATA 0x00000066
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_211_DATA 0x00000067
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_212_DATA 0x00000068
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_213_DATA 0x00000069
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_214_DATA 0x0000006A
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_216_DATA 0x0000006B
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_217_DATA 0x0000006C
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_218_DATA 0x0000006D
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_225_DATA 0x0000006E
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_226_DATA 0x0000006F
#define DC_ATTR_ID_CUBEADCS_GEN2_TLM_FRAME_165_DATA 0x00000070
#define DC_ATTR_ID_GNSS_TIME_DATA 0x00000071
#define DC_ATTR_ID_GNSS_BESTXYZ_DATA 0x00000072
#define DC_ATTR_ID_EPSOVERALLBATTERYINFO_DATA 0x00000073
#define DC_ATTR_ID_EPS2_BP_INST0_BP_INFO_DATA 0x00000101
#define DC_ATTR_ID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA 0x00000102
#define DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR1_DATA 0x00000103
#define DC_ATTR_ID_EPS2_BP_INST0_INA_SENSOR2_DATA 0x00000104
#define DC_ATTR_ID_EPS2_BP_INST0_BALANCER_INFO_DATA 0x00000105
#define DC_ATTR_ID_EPS2_BP_INST0_BALANCER_STATUS_DATA 0x00000106
#define DC_ATTR_ID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA 0x00000107
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XP_DATA 0x00000108
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_XR_DATA 0x00000109
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YP_DATA 0x0000010A
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_YR_DATA 0x0000010B
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZP_DATA 0x0000010C
#define DC_ATTR_ID_EPS2_BP_INST0_CHARGER_ZR_DATA 0x0000010D
#define DC_ATTR_ID_EPS2_BP_INST1_BP_INFO_DATA 0x0000010E
#define DC_ATTR_ID_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA 0x0000010F
#define DC_ATTR_ID_EPS2_BP_INST1_INA_SENSOR1_DATA 0x00000110
#define DC_ATTR_ID_EPS2_BP_INST1_INA_SENSOR2_DATA 0x00000111
#define DC_ATTR_ID_EPS2_BP_INST1_BALANCER_INFO_DATA 0x00000112
#define DC_ATTR_ID_EPS2_BP_INST1_BALANCER_STATUS_DATA 0x00000113
#define DC_ATTR_ID_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA 0x00000114
#define DC_ATTR_ID_EPS2_BP_INST1_CHARGER_XP_DATA 0x00000115
#define DC_ATTR_ID_EPS2_BP_INST1_CHARGER_XR_DATA 0x00000116
#define DC_ATTR_ID_EPS2_BP_INST1_CHARGER_YP_DATA 0x00000117
#define DC_ATTR_ID_EPS2_BP_INST1_CHARGER_YR_DATA 0x00000118
#define DC_ATTR_ID_EPS2_BP_INST1_CHARGER_ZP_DATA 0x00000119
#define DC_ATTR_ID_EPS2_BP_INST1_CHARGER_ZR_DATA 0x0000011A
#define DC_ATTR_ID_EPS2_BP_INST2_BP_INFO_DATA 0x0000011B
#define DC_ATTR_ID_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA 0x0000011C
#define DC_ATTR_ID_EPS2_BP_INST2_INA_SENSOR1_DATA 0x0000011D
#define DC_ATTR_ID_EPS2_BP_INST2_INA_SENSOR2_DATA 0x0000011E
#define DC_ATTR_ID_EPS2_BP_INST2_BALANCER_INFO_DATA 0x0000011F
#define DC_ATTR_ID_EPS2_BP_INST2_BALANCER_STATUS_DATA 0x00000120
#define DC_ATTR_ID_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA 0x00000121
#define DC_ATTR_ID_EPS2_BP_INST2_CHARGER_XP_DATA 0x00000122
#define DC_ATTR_ID_EPS2_BP_INST2_CHARGER_XR_DATA 0x00000123
#define DC_ATTR_ID_EPS2_BP_INST2_CHARGER_YP_DATA 0x00000124
#define DC_ATTR_ID_EPS2_BP_INST2_CHARGER_YR_DATA 0x00000125
#define DC_ATTR_ID_EPS2_BP_INST2_CHARGER_ZP_DATA 0x00000126
#define DC_ATTR_ID_EPS2_BP_INST2_CHARGER_ZR_DATA 0x00000127


typedef struct {
    uint8_t u8OpMode;
    uint32_t u32UpTime;
    uint16_t u16TotalResetCount;
    uint16_t u16ResetReasonBitField;
    uint16_t u16PayloadModesStatus;
} PACKED_STRUCT DATA_CACHE_OBC_0_t;

typedef struct {
    int16_t ai16MagFieldVec[3];
    int16_t ai16CoarseSunVec[3];
    int16_t ai16FineSunVec[3];
    int16_t ai16NadirVec[3];
    int16_t ai16AngRateVec[3];
    int16_t ai16WheelSpeedArr[3];
} PACKED_STRUCT DATA_CACHE_ADCS_0_t;

typedef struct {
    int16_t ai16EstQSet[3];
    int16_t ai16EstAngRateVec[3];
    int16_t ai16ControlledAngles[3];
    int16_t ai16RawGyroRates[3];
} PACKED_STRUCT DATA_CACHE_ADCS_1_t;

typedef struct {
    uint8_t au8AdcsState[6];
} PACKED_STRUCT DATA_CACHE_ADCS_2_t;

typedef struct {
    int64_t i64BattEnergy;
    int64_t i64BattCharge;
    int64_t i64BattChargeCapacity;
    int64_t i64BattPercent;
    int32_t i32BattVoltage;
    int32_t i32BattCurrent;
    int32_t i32BattTemperature;
} PACKED_STRUCT DATA_CACHE_EPS_0_t;

typedef struct {
    uint16_t u16SunDataMain;
    uint16_t u16SunDataExt;
    int16_t i16TempMCU;
    int16_t i16TempMain;
    int16_t i16TempExt1;
    int16_t i16TempExt2;
} PACKED_STRUCT DATA_CACHE_SSP_0_t;

typedef struct {
    uint16_t u16SunDataMain;
    uint16_t u16SunDataExt;
    int16_t i16TempMCU;
    int16_t i16TempMain;
    int16_t i16TempExt1;
    int16_t i16TempExt2;
} PACKED_STRUCT DATA_CACHE_SSP_1_t;

typedef struct {
    uint16_t u16SunDataMain;
    uint16_t u16SunDataExt;
    int16_t i16TempMCU;
    int16_t i16TempMain;
    int16_t i16TempExt1;
    int16_t i16TempExt2;
} PACKED_STRUCT DATA_CACHE_SSP_2_t;

typedef struct {
    uint32_t u32AdcsErrFlags;
    int32_t i32EstAngRateNorm;
    int32_t ai32EstAngRateVec[3];
    int32_t ai32EstAttAngles[3];
    int16_t ai16MeasWheelSpeed[4];
} PACKED_STRUCT DATA_CACHE_AOCS_CNTRL_TLM_t;

typedef struct {
    int16_t ai16TaskStackMaxUnusedSize[30];
} PACKED_STRUCT DATA_CACHE_TaskStats_t;

typedef struct {
    uint16_t u16SunDataMain;
    uint16_t u16SunDataExt;
    int16_t i16TempMCU;
    int16_t i16TempMain;
    int16_t i16TempExt1;
    int16_t i16TempExt2;
} PACKED_STRUCT DATA_CACHE_SSP_3_t;

typedef struct {
    int32_t i32MAG_X;
    int32_t i32MAG_Y;
    int32_t i32MAG_Z;
} PACKED_STRUCT DATA_CACHE_SENSOR_MAG_PRIMARY_t;

typedef struct {
    int32_t i32MAG_X;
    int32_t i32MAG_Y;
    int32_t i32MAG_Z;
} PACKED_STRUCT DATA_CACHE_SENSOR_MAG_SECONDARY_t;

typedef struct {
    int32_t i32GYRO_1;
    int32_t i32GYRO_2;
    int32_t i32GYRO_3;
} PACKED_STRUCT DATA_CACHE_SENSOR_GYRO_t;

typedef struct {
    int32_t i32CSS_PANEL_1;
    int32_t i32CSS_PANEL_2;
    int32_t i32CSS_PANEL_3;
    int32_t i32CSS_PANEL_4;
    int32_t i32CSS_PANEL_5;
    int32_t i32CSS_PANEL_6;
} PACKED_STRUCT DATA_CACHE_SENSOR_COARSE_SUN_t;

typedef struct {
    int32_t i32MAG_X_CURRENT;
    int32_t i32MAG_Y_CURRENT;
    int32_t i32MAG_Z_CURRENT;
    int32_t i32MAG_X_PREVIOUS;
    int32_t i32MAG_Y_PREVIOUS;
    int32_t i32MAG_Z_PREVIOUS;
} PACKED_STRUCT DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t;

typedef struct {
    int32_t i32MAG_X_CURRENT;
    int32_t i32MAG_Y_CURRENT;
    int32_t i32MAG_Z_CURRENT;
    int32_t i32MAG_X_PREVIOUS;
    int32_t i32MAG_Y_PREVIOUS;
    int32_t i32MAG_Z_PREVIOUS;
} PACKED_STRUCT DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t;

typedef struct {
    int32_t i32GYRO_X;
    int32_t i32GYRO_Y;
    int32_t i32GYRO_Z;
} PACKED_STRUCT DATA_CACHE_ES_ADCS_SENSOR_GYRO_t;

typedef struct {
    int32_t i32CSS_AXIS_X_PLUS;
    int32_t i32CSS_AXIS_Y_PLUS;
    int32_t i32CSS_AXIS_Z_PLUS;
    int32_t i32CSS_AXIS_X_MINUS;
    int32_t i32CSS_AXIS_Y_MINUS;
    int32_t i32CSS_AXIS_Z_MINUS;
} PACKED_STRUCT DATA_CACHE_ES_ADCS_SENSOR_CSS_t;

typedef struct {
    int32_t i32MAG_FIELD_DERIV_X;
    int32_t i32MAG_FIELD_DERIV_Y;
    int32_t i32MAG_FIELD_DERIV_Z;
} PACKED_STRUCT DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t;

typedef struct {
    int8_t i8MAGTORQUE_VALUE_X;
    int8_t i8MAGTORQUE_VALUE_Y;
    int8_t i8MAGTORQUE_VALUE_Z;
} PACKED_STRUCT DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t;

typedef struct {
    bool bPAY_ERR;
    bool bADCS_ERR;
    bool bDETUMB_COMPLETED;
} PACKED_STRUCT DATA_CACHE_ConOpsFlags_t;

typedef struct {
    uint8_t u8AdcsSysState;
    uint8_t u8AdcsSysStateStatus;
} PACKED_STRUCT DATA_CACHE_AOCS_CNTRL_SYS_STATE_t;

typedef struct {
    int16_t i16Est_roll_angle;
    int16_t i16Est_pitch_angle;
    int16_t i16Est_yaw_angle;
    int16_t i16IGRF_MagField_X;
    int16_t i16IGRF_MagField_Y;
    int16_t i16IGRF_MagField_Z;
    int16_t i16Modelled_Sun_V_X;
    int16_t i16Modelled_Sun_V_Y;
    int16_t i16Modelled_Sun_V_Z;
    int16_t i16EstGyroBias_X;
    int16_t i16EstGyroBias_Y;
    int16_t i16EstGyroBias_Z;
    int16_t i16Innovation_Vec_X;
    int16_t i16Innovation_Vec_Y;
    int16_t i16Innovation_Vec_Z;
    int16_t i16Err_Q1;
    int16_t i16Err_Q2;
    int16_t i16Err_Q3;
    int16_t i16RMS_Q1;
    int16_t i16RMS_Q2;
    int16_t i16RMS_Q3;
    int16_t i16X_AngRate_Cov;
    int16_t i16Y_AngRate_Cov;
    int16_t i16Z_AngRate_Cov;
    int16_t i16X_Rate;
    int16_t i16Y_Rate;
    int16_t i16Z_Rate;
    int16_t i16Q0;
    int16_t i16Q1;
    int16_t i16Q2;
} PACKED_STRUCT DATA_CACHE_ADCS_3_t;

typedef struct {
    uint16_t u16Cubesense1_3V3_Current;
    uint16_t u16Cubesense1_SRAM_Current;
    uint16_t u16Cubesense2_3V3_Current;
    uint16_t u16Cubesense2_SRAM_Current;
    uint16_t u16CubeControl_3V3_Current;
    uint16_t u16CubeControl_5V_Current;
    uint16_t u16CubeControl_Vbat_Current;
    uint16_t u16Wheel_1_Current;
    uint16_t u16Wheel_2_Current;
    uint16_t u16Wheel_3_Current;
    uint16_t u16CubeStar_Current;
    uint16_t u16MTQ_Current;
    int16_t i16CubeStar_MCU_Temp;
    int16_t i16ADCS_MCU_Temp;
    int16_t i16MTM_Temp;
    int16_t i16RMTM_Temp;
    int16_t i16X_Rate_Sensor_Temp;
    int16_t i16Y_Rate_Sensor_Temp;
    int16_t i16Z_Rate_Sensor_Temp;
} PACKED_STRUCT DATA_CACHE_ADCS_4_t;

/*
    GetPowerDistributionInfo from EPSII_PDM_1 interface
*/
typedef struct {
    int32_t i32In_SysBUS_Voltage;
    int32_t i32Out_BatRAW_Output_Sense_U;
    int32_t i32Out_BatRAW_Output_Sense_I;
    int32_t i32Out_BatRAW_Output_Sense_P;
    int32_t i32Out_12V_Output_Sense_U;
    int32_t i32Out_12V_Output_Sense_I;
    int32_t i32Out_12V_Output_Sense_P;
    int32_t i32Out_12V_Output_ILimit;
    int32_t i32Out_5V_Output1_Sense_U;
    int32_t i32Out_5V_Output1_Sense_I;
    int32_t i32Out_5V_Output1_Sense_P;
    int32_t i32Out_5V_Output1_ILimit;
    int32_t i32Out_5V_Output2_Sense_U;
    int32_t i32Out_5V_Output2_Sense_I;
    int32_t i32Out_5V_Output2_Sense_P;
    int32_t i32Out_5V_Output2_ILimit;
    int32_t i32Out_3V3_Output1_Sense_U;
    int32_t i32Out_3V3_Output1_Sense_I;
    int32_t i32Out_3V3_Output1_Sense_P;
    int32_t i32Out_3V3_Output1_ILimit;
    int32_t i32Out_3V3_Output2_Sense_U;
    int32_t i32Out_3V3_Output2_Sense_I;
    int32_t i32Out_3V3_Output2_Sense_P;
    int32_t i32Out_3V3_Output2_ILimit;
} PACKED_STRUCT DATA_CACHE_EPS_9_t;

/*
    GetDeviceHealthInfo from EPSII_PDM_1 interface
*/
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
    uint8_t u8DPOT_MCP4562_LUP_3V3_1P;
    uint8_t u8DPOT_MCP4562_LUP_3V3_1R;
    uint8_t u8DPOT_MCP4562_LUP_3V3_2P;
    uint8_t u8DPOT_MCP4562_LUP_3V3_2R;
    uint8_t u8DPOT_MCP4562_LUP_5V_1P;
    uint8_t u8DPOT_MCP4562_LUP_5V_1R;
    uint8_t u8DPOT_MCP4562_LUP_5V_2P;
    uint8_t u8DPOT_MCP4562_LUP_5V_2R;
    uint8_t u8DPOT_MCP4562_LUP_12V_P;
    uint8_t u8DPOT_MCP4562_LUP_12V_R;
    uint8_t u8DPOT_MCP4562_OUTU_12V_P;
    uint8_t u8DPOT_MCP4562_OUTU_12V_R;
    uint8_t u8GPIO_PCA9538_U1001;
    uint8_t u8GPIO_PCA9538_U1000;
    uint8_t u8GPIO_PCA9538_U1004;
    uint8_t u8GPIO_PCA9538_U1011;
    uint8_t u8INA_LUP_IN_3V3_1P;
    uint8_t u8INA_LUP_IN_3V3_1R;
    uint8_t u8INA_LUP_IN_3V3_2P;
    uint8_t u8INA_LUP_IN_3V3_2R;
    uint8_t u8INA_LUP_IN_5V_1P;
    uint8_t u8INA_LUP_IN_5V_1R;
    uint8_t u8INA_LUP_IN_5V_2P;
    uint8_t u8INA_LUP_IN_5V_2R;
    uint8_t u8INA_LUP_IN_12V_P;
    uint8_t u8INA_LUP_IN_12V_R;
    uint8_t u8TMP117_U1014;
    uint8_t u8TMP117_U1031;
} PACKED_STRUCT DATA_CACHE_EPS_10_t;

/*
    GetRAWSensors from EPSII_PDM_1 interface (Indexes 1-54)
*/
typedef struct {
    int32_t ai32Pdm_1_54_values[54];
} PACKED_STRUCT DATA_CACHE_EPS_14_t;

typedef struct {
    int32_t i32ACC_X;
    int32_t i32ACC_Y;
    int32_t i32ACC_Z;
} PACKED_STRUCT DATA_CACHE_SENSOR_ACC_PRIMARY_t;

typedef struct {
    int32_t i32ACC_X;
    int32_t i32ACC_Y;
    int32_t i32ACC_Z;
} PACKED_STRUCT DATA_CACHE_SENSOR_ACC_SECONDARY_t;

typedef struct {
    int32_t i32ACC_X;
    int32_t i32ACC_Y;
    int32_t i32ACC_Z;
} PACKED_STRUCT DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t;

typedef struct {
    int32_t i32ACC_X;
    int32_t i32ACC_Y;
    int32_t i32ACC_Z;
} PACKED_STRUCT DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t;

/*
    Panel temeprature sensors measurements in [degC] in Sensor Frame (mounting locations)
*/
typedef struct {
    int16_t i16PAN_1_TEMP;
    int16_t i16PAN_2_TEMP;
    int16_t i16PAN_3_TEMP;
    int16_t i16PAN_4_TEMP;
    int16_t i16PAN_5_TEMP;
    int16_t i16PAN_6_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_PANEL_TEMP_t;

/*
    Panel temeprature sensors measurements in [degC] in Satellite Frame
*/
typedef struct {
    int16_t i16PAN_X_PLUS_TEMP;
    int16_t i16PAN_Y_PLUS_TEMP;
    int16_t i16PAN_Z_PLUS_TEMP;
    int16_t i16PAN_X_MINUS_TEMP;
    int16_t i16PAN_Y_MINUS_TEMP;
    int16_t i16PAN_Z_MINUS_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t;

/*
    Rate sensors temperatures in the sensor frame
*/
typedef struct {
    int16_t i16GYRO_1_TEMP;
    int16_t i16GYRO_2_TEMP;
    int16_t i16GYRO_3_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_GYRO_TEMP_t;

/*
    Rate sensors temperature for the three primary axes (Satellite Frame)
*/
typedef struct {
    int16_t i16GYRO_X_TEMP;
    int16_t i16GYRO_Y_TEMP;
    int16_t i16GYRO_Z_TEMP;
} PACKED_STRUCT DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t;

/*
    CubeADCS Gen2 common operational status - TLM_137, TLM_183, TLM_230
*/
typedef struct {
    uint8_t u8State;
    uint8_t u8ResetReason;
    bool bDualBankBoot;
    bool bAppReadError;
    bool bAppEmptyError;
    bool bAppTypeError;
    bool bAppVectTblError;
    bool bConfigReadError;
    bool bConfigEmptyError;
    bool bConfigTypeError;
    bool bConfigMismatchError;
    bool bSharedParamsError;
    bool bPortValidationError;
    bool bPortDiscoveryError;
    bool bOtpSerialError;
    bool bCfgSerialError;
    bool bSerialMismatchError;
    bool bConfigUnlockError;
    bool bConfigInvalidError;
    uint8_t u8Rwl0;
    uint8_t u8Rwl1;
    uint8_t u8Rwl2;
    uint8_t u8Rwl3;
    uint8_t u8Mag0;
    uint8_t u8Mag1;
    uint8_t u8Gyro0;
    uint8_t u8Gyro1;
    uint8_t u8Fss0;
    uint8_t u8Fss1;
    uint8_t u8Fss2;
    uint8_t u8Fss3;
    uint8_t u8Hss0;
    uint8_t u8Hss1;
    uint8_t u8Str0;
    uint8_t u8Str1;
    uint8_t u8ExtSensor0;
    uint8_t u8ExtSensor1;
    uint32_t u32MasterSvc;
    uint32_t u32FramFsSvc;
    uint32_t u32EventLogSvc;
    uint32_t u32ImgLogSvc;
    uint32_t u32TlmLogSvc;
    uint32_t u32ImuSvc;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t;

/*
    CubeADCS Gen2 application control program operational status - TLM_185, TLM_199, TLM_200
*/
typedef struct {
    uint8_t u8Run_mode;
    uint8_t u8Control_mode;
    uint16_t u16Magnetic_control_timeout;
    uint8_t u8Estimator_main;
    uint8_t u8Estimator_backup;
    uint8_t u8Adcs_op_state;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t;

typedef struct {
    float fRefParam1;
    float fRefParam2;
    float fRefParam3;
} PACKED_STRUCT DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t;

/*
    CubeADCS Gen2 TLM_166 - Health telemetry for cubenode pst3s
*/
typedef struct {
    double dStr0McuTemp;
    double dStr0McuCurrent;
    uint16_t u16Str0McuVoltage;
    double dStr0Pst3sCurrent;
    bool bStr0Pst3sOvercurrent;
    double dStr1McuTemp;
    double dStr1McuCurrent;
    uint16_t u16Str1McuVoltage;
    double dStr1Pst3sCurrent;
    bool bStr1Pst3sOvercurrent;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t;

/*
    CubeADCS Gen2 TLM_167 - Health telemetry for CubeMag magnetometer
*/
typedef struct {
    double dMag0McuTemp;
    double dMag0McuCurrent;
    uint16_t u16Mag0McuVoltage;
    double dMag0PrimaryTemp;
    double dMag0RedTemp;
    uint32_t u32Mag0BurnCurrent;
    bool bMag0DeployPinState;
    bool bMag0BurnPinState;
    bool bMag0BurnUnderCurrent;
    bool bMag0BurnOverCurrent;
    bool bMag0DeployTimeout;
    double dMag1McuTemp;
    double dMag1McuCurrent;
    uint16_t u16Mag1McuVoltage;
    double dMag1PrimaryTemp;
    double dMag1RedTemp;
    uint32_t u32Mag1BurnCurrent;
    bool bMag1DeployPinState;
    bool bMag1BurnPinState;
    bool bMag1BurnUnderCurrent;
    bool bMag1BurnOverCurrent;
    bool bMag1DeployTimeout;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t;

/*
    CubeADCS Gen2 TLM_168 - Health telemetry for CubeSense Sun
*/
typedef struct {
    double dFss0McuTemp;
    double dFss0McuCurrent;
    uint16_t u16Fss0McuVoltage;
    double dFss0CurrentCam;
    double dFss0CurrentSram;
    bool bFss0OvercurrentCam;
    bool bFss0OvercurrentSram;
    double dFss1McuTemp;
    double dFss1McuCurrent;
    uint16_t u16Fss1McuVoltage;
    double dFss1CurrentCam;
    double dFss1CurrentSram;
    bool bFss1OvercurrentCam;
    bool bFss1OvercurrentSram;
    double dFss2McuTemp;
    double dFss2McuCurrent;
    uint16_t u16Fss2McuVoltage;
    double dFss2CurrentCam;
    double dFss2CurrentSram;
    bool bFss2OvercurrentCam;
    bool bFss2OvercurrentSram;
    double dFss3McuTemp;
    double dFss3McuCurrent;
    uint16_t u16Fss3McuVoltage;
    double dFss3CurrentCam;
    double dFss3CurrentSram;
    bool bFss3OvercurrentCam;
    bool bFss3OvercurrentSram;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t;

/*
    CubeADCS Gen2 TLM_169 - Torquer Current measurements
*/
typedef struct {
    float fMtq1TotalCurrentPeakPos;
    float fMtq1TotalCurrentAveragePos;
    float fMtq1TotalCurrentPeakNeg;
    float fMtq1TotalCurrentAverageNeg;
    float fMtq2TotalCurrentPeakPos;
    float fMtq2TotalCurrentAveragePos;
    float fMtq2TotalCurrentPeakNeg;
    float fMtq2TotalCurrentAverageNeg;
    float fMtq3TotalCurrentPeakPos;
    float fMtq3TotalCurrentAveragePos;
    float fMtq3TotalCurrentPeakNeg;
    float fMtq3TotalCurrentAverageNeg;
    uint8_t u8Mtq1Polarity;
    uint8_t u8Mtq2Polarity;
    uint8_t u8Mtq3Polarity;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t;

/*
    CubeADCS Gen2 TLM_170 - Raw CubeSense Sun telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dFss0Alpha;
    double dFss0Beta;
    uint8_t u8Fss0CaptureResult;
    uint8_t u8Fss0DetectionResult;
    double dFss1Alpha;
    double dFss1Beta;
    uint8_t u8Fss1CaptureResult;
    uint8_t u8Fss1DetectionResult;
    double dFss2Alpha;
    double dFss2Beta;
    uint8_t u8Fss2CaptureResult;
    uint8_t u8Fss2DetectionResult;
    double dFss3Alpha;
    double dFss3Beta;
    uint8_t u8Fss3CaptureResult;
    uint8_t u8Fss3DetectionResult;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t;

/*
    CubeADCS Gen2 TLM_171 - Raw external sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fExtSensor0Float0;
    float fExtSensor0Float1;
    float fExtSensor0Float2;
    float fExtSensor0Float3;
    float fExtSensor0Float4;
    float fExtSensor0Float5;
    float fExtSensor1Float0;
    float fExtSensor1Float1;
    float fExtSensor1Float2;
    float fExtSensor1Float3;
    float fExtSensor1Float4;
    float fExtSensor1Float5;
    bool bExtSensor0IsValid;
    bool bExtSensor1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t;

/*
    CubeADCS Gen2 TLM_172 - Controller telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dRpyCmdRoll;
    double dRpyCmdPitch;
    double dRpyCmdYaw;
    double dRpyErrRoll;
    double dRpyErrPitch;
    double dRpyErrYaw;
    float fTgtRefLat;
    float fTgtRefLon;
    int32_t i32TgtRefAlt;
    double dQuatErrQ0;
    double dQuatErrQ1;
    double dQuatErrQ2;
    float fRwl0CmdSpeed;
    float fRwl1CmdSpeed;
    float fRwl2CmdSpeed;
    float fRwl3CmdSpeed;
    float fRwl0CmdMom;
    float fRwl1CmdMom;
    float fRwl2CmdMom;
    float fRwl3CmdMom;
    float fRwl0CmdTorque;
    float fRwl1CmdTorque;
    float fRwl2CmdTorque;
    float fRwl3CmdTorque;
    double dMtq0CmdDip;
    double dMtq1CmdDip;
    double dMtq2CmdDip;
    float fMtq0CmdTorque;
    float fMtq1CmdTorque;
    float fMtq2CmdTorque;
    int16_t i16Mtq0CmdOnTime;
    int16_t i16Mtq1CmdOnTime;
    int16_t i16Mtq2CmdOnTime;
    uint16_t u16MagConTimeout;
    uint8_t u8ConModeActive;
    bool bRwl0ErrorFlag;
    bool bRwl1ErrorFlag;
    bool bRwl2ErrorFlag;
    bool bRwl3ErrorFlag;
    bool bRwl0ActiveFlag;
    bool bRwl1ActiveFlag;
    bool bRwl2ActiveFlag;
    bool bRwl3ActiveFlag;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t;

/*
    CubeADCS Gen2 TLM_173 - Backup estimator telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dEstRpyRoll;
    double dEstRpyPitch;
    double dEstRpyYaw;
    double dEstQuatQ0;
    double dEstQuatQ1;
    double dEstQuatQ2;
    double dEstQuatQ3;
    double dEstGyroBiasX;
    double dEstGyroBiasY;
    double dEstGyroBiasZ;
    double dEstRateOrcX;
    double dEstRateOrcY;
    double dEstRateOrcZ;
    double dEstRateIrcX;
    double dEstRateIrcY;
    double dEstRateIrcZ;
    float fEstGyrTorqueX;
    float fEstGyrTorqueY;
    float fEstGyrTorqueZ;
    double dEstInnovX;
    double dEstInnovY;
    double dEstInnovZ;
    double dEstStdDevRateX;
    double dEstStdDevRateY;
    double dEstStdDevRateZ;
    double dEstStdDevQ0;
    double dEstStdDevQ1;
    double dEstStdDevQ2;
    uint8_t u8EstModeActive;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t;

/*
    CubeADCS Gen2 TLM_174 - Models telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    int32_t i32SatPosEciX;
    int32_t i32SatPosEciY;
    int32_t i32SatPosEciZ;
    int16_t i16SatVelEciX;
    int16_t i16SatVelEciY;
    int16_t i16SatVelEciZ;
    double dSatLatGeod;
    double dSatLatGeoc;
    double dSatLon;
    double dSatAlt;
    int32_t i32TgtPosEciX;
    int32_t i32TgtPosEciY;
    int32_t i32TgtPosEciZ;
    double dModelMagOrcX;
    double dModelMagOrcY;
    double dModelMagOrcZ;
    double dModelSunOrcX;
    double dModelSunOrcY;
    double dModelSunOrcZ;
    double dModelSunBetaAngle;
    double dModelHorRhoAngle;
    double dModelHorXoEastAngle;
    double dModelHorYiEastAngle;
    int32_t i32Sat2TgtGndOrcX;
    int32_t i32Sat2TgtGndOrcY;
    int32_t i32Sat2TgtGndOrcZ;
    uint16_t u16Asgp4BatchCtr;
    uint16_t u16Asgp4PosDelta;
    uint8_t u8OrbModeActive;
    bool bAsgp4Error;
    bool bEclipse;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t;

/*
    CubeADCS Gen2 TLM_175 - Calibrated GNSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fGnssSatPosEcefX;
    float fGnssSatPosEcefY;
    float fGnssSatPosEcefZ;
    float fGnssSatVelEcefX;
    float fGnssSatVelEcefY;
    float fGnssSatVelEcefZ;
    uint32_t u32GnssTimeSeconds;
    uint32_t u32GnssTimeNs;
    bool bGnssIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t;

/*
    CubeADCS Gen2 TLM_176 - Calibrated HSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dHss0CalVecX;
    double dHss0CalVecY;
    double dHss0CalVecZ;
    double dHss1CalVecX;
    double dHss1CalVecY;
    double dHss1CalVecZ;
    bool bHss0IsValid;
    bool bHss1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t;

/*
    CubeADCS Gen2 TLM_177 - Calibrated MAG sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dMag0CalVecX;
    double dMag0CalVecY;
    double dMag0CalVecZ;
    double dMag1CalVecX;
    double dMag1CalVecY;
    double dMag1CalVecZ;
    bool bMag0IsValid;
    bool bMag1IsValid;
    bool bMag0IsBest;
    bool bMag1IsBest;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t;

/*
    CubeADCS Gen2 TLM_178 - Calibrated FSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dFss0CalVecX;
    double dFss0CalVecY;
    double dFss0CalVecZ;
    double dFss1CalVecX;
    double dFss1CalVecY;
    double dFss1CalVecZ;
    double dFss2CalVecX;
    double dFss2CalVecY;
    double dFss2CalVecZ;
    double dFss3CalVecX;
    double dFss3CalVecY;
    double dFss3CalVecZ;
    bool bFss0IsValid;
    bool bFss1IsValid;
    bool bFss2IsValid;
    bool bFss3IsValid;
    bool bFss0IsBest;
    bool bFss1IsBest;
    bool bFss2IsBest;
    bool bFss3IsBest;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t;

/*
    CubeADCS Gen2 TLM_179 - Raw CubeSense Earth telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dHss0RawElev;
    double dHss0RawRot;
    uint8_t u8Hss0CaptureResult;
    uint8_t u8Hss0DetectionResult;
    double dHss1RawElev;
    double dHss1RawRot;
    uint8_t u8Hss1CaptureResult;
    uint8_t u8Hss1DetectionResult;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t;

/*
    CubeADCS Gen2 TLM_180 - Raw MAG sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dMag0RawVecX;
    double dMag0RawVecY;
    double dMag0RawVecZ;
    double dMag1RawVecX;
    double dMag1RawVecY;
    double dMag1RawVecZ;
    bool bMag0IsValid;
    bool bMag1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t;

/*
    CubeADCS Gen2 TLM_203 - Raw CSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    uint8_t u8Css0Raw;
    uint8_t u8Css1Raw;
    uint8_t u8Css2Raw;
    uint8_t u8Css3Raw;
    uint8_t u8Css4Raw;
    uint8_t u8Css5Raw;
    uint8_t u8Css6Raw;
    uint8_t u8Css7Raw;
    uint8_t u8CsInt8Raw;
    uint8_t u8Css9Raw;
    bool bCssIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t;

/*
    CubeADCS Gen2 TLM_204 - Raw GYR sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fGyro0RawRateX;
    float fGyro0RawRateY;
    float fGyro0RawRateZ;
    float fGyro1RawRateX;
    float fGyro1RawRateY;
    float fGyro1RawRateZ;
    bool bGyro0IsValid;
    bool bGyro1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t;

/*
    CubeADCS Gen2 TLM_205 - Raw RWL sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fRwl0MeasSpeed;
    float fRwl1MeasSpeed;
    float fRwl2MeasSpeed;
    float fRwl3MeasSpeed;
    bool bRwl0IsValid;
    bool bRwl1IsValid;
    bool bRwl2IsValid;
    bool bRwl3IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t;

/*
    CubeADCS Gen2 TLM_206 - Calibrated CSS sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dCssCalVecX;
    double dCssCalVecY;
    double dCssCalVecZ;
    bool bCssIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t;

/*
    CubeADCS Gen2 TLM_207 - Calibrated GYR sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fGyro0CalRateX;
    float fGyro0CalRateY;
    float fGyro0CalRateZ;
    float fGyro1CalRateX;
    float fGyro1CalRateY;
    float fGyro1CalRateZ;
    bool bGyro0IsValid;
    bool bGyro1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t;

/*
    CubeADCS Gen2 TLM_208 - Calibrated STR sensor telemetry Part 1
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dStr0MeasBodyVec0X;
    double dStr0MeasBodyVec0Y;
    double dStr0MeasBodyVec0Z;
    double dStr0MeasBodyVec1X;
    double dStr0MeasBodyVec1Y;
    double dStr0MeasBodyVec1Z;
    double dStr0MeasBodyVec2X;
    double dStr0MeasBodyVec2Y;
    double dStr0MeasBodyVec2Z;
    double dStr0ModelOrbitVec0X;
    double dStr0ModelOrbitVec0Y;
    double dStr0ModelOrbitVec0Z;
    double dStr0ModelOrbitVec1X;
    double dStr0ModelOrbitVec1Y;
    double dStr0ModelOrbitVec1Z;
    double dStr0ModelOrbitVec2X;
    double dStr0ModelOrbitVec2Y;
    double dStr0ModelOrbitVec2Z;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t;

/*
    CubeADCS Gen2 TLM_208 - Calibrated STR sensor telemetry part 2
*/
typedef struct {
    double dStr1MeasBodyVec0X;
    double dStr1MeasBodyVec0Y;
    double dStr1MeasBodyVec0Z;
    double dStr1MeasBodyVec1X;
    double dStr1MeasBodyVec1Y;
    double dStr1MeasBodyVec1Z;
    double dStr1MeasBodyVec2X;
    double dStr1MeasBodyVec2Y;
    double dStr1MeasBodyVec2Z;
    double dStr1ModelOrbitVec0X;
    double dStr1ModelOrbitVec0Y;
    double dStr1ModelOrbitVec0Z;
    double dStr1ModelOrbitVec1X;
    double dStr1ModelOrbitVec1Y;
    double dStr1ModelOrbitVec1Z;
    double dStr1ModelOrbitVec2X;
    double dStr1ModelOrbitVec2Y;
    double dStr1ModelOrbitVec2Z;
    bool bStr0IsValid;
    bool bStr1IsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t;

/*
    CubeADCS Gen2 TLM_209 - Calibrated RWL sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fRwlTorqueVecX;
    float fRwlTorqueVecY;
    float fRwlTorqueVecZ;
    float fRwlMomVecX;
    float fRwlMomVecY;
    float fRwlMomVecZ;
    bool bRwlIsValid;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t;

/*
    CubeADCS Gen2 TLM_210 - Main estimator telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    double dEstRpyRoll;
    double dEstRpyPitch;
    double dEstRpyYaw;
    double dEstQuatQ0;
    double dEstQuatQ1;
    double dEstQuatQ2;
    double dEstQuatQ3;
    double dEstGyroBiasX;
    double dEstGyroBiasY;
    double dEstGyroBiasZ;
    double dEstRateOrcX;
    double dEstRateOrcY;
    double dEstRateOrcZ;
    double dEstRateIrcX;
    double dEstRateIrcY;
    double dEstRateIrcZ;
    float fEstGyrTorqueX;
    float fEstGyrTorqueY;
    float fEstGyrTorqueZ;
    double dEstInnovX;
    double dEstInnovY;
    double dEstInnovZ;
    double dEstStdDevRateX;
    double dEstStdDevRateY;
    double dEstStdDevRateZ;
    double dEstStdDevQ0;
    double dEstStdDevQ1;
    double dEstStdDevQ2;
    uint8_t u8EstModeActive;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t;

/*
    CubeADCS Gen2 TLM_211 - Main estimator high-resolution telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    float fEstQuatQ0;
    float fEstQuatQ1;
    float fEstQuatQ2;
    float fEstQuatQ3;
    float fEstRateOrcX;
    float fEstRateOrcY;
    float fEstRateOrcZ;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t;

/*
    CubeADCS Gen2 TLM_212 - Raw GNSS sensor telemetry
*/
typedef struct {
    uint32_t u32RtcTimeSeconds;
    uint32_t u32RtcTimeNs;
    int32_t i32RtcDriftNs;
    float fGnssSatPosEcefX;
    float fGnssSatPosEcefY;
    float fGnssSatPosEcefZ;
    float fGnssSatVelEcefX;
    float fGnssSatVelEcefY;
    float fGnssSatVelEcefZ;
    uint32_t u32GnssTimeSeconds;
    uint32_t u32GnssTimeNs;
    uint16_t u16GpsWeek;
    uint32_t u32Tow;
    int8_t i8UtcOffset;
    bool bGnssValidData;
    bool bGnssLock;
    bool bGnssPPSDetected;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t;

/*
    CubeADCS Gen2 TLM_213 - Raw PST3S star tracker telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    uint8_t u8StrInstance;
    uint8_t u8Pst3sVersion;
    float fQuat1;
    float fQuat2;
    float fQuat3;
    float fQuat4;
    float fAngVelX;
    float fAngVelY;
    float fAngVelZ;
    uint8_t u8RateQuality;
    uint32_t u32UnixSeconds;
    float fUnixSecondsDecimal;
    int8_t i8Temperature;
    uint8_t u8ImageExposure;
    uint8_t u8ImageThreshold;
    uint8_t u8BackGroundValues;
    uint8_t u8InternalProcessCode;
    uint8_t u8CmosChipIdResult;
    uint8_t u8FpgaMRamResult;
    uint8_t u8NumberOfExtractedStars;
    uint8_t u8OperatingMode;
    uint8_t u8ImagingGain;
    uint8_t u8MinNavigationStars;
    uint8_t u8DataValid;
    uint8_t u8ExtImageState;
    uint8_t u8IdentifiedStars;
    uint8_t u8DeviceNumber;
    uint8_t u8SoftwareVersion;
    uint8_t u8EdacErrorCount;
    uint32_t u32ImageFrameNumber;
    uint8_t u8DynamicMode;
    uint8_t u8SaaMode;
    uint8_t u8SaaThreshold;
    uint8_t u8QuaternionFilteringState;
    uint8_t u8FourStarCaptureThreshold;
    uint8_t u8TrackingThreshold;
    bool bEdacSwitch;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t;

/*
    CubeADCS Gen2 TLM_214 - ACP execution telemetry
*/
typedef struct {
    uint16_t u16TimeSinceLoopStart;
    uint8_t u8CurrentExecutionPoint;
    uint16_t u16ExecTimeNodeSync;
    uint16_t u16ExecTimeSensorComms;
    uint16_t u16ExecTimeSensorCal;
    uint16_t u16ExecTimeEstimators;
    uint16_t u16ExecTimeControllers;
    uint16_t u16ExecTimeWheelComms;
    uint16_t u16ExecTimeModels;
    uint16_t u16ExecTimeLoopSync;
    uint16_t u16ExecTimeHealth;
    uint16_t u16ExecTimeTlmLog;
    int16_t i16LoopRtcOffset;
    bool bLoopHasStarted;
    bool bHilSyncOk;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t;

/*
    CubeADCS Gen2 TLM_216 - CubeComputer Health
*/
typedef struct {
    double dMcuTemp;
    double dMcuCurrent;
    uint16_t u16McuVoltage;
    uint16_t u16SupplyVoltage;
    uint16_t u16V5Sense;
    double dSram1Current;
    double dSram2Current;
    double dAdcCurrent;
    double dFlashCurrent;
    double dRs485Current;
    double dCanCurrent;
    double dGyroCurrent;
    double dRedGyroCurrent;
    bool bGyroOverVoltage;
    bool bGyroUnderVoltage;
    bool bRedGyroOverVoltage;
    bool bRedGyroUnderVoltage;
    uint8_t au8WatchdogCount[5];
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t;

/*
    CubeADCS Gen2 TLM_217 - Health telemetry for CubeSense Earth
*/
typedef struct {
    double dHss0McuTemp;
    double dHss0McuCurrent;
    uint16_t u16Hss0McuVoltage;
    double dHss0DetectorTemp;
    double dHss0DetectorCurrent;
    double dHss1McuTemp;
    double dHss1McuCurrent;
    uint16_t u16Hss1McuVoltage;
    double dHss1DetectorTemp;
    double dHss1DetectorCurrent;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t;

/*
    CubeADCS Gen2 TLM_218 - Health telemetry for Reaction Wheels
*/
typedef struct {
    double dRwl0McuTemp;
    double dRwl0McuCurrent;
    uint16_t u16Rwl0BatVoltage;
    double dRwl0BatCurrent;
    double dRwl1McuTemp;
    double dRwl1McuCurrent;
    uint16_t u16Rwl1BatVoltage;
    double dRwl1BatCurrent;
    double dRwl2McuTemp;
    double dRwl2McuCurrent;
    uint16_t u16Rwl2BatVoltage;
    double dRwl2BatCurrent;
    double dRwl3McuTemp;
    double dRwl3McuCurrent;
    uint16_t u16Rwl3BatVoltage;
    double dRwl3BatCurrent;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t;

/*
    CubeADCS Gen2 TLM_225 - Health telemetry for CubeNode NSSRWL
*/
typedef struct {
    double dRwl0McuTemp;
    double dRwl0McuCurrent;
    uint16_t u16Rwl0McuVoltage;
    double dRwl0Current5v;
    bool bRwl0Overcurrent5v;
    double dRwl1McuTemp;
    double dRwl1McuCurrent;
    uint16_t u16Rwl1McuVoltage;
    double dRwl1Current5v;
    bool bRwl1Overcurrent5v;
    double dRwl2McuTemp;
    double dRwl2McuCurrent;
    uint16_t u16Rwl2McuVoltage;
    double dRwl2Current5v;
    bool bRwl2Overcurrent5v;
    double dRwl3McuTemp;
    double dRwl3McuCurrent;
    uint16_t u16Rwl3McuVoltage;
    double dRwl3Current5v;
    bool bRwl3Overcurrent5v;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t;

/*
    CubeADCS Gen2 TLM_226 - Raw NSSRWL sensor telemetry
*/
typedef struct {
    uint32_t u32TimeSeconds;
    uint32_t u32TimeNs;
    int16_t i16Rwl0TargetValue;
    float fRwl0MeasSpeed;
    int16_t i16Rwl0MeasCurrent;
    int16_t i16Rwl0Temp;
    int16_t i16Rwl1TargetValue;
    float fRwl1MeasSpeed;
    int16_t i16Rwl1MeasCurrent;
    int16_t i16Rwl1Temp;
    int16_t i16Rwl2TargetValue;
    float fRwl2MeasSpeed;
    int16_t i16Rwl2MeasCurrent;
    int16_t i16Rwl2Temp;
    int16_t i16Rwl3TargetValue;
    float fRwl3MeasSpeed;
    int16_t i16Rwl3MeasCurrent;
    int16_t i16Rwl3Temp;
    bool bRwl0IsValid;
    bool bRwl0WheelMode;
    bool bRwl0CurentCtrlMode;
    bool bRwl0SpeedCtrlMode;
    bool bRwl0TorqueCtrlMode;
    bool bRwl0CrcError;
    bool bRwl0WrongLlCmd;
    bool bRwl0WrongHlCmd;
    bool bRwl0ToutSci1Main;
    bool bRwl1IsValid;
    bool bRwl1WheelMode;
    bool bRwl1CurentCtrlMode;
    bool bRwl1SpeedCtrlMode;
    bool bRwl1TorqueCtrlMode;
    bool bRwl1CrcError;
    bool bRwl1WrongLlCmd;
    bool bRwl1WrongHlCmd;
    bool bRwl1ToutSci1Main;
    bool bRwl2IsValid;
    bool bRwl2WheelMode;
    bool bRwl2CurentCtrlMode;
    bool bRwl2SpeedCtrlMode;
    bool bRwl2TorqueCtrlMode;
    bool bRwl2CrcError;
    bool bRwl2WrongLlCmd;
    bool bRwl2WrongHlCmd;
    bool bRwl2ToutSci1Main;
    bool bRwl3IsValid;
    bool bRwl3WheelMode;
    bool bRwl3CurentCtrlMode;
    bool bRwl3SpeedCtrlMode;
    bool bRwl3TorqueCtrlMode;
    bool bRwl3CrcError;
    bool bRwl3WrongLlCmd;
    bool bRwl3WrongHlCmd;
    bool bRwl3ToutSci1Main;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t;

/*
    CubeADCS Gen2 TLM_165 - Health telemetry for CubeStar
*/
typedef struct {
    double dStr0McuTemp;
    double dStr0McuCurrent;
    uint16_t u16Str0McuVoltage;
    double dStr0Current;
    bool bStr0Overcurrent;
    uint32_t u32Str0ErrorCode;
    double dStr1McuTemp;
    double dStr1McuCurrent;
    uint16_t u16Str1McuVoltage;
    double dStr1Current;
    bool bStr1Overcurrent;
    uint32_t u32Str1ErrorCode;
} PACKED_STRUCT DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t;

typedef struct {
    uint8_t u8Sync;
    uint8_t au8Message[25];
    uint8_t au8Port[8];
    int32_t i32Sequence;
    float fIdle_time;
    uint32_t u32Time_status;
    uint32_t u32Week;
    float fSeconds;
    uint32_t u32Receiver_status;
    uint32_t u32Reserved;
    uint32_t u32Receiver_sw_version;
    uint8_t u8End1;
    uint32_t u32Clock_status;
    double dOffset;
    double dOffset_std;
    double dUtc_offset;
    uint32_t u32Utc_year;
    uint8_t u8Utc_month;
    uint8_t u8Utc_day;
    uint8_t u8Utc_hour;
    uint8_t u8Utc_min;
    uint32_t u32Utc_ms;
    uint32_t u32Utc_status;
    uint32_t u32Crc32;
    uint8_t au8End2[2];
} PACKED_STRUCT DATA_CACHE_GNSS_TIME_t;

typedef struct {
    uint8_t u8Sync;
    uint8_t au8Message[25];
    uint8_t au8Port[8];
    int32_t i32Sequence;
    float fIdle_time;
    uint32_t u32Time_status;
    uint32_t u32Week;
    float fSeconds;
    uint32_t u32Receiver_status;
    uint32_t u32Reserved1;
    uint32_t u32Receiver_sw_version;
    uint8_t u8End1;
    uint32_t u32P_sol_status;
    uint32_t u32Pos_type;
    double dPx;
    double dPy;
    double dPz;
    float fPxo;
    float fPyo;
    float fPzo;
    uint32_t u32V_sol_status;
    uint32_t u32Vel_type;
    double dVx;
    double dVy;
    double dVz;
    float fVxo;
    float fVyo;
    float fVzo;
    uint8_t au8Stn_id[4];
    float fV_latency;
    float fDiff_age;
    float fSol_age;
    uint8_t u8Svs;
    uint8_t u8Solnsvs;
    uint8_t u8Ggl1;
    uint8_t u8Solnmultisvs;
    uint8_t u8Reserved2;
    uint8_t u8Ext_sol_stat;
    uint8_t u8Galileo_and_beidou_sig_mask;
    uint8_t u8Gps_and_glonass_sig_mask;
    uint32_t u32Crc32;
    uint8_t au8End2[2];
} PACKED_STRUCT DATA_CACHE_GNSS_BESTXYZ_t;

/*
    GetBatteryInfo from EPSII_BP_1 interface
*/
typedef struct {
    uint32_t u32Capacity;
    uint16_t u16Voltage;
} PACKED_STRUCT DATA_CACHE_EpsOverallBatteryInfoType_t;

/*
    GetBatteryInfo from EPSII_BP_1 interface
*/
typedef struct {
    uint32_t u32Capacity;
    uint16_t u16Voltage;
    int16_t i16Current;
    int32_t i32Temperature;
    uint8_t u8Bp_mode;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BatteryInfoType_t;

/*
    GetDeviceHealthInfo from EPSII_BP_1 interface
*/
typedef struct {
    int32_t i32ActiveCPU_RunningTime;
    int32_t i32ActiveCPU_Voltage;
    int32_t i32ActiveCPU_Temperature;
    int32_t i32PCB_Temperature_1;
    int32_t i32PCB_Temperature_2;
    uint8_t u8BALANCER_CHIP_1;
    uint8_t u8LT8491_IC_XP;
    uint8_t u8LT8491_IC_XR;
    uint8_t u8LT8491_IC_YP;
    uint8_t u8LT8491_IC_YR;
    uint8_t u8LT8491_IC_ZP;
    uint8_t u8LT8491_IC_ZR;
    uint8_t u8INA_BAT_OUT_1;
    uint8_t u8INA_BAT_OUT_2;
    uint8_t u8TMP117_U810;
    uint8_t u8TMP117_U811;
    uint8_t u8GPIO_PCA9538_U2001;
    uint8_t u8GPIO_PCA9538_U2002;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t;

/*
    Information provided by INA sensor 1
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0InaSensors1Type_t;

/*
    Information provided by INA sensor 2
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0InaSensors2Type_t;

/*
    Telemetry provided by the Balancer
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Internal_Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BalancerInfoType_t;

/*
    Status provided by the Balancer
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint8_t u8Status_register_0;
    uint8_t u8Status_register_1;
    uint8_t u8Status_register_2;
    uint8_t u8Status_register_3;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BalancerStatusType_t;

/*
    Balancer Cells info
*/
typedef struct {
    uint16_t u16Cell_1;
    uint16_t u16Cell_2;
    uint16_t u16Cell_3;
    uint16_t u16Cell_4;
    uint16_t u16Cell_5;
    uint16_t u16Cell_6;
    uint16_t u16Cell_7;
    uint16_t u16Cell_8;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerXpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerXrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerYpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerYrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerZpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst0ChargerZrType_t;

/*
    GetBatteryInfo from EPSII_BP_1 interface
*/
typedef struct {
    uint32_t u32Capacity;
    uint16_t u16Voltage;
    int16_t i16Current;
    int32_t i32Temperature;
    uint8_t u8Bp_mode;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1BatteryInfoType_t;

/*
    GetDeviceHealthInfo from EPSII_BP_1 interface
*/
typedef struct {
    int32_t i32ActiveCPU_RunningTime;
    int32_t i32ActiveCPU_Voltage;
    int32_t i32ActiveCPU_Temperature;
    int32_t i32PCB_Temperature_1;
    int32_t i32PCB_Temperature_2;
    uint8_t u8BALANCER_CHIP_1;
    uint8_t u8LT8491_IC_XP;
    uint8_t u8LT8491_IC_XR;
    uint8_t u8LT8491_IC_YP;
    uint8_t u8LT8491_IC_YR;
    uint8_t u8LT8491_IC_ZP;
    uint8_t u8LT8491_IC_ZR;
    uint8_t u8INA_BAT_OUT_1;
    uint8_t u8INA_BAT_OUT_2;
    uint8_t u8TMP117_U810;
    uint8_t u8TMP117_U811;
    uint8_t u8GPIO_PCA9538_U2001;
    uint8_t u8GPIO_PCA9538_U2002;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t;

/*
    Information provided by INA sensor 1
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1InaSensors1Type_t;

/*
    Information provided by INA sensor 2
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1InaSensors2Type_t;

/*
    Telemetry provided by the Balancer
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Internal_Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1BalancerInfoType_t;

/*
    Status provided by the Balancer
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint8_t u8Status_register_0;
    uint8_t u8Status_register_1;
    uint8_t u8Status_register_2;
    uint8_t u8Status_register_3;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1BalancerStatusType_t;

/*
    Balancer Cells info
*/
typedef struct {
    uint16_t u16Cell_1;
    uint16_t u16Cell_2;
    uint16_t u16Cell_3;
    uint16_t u16Cell_4;
    uint16_t u16Cell_5;
    uint16_t u16Cell_6;
    uint16_t u16Cell_7;
    uint16_t u16Cell_8;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1ChargerXpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1ChargerXrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1ChargerYpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1ChargerYrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1ChargerZpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst1ChargerZrType_t;

/*
    GetBatteryInfo from EPSII_BP_1 interface
*/
typedef struct {
    uint32_t u32Capacity;
    uint16_t u16Voltage;
    int16_t i16Current;
    int32_t i32Temperature;
    uint8_t u8Bp_mode;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2BatteryInfoType_t;

/*
    GetDeviceHealthInfo from EPSII_BP_1 interface
*/
typedef struct {
    int32_t i32ActiveCPU_RunningTime;
    int32_t i32ActiveCPU_Voltage;
    int32_t i32ActiveCPU_Temperature;
    int32_t i32PCB_Temperature_1;
    int32_t i32PCB_Temperature_2;
    uint8_t u8BALANCER_CHIP_1;
    uint8_t u8LT8491_IC_XP;
    uint8_t u8LT8491_IC_XR;
    uint8_t u8LT8491_IC_YP;
    uint8_t u8LT8491_IC_YR;
    uint8_t u8LT8491_IC_ZP;
    uint8_t u8LT8491_IC_ZR;
    uint8_t u8INA_BAT_OUT_1;
    uint8_t u8INA_BAT_OUT_2;
    uint8_t u8TMP117_U810;
    uint8_t u8TMP117_U811;
    uint8_t u8GPIO_PCA9538_U2001;
    uint8_t u8GPIO_PCA9538_U2002;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t;

/*
    Information provided by INA sensor 1
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2InaSensors1Type_t;

/*
    Information provided by INA sensor 2
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Energy;
    int16_t i16Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2InaSensors2Type_t;

/*
    Telemetry provided by the Balancer
*/
typedef struct {
    uint16_t u16Voltage;
    int16_t i16Current;
    int16_t i16Internal_Temperature;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2BalancerInfoType_t;

/*
    Status provided by the Balancer
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint8_t u8Status_register_0;
    uint8_t u8Status_register_1;
    uint8_t u8Status_register_2;
    uint8_t u8Status_register_3;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2BalancerStatusType_t;

/*
    Balancer Cells info
*/
typedef struct {
    uint16_t u16Cell_1;
    uint16_t u16Cell_2;
    uint16_t u16Cell_3;
    uint16_t u16Cell_4;
    uint16_t u16Cell_5;
    uint16_t u16Cell_6;
    uint16_t u16Cell_7;
    uint16_t u16Cell_8;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2ChargerXpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2ChargerXrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2ChargerYpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2ChargerYrType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2ChargerZpType_t;

/*
    Charger info
*/
typedef struct {
    uint8_t u8COM_STATE;
    uint16_t u16STAT_SUPPLY;
    uint16_t u16TELE_POUT;
    uint16_t u16TELE_PIN;
    uint16_t u16TELE_IOUT;
    uint16_t u16TELE_IIN;
    uint16_t u16TELE_VBAT;
    uint16_t u16TELE_VINR;
} PACKED_STRUCT DATA_CACHE_Eps2Inst2ChargerZrType_t;


// Enum type to access the datacache structure with the index
typedef enum
{
    DC_DID_OBC_0_DATA,
    DC_DID_ADCS_0_DATA,
    DC_DID_ADCS_1_DATA,
    DC_DID_ADCS_2_DATA,
    DC_DID_EPS_0_DATA,
    DC_DID_SSP_0_DATA,
    DC_DID_SSP_1_DATA,
    DC_DID_SSP_2_DATA,
    DC_DID_AOCS_CNTRL_TLM_DATA,
    DC_DID_OS_TASK_DATA,
    DC_DID_SSP_3_DATA,
    DC_DID_SENSOR_MAG_PRIMARY_DATA,
    DC_DID_SENSOR_MAG_SECONDARY_DATA,
    DC_DID_SENSOR_GYRO_DATA,
    DC_DID_SENSOR_COARSE_SUN_DATA,
    DC_DID_ES_ADCS_SENSOR_MAG_PRIMARY_DATA,
    DC_DID_ES_ADCS_SENSOR_MAG_SECONDARY_DATA,
    DC_DID_ES_ADCS_SENSOR_GYRO_DATA,
    DC_DID_ES_ADCS_SENSOR_CSS_DATA,
    DC_DID_ES_ADCS_ESTIMATES_BDOT_DATA,
    DC_DID_ES_ADCS_CONTROL_VALUES_MTQ_DATA,
    DC_DID_CONOPSFLAGS_DATA,
    DC_DID_AOCS_CNTRL_SYS_STATE_DATA,
    DC_DID_ADCS_3_DATA,
    DC_DID_ADCS_4_DATA,
    DC_DID_EPS_9_DATA,
    DC_DID_EPS_10_DATA,
    DC_DID_EPS_14_DATA,
    DC_DID_SENSOR_ACC_PRIMARY_DATA,
    DC_DID_SENSOR_ACC_SECONDARY_DATA,
    DC_DID_SENSOR_ACC_PRIMARY_SAT_FRAME_DATA,
    DC_DID_SENSOR_ACC_SECONDARY_SAT_FRAME_DATA,
    DC_DID_SENSOR_PANEL_TEMP_DATA,
    DC_DID_SENSOR_PANEL_TEMP_SAT_FRAME_DATA,
    DC_DID_SENSOR_GYRO_TEMP_DATA,
    DC_DID_SENSOR_GYRO_TEMP_SAT_FRAME_DATA,
    DC_DID_CUBEADCS_GEN2_OP_STATUS_COMMON_DATA,
    DC_DID_CUBEADCS_GEN2_OP_STATUS_APP_DATA,
    DC_DID_AOCS_CNTRL_REF_PARAMS_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_166_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_167_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_168_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_169_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_170_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_171_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_172_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_173_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_174_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_175_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_176_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_177_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_178_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_179_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_180_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_203_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_204_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_205_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_206_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_207_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_1_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_208_2_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_209_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_210_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_211_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_212_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_213_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_214_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_216_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_217_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_218_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_225_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_226_DATA,
    DC_DID_CUBEADCS_GEN2_TLM_FRAME_165_DATA,
    DC_DID_GNSS_TIME_DATA,
    DC_DID_GNSS_BESTXYZ_DATA,
    DC_DID_EPSOVERALLBATTERYINFO_DATA,
    DC_DID_EPS2_BP_INST0_BP_INFO_DATA,
    DC_DID_EPS2_BP_INST0_DEVICE_HEALTH_INFO_DATA,
    DC_DID_EPS2_BP_INST0_INA_SENSOR1_DATA,
    DC_DID_EPS2_BP_INST0_INA_SENSOR2_DATA,
    DC_DID_EPS2_BP_INST0_BALANCER_INFO_DATA,
    DC_DID_EPS2_BP_INST0_BALANCER_STATUS_DATA,
    DC_DID_EPS2_BP_INST0_BALANCER_CELLS_INFO_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_XP_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_XR_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_YP_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_YR_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_ZP_DATA,
    DC_DID_EPS2_BP_INST0_CHARGER_ZR_DATA,
    DC_DID_EPS2_BP_INST1_BP_INFO_DATA,
    DC_DID_EPS2_BP_INST1_DEVICE_HEALTH_INFO_DATA,
    DC_DID_EPS2_BP_INST1_INA_SENSOR1_DATA,
    DC_DID_EPS2_BP_INST1_INA_SENSOR2_DATA,
    DC_DID_EPS2_BP_INST1_BALANCER_INFO_DATA,
    DC_DID_EPS2_BP_INST1_BALANCER_STATUS_DATA,
    DC_DID_EPS2_BP_INST1_BALANCER_CELLS_INFO_DATA,
    DC_DID_EPS2_BP_INST1_CHARGER_XP_DATA,
    DC_DID_EPS2_BP_INST1_CHARGER_XR_DATA,
    DC_DID_EPS2_BP_INST1_CHARGER_YP_DATA,
    DC_DID_EPS2_BP_INST1_CHARGER_YR_DATA,
    DC_DID_EPS2_BP_INST1_CHARGER_ZP_DATA,
    DC_DID_EPS2_BP_INST1_CHARGER_ZR_DATA,
    DC_DID_EPS2_BP_INST2_BP_INFO_DATA,
    DC_DID_EPS2_BP_INST2_DEVICE_HEALTH_INFO_DATA,
    DC_DID_EPS2_BP_INST2_INA_SENSOR1_DATA,
    DC_DID_EPS2_BP_INST2_INA_SENSOR2_DATA,
    DC_DID_EPS2_BP_INST2_BALANCER_INFO_DATA,
    DC_DID_EPS2_BP_INST2_BALANCER_STATUS_DATA,
    DC_DID_EPS2_BP_INST2_BALANCER_CELLS_INFO_DATA,
    DC_DID_EPS2_BP_INST2_CHARGER_XP_DATA,
    DC_DID_EPS2_BP_INST2_CHARGER_XR_DATA,
    DC_DID_EPS2_BP_INST2_CHARGER_YP_DATA,
    DC_DID_EPS2_BP_INST2_CHARGER_YR_DATA,
    DC_DID_EPS2_BP_INST2_CHARGER_ZP_DATA,
    DC_DID_EPS2_BP_INST2_CHARGER_ZR_DATA,
    DC_DID_MAX
} dc_did_id;


/**********************************************************************
 *
 *  DataCache function prototypes
 *
 **********************************************************************/

/*!
* @brief Init routine for the DataCache component
*/
void dc_init(void);
/*!
* @brief Main Data Cache task function
* @warning Should not be called too often because it locks the data in order to modify it and
*          could interfere with the set/get operations called by DC clients.
*/
void dc_task(void);

dc_data_status_t dc_get_obc_0_data(DATA_CACHE_OBC_0_t * const p_data);
void dc_set_obc_0_data(DATA_CACHE_OBC_0_t * const p_new_data);

dc_data_status_t dc_get_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_data);
void dc_set_adcs_0_data(DATA_CACHE_ADCS_0_t * const p_new_data);

dc_data_status_t dc_get_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_data);
void dc_set_adcs_1_data(DATA_CACHE_ADCS_1_t * const p_new_data);

dc_data_status_t dc_get_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_data);
void dc_set_adcs_2_data(DATA_CACHE_ADCS_2_t * const p_new_data);

dc_data_status_t dc_get_eps_0_data(DATA_CACHE_EPS_0_t * const p_data);
void dc_set_eps_0_data(DATA_CACHE_EPS_0_t * const p_new_data);

dc_data_status_t dc_get_ssp_0_data(DATA_CACHE_SSP_0_t * const p_data);
void dc_set_ssp_0_data(DATA_CACHE_SSP_0_t * const p_new_data);

dc_data_status_t dc_get_ssp_1_data(DATA_CACHE_SSP_1_t * const p_data);
void dc_set_ssp_1_data(DATA_CACHE_SSP_1_t * const p_new_data);

dc_data_status_t dc_get_ssp_2_data(DATA_CACHE_SSP_2_t * const p_data);
void dc_set_ssp_2_data(DATA_CACHE_SSP_2_t * const p_new_data);

dc_data_status_t dc_get_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_data);
void dc_set_aocs_cntrl_tlm_data(DATA_CACHE_AOCS_CNTRL_TLM_t * const p_new_data);

dc_data_status_t dc_get_os_task_data(DATA_CACHE_TaskStats_t * const p_data);
void dc_set_os_task_data(DATA_CACHE_TaskStats_t * const p_new_data);

dc_data_status_t dc_get_ssp_3_data(DATA_CACHE_SSP_3_t * const p_data);
void dc_set_ssp_3_data(DATA_CACHE_SSP_3_t * const p_new_data);

dc_data_status_t dc_get_sensor_mag_primary_data(DATA_CACHE_SENSOR_MAG_PRIMARY_t * const p_data);
void dc_set_sensor_mag_primary_data(DATA_CACHE_SENSOR_MAG_PRIMARY_t * const p_new_data);

dc_data_status_t dc_get_sensor_mag_secondary_data(DATA_CACHE_SENSOR_MAG_SECONDARY_t * const p_data);
void dc_set_sensor_mag_secondary_data(DATA_CACHE_SENSOR_MAG_SECONDARY_t * const p_new_data);

dc_data_status_t dc_get_sensor_gyro_data(DATA_CACHE_SENSOR_GYRO_t * const p_data);
void dc_set_sensor_gyro_data(DATA_CACHE_SENSOR_GYRO_t * const p_new_data);

dc_data_status_t dc_get_sensor_coarse_sun_data(DATA_CACHE_SENSOR_COARSE_SUN_t * const p_data);
void dc_set_sensor_coarse_sun_data(DATA_CACHE_SENSOR_COARSE_SUN_t * const p_new_data);

dc_data_status_t dc_get_es_adcs_sensor_mag_primary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t * const p_data);
void dc_set_es_adcs_sensor_mag_primary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_PRIMARY_t * const p_new_data);

dc_data_status_t dc_get_es_adcs_sensor_mag_secondary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t * const p_data);
void dc_set_es_adcs_sensor_mag_secondary_data(DATA_CACHE_ES_ADCS_SENSOR_MAG_SECONDARY_t * const p_new_data);

dc_data_status_t dc_get_es_adcs_sensor_gyro_data(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t * const p_data);
void dc_set_es_adcs_sensor_gyro_data(DATA_CACHE_ES_ADCS_SENSOR_GYRO_t * const p_new_data);

dc_data_status_t dc_get_es_adcs_sensor_css_data(DATA_CACHE_ES_ADCS_SENSOR_CSS_t * const p_data);
void dc_set_es_adcs_sensor_css_data(DATA_CACHE_ES_ADCS_SENSOR_CSS_t * const p_new_data);

dc_data_status_t dc_get_es_adcs_estimates_bdot_data(DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t * const p_data);
void dc_set_es_adcs_estimates_bdot_data(DATA_CACHE_ES_ADCS_ESTIMATES_BDOT_t * const p_new_data);

dc_data_status_t dc_get_es_adcs_control_values_mtq_data(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t * const p_data);
void dc_set_es_adcs_control_values_mtq_data(DATA_CACHE_ES_ADCS_CONTROL_VALUES_MTQ_t * const p_new_data);

dc_data_status_t dc_get_conopsflags_data(DATA_CACHE_ConOpsFlags_t * const p_data);
void dc_set_conopsflags_data(DATA_CACHE_ConOpsFlags_t * const p_new_data);

dc_data_status_t dc_get_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_data);
void dc_set_aocs_cntrl_sys_state_data(DATA_CACHE_AOCS_CNTRL_SYS_STATE_t * const p_new_data);

dc_data_status_t dc_get_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_data);
void dc_set_adcs_3_data(DATA_CACHE_ADCS_3_t * const p_new_data);

dc_data_status_t dc_get_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_data);
void dc_set_adcs_4_data(DATA_CACHE_ADCS_4_t * const p_new_data);

dc_data_status_t dc_get_eps_9_data(DATA_CACHE_EPS_9_t * const p_data);
void dc_set_eps_9_data(DATA_CACHE_EPS_9_t * const p_new_data);

dc_data_status_t dc_get_eps_10_data(DATA_CACHE_EPS_10_t * const p_data);
void dc_set_eps_10_data(DATA_CACHE_EPS_10_t * const p_new_data);

dc_data_status_t dc_get_eps_14_data(DATA_CACHE_EPS_14_t * const p_data);
void dc_set_eps_14_data(DATA_CACHE_EPS_14_t * const p_new_data);

dc_data_status_t dc_get_sensor_acc_primary_data(DATA_CACHE_SENSOR_ACC_PRIMARY_t * const p_data);
void dc_set_sensor_acc_primary_data(DATA_CACHE_SENSOR_ACC_PRIMARY_t * const p_new_data);

dc_data_status_t dc_get_sensor_acc_secondary_data(DATA_CACHE_SENSOR_ACC_SECONDARY_t * const p_data);
void dc_set_sensor_acc_secondary_data(DATA_CACHE_SENSOR_ACC_SECONDARY_t * const p_new_data);

dc_data_status_t dc_get_sensor_acc_primary_sat_frame_data(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t * const p_data);
void dc_set_sensor_acc_primary_sat_frame_data(DATA_CACHE_SENSOR_ACC_PRIMARY_SAT_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_acc_secondary_sat_frame_data(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t * const p_data);
void dc_set_sensor_acc_secondary_sat_frame_data(DATA_CACHE_SENSOR_ACC_SECONDARY_SAT_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_panel_temp_data(DATA_CACHE_SENSOR_PANEL_TEMP_t * const p_data);
void dc_set_sensor_panel_temp_data(DATA_CACHE_SENSOR_PANEL_TEMP_t * const p_new_data);

dc_data_status_t dc_get_sensor_panel_temp_sat_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t * const p_data);
void dc_set_sensor_panel_temp_sat_frame_data(DATA_CACHE_SENSOR_PANEL_TEMP_SAT_FRAME_t * const p_new_data);

dc_data_status_t dc_get_sensor_gyro_temp_data(DATA_CACHE_SENSOR_GYRO_TEMP_t * const p_data);
void dc_set_sensor_gyro_temp_data(DATA_CACHE_SENSOR_GYRO_TEMP_t * const p_new_data);

dc_data_status_t dc_get_sensor_gyro_temp_sat_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t * const p_data);
void dc_set_sensor_gyro_temp_sat_frame_data(DATA_CACHE_SENSOR_GYRO_TEMP_SAT_FRAME_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_data);
void dc_set_cubeadcs_gen2_op_status_common_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_COMMON_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_data);
void dc_set_cubeadcs_gen2_op_status_app_data(DATA_CACHE_CUBEADCS_GEN2_OP_STATUS_APP_t * const p_new_data);

dc_data_status_t dc_get_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_data);
void dc_set_aocs_cntrl_ref_params_data(DATA_CACHE_AOCS_CNTRL_REF_PARAMS_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_166_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_166_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_167_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_167_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_168_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_168_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_169_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_169_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_170_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_170_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_171_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_171_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_172_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_172_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_173_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_173_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_174_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_174_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_175_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_175_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_176_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_176_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_177_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_177_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_178_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_178_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_179_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_179_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_180_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_180_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_203_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_203_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_204_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_204_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_205_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_205_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_206_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_206_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_207_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_207_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_208_1_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_1_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_208_2_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_208_2_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_209_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_209_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_210_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_210_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_211_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_211_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_212_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_212_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_213_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_213_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_214_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_214_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_216_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_216_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_217_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_217_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_218_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_218_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_225_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_225_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_226_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_226_t * const p_new_data);

dc_data_status_t dc_get_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_data);
void dc_set_cubeadcs_gen2_tlm_frame_165_data(DATA_CACHE_CUBEADCS_GEN2_TLM_FRAME_165_t * const p_new_data);

dc_data_status_t dc_get_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_data);
void dc_set_gnss_time_data(DATA_CACHE_GNSS_TIME_t * const p_new_data);

dc_data_status_t dc_get_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_data);
void dc_set_gnss_bestxyz_data(DATA_CACHE_GNSS_BESTXYZ_t * const p_new_data);

dc_data_status_t dc_get_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_data);
void dc_set_epsoverallbatteryinfo_data(DATA_CACHE_EpsOverallBatteryInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_bp_info_data(DATA_CACHE_Eps2Inst0BatteryInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_device_health_info_data(DATA_CACHE_Eps2Inst0DeviceHealthInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_data);
void dc_set_eps2_bp_inst0_ina_sensor1_data(DATA_CACHE_Eps2Inst0InaSensors1Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_data);
void dc_set_eps2_bp_inst0_ina_sensor2_data(DATA_CACHE_Eps2Inst0InaSensors2Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_balancer_info_data(DATA_CACHE_Eps2Inst0BalancerInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_data);
void dc_set_eps2_bp_inst0_balancer_status_data(DATA_CACHE_Eps2Inst0BalancerStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_data);
void dc_set_eps2_bp_inst0_balancer_cells_info_data(DATA_CACHE_Eps2Inst0BalancerCellsInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_xp_data(DATA_CACHE_Eps2Inst0ChargerXpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_xr_data(DATA_CACHE_Eps2Inst0ChargerXrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_yp_data(DATA_CACHE_Eps2Inst0ChargerYpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_yr_data(DATA_CACHE_Eps2Inst0ChargerYrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_zp_data(DATA_CACHE_Eps2Inst0ChargerZpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_data);
void dc_set_eps2_bp_inst0_charger_zr_data(DATA_CACHE_Eps2Inst0ChargerZrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_bp_info_data(DATA_CACHE_Eps2Inst1BatteryInfoType_t * const p_data);
void dc_set_eps2_bp_inst1_bp_info_data(DATA_CACHE_Eps2Inst1BatteryInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_device_health_info_data(DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t * const p_data);
void dc_set_eps2_bp_inst1_device_health_info_data(DATA_CACHE_Eps2Inst1DeviceHealthInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_ina_sensor1_data(DATA_CACHE_Eps2Inst1InaSensors1Type_t * const p_data);
void dc_set_eps2_bp_inst1_ina_sensor1_data(DATA_CACHE_Eps2Inst1InaSensors1Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_ina_sensor2_data(DATA_CACHE_Eps2Inst1InaSensors2Type_t * const p_data);
void dc_set_eps2_bp_inst1_ina_sensor2_data(DATA_CACHE_Eps2Inst1InaSensors2Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_balancer_info_data(DATA_CACHE_Eps2Inst1BalancerInfoType_t * const p_data);
void dc_set_eps2_bp_inst1_balancer_info_data(DATA_CACHE_Eps2Inst1BalancerInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_balancer_status_data(DATA_CACHE_Eps2Inst1BalancerStatusType_t * const p_data);
void dc_set_eps2_bp_inst1_balancer_status_data(DATA_CACHE_Eps2Inst1BalancerStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_balancer_cells_info_data(DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t * const p_data);
void dc_set_eps2_bp_inst1_balancer_cells_info_data(DATA_CACHE_Eps2Inst1BalancerCellsInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_charger_xp_data(DATA_CACHE_Eps2Inst1ChargerXpType_t * const p_data);
void dc_set_eps2_bp_inst1_charger_xp_data(DATA_CACHE_Eps2Inst1ChargerXpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_charger_xr_data(DATA_CACHE_Eps2Inst1ChargerXrType_t * const p_data);
void dc_set_eps2_bp_inst1_charger_xr_data(DATA_CACHE_Eps2Inst1ChargerXrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_charger_yp_data(DATA_CACHE_Eps2Inst1ChargerYpType_t * const p_data);
void dc_set_eps2_bp_inst1_charger_yp_data(DATA_CACHE_Eps2Inst1ChargerYpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_charger_yr_data(DATA_CACHE_Eps2Inst1ChargerYrType_t * const p_data);
void dc_set_eps2_bp_inst1_charger_yr_data(DATA_CACHE_Eps2Inst1ChargerYrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_charger_zp_data(DATA_CACHE_Eps2Inst1ChargerZpType_t * const p_data);
void dc_set_eps2_bp_inst1_charger_zp_data(DATA_CACHE_Eps2Inst1ChargerZpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst1_charger_zr_data(DATA_CACHE_Eps2Inst1ChargerZrType_t * const p_data);
void dc_set_eps2_bp_inst1_charger_zr_data(DATA_CACHE_Eps2Inst1ChargerZrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_bp_info_data(DATA_CACHE_Eps2Inst2BatteryInfoType_t * const p_data);
void dc_set_eps2_bp_inst2_bp_info_data(DATA_CACHE_Eps2Inst2BatteryInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_device_health_info_data(DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t * const p_data);
void dc_set_eps2_bp_inst2_device_health_info_data(DATA_CACHE_Eps2Inst2DeviceHealthInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_ina_sensor1_data(DATA_CACHE_Eps2Inst2InaSensors1Type_t * const p_data);
void dc_set_eps2_bp_inst2_ina_sensor1_data(DATA_CACHE_Eps2Inst2InaSensors1Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_ina_sensor2_data(DATA_CACHE_Eps2Inst2InaSensors2Type_t * const p_data);
void dc_set_eps2_bp_inst2_ina_sensor2_data(DATA_CACHE_Eps2Inst2InaSensors2Type_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_balancer_info_data(DATA_CACHE_Eps2Inst2BalancerInfoType_t * const p_data);
void dc_set_eps2_bp_inst2_balancer_info_data(DATA_CACHE_Eps2Inst2BalancerInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_balancer_status_data(DATA_CACHE_Eps2Inst2BalancerStatusType_t * const p_data);
void dc_set_eps2_bp_inst2_balancer_status_data(DATA_CACHE_Eps2Inst2BalancerStatusType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_balancer_cells_info_data(DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t * const p_data);
void dc_set_eps2_bp_inst2_balancer_cells_info_data(DATA_CACHE_Eps2Inst2BalancerCellsInfoType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_charger_xp_data(DATA_CACHE_Eps2Inst2ChargerXpType_t * const p_data);
void dc_set_eps2_bp_inst2_charger_xp_data(DATA_CACHE_Eps2Inst2ChargerXpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_charger_xr_data(DATA_CACHE_Eps2Inst2ChargerXrType_t * const p_data);
void dc_set_eps2_bp_inst2_charger_xr_data(DATA_CACHE_Eps2Inst2ChargerXrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_charger_yp_data(DATA_CACHE_Eps2Inst2ChargerYpType_t * const p_data);
void dc_set_eps2_bp_inst2_charger_yp_data(DATA_CACHE_Eps2Inst2ChargerYpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_charger_yr_data(DATA_CACHE_Eps2Inst2ChargerYrType_t * const p_data);
void dc_set_eps2_bp_inst2_charger_yr_data(DATA_CACHE_Eps2Inst2ChargerYrType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_charger_zp_data(DATA_CACHE_Eps2Inst2ChargerZpType_t * const p_data);
void dc_set_eps2_bp_inst2_charger_zp_data(DATA_CACHE_Eps2Inst2ChargerZpType_t * const p_new_data);

dc_data_status_t dc_get_eps2_bp_inst2_charger_zr_data(DATA_CACHE_Eps2Inst2ChargerZrType_t * const p_data);
void dc_set_eps2_bp_inst2_charger_zr_data(DATA_CACHE_Eps2Inst2ChargerZrType_t * const p_new_data);


/*!
* @brief Provides raw data access to individual data cache entries.
* @param id identifier of the DC entry to access
* @param p_data a pointer to the buffer where the DC entry bytes shall be written
* @param user_buf_size size in bytes of the user-provided buffer
* @param start_offset initial offset where to copy from
* @param bytes_to_read number of bytes to read starting from start_offset position
*
* @return DC entry data status
*
* @note Users have to provide a buffer >= to the size of the DC entry, otherwise the
*       operation will assert if debugging is turned on.
*/
dc_data_status_t dc_get_raw_data(const dc_did_id id,
                                 void * const p_data,
                                 const uint32_t user_buf_size,
                                 const uint32_t start_offset,
                                 const uint32_t bytes_to_read);

/*!
* @brief Used to update a DC entry as a binary blob.
* @param input_type identifies how data is fed to the DataCache (e.g. internally by the system or through a simulation interface)
* @param id identifier of the DC entry to update
* @param p_new_data a pointer to the buffer where the new DC entry data shall be copied from
* @param data_size size in bytes of the user-provided buffer
*/
void dc_set_raw_data(const dc_data_input_t input_type, const dc_did_id id, const void * const p_new_data, const uint32_t data_size);

/*!
* @brief Provides the size in bytes of a DC entry given its unique id
* @param id identifier of the requested DC entry
*
* @return size in bytes of the DC binary block
*/
uint32_t dc_get_data_size(const dc_did_id id);

/*!
* @brief Provides the internal item index based on the data attribute idenitifier defined in your FIDL file
* @param type_id ID from FIDL file for the corresponding DataCache attribute entry
*
* @return internal ID which can directly be used with DataCache APIs
*/
dc_did_id dc_get_index_by_data_id(const uint16_t attr_id);

/*!
* @brief Sets the input mode for one or all DataCache entries.
* @param id ID from FIDL file for the corresponding DataCache attribute entry
*           (if DC_DID_MAX specified, all entries get updated)
* @param input_type specifies the input type to use for the specified entry
*/
void dc_set_input_mode(const dc_did_id id, dc_data_input_t input_type);

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __DATACACHE_H__

