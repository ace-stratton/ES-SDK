/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_TC_TLM_DESCR_H_
#define CUBEADCS_TC_TLM_DESCR_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_tc_tlm_descr.h
 * @brief    Types description used when requesting telemetry or telecommands. Based on
 * 			 CubeSpace's Firmware Reference Manual
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif    // #ifdef __cplusplus

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/

#include "es_cdef.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

/*-----------------------------------------------------------------------------------------*/
/*-------------------------------------Custom TC/TLM types---------------------------------*/
/*-----------------------------------------------------------------------------------------*/
typedef struct tag_cubeadcs_ref
{
    float ref_param_1;
    float ref_param_2;
    float ref_param_3;

} PACKED cubeadcs_ref_t;

/*-----------------------------------------------------------------------------------------*/
/*-------------------------------------Common TC/TLM types---------------------------------*/
/*-----------------------------------------------------------------------------------------*/

typedef enum tag_eCubeADCS_FTypes {
    eCUBEADCS_FTYPES_TLM_LOG = 2,
    eCUBEADCS_FTYPES_JPG_IMG = 3,
    eCUBEADCS_FTYPES_BMP_IMG = 4,
    eCUBEADCS_FTYPES_INDEX   = 15,

} eCubeADCS_FTypes_t;

typedef struct tag_CubeADCS_TargRef
{
    float fGeoLon;
    float fGeoLat;
    float fGeoAlt;

} PACKED CubeADCS_TargRef_t;

typedef struct tag_CubeADCS_SGP4_Orbit_Params {
	double dInc; 	/* Inclination */
	double dEcc;	/* Eccentricity */
	double dRAAN; 	/* Right-ascension of the Ascending Node */
	double dAOP; 	/* Argument of perigee */
	double dBStar; 	/* B-Star drag term */
	double dMeanM;	/* Mean Motion */
	double dMeanA; 	/* Mean Anomaly */
	double dEpoch; 	/* Epoch */

} PACKED CubeADCS_SGP4_Orbit_Params_t;

typedef struct tag_CubeADCS_UnixTime {
	uint32_t u32CurrentUnixTime;
	uint16_t u16Milliseconds;

} PACKED CubeADCS_UnixTime_t;

typedef union tag_uCubeADCS_UnixTimeSaveCfg {
	struct {
		uint8_t save_now		: 1;
		uint8_t save_on_update	: 1;
		uint8_t save_periodic	: 1;
		uint8_t res				: 5;
	} cfg;
	uint8_t u8Data;

} PACKED uCubeADCS_UnixTimeSaveCfg;

typedef struct tag_CubeADCS_UnixTimeSave {
	uCubeADCS_UnixTimeSaveCfg uSaveCfg;
	uint8_t u8Period;

} PACKED CubeADCS_UnixTimeSave_t;

/*-----------------------------------------------------------------------------------------*/
/*----------------------------------------TLM types----------------------------------------*/
/*-----------------------------------------------------------------------------------------*/

typedef struct tag_CubeADCS_TLM128
{
    uint8_t  cmdID;
    uint8_t  NodeType;
    uint8_t  InterfaceVersion;
    uint8_t  MajorFirmwareVersion;
    uint8_t  MinorFirmwareVersion;
    uint16_t RuntimeSeconds;
    uint16_t RuntimeMiliseconds;

} __attribute__((__packed__)) CubeADCS_TLM128_t;

typedef enum tag_eCubeADCS_TLM129_BootCause_t {
	eCUBEADCS_TLM129_BOOTCAUSE_UNEXPECTED 	= 0,
	eCUBEADCS_TLM129_BOOTCAUSE_NOT_USED	  	= 1,
	eCUBEADCS_TLM129_BOOTCAUSE_COMM_TIMEOUT = 2,
	eCUBEADCS_TLM129_BOOTCAUSE_COMMANDED 	= 3,
	eCUBEADCS_TLM129_BOOTCAUSE_NOT_USED2	= 4,
	eCUBEADCS_TLM129_BOOTCAUSE_SRAM_LATCHUP = 5

} eCubeADCS_TLM129_BootCause_t;

