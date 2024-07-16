/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup can
 * @{
 *
 * @file can.c
 *
 * @brief CAN driver implementation
 *
 * @}
 */

#include <string.h>
#include "can.h"
#include "can_defs.h"
#include "can_pin_defs.h"
#include "can_internal_types.h"
#include "trace.h"
#include "timer.h"
#include "TaskMonitor.h"

typedef struct
{
    uint32_t rx_cnt;                /**< number of successfully received CAN frames */
    uint16_t rx_os_queue_err_cnt;   /**< number of failed OS queue attempts for Rx frames */
    uint32_t tx_cnt;                /**< number of successfully queued CAN frames (to TX FIFO) */
    uint16_t tx_fifo_full_cnt;      /**< number of times the CAN TX FIFO queue was full when trying to transmit */
    uint16_t rx_msg_lost_cnt;       /**< number of lost messages on reception (due to overrun) */
    uint16_t tx_fifo_lost_cnt;      /**< number of lost CAN TX FIFO frames */
    uint16_t err_passive_cnt;       /**< number of FDCAN_IT_ERROR_PASSIVE events on the bus */
    uint16_t err_warn_cnt;          /**< number of FDCAN_IT_ERROR_WARNING events on the bus */
    uint16_t err_bus_off_cnt;       /**< number of FDCAN_IT_BUS_OFF events on the bus */
} can_drv_stats_t;

/** @brief General CAN statistic counters */
static can_drv_stats_t can_drv_stats;

/** @brief CAN driver statistics periodic trace timer */
static timer_handle_t stats_timer;

/** @brief transmit message queue */
static osMessageQueueId_t fs_txq = NULL;

/** @brief Init/DeInit requests queue */
static osMessageQueueId_t fs_iniq = NULL;

/** @brief transmit lock guard */
static osMutexId_t fs_tx_lock = NULL;

/** @brief CAN Init/DeInit task handle */
static osThreadId_t fs_init_task_h  = NULL;

/** @brief CAN TX task handle */
static osThreadId_t fs_tx_task_h = NULL;

/** @brief CAN TX task attributes */
static const osThreadAttr_t fs_tx_task_attr =
{
    .attr_bits  = osThreadDetached,
    .name       = "can_tx",
    .priority   = osPriorityNormal,
    .cb_mem     = NULL,
    .cb_size    = 0U,
    .stack_mem  = NULL,
    .stack_size = 512,
    .tz_module  = 0U,
    .reserved   = 0U,
};

/** @brief CAN Init/DeInit task attributes */
static const osThreadAttr_t fs_init_task_attr =
{
    .attr_bits  = osThreadDetached,
    .name       = "can_init",
    .priority   = osPriorityNormal,
    .cb_mem     = NULL,
    .cb_size    = 0U,
    .stack_mem  = NULL,
    .stack_size = 1024,
    .tz_module  = 0U,
    .reserved   = 0U,
};


static void fs_msp_init_callback(FDCAN_HandleTypeDef* hfdcan);
static void fs_msp_deinit_callback(FDCAN_HandleTypeDef* hfdcan);
static bool fs_rx_default(const can_msg_t* const msg);
static void fs_tx_task(void* args);
static void fs_init_task(void* args);


static can_rx_ctx_t fs_rx_ctx[CAN_ID_COUNT] =
{
    [CAN_ID_STANDARD] =
    {
        .q                 = NULL,
        .user_callback_set = false,
        .user_callback     = fs_rx_default,
    },
    [CAN_ID_EXTENDED] =
    {
        .q                 = NULL,
        .user_callback_set = false,
        .user_callback     = fs_rx_default,
    },
};


