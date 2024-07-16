/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*
 * es_sxband_config.h
 *
 *  Created on: Oct 24, 2022
 *      Author: Ivan Petrov
 */

#ifndef ES_SXBAND_CONFIG_H
#define ES_SXBAND_CONFIG_H

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_uart.h"
#include "stm32h7xx_hal_rcc.h"

#define SX_BAND_RX_Pin               GPIO_PIN_9
#define SX_BAND_RX_GPIO_Port         GPIOD
#define SX_BAND_TX_Pin               GPIO_PIN_10
#define SX_BAND_TX_GPIO_Port         GPIOB
#define SX_BAND_TxEnblPin            GPIO_PIN_10
#define SX_BAND_TxEnbl_GPIO_Port     GPIOD
#define USART_IRQ                    USART3_IRQn
#define DMA_Stream1_IRQn             DMA2_Stream0_IRQn
#define DMA_Stream2_IRQn             DMA2_Stream5_IRQn
#define DMA_CLK_ENABLE()             __HAL_RCC_DMA2_CLK_ENABLE()

#define S_X_BAND_TRNSM_STRCT_SIZE    (14)     /**< size of one packet without the data and the CRC */
#define S_X_BAND_TRNSM_TX_BUFF_SIZE  (1536)
#define S_X_BAND_TRNSM_RX_BUFF_SIZE  (1536)

#define FILE_TEMP_BUFFER_SIZE        (1500U)  /**< Size in bytes of the memory buffer used to format SXBand responses before writing them to a file */

#define SX_BAND_FOUTPUT_NAME         "SXBAND.LOG"

#define SX_BAND_FILECACHE_NAME       "CACHE.SXB"    /**< Name of the SXBand SD card file cache data which is used for command timeout calculations by the driver */

/** Debugging the X-Band stack */
#define S_X_BAND_STACK_DEBUG                  (0)

#if S_X_BAND_STACK_DEBUG
#define SX_BAND_TRACE(formatStr, ...)         ES_TRACE_DEBUG(formatStr OPT_VA_ARGS(__VA_ARGS__))
#define SX_BAND_TRACE_VERBOSE(formatStr, ...)
#else
#define SX_BAND_TRACE(formatStr, ...)
#define SX_BAND_TRACE_VERBOSE(formatStr, ...)
#endif
void es_sxband_config_init(void);
void es_sxband_config_uart_init(UART_HandleTypeDef * const huart);
void es_sxband_config_uart_deinit(UART_HandleTypeDef * const huart);
void es_sxband_config_usart_irq(void);
void es_sxband_config_dma_rx_irq(void);
void es_sxband_config_dma_tx_irq(void);
UART_HandleTypeDef * es_sxband_config_get_usart_hnd(void);

#endif /* ES_SXBAND_CONFIG_H */
