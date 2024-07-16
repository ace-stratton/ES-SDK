/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @file  sys_hook_dispatcher.c
 * @brief Interrupt handler dispatcher
 */

#include "if_sys_hook_dispatcher.h"

#include "if_sys_conf.h"
#include "if_sys_instancer.h"
#include "TaskMonitor.h"
#include "SdMngr.h"
#include "nvm_resetcounters.h"
#include "cubeadcs_driver.h"
#include "can.h"
#include "es_sxband_config.h"
#include "S_X_Band_Trnsm.h"
#include "trace_config.h"
#include "cubeobc_uart.h"
#if defined(SLIP_SUPPORT_ENABLED) && defined(LWIP_SUPPORT_ENABLED)
#include "slipif_cfg.h"
#endif
#if defined(GNSS_ENABLED)
#include "gnss_irq.h"
#endif
#include "stm32h7xx_hal.h"

/**
 * @brief This function handles global UART3 interrupt
 */
void USART3_IRQHandler(void)
{
    if (sys_conf_is_module_active(SYS_MODULE_ID_SX_BAND))
    {
        es_sxband_config_usart_irq();
    }
    else
    {
        Error_Handler();
    }
}

/**
 * @brief This function handles global UART4 interrupt
 */
void UART4_IRQHandler(void)
{
    // UART4 is assigned to the Cube ADCS exclusively
    if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
    {
        cubeadcs_driver_uart_irq_handler();
    }
#if defined(CUBEADCS_GEN2_ENABLED)
    else if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
    {
        cubeobc_uart_irq_handler();
    }
#endif
    else
    {
        Error_Handler();
    }
}

/**
 * @brief This function handles global UART5 interrupt
 */
void UART5_IRQHandler(void)
{
#if defined(GNSS_ENABLED)
    if (sys_conf_is_module_active(SYS_MODULE_ID_GNSS))
    {
        gnss_irq_uart_handler();
    }
    else
#endif
    {
        Error_Handler();
    }
}

/**
 * @brief This function handles global UART7 interrupt
 */
void UART7_IRQHandler(void)
{
    Error_Handler();
}

/**
 * @brief This function handles global UART8 interrupt
 */
void UART8_IRQHandler(void)
{
#if defined(SLIP_SUPPORT_ENABLED) && defined(LWIP_SUPPORT_ENABLED)
    slipif_cfg_irq();
#else
    Error_Handler();
#endif
}

/**
 * @brief This function handles CAN interrupt
 */
void FDCAN1_IT0_IRQHandler(void)
{
    can_irq_it0_handler();
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1_CH1 and DAC1_CH2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim6);
}

/**
 * @brief This function handles TIM5 global interrupt.
 */
void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim5);
}

/**
 * @brief This function handles RCC global interrupt.
 */
void RCC_IRQHandler(void)
{
}

/**
 * @brief This function handles DMA1 stream5 global interrupt.
 */
void DMA1_Stream5_IRQHandler(void)
{
    if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS))
    {
    	cubeadcs_driver_dma_irq_handler();
    }
#if defined(CUBEADCS_GEN2_ENABLED)
    else if (sys_conf_is_module_active(SYS_MODULE_ID_CUBE_ADCS_GEN2))
    {
    	cubeobc_uart_dma_irq_handler();
    }
#endif
    else
    {
        Error_Handler();
    }
}

/**
 * @brief This function handles DMA2 stream0 global interrupt.
 */
void DMA2_Stream0_IRQHandler(void)
{
    if (sys_conf_is_module_active(SYS_MODULE_ID_SX_BAND))
    {
    	es_sxband_config_dma_rx_irq();
    }
    else
    {
        Error_Handler();
    }
}

/**
 * @brief This function handles DMA2 stream1 global interrupt.
 */
void DMA2_Stream1_IRQHandler(void)
{
#if defined(GNSS_ENABLED)
    if (sys_conf_is_module_active(SYS_MODULE_ID_GNSS))
    {
        gnss_irq_dma_handler();
    }
    else
#endif
    {
        Error_Handler();
    }
}

/**
 * @brief This function handles DMA2 stream5 global interrupt.
 */