/** @brief FDCAN handler */
static FDCAN_HandleTypeDef fs_fdcan =
{
    .Instance                    = FDCAN1,
    .ttcan                       = NULL,
    .Init.FrameFormat            = FDCAN_FRAME_CLASSIC,
    .Init.Mode                   = FDCAN_MODE_NORMAL,
    .Init.AutoRetransmission     = ENABLE,
    .Init.TransmitPause          = DISABLE,
    .Init.ProtocolException      = ENABLE,
    .Init.NominalPrescaler       = 15,
    .Init.NominalSyncJumpWidth   = 1,
    .Init.NominalTimeSeg1        = 2,
    .Init.NominalTimeSeg2        = 1,
    .Init.DataPrescaler          = 15,
    .Init.DataSyncJumpWidth      = 1,
    .Init.DataTimeSeg1           = 2,
    .Init.DataTimeSeg2           = 1,
    .Init.MessageRAMOffset       = 0,
    .Init.StdFiltersNbr          = 0,
    .Init.ExtFiltersNbr          = 0,
    .Init.RxFifo0ElmtsNbr        = 64,
    .Init.RxFifo0ElmtSize        = FDCAN_DATA_BYTES_8,
    .Init.RxFifo1ElmtsNbr        = 0,
    .Init.RxFifo1ElmtSize        = FDCAN_DATA_BYTES_8,
    .Init.RxBuffersNbr           = 0,
    .Init.RxBufferSize           = FDCAN_DATA_BYTES_8,
    .Init.TxEventsNbr            = 32,
    .Init.TxBuffersNbr           = 0,
    .Init.TxFifoQueueElmtsNbr    = 32,
    .Init.TxFifoQueueMode        = FDCAN_TX_FIFO_OPERATION,
    .Init.TxElmtSize             = FDCAN_DATA_BYTES_8,
    .msgRam.StandardFilterSA     = 0,
    .msgRam.ExtendedFilterSA     = 0,
    .msgRam.RxFIFO0SA            = 0,
    .msgRam.RxFIFO1SA            = 0,
    .msgRam.RxBufferSA           = 0,
    .msgRam.TxEventFIFOSA        = 0,
    .msgRam.TxBufferSA           = 0,
    .msgRam.TxFIFOQSA            = 0,
    .msgRam.TTMemorySA           = 0,
    .msgRam.EndAddress           = 0,
    .LatestTxFifoQRequest        = 0,
    .State                       = HAL_FDCAN_STATE_RESET,
    .Lock                        = HAL_UNLOCKED,
    .ErrorCode                   = HAL_FDCAN_ERROR_NONE,
    .ClockCalibrationCallback    = NULL,
    .TxEventFifoCallback         = NULL,
    .RxFifo0Callback             = NULL,
    .RxFifo1Callback             = NULL,
    .TxFifoEmptyCallback         = NULL,
    .TxBufferCompleteCallback    = NULL,
    .TxBufferAbortCallback       = NULL,
    .RxBufferNewMessageCallback  = NULL,
    .HighPriorityMessageCallback = NULL,
    .TimestampWraparoundCallback = NULL,
    .TimeoutOccurredCallback     = NULL,
    .ErrorCallback               = NULL,
    .ErrorStatusCallback         = NULL,
    .TT_ScheduleSyncCallback     = NULL,
    .TT_TimeMarkCallback         = NULL,
    .TT_StopWatchCallback        = NULL,
    .TT_GlobalTimeCallback       = NULL,
    .MspInitCallback             = fs_msp_init_callback,
    .MspDeInitCallback           = fs_msp_deinit_callback,
};


void can_reg_rx(const can_id_t type, can_rx_clbk_t callback)
{
    if ((NULL != callback) &&
        (CAN_ID_COUNT > type) &&
        (false == fs_rx_ctx[type].user_callback_set))
    {
        fs_rx_ctx[type].user_callback_set = true;
        fs_rx_ctx[type].user_callback     = callback;
    }
}


bool can_rxq_init(const can_id_t type, const uint32_t sz)
{
    bool ret = false;

    if ((0 < sz) &&
        (CAN_ID_COUNT > type) &&
        (NULL == fs_rx_ctx[type].q))
    {
        fs_rx_ctx[type].q = osMessageQueueNew(sz, sizeof(can_msg_t), NULL);

        if (NULL != fs_rx_ctx[type].q)
        {
            ret = true;
        }
    }

    return ret;
}


