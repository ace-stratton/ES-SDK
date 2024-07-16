/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup upython
 * @{
 *
 * @file upy_scr_mgr.h
 * @brief interface provided by upython script manager.
 *
 * @}
 * @}
 */

#ifndef UPYTHON_SCR_MGR_H_
#define UPYTHON_SCR_MGR_H_

/**
 * \enum
 * \brief return type used in UPY_SCR_MGR component
 *
 */
typedef enum
{
    UPY_SCR_MGR_OK,               /**< UPY_SCR_MGR_OK */
    UPY_SCR_MGR_ERROR,            /**< UPY_SCR_MGR_ERROR */
    UPY_SCR_MGR_WRONG_PARAMS,     /**< UPY_SCR_MGR_WRONG_PARAMS */
    UPY_SCR_MGR_MUTEX_ERROR,      /**< UPY_SCR_MGR_MUTEX_ERROR */
    UPY_SCR_MGR_SCRIPT_NOT_FOUND, /**< UPY_SCR_MGR_SCRIPT_NOT_FOUND */
    UPY_SCR_MGR_CNT               /**< UPY_SCR_MGR_CNT */
} upy_scr_mgr_return_t;

/**
 * \brief Initialization of the internal data of the component
 *
 * \param mutex_id Already created mutex ID. If NULL is passed exception will
 * be raised.
 */
void
upy_scr_mgr_init(osMutexId_t mutex_id);

/**
 * uint32_t, pfMicropythonExecScript_Cbk_t, uint8_t* const) \brief
 *
 * \param p_name - file name string.
 * \param len: length of the p_name no NULL terminator included.
 * \param time_out
 * \param p_on_send_result_cbk
 * \param p_script_id
 * \return
 */
upy_scr_mgr_return_t
upy_scr_mgr_add(const char *const p_name, uint8_t len, uint32_t time_out,
                pfMicropythonExecScript_Cbk_t p_on_send_result_cbk,
                uint8_t *const                p_script_id);

/**
 * \brief Updates the status of a script based on the ID in case the script is
 * in the queue
 *
 * \param script_id
 * \param p_new_script_data - pointer to output variable for script data to be
 * filled in
 * \return
 * UPY_SCR_MGR_ERROR: in case unknown error
 * UPY_SCR_MGR_OK: in case of successful operation
 * UPY_SCR_MGR_SCRIPT_NOT_FOUND: in case the script is not found in the queue
 * UPY_SCR_MGR_MUTEX_ERROR: in case of problem with MUTEX usage
 * UPY_SCR_MGR_WRONG_PARAMS: in case of wrong input parameters
 *
 */
upy_scr_mgr_return_t
upy_scr_mgr_set_status(uint8_t                    script_id,
                       sScriptData_t const *const p_new_script_data);

/**
 * \brief Updates the status of a script based on the ID in case the script is
 * in the queue
 *
 * \param script_id - identifier of the script which shall be updated
 * \param p_script_data - pointer to output variable for script data to be
 * filled in
 * \return
 * UPY_SCR_MGR_ERROR: in case unknown error
 * UPY_SCR_MGR_OK: in case of successful operation
 * UPY_SCR_MGR_SCRIPT_NOT_FOUND: in case the script is not found in the queue
 * UPY_SCR_MGR_MUTEX_ERROR: in case of problem with MUTEX usage
 * UPY_SCR_MGR_WRONG_PARAMS: in case of wrong input parameters
 *
 */
upy_scr_mgr_return_t
upy_scr_mgr_get_status(uint8_t script_id, sScriptData_t *const p_script_data);

#endif //UPYTHON_SCR_MGR_H_
/***end of file***/
