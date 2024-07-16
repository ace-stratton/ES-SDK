#ifndef CUBEOBC_DEFS_H_
#define CUBEOBC_DEFS_H_

#include <stdbool.h>
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_uart.h"
#include "stm32h7xx_hal_uart_ex.h"
#include "stm32h7xx_hal_dma.h"


#define CUBEOBC_UART_HAS_RS485_CHIP

#define CUBEOBC_UART_INSTANCE        UART4
#define CUBEOBC_UART_TX_PORT         GPIOH
#define CUBEOBC_UART_TX_PIN          GPIO_PIN_13
#define CUBEOBC_UART_RX_PORT         GPIOI
#define CUBEOBC_UART_RX_PIN          GPIO_PIN_9
#define CUBEOBC_UART_PIN_ALTERNATE   GPIO_AF8_UART4
#define CUBEOBC_UART_BAUDRATE        921600
#define CUBEOBC_UART_IRQN            UART4_IRQn
#define CUBEOBC_UART_RCC_PERIPHCLK   RCC_PERIPHCLK_UART4
#define CUBEOBC_DMA_RX_INSTANCE      DMA1_Stream5
#define CUBEOBC_DMA_RX_IRQN          DMA1_Stream5_IRQn
#define CUBEOBC_DMA_RX_REQUEST_RX    DMA_REQUEST_UART4_RX
#define CUBEOBC_IRQ_PRIO             5

#ifdef CUBEOBC_UART_HAS_RS485_CHIP

# define CUBEOBC_UART_RS485_TE_PORT  GPIOE
# define CUBEOBC_UART_RS485_TE_PIN   GPIO_PIN_3
# define CUBEOBC_UART_RS485_DE_PORT  GPIOF
# define CUBEOBC_UART_RS485_DE_PIN   GPIO_PIN_13
# define CUBEOBC_UART_RS485_NRE_PORT GPIOF
# define CUBEOBC_UART_RS485_NRE_PIN  GPIO_PIN_14

static inline void cubeobc_uart_rs485_chip_init(void)
{
    GPIO_InitTypeDef gpio = { 0 };

    gpio.Pin   = CUBEOBC_UART_RS485_TE_PIN;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_WritePin(CUBEOBC_UART_RS485_TE_PORT, CUBEOBC_UART_RS485_TE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_Init(CUBEOBC_UART_RS485_TE_PORT, &gpio);

    gpio.Pin   = CUBEOBC_UART_RS485_DE_PIN;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_WritePin(CUBEOBC_UART_RS485_DE_PORT, CUBEOBC_UART_RS485_DE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_Init(CUBEOBC_UART_RS485_DE_PORT, &gpio);

    gpio.Pin   = CUBEOBC_UART_RS485_NRE_PIN;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_WritePin(CUBEOBC_UART_RS485_NRE_PORT, CUBEOBC_UART_RS485_NRE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_Init(CUBEOBC_UART_RS485_NRE_PORT, &gpio);
}
#endif // #ifdef CUBEOBC_UART_HAS_RS485_CHIP


static inline void cubeobc_uart_clk_enable(const bool enable)
{
    if (true == enable)
    {
        __HAL_RCC_UART4_CLK_ENABLE();
    }
    else
    {
        __HAL_RCC_UART4_CLK_DISABLE();
    }
}


static inline void cubeobc_uart_tx_clk_enable(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();
}


static inline void cubeobc_uart_rx_clk_enable(void)
{
    __HAL_RCC_GPIOI_CLK_ENABLE();
}


static inline void cubeobc_dma_rx_clk_enable(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();
}


#endif /* CUBEOBC_DEFS_H_ */
