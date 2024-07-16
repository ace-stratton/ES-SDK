/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2017        */
/*                                                                       */
/*   Portions COPYRIGHT 2017 STMicroelectronics                          */
/*   Portions Copyright (C) 2017, ChaN, all right reserved               */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various existing      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "integer.h"
#include "diskio.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include "assert.h"

#if defined ( __GNUC__ )
#ifndef __weak
#define __weak __attribute__((weak))
#endif
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// table for mapping the results returned by the SD driver to those needed by the FATFS
const DRESULT pResultMap[eRES_COUNT] = {RES_OK, RES_ERROR, RES_NOTRDY, RES_WRPRT, RES_NOTRDY };

extern Disk_drvTypeDef  disk;

/* Private function prototypes -----------------------------------------------*/

/**
 * @fn DRESULT sd_disk_read_wrapper(BYTE*, DWORD, UINT)
 * @brief Wrapper of SD Disk Read function to general diskio interface.
 *
 * @param buff - Pointer to the buffer that will contain the read data
 * @param sector - Sector address from where to read(LBA)
 * @param count - Number of sectors to read
 * @return
 */
static DRESULT sd_disk_read_wrapper(BYTE* buff, DWORD sector, UINT count);

/**
 * @fn DRESULT sd_disk_write_wrapper(const BYTE*, DWORD, UINT)
 * @brief Wrapper of SD Disk Write function to general diskio interface.
 *
 * @param buff - Pointer to the buffer that will contain the data to write
 * @param sector - Sector address from where to write(LBA)
 * @param count - Number of sectors to write
 * @return RES_OK: Successful execution of IO command.
 *         RES_ERROR: R/W Error
 */
static DRESULT sd_disk_write_wrapper(const BYTE* buff, DWORD sector, UINT count);

/**
 * @fn DRESULT sd_disk_ioctl_wrapper(BYTE, void*)
 * @brief Wrapper of SD Disk IO functions to general diskio interface.
 *
 * @param cmd - IO command id. Commands are defined in diskio.h provided by the
 * FATFS module
 * @param buff - pointer to be used by the IO command.
 * @return  RES_OK: Successful execution of IO command.
            RES_ERROR: R/W Error
            RES_WRPRT: Write Protected
            RES_NOTRDY: Not Ready
            RES_PARERR: Invalid Parameter
 */
static DRESULT sd_disk_ioctl_wrapper(BYTE cmd, void *buff);


