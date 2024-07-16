/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef MODULE_ID_CFG_H
#define MODULE_ID_CFG_H

/**
 * @addtogroup module_id
 * @{
 *
 * @file module_id_cfg.h
 * @brief Module ID configurable definitions
 *
 * @}
 */
#include "es_cdef.h"

/*
***************************************************************************************************
* EXTERNAL DEFINES
***************************************************************************************************
*/

#if defined(DEBUG_ENABLED)
#define MODULEID_CFG_ACTIVE_IMAGE_TYPE MODID_SWIMGTYPE_APPLICATION_DEBUG
#else
#define MODULEID_CFG_ACTIVE_IMAGE_TYPE MODID_SWIMGTYPE_APPLICATION
#endif

// Necessary to convert a macro into a C string
#define ADD_QUOTES(val)  #val // NOSONAR
#define QUOTE_MACRO(val) ADD_QUOTES(val) // NOSONAR

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
extern const uint8_t module_id_major_version;
extern const uint8_t module_id_minor_version;
extern const uint8_t module_id_patch_version;
extern const char    module_id_label_version[30];
extern const uint8_t module_id_active_img_id;

/*
***************************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
***************************************************************************************************
*/

#endif /* MODULE_ID_CFG_H */
