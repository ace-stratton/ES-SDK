/*!
********************************************************************************************
* @file FP_obc_adis16265_gyroProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface obc_adis16265_gyro v3.0
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

#ifndef __FP_OBC_ADIS16265_GYROPROTOCOLTYPES_H__
#define __FP_OBC_ADIS16265_GYROPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_OBC_ADIS16265_GYRO ((uint16_t) (0x00000048))

#define OBC_ADIS16265_GYRO_SET_GYROSCOPE_CONFIG_FUNC_ID ((funcIdType_t) 0x00000001)
#define OBC_ADIS16265_GYRO_GET_GYROSCOPE_CONFIG_FUNC_ID ((funcIdType_t) 0x00000002)
#define OBC_ADIS16265_GYRO_SAVE_GYRO_PANEL_CONFIG_FUNC_ID ((funcIdType_t) 0x00000003)
#define OBC_ADIS16265_GYRO_LOAD_GYRO_PANEL_CONFIG_FUNC_ID ((funcIdType_t) 0x00000004)
#define OBC_ADIS16265_GYRO_SET_GYROSCOPE_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define OBC_ADIS16265_GYRO_GET_GYROSCOPE_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define OBC_ADIS16265_GYRO_SAVE_GYRO_PANEL_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define OBC_ADIS16265_GYRO_LOAD_GYRO_PANEL_CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000004)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define OBC_ADIS16265_GYRO_RESULT_OK ((uint8_t) 0)
#define OBC_ADIS16265_GYRO_RESULT_FAIL ((uint8_t) 1)
#define OBC_ADIS16265_GYRO_RESULT_MAX_CNT  ((uint8_t) 2)
typedef uint8_t OBC_ADIS16265_GYRO_RESULT_t;

/*
    This corresponds to enum Panel_Number_t from panels.h
*/
#define OBC_ADIS16265_GYRO_PANEL_ONE ((uint8_t) 1)
#define OBC_ADIS16265_GYRO_PANEL_TWO ((uint8_t) 2)
#define OBC_ADIS16265_GYRO_PANEL_THREE ((uint8_t) 3)
#define OBC_ADIS16265_GYRO_PANEL_FOUR ((uint8_t) 4)
#define OBC_ADIS16265_GYRO_PANEL_FIVE ((uint8_t) 5)
#define OBC_ADIS16265_GYRO_PANEL_SIX ((uint8_t) 6)
#define OBC_ADIS16265_GYRO_PANEL_MAX_CNT  ((uint8_t) 7)
typedef uint8_t OBC_ADIS16265_GYRO_PANEL_t;


typedef struct {
    OBC_ADIS16265_GYRO_PANEL_t eX_AXIS_PANEL;
    OBC_ADIS16265_GYRO_PANEL_t eY_AXIS_PANEL;
    OBC_ADIS16265_GYRO_PANEL_t eZ_AXIS_PANEL;
} PACKED_STRUCT obc_adis16265_gyroSET_GYROSCOPE_CONFIGRequestData_t;


typedef struct {
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;
} PACKED_STRUCT obc_adis16265_gyroSET_GYROSCOPE_CONFIGResponseData_t;

typedef struct {
    OBC_ADIS16265_GYRO_PANEL_t eX_AXIS_ACTIVE_PANEL;
    OBC_ADIS16265_GYRO_PANEL_t eY_AXIS_ACTIVE_PANEL;
    OBC_ADIS16265_GYRO_PANEL_t eZ_AXIS_ACTIVE_PANEL;
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;
} PACKED_STRUCT obc_adis16265_gyroGET_GYROSCOPE_CONFIGResponseData_t;

typedef struct {
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;
} PACKED_STRUCT obc_adis16265_gyroSAVE_GYRO_PANEL_CONFIGResponseData_t;

typedef struct {
    OBC_ADIS16265_GYRO_RESULT_t eOpResult;
} PACKED_STRUCT obc_adis16265_gyroLOAD_GYRO_PANEL_CONFIGResponseData_t;


#endif  // #ifndef __FP_OBC_ADIS16265_GYROPROTOCOLTYPES_H__

