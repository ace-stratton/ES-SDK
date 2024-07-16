/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup tle
 * @{
 *
 * @file TleUpdate.c
 * @brief Stores runtime operational data supplied by other components in the system.
 *
 * @}
 */

#include "SdMngr.h"

#include "TleUpdate.h"
#include "cubeadcs.h"
#include "string.h"
#include "cubeadcs.h"
#include "if_sys_conf.h"

tle_update_err_t TleUpdateFromFile(const char *file_name)
{
    FIL fileHandle;
    sgp4_two_line_element_t tle;
    sgp4_parsed_two_line_element_t  parsed_tle;
    CubeADCS_SGP4_Orbit_Params_t orbit_params;

	if (file_name == NULL)
		return TLE_UPDATE_ERR_FILE;

	if (SdMngr_f_open(&fileHandle, (const TCHAR *)file_name, FA_OPEN_EXISTING | FA_READ) != FR_OK)
	{
		return TLE_UPDATE_ERR_FILE;
	}

	memset(tle.line, 0, sizeof(tle.line));
	if (SdMngr_f_gets((TCHAR *)&(tle.line[0]), SGP4_TLE_CHARS_PER_LINE+4, &fileHandle) == NULL)
	{
		SdMngr_f_close(&fileHandle);
		return TLE_UPDATE_ERR_FILE;
	}
	tle.line[0][SGP4_TLE_CHARS_PER_LINE] = 0;

	if (SdMngr_f_gets((TCHAR *)&(tle.line[1]), SGP4_TLE_CHARS_PER_LINE+4, &fileHandle) == NULL)
	{
		SdMngr_f_close(&fileHandle);
		return TLE_UPDATE_ERR_FILE;
	}
	tle.line[1][SGP4_TLE_CHARS_PER_LINE] = 0;

	SdMngr_f_close(&fileHandle);

	if (sgp4_tle_verify_format(&tle) != SGP4_OK)
		return TLE_UPDATE_ERR_SGP4;

	if (sgp4_tle_verify_checksum(&tle) != SGP4_OK)
		return TLE_UPDATE_ERR_SGP4;

	if (sgp4_tle_parse(&tle, &parsed_tle, false) != SGP4_OK)
		return TLE_UPDATE_ERR_SGP4;

	orbit_params.dInc   = parsed_tle.incl;     // Inclination
	orbit_params.dEcc   = parsed_tle.ecc;      // Eccentricity
	orbit_params.dRAAN  = parsed_tle.raan;     // Right-ascension of the Ascending Node
	orbit_params.dAOP   = parsed_tle.aop;      // Argument of perigee
	orbit_params.dBStar = parsed_tle.bstar;    // B-Star drag term
	orbit_params.dMeanM = parsed_tle.mmotion;  // Mean Motion
	orbit_params.dMeanA = parsed_tle.manomaly; // Mean Anomaly
	orbit_params.dEpoch = parsed_tle.epoch;    // Epoch

	if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
	{
	    if (CubeADCS_SetSGP4OrbitParams(&orbit_params) != eCUBEADCS_STDRPLY_OK)
	        return TLE_UPDATE_ERR_ADCS;
	}
	else
	{
	    (void)orbit_params;
	}

	return TLE_UPDATE_OK;
}
