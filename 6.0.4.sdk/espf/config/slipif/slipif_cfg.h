/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/*
 * slipif_cfg.h
 *
 *  Created on: Oct 24, 2022
 *      Author: Ivan Petrov
 */

#ifndef SLIPIF_CFG_H
#define SLIPIF_CFG_H

#include "stm32h7xx_hal.h"
#include "lwip/netif.h"

/** @brief UART bps rate used for all SLIP interfaces */
#define SLIP_UART_SPEED_BPS		(115200U)

// SLIP[0] IP Address
#define SLIP_IP_ADDR0   ((uint8_t) 192U)
#define SLIP_IP_ADDR1   ((uint8_t) 168U)
#define SLIP_IP_ADDR2   ((uint8_t) 70U)
#define SLIP_IP_ADDR3   ((uint8_t) 10U)

// SLIP[0] Netmask
#define SLIP_NETMASK_ADDR0   ((uint8_t) 255U)
#define SLIP_NETMASK_ADDR1   ((uint8_t) 255U)
#define SLIP_NETMASK_ADDR2   ((uint8_t) 255U)
#define SLIP_NETMASK_ADDR3   ((uint8_t) 0U)

// SLIP[0] Gateway host address
#define SLIP_GW_ADDR0        ((uint8_t) 192U)
#define SLIP_GW_ADDR1        ((uint8_t) 168U)
#define SLIP_GW_ADDR2        ((uint8_t) 70U)
#define SLIP_GW_ADDR3        ((uint8_t) 1U)

typedef struct
{
    UART_HandleTypeDef *p_uart;
    DMA_HandleTypeDef *p_uart_dma_rx;
    GPIO_TypeDef *p_rx_gpio_port;
    GPIO_TypeDef *p_tx_gpio_port;
    uint16_t rx_pin;
    uint16_t tx_pin;
    uint32_t af;    // alternate pin function setting
} slipif_uart_cfg_t;

typedef struct
{
    ip_addr_t ipaddr;                    /**< SLIP interface IP address */
    ip_addr_t netmask;                   /**< SLIP interface netmask */
    ip_addr_t gw;                        /**< SLIP interface GW address */
    struct netif slipnet_if;             /**< SLIP interface netw service context */
} slipif_net_cfg_t;

typedef struct {
  void * sd;
  /* q is the whole pbuf chain for a packet, p is the current pbuf in the chain */
  struct pbuf *p, *q;
  u8_t state;
  u16_t i, recved;
//#if SLIP_RX_FROM_ISR
  struct pbuf *rxpackets;
//#endif
} slipif_priv_t;

typedef struct
{
    uint8_t devnum;                     /**< SLIP interface device ID */
    slipif_priv_t priv_static;     /**< static data associated to the SLIP interface */
} slipif_net_cfg_state_t;

typedef enum
{
    SLIPIF_CMD_INIT = 0,
    SLIPIF_CMD_CLK_ENABLE,
    SLIPIF_CMD_CLK_DISABLE,
    SLIPIF_CMD_IRQ_ENABLE,
    SLIPIF_CMD_IRQ_DISABLE,
    SLIPIF_CMD_MAX
} slipif_cmd_t;

slipif_uart_cfg_t *slipif_uart_cfg_get(const uint8_t devnum);
slipif_net_cfg_t *slipif_net_cfg_get(const uint8_t devnum);
void slipif_cfg_ctl(const slipif_cmd_t cmd, const uint8_t devnum);
void slipif_cfg_irq(void);

/** @brief Resets the SLIP SIO instances */
void sio_netif_iter_begin(void);

/** @brief Returns a pointer to the next configured SIO instance descriptor
 *
 *  @param[out] p_devnum Device ID associated to the returned SLIPIF network configuration instance
 * */
slipif_net_cfg_t * const sio_netif_iter_next(uint8_t * const p_devnum);

#endif /* SLIPIF_CFG_H */
