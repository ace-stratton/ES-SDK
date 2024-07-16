/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 ******************************************************************************
 * @file    LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/ethernetif.c
 * @author  MCD Application Team
 * @brief   This file implements Ethernet network interface drivers for lwIP
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 * @note The file has been modified EnduroSat to account for OBC SDK specifics.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"
#include "netif/etharp.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/tcpip.h"

#include "ethernetif.h"
#include "nxp-tja1100.h"
#include "cmsis_os2.h"
#include <string.h>
#include "TaskMonitor.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* The time to block waiting for input. */
#define TIME_WAITING_FOR_INPUT                 (60000U)
/* Stack size of the interface thread */
#define INTERFACE_THREAD_STACK_SIZE            (2048)
/* This is the time (in ms) to wait for invocation of the DMA Tx ISR handler to indicate the Tx is complete */
#define TIME_WAITING_FOR_TX                    (10000U)

/* Define those to better describe your network interface. */
#define IFNAME0 's'
#define IFNAME1 't'

#define ETH_DMA_TRANSMIT_TIMEOUT               (20U)

#define ETH_RX_BUFFER_CNT             12U
#define ETH_TX_BUFFER_MAX             ((ETH_TX_DESC_CNT) * 2U)

/* Private macro -------------------------------------------------------------*/
/*
 * OBC configuration with TJA1100
 * */

#define ETH_RST_PIN GPIO_PIN_2
#define ETH_EN_PIN GPIO_PIN_3

/* Private variables ---------------------------------------------------------*/
/*
 @Note: This interface is implemented to operate in zero-copy mode only:
 - Rx Buffers will be allocated from LwIP stack memory heap,
 then passed to ETH HAL driver.
 - Tx Buffers will be allocated from LwIP stack memory heap,
 then passed to ETH HAL driver.

 @Notes:
 1.a. ETH DMA Rx descriptors must be contiguous, the default count is 4,
 to customize it please redefine ETH_RX_DESC_CNT in ETH GUI (Rx Descriptor Length)
 so that updated value will be generated in stm32xxxx_hal_conf.h
 1.b. ETH DMA Tx descriptors must be contiguous, the default count is 4,
 to customize it please redefine ETH_TX_DESC_CNT in ETH GUI (Tx Descriptor Length)
 so that updated value will be generated in stm32xxxx_hal_conf.h

 2.a. Rx Buffers number: ETH_RX_BUFFER_CNT must be greater than ETH_RX_DESC_CNT.
 2.b. Rx Buffers must have the same size: ETH_RX_BUFFER_SIZE, this value must
 passed to ETH DMA in the init field (heth.Init.RxBuffLen)
 */
typedef enum
{
    RX_ALLOC_OK = 0x00,
    RX_ALLOC_ERROR = 0x01
} RxAllocStatusTypeDef;

typedef struct
{
    struct pbuf_custom pbuf_custom;
    uint8_t buff[(uint32_t) (ETH_RX_BUFFER_SIZE + 31) & (uint32_t) ~31] __ALIGNED(32);
} RxBuff_t;

ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".DMA_Rx_Decr_Section"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".DMA_Tx_Decr_Section"))); /* Ethernet Tx DMA Descriptors */

/* Memory Pool Declaration */
LWIP_MEMPOOL_DECLARE(RX_POOL, ETH_RX_BUFFER_CNT, sizeof(RxBuff_t), "Zero-copy RX PBUF pool")

__attribute__((section(".LwIP_Rx_PoolSection")))     extern u8_t memp_memory_RX_POOL_base[];

/* Variable Definitions */
static uint8_t RxAllocStatus;

osSemaphoreId RxPktSemaphore = NULL; /* Semaphore to signal incoming packets */

TaskHandle_t EthIfThread; /* Handle of the interface thread */
osSemaphoreId TxPktSemaphore = NULL; /* Semaphore to signal transmit packet complete */

/* Global Ethernet handle */
ETH_HandleTypeDef EthHandle;
ETH_TxPacketConfig TxConfig;

