/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef CUBEADCS_H
#define CUBEADCS_H

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup cubeadcs CubeADCS
 * @{
 * The CubeADCS module provides integration for the (Gen1) 3-Axis/Y-Momentum ADCS solution provided by CubeSpace. The module includes:
 * - Low-level driver over UART
 * - File-list download and file download logic implementation
 * - Constant monitoring of the ADCS status and health
 * - Support for quick Operational Modes integration
 * - Error handling logic
 * - Application level commands
 *
 * ## Introduction
 *
 * This module consists of a low-level driver over UART and  a mixed application/middleware layer distributed
 * into several source and header files. Two tasks are used by the module - a file transfer task (normal priority), which deals with file downloads, uploads and file list downloads
 * and a general task (again with normal priority) which takes care of the periodic health checks, errors, resets, etc. The current driver relies on a mutex to manage the access to the
 * UART channel from overlapping requests to the CubeADCS which may occur from - the two tasks, user generic TC/TLM requests, Operational modes requests (read angular velocity, set new state for the CubeADCS, etc.).
 * Typically, the response time of the CubeADCS is within a few [ms] which rarely results in a command request to fail.
 *
 * @note If you perform command requests while a file transfer is ongoing the latter will probably fail as the transfer will be inhibited by the request. It is best to avoid this while performing file transfers.
 *
 * ## The main task
 *
 * The main task implements a state machine which drives the periodic checks of the CubeADCS. The states of the state machine are depicted in the following table:
 *
 * | State Machine State      | Description |
 * | ----------- | ----------- |
 * | INIT_WAIT | This is the state at power-up of the OBC. The task remains in this state for 10 seconds before moving to the INIT state. This wait is mandatory as it takes several seconds for the CubeADCS ACP to be booted by the CubeADCS Bootloader. If the wait is not there, the CubeADCS start-up sequence will be inhibited and the CubeADCS will remain in bootloader.       |
 * | INIT | In this state the task sends a TLM128 request (identification telemetry) to assess if the CubeADCS has successfully started the ACP. In case the latter was not started, the state machine will remain in the INIT state indefinitely.        |
 * | IDLE | This is basically a wait state. The task remains in the IDLE state 10 seconds before continuing. This state also serves as the state transition state - if a request for a different state (such as reset is received) it will only be accepted if the current CubeADCS task state is IDLE. Once the 10 seconds elapse, the CubeADCS task switches to the Health Check state.|
 * | HEALTH_CHECK | In this state telemetry regarding the current CubeADCS system state is gathered. The logic verifies that the current ADCS system state is the expected one, checks whether a switch to CubeACP in case we are in bootloader (it may happen in case the CubeADCS experiences a reset but the OBC does not) is necessary and calls the error handling implementation (this is performed always unless a switch to CubeACP is needed). At the end of the state the error counters are updated and, if necessary, a specific error handling logic is activated. |
 * | SYSSTATE_CHANGE | Performs a change of the state of the CubeADCS system → enables/disables nodes, changes control and estimation modes. Each pass through this state takes about 1 second and will be repeated no more than 5 times. The result of the state change attempt is written and can be read.|
 * | PREP_DETUMB | This state is called always after the HEALTH_CHECK state is passed. It serves the purpose to put the CubeADCS in a detumbling friendly state. Ideally, this state will be truly executed only once unless the CubeADCS undergoes a reset or is reset by a user command.|
 *
 * ## The low-level driver
 *
 * The driver is responsible for sending commands and receiving telemetry from the CubeADCS via a dedicated UART channel. The driver is using the HAL library to perform transmit and receive. Data is transmitted by using blocking logic, but is received in a non-blocking manner (to this end a DMA channels is used).
 * Several buffers are used for packing and unpacking of the data based on the CubeSpace protocol description. You can request fetch commands, transmit only, receive only and receive only in file download mode. Each receive or fetch request is marked by a non-blocking 1000 ms wait period in which the OBC waits to receive the correct number of bytes from the CubeADCS.
 * The return from the execution of a request can be:
 *
 * - **COMM_OK**: Successful communication, no errors
 * - **COMM_ERR**: Unsuccessful communication, unspecified error
 * - **COMM_CMD_ERR**: Requested command ID not found in the list of known CubeADCS commands (the commands IDs, RX length and TX lengths are depicted in the driver sources)
 * - **COMM_LEN_WRT_ERR**: Expected vs given TC command data size mismatch
 * - **COMM_LEN_READ_ERR**: Expected vs received TC/TLM command data size mismatch
 * - **COMM_RX_TIMEOUT**: Timeout while receiving command request response
 * - **COMM_TX_TOMEUT**: Timeout while transmitting a command
 * - **COMM_INV_DATA**: Received correct number of bytes but command ID in header is not correct
 * - **COMM_COMM_ERR**: Error while receiving command request reply (wrong start/end sequence, etc.)
 *
 * @note These responses are featured in the error counters. Each time a command is sent, the reply is used to update the relevant error counter.
 *
 * @warning Sometimes the CubeADCS response exceeds few hundred of milliseconds. Moreover, it happens that a response is never sent back. This accounts to a small number of COMM_RX_TIMEOUT replies from the driver.!!!
 *
 * ## The CRC Calculation
 *
 * Two types of CRC (**CRC8** and **CRC16**) are used by CubeSpace. A **CRC8** is attached to telecommands and a **CRC16** is used during file transfers to check file consistency.
 *
 * ## Error Handling
 *
 * @warning This logic has a persistent configuration. By default this logic is turned **OFF** as it has not been thoroughly tested.
 *
 * The automatic error handling logic consists of seventeen cases split into separate functions, taking care of the moderate and severe errors reported back by the CubeADCS.
 * Each error handling logic can be activated once or several times and this is currently hardcoded. The limitation is put in place since, for example, there is no need to power cycle indefinitely an unresponsive node, or constantly change the magnetometer configuration.
 * A table with all the errors that can be handled by the logic is depicted here:
 *
 * ![Error Handling Logic](../img/err_handl_logic.png)
 *
 * ### Handling Magnetometer Errors
 *
 * - Enables the CubeControl Motor MCU in order not to lose control and estimation
 * - Power cycles the CubeControl Signal MCU on first error
 * - Sample the redundant magnetometer on second error
 * - Sample the main magnetometer with the CubeControl Motor MCU on third error
 * - Raise the latched error flag to notify users on fourth error
 *
 * ### Handling Cam1, Cam2 and CamStar Errors
 *
 * - The logic for all camera nodes is currently identical
 * - The faulty camera node is power cycled several times
 *
 * ### Handling Node Recovery Errors
 *
 * - Compares the currently enabled nodes with the nodes enabled by the OBC (but not the nodes enabled through the generic commands to the CubeADCS)
 * - Stores the potential faulty node in a register and updates the status flag indicating this error has occurred
 *
 * ### Handling Rate Sensor and Wheel Errors
 *
 * - Stops all reaction wheels (By setting the RPM to 0)
 * - Increases the rate sensor multiplier to maximize the rate sensor detection range
 * - Enables both CubeControl MCUs
 * - Sets the estimation mode to MEMS rate
 * - Reads the angular rate and decides if fast or very fast detumbling should be activated
 *
 * ### Handling Rate Sensor Failure
 *
 * - Stops all reaction wheels (By setting the RPM to 0)
 * - Enables CubeControl Signal MCU
 * - Transition to Very Fast Detumbling mode if Signal MCU has been enabled
 * - Transition to Fast Detumbling mode if Signal MCU has not been enabled
 *
 * ### Handling Orbit, Config, Estimation and Control Mode Errors
 *
 * No specific error handling logic is implemented.
 *
 * ## Commands
 *
 * There are two types of CubeADCS commands:
 * - The first type are the commands which deal with the CubeADCS, but are implemented in the OBC.
 *   Details of these commands can be found in the fidl: **OBC_CUBEADCS.fidl**. Most are high-level functionality commands whcih are used to download files, read the operational status etc.
 *   There is a generic command which can be used to request almost any CubeADCS command. However, the data is presented raw.
 * - The second type are the CubeADCS specific commands, their full description can be found in the **CubeADCS - Firmware Reference Manual [V7.2].pdf**.
 *   The fidl descriptions are in: **OBC_CP_CUBEADCS_GATEWAY.fidl**. These commands can be send only using the Command Protocol (CP).
 *
 * ## File Transfers
 *
 * File transfers are organized in a separate task which drives the state machines of the file transfer processes. Currently supported:
 * - @emoji :white_check_mark: File-list download
 * - @emoji :white_check_mark: File downloads
 * - @emoji :x: File uploads (not implemented)
 *
 * @note The implementation deals with the transfer of files between the OBC and the CubeADCS only. File transfers between the Ground Station and the OBC are not discussed here.
 *
 * The CubeADCS supports a few file types (consult CubeSpace's documentation for further details). Therefore, files are downloaded to the OBC using a fixed naming convention:
 *
 * | Full File Name      | File Extension | Details |
 * | ----------- | ----------- | ----------- |
 * | xxxCSTLM      | .txt       | Telemetry logs |
 * | xxxCSIMG   | .jpg        | Jpg images |
 * | xxxCSIMG   | .bmp        | Bmp images |
 * | xxxCSIND   | .txt        | Index file |
 * | CSFL'IST   | .txt        | File list dump |
 *
 * , where **xxx** is the file type number.
 *
 * Logs, images and the index file are downloaded as they are, but the file list is downloaded in a human readable format.
 * An example file list has the structure depicted below, where **FileType** is given as a string (the actual file type) and as a number (each file type is associated with a number).
 *
 * > CubeADCS File List
 * >
 * > FileType (s|d)	 Size	 CRC	 Time	 Ctr
 * >
 * > Tlm | 2	 0x00001D7A	 0x181F	 15/09/2044 13:49:22	 000\n
 * > Tlm | 2	 0x0001A620	 0x3E97	 01/09/2021 11:48:10	 001\n
 * > Tlm | 2	 0x00003E4A	 0xBC2A	 15/09/2044 13:37:30	 002\n
 * > Tlm | 2	 0x000004EA	 0x9E01	 15/09/2044 13:38:00	 003\n
 * > Tlm | 2	 0x00000E4A	 0x6F19	 15/09/2044 13:39:52	 004\n
 * > Tlm | 2	 0x000000CA	 0x0FD4	 15/09/2044 13:29:48	 005\n
 *
 * When starting a file transfer, the user must provide information regarding the file which has to be downloaded.
 * To uniquely identify a file and make a successful transfer, the following information is required:
 *
 * - FileType
 * - Counter
 * - CRC16
 * - FileSize
 * - sdCardID
 *
 * There is no indication of the percentage of file downloaded, but the user can poll the status of the transfer. Typically, a file list download is almost instant, but a large file (~1MByte images) takes several minutes.
 *
 * ## The System State Configuration
 *
 * The CubeADCS is a system of its own with many different states and modes. However, from the perspective of the user (for example, the Operational Modes) the CubeADCS is **in a specific system state**. This state is described by:
 * - control mode
 * - estimation mode
 * - enabled periphery (nodes)
 * To change these, several commands have to be sent to the CubeADCS coupled with relevant checks. Therefore, logic is implemented which will change these and make the necessary verification.
 * The system states are populated in a configuration (array), which the user can extend.
 *
 * The array has the following structure:
 * @code {.c}
 * const CubeADCS_Cfg_t asCubeADCS_SysStates[eCUBEADCS_CFGTYPE_NUMBER] = {
 * 	  {	    eCUBEADCS_CFGTYPE_PWR_UP,
 * 	        { .CubeControl_Signal = 1,
 * 	    	  .CubeControl_Motor  = 1,
 * 			  .CubeSense1 = 0,
 * 	          .CubeSense2 = 0,
 * 			  .CubeStar   = 0,
 * 			  .CubeWheel1 = 0,
 * 			  .CubeWheel2 = 0,
 * 			  .CubeWheel3 = 0
 * 	        },
 * 	        eCUBE_ADCS_TC_13_CONTROLMODE_NO_CNTRL,
 * 		    eCUBE_ADCS_TC_14_ESTIMATIONMODE_MTM_RATE_FILT,
 * 		    eCUBE_ADCS_TC10_RUNMODE_ENABLED,
 * 		    0,
 * 	  },
 * 	  {     eCUBEADCS_CFGTYPE_NORMAL_DETUMBLING,
 * 	        { .CubeControl_Signal = 1,
 * 	          .CubeControl_Motor  = 1,
 * 	          .CubeSense1 = 0,
 * 			  .CubeSense2 = 0,
 * 			  .CubeStar   = 0,
 * 	          .CubeWheel1 = 0,
 * 			  .CubeWheel2 = 0,
 * 			  .CubeWheel3 = 0
 * 	        },
 * 	        eCUBE_ADCS_TC_13_CONTROLMODE_DETUMB_CNTRL,
 * 		    eCUBE_ADCS_TC_14_ESTIMATIONMODE_MTM_RATE_FILT,
 * 		    eCUBE_ADCS_TC10_RUNMODE_ENABLED,
 * 		    0,
 * 	  },
 * 	  ...
 * @endcode
 *
 * @note At power-up, the OBC instructs the CubeADCS to enter the **eCUBEADCS_CFGTYPE_PWR_UP** system state. In this state the necessary ADCS periphery to
 * perform detumbling is enabled, but the control mode is **NOT** activated. However in case the error handling logic is enabled and the angular rates exceeds 100 deg/s, fast or very-fast detumbling will be enabled.
 * This is independent of the system states changes, which are driven by a higher level logic such as the Operational Modes.
 *
 * @file cubeadcs.h
 *
 * @brief Public interface of the CubeADCS
 *
 * @}
 * @}
 *
*/

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

/*
*********************************************************************************************
* INCLUDES
*********************************************************************************************
*/
#include "../cfg/cubeadcs_cfg.h"
#include "cubeadcs_driver.h"
#include "cubeadcs_ftransfer.h"
#include "cubeadcs_persist.h"
#include <if_sys_mod.h>
#include <sys_instancer_ct.h>

#include <math.h>

#include "es_exeh.h"

/*
*********************************************************************************************
* EXTERNAL DEFINES
*********************************************************************************************
*/
/** @brief Used to indicate that an update to the dynamic CubeADCS status cache must be performed */
#define CUBEADCS_DIAG_UPDATE_OK     ((uint8_t)0x33)
/** @brief Used to indicate that no update to the dynamic CubeADCS status cache is necessary */
#define CUBEADCS_DIAG_UPDATE_NOK    ((uint8_t)0x00)
/** @brief TC reply length in bytes */
#define CUBEADCS_TC_LEN             ((uint8_t)0x02)
/** @brief TLM128 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM128_LEN         ((uint8_t)0x09)
/** @brief TLM129 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM129_LEN         ((uint8_t)0x07)
/** @brief TLM130 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM130_LEN         ((uint8_t)0x03)
/** @brief TLM135 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM135_LEN         ((uint8_t)0x02)
/** @brief TLM132 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM132_LEN         ((uint8_t)0x07)
/** @brief TLM138 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM138_LEN         ((uint8_t)0x0B)
/** @brief TLM140 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM140_LEN			((uint8_t)0x07)
/** @brief TLM146 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM146_LEN         ((uint8_t)0x07)
/** @brief TLM147 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM147_LEN         ((uint8_t)0x07)
/** @brief TLM155 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM155_LEN         ((uint8_t)0x07)
/** @brief TLM156 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM156_LEN         ((uint8_t)0x07)
/** @brief TLM163 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM163_LEN         ((uint8_t)0x07)
/** @brief TLM197 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM197_LEN         ((uint8_t)0x04)
/** @brief TLM200 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM200_LEN         ((uint8_t)0x0D)
/** @brief TLM207 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM207_LEN			((uint8_t)0x41)
/** @brief TLM224 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM224_LEN         ((uint8_t)0x07)
/** @brief TLM242 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM242_LEN         ((uint8_t)0x06)
/** @brief TLM243 request reply length: command reply + 1 byte (TLM ID preceding each TLM reply) */
#define CUBEADCS_TLM243_LEN         ((uint8_t)0x0D)
/** @brief TLM255 request reply length: expected reply is 20bytes payload + 2bytes for header ID + 1 for TLM ID
 *
 *  @note This is not an actual command ID. We use it internally to identify file burst packets!
 *  The speicifed length is the length of a single burst packet.
 */
#define CUBEADCS_TLM255_LEN         ((uint8_t)0x17)


/*--------------Automatic err handling defines--*/
/** @brief Used to indicate that no validation of received data is necessary */
#define CUBEADCS_VALIDATE_DATA_FALSE    ((uint8_t)0x00)
/** @brief Used to indicate that validation of received data is necessary */
#define CUBEADCS_VALIDATE_DATA_TRUE     ((uint8_t)0x11)

/*---------------TC defines---------------------*/
/** @brief The reset magic number used to perform a CubeADCS reset request */
#define CUBEADCS_TC_01_MAGIC_NUM        ((uint8_t)0x5A)
/** @brief TC2 length in bytes */
#define CUBEADCS_TC_02_BYTE_LEN         ((uint8_t)0x06)
/** @brief TC9 length in bytes */
#define CUBEADCS_TC_09_BYTE_LEN         ((uint8_t)0x02)
/** @brief TC10 length in bytes */
#define CUBEADCS_TC_10_BYTE_LEN         ((uint8_t)0x01)
/** @brief TC11 length in bytes */
#define CUBEADCS_TC_11_BYTE_LEN         ((uint16_t)0x03)
/** @brief TC13 length in bytes */
#define CUBEADCS_TC_13_BYTE_LEN         ((uint16_t)0x03)
/** @brief TC14 length in bytes */
#define CUBEADCS_TC_14_BYTE_LEN         ((uint16_t)0x01)
/** @brief TC15 length in bytes */
#define CUBEADCS_TC_15_BYTE_LEN         ((uint16_t)0x06)
/** @brief TC17 length in bytes */
#define CUBEADCS_TC_17_BYTE_LEN         ((uint16_t)0x06)
/** @brief TC45 length in bytes */
#define CUBEADCS_TC_45_BYTE_LEN			((uint16_t)0x40)
/** @brief TC55 length in bytes */
#define CUBEADCS_TC_55_BYTE_LEN         ((uint16_t)0x0C)
/** @brief TC64 length in bytes */
#define CUBEADCS_TC_64_BYTE_LEN			((uint16_t)0x00)
/** @brief TC113 length in bytes */
#define CUBEADCS_TC_113_BYTE_LEN        ((uint16_t)0x00)
/** @brief TC118 length in bytes */
#define CUBEADCS_TC_118_BYTE_LEN        ((uint16_t)0x00)
/** @brief TC13, input value used to indicate no timeout for the control mode activation */
#define CUBEADCS_TC_13_NO_TIMEOUT       ((uint16_t)0xFFFF)

/*--------------CubeADCS Task related defines--------------------*/
/** @brief Base delay used by the CubeADCS task */
#define CUBEADCS_TASK_BASE_DELAY_MS    ((uint32_t)500)
/** @brief IDLE time delay time used in the CubeADCS task */
#define CUBEADCS_TASK_IDLE_DELAY_MS    ((uint32_t)10000)

/*--------------Other--------------------*/
/** @brief Value passed to indicate the state change request should be executed */
#define CUBEADCS_EXEC_STATE_REQ         (true)
/** @brief Value passed to indicate the state change request should NOT be executed */
#define CUBEADCS_DONT_EXEC_STATE_REQ    (false)
/*
*********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
*********************************************************************************************
*/

/*------------------------------------------------------------------------------ */
/*-------------------------- CUBEADCS COMMON TYPES------------------------------ */
/*------------------------------------------------------------------------------ */
/** @brief Enum used when performing a state change of the main state machine */
typedef enum {
    eCUBEADCS_FORCESTATECHG_TRUE,
    eCUBEADCS_FORCESTATECHG_FALSE,

} eCubeADCS_ForceStateChg_t;

/** @brief Enum of the standard replies */
typedef enum {
    eCUBEADCS_STDRPLY_OK,
    eCUBEADCS_STDRPLY_ERR,
	eCUBEADCS_STDRPLY_INVALID_ARGS,

} eCubeADCS_StdRply;

/** @brief Enum of the states of the main CubeADCS state machine
 *
 *  @note Extend if necessary, don't change order
 */
typedef enum tag_eCubeADCS_State
{
    eCUBEADCS_STATE_INIT_WAIT,
    eCUBEADCS_STATE_INIT,
    eCUBEADCS_STATE_IDLE,
    eCUBEADCS_STATE_HEALTH_CHECK,
    eCUBEADCS_STATE_SYSSTATE_CHANGE,
    eCUBEADCS_STATE_PREP_DETUMB,

    eCUBEADCS_STATE_NUMBER

} eCubeADCS_State_t;

/** @brief A short list of the commands used by the higher level logic
 *
 *  @note Extend if needed with more commands
 */
typedef enum tag_eCubeADCS_CMD_List
{
    eCUBEADCS_CMD_ID_1   = 1,
	eCUBEADCS_CMD_ID_2   = 2,
    eCUBEADCS_CMD_ID_7   = 7,
	eCUBEADCS_CMD_ID_9   = 9,
    eCUBEADCS_CMD_ID_10  = 10,
    eCUBEADCS_CMD_ID_11  = 11,
    eCUBEADCS_CMD_ID_12  = 12,
    eCUBEADCS_CMD_ID_13  = 13,
    eCUBEADCS_CMD_ID_14  = 14,
    eCUBEADCS_CMD_ID_15  = 15,
    eCUBEADCS_CMD_ID_17  = 17,
    eCUBEADCS_CMD_ID_23  = 23,
	eCubeADCS_CMD_ID_45  = 45,
    eCUBEADCS_CMD_ID_55  = 55,
    eCUBEADCS_CMD_ID_56  = 56,
	eCUBEADCS_CMD_ID_64  = 64,
    eCUBEADCS_CMD_ID_100 = 100,
    eCUBEADCS_CMD_ID_112 = 112,
    eCUBEADCS_CMD_ID_113 = 113,
    eCUBEADCS_CMD_ID_118 = 118,
    eCUBEADCS_CMD_ID_119 = 119,
    eCUBEADCS_CMD_ID_120 = 120,
    eCUBEADCS_CMD_ID_121 = 121,
    eCUBEADCS_CMD_ID_122 = 122,
    eCUBEADCS_CMD_ID_123 = 123,
    eCUBEADCS_CMD_ID_124 = 124,
    eCUBEADCS_CMD_ID_125 = 125,
    eCUBEADCS_CMD_ID_126 = 126,
    eCUBEADCS_CMD_ID_127 = 127,
    eCUBEADCS_CMD_ID_128 = 128,
    eCUBEADCS_CMD_ID_129 = 129,
    eCUBEADCS_CMD_ID_130 = 130,
    eCUBEADCS_CMD_ID_132 = 132,
    eCUBEADCS_CMD_ID_135 = 135,
    eCUBEADCS_CMD_ID_138 = 138,
	eCUBEADCS_CMD_ID_140 = 140,
	eCUBEADCS_CMD_ID_146 = 146,
    eCUBEADCS_CMD_ID_147 = 147,
    eCUBEADCS_CMD_ID_155 = 155,
	eCUBEADCS_CMD_ID_156 = 156,
    eCUBEADCS_CMD_ID_163 = 163,
    eCUBEADCS_CMD_ID_197 = 197,
    eCUBEADCS_CMD_ID_200 = 200,
	eCUBEADCS_CMD_ID_207 = 207,
    eCUBEADCS_CMD_ID_224 = 224,
    eCUBEADCS_CMD_ID_242 = 242,
    eCUBEADCS_CMD_ID_243 = 243,
    eCUBEADCS_CMD_ID_255_CUSTOM = 255,

} eCubeADCS_CMD_List_t;

/** @brief A list of the number of commands used during the INIT state of the main state machine */
typedef enum tag_eCubeADCS_INIT_STATE_CMD_List
{
    eCUBEADCS_INIT_STATE_CMD_ID_128,

    eCUBEADCS_INIT_STATE_CMD_ID_NUM,

} eCubeADCS_INIT_STATE_CMD_List_t;

/** @brief A list of the number of commands used during the IDLE state of the main state machine */
typedef enum tag_eCubeADCS_IDLE_STATE_CMD_List
{
    eCUBEADCS_IDLE_STATE_CMD_ID_128,
	eCUBEADCS_IDLE_STATE_CMD_ID_129,
    eCUBEADCS_IDLE_STATE_CMD_ID_130,
    eCUBEADCS_IDLE_STATE_CMD_ID_132,
    eCUBEADCS_IDLE_STATE_CMD_ID_224,
    eCUBEADCS_IDLE_STATE_CMD_ID_197,
	eCUBEADCS_IDLE_STATE_CMD_ID_135,

    eCUBEADCS_IDLE_STATE_CMD_ID_NUM,

} eCubeADCS_IDLE_STATE_CMD_List_t;

/** @brief CubeADCS states type - TLM135, TLM132, TLM224, TLM129, TLM130 */
typedef struct tag_CubeADCS_State
{
    CubeADCS_TLM135_t State_Err;
    CubeADCS_TLM132_t State_ADCS;
    CubeADCS_TLM224_t State2_ADCS;
    CubeADCS_TLM129_t boot_status;
    CubeADCS_TLM130_t prog_status;

} __attribute__((__packed__)) CubeADCS_State_t;

/** @brief The operational status type - used by the main logic to keep important runtime information of the status of the CubeADCS */
typedef struct tag_CubeADCS_Op_Status
{
    eCubeADCS_Mode_t        Mode;
    CubeADCS_State_t        State;
    CubeADCS_Status_t       Status;
    eCubeADCS_Comm_Status_t Comm;

} __attribute__((__packed__)) CubeADCS_Op_Status_t;

/** @brief Enum of the command request reply */
typedef enum {
    eCUBEADCS_REQCMD_STATUS_SUCCESS,
    eCUBEADCS_REQCMD_STATUS_ERROR,
    eCUBEADCS_REQCMD_CMD_ID_ERROR,
    eCUBEADCS_REQCMD_STATUS_INVALID_ARGS,
    eCUBEADCS_REQCMD_STATUS_IN_USE
} eCubeADCS_ReqCmd_Status_t;

/** @brief Enum used by the angular rate function with weighted option */
typedef enum tag_eCubeADCS_AngRateType {
    eCUBEADCS_ANGRATETYPE_EST,
    eCUBEADCS_ANGRATETYPE_RATE,
    eCUBEADCS_ANGRATETYPE_WEIGHTED,

	eCUBEADCS_ANGRATETYPE_NUM,
} eCubeADCS_AngRateType_t;

/*
*********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
*********************************************************************************************
*/

/** @brief Configuration interface for the system instancer */
extern if_sys_mod_t cube_adcs_module_configuration;

/*
*********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
*********************************************************************************************
*/

/** @brief Configuration interface init implementation for the system instancer
 *
 *  @param[in] level the level of initialisation
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_init(sys_init_level_id_t level);

/** @brief Configuration interface run implementation for the system instancer
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_run();

/** @brief Configuration interface stop implementation for the system instancer
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_stop();

/** @brief Configuration interface deinit implementation for the system instancer
 *
 *  @param[in] level the level of initialisation
 *
 *  @return result from the initialisation command
 */
mod_op_status_id_t cube_adcs_deinit(sys_init_level_id_t level);

/** @brief Initializes the CubeADCS task */
void CubeADCS_TaskInit(void);

/** @brief Delay the execution of the CubeADCS task with the requested amount
 *
 *  @param[in] delay time in [ms] to delay the task
 */
void CubeADCS_DelayTask(uint32_t delay);

/** @brief Read current commissioning status value
 *
 *  @return eCubeADCS_Commissioning_t the current commissioning status value
 */
eCubeADCS_Commissioning_t cubeadcs_get_cms_status(void);

/** @brief Set new commissioning status value
 *
 *  @return eCubeADCS_StdRply operation result
 */
eCubeADCS_StdRply cubeadcs_set_cms_status(const eCubeADCS_Commissioning_t newStatus);

/** @brief Send a new command or request new telemetry from the CubeADCS
 *
 *  @param[in] sCmd pointer to command details (context)
 *  @param[in] eCommReqType type of communication request
 *
 *  @note Wrapper around the CubeADCS_Driver_ExecCmdReq controlling the actual access to the CubeADCS.
*         Access to the UART is blocked (mutex) until transaction is finished.
 *
 *  @return status of the performed request
 */
eCubeADCS_Comm_Status_t CubeADCS_SendCmd(CubeADCS_CmdCfg_t *sCmd, eCubeADCS_CommReqType_t eCommReqType);

/** @brief Get the current CubeADCS main state machine task
 *
 *  @return the current state machine state
 */
eCubeADCS_State_t CubeADCS_GetState(void);

/** @brief Sets the command details (context)
 *
 *  @note This function performs NO CHECKS on the input data (null pointers, etc.)
 */
void CubeADCS_PREPCmd(CubeADCS_CmdCfg_t *sCmd,
		uint8_t   u8CmdID,
		uint8_t  *pu8CmdData,
		uint16_t  u16CmdDataSize,
		void     *pvCmdResDst,
		uint16_t  u16CmdResDstSize,
		uint16_t *u16CmdResSize);

/** @brief Get current running program - Bootloader or ACP */
eCubeADCS_Mode_t CubeADCS_GetNodeType(void);

/** @brief Get the control mode from the operational status cache
 *
 *  @note This will return the LAST read control mode, not the CURRENT control mode of the CubeADCS
 */
eCUBE_ADCS_TC_13_CONTROL_MODE_t CubeADCS_GetCntrlMode(void);

/** @brief Get the estimation mode from the operational status cache
 *
 *  @note This will return the LAST read estimation mode, not the CURRENT estimation mode of the CubeADCS
 */
eCUBE_ADCS_TC_14_ESTIMATION_MODE_t CubeADCS_GetEstMode(void);

/** @brief Set a new control mode
 *
 *  @param[in] eCntlMode the new control mode
 *  @param[in] u16TimeOut control mode activation timeout
 */
void CubeADCS_SetControlMode(eCUBE_ADCS_TC_13_CONTROL_MODE_t eCntlMode, uint16_t u16TimeOut);

/** @brief Set a new estimation mode
 *
 *  @param[in] eEstMode the new estimation mode
 */
void CubeADCS_SetEstimationMode(eCUBE_ADCS_TC_14_ESTIMATION_MODE_t eEstMode);

/** @brief Set the CubeADCS run mode as stored in the operational status
 *
 *  @note This will return the LAST read run mode, not the CURRENT run mode of the CubeADCS
 */
eCUBE_ADCS_TC_10_RUNMODE_t CubeADCS_GetADCSRunMode(void);

/** @brief Set a new value for the CubeADCS run mode */
void CubeADCS_SetADCSRunMode(eCUBE_ADCS_TC_10_RUNMODE_t eRunMode);

/** @brief Power ON/OFF a CubeADCS node
 *
 *  @param[in] node the CubeADCS node
 *  @param[in] state the new state of the node
 */
void cubeadcs_set_node_pwr_state(eCUBE_ADCS_TC_11_NODES_t node, eCUBE_ADCS_TC_11_PWR_STATES_t state);

/** @brief Get angular rate from the CubeADCS in [rad/s]
 *
 *  @param[in] eMeasType measurement type
 *  @param[out] sAngRate pointer to the destination to store the read angular rates
 *
 *  @return operation status
 *
 *  @note See CMD ID 147 and CMD ID 155 in the Firmware Reference Manual for further description
 */
eCubeADCS_StdRply CubeADCS_GetAngularRate(CubeADCS_AngRateFormatted_t *sAngRate, eCubeADCS_AngRateType_t eMeasType);

/** @brief Get the operational status cache
 *
 *  @param[out] psDst pointer to the destination to store the read operational status
 *
 *  @return operation status
 */
bool cubeadcs_get_op_status(CubeADCS_Op_Status_t *psDst);

/** @brief Get the TLM132 from the operational status cache
 *
 *  @param[out] psDst pointer to the destination to store the read value
 *
 *  @retval true on success
 *  @retval false on failure
 */
bool cubeadcs_get_op_status_adcs_state(CubeADCS_TLM132_t *psDst);

/** @brief Sets power to nodes according to a provided mask
 *
 *  @param[in] uNodeMask the mask
 */
void CubeADCS_SetPwrNodeStates(uCubeADCS_CfgNodwPwrMask_t uNodeMask);

/** @brief Gets the power state of all CubeADCS nodes
 *
 *  @return the power mask of all CubeADCS nodes
 *
 *  @note This will return the LAST read state of the nodes, not the current CubeADCS power node states
 */
uCubeADCS_CfgNodwPwrMask_t CubeADCS_GetADCSNodesPwrMask(void);

/** @brief Gets the power state of a specific CubeADCS node
 *
 *  @return the power state of the CubeADCS node
 *
 *  @note This will return the LAST read state of the node, not the current node power state
 */
eCUBE_ADCS_TC_11_PWR_STATES_t CubeADCS_GetADCSNodePwrState(eCUBE_ADCS_TC_11_NODES_t eNode);

/** @brief Wrapper around CubeADCS_SendCmd used to correctly update the operational status of the CubeADCS
 *
 *	@param[in] sCmd pointer to command details (context)
 *	@param[in] u8Update value to indicate whether an update of the diagnostic counters is requested or not
 *	@param[in] u8Valid value to indicate whether the update should happen only on validated data
 *
 *  @return status of the command request
 *
 *  @note This wrapper updates the operational status structure on request and if
 *         command request resulted in valid data.
 *
 *         Data is read first into a temporary location and if this data is found
 *         to be valid (by expecting OK from the communication and a valid first byte)
 *         it is written in the operational status structure.
 */
eCubeADCS_Comm_Status_t CubeADCS_SendCmdWithChecks(CubeADCS_CmdCfg_t *sCmd, uint8_t u8Update, uint8_t u8Valid);

/** @brief Set R-Wheels speed to 0 RPM */
void CubeADCS_StopRWheels(void);

/** @brief Change the multiplier of the rate sensor measurement
 *
 *  @param[in] u8RateSensMult the new value for the multiplier
 */
void CubeADCS_ChngRateSensorMult(eCUBE_ADCS_TC_23_RATE_SENSOR_MULT_t u8RateSensMult);

/** @brief Clear latched-up error flags in the CubeADCS
 *
 *  @note This function is typically called after successful communication (TLMs) and
 *   	  the CubeADCS is expected to be working normally.
 */
void CubeADCS_ClrErrFlags(void);

/** @brief Change the sampling mode of the magnetometer
 *
 *  @param[in] eMtmMode the new sampling mode
 */
void CubeADCS_ChngMtmSampling(eCUBE_ADCS_TC_56_MTM_MODE_t eMtmMode);

/** @brief Get the Node Control Status that was requested by the OBC
 *
 *  @return the node control status telemetry frame (TLM197)
 */
CubeADCS_TLM197_t cubeadcs_get_node_cntrl_status(void);

/** @brief Get the last node control status as read by the OBC in the operational status
 *
 *  @return the node control status telemetry frame (TLM197)
 */
CubeADCS_TLM197_t cubeadcs_get_last_pwr_cntrl_tlmtr_data(void);

/** @brief Get a specific telemetry frame from the operational status
 *
 *  @return pointer to the command details (context)
 */
CubeADCS_CmdCfg_t *CubeADCS_GetHCheckCmdDetails(eCubeADCS_IDLE_STATE_CMD_List_t eCmdId);

/** @brief Get the main CubeADCS thread handle
 *
 *  @return the thread ID
 */
osThreadId_t CubeADCS_GetThreadHandle(void);

/** @brief Accumulate angular velocity samples into an average value
 *
 *
 *  @param[in] eMeasType type of angular rate measurement
 *  @param[in] u8SCntToDecision number of samples to be gathered before an average values is produced
 *  @param[out] sAvrgAngVel pointer to destination location to store the computed average
 *
 *  @retval ERR: Not enough samples gathered or an error occurred
 *  @retval OK: Enough samples gathered
 *
 *  @note The function has to be called periodically to get a sample of the angular rate. The average value is stored internally.
 */
eCubeADCS_StdRply CubeADCS_GetAvrgAngVel(CubeADCS_AngRateFormatted_t *sAvrgAngVel, eCubeADCS_AngRateType_t eMeasType, uint8_t u8SCntToDecision);

/** @brief Get the quaternion error vector formatted
 *
 *  @retval ERR: Failure
 *  @retval OK: Success
 *
 *  @note TLM163, formatted
 */
eCubeADCS_StdRply CubeADCS_GetQErrFormatted(CubeADCS_QErrFormatted_t *sQErr);

/** @brief Set the reference for specific system state and start it
 *
 *  @retval False: Failure
 *  @retval True: Success
 *
 *  @note This function uses TC55 to set the target reference coordinates or stashes the RPY angles for when performing
 */
bool cubeadcs_set_sys_state_and_ref(cubeadcs_ref_t *p_ref, eCubeADCS_CfgType new_sys_cfg);

/** @brief Set a new ADCS system configuration and execute it based on request
 *
 *  @param[in] eNewADCSCfg new_sys_cfg - the new system configuration
 *  @param[in] bool exec_state_req - execute the requested state change
 */
void cubeadcs_set_state_cfg(eCubeADCS_CfgType new_sys_cfg, bool exec_state_req);

/** @brief Get the last set ADCS System State Configuration
 *
 *  @param[out] peADCSCfg pointer to the destination to store the read adcs system state configuration
 */
void cubeadcs_get_adcs_state_cfg(CubeADCS_SysSCfg_t * const peADCSCfg);

/** @brief Get the currently set magnetometer sampling mode
 *
 *  @return the current magnetometer sampling mode
 */
eCUBE_ADCS_TC_56_MTM_MODE_t CubeADCS_GetMTMSamplingMode(void);

/** @brief Set SGP4 Orbit Parameters
 *
 *  @param[in] sOrbitParams pointer to the orbit parameters
 *
 *  @return operation result
 */
eCubeADCS_StdRply CubeADCS_SetSGP4OrbitParams(CubeADCS_SGP4_Orbit_Params_t * const sOrbitParams);

/** @brief Get SGP4 Orbit Parameters
 *
 *  @param[out] sOrbitParams pointer to the orbit parameters destination
 *
 *  @return operation result
 */
eCubeADCS_StdRply CubeADCS_GetSGP4OrbitParams(CubeADCS_SGP4_Orbit_Params_t * const sOrbitParams);

/** @brief Update UNIX time
 *
 *  @param[in] psNewUnixTime pointer to the new UNIX time
 *
 *  @return operation result
 */
eCubeADCS_StdRply cubeadcs_update_unix_time(CubeADCS_UnixTime_t * const psNewUnixTime);

/** @brief Get current UNIX time
 *
 *  @param[out] psCurrentUnixTime pointer to the destination to store the read unix time
 *
 *  @return operation result
 */
eCubeADCS_StdRply cubeadcs_get_unix_time(CubeADCS_UnixTime_t * const psCurrentUnixTime);

/** @brief Get the runtime latched errors of the CubeADCS from the operational status
 *
 *  @param[out] u16Dst pointer to the destination to store the read errors
 *
 *  @retval true: On successful read operation
 *  @retval false: On failure
 */
bool cubeadcs_get_latched_err(uint16_t *u16Dst);

/** @brief Set the runtime latched errors of the CubeADCS to the operational status
 *
 *  @param[in] uint16_t const *p_src pointer to the data to store
 *
 *  @retval true: On successful read operation
 *  @retval false: On failure
 */
bool cubeadcs_set_latched_err(uint16_t const *p_src);

/** @brief Lock access to the operational status data
 *
 *  @param[in] u32WaitTimeMS time to wait to acquire a lock
 *
 *  @retval true: On successful lock
 *  @retval false: On failure
 */
bool cubeadcs_lock_data_access(uint32_t u32WaitTimeMS);

/** @brief Unlock access to the operational status data
 *
 *  @retval true: On successful unlock
 *  @retval false: On failure to unlock
 */
bool cubeadcs_unlock_data_access(void);

/** @brief Get estimated angular rate from the CubeADCS in [mrad/s]
 *
 *  @param[out] psAngRate pointer to destination to store read data
 *
 *  @retval true: On operation success
 *  @retval false: On operation failure
 *
 *  @note Uses TLM147 to get the estimated angular rate, formats it in [rad/s] and
 * 		  converts it to [mrad/s]
 */
bool cubeadcs_get_est_ang_rate(CubeADCS_AngRate_Formatted_t * const psAngRate);

/** @brief Get estimated angular rate norm and per axis value
 *
 *  @param[out] psDst pointer to destination to store read data
 *
 *  @retval true: On operation success
 *  @retval false: On operation failure
 *
 *  @note Uses TLM147 to get the estimated angular rate and computes the norm.
 * 		  Data is copied - norm first, per axis next.
 */
bool cubeadcs_get_est_ang_rate_complete(CubeADCS_AngRate_Complete_t * const psDst);

/** @brief Get estimated attitude angles formatted from the CubeADCS in [mdeg]
 *
 *  @param[out] psEstAttAng pointer to destination to store read data
 *
 *  @retval true: On operation success
 *  @retval false: On operation failure
 *
 *  @note Uses TLM146 to get the estimated attitude angles. Formats the values and
 * 		  presents them as int32. Original value is raw, if multiplied by 0.01 it will
 * 		  output the result in deg as a floating number. Since we want to work with integers
 * 		  we multiply by 10 to get [mdeg].
 */
bool cubeadcs_get_est_att_angles(cubeadcs_est_att_ang_fmt_t * const psEstAttAng);

/** @brief Resets the CubeADCS and puts it in either bootloader or ACP
 *
 *  @param[in] eMode mode request after reset
 *
 *  @retval true: On operation success
 *  @retval false: On operation failure
 */
bool cubeadcs_reset(eCubeADCS_Mode_t eMode);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* CUBEADCS_H */

/* ******************************************************************************************* */
