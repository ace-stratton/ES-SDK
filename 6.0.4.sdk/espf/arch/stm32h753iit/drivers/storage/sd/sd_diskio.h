/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __SD_DISKIO_H
#define __SD_DISKIO_H
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup storage_sd SD Storage
 * @{
 *
 * Drivers for the micro SD card read and write operations.
 *
 * @file    sd_diskio.h
 * @brief   Header for sd_diskio.c module
 *
 * @}
 * @}
 */

#include "bsp_driver_sd.h"
#include "es_cdef.h"

/* Results of Disk Functions */
typedef enum {
    eRES_OK = 0,
    eRES_ERROR,
    eRES_NOT_READY,
    eRES_WRONG_PARAMS,
    eRES_NOT_INITIALIZED,
    eRES_COUNT
} SDRESULT;

/**
  * @fn SDRESULT SD_read_drv(uint8_t*, uint32_t, uint32_t)
  * @brief  Reads Sector(s)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval SDRESULT: Operation result
  */
SDRESULT SD_read_drv(uint8_t *buff, uint32_t sector, uint32_t count);

/**
 * @fn bool SD_initialize(void)
 * @brief  Initializes SD Drive
 *
 * @return true - successful initialization
 *         false - not successfully initialized
 */
bool SD_initialize (void);

/**
 * @fn bool SD_IsInitialized(void)
 * @brief Checks if the SD is already initialized.
 *
 * @return true in case the SD card is initialized, false otherwise.
 */
bool SD_IsInitialized(void);

/**
  * @fn SDRESULT SD_read(uint8_t* const, uint32_t, uint32_t)
  * @brief  Read sectors on SD card with reinit retries on error
  *
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval SDRESULT: eRES_OK - on success
  *                   eRES_ERROR - in case of problem while reading
  */
SDRESULT SD_read(uint8_t* const buff, uint32_t sector, uint32_t count);

/**
 * @fn SDRESULT SD_write(const uint8_t*, uint32_t, uint32_t)
 * @brief Write sectors on SD card with reinit retries on error
 *
 * @param buff - Pointer to the buffer that will contain the data to write
 * @param sector - Sector address from where to write(LBA)
 * @param count - Number of sectors to write
 * @return eRES_OK - on success
  *        eRES_ERROR - in case of problem while writing
 */
SDRESULT SD_write(const uint8_t* buff, uint32_t sector, uint32_t count);

/**
 * @fn SDRESULT SD_GetSectorCount(uint32_t* const)
 * @brief  used to provide the Sectors count
 *
 * @param fp_pSectorCount - output parameter for sector count
 * @return eRES_OK - in case the operation is successful
 *         eRES_NOT_READY - in case the driver is not initialized.
 */
SDRESULT SD_GetSectorCount(uint32_t* const fp_pSectorCount);

/**
 * @fn SDRESULT SD_GetSectorSize(uint32_t* const)
 * @brief used to provide the Sector size
 *
 * @param fp_pSize - output parameter for sector size.
 * @return eRES_OK - in case the operation is successful
 *         eRES_NOT_READY - in case the driver is not initialized.
 */
SDRESULT SD_GetSectorSize(uint32_t* const fp_pSize);

/**
 * @fn SDRESULT SD_GetBlockSize(uint32_t* const)
 * @brief used to provide the block size
 *
 * @param fp_pBlockSize - output parameter for block size.
 * @return eRES_OK - in case the operation is successful
 *         eRES_NOT_READY - in case the driver is not initialized.
 */
SDRESULT SD_GetBlockSize(uint32_t* const fp_pBlockSize);



#endif /* __SD_DISKIO_H */
