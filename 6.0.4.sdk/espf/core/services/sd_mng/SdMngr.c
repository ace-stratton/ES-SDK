/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup sd_mng
 * @{
 *
 * @file SdMngr.c
 *
 * @brief Manages common SD card functionalities and do some service operations
 *
 * @}
 *
 */

#include <SdMngr.h>
#include <cmsis_os2.h>
#include <TaskMonitor.h>
#include "es_cdef.h"
#include "es_exeh.h"
#include "string.h"
#include "ff_gen_drv.h"
#include "FileManager.h"
#include "limits.h"
#include "assertions.h"
#include "nvm.h"
#include "stdatomic.h"
#include "timer.h"

/*
 ********************************************************************************************
 * INTERNAL DEFINES
 ********************************************************************************************
 */
#define SDMNGR_EVENT_CARD_0_READY (1)

#define SDMNGR_MAX_RETRY         (3)   // number of retries for any failed operation
#define SDMNG_INIT_RETRY_TIMEOUT (100) // timeout after a failed init before attempting a new init

#define SDMNGR_MAX_IN_USE_TIMEOUT_MS (3000)                                                                          // should be a bit longer then max SD card timeout -> SD_TIMEOUT)
#define SDMNGR_MAX_REINIT_TIMEOUT_MS (SDMNGR_MAX_IN_USE_TIMEOUT_MS * SDMNGR_MAX_RETRY + 500)                         // should be a bit longer then max SD card timeout -> SD_TIMEOUT)
#define SDMNGR_MAX_FORMAT_TIMEOUT_MS (SDMNGR_MAX_IN_USE_TIMEOUT_MS + SDMMC_MAXERASETIMEOUT * SDMNGR_MAX_RETRY + 500) // max time it would take to wait for the sd card to finish whatever it was doing, + the max time to finish the formatting + some generic time(500 ms is more than enough) for the overhead

#define SDMNGT_TASK_TIME_CYCLE (2000)

#define SDMNGR_BLOCKING_REINIT_POLL_INTERVAL (10)  // ms to check for a sd card init complete
#define SDMNGR_BLOCKING_FORMAT_POLL_INTERVAL (100) // ms to check for a sd card format complete

#define SDMNG_LOCK_POLL_PERIOD (100)

#define SDMNGR_SIZEOF_PATH_DELIMITER (1)

#define PIN_STATE_FULL_CLEAR (0x00)
#define PIN_STATE_FULL_SET   (0xFF)
#define PIN_STATE_INIT       (0x55)
#define PIN_STATE_TIMEOUT_MS (5)

#define ALIGN_ATOMIC_4_BYTE __attribute__((aligned(4)))

#define SDMNG_TASK_STACK_SIZE 1280

/*
 * Helper functions
 *******************/
static int16_t ff_call_use_count;
static int16_t ff_call_use_max_value;

static inline void inc_ff_use_count(void)
{
    ff_call_use_count++;
    if (ff_call_use_max_value < ff_call_use_count)
    {
        ff_call_use_max_value = ff_call_use_count;
    }
}

static inline void dec_ff_use_count(void)
{
    CRIT_ASSERT(ff_call_use_count);
    ff_call_use_count--;
}

#define SDMNG_CHECK_NULL_PTR(ptr)        \
    do                                   \
    {                                    \
        if (NULL == ptr)                 \
        {                                \
            return FR_INVALID_PARAMETER; \
        }                                \
    } while (false)

#define SDMNG_CHECK_FRESULT(check)              \
    do                                          \
    {                                           \
        FRESULT fresult;                        \
        fresult = (check);                      \
        if (FR_OK != fresult)                   \
        {                                       \
            CRIT_ASSERT(FR_INT_ERR != fresult); \
            return fresult;                     \
        }                                       \
    } while (false)

#define SDMNG_USE_FF_API_AND_RETURN(apiStatement) \
    do                                            \
    {                                             \
        FRESULT fresult = FR_INT_ERR;             \
                                                  \
        inc_ff_use_count();                       \
                                                  \
        fresult = (apiStatement);                 \
                                                  \
        dec_ff_use_count();                       \
                                                  \
        if (fresult != FR_OK)                     \
        {                                         \
            HandleFFError(fresult);               \
        }                                         \
                                                  \
        return fresult;                           \
    } while (0)

static inline eSdMngr_partition_t fs_get_partition_id(const TCHAR *path);

/*
 * SD FORMAT STATUS VARIABLES
 ****************************/
static uint8_t                         b_SdMngr_sdCardReinitRequested;
static uint8_t                         b_SdMngr_sdCardReinitFinished;
static uint8_t                         b_SdMngr_Card_Eject_detected;
static osEventFlagsId_t                SdMngr_Event_SDReady;
static uint8_t                         SdMngr_formatBuffer[FF_MAX_SS];
SdMngr_cardStatus_enum                 eCardState              = SDMNGR_CARD_STATE_NOT_INIT;
static atomic_bool ALIGN_ATOMIC_4_BYTE b_sd_card_access_locked = true; // Protect the access to the fs while init or format the sd card
static const uint16_t                  wait_fs_free_timeout_ms = 2000; // in milliseconds
/*
 * SD_MNGR_FATFS_SDCARD_PARTITION PARAMETERS
 ********************************************/
/** Dynamic information */
static sSdMngr_partiton_dyn_data fatfs_dyn_data = { .b_is_format_requested = false,
                                                    .format_status         = FR_OK };

/** Description of all configured partitions */
static const sSdMngr_partition_info_t
    sSdMngr_partition_info[SD_MNGR_PARTITIONS_CNT] = {
        {.psFileSystem = &SDFatFS,
         .fs_type      = FS_TYPE_FATFS,
         .p_dyn_data   = &fatfs_dyn_data}
};
/** Partition mount names */
static const char *acMountPointNames[SD_MNGR_PARTITIONS_CNT] = {
    "/sd", // SD_MNGR_FATFS_SDCARD_PARTITION
};

