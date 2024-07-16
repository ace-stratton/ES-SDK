/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_CRC_H_
#define CUBEADCS_CRC_H_

/**
 * @addtogroup cubeadcs
 * @{
 *
 * @file     cubeadcs_crc.h
 * @brief    Interface of CRC calculations implementation specific to the CubeADCS. Used internally.
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/

#include <stdint.h>

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/

/** @brief Used CRC8 polynomial */
#define CUBEADCS_CRC_CRC8_POLY  ((uint8_t)0x91)
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

/** @brief CRC8 Table used in the CRC8 calculation */
extern const uint8_t CubeADCS_CRC_8_Tab[256];

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/

/** @brief Calculate CRC8 of a sequence of bytes
 *  @param[in] buf pointer to the data
 *  @param[in] size number of data bytes to calculate the CRC for
 *
 *  @return the calculated CRC8
 *
 *  @note This function is a direct implementation as provided by CubeADCS documentation.
 *  	  It is used for TC/TLM with the CubeADCS module over the used interface.
 */
uint8_t CubeADCS_CRC_8(uint8_t *buf, uint16_t size);


/** @brief Calculate CRC16 of a sequence of bytes
 *  @param[in] u8Start pointer to the data
 *  @param[in] u8Len number of data bytes to calculate the CRC for
 *
 *  @return the calculated CRC16
 *
 *  @note This function is based on CubeADCS's documentation and is used in the file
 *        transfer procedures requiring a CRC16 check
 */
uint16_t CubeADCS_CRC_16(uint8_t *u8Start, uint32_t u8Len);

/** @brief Update an existing CRC16 calculation when a new byte is added to the data pool
 *  @param[in] u16Crc existing CRC16 calculation
 *  @param[in] u8Data the new byte added to the pool used for the CRC16 calculation
 *
 *  @return the calculated CRC16
 *
 *  @note This function is based on CubeADCS's documentation and is used in the file
 *        transfer procedures requiring a CRC16 check.
 */
uint16_t CubeADCS_Calculate_Single_CRC_16(uint16_t u16Crc, uint8_t u8Data);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_CRC_H_ */

/* ******************************************************************************************* */