typedef struct tag_CubeADCS_TLM129
{
	uint8_t  cmdID;
	uint8_t rst_and_boot;
	uint16_t boot_cnt;
	uint8_t	boot_prg_indx;
	uint8_t fw_ver_major;
	uint8_t fw_ver_minor;

} PACKED CubeADCS_TLM129_t;

typedef enum tag_eCubeADCS_TLM130_ProgIndx_t
{
    eCUBEADCS_TLM130_PROGINDX_INTERNAL_FLASH_PROGRAM = 1,
    eCUBEADCS_TLM130_PROGINDX_BOOTLOADER             = 2,

} eCubeADCS_TLM130_ProgIndx_t;

typedef enum tag_eCubeADCS_TLM130_BootStatus_t
{
    eCUBEADCS_TLM130_BOOTSTATUS_NEW_SELECTION = 0,
    eCUBEADCS_TLM130_BOOT_SUCCESS             = 1,
    eCUBEADCS_TLM130_FAILED_1                 = 2,
    eCUBEADCS_TLM130_FAILED_2                 = 3,
    eCUBEADCS_TLM130_FAILED_3                 = 4,

} eCubeADCS_TLM130_BootStatus_t;

typedef struct tag_eCubeADCS_TLM130
{
    uint8_t                       cmdID;
    eCubeADCS_TLM130_ProgIndx_t   eProgramIndex;
    eCubeADCS_TLM130_BootStatus_t eBootStatus;

} __attribute__((__packed__)) CubeADCS_TLM130_t;

typedef union tag_uCubeADCS_TLM132_Boot_Flags
{
    struct {
        uint16_t SRAM1_en:      1;
        uint16_t SRAM2_en:      1;
        uint16_t SRAM_LUP_err:  1;
        uint16_t SRAM_LUP_rec:  1;
        uint16_t SD_CARD_err:   1;
        uint16_t Ext_Flash_err: 1;
        uint16_t Int_Flash_err: 1;
        uint16_t EEPROM_err:    1;
        uint16_t Boot_reg_err:  1;
        uint16_t Comm_radio_err:1;
        uint16_t res:           6;
    } Data;
    uint16_t u16DataBytes;

} __attribute__((__packed__)) uCubeADCS_TLM132_Boot_Flags_t;

typedef struct tag_CubeADCS_TLM132_Boot
{
    uint16_t uptime;
    uCubeADCS_TLM132_Boot_Flags_t flags;
    uint16_t res;

} __attribute__((__packed__)) CubeADCS_TLM132_Boot_t;

typedef union tag_uCubeADCS_TLM132_App_Byte0
{
    struct {
        uint8_t Att_Est_Mode: 4;
        uint8_t Control_Mode: 4;
    } Data;
        uint8_t u8DataByte;

} __attribute__((__packed__)) uCubeADCS_TLM132_App_Byte0_t;

typedef union tag_uCubeADCS_TLM132_App_Byte1
{
    struct {
        uint8_t ADCS_Run_Mode         : 2;
        uint8_t ASGP4_Mode            : 2;
        bool CubeControl_Signal_en : 1;
        bool CubeControl_Motor_en  : 1;
        bool CubeSense1_en         : 1;
        bool CubeSense2_en         : 1;
    } Data;
        uint8_t u8DataByte;

} __attribute__((__packed__)) uCubeADCS_TLM132_App_Byte1_t;

typedef union tag_uCubeADCS_TLM132_App_Byte2
{
    struct {
        bool CubeWheel1_en      : 1;
        bool CubeWheel2_en      : 1;
        bool CubeWheel3_en      : 1;
        bool CubeStar_en        : 1;
        bool GPS_rx_en          : 1;
        bool GPS_LNA_en         : 1;
        bool Motor_drv_en       : 1;
        bool Sun_above_Horizon  : 1;
    } Data;
        uint8_t u8DataByte;

} __attribute__((__packed__)) uCubeADCS_TLM132_App_Byte2_t;

