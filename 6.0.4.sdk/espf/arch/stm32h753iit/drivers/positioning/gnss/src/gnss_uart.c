/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_uart.c
 *
 *
 * @}
 * @}
 */
#include "gnss_uart.h"
#include "gnss_irq.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_uart.h"
#include "stm32h7xx_hal_dma.h"
#include "cmsis_os2.h"
#include <string.h>


/** @brief RX queue length */
#define FS_RX_Q_SZ  3


static void fs_msp_init_callback  (UART_HandleTypeDef* huart);
static void fs_msp_deinit_callback(UART_HandleTypeDef* huart);
static void fs_rx_event_callback  (UART_HandleTypeDef* huart, uint16_t size);


/** @brief UART handle */
static UART_HandleTypeDef fs_huart =
{
    .Instance                         = UART5,
    .Init.WordLength                  = UART_WORDLENGTH_8B,
    .Init.StopBits                    = UART_STOPBITS_1,
    .Init.Parity                      = UART_PARITY_NONE,
    .Init.Mode                        = UART_MODE_TX_RX,
    .Init.HwFlowCtl                   = UART_HWCONTROL_NONE,
    .Init.OverSampling                = UART_OVERSAMPLING_16,
    .Init.OneBitSampling              = UART_ONE_BIT_SAMPLE_DISABLE,
    .Init.ClockPrescaler              = UART_PRESCALER_DIV1,
    .AdvancedInit.AdvFeatureInit      = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT,
    .AdvancedInit.OverrunDisable      = UART_ADVFEATURE_OVERRUN_DISABLE,
    .AdvancedInit.AdvFeatureInit      = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT | UART_ADVFEATURE_DMADISABLEONERROR_INIT,
    .AdvancedInit.OverrunDisable      = UART_ADVFEATURE_OVERRUN_DISABLE,
    .AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR,
    .MspInitCallback                  = fs_msp_init_callback,
    .MspDeInitCallback                = fs_msp_deinit_callback
};

/** @brief DMA handle */
static DMA_HandleTypeDef fs_hdma_uart_rx =
{
    .Instance                 = DMA2_Stream1,
    .Init.Request             = DMA_REQUEST_UART5_RX,
    .Init.Direction           = DMA_PERIPH_TO_MEMORY,
    .Init.PeriphInc           = DMA_PINC_DISABLE,
    .Init.MemInc              = DMA_MINC_ENABLE,
    .Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
    .Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE,
    .Init.Mode                = DMA_NORMAL,
    .Init.Priority            = DMA_PRIORITY_LOW,
    .Init.FIFOMode            = DMA_FIFOMODE_DISABLE
};

/** @brief UART RX queue used to store receive messages */
static osMessageQueueId_t fs_rx_q = NULL;

/** @brief UART RX buffer to be filled by DMA */
static volatile gnss_uart_resp_t fs_rx_msg;

/** @brief pointer to user-defined callback which is called on every RX event */
static gnss_uart_rx_callback fs_rx_user_callback = NULL;


bool gnss_uart_reg(gnss_uart_rx_callback callback)
{
    bool ret = false;

    if (NULL != callback)
    {
        fs_rx_user_callback = callback;
        ret = true;
    }

    return ret;
}


bool gnss_uart_init(const uint32_t baudrate)
{
    if (NULL == fs_rx_q)
    {
        fs_rx_q = osMessageQueueNew(FS_RX_Q_SZ, sizeof(gnss_uart_resp_t), NULL);

        if (NULL == fs_rx_q)
        {
            return false;
        }
    }

    fs_huart.Init.BaudRate = baudrate;

    if (HAL_OK != HAL_UART_Init(&fs_huart))
    {
        return false;
    }

    __HAL_RCC_DMA2_CLK_ENABLE();

    if (HAL_OK != HAL_DMA_Init(&fs_hdma_uart_rx))
    {
        return false;
    }

    __HAL_LINKDMA(&fs_huart, hdmarx, fs_hdma_uart_rx);

    __HAL_DMA_DISABLE_IT(&fs_hdma_uart_rx, DMA_IT_HT);

    if ((HAL_OK != HAL_UART_RegisterRxEventCallback(&fs_huart, fs_rx_event_callback)) ||
        (HAL_OK != HAL_UART_AbortReceive(&fs_huart)) ||
        (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&fs_huart, (uint8_t*)fs_rx_msg.data, sizeof(fs_rx_msg.data))))
    {
        return false;
    }

    HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

    HAL_NVIC_SetPriority(UART5_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);

    return true;
}


