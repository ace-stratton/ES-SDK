/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ES_ES_LZ77_H
#define ES_ES_LZ77_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup liblz77 LZ77
 * @{
 *
 * Simple Hashing LZ77 Sliding Dictionary Compression
 *
 * @file es_lz77.h
 * @brief Public interface for the LZ77 library
 *
 * @}
 * @}
 */

#define LZ77_ERROR_OK      0
#define LZ77_ERROR_TIMEOUT 1
#define LZ77_ERROR_LOCK    2
#define LZ77_ERROR_FILE    3
#define LZ77_ERROR_OP      4

/**
 * @brief Initialize the memory dependencies of the library
 */
extern void LZ77_Init(void);

/**
 * @brief Compress a file located in the SD card
 * @param name_in: name/path of the input file to be compressed
 * @param name_in: name/path of the compressed file to be saved
 * @param timeout: timeout to wait in ms before exiting
 *
 * @retval LZ77_ERROR_OK: operation completed succesfully
 * @retval LZ77_ERROR_TIMEOUT: timeout before the operation could be performed
 * @retval LZ77_ERROR_LOCK: could not acquire the mutex
 * @retval LZ77_ERROR_FILE: did not find the input file or could not write the output file
 */
extern int LZ77_Compress(char *name_in, char *name_out, uint32_t timeout);

/**
 * @brief Decompress a file located in the SD card
 * @param name_in: name/path of the input file to be decompressed
 * @param name_in: name/path of the decompressed file to be saved
 * @param timeout: timeout to wait in ms before exiting
 *
 * @retval LZ77_ERROR_OK: operation completed succesfully
 * @retval LZ77_ERROR_TIMEOUT: timeout before the operation could be performed
 * @retval LZ77_ERROR_LOCK: could not acquire the mutex
 * @retval LZ77_ERROR_FILE: did not find the input file or could not write the output file
 */
extern int LZ77_Decompress(char *name_in, const char *name_out, uint32_t timeout);

#endif
