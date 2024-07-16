/*!
********************************************************************************************
* @file FP_OBCProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface OBC v3.4
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

#ifndef __FP_OBCPROTOCOLTYPES_H__
#define __FP_OBCPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC ((uint16_t) (0x0000000E))

#define OBC_GETGPOUTPUTSTATES_FUNC_ID ((funcIdType_t) 0x0000000E)
#define OBC_SETGPOUTPUTSTATE_FUNC_ID ((funcIdType_t) 0x0000000F)
#define OBC_GETI2CPULLUPSSTATE_FUNC_ID ((funcIdType_t) 0x00000012)
#define OBC_SETI2CPULLUPSSTATE_FUNC_ID ((funcIdType_t) 0x00000013)
#define OBC_GET_UPTIME_FUNC_ID ((funcIdType_t) 0x00000018)
#define OBC_GETRESETCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000002A)
#define OBC_CLEARRESETCOUNTER_FUNC_ID ((funcIdType_t) 0x0000002B)
#define OBC_TRIGGERRESETINMODE_FUNC_ID ((funcIdType_t) 0x00000036)
#define OBC_SET_DEVICE_MAC_ADDRESS_FUNC_ID ((funcIdType_t) 0x00000040)
#define OBC_GET_DEVICE_MAC_ADDRESS_FUNC_ID ((funcIdType_t) 0x00000041)
#define OBC_GETGPOUTPUTSTATES_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define OBC_SETGPOUTPUTSTATE_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define OBC_GETI2CPULLUPSSTATE_FUNCRESP_ID ((funcIdType_t) 0x00000012)
#define OBC_SETI2CPULLUPSSTATE_FUNCRESP_ID ((funcIdType_t) 0x00000013)
#define OBC_GET_UPTIME_FUNCRESP_ID ((funcIdType_t) 0x00000018)
#define OBC_GETRESETCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000002A)
#define OBC_CLEARRESETCOUNTER_FUNCRESP_ID ((funcIdType_t) 0x0000002B)
#define OBC_TRIGGERRESETINMODE_FUNCRESP_ID ((funcIdType_t) 0x00000036)
#define OBC_SET_DEVICE_MAC_ADDRESS_FUNCRESP_ID ((funcIdType_t) 0x00000040)
#define OBC_GET_DEVICE_MAC_ADDRESS_FUNCRESP_ID ((funcIdType_t) 0x00000041)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    General status type used for HW-related communication and/or settings
*/
#define OBC_HWRESULT_SUCCESS ((uint8_t) 0)
#define OBC_HWRESULT_ERROR ((uint8_t) 1)
#define OBC_HWRESULT_DISABLED ((uint8_t) 255)
#define OBC_HWRESULT_MAX_CNT  ((uint8_t) 256)
typedef uint8_t OBC_HwResult_t;

/*
    General status type used for SW-related communication and/or settings.
*/
#define OBC_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define OBC_STANDARDRESULT_ERROR ((uint8_t) 1)
#define OBC_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define OBC_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define OBC_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t OBC_StandardResult_t;

/*
    Onboard Computer Application mode
*/
#define OBC_APPLICATIONMODE_APPLICATION ((uint8_t) 0)
#define OBC_APPLICATIONMODE_BOOTLOADER ((uint8_t) 1)
#define OBC_APPLICATIONMODE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ApplicationMode_t;

/*
    Structure for the individual OBC general purpose outputs.
*/
typedef struct {
    uint8_t u8GpioStatusBitField;
} PACKED_STRUCT OBC_GpioStatus_t;

/*
    Structure for the I2C Pull-Up Resistors.
*/
typedef struct {
    bool bSystemBus_4K7;
    bool bSystemBus_10K;
    bool bPayloadBus_4K7;
    bool bPayloadBus_10K;
} PACKED_STRUCT OBC_I2CPullUpsState_t;

/*
    This structure keeps information about the OBC reset counters.
                          Each counter represents the number of specific resets which took place since last
                          clear operation.
*/
typedef struct {
    uint32_t u32WWD;
    uint32_t u32IWD;
    uint32_t u32LPR;
    uint32_t u32POR;
    uint32_t u32RstPin;
    uint32_t u32BOR;
    uint32_t u32HardFault;
    uint32_t u32MemFault;
    uint32_t u32BusFault;
    uint32_t u32UsageFault;
} PACKED_STRUCT OBC_ResetCountersInfo_t;

/*
    This enumeration maps to the individual fields of the ResetCountersInfo structure
*/
#define OBC_RESETCNTRID_WWD ((uint8_t) 0)
#define OBC_RESETCNTRID_IWD ((uint8_t) 1)
#define OBC_RESETCNTRID_LPR ((uint8_t) 2)
#define OBC_RESETCNTRID_POR ((uint8_t) 3)
#define OBC_RESETCNTRID_RSTPIN ((uint8_t) 4)
#define OBC_RESETCNTRID_BOR ((uint8_t) 5)
#define OBC_RESETCNTRID_HARDFAULT ((uint8_t) 6)
#define OBC_RESETCNTRID_MEMFAULT ((uint8_t) 7)
#define OBC_RESETCNTRID_BUSFAULT ((uint8_t) 8)
#define OBC_RESETCNTRID_USAGEFAULT ((uint8_t) 9)
#define OBC_RESETCNTRID_ALL ((uint8_t) 10)
#define OBC_RESETCNTRID_MAX_CNT  ((uint8_t) 11)
typedef uint8_t OBC_ResetCntrId_t;

