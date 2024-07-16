/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include "cubeadcs_gen2_transfer.h"
#include "cubeadcs_gen2_gw.h"
#include "cubeadcs_gen2_types.h"
#include "assertions.h"
#include "TaskMonitor.h"
#include "SdMngr.h"
#include "cmsis_os2.h"
#include <cubeObc/arch/cubeObc_critical.h>
#include <string.h>


/** @brief flag used to signal main task for upload/download requests */
#define FS_START_TRANSFER_FLAG (0x01)

/** @brief mutex acquire timeout */
#define FS_LOCK_TIMEOUT        (0)



/** @brief lock to prevent concurrent file uploads/downloads */
static osMutexId_t fs_lock = NULL;

/** @brief upload/download task handle */
static osThreadId_t fs_task  = NULL;

/** @brief event download parameters */
static cubeadcs_gen2_transfer_evt_status_t fs_evt = { 0 };

/** @brief telemetry download parameters */
static cubeadcs_gen2_transfer_tlm_status_t fs_tlm = { 0 };

/** @brief stored image download parameters */
static cubeadcs_gen2_transfer_img_stored_status_t fs_img_stored = { 0 };

/** @brief bootloader cube space file upload parameters */
static cubeadcs_gen2_transfer_boot_cube_space_file_status_t fs_csf_bl = { 0 };

/** @brief application cube space file upload parameters */
static cubeadcs_gen2_transfer_appl_cube_space_file_status_t fs_csf_ap = { 0 };

/** @brief used to keep the ongoing file transfer context information */
static cubeadcs_gen2_file_context_t fs_file_ctx;


static void fs_transfer_task(void* args);


