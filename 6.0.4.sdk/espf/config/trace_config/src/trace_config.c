/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libtrace
 * @{
 *
 * @file trace_config.c
 * @brief `trace` configuration implementation
 *
 * @}
 */
#include "trace_config.h"
#include "trace.h"
#include "trace_defs.h"
#include "SdMngr.h"
#include "if_sys_conf.h"
#include "es_cdef.h"
#include "cmsis_os2.h"
#include "stm32h7xx_hal.h"


/** @brief Period of the OS threads that service the trace channel buffers */
#define FS_TRACE_SERVE_MS        (25)

/** Maximum size in bytes of the buffer for a single channel of trace data */
#define FS_CHAN_BUF_SZ           (1024)

/** Maximum size in bytes of the channel data that is read on a single execution of a servicing thread */
#define FS_WORK_BUF_SZ           (FS_CHAN_BUF_SZ / 2)

/** Name pattern for the rolling file used by the file trace channel */
#define FS_ROLLING_FILE_NAME     "trace_log.d__"

/** Maximum size of one instance of the rolling file */
#define FS_ROLLING_FILE_SIZE     (10485760) // 10MB

/** Maximum number of rolling file instances */
#define FS_ROLLING_FILE_CNT      (10)

/** Index in the rolling file name pattern of the marker of active/inactive file */
#define FS_ROLLING_FILE_MARK_POS (11)

/** Index in the rolling file name pattern of the file instance index */
#define FS_ROLLING_FILE_IDX_POS  (12)

/** Marker in the rolling file name for the currently active file */
#define FS_ROLLING_FILE_ACTIVE   'o'

/** Marker in the rolling file name for currently inactive files */
#define FS_ROLLING_FILE_INACTIVE 'x'

typedef enum
{
    FS_CHANNEL_UART = 0, /**< Trace output to UART */
    FS_CHANNEL_FILE,     /**< Trace output to a file on the SD card */
#if defined(STM32_SWV_SUPPORT) && defined(DEBUG_ENABLED)
    FS_CHANNEL_SWV,      /**< Trace output to SWV */
#endif
    FS_CHANNEL_COUNT     /**< Number of trace output channels */
} fs_channel_t;


static void fs_thread_uart(void* args);
static void fs_thread_file(void* args);
static uint32_t fs_channel_data_send_to_uart(const uint8_t* data, const uint32_t data_sz);
static uint32_t fs_channel_data_send_to_file(const uint8_t* data, const uint32_t data_sz);
static void trace_uart_init(void);
#if defined(STM32_SWV_SUPPORT) && defined(DEBUG_ENABLED)
static void fs_thread_swv(void* args);
static uint32_t fs_channel_data_send_to_swv(const uint8_t* data, const uint32_t data_sz);
#endif


static osThreadId_t fs_thread_handle[FS_CHANNEL_COUNT];
static osThreadAttr_t fs_thread_attr[FS_CHANNEL_COUNT];
static const uint16_t fs_thread_stack_sz[FS_CHANNEL_COUNT] =
{
    [FS_CHANNEL_UART] = 512,
    [FS_CHANNEL_FILE] = 2048,
#if defined(STM32_SWV_SUPPORT) && defined(DEBUG_ENABLED)
    [FS_CHANNEL_SWV]  = 512
#endif
};

static uint8_t fs_channel_buf[FS_CHANNEL_COUNT][FS_CHAN_BUF_SZ];
static uint8_t fs_work_buf[FS_CHANNEL_COUNT][FS_WORK_BUF_SZ];

static osThreadFunc_t fs_thread_routine[FS_CHANNEL_COUNT] =
{
    [FS_CHANNEL_UART] = fs_thread_uart,
    [FS_CHANNEL_FILE] = fs_thread_file,
#if defined(STM32_SWV_SUPPORT) && defined(DEBUG_ENABLED)
    [FS_CHANNEL_SWV]  = fs_thread_swv
#endif
};

