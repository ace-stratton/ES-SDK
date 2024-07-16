/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef COBS_INPLACE_H_
#define COBS_INPLACE_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @addtogroup libcobs_inplace
 * @{
 * Provides implementation of the Inplace Consistent Overhead Byte Stuffing (COBS) algorithm
 *
 * @file cobs_inplace.h
 * @brief based on https://github.com/charlesnicholson/nanocobs
 *
 * @}
 * @}
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>

/**
 * @addtogroup libcobs_inplace
 * @{
 */

/**
 * @addtogroup public_macros
 * @{
 */

/*
 * @brief In-place encoding mandatory placeholder byte values.
 */
#define COBS_INPLACE_SENTINEL_VALUE     0x5A

/*
 * @brief All COBS frames end with this value. If you're scanning a data source
 *        for frame delimiters, the presence of this zero byte indicates the
 *        completion of a frame.
 */
#define COBS_INPLACE_FRAME_DELIMITER    0x00

/*
 * @brief In-place encodings that fit in a buffer of this size will always succeed.
 */
#define COBS_INPLACE_SAFE_BUFFER_SIZE   256

/**
 * @}
 */

/**
 * @addtogroup public_types
 * @{
 */

typedef unsigned cobs_inplace_sz_t;

/**
 * @}
 */

/**
 * @addtogroup public_functions
 * @{
 */

/*
 * @brief Encode in-place the contents of the provided buffer |buf| of length |len|.
 *        Returns True on successful encoding.
 *
 *        Because encoding adds leading and trailing bytes, your buffer must reserve
 *        bytes 0 and len-1 for the encoding. If the first and last bytes of |buf|
 *        are not set to COBS_INPLACE_SENTINEL_VALUE, the function will fail with
 *        False.
 *
 *        If a null pointer or invalid length are provided, the function will fail
 *        with False.
 *
 *        If |len| is less than or equal to COBS_INPLACE_SAFE_BUFFER_SIZE, the
 *        contents of |buf| will never cause encoding to fail. If |len| is larger
 *        than COBS_INPLACE_SAFE_BUFFER_SIZE, encoding can possibly fail with
 *        False if there are more than 254 bytes between zeros.
 *
 *        If the function returns False, the contents of |buf| are
 *        left indeterminate and must not be relied on to be fully encoded or decoded.
 */
bool cobs_inplace_encode(void* buf, cobs_inplace_sz_t len);


/*
 * @brief Decode in-place the contents of the provided buffer |buf| of length |len|.
 *        Returns True on successful decoding.
 *
 *        Because decoding is in-place, the first and last bytes of |buf| will be set
 *        to the value COBS_INPLACE_SENTINEL_VALUE if decoding succeeds. The decoded
 *        contents are stored in the inclusive span defined by buf[1] and buf[len-2].
 *
 *        If a null pointer or invalid length are provided, the function will fail
 *        with False.
 *
 *        If the encoded buffer contains any code bytes that exceed |len|, the
 *        function will fail with False. If the buffer starts
 *        with a 0 byte, or ends in a nonzero byte, the function will fail with
 *        False.
 *
 *        If the function returns False, the contents of |buf| are
 *        left indeterminate and must not be relied on to be fully encoded or decoded.
 */
bool cobs_inplace_decode(void* buf, const cobs_inplace_sz_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* COBS_INPLACE_H_ */