ErrorCode cubeadcs_gen2_transfer_init(void)
{
    ErrorCode ret = CUBEOBC_ERROR_OK;

    if (NULL == fs_lock)
    {
        fs_evt.err_code = CUBEOBC_ERROR_USAGE;
        fs_tlm.err_code = CUBEOBC_ERROR_USAGE;
        fs_img_stored.err_code = CUBEOBC_ERROR_USAGE;
        fs_csf_bl.err_code = CUBEOBC_ERROR_USAGE;
        fs_csf_ap.err_code = CUBEOBC_ERROR_USAGE;

        osMutexAttr_t attr =
        {
            .name      = "cube_transfer",
            .attr_bits = osMutexRecursive | osMutexPrioInherit,
            .cb_mem    = NULL,
            .cb_size   = 0U
        };

        fs_lock = osMutexNew(&attr);

        if (NULL == fs_lock)
        {
            ret = CUBEOBC_ERROR_USAGE;
        }
    }

    if ((CUBEOBC_ERROR_OK == ret) && (NULL == fs_task))
    {
        osThreadAttr_t attr =
        {
            .attr_bits  = osThreadDetached,
            .name       = "cube_transfer",
            .priority   = osPriorityNormal,
            .cb_mem     = NULL,
            .cb_size    = 0U,
            .stack_mem  = NULL,
            .stack_size = 2048,
            .tz_module  = 0U,
            .reserved   = 0U,
        };

        fs_task = osThreadNew(fs_transfer_task, NULL, &attr);

        if (NULL == fs_task)
        {
            ret = CUBEOBC_ERROR_USAGE;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_evt(const char* file_name, const TctlmCubeComputerCommon3_EventLogFilterTransferSetup* setup)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;
    uint32_t len = strnlen(file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ);

    if ((NULL != file_name) &&
        (0 < len) &&
        (NULL != setup))
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memset(&fs_evt, 0, sizeof(fs_evt));
            memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));
            memcpy(fs_evt.file_name, file_name, len);
            memcpy(&fs_evt.setup, setup, sizeof(fs_evt.setup));

            // null termination already added by memset()
            memcpy(fs_file_ctx.file_name, file_name, len);

            fs_file_ctx.context = CUBEADCS_GEN2_BDT_CTX_EVT_CC;

            // create the file
            if (FR_OK == SdMngr_f_open(&fs_file_ctx.file_handle, fs_file_ctx.file_name, FA_CREATE_ALWAYS | FA_WRITE))
            {
                ret = CUBEOBC_ERROR_OK;

                (void)SdMngr_f_close(&fs_file_ctx.file_handle);
                (void)osThreadFlagsSet(fs_task, FS_START_TRANSFER_FLAG);
            }
            else
            {
                ret = CUBEOBC_ERROR_UNKNOWN;
            }

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_evt_status(cubeadcs_gen2_transfer_evt_status_t* status)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;

    if (NULL != status)
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memcpy(status, &fs_evt, sizeof(fs_evt));

            ret = CUBEOBC_ERROR_OK;

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_tlm(const char* file_name, const TctlmCubeComputerCommon3_TelemetryLogTransferSetup* setup)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;
    uint32_t len = strnlen(file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ);

    if ((NULL != file_name) &&
        (0 < len) &&
        (NULL != setup))
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memset(&fs_tlm, 0, sizeof(fs_tlm));
            memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));
            memcpy(fs_tlm.file_name, file_name, len);
            memcpy(&fs_tlm.setup, setup, sizeof(fs_tlm.setup));

            // null termination already added by memset()
            memcpy(fs_file_ctx.file_name, file_name, len);

            fs_file_ctx.context = CUBEADCS_GEN2_BDT_CTX_TLM_CC;

            // create the file
            if (FR_OK == SdMngr_f_open(&fs_file_ctx.file_handle, fs_file_ctx.file_name, FA_CREATE_ALWAYS | FA_WRITE))
            {
                ret = CUBEOBC_ERROR_OK;

                (void)SdMngr_f_close(&fs_file_ctx.file_handle);
                (void)osThreadFlagsSet(fs_task, FS_START_TRANSFER_FLAG);
            }
            else
            {
                ret = CUBEOBC_ERROR_UNKNOWN;
            }

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_tlm_status(cubeadcs_gen2_transfer_tlm_status_t* status)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;

    if (NULL != status)
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memcpy(status, &fs_tlm, sizeof(fs_tlm));

            ret = CUBEOBC_ERROR_OK;

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_img_stored(const char* file_name, const U32 file_handle)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;
    uint32_t len = strnlen(file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ);

    if ((NULL != file_name) &&
        (0 < len))
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memset(&fs_img_stored, 0, sizeof(fs_img_stored));
            memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));
            memcpy(fs_img_stored.file_name, file_name, len);

            // null termination already added by memset()
            memcpy(fs_file_ctx.file_name, file_name, len);

            fs_file_ctx.context = CUBEADCS_GEN2_BDT_CTX_TLM_CC;
            fs_img_stored.setup = file_handle;

            // create the file
            if (FR_OK == SdMngr_f_open(&fs_file_ctx.file_handle, fs_file_ctx.file_name, FA_CREATE_ALWAYS | FA_WRITE))
            {
                ret = CUBEOBC_ERROR_OK;

                (void)SdMngr_f_close(&fs_file_ctx.file_handle);
                (void)osThreadFlagsSet(fs_task, FS_START_TRANSFER_FLAG);
            }
            else
            {
                ret = CUBEOBC_ERROR_UNKNOWN;
            }

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_img_stored_status(cubeadcs_gen2_transfer_img_stored_status_t* status)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;

    if (NULL != status)
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memcpy(status, &fs_img_stored, sizeof(fs_img_stored));

            ret = CUBEOBC_ERROR_OK;

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_boot_cube_space_file(
       const char* cp_file_name,
       const char* cfg_file_name,
       const bool force)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;
    uint32_t cp_len = strnlen(cp_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ);
    uint32_t cfg_len = strnlen(cfg_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ);

    if ((NULL != cp_file_name) && (0 < cp_len) &&
        (NULL != cfg_file_name) && (0 < cfg_len))
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memset(&fs_csf_bl, 0, sizeof(fs_csf_bl));
            memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));

            // null termination already added by memset()
            memcpy(fs_csf_bl.cp_file_name, cp_file_name, cp_len);
            memcpy(fs_csf_bl.cfg_file_name, cfg_file_name, cfg_len);

            fs_file_ctx.context = CUBEADCS_GEN2_BDT_CTX_FTP_BL;
            fs_csf_bl.force = force;

            ret = CUBEOBC_ERROR_OK;

            (void)osThreadFlagsSet(fs_task, FS_START_TRANSFER_FLAG);
            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_boot_cube_space_file_status(cubeadcs_gen2_transfer_boot_cube_space_file_status_t* status)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;

    if (NULL != status)
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memcpy(status, &fs_csf_bl, sizeof(fs_csf_bl));

            ret = CUBEOBC_ERROR_OK;

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_appl_cube_space_file(
        const char* cp_file_name,
        const char* cfg_file_name,
        const bool force,
        TctlmCommonFrameworkEnums_NodeType node_type,
        U32 serial_int)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;
    uint32_t cp_len = strnlen(cp_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ);
    uint32_t cfg_len = strnlen(cfg_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ);

    if ((NULL != cp_file_name) && (0 < cp_len) &&
        (NULL != cfg_file_name) && (0 < cfg_len))
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memset(&fs_csf_ap, 0, sizeof(fs_csf_ap));
            memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));

            // null termination already added by memset()
            memcpy(fs_csf_ap.cp_file_name, cp_file_name, cp_len);
            memcpy(fs_csf_ap.cfg_file_name, cfg_file_name, cfg_len);

            fs_file_ctx.context = CUBEADCS_GEN2_BDT_CTX_FTP_AP;
            fs_csf_ap.force = force;
            fs_csf_ap.node_type = node_type;
            fs_csf_ap.serial_int = serial_int;

            ret = CUBEOBC_ERROR_OK;

            (void)osThreadFlagsSet(fs_task, FS_START_TRANSFER_FLAG);
            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


