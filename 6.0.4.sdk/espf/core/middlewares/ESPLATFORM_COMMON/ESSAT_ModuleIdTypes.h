/*
 * Global definition of EnduroSat module identification support types
 *
 * Reference:
 * https://endurosat.atlassian.net/wiki/spaces/ENDUROSAT/pages/1632273032/SW+support+for+basic+module+identification
 */
#ifndef __ESSAT_MODULEIDTYPES_H__
#define __ESSAT_MODULEIDTYPES_H__

#include <stdint.h>

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/* 
    Enumeration for the SW_IMG_TYPE field 
*/
#define MODID_SWIMGTYPE_BOOTLOADER            ((uint8_t) 0)
#define MODID_SWIMGTYPE_BOOTLOADER_DEBUG      ((uint8_t) 1)
#define MODID_SWIMGTYPE_APPLICATION           ((uint8_t) 2)
#define MODID_SWIMGTYPE_APPLICATION_DEBUG     ((uint8_t) 3)
#define MODID_SWIMGTYPE_OTHER                 ((uint8_t) 4)
#define MODID_SWIMGTYPE_MAX_CNT               ((uint8_t) 5)
typedef uint8_t MODID_SwImgType_t;

// __TIME__ preprocessor symbol expansion +1 byte for NULLZ
#define cu8BuildTimeSizeBytes            (9U)
// __DATE__ preprocessor symbol expansion +1 byte for NULLZ
#define cu8BuildDateSizeBytes            (12U)
#define cu8BuildDescrSizeBytes           (30U)
#define cu8HwSerialSizeBytes             (30U)

#pragma pack(push)
#pragma pack(1)

typedef struct {
    uint16_t u16Major;
    uint16_t u16Minor;
    uint16_t u16Patch;
} MODID_BasicVersion_t;

typedef struct {
    uint16_t u16ModuleType;
    MODID_BasicVersion_t sFwVersion;
    uint8_t au8BuildTime[cu8BuildTimeSizeBytes];
    uint8_t au8BuildDate[cu8BuildDateSizeBytes];
    uint8_t au8BuildDescription[cu8BuildDescrSizeBytes];
    uint8_t u8ActiveImageId;
    uint8_t au8HwSerialNumber[cu8HwSerialSizeBytes];
    MODID_BasicVersion_t sHwVersion;
    MODID_SwImgType_t eActiveImageType;
} MODID_VersionInfo_t;

#pragma pack(pop)                // #pragma pack(1) - end of byte aligned structures

#endif // #ifndef __ESSAT_MODULEIDTYPES_H__
