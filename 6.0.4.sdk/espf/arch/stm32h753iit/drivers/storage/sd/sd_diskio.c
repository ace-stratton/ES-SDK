/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup storage_sd
 * @{
 *
 * @file    sd_diskio.c
 * @brief   SD Disk I/O driver
 *
 * @}
 */


/* Includes ------------------------------------------------------------------*/
#include "sd_diskio.h"
#include "cmsis_os.h"
#include <string.h>
#include "MCU_Init.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define QUEUE_SIZE         (uint32_t) 10
#define READ_CPLT_MSG      (uint32_t) 1
#define WRITE_CPLT_MSG     (uint32_t) 2
/*
==================================================================
enable the defines below to send custom rtos messages
when an error or an abort occurs.
Notice: depending on the HAL/SD driver the HAL_SD_ErrorCallback()
may not be available.
See BSP_SD_ErrorCallback() and BSP_SD_AbortCallback() below
==================================================================

#define RW_ERROR_MSG       (uint32_t) 3
#define RW_ABORT_MSG       (uint32_t) 4
*/
/*
 * the following Timeout is useful to give the control back to the applications
 * in case of errors in either BSP_SD_ReadCpltCallback() or BSP_SD_WriteCpltCallback()
 * the value by default is as defined in the BSP platform driver otherwise 30 secs
 */
#define SD_TIMEOUT 2 * 1000

#define SD_DEFAULT_BLOCK_SIZE 512

/*
 * Depending on the use case, the SD card initialization could be done at the
 * application level: if it is the case define the flag below to disable
 * the BSP_SD_Init() call in the SD_Initialize() and add a call to
 * BSP_SD_Init() elsewhere in the application.
 */
/* USER CODE BEGIN disableSDInit */
/* Use  #define DISABLE_SD_INIT in case you need to disable the SD initialization */
/* USER CODE END disableSDInit */

/*
 * when using cacheable memory region, it may be needed to maintain the cache
 * validity. Enable the define below to activate a cache maintenance at each
 * read and write operation.
 * Notice: This is applicable only for cortex M7 based platform.
 */
/* USER CODE BEGIN enableSDDmaCacheMaintenance */
/* #define ENABLE_SD_DMA_CACHE_MAINTENANCE  1 */
/* USER CODE END enableSDDmaCacheMaintenance */

/*
* Some DMA requires 4-Byte aligned address buffer to correctly read/write data,
* in FatFs some accesses aren't thus we need a 4-byte aligned scratch buffer to correctly
* transfer data
*/
/* USER CODE BEGIN enableScratchBuffer */
#ifndef ENABLE_SCRATCH_BUFFER
#define ENABLE_SCRATCH_BUFFER
#define ENABLE_SD_DMA_CACHE_MAINTENANCE 0
#endif
/* USER CODE END enableScratchBuffer */

/* Private variables ---------------------------------------------------------*/
#if defined(ENABLE_SCRATCH_BUFFER)
#if defined (ENABLE_SD_DMA_CACHE_MAINTENANCE)
ALIGN_32BYTES(static uint8_t scratch[BLOCKSIZE]); // 32-Byte aligned for cache maintenance
#else
__ALIGN_BEGIN static uint8_t scratch[BLOCKSIZE] __ALIGN_END;
#endif
#endif

/* Disk status */
static bool bIsSdInitialized = false;

#if (osCMSIS <= 0x20000U)
static osMessageQId SDQueueID = NULL;
#else
static osMessageQueueId_t SDQueueID = NULL;
#endif

extern int RAM_D2_START_ADDRESS;    // import linker script symbol

/* Private function prototypes -----------------------------------------------*/
/**
 * @fn bool SD_CheckStatusWithTimeout(uint32_t)
 * @brief Checks if the SDCard is ready within the given timeout. In case it is
 * not ready it waits actively for that time.
 *
 * @param timeout time in milliseconds for active wait in case the SD Card is
 * currently occupied by ongoing operation.
 * @return true: in case the SD Card is in Transfer Mode in the time given as
 * timeout which means that it is ready for use.
 *        false: in case the SDCard is not ready even after the timeout is
 *         elapsed.
 *
 */
static bool SD_IsReadyWithTimeout(uint32_t timeout);

/**
 * @fn bool SD_IsReady(void)
 * @brief Check if the SD card is ready for use or it has some ongoing
 * operations.
 *
 * @return true in case the Card is in Transfer Mode which means that it is
 *  ready for use.
 */
