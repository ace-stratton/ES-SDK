/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_crc.c
 * @brief    Functions used to calculate the CRCs used throughout the CubeADCS logic.
 *
 * @}
 */

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "../inc/cubeadcs_crc.h"

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/
const uint8_t CubeADCS_CRC_8_Tab[256] = {
        0x00, 0x41, 0x13, 0x52, 0x26, 0x67,
        0x35, 0x74, 0x4C, 0x0D, 0x5F, 0x1E,
        0x6A, 0x2B, 0x79, 0x38, 0x09, 0x48,
        0x1A, 0x5B, 0x2F, 0x6E, 0x3C, 0x7D,
        0x45, 0x04, 0x56, 0x17, 0x63, 0x22,
        0x70, 0x31, 0x12, 0x53, 0x01, 0x40,
        0x34, 0x75, 0x27, 0x66, 0x5E, 0x1F,
        0x4D, 0x0C, 0x78, 0x39, 0x6B, 0x2A,
        0x1B, 0x5A, 0x08, 0x49, 0x3D, 0x7C,
        0x2E, 0x6F, 0x57, 0x16, 0x44, 0x05,
        0x71, 0x30, 0x62, 0x23, 0x24, 0x65,
        0x37, 0x76, 0x02, 0x43, 0x11, 0x50,
        0x68, 0x29, 0x7B, 0x3A, 0x4E, 0x0F,
        0x5D, 0x1C, 0x2D, 0x6C, 0x3E, 0x7F,
        0x0B, 0x4A, 0x18, 0x59, 0x61, 0x20,
        0x72, 0x33, 0x47, 0x06, 0x54, 0x15,
        0x36, 0x77, 0x25, 0x64, 0x10, 0x51,
        0x03, 0x42, 0x7A, 0x3B, 0x69, 0x28,
        0x5C, 0x1D, 0x4F, 0x0E, 0x3F, 0x7E,
        0x2C, 0x6D, 0x19, 0x58, 0x0A, 0x4B,
        0x73, 0x32, 0x60, 0x21, 0x55, 0x14,
        0x46, 0x07, 0x48, 0x09, 0x5B, 0x1A,
        0x6E, 0x2F, 0x7D, 0x3C, 0x04, 0x45,
        0x17, 0x56, 0x22, 0x63, 0x31, 0x70,
        0x41, 0x00, 0x52, 0x13, 0x67, 0x26,
        0x74, 0x35, 0x0D, 0x4C, 0x1E, 0x5F,
        0x2B, 0x6A, 0x38, 0x79, 0x5A, 0x1B,
        0x49, 0x08, 0x7C, 0x3D, 0x6F, 0x2E,
        0x16, 0x57, 0x05, 0x44, 0x30, 0x71,
        0x23, 0x62, 0x53, 0x12, 0x40, 0x01,
        0x75, 0x34, 0x66, 0x27, 0x1F, 0x5E,
        0x0C, 0x4D, 0x39, 0x78, 0x2A, 0x6B,
        0x6C, 0x2D, 0x7F, 0x3E, 0x4A, 0x0B,
        0x59, 0x18, 0x20, 0x61, 0x33, 0x72,
        0x06, 0x47, 0x15, 0x54, 0x65, 0x24,
        0x76, 0x37, 0x43, 0x02, 0x50, 0x11,
        0x29, 0x68, 0x3A, 0x7B, 0x0F, 0x4E,
        0x1C, 0x5D, 0x7E, 0x3F, 0x6D, 0x2C,
        0x58, 0x19, 0x4B, 0x0A, 0x32, 0x73,
        0x21, 0x60, 0x14, 0x55, 0x07, 0x46,
        0x77, 0x36, 0x64, 0x25, 0x51, 0x10,
        0x42, 0x03, 0x3B, 0x7A, 0x28, 0x69,
        0x1D, 0x5C, 0x0E, 0x4F
};

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/

uint8_t CubeADCS_CRC_8(uint8_t *buf, uint16_t size)
{
    if ( size == 0 )
        return 0xFF;

    uint16_t i;
    uint8_t  crc = 0;

    for ( i = 0; i < size; i++ ) {
        crc = CubeADCS_CRC_8_Tab[ crc ^ buf[i] ];
    }

    return crc;

}

uint16_t CubeADCS_CRC_16(uint8_t *u8Start, uint32_t u8Len)
{
    uint8_t *u8Data;
    uint8_t *u8End = u8Start + u8Len;

    uint16_t u16Crc = 0;

    for (u8Data = u8Start; u8Data < u8End; u8Data++)
        CubeADCS_Calculate_Single_CRC_16(u16Crc, *u8Data);

    return u16Crc;
}

uint16_t CubeADCS_Calculate_Single_CRC_16(uint16_t u16Crc, uint8_t u8Data)
{
    u16Crc  = (u16Crc >> 8) | (u16Crc << 8);
    u16Crc ^= u8Data;
    u16Crc ^= (u16Crc & 0xff) >> 4;
    u16Crc ^=  u16Crc << 12;
    u16Crc ^= (u16Crc & 0xff) << 5;

    return u16Crc;
}

/* ******************************************************************************************* */
