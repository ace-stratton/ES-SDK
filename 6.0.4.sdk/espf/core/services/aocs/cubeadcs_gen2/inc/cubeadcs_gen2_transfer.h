/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CUBEADCS_GEN2_TRANSFER_H_
#define CUBEADCS_GEN2_TRANSFER_H_

/**
 * @addtogroup cubeadcs_gen2_transfer
 * @{
 *
 * @file cubeadcs_gen2_transfer.h
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "es_cdef.h"
#include "cubeadcs_gen2_types.h"
#include <cubeObc/cubeObc.h>


/** @brief defines event download parameters */
typedef struct
{
    ErrorCode err_code;                                         /**< error code */
    TctlmCubeComputerCommon3_EventLogFilterTransferSetup setup; /**< @ref cubeObc_cubeComputer_eventDownload() */
    TctlmCubeComputerCommon3_EventLogStatus status;             /**< @ref cubeObc_cubeComputer_eventDownload() */
    char file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ];             /**< file name */
} PACKED cubeadcs_gen2_transfer_evt_status_t;

/** @brief defines telemetry download parameters */
typedef struct
{
    ErrorCode err_code;                                       /**< error code */
    TctlmCubeComputerCommon3_TelemetryLogTransferSetup setup; /**< @ref cubeObc_cubeComputer_tlmDownload() */
    TctlmCubeComputerCommon3_TelemtryLogStatus status;        /**< @ref cubeObc_cubeComputer_tlmDownload() */
    char file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ];           /**< file name */
} PACKED cubeadcs_gen2_transfer_tlm_status_t;

/** @brief defines stored image download parameters */
typedef struct
{
    ErrorCode err_code;                                  /**< error code */
    U32 setup;                                           /**< @ref cubeObc_cubeComputer_imageDownloadStored() */
    TctlmCubeComputerCommon3_ImageTransferStatus status; /**< @ref cubeObc_cubeComputer_imageDownloadStored() */
    char file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ];      /**< file name */
} PACKED cubeadcs_gen2_transfer_img_stored_status_t;

/** @brief defines bootloader cube space file upload parameters */
typedef struct
{
    ErrorCode err_code;                                  /**< error code */
    Boolean force;                                       /**< force mode flag */
    TctlmCubeCommonBaseBootloader5_Errors status;        /**< @ref cubeObc_bootloader_uploadCubeSpaceFile() */
    char cp_file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ];   /**< control program file name */
    char cfg_file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ];  /**< configuration file name */
} PACKED cubeadcs_gen2_transfer_boot_cube_space_file_status_t;

/** @brief defines application cube space file upload parameters */
typedef struct
{
    ErrorCode err_code;                                         /**< error code */
    Boolean force;                                              /**< force mode flag */
    TctlmCommonFrameworkEnums_NodeType node_type;               /**< @ref cubeObc_cubeComputer_upgrade() */
    U32 serial_int;                                             /**< @ref cubeObc_cubeComputer_upgrade() */
    TctlmCubeComputerControlProgram8_FileTransferStatus status; /**< @ref cubeObc_cubeComputer_upgrade() */
    char cp_file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ];          /**< control program file name */
    char cfg_file_name[CUBEADCS_GEN2_BDT_FILE_NAME_SZ];         /**< configuration file name */
} PACKED cubeadcs_gen2_transfer_appl_cube_space_file_status_t;


