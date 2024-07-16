/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/** @file sio.c
 *
 * @brief Serial driver implementation for the Ethernet SLIP interface
 *
 * Rx operation is performed via DMA, while Tx operation is using blocking transmit HAL calls for
 * efficiency since this is actually how the SIO interface expects the operation to be performed in
 * the netw context. This is also how maximum throughput is achieved avoiding unnecessary task context
 * switches as the transmission occurs directly in the calling TCP/IP task. Short timeouts are provided to
 * ensure the calling task will not block indefinitely, hence breaking other TCP/IP operations.
 *
 */

#include <string.h>
#include "es_cdef.h"
#include "stm32h7xx_hal.h"
#include "lwip/sio.h"
#include "cmsis_os2.h"
#include "slipif_cfg.h"
#include "core/middlewares/external/lwIP/src/include/netif/slipif.h"
#include "TaskMonitor.h"
#include "trace.h"
#include "debug.h"

#define DMA_RX_ARM_FAILURE_EVENT    (0x01U)

typedef struct
{
    slipif_net_cfg_t *p_slipif_net_cfg;      /**< a pointer to the SLIP network interface configuration */
    slipif_uart_cfg_t *p_slip_cfg;           /**< a pointer to the SLIP UART configuration */
    uint8_t dma_rx_buf[32U];                 /**< DMA buffer used for reception on the SLIP interface */
    bool init_finished : 1;                  /**< indicates if the initialization sequence is over */
    osThreadId_t com_monitor_task_id;        /**< DMA Rx monitor task */
    osEventFlagsId_t evt_id;                 /**< monitor task OS event */
} sio_descriptor_t;

/** @brief SLIP interface descriptors list */
STATIC sio_descriptor_t sio_descriptor[1U] =
{
    {
        .init_finished = false,
        .p_slip_cfg = NULL,
        .dma_rx_buf = { 0 },
        .p_slipif_net_cfg = NULL,
        .com_monitor_task_id = NULL
    }
};

STATIC const osThreadAttr_t slip_com_mon_task_attr =
{
    .attr_bits = osThreadDetached,
    .name      = "slip_com_monitor_task",
    .priority  = osPriorityAboveNormal,
    .cb_mem    = NULL,
    .cb_size   = 0U,
    .stack_mem = NULL,
    .stack_size = 500U
};

STATIC void slip_com_recovery_task(void *arg);
STATIC bool arm_dma_rx(sio_descriptor_t * const p_descr);
STATIC inline sio_descriptor_t *get_sio_descr_by_uart_hnd(UART_HandleTypeDef * const p_uart_hnd, uint8_t * const p_dev_num);
STATIC void uart_error_cb(UART_HandleTypeDef* p_uart);
STATIC void uart_rx_event_cb(struct __UART_HandleTypeDef *p_uart, uint16_t Pos);
STATIC void uart_msp_init_cb(UART_HandleTypeDef* p_uart);
STATIC void uart_msp_deinit_cb(UART_HandleTypeDef* p_uart);
STATIC void uart_init(u8_t devnum);

STATIC bool arm_dma_rx(sio_descriptor_t * const p_descr)
{
    bool res = false;

    CRIT_ASSERT(NULL != p_descr);

    HAL_StatusTypeDef hal_stat = HAL_ERROR;

    hal_stat = HAL_UART_AbortReceive(p_descr->p_slip_cfg->p_uart);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UART_AbortReceive() failed with code '%d'!", hal_stat);
    }
    else
    {
        hal_stat = HAL_UARTEx_ReceiveToIdle_DMA(p_descr->p_slip_cfg->p_uart, (uint8_t *) p_descr->dma_rx_buf, sizeof(p_descr->dma_rx_buf));

        if (HAL_OK != hal_stat)
        {
            if (HAL_OK != hal_stat)
            {
                ES_TRACE_ERROR("HAL_UARTEx_ReceiveToIdle_DMA() failed with code '%d'!", hal_stat);

                hal_stat = HAL_UART_AbortReceive(p_descr->p_slip_cfg->p_uart);

                if (HAL_OK != hal_stat)
                {
                    ES_TRACE_ERROR("HAL_UART_AbortReceive() failed with code '%d'!", hal_stat);
                }
                else
                {
                    ES_TRACE_WARN("DMA Rx rearmed...\r\n");
                }
            }
        }
        else
        {
            res = true;
        }
    }

    return res;
}

