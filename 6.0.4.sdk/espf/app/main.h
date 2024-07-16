/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef MAIN_H
#define MAIN_H

/**
 * @defgroup app Applications
 * @{
 *
 * @addtogroup app
 * @{
 *
 * @defgroup app_main main
 * @{
 *
 * ## Startup code
 *
 * The file arch/stm32h753iit/startup/startup_stm32h753iitx.s is written in assembly language and
 *  contains the reset vector implementation for the CPU. It also contains code taking care of:
 *
 * - system clock initialization
 * - setup of the full interrupt vector table with the addresses of the user Interrupt Service Routines
 * - initialization of the RAM data sections defined in the linker script
 * - setup of the initial stack pointer
 * - basic handling of unexpected CPU interrupts
 * - jumping to the main() entry point for the application
 *
 * A call to the SystemInit() function is made just before jumping to the main() entry point to make
 *  some final initialization.
 *
 * @file main.h
 * @brief main header
 *
 * @}
 * @}
 * @}
 */

#include <MCU_Init.h>

#define	__disable_interrupt()	__disable_irq()
#define	__enable_interrupt()	__enable_irq()

//Prevent hands in HAL_Delay() and following watch-dog reset
//If the kernel is initialized together with any tasks/mutexes/semaphores/queues the interrupts are disabled until the OS is started
#ifdef DEBUG_ENABLED
#define HAL_DELAY(a) if (osKernelGetState() == osKernelReady) Error_Handler(); else HAL_Delay(a);
#else
#define HAL_DELAY(a) if (osKernelGetState() == osKernelInactive) HAL_Delay(a);
#endif

#define sysDelay(a)         { if (osKernelGetState() == osKernelRunning) osDelay((a)); else HAL_DELAY(a); }



/**
 * @brief This function is called when an error occurs. It sets the LEDs in a specific state.
 */
void Error_Handler(void);

#endif				/* MAIN_H */
