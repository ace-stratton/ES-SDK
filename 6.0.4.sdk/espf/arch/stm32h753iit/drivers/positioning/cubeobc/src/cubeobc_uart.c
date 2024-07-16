/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup CubeAdcsGen2
 * @{
 *
 * @file cubeobc_uart.c
 *
 * @brief CubeAdcsGen2 driver implementation
 *
 * @}
 */

#include "cubeobc_uart.h"
#include "cubeobc_uart_defs.h"
#include "trace.h"
#include "assertions.h"
#include "TaskMonitor.h"
#include "cmsis_os2.h"
#include <cubeObc/cubeObc_errorDef.h>
#include <cubeObc/interfaces/cubeObc_uartIfc.h>
#include <string.h>



/** @brief UART RX Q size */
#define FS_UART_RXQ_SIZE        1

/** @brief UART init/deinit/reinit queue size */
#define FS_UART_INIQ_SIZE       10

/** @brief UART init/deinit/reinit queue request types */
typedef uint8_t fs_uart_req_t;
#define FS_UART_REQ_INIT        ((fs_uart_req_t)1)
#define FS_UART_REQ_DEINIT      ((fs_uart_req_t)2)
#define FS_UART_REQ_REINIT      ((fs_uart_req_t)3)


/**
 * @brief TC/TLM protocol max frame size as per documentation
 */
#define FS_COMM_BUF_SZ (512)


/**
 * @brief Defines Cubeobc uart RX message
 */
typedef struct
{
    uint8_t  data[FS_COMM_BUF_SZ]; /**< message buffer */
    uint32_t size;                 /**< message size */
} fs_uart_rx_msg_t;


static void fs_uart_msp_init_callback(UART_HandleTypeDef* huart);
static void fs_uart_msp_deinit_callback(UART_HandleTypeDef* huart);
static void fs_uart_err_callback(UART_HandleTypeDef* huart);
static void fs_uart_rx_event_callback(UART_HandleTypeDef* huart, uint16_t size);
static void fs_uart_thread(void* args);



/** @brief UART handle */
static UART_HandleTypeDef fs_huart =
{
    .Instance                         = CUBEOBC_UART_INSTANCE,
    .Init.BaudRate                    = CUBEOBC_UART_BAUDRATE,
    .Init.WordLength                  = UART_WORDLENGTH_8B,
    .Init.StopBits                    = UART_STOPBITS_1,
    .Init.Parity                      = UART_PARITY_NONE,
    .Init.Mode                        = UART_MODE_TX_RX,
    .Init.HwFlowCtl                   = UART_HWCONTROL_NONE,
    .Init.OverSampling                = UART_OVERSAMPLING_16,
    .Init.OneBitSampling              = UART_ONE_BIT_SAMPLE_DISABLE,
    .Init.ClockPrescaler              = UART_PRESCALER_DIV1,
    .AdvancedInit.AdvFeatureInit      = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT | UART_ADVFEATURE_DMADISABLEONERROR_INIT,
    .AdvancedInit.OverrunDisable      = UART_ADVFEATURE_OVERRUN_DISABLE,
    .AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR,
    .MspInitCallback                  = fs_uart_msp_init_callback,
    .MspDeInitCallback                = fs_uart_msp_deinit_callback,
};

/** @brief DMA handle */
static DMA_HandleTypeDef fs_hdma_uart_rx =
{
    .Instance                         = CUBEOBC_DMA_RX_INSTANCE,
    .Init.Request                     = CUBEOBC_DMA_RX_REQUEST_RX,
    .Init.Direction                   = DMA_PERIPH_TO_MEMORY,
    .Init.PeriphInc                   = DMA_PINC_DISABLE,
    .Init.MemInc                      = DMA_MINC_ENABLE,
    .Init.PeriphDataAlignment         = DMA_PDATAALIGN_BYTE,
    .Init.MemDataAlignment            = DMA_MDATAALIGN_BYTE,
    .Init.Mode                        = DMA_NORMAL,
    .Init.Priority                    = DMA_PRIORITY_LOW,
    .Init.FIFOMode                    = DMA_FIFOMODE_DISABLE,
};