/**
 * @brief Returns an internal Serial IO decscriptor based on the registered UART instance handle pointer.
 *
 * @param[in] p_uart_hnd UART instance handle pointer
 * @param[out] p_dev_num internal SLIP device ID corresponding to the provided p_uart_hnd
 */
STATIC inline sio_descriptor_t *get_sio_descr_by_uart_hnd(UART_HandleTypeDef * const p_uart_hnd, uint8_t * const p_dev_num)
{
    sio_descriptor_t *p_descr = NULL;

    for (uint8_t idx = 0; idx < CDEF_ELEMENT_COUNT(sio_descriptor); idx++)
    {
        if (p_uart_hnd == sio_descriptor[idx].p_slip_cfg->p_uart)
        {
            p_descr = &sio_descriptor[idx];

            if (NULL != p_dev_num)
            {
                *p_dev_num = idx;
            }
        }
    }

    return p_descr;
}

/**
 * @brief HAL UART callback executed on error.
 *
 * @param[in] p_uart UART instance handle pointer
 */
STATIC void uart_error_cb(UART_HandleTypeDef* p_uart)
{
    sio_descriptor_t *p_descr = get_sio_descr_by_uart_hnd(p_uart, NULL);

    CRIT_ASSERT(NULL != p_descr);

    if (NULL != p_descr)
    {
        if (p_uart->Instance == p_descr->p_slip_cfg->p_uart->Instance)
        {
            __HAL_UART_CLEAR_OREFLAG(p_uart);
            __HAL_UART_CLEAR_NEFLAG(p_uart);
            __HAL_UART_CLEAR_FEFLAG(p_uart);
            __HAL_UART_DISABLE_IT(p_uart, UART_IT_ERR);
        }
    }
}

/**
 * @brief UART HAL callback registered for execution upon reception of a block of data over DMA.
 *
 * The callback runs when the UART detects a bus IDLE condition, providing the data that was captured
 * before the bus IDLE event.
 *
 * @param[in] p_uart UART handle instance pointer
 * @param[in] Pos byte position in the pre-assigned DMA Rx buffer of the last received byte
 *
 * @note The callback ensures that DMA reception starts all over after reading the data and feeding it to
 *       the Ethernet stack via a call to @ref slipif_received_bytes().
 */
STATIC void uart_rx_event_cb(struct __UART_HandleTypeDef *p_uart, uint16_t Pos)
{
    sio_descriptor_t *p_descr = get_sio_descr_by_uart_hnd(p_uart, NULL);

    CRIT_ASSERT(NULL != p_descr);
    CRIT_ASSERT(p_uart->Instance == p_descr->p_slip_cfg->p_uart->Instance);

    if (NULL != p_descr)
    {
        slipif_received_bytes(&p_descr->p_slipif_net_cfg->slipnet_if, p_descr->dma_rx_buf, Pos);

        if (!arm_dma_rx(p_descr))
        {
            uint32_t evt_res = osEventFlagsSet(p_descr->evt_id, DMA_RX_ARM_FAILURE_EVENT);

            if ((int32_t) evt_res < (int32_t) osOK)
            {
                ES_TRACE_ERROR("osEventFlagsSet(RX_EVENT) failed with code '%i'!", evt_res);
            }

        }
    }
}

/**
 * @brief UART HAL callback registered for execution upon HAL_UART_Init() call.
 *
 * @param[in] p_uart UART handle instance pointer
 */
