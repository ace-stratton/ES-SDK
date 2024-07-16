/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef MODULE_ID_H
#define MODULE_ID_H
/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup module_id Module ID
 * @{
 *
 * Library containing a common interface between Endurosat devices to retrieve the
 *  basic firmware information.
 *
 * @file module_id.h
 * @brief Public interface of Module ID
 *
 * @}
 * @}
 */
#include <stdint.h>
#include "ESPLATFORM_COMMON/ESSAT_ModuleIdTypes.h"

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL TYPES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/
/**
 * @brief Get the module information structure
 * @param p_version_info: pointer to the obtained information
 */
void module_id_get_info(MODID_VersionInfo_t * const p_version_info);

/**
 * @brief Get the image name based on the image type
 * @param img_type_id: type of the image to return the name of
 *
 * @return string with the name of the image
 */
const char *module_id_get_image_type_name(const MODID_SwImgType_t img_type_id);

#endif    /* MODULE_ID_H */