typedef union tag_uCubeADCS_TLM132_App_Byte3
{
    struct {
        uint8_t CubeSense1_comm_err  : 1;
        uint8_t CubeSense2_comm_err  : 1;
        uint8_t CubeControl_comm_err : 1;
        uint8_t CubeMotor_comm_err   : 1;
        uint8_t CubeWheel1_comm_err  : 1;
        uint8_t CubeWheel2_comm_err  : 1;
        uint8_t CubeWheel3_comm_err  : 1;
        uint8_t CubeStar_comm_err    : 1;
    } Data;
        uint8_t u8DataByte;

} __attribute__((__packed__)) uCubeADCS_TLM132_App_Byte3_t;

typedef union tag_uCubeADCS_TLM132_App_Byte4
{
    struct {
        uint8_t Mag_range_err           : 1;
        uint8_t Cam1_SRAM_overcurrent   : 1;
        uint8_t Cam1_3V3_overcurrent    : 1;
        uint8_t Cam1_busy_err           : 1;
        uint8_t Cam1_detect_err         : 1;
        uint8_t Sun_detection_err       : 1;
        uint8_t Cam2_SRAM_overcurrent   : 1;
        uint8_t Cam2_3V3_overcurrent    : 1;
    } Data;
        uint8_t u8DataByte;

} __attribute__((__packed__)) uCubeADCS_TLM132_App_Byte4_t;

typedef union tag_uCubeADCS_TLM132_App_Byte5
{
    struct {
        uint8_t Cam2_busy_err           : 1;
        uint8_t Cam2_detect_err         : 1;
        uint8_t Nadir_range_err         : 1;
        uint8_t Rate_range_err          : 1;
        uint8_t Wheel_speed_range_err   : 1;
        uint8_t Coarse_sun_range_err    : 1;
        uint8_t Star_match_err          : 1;
        uint8_t Star_overcurrent        : 1;
    } Data;
        uint8_t u8DataByte;

} __attribute__((__packed__)) uCubeADCS_TLM132_App_Byte5_t;

typedef struct tag_CubeADCS_TLM132_App
{
    uCubeADCS_TLM132_App_Byte0_t Byte0;
    uCubeADCS_TLM132_App_Byte1_t Byte1;
    uCubeADCS_TLM132_App_Byte2_t Byte2;
    uCubeADCS_TLM132_App_Byte3_t Byte3;
    uCubeADCS_TLM132_App_Byte4_t Byte4;
    uCubeADCS_TLM132_App_Byte5_t Byte5;

} __attribute__((__packed__)) CubeADCS_TLM132_App_t;

typedef union tag_uCubeADCS_TLM132
{
    CubeADCS_TLM132_Boot_t Boot;
    CubeADCS_TLM132_App_t  App;
} __attribute__((__packed__)) uCubeADCS_TLM132_t ;

typedef struct tag_CubeADCS_TLM132 {
    uint8_t                cmdID;
    uCubeADCS_TLM132_t     TLM;

} __attribute__((__packed__)) CubeADCS_TLM132_t;

typedef struct tag_CubeADCS_TLM135
{
    uint8_t cmdID;
    union {
        struct {
            uint8_t ADCS_Config_Load_Err :1;
            uint8_t Orbit_Param_Load_Err :1;
            uint8_t Sys_Config_Load_Err  :1;
            uint8_t res                  :5;
        } Data;
            uint8_t u8DataByte;
    } ACP_State;

} __attribute__((__packed__)) CubeADCS_TLM135_t;