const Diskio_drvTypeDef  SD_Driver =
{
        sd_disk_read_wrapper,
#if  FF_USE_WRITE == 1
        sd_disk_write_wrapper,
#endif /* FF_USE_WRITE == 1 */

#if  FF_USE_IOCTL == 1
        sd_disk_ioctl_wrapper,
#endif /* FF_USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/
static DRESULT sd_disk_write_wrapper(const BYTE* buff, DWORD sector, UINT count)
{
    SDRESULT res = eRES_WRONG_PARAMS;

    static_assert(sizeof(BYTE)==sizeof(uint8_t));
    static_assert(sizeof(sector)==sizeof(uint32_t));
    static_assert(sizeof(count)==sizeof(uint32_t));

    if (NULL != buff)
    {
        res = SD_write(buff, sector, count);
    }

    return pResultMap[res];
}

static DRESULT sd_disk_read_wrapper(BYTE* buff, DWORD sector, UINT count)
{
    SDRESULT res = eRES_WRONG_PARAMS;

    static_assert(sizeof(BYTE)==sizeof(uint8_t));
    static_assert(sizeof(sector)==sizeof(uint32_t));
    static_assert(sizeof(count)==sizeof(uint32_t));

    if (NULL != buff)
    {
        res = SD_read(buff, sector, count);
    }

    return pResultMap[res];
}

static DRESULT sd_disk_ioctl_wrapper(uint8_t cmd, void *buff)
{
  SDRESULT sd_res = eRES_WRONG_PARAMS;

  if ( (CTRL_SYNC == cmd)
       || (NULL != buff) )
  {
      switch (cmd)
      {
      /* Make sure that no pending write process */
      case CTRL_SYNC :
          sd_res = eRES_OK;
        break;

      /* Get number of sectors on the disk (uint32_t) */
      case GET_SECTOR_COUNT :
          sd_res = SD_GetSectorCount(buff);
        break;

      /* Get R/W sector size (uint16_t) */
      case GET_SECTOR_SIZE :
          sd_res = SD_GetSectorSize(buff);
        break;

      /* Get erase block size in unit of sector (uint32_t) */
      case GET_BLOCK_SIZE :
          sd_res = SD_GetBlockSize(buff);
        break;
      case IOCTL_INIT:
      {
          bool bIsInitialized = SD_initialize();
          if (bIsInitialized)
          {
              *(DSTATUS*)buff = 0;
              sd_res = eRES_OK;
          }
          else
          {
              *(DSTATUS*)buff = (DSTATUS)STA_NOINIT;
              sd_res = eRES_ERROR;
          }
        break;
      }
      case IOCTL_STATUS:
      {
          bool bIsInitialized = SD_IsInitialized();
          if (bIsInitialized)
          {
              *(DSTATUS*)buff = (DSTATUS)0;
              sd_res = eRES_OK;
          }
          else
          {
              *(DSTATUS*)buff = (DSTATUS)STA_NOINIT;
              sd_res = eRES_ERROR;
          }
        break;
      }
      default:
          sd_res = eRES_WRONG_PARAMS;
      }
  }

  return pResultMap[sd_res];
}

/* Public functions ---------------------------------------------------------*/

/**
  * @brief  Implementation of the interface needed by FATFS for Reading Sector(s)
  * @param  drv: pointer to the physical drive driver
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT disk_read (
    void *drv,      /* pointer to the physical drive driver */
    BYTE *buff,     /* Data buffer to store read data */
    DWORD sector,           /* Sector address in LBA */
    UINT count      /* Number of sectors to read */
)
{
  DRESULT res = RES_PARERR;
  BYTE pdrv;

  if ( (NULL != drv)
       && (NULL != buff) )
  {
      res = RES_ERROR;
      FRESULT fr = FATFS_FindVolume(drv, &pdrv); // Physical drive nmuber (0..)

      if (FR_OK == fr)
      {
          res = disk.drv[pdrv]->disk_read(buff, sector, count);
      }
  }

  return res;
}

/**
  * @brief  Implementation of the interface needed by FATFS for Writing
  * Sector(s)
  * @param  drv: pointer to the physical drive driver
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if FF_USE_WRITE == 1
DRESULT disk_write (
    void *drv,      /* pointer to the physical drive driver */
    const BYTE *buff,   /* Data to be written */
    DWORD sector,       /* Sector address in LBA */
    UINT count          /* Number of sectors to write */
)
{
  DRESULT res = RES_PARERR;
  BYTE pdrv;

  if ( (NULL != drv)
       && (NULL != buff) )
  {
      res = RES_ERROR;
      FRESULT fr = FATFS_FindVolume(drv, &pdrv); // Physical drive nmuber (0..)

      if (FR_OK == fr)
      {
          res = disk.drv[pdrv]->disk_write(buff, sector, count);
      }
  }

  return res;
}
#endif /* FF_USE_WRITE == 1 */

/**
  * @brief  Implementation of the interface needed by FATFS for I/O control
  *  operation
  * @param  drv: pointer to the physical drive driver
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if FF_USE_IOCTL == 1
DRESULT disk_ioctl (
    void *drv,      /* pointer to the physical drive driver */
    BYTE cmd,       /* Control code */
    void *buff      /* Buffer to send/receive control data */
)
{
  DRESULT res = RES_PARERR;
  BYTE pdrv;

  if ( ((NULL != drv) && (NULL != buff))
       || (CTRL_SYNC == cmd)
       )
  {
      res = RES_ERROR;
      FRESULT fr = FATFS_FindVolume(drv, &pdrv); // Physical drive nmuber (0..)

      if (FR_OK == fr)
      {
          res = disk.drv[pdrv]->disk_ioctl(cmd, buff);
      }
  }

  return res;
}
#endif /* _USE_IOCTL == 1 */


/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
__weak DWORD get_fattime (void)
{
  return 0;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

