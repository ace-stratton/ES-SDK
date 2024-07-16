/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup es_sxband
 * @{
 *
 * @file     S_X_Band_Trnsm.c
 * @brief    S/X Band transmitter commands implementation
 *
 * @}
 *
 */

#include "es_cdef.h"
#include "S_X_Band_Trnsm.h"
#include "es_crc32.h"
#include "stm32h7xx_it.h"
#include "SdMngr.h"
#include "TaskMonitor.h"
#include "es_exeh.h"        /* Include DTC error handling */
#include "payload_shared_types.h"
#include "eps_ctrl.h"
#include "eps_ctrl_cfg.h"
#include "assertions.h"
#include "FileSink.h"
#include "crypto.h"
#include "timer.h"

#include <ctype.h>
#include <string.h>

/*
*********************************************************************************************
* INTERNAL DEFINES
*********************************************************************************************
*/
#define S_X_BAND_TRNSM_TX_RETRY               (10)                /**< Number of times to retry any packet */
#define S_X_BAND_TRNSM_CMD_RETRY              (6)                 /**< Number of times to retry a whole request/Command */
#define S_X_BAND_TRNSM_DELALL_CMD_RETRY       (150)               /**< Number of times to retry for the Delete All Files command */
#define S_X_BAND_TRNSM_HEADER                 (0x50555345)        /**< Header of every packet */
#define S_X_BAND_TRNSM_READ_FILE_CHUNCK_SIZE  (1472)              /**< Size of data read by one packet */
#define S_X_BAND_TRNSM_MAX_READ_BUFFER        (S_X_BAND_TRNSM_READ_FILE_CHUNCK_SIZE + S_X_BAND_TRNSM_TX_RETRY)   /**< Maximum size of read data */
#define S_X_BAND_TRNSM_DEFAULT_BAUDRATE       (4)                 /**< Default speed of the USART that is connected to the S-band transmitter */
#define S_X_BAND_STACK_SIZE                   (3)                 /**< X-Band stack size */
#define S_X_BAND_STACK_DELAY                  (2)                 /**< Default X-Band stack delay between protocol states (in ms) - this gets overridden for certain commands */
#define SBAND_OPEN_FILE_DELAY_MS              (3)                 /**< GetResult delay for OpenFile command on SBand modules */
#define XBAND_OPEN_FILE_DELAY_MS              (1)                 /**< GetResult delay for OpenFile command on XBand modules */
#define SBAND_DEL_FILE_DELAY_MS               (100)               /**< GetResult delay for DelFile command on SBand modules */
#define XBAND_DEL_FILE_DELAY_MS               (100)               /**< GetResult delay for DelFile command on XBand modules */

#define S_X_BAND_CMD_RESP_DELAY               (20)                /**< X-Band stack delay - time enough to guarantee the CMD response has been received (ms)*/
#define S_X_BAND_GET_RESULT_DELAY             (20)                /**< X-Band stack delay - time enough to guarantee the GET_RESULT response has been received (ms)*/
#define S_X_BAND_PACK_SIZE                    (16)                /**< X-Band packet size in bytes */
#define BITS_IN_1_BYTE                        (8)                 /**< number of bits in 1 byte; used to avoid magic numbers in the code */
/** Retry condition */
#define S_X_BAND_STACK_RETR_COND(stat)        (S_X_BAND_TRNSM_STAT_BUSY == (stat) || S_X_BAND_TRNSM_STAT_NACK == (stat))
/** Explicit macro for protocol retries reduction on condition */
#define S_X_BAND_STACK_RETR_SUB(condition,stackEntry)   if ((condition) && ((stackEntry)->retries > 0U)) (stackEntry)->retries--
#define DECR_IF_NONZERO(var)    if ((var) > 0U) (var)--

/** X-Band stack safety enabled or not */
#define S_X_BAND_STACK_SAFETY                 (1)

#define S_X_BAND_TASK_DMA_FLAG                (0x10)

#define TX_CMD_TIMEOUT_MS                     (60000U)   /**< maximum timeout for the TX mode command in milliseconds */
#define DEL_CMD_TIMEOUT_MS                    (60000U)   /**< maximum timeout for the Delete/DeleteAll commands in milliseconds */
#define CMD_AVG_TIMEOUT_MS                    (5000U)    /**< average worst-case timeout which should work for most commands */
#define FILE_CMD_TIMEOUT_MIN_MS               (1000.)    /**< minimum timeout in milliseconds for file operations */
#define WORST_BYTES_PER_SEC_RATE              (5000)     /**< OBC-to-SXBand upload Bps rate calculated with 20% margin on 250K physical bps link + streaming encryption overhead */

#define UNBLOCK_CACHE_THREAD_FLAG             (0x01)     /**< Event flag value used to unblock the cache update calling thread when the operation is finished */

#define INVALID_SETTING_VALUE_1B              (0xFF)     /**< Invalid setting value used for 1-byte module cache items */
#define INVALID_SETTING_VALUE_2B              (0xFFFF)   /**< Invalid setting value used for 2-byte module cache items */
#define TRNSM_ENC_OVERHEAD_PERCENTAGE         (36)       /**< Value in percent (%) of transmission-specific overhead such as zero packets, 8B/10B encoding and 2 intermittent comma characters for each 184 byte-packets */

static uint8_t file_tmp_buf[FILE_TEMP_BUFFER_SIZE];
static FIL fhnd;
static file_stream_fmt_ctx_t fstream_ctx =
{
    .p_data_buf = file_tmp_buf,
    .data_buf_size = sizeof(file_tmp_buf),
    .fop_status_last = FR_OK,
    .file_name = SX_BAND_FOUTPUT_NAME,
    .p_fhnd = &fhnd
};

static void USER_START_MULTI_BUF_SEQ(sUserResponseCtx_t * const pUserRespCtx)
{
    start_multi_buf_seq(pUserRespCtx);
    fstart_multi_buf_seq(&fstream_ctx);
}

static void USER_COMMIT_MULTI_BUF_SEQ(sUserResponseCtx_t * const pUserRespCtx)
{
    fcommit_multi_buf_seq(&fstream_ctx);
    commit_multi_buf_seq(pUserRespCtx);
}

#define USER_APPEND_FORMATTED_BUF(pUserRespCtx, format, ...) \
do \
{ \
    append_formatted_buf((pUserRespCtx), (format) OPT_VA_ARGS(__VA_ARGS__)); \
    fappend_formatted_buf(&fstream_ctx, (format) OPT_VA_ARGS(__VA_ARGS__)); \
} while (0)

#define USER_COMMIT_FORMATTED_BUF(pUserRespCtx, format, ...) \
do \
{\
    commit_formatted_buf((pUserRespCtx), (format) OPT_VA_ARGS(__VA_ARGS__));\
    fcommit_formatted_buf(&fstream_ctx, (format) OPT_VA_ARGS(__VA_ARGS__));\
} while (0)

/*
*********************************************************************************************
* INTERNAL TYPES DEFINITION
*********************************************************************************************
*/
/*
 * Protocol stack machine-related
 */
/** Commands NB states */
typedef enum S_X_BAND_TRNSM_CMD_State {
    S_X_BAND_TRNSM_CMD_STATE_EMPTY = 0x00,
    S_X_BAND_TRNSM_CMD_STATE_CMD,
    S_X_BAND_TRNSM_CMD_STATE_CMD_RES,
    S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT,
    S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES,
    S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED
} S_X_BAND_TRNSM_CMD_State;

/** Stack node/entry structure */
typedef struct X_BAND_CMD_StackEntry {
    uint16_t devID;
    S_X_BAND_TRNSM_CMD_State state;
    S_X_BAND_TRNSM_GW_CMD_ID_enum ESTTC_request;
    uint8_t ESTTC_request_type;
    uint8_t ESTTC_data_size;
    __ALIGN_BEGIN uint8_t ESTTC_data[S_X_BAND_TRNSM_RX_BUFF_SIZE] __ALIGN_END;
    S_X_BAND_TRNSM_CMD_enum command;
    bool isFileCommand;
    uint16_t type;
    S_X_BAND_TRNSM_Response_enum response;
    S_X_BAND_TRNSM_RetRes_enum result;
    uint32_t fileHandler, fileSize;
    uint32_t timestamp, minDelay;
    int16_t retries;
    uint8_t expectSlaveCommand;
    sUserResponseCtx_t *pUserRespCtx;
    struct X_BAND_CMD_StackEntry *parentEntry;
} S_X_BAND_CMD_StackEntry;

/** Callbacks type */
typedef uint8_t (*S_X_BAND_TRNSM_CMD_callbacks_t)(S_X_BAND_CMD_StackEntry *);

typedef enum {
    SX_SELECT_S_BAND_TRANSCEIVER,
    SX_SELECT_X_BAND_TRANSCEIVER,
    SX_SELECT_NONE,
    SX_SELECT_NUMBER
} S_X_BAND_Selection_Enum;

typedef enum
{
    CMD_EXTRACT_RESULT_UNSUP_CMD,
    CMD_EXTRACT_RESULT_VALID_CMD
} S_X_BAND_CMD_EXTRACT_RES;

typedef struct
{
    bool in_progress : 1;                       /**< true: dir list enumeration is in progress; false - otherwise */
    bool file_cache_valid : 1;                  /**< true: cache file is up to date; false: cache file content is out of date */
    bool settings_cache_valid : 1;              /**< true: ModCod and SymRate settings cache is valid; false: settings cache is not up to date */
    FIL fhnd;                                   /**< File handle for the cached SXBand file data */
    uint8_t sym_rate;                           /**< Symbol rate setting in MSym/s for SXBand module */
    uint8_t modcod;                             /**< Modulation Code index setting for SXBand module */
    uint16_t pretx_delay_ms;                    /**< Pre-transmission delay when switching to TX mode */
} S_X_BAND_Module_Cache;

/*
*********************************************************************************************
* EXTERNAL VARIABLES DEFINITION
*********************************************************************************************
*/
static uint16_t S_X_Band_Index = 0;                                              /* Number of received bytes */
static uint8_t  S_X_BAND_TRNSM_X_Band_Data[S_X_BAND_TRNSM_RX_BUFF_SIZE];         /* Buffer for row data from the S-band transmitter - includes header, information about the packet and the data itself */
static uint8_t  S_X_BAND_TRNSM_Result_Rx_Buffer[S_X_BAND_TRNSM_RX_BUFF_SIZE];    /* The received data that has been requested */
static __ALIGN_BEGIN uint8_t  S_X_BAND_DMA_Buffer[2 * S_X_BAND_PACK_SIZE] __ALIGN_END;

/** Configuration interface for the system instancer */
if_sys_mod_t sx_band_module_configuration = {
    .init = sx_band_init,
    .run = sx_band_run,
    .stop = sx_band_stop,
    .deinit = sx_band_deinit,
};

/*
*********************************************************************************************
* INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
*********************************************************************************************
*/
static __ALIGN_BEGIN uint8_t  TxDataBuffer[S_X_BAND_TRNSM_TX_BUFF_SIZE] __ALIGN_END;  /* Buffer for the data that is going to be transmitted */
static uint32_t S_X_BAND_TRNSM_S_Current_Baudrate;                                    /* Currently used baudrate */
static uint32_t S_X_BAND_LastExecCmd_Tick;                                            /* How much ticks has passed from the last executed command */
static S_X_BAND_Selection_Enum SX_BAND_Select_Module = SX_SELECT_NONE;

/** Descriptor of all commands: Gives the Value of the command and it's maximum size */
static const S_X_BAND_TRNSM_CMD_INFO_TxInfo_struct TxCMD_Descriptor[S_X_BAND_TRNSM_CMD_NUMBER] =
{
/* X_BAND_TRNSM_CMD_GET,          */ { S_X_BAND_TRNSM_CMD_VAL_GET           , 0                             ,12                             },
/* X_BAND_TRNSM_CMD_SET,          */ { S_X_BAND_TRNSM_CMD_VAL_SET           , 112                           ,1                              },
/* X_BAND_TRNSM_CMD_DIR_F,        */ { S_X_BAND_TRNSM_CMD_VAL_DIR_F         , 0                             ,S_X_BAND_TRNSM_MAX_READ_BUFFER   },
/* X_BAND_TRNSM_CMD_DIR_NEXT_F,   */ { S_X_BAND_TRNSM_CMD_VAL_DIR_NEXT_F    , 0                             ,S_X_BAND_TRNSM_MAX_READ_BUFFER   },
/* X_BAND_TRNSM_CMD_DELL_F,       */ { S_X_BAND_TRNSM_CMD_VAL_DELL_F        , 31                            ,1                              },
/* X_BAND_TRNSM_CMD_DELL_ALL_F,   */ { S_X_BAND_TRNSM_CMD_VAL_DELL_ALL_F    , 0                             ,1                              },
/* X_BAND_TRNSM_CMD_CREATE_F,     */ { S_X_BAND_TRNSM_CMD_VAL_CREATE_F      , 31                            ,1                              },
/* X_BAND_TRNSM_CMD_WRITE_F,      */ { S_X_BAND_TRNSM_CMD_VAL_WRITE_F       , S_X_BAND_TRNSM_MAX_READ_BUFFER  ,1                              },
/* X_BAND_TRNSM_CMD_OPEN_F,       */ { S_X_BAND_TRNSM_CMD_VAL_OPEN_F        , 31                            ,1                              },
/* X_BAND_TRNSM_CMD_READ_F,       */ { S_X_BAND_TRNSM_CMD_VAL_READ_F        , 4                             ,S_X_BAND_TRNSM_MAX_READ_BUFFER   },
/* X_BAND_TRNSM_CMD_SEND_F,       */ { S_X_BAND_TRNSM_CMD_VAL_SEND_F        , 31                            ,1                              },
/* X_BAND_TRNSM_CMD_TX_MODE,      */ { S_X_BAND_TRNSM_CMD_VAL_TX_MODE       , 0                             ,1                              },
/* X_BAND_TRNSM_CMD_LOAD_MODE,    */ { S_X_BAND_TRNSM_CMD_VAL_IDLE_MODE     , 0                             ,1                              },
/* X_BAND_TRNSM_CMD_UPDATE_FW,    */ { S_X_BAND_TRNSM_CMD_VAL_UPDATE_FW     , 31                            ,1                              },
/* X_BAND_TRNSM_CMD_SAFE_SHUTDOWN,*/ { S_X_BAND_TRNSM_CMD_VAL_SAFE_SHUTDOWN , 0                             ,1                              },
/* X_BAND_TRNSM_CMD_GET_RES,      */ { S_X_BAND_TRNSM_CMD_VAL_GET_RESULT    , 2                             ,S_X_BAND_TRNSM_MAX_READ_BUFFER   }
};

/** @brief command-specific GetResult poll intervals while status is busy (in milliseconds)
 */
static const uint8_t TxCMD_BusyTimePeriod[S_X_BAND_TRNSM_CMD_NUMBER] =
{
/* S_X_BAND_TRNSM_CMD_GET,          */ 1,
/* S_X_BAND_TRNSM_CMD_SET,          */ 10,
/* S_X_BAND_TRNSM_CMD_DIR_F,        */ 1,
/* S_X_BAND_TRNSM_CMD_DIR_NEXT_F,   */ 1,
/* S_X_BAND_TRNSM_CMD_DELL_F,       */ 200,
/* S_X_BAND_TRNSM_CMD_DELL_ALL_F,   */ 255,
/* S_X_BAND_TRNSM_CMD_CREATE_F,     */ 1,
/* S_X_BAND_TRNSM_CMD_WRITE_F,      */ 1,
/* S_X_BAND_TRNSM_CMD_OPEN_F,       */ 1,
/* S_X_BAND_TRNSM_CMD_READ_F,       */ 1,
/* S_X_BAND_TRNSM_CMD_SEND_F,       */ 255,
/* S_X_BAND_TRNSM_CMD_TX_MODE,      */ 255,
/* S_X_BAND_TRNSM_CMD_LOAD_MODE,    */ 10,
/* S_X_BAND_TRNSM_CMD_UPDATE_FW,    */ 10,
/* S_X_BAND_TRNSM_CMD_SAFE_SHUTDOWN,*/ 1,
/* S_X_BAND_TRNSM_CMD_GET_RES,      */ 1
};

/** Supported baudrates */
static const uint32_t BaudRateArray[] = {
        250000,     //0 250kHz
        500000,     //1 500kHz
        1000000,    //2 1MHz
        2000000,    //3 2MHz
        3000000,    //4 3MHz
        5000000,    //5 5MHz
};

/** @brief ModCod coefficients for downlink worst-case timeout estimation
 *  Refer to SXBand User's Manual for calculation details
 *  - S-Band Transmitter rev. 2.11 / page 68
 *  - X-Band Transmitter rev. 2.5 / page 68
 */
static const float ModCod_BitRate_Coeffs[] =
{
    0.481,    // QPSK_1/4
    0.643,    // QPSK_1/3
    0.774,    // QPSK_2/5
    0.968,    // QPSK_1/2
    1.163,    // QPSK_3/5
    1.294,    // QPSK_2/3
    1.455,    // QPSK_3/4
    1.551,    // QPSK_4/5
    1.618,    // QPSK_5/6
    1.727,    // QPSK_8/9
    1.749,    // QPSK_9/10
    1.744,    // 8PSK_3/5
    1.940,    // 8PSK_2/3
    2.182,    // 8PSK_3/4
    2.427,    // 8PSK_5/6
    2.590,    // 8PSK_8/9
    2.623,    // 8PSK_9/10
    2.580,    // 16APSK_2/3
    2.902,    // 16APSK_3/4
    3.096,    // 16APSK_4/5
    3.227,    // 16APSK_5/6
    3.445,    // 16APSK_8/9
    3.487,    // 16APSK_9/10
    3.630,    // 32APSK_3/4
    3.973,    // 32APSK_4/5
    4.037,    // 32APSK_5/6
    4.310,    // 32APSK_8/9
    4.364,    // 32APSK_9/10
};

/* Stack-related */
/** Stack structure */
static S_X_BAND_CMD_StackEntry XSBandStack[S_X_BAND_STACK_SIZE];
static S_X_BAND_CMD_StackEntry XSBandStack_Slave;

/* Driver device type */
static S_X_BAND_TRNSM_DEVTYPE XSBandDevType = S_X_BAND_TRNSM_DEVTYPE_UNKNOWN;