typedef union tag_uCubeADCS_TLM224_App_Byte0
{
    struct {
        uint8_t OrbitParam_invalid    : 1;
        uint8_t Config_invalid        : 1;
        uint8_t CntrlModeChg_X        : 1;
        uint8_t EstChg_X              : 1;
        uint8_t MagnetometerSampMode  : 2;
        uint8_t Diff_Magnetic_field   : 1;
        uint8_t Node_Recovery_err     : 1;
    } Data;
        uint8_t u8DataByte;

} __attribute__((__packed__)) uCubeADCS_TLM224_App_Byte0_t;

typedef union tag_uCubeADCS_TLM224_App_Byte1
{
    struct {
        uint8_t CubeSense1_err          : 1;
        uint8_t CubeSense2_err          : 1;
        uint8_t CubeControlSignal_err   : 1;
        uint8_t CubeControlMotor_err    : 1;
        uint8_t CubeWheel1_err          : 1;
        uint8_t CubeWheel2_err          : 1;
        uint8_t CubeWheel3_err          : 1;
        uint8_t CubeStar_err            : 1;
    } Data;
        uint8_t u8DataByte;
} __attribute__((__packed__)) uCubeADCS_TLM224_App_Byte1_t;

typedef union tag_uCubeADCS_TLM224_App_Byte2
{
    struct {
        uint8_t Magnetometer_err        : 1;
        uint8_t RateSensor_fail         : 1;
        uint8_t Res                     : 6;
    } Data;
            uint8_t u8DataByte;
} __attribute__((__packed__)) uCubeADCS_TLM224_App_Byte2_t;

typedef struct tag_CubeADCS_TLM224
{
    uint8_t                      cmdID;
    uCubeADCS_TLM224_App_Byte0_t Byte0;
    uCubeADCS_TLM224_App_Byte1_t Byte1;
    uCubeADCS_TLM224_App_Byte2_t Byte2;
    uint8_t                      Byte3;
    uint8_t                      Byte4;
    uint8_t                      Byte5;

} __attribute__((__packed__)) CubeADCS_TLM224_t;

typedef enum tag_eCUBE_ADCS_TLM128 {
    eCUBEADCS_TLM128_BYTE0_CMD_ID,
    eCUBEADCS_TLM128_BYTE1_NODE_TYPE,
    eCUBEADCS_TLM128_BYTE2_INTERFACE_VERSION,
    eCUBEADCS_TLM128_BYTE3_MAJOR_FW_VERSION,
    eCUBEADCS_TLM128_BYTE4_MINOR_FW_VERSION,
    eCUBEADCS_TLM128_BYTE5_RUNTIME_SECONDS_HIGH,
    eCUBEADCS_TLM128_BYTE6_RUNTIME_SECONDS_LOW,
    eCUBEADCS_TLM128_BYTE7_RUNTIME_MILISECONDS_HIGH,
    eCUBEADCS_TLM128_BYTE8_RUNTIME_MILISECONDS_LOW,

} eCUBE_ADCS_TLM128_t;

typedef enum tag_eCUBE_ADCS_TLM135 {
    eCUBEADCS_TLM135_BYTE0_CMD_ID,
    eCUBEADCS_TLM135_BYTE1_ACP_STATE,

} eCUBE_ADCS_TLM135_t;

typedef enum tag_eCUBE_ADCS_TLM132 {
    eCUBEADCS_TLM132_BYTE_CMD_ID,
    eCUBEADCS_TLM132_BYTE0,
    eCUBEADCS_TLM132_BYTE1,
    eCUBEADCS_TLM132_BYTE2,
    eCUBEADCS_TLM132_BYTE3,
    eCUBEADCS_TLM132_BYTE4,
    eCUBEADCS_TLM132_BYTE5,

} eCUBE_ADCS_TLM132_t;

typedef enum tag_eCUBE_ADCS_TLM224 {
    eCUBEADCS_TLM224_BYTE_CMD_ID,
    eCUBEADCS_TLM224_BYTE0,
    eCUBEADCS_TLM224_BYTE1,
    eCUBEADCS_TLM224_BYTE2,
    eCUBEADCS_TLM224_BYTE3,
    eCUBEADCS_TLM224_BYTE4,
    eCUBEADCS_TLM224_BYTE5,

} eCUBE_ADCS_TLM224_t;