/** @brief used to read messages from DMA in IRQ context */
static volatile fs_uart_rx_msg_t fs_rx_msg;

/** @brief RX queue handle */
static osMessageQueueId_t fs_rxq = NULL;

/** @brief init/deinit/reinit queue handle */
static osMessageQueueId_t fs_iniq = NULL;

/** @brief lock handle that ensures thread safe operations */
static osMutexId_t fs_lock = NULL;

/** @brief init/deinit/reinit thread handle */
static osThreadId_t fs_thread = NULL;



bool cubeobc_uart_init(void)
{
    if (NULL == fs_lock)
    {
        osMutexAttr_t attr =
        {
            .name      = NULL,
            .attr_bits = osMutexRecursive | osMutexPrioInherit,
            .cb_mem    = NULL,
            .cb_size   = 0U
        };

        fs_lock = osMutexNew(&attr);

        if (NULL == fs_lock)
        {
            return false;
        }
    }

    if (NULL == fs_thread)
    {
        osThreadAttr_t attr =
        {
            .attr_bits  = osThreadDetached,
            .name       = "cubeobc_uart",
            .priority   = osPriorityNormal,
            .cb_mem     = NULL,
            .cb_size    = 0U,
            .stack_mem  = NULL,
            .stack_size = 800,
            .tz_module  = 0U,
            .reserved   = 0U,
        };

        fs_thread = osThreadNew(fs_uart_thread, NULL, &attr);

        if (NULL == fs_thread)
        {
            return false;
        }
    }

    if (NULL == fs_rxq)
    {
        fs_rxq = osMessageQueueNew(FS_UART_RXQ_SIZE, sizeof(fs_uart_rx_msg_t), NULL);

        if (NULL == fs_rxq)
        {
            return false;
        }
    }

    if (NULL == fs_iniq)
    {
        fs_iniq = osMessageQueueNew(FS_UART_INIQ_SIZE, sizeof(fs_uart_req_t), NULL);

        if (NULL == fs_iniq)
        {
            return false;
        }
    }

    fs_uart_req_t req = FS_UART_REQ_INIT;

    if (osOK != osMessageQueuePut(fs_iniq, (const void*)&req, 0, 0))
    {
        return false;
    }

    return true;
}


bool cubeobc_uart_deinit(void)
{
    bool ret = false;
    fs_uart_req_t req = FS_UART_REQ_DEINIT;

    if ((NULL != fs_iniq) &&
        (osOK == osMessageQueuePut(fs_iniq, (const void*)&req, 0, 0)))
    {
        ret = true;
    }

    return ret;
}


void cubeobc_uart_irq_handler(void)
{
    HAL_UART_IRQHandler(&fs_huart);
}


void cubeobc_uart_dma_irq_handler(void)
{
    HAL_DMA_IRQHandler(&fs_hdma_uart_rx);
}


/**
 * @brief Blocking transmit
 *
 * @param[in] data    Data to transmit
 * @param[in] data_sz Data size in bytes
 *
 * @retval true  Transmit success
 * @retval false Transmit fail
 */
static bool fs_uart_tx(const uint8_t* data, const uint32_t data_sz)
{
    CRIT_ASSERT(NULL != data);
    CRIT_ASSERT(0 < data_sz);

    bool ret = false;
    HAL_StatusTypeDef status = HAL_ERROR;


    if ((NULL != data) &&
        (0 < data_sz) &&
        (NULL != fs_lock) &&
        (osOK == osMutexAcquire(fs_lock, osWaitForever)))
    {
        uint32_t timeout = data_sz * 100;
        status = HAL_UART_Transmit(&fs_huart, (uint8_t*)data, (uint16_t)data_sz, timeout);

        if (HAL_OK == status)
        {
            ret = true;
        }
        else
        {
            ES_TRACE_ERROR("tx fail");

            // signal the thread to re-initialize the whole communication
            fs_uart_req_t req = FS_UART_REQ_REINIT;

            (void)osMessageQueuePut(fs_iniq, (const void*)&req, 0, 0);
        }

        (void)osMutexRelease(fs_lock);
    }

    return ret;
}