bool can_txq_init(const uint32_t sz)
{
    bool ret = false;
    uint32_t tx_sz;

    if (NULL == fs_txq)
    {
        tx_sz = (sz > 0) ? sz : CANDEF_DEFAULT_TX_Q_SIZE;

        fs_txq = osMessageQueueNew(tx_sz, sizeof(can_msg_t), NULL);

        if (NULL != fs_txq)
        {
            ret = true;
        }
    }

    return ret;
}


bool can_init(void)
{
    bool ret = false;

    (void) memset(&can_drv_stats, 0U, sizeof(can_drv_stats));

    timer_start(&stats_timer);

    if (NULL == fs_iniq)
    {
        fs_iniq = osMessageQueueNew(CANDEF_DEFAULT_INIT_Q_SIZE, sizeof(can_request_t), NULL);

        if (NULL == fs_iniq)
        {
            return ret;
        }
    }

    if (NULL == fs_tx_task_h)
    {
        fs_tx_task_h = osThreadNew(fs_tx_task, NULL, &fs_tx_task_attr);

        if (NULL == fs_tx_task_h)
        {
            return ret;
        }
    }

    if (NULL == fs_tx_lock)
    {
        fs_tx_lock = osMutexNew(NULL);

        if (NULL == fs_tx_lock)
        {
            return ret;
        }
    }

    if (NULL == fs_init_task_h)
    {
        fs_init_task_h = osThreadNew(fs_init_task, NULL, &fs_init_task_attr);

        if (NULL == fs_init_task_h)
        {
            return ret;
        }
    }

    can_request_t req = CAN_REQUEST_INIT;

    if (osOK == osMessageQueuePut(fs_iniq, &req, 0, 0))
    {
        ret = true;
    }
    else
    {
        ES_TRACE_ERROR("init q");
    }

    return ret;
}


bool can_deinit(void)
{
    bool ret = false;
    can_request_t req = CAN_REQUEST_DEINIT;

    if (osOK == osMessageQueuePut(fs_iniq, &req, 0, 0))
    {
        ret = true;
    }
    else
    {
        ES_TRACE_ERROR("init q");
    }

    return ret;
}


bool can_reinit(void)
{
    bool ret = false;
    can_request_t req = CAN_REQUEST_REINIT;

    if (osOK == osMessageQueuePut(fs_iniq, &req, 0, 0))
    {
        ret = true;
    }
    else
    {
        ES_TRACE_ERROR("init q");
    }

    return ret;
}


bool can_rxq_reset(const can_id_t type)
{
    bool ret = false;

    if ((CAN_ID_COUNT > type) &&
        (NULL != fs_rx_ctx[type].q) &&
        (osOK == osMessageQueueReset(fs_rx_ctx[type].q)))
    {
        ret = true;
    }

    return ret;
}


bool can_txq_reset(void)
{
    bool ret = false;

    if ((NULL != fs_txq) &&
        (osOK == osMessageQueueReset(fs_txq)))
    {
        ret = true;
    }

    return ret;
}


bool can_tx(const can_msg_t* const msg)
{
    bool ret = false;

    if ((NULL != msg) &&
        (NULL != fs_txq) &&
        (CAN_MSG_DATA_SZ >= msg->data_sz) &&
        (CAN_ID_COUNT > msg->id_type))
    {
        if (osOK == osMessageQueuePut(fs_txq, msg, 0, 0))
        {
            ret = true;
        }
        else
        {
            ES_TRACE_ERROR("tx q");
        }
    }

    return ret;
}


bool can_rx(can_msg_t* const msg, const can_id_t type)
{
    bool ret = false;
    uint8_t msg_prio;

    if ((NULL != msg) &&
        (CAN_ID_COUNT > type) &&
        (NULL != fs_rx_ctx[type].q) &&
        (osOK == osMessageQueueGet(fs_rx_ctx[type].q, msg, &msg_prio, 0)))
    {
        ret = true;
    }

    return ret;
}