/*
 * SD MNGR TASK DEFINITIONS
 **************************/
osThreadId_t                SdMngr_TaskHandle;
static const osThreadAttr_t SdMngr_attributes = {
    .name       = "SdMngr_Task",
    .priority   = (osPriority_t)osPriorityNormal,
    .stack_size = SDMNG_TASK_STACK_SIZE
};

static ff_stats_t statCounters;
static bool       bApiErrCountersChanged = false;

static void eject_detection_service(void);
static void handle_format_requests(void);
static void format_sd_card(sSdMngr_partition_info_t const *p_partition_info, uint8_t max_retries);
static void handle_sdcard_init(void);
static bool lock_fs(void); /** Return if the fs is locked successfully */
static void SdMngr_Task(void *argument);

/*
 * ERROR HANDLER DEFS
 ********************/
static void HandleFFError(FRESULT error);
static void SdMngr_BlockingWaitReinit(uint32_t maxMsToWait);
static void SdMngr_BlockingWaitFormat(eSdMngr_partition_t partition_id, uint32_t maxMsToWait);

/** @brief In case a new file has to be created this function is taking care of
 *  switching the context to the new file name. It takes into account all of the
 *  configurations for the file name and creates a proper one.
 *
 *  @param fp_psCtx : context of a rolling file name
 *  @return status of the operation
 */
static FRESULT rlf_SetNextFileName(sSdMngr_rlf_ctx_t *const fp_psCtx);

/** @brief This function is responsible to check the existing files and to initialize
 *  the context to the correct file which after that will be ready for writing.
 *
 *  @param fp_psCtx : context of a rolling file name. This context will be updated by
 *  the function.
 *  @return status of the operation
 */
static FRESULT rlf_GetInitialFileName(sSdMngr_rlf_ctx_t *const fp_psCtx);

/**
 * uint32_t*)
 * \brief Writing to rolling files. This function is checking if
 * current file is filled in and switches to next file if the space is not
 * enough. This is done until the needed bytes are written.
 *
 * \param fp_psCtx Context of a rolling file
 * \param fp_pBuff buffer to be written
 * \param fp_u32BytesToWrite number of bytes to write
 * \param fp_pu32BytesWritten number of bytes written to the rolling file.
 * \return Returns FR_OK if all the needed data is written correctly, otherwise
 * returns the error provided by SdMngr_f_write or rlf_SetNextFileName depending
 * on which of them is failing.
 */
static FRESULT rlf_WriteToFiles(sSdMngr_rlf_ctx_t *const fp_psCtx, const void *fp_pBuff, uint32_t fp_u32BytesToWrite, uint32_t *fp_pu32BytesWritten);

/*
 ********************************************************************************************
 * EXTERNAL (NONE STATIC) ROUTINES DEFINITION
 ********************************************************************************************
 */
void SdMngr_InitTask(void)
{
    SdMngr_Event_SDReady = osEventFlagsNew(NULL);

    for (uint8_t i = 0; i < SD_MNGR_PARTITIONS_CNT; i++)
    {
        sSdMngr_partition_info[i].p_dyn_data->b_is_format_requested = false;
        sSdMngr_partition_info[i].p_dyn_data->format_status         = FR_OK;
    }

    b_SdMngr_Card_Eject_detected = false;

    eCardState = SDMNGR_CARD_STATE_NOT_INIT;

    b_SdMngr_sdCardReinitRequested = true;
    b_SdMngr_sdCardReinitFinished  = true;
    b_sd_card_access_locked        = false;

    Nvm_GetBlockById(NVM_FF_STATS, &statCounters);

    SdMngr_TaskHandle = osThreadNew(SdMngr_Task, NULL, &SdMngr_attributes);
    CRIT_ASSERT(SdMngr_TaskHandle);
}

SdMngr_cardStatus_enum SdMngr_GetCardState(void)
{
    return eCardState;
}

void SD_Card_Eject_Detected(void)
{
    b_SdMngr_Card_Eject_detected = true;

    eCardState = SDMNGR_CARD_STATE_EJECTED;

    SdMngr_NotifyTaskFromISR();
}

bool SdMngr_RequestSdCardInit(bool blocking)
{
    bool b_retVal = true;

    b_SdMngr_sdCardReinitRequested = true;

    eCardState = SDMNGR_CARD_STATE_NOT_INIT;

    SdMngr_NotifyTask();

    if (blocking)
    {
        SdMngr_BlockingWaitReinit(SDMNGR_MAX_IN_USE_TIMEOUT_MS + SDMNGR_MAX_REINIT_TIMEOUT_MS);
        b_retVal = b_SdMngr_sdCardReinitFinished;
    }

    return b_retVal;
}

FRESULT SdMngr_RequestPartitionFormat(eSdMngr_partition_t partition_id, bool blocking)
{
    FRESULT retVal = FR_INVALID_PARAMETER;

    if (SD_MNGR_PARTITIONS_CNT > partition_id)
    {
        if (!sSdMngr_partition_info[partition_id].p_dyn_data->b_is_format_requested)
        {
            sSdMngr_partition_info[partition_id].p_dyn_data->b_is_format_requested = true;

            sSdMngr_partition_info[partition_id].p_dyn_data->format_status = FR_NO_FILESYSTEM;

            SdMngr_NotifyTask();

            if (blocking)
            {
                SdMngr_BlockingWaitFormat(partition_id, SDMNGR_MAX_FORMAT_TIMEOUT_MS);
                retVal = sSdMngr_partition_info[partition_id].p_dyn_data->format_status;
            }
            else
            {
                retVal = FR_OK;
            }
        }
    }

    return retVal;
}