static trace_channel_t fs_channel_list[FS_CHANNEL_COUNT] =
{
    [FS_CHANNEL_UART] =
    {
        .name      = "uart",
        .active    = true, // Not supposed to be modified at run-time, unless in error conditions
        .encoded   = true,
        .lock      = NULL,
        .data_send = fs_channel_data_send_to_uart,
        .cbuf      = {.head = 0, .tail = 0, .buf = NULL, .buf_sz = 0, .space = 0 },
        .buf       = fs_channel_buf[FS_CHANNEL_UART],
        .buf_sz    = sizeof(fs_channel_buf[FS_CHANNEL_UART]),
        .levels    = (uint8_t)(TRACE_LVL_ENABLE(TRACE_LVL_INFO)  |
                               TRACE_LVL_ENABLE(TRACE_LVL_WARN)  |
                               TRACE_LVL_ENABLE(TRACE_LVL_ERROR) |
                               TRACE_LVL_ENABLE(TRACE_LVL_FATAL) |
                               TRACE_LVL_ENABLE(TRACE_LVL_DEBUG))
    },
    [FS_CHANNEL_FILE] =
    {
        .name      = FS_ROLLING_FILE_NAME,
        .active    = true, // Disabled until trace usage of SD card is analyzed
        .encoded   = true,
        .lock      = NULL,
        .data_send = fs_channel_data_send_to_file,
        .cbuf      = {.head = 0, .tail = 0, .buf = NULL, .buf_sz = 0, .space = 0 },
        .buf       = fs_channel_buf[FS_CHANNEL_FILE],
        .buf_sz    = sizeof(fs_channel_buf[FS_CHANNEL_FILE]),
        .levels    = (uint8_t)(TRACE_LVL_ENABLE(TRACE_LVL_ERROR) |
                               TRACE_LVL_ENABLE(TRACE_LVL_WARN)  |
                               TRACE_LVL_ENABLE(TRACE_LVL_FATAL))
    },
#if defined(STM32_SWV_SUPPORT) && defined(DEBUG_ENABLED)
    [FS_CHANNEL_SWV] =
    {
        .name      = "swv",
        .active    = true,
        .encoded   = false,
        .lock      = NULL,
        .data_send = fs_channel_data_send_to_swv,
        .cbuf      = {.head = 0, .tail = 0, .buf = NULL, .buf_sz = 0, .space = 0 },
        .buf       = fs_channel_buf[FS_CHANNEL_SWV],
        .buf_sz    = sizeof(fs_channel_buf[FS_CHANNEL_SWV]),
        .levels    = (uint8_t)(TRACE_LVL_ENABLE(TRACE_LVL_INFO)  |
                               TRACE_LVL_ENABLE(TRACE_LVL_WARN)  |
                               TRACE_LVL_ENABLE(TRACE_LVL_ERROR) |
                               TRACE_LVL_ENABLE(TRACE_LVL_FATAL) |
                               TRACE_LVL_ENABLE(TRACE_LVL_DEBUG))
    },
#endif
};

static UART_HandleTypeDef fs_huart;

static const sSdMngr_rlf_cfg_t fs_rolling_file_cfg =
{
    .u32MaxSizeInBytes = FS_ROLLING_FILE_SIZE,
    .acNamePattern     = FS_ROLLING_FILE_NAME,
    .u8MarkerPos       = FS_ROLLING_FILE_MARK_POS,
    .u8IndexPos        = FS_ROLLING_FILE_IDX_POS,
    .u8FilesCount      = FS_ROLLING_FILE_CNT,
    .cActiveMarker     = FS_ROLLING_FILE_ACTIVE,
    .cInactiveMarker   = FS_ROLLING_FILE_INACTIVE
};

static sSdMngr_rlf_ctx_t fs_rolling_file =
{
    .acFileName    = "",
    .psCfg         = &fs_rolling_file_cfg,
    .u8CurrentIdx  = 0,
    .bIsFileOpened = false
};

void trace_config_init(trace_channel_t** const chan_list, uint32_t* const chan_list_sz)
{
    trace_assert(NULL != chan_list);
    trace_assert(NULL != chan_list_sz);

    trace_uart_init();

    for (uint32_t i = 0; i < CDEF_ELEMENT_COUNT(fs_channel_list); i++)
    {
        if (false != fs_channel_list[i].active) // Inactive channels shouldn't occupy OS resources
        {
            fs_thread_attr[i].attr_bits  = osThreadDetached;
            fs_thread_attr[i].name       = fs_channel_list[i].name;
            fs_thread_attr[i].priority   = osPriorityNormal;
            fs_thread_attr[i].cb_mem     = NULL;
            fs_thread_attr[i].cb_size    = 0U;
            fs_thread_attr[i].stack_mem  = NULL;
            fs_thread_attr[i].stack_size = fs_thread_stack_sz[i];
            fs_thread_attr[i].tz_module  = 0U;
            fs_thread_attr[i].reserved   = 0U;

            fs_thread_handle[i] = NULL;
            fs_thread_handle[i] = osThreadNew(fs_thread_routine[i], NULL, &fs_thread_attr[i]);

            trace_assert(NULL != fs_thread_handle[i]);
        }
    }

    *chan_list = fs_channel_list;
    *chan_list_sz = CDEF_ELEMENT_COUNT(fs_channel_list);
}


void trace_assert(bool condition)
{
    if (!condition)
    {
        Error_Handler();
    }
}