static bool SD_IsReady(void);
/* USER CODE BEGIN beforeFunctionSection */
/* can be used to modify / undefine following code or add new code */
/* USER CODE END beforeFunctionSection */

/**
  * @brief  Writes Sector(s)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval SDRESULT: Operation result
  */
static SDRESULT SD_write_drv(const uint8_t *buff, uint32_t sector, uint32_t count);

/**
 * @fn void SD_reinit(void)
 * @brief re-initialization of the hardware used in case problems are detected
 * while reading or writing
 *
 */
static void SD_reinit(void);
/* Private functions ---------------------------------------------------------*/

static bool SD_IsReadyWithTimeout(uint32_t timeout)
{
  uint32_t timer;
  bool bRes = false;
  /* block until SDIO peripheral is ready again or a timeout occur */
#if (osCMSIS <= 0x20000U)
  timer = osKernelSysTick();
  while( osKernelSysTick() - timer < timeout)
#else
  timer = osKernelGetTickCount();
  while( osKernelGetTickCount() - timer < timeout)
#endif
  {
    if (BSP_SD_GetCardState() == SD_TRANSFER_OK)
    {
      bRes = true;
      break;
    }
  }

  return bRes;
}

static bool SD_IsReady(void)
{
    return (BSP_SD_GetCardState() == SD_TRANSFER_OK);
}

bool SD_IsInitialized(void)
{
    return bIsSdInitialized;
}

bool SD_initialize(void)
{
   bool bIsSdReady = false;

   bIsSdInitialized = false;

  /*
   * check that the kernel has been started before continuing
   * as the osMessage API will fail otherwise
   */
#if (osCMSIS <= 0x20000U)
  if(osKernelRunning())
#else
  if(osKernelGetState() == osKernelRunning)
#endif
  {
#if !defined(DISABLE_SD_INIT)

    if(BSP_SD_Init() == MSD_OK)
    {
        bIsSdReady = SD_IsReady();
    }

#else
    bIsSdReady = SD_IsReady();
#endif

    /*
    * if the SD is correctly initialized, create the operation queue
    * if not already created
    */

    if (bIsSdReady)
    {
      if (SDQueueID == NULL)
      {
 #if (osCMSIS <= 0x20000U)
      osMessageQDef(SD_Queue, QUEUE_SIZE, uint16_t);
      SDQueueID = osMessageCreate (osMessageQ(SD_Queue), NULL);
#else
      SDQueueID = osMessageQueueNew(QUEUE_SIZE, 2, NULL);
#endif
      }

      if (SDQueueID != NULL)
      {
          bIsSdInitialized = true;
      }
    }
  }

  return bIsSdInitialized;
}

/* USER CODE BEGIN beforeReadSection */
/* can be used to modify previous code / undefine following code / add new code */

static void SD_reinit(void)
{
    HAL_GPIO_WritePin(SD_EN_GPIO_Port, SD_EN_Pin, GPIO_PIN_SET);

    __HAL_RCC_SDMMC1_CLK_DISABLE();

    //RCC SDIO1 RESET
    __HAL_RCC_SDMMC1_FORCE_RESET();
    while( ( RCC->AHB3RSTR & RCC_AHB3RSTR_SDMMC1RST ) != RCC_AHB3RSTR_SDMMC1RST ){
        //wait for reset to happen
    }
    osDelay(1);
    __HAL_RCC_SDMMC1_RELEASE_RESET();
    while( ( RCC->AHB3RSTR & RCC_AHB3RSTR_SDMMC1RST ) == RCC_AHB3RSTR_SDMMC1RST ){
        //wait for reset to happen
    }

    osDelay(150);

    HAL_GPIO_WritePin(SD_EN_GPIO_Port, SD_EN_Pin, GPIO_PIN_RESET);

    __HAL_RCC_SDMMC1_CLK_ENABLE();
    osDelay(1);

    (void)HAL_SD_Init(&hsd1);

    osDelay(10);
}