ErrorCode cubeadcs_gen2_transfer_appl_cube_space_file_status(cubeadcs_gen2_transfer_appl_cube_space_file_status_t* status)
{
    ErrorCode ret = CUBEOBC_ERROR_USAGE;

    if (NULL != status)
    {
        if (osOK == osMutexAcquire(fs_lock, FS_LOCK_TIMEOUT))
        {
            memcpy(status, &fs_csf_ap, sizeof(fs_csf_ap));

            ret = CUBEOBC_ERROR_OK;

            (void)osMutexRelease(fs_lock);
        }
        else
        {
            ret = CUBEOBC_ERROR_BUSY;
        }
    }

    return ret;
}


/**
 * @brief Performs blocking upload of cube space files to the bootloader
 *
 * @return @ref ErrorCode
 */
static ErrorCode fs_start_blocking_upload_to_boot(TypeDef_TctlmEndpoint* endpoint)
{
    CRIT_ASSERT(NULL != endpoint);

    ErrorCode status;
    FILINFO fno_cp;
    FILINFO fno_cfg;
    TctlmCommonFramework1_Identification identity;

    // Check if the file exists in OBC.
    // Since we are uploading, it must exist in our file system.
    if (FR_OK != SdMngr_f_stat(fs_csf_bl.cp_file_name, &fno_cp))
    {
        // The file doesn't exist...
        status = CUBEOBC_ERROR_EXIST;
    }
    else
    {
        // The file exists, we can continue with next steps.
        status = CUBEOBC_ERROR_OK;
    }

    // Check if the file exists in OBC.
    // Since we are uploading, it must exist in our file system.
    if (CUBEOBC_ERROR_OK == status)
    {
        if (FR_OK != SdMngr_f_stat(fs_csf_bl.cfg_file_name, &fno_cfg))
        {
            // The file doesn't exist...
            status = CUBEOBC_ERROR_EXIST;
        }
        else
        {
            // The file exists, we can continue with next steps.
            status = CUBEOBC_ERROR_OK;
        }
    }

    if (CUBEOBC_ERROR_OK == status)
    {
        status = CubeADCS_Gen2_CommonFramework1_getIdentificationRequestGw(
            TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &identity, CUBEOBC_CRITICAL_WAIT_FOREVER);
    }

    if ((CUBEOBC_ERROR_OK == status) &&
        (TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_BOOTLOADER == identity.programType))
    {
        // we are already in bootloader. go directly to upload.
    }
    else if ((CUBEOBC_ERROR_OK == status) &&
             (true == fs_csf_bl.force) &&
             (TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_CONTROL == identity.programType))
    {
        // reset to bootloader
        (void)CubeADCS_Gen2_CommonFramework1_setResetRequestGw(
            TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, TCTLM_COMMON_FRAMEWORK_1__SOFT, CUBEOBC_CRITICAL_WAIT_FOREVER);

        // wait for boot
        cubeObc_time_delay(1000u);

        status = CubeADCS_Gen2_CommonFramework1_getIdentificationRequestGw(
            TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &identity, CUBEOBC_CRITICAL_WAIT_FOREVER);

        if ((CUBEOBC_ERROR_OK == status) &&
            ((TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER != identity.nodeType) ||
             (TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_BOOTLOADER != identity.programType)))
        {
            // failed to enter bootloader
            status = CUBEOBC_ERROR_UNKNOWN;
        }

        if (CUBEOBC_ERROR_OK == status)
        {
            // stay in bootloader. do not jump to application
            status = CubeADCS_Gen2_CubeCommonBaseBootloader5_setHaltRequestGw(
                TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, CUBEOBC_CRITICAL_WAIT_FOREVER);
        }
    }
    else if (CUBEOBC_ERROR_OK == status)
    {
        // we do not support uploads in any other program type
        status = CUBEOBC_ERROR_UNKNOWN;
    }
    else
    {
        // nothing to do
    }

    // save context type
    U32 ctx = fs_file_ctx.context;

    if (CUBEOBC_ERROR_OK == status)
    {
        // reset whole file context
        memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));

        (void)memcpy(
            fs_file_ctx.file_name,
            fs_csf_bl.cp_file_name,
            strnlen(fs_csf_bl.cp_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ));

        // restore context type
        fs_file_ctx.context = ctx;

        status = cubeObc_bootloader_uploadCubeSpaceFile(
            endpoint, fno_cp.fsize, &fs_file_ctx, &fs_csf_bl.status);
    }

    if (CUBEOBC_ERROR_OK == status)
    {
        // reset whole file context
        memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));

        (void)memcpy(
            fs_file_ctx.file_name,
            fs_csf_bl.cfg_file_name,
            strnlen(fs_csf_bl.cfg_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ));

        // restore context type
        fs_file_ctx.context = ctx;

        status = cubeObc_bootloader_uploadCubeSpaceFile(
            endpoint, fno_cfg.fsize, &fs_file_ctx, &fs_csf_bl.status);
    }

    if ((CUBEOBC_ERROR_OK == status) && (CUBEOBC_ERROR_OK == fs_csf_bl.status.result))
    {
        status = CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultAppRequestGw(
            TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, CUBEOBC_CRITICAL_WAIT_FOREVER);
    }

    return status;
}