void SdMngr_NotifyTaskFromISR(void)
{
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    vTaskNotifyGiveFromISR(SdMngr_TaskHandle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void SdMngr_NotifyTask(void)
{
    xTaskNotifyGive(SdMngr_TaskHandle);
}

uint16_t SdMngr_GetStatisticCounterById(FRESULT id)
{
    return (id < CDEF_ELEMENT_COUNT(statCounters.ff_api_err_counters))
               ? statCounters.ff_api_err_counters[(uint8_t)id]
               : 0U;
}

void SdMngr_GetRamStatisticCounters(sRamStats_t *const pStats)
{
    if (pStats != NULL)
    {
        taskENTER_CRITICAL();
        pStats->ff_call_use_count     = ff_call_use_count;
        pStats->ff_call_use_max_value = ff_call_use_max_value;
        taskEXIT_CRITICAL();
    }
}

void SdMngr_ClearStatisticCounters(void)
{
    ff_call_use_count     = 0U;
    ff_call_use_max_value = 0U;

    (void)memset(&statCounters, 0U, sizeof(statCounters));
    bApiErrCountersChanged = true;
}

const char *SdMngr_get_mnt_point_name(eSdMngr_partition_t partition_id)
{
    const char *name = NULL;
    if (partition_id < SD_MNGR_PARTITIONS_CNT)
    {
        name = acMountPointNames[partition_id];
    }
    return name;
}

eSdMngr_partition_t SdMngr_get_partition_id(const FIL *fp)
{
    eSdMngr_partition_t res = SD_MNGR_PARTITIONS_CNT;

    if ((NULL == fp) || (NULL == fp->obj.fs))
    {
        return SD_MNGR_PARTITIONS_CNT;
    }

    for (eSdMngr_partition_t i = 0; i < SD_MNGR_PARTITIONS_CNT; i++)
    {
        if (sSdMngr_partition_info[i].psFileSystem == fp->obj.fs)
        {
            res = i;
            break;
        }
    }

    return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

static inline eSdMngr_partition_t fs_eGetPartitionForPhysDrv(const Diskio_drvTypeDef *drv)
{
    eSdMngr_partition_t result = SD_MNGR_PARTITIONS_CNT;
    uint8_t             physDriveNumber;
    FRESULT             fr = FATFS_FindVolume(drv, &physDriveNumber);

    if (FR_OK == fr)
    {
        if (SD_MNGR_PARTITIONS_CNT > physDriveNumber)
        {
            result = (eSdMngr_partition_t)physDriveNumber;
        }
    }

    return result;
}

static inline FRESULT sdmng_check_card(void)
{
    if ((true == b_sd_card_access_locked) || (eCardState != SDMNGR_CARD_STATE_READY))
    {
        // TODO add a flag to check for in case of not ready
        //  flag is set on format/reinit
        //  if flag is set, then add a blocking wait for the
        //  sd card / format to finish
        return FR_DISK_ERR;
    }

    return FR_OK;
}

static FRESULT sdmng_check_partition(eSdMngr_partition_t partition_id)
{
    if (SD_MNGR_PARTITIONS_CNT <= partition_id)
    {
        return FR_INVALID_DRIVE;
    }

    if (FR_OK != sSdMngr_partition_info[partition_id].p_dyn_data->format_status)
    {
        // TODO see sdmng_check_card
        return FR_DISK_ERR;
    }

    return FR_OK;
}

static FRESULT sdmng_check_file(const FIL *fp)
{
    eSdMngr_partition_t partition_id = SD_MNGR_PARTITIONS_CNT;

    SDMNG_CHECK_NULL_PTR(fp);

    SDMNG_CHECK_NULL_PTR(fp->obj.fs);

    partition_id = fs_eGetPartitionForPhysDrv((fp->obj.fs)->drv);

    return sdmng_check_partition(partition_id);
}

static FRESULT sdmng_check_dir(const FF_DIR *dp)
{
    eSdMngr_partition_t partition_id = SD_MNGR_PARTITIONS_CNT;

    SDMNG_CHECK_NULL_PTR(dp);

    SDMNG_CHECK_NULL_PTR(dp->obj.fs);

    partition_id = fs_eGetPartitionForPhysDrv((dp->obj.fs)->drv);

    return sdmng_check_partition(partition_id);
}

static FRESULT sdmng_check_valid_mkfs_opt(BYTE opt)
{
    if ((0 != (FM_ANY & opt)) && (0 == (opt & (BYTE)(~(FM_ANY | FM_SFD)))))
    {
        return FR_OK;
    }
    return FR_INVALID_PARAMETER;
}

static FRESULT sdmng_get_partition_and_strip_path(const TCHAR **p_path, eSdMngr_partition_t *p_partition_id)
{
    eSdMngr_partition_t partition_id;
    const char         *mount_name    = NULL;
    TCHAR              *stripped_path = NULL;
    size_t              sz_mount_name = 0;
    size_t              sz_path       = 0;
    size_t              sz_full       = 0;

    SDMNG_CHECK_NULL_PTR(p_path);
    SDMNG_CHECK_NULL_PTR(*p_path);

    partition_id = fs_get_partition_id(*p_path);

    SDMNG_CHECK_FRESULT(sdmng_check_partition(partition_id));

    mount_name = SdMngr_get_mnt_point_name(partition_id);
    if (NULL == mount_name)
    {
        // sdmng_check_partition() validates the partition_id; this code here should not be reached
        return FR_INT_ERR;
    }

    *p_partition_id = partition_id;

    stripped_path = strnstr(*p_path, mount_name, strnlen(mount_name, FF_LFN_BUF));

    // if the name of the mount point is found in the beginning of the path
    if (*p_path == stripped_path)
    {
        stripped_path = stripped_path + strnlen(mount_name, FF_LFN_BUF);
        // When looking for second level elements, we must remove also the '/'
        //  after /sd/
        if ('/' == stripped_path[0])
        {
            stripped_path = stripped_path + 1;
        }

        *p_path = stripped_path;
    }

    sz_mount_name = strnlen(mount_name, FF_MAX_LFN);
    sz_path       = strnlen(*p_path, FF_MAX_LFN);
    sz_full       = sz_mount_name + SDMNGR_SIZEOF_PATH_DELIMITER + sz_path;
    if (FF_MAX_LFN <= sz_full)
    {
        return FR_INVALID_PARAMETER;
    }

    return FR_OK;
}

FRESULT SdMngr_f_open(FIL *fp, const TCHAR *path, const BYTE mode)
{
    eSdMngr_partition_t partition_id = SD_MNGR_PARTITIONS_CNT;

    SDMNG_CHECK_NULL_PTR(fp);

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_open(sSdMngr_partition_info[partition_id].psFileSystem, fp, path, mode));
}

FRESULT SdMngr_f_close(FIL *fp)
{
    SDMNG_CHECK_FRESULT(sdmng_check_file(fp));

    SDMNG_USE_FF_API_AND_RETURN(f_close(fp));
}

FRESULT SdMngr_f_read(FIL *fp, void *buff, UINT btr, UINT *br)
{
    UINT bytes_read = 0U;

    if (NULL == br)
    {
        br = &bytes_read;
    }

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_file(fp));

    SDMNG_USE_FF_API_AND_RETURN(f_read(fp, buff, btr, br));
}

FRESULT SdMngr_f_write(FIL *fp, const void *buff, UINT btw, UINT *bw)
{
    UINT bytes_written = 0U;

    if (NULL == bw)
    {
        bw = &bytes_written;
    }

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_file(fp));

    SDMNG_USE_FF_API_AND_RETURN(f_write(fp, buff, btw, bw));
}

