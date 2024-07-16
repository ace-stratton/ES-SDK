/**
  ******************************************************************************
  * @file    ff_gen_drv.h
  * @author  MCD Application Team
  * @brief   Header for ff_gen_drv.c module.
  *****************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
**/

/**
 * @addtogroup Middleware
 * @{
 */
/**
 * @addtogroup fatfs
 * @{
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FF_GEN_DRV_H
#define __FF_GEN_DRV_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "integer.h"
#include "ffconf.h"
#include "ff.h"
#include "diskio.h"
/* Exported types ------------------------------------------------------------*/

/**
  * @brief  Disk IO Driver structure definition. This is general diskio
  * structure. All disks in the system need to provide this interface
  * to be able to connect to the file system.
  */
typedef struct
{
  DRESULT (*disk_read)       ( BYTE*, DWORD, UINT);       /**< Read Sector(s)                            */
#if FF_USE_WRITE == 1
  DRESULT (*disk_write)      ( const BYTE*, DWORD, UINT); /**< Write Sector(s) when FF_USE_WRITE = 0       */
#endif /* FF_USE_WRITE == 1 */
#if FF_USE_IOCTL == 1
  DRESULT (*disk_ioctl)      ( BYTE, void*);              /**< I/O control operation when FF_USE_IOCTL = 1 */
#endif /* FF_USE_IOCTL == 1 */

}Diskio_drvTypeDef;

 extern const Diskio_drvTypeDef  SD_Driver;


/**
  * @brief  Global Disk Drivers structure definition
  */
typedef struct
{
  uint8_t                 is_initialized[FF_VOLUMES];
  const Diskio_drvTypeDef *drv[FF_VOLUMES];
  volatile uint8_t        nbr;

}Disk_drvTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Links a compatible diskio driver and increments the number of active
  *         linked drivers.
  * @note   The number of linked drivers (volumes) is up to 10 due to FatFs limits
  * @param  drv: pointer to the disk IO Driver structure
  * @param  fatfs: pointer to the FAT File System object.
  * @retval Returns 0 in case of success, otherwise 1.
  */
uint8_t FATFS_LinkDriver(const Diskio_drvTypeDef * const drv, FATFS * const fatfs);

/**
  * @brief  Unlinks a diskio driver and decrements the number of active linked
  *         drivers.
  * @param  fatfs: pointer to the FAT File System object.
  * @retval Returns 0 in case of success, otherwise 1.
  */
uint8_t FATFS_UnLinkDriver(FATFS* const fatfs);

/**
  * @brief  Links a compatible diskio driver/lun id and increments the number of active
  *         linked drivers.
  * @note   The number of linked drivers (volumes) is up to 10 due to FatFs limits.
  * @param  drv: pointer to the disk IO Driver structure
  * @param  fatfs: pointer to the FAT File System object.
  * @retval Returns 0 in case of success, otherwise 1.
  */
uint8_t FATFS_LinkDriverEx(const Diskio_drvTypeDef* const drv, FATFS* const fatfs);

/**
  * @brief  Unlinks a diskio driver and decrements the number of active linked
  *         drivers.
  * @param  fatfs: pointer to the FAT File System object.
  * @retval Returns 0 in case of success, otherwise 1.
  */
uint8_t FATFS_UnLinkDriverEx(FATFS* const fatfs);

/**
  * @brief  Gets number of linked drivers to the FatFs module.
  * @param  None
  * @retval Number of attached drivers.
  */
uint8_t FATFS_GetAttachedDriversNbr(void);

/**
 * @fn uint8_t FATFS_FindVolume(const Diskio_drvTypeDef* const, uint8_t* const)
 * @brief Finds the Volume ID to which the driver is linked.
 *
 * @param drv: pointer to the disk IO Driver structure
 * @param pVolume: pointer to returned value which is the found volume
 * @return Returns 0 in case of success, otherwise 1.
 */
uint8_t FATFS_FindVolume(const Diskio_drvTypeDef* const drv, uint8_t* const pVolume);

#ifdef __cplusplus
}
#endif

#endif /* __FF_GEN_DRV_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
 /**
  * @}
  * @}
  */
