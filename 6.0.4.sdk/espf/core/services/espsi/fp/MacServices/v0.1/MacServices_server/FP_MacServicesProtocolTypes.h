/*!
********************************************************************************************
* @file FP_MacServicesProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface MacServices v0.1
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

#ifndef __FP_MACSERVICESPROTOCOLTYPES_H__
#define __FP_MACSERVICESPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_MACSERVICES ((uint16_t) (0x00000019))

#define MACSERVICES_GETMACBUSTERMINATIONSETTING_FUNC_ID ((funcIdType_t) 0x00000000)
#define MACSERVICES_SETMACBUSTERMINATIONSETTING_FUNC_ID ((funcIdType_t) 0x00000001)
#define MACSERVICES_SETMACADDRESS_FUNC_ID ((funcIdType_t) 0x00000010)
#define MACSERVICES_GETMACBUSTERMINATIONSETTING_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define MACSERVICES_SETMACBUSTERMINATIONSETTING_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define MACSERVICES_SETMACADDRESS_FUNCRESP_ID ((funcIdType_t) 0x00000010)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/

typedef struct {
    bool bReadPersistentSetting;
} PACKED_STRUCT MacServicesgetMacBusTerminationSettingRequestData_t;

typedef struct {
    uint8_t u8SupportedInterfacesBitField;
    uint8_t u8BusTerminationSettingsBitField;
} PACKED_STRUCT MacServicessetMacBusTerminationSettingRequestData_t;

typedef struct {
    uint8_t u8MacAddr;
} PACKED_STRUCT MacServicessetMacAddressRequestData_t;


typedef struct {
    uint8_t u8SupportedInterfacesBitField;
    uint8_t u8BusTerminationSettingsBitField;
} PACKED_STRUCT MacServicesgetMacBusTerminationSettingResponseData_t;

typedef struct {
    uint8_t u8UpdatedMacAddr;
} PACKED_STRUCT MacServicessetMacAddressResponseData_t;


#endif  // #ifndef __FP_MACSERVICESPROTOCOLTYPES_H__

