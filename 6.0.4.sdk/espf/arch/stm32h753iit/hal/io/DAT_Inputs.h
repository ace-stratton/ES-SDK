/*!
********************************************************************************************
* @file DAT_Inputs.h
* @brief Header of DAT_Inputs.c
********************************************************************************************
* @author            Kolio
* @version           1.0.0
* @date              2018.07.04
*
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
* @history
* @revision{         1.0.0  , 2018.07.04, author Kolio, Initial revision }
* @endhistory
********************************************************************************************
*/
#ifndef DAT_INPUTS_H
#define DAT_INPUTS_H

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "User_types.h"
#include "ais328dq_driver.h"
#include "LIS3MDL_MAG_driver.h"
#include "adis16265_driver.h"

#include <stdint.h>

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/

#define LIS3MDL_4GAUSS_LSB  ((double)(1.00/6842.00))
#define LIS3MDL_8GAUSS_LSB  ((double)(1.00/3421.00))
#define LIS3MDL_12GAUSS_LSB ((double)(1.00/2281.00))
#define LIS3MDL_16GAUSS_LSB ((double)(1.00/1711.00))

#define LIS3MDL_CONV_GAUSS_TO_TESLA ((double)0.0001)
#define LIS3MDL_CONV_GAUSS_TO_nTESLA ((double)100000)

/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/

typedef enum tag_MagnetoDataFormat {
    MAGNETODATAFORMAT_RAW,
    MAGNETODATAFORMAT_GAUSS,
    MAGNETODATAFORMAT_nTESLA,
    MAGNETODATAFORMAT_TESLA,
    MAGNETODATAFORMAT_MAX
} eMagnetoDataFormat_t;

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/
/* No External variables declarations */

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS 
*********************************************************************************************
*/
ES_ReturnType Magnitometers_LIS3MDL_Init(uint8_t Dev_No);
ES_ReturnType Magnitometers_LIS3MDL_Read_Data (Compass_Axis_t *MagOutData, uint8_t Dev_No, eMagnetoDataFormat_t u8DataFormat);

#endif    /* DAT_INPUTS_H */
/* **************************************************************************************** */
