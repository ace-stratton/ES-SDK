/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup Networking
 * @{
 *
 * @file netw.c
 * @brief Networking services
 *
 * The networking service is responsible to initialize the Ethernet interface and configure
 * all supported network interfaces in the system and activate them.
 *
 * @}
*/

#include "netw.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "config/netw/netw_cfg.h"
#include "slipif_cfg.h"

#if defined(ETHERNET_SUPPORT_ENABLED)
#include "ethernetif.h"
#endif // ETHERNET_SUPPORT_ENABLED

#if defined(TFTPD_SUPPORT_ENABLED)
#include "tftpd.h"
#endif

#if defined(SLIP_SUPPORT_ENABLED)
#include "netif/slipif.h"
#endif

static struct netif gnetif;    /**< network interface structure */

static osThreadId_t eth_link_task_hnd = NULL;
static osThreadId_t netw_task_hnd = NULL;

static void netif_config(void);

#if defined(ETHERNET_SUPPORT_ENABLED)
static void on_eth_link_status_update(struct netif *netif);

/**
  * @brief  Notify the User about the network interface config status
  * @param  netif: the network interface
  * @retval None
  */
static void on_eth_link_status_update(struct netif *netif)
{
    // currently this implementation is empty
    if (netif_is_up(netif))
    {
        (void) netif;
    }
    else
    {
        (void) netif;
    }
}
#endif // ETHERNET_SUPPORT_ENABLED

/**
  * @brief  Initializes the lwIP stack
  * @param  None
  * @retval None
  */
static void netif_config(void)
{
    osThreadAttr_t ethernet_link_task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "netw_link_task",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = configMINIMAL_STACK_SIZE * 4
    };

    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

#if defined(ETHERNET_SUPPORT_ENABLED)

#if LWIP_DHCP
    ip_addr_set_zero_ip4(&ipaddr);
    ip_addr_set_zero_ip4(&netmask);
    ip_addr_set_zero_ip4(&gw);
#else
    IP_ADDR4(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
    IP_ADDR4(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
    IP_ADDR4(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
#endif /* LWIP_DHCP */

    /* add the network interface */
    netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

    /*  Registers the default network interface. */
    netif_set_default(&gnetif);

    on_eth_link_status_update(&gnetif);

#endif  // ETHERNET_SUPPORT_ENABLED

#if LWIP_NETIF_LINK_CALLBACK
    netif_set_link_callback(&gnetif, on_eth_link_status_update);

    /* create the task that handles the ETH_MAC */
    if (NULL == eth_link_task_hnd)
    {
        eth_link_task_hnd = osThreadNew(ethernet_link_thread,
                                        (void *) &gnetif,
                                        &ethernet_link_task_attr);
    }
#endif  // #if LWIP_NETIF_LINK_CALLBACK

#if defined(SLIP_SUPPORT_ENABLED)
    uint8_t devnum;

    sio_netif_iter_begin();

    slipif_net_cfg_t *p_slipif_net_cfg = sio_netif_iter_next(&devnum);

    while (NULL != p_slipif_net_cfg)
    {
        slipif_cfg_ctl(SLIPIF_CMD_INIT, devnum);

#if LWIP_DHCP
        ip_addr_set_zero_ip4(&ipaddr);
        ip_addr_set_zero_ip4(&netmask);
        ip_addr_set_zero_ip4(&gw);
#else
        ip4_addr_set(&ipaddr, &p_slipif_net_cfg->ipaddr);
        netmask = p_slipif_net_cfg->netmask;
        gw = p_slipif_net_cfg->gw;
#endif /* LWIP_DHCP */

        struct netif *p_netif_initialized = netif_add(&p_slipif_net_cfg->slipnet_if, &ipaddr, &netmask, &gw, NULL, &slipif_init, &tcpip_input);

        if (p_netif_initialized != NULL)
        {
            /* Registers SLIP network interface */
            netif_set_up(p_netif_initialized);
            netif_set_link_up(p_netif_initialized);
        }
        else
        {
            /* When the netif link is down this function must be called */
            netif_set_down(p_netif_initialized);
        }

        p_slipif_net_cfg = sio_netif_iter_next(&devnum);
    }
#endif
}

static void netw_task(void *arg)
{
    (void) arg;

    /* Create tcp_ip stack thread */
    tcpip_init(NULL, NULL);

    /* Initialize the LwIP stack */
    netif_config();

#if defined(TFTPD_SUPPORT_ENABLED)
    tftpd_init_server();
#endif

#if defined(SLIP_SUPPORT_ENABLED)
  while (1)
  {
      sio_netif_iter_begin();

      slipif_net_cfg_t *p_slipif_net_cfg = sio_netif_iter_next(NULL);

      while (NULL != p_slipif_net_cfg)
      {
          slipif_process_rxqueue(&p_slipif_net_cfg->slipnet_if);

          p_slipif_net_cfg = sio_netif_iter_next(NULL);
      }

	  osDelay(1);
  }
#endif  // #if defined(SLIP_SUPPORT_ENABLED)

  osThreadTerminate(osThreadGetId());
}

void netw_init(void)
{
    static const osThreadAttr_t netw_task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "netw_task",
        .priority  = osPriorityNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = 2048
    };

    /* create the task that handles the ETH_MAC */
    if (NULL == netw_task_hnd)
    {
        netw_task_hnd = osThreadNew(netw_task,
                                    (void *) NULL,
                                    &netw_task_attr);
    }
}