void can_irq_it0_handler(void)
{
    HAL_FDCAN_IRQHandler(&fs_fdcan);
}


/**
 * @brief Tx Event callback.
 *
 * @param hfdcan            pointer to an FDCAN_HandleTypeDef structure that contains
 *                          the configuration information for the specified FDCAN.
 *
 * @param tx_event_fifo_its indicates which Tx Event FIFO interrupts are signaled.
 *                          This parameter can be any combination of @arg FDCAN_Tx_Event_Fifo_Interrupts.
 */
static void fs_tx_event_fifo_callback(FDCAN_HandleTypeDef* hfdcan, uint32_t tx_event_fifo_its)
{
    FDCAN_TxEventFifoTypeDef event = { 0 };

    if ((NULL != hfdcan) &&
        (NULL != hfdcan->Instance) &&
        (fs_fdcan.Instance == hfdcan->Instance))
    {
        (void)HAL_FDCAN_GetTxEvent(&fs_fdcan, &event);

        if (0 != (FDCAN_IT_TX_EVT_FIFO_ELT_LOST & tx_event_fifo_its))
        {
            can_drv_stats.tx_fifo_lost_cnt++;
        }

        if (0 != (FDCAN_IT_TX_EVT_FIFO_FULL & tx_event_fifo_its))
        {
            can_drv_stats.tx_fifo_full_cnt++;
        }
    }
}


/**
 * @brief Error status callback.
 *
 * @param hfdcan           pointer to an FDCAN_HandleTypeDef structure that contains
 *                         the configuration information for the specified FDCAN.
 *
 * @param error_status_its indicates which Error Status interrupts are signaled.
 *                         This parameter can be any combination of @arg FDCAN_Error_Status_Interrupts.
 */
static void fs_error_status_callback(FDCAN_HandleTypeDef* hfdcan, uint32_t error_status_its)
{
    if ((NULL != hfdcan) &&
        (NULL != hfdcan->Instance) &&
        (fs_fdcan.Instance == hfdcan->Instance))
    {
        if (0 != (FDCAN_IT_ERROR_PASSIVE & error_status_its))
        {
            can_drv_stats.err_passive_cnt++;
        }

        if (0 != (FDCAN_IT_ERROR_WARNING & error_status_its))
        {
            can_drv_stats.err_warn_cnt++;
        }

        if (0 != (FDCAN_IT_BUS_OFF & error_status_its))
        {
            (void)can_reinit();

            can_drv_stats.err_bus_off_cnt++;
        }
    }
}


/**
 * @brief  Error callback.
 *
 * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
 *                the configuration information for the specified FDCAN.
 */
static void fs_error_callback(FDCAN_HandleTypeDef* hfdcan)
{
    if ((NULL != hfdcan) &&
        (NULL != hfdcan->Instance) &&
        (fs_fdcan.Instance == hfdcan->Instance))
    {
        (void)can_reinit();
    }
}


/**
 * @brief Initializes the FDCAN MSP.
 *
 * @param hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
 *               the configuration information for the specified FDCAN.
 */
static void fs_msp_init_callback(FDCAN_HandleTypeDef* hfdcan)
{
    if ((NULL != hfdcan) &&
        (NULL != hfdcan->Instance) &&
        (fs_fdcan.Instance == hfdcan->Instance))
    {
        GPIO_InitTypeDef gpio_init_struct = { 0 };

        __HAL_RCC_FDCAN_CLK_ENABLE();

        CANDEF_TX_PORT_CLK_EN();
        CANDEF_RX_PORT_CLK_EN();

        gpio_init_struct.Pin       = CANDEF_TX_PIN;
        gpio_init_struct.Mode      = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull      = GPIO_NOPULL;
        gpio_init_struct.Speed     = GPIO_SPEED_FREQ_LOW;
        gpio_init_struct.Alternate = GPIO_AF9_FDCAN1;
        HAL_GPIO_Init(CANDEF_TX_PORT, &gpio_init_struct);

        gpio_init_struct.Pin       = CANDEF_RX_PIN;
        gpio_init_struct.Mode      = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull      = GPIO_NOPULL;
        gpio_init_struct.Speed     = GPIO_SPEED_FREQ_LOW;
        gpio_init_struct.Alternate = GPIO_AF9_FDCAN1;
        HAL_GPIO_Init(CANDEF_RX_PORT, &gpio_init_struct);
    }
}


