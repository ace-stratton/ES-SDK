/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef FILE_MANAGER_CFG_H
#define FILE_MANAGER_CFG_H

/**
 * @addtogroup sd_mng
 * @{
 *
 * @file FileManager_Cfg.c
 *
 * @brief File Manager implementation configuration definitions
 *
 * @}
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include "es_cdef.h"
#include "ffconf.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/
#define FILEMANAGER_MAX_FILE_HANDLE_COUNT       ((uint8_t) 20)
// defines the size of a single block read during file checksum calculation
#define FILEMANAGER_CS_BUF_SIZE_BYTES           ((uint8_t) 100)
// maximum size of the file path string that can be passed to FileManager APIs (allocated
// statically on the local function stack)
#define LOCAL_FILE_PATH_BUF_SIZE_BYTES          ((uint8_t) FF_LFN_BUF)

//in practice there is no limitation of directory levels. The only limitation is coming from
//file name size
#define MAX_DIR_LEVELS (FF_LFN_BUF/2)
/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/
/* No External variables declarations */

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS 
********************************************************************************************
*/

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif    /* FILE_MANAGER_CFG_H */