typedef union tag_uCubeADCS_TLM197_Byte0
{
    struct {
        uint8_t CubeControl_Signal  : 2;
        uint8_t CubeControl_Motor   : 2;
        uint8_t CubeSense1          : 2;
        uint8_t CubeSense2          : 2;
    } Data;
    uint8_t u8DataByte;
} __attribute__((__packed__)) uCubeADCS_TLM197_Byte0_t;

typedef union tag_uCubeADCS_TLM197_Byte1
{
    struct {
        uint8_t CubeStar            : 2;
        uint8_t CubeWheel1          : 2;
        uint8_t CubeWheel2          : 2;
        uint8_t CubeWheel3          : 2;
    } Data;
    uint8_t u8DataByte;
} __attribute__((__packed__)) uCubeADCS_TLM197_Byte1_t;

typedef union tag_uCubeADCS_TLM197_Byte2
{
    struct {
        uint8_t MotorPwr            : 2;
        uint8_t GPSPwr              : 2;
        uint8_t res                 : 4;
    } Data;
    uint8_t u8DataByte;
} __attribute__((__packed__)) uCubeADCS_TLM197_Byte2_t;

typedef union tag_CubeADCS_TLM197
{
    struct {
        uint8_t                  cmdID;
        uCubeADCS_TLM197_Byte0_t Byte0;
        uCubeADCS_TLM197_Byte1_t Byte1;
        uCubeADCS_TLM197_Byte2_t Byte2;
    } Data;
    uint32_t u32RawData;

} __attribute__((__packed__)) CubeADCS_TLM197_t;

typedef struct tag_CubeADCS_AngRateFormatted {
    float fX;
    float fY;
    float fZ;

} __attribute__((__packed__)) CubeADCS_AngRateFormatted_t;

typedef struct tag_CubeADCS_AngRate {
    int16_t i16X;
    int16_t i16Y;
    int16_t i16Z;

} __attribute__((__packed__)) CubeADCS_AngRate_t;

typedef struct tag_CubeADCS_TLM147 {
    uint8_t  cmdID;
    CubeADCS_AngRate_t AngRate;

} __attribute__((__packed__)) CubeADCS_TLM147_t;

typedef struct tag_CubeADCS_TLM155 {
    uint8_t  cmdID;
    CubeADCS_AngRate_t AngRate;

} __attribute__((__packed__)) CubeADCS_TLM155_t;

typedef enum tag_eCubeADCS_TLM243_FileType
{
    eCUBEADCS_TLM243_FILETYPE_TLM_LOG = 2,
    eCUBEADCS_TLM243_FILETYPE_JPG_IMG = 3,
    eCUBEADCS_TLM243_FILETYPE_BMP_IMG = 4,
    eCUBEADCS_TLM243_FILETYPE_INDX   = 15,

} eCubeADCS_TLM243_FileType;

typedef union tag_CubeADCS_TLM243_Byte0
{
    struct {
        uint8_t fileType: 4;
        uint8_t busy    : 1;
        uint8_t res     : 3;

    } Data;
    uint8_t u8RawData;

}__attribute__((__packed__)) CubeADCS_TLM243_Byte0;

typedef struct tag_CubeADCS_TLM243_Data {

    CubeADCS_TLM243_Byte0 Byte0;
    uint8_t               Counter;
    uint32_t              Size;
    uint32_t              DateTime;
    uint16_t              CRC16;

} __attribute__((__packed__)) CubeADCS_TLM243_Data_t;

typedef struct tag_CubeADCS_TLM243 {

    uint8_t                cmdID;
    CubeADCS_TLM243_Data_t TLM243;

} __attribute__((__packed__)) CubeADCS_TLM243_t;

