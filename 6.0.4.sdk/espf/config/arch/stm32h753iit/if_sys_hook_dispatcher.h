/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*!
 * @file     if_sys_hook_dispatcher.h
 * @author   SW Platform
 * @brief    Interrupt dispatcher declarations
 *******************************************************************************************
 * @version  N/A
 * @date     2022.07.06
 * @copyright (C) Copyright Endurosat
 *
 *           Contents and presentations are protected world-wide.
 *           Any kind of using, copying etc. is prohibited without prior permission.
 *           All rights, incl. industrial property rights, are reserved.
 *
 *******************************************************************************************
 */

#ifndef ESPF_CONFIG_SYS_HOOK_DISPATCHER_IF_SYS_HOOK_DISPATCHER_H_
#define ESPF_CONFIG_SYS_HOOK_DISPATCHER_IF_SYS_HOOK_DISPATCHER_H_

#include <MCU_Init.h>
extern RNG_HandleTypeDef hrng;
extern TIM_HandleTypeDef htim6;

/********************************************************************************************************
 * The peripherals used by the modules included in the runtime configuration
 * - UART3   - as part of RS485 Sys1 --> S/X Band
 * - UART4   - as part of Pay2 --> Cube ADCS
 * - UART7   - Just Tx/Rx            --> EPS M (third party EPS)
 * - UART5   - Just Tx/Rx            --> GNSS
 * - GPIOG7  - EPS Reset Pin         --> EPS I
 * - GPIOF11 - En GNSS Pin           --> GNSS
 * - TIM1                            --> GNSS
 *
 * So far there is no Overlaping of peripherals so we don't  really need to
 *  redirect anything with the sys_hook_dispatcher
 *
 */

void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void UART7_IRQHandler(void);
void UART8_IRQHandler(void);

void DMA1_Stream5_IRQHandler(void);

void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);

void ADC_IRQHandler(void);

void FDCAN1_IT0_IRQHandler(void);

void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void I2C3_EV_IRQHandler(void);
void I2C3_ER_IRQHandler(void);

void SPI2_IRQHandler(void);

void TIM5_IRQHandler(void);

void SDMMC1_IRQHandler(void);

void FPU_IRQHandler(void);

void HSEM1_IRQHandler(void);

void EXTI0_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

void NMI_Handler(void);
void DebugMon_Handler(void);
void SysTick_Handler(void);
void PVD_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void HASH_RNG_IRQHandler(void);

#endif /* ESPF_CONFIG_SYS_HOOK_DISPATCHER_IF_SYS_HOOK_DISPATCHER_H_ */