/**
 * @brief Non-blocking receive
 *
 * @param[out] msg RX message
 *
 * @retval true  Message received
 * @retval false No message received
 */
static bool fs_uart_rx(fs_uart_rx_msg_t* const msg)
{
    CRIT_ASSERT(NULL != msg);
    CRIT_ASSERT(NULL != fs_rxq);

    bool ret = false;

    if ((NULL != msg) &&
        (NULL != fs_rxq) &&
        (osOK == osMessageQueueGet(fs_rxq, msg, 0, 0)))
    {
        ret = true;
    }

    return ret;
}


/**
 * @brief Flush RX queue
 */
static void fs_uart_rx_flush(void)
{
    CRIT_ASSERT(NULL != fs_rxq);

    if (NULL != fs_rxq)
    {
        (void)osMessageQueueReset(fs_rxq);
    }
}


/**
 * @brief Init communication peripherals
 *
 * @retval true  Operation succeeded
 * @retval false Operation failed
 */
static bool fs_uart_init(void)
{
    RCC_PeriphCLKInitTypeDef periph_clk = { 0 };

    periph_clk.PeriphClockSelection      = CUBEOBC_UART_RCC_PERIPHCLK;
    periph_clk.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;

    if ((HAL_OK != HAL_RCCEx_PeriphCLKConfig(&periph_clk)) ||
        (HAL_OK != HAL_UART_Init(&fs_huart)))
    {
        return false;
    }

    cubeobc_dma_rx_clk_enable();

    if (HAL_OK != HAL_DMA_Init(&fs_hdma_uart_rx))
    {
        return false;
    }

    __HAL_LINKDMA(&fs_huart, hdmarx, fs_hdma_uart_rx);

    if ((HAL_OK != HAL_UART_RegisterCallback(&fs_huart, HAL_UART_ERROR_CB_ID, fs_uart_err_callback)) ||
        (HAL_OK != HAL_UART_RegisterRxEventCallback(&fs_huart, fs_uart_rx_event_callback)) ||
        (HAL_OK != HAL_UART_AbortReceive(&fs_huart)) ||
        (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&fs_huart, (uint8_t*)fs_rx_msg.data, sizeof(fs_rx_msg.data))))
    {
        return false;
    }

    __HAL_DMA_DISABLE_IT(&fs_hdma_uart_rx, DMA_IT_HT);

    HAL_NVIC_SetPriority(CUBEOBC_DMA_RX_IRQN, CUBEOBC_IRQ_PRIO, 0);
    HAL_NVIC_EnableIRQ(CUBEOBC_DMA_RX_IRQN);

    HAL_NVIC_SetPriority(CUBEOBC_UART_IRQN, CUBEOBC_IRQ_PRIO, 0);
    HAL_NVIC_EnableIRQ(CUBEOBC_UART_IRQN);

    return true;
}


/**
 * @brief DeInit communication peripherals
 *
 * @retval true  Operation succeeded
 * @retval false Operation failed
 */
static bool fs_uart_deinit(void)
{
    bool ret = false;

    HAL_NVIC_DisableIRQ(CUBEOBC_DMA_RX_IRQN);
    HAL_NVIC_DisableIRQ(CUBEOBC_UART_IRQN);

    if ((HAL_OK == HAL_UART_DeInit(&fs_huart)) &&
        (HAL_OK == HAL_DMA_DeInit(&fs_hdma_uart_rx)))
    {
        ret = true;
    }

    return ret;

}


/**
 * @brief Initializes the UART MSP
 *
 * @param[in] huart UART handle
 */
