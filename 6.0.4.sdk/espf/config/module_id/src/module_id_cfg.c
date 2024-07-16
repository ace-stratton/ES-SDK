/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup module_id
 * @{
 *
 * @file module_id_cfg.c
 * @brief Module ID configurable definitions
 * 
 * @note `OBC_VERSION_MAJOR`, `OBC_VERSION_MINOR`, `OBC_VERSION_PATCH`
 * and `OBC_VERSION_LABEL` are expected to be defined at build time.
 *
 * @}
 *
 */
#include "module_id_cfg.h"

/*
***************************************************************************************************
* INTERNAL DEFINES
***************************************************************************************************
*/

/*
***************************************************************************************************
* INTERNAL TYPES DEFINITION
***************************************************************************************************
*/

/*
***************************************************************************************************
* EXTERNAL VARIABLES DEFINITION
***************************************************************************************************
*/

const uint8_t module_id_major_version     = ((uint8_t)OBC_VERSION_MAJOR);
const uint8_t module_id_minor_version     = ((uint8_t)OBC_VERSION_MINOR);
const uint8_t module_id_patch_version     = ((uint8_t)OBC_VERSION_PATCH);
const char    module_id_label_version[30] = "STDPF-STM32H_" QUOTE_MACRO(OBC_VERSION_LABEL);
const uint8_t module_id_active_img_id     = 0;

/*
***************************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
***************************************************************************************************
*/

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

/*
***************************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
***************************************************************************************************
*/