typedef union tag_uCubeADCS_TLM242_Byte0
{
    struct {
        uint8_t rdy      : 1;
        uint8_t ParamErr : 1;
        uint8_t res      : 6;
    } Data;
    uint8_t u8RawData;
} __attribute__((__packed__)) uCubeADCS_TLM242_Byte0_t;

typedef struct tag_eCubeADCS_TLM242_Data {

    uCubeADCS_TLM242_Byte0_t Byte0;
    uint16_t                 Crc16;
    uint16_t                 BlockLen;

} __attribute__((__packed__)) eCubeADCS_TLM242_Data_t;

typedef struct tag_eCubeADCS_TLM242 {
    uint8_t                 cmdID;
    eCubeADCS_TLM242_Data_t TLM242;
} __attribute__((__packed__)) eCubeADCS_TLM242_t;

typedef struct tag_eCubeADCS_TLM119 {
    uint8_t  HeadID;
    uint16_t BurstCnt;
    uint8_t  Payload[20];

} __attribute__((__packed__)) eCubeADCS_TLM119_t;

typedef struct tag_CubeADCS_QErr {
    int16_t i16Q1;
    int16_t i16Q2;
    int16_t i16Q3;

} __attribute__((__packed__)) CubeADCS_QErr_t;

typedef struct tag_CubeADCS_QErrFormatted {
    float fQ1;
    float fQ2;
    float fQ3;

} __attribute__((__packed__)) CubeADCS_QErrFormatted_t;

typedef struct tag_CubeADCS_TLM163 {
    uint8_t  cmdID;
    CubeADCS_QErr_t QErr;

} __attribute__((__packed__)) CubeADCS_TLM163_t;

typedef struct tag_CubeADCS_TLM207 {
    uint8_t  cmdID;
    CubeADCS_SGP4_Orbit_Params_t sSGP4_Orbit_Params;

} __attribute__((__packed__)) CubeADCS_TLM207_t;

typedef struct tag_CubeADCS_TLM140 {
    uint8_t  cmdID;
    CubeADCS_UnixTime_t sUnixTime;

} PACKED CubeADCS_TLM140_t;

typedef struct tag_CubeADCS_AngRate_Formatted {
	int32_t X;
	int32_t Y;
	int32_t Z;

} PACKED CubeADCS_AngRate_Formatted_t;

typedef struct tag_CubeADCS_AngRate_Complete {
    int32_t fAngVelNorm;
    CubeADCS_AngRate_Formatted_t sAngVelVec;

} PACKED CubeADCS_AngRate_Complete_t;

typedef struct tag_cubeadcs_est_att_ang_fmt_t {
	int32_t i32Roll;
	int32_t i32Pitch;
	int32_t i32Yaw;

} PACKED cubeadcs_est_att_ang_fmt_t;

typedef struct cubeadcs_est_att_ang_t {
    int16_t i16Roll_raw;
    int16_t i16Pitch_raw;
    int16_t i16Yaw_raw;

} PACKED cubeadcs_est_att_ang_t;

typedef struct tag_cubeadcs_tlm_146_t {
    uint8_t  cmdID;
    cubeadcs_est_att_ang_t sRawAttAng;

} PACKED cubeadcs_tlm_146_t;

typedef struct {
	int16_t X_Wheel;
	int16_t Y_Wheel;
	int16_t Z_Wheel;

} PACKED cubeadcs_meas_wheel_speed_t;

typedef struct {
    uint8_t  cmdID;
    cubeadcs_meas_wheel_speed_t meas_wheel_speed;

} PACKED cubeadcs_tlm_156_t;

/*-----------------------------------------------------------------------------------------*/
/*-----------------------------------------TC types----------------------------------------*/
/*-----------------------------------------------------------------------------------------*/