/**
 * @brief Initialises the file transfer/firmware update service
 * 
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_init(void);

/**
 * @brief Nonblocking event file download. 
 *        Will fail if there is any ongoing upload/download.
 *
 * @param[in] file_name Output file name to be created on OBC. 
 *                      Maximum allowed length is @ref CUBEADCS_GEN2_BDT_FILE_NAME_SZ
 * @param[in] setup     Download setup
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_evt(
        const char* file_name,
        const TctlmCubeComputerCommon3_EventLogFilterTransferSetup* setup);

/**
 * @brief Get last event file download status. 
 *        Returns the same result until a new event download is initiated.
 *
 * @param[out] status Download status
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_evt_status(
        cubeadcs_gen2_transfer_evt_status_t* status);

/**
 * @brief Nonblocking telemetry file download. 
 *        Will fail if there is any ongoing upload/download.
 *
 * @param[in] file_name Output file name to be created on OBC. 
 *                      Maximum allowed length is @ref CUBEADCS_GEN2_BDT_FILE_NAME_SZ
 * @param[in] setup     Download setup
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_tlm(
        const char* file_name,
        const TctlmCubeComputerCommon3_TelemetryLogTransferSetup* setup);

/**
 * @brief Get last telemetry file download status. 
 *        Returns the same result until a new telemetry download is initiated.
 *
 * @param[out] status Telemetry download status
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_tlm_status(
        cubeadcs_gen2_transfer_tlm_status_t* status);

/**
 * @brief Nonblocking stored image file download. 
 *        Will fail if there is any ongoing upload/download.
 *
 * @param[in] file_name   Output file name to be created on OBC. 
 *                        Maximum allowed length is @ref CUBEADCS_GEN2_BDT_FILE_NAME_SZ
 * @param[in] file_handle File handle
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_img_stored(const char* file_name, const U32 file_handle);

/**
 * @brief Get last stored image file download status. 
 *        Returns the same result until a new stored image download is initiated.
 *
 * @param[out] status Image download status
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_img_stored_status(
        cubeadcs_gen2_transfer_img_stored_status_t* status);

/**
 * @brief Nonblocking file upload to bootloader.
 *        Will fail if there is any ongoing upload/download.
 *        The file will be used automatically by the bootloader to update the control program of CubeObc.
 *
 * @param[in] cp_file_name  Existing file on OBC (control program).
 *                          Maximum allowed length is @ref CUBEADCS_GEN2_BDT_FILE_NAME_SZ
 * @param[in] cfg_file_name Existing file on OBC (configuration).
 *                          Maximum allowed length is @ref CUBEADCS_GEN2_BDT_FILE_NAME_SZ
 * @param[in] force         If parameter is set to true - jump to boot (if in app)
 *                          otherwise the upload fails if device is not already in boot
 *
 * @return CUBEOBC_ERROR_OK on success else @reef ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_boot_cube_space_file(
       const char* cp_file_name,
       const char* cfg_file_name,
       const bool force);

/**
 * @brief Get last cube space file upload to bootloader status.
 *        Returns the same result until a new cube space file upload is initiated.
 *
 * @param[out] status file upload status
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_boot_cube_space_file_status(
        cubeadcs_gen2_transfer_boot_cube_space_file_status_t* status);

/**
 * @brief Nonblocking cube space file upload to application. 
 *        Will fail if there is any ongoing upload/download.
 *        The file will be used automatically by the application to update a CubeNode's control program.
 *
 * @param[in] cp_file_name  Existing file on OBC (control program).
 *                          Maximum allowed length is @ref CUBEADCS_GEN2_BDT_FILE_NAME_SZ
 * @param[in] cfg_file_name Existing file on OBC (configuration).
 *                          Maximum allowed length is @ref CUBEADCS_GEN2_BDT_FILE_NAME_SZ
 * @param[in] force         If parameter is set to true - jump to app, if in boot,
 *                          otherwise the upload fails if device is not already in app
 * @param[in] node_type     @ref cubeObc_cubeComputer_upgrade()
 * @param[in] serial_int    @ref cubeObc_cubeComputer_upgrade()
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_appl_cube_space_file(
        const char* cp_file_name,
        const char* cfg_file_name,
        const bool force,
        TctlmCommonFrameworkEnums_NodeType node_type,
        U32 serial_int);

/**
 * @brief Get cube space file last upload (to bootloader) status. 
 *        Returns the same result until a new cube space file upload is initiated.
 *
 * @param[out] status file upload status
 *
 * @return CUBEOBC_ERROR_OK on success else @ref ErrorCode
 */
ErrorCode cubeadcs_gen2_transfer_appl_cube_space_file_status(
        cubeadcs_gen2_transfer_appl_cube_space_file_status_t* status);


#ifdef __cplusplus
}
#endif

#endif /* CUBEADCS_GEN2_TRANSFER_H_ */