static void fs_uart_msp_init_callback(UART_HandleTypeDef* huart)
{
    if (CUBEOBC_UART_INSTANCE == huart->Instance)
    {
        cubeobc_uart_clk_enable(true);
        cubeobc_uart_rx_clk_enable();
        cubeobc_uart_tx_clk_enable();

        GPIO_InitTypeDef gpio = { 0 };

        gpio.Pin       = CUBEOBC_UART_RX_PIN;
        gpio.Mode      = GPIO_MODE_AF_PP;
        gpio.Pull      = GPIO_NOPULL;
        gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio.Alternate = CUBEOBC_UART_PIN_ALTERNATE;

        HAL_GPIO_Init(CUBEOBC_UART_RX_PORT, &gpio);

        gpio.Pin       = CUBEOBC_UART_TX_PIN;
        gpio.Mode      = GPIO_MODE_AF_PP;
        gpio.Pull      = GPIO_NOPULL;
        gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio.Alternate = CUBEOBC_UART_PIN_ALTERNATE;

        HAL_GPIO_Init(CUBEOBC_UART_TX_PORT, &gpio);

#ifdef CUBEOBC_UART_HAS_RS485_CHIP
        cubeobc_uart_rs485_chip_init();
#endif
    }
}


/**
 * @brief DeInitializes the UART MSP
 *
 * @param[in] huart UART handle
 */
static void fs_uart_msp_deinit_callback(UART_HandleTypeDef* huart)
{
    if (CUBEOBC_UART_INSTANCE == huart->Instance)
    {
        cubeobc_uart_clk_enable(false);
        HAL_GPIO_DeInit(CUBEOBC_UART_RX_PORT, CUBEOBC_UART_RX_PIN);
        HAL_GPIO_DeInit(CUBEOBC_UART_TX_PORT, CUBEOBC_UART_TX_PIN);
    }
}


/**
 * @brief UART error callback.
 *
 * @param[in] huart UART handle.
 */
static void fs_uart_err_callback(UART_HandleTypeDef* huart)
{
    if (CUBEOBC_UART_INSTANCE == huart->Instance)
    {
        // signal the thread to re-initialize the whole communication
        fs_uart_req_t req = FS_UART_REQ_REINIT;

        (void)osMessageQueuePut(fs_iniq, (const void*)&req, 0, 0);
    }
}


/**
 * @brief Reception event callback
 *
 * @param[in] huart UART handle
 * @param[in] size  Number of data available in application reception buffer
 */
static void fs_uart_rx_event_callback(UART_HandleTypeDef* huart, uint16_t size)
{
    if (CUBEOBC_UART_INSTANCE == huart->Instance)
    {
        CRIT_ASSERT(NULL != fs_rxq);

        // try to add the message to the RX queue

        fs_rx_msg.size = size;

        if ((NULL == fs_rxq) || (osOK != osMessageQueuePut(fs_rxq, (const void*)&fs_rx_msg, 0, 0)))
        {
            // no logging from isr
        }

        // re-enable RX interrupt
        if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&fs_huart, (uint8_t*)fs_rx_msg.data, sizeof(fs_rx_msg.data)))
        {
            fs_uart_err_callback(&fs_huart);
        }

        // disable the half transfer interrupt because we are not interested in it
        __HAL_DMA_DISABLE_IT(&fs_hdma_uart_rx, DMA_IT_HT);
    }
}


/**
 * @brief This thread handles all init/deinit/reinit requests
 */