FRESULT SdMngr_f_lseek(FIL *fp, FSIZE_t ofs)
{
    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_file(fp));

    SDMNG_USE_FF_API_AND_RETURN(f_lseek(fp, ofs));
}

FRESULT SdMngr_f_truncate(FIL *fp)
{
    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_file(fp));

    SDMNG_USE_FF_API_AND_RETURN(f_truncate(fp));
}

FRESULT SdMngr_f_sync(FIL *fp)
{
    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_file(fp));

    SDMNG_USE_FF_API_AND_RETURN(f_sync(fp));
}

FRESULT SdMngr_f_opendir(FF_DIR *dp, const TCHAR *path)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_NULL_PTR(dp);

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_opendir(sSdMngr_partition_info[partition_id].psFileSystem, dp, path));
}

FRESULT SdMngr_f_closedir(FF_DIR *dp)
{
    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_dir(dp));

    SDMNG_USE_FF_API_AND_RETURN(f_closedir(dp));
}

FRESULT SdMngr_f_readdir(FF_DIR *dp, FILINFO *fno)
{
    SDMNG_CHECK_NULL_PTR(fno);

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_dir(dp));

    SDMNG_USE_FF_API_AND_RETURN(f_readdir(dp, fno));
}

FRESULT SdMngr_f_findfirst(FF_DIR *dp, FILINFO *fno, const TCHAR *path,
                           const TCHAR *pattern)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_NULL_PTR(fno);
    SDMNG_CHECK_NULL_PTR(pattern);

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_findfirst(sSdMngr_partition_info[partition_id].psFileSystem, dp, fno, path, pattern));
}

FRESULT SdMngr_f_findnext(FF_DIR *dp, FILINFO *fno)
{
    SDMNG_CHECK_NULL_PTR(fno);

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_dir(dp));

    SDMNG_USE_FF_API_AND_RETURN(f_findnext(dp, fno));
}

FRESULT SdMngr_f_mkdir(const TCHAR *path)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_mkdir(sSdMngr_partition_info[partition_id].psFileSystem, path));
}

FRESULT SdMngr_f_unlink(const TCHAR *path)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_unlink(sSdMngr_partition_info[partition_id].psFileSystem, path));
}

FRESULT SdMngr_f_rename(const TCHAR *path_old, const TCHAR *path_new)
{
    eSdMngr_partition_t partition_id_old;
    eSdMngr_partition_t partition_id_new;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path_old, &partition_id_old));
    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path_new, &partition_id_new));

    if (partition_id_old != partition_id_new)
    {
        HandleFFError(FR_INVALID_DRIVE);
        return FR_INVALID_DRIVE;
    }

    SDMNG_USE_FF_API_AND_RETURN(f_rename(sSdMngr_partition_info[partition_id_old].psFileSystem, path_old, path_new));
}

FRESULT SdMngr_f_stat(const TCHAR *path, FILINFO *fno)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_stat(sSdMngr_partition_info[partition_id].psFileSystem, path, fno));
}

FRESULT SdMngr_f_chmod(const TCHAR *path, BYTE attr, BYTE mask)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_chmod(sSdMngr_partition_info[partition_id].psFileSystem, path, attr, mask));
}

FRESULT SdMngr_f_utime(const TCHAR *path, const FILINFO *fno)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_NULL_PTR(fno);

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_utime(sSdMngr_partition_info[partition_id].psFileSystem, path, fno));
}

FRESULT SdMngr_f_chdir(const TCHAR *path)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_chdir(sSdMngr_partition_info[partition_id].psFileSystem, path));
}