/** @brief SXBand local cache information and validity status */
static S_X_BAND_Module_Cache moduleCacheInfo =
{
    .in_progress = false,
    .file_cache_valid = false,
    .settings_cache_valid = false,
    .modcod = INVALID_SETTING_VALUE_1B,
    .sym_rate = INVALID_SETTING_VALUE_1B,
    .pretx_delay_ms = INVALID_SETTING_VALUE_2B
};

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DECLARATION
*********************************************************************************************
*/
static void S_X_BAND_TRNSM_Init_Usart(uint32_t baud_rate);
static void S_X_BAND_TRNSM_Rx_Tx_State (uint8_t state);
static void S_X_BAND_TRNSM_Send_Ack (uint16_t Identifier, S_X_BAND_TRNSM_CMD_enum CMD, uint16_t CMD_Type);
static uint8_t S_X_BAND_TRNSM_CMD_GET_Param (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_CMD_SET_Param (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_CMD_Dir (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_CMD_Dir_Extended (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_DelFile (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_CreateFile (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_UploadFileToSBandTrnsm (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_DownloadFileFromSBandTrnsm (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_OpenFile (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_SendFile (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_StartTxMode (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_StartLoadMode (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_FW_Update (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_ShutDownMode (S_X_BAND_CMD_StackEntry *stackEntry);
static uint8_t S_X_BAND_TRNSM_CMD_SET_Param_Baudrate (S_X_BAND_CMD_StackEntry *stackEntry);
static void XSBandTryFinish (uint8_t retRes, S_X_BAND_CMD_StackEntry *stackEntry);
static S_X_BAND_CMD_EXTRACT_RES XSBandExtractCommandAndType (S_X_BAND_CMD_StackEntry *stackEntry);
static bool S_X_BAND_TRNSM_Scan_Baud_Rates(uint16_t Identifier);
static uint8_t S_X_BAND_TRNSM_FileNameParser (uint16_t Identifier, uint8_t * FileListBuffer, S_X_BAND_TRNSM_FileInfo_struct * File);
/* Low level functions */
static S_X_BAND_TRNSM_Response_enum S_X_BAND_TRNSM_SendCMD(uint16_t Identifier, S_X_BAND_TRNSM_CMD_enum CMD, uint16_t CMD_Type, const uint8_t * TxData, uint16_t TxDataLenght);
static S_X_BAND_TRNSM_Response_enum S_X_BAND_TRNSM_GetResult(uint16_t Identifier, S_X_BAND_TRNSM_CMD_enum CMD, uint16_t CMD_Type, uint8_t * RxData, uint16_t * RxDataLenght);
static uint8_t S_X_Select(S_X_BAND_Selection_Enum Type );
static void S_X_DeSelect(void);
static void S_X_BAND_TRNSM_Detect_Band_Type(const uint16_t Identifier);
static uint32_t S_X_Band_Get_Cmd_Timeout(uint16_t Identifier, S_X_BAND_TRNSM_GW_CMD_ID_enum Cmd, uint8_t Type, uint8_t size, const uint8_t * pData);
static void S_X_Band_On_Dir_List_Start(void);
static void S_X_Band_On_Enumerate_File(const S_X_BAND_TRNSM_FileInfo_struct * const pFileInfo);
static void S_X_Band_On_Dir_List_Finished(void);
static uint64_t S_X_Band_Get_File_Size_From_Cache(const char * const pFilePattern);
static bool S_X_Band_Is_Pattern_Matching(const char* const pFilePattern, const uint32_t patSize, const char* const pFileName, const uint32_t fnSize);
static void S_X_Band_Update_Module_Cache(uint16_t Identifier);
static void S_X_Band_On_CacheUpdateReady(void * const pUserCtx);
static void sx_band_init_stack(S_X_BAND_CMD_StackEntry * const p_stack_entry);

/* A function to check whether the radio module is an X-Band type */
static inline bool IS_XBAND(void) { return S_X_BAND_TRNSM_DEVTYPE_XBAND == XSBandDevType; }

/** @brief A thread handle for the cache update task */
static osThreadId_t cacheUpdateThread = NULL;

/* End of Low level functions */
// Stack callback table
static const S_X_BAND_TRNSM_CMD_callbacks_t XSBandCallbacks[S_X_BAND_TRNSM_CMD_NUMBER] = {
    /* S_X_BAND_TRNSM_CMD_GET */                      S_X_BAND_TRNSM_CMD_GET_Param,
    /* S_X_BAND_TRNSM_CMD_SET */                      S_X_BAND_TRNSM_CMD_SET_Param,
    /* S_X_BAND_TRNSM_CMD_DIR_F */                    S_X_BAND_TRNSM_CMD_Dir_Extended,
    /* S_X_BAND_TRNSM_CMD_DIR_NEXT_F */               S_X_BAND_TRNSM_CMD_Dir_Extended,
    /* S_X_BAND_TRNSM_CMD_DELL_F */                   S_X_BAND_TRNSM_DelFile,
    /* S_X_BAND_TRNSM_CMD_DELL_ALL_F */               S_X_BAND_TRNSM_DelFile,
    /* S_X_BAND_TRNSM_CMD_CREATE_F */                 S_X_BAND_TRNSM_UploadFileToSBandTrnsm,
    /* S_S_X_BAND_TRNSM_CMD_WRITE_F */                S_X_BAND_TRNSM_UploadFileToSBandTrnsm,
    /* S_X_BAND_TRNSM_CMD_OPEN_F */                   S_X_BAND_TRNSM_DownloadFileFromSBandTrnsm,
    /* S_X_BAND_TRNSM_CMD_READ_F */                   S_X_BAND_TRNSM_DownloadFileFromSBandTrnsm,
    /* S_X_BAND_TRNSM_CMD_SEND_F */                   S_X_BAND_TRNSM_SendFile,
    /* S_X_BAND_TRNSM_CMD_TX_MODE */                  S_X_BAND_TRNSM_StartTxMode,
    /* S_X_BAND_TRNSM_CMD_LOAD_MODE */                S_X_BAND_TRNSM_StartLoadMode,
    /* S_X_BAND_TRNSM_CMD_UPDATE_FW */                S_X_BAND_TRNSM_FW_Update,
    /* S_X_BAND_TRNSM_CMD_SAFE_SHUTDOWN */            S_X_BAND_TRNSM_ShutDownMode,
    /* S_X_BAND_TRNSM_CMD_GET_RES */                  NULL
};

static osThreadId_t S_X_BAND_Task_TaskHandle;
static const osThreadAttr_t S_X_BAND_Task_attributes = {
  .name = "S_X_BAND_Task",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 8192
};

static const osMutexAttr_t sxband_lock_attr =
{
    "sxband_mutex",       // human readable mutex name
    osMutexRecursive,     // attr_bits
    NULL,                 // memory for control block
    0U                    // size for control block
};

/** @brief Mutex handle provided by the OS */
static osMutexId_t sxband_lock_id;

static UART_HandleTypeDef *p_sx_band_uart_hnd = (UART_HandleTypeDef *) NULL;

/*
*********************************************************************************************
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
// System module interface functions
mod_op_status_id_t sx_band_init(sys_init_level_id_t level){
    mod_op_status_id_t ret = STATUS_NOT_SUPPORTED;

    // Eventually, to split the initialisation into the different levels
    if(level == INIT_MEM)
    {
        /* MEMORY LEVEL INITIALIZATION */
        /* Reset the in-memory structures */
        for (uint8_t stack_idx = 0; stack_idx < S_X_BAND_STACK_SIZE; stack_idx++)
        {
            sx_band_init_stack(&XSBandStack[stack_idx]);
        }
        sx_band_init_stack(&XSBandStack_Slave);
        memset(TxDataBuffer, 0, S_X_BAND_TRNSM_TX_BUFF_SIZE);
        S_X_BAND_LastExecCmd_Tick = 0;

        es_sxband_config_init();

        p_sx_band_uart_hnd = es_sxband_config_get_usart_hnd();
        CRIT_ASSERT(NULL != p_sx_band_uart_hnd);

        /* Initialize the Current baudrate to default */
        S_X_BAND_TRNSM_S_Current_Baudrate = S_X_BAND_TRNSM_DEFAULT_BAUDRATE;

        XSBandDevType = S_X_BAND_TRNSM_DEVTYPE_UNKNOWN;

        ret = STATUS_OK;
    }
    else if (level == INIT_HW)
    {
        GPIO_InitTypeDef GPIO_InitStruct;

        /* HW LEVEL INITIALIZATION */
        HAL_UART_DMAStop(p_sx_band_uart_hnd);
        HAL_UART_DeInit(p_sx_band_uart_hnd);

        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();

        /* DMA controller clock enable */
        DMA_CLK_ENABLE();

        /* DMA interrupt init */
        /* DMA_Stream1_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(DMA_Stream1_IRQn, 4, 0);
        HAL_NVIC_EnableIRQ(DMA_Stream1_IRQn);
        /* DMA_Stream2_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(DMA_Stream2_IRQn, 4, 0);
        HAL_NVIC_EnableIRQ(DMA_Stream2_IRQn);

        /* USART_IRQ interrupt configuration */
        HAL_NVIC_SetPriority(USART_IRQ, 5, 0);
        HAL_NVIC_EnableIRQ(USART_IRQ);

        S_X_BAND_TRNSM_Init_Usart(S_X_BAND_TRNSM_GetBaudrate());

        HAL_UART_RegisterCallback(p_sx_band_uart_hnd, HAL_UART_RX_HALFCOMPLETE_CB_ID, S_X_BAND_UART_RxHalfCpltCallback);
        HAL_UART_RegisterCallback(p_sx_band_uart_hnd, HAL_UART_RX_COMPLETE_CB_ID, S_X_BAND_UART_RxCpltCallback);
        HAL_UART_RegisterCallback(p_sx_band_uart_hnd, HAL_UART_TX_COMPLETE_CB_ID, S_X_BAND_UART_TxCpltCallback);
        HAL_UART_RegisterCallback(p_sx_band_uart_hnd, HAL_UART_ERROR_CB_ID, S_X_BAND_UART_ErrorCallback);

        /*Configure GPIO pin Output Level */
        HAL_GPIO_WritePin(SX_BAND_TxEnbl_GPIO_Port, SX_BAND_TxEnblPin, GPIO_PIN_RESET);

        /*Configure GPIO pin : RS485 Transmit enable pin */
        GPIO_InitStruct.Pin = SX_BAND_TxEnblPin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(SX_BAND_TxEnbl_GPIO_Port, &GPIO_InitStruct);

        /* Release the USART interface */
        S_X_DeSelect();

        ret = STATUS_OK;
    }
    else if (level == INIT_OS)
    {
        if (NULL == sxband_lock_id)
        {
            sxband_lock_id = osMutexNew(&sxband_lock_attr);
        }


        S_X_BAND_Task_TaskHandle = osThreadNew(S_X_BAND_Task, NULL, &S_X_BAND_Task_attributes);
        CRIT_ASSERT( S_X_BAND_Task_TaskHandle );

        // Set the task monitor policy
        task_mon_set_task_policy(TASK_MONITOR_S_X_BAND, TASK_MON_POLICY_MONITOR);
        ret = STATUS_OK;
    }
    else
    {
        ret = STATUS_NOT_SUPPORTED;;
    }

    return ret;
}
mod_op_status_id_t sx_band_run(){
    // This is to be implemented
    return STATUS_NOT_SUPPORTED;
}
mod_op_status_id_t sx_band_stop()
{
    (void) osMutexAcquire(sxband_lock_id, osWaitForever);

    sx_band_init(INIT_MEM);
    sx_band_init(INIT_HW);

    (void) osMutexRelease(sxband_lock_id);

    return STATUS_OK;
}
mod_op_status_id_t sx_band_deinit(sys_init_level_id_t level){
    // Hardware and OS levels
    if (level ==  INIT_HW)
    {
        p_sx_band_uart_hnd = es_sxband_config_get_usart_hnd();
        CRIT_ASSERT(NULL != p_sx_band_uart_hnd);
        /* HW LEVEL DEINITIALIZATION */
        HAL_UART_DMAStop(p_sx_band_uart_hnd);

        GPIO_InitTypeDef GPIO_InitStruct = {0};

        HAL_UART_DeInit(p_sx_band_uart_hnd);

        HAL_GPIO_WritePin(U3_RS485_S1_DE_GPIO_Port, U3_RS485_S1_DE_Pin, GPIO_PIN_RESET);

        /*Configure GPIO pins : U3_RS485_S1_DE_Pin */
        GPIO_InitStruct.Pin = U3_RS485_S1_DE_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(U3_RS485_S1_DE_GPIO_Port, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = U3_RS485_S1_nRE_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(U3_RS485_S1_nRE_GPIO_Port, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = U3_RS485_S1_RX_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(U3_RS485_S1_RX_GPIO_Port, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = U3_RS485_S1_TX_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(U3_RS485_S1_TX_GPIO_Port, &GPIO_InitStruct);
    }
    else if (level == INIT_OS) {
        task_mon_set_task_policy(TASK_MONITOR_S_X_BAND, TASK_MON_POLICY_DONT_CARE);
    }

    return STATUS_OK;

}

uint32_t S_X_BAND_TRNSM_GetBaudrate(void)
{
    return BaudRateArray[S_X_BAND_TRNSM_S_Current_Baudrate];
}

static void S_X_BAND_TRNSM_Init_Usart(uint32_t baud_rate)
{
    p_sx_band_uart_hnd->Init.BaudRate = baud_rate;
    p_sx_band_uart_hnd->Init.WordLength = UART_WORDLENGTH_8B;
    p_sx_band_uart_hnd->Init.StopBits = UART_STOPBITS_1;
    p_sx_band_uart_hnd->Init.Parity = UART_PARITY_NONE;
    p_sx_band_uart_hnd->Init.Mode = UART_MODE_TX_RX;
    p_sx_band_uart_hnd->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    p_sx_band_uart_hnd->Init.OverSampling = UART_OVERSAMPLING_8;
    p_sx_band_uart_hnd->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    p_sx_band_uart_hnd->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(p_sx_band_uart_hnd) != HAL_OK)
    {
        Error_Handler();
    }
}

/*
********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
********************************************************************************************
*/

static uint8_t S_X_Select(S_X_BAND_Selection_Enum Type )
{
    uint8_t retVal;

    if((Type < SX_SELECT_NONE)&&(SX_BAND_Select_Module >= SX_SELECT_NONE))
    {
        SX_BAND_Select_Module = Type;
        retVal = pdTRUE;
    }else{
        retVal = pdFALSE;
    }

    return retVal;
}

static void S_X_DeSelect(void)
{
    SX_BAND_Select_Module = SX_SELECT_NONE;
}

/**
 * @brief Send a command to S-Band transmitter
 * @param[input]      Identifier - ID of the used S or X band transmitter
 * @param[input]      CMD - command number from enumeration X_BAND_TRNSM_CMD_enum
 * @param[input]      CMD_Type - Some commands have different types, the rest don't have. Use values as follow:
 *                       + X_BAND_TRNSM_NULL_TYPE - for commands without type
 *                       + value form X_BAND_TRNSM_GET_types_enum - for Command GET (X_BAND_TRNSM_CMD_GET)
 *                       + value from X_BAND_TRNSM_SET_types_enum - for Command SET (X_BAND_TRNSM_CMD_SET)
 *                       + value from X_BAND_TRNSM_SendFile_types_enum - for Command SEND FILE (X_BAND_TRNSM_CMD_SEND_F)
 *                       + value from X_BAND_TRNSM_SendFile_types_enum - for Command SEND FILE (X_BAND_TRNSM_CMD_SEND_F)
 * @param[input]      TxData - Data that is going to be transmitted. If the command does not require TxData can be = NULL
 * @param[input]      TxDataLenght - Number of bytes to be transmitted
 *
 * @return            retStat - a value from enumeration S_X_BAND_TRNSM_Response_enum
 */
static S_X_BAND_TRNSM_Response_enum S_X_BAND_TRNSM_SendCMD (uint16_t Identifier, S_X_BAND_TRNSM_CMD_enum CMD, uint16_t CMD_Type, const uint8_t * TxData, uint16_t TxDataLenght) {
    uint8_t retries;
    S_X_BAND_TRNSM_Pack_struct * RxPackStruct = (S_X_BAND_TRNSM_Pack_struct *)S_X_BAND_TRNSM_X_Band_Data;
    S_X_BAND_TRNSM_Pack_struct * TxPackStruct = (S_X_BAND_TRNSM_Pack_struct *)TxDataBuffer;
    uint32_t RxCRC;
    uint32_t * pRxCRC;
    uint32_t TxPackCRC = 0;

    if (CMD >= S_X_BAND_TRNSM_CMD_GET_RES) {
        /* allow all commands but Get result */
        return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
    }
    if ((TxDataLenght + sizeof (S_X_BAND_TRNSM_Pack_struct) + sizeof(RxCRC) ) > S_X_BAND_TRNSM_TX_BUFF_SIZE) {
        /* if CPU stops here - please increase the size of the buffer -> X_BAND_TRNSM_TX_BUFF_SIZE */
        return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
    }
    // Stack timeout
    if ((xTaskGetTickCount() - S_X_BAND_LastExecCmd_Tick) < (1 * S_X_BAND_STACK_DELAY)) {
        return S_X_BAND_TRNSM_STAT_GET_RESULT;
    }
    TxPackStruct->Header = S_X_BAND_TRNSM_HEADER;
    TxPackStruct->ModuleID = Identifier;
    if (TxCMD_Descriptor[CMD].tx_data_max_size > 0) {
        if (TxCMD_Descriptor[CMD].tx_data_max_size >= TxDataLenght) {
            TxPackStruct->Length = TxDataLenght;
        } else {
            return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
        }
    } else {
        TxPackStruct->Length = 0;
    }
    TxPackStruct->Response = 0;
    TxPackStruct->CMD = TxCMD_Descriptor[CMD].CMD;
    TxPackStruct->Type = CMD_Type;
    if (TxPackStruct->Length > 0) {
        if (!TxData) {
            /* Invalid data pointer */
            return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
        }
        /* copy the data of the packet to the transmit buffer, after the structure */
        memcpy(&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE], TxData, TxPackStruct->Length);

        /* copy the CRC to the transmit buffer after the data */
        TxPackCRC = crc32(0, (BYTE *)TxPackStruct, S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length);
        memcpy(&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE+TxPackStruct->Length], &TxPackCRC, sizeof(TxPackCRC));
    } else {
        TxPackCRC = crc32(0, (BYTE *)TxPackStruct, S_X_BAND_TRNSM_STRCT_SIZE);
        /* copy the CRC to the transmit buffer after the structure of the packet */
        memcpy(&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE], &TxPackCRC, sizeof(TxPackCRC));
    }
    for (retries = 0; retries < S_X_BAND_TRNSM_TX_RETRY ;) {
        if (((((S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC) - 1) >> 4) + 1) << 4) > sizeof (TxDataBuffer)) {
            S_X_BAND_LastExecCmd_Tick = xTaskGetTickCount();
            /* check if the transmit buffer is insufficient */
            return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
        }
        /* Reserve the USART interface for X-band */
        if (pdFALSE == S_X_Select (SX_SELECT_X_BAND_TRANSCEIVER)) {
            S_X_BAND_LastExecCmd_Tick = xTaskGetTickCount();
            return S_X_BAND_TRNSM_STAT_COMM_ERR;
        }

        osThreadFlagsClear(S_X_BAND_TASK_DMA_FLAG);
        S_X_Band_Index = 0;
        HAL_StatusTypeDef HalRes = HAL_UART_Receive_DMA (p_sx_band_uart_hnd, S_X_BAND_DMA_Buffer, 2*S_X_BAND_PACK_SIZE);

        if (HAL_OK != HalRes)
        {
            (void) HAL_UART_AbortReceive_IT(p_sx_band_uart_hnd);
        }
        // Clear the extra bytes that will be set after the packet to complete to divisible to 16
        memset (&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC)], 0, ((((S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC) - 1) >> 4) + 1) << 4) - (S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC)));
        S_X_BAND_TRNSM_Rx_Tx_State(1);
        (void) HAL_UART_Transmit_DMA (p_sx_band_uart_hnd, TxDataBuffer, (((S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC) - 1) >> 4) + 1) << 4);
        (void) osThreadFlagsWait(S_X_BAND_TASK_DMA_FLAG, osFlagsWaitAny, S_X_BAND_CMD_RESP_DELAY);

        HAL_UART_AbortReceive(p_sx_band_uart_hnd); // the packet is received, no need to continued receiving (the DMA buffer is bigger then the packet and will never be filled with one packet)
        /* Release the USART interface */
        S_X_DeSelect();

        if (S_X_Band_Index > 0) {
            S_X_Band_Index = 0;
            // check for end of pack and verify the packet
            if (
                 (RxPackStruct->Header == TxPackStruct->Header) &&
                 (RxPackStruct->ModuleID == TxPackStruct->ModuleID)) {
                RxCRC = crc32 (0, S_X_BAND_TRNSM_X_Band_Data, S_X_BAND_TRNSM_STRCT_SIZE);
                pRxCRC = (uint32_t *)&S_X_BAND_TRNSM_X_Band_Data[S_X_BAND_TRNSM_STRCT_SIZE];
                if (*pRxCRC == RxCRC) {
                    if (RxPackStruct->Response == S_X_BAND_TRNSM_STAT_ACK) {
                        retries = S_X_BAND_TRNSM_TX_RETRY; // exit the loop

                        // This delay is absolutely necessary for proper GetResult response, otherwise NCE my occur
                        osDelay(2);
                    } else {
                        RxPackStruct->Response = S_X_BAND_TRNSM_STAT_NACK;
                        // retry - send the packet again
                    }
                } else {
                    // wrong CRC
                    RxPackStruct->Response = S_X_BAND_TRNSM_STAT_COMM_ERR;
                    // retry - send the packet again
                }
            } else {
                // wrong data structure
                RxPackStruct->Response = S_X_BAND_TRNSM_STAT_COMM_ERR;
                // retry - send the packet again
            }
        } else {
            // none bytes are received
            RxPackStruct->Response = S_X_BAND_TRNSM_STAT_COMM_ERR;
            // retry - send the packet again - due to timeout with on answer
        }
        if (retries < S_X_BAND_TRNSM_TX_RETRY) {
            retries++;
        }
    }
    S_X_BAND_LastExecCmd_Tick = xTaskGetTickCount();

    return (S_X_BAND_TRNSM_Response_enum)RxPackStruct->Response;
}

/**
 * @brief Gets the result of a command that have been transmitted recently
 * @param[input]      Identifier - ID of the used S or X band transmitter
 * @param[input]      CMD - command number from enumeration X_BAND_TRNSM_CMD_enum, that was already transmitted
 * @param[input]      CMD_Type - value from enumeration X_BAND_TRNSM_RetRes_enum
 * @param[output]     RxData - Data that is going to be received. If the command does not require RxData can be = NULL
 * @param[output]     RxDataLenght - Number of bytes to be received
 *
 * @return            retStat - a value from enumeration S_X_BAND_TRNSM_Response_enum
 */
static S_X_BAND_TRNSM_Response_enum S_X_BAND_TRNSM_GetResult (uint16_t Identifier, S_X_BAND_TRNSM_CMD_enum CMD, uint16_t CMD_Type, uint8_t * RxData, uint16_t * RxDataLenght) {
    S_X_BAND_TRNSM_Pack_struct * RxPackStruct = (S_X_BAND_TRNSM_Pack_struct *)S_X_BAND_TRNSM_X_Band_Data;
    S_X_BAND_TRNSM_Pack_struct * TxPackStruct = (S_X_BAND_TRNSM_Pack_struct *)TxDataBuffer;
    uint32_t RxCRC;
    uint32_t const * pRxCRC;
    uint32_t TxPackCRC = 0;

    if (!RxDataLenght) {
        /* Invalid data pointer */
        return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
    } else {
        /* default value - 0 byes have been read */
        *RxDataLenght = 0;
    }
    if (!RxData) {
        /* Invalid data pointer */
        return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
    }
    TxPackStruct->Header = S_X_BAND_TRNSM_HEADER;
    TxPackStruct->ModuleID = Identifier;
    TxPackStruct->Response = 0;
    TxPackStruct->CMD = TxCMD_Descriptor[S_X_BAND_TRNSM_CMD_GET_RES].CMD;
    TxPackStruct->Type = TxCMD_Descriptor[CMD].CMD;
    if ((CMD == S_X_BAND_TRNSM_CMD_GET) ||
        (CMD == S_X_BAND_TRNSM_CMD_SET)  ||
        (CMD == S_X_BAND_TRNSM_CMD_SEND_F)) {
        /* copy the type of the command */
        TxPackStruct->Length = 2;
        TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE] = (uint8_t)CMD_Type;
        TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE+1] = (uint8_t)(CMD_Type>>8);
    } else {
        TxPackStruct->Length = 0;
    }

    /* copy the structure of the packet to the transmit buffer */
    TxPackCRC = crc32 (0, (BYTE *)TxPackStruct, S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length);
    /* copy the CRC to the transmit buffer after the structure of the packet */
    memcpy (&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length], &TxPackCRC, sizeof (TxPackCRC));
    for (uint8_t retries = 0; retries < S_X_BAND_TRNSM_TX_RETRY ;) {
        if (((((S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC) - 1) >> 4) + 1) << 4) > sizeof (TxDataBuffer)) {
            /* check if the transmit buffer is insufficient */
            return S_X_BAND_TRNSM_STAT_WRONG_PARAM;
        }
        /* Reserve the USART interface for X-band */
        if (pdFALSE == S_X_Select (SX_SELECT_X_BAND_TRANSCEIVER)) {
            return S_X_BAND_TRNSM_STAT_COMM_ERR;
        }

        osThreadFlagsClear(S_X_BAND_TASK_DMA_FLAG);
        S_X_Band_Index = 0;
        HAL_StatusTypeDef HalRes = HAL_UART_Receive_DMA (p_sx_band_uart_hnd, S_X_BAND_DMA_Buffer, 2*S_X_BAND_PACK_SIZE);

        if (HAL_OK != HalRes)
        {
            (void) HAL_UART_AbortReceive_IT(p_sx_band_uart_hnd);
        }
        // Clear the extra bytes that will be set after the packet to complete to divisible to 16
        memset (&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC)], 0, ((((S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC) - 1) >> 4) + 1) << 4) - (S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC)));
        S_X_BAND_TRNSM_Rx_Tx_State(1);
        (void) HAL_UART_Transmit_DMA (p_sx_band_uart_hnd, TxDataBuffer, (((S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length + sizeof (TxPackCRC) - 1) >> 4) + 1) << 4);
        (void) osThreadFlagsWait(S_X_BAND_TASK_DMA_FLAG, osFlagsWaitAny, S_X_BAND_GET_RESULT_DELAY);

        (void) HAL_UART_AbortReceive(p_sx_band_uart_hnd); // the packet is received, no need to continued receiving (the DMA buffer is bigger then the packet and will never be filled with one packet)
        /* Release the USART interface */
        S_X_DeSelect();

        SX_BAND_TRACE_VERBOSE("hdr: 0x%08x mod: 0x%04x len: %ld cmd: 0x%04x type: %ld resp: %ld\r\n", RxPackStruct->Header, RxPackStruct->ModuleID, RxPackStruct->Length, RxPackStruct->CMD, RxPackStruct->Type, RxPackStruct->Response);

        if (S_X_Band_Index > 0) {
            S_X_Band_Index = 0;
            // check for end of pack and verify the packet
            if (
                 (RxPackStruct->Header == TxPackStruct->Header) &&
                 (RxPackStruct->ModuleID == TxPackStruct->ModuleID)
               ) {
                RxCRC = crc32 (0, S_X_BAND_TRNSM_X_Band_Data, S_X_BAND_TRNSM_STRCT_SIZE + RxPackStruct->Length);
                pRxCRC = (uint32_t *)&S_X_BAND_TRNSM_X_Band_Data[S_X_BAND_TRNSM_STRCT_SIZE + RxPackStruct->Length];

                SX_BAND_TRACE_VERBOSE("RxCRC = 0x%08x RcvdCRC = 0x%08x\r\n", RxCRC, *pRxCRC);

                if (*pRxCRC == RxCRC) {
                    if (RxPackStruct->Response == S_X_BAND_TRNSM_STAT_BUSY) {
                        osDelay (TxCMD_BusyTimePeriod[CMD]);
                        break;
                    } else { // Constant looping between states !!!!!!!!!!!!!!!!!!!!!!!
                        retries = S_X_BAND_TRNSM_TX_RETRY; // exit the loop
                        if (RxPackStruct->Response == S_X_BAND_TRNSM_STAT_GET_RESULT) {
                            // Copy the length of data
                            *RxDataLenght = RxPackStruct->Length;
                            //copy the data
                            memcpy (RxData, &S_X_BAND_TRNSM_X_Band_Data[S_X_BAND_TRNSM_STRCT_SIZE], RxPackStruct->Length);
                            S_X_BAND_TRNSM_Send_Ack (Identifier, CMD, CMD_Type);
                        }
                    }
                }
            }
        }

        if (retries < S_X_BAND_TRNSM_TX_RETRY) {  // If maximum number of retries is not reached
            retries++;  // Count one more retry
            if (retries == S_X_BAND_TRNSM_TX_RETRY) { // If last retry is done
                RxPackStruct->Response = S_X_BAND_TRNSM_STAT_NACK;
            } else {
                // Retry
            }
        }
    }

    return (S_X_BAND_TRNSM_Response_enum)RxPackStruct->Response;
}