/**
 * @brief Performs blocking upload of cube space files to the application
 *
 * @return @ref ErrorCode
 */
static ErrorCode fs_start_blocking_upload_to_appl(TypeDef_TctlmEndpoint* endpoint)
{
    CRIT_ASSERT(NULL != endpoint);

    ErrorCode status;
    FILINFO fno_cp;
    FILINFO fno_cfg;
    TctlmCommonFramework1_Identification identity;

    // Check if the file exists in OBC.
    // Since we are uploading, it must exist in our file system.
    if (FR_OK != SdMngr_f_stat(fs_csf_ap.cp_file_name, &fno_cp))
    {
        // The file doesn't exist...
        status = CUBEOBC_ERROR_EXIST;
    }
    else
    {
        // The file exists, we can continue with next steps.
        status = CUBEOBC_ERROR_OK;
    }

    // Check if the file exists in OBC.
    // Since we are uploading, it must exist in our file system.
    if (CUBEOBC_ERROR_OK == status)
    {
        if (FR_OK != SdMngr_f_stat(fs_csf_ap.cfg_file_name, &fno_cfg))
        {
            // The file doesn't exist...
            status = CUBEOBC_ERROR_EXIST;
        }
        else
        {
            // The file exists, we can continue with next steps.
            status = CUBEOBC_ERROR_OK;
        }
    }

    if (CUBEOBC_ERROR_OK == status)
    {
        status = CubeADCS_Gen2_CommonFramework1_getIdentificationRequestGw(
            TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &identity, CUBEOBC_CRITICAL_WAIT_FOREVER);
    }

    if ((CUBEOBC_ERROR_OK == status) &&
        (TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_CONTROL == identity.programType))
    {
        // we are already in application. go directly to upload.
    }
    else if ((CUBEOBC_ERROR_OK == status) &&
             (true == fs_csf_ap.force) &&
             (TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_BOOTLOADER == identity.programType))
    {
        status = CubeADCS_Gen2_CubeCommonBaseBootloader5_setJumpToDefaultAppRequestGw(
            TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, CUBEOBC_CRITICAL_WAIT_FOREVER);

        if (CUBEOBC_ERROR_OK == status)
        {
            // wait for boot
            cubeObc_time_delay(1000u);

            // Wait for port validation/auto-discovery to complete
            status = cubeObc_common_pollForBootState(
                endpoint, TCTLM_COMMON_FRAMEWORK_1__APPLICATION_RUNNING, 500u, 10000u, FALSE);
        }
    }
    else if (CUBEOBC_ERROR_OK == status)
    {
        // we do not support uploads in any other program type
        status = CUBEOBC_ERROR_UNKNOWN;
    }
    else
    {
        // nothing to do
    }

    // save context type
    U32 ctx = fs_file_ctx.context;

    if (CUBEOBC_ERROR_OK == status)
    {
        // reset whole file context
        memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));

        (void)memcpy(
            fs_file_ctx.file_name,
            fs_csf_ap.cp_file_name,
            strnlen(fs_csf_ap.cp_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ));

        // restore context type
        fs_file_ctx.context = ctx;

        status = cubeObc_cubeComputer_uploadCubeSpaceFile(
            endpoint, fno_cp.fsize, &fs_file_ctx, &fs_csf_ap.status);
    }

    if (CUBEOBC_ERROR_OK == status)
    {
        // reset whole file context
        memset(&fs_file_ctx, 0, sizeof(fs_file_ctx));

        (void)memcpy(
            fs_file_ctx.file_name,
            fs_csf_ap.cfg_file_name,
            strnlen(fs_csf_ap.cfg_file_name, CUBEADCS_GEN2_BDT_FILE_NAME_SZ));

        // restore context type
        fs_file_ctx.context = ctx;

        status = cubeObc_cubeComputer_uploadCubeSpaceFile(
            endpoint, fno_cfg.fsize, &fs_file_ctx, &fs_csf_ap.status);
    }

    if ((CUBEOBC_ERROR_OK == status) && (CUBEOBC_ERROR_OK == fs_csf_ap.status.errorCode))
    {
        status = cubeObc_cubeComputer_upgrade(
            endpoint,
            fs_csf_ap.node_type,
            fs_csf_ap.serial_int,
            TCTLM_COMMON_FRAMEWORK_ENUMS__PROGRAM_TYPE_CONTROL,
            TCTLM_CUBE_COMPUTER_CONTROL_PROGRAM_8__PORT_NONE,
            &fs_csf_ap.status);
    }

    return status;
}