STATIC void uart_msp_init_cb(UART_HandleTypeDef* p_uart)
{
    uint8_t devnum = CDEF_ELEMENT_COUNT(sio_descriptor);
    sio_descriptor_t *p_descr = get_sio_descr_by_uart_hnd(p_uart, &devnum);

    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(sio_descriptor));
    CRIT_ASSERT(NULL != p_descr);
    CRIT_ASSERT(p_uart->Instance == p_descr->p_slip_cfg->p_uart->Instance);

    if (NULL != p_descr)
    {
        GPIO_InitTypeDef gpio_init_struct = { 0 };

        slipif_cfg_ctl(SLIPIF_CMD_CLK_ENABLE, devnum);

        gpio_init_struct.Pin       = p_descr->p_slip_cfg->rx_pin;
        gpio_init_struct.Mode      = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull      = GPIO_NOPULL;
        gpio_init_struct.Speed     = GPIO_SPEED_FREQ_LOW;
        gpio_init_struct.Alternate = p_descr->p_slip_cfg->af;
        HAL_GPIO_Init(sio_descriptor[devnum].p_slip_cfg->p_rx_gpio_port, &gpio_init_struct);

        gpio_init_struct.Pin       = p_descr->p_slip_cfg->tx_pin;
        gpio_init_struct.Mode      = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull      = GPIO_NOPULL;
        gpio_init_struct.Speed     = GPIO_SPEED_FREQ_LOW;
        gpio_init_struct.Alternate = p_descr->p_slip_cfg->af;
        HAL_GPIO_Init(p_descr->p_slip_cfg->p_tx_gpio_port, &gpio_init_struct);

        p_descr->p_slip_cfg->p_uart_dma_rx->Init.Direction = DMA_PERIPH_TO_MEMORY;
        p_descr->p_slip_cfg->p_uart_dma_rx->Init.PeriphInc = DMA_PINC_DISABLE;
        p_descr->p_slip_cfg->p_uart_dma_rx->Init.MemInc = DMA_MINC_ENABLE;
        p_descr->p_slip_cfg->p_uart_dma_rx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        p_descr->p_slip_cfg->p_uart_dma_rx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        p_descr->p_slip_cfg->p_uart_dma_rx->Init.Mode = DMA_NORMAL;
        p_descr->p_slip_cfg->p_uart_dma_rx->Init.Priority = DMA_PRIORITY_MEDIUM;
        p_descr->p_slip_cfg->p_uart_dma_rx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;

        HAL_StatusTypeDef hal_stat = HAL_DMA_Init(p_descr->p_slip_cfg->p_uart_dma_rx);

        if (HAL_OK != hal_stat)
        {
            ES_TRACE_ERROR("HAL_DMA_Init() failed with code '%d'!", hal_stat);
        }
    }
}

/**
 * @brief UART HAL callback registered for execution upon HAL_UART_Deinit() call.
 *
 * @param[in] p_uart UART handle instance pointer
 */
STATIC void uart_msp_deinit_cb(UART_HandleTypeDef* p_uart)
{
    uint8_t devnum = CDEF_ELEMENT_COUNT(sio_descriptor);
    sio_descriptor_t *p_descr = get_sio_descr_by_uart_hnd(p_uart, &devnum);

    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(sio_descriptor));
    CRIT_ASSERT(NULL != p_descr);
    CRIT_ASSERT(p_uart->Instance == p_descr->p_slip_cfg->p_uart->Instance);

    if (NULL != p_descr)
    {
        slipif_cfg_ctl(SLIPIF_CMD_CLK_DISABLE, devnum);

        HAL_GPIO_DeInit(p_descr->p_slip_cfg->p_rx_gpio_port, p_descr->p_slip_cfg->rx_pin);
        HAL_GPIO_DeInit(p_descr->p_slip_cfg->p_tx_gpio_port, p_descr->p_slip_cfg->tx_pin);

        (void) HAL_DMA_DeInit(p_descr->p_slip_cfg->p_uart_dma_rx);

        slipif_cfg_ctl(SLIPIF_CMD_IRQ_DISABLE, devnum);
    }
}

/**
 * @brief Initializes the SLIP UART for communication.
 *
 * @param[in] devnum SLIP device ID
 */