FRESULT SdMngr_f_chdrive(const TCHAR *path)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    // TODO implement support for multiple drives.

    return FR_INT_ERR;
}

FRESULT SdMngr_f_getfree(const TCHAR *path, DWORD *nclst, FATFS **fatfs)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_NULL_PTR(nclst);
    SDMNG_CHECK_NULL_PTR(fatfs);

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    *fatfs = sSdMngr_partition_info[partition_id].psFileSystem;

    SDMNG_USE_FF_API_AND_RETURN(f_getfree(sSdMngr_partition_info[partition_id].psFileSystem, nclst));
}

FRESULT SdMngr_f_mkfs(const TCHAR *path, BYTE opt, DWORD au, void *work, UINT len)
{
    eSdMngr_partition_t partition_id;

    SDMNG_CHECK_FRESULT(sdmng_check_card());

    SDMNG_CHECK_FRESULT(sdmng_check_valid_mkfs_opt(opt));

    SDMNG_CHECK_FRESULT(sdmng_get_partition_and_strip_path(&path, &partition_id));

    SDMNG_USE_FF_API_AND_RETURN(f_mkfs(sSdMngr_partition_info[partition_id].psFileSystem, opt, au, work, len));
}

int SdMngr_f_putc(TCHAR c, FIL *fp)
{
    int ret = 0;

    if ((FR_OK != sdmng_check_card()) || (FR_OK != sdmng_check_file(fp)))
    {
        return 0;
    }

    inc_ff_use_count();

    ret = f_putc(c, fp);

    dec_ff_use_count();

    return ret;
}

int SdMngr_f_puts(const TCHAR *str, FIL *fp)
{
    int ret = 0;

    if ((NULL == str) || (FR_OK != sdmng_check_card()) || (FR_OK != sdmng_check_file(fp)))
    {
        return 0;
    }

    inc_ff_use_count();

    ret = f_puts(str, fp);

    dec_ff_use_count();

    return ret;
}

