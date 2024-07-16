/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CBUF_H_
#define CBUF_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @addtogroup libcbuf
 * @{
 * Provides a circular buffer generic operations.
 *
 * @warning The library is reentrant but not thread-safe and special care must be taken
 * to protect instances in a multi-threaded environment.
 *
 * @file cbuf.h
 * @brief Simple circular buffer operations library.
 *
 * @}
 * @}
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>

/**
 * @addtogroup libcbuf
 * @{
 */

/**
 * @addtogroup types
 * @{
 */

/**
 * @brief Defines a circular buffer type
 */
typedef struct
{
    uint32_t head;     /**< circular buffer 'head' */
    uint32_t tail;     /**< circular buffer 'tail' */
    uint8_t* buf;      /**< working buffer */
    uint32_t buf_sz;   /**< working buffer size */
    uint32_t space;    /**< number of empty spaces in the working buffer */
} cbuf_t;

/**
 * @}
 */

/**
 * @addtogroup public_functions
 * @{
 */

/**
 * @brief Initialises a buffer.
 *
 * @param cbuf Circular buffer context
 */
void cbuf_init(cbuf_t* const cbuf, uint8_t* const buf, const uint32_t buf_sz);

/**
 * @brief Clears the buffer 'quick'.
 *
 * @param cbuf Circular buffer context
 */
void cbuf_clearq(cbuf_t* const cbuf);

/**
 * @brief Clears the buffer.
 *
 * @param cbuf Circular buffer context
 */
void cbuf_clear(cbuf_t* const cbuf);

/**
 * @brief Writes data to the buffer.
 *
 * @param cbuf Circular buffer context
 * @param data Buffer containing data to be written
 * @param data_sz Number of elements to write
 * @param overwrite Setting this parameter to true forces writing of data
 *                  even if it causes overwrite of unread data
 *
 * @return Written data size
 */
uint32_t cbuf_push(cbuf_t* const cbuf, const uint8_t* data, const uint32_t data_sz, const bool overwrite);

/**
 * @brief Reads data from the buffer.
 *
 * @param cbuf Circular buffer context
 * @param data Buffer to store read data
 * @param data_sz Number of elements to read
 *
 * @return Read data size
 */
uint32_t cbuf_pop(cbuf_t* const cbuf, uint8_t* const data, const uint32_t data_sz);

/**
 * @brief Reads data from the buffer without removing it.
 *
 * @param cbuf Circular buffer context
 * @param data Buffer to store read data
 * @param data_sz Number of elements to read
 *
 * @return Read data size
 */
uint32_t cbuf_peek(const cbuf_t* cbuf, uint8_t* const data, const uint32_t data_sz);

/**
 * @brief Releases a number of occupied buffer spaces.
 *
 * @param[in] cbuf Circular buffer context
 * @param[in] data_sz Number of elements to release
 *
 * @return Number of released buffer spaces
 */
uint32_t cbuf_free(cbuf_t* const cbuf, const uint32_t data_sz);

/**
 * @brief Gets total buffer capacity.
 *
 * @param[in] cbuf Circular buffer context
 *
 * @return total buffer capacity
 */
uint32_t cbuf_capacity(const cbuf_t* cbuf);

/**
 * @brief Gets the number of free elements in the buffer.
 *
 * @param[in] cbuf Circular buffer context
 *
 * @return Number of free elements in the buffer
 */
uint32_t cbuf_space(const cbuf_t* cbuf);

/**
 * @brief Gets the number of added elements in the buffer.
 *
 * @param[in] cbuf Circular buffer context
 *
 * @return Number of added elements in the buffer
 */
uint32_t cbuf_size(const cbuf_t* cbuf);

/**
 * @brief Checks if the buffer is full.
 *
 * @param[in] cbuf Circular buffer context
 *
 * @return true: buffer is full, false: buffer is not full
 */
bool cbuf_full(const cbuf_t* cbuf);

/**
 * @brief Checks if the buffer is empty.
 *
 * @param[in] cbuf Circular buffer context
 *
 * @return true: buffer is empty, false: buffer is not empty
 */
bool cbuf_empty(const cbuf_t* cbuf);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* CBUF_H_ */