/* USER CODE END beforeReadSection */
SDRESULT SD_read_drv(uint8_t *buff, uint32_t sector, uint32_t count)
{
  uint8_t ret = MSD_ERROR;
  SDRESULT res = eRES_ERROR;
  uint32_t timer;
#if (osCMSIS < 0x20000U)
  osEvent event;
#else
  uint16_t event;
  osStatus_t status;
#endif
#if (ENABLE_SD_DMA_CACHE_MAINTENANCE == 1)
  uint32_t alignedAddr;
#endif
  /*
  * ensure the SDCard is ready for a new operation
  */

  if (!SD_IsReadyWithTimeout(SD_TIMEOUT))
  {
    return eRES_NOT_READY;
  }

#if defined(ENABLE_SCRATCH_BUFFER)
  // for some reason, reading directly to memory in the D2 RAM region fails with SD DMA,
  // hence all reads to such regions are routed through the scratch buffer for now
  if ((uint32_t)0 == ((uint32_t)buff & (uint32_t)0x3)
	  && ((uint32_t) buff < (uint32_t) &RAM_D2_START_ADDRESS))
  {
#endif
    /* Fast path cause destination buffer is correctly aligned */
    ret = BSP_SD_ReadBlocks_DMA((uint32_t*)buff, sector, count);

    if (ret == MSD_OK) {
#if (osCMSIS < 0x20000U)
    /* wait for a message from the queue or a timeout */
    event = osMessageGet(SDQueueID, SD_TIMEOUT);

    if (event.status == osEventMessage)
    {
      if (event.value.v == READ_CPLT_MSG)
      {
        timer = osKernelSysTick();
        /* block until SDIO IP is ready or a timeout occur */
        while(osKernelSysTick() - timer <SD_TIMEOUT)
#else
          status = osMessageQueueGet(SDQueueID, (void *)&event, NULL, SD_TIMEOUT);
          if ((status == osOK) && (event == READ_CPLT_MSG))
          {
            timer = osKernelGetTickCount();
            /* block until SDIO IP is ready or a timeout occur */
            while(osKernelGetTickCount() - timer <SD_TIMEOUT)
#endif
            {
              if (BSP_SD_GetCardState() == SD_TRANSFER_OK)
              {
                res = eRES_OK;
#if (ENABLE_SD_DMA_CACHE_MAINTENANCE == 1)
                /*
                the SCB_InvalidateDCache_by_Addr() requires a 32-uint8_t aligned address,
                adjust the address and the D-Cache size to invalidate accordingly.
                */
                alignedAddr = (uint32_t)buff & ~0x1F;
                SCB_InvalidateDCache_by_Addr((uint32_t*)alignedAddr, count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));
#endif
                break;
              }
            }
#if (osCMSIS < 0x20000U)
          }
        }
#else
      }
#endif
    }

#if defined(ENABLE_SCRATCH_BUFFER)
    }
    else
    {
      /* Slow path, fetch each sector a part and memcpy to destination buffer */
      uint32_t i;

      for (i = 0; i < count; i++)
      {
        ret = BSP_SD_ReadBlocks_DMA((uint32_t*)scratch, sector, 1);
        sector++;
        if (ret == MSD_OK )
        {
          /* wait until the read is successful or a timeout occurs */
#if (osCMSIS < 0x20000U)
          /* wait for a message from the queue or a timeout */
          event = osMessageGet(SDQueueID, SD_TIMEOUT);

          if (event.status == osEventMessage)
          {
            if (event.value.v == READ_CPLT_MSG)
            {
              timer = osKernelSysTick();
              /* block until SDIO IP is ready or a timeout occur */
              while(osKernelSysTick() - timer <SD_TIMEOUT)
#else
                status = osMessageQueueGet(SDQueueID, (void *)&event, NULL, SD_TIMEOUT);
              if ((status == osOK) && (event == READ_CPLT_MSG))
              {
                timer = osKernelGetTickCount();
                /* block until SDIO IP is ready or a timeout occur */
                ret = MSD_ERROR;
                while(osKernelGetTickCount() - timer < SD_TIMEOUT)
#endif
                {
                  ret = BSP_SD_GetCardState();

                  if (ret == MSD_OK)
                  {
                    break;
                  }
                }

                if (ret != MSD_OK)
                {
                  break;
                }
#if (osCMSIS < 0x20000U)
              }
            }
#else
          }
#endif
#if (ENABLE_SD_DMA_CACHE_MAINTENANCE == 1)
          /*
          *
          * invalidate the scratch buffer before the next read to get the actual data instead of the cached one
          */
          SCB_InvalidateDCache_by_Addr((uint32_t*)scratch, BLOCKSIZE);
#endif
          memcpy(buff, scratch, BLOCKSIZE);
          buff += BLOCKSIZE;
        }
        else
        {
          break;
        }
      }

      if ((i == count) && (ret == MSD_OK ))
      {
        res = eRES_OK;
      }
    }
#endif
  return res;
}

/* USER CODE BEGIN beforeWriteSection */
/* can be used to modify previous code / undefine following code / add new code */


