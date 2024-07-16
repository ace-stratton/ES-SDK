/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef TLEUPDATE_H
#define TLEUPDATE_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup tle TLE
 * @{
 *
 * Two-Line Element helper library
 *
 * @file TleUpdate.h
 * @brief Public interface of the TLE library
 *
 * @}
 * @}
 */

#include "cmsis_os.h"
#include <main.h>
#include "sgp4_propagator.h"

typedef enum
{
	TLE_UPDATE_OK = 0,
	TLE_UPDATE_ERR_FILE,
	TLE_UPDATE_ERR_SGP4,
	TLE_UPDATE_ERR_ADCS,
} tle_update_err_t;

/**
 * @brief Update the TLE of the system from a pre-uploaded file
 * @param[input]      file_name: string containing the file name
 *
 * @retval TLE_UPDATE_OK: the operation was successful
 * @retval TLE_UPDATE_ERR_FILE: could not write or read the file
 * @retval TLE_UPDATE_ERR_SGP4: error with the contents or format of the TLE
 * @retval TLE_UPDATE_ERR_ADCS: error setting the TLE params in the ADCS
 */
tle_update_err_t TleUpdateFromFile(const char *file_name);

#endif    /* DATACACHE_H */
/* ******************************************************************************************* */