/* Private function prototypes -----------------------------------------------*/
extern void Error_Handler(void);
static void ethernetif_input(void *argument);

#ifdef USE_CACHE
    static void mpu_config(void);
    static void cpu_cache_enable(void)
#endif

int32_t ETH_PHY_IO_Init(void);
int32_t ETH_PHY_IO_DeInit(void);
int32_t ETH_PHY_IO_ReadReg(uint32_t DevAddr, uint32_t RegAddr, uint32_t *pRegVal);
int32_t ETH_PHY_IO_WriteReg(uint32_t DevAddr, uint32_t RegAddr, uint32_t RegVal);
int32_t ETH_PHY_IO_GetTick(void);

/* Private functions ---------------------------------------------------------*/
void pbuf_free_custom(struct pbuf *p);
/*******************************************************************************
 LL Driver Interface ( LwIP stack --> ETH)
 *******************************************************************************/
/**
 * @brief In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
phy_Object_t PHY_OBJ;
tja1100_IOCtx_t PHY_IOCtx = { ETH_PHY_IO_Init,
        ETH_PHY_IO_DeInit,
        ETH_PHY_IO_WriteReg,
        ETH_PHY_IO_ReadReg,
        ETH_PHY_IO_GetTick };

static osThreadId_t os_task_hnd = NULL;

static void low_level_init(struct netif *netif)
{
    osThreadAttr_t ethernetif_task_attr =
    {
        .attr_bits = osThreadDetached,
        .name      = "ethernetif_task",
        .priority  = osPriorityAboveNormal,
        .cb_mem    = NULL,
        .cb_size   = 0U,
        .stack_mem = NULL,
        .stack_size = INTERFACE_THREAD_STACK_SIZE
    };

    int32_t PHYLinkState = 0U;
    uint8_t macaddress[6] = { ETH_MAC_ADDR0, ETH_MAC_ADDR1, ETH_MAC_ADDR2, ETH_MAC_ADDR3, ETH_MAC_ADDR4, ETH_MAC_ADDR5 };

#ifdef USE_CACHE
    /* Configure the MPU attributes as Device memory for ETH DMA descriptors */
    mpu_config();

    /* Enable the CPU Cache */
    cpu_cache_enable();