/**
 * @brief DeInitializes the FDCAN MSP.
 *
 * @param hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
 *               the configuration information for the specified FDCAN.
 */
static void fs_msp_deinit_callback(FDCAN_HandleTypeDef* hfdcan)
{
    if ((NULL != hfdcan) &&
        (NULL != hfdcan->Instance) &&
        (fs_fdcan.Instance == hfdcan->Instance))
    {
        HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);

        HAL_GPIO_DeInit(CANDEF_TX_PORT, CANDEF_TX_PIN);
        HAL_GPIO_DeInit(CANDEF_RX_PORT, CANDEF_RX_PIN);
    }
}


/**
 * @brief Enable/Disable external CAN PHY
 *
 * @param enable If true - enabled.
 */
static void fs_enable(bool enable)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    CANDEF_EN_PORT_CLK_EN();

    if (enable)
    {
        HAL_GPIO_WritePin(CANDEF_EN_PORT, CANDEF_EN_PIN, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(CANDEF_EN_PORT, CANDEF_EN_PIN, GPIO_PIN_SET);
    }

    gpio_init_struct.Pin   = CANDEF_EN_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(CANDEF_EN_PORT, &gpio_init_struct);
}


/**
 * @brief Converts FDCAN data size to normal data size
 *
 * @return normal data size
 */
static inline uint8_t fs_fdcan_sz_to_data_sz(const uint32_t sz)
{
    return (uint8_t)(sz >> 16);
}


/**
 * @brief Converts normal data size to FDCAN data size
 *
 * @return FDCAN data size
 */
static inline uint32_t fs_data_sz_to_fdcan_sz(const uint32_t sz)
{
    return (sz << 16);
}


/**
 * @brief Rx FIFO 0 callback.
 *
 * @param hfdcan       pointer to an FDCAN_HandleTypeDef structure that contains
 *                     the configuration information for the specified FDCAN.
 *
 * @param rx_fifo0_its indicates which Rx FIFO 0 interrupts are signaled.
 *                     This parameter can be any combination of @arg FDCAN_Rx_Fifo0_Interrupts.
 */
static void fs_rxfifo0_callback(FDCAN_HandleTypeDef* hfdcan, uint32_t rx_fifo0_its)
{
    FDCAN_RxHeaderTypeDef hdr;
    HAL_StatusTypeDef fdcan_status = HAL_ERROR;
    can_msg_t msg;

    if ((NULL != hfdcan) &&
        (NULL != hfdcan->Instance) &&
        (fs_fdcan.Instance == hfdcan->Instance) &&
        (0 != (FDCAN_IT_RX_FIFO0_NEW_MESSAGE & rx_fifo0_its)))
    {
        uint8_t rx_q_msg_cnt = HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO0);

        // read all queued frames until HW RX FIFO is empty or error occurs
        while (rx_q_msg_cnt > 0)
        {
            fdcan_status = HAL_FDCAN_GetRxMessage(&fs_fdcan, FDCAN_RX_FIFO0, &hdr, msg.data);

            if ((HAL_OK == fdcan_status) &&
                (IS_FDCAN_DLC(hdr.DataLength)))
            {
                msg.id_type = (hdr.IdType == FDCAN_EXTENDED_ID) ? CAN_ID_EXTENDED : CAN_ID_STANDARD;
                msg.id      = hdr.Identifier;
                msg.data_sz = fs_fdcan_sz_to_data_sz(hdr.DataLength);

                bool msg_processed = false;

                if (true == fs_rx_ctx[msg.id_type].user_callback_set)
                {
                    msg_processed = fs_rx_ctx[msg.id_type].user_callback(&msg);
                }

                if ((false == msg_processed) &&
                    (NULL != fs_rx_ctx[msg.id_type].q))
                {
                    osStatus_t msg_queue_status = osMessageQueuePut(fs_rx_ctx[msg.id_type].q, &msg, 0, 0);

                    can_drv_stats.rx_cnt++;

                    if (osOK != msg_queue_status)
                    {
                        can_drv_stats.rx_os_queue_err_cnt++;
                    }
                }
            }

            rx_q_msg_cnt--;
        }
    }

    if (0 != (FDCAN_IT_RX_FIFO0_MESSAGE_LOST & rx_fifo0_its))
    {
        can_drv_stats.rx_msg_lost_cnt++;
    }
}