TCHAR *SdMngr_f_gets(TCHAR *buff, int len, FIL *fp)
{
    TCHAR *ret = NULL;

    if ((NULL == buff) || (FR_OK != sdmng_check_card()) || (FR_OK != sdmng_check_file(fp)))
    {
        return NULL;
    }

    inc_ff_use_count();

    ret = f_gets(buff, len, fp);

    dec_ff_use_count();

    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

/*
 ********************************************************************************************
 * INTERNAL (STATIC) ROUTINES DEFINITION
 ********************************************************************************************
 */
/*!
 *********************************************************************************************
 * @brief Task routing that serves requests for Reinit, Format, Eject/Inserted card
 *********************************************************************************************
 * @param[input]      none
 * @param[output]     none
 * @return            none
 * @note              none
 *********************************************************************************************
 */
static void SdMngr_Task(void *argument)
{
    TaskMonitor_TaskInitialized(TASK_MONITOR_SD_MANAGER);

    for (;;)
    {
        eject_detection_service();

        if (bApiErrCountersChanged)
        {
            Nvm_SetBlockById(NVM_FF_STATS, &statCounters, NVMSETBLOCK_STORE_IMMEDIATELY);

            bApiErrCountersChanged = false;
        }

        if (eCardState != SDMNGR_CARD_STATE_READY)
        {
            handle_sdcard_init();
        }
        else
        {
            handle_format_requests();
        }

        (void)ulTaskNotifyTake(pdTRUE, SDMNGT_TASK_TIME_CYCLE);

        TaskMonitor_IamAlive(TASK_MONITOR_SD_MANAGER);
        vApplicationLowStackCheck(TASK_MONITOR_SD_MANAGER);
    }
}

FRESULT SdMngr_rlf_open(sSdMngr_rlf_ctx_t *const fp_psCtx)
{
    FRESULT res = FR_INT_ERR;

    if (NULL != fp_psCtx)
    {
        if (false == fp_psCtx->bIsFileOpened)
        {
            sSdMngr_rlf_cfg_t const *const cfg = fp_psCtx->psCfg;

            // it is not expected file name to be more than 255 symbols. This is
            // FATFS limitation. This is the reason to use 1 byte variable for
            // keeping the length of the name.
            uint8_t fn_len = (uint8_t)strlen(fp_psCtx->psCfg->acNamePattern);
            if ((cfg->u8IndexPos != cfg->u8MarkerPos) && (fn_len >= cfg->u8IndexPos) && (fn_len >= cfg->u8MarkerPos))
            {
                res = rlf_GetInitialFileName(fp_psCtx);
                if (FR_OK == res)
                {
                    fp_psCtx->bIsFileOpened = true;
                }
            }
            else
            {
                res = FR_INVALID_PARAMETER;
            }
        }
        else
        {
            res = FR_OK; // the file is already opened.
        }
    }
    else
    {
        res = FR_INVALID_PARAMETER;
    }

    if (res != FR_OK)
    {
        HandleFFError(res);
    }

    return res;
}

FRESULT SdMngr_rlf_close(sSdMngr_rlf_ctx_t *const fp_psCtx)
{
    FRESULT res = FR_INT_ERR;

    // Check SD Card is initialized and formatted
    if (b_sd_card_access_locked)
    {
        return FR_DISK_ERR;
    }

    if (NULL != fp_psCtx)
    {
        if (fp_psCtx->bIsFileOpened)
        {
            res                     = SdMngr_f_close(&fp_psCtx->sFileHnd);
            fp_psCtx->bIsFileOpened = false;
        }
        else
        {
            res = FR_NO_FILE;
        }
    }
    else
    {
        res = FR_INVALID_PARAMETER;
    }

    if (res != FR_OK)
    {
        HandleFFError(res);
    }

    return res;
}

FRESULT SdMngr_rlf_write(sSdMngr_rlf_ctx_t *const fp_psCtx, const void *fp_pBuff, UINT btw, UINT *bw)
{
    FRESULT res = FR_OK;

    if ((NULL != fp_psCtx) && (NULL != fp_pBuff) && (NULL != bw))
    {
        if (fp_psCtx->bIsFileOpened)
        {
            // make sure that the file is not already full
            if (fp_psCtx->psCfg->u32MaxSizeInBytes <= f_size(&fp_psCtx->sFileHnd))
            {
                res = rlf_SetNextFileName(fp_psCtx);
            }
            if (FR_OK == res)
            {
                // at this place most of the checks are already done so we can do the logic for writing.
                res = rlf_WriteToFiles(fp_psCtx, fp_pBuff, btw, (uint32_t *)bw);
            }
        }
        else
        {
            res = FR_NO_FILE;
        }
    }
    else
    {
        res = FR_INVALID_PARAMETER;
    }

    if (res != FR_OK)
    {
        HandleFFError(res);
    }

    return res;
}

/**
 * @brief Handle errors from the SD card and increase respective statistics counter
 * @param[input]      error - the error to be handled
 */
static void HandleFFError(FRESULT error)
{
    static const eEXEHSeverityLevel_t severity[FFAPIERR_MAX_CNT] = { eEXEHSeverity_Error,   // FR_OK
                                                                     eEXEHSeverity_Error,   // FR_DISK_ERR
                                                                     eEXEHSeverity_Fatal,   // FR_INT_ERR
                                                                     eEXEHSeverity_Error,   // FR_NOT_READY
                                                                     eEXEHSeverity_Warning, // FR_NO_FILE
                                                                     eEXEHSeverity_Warning, // FR_NO_PATH
                                                                     eEXEHSeverity_Warning, // FR_INVALID_NAME
                                                                     eEXEHSeverity_Warning, // FR_DENIED
                                                                     eEXEHSeverity_Warning, // FR_EXIST
                                                                     eEXEHSeverity_Warning, // FR_INVALID_OBJECT
                                                                     eEXEHSeverity_Warning, // FR_WRITE_PROTECTED
                                                                     eEXEHSeverity_Warning, // FR_INVALID_DRIVE
                                                                     eEXEHSeverity_Error,   // FR_NOT_ENABLED
                                                                     eEXEHSeverity_Error,   // FR_NO_FILESYSTEM
                                                                     eEXEHSeverity_Error,   // FR_MKFS_ABORTED
                                                                     eEXEHSeverity_Error,   // FR_TIMEOUT
                                                                     eEXEHSeverity_Error,   // FR_LOCKED
                                                                     eEXEHSeverity_Error,   // FR_NOT_ENOUGH_CORE
                                                                     eEXEHSeverity_Error,   // FR_TOO_MANY_OPEN_FILES
                                                                     eEXEHSeverity_Error }; // FR_INVALID_PARAMETER

    // no need to use a mutex here as reads and writes of the counters are atomic
    if (FFAPIERR_MAX_CNT > error)
    {
        if (statCounters.ff_api_err_counters[error] < USHRT_MAX)
        {
            statCounters.ff_api_err_counters[error]++;
            bApiErrCountersChanged = true;
            // eEXEH_SDMNGR_ExceptionID_t mirrors the values of FRESULT, see definitions
            EXEH_vException(severity[error], eEXEHModuleID_SDMNGR, (int32_t)error, __LINE__);
        }
    }
    else
    {
        Error_Handler();
    }
}

/*!
 *********************************************************************************************
 * @brief
 *********************************************************************************************
 * @param[input]      path - path to the file/directory used for last operation
 * @return            eSdMngr_partition_t: id of the partition
 *********************************************************************************************
 */
static inline eSdMngr_partition_t fs_get_partition_id(const TCHAR *path)
{
    eSdMngr_partition_t res = SD_MNGR_PARTITIONS_CNT;

    if (path != NULL)
    {
        if ('/' == path[0])
        {
            int32_t result;
            if (SD_MNGR_PARTITIONS_CNT > 0)
            {
                uint8_t partition_id = (uint8_t)SD_MNGR_PARTITIONS_CNT;
                size_t  sz_partition_name;
                do
                {
                    partition_id--;
                    result            = 1; // return value of '1' from strncmp means nomatch
                    sz_partition_name = strnlen(acMountPointNames[partition_id], FF_LFN_BUF);
                    if (('\0' == path[sz_partition_name]) || ('/' == path[sz_partition_name]))
                    {
                        result = strncmp(path, acMountPointNames[partition_id], sz_partition_name);
                    }
                } while ((0 != result) && (0U != partition_id));

                if (0 == result)
                {
                    res = partition_id;
                }
            }
        }
        else
        {
            // by default return FATFS SDCARD partition
            res = SD_MNGR_FATFS_SDCARD_PARTITION;
        }
    }

    return res;
}

/*!
 * @brief       Waits to finish the already requested ReInit of a SD card
 * @param[in]   maxMsToWait The maximum wait for the Reinit operation to finish.
 */
static void SdMngr_BlockingWaitReinit(const uint32_t max_ms_time_to_wait)
{
    timer_handle_t th;
    timer_start(&th);

    while (!timer_is_elapsed(&th, max_ms_time_to_wait) && b_SdMngr_sdCardReinitRequested)
    {
        osDelay(SDMNGR_BLOCKING_REINIT_POLL_INTERVAL);
    }
}

/**
 * @brief Waits to finish the already requested Format of a SD card
 * @param partition_id Partition to be waited for
 * @param max_ms_to_wait maximum time in ms to wait for the partition to be ready
 */
static void SdMngr_BlockingWaitFormat(eSdMngr_partition_t partition_id, uint32_t maxMsToWait)
{
    const uint32_t wait_till = osKernelGetTickCount() + maxMsToWait;

    while (wait_till > osKernelGetTickCount())
    {
        if (false == sSdMngr_partition_info[partition_id].p_dyn_data->b_is_format_requested)
        {
            break;
        }
        osDelay(SDMNGR_BLOCKING_FORMAT_POLL_INTERVAL);
    }
}

static FRESULT rlf_SetNextFileName(sSdMngr_rlf_ctx_t *const fp_psCtx)
{
    FRESULT res = FR_INT_ERR;

    // Check SD Card is initialized and formatted
    if (b_sd_card_access_locked)
    {
        return FR_DISK_ERR;
    }

    if (NULL != fp_psCtx)
    {
        if (true == fp_psCtx->bIsFileOpened)
        {
            char file_name_temp[FF_MAX_LFN];

            (void)SdMngr_f_close(&fp_psCtx->sFileHnd);

            (void)strncpy(file_name_temp, fp_psCtx->acFileName, FF_MAX_LFN);

            // preserve the existing file under a different name
            file_name_temp[fp_psCtx->psCfg->u8MarkerPos] = fp_psCtx->psCfg->cInactiveMarker;
            // delete any old dump with the same name...
            (void)SdMngr_f_unlink(file_name_temp);
            // rename current dump
            (void)SdMngr_f_rename(fp_psCtx->acFileName, file_name_temp);

            fp_psCtx->u8CurrentIdx += 1U;

            // move index position for new file and mark it as active
            fp_psCtx->acFileName[fp_psCtx->psCfg->u8IndexPos] = '0' + (fp_psCtx->u8CurrentIdx % fp_psCtx->psCfg->u8FilesCount);

            res = SdMngr_f_open(&fp_psCtx->sFileHnd, fp_psCtx->acFileName, FA_WRITE | FA_CREATE_ALWAYS);

            if (FR_OK == res)
            {
                fp_psCtx->bIsFileOpened = true;
            }
        }
        else
        {
            res = FR_NO_FILE;
        }
    }
    else
    {
        res = FR_INVALID_PARAMETER;
    }

    return res;
}

static FRESULT rlf_GetInitialFileName(sSdMngr_rlf_ctx_t *const fp_psCtx)
{
    FRESULT res = FR_INT_ERR;
    FILINFO fInfo;

    (void)strncpy(fp_psCtx->acFileName, fp_psCtx->psCfg->acNamePattern, FF_MAX_LFN);

    // try to determine the next file name to use for writing...
    // the currently active file ends with an "cActiveMarker", while older dumps end with an "cInactiveMarker"
    bool bFreeSlotFound                                = false;
    fp_psCtx->acFileName[fp_psCtx->psCfg->u8MarkerPos] = fp_psCtx->psCfg->cActiveMarker;

    for (uint8_t fileId = 0U; fileId < fp_psCtx->psCfg->u8FilesCount; fileId++)
    {
        fp_psCtx->acFileName[fp_psCtx->psCfg->u8IndexPos] = (uint8_t)('0' + fileId);

        res = SdMngr_f_stat(fp_psCtx->acFileName, &fInfo);
        if (FR_OK == res)
        {
            bFreeSlotFound         = true;
            fp_psCtx->u8CurrentIdx = fileId;
            break;
        }
    }

    // if no active slot found, use zero slot...
    if (!bFreeSlotFound)
    {
        fp_psCtx->acFileName[fp_psCtx->psCfg->u8IndexPos] = (uint8_t)'0';
    }

    res = SdMngr_f_open(&fp_psCtx->sFileHnd, fp_psCtx->acFileName, FA_WRITE | FA_OPEN_APPEND);

    return res;
}

static FRESULT rlf_WriteToFiles(sSdMngr_rlf_ctx_t *const fp_psCtx,
                                const void              *fp_pBuff,
                                uint32_t                 fp_u32BytesToWrite,
                                uint32_t                *fp_pu32BytesWritten)
{
    const uint8_t *pu8BuffStart    = fp_pBuff;
    FRESULT        res             = FR_INT_ERR;
    uint32_t       u32BytesToWrite = fp_u32BytesToWrite;
    *fp_pu32BytesWritten           = 0;

    do
    {
        uint32_t u32FreeFileSize              = fp_psCtx->psCfg->u32MaxSizeInBytes - f_size(&fp_psCtx->sFileHnd);
        uint32_t u32BytesToWriteInCurrentFile = 0;
        uint32_t u32BytesWrittenInCurrentFile = 0;

        if (u32BytesToWrite < u32FreeFileSize)
        {
            u32BytesToWriteInCurrentFile = u32BytesToWrite;
        }
        else
        {
            u32BytesToWriteInCurrentFile = u32FreeFileSize;
        }

        res = SdMngr_f_write(&fp_psCtx->sFileHnd, pu8BuffStart, u32BytesToWriteInCurrentFile, (UINT *)&u32BytesWrittenInCurrentFile);

        if (FR_OK == res)
        {
            u32BytesToWrite -= u32BytesWrittenInCurrentFile;
            pu8BuffStart += u32BytesWrittenInCurrentFile;
            *fp_pu32BytesWritten += u32BytesWrittenInCurrentFile;

            if (u32BytesToWrite > 0)
            {
                res = rlf_SetNextFileName(fp_psCtx);
            }
        }
    } while ((u32BytesToWrite != 0) && (res == FR_OK));

    return res;
}

/**
 * @brief Checking if any SD card is ejected and inserted again.
 */
static void eject_detection_service(void)
{
    GPIO_TypeDef *GPIOx;
    uint16_t      GPIO_Pin;
    SD_TypeDef   *Instance;

    uint8_t filtered_pin_state = PIN_STATE_INIT;
    if (b_SdMngr_Card_Eject_detected) // Is the card ejected or inserted in
                                      // the slot
    {
        GPIOx    = SD_DET_GPIO_Port;
        GPIO_Pin = SD_DET_Pin;
        Instance = hsd1.Instance;

        do
        {
            filtered_pin_state <<= 1;
            filtered_pin_state |= HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
            osDelay(PIN_STATE_TIMEOUT_MS);
        } while ((PIN_STATE_FULL_CLEAR != filtered_pin_state) && (PIN_STATE_FULL_SET != filtered_pin_state));

        if ((PIN_STATE_FULL_SET == filtered_pin_state) && (FR_OK != SDMMC_CmdReadSingleBlock(Instance, 0)))
        {
            b_SdMngr_sdCardReinitRequested = true;
        }

        b_SdMngr_Card_Eject_detected = false;
    }
}

/**
 * @brief Check and process any SD Card format requests.
 */
static void handle_format_requests(void)
{
    for (uint8_t partition_id = 0; partition_id < SD_MNGR_PARTITIONS_CNT;
         partition_id++)
    {
        if ((sSdMngr_partition_info[partition_id].p_dyn_data->b_is_format_requested) && (sSdMngr_partition_info[partition_id].fs_type == FS_TYPE_FATFS))
        {
            format_sd_card(&sSdMngr_partition_info[partition_id], SDMNGR_MAX_RETRY);
        }
    }
}

static void format_sd_card(sSdMngr_partition_info_t const *p_partition_info, uint8_t max_retries)
{
    b_sd_card_access_locked = true;

    if (!lock_fs())
    {
        // Free the sd card if we failed to lock the fs
        b_SdMngr_sdCardReinitRequested = false;
        b_sd_card_access_locked        = false;
        return;
    }

    uint8_t n_retries = max_retries;
    eCardState        = SDMNGR_CARD_STATE_NOT_INIT;
    while (n_retries > 0)
    {
        // Try to format the file system
        p_partition_info->p_dyn_data->format_status = f_mkfs(p_partition_info->psFileSystem, FM_FAT32, 0, SdMngr_formatBuffer, FF_MAX_SS);
        if (FR_OK == p_partition_info->p_dyn_data->format_status)
        {
            p_partition_info->p_dyn_data->b_is_format_requested = false;
            b_sd_card_access_locked                             = false;
            break;
        }
        else
        {
            // If mkfs fails try reinitializing the SD Card peripheral
            b_SdMngr_sdCardReinitFinished = (MCU_InitSdCard(SD_MNGR_CARD_0, pdFALSE) & SD_MNGR_CARD_0);
            if (!b_SdMngr_sdCardReinitFinished)
            {
                // Try again with HW reset
                b_SdMngr_sdCardReinitFinished = (MCU_InitSdCard(SD_MNGR_CARD_0, pdTRUE) & SD_MNGR_CARD_0);
            }
        }

        // Avoid Task Monitor resets while formating
        TaskMonitor_IamAlive(TASK_MONITOR_SD_MANAGER);
        n_retries--;
    }

    // If all the tries failed, report the error and unlock the card access
    if (b_sd_card_access_locked)
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_SDMNGR, eEXEH_SDMNGR_EXCEPTION_FORMAT_FAILED, __LINE__);
        p_partition_info->p_dyn_data->b_is_format_requested = false;
        b_sd_card_access_locked                             = false;
    }
}