#endif

    EthHandle.Instance = ETH;
    EthHandle.Init.MACAddr = macaddress;
    EthHandle.Init.MediaInterface = HAL_ETH_MII_MODE;
    EthHandle.Init.RxDesc = DMARxDscrTab;
    EthHandle.Init.TxDesc = DMATxDscrTab;
    EthHandle.Init.RxBuffLen = ETH_RX_BUFFER_SIZE;

    /* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
    HAL_ETH_Init(&EthHandle);

    /* set MAC hardware address length */
    netif->hwaddr_len = ETH_HWADDR_LEN;

    /* set MAC hardware address */
  netif->hwaddr[0] =  EthHandle.Init.MACAddr[0];
  netif->hwaddr[1] =  EthHandle.Init.MACAddr[1];
  netif->hwaddr[2] =  EthHandle.Init.MACAddr[2];
  netif->hwaddr[3] =  EthHandle.Init.MACAddr[3];
  netif->hwaddr[4] =  EthHandle.Init.MACAddr[4];
  netif->hwaddr[5] =  EthHandle.Init.MACAddr[5];

    /* maximum transfer unit */
    netif->mtu = ETH_MAX_PAYLOAD;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

    /* Initialize the RX POOL */
    LWIP_MEMPOOL_INIT(RX_POOL);

    /* Set Tx packet config common parameters */
    memset(&TxConfig, 0, sizeof(ETH_TxPacketConfig));
    TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
    TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;

    /* create a binary semaphore used for informing ethernetif of frame reception */
    RxPktSemaphore = osSemaphoreNew(1, 1, NULL);

    /* create a binary semaphore used for informing ethernetif of frame transmission */
    TxPktSemaphore = osSemaphoreNew(1, 1, NULL);

    /* create the task that handles the ETH_MAC */
    if (NULL == os_task_hnd)
    {
        os_task_hnd = osThreadNew(ethernetif_input,
                                     (void *) netif,
                                     &ethernetif_task_attr);
    }

    PHYLinkState = TJA1100_GetLinkState(&PHY_OBJ);

    /* Get link state */
    if (PHYLinkState <= PHY_STATUS_LINK_DOWN)
    {
        netif_set_link_down(netif);
        netif_set_down(netif);
    }
    else
    {
        HAL_ETH_Start_IT(&EthHandle);
        netif_set_up(netif);
        netif_set_link_up(netif);
    }
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet was sent, or ERR_IF if the packet was unable to be sent
 *
 * @note ERR_OK means the packet was sent (but not necessarily transmit complete),
 * and ERR_IF means the packet has more chained buffers than what the interface supports.
 */
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    uint32_t i = 0U;
    err_t errval = ERR_OK;
    ETH_BufferTypeDef Txbuffer[ETH_TX_DESC_CNT] = {0};

    (void) netif;

    memset(Txbuffer, 0, ETH_TX_DESC_CNT * sizeof(ETH_BufferTypeDef));

    for (struct pbuf *q = p; q != NULL; q = q->next)
    {
        if (i >= ETH_TX_DESC_CNT)
        {
            return ERR_IF;
        }

        Txbuffer[i].buffer = q->payload;
        Txbuffer[i].len = q->len;

        if (i > 0)
        {
            Txbuffer[i - 1].next = &Txbuffer[i];
        }

        if (q->next == NULL)
        {
            Txbuffer[i].next = NULL;
        }

        i++;
    }

    TxConfig.Length = (NULL != p) ? p->tot_len : 0;
    TxConfig.TxBuffer = Txbuffer;
    TxConfig.pData = p;

    pbuf_ref(p);

    HAL_ETH_Transmit_IT(&EthHandle, &TxConfig);

    osStatus_t status = osSemaphoreAcquire(TxPktSemaphore, TIME_WAITING_FOR_TX);

    switch (status)
    {
        case osOK:
        {
            errval = ERR_OK;
            break;
        }

        case osErrorTimeout:
        {
            errval = ERR_TIMEOUT;
            break;
        }

        case osErrorNoMemory:
        {
            errval = ERR_MEM;
            break;
        }

        default:
        {
            errval = ERR_IF;
            break;
        }
    }

    HAL_ETH_ReleaseTxPacket(&EthHandle);

    return errval;
}

/**
 * @brief Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf* low_level_input(struct netif *netif)
{
    struct pbuf *p = NULL;

    (void) netif;

    if (RxAllocStatus == RX_ALLOC_OK)
    {
        HAL_StatusTypeDef read_status = HAL_ETH_ReadData(&EthHandle, (void**) &p);

        if (HAL_OK != read_status)
        {
            p = NULL;
        }
    }

    return p;
}

/**
 * This task should be signaled when a receive packet is ready to be read
 * from the interface.
 *
 * @param argument the lwip network interface structure for this ethernetif
 */
static __attribute__((noreturn)) void ethernetif_input(void *argument)
{
    struct pbuf *p = NULL;
    struct netif *netif = (struct netif*) argument;

    for (;;)
    {
        osStatus_t semStatus = osSemaphoreAcquire(RxPktSemaphore, TIME_WAITING_FOR_INPUT);

        if (osOK == semStatus)
        {
            do
            {
                p = low_level_input(netif);
                if (p != NULL)
                {
                    if (netif->input(p, netif) != ERR_OK)
                    {
                        pbuf_free(p);
                    }
                }

            } while (p != NULL);
        }

        TaskMonitor_IamAlive(TASK_ETHERNET);
        vApplicationLowStackCheck(TASK_ETHERNET);
    }
}