SDRESULT SD_read(uint8_t* const buff, uint32_t sector, uint32_t count)
{
	SDRESULT res = eRES_ERROR;

	for (uint32_t block = 0; block < count; block++)
    {
        for (uint8_t retry = 0; retry < SD_REINIT_MAX_RETRIES; retry++)
        {
            res = SD_read_drv(&buff[block*hsd1.SdCard.BlockSize], sector+block, 1);
            if (res != eRES_OK)
            {
                SD_reinit();
            } else
            {
                break;
            }
        }
        if (eRES_OK != res)
        {
            break;
        }
    }

    return res;
}

/* USER CODE END beforeWriteSection */
static SDRESULT SD_write_drv(const uint8_t *buff, uint32_t sector, uint32_t count)
{
  SDRESULT res = eRES_ERROR;
  uint32_t timer;

#if (osCMSIS < 0x20000U)
  osEvent event;
#else
  uint16_t event;
  osStatus_t status;
#endif

#if defined(ENABLE_SCRATCH_BUFFER)
  uint8_t ret = MSD_ERROR;
#endif

  /*
  * ensure the SDCard is ready for a new operation
  */

  if (!SD_IsReadyWithTimeout(SD_TIMEOUT))
  {
    return eRES_NOT_READY;
  }

#if defined(ENABLE_SCRATCH_BUFFER)
  if ((uint32_t)0 == ((uint32_t)buff & (uint32_t)0x3))
  {
#endif
#if (ENABLE_SD_DMA_CACHE_MAINTENANCE == 1)
  uint32_t alignedAddr;
  /*
    the SCB_CleanDCache_by_Addr() requires a 32-uint8_t aligned address
    adjust the address and the D-Cache size to clean accordingly.
  */
  alignedAddr = (uint32_t)buff & ~0x1F;
  SCB_CleanDCache_by_Addr((uint32_t*)alignedAddr, count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));
#endif

  if(BSP_SD_WriteBlocks_DMA((uint32_t*)buff,
                           sector,
                           count) == MSD_OK)
  {
#if (osCMSIS < 0x20000U)
    /* Get the message from the queue */
    event = osMessageGet(SDQueueID, SD_TIMEOUT);

    if (event.status == osEventMessage)
    {
      if (event.value.v == WRITE_CPLT_MSG)
      {
#else
    status = osMessageQueueGet(SDQueueID, (void *)&event, NULL, SD_TIMEOUT);
    if ((status == osOK) && (event == WRITE_CPLT_MSG))
    {
#endif
 #if (osCMSIS < 0x20000U)
        timer = osKernelSysTick();
        /* block until SDIO IP is ready or a timeout occur */
        while(osKernelSysTick() - timer  < SD_TIMEOUT)
#else
        timer = osKernelGetTickCount();
        /* block until SDIO IP is ready or a timeout occur */
        while(osKernelGetTickCount() - timer  < SD_TIMEOUT)
#endif
        {
          if (BSP_SD_GetCardState() == SD_TRANSFER_OK)
          {
            res = eRES_OK;
            break;
          }
        }
#if (osCMSIS < 0x20000U)
      }
    }
#else
    }
#endif
  }
#if defined(ENABLE_SCRATCH_BUFFER)
  }
  else
  {
    /* Slow path, fetch each sector a part and memcpy to destination buffer */
    uint32_t i;

#if (ENABLE_SD_DMA_CACHE_MAINTENANCE == 1)
    /*
     * invalidate the scratch buffer before the next write to get the actual data instead of the cached one
     */
     SCB_InvalidateDCache_by_Addr((uint32_t*)scratch, BLOCKSIZE);
#endif
      for (i = 0; i < count; i++)
      {
        memcpy((void *)scratch, buff, BLOCKSIZE);
        buff += BLOCKSIZE;

        ret = BSP_SD_WriteBlocks_DMA((uint32_t*)scratch, sector, 1);
        sector++;
        if (ret == MSD_OK )
        {
          /* wait until the read is successful or a timeout occurs */
#if (osCMSIS < 0x20000U)
          /* wait for a message from the queue or a timeout */
          event = osMessageGet(SDQueueID, SD_TIMEOUT);

          if (event.status == osEventMessage)
          {
            if (event.value.v == READ_CPLT_MSG)
            {
              timer = osKernelSysTick();
              /* block until SDIO IP is ready or a timeout occur */
              while(osKernelSysTick() - timer <SD_TIMEOUT)
#else
                status = osMessageQueueGet(SDQueueID, (void *)&event, NULL, SD_TIMEOUT);
              if ((status == osOK) && (event == READ_CPLT_MSG))
              {
                timer = osKernelGetTickCount();
                /* block until SDIO IP is ready or a timeout occur */
                ret = MSD_ERROR;
                while(osKernelGetTickCount() - timer < SD_TIMEOUT)
#endif
                {
                  ret = BSP_SD_GetCardState();

                  if (ret == MSD_OK)
                  {
                    break;
                  }
                }

                if (ret != MSD_OK)
                {
                  break;
                }
#if (osCMSIS < 0x20000U)
              }
            }
#else
          }
#endif
        }
        else
        {
          break;
        }
      }

      if ((i == count) && (ret == MSD_OK ))
      {
        res = eRES_OK;
      }
    }