/**
 * @brief Check and process any SD Card init requests.
 */
static void handle_sdcard_init(void)
{
    b_sd_card_access_locked = true;

    if (!lock_fs())
    {
        // Free the sd card if we failed to lock the fs
        b_SdMngr_sdCardReinitRequested = false;
        b_sd_card_access_locked        = false;
        return;
    }

    uint8_t n_retries = SDMNGR_MAX_RETRY;
    while (n_retries > 0)
    {
        b_SdMngr_sdCardReinitFinished = MCU_InitSdCard(SD_MNGR_CARD_0, pdTRUE) & SD_MNGR_CARD_0;

        if (b_SdMngr_sdCardReinitFinished)
        {
            eCardState = SDMNGR_CARD_STATE_READY;
            osEventFlagsSet(SdMngr_Event_SDReady, SDMNGR_EVENT_CARD_0_READY);
            b_SdMngr_Card_Eject_detected   = false; // Clear the flags
            b_SdMngr_sdCardReinitRequested = false;
            b_sd_card_access_locked        = false;
            break;
        }
        else
        {
            osDelay(SDMNG_INIT_RETRY_TIMEOUT);
        }

        TaskMonitor_IamAlive(TASK_MONITOR_SD_MANAGER);
        n_retries--;
    }

    // If all the tries failed, report the error and unlock the card access
    if (b_sd_card_access_locked)
    {
        EXEH_vException(eEXEHSeverity_Error, eEXEHModuleID_SDMNGR, eEXEH_SDMNGR_EXCEPTION_INIT_FAILED, __LINE__);
        b_SdMngr_Card_Eject_detected   = false; // Clear the flags
        b_SdMngr_sdCardReinitRequested = false;
        b_sd_card_access_locked        = false;
    }
}

static bool lock_fs(void)
{
    // Wait until the fs is free
    timer_handle_t timeout = { 0, SAFE_FALSE };
    timer_start(&timeout);
    while (ff_call_use_count > 0)
    {
        if (timer_is_elapsed(&timeout, wait_fs_free_timeout_ms))
        {
            return false;
        }
        osDelay(SDMNG_LOCK_POLL_PERIOD);
    }
    return true;
}