/**
 * @brief Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t ethernetif_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME == 1
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

    /*
     * Initialize the snmp variables and counters inside the struct netif.
     * The last argument should be replaced with your link speed, in units
     * of bits per second.
     */
    MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;

    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

    /* initialize the hardware */
    low_level_init(netif);

    return ERR_OK;
}

/**
 * @brief  Custom Rx pbuf free callback
 * @param  pbuf: pbuf to be freed
 * @retval None
 */
void pbuf_free_custom(struct pbuf *p)
{
    struct pbuf_custom *custom_pbuf = (struct pbuf_custom*) p;
    LWIP_MEMPOOL_FREE(RX_POOL, custom_pbuf);

    if (RxAllocStatus == RX_ALLOC_ERROR)
    {
        RxAllocStatus = RX_ALLOC_OK;
        osSemaphoreRelease(RxPktSemaphore);
    }
}

/**
 * @brief  Returns the current time in milliseconds
 *         when LWIP_TIMERS == 1 and NO_SYS == 1
 * @param  None
 * @retval Current Time value
 */
u32_t sys_now(void)
{
    return HAL_GetTick();
}

// EN35IPHY enable input (active-HIGH); page 6
void HAL_ETH_Enable_PHY(void)
{
    HAL_GPIO_WritePin(GPIOH, ETH_EN_PIN, GPIO_PIN_SET);
}

void HAL_ETH_Disable_PHY(void)
{
    HAL_GPIO_WritePin(GPIOH, ETH_EN_PIN, GPIO_PIN_RESET);
}

void HAL_ETH_Reset_PHY(void)
{
    HAL_GPIO_WritePin(GPIOH, ETH_RST_PIN, GPIO_PIN_RESET);

    // pins RST_N, ENtdet(rst)reset detection time 5-20 uS

    //wait at minimum 40uS
    for (uint32_t i = 0; i < 400 * 40; i++)
    {
        __NOP();
    }

    HAL_GPIO_WritePin(GPIOH, ETH_RST_PIN, GPIO_PIN_SET);
}

void ETH_PHY_keep_in_reset(void)
{
    HAL_GPIO_WritePin(GPIOH, ETH_RST_PIN, GPIO_PIN_RESET);

    // pins RST_N, ENtdet(rst)reset detection time 5-20 uS

    //wait at minimum 40uS
    for (uint32_t i = 0; i < 400 * 40; i++)
    {
        __NOP();
    }
}
/*******************************************************************************
 Ethernet MSP Routines
 *******************************************************************************/
/**
 * @brief  Initializes the ETH MSP.
 * @param  heth: ETH handle
 * @retval None
 */
void HAL_ETH_MspInit(ETH_HandleTypeDef *ethHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    if (ethHandle->Instance == ETH)
    {
        __HAL_RCC_ETH1MAC_CLK_ENABLE();
        __HAL_RCC_ETH1TX_CLK_ENABLE();
        __HAL_RCC_ETH1RX_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOH_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /**ETH GPIO Configuration
         _PE2     ------> ETH_TXD3
         _PC1     ------> ETH_MDC
         _PC2_C     ------> ETH_TXD2
         _PC3_C     ------> ETH_TX_CLK
         _PA1     ------> ETH_RX_CLK
         _PA2     ------> ETH_MDIO
         -not connected- PH2     ------> ETH_CRS
         -not connected- PH3     ------> ETH_COL
         +PH2     ------> ETH_RST
         +PH3     ------> ETH_EN
         _PA7     ------> ETH_RX_DV
         _PC4     ------> ETH_RXD0
         _PC5     ------> ETH_RXD1
         +PH6     ------> ETH_RXD2
         _PB1     ------> ETH_RXD3
         _PB11     ------> ETH_TX_EN
         _PB12     ------> ETH_TXD0
         _PB13     ------> ETH_TXD1
         */

//        KEEP tja1100 in reset state while configuring pins
//        once configuration is done
//        ETH_PHY_keep_in_reset();
//        keep phy in disabled state while preparing the pins. Schematic keeps the PHY in disabled state but we ensure this as well
        HAL_ETH_Disable_PHY();

        // Initialize Ethernet Control pins RST and EN
        GPIO_InitStruct.Pin = ETH_RST_PIN | ETH_EN_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                | GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_11 | GPIO_PIN_12
                | GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Enable the Ethernet global Interrupt */
        HAL_NVIC_SetPriority(ETH_IRQn, 0x7, 0);
        HAL_NVIC_EnableIRQ(ETH_IRQn);

        // reset phy and enable it
        HAL_ETH_Reset_PHY();
        HAL_ETH_Enable_PHY();

        /* Set PHY IO functions */
        TJA1100_RegisterBusIO(&PHY_OBJ, &PHY_IOCtx);

        /* Initialize the ETH PHY */

        uint32_t tickstart = HAL_GetTick();

        while(PHY_STATUS_OK != TJA1100_Init(&PHY_OBJ))
        {
            if ((HAL_GetTick() - tickstart) > 2000U)
            {
                Error_Handler();
                //should not come here
                break;
            }
        }
    }
}

