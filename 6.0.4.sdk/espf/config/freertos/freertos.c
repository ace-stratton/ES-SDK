/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

/* Pre/Post sleep processing prototypes */
void PreSleepProcessing(uint32_t *ulExpectedIdleTime);
void PostSleepProcessing(uint32_t *ulExpectedIdleTime);

/* USER CODE BEGIN PREPOSTSLEEP */
__weak void PreSleepProcessing(uint32_t *ulExpectedIdleTime)
{
/* place for user code */ 
}

__weak void PostSleepProcessing(uint32_t *ulExpectedIdleTime)
{
/* place for user code */
}
/* USER CODE END PREPOSTSLEEP */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

//
// Heap linker imports
//
extern uint8_t lnk_freertos_heap_start_addr;    /**< start address of the FreeRTOS heap region */
extern uint8_t lnk_freertos_heap_size_bytes;    /**< size in bytes of the FreeRTOS heap region */

/** @brief List of regions to be used as FreeRTOS heap for the heap_5.c allocator
 */
static const HeapRegion_t freertos_heap_rgn_list[2] =
{
    { .pucStartAddress = &lnk_freertos_heap_start_addr, .xSizeInBytes = (size_t) &lnk_freertos_heap_size_bytes },
    { NULL, 0 }
};

/**
* @brief Perform user-specific FreeRTOS initialization
*
* @note              Takes care to setup the heap_5 memory allocator by providing a list of
*                    memory regions to be used as heap
*/
void freertos_user_init(void)
{
    // setup FreeRTOS heap allocator regions
    vPortDefineHeapRegions(freertos_heap_rgn_list);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