typedef enum tag_eCUBE_ADCS_TC_10_RUNMODE {
    eCUBE_ADCS_TC10_RUNMODE_OFF,
    eCUBE_ADCS_TC10_RUNMODE_ENABLED,
    eCUBE_ADCS_TC10_RUNMODE_TRIGGERED,
    eCUBE_ADCS_TC10_RUNMODE_SIMULATION,

} eCUBE_ADCS_TC_10_RUNMODE_t;

typedef enum tag_eCUBE_ADCS_TC_11_NODES {
    eCUBE_ADCS_TC11_NODES_CUBECONTROL_SIGNAL,
    eCUBE_ADCS_TC11_NODES_CUBECONTROL_MOTOR,
    eCUBE_ADCS_TC11_NODES_CUBESENSE_1,
    eCUBE_ADCS_TC11_NODES_CUBESENSE_2,
    eCUBE_ADCS_TC11_NODES_CUBESTAR,
    eCUBE_ADCS_TC11_NODES_CUBEWHEEL_1,
    eCUBE_ADCS_TC11_NODES_CUBEWHEEL_2,
    eCUBE_ADCS_TC11_NODES_CUBEWHEEL_3,
    eCUBE_ADCS_TC11_NODES_MOTOR,
    eCUBE_ADCS_TC11_NODES_GPS,
    eCUBE_ADCS_TC11_NODES_NUMBER,

} eCUBE_ADCS_TC_11_NODES_t;

typedef enum tag_eCUBE_ADCS_TC_11_PWR_STATES {
    eCUBE_ADCS_TC11_STATE_OFF,
    eCUBE_ADCS_TC11_STATE_ON,
    eCUBE_ADCS_TC11_STATE_NO_CHANGE,
    eCUBE_ADCS_TC11_STATE_NUMBER,

} eCUBE_ADCS_TC_11_PWR_STATES_t;

typedef enum tag_eCUBE_ADCS_TC_56_MTM_MODE {
    eCUBEADCS_TC56_MAIN_MTM_SIGNAL_MCU,
    eCUBEADCS_TC56_REDUNT_MTM_SIGNAL_MCU,
    eCUBEADCS_TC56_MAIN_MTM_MOTOR_MCU,
    eCUBEADCS_TC56_NONE,

} eCUBE_ADCS_TC_56_MTM_MODE_t;

typedef enum tag_eCUBE_ADCS_TC_23_RATE_SENSOR_MULT {
    eCUBEADCS_TC23_RATESENSORMULT_0,
    eCUBEADCS_TC23_RATESENSORMULT_1,
    eCUBEADCS_TC23_RATESENSORMULT_2,
    eCUBEADCS_TC23_RATESENSORMULT_3,
    eCUBEADCS_TC23_RATESENSORMULT_4,
    eCUBEADCS_TC23_RATESENSORMULT_5,
    eCUBEADCS_TC23_RATESENSORMULT_6,
    eCUBEADCS_TC23_RATESENSORMULT_7,
    eCUBEADCS_TC23_RATESENSORMULT_8,
    eCUBEADCS_TC23_RATESENSORMULT_9,
    eCUBEADCS_TC23_RATESENSORMULT_10,
    eCUBEADCS_TC23_RATESENSORMULT_11,
    eCUBEADCS_TC23_RATESENSORMULT_12,

} eCUBE_ADCS_TC_23_RATE_SENSOR_MULT_t;

