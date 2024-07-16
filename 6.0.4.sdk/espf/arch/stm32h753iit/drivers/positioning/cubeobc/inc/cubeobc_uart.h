/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CUBEOBC_UART_H_
#define CUBEOBC_UART_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @addtogroup CubeAdcsGen2
 * @{
 *
 * @file cubeobc_uart.h
 *
 * @brief Provide an interface for the CubeAdcsGen2 UART communication
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Init Driver
 *
 * @retval true  Init success
 * @retval false Init fail
 */
bool cubeobc_uart_init(void);

/**
 * @brief DeInit Driver
 *
 * @retval true  DeInit success
 * @retval false DeInit fail
 */
bool cubeobc_uart_deinit(void);

/**
 * @brief UART interrupt handler
 */
void cubeobc_uart_irq_handler(void);

/**
 * @brief DMA interrupt handler
 */
void cubeobc_uart_dma_irq_handler(void);


#ifdef __cplusplus
}
#endif

#endif /* CUBEOBC_UART_H_ */