/**
 * @brief Performs blocking upload/download
 */
static void fs_start_blocking_transfer(void)
{
    ErrorCode status;
    TypeDef_TctlmEndpoint endpoint;
    TctlmCommonFramework1_Identification identity;

    // setup the endpoint to the standard configuration
    cubeadcs_gen2_setup_endpoint(
        &endpoint, TYPEDEF__COMMS_ENDPOINT_UART, CUBEADCS_GEN2_DEFAULT_CONN_TIMEOUT);

    status = CubeADCS_Gen2_CommonFramework1_getIdentificationRequestGw(
        TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_COMPUTER, &identity, CUBEOBC_CRITICAL_WAIT_FOREVER);

    if ((CUBEOBC_ERROR_OK == status) &&
        (TCTLM_COMMON_FRAMEWORK_ENUMS__NODE_TYPE_CUBE_COMPUTER != identity.nodeType))
    {
        status = CUBEOBC_ERROR_NODE_TYPE;
    }

    switch (fs_file_ctx.context)
    {
        case CUBEADCS_GEN2_BDT_CTX_EVT_CC:
        {
            fs_evt.err_code = (CUBEOBC_ERROR_OK != status) ? status :
                cubeObc_cubeComputer_eventDownload(
                    &endpoint, &fs_evt.setup, &fs_file_ctx, &fs_evt.status);
        } break;
        case CUBEADCS_GEN2_BDT_CTX_TLM_CC:
        {
            fs_tlm.err_code = (CUBEOBC_ERROR_OK != status) ? status :
                cubeObc_cubeComputer_tlmDownload(
                    &endpoint, &fs_tlm.setup, &fs_file_ctx, &fs_tlm.status);
        } break;
        case CUBEADCS_GEN2_BDT_CTX_IMG_CC:
        {
            fs_img_stored.err_code = (CUBEOBC_ERROR_OK != status) ? status :
                cubeObc_cubeComputer_imageDownloadStored(
                    &endpoint, fs_img_stored.setup, &fs_file_ctx, &fs_img_stored.status);
        } break;
        case CUBEADCS_GEN2_BDT_CTX_FTP_BL:
        {
            fs_csf_bl.err_code = (CUBEOBC_ERROR_OK != status) ? status :
                fs_start_blocking_upload_to_boot(&endpoint);
        } break;
        case CUBEADCS_GEN2_BDT_CTX_FTP_AP:
        {
            fs_csf_ap.err_code = (CUBEOBC_ERROR_OK != status) ? status :
                fs_start_blocking_upload_to_appl(&endpoint);
        } break;
        default:
        {
            // no more contexts
            CRIT_ASSERT(false);
        } break;
    }
}


/**
 * @brief This task is responsible for handling all upload/download requests
 */
static void fs_transfer_task(void* args)
{
    (void)args;

    TaskMonitor_TaskInitialized(TASK_MONITOR_CUBEADCS_GEN2_TRANSFER);
    task_mon_set_task_policy(TASK_MONITOR_CUBEADCS_GEN2_TRANSFER, TASK_MON_POLICY_MONITOR);

    while (1)
    {
        TaskMonitor_IamAlive(TASK_MONITOR_CUBEADCS_GEN2_TRANSFER);

        if ((FS_START_TRANSFER_FLAG == osThreadFlagsWait(FS_START_TRANSFER_FLAG, osFlagsWaitAny, 5000)) &&
            (osOK == osMutexAcquire(fs_lock, osWaitForever)))
        {
            fs_start_blocking_transfer();

            (void)osMutexRelease(fs_lock);
        }

        vApplicationLowStackCheck(TASK_MONITOR_CUBEADCS_GEN2_TRANSFER);
    }
}