bool gnss_uart_deinit(void)
{
    HAL_NVIC_DisableIRQ(DMA2_Stream1_IRQn);
    HAL_NVIC_DisableIRQ(UART5_IRQn);

    if (HAL_OK != HAL_UART_DeInit(&fs_huart))
    {
        return false;
    }

    if (HAL_OK != HAL_DMA_DeInit(&fs_hdma_uart_rx))
    {
        return false;
    }

    return true;
}


bool gnss_uart_tx(const uint8_t* data, const uint16_t data_sz)
{
    bool res = false;

    if (HAL_OK == HAL_UART_Transmit(&fs_huart, (uint8_t*)data, data_sz, 1000))
    {
        res = true;
    }

    return res;
}


bool gnss_uart_rx(gnss_uart_resp_t* resp)
{
    bool ret = false;
    uint8_t msg_prio;

    if ((NULL != resp) &&
        (NULL != fs_rx_q) &&
        (osOK == osMessageQueueGet(fs_rx_q, (void*)resp, &msg_prio, 0)))
    {
        ret = true;
    }

    return ret;
}


void gnss_irq_uart_handler(void)
{
    HAL_UART_IRQHandler(&fs_huart);
}


void gnss_irq_dma_handler(void)
{
    HAL_DMA_IRQHandler(&fs_hdma_uart_rx);
}


/**
 * @brief Initializes the UART MSP
 *
 * @param[in] huart UART handle
 */
static void fs_msp_init_callback(UART_HandleTypeDef* huart)
{
    if ((UART5 == huart->Instance) && (huart == &fs_huart))
    {
        __HAL_RCC_UART5_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitTypeDef gpio_init_struct = { 0 };
        gpio_init_struct.Pin       = GPIO_PIN_5 | GPIO_PIN_6;
        gpio_init_struct.Mode      = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull      = GPIO_NOPULL;
        gpio_init_struct.Speed     = GPIO_SPEED_FREQ_LOW;
        gpio_init_struct.Alternate = GPIO_AF14_UART5;
        HAL_GPIO_Init(GPIOB, &gpio_init_struct);
    }
}


/**
 * @brief DeInitializes the UART MSP
 *
 * @param[in] huart UART handle
 */
static void fs_msp_deinit_callback(UART_HandleTypeDef* huart)
{
    if ((UART5 == huart->Instance) && (huart == &fs_huart))
    {
        __HAL_RCC_UART5_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5 | GPIO_PIN_6);
    }
}


/**
 * @brief Reception event callback
 *
 * @param[in] huart UART handle
 * @param[in] size  Number of data available in application reception buffer
 */
static void fs_rx_event_callback(UART_HandleTypeDef* huart, uint16_t size)
{
    if ((UART5 == huart->Instance) && (huart == &fs_huart))
    {
        fs_rx_msg.data_sz = size;

        if ((NULL != fs_rx_q) &&
            (NULL != fs_rx_user_callback))
        {
            (void)osMessageQueuePut(fs_rx_q, (const void*)&fs_rx_msg, 0, 0);

            fs_rx_user_callback();
        }

        (void)HAL_UARTEx_ReceiveToIdle_DMA(&fs_huart, (uint8_t*)fs_rx_msg.data, sizeof(fs_rx_msg.data));

        __HAL_DMA_DISABLE_IT(&fs_hdma_uart_rx, DMA_IT_HT);
    }
}