/**
 * @brief Peripheral init
 *
 * @retval true  success
 * @retval false error
 */
static bool fs_init(void)
{
    bool ret = false;

    if ((HAL_OK == HAL_FDCAN_Init(&fs_fdcan)) &&
        (HAL_OK == HAL_FDCAN_RegisterCallback(&fs_fdcan, HAL_FDCAN_ERROR_CALLBACK_CB_ID, fs_error_callback)) &&
        (HAL_OK == HAL_FDCAN_RegisterErrorStatusCallback(&fs_fdcan, fs_error_status_callback)) &&
        (HAL_OK == HAL_FDCAN_RegisterRxFifo0Callback(&fs_fdcan, fs_rxfifo0_callback)) &&
        (HAL_OK == HAL_FDCAN_RegisterTxEventFifoCallback(&fs_fdcan, fs_tx_event_fifo_callback)) &&
        (HAL_OK == HAL_FDCAN_ConfigInterruptLines(&fs_fdcan, CANDEF_IT_GROUP, FDCAN_INTERRUPT_LINE0)) &&
        (HAL_OK == HAL_FDCAN_ActivateNotification(&fs_fdcan, CANDEF_IT_GROUP, 0)) &&
        (HAL_OK == HAL_FDCAN_Start(&fs_fdcan)))
    {
        HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, CANDEF_IRQ_PRIO, 0);
        HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);

        fs_enable(true);

        ret = true;
    }

    return ret;
}


/**
 * @brief Peripheral DeInit
 *
 * @retval true  success
 * @retval false error
 */
static bool fs_deinit(void)
{
    bool ret = true;

    fs_enable(false);

    if (HAL_OK != HAL_FDCAN_DeInit(&fs_fdcan))
    {
        ret = false;
    }

    return ret;
}


/**
 * @brief Default RX handler
 */
static bool fs_rx_default(const can_msg_t* const msg)
{
    (void)msg;

    return true;
}


/**
 * @brief Blocking wait for reset from Task Monitor
 */
static void fs_block_wait_reset(void)
{
    osDelay(osWaitForever);
}


/**
 * @brief Task for handling Init/DeInit requests
 */
static void fs_init_task(void* args)
{
    (void)args;

    uint8_t msg_prio;
    can_request_t action;
    bool init_done = false;

    TaskMonitor_TaskInitialized(TASK_CAN_INIT);
    task_mon_set_task_policy(TASK_CAN_INIT, TASK_MON_POLICY_MONITOR);

    while (1)
    {
        TaskMonitor_IamAlive(TASK_CAN_INIT);

        if ((osOK == osMessageQueueGet(fs_iniq, &action, &msg_prio, CANDEF_TIMEOUT)) &&
            (osOK == osMutexAcquire(fs_tx_lock, osWaitForever)))
        {
            if (0 != (CAN_REQUEST_DEINIT & action))
            {
                if (false == fs_deinit())
                {
                    // we shouldn't be here
                    // log error and blocking wait for system reset

                    ES_TRACE_ERROR("deinit fail");

                    fs_block_wait_reset();
                }
                else
                {
                    init_done = false;
                }
            }

            // consecutive init not allowed
            if ((0 != (CAN_REQUEST_INIT & action)) && (false == init_done))
            {
                init_done = fs_init();

                if (false == init_done)
                {
                    // we shouldn't be here
                    // log error and blocking wait for system reset

                    ES_TRACE_ERROR("init fail");

                    fs_block_wait_reset();
                }
            }

            (void)osMutexRelease(fs_tx_lock);
        }

        // periodic trace of the CAN driver statistics
        if (true == timer_is_elapsed(&stats_timer, CANDEF_STATS_TRACE_PERIOD_MS))
        {
            ES_TRACE_DEBUG("CAN => [%ld|%ld|%d|%d|%d|%d|%d|%d|%d]",
                           can_drv_stats.rx_cnt,
                           can_drv_stats.tx_cnt,
                           can_drv_stats.rx_os_queue_err_cnt,
                           can_drv_stats.rx_msg_lost_cnt,
                           can_drv_stats.tx_fifo_full_cnt,
                           can_drv_stats.tx_fifo_lost_cnt,
                           can_drv_stats.err_passive_cnt,
                           can_drv_stats.err_warn_cnt,
                           can_drv_stats.err_bus_off_cnt);

            timer_start(&stats_timer);
        }

        vApplicationLowStackCheck(TASK_CAN_INIT);
    }
}