STATIC void uart_init(u8_t devnum)
{
    HAL_StatusTypeDef hal_stat = HAL_ERROR;

    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(sio_descriptor));

    hal_stat = HAL_UART_RegisterCallback(sio_descriptor[devnum].p_slip_cfg->p_uart, HAL_UART_MSPINIT_CB_ID, &uart_msp_init_cb);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UART_RegisterCallback(HAL_UART_MSPINIT_CB_ID) failed with code '%d'!", hal_stat);
    }

    hal_stat = HAL_UART_RegisterCallback(sio_descriptor[devnum].p_slip_cfg->p_uart, HAL_UART_MSPDEINIT_CB_ID, &uart_msp_deinit_cb);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UART_RegisterCallback(HAL_TIM_BASE_MSPDEINIT_CB_ID) failed with code '%d'!", hal_stat);
    }

    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.BaudRate = SLIP_UART_SPEED_BPS;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.WordLength = UART_WORDLENGTH_8B;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.StopBits = UART_STOPBITS_1;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.Parity = UART_PARITY_NONE;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.Mode = UART_MODE_TX_RX;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.OverSampling = UART_OVERSAMPLING_16;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    sio_descriptor[devnum].p_slip_cfg->p_uart->Init.ClockPrescaler = UART_PRESCALER_DIV1;
    sio_descriptor[devnum].p_slip_cfg->p_uart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT | UART_ADVFEATURE_DMADISABLEONERROR_INIT;
    sio_descriptor[devnum].p_slip_cfg->p_uart->AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
    sio_descriptor[devnum].p_slip_cfg->p_uart->AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;

    hal_stat = HAL_UART_Init(sio_descriptor[devnum].p_slip_cfg->p_uart);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UART_Init() failed with code '%d'!", hal_stat);
    }

    hal_stat = HAL_UARTEx_SetTxFifoThreshold(sio_descriptor[devnum].p_slip_cfg->p_uart, UART_TXFIFO_THRESHOLD_1_2);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UARTEx_SetTxFifoThreshold() failed with code '%d'!", hal_stat);
    }

    hal_stat = HAL_UARTEx_SetRxFifoThreshold(sio_descriptor[devnum].p_slip_cfg->p_uart, UART_TXFIFO_THRESHOLD_1_2);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UARTEx_SetRxFifoThreshold() failed with code '%d'!", hal_stat);
    }

    hal_stat = HAL_UARTEx_EnableFifoMode(sio_descriptor[devnum].p_slip_cfg->p_uart);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UARTEx_DisableFifoMode() failed with code '%d'!", hal_stat);
    }

    hal_stat = HAL_UART_RegisterCallback(sio_descriptor[devnum].p_slip_cfg->p_uart, HAL_UART_ERROR_CB_ID, &uart_error_cb);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UART_RegisterCallback(HAL_UART_ERROR_CB_ID) failed with code '%d'!", hal_stat);
    }

    hal_stat = HAL_UART_RegisterRxEventCallback(sio_descriptor[devnum].p_slip_cfg->p_uart, &uart_rx_event_cb);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UART_RegisterRxEventCallback() failed with code '%d'!", hal_stat);
    }

    slipif_cfg_ctl(SLIPIF_CMD_IRQ_ENABLE, devnum);
}

/**
 * Opens a serial device for communication.
 *
 * @param devnum device number
 * @return handle to serial device if successful, NULL otherwise
 */
sio_fd_t sio_open(u8_t devnum)
{
    sio_fd_t dev_fd = NULL;

    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(sio_descriptor));

    if (devnum < CDEF_ELEMENT_COUNT(sio_descriptor))
    {
        sio_descriptor[devnum].p_slip_cfg = slipif_uart_cfg_get(devnum);
        sio_descriptor[devnum].p_slipif_net_cfg = slipif_net_cfg_get(devnum);

        uart_init(devnum);

        (void) memset((void *) sio_descriptor[devnum].dma_rx_buf, 0U, sizeof(sio_descriptor[devnum].dma_rx_buf));

        if (NULL == sio_descriptor[devnum].evt_id)
        {
            sio_descriptor[devnum].evt_id = osEventFlagsNew(NULL);
        }

        if (NULL == sio_descriptor[devnum].com_monitor_task_id)
        {
            sio_descriptor[devnum].com_monitor_task_id = osThreadNew(&slip_com_recovery_task,
                                                                        (void *) ((uint32_t) devnum),
                                                                        &slip_com_mon_task_attr);
        }

        dev_fd = &sio_descriptor[devnum];

        sio_descriptor[devnum].init_finished = true;

        (void) arm_dma_rx(&sio_descriptor[devnum]);
    }

    return dev_fd;
}