/*
    Enumeration for the Solar Panel IDs
*/
#define OBC_PANELID_X_P ((uint8_t) 0)
#define OBC_PANELID_Y_P ((uint8_t) 1)
#define OBC_PANELID_Z_P ((uint8_t) 2)
#define OBC_PANELID_X_M ((uint8_t) 3)
#define OBC_PANELID_Y_M ((uint8_t) 4)
#define OBC_PANELID_Z_M ((uint8_t) 5)
#define OBC_PANELID_MAX_CNT  ((uint8_t) 6)
typedef uint8_t OBC_PanelId_t;

/*
    Struct containing the values of an accelerometer register
*/
typedef struct {
    OBC_HwResult_t eStatus;
    uint16_t u16Data;
} PACKED_STRUCT OBC_RegData_t;

/*
    Structure for the sensors currently in use
*/
typedef struct {
    bool bIsSensorValid;
    uint8_t u8UsersCount;
} PACKED_STRUCT OBC_SensorInUseData_t;

/*
    Enumeration for the Accelerometer IDs
*/
#define OBC_ACCELID_ONE ((uint8_t) 0)
#define OBC_ACCELID_TWO ((uint8_t) 1)
#define OBC_ACCELID_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_AccelId_t;

/*
    Enumeration for the magnetometer IDs
*/
#define OBC_MAGNETOMETERID_LOW ((uint8_t) 0)
#define OBC_MAGNETOMETERID_HIGH ((uint8_t) 1)
#define OBC_MAGNETOMETERID_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_MagnetometerId_t;

/*
    Enumeration for SAFE booleans
*/
#define OBC_SAFEBOOL_FALSE ((uint8_t) 0)
#define OBC_SAFEBOOL_TRUE ((uint8_t) 255)
#define OBC_SAFEBOOL_MAX_CNT  ((uint8_t) 256)
typedef uint8_t OBC_SafeBool_t;


typedef struct {
    uint8_t u8PinId;
    bool bValue;
} PACKED_STRUCT OBCsetGpOutputStateRequestData_t;

typedef struct {
    OBC_I2CPullUpsState_t sPullupsState;
} PACKED_STRUCT OBCsetI2CPullUpsStateRequestData_t;

typedef struct {
    OBC_ResetCntrId_t eId;
} PACKED_STRUCT OBCclearResetCounterRequestData_t;

typedef struct {
    OBC_ApplicationMode_t eStartMode;
} PACKED_STRUCT OBCtriggerResetInModeRequestData_t;

typedef struct {
    uint8_t u8New_mac_address;
    uint8_t u8Device_id;
} PACKED_STRUCT OBCset_device_mac_addressRequestData_t;

typedef struct {
    uint8_t u8Device_id;
} PACKED_STRUCT OBCget_device_mac_addressRequestData_t;


typedef struct {
    OBC_GpioStatus_t sData;
} PACKED_STRUCT OBCgetGpOutputStatesResponseData_t;

typedef struct {
    OBC_HwResult_t eOpResult;
} PACKED_STRUCT OBCsetGpOutputStateResponseData_t;

typedef struct {
    OBC_I2CPullUpsState_t sNvm_pullupsState;
    OBC_I2CPullUpsState_t sIo_pullupsState;
} PACKED_STRUCT OBCgetI2CPullUpsStateResponseData_t;

typedef struct {
    OBC_I2CPullUpsState_t sPullupsIoState;
} PACKED_STRUCT OBCsetI2CPullUpsStateResponseData_t;

typedef struct {
    uint32_t u32Uptime;
} PACKED_STRUCT OBCget_uptimeResponseData_t;

typedef struct {
    OBC_ResetCountersInfo_t sStatus;
} PACKED_STRUCT OBCgetResetCountersResponseData_t;

typedef struct {
    OBC_StandardResult_t eOpResult;
} PACKED_STRUCT OBCclearResetCounterResponseData_t;

typedef struct {
    OBC_StandardResult_t eOpResult;
} PACKED_STRUCT OBCtriggerResetInModeResponseData_t;

typedef struct {
    OBC_StandardResult_t eOpResult;
} PACKED_STRUCT OBCset_device_mac_addressResponseData_t;

typedef struct {
    uint8_t u8Mac_address;
    OBC_StandardResult_t eOpResult;
} PACKED_STRUCT OBCget_device_mac_addressResponseData_t;


#endif  // #ifndef __FP_OBCPROTOCOLTYPES_H__