/**
 * @brief Change the Setting: Baudrate
 * @param[input]      stackEntry - current stack entry
 *
 * @return            retStat - a value from enumeration X_BAND_TRNSM_SetGetParams_enum
 */
static uint8_t S_X_BAND_TRNSM_CMD_SET_Param_Baudrate (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t  retStat = 0x00;
    uint16_t RxDataLenght;
    static uint32_t Current_Baudrate_Temp;
    uint8_t pBaudrate = *((uint8_t *)stackEntry->ESTTC_data);

    // Check the requested baud rate
    if (pBaudrate >= CDEF_ELEMENT_COUNT(BaudRateArray)) {
        retStat = S_X_BAND_TRNSM_PARAMS_PARAMS_ERR;
        return retStat;
    }
    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = 0x01;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            Current_Baudrate_Temp = S_X_BAND_TRNSM_S_Current_Baudrate;
            S_X_BAND_TRNSM_S_Current_Baudrate = pBaudrate;
            // Send command
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, &pBaudrate, sizeof (pBaudrate));
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
            } else {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) {
                break;
            }

            stackEntry->timestamp = xTaskGetTickCount();
            // Change to the new baudrate
            S_X_BAND_TRNSM_Init_Usart (BaudRateArray[pBaudrate]);
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (sizeof (retStat) == RxDataLenght) {
                    // Update the state
                    stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    if ((retStat == S_X_BAND_TRNSM_PARAMS_OK) || (retStat == S_X_BAND_TRNSM_PARAMS_PARAMS_ERR)) {
                        if (retStat == S_X_BAND_TRNSM_PARAMS_OK) {
                            S_X_BAND_TRNSM_S_Current_Baudrate = pBaudrate;
                        }
                        break;
                    }
                } else {
                    // Go back to the previous baud rate
                    S_X_BAND_TRNSM_S_Current_Baudrate = Current_Baudrate_Temp;
                    S_X_BAND_TRNSM_Init_Usart (S_X_BAND_TRNSM_GetBaudrate());
                }
            } else {
                if (S_X_BAND_STACK_RETR_COND(retStat)){
                    retStat = 0x00;

                    if( stackEntry->retries <= 1 )  // on last try to get results change the baudrate back to normal
                    {
                        // Go back to the previous baud rate
                        S_X_BAND_TRNSM_S_Current_Baudrate = Current_Baudrate_Temp;
                        S_X_BAND_TRNSM_Init_Usart (S_X_BAND_TRNSM_GetBaudrate());
                    }
                }
            }

            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/**
 * @brief Lists all available files in the SD card
 * @param[input]      stackEntry - current stack entry
 *
 * @return            retStat - a value from enumeration X_BAND_TRNSM_Dir_enum
 */
static uint8_t S_X_BAND_TRNSM_CMD_Dir (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLenght;
    S_X_BAND_TRNSM_FileList_struct *DirData = (S_X_BAND_TRNSM_FileList_struct *)stackEntry->ESTTC_data;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, 0, 0);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) {
                break;
            }
            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLenght >= 4) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if (retStat == S_X_BAND_TRNSM_DIR_OK || retStat == S_X_BAND_TRNSM_DIR_NO_FILES) {
                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        // Copy the data
                        if (retStat == S_X_BAND_TRNSM_DIR_OK) {
                            DirData->DirNextAvailable = S_X_BAND_TRNSM_Result_Rx_Buffer[1];
                            DirData->NumberFiles = (S_X_BAND_TRNSM_Result_Rx_Buffer[3] << 8) + S_X_BAND_TRNSM_Result_Rx_Buffer[2];
                                memcpy (&stackEntry->ESTTC_data[sizeof (DirData->DirNextAvailable) + sizeof (DirData->NumberFiles)], &S_X_BAND_TRNSM_Result_Rx_Buffer[4], RxDataLenght - 4);
                                stackEntry->ESTTC_data_size = RxDataLenght - 1;
                        } else {
                            DirData->DirNextAvailable = DirData->NumberFiles = 0;
                        }
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) {
                    retStat = 0x00;
                }
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/**
 * @brief Lists all available files in the SD card
 * @param[input]      stackEntry - current stack entry
 *
 * @return            retStat - a value from enumeration X_BAND_TRNSM_Dir_enum
 */
static uint8_t S_X_BAND_TRNSM_CMD_Dir_Extended (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    S_X_BAND_TRNSM_FileList_struct DirData;
    S_X_BAND_TRNSM_FileInfo_struct FileName;
    static uint16_t S_X_BAND_TRNSM_CMD_Dir_i, S_X_BAND_TRNSM_CMD_Dir_index;

    // Start the complex command sequence
    if (stackEntry->expectSlaveCommand) {
        memcpy (&XSBandStack_Slave, stackEntry, sizeof (S_X_BAND_CMD_StackEntry));
        XSBandStack_Slave.expectSlaveCommand = stackEntry->expectSlaveCommand = 0;
        S_X_BAND_TRNSM_CMD_Dir_i = S_X_BAND_TRNSM_CMD_Dir_index = 0;
        XSBandStack_Slave.parentEntry = stackEntry;

        USER_START_MULTI_BUF_SEQ(XSBandStack_Slave.pUserRespCtx);
        S_X_Band_On_Dir_List_Start();
    }

    retStat = S_X_BAND_TRNSM_CMD_Dir (&XSBandStack_Slave);

    if (retStat) {
        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
        USER_COMMIT_MULTI_BUF_SEQ(XSBandStack_Slave.pUserRespCtx);
        S_X_Band_On_Dir_List_Finished();
        return retStat;
    } else if (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
        // Check the status
        if (XSBandStack_Slave.ESTTC_data_size >= (sizeof (uint8_t) + sizeof (uint16_t))) {
            memcpy (&DirData, XSBandStack_Slave.ESTTC_data, sizeof (uint8_t) + sizeof (uint16_t));
            DirData.FileList = &XSBandStack_Slave.ESTTC_data[sizeof (uint8_t) + sizeof (uint16_t)];
        }

        XSBandStack_Slave.timestamp = xTaskGetTickCount();
        XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
        USER_APPEND_FORMATTED_BUF(XSBandStack_Slave.pUserRespCtx, "Page %d, Found files = %d \r\n", S_X_BAND_TRNSM_CMD_Dir_i, DirData.NumberFiles);
        for (uint8_t i = 0; i < DirData.NumberFiles; i++) {
            if (pdTRUE == S_X_BAND_TRNSM_FileNameParser (XSBandStack_Slave.devID, &DirData.FileList[S_X_BAND_TRNSM_CMD_Dir_index], &FileName)) {
                S_X_BAND_TRNSM_CMD_Dir_index += FileName.NameLength + 4;
                USER_APPEND_FORMATTED_BUF(XSBandStack_Slave.pUserRespCtx, "%02d Name: %s ", i, FileName.FileName);
                USER_APPEND_FORMATTED_BUF(XSBandStack_Slave.pUserRespCtx, " [Size: %lu]\r\n", (int)FileName.Size);
                S_X_Band_On_Enumerate_File(&FileName);
            } else {
                USER_APPEND_FORMATTED_BUF(XSBandStack_Slave.pUserRespCtx, " File name parser Err \r\n");
                retStat = 0x01;
                DirData.DirNextAvailable = 0;
                break;
            }
        }

        S_X_BAND_TRNSM_CMD_Dir_i++;

        // Reset the slave command
        XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_DIR_NEXT_F;
        XSBandStack_Slave.ESTTC_data_size = 0;
        S_X_BAND_TRNSM_CMD_Dir_index = 0;

        // Check for more data
        if (!DirData.DirNextAvailable) {
            USER_COMMIT_MULTI_BUF_SEQ(XSBandStack_Slave.pUserRespCtx);
            S_X_Band_On_Dir_List_Finished();

            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
        }
    }

    return retStat;
}

/**
 * @brief Lists all available files in the SD card
 * @param[input]      Identifier - ID of the used S or X band transmitter
 * @param[input]      FileListBuffer - FileList from functions X_BAND_TRNSM_CMD_Dir() and X_BAND_TRNSM_CMD_DirNext()
 * @param[output]     File - a buffer where will be written the found filename, the length of the name, and the size of the file
 *
 * @return            pdTRUE - the name of the file has been found, pdFALSE - Error
 */
static uint8_t S_X_BAND_TRNSM_FileNameParser (uint16_t Identifier, uint8_t * FileListBuffer, S_X_BAND_TRNSM_FileInfo_struct * File) {
    (void) Identifier;

    File->NameLength = strlen((char *)FileListBuffer)+1;  //Get the length of the name of the file + the Null character after it

    if( (File->NameLength > 0 ) && (File->NameLength <= SXBAND_FILE_NAME_SIZE ) )  // Verify the length
    {
        /* Get the size of the file */
        const uint32_t *Size = (uint32_t *)&FileListBuffer[File->NameLength];
        File->Size = *Size;

        (void) memset(File->FileName, 0, sizeof(File->FileName));

        // Copy the name of the file
        memcpy( File->FileName, FileListBuffer, File->NameLength);

        return pdTRUE; //OK
    }

    return pdFALSE;   //File name is NOT found
}

/**
 * @brief Delete a file from the SD card of the S-Band transmitter
 * @param[input]      stackEntry - current stack entry
 *
 * @return            retStat - a value from enumeration X_BAND_TRNSM_DellStatus_enum
 */
static uint8_t S_X_BAND_TRNSM_DelFile (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLength;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            if (stackEntry->command == S_X_BAND_TRNSM_CMD_DELL_F) {
                uint8_t *FileName = (uint8_t *)stackEntry->ESTTC_data;
                uint8_t FileNameLength = strlen ((char *)FileName) + 1;
                retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, FileName, FileNameLength);
            } else {
                retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, 0, 0);
            }

            SX_BAND_TRACE("SXBand CMD res: %d\n", retStat);

            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
                // Delete All operation with multiple files is quite slow, hence the
                // big amount of GetResult retries here
                stackEntry->retries = S_X_BAND_TRNSM_DELALL_CMD_RETRY;
                stackEntry->minDelay = IS_XBAND() ? XBAND_DEL_FILE_DELAY_MS : SBAND_DEL_FILE_DELAY_MS;
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB ((retStat != S_X_BAND_TRNSM_STAT_ACK) && (retStat != S_X_BAND_TRNSM_STAT_GET_RESULT), stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)){
                break;
            }
            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLength);

            // preserve the last status to report later
            stackEntry->response = retStat;

            SX_BAND_TRACE("Del file GetResult res: %d\n", retStat);

            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLength == sizeof (retStat)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];

                    // preserve the last status to report later
                    stackEntry->response = retStat;

                    // If the status is "OK"
                    if ((retStat == S_X_BAND_TRNSM_DELL_OK) || (retStat == S_X_BAND_TRNSM_DELL_NOT_FOUND)) {
                        SX_BAND_TRACE("Del file GetResult finished with res: %d\n", retStat);

                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) {
                    retStat = 0x00;
                }
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/**
 * @brief Create a file in the SD card of the S-Band transmitter
 * @param[input]      stackEntry: current stack entry
 *
 * @return            retStat: a value from enumeration X_BAND_TRNSM_CrateStatus_enum
*/
static uint8_t S_X_BAND_TRNSM_CreateFile (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLenght;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            if (!stackEntry->fileSize) {
                retStat = 0x01;
                break;
            }
            // Should insert FileName + FileSize like that
            memcpy (&(stackEntry->ESTTC_data[stackEntry->ESTTC_data_size]), &stackEntry->fileSize, sizeof (stackEntry->fileSize));
            stackEntry->ESTTC_data_size += sizeof (stackEntry->fileSize);
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, stackEntry->ESTTC_data, stackEntry->ESTTC_data_size);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) {
                break;
            }

            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLenght == sizeof (retStat) + sizeof (uint32_t)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if ((retStat == S_X_BAND_TRNSM_CREATE_OK) || (retStat == S_X_BAND_TRNSM_CREATE_ERR)) {
                        // Return data
                        if (retStat == S_X_BAND_TRNSM_CREATE_OK) {
                            stackEntry->fileHandler = *((uint32_t *)&S_X_BAND_TRNSM_Result_Rx_Buffer[1]);
                        }
                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) retStat = 0x00;
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/**
 * @brief Create a file in the SD card of the S-Band transmitter
 * @param[input]      stackEntry - current stack entry
 *
 * @return            retStat - a value from enumeration X_BAND_TRNSM_OpenStatus_enum
 */
