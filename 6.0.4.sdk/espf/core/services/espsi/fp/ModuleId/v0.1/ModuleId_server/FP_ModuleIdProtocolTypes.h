/*!
********************************************************************************************
* @file FP_ModuleIdProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface ModuleId v0.1
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

#ifndef __FP_MODULEIDPROTOCOLTYPES_H__
#define __FP_MODULEIDPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_MODULEID ((uint16_t) (0x00000100))

#define MODULEID_GETMODULEVERSIONINFO_FUNC_ID ((funcIdType_t) 0x00000000)
#define MODULEID_GETMODULEVERSIONINFO_FUNCRESP_ID ((funcIdType_t) 0x00000000)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Enumeration for the SW_IMG_TYPE field which refers to the type of build the image belongs to
*/
#define MODULEID_SWIMGTYPE_BOOTLOADER ((uint8_t) 0)
#define MODULEID_SWIMGTYPE_BOOTLOADER_DEBUG ((uint8_t) 1)
#define MODULEID_SWIMGTYPE_APPLICATION ((uint8_t) 2)
#define MODULEID_SWIMGTYPE_APPLICATION_DEBUG ((uint8_t) 3)
#define MODULEID_SWIMGTYPE_OTHER ((uint8_t) 4)
#define MODULEID_SWIMGTYPE_MAX_CNT  ((uint8_t) 5)
typedef uint8_t MODULEID_SwImgType_t;

/*
    Version of the firmware
*/
typedef struct {
    uint16_t u16Major;
    uint16_t u16Minor;
    uint16_t u16Patch;
} PACKED_STRUCT MODULEID_BasicVersion_t;

/*
    Additional information about the firmware running
*/
typedef struct {
    uint16_t u16ModuleType;
    MODULEID_BasicVersion_t sFwVersion;
    uint8_t au8BuildTime[8];
    uint8_t au8BuildDate[11];
    uint8_t au8BuildDescription[30];
    MODULEID_SwImgType_t eActiveImageType;
    uint8_t u8ActiveImageId;
    uint8_t au8HwSerialNumber[30];
    MODULEID_BasicVersion_t sHwVersion;
} PACKED_STRUCT MODULEID_VersionInfo_t;



typedef struct {
    MODULEID_VersionInfo_t sSettings;
} PACKED_STRUCT ModuleIdgetModuleVersionInfoResponseData_t;


#endif  // #ifndef __FP_MODULEIDPROTOCOLTYPES_H__