/**
 * @brief Task for handling transmit requests
 */
static void fs_tx_task(void* args)
{
    (void)args;

    can_msg_t msg;
    uint8_t msg_prio;
    FDCAN_TxHeaderTypeDef hdr;
    uint8_t free_lvl_fail_count = 0;

    TaskMonitor_TaskInitialized(TASK_CAN_TX);
    task_mon_set_task_policy(TASK_CAN_TX, TASK_MON_POLICY_MONITOR);

    while (1)
    {
        TaskMonitor_IamAlive(TASK_CAN_TX);

        if (osOK == osMessageQueueGet(fs_txq, &msg, &msg_prio, CANDEF_TIMEOUT))
        {
            uint32_t retry = 0;
            HAL_StatusTypeDef res = HAL_BUSY;

            do
            {
                if (osOK == osMutexAcquire(fs_tx_lock, osWaitForever))
                {
                    hdr.Identifier          = msg.id;
                    hdr.IdType              = (msg.id_type == CAN_ID_EXTENDED) ? FDCAN_EXTENDED_ID : FDCAN_STANDARD_ID;
                    hdr.TxFrameType         = FDCAN_DATA_FRAME;
                    hdr.DataLength          = fs_data_sz_to_fdcan_sz(msg.data_sz);
                    hdr.ErrorStateIndicator = FDCAN_ESI_ACTIVE; // TODO use transition counter?
                    hdr.BitRateSwitch       = FDCAN_BRS_OFF;
                    hdr.FDFormat            = FDCAN_CLASSIC_CAN;
                    hdr.TxEventFifoControl  = FDCAN_STORE_TX_EVENTS;
                    hdr.MessageMarker       = 0; // TODO use it?

                    if (0 < HAL_FDCAN_GetTxFifoFreeLevel(&fs_fdcan))
                    {
                        res = HAL_FDCAN_AddMessageToTxFifoQ(&fs_fdcan, &hdr, msg.data);
                    }

                    (void)osMutexRelease(fs_tx_lock);

                    if (HAL_OK == res)
                    {
                        free_lvl_fail_count = 0;
                        can_drv_stats.tx_cnt++;

                        break;
                    }
                    else if ((HAL_ERROR == res) || (CANDEF_FREE_LVL_MAX_COUNT < free_lvl_fail_count))
                    {
                        free_lvl_fail_count = 0;

                        (void)can_reinit();

                        break;
                    }
                    else
                    {
                        free_lvl_fail_count++;
                    }
                }

                osDelay(CANDEF_TX_RETRY_PERIOD_MS);

                retry++;
            } while (CANDEF_TX_RETRY_MAX > retry);

            if (CANDEF_TX_RETRY_MAX <= retry)
            {
                ES_TRACE_ERROR("tx fail");
            }
        }

        vApplicationLowStackCheck(TASK_CAN_TX);
    }
}