trace_lock_t trace_lock_new(void)
{
    osMutexAttr_t attr =
    {
        .name      = NULL,
        .attr_bits = osMutexRecursive | osMutexPrioInherit,
        .cb_mem    = NULL,
        .cb_size   = 0U
    };

    return osMutexNew(&attr);
}


void trace_lock_acquire(trace_lock_t lock)
{
    if (NULL != lock)
    {
        (void)osMutexAcquire(lock, osWaitForever);
    }
    else
    {
        trace_assert(false);
    }
}


void trace_lock_release(trace_lock_t lock)
{
    if (NULL != lock)
    {
        (void)osMutexRelease(lock);
    }
    else
    {
        trace_assert(false);
    }
}


static void fs_thread_uart(void* args)
{
    (void)args;

    while (1)
    {
        trace_serve_chan(
                (uint32_t)FS_CHANNEL_UART,
                fs_work_buf[FS_CHANNEL_UART],
                sizeof(fs_work_buf[FS_CHANNEL_UART]));

        osDelay(FS_TRACE_SERVE_MS);
    }
}


static void fs_thread_file(void* args)
{
    (void)args;

    while (1)
    {
        trace_serve_chan(FS_CHANNEL_FILE,
                fs_work_buf[FS_CHANNEL_FILE],
                sizeof(fs_work_buf[FS_CHANNEL_FILE]));

        osDelay(FS_TRACE_SERVE_MS);
    }
}


static uint32_t fs_channel_data_send_to_uart(const uint8_t* data, const uint32_t data_sz)
{
    trace_assert(NULL != data);
    trace_assert(0 < data_sz);

    uint32_t transmitted_sz = data_sz;

    // transmit timeout set according to data_sz
    if (HAL_OK != HAL_UART_Transmit(&fs_huart, (uint8_t*)data, (uint16_t)data_sz, data_sz))
    {
        transmitted_sz = 0;
    }

    return transmitted_sz;
}


static uint32_t fs_channel_data_send_to_file(const uint8_t* data, const uint32_t data_sz)
{
    trace_assert(NULL != data);
    trace_assert(0 < data_sz);

    uint32_t written_data = 0;
    UINT bw = 0;

    if (FR_OK == SdMngr_rlf_open(&fs_rolling_file))
    {
        if (FR_OK == SdMngr_rlf_write(&fs_rolling_file, data, data_sz, &bw))
        {
            written_data = bw;
        }

        (void)SdMngr_rlf_close(&fs_rolling_file);
    }

    return written_data;
}


#if defined(STM32_SWV_SUPPORT) && defined(DEBUG_ENABLED)
static void fs_thread_swv(void* args)
{
    (void)args;

    while (1)
    {
        trace_serve_chan(FS_CHANNEL_SWV,
                fs_work_buf[FS_CHANNEL_SWV],
                sizeof(fs_work_buf[FS_CHANNEL_SWV]));

        osDelay(FS_TRACE_SERVE_MS);
    }
}


static uint32_t fs_channel_data_send_to_swv(const uint8_t* data, const uint32_t data_sz)
{
    trace_assert(NULL != data);
    trace_assert(0 < data_sz);

    for (uint32_t i = 0; i < data_sz; i++)
    {
        ITM_SendChar(data[i]);
    }

    return data_sz;
}
#endif


/**
 * @brief Initialization of UART for the UART trace output.
 */
static void trace_uart_init(void)
{
    fs_huart.Instance = NULL;

    if (true != sys_conf_is_module_active(SYS_MODULE_ID_GNSS))
    {
        fs_huart.Instance = UART5;
    }
    else if (true != sys_conf_is_module_active(SYS_MODULE_ID_EPS_M))
    {
        fs_huart.Instance = UART7;
    }
    else
    {
#if !defined(SLIP_SUPPORT_ENABLED) || !defined(LWIP_SUPPORT_ENABLED)
        fs_huart.Instance = UART8;
#endif
    }

    if (fs_huart.Instance != NULL)
    {
        fs_huart.Init.BaudRate               = 115200;
        fs_huart.Init.WordLength             = UART_WORDLENGTH_8B;
        fs_huart.Init.StopBits               = UART_STOPBITS_1;
        fs_huart.Init.Parity                 = UART_PARITY_NONE;
        fs_huart.Init.Mode                   = UART_MODE_TX;
        fs_huart.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
        fs_huart.Init.OverSampling           = UART_OVERSAMPLING_16;
        fs_huart.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
        fs_huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

        if (HAL_OK != HAL_UART_Init(&fs_huart))
        {
            fs_channel_list[FS_CHANNEL_UART].active = false; // Trace channel for UART shall not be used
            trace_assert(false);
        }
    }
    else
    {
        // All UARTs are occupied, so there will be no trace output via UART
        fs_channel_list[FS_CHANNEL_UART].active = false;
    }
}