static void fs_uart_thread(void* args)
{
    (void)args;

    uint8_t msg_prio;
    fs_uart_req_t action;
    bool init_done = false;
    bool failed = true;

    TaskMonitor_TaskInitialized(TASK_MONITOR_CUBEADCS_GEN2_COMM);
    task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_GEN2_COMM, TASK_MON_POLICY_MONITOR);

    while (1)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_CUBEADCS_GEN2_COMM);

        if ((osOK == osMessageQueueGet(fs_iniq, &action, &msg_prio, 1000)) &&
            (osOK == osMutexAcquire(fs_lock, osWaitForever)))
        {
            if (0 != (FS_UART_REQ_DEINIT & action))
            {
                if (false == fs_uart_deinit())
                {
                    failed = true;
                    ES_TRACE_ERROR("deinit fail");
                }
                else
                {
                    failed = false;
                    init_done = false;
                }
            }

            // consecutive init not allowed
            if ((0 != (FS_UART_REQ_INIT & action)) && (false == init_done))
            {
                init_done = fs_uart_init();

                if (false == init_done)
                {
                    failed = true;
                    ES_TRACE_ERROR("init fail");
                }
                else
                {
                    failed = false;
                }
            }

            (void)osMutexRelease(fs_lock);
        }

        // TX might get blocked if no delay is added here.
        // Also, since when cube adcs is powered off there is
        // a LOT of error interrupts in DMA dew to floating RX/TX line levels, 
        // other tasks might be blocked from execution.
        osDelay(100);

        // deinit or init failed... wait and try again
        if (true == failed)
        {
            osDelay(1000);

            action = FS_UART_REQ_REINIT;

            (void)osMessageQueuePut(fs_iniq, (const void*)&action, 0, 0);
        }

        vApplicationLowStackCheck(TASK_MONITOR_CUBEADCS_GEN2_COMM);
    }
}


/**
 * @brief Defines the RX state machine parameters used
 *        with CubeAdcsGen2 callback methods
 */
typedef struct
{
    fs_uart_rx_msg_t msg; /**< for RX message storage */
    uint32_t offset;      /**< current read offset    */
    bool read_done;       /**< indicator for read operation */
} fs_rx_state_t;


/** @brief RX state for use with CubeAdcsGen2 callback methods */
static fs_rx_state_t fs_rx_state =
{
    .read_done = false,
    .offset    = 0,
    .msg.size  = 0
};


/**
 * @brief This method replaces a WEAK callback from the CubeAdcsGen2 library. 
 *        On flush request we reset the whole state machine 
 *        and the low level UART driver RX queue
 */
void cubeObc_uartIfc_rxFlush(void)
{
    fs_rx_state.read_done = false;
    fs_rx_state.offset    = 0;
    fs_rx_state.msg.size  = 0;
    fs_uart_rx_flush();
}


/**
 * @brief This method replaces a WEAK callback from the CubeAdcsGen2 library. 
 *        It is responsible for retrieving data from the low level UART driver.
 * 
 * @note  Since the library request the data byte by byte we need a state machine.
 *        It also works with request > than 1 byte.
 * 
 * @param[in]  data     Pointer to a buffer where we need to pass requested data
 * @param[in]  size     Size of the requested data
 * @param[out] sizeRead The actual read size
 *
 * @return @ref ErrorCode
 */
ErrorCode cubeObc_uartIfc_rx(U8* data, U32 size, U32* size_read)
{
    ErrorCode err = CUBEOBC_ERROR_READ;

    if ((false == fs_rx_state.read_done) &&
        (true == fs_uart_rx(&fs_rx_state.msg)) &&
        (0 != fs_rx_state.msg.size) &&
        (sizeof(fs_rx_state.msg.data) >= fs_rx_state.msg.size))
    {
        fs_rx_state.read_done = true;
        fs_rx_state.offset    = fs_rx_state.msg.size;
    }

    if ((true == fs_rx_state.read_done) &&
        (size <= fs_rx_state.offset) &&
        (0 != fs_rx_state.offset))
    {
        memcpy(data, &fs_rx_state.msg.data[fs_rx_state.msg.size - fs_rx_state.offset], size);
        fs_rx_state.offset -= size;
        *size_read = size;

        err = CUBEOBC_ERROR_OK;
    }

    return err;
}


/**
 * @brief This method replaces a WEAK callback from the CubeAdcsGen2 library. 
 *        Sends data to the low level UART driver for transmission
 * 
 * @param[in] data Pointer to the data to be transmitted
 * @param[in] size Size of the data to be transmitted
 *
 * @return @ref ErrorCode
 */
ErrorCode cubeObc_uartIfc_tx(CONST U8* data, U32 size)
{
    ErrorCode err = CUBEOBC_ERROR_WRITE;

    if (true == fs_uart_tx(data, size))
    {
        err = CUBEOBC_ERROR_OK;
    }

    return err;
}