static uint8_t S_X_BAND_TRNSM_OpenFile (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLenght;
    uint8_t *FileName = (uint8_t *)stackEntry->ESTTC_data;
    uint8_t FileNameLength = strlen ((char *)FileName) + 1;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            // Should insert FileName + FileSize like that
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, FileName, FileNameLength);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();

                SX_BAND_TRACE("OpenFile ACK rcvd!\n");
            } else {
                // Failed to send the command
                SX_BAND_TRACE("=> OpenFile NACK!\n");
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)){
                break;
            }
            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);

            SX_BAND_TRACE("OpenFile GetResult: %d\n", retStat);

            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLenght == sizeof(retStat) + sizeof(uint32_t) + sizeof(uint32_t)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if ((retStat == S_X_BAND_TRNSM_OPEN_OK) || (retStat == S_X_BAND_TRNSM_OPEN_ERR)) {
                        // Return data
                        if (retStat == S_X_BAND_TRNSM_OPEN_OK) {
                            stackEntry->fileHandler = *((uint32_t *)&S_X_BAND_TRNSM_Result_Rx_Buffer[1]);
                            stackEntry->fileSize = *((uint32_t *)&S_X_BAND_TRNSM_Result_Rx_Buffer[5]);
                            SX_BAND_TRACE("File info [hnd = 0x%04x, size = %ul\n");
                        }
                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        break;
                    }
                } else {
                    // Wrong answer
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) retStat = 0x00;
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Transmit a file from the SD card of the S-Band transmitter trough the radio
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            retStat - a value from enumeration X_BAND_TRNSM_SendStatus_enum
* @note              none
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_SendFile (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLenght;
    uint8_t *FileName = (uint8_t *)stackEntry->ESTTC_data;
    uint8_t FileNameLength = strlen ((char *)FileName) + 1;
    static timer_handle_t profile_timer;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
            SX_BAND_TRACE("sendfile failed\r\n");
            timer_stop(&profile_timer);
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            // Should insert FileName + FileSize like that
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, FileName, FileNameLength);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
                timer_start(&profile_timer);
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) break;
            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLenght == sizeof(retStat)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];

                    SX_BAND_TRACE("sendfile: status = %d\r\n", retStat);

                    // If the status is "OK"
                    if (retStat == S_X_BAND_TRNSM_SEND_OK) {
                        // Update the state
                        SX_BAND_TRACE("sendfile finished successfully (%lu ms)\r\n", timer_get_elapsed_time(&profile_timer));
                        timer_stop(&profile_timer);
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) retStat = 0x00;
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Switch the S-Band to transmit mode (Attention: High power consumption)
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            retStat - a value from enumeration X_BAND_TRNSM_ChangeMode_enum
* @note              none
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_StartTxMode (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLenght;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            // Should insert FileName + FileSize like that
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, 0, 0);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) break;
            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLenght == sizeof(retStat)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if (retStat == S_X_BAND_TRNSM_CHANG_MODE_OK) {
                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) retStat = 0x00;
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Switch the S-Band to standby mode (Low power consumption)
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            retStat - a value from enumeration X_BAND_TRNSM_ChangeMode_enum
* @note              none
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_StartLoadMode (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLenght;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            // Should insert FileName + FileSize like that
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, 0, 0);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) {
                break;
            }
            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLenght == sizeof(retStat)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if (retStat == S_X_BAND_TRNSM_CHANG_MODE_OK) {
                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) {
                    retStat = 0x00;
                }
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Change firmware using a file in the SD card of the S-Band transmitter
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            retStat - a value from enumeration X_BAND_TRNSM_FW_update_enum
* @note              none
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_FW_Update (S_X_BAND_CMD_StackEntry *stackEntry) {
    typedef enum X_BAND_TRNSM_FW_Update_State_t {
        S_X_BAND_TRNSM_FW_Update_State_DIR = 0x00,
        S_X_BAND_TRNSM_FW_Update_State_REPORT,
        S_X_BAND_TRNSM_FW_Update_State_FWUPD,
        S_X_BAND_TRNSM_FW_Update_State_REPORT2,
        S_X_BAND_TRNSM_FW_Update_State_DELAY
    } S_X_BAND_TRNSM_FW_Update_State_t;

    uint8_t retStat = 0x00;
    static S_X_BAND_TRNSM_FW_Update_State_t S_X_BAND_TRNSM_FW_Update_State;
    static X_BAND_TRNSM_GET_FullReport_struct FullReportData_Temp[2];
    static S_BAND_TRNSM_GET_SimpleReport_struct SimpleReportData_Temp[2];

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Start the complex command sequence
    if (stackEntry->expectSlaveCommand) {
        memset (FullReportData_Temp, 0x00, sizeof (FullReportData_Temp));
        memcpy (&XSBandStack_Slave, stackEntry, sizeof (S_X_BAND_CMD_StackEntry));
        XSBandStack_Slave.expectSlaveCommand = stackEntry->expectSlaveCommand = 0;
        XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_DIR_F;
        XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
        S_X_BAND_TRNSM_FW_Update_State = S_X_BAND_TRNSM_FW_Update_State_DIR;
        XSBandStack_Slave.parentEntry = stackEntry;
    }
    // Check the global state of the complex command
    switch (S_X_BAND_TRNSM_FW_Update_State) {
        case S_X_BAND_TRNSM_FW_Update_State_DIR:
            retStat = S_X_BAND_TRNSM_CMD_Dir (&XSBandStack_Slave);
            if (!retStat && XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
                XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_GET;
                if (IS_XBAND()) {
                    XSBandStack_Slave.type = X_BAND_TRNSM_GET_TYPE_FULL_REPORT;
                } else {
                    XSBandStack_Slave.type = S_X_BAND_TRNSM_GET_TYPE_SIMPLE_REPORT;
                }
                XSBandStack_Slave.retries = S_X_BAND_TRNSM_CMD_RETRY;
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                S_X_BAND_TRNSM_FW_Update_State = S_X_BAND_TRNSM_FW_Update_State_REPORT;
            }
            break;
        case S_X_BAND_TRNSM_FW_Update_State_REPORT:
            retStat = S_X_BAND_TRNSM_CMD_GET_Param (&XSBandStack_Slave);
            if ((!retStat) && (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED)) {
                XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_UPDATE_FW;
                XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
                XSBandStack_Slave.retries = S_X_BAND_TRNSM_CMD_RETRY;
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                S_X_BAND_TRNSM_FW_Update_State = S_X_BAND_TRNSM_FW_Update_State_FWUPD;
                if (IS_XBAND()) {
                    memcpy (&FullReportData_Temp[0], XSBandStack_Slave.ESTTC_data, XSBandStack_Slave.ESTTC_data_size);
                } else {
                    memcpy (&SimpleReportData_Temp[0], XSBandStack_Slave.ESTTC_data, XSBandStack_Slave.ESTTC_data_size);
                }
            }
            break;
        case S_X_BAND_TRNSM_FW_Update_State_FWUPD:
            retStat = S_X_BAND_TRNSM_SendCMD (XSBandStack_Slave.devID, S_X_BAND_TRNSM_CMD_UPDATE_FW, S_X_BAND_TRNSM_NULL_TYPE, (uint8_t *)((char *)stackEntry->ESTTC_data), (uint16_t)(strlen ((char *)stackEntry->ESTTC_data) + 1));
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                XSBandStack_Slave.timestamp = stackEntry->timestamp = xTaskGetTickCount();
                XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_GET;
                if (IS_XBAND()) {
                    XSBandStack_Slave.type = X_BAND_TRNSM_GET_TYPE_FULL_REPORT;
                } else {
                    XSBandStack_Slave.type = S_X_BAND_TRNSM_GET_TYPE_SIMPLE_REPORT;
                }
                XSBandStack_Slave.retries = S_X_BAND_TRNSM_CMD_RETRY;
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                S_X_BAND_TRNSM_FW_Update_State = S_X_BAND_TRNSM_FW_Update_State_REPORT2;
                retStat = 0x00;
            } else {
                // Failed to send the command
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                    return S_X_BAND_TRNSM_PARAMS_COMM_ERR;
                }
                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, &XSBandStack_Slave);
            }
            break;
        case S_X_BAND_TRNSM_FW_Update_State_REPORT2:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) break;
            stackEntry->timestamp = xTaskGetTickCount();
            // Do da dew
            retStat = S_X_BAND_TRNSM_CMD_GET_Param (&XSBandStack_Slave);
            if (!retStat && XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                S_X_BAND_TRNSM_FW_Update_State = S_X_BAND_TRNSM_FW_Update_State_DELAY;
                XSBandStack_Slave.timestamp = xTaskGetTickCount();
                XSBandStack_Slave.minDelay = 500;
                if (IS_XBAND()) {
                    memcpy (&FullReportData_Temp[1], XSBandStack_Slave.ESTTC_data, XSBandStack_Slave.ESTTC_data_size);
                    // Check the FW version
                    if (FullReportData_Temp[0].FW_Version != FullReportData_Temp[1].FW_Version) {
                        return S_X_BAND_TRNSM_FW_UPDATE_OK;
                    } else {
                        return S_X_BAND_TRNSM_FW_UPDATE_UPDATE_FAILD;
                    }
                } else {
                    memcpy (&SimpleReportData_Temp[1], XSBandStack_Slave.ESTTC_data, XSBandStack_Slave.ESTTC_data_size);
                    // Check the FW version
                    if (SimpleReportData_Temp[0].FW_Version != SimpleReportData_Temp[1].FW_Version) {
                        return S_X_BAND_TRNSM_FW_UPDATE_OK;
                    } else {
                        return S_X_BAND_TRNSM_FW_UPDATE_UPDATE_FAILD;
                    }
                }
            }
            break;
        case S_X_BAND_TRNSM_FW_Update_State_DELAY:
            // Check whether the protocol delay has passed
            if (XSBandStack_Slave.minDelay > (xTaskGetTickCount() - XSBandStack_Slave.timestamp)) {
                break;
            }

            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
            return 0x00;
    }
    // Retry on error
    if ((0x00 != retStat) || !XSBandStack_Slave.retries) {
        DECR_IF_NONZERO(stackEntry->retries);
        memset (FullReportData_Temp, 0x00, sizeof (FullReportData_Temp));
        memset (SimpleReportData_Temp, 0x00, sizeof (SimpleReportData_Temp));
        memcpy (&XSBandStack_Slave, stackEntry, sizeof (S_X_BAND_CMD_StackEntry));
        XSBandStack_Slave.retries = S_X_BAND_TRNSM_CMD_RETRY;
        XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_DIR_F;
        XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
        S_X_BAND_TRNSM_FW_Update_State = S_X_BAND_TRNSM_FW_Update_State_DIR;
        XSBandStack_Slave.parentEntry = stackEntry;
        return 0x00;
    } else if (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
        if (S_X_BAND_TRNSM_FW_Update_State++ == S_X_BAND_TRNSM_FW_Update_State_DELAY) {
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
            return retStat;
        }
        XSBandStack_Slave.retries = S_X_BAND_TRNSM_CMD_RETRY;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Prepare S-Band transmitter to be turned off using the power supply
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            retStat - a value from enumeration X_BAND_TRNSM_ChangeMode_enum
* @note              none
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_ShutDownMode (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            stackEntry->timestamp = xTaskGetTickCount();
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, 0, 0);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        default:
            break;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Copy a file from the SD card of the X-Band Transmitter to the SD card of the OBC
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            uint8_t:
*                      + X_BAND_TRNSM_STAT_WRONG_PARAM - file not found
*                      + X_BAND_TRNSM_DellStatus_enum  - delete Error
* @note              if such a file is already existing it will be overwritten
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_DownloadFileFromSBandTrnsm (S_X_BAND_CMD_StackEntry *stackEntry) {
    typedef enum X_BAND_TRNSM_DownloadFromXSBand_State_t {
        S_X_BAND_TRNSM_DownloadFromXSBand_State_OPENFILE = 0x00,
        S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE,
        S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE_GETRESULT
    } S_X_BAND_TRNSM_DownloadFromXSBand_State_t;

    volatile uint8_t retStat = 0x00;
    uint16_t RxDataLenght;
    S_X_BAND_TRNSM_ReadFile_struct FileDataBuffer, FileDataBufferTmp;
    static S_X_BAND_TRNSM_DownloadFromXSBand_State_t S_X_BAND_TRNSM_DownloadFromXSBand_State;
    static FIL S_X_BAND_TRNSM_DownloadFromXSBand_file_descr;
    static uint32_t S_X_BAND_TRNSM_DownloadFromXSBand_PacketNumber, S_X_BAND_TRNSM_DownloadFromXSBand_FPos;
    static timer_handle_t profile_timer;
    static uint32_t rx_len;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        SX_BAND_TRACE("X_BAND_TRNSM_DownloadFileFromSBandTrnsm() FINISHED ERR, time =  %d\r\n", (int)xTaskGetTickCount());
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
            SX_BAND_TRACE("ERROR\n");
        }
        return retStat;
    }
    // Start the complex command sequence
    if (stackEntry->expectSlaveCommand) {
        SX_BAND_TRACE("X_BAND_TRNSM_DownloadFileFromSBandTrnsm() START time =  %d\r\n", (int)xTaskGetTickCount());
        memcpy (&XSBandStack_Slave, stackEntry, sizeof (S_X_BAND_CMD_StackEntry));
        memset (&FileDataBuffer, 0x00, sizeof (FileDataBuffer));
        XSBandStack_Slave.expectSlaveCommand = stackEntry->expectSlaveCommand = 0;
        XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_OPEN_F;
        XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
        XSBandStack_Slave.fileHandler = -1;
        S_X_BAND_TRNSM_DownloadFromXSBand_State = S_X_BAND_TRNSM_DownloadFromXSBand_State_OPENFILE;
        // timing is very critical here depending on SXBand type
        // (using lower times for SBand may lead to every second command request failing with BUSY status,
        //  while using higher times for XBand leads to NCE (No Command For Execution) error which means the
        // request timed out before getting the results
        XSBandStack_Slave.minDelay = IS_XBAND() ? XBAND_OPEN_FILE_DELAY_MS : SBAND_OPEN_FILE_DELAY_MS;
        XSBandStack_Slave.parentEntry = stackEntry;
        SX_BAND_TRACE("Download START\n");
    }

    SX_BAND_TRACE("Download State = %d (retries: %d)\n", S_X_BAND_TRNSM_DownloadFromXSBand_State, stackEntry->retries);

    // Check the global state of the complex command
    switch (S_X_BAND_TRNSM_DownloadFromXSBand_State) {
        case S_X_BAND_TRNSM_DownloadFromXSBand_State_OPENFILE:
            retStat = S_X_BAND_TRNSM_OpenFile (&XSBandStack_Slave);
            if ((!retStat) && (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED)) {
                if ((XSBandStack_Slave.fileHandler != -1) || (XSBandStack_Slave.fileSize > 0U)) {
                    FRESULT fr = SdMngr_f_open (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr, (char *)stackEntry->ESTTC_data, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
                    retStat = fr;
                    if (fr != FR_OK) {
                        // on disk error - try to reinitialise the SD card
                        if ((fr == FR_DISK_ERR) || (fr == FR_LOCKED)) {
                            SX_BAND_TRACE("X_BAND_TRNSM_DownloadFileFromSBandTrnsm() SD card. ERR = %d\r\n", fr);
                        }
                        // Close the file - regardless if the copy procedure is successful or not
                        SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                    } else {
                        timer_start(&profile_timer);
                        rx_len = 0;

                        XSBandStack_Slave.retries = stackEntry->retries;
                        XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                        S_X_BAND_TRNSM_DownloadFromXSBand_State = S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE;
                        S_X_BAND_TRNSM_DownloadFromXSBand_PacketNumber = S_X_BAND_TRNSM_DownloadFromXSBand_FPos = 0;
                    }
                } else {
                    retStat = 0xFA;
                }
            }
            break;
        case S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE:
            if (S_X_BAND_TRNSM_DownloadFromXSBand_FPos >= XSBandStack_Slave.fileSize) {
                if (S_X_BAND_TRNSM_DownloadFromXSBand_FPos == XSBandStack_Slave.fileSize) {
                    retStat = 0x00;
                } else {
                    retStat = 0x01;
                }
                SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                S_X_BAND_TRNSM_DownloadFromXSBand_State = S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE_GETRESULT;
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
            } else {
                retStat = S_X_BAND_TRNSM_SendCMD (XSBandStack_Slave.devID, S_X_BAND_TRNSM_CMD_READ_F, S_X_BAND_TRNSM_NULL_TYPE, (uint8_t *)&XSBandStack_Slave.fileHandler, sizeof (XSBandStack_Slave.fileHandler));
                if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                    XSBandStack_Slave.minDelay = 1;
                    XSBandStack_Slave.timestamp = stackEntry->timestamp = xTaskGetTickCount();
                    XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_READ_F;
                    XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
                    XSBandStack_Slave.retries = stackEntry->retries;
                    XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                    S_X_BAND_TRNSM_DownloadFromXSBand_State = S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE_GETRESULT;
                    retStat = 0x00;
                } else {
                    // Failed to send the command
                    if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                        stackEntry->retries = 0;
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        return S_X_BAND_TRNSM_PARAMS_COMM_ERR;
                    }
                    S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, &XSBandStack_Slave);
                }
            }
            break;
        case S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE_GETRESULT:
            // Check whether the protocol delay has passed
            if (XSBandStack_Slave.minDelay > (xTaskGetTickCount() - XSBandStack_Slave.timestamp)) {
                break;
            }
            XSBandStack_Slave.timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (XSBandStack_Slave.devID, S_X_BAND_TRNSM_CMD_READ_F, S_X_BAND_TRNSM_NULL_TYPE, &FileDataBuffer.Status, &RxDataLenght);
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                retStat = S_X_BAND_TRNSM_SEND_CARD_ERR;
                // Verify the answer
                if (RxDataLenght > 0) {
                    if (FileDataBuffer.PacketNumber == S_X_BAND_TRNSM_DownloadFromXSBand_PacketNumber) {
                        // Get the status of the request
                        retStat = FileDataBuffer.Status;
                        // If the status is "OK"
                        if (!retStat) {
                            FRESULT fr = SdMngr_f_lseek (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr, S_X_BAND_TRNSM_DownloadFromXSBand_FPos);
                            if (fr == FR_OK) {
                                uint32_t NumberReadBytes;

                                // Read a piece of file in the OBC
                                fr = SdMngr_f_write (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr, &FileDataBuffer.Data, FileDataBuffer.Length, (UINT*)&NumberReadBytes);
                                if ((fr != FR_OK) || (FileDataBuffer.Length != NumberReadBytes)) {
                                    // Wrong answer
                                    SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                                    fr = SdMngr_f_open (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr, (char *)stackEntry->ESTTC_data, FA_READ | FA_WRITE | FA_OPEN_EXISTING);
                                    if (fr != FR_OK) {
                                        retStat = S_X_BAND_TRNSM_SEND_CARD_ERR;
                                        SX_BAND_TRACE("\r\n READ_F CMD f_open() error = %d (retry No %d)", fr, stackEntry->retries);
                                    } else {
                                        retStat = 0x00;
                                    }
                                    DECR_IF_NONZERO(stackEntry->retries);
                                } else {
                                    rx_len += FileDataBuffer.Length;

                                    float elapsed_time_sec = timer_get_elapsed_time(&profile_timer) / 1000.;
                                    float download_rate_bytes_per_sec = rx_len / elapsed_time_sec;
                                    float eta_min = ((XSBandStack_Slave.fileSize - rx_len) / download_rate_bytes_per_sec) / 60.;

                                    SX_BAND_TRACE("[%ld sec @ %.2f Bps] sxband-download: %ld/%ld bytes transferred [%.2f%%] (ETA: %.2f min)\r\n", (uint32_t) elapsed_time_sec, download_rate_bytes_per_sec, rx_len, XSBandStack_Slave.fileSize, (rx_len * 100.) / XSBandStack_Slave.fileSize, eta_min);

                                    S_X_BAND_TRNSM_DownloadFromXSBand_PacketNumber++;
                                    S_X_BAND_TRNSM_DownloadFromXSBand_FPos += FileDataBuffer.Length;
                                    // Update the state
                                    S_X_BAND_TRNSM_DownloadFromXSBand_State = S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE;
                                    XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                                    XSBandStack_Slave.retries = stackEntry->retries;
                                    memcpy (&FileDataBufferTmp, &FileDataBuffer, sizeof (FileDataBuffer));

                                }
                            } else {
                                SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                                fr = SdMngr_f_open (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr, (char *)stackEntry->ESTTC_data, FA_READ | FA_WRITE | FA_OPEN_EXISTING);
                                if (fr != FR_OK) {
                                    retStat = S_X_BAND_TRNSM_SEND_CARD_ERR;
                                    SX_BAND_TRACE("\r\n READ_F CMD f_open() error = %d (retry No %d)", fr, stackEntry->retries);
                                } else {
                                    retStat = 0x00;
                                }
                            }
                        } else {
                            SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                            retStat = 0xF3;
                            // Wrong answer
                        }
                    } else {
                        SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                        retStat = 0xF4;
                        // Wrong answer
                    }
                } else {
                    SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                    retStat = 0xF5;
                    // Wrong answer
                }
            } else {
                if (S_X_BAND_STACK_RETR_COND(retStat)) retStat = 0x00;
                else {
                    SdMngr_f_close (&S_X_BAND_TRNSM_DownloadFromXSBand_file_descr);
                    retStat = 0xF6;
                }
                // Failed to send the command
            }
            break;
    }
    // Retry on error
    if (retStat || (0U == XSBandStack_Slave.retries)) {
        timer_stop(&profile_timer);
        SX_BAND_TRACE("\r\n <DOWNLOAD> Error on state = %d", S_X_BAND_TRNSM_DownloadFromXSBand_State);
        SX_BAND_TRACE("\r\n <DOWNLOAD> Retrying on retStat = %d (retry No %d) (local retry %d)", retStat, stackEntry->retries - 1, XSBandStack_Slave.retries);
        DECR_IF_NONZERO(stackEntry->retries);
        memcpy (&XSBandStack_Slave, stackEntry, sizeof (S_X_BAND_CMD_StackEntry));
        XSBandStack_Slave.retries = stackEntry->retries;
        XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_OPEN_F;
        XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
        XSBandStack_Slave.fileHandler = -1;
        S_X_BAND_TRNSM_DownloadFromXSBand_State = S_X_BAND_TRNSM_DownloadFromXSBand_State_OPENFILE;
        XSBandStack_Slave.parentEntry = stackEntry;
        return 0x00;
    } else if (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
        if (S_X_BAND_TRNSM_DownloadFromXSBand_State == S_X_BAND_TRNSM_DownloadFromXSBand_State_READFILE_GETRESULT) {
            SX_BAND_TRACE("X_BAND_TRNSM_DownloadFileFromSBandTrnsm() FINISHED OK, time =  %d\r\n", (int)xTaskGetTickCount());
            timer_stop(&profile_timer);
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
            SX_BAND_TRACE("Download SUCCESS\n");
            return retStat;
        }
        XSBandStack_Slave.retries = stackEntry->retries;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Copy a file from the SD card of the OBC to the SD card of the S-Band Transmitter
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            uint8_t:
*                      + X_BAND_TRNSM_STAT_WRONG_PARAM - file not found
*                      + X_BAND_TRNSM_DellStatus_enum  - delete Error
* @note              if such a file is already existing it will be overwritten
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_UploadFileToSBandTrnsm (S_X_BAND_CMD_StackEntry *stackEntry) {
    typedef enum S_X_BAND_TRNSM_UploadToXSBand_State_t {
        S_X_BAND_TRNSM_UploadToXSBand_State_OPEN_FILE = 0x00,
        S_X_BAND_TRNSM_UploadToXSBand_State_DEL_FILE,
        S_X_BAND_TRNSM_UploadToXSBand_State_CREATEFILE,
        S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE,
        S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE_GETRESULT
    } S_X_BAND_TRNSM_UploadToXSBand_State_t;

    uint8_t retStat = 0x00;
    uint16_t RxDataLength;
    uint32_t S_X_BAND_TRNSM_UploadToXSBand_ReadLen;
    static uint32_t tx_len = 0U;
    static timer_handle_t profile_timer;
    static timer_handle_t cmd_timer;
    static crypto_stream_hnd_t crypto_hnd;
    crypto_api_res_t crypto_res;
    static S_X_BAND_TRNSM_UploadToXSBand_State_t S_X_BAND_TRNSM_UploadToXSBand_State;
    static S_X_BAND_TRNSM_WriteFile_struct S_X_BAND_TRNSM_FileDataBuffer;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        SX_BAND_TRACE_VERBOSE("S_X_BAND_TRNSM_UploadFileToSBandTrnsm() FINISHED tick =  %d\r\n", (int)xTaskGetTickCount());
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Start the complex command sequence
    if (stackEntry->expectSlaveCommand) {
        SX_BAND_TRACE_VERBOSE("X_BAND_TRNSM_UploadFileToSBandTrnsm() START tick =  %d\r\n", (int)xTaskGetTickCount());
        memcpy (&XSBandStack_Slave, stackEntry, sizeof (S_X_BAND_CMD_StackEntry));
        XSBandStack_Slave.expectSlaveCommand = stackEntry->expectSlaveCommand = 0;
        XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_DELL_F;
        XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
        XSBandStack_Slave.fileHandler = -1;
        S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_OPEN_FILE;
        XSBandStack_Slave.parentEntry = stackEntry;
    }
    // Check the global state of the complex command
    switch (S_X_BAND_TRNSM_UploadToXSBand_State) {
        case S_X_BAND_TRNSM_UploadToXSBand_State_OPEN_FILE:
            crypto_res = crypto_stream_open_always(&crypto_hnd, (char *)stackEntry->ESTTC_data, OP_CMOX_AES_GCM_ENC);
            tx_len = 0U;
            timer_start(&profile_timer);

            if (crypto_res != CRYPTO_API_RES_OK) {
                SX_BAND_TRACE("X_BAND_TRNSM_UploadFileToSBandTrnsm() Error crypto_stream_open_always(). ERR = %d\r\n", crypto_res);

                retStat = 0x01;
                break;
            }

            XSBandStack_Slave.retries = stackEntry->retries;
            S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_DEL_FILE;
            XSBandStack_Slave.minDelay = IS_XBAND() ? XBAND_DEL_FILE_DELAY_MS : SBAND_DEL_FILE_DELAY_MS;

        break;

        case S_X_BAND_TRNSM_UploadToXSBand_State_DEL_FILE:
            retStat = S_X_BAND_TRNSM_DelFile (&XSBandStack_Slave);
            if (((0x00 == retStat) || (retStat == S_X_BAND_TRNSM_DELL_NOT_FOUND)) &&
                (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED)) {
                retStat = 0x00;
                XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_CREATE_F;
                XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
                XSBandStack_Slave.retries = stackEntry->retries;
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_CREATEFILE;
            } else if (retStat) {
                SX_BAND_TRACE("\r\n S_X_BAND_TRNSM_UploadToXSBand_State_DEL_FILE ERROR = %d (retry No %d) (local retry %d)", retStat, stackEntry->retries - 1, XSBandStack_Slave.retries);
            }
        break;

        case S_X_BAND_TRNSM_UploadToXSBand_State_CREATEFILE:
            crypto_res = crypto_stream_get_size(&crypto_hnd, &XSBandStack_Slave.fileSize);

            if (crypto_res != CRYPTO_API_RES_OK)
            {
                retStat = 0x03;
                break;
            }

            retStat = S_X_BAND_TRNSM_CreateFile (&XSBandStack_Slave);
            if ((0x00 == retStat) && (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED)) {
                XSBandStack_Slave.retries = stackEntry->retries;
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE;
                memset (&S_X_BAND_TRNSM_FileDataBuffer, 0x00, sizeof (S_X_BAND_TRNSM_FileDataBuffer));
                S_X_BAND_TRNSM_FileDataBuffer.FileHandler = XSBandStack_Slave.fileHandler;

                SX_BAND_TRACE_VERBOSE("sxband-upload: SXBand file handle: %ld\r\n", S_X_BAND_TRNSM_FileDataBuffer.FileHandler);

            } else if ((0x00 != retStat) && (XSBandStack_Slave.fileHandler == -1)) {
                SX_BAND_TRACE("\r\n S_X_BAND_TRNSM_UploadToXSBand_State_CREATEFILE ERROR = %d (retry No %d) (local retry %d)", retStat, stackEntry->retries - 1, XSBandStack_Slave.retries);
                retStat = 0x03;
            }
            break;

        case S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE:
            S_X_BAND_TRNSM_FileDataBuffer.Size = S_X_BAND_TRNSM_READ_FILE_CHUNCK_SIZE;

            // Set the cursor to the end of the file
            crypto_res = crypto_stream_read(&crypto_hnd, S_X_BAND_TRNSM_FileDataBuffer.Data, S_X_BAND_TRNSM_FileDataBuffer.Size, &S_X_BAND_TRNSM_UploadToXSBand_ReadLen);

            if ((S_X_BAND_TRNSM_UploadToXSBand_ReadLen > 0) && ((crypto_res == CRYPTO_API_RES_EOS) || (crypto_res == CRYPTO_API_RES_OK)))
            {
                S_X_BAND_TRNSM_FileDataBuffer.Size = S_X_BAND_TRNSM_UploadToXSBand_ReadLen;

                const uint8_t *p_write_file_hdr_start = (uint8_t *)&S_X_BAND_TRNSM_FileDataBuffer.Size;     // point to the first field of the header
                // size includes the header size + currently read data from the stream
                const uint16_t write_file_cmd_size = sizeof(S_X_BAND_TRNSM_FileDataBuffer.Size) +
                                                     sizeof(S_X_BAND_TRNSM_FileDataBuffer.FileHandler) +
                                                     sizeof(S_X_BAND_TRNSM_FileDataBuffer.PacketNumber) +
                                                     S_X_BAND_TRNSM_UploadToXSBand_ReadLen;

                retStat = S_X_BAND_TRNSM_SendCMD (XSBandStack_Slave.devID, S_X_BAND_TRNSM_CMD_WRITE_F, S_X_BAND_TRNSM_NULL_TYPE, p_write_file_hdr_start, (uint16_t) write_file_cmd_size);

                if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                    SX_BAND_TRACE_VERBOSE("sxband-upload: %ld bytes ACK'd @ file handle: %ld\r\n", write_file_cmd_size, S_X_BAND_TRNSM_FileDataBuffer.FileHandler);

                    XSBandStack_Slave.minDelay = 2;
                    XSBandStack_Slave.timestamp = stackEntry->timestamp = xTaskGetTickCount();
                    XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_WRITE_F;
                    XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
                    XSBandStack_Slave.retries = stackEntry->retries;
                    XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                    S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE_GETRESULT;
                    retStat = 0x00;
                } else {
                    if (retStat) {
                        SX_BAND_TRACE("\r\n WRITE_F CMD ERROR = %d (retry No %d)", retStat, stackEntry->retries);
                    }
                    // Failed to send the command
                    if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                        stackEntry->retries = 0;
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        return S_X_BAND_TRNSM_PARAMS_COMM_ERR;
                    }
                    S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, &XSBandStack_Slave);
                }

                timer_start(&cmd_timer);
            }

            if (crypto_res == CRYPTO_API_RES_EOS)
            {
                retStat = 0x00;

                S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE_GETRESULT;
                XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
            }
            break;

        case S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE_GETRESULT:
            // Check whether the protocol delay has passed
            if (XSBandStack_Slave.minDelay > (xTaskGetTickCount() - XSBandStack_Slave.timestamp)) {
                break;
            }

            XSBandStack_Slave.timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (XSBandStack_Slave.devID, S_X_BAND_TRNSM_CMD_WRITE_F, S_X_BAND_TRNSM_NULL_TYPE, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLength);

            if (cmd_timer.is_running)
            {
                SX_BAND_TRACE_VERBOSE("[WRITE-GETRES delta] => %ld\r\n", timer_get_elapsed_time(&cmd_timer));
                timer_stop(&cmd_timer);
            }

            SX_BAND_TRACE_VERBOSE("GetResult ==> retStat = %d | op_res = %d | len = %ld\r\n", retStat, S_X_BAND_TRNSM_Result_Rx_Buffer[0], RxDataLength);

            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (RxDataLength == sizeof (retStat)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if (0x00 == retStat) {
                        // On success move to the next packet
                        S_X_BAND_TRNSM_FileDataBuffer.PacketNumber++;
                        tx_len += S_X_BAND_TRNSM_FileDataBuffer.Size;

                        float elapsed_time_sec = timer_get_elapsed_time(&profile_timer) / 1000.;
                        float upload_rate_bytes_per_sec = tx_len / elapsed_time_sec;
                        float eta_min = ((XSBandStack_Slave.fileSize - tx_len) / upload_rate_bytes_per_sec) / 60.;

                        SX_BAND_TRACE("[%ld sec @ %.2f Bps] sxband-upload: %ld/%ld bytes transferred [%.2f%%] (ETA: %.2f min)\r\n", (uint32_t) elapsed_time_sec, upload_rate_bytes_per_sec, tx_len, XSBandStack_Slave.fileSize, (tx_len * 100.) / XSBandStack_Slave.fileSize, eta_min);

                        // Update the state
                        S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE;
                        XSBandStack_Slave.state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                        XSBandStack_Slave.retries = stackEntry->retries;
                    } else {
                        retStat = 0xF3;
                        // Wrong answer
                    }
                } else {
                    retStat = 0xF5;
                    // Wrong answer
                }
            } else {
                if (S_X_BAND_STACK_RETR_COND(retStat)) {
                    retStat = 0x00;
                }
                else {
                    if (retStat) {
                        SX_BAND_TRACE("\r\n WRITE_F GETRESULT LOCAL ERR = %d (retry No %d)", retStat, XSBandStack_Slave.retries);
                    }
                    retStat = 0xF6;
                }
                // Failed to send the command
            }
            if (retStat) {
                SX_BAND_TRACE("\r\n WRITE_F GETRESULT ERROR = %d (retry No %d)", retStat, stackEntry->retries);
            }
            break;
    }
    // Retry on error
    if ((0x00 != retStat) || (!XSBandStack_Slave.retries)) {
        SX_BAND_TRACE("\r\n Error on state = %d", S_X_BAND_TRNSM_UploadToXSBand_State);
        SX_BAND_TRACE("\r\n Retrying on retStat = %d (retry No %d) (local retry %d)", retStat, stackEntry->retries - 1, XSBandStack_Slave.retries);
        retStat = 0x00;
        DECR_IF_NONZERO(stackEntry->retries);
        memcpy (&XSBandStack_Slave, stackEntry, sizeof (S_X_BAND_CMD_StackEntry));
        XSBandStack_Slave.retries = stackEntry->retries;
        XSBandStack_Slave.command = S_X_BAND_TRNSM_CMD_DELL_F;
        XSBandStack_Slave.type = S_X_BAND_TRNSM_NULL_TYPE;
        XSBandStack_Slave.fileHandler = -1;
        S_X_BAND_TRNSM_UploadToXSBand_State = S_X_BAND_TRNSM_UploadToXSBand_State_OPEN_FILE;
        XSBandStack_Slave.parentEntry = stackEntry;
        timer_stop(&profile_timer);

        crypto_stream_close(&crypto_hnd);

        return retStat;
    } else if (XSBandStack_Slave.state == S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
        if (S_X_BAND_TRNSM_UploadToXSBand_State == S_X_BAND_TRNSM_UploadToXSBand_State_WRITEFILE_GETRESULT) {
            SX_BAND_TRACE("S_X_BAND_TRNSM_UploadFileToSBandTrnsm() FINISHED OK, time =  %.2f min\r\n", (timer_get_elapsed_time(&profile_timer) / 1000.) / 60.);

            // make sure the file cache is invalidated when an upload operation to SXBand finishes
            moduleCacheInfo.file_cache_valid = false;

            timer_stop(&profile_timer);
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;

            crypto_stream_close(&crypto_hnd);

            return retStat;
        }
        XSBandStack_Slave.retries = stackEntry->retries;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief A Task that serves commands through ESTTC protocol
*********************************************************************************************
* @param[input]      argument - unused, a template is followed
* @param[output]     none
* @return            none
*********************************************************************************************
*/

void S_X_BAND_Task(void * argument) {
    uint8_t i;
    bool stack_empty;

    (void) argument;

    TaskMonitor_TaskInitialized(TASK_MONITOR_S_X_BAND);

    for (;;) {
        (void) osMutexAcquire(sxband_lock_id, osWaitForever);

        TaskMonitor_IamAlive(TASK_MONITOR_S_X_BAND);

        stack_empty = true;
        // Process with the state machine
        for (i = 0; i < S_X_BAND_STACK_SIZE; ++i) {
            // Empty slot - continue
            if ((XSBandStack[i].state != S_X_BAND_TRNSM_CMD_STATE_EMPTY) && (XSBandStack[i].state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED))
            {
                stack_empty = false;
                // Processing state - process the data and induce a new state if needed
                if ((XSBandStack[i].command < S_X_BAND_TRNSM_CMD_NUMBER) &&
                    (NULL != XSBandCallbacks[XSBandStack[i].command])) {
                    XSBandTryFinish (XSBandCallbacks[XSBandStack[i].command] (&XSBandStack[i]), &XSBandStack[i]);
                }
                else
                {
                    sx_band_init_stack(&XSBandStack[i]);
                }

                break;
            }
        }

        if ((stack_empty) && (NULL != cacheUpdateThread)) {
            // signal cache update when there are no commands in the stack anymore (just in case it is pending for execution)
            (void) osThreadFlagsSet(cacheUpdateThread, UNBLOCK_CACHE_THREAD_FLAG);
        }
        (void) osMutexRelease(sxband_lock_id);

        // Check if all the stack was empty
        if (stack_empty) {
            osDelay (200);
        } else {
            osDelay (1);
        }

        vApplicationLowStackCheck(TASK_MONITOR_S_X_BAND);
    }
}

/*!
*********************************************************************************************
* @brief Request a command from ESTTC gateway
*********************************************************************************************
* @param[input]      Identifier - SXBand module identifier to send the command to
* @param[input]      Cmd - Command number that is requested to be executed
*                     - 0x01    Symbol Rate
*                     - 0x02    Tx Power
*                     - 0x03    Central Frequency
*                     - 0x04    MODCOD
*                     - 0x05    Roll-Off
*                     - 0x06    Pilot Signal On/Off
*                     - 0x07    FEC Frame size
*                     - 0x08    Pretransmission Staffing Delay
*                     - 0x09    Change All Parameters
*                     - 0x0A    Simple Report
*                     - 0x0B    Full Report
*                     - 0x0C    Change Baudrate
*                     - 0x30    TxMode
*                     - 0x31    Load Mode
*                     - 0x32    Prepare to ShutDown
*                     - 0x35    FW update
*                     - 0x40    Dir
*                     - 0x50    Delete
*                     - 0x55    Delete all
*                     - 0x60    Upload a file
*                     - 0x61    Download a file
*                     - 0x70    Send a file
* @param[input]      Type - accepts only: 'R' - Read command, 'W' - Write commands
* @param[input]      size - size of the input data if used (if pData == NULL, this parameter is ignored)
* @param[input]      pData - pointer to the input data (if not needed set to NULL. This can be settings, file name etc.)
* @param[input]      pOnCmdResponse - pointer to a user-defined callback which receives the result from the command
* @param[output]     p_cmd_eta_ms - milliseconds to wait for the command to finish
* @return            none
*********************************************************************************************
*/
void S_X_BAND_TRNSM_ESTTC_StartCmd(uint16_t Identifier, S_X_BAND_TRNSM_GW_CMD_ID_enum Cmd, uint8_t Type, uint8_t size, const uint8_t * pData, sUserResponseCtx_t *pUserRespCtx, uint32_t * const p_cmd_eta_ms)
{
    uint8_t i;

    // Check if any command is currently in progress
    // Should we add a new command to the stack ???
    // First, check whether this is attempted consecutive file commands execution
    bool is_file_cmd = ((uint8_t) Cmd >= S_X_BAND_TRNSM_GW_CMD_ID_FW_UPDATE) && ((uint8_t) Cmd <= S_X_BAND_TRNSM_GW_CMD_ID_SEND_FILES);
    bool accept_startcmd_req = true;

    (void) osMutexAcquire(sxband_lock_id, osWaitForever);

#if S_X_BAND_STACK_SAFETY
    for (i = 0; i < S_X_BAND_STACK_SIZE; ++i) {
        if (XSBandStack[i].state != S_X_BAND_TRNSM_CMD_STATE_EMPTY) {
            if (is_file_cmd && XSBandStack[i].isFileCommand) {
#ifdef S_X_BAND_STACK_DEBUG
                for (uint8_t p = 0; p < S_X_BAND_STACK_SIZE; ++p) {
                    SX_BAND_TRACE("Stack lvl [%d] - STATUS: %d RETR: %d CMD: %d !!!\r\n", p, XSBandStack[p].state, XSBandStack[p].retries, XSBandStack[p].command);
                }
                if (XSBandStack_Slave.parentEntry != NULL) {
                    SX_BAND_TRACE("Stack lvl [SLAVE] {PARENT: %d} - STATUS: %d RETR: %d CMD: %d !!!\r\n", XSBandStack_Slave.parentEntry->command, XSBandStack_Slave.state, XSBandStack_Slave.retries, XSBandStack_Slave.command);
                }
#endif
                accept_startcmd_req = false;
            } else if ((XSBandStack[i].ESTTC_request == Cmd) && (XSBandStack[i].ESTTC_request_type == Type)) {
#ifdef S_X_BAND_STACK_DEBUG
                for (uint8_t p = 0; p < S_X_BAND_STACK_SIZE; ++p) {
                    SX_BAND_TRACE("Stack lvl [%d] - STATUS: %d RETR: %d CMD: %d !!!\r\n", p, XSBandStack[p].state, XSBandStack[p].retries, XSBandStack[p].command);
                }
                if (XSBandStack_Slave.parentEntry != NULL) {
                    SX_BAND_TRACE("Stack lvl [SLAVE] {PARENT: %d} - STATUS: %d RETR: %d CMD: %d !!!\r\n", XSBandStack_Slave.parentEntry->command, XSBandStack_Slave.state, XSBandStack_Slave.retries, XSBandStack_Slave.command);
                }
#endif
                accept_startcmd_req = false;
            }
        }
    }
#endif /* S_X_BAND_STACK_SAFETY */

    if (accept_startcmd_req)
    {

        // before executing the command, attempt a one-time SXBand module type detection because
        // certain commands require different interpretation depending on the module type
        S_X_BAND_TRNSM_Detect_Band_Type(Identifier);

        // attempt to update file cache before executing the queued command
        // (performed only for TX_MODE, DOWNLOAD_FILE and SEND_FILES commands where the local cache is
        // needed to properly calculate the command timeout)
        if ((!moduleCacheInfo.file_cache_valid) &&
            ((S_X_BAND_TRNSM_GW_CMD_ID_TX_MODE == Cmd) ||
             (S_X_BAND_TRNSM_GW_CMD_ID_DOWNLOAD_FILE == Cmd) ||
             (S_X_BAND_TRNSM_GW_CMD_ID_SEND_FILES == Cmd)))
        {
            cacheUpdateThread = osThreadGetId();

            // let the main driver task perform the cache update...
            (void) osMutexRelease(sxband_lock_id);

            (void) osThreadFlagsWait(UNBLOCK_CACHE_THREAD_FLAG,
                                     osFlagsWaitAll,
                                     TX_CMD_TIMEOUT_MS);

            S_X_Band_Update_Module_Cache(Identifier);

            // ...and lock again to add the current command to the command stack
            (void) osMutexAcquire(sxband_lock_id, osWaitForever);
        }

        // Try to add
        for (i = 0; i < S_X_BAND_STACK_SIZE; ++i) {
            if (XSBandStack[i].state == S_X_BAND_TRNSM_CMD_STATE_EMPTY) {
                sx_band_init_stack(&XSBandStack[i]);
                XSBandStack[i].devID = Identifier;
                XSBandStack[i].ESTTC_request = Cmd;
                XSBandStack[i].isFileCommand = is_file_cmd;
                XSBandStack[i].ESTTC_request_type = Type;
                XSBandStack[i].ESTTC_data_size = size;

                if ((XSBandStack[i].ESTTC_data_size > 0) && (NULL != pData)) {
                    memcpy (XSBandStack[i].ESTTC_data, pData, XSBandStack[i].ESTTC_data_size);
                }

                XSBandStack[i].retries = S_X_BAND_TRNSM_CMD_RETRY;
                XSBandStack[i].timestamp = 0;
                XSBandStack[i].minDelay = S_X_BAND_STACK_DELAY;
                XSBandStack[i].pUserRespCtx = pUserRespCtx;

                if (CMD_EXTRACT_RESULT_UNSUP_CMD == XSBandExtractCommandAndType (&XSBandStack[i])) {
                    USER_COMMIT_FORMATTED_BUF(XSBandStack[i].pUserRespCtx, "Error - Command '0x%02x' not supported by module\r\n", Cmd);
                    memset (&XSBandStack[i], 0x00, sizeof (XSBandStack[i]));
                }
                else
                {
                    if (NULL != p_cmd_eta_ms)
                    {
                        *p_cmd_eta_ms = S_X_Band_Get_Cmd_Timeout(Identifier, Cmd, Type, size, pData);
                    }

                    XSBandStack[i].state = S_X_BAND_TRNSM_CMD_STATE_CMD;
                }

                break;
            }
        }

        if (i == S_X_BAND_STACK_SIZE) {
            SX_BAND_TRACE("Error - Cannot add command to the stack !!!\r\n");
    #ifdef S_X_BAND_STACK_DEBUG
            for (i = 0; i < S_X_BAND_STACK_SIZE; ++i) {
                SX_BAND_TRACE("Stack lvl [%d] - STATUS: %d RETR: %d CMD: %d !!!\r\n", i, XSBandStack[i].state, XSBandStack[i].retries, XSBandStack[i].command);
            }
            if (XSBandStack_Slave.parentEntry != NULL) {
                SX_BAND_TRACE("Stack lvl [SLAVE] {PARENT: %d} - STATUS: %d RETR: %d CMD: %d !!!\r\n", XSBandStack_Slave.parentEntry->command, XSBandStack_Slave.state, XSBandStack_Slave.retries, XSBandStack_Slave.command);
            }
    #endif
        }
    }
    else
    {
        USER_COMMIT_FORMATTED_BUF(pUserRespCtx, "Error - Cannot execute several commands of the same type simultaneously!\r\n");
    }

    (void) osMutexRelease(sxband_lock_id);
}

/** @brief Called when the Dir List internal cache update command has finished
 *
 *  @param[in] pUserCtx User context data provided initially when the DirList command was queued for execution
 */
static void S_X_Band_On_CacheUpdateReady(void * const pUserCtx)
{
    if (NULL != cacheUpdateThread)
    {
        (void) osThreadFlagsSet(cacheUpdateThread, UNBLOCK_CACHE_THREAD_FLAG);
    }
}

/** @brief The function performs a module parameters update and a dir list command to update the local file index.
 *
 *  @param[in] Identifier id of the SXBand module
 */
static void S_X_Band_Update_Module_Cache(uint16_t Identifier)
{
    if (!moduleCacheInfo.in_progress)
    {
        moduleCacheInfo.in_progress = true;

        if (!moduleCacheInfo.settings_cache_valid)
        {
            uint8_t all_params[13];

            moduleCacheInfo.modcod = 0;
            moduleCacheInfo.sym_rate = 0;
            moduleCacheInfo.pretx_delay_ms = 0;

            // try to obtain the Symbol rate, ModCod and other settings which may be needed to properly estimate the ground station
            // downlink timeout
            S_X_BAND_TRNSM_Response_enum cmd_stat = S_X_BAND_TRNSM_SendCMD(Identifier, S_X_BAND_TRNSM_CMD_GET, S_X_BAND_TRNSM_GET_TYPE_ALL_CHANGE_MODE, (uint8_t *) NULL, 0);

            // command was confirmed by the device and CRC checks passed
            if (S_X_BAND_TRNSM_STAT_ACK == cmd_stat)
            {
                uint16_t RxDataLength;

                (void) S_X_BAND_TRNSM_GetResult(Identifier, S_X_BAND_TRNSM_CMD_GET, S_X_BAND_TRNSM_GET_TYPE_ALL_CHANGE_MODE, all_params, &RxDataLength);

                // all_params[0] contains the command status and we want to skip that before casting to S_X_BAND_TRNSM_GET_AllParams_struct *
                moduleCacheInfo.modcod = ((S_X_BAND_TRNSM_GET_AllParams_struct *) &all_params[1])->MODCOD;
                moduleCacheInfo.sym_rate = ((S_X_BAND_TRNSM_GET_AllParams_struct *) &all_params[1])->SymbolRate;
                moduleCacheInfo.pretx_delay_ms = ((S_X_BAND_TRNSM_GET_AllParams_struct *) &all_params[1])->PreTxStaffingDelay;

                moduleCacheInfo.settings_cache_valid = true;
            }
        }

        // now get the file list to be aware of the file sizes stored on the SXBand SD card
        static sUserResponseCtx_t user_resp_ctx;

        user_resp_ctx.pUserCtx = NULL;
        user_resp_ctx.pu8DataBuf = NULL;
        user_resp_ctx.onCmdResponseReady = &S_X_Band_On_CacheUpdateReady;

        // in order to block the caller of this function (who will reside in a different thread than the SXBand driver thread,
        // we need to obtain the active thread ID for signalling later when the operation is finished)
        cacheUpdateThread = osThreadGetId();

        S_X_BAND_TRNSM_ESTTC_StartCmd(Identifier, S_X_BAND_TRNSM_GW_CMD_ID_DIR_LIST, 'R', 0, NULL, &user_resp_ctx, NULL);

        // just perform a blocking wait until command is over (we don't actually care if a timeout occurred)
        (void) osThreadFlagsWait(UNBLOCK_CACHE_THREAD_FLAG,
                                 osFlagsWaitAll,
                                 TX_CMD_TIMEOUT_MS);

        user_resp_ctx.pUserCtx = NULL;
        user_resp_ctx.pu8DataBuf = NULL;
        user_resp_ctx.onCmdResponseReady = NULL;
        moduleCacheInfo.in_progress = false;
    }
}

/*
*********************************************************************************************
* INTERNAL (STATIC) ROUTINES DEFINITION
*********************************************************************************************
*/
/*!
*********************************************************************************************
* @brief Fill up the stack according to the command
*********************************************************************************************
* @param[input]      none
* @param[output]     stackEntry - current stack entry
* @return            see S_X_BAND_CMD_EXTRACT_RES description
*********************************************************************************************
*/
static S_X_BAND_CMD_EXTRACT_RES XSBandExtractCommandAndType (S_X_BAND_CMD_StackEntry *stackEntry) {
    if (stackEntry->ESTTC_request_type == 'R') {
        switch (stackEntry->ESTTC_request) {
            case S_X_BAND_TRNSM_GW_CMD_ID_SYM_RATE:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_SYMBOL_RATE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_TX_PWR:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_TX_POWER;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_CENT_FREQ:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_CENTRAL_FREQ;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_MODCOD:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_MODCOD;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_ROLL_OFF:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_ROLL_OFF;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PILOT:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_PILOT_SIGNAL;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_FEC_FR_SZ:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_FEC_FRAME_SIZE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PRETX_DELAY:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_PRETRASIT_DELAY;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_ALL_PARAMS:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_ALL_CHANGE_MODE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_REP_SIMPLE:
                stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_SIMPLE_REPORT;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_REP_FULL:
                if (IS_XBAND()) {
                    stackEntry->command = S_X_BAND_TRNSM_CMD_GET;
                    stackEntry->type = X_BAND_TRNSM_GET_TYPE_FULL_REPORT;
                } else {
                    return CMD_EXTRACT_RESULT_UNSUP_CMD;
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DIR_LIST:
                stackEntry->command = S_X_BAND_TRNSM_CMD_DIR_F;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                stackEntry->expectSlaveCommand = 1;
                stackEntry->minDelay = 250;
                break;
            default:
                return CMD_EXTRACT_RESULT_UNSUP_CMD;
        }
    } else if (stackEntry->ESTTC_request_type == 'W') {
        switch (stackEntry->ESTTC_request) {
            case S_X_BAND_TRNSM_GW_CMD_ID_SYM_RATE:
                stackEntry->ESTTC_data[0] = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                stackEntry->ESTTC_data_size = sizeof (uint8_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_SYMBOL_RATE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_TX_PWR:
                stackEntry->ESTTC_data[0] = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                stackEntry->ESTTC_data_size = sizeof (uint8_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_TX_POWER;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_CENT_FREQ:
            {
                float centralFreq = (stackEntry->ESTTC_data[0] * 1000) + (stackEntry->ESTTC_data[1] * 100) + (stackEntry->ESTTC_data[2] * 10) + stackEntry->ESTTC_data[3];
                float decPart = (stackEntry->ESTTC_data[5] * 100) + (stackEntry->ESTTC_data[6] * 10) + stackEntry->ESTTC_data[7];
                decPart /= 1000;
                centralFreq += decPart;
                memcpy (stackEntry->ESTTC_data, &centralFreq, sizeof (centralFreq));
                stackEntry->ESTTC_data_size = sizeof (centralFreq);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_CENTRAL_FREQ;
                break;
            }
            case S_X_BAND_TRNSM_GW_CMD_ID_MODCOD:
                stackEntry->ESTTC_data[0] = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                stackEntry->ESTTC_data_size = sizeof (uint8_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_MODCOD;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_ROLL_OFF:
                stackEntry->ESTTC_data[0] = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                stackEntry->ESTTC_data_size = sizeof (uint8_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_ROLL_OFF;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PILOT:
                stackEntry->ESTTC_data[0] = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                stackEntry->ESTTC_data_size = sizeof (uint8_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_PILOT_SIGNAL;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_FEC_FR_SZ:
                stackEntry->ESTTC_data[0] = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                stackEntry->ESTTC_data_size = sizeof (uint8_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_FEC_FRAME_SIZE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PRETX_DELAY:
            {
                uint16_t preTransDelay = (stackEntry->ESTTC_data[0] * 1000) + (stackEntry->ESTTC_data[1] * 100) + (stackEntry->ESTTC_data[2] * 10) + stackEntry->ESTTC_data[3];
                memcpy (stackEntry->ESTTC_data, &preTransDelay, sizeof (preTransDelay));
                stackEntry->ESTTC_data_size = sizeof (uint16_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_PRETRASIT_DELAY;
                break;
            }
            case S_X_BAND_TRNSM_GW_CMD_ID_ALL_PARAMS:
            {
                S_X_BAND_TRNSM_GET_AllParams_struct AllParamsData;
                AllParamsData.SymbolRate         = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                AllParamsData.TxPower            = (stackEntry->ESTTC_data[2] * 10) + stackEntry->ESTTC_data[3];
                AllParamsData.MODCOD             = (stackEntry->ESTTC_data[4] * 10) + stackEntry->ESTTC_data[5];
                AllParamsData.RollOff            = (stackEntry->ESTTC_data[6] * 10) + stackEntry->ESTTC_data[7];
                AllParamsData.PilotSignal        = (stackEntry->ESTTC_data[8] * 10) + stackEntry->ESTTC_data[9];
                AllParamsData.FEC_Frame_Size     = (stackEntry->ESTTC_data[10] * 10) + stackEntry->ESTTC_data[11];
                AllParamsData.PreTxStaffingDelay = (stackEntry->ESTTC_data[12] * 1000) + (stackEntry->ESTTC_data[13] * 100) + (stackEntry->ESTTC_data[14] * 10) + (stackEntry->ESTTC_data[15] * 1);
                AllParamsData.CentralFreq        = (stackEntry->ESTTC_data[16] * 1000) + (stackEntry->ESTTC_data[17] * 100) + (stackEntry->ESTTC_data[18] * 10) + (stackEntry->ESTTC_data[19] * 1);
                float decimal_part               = (stackEntry->ESTTC_data[21] * 100) + (stackEntry->ESTTC_data[22] * 10) + (stackEntry->ESTTC_data[23] * 1);
                decimal_part = decimal_part / 1000;
                AllParamsData.CentralFreq += decimal_part;
                memcpy (stackEntry->ESTTC_data, &AllParamsData, sizeof (S_X_BAND_TRNSM_GET_AllParams_struct));
                stackEntry->ESTTC_data_size = sizeof (S_X_BAND_TRNSM_GET_AllParams_struct);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_GET_TYPE_ALL_CHANGE_MODE;
                break;
            }
            case S_X_BAND_TRNSM_GW_CMD_ID_BAUD_RATE:
                stackEntry->ESTTC_data[0] = (stackEntry->ESTTC_data[0] * 10) + stackEntry->ESTTC_data[1];
                stackEntry->ESTTC_data_size = sizeof (uint8_t);
                stackEntry->command = S_X_BAND_TRNSM_CMD_SET;
                stackEntry->type = S_X_BAND_TRNSM_SET_TYPE_BAUDRATE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_TX_MODE:
                stackEntry->command = S_X_BAND_TRNSM_CMD_TX_MODE;
                stackEntry->retries = 300;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_IDLE_MODE:
                stackEntry->command = S_X_BAND_TRNSM_CMD_LOAD_MODE;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                stackEntry->retries = 300;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_SAFE_SHUTDOWN:
                stackEntry->command = S_X_BAND_TRNSM_CMD_SAFE_SHUTDOWN;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                stackEntry->minDelay = 650;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_FW_UPDATE:
                SX_BAND_TRACE("Updating ... \r\n");
                stackEntry->command = S_X_BAND_TRNSM_CMD_UPDATE_FW;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                stackEntry->expectSlaveCommand = 1;
                stackEntry->minDelay = 3000;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DEL_FILE:
                // Data implicitly set as string
                stackEntry->command = S_X_BAND_TRNSM_CMD_DELL_F;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DEL_ALL:
                stackEntry->command = S_X_BAND_TRNSM_CMD_DELL_ALL_F;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_UPLOAD_FILE:
                // Data implicitly set as string
                stackEntry->retries = 3;
                stackEntry->command = S_X_BAND_TRNSM_CMD_WRITE_F;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                stackEntry->expectSlaveCommand = 1;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DOWNLOAD_FILE:
                // Data implicitly set as string
                stackEntry->retries = 3;
                stackEntry->command = S_X_BAND_TRNSM_CMD_READ_F;
                stackEntry->type = S_X_BAND_TRNSM_NULL_TYPE;
                stackEntry->expectSlaveCommand = 1;
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_SEND_FILES:
                // Data implicitly set as string
                stackEntry->minDelay = 50;
                stackEntry->retries = 6000;
                stackEntry->command = S_X_BAND_TRNSM_CMD_SEND_F;
                stackEntry->type = IS_XBAND() ? S_X_BAND_TRNSM_SEND_F_TYPE_PREDIS_AND_RF : S_X_BAND_TRNSM_SEND_F_TYPE_WITH_RF_TRACT;
                break;
            default:
                return CMD_EXTRACT_RESULT_UNSUP_CMD;
        }
    }

    return CMD_EXTRACT_RESULT_VALID_CMD;
}

/*!
*********************************************************************************************
* @brief A Task that serves commands through ESTTC protocol
*********************************************************************************************
* @param[input]      retRes - execution status
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            none
*********************************************************************************************
*/
static void XSBandTryFinish (uint8_t retRes, S_X_BAND_CMD_StackEntry *stackEntry) {
    // Exit condition - command hasn't been finished yet
    if ((stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) && (0x00 == retRes)) {
        return;
    }
    // Process the stack command result
    if (stackEntry->ESTTC_request_type == 'R') {
        switch (stackEntry->ESTTC_request) {
            case S_X_BAND_TRNSM_GW_CMD_ID_SYM_RATE:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Symbol Rate = %d \r\n", *stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_TX_PWR:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Tx Power = %d \r\n", *stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_CENT_FREQ:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Central Frequency = %4.3f \r\n", *((float *)stackEntry->ESTTC_data));
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_MODCOD:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "MODCOD = %d \r\n", *stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_ROLL_OFF:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Roll-Off = %d \r\n", *stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PILOT:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Pilot Signal = %d \r\n", *stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_FEC_FR_SZ:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "FEC Frame size = %d \r\n", *stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PRETX_DELAY:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Pretransmission Staf Delay = %d \r\n", *((uint16_t *)stackEntry->ESTTC_data));
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_ALL_PARAMS:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    S_X_BAND_TRNSM_GET_AllParams_struct *AllParamsData = (S_X_BAND_TRNSM_GET_AllParams_struct *)stackEntry->ESTTC_data;
                    USER_START_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "           Symbol Rate = %d \r\n"   , AllParamsData->SymbolRate);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "              Tx Power = %d \r\n"   , AllParamsData->TxPower);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                MODCOD = %d \r\n"   , AllParamsData->MODCOD);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "              Roll Off = %d \r\n"   , AllParamsData->RollOff);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "          Pilot Signal = %d \r\n"   , AllParamsData->PilotSignal);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "   Pre. FEC Frame Size = %d \r\n"   , AllParamsData->FEC_Frame_Size);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "Pre. Tx Staffing delay = %d \r\n"   , AllParamsData->PreTxStaffingDelay);
                    USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "     Central Frequency = %4.3f \r\n", AllParamsData->CentralFreq);
                    USER_COMMIT_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_REP_SIMPLE:
                if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                    if (IS_XBAND()) {
                        X_BAND_TRNSM_GET_SimpleReport_struct *SimpleReportData = (X_BAND_TRNSM_GET_SimpleReport_struct *)stackEntry->ESTTC_data;
                        USER_START_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "          System State = %d \r\n", SimpleReportData->SystemState);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "           Status Flag = %d \r\n", SimpleReportData->StatusFlag);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "        PA Temperature = %d \r\n", SimpleReportData->PA_Temp);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "              Tx Power = %d \r\n", SimpleReportData->TxPower_m);
                        USER_COMMIT_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                    } else {
                        S_BAND_TRNSM_GET_SimpleReport_struct *SimpleReportData = (S_BAND_TRNSM_GET_SimpleReport_struct *)stackEntry->ESTTC_data;
                        USER_START_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "          System State = %d \r\n",    SimpleReportData->SystemState);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "           Status Flag = %d \r\n",    SimpleReportData->StatusFlag);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "     CPU Temperature = %3.1f \r\n",   SimpleReportData->CPU_Temp);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "           FW version = %d \r\n",     (int) SimpleReportData->FW_Version);
                        USER_COMMIT_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_REP_FULL:
                if (IS_XBAND()) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        X_BAND_TRNSM_GET_FullReport_struct *FullReportData = (X_BAND_TRNSM_GET_FullReport_struct *)stackEntry->ESTTC_data;
                        USER_START_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                  System State         = %d \r\n", FullReportData->SystemState);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                   Status Flag         = %d \r\n", FullReportData->StatusFlag);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                PA Temperature         = %d \r\n", FullReportData->PA_Temp);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                      Tx Power         = %d \r\n", FullReportData->TxPower_m);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "          Predistortion Status         = %d \r\n", FullReportData->PredistortionStat);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "           Predistortion Error         = %d \r\n", FullReportData->PredistortionErr);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "         Predistortion Warning         = %d \r\n", FullReportData->PredistortionWarning);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "        Predistortion Frequency Range  = %d \r\n", FullReportData->PredistortionFreqRange);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "        Predistortion Adaptation Mode  = %d \r\n", FullReportData->PredistortionAdaptMode);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "        Predistortion Adaptation State = %d \r\n", FullReportData->PredistortionAdaptState);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "           Predistortion Output Status = %d \r\n", FullReportData->PredistortionOutputStat);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "    Predistortion Normalization Factor = %d \r\n", FullReportData->PredistortionNomrFact);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                Predistortion RFIN_AGC = %d \r\n", FullReportData->PredistortionRFIN_AGC);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                Predistortion RFRB_AGC = %d \r\n", FullReportData->PredistortionRFRB_AGC);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "Predistortion Unnormilized Coefficient = %d \r\n", FullReportData->PredistortionUnnormCoeff);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "    Predistortion Internal Temperature = %d \r\n", FullReportData->PredistortionInternTemp);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "  Predistortion Minimum Frequency Scan = %f \r\n", FullReportData->PredisMinFreqScan);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "  Predistortion Maximum Frequency Scan = %f \r\n", FullReportData->PredisMaxFreqScan);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "        Predistortion Signal Bandwidth = %f \r\n", FullReportData->PredisSignalBandwidth);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "       Predistortion Central Frequency = %f \r\n", FullReportData->PredisCentralFreq);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                       CPU Temperature = %f \r\n", FullReportData->CPU_Temperature);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                            FW version = %d \r\n", (int)FullReportData->FW_Version);
                        USER_COMMIT_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Error: Command not supported for SBand module\r\n");
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DIR_LIST:
                if (S_X_BAND_TRNSM_DIR_OK != retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Reading: Error %d \r\n", retRes);
                }
                break;
            default:
                USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err Unknown CMD 0x%X\r\n", (uint8_t) stackEntry->ESTTC_request);
                break;
        }
    } else if (stackEntry->ESTTC_request_type == 'W') {
        switch (stackEntry->ESTTC_request) {
            case S_X_BAND_TRNSM_GW_CMD_ID_SYM_RATE:
                if (stackEntry->ESTTC_data_size == sizeof (uint8_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Symbol Rate = %d \r\n", stackEntry->ESTTC_data[0]);

                        // update cached value when the user makes a set request to the module
                        moduleCacheInfo.sym_rate = stackEntry->ESTTC_data[0];
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_TX_PWR:
                if (stackEntry->ESTTC_data_size == sizeof (uint8_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Tx Power = %d \r\n", stackEntry->ESTTC_data[0]);
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_CENT_FREQ:
                if (stackEntry->ESTTC_data_size == sizeof (float)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Central Frequency = %4.3f \r\n", *((float *)stackEntry->ESTTC_data));
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_MODCOD:
                if (stackEntry->ESTTC_data_size == sizeof (uint8_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "MODCOD = %d \r\n", stackEntry->ESTTC_data[0]);

                        // update cached value when the user makes a set request to the module
                        moduleCacheInfo.modcod = stackEntry->ESTTC_data[0];
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_ROLL_OFF:
                if (stackEntry->ESTTC_data_size == sizeof (uint8_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Roll-Off = %d \r\n", stackEntry->ESTTC_data[0]);
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PILOT:
                if (stackEntry->ESTTC_data_size == sizeof (uint8_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Pilot Signal = %d \r\n", stackEntry->ESTTC_data[0]);
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_FEC_FR_SZ:
                if (stackEntry->ESTTC_data_size == sizeof (uint8_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "FEC Frame size = %d \r\n", stackEntry->ESTTC_data[0]);
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_PRETX_DELAY:
                if (stackEntry->ESTTC_data_size == sizeof (uint16_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Pretransmission Staf Delay = %d \r\n", *((uint16_t *)stackEntry->ESTTC_data));
                        moduleCacheInfo.pretx_delay_ms = *((uint16_t *) (stackEntry->ESTTC_data));
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_ALL_PARAMS:
                if (stackEntry->ESTTC_data_size == sizeof (S_X_BAND_TRNSM_GET_AllParams_struct)) {
                    S_X_BAND_TRNSM_GET_AllParams_struct AllParamsData;
                    memcpy (&AllParamsData, stackEntry->ESTTC_data, sizeof (S_X_BAND_TRNSM_GET_AllParams_struct));
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_START_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "           Symbol Rate = %d \r\n"   , AllParamsData.SymbolRate);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "              Tx Power = %d \r\n"   , AllParamsData.TxPower);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "                MODCOD = %d \r\n"   , AllParamsData.MODCOD);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "              Roll Off = %d \r\n"   , AllParamsData.RollOff);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "          Pilot Signal = %d \r\n"   , AllParamsData.PilotSignal);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "   Pre. FEC Frame Size = %d \r\n"   , AllParamsData.FEC_Frame_Size);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "Pre. Tx Staffing delay = %d \r\n"   , AllParamsData.PreTxStaffingDelay);
                        USER_APPEND_FORMATTED_BUF(stackEntry->pUserRespCtx, "     Central Frequency = %4.3f \r\n", AllParamsData.CentralFreq);
                        USER_COMMIT_MULTI_BUF_SEQ(stackEntry->pUserRespCtx);

                        // update cached values on set
                        moduleCacheInfo.sym_rate = AllParamsData.SymbolRate;
                        moduleCacheInfo.modcod = AllParamsData.MODCOD;
                        moduleCacheInfo.pretx_delay_ms = AllParamsData.PreTxStaffingDelay;

                        moduleCacheInfo.settings_cache_valid = true;
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_BAUD_RATE:
                if (stackEntry->ESTTC_data_size == sizeof (uint8_t)) {
                    if (S_X_BAND_TRNSM_PARAMS_OK == retRes) {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Baud rate = %d \r\n", stackEntry->ESTTC_data[0]);
                    } else {
                        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                    }
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err - Size %d\r\n", stackEntry->ESTTC_data_size);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_TX_MODE:
                if (S_X_BAND_TRNSM_CHANG_MODE_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Tx mode started \r\n");
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_IDLE_MODE:
                if (S_X_BAND_TRNSM_CHANG_MODE_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Load mode started \r\n");
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_SAFE_SHUTDOWN:
                if (S_X_BAND_TRNSM_CHANG_MODE_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Ready to Shut Down \r\n");
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_FW_UPDATE:
                if (S_X_BAND_TRNSM_CHANG_MODE_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "FW Updated using  '%s' \r\n", (char *)stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DEL_FILE:
                if (S_X_BAND_TRNSM_DELL_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "File '%s' deleted \r\n", (char *)stackEntry->ESTTC_data);
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DEL_ALL:
                if (S_X_BAND_TRNSM_DELL_OK == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "All files deleted \r\n");
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Set Parameter: Error %d \r\n", stackEntry->response);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_UPLOAD_FILE:  // Copy a file from the OBC to the X-Band
                if (0x00 == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "File '%s' Uploaded\r\n", (char *)stackEntry->ESTTC_data);
                } else if (S_X_BAND_TRNSM_STAT_WRONG_PARAM == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Copy Err - Parameter/File name \r\n");
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Copy Err %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_DOWNLOAD_FILE:  // Copy a file from X-Band to the OBC
                if (0x00 == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "File '%s' Downloaded\r\n", (char *)stackEntry->ESTTC_data);
                } else if (S_X_BAND_TRNSM_STAT_WRONG_PARAM == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Copy Err - Parameter/File name \r\n");
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Copy Err %d \r\n", retRes);
                }
                break;
            case S_X_BAND_TRNSM_GW_CMD_ID_SEND_FILES: // Start transmitting files over radio
                if (0x00 == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "File '%s' Sent\r\n", (char *)stackEntry->ESTTC_data);
                } else if (S_X_BAND_TRNSM_STAT_WRONG_PARAM == retRes) {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Sending Err - Parameter/File name \r\n");
                } else {
                    USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Sending Err %d \r\n", retRes);
                }
                break;
            default:
                USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Err Unknown CMD 0x%X\r\n", (uint8_t) stackEntry->ESTTC_request);
                break;
        }
    } else {
        USER_COMMIT_FORMATTED_BUF(stackEntry->pUserRespCtx, "Unknown request type '%c' \r\n", stackEntry->ESTTC_request_type);
    }
    stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_EMPTY;
    stackEntry->pUserRespCtx = NULL;
    if (XSBandStack_Slave.parentEntry == stackEntry) {
        sx_band_init_stack(&XSBandStack_Slave);
    }
}

/*!
*********************************************************************************************
* @brief Change the mode of the RS485
*********************************************************************************************
* @param[input]      state:
*                       1 - Transmit
*                       0 - Receive
* @param[output]     none
* @return            none
* @note              none
*********************************************************************************************
*/
static void S_X_BAND_TRNSM_Rx_Tx_State(uint8_t state)
{
    if( state == 0 )
    {
        /* Receive mode */
        HAL_GPIO_WritePin(SX_BAND_TxEnbl_GPIO_Port, SX_BAND_TxEnblPin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(U3_RS485_S1_nRE_GPIO_Port, U3_RS485_S1_nRE_Pin, GPIO_PIN_RESET);
    }else{
        /* Transmit mode */
        HAL_GPIO_WritePin(SX_BAND_TxEnbl_GPIO_Port, SX_BAND_TxEnblPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(U3_RS485_S1_nRE_GPIO_Port, U3_RS485_S1_nRE_Pin, GPIO_PIN_SET);
    }

    osDelay(1);
}


/*!
*********************************************************************************************
* @brief Transmit Acknowledge packet after response of a successful command
*********************************************************************************************
* @param[input]      Identifier - ID of the used S or X band transmitter
* @param[input]      CMD - command number from enumeration X_BAND_TRNSM_CMD_enum, that was already transmitted
* @param[input]      CMD_Type - Some commands have different types, the rest don't have. Use values as follow:
*                       + X_BAND_TRNSM_NULL_TYPE - for commands without type
*                       + value form X_BAND_TRNSM_GET_types_enum - for Command GET (X_BAND_TRNSM_CMD_GET)
*                       + value from X_BAND_TRNSM_SET_types_enum - for Command SET (X_BAND_TRNSM_CMD_SET)
*                       + value from X_BAND_TRNSM_SendFile_types_enum - for Command SEND FILE (X_BAND_TRNSM_CMD_SEND_F)
*                       + value from X_BAND_TRNSM_SendFile_types_enum - for Command SEND FILE (X_BAND_TRNSM_CMD_SEND_F)
* @param[output]     none
* @return            none
* @note              none
*********************************************************************************************
*/
static void S_X_BAND_TRNSM_Send_Ack(uint16_t Identifier, S_X_BAND_TRNSM_CMD_enum CMD, uint16_t CMD_Type) {
    uint32_t TxPackCRC = 0;
    S_X_BAND_TRNSM_Pack_struct * TxPackStruct = (S_X_BAND_TRNSM_Pack_struct *)TxDataBuffer;

    TxPackStruct->Header = S_X_BAND_TRNSM_HEADER;
    TxPackStruct->ModuleID = Identifier;
    TxPackStruct->Length = 0;
    TxPackStruct->Response = S_X_BAND_TRNSM_STAT_ACK;
    TxPackStruct->CMD = (uint16_t) TxCMD_Descriptor[CMD].CMD;
    TxPackStruct->Type = CMD_Type;

    /* copy the structure of the packet to the transmit buffer */
    TxPackCRC = crc32(0, (BYTE *)TxPackStruct, S_X_BAND_TRNSM_STRCT_SIZE);

    // Clear the extra bytes that will be set after the packet to complete to divisible to 16
    memset(&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE + sizeof(TxPackCRC)],0,((((S_X_BAND_TRNSM_STRCT_SIZE + sizeof(TxPackCRC))>>4)+1)<<4) - (S_X_BAND_TRNSM_STRCT_SIZE + sizeof(TxPackCRC)));

    /* copy the CRC to the transmit buffer after the structure of the packet */
    memcpy(&TxDataBuffer[S_X_BAND_TRNSM_STRCT_SIZE + TxPackStruct->Length], &TxPackCRC, sizeof(TxPackCRC));

    S_X_BAND_TRNSM_Rx_Tx_State(1);

    (void) HAL_UART_Transmit_DMA (p_sx_band_uart_hnd, TxDataBuffer, (((S_X_BAND_TRNSM_STRCT_SIZE + sizeof(TxPackCRC))>>4)+1)<<4);
}

/*!
*********************************************************************************************
* @brief Writes all settings of the S-Band transmitter (without the baud-rate)
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            retStat - a value from enumeration X_BAND_TRNSM_SetGetParams_enum
* @note              none
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_CMD_SET_Param (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLenght;

    // Check for baudrate
    if (stackEntry->type == S_X_BAND_TRNSM_SET_TYPE_BAUDRATE) {
        return S_X_BAND_TRNSM_CMD_SET_Param_Baudrate (stackEntry);
    }
    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, stackEntry->ESTTC_data, stackEntry->ESTTC_data_size);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) {
                break;
            }
            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLenght);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Verify the answer
                if (sizeof (retStat) == RxDataLenght) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if ((retStat == S_X_BAND_TRNSM_PARAMS_OK) || (retStat == S_X_BAND_TRNSM_PARAMS_PARAMS_ERR)) {
                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) {
                    retStat = 0x00;
                }
#if S_X_BAND_STACK_DELAY
                else {
                    SX_BAND_TRACE("X_BAND_TRNSM_CMD_SET_Param GETRESULT error %d\r\n", (int)retStat);
                }
#endif
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Reads one settings of the S-Band transmitter (without the baud-rate)
*********************************************************************************************
* @param[input]      stackEntry - current stack entry
* @param[output]     none
* @return            retStat - a value from enumeration X_BAND_TRNSM_SetGetParams_enum
* @note              none
*********************************************************************************************
*/
static uint8_t S_X_BAND_TRNSM_CMD_GET_Param (S_X_BAND_CMD_StackEntry *stackEntry) {
    uint8_t retStat = 0x00;
    uint16_t RxDataLength;
    uint32_t expectedSize = 0;

    // Check for available retries
    if (stackEntry->retries <= 0) {
        if (stackEntry->state != S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED) {
            retStat = S_X_BAND_TRNSM_PARAMS_COMM_ERR;
        }
        return retStat;
    }
    // Check for command state
    switch (stackEntry->state) {
        case S_X_BAND_TRNSM_CMD_STATE_CMD:
        case S_X_BAND_TRNSM_CMD_STATE_CMD_RES:
            // Send command
            retStat = S_X_BAND_TRNSM_SendCMD (stackEntry->devID, stackEntry->command, stackEntry->type, 0, 0);
            if (S_X_BAND_TRNSM_STAT_ACK == retStat) {
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT;
                stackEntry->timestamp = xTaskGetTickCount();
            } else {
                // Failed to send the command
                stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_RES;
                if ((S_X_BAND_TRNSM_STAT_COMM_ERR == retStat) && (!S_X_BAND_TRNSM_Scan_Baud_Rates (stackEntry->devID))) {
                    stackEntry->retries = 0;
                    break;
                }

                S_X_BAND_STACK_RETR_SUB (retStat != S_X_BAND_TRNSM_STAT_ACK && retStat != S_X_BAND_TRNSM_STAT_GET_RESULT, stackEntry);
            }
            retStat = 0x00;
            break;
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT:
        case  S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES:
            // Check whether the protocol delay has passed
            if (stackEntry->minDelay > (xTaskGetTickCount() - stackEntry->timestamp)) {
                break;
            }

            stackEntry->timestamp = xTaskGetTickCount();
            // Send GetResult command
            retStat = S_X_BAND_TRNSM_GetResult (stackEntry->devID, stackEntry->command, stackEntry->type, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLength);
            // Update the state
            stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_GETRESULT_RES;
            if (S_X_BAND_TRNSM_STAT_GET_RESULT == retStat) {
                // Identify the expected size
                switch (stackEntry->type) {
                    case S_X_BAND_TRNSM_GET_TYPE_SIMPLE_REPORT:
                        if (IS_XBAND()) {
                            expectedSize = sizeof (X_BAND_TRNSM_GET_SimpleReport_struct);
                        } else {
                            expectedSize = sizeof (S_BAND_TRNSM_GET_SimpleReport_struct);
                        }
                        break;
                    case X_BAND_TRNSM_GET_TYPE_FULL_REPORT:
                        expectedSize = sizeof (X_BAND_TRNSM_GET_FullReport_struct);
                        break;

                    default:
                        expectedSize = sizeof (S_X_BAND_TRNSM_GET_AllParams_struct);
                        break;
                }

                // Verify the answer
                ++expectedSize;

                if ((expectedSize >= RxDataLength) && (RxDataLength > 0)) {
                    // Get the status of the request
                    retStat = S_X_BAND_TRNSM_Result_Rx_Buffer[0];
                    // If the status is "OK"
                    if (retStat == S_X_BAND_TRNSM_PARAMS_OK) {
                        // Update the state
                        stackEntry->state = S_X_BAND_TRNSM_CMD_STATE_CMD_FINISHED;
                        // Copy the data
                        stackEntry->ESTTC_data_size = RxDataLength - 1;
                        memcpy (stackEntry->ESTTC_data, &S_X_BAND_TRNSM_Result_Rx_Buffer[1], stackEntry->ESTTC_data_size);
                        break;
                    }
                }
            } else {
                // Failed to send the command
                if (S_X_BAND_STACK_RETR_COND(retStat)) {
                    retStat = 0x00;
                }
#if S_X_BAND_STACK_DELAY
                else {
                    SX_BAND_TRACE("X_BAND_TRNSM_CMD_GET_Param GETRESULT error %d\r\n", (int)retStat);
                }
#endif
            }
            // Subtract the retry count
            DECR_IF_NONZERO(stackEntry->retries);
            break;
        default:
            break;
    }

    return retStat;
}

/*!
*********************************************************************************************
* @brief Check for successful communication at all available baudrates
*********************************************************************************************
* @param[input]      Identifier - ID of the used S or X band transmitter
* @param[output]     none
* @return            true - done, false - failed to establish communication
* @note              none
*********************************************************************************************
*/
static bool S_X_BAND_TRNSM_Scan_Baud_Rates(uint16_t Identifier)
{
    bool comm_success = false;

    for (uint8_t Baudrate = 0U; Baudrate < CDEF_ELEMENT_COUNT(BaudRateArray); Baudrate++)
    {
        S_X_BAND_TRNSM_S_Current_Baudrate = Baudrate;
        S_X_BAND_LastExecCmd_Tick = 0U;

        // reinitialize UART with a different baud-rate
        sx_band_init(INIT_HW);

        S_X_BAND_TRNSM_Response_enum cmd_stat = S_X_BAND_TRNSM_SendCMD(Identifier, S_X_BAND_TRNSM_CMD_GET, S_X_BAND_TRNSM_GET_TYPE_SYMBOL_RATE, 0, 0);

        if (S_X_BAND_TRNSM_STAT_ACK == cmd_stat)
        {
            uint16_t RxDataLength;
            // just obtain the result of the command to clean it up from the X-band Transmitter stack
            (void) S_X_BAND_TRNSM_GetResult(Identifier, S_X_BAND_TRNSM_CMD_GET, S_X_BAND_TRNSM_GET_TYPE_SYMBOL_RATE, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLength);

            comm_success = true;
            break;
        }
    }

    if (!comm_success)
    {
        S_X_BAND_TRNSM_S_Current_Baudrate = S_X_BAND_TRNSM_DEFAULT_BAUDRATE;
        sx_band_init(INIT_HW);
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_S_X_BAND, eEXEH_S_X_BAND_EXCEPTION_ID_AUTO_BAUD_RATE_NOT_FOUND, __LINE__);
    }

    return comm_success;
}

/*!
*********************************************************************************************
* @brief The function probes the radio module with the `Simple Report` command to determine
*         the correct type of device connected to the OBC. The returned response differs in
*         size between the S- and X-Band modules.
*********************************************************************************************
*/
static void S_X_BAND_TRNSM_Detect_Band_Type(const uint16_t Identifier)
{
    // one time detection is performed after SXBand subsystem init
    if (S_X_BAND_TRNSM_DEVTYPE_UNKNOWN == XSBandDevType)
    {
        S_X_BAND_TRNSM_Response_enum cmd_stat = S_X_BAND_TRNSM_SendCMD(Identifier, S_X_BAND_TRNSM_CMD_GET, S_X_BAND_TRNSM_GET_TYPE_SIMPLE_REPORT, (uint8_t *) NULL, 0);

        // command was confirmed by the device and CRC checks passed
        if (S_X_BAND_TRNSM_STAT_ACK == cmd_stat)
        {
            uint16_t RxDataLength;

            (void) S_X_BAND_TRNSM_GetResult(Identifier, S_X_BAND_TRNSM_CMD_GET, S_X_BAND_TRNSM_GET_TYPE_SIMPLE_REPORT, S_X_BAND_TRNSM_Result_Rx_Buffer, &RxDataLength);

            switch (RxDataLength)
            {
                case sizeof(X_BAND_TRNSM_GET_SimpleReport_struct) + 1U:
                    XSBandDevType = S_X_BAND_TRNSM_DEVTYPE_XBAND;
                break;

                case sizeof(S_BAND_TRNSM_GET_SimpleReport_struct) + 1U:
                    XSBandDevType = S_X_BAND_TRNSM_DEVTYPE_SBAND;
                break;

                default:
                    // assume we have an XBand just to avoid forcing detection on each subsequent command
                    XSBandDevType = S_X_BAND_TRNSM_DEVTYPE_XBAND;
                break;
            }
        }

        // no else clause because this means that the command could not be sent and we should try
        // again next time
    }
}

/*!
*********************************************************************************************
* @brief The function provides a worst-case estimate of the time to wait for a command to
*        finish execution.
*
* The calculated ETA can be used to schedule command execution in series without prematurely
* timing out.
*
* @param[in[ Id Module identifier (not relevant for the timeout estimation but needed for
*               certain commands to collect settings from the module before estimating the
*               time to wait)
* @param[in] Cmd command identifier
* @param[in] Type command type (ASCII 'R'ead or 'W'rite)
* @param[in] size Data size in bytes
* @param[in] pData command data (used for certain commands such as 'Send files' to be able to
*                  estimate the size of all files requested)
* @return worst-case timeout for the specified command in milliseconds
*********************************************************************************************
*/
static uint32_t S_X_Band_Get_Cmd_Timeout(uint16_t Identifier, S_X_BAND_TRNSM_GW_CMD_ID_enum Cmd, uint8_t Type, uint8_t size, const uint8_t * pData)
{
    double timeout_ms = CMD_AVG_TIMEOUT_MS;

    switch (Cmd)
    {
        case S_X_BAND_TRNSM_GW_CMD_ID_UPLOAD_FILE:
        {
            uint32_t fsize = 0U;
            FILINFO fno;

            FRESULT fres = SdMngr_f_stat((const TCHAR *) pData, &fno);

            fsize = (FR_OK == fres) ? fno.fsize : 0;

            if (0U == fsize)
            {
                timeout_ms = FILE_CMD_TIMEOUT_MIN_MS;
            }
            else
            {
                timeout_ms = (1000. * fsize) / WORST_BYTES_PER_SEC_RATE;

                // put minimum timeout to ensure that waiting will not finish before the SXBand driver has a chance to
                // activate its task to attempt communication
                if (timeout_ms < FILE_CMD_TIMEOUT_MIN_MS)
                {
                    timeout_ms = FILE_CMD_TIMEOUT_MIN_MS;
                }
            }

            break;
        }

        case S_X_BAND_TRNSM_GW_CMD_ID_DOWNLOAD_FILE:
        {
            uint64_t downloadSizeBytes = S_X_Band_Get_File_Size_From_Cache((const char * const) pData);

            timeout_ms = (1000. * downloadSizeBytes) / WORST_BYTES_PER_SEC_RATE;


            break;
        }

        case S_X_BAND_TRNSM_GW_CMD_ID_SEND_FILES:
        {
            if ((moduleCacheInfo.settings_cache_valid) &&
                (moduleCacheInfo.file_cache_valid) &&
                (moduleCacheInfo.modcod < CDEF_ELEMENT_COUNT(ModCod_BitRate_Coeffs) - 1) &&
                (moduleCacheInfo.sym_rate != INVALID_SETTING_VALUE_1B))
            {
                uint64_t downloadSizeBytes = S_X_Band_Get_File_Size_From_Cache((const char * const) pData);

                // refer to SXBand User's Manual for calculation details
                // (S-Band Transmitter rev. 2.15 / page 76)
                // (X-Band Transmitter rev. 2.15 / page 76)
                double max_bits_per_sec = (moduleCacheInfo.sym_rate * 1e6) * ModCod_BitRate_Coeffs[moduleCacheInfo.modcod];

                // decrease bit rate estimation with the transmission-specfic overhead
                max_bits_per_sec -= ((max_bits_per_sec * TRNSM_ENC_OVERHEAD_PERCENTAGE) / 100.);

                timeout_ms = (BITS_IN_1_BYTE * 1000. * downloadSizeBytes) / max_bits_per_sec;
            }
            else
            {
                // the timeout calculation cannot be performed due to invalid cache
                timeout_ms = TX_CMD_TIMEOUT_MS;
            }

            break;
        }

        case S_X_BAND_TRNSM_GW_CMD_ID_TX_MODE:
        {
            timeout_ms = TX_CMD_TIMEOUT_MS;

            // if the pretransmission delay value is cached, also add it here just in case
            if ((moduleCacheInfo.settings_cache_valid) &&
                (moduleCacheInfo.pretx_delay_ms != INVALID_SETTING_VALUE_2B))
            {
                timeout_ms += moduleCacheInfo.pretx_delay_ms;
            }

            break;
        }

        case S_X_BAND_TRNSM_GW_CMD_ID_DEL_FILE:
        case S_X_BAND_TRNSM_GW_CMD_ID_DEL_ALL:
        {
            timeout_ms = DEL_CMD_TIMEOUT_MS;
            break;
        }

        case S_X_BAND_TRNSM_GW_CMD_ID_SYM_RATE:
        case S_X_BAND_TRNSM_GW_CMD_ID_TX_PWR:
        case S_X_BAND_TRNSM_GW_CMD_ID_CENT_FREQ:
        case S_X_BAND_TRNSM_GW_CMD_ID_MODCOD:
        case S_X_BAND_TRNSM_GW_CMD_ID_ROLL_OFF:
        case S_X_BAND_TRNSM_GW_CMD_ID_PILOT:
        case S_X_BAND_TRNSM_GW_CMD_ID_FEC_FR_SZ:
        case S_X_BAND_TRNSM_GW_CMD_ID_PRETX_DELAY:
        case S_X_BAND_TRNSM_GW_CMD_ID_ALL_PARAMS:
        case S_X_BAND_TRNSM_GW_CMD_ID_REP_SIMPLE:
        case S_X_BAND_TRNSM_GW_CMD_ID_REP_FULL:
        case S_X_BAND_TRNSM_GW_CMD_ID_BAUD_RATE:
        case S_X_BAND_TRNSM_GW_CMD_ID_IDLE_MODE:
        case S_X_BAND_TRNSM_GW_CMD_ID_SAFE_SHUTDOWN:
        case S_X_BAND_TRNSM_GW_CMD_ID_FW_UPDATE:
        case S_X_BAND_TRNSM_GW_CMD_ID_DIR_LIST:
        case S_X_BAND_TRNSM_GW_CMD_ID_MAX:
        default:
        {
            break;
        }
    }

    // assuming the command sender thread blocks for the calculated timeout value here, if the value is
    // too small, the caller may unblock its thread and decide there is a buffer timeout prematurely as
    // the SXBand response buffer needs several task executions to be filled completely and sent back
    // (this average worst case timeout guard is here to avoid such situations)
    if (((uint32_t) timeout_ms) < CMD_AVG_TIMEOUT_MS)
    {
        timeout_ms = CMD_AVG_TIMEOUT_MS;
    }

    SX_BAND_TRACE("cmd 0x%04x | type: %c | sz = %lu == timeout (ms) ==> %lu\r\n", Cmd, (char) Type, size, (uint32_t) timeout_ms);

    return (uint32_t) timeout_ms;
}

/** @brief Called when a new dir list command is triggered for execution */
static void S_X_Band_On_Dir_List_Start(void)
{
    moduleCacheInfo.file_cache_valid = false;

    (void) SdMngr_f_close(&moduleCacheInfo.fhnd);
    (void) SdMngr_f_open(&moduleCacheInfo.fhnd, SX_BAND_FILECACHE_NAME, FA_CREATE_ALWAYS | FA_WRITE);
}

/** @brief Called when new file data is enumerated by the Dir List command
 *  @param[in] pFileInfo a pointer to the file info structure as reported by the SXBand module
 */
static void S_X_Band_On_Enumerate_File(const S_X_BAND_TRNSM_FileInfo_struct * const pFileInfo)
{
    if (moduleCacheInfo.in_progress)
    {
        uint32_t bytes_written = 0U;
        FRESULT fres = SdMngr_f_write(&moduleCacheInfo.fhnd, pFileInfo, sizeof(S_X_BAND_TRNSM_FileInfo_struct), (UINT *) &bytes_written);

        if ((FR_OK == fres) && (bytes_written == sizeof(S_X_BAND_TRNSM_FileInfo_struct)))
        {
            SX_BAND_TRACE("== SXB CACHE UPDATE ===> %s | size = %lu\r\n", pFileInfo->FileName, pFileInfo->Size);
            moduleCacheInfo.file_cache_valid = true;
        }
        else
        {
            moduleCacheInfo.file_cache_valid = false;
        }
    }
}

/** @brief Called when the dir list operation finished and there are no more files to report via
 *         @ref S_X_Band_On_Enumerate_File()
 */
static void S_X_Band_On_Dir_List_Finished(void)
{
    (void) SdMngr_f_close(&moduleCacheInfo.fhnd);
}

/** @brief Scans the existing SXBand SD card file cache for one or more files and
 *         calculates their total size.
 *
 *  The function is used for worst-case timeout calculations when scheduling SXBand
 *  file transfer commands.
 *
 *  @param[in] pFilePattern a single file name or a valid SXBand file pattern which can
 *                          be used with the SendFiles command (only asterisk '*' symbol is supported)
 *  @return size in bytes of all files matching the pattern specified
 */
static uint64_t S_X_Band_Get_File_Size_From_Cache(const char * const pFilePattern)
{
    uint64_t totalSize = 0LL;
    FIL fhnd;
    uint32_t bytes_read = 0U;

    FRESULT fres = SdMngr_f_open(&fhnd, SX_BAND_FILECACHE_NAME, FA_OPEN_EXISTING | FA_READ);

    if (FR_OK == fres)
    {
        S_X_BAND_TRNSM_FileInfo_struct finfo_entry;

        fres = SdMngr_f_read(&fhnd, &finfo_entry, sizeof(finfo_entry), (UINT *) &bytes_read);

        while (bytes_read > 0)
        {
            if ((FR_OK == fres) && (bytes_read == sizeof(finfo_entry)))
            {
                if ((finfo_entry.NameLength > 0) &&
                    (S_X_Band_Is_Pattern_Matching(pFilePattern,
                                                  strlen(pFilePattern),
                                                  (const char * const) finfo_entry.FileName,
                                                  finfo_entry.NameLength - 1)))
                {
                    totalSize += finfo_entry.Size;

                    // if this is not a pattern string and we already found a match, there is no need to go on
                    // with checking
                    if (NULL == strstr(pFilePattern, "*"))
                    {
                        break;
                    }
                }
            }

            fres = SdMngr_f_read(&fhnd, &finfo_entry, sizeof(finfo_entry), (UINT *) &bytes_read);
        }
    }

    SdMngr_f_close(&fhnd);

    return totalSize;
}

/** @brief Checks if a specified pattern matches a file name
 *
 *  Supports wildcards with an asterisk '*' symbol only (it represents any string, character or even lack of string).
 *
 *  @param[in] pFilePattern Valid SXBand SendFiles file pattern string
 *  @param[in] patSize size of pFilePattern in bytes (without any NULLZ characters)
 *  @param[in] pFileName File name to check against the pattern
 *  @param[in] fnSize size of pFilePattern in bytes (without any NULLZ characters)*
 *
 *  @return true: the file name matches the pattern; false: otherwise
 */
static bool S_X_Band_Is_Pattern_Matching(const char* const pFilePattern, const uint32_t patSize, const char* const pFileName, const uint32_t fnSize)
{
    const char* p_pat = pFilePattern;
    const char* p_fil = pFileName;
    uint8_t pat_idx = 0;
    uint8_t fli_idx = 0;
    bool starts_with_asterisk = false;

    while ((pat_idx < patSize) && (fli_idx < patSize))
    {
        while (*p_pat == '*')
        {
            starts_with_asterisk = true;
            p_pat++;
            pat_idx++;

            if (pat_idx >= patSize)
            {
                // pattern string finished with an asterisk, so we match the rest of the filename automatically
                return true;
            }
        }

        if (starts_with_asterisk)
        {
            while (toupper(*p_pat) != toupper(*p_fil))
            {
                if (fli_idx >= fnSize)
                {
                    // we reached end of the file name string without any match
                    return false;
                }

                fli_idx++;
                p_fil++;
            }
        }

        // match fixed part
        while (toupper(*p_pat) == toupper(*p_fil))
        {
            if ((pat_idx >= patSize) && (fli_idx >= fnSize))
            {
                // both strings finished and comparison didn't fail up to now - we have a match
                return true;
            }

            p_pat++;
            p_fil++;

            pat_idx++;
            fli_idx++;
        }

        if (*p_pat != '*')
        {
            // match sequence stopped and the pattern doesn't continue with a wildcard symbol in
            // order to continue matching
            return false;
        }
    }

    return true;
}

/** @brief Initialize an SXBand stack entry in memory
 *
 *  @param[out] p_stack_entry a pointer to the entry to be initialized
 *
 */
static void sx_band_init_stack(S_X_BAND_CMD_StackEntry * const p_stack_entry)
{
    CRIT_ASSERT(NULL != p_stack_entry);

    p_stack_entry->devID = 0x0000;
    p_stack_entry->state = S_X_BAND_TRNSM_CMD_STATE_EMPTY;
    p_stack_entry->ESTTC_request = S_X_BAND_TRNSM_GW_CMD_ID_MAX;
    p_stack_entry->ESTTC_request_type = '\0';
    p_stack_entry->ESTTC_data_size = 0;
    (void) memset(p_stack_entry->ESTTC_data, 0, sizeof(p_stack_entry->ESTTC_data));
    p_stack_entry->command = S_X_BAND_TRNSM_CMD_NUMBER;
    p_stack_entry->isFileCommand = false;
    p_stack_entry->type = 0;
    p_stack_entry->response = S_X_BAND_TRNSM_STAT_NUMBER;
    p_stack_entry->result = S_X_BAND_TRNSM_RET_RES_NUMBER;
    p_stack_entry->fileHandler = (uint32_t) -1;
    p_stack_entry->fileSize = 0;
    p_stack_entry->timestamp = 0;
    p_stack_entry->minDelay = 0;
    p_stack_entry->retries = 0;
    p_stack_entry->expectSlaveCommand = 0;
    p_stack_entry->pUserRespCtx = NULL;
    p_stack_entry->parentEntry = NULL;
}

/*!
*********************************************************************************************
* @brief Transfers the received SXBand data from the DMA buffer to the local data buffer
*          using a given DMA buffer offset
*********************************************************************************************
* @param[input]      offset - byte offset to use when copying data from the DMA buffer
* @return            none
*********************************************************************************************
*/
static void Transfer_Rx_Data_From_Offset(const uint32_t offset)
{
    memcpy(&(S_X_BAND_TRNSM_X_Band_Data[S_X_Band_Index * S_X_BAND_PACK_SIZE]), &S_X_BAND_DMA_Buffer[offset], S_X_BAND_PACK_SIZE);
    S_X_Band_Index++;

    uint32_t data_size = 18 + S_X_BAND_TRNSM_X_Band_Data[6] + S_X_BAND_TRNSM_X_Band_Data[7] * 256L;
    uint32_t pack_count = ((data_size % 16) == 0) ? (data_size / 16) : ((data_size / 16) + 1);
    if (S_X_Band_Index >= pack_count)
    {
        osThreadFlagsSet(S_X_BAND_Task_TaskHandle, S_X_BAND_TASK_DMA_FLAG);
    }
}

void S_X_BAND_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
    (void) huart;

    Transfer_Rx_Data_From_Offset(0U);
}

void S_X_BAND_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    (void) huart;

    Transfer_Rx_Data_From_Offset(S_X_BAND_PACK_SIZE);
}

void S_X_BAND_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    (void) huart;

    S_X_BAND_TRNSM_Rx_Tx_State (0);
}

void S_X_BAND_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    (void) huart;

    S_X_BAND_TRNSM_Rx_Tx_State (0);
}

/* ******************************************************************************************* */