#endif

  return res;
}

/* USER CODE BEGIN beforeIoctlSection */
/* can be used to modify previous code / undefine following code / add new code */

SDRESULT SD_write(const uint8_t *buff, uint32_t sector, uint32_t count)
{
	SDRESULT res = eRES_ERROR;

    res = SD_write_drv(buff, sector, count);
    if (res == eRES_OK)
    {
        return res;
    }

    SD_reinit();

    for (uint32_t block = 0; block < count; block++)
    {
        for (uint8_t retry = 0; retry < SD_REINIT_MAX_RETRIES; retry++)
        {
            res = SD_write_drv(&buff[block*hsd1.SdCard.BlockSize], sector+block, 1);
            if (res != eRES_OK)
            {
                SD_reinit();
            } else
            {
                break;
            }
        }
        if (res != eRES_OK)
        {
            break;
        }
    }

    return res;
}

/* USER CODE END beforeIoctlSection */

SDRESULT SD_GetSectorCount(uint32_t* const fp_pSectorCount)
{
    SDRESULT res = eRES_NOT_READY;
    BSP_SD_CardInfo CardInfo;

    if (bIsSdInitialized)
    {
        BSP_SD_GetCardInfo(&CardInfo);
        *fp_pSectorCount = CardInfo.LogBlockNbr;
        res = eRES_OK;
    }

    return res;
}

SDRESULT SD_GetSectorSize(uint32_t* const fp_pSize)
{
    SDRESULT res = eRES_NOT_READY;
    BSP_SD_CardInfo CardInfo;

    if (bIsSdInitialized)
    {
        BSP_SD_GetCardInfo(&CardInfo);
        *fp_pSize = CardInfo.LogBlockSize;
        res = eRES_OK;
    }

    return res;
}

SDRESULT SD_GetBlockSize(uint32_t* const fp_pBlockSize)
{
    SDRESULT res = eRES_NOT_READY;
    BSP_SD_CardInfo CardInfo;

    if (bIsSdInitialized)
    {
        BSP_SD_GetCardInfo(&CardInfo);
        *fp_pBlockSize = CardInfo.LogBlockSize / SD_DEFAULT_BLOCK_SIZE;
        res = eRES_OK;
    }

    return res;
}

/* USER CODE BEGIN afterIoctlSection */
/* can be used to modify previous code / undefine following code / add new code */
/* USER CODE END afterIoctlSection */

/* USER CODE BEGIN callbackSection */
/* can be used to modify / following code or add new code */
/* USER CODE END callbackSection */
/**
  * @brief Tx Transfer completed callbacks
  * @param hsd: SD handle
  * @retval None
  */
void BSP_SD_WriteCpltCallback(void)
{

  /*
   * No need to add an "osKernelRunning()" check here, as the SD_initialize()
   * is always called before any SD_Read()/SD_Write() call
   */
#if (osCMSIS < 0x20000U)
   osMessagePut(SDQueueID, WRITE_CPLT_MSG, 0);
#else
   const uint16_t msg = WRITE_CPLT_MSG;
   osMessageQueuePut(SDQueueID, (const void *)&msg, 0, 0);
#endif
}

/**
  * @brief Rx Transfer completed callbacks
  * @param hsd: SD handle
  * @retval None
  */
void BSP_SD_ReadCpltCallback(void)
{
  /*
   * No need to add an "osKernelRunning()" check here, as the SD_initialize()
   * is always called before any SD_Read()/SD_Write() call
   */
#if (osCMSIS < 0x20000U)
   osMessagePut(SDQueueID, READ_CPLT_MSG, 0);
#else
   const uint16_t msg = READ_CPLT_MSG;
   osMessageQueuePut(SDQueueID, (const void *)&msg, 0, 0);
#endif
}