/**
 * @brief  Ethernet Rx Transfer completed callback
 * @param  heth: ETH handle
 * @retval None
 */
void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
    (void) heth;

    osSemaphoreRelease(RxPktSemaphore);
}

/**
 * @brief  Ethernet Tx Transfer completed callback
 * @param  heth: ETH handle
 * @retval None
 */
void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
{
    (void) heth;

    osSemaphoreRelease(TxPktSemaphore);
}

/**
 * @brief  Ethernet DMA transfer error callback
 * @param  heth: ETH handle
 * @retval None
 */
void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    if ((HAL_ETH_GetDMAError(heth) & ETH_DMACSR_RBU) == ETH_DMACSR_RBU)
    {
        osSemaphoreRelease(RxPktSemaphore);
    }

    if ((HAL_ETH_GetDMAError(heth) & ETH_DMACSR_TBU) == ETH_DMACSR_TBU)
    {
        osSemaphoreRelease(TxPktSemaphore);
    }
}

/*******************************************************************************
 PHI IO Functions
 *******************************************************************************/
/**
 * @brief  Initializes the MDIO interface GPIO and clocks.
 * @param  None
 * @retval 0 if OK, -1 if ERROR
 */
int32_t ETH_PHY_IO_Init(void)
{
    /* We assume that MDIO GPIO configuration is already done
     in the ETH_MspInit() else it should be done here
     */

    /* Configure the MDIO Clock */
    HAL_ETH_SetMDIOClockRange(&EthHandle);

    return 0;
}

/**
 * @brief  De-Initializes the MDIO interface .
 * @param  None
 * @retval 0 if OK, -1 if ERROR
 */
int32_t ETH_PHY_IO_DeInit(void)
{
    return 0;
}

/**
 * @brief  Read a PHY register through the MDIO interface.
 * @param  DevAddr: PHY port address
 * @param  RegAddr: PHY register address
 * @param  pRegVal: pointer to hold the register value
 * @retval 0 if OK -1 if Error
 */
int32_t ETH_PHY_IO_ReadReg(uint32_t DevAddr, uint32_t RegAddr, uint32_t *pRegVal)
{
    HAL_StatusTypeDef hal_status = HAL_ETH_ReadPHYRegister(&EthHandle, DevAddr, RegAddr, pRegVal);

    return (HAL_OK == hal_status) ? 0 : -1;
}

/**
 * @brief  Write a value to a PHY register through the MDIO interface.
 * @param  DevAddr: PHY port address
 * @param  RegAddr: PHY register address
 * @param  RegVal: Value to be written
 * @retval 0 if OK -1 if Error
 */
int32_t ETH_PHY_IO_WriteReg(uint32_t DevAddr, uint32_t RegAddr, uint32_t RegVal)
{
    HAL_StatusTypeDef hal_status = HAL_ETH_WritePHYRegister(&EthHandle, DevAddr, RegAddr, RegVal);

    return (HAL_OK == hal_status) ? 0 : -1;
}

