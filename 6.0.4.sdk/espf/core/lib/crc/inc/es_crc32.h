/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __ES_CRC32_H
#define __ES_CRC32_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup crc Cyclic Redundancy Check
 * @{
 * Tools to calculate different CRC that are used in the SW platform
 *
 * @file    es_crc32.h
 * @brief   This file contains the crc32 function definitions.
 *
 * @}
 * @}
 *
 */

#define CRC32_POLY                  ((DWORD)0x04C11DB7)                  /* where 104C11DB7 is a common CRC32 generator polynomial*/
#define CRC32_INIT_REMAINDER        ((DWORD)0x00000000)
#define CRC32_FINAL_XOR_VALUE       ((DWORD)0xFFFFFFFF)

#include "integer.h"

extern   DWORD crc32_tab[];

/**
* @brief Calculate CRC32 checksum over given data length with a parameter for init value of the checksum
* @param init: initial value for the remainder
* @param ptr: pointer to data first byte
* @param size: size of data to calculate the checksum for
*
* @return checksum value
* @note Used polynomial is 0x04C11DB7. Implementation is standard table algorithm
*       with reflection and byte reversal. Implementation details borrowed from literature.
*/
DWORD crc32(DWORD crc, BYTE *buf, DWORD size);
         
static __inline DWORD crc32_inline(DWORD crc, BYTE buf)
{
    crc = ~crc;
	return ~( crc32_tab[ (BYTE)crc ^ buf ] ^ ( crc >> 8) );
}

#endif
