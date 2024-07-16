/*
* Copyright (c) 2023 EnduroSat AD. All rights reserved.
*
* Contents and presentations are protected world-wide.
* Any kind of using, copying etc. is prohibited without prior permission.
*/
/**
 * @addtogroup module_id
 * @{
 *
 * @file module_id.c
 * @brief Module Information
 *
 * @}
 *
 */

#include <string.h>
#include "module_id.h"
#include "module_id_cfg.h"
#include "es_cdef.h"
#include "nvm/inc/nvm.h"

/*
***************************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
***************************************************************************************************
*/

static sModuleIdPersistentSettings_t mod_id_settings;

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL (NON STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/

const char *module_id_get_image_type_name(const MODID_SwImgType_t img_type_id)
{
    static const char *image_type_names[MODID_SWIMGTYPE_MAX_CNT] = {
        "BOOT\0",
        "BOOTDBG\0",
        "APPL\0",
        "APPLDBG\0",
        "OTHER\0"
    };

    return (img_type_id <
        MODID_SWIMGTYPE_MAX_CNT) ? (image_type_names[img_type_id])
        : "OTHER\0";
}

void module_id_get_info(MODID_VersionInfo_t * const p_version_info)
{
    memset(p_version_info, 0, sizeof(MODID_VersionInfo_t));

    if (p_version_info != NULL) {
        Nvm_GetBlockById(NVM_BLOCK_MODULEID, &mod_id_settings);

        p_version_info->u16ModuleType = mod_id_settings.nModuleType;
        p_version_info->eActiveImageType = MODULEID_CFG_ACTIVE_IMAGE_TYPE;
        p_version_info->u8ActiveImageId = module_id_active_img_id;
        p_version_info->sFwVersion.u16Major = module_id_major_version;
        p_version_info->sFwVersion.u16Minor = module_id_minor_version;
        p_version_info->sFwVersion.u16Patch = module_id_patch_version;
        p_version_info->sHwVersion.u16Major = (uint8_t) mod_id_settings.nModuleHWConfig >> 8U;
        p_version_info->sHwVersion.u16Minor = (uint8_t) mod_id_settings.nModuleHWConfig;
        p_version_info->sHwVersion.u16Patch = (uint8_t) 0U;
        (void)memcpy(p_version_info->au8HwSerialNumber, mod_id_settings.szModuleSerial, sizeof(p_version_info->au8HwSerialNumber));
        (void)memcpy(p_version_info->au8BuildTime, __TIME__, sizeof(__TIME__));
        (void)memcpy(p_version_info->au8BuildDate, __DATE__, sizeof(__DATE__));
        (void)memset(p_version_info->au8BuildDescription, 0x00, sizeof(module_id_label_version));
        (void)memcpy(p_version_info->au8BuildDescription, module_id_label_version, sizeof(p_version_info->au8BuildDescription));
    }
}

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