void DMA2_Stream5_IRQHandler(void)
{
    if (sys_conf_is_module_active(SYS_MODULE_ID_SX_BAND))
    {
        es_sxband_config_dma_tx_irq();
    }
    else
    {
        Error_Handler();
    }
}

/**
 * @brief This function handles ADC1 and ADC2 global interrupts.
 */
void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hadc1);
}

/**
 * @brief This function handles I2C1 event interrupt.
 */
void I2C1_EV_IRQHandler(void)
{
    HAL_I2C_EV_IRQHandler(&hi2c1);
}

/**
 * @brief This function handles I2C1 error interrupt.
 */
void I2C1_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(&hi2c1);
}

/**
 * @brief This function handles I2C2 event interrupt.
 */
void I2C2_EV_IRQHandler(void)
{
    HAL_I2C_EV_IRQHandler(&hi2c2);
}

/**
 * @brief This function handles I2C2 error interrupt.
 */
void I2C2_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(&hi2c2);
}

/**
 * @brief This function handles I2C3 event interrupt.
 */
void I2C3_EV_IRQHandler(void)
{
    HAL_I2C_EV_IRQHandler(&hi2c3);
}

/**
 * @brief This function handles I2C3 error interrupt.
 */
void I2C3_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(&hi2c3);
}

/**
 * @brief This function handles SPI2 global interrupt.
 */
void SPI2_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&hspi2);
}

/**
 * @brief This function handles SDMMC1 global interrupt.
 */
void SDMMC1_IRQHandler(void)
{
    HAL_SD_IRQHandler(&hsd1);
}

/**
 * @brief This function handles HASH and RNG global interrupts.
 */
void HASH_RNG_IRQHandler(void)
{
    HAL_RNG_IRQHandler(&hrng);
}

/**
 * @brief This function handles FPU global interrupt.
 */
void FPU_IRQHandler(void)
{
}

/**
 * @brief This function handles HSEM1 global interrupt.
 */
void HSEM1_IRQHandler(void)
{
    HAL_HSEM_IRQHandler();
}

/**
 * @brief This function handles PVD interrupt through EXTI line 16.
 */
void PVD_AVD_IRQHandler(void)
{
    HAL_PWR_PVD_IRQHandler();
}

/**
 * @brief This function handles EXTI line[0] interrupts.
 */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);     //COM USART Rx ISR
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_All);   //UHF Rx ISR
}

/**
 * @brief This function handles EXTI line[9:5] interrupts.
 */
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);     //COM USART Rx ISR
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_All);   //UHF Rx ISR
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);    // SD card 1 detection ISR
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);    // SD card 2 detection ISR

    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);    // USART1 Rx
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_All);

}

/**
 * @brief This Callback handles EXTI line[15:10] interrupts.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if( GPIO_PIN_15 == GPIO_Pin)
    {
        // interrupt if SD card is inserted or ejected
        SD_Card_Eject_Detected();
    }
}

/**
 * @brief This function handles Flash global interrupt.
 */
void FLASH_IRQHandler(void)
{
    __HAL_FLASH_DISABLE_IT(FLASH_IT_SNECCERR_BANK2);
    __HAL_FLASH_DISABLE_IT(FLASH_IT_DBECCERR_BANK2);

    if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_SNECCERR_BANK2))
    {
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_SNECCERR_BANK2);
    }

    if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_DBECCERR_BANK2))
    {
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_DBECCERR_BANK2);
    }

    HAL_FLASH_IRQHandler();

    __HAL_FLASH_ENABLE_IT(FLASH_IT_SNECCERR_BANK2);
    __HAL_FLASH_ENABLE_IT(FLASH_IT_DBECCERR_BANK2);
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM6 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        HAL_IncTick();
    }
}

/********************************************************************************************************
 * Fault Handlers
 ********************************************************************************************************/

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
    HAL_RCC_NMI_IRQHandler();

    while (1)
    {
    }
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
#if (INCLUDE_xTaskGetSchedulerState == 1 )
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
#endif /* INCLUDE_xTaskGetSchedulerState */
        xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
    }
#endif /* INCLUDE_xTaskGetSchedulerState */
}


void HAL_RCC_CCSCallback(void)
{
    TaskMonitor_ImmediateReset(TASK_MONITOR_FAULT_RESET);
}
