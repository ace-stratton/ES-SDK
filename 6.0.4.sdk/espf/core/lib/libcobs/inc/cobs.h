/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
*/
#ifndef COBS_H
#define COBS_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup lib_cobs COBS codec
 * @{
 *
 * The library provides an efficient way to implement data framing without much overhead and
 * decode it back. See [here](https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing) for
 * more details on the exact algorithm.
 *
 * @file cobs.h
 * @brief Basic [COBS](https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing)
 * (Consistent Overhead Byte Stuffing) algorithm encoder/decoder library.
 *
 * @}
 * @}
 */

#include <stdint.h>

/**
 * @brief Encodes a user-provided buffer using the COBS algorithm and provides the
 * encoded output.
 *
 * @param[in] input A pointer to the user buffer which must be encoded
 * @param[in] length Length of the data pointed to by the #input parameter
 * @param[out] output A pointer to the user buffer to receive the encoded data
 * @return Number of bytes written to #output
 */
uint32_t cobs_encode(const uint8_t * input, uint32_t length, uint8_t * output);

/**
 * @brief Decodes a user-provided COBS-encoded buffer and provides the
 * decoded output.
 *
 * @param[in] input A pointer to a COBS-encoded user buffer
 * @param[in] length Length of the data pointed to by the #input parameter
 * @param[out] output A pointer to the user buffer to receive the decoded data
 * @return Number of bytes written to #output
 */
uint32_t cobs_decode(const uint8_t * input, uint32_t length, uint8_t * output);

#endif
