/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*
 * slipif_cfg.c
 *
 *  Created on: Oct 24, 2022
 *      Author: Ivan Petrov
 */

#include "es_cdef.h"
#include "slipif_cfg.h"
#include "debug.h"

#define SLIPIF_COUNT         (1U)

typedef struct
{
	UART_HandleTypeDef uart_hnd;
	DMA_HandleTypeDef dma_rx_hnd;
	DMA_HandleTypeDef dma_tx_hnd;
} handles_t;

typedef struct
{
    handles_t handles;
    slipif_uart_cfg_t uart_cfg;
    slipif_net_cfg_t net_cfg;
    slipif_net_cfg_state_t state;
} slipif_dev_cfg_t;

STATIC slipif_dev_cfg_t slip_cfg[SLIPIF_COUNT];
STATIC uint8_t iter_devnum = 0;     /**< SLIP SIO devices iterator used to enumarate all configured SIO instances */

STATIC void slipif_cfg_init(const uint8_t devnum);
STATIC void slipif_cfg_clk_enable(const uint8_t devnum);
STATIC void slipif_cfg_clk_disable(const uint8_t devnum);
STATIC void slipif_cfg_irq_enable(const uint8_t devnum);
STATIC void slipif_cfg_irq_disable(const uint8_t devnum);

slipif_uart_cfg_t *slipif_uart_cfg_get(const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));

    return &slip_cfg[devnum].uart_cfg;
}

slipif_net_cfg_t *slipif_net_cfg_get(const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));

    return &slip_cfg[devnum].net_cfg;
}

void slipif_cfg_ctl(const slipif_cmd_t cmd, const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));
    CRIT_ASSERT(cmd < SLIPIF_CMD_MAX);

    switch (cmd)
    {
        case SLIPIF_CMD_INIT:
        {
            slipif_cfg_init(devnum);

            break;
        }

        case SLIPIF_CMD_CLK_ENABLE:
        {
            slipif_cfg_clk_enable(devnum);

            break;
        }

        case SLIPIF_CMD_CLK_DISABLE:
        {
            slipif_cfg_clk_disable(devnum);

            break;
        }

        case SLIPIF_CMD_IRQ_ENABLE:
        {
            slipif_cfg_irq_enable(devnum);

            break;
        }

        case SLIPIF_CMD_IRQ_DISABLE:
        {
            slipif_cfg_irq_disable(devnum);

            break;
        }

        default:
        {
            CRIT_ASSERT(false);
            break;
        }
    }
}

STATIC void slipif_cfg_init(const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));

    switch (devnum)
    {
        case 0U:
        {
            slip_cfg[devnum].handles.uart_hnd.Instance = UART8;
            slip_cfg[devnum].handles.dma_rx_hnd.Instance = DMA2_Stream2;
            slip_cfg[devnum].handles.dma_rx_hnd.Init.Request = DMA_REQUEST_UART8_RX;

			__HAL_LINKDMA(&slip_cfg[devnum].handles.uart_hnd, hdmarx, slip_cfg[devnum].handles.dma_rx_hnd);

			__HAL_DMA_DISABLE_IT(&slip_cfg[devnum].handles.dma_rx_hnd, DMA_IT_HT);

            slip_cfg[devnum].uart_cfg.p_uart = &slip_cfg[devnum].handles.uart_hnd;
            slip_cfg[devnum].uart_cfg.p_uart_dma_rx = &slip_cfg[devnum].handles.dma_rx_hnd;
            slip_cfg[devnum].uart_cfg.p_rx_gpio_port = GPIOE;
            slip_cfg[devnum].uart_cfg.rx_pin = GPIO_PIN_0;
            slip_cfg[devnum].uart_cfg.af = GPIO_AF8_UART8;
            slip_cfg[devnum].uart_cfg.p_tx_gpio_port = GPIOE;
            slip_cfg[devnum].uart_cfg.tx_pin = GPIO_PIN_1;

            IP_ADDR4(&slip_cfg[devnum].net_cfg.ipaddr, SLIP_IP_ADDR0, SLIP_IP_ADDR1, SLIP_IP_ADDR2, SLIP_IP_ADDR3);
            IP_ADDR4(&slip_cfg[devnum].net_cfg.netmask, SLIP_NETMASK_ADDR0, SLIP_NETMASK_ADDR1, SLIP_NETMASK_ADDR2, SLIP_NETMASK_ADDR3);
            IP_ADDR4(&slip_cfg[devnum].net_cfg.gw, SLIP_GW_ADDR0, SLIP_GW_ADDR1, SLIP_GW_ADDR2, SLIP_GW_ADDR3);

            // set the netif state variable to point to the specific context associated to devnum
            slip_cfg[devnum].net_cfg.slipnet_if.state = (void *) &slip_cfg[devnum].state;

            break;
        }

        default:
        {
            break;
        }
    }
}

STATIC void slipif_cfg_clk_enable(const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));

    switch (devnum)
    {
        case 0U:
        {
            __HAL_RCC_UART8_CLK_ENABLE();
            __HAL_RCC_GPIOE_CLK_ENABLE();
            __HAL_RCC_DMA2_CLK_ENABLE();

            break;
        }

        default:
        {
            break;
        }
    }
}

STATIC void slipif_cfg_clk_disable(const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));

    switch (devnum)
    {
        case 0U:
        {
            __HAL_RCC_UART8_CLK_DISABLE();
            // GPIOE clock must not be stopped in order to not affect
            // other functionalities

            break;
        }

        default:
        {
            break;
        }
    }
}

STATIC void slipif_cfg_irq_enable(const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));

    switch (devnum)
    {
        case 0U:
        {
            HAL_NVIC_SetPriority(UART8_IRQn, 4, 0);
            HAL_NVIC_EnableIRQ(UART8_IRQn);

            HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 5, 0);
		    HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

            break;
        }

        default:
        {
            break;
        }
    }

}

STATIC void slipif_cfg_irq_disable(const uint8_t devnum)
{
    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(slip_cfg));

    switch (devnum)
    {
        case 0U:
        {
            HAL_NVIC_DisableIRQ(UART8_IRQn);
	        HAL_NVIC_DisableIRQ(DMA2_Stream2_IRQn);

            break;
        }

        default:
        {
            break;
        }
    }

}

void slipif_cfg_irq(void)
{
    HAL_UART_IRQHandler(slip_cfg[0U].uart_cfg.p_uart);
}

void DMA2_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&slip_cfg[0U].handles.dma_rx_hnd);
}

void sio_netif_iter_begin(void)
{
    iter_devnum = 0;
}

slipif_net_cfg_t * const sio_netif_iter_next(uint8_t * const p_devnum)
{
    slipif_net_cfg_t *p_netif = NULL;

    if (iter_devnum < CDEF_ELEMENT_COUNT(slip_cfg))
    {
        p_netif = &slip_cfg[iter_devnum].net_cfg;

        if (NULL != p_devnum)
        {
            *p_devnum = iter_devnum;
        }

        iter_devnum++;
    }

    return p_netif;
}