/**
 * Sends a single character to the serial device.
 *
 * @param c character to send
 * @param fd serial device handle
 *
 * @note This function will block until the character can be sent.
 */
void sio_send(u8_t c, sio_fd_t fd)
{
    sio_write(fd, (u8_t *) &c, 1);
}

/**
 * Receives a single character from the serial device.
 *
 * @param fd serial device handle
 *
 * @note This function will block until a character is received.
 */
u8_t sio_recv(sio_fd_t fd)
{
    uint8_t data = 0U;

    uint32_t bytes_read = sio_read(fd, &data, 1);

    if (0U == bytes_read)
    {
        ES_TRACE_ERROR("sio_read() failed!");
    }

    return data;
}

/**
 * Reads from the serial device.
 *
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received - may be 0 if aborted by sio_read_abort
 *
 * @note The function is not implemented because reception is performed via DMA through the
 * @ref uart_rx_event_cb() function called by the UART HAL callback mechanism.
 *
 */
u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len)
{
    CRIT_ASSERT(false);

    (void) fd;
    (void) data;
    (void) len;

    return 0;
}

/**
 * Tries to read from the serial device. Same as sio_read but returns
 * immediately if no data is available and never blocks.
 *
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received
 */
u32_t sio_tryread(sio_fd_t fd, u8_t *data, u32_t len)
{
    CRIT_ASSERT(false);

    (void) fd;
    (void) data;
    (void) len;

    return 0;
}

/**
 * Writes to the serial device.
 *
 * @param fd serial device handle
 * @param data pointer to data to send
 * @param len length (in bytes) of data to send
 * @return number of bytes actually sent
 *
 * @note This function will block until all data can be sent.
 */
u32_t sio_write(sio_fd_t fd, u8_t *data, u32_t len)
{
    sio_descriptor_t *p_descr = (sio_descriptor_t *) fd;
    u32_t bytes_sent = 0;

    if (p_descr->init_finished)
    {
        for (uint8_t b_idx = 0; b_idx < len; b_idx++)
        {
            HAL_StatusTypeDef hal_stat = HAL_UART_Transmit(p_descr->p_slip_cfg->p_uart, &data[b_idx], (uint16_t) 1, 10);

            if (HAL_OK != hal_stat)
            {
                ES_TRACE_ERROR("HAL_UART_Transmit() failed with code '%d'!", hal_stat);
                break;
            }
            else
            {
                bytes_sent++;
            }
        }
    }

    return bytes_sent;
}

/**
 * Aborts a blocking sio_read() call.
 *
 * @param fd serial device handle
 */
void sio_read_abort(sio_fd_t fd)
{
    sio_descriptor_t *p_descr = (sio_descriptor_t *) fd;
    CRIT_ASSERT(NULL != p_descr);

    HAL_StatusTypeDef hal_stat = HAL_UART_AbortReceive(p_descr->p_slip_cfg->p_uart);

    if (HAL_OK != hal_stat)
    {
        ES_TRACE_ERROR("HAL_UART_AbortReceive() failed with code '%d'!", hal_stat);
    }
}

/** @brief SLIP RX recovery task
 *
 *  The task is responsible to recover DMA operation in case of HAL driver issue.
 *  DMA reception.
 *
 *  @param[in] arg represents the device ID for the SLIP interface to recover
 *
 */
STATIC void slip_com_recovery_task(void *arg)
{
    uint8_t devnum = (uint8_t) ((uint32_t) arg);

    CRIT_ASSERT(devnum < CDEF_ELEMENT_COUNT(sio_descriptor));

    while (true)
    {
        if (sio_descriptor[devnum].init_finished)
        {
            uint32_t evt_res = osEventFlagsWait(sio_descriptor[devnum].evt_id, DMA_RX_ARM_FAILURE_EVENT, osFlagsWaitAny, 5000);

            if ((int32_t) DMA_RX_ARM_FAILURE_EVENT == (int32_t) evt_res)
            {
                (void) arm_dma_rx(&sio_descriptor[devnum]);
            }
        }

        TaskMonitor_IamAlive(TASK_SLIP);
        vApplicationLowStackCheck(TASK_SLIP);

        osDelay(10);
    }
}
