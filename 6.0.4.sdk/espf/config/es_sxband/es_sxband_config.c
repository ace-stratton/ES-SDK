/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*
 * es_sxband_config.c
 *
 *  Created on: Oct 24, 2022
 *      Author: Ivan Petrov
 */

#include "es_sxband_config.h"
#include "if_sys_conf.h"
#include "assertions.h"

static USART_TypeDef * const pc_usart_handle = USART3;

static UART_HandleTypeDef sx_band_usart_handle =
{
	.Instance = pc_usart_handle
};

static DMA_HandleTypeDef hdma_usart3_rx;
static DMA_HandleTypeDef hdma_usart3_tx;

void es_sxband_config_init(void)
{
	sx_band_usart_handle.Instance = pc_usart_handle;
}

UART_HandleTypeDef * es_sxband_config_get_usart_hnd(void)
{
	return &sx_band_usart_handle;
}

void es_sxband_config_uart_init(UART_HandleTypeDef * const huart)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3;
	PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
	    // Could not initialize USART3 peripheral clocks
		CRIT_ASSERT(false);
	}

	/* Peripheral clock enable */
	__HAL_RCC_USART3_CLK_ENABLE();

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	/**USART3 GPIO Configuration
	PB10     ------> USART3_TX
	PD9     ------> USART3_RX
	*/
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin  = SX_BAND_TX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(SX_BAND_TX_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin  = SX_BAND_RX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(SX_BAND_RX_GPIO_Port, &GPIO_InitStruct);

	/* USART3 DMA Init */
	/* USART3_RX Init */
	hdma_usart3_rx.Instance = DMA2_Stream0;
	hdma_usart3_rx.Init.Request = DMA_REQUEST_USART3_RX;
	hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart3_rx.Init.Mode = DMA_CIRCULAR;
	hdma_usart3_rx.Init.Priority = DMA_PRIORITY_HIGH;
	hdma_usart3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
	{
	    // Could not initialize USART3 DMA Rx channel
		CRIT_ASSERT(false);
	}

	__HAL_LINKDMA(huart,hdmarx,hdma_usart3_rx);

	/* USART3_TX Init */
	hdma_usart3_tx.Instance = DMA2_Stream5;
	hdma_usart3_tx.Init.Request = DMA_REQUEST_USART3_TX;
	hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart3_tx.Init.Mode = DMA_NORMAL;
	hdma_usart3_tx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_usart3_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
	{
	    // Could not initialize USART3 DMA Tx channel
		CRIT_ASSERT(false);
	}

	__HAL_LINKDMA(huart,hdmatx,hdma_usart3_tx);

	/* USART3 interrupt Init */
	HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
}

void es_sxband_config_uart_deinit(UART_HandleTypeDef * const huart)
{
	__HAL_RCC_USART3_CLK_DISABLE();

	/**USART3 GPIO Configuration
	PB10     ------> USART3_TX
	PD9     ------> USART3_RX
	*/
	HAL_GPIO_DeInit(SX_BAND_TX_GPIO_Port, SX_BAND_TX_Pin);
	HAL_GPIO_DeInit(SX_BAND_RX_GPIO_Port, SX_BAND_RX_Pin);

	/* USART3 DMA DeInit */
	HAL_DMA_DeInit(huart->hdmarx);
	HAL_DMA_DeInit(huart->hdmatx);

	/* USART3 interrupt DeInit */
	HAL_NVIC_DisableIRQ(USART3_IRQn);
}

void es_sxband_config_usart_irq(void)
{
	HAL_UART_IRQHandler(&sx_band_usart_handle);
}

void es_sxband_config_dma_rx_irq(void)
{
	HAL_DMA_IRQHandler(&hdma_usart3_rx);
}

void es_sxband_config_dma_tx_irq(void)
{
	HAL_DMA_IRQHandler(&hdma_usart3_tx);
}
