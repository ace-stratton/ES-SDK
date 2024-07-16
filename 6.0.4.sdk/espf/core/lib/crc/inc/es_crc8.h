/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ES_CRC8_H
#define ES_CRC8_H

/**
 * @addtogroup crc
 * @{
 *
 * @file    ces_crc8.h
 * @brief   Header of es_crc8.c
 *
 * @}
 */

#include "main.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/

#define CRC8_POLY                  ((uint8_t)0x91)                      /* Used CRC8 polynomial */
/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/

extern uint8_t crc8_tab[];

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/

/**
* @brief Calculate CRC8 of a sequence of bytes
* @param buf: pointer to the data
* @param size: number of data bytes to calculate for
* @param bEsc: escape escape character
* @param u8EsC: escape character
* @return the calculated crc
* @note This function is taken from CubeADCS documentation and is used to send
*        commands and receive data with CRC8 from the CubeADCS
*********************************************************************************************
*/
extern uint8_t crc8(uint8_t *buf, uint16_t size, uint8_t bEsc, uint8_t u8EsC);

#endif /* ES_CRC8_H */