typedef enum tag_eCUBE_ADCS_TC_13_CONTROL_MODE {
    eCUBE_ADCS_TC_13_CONTROLMODE_NO_CNTRL,
    eCUBE_ADCS_TC_13_CONTROLMODE_DETUMB_CNTRL,
    eCUBE_ADCS_TC_13_CONTROLMODE_Y_THOMPSON,
    eCUBE_ADCS_TC_13_CONTROLMODE_Y_WHEEL_INITIAL,
    eCUBE_ADCS_TC_13_CONTROLMODE_Y_WHEEL_STEADY,
    eCUBE_ADCS_TC_13_CONTROLMODE_XYZ_WHEEL_CNTRL,
    eCUBE_ADCS_TC_13_CONTROLMODE_RWHEEL_SUN_TRACKING,
    eCUBE_ADCS_TC_13_CONTROLMODE_RWHEEL_TARGET_TRACKING,
    eCUBE_ADCS_TC_13_CONTROLMODE_VERY_FAST_SPIN_DETUMB,
    eCUBE_ADCS_TC_13_CONTROLMODE_FAST_SPIN_DETUMB,
    eCUBE_ADCS_TC_13_CONTROLMODE_USER_MODE_1,
    eCUBE_ADCS_TC_13_CONTROLMODE_USER_MODE_2,
    eCUBE_ADCS_TC_13_CONTROLMODE_STOP_R_WHEELS,
    eCUBE_ADCS_TC_13_CONTROLMODE_USER_CODED_MODE,
    eCUBE_ADCS_TC_13_CONTROLMODE_SUN_TRACKING_YAW_OR_ROLL_ONLY,
    eCUBE_ADCS_TC_13_CONTROLMODE_TARGET_TRACKING_YAW_ONLY,
} eCUBE_ADCS_TC_13_CONTROL_MODE_t;

typedef struct tag_CubeADCS_TC_13 {
    eCUBE_ADCS_TC_13_CONTROL_MODE_t ControlMode;
    uint16_t                        u16Timeout;
} __attribute__((__packed__)) CubeADCS_TC_13_t;

typedef struct tag_CubeADCS_TC_112 {
    eCubeADCS_FTypes_t eFType;
    uint8_t            u8Counter;
    uint32_t           u32Offset;
    uint16_t           u16BlockLen;
} __attribute__((__packed__)) CubeADCS_TC_112_t;

typedef struct tag_CubeADCS_TC_119 {
    uint8_t MessageLen;
    bool    IgnoreHoleMap;
} __attribute__((__packed__)) CubeADCS_TC_119_t;

typedef enum tag_eCUBE_ADCS_TC_14_ESTIMATION_MODE {
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_NO_EST,
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_RATE_SENS,
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_MTM_RATE_FILT,
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_MTM_RATE_FILT_WITH_PITCH,
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_MTM_FINE_SUN_TRIAD,
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_FULL_EKF,
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_MEMS_GYRO_EKF,
    eCUBE_ADCS_TC_14_ESTIMATIONMODE_USR_CODED,

} eCUBE_ADCS_TC_14_ESTIMATION_MODE_t;

typedef struct tag_CubeADCS_TC_HoleMAP_t
{
    uint8_t u8HoleMapArr[16];
} __attribute__((__packed__)) CubeADCS_TC_HoleMAP_t;

typedef struct tag_CubeADCS_Command_Angles
{
    int16_t i16RollAngle;
    int16_t i16PitchAngle;
    int16_t i16YawAngle;
} __attribute__((__packed__)) CubeADCS_Command_Angles_t;

typedef struct tag_CubeADCS_TC_15 {
    CubeADCS_Command_Angles_t CommandedAngles;

} __attribute__((__packed__)) CubeADCS_TC_15_t;

typedef struct tag_CubeADCS_RWheels_Speed
{
    int16_t i16RWheel_X;
    int16_t i16RWheel_Y;
    int16_t i16RWheel_Z;

} __attribute__((__packed__)) CubeADCS_RWheels_Speed_t;

typedef struct tag_CubeADCS_TC_17 {
    CubeADCS_RWheels_Speed_t RWheelsRPM;

} __attribute__((__packed__)) CubeADCS_TC_17_t;

typedef struct tag_CubeADCS_TC_55 {
    CubeADCS_TargRef_t sTargRef;

} PACKED CubeADCS_TLM_55_t;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/

#ifdef __cplusplus
}
#endif    // #ifdef __cplusplus

#endif    /* CUBEADCS_TC_TLM_DESCR_H_ */
/* ******************************************************************************************* */