/**
 * @brief  Get the time in millisecons used for internal PHY driver process.
 * @retval Time value
 */
int32_t ETH_PHY_IO_GetTick(void)
{
    return (int32_t) HAL_GetTick();
}

/**
 * @brief  Check the ETH link state and update netif accordingly.
 * @param  argument: netif
 * @retval None
 */
__attribute__((noreturn)) void ethernet_link_thread(void *arg)
{
    int32_t PHYLinkState = 0U;
    struct netif *netif = (struct netif*) arg;

    for (;;)
    {
        PHYLinkState = TJA1100_GetLinkState(&PHY_OBJ);

        if (netif_is_link_up(netif) > 0)
        {
            if (PHYLinkState <= PHY_STATUS_LINK_DOWN)
            {
                HAL_ETH_Stop_IT(&EthHandle);
                netif_set_down(netif);
                netif_set_link_down(netif);
            }
        }
        else
        {
            if (PHYLinkState > PHY_STATUS_LINK_DOWN)
            {
                HAL_ETH_Start_IT(&EthHandle);
                netif_set_up(netif);
                netif_set_link_up(netif);
            }
        }

        osDelay(100);
    }
}

void HAL_ETH_RxAllocateCallback(uint8_t **buff)
{
    struct pbuf_custom *p = LWIP_MEMPOOL_ALLOC(RX_POOL);

    if (NULL != p)
    {
        /* Get the buff from the struct pbuf address. */
        *buff = (uint8_t*) p + offsetof(RxBuff_t, buff);
        p->custom_free_function = pbuf_free_custom;
        /* Initialize the struct pbuf.
         * This must be performed whenever a buffer's allocated because it may be
         * changed by lwIP or the app, e.g., pbuf_free decrements ref. */
        pbuf_alloced_custom(PBUF_RAW, 0, PBUF_REF, p, *buff, ETH_RX_BUFFER_SIZE);
    }
    else
    {
        RxAllocStatus = RX_ALLOC_ERROR;
        *buff = NULL;
    }
}

void HAL_ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t Length)
{
    struct pbuf **ppStart = (struct pbuf**) pStart;
    struct pbuf **ppEnd = (struct pbuf**) pEnd;
    struct pbuf *p = NULL;

    /* Get the struct pbuf from the buff address. */
    p = (struct pbuf*) (buff - offsetof(RxBuff_t, buff));
    p->next = NULL;
    p->tot_len = 0;
    p->len = Length;

    /* Chain the buffer. */
    if (!*ppStart)
    {
        /* The first buffer of the packet. */
        *ppStart = p;
    }
    else
    {
        /* Chain the buffer to the end of the packet. */
        (*ppEnd)->next = p;
    }
    *ppEnd = p;

    /* Update the total length of all the buffers of the chain. Each pbuf in the chain should have its tot_len
     * set to its own length, plus the length of all the following pbufs in the chain. */
    for (p = *ppStart; p != NULL; p = p->next)
    {
        p->tot_len += Length;
    }

#ifdef USE_CACHE
    /* Invalidate data cache because Rx DMA's writing to physical memory makes it stale. */
    SCB_InvalidateDCache_by_Addr((uint32_t*) buff, Length);
#endif

}

void HAL_ETH_TxFreeCallback(uint32_t *buff)
{
    pbuf_free((struct pbuf*) buff);
}

/**
 * @brief  This function handles Ethernet interrupt request.
 */
void ETH_IRQHandler(void)
{
    HAL_ETH_IRQHandler(&EthHandle);
}

#ifdef USE_CACHE
/**
  * @brief  Configure the MPU attributes
  * @param  None
  * @retval None
  */
static void mpu_config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU as Strongly ordered for not defined regions */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x00;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU attributes as Device not cacheable
     for ETH DMA descriptors */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x30000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_1KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU attributes as Normal Non Cacheable
     for LwIP RAM heap which contains the Tx buffers */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x30004000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_16KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void cpu_cache_enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
#endif
