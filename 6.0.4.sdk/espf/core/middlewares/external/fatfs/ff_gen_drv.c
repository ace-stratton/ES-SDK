/**
  ******************************************************************************
  * @file    ff_gen_drv.c
  * @author  MCD Application Team
  * @brief   FatFs generic low level driver.
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
/* Includes ------------------------------------------------------------------*/
#include "es_cdef.h"
#include "ff_gen_drv.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Disk_drvTypeDef disk = {{0},{0},0};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

uint8_t FATFS_LinkDriverEx(const Diskio_drvTypeDef* const drv, FATFS* const fatfs)
{
  uint8_t ret = 1;

  if(disk.nbr < FF_VOLUMES)
  {
    fatfs->drv = (void *)drv;
    disk.is_initialized[disk.nbr] = 0;
    disk.drv[disk.nbr] = drv;
    disk.nbr++;
    ret = 0;
  }

  return ret;
}

uint8_t FATFS_LinkDriver(const Diskio_drvTypeDef* const drv, FATFS* const fatfs)
{
  return FATFS_LinkDriverEx(drv, fatfs);
}

uint8_t FATFS_UnLinkDriverEx( FATFS * const fatfs)
{
  uint8_t DiskNum = 0;
  uint8_t ret = 1;
  FRESULT fr = FR_OK;

  if(disk.nbr >= 1)
  {
    fr = FATFS_FindVolume(fatfs->drv, &DiskNum);

    if ( (FR_OK == fr)
          && (disk.drv[DiskNum] != 0) )
    {
        fatfs->drv = 0;
        disk.drv[DiskNum] = 0;
        disk.nbr--;
        ret = 0;
    }
  }

  return ret;
}

uint8_t FATFS_UnLinkDriver(FATFS* const fatfs)
{
  return FATFS_UnLinkDriverEx(fatfs);
}

uint8_t FATFS_GetAttachedDriversNbr(void)
{
  return disk.nbr;
}

FRESULT FATFS_FindVolume(const Diskio_drvTypeDef* const drv, uint8_t * const pVolume)
{
    FRESULT res = FR_INVALID_PARAMETER;
    bool found = false;

    if ((NULL != drv)
       && (NULL != pVolume))
    {
        *pVolume = 0;

        while ( (!found)
                && (*pVolume <= FF_VOLUMES)
               )
        {
            if (disk.drv[*pVolume] == drv)
            {
                found = true;
                res = FR_OK;
            }
            else
            {
                (*pVolume)++;
            }
        }

        if (!found)
        {
            res = FR_INVALID_DRIVE; // In case we don't find the file system. This shall not be possible.
        }
    }

    return res;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

