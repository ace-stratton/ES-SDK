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
 * @defgroup service_exeh Exception Handling
 * @{
 *
 * The service provides:
 * - Basic exception tracing capability.
 * - Storage of exceptions in a cyclic file buffer on the SD card.
 *
 * @subsection exeh_usage How to use the service?
 *
 * In order to use the service, there are a few basic steps you need to take:
 * - Define one or more module IDs to be used for exception reporting (one module corresponds to one physical file) in es_exeh_cfg.h
 * by extending the @ref eEXEHModuleID_t type.
 * @emoji :heavy-exclamation-mark: Make sure to add your new entry before the @ref eEXEHModuelID_COUNT item.
 *
 * @code {.c}
 * typedef enum
 * {
 *      // ...
 *      eEXEHModuleID_MyModule_File1    // <-- this is your new entry
 *      eEXEHModuleID_COUNT
 * } eEXEHModuleID_t;
 * @endcode
 *
 * - Extend the list of user-defined types in es_exeh_cfg.h with a custom list of enum values matching the
 * specific exception events that you want to report for your modules.
 *
 * @code {.c}
 * typedef enum
 * {
 *      eEXEH_MyModule_File1_ERROR1,
 *      eEXEH_MyModule_File1_ERROR2,
 * }
 * eEXEH_MyModule_File1_ExceptionID_t;
 * @endcode
 *
 * You are now ready to use your custom exceptions in your own module implementation. Here is an example code snippet:
 *
 * @code {.c}
 * #include "es_exeh.h"
 *
 * // make a single error report by explicitly specifying the module ID
 * EXEH_HANDLE_EX(eEXEHSeverity_Error, eEXEHModuleID_MyModule_File1, (int32_t) eEXEH_MyModule_File1_ERROR1);
 * @endcode
 *
 * In case you have many reports in your file, you can use a shorter version of the reporting macro as follows:
 * @code {.c}
 * #include "es_exeh.h"
 *
 * // at the beginning of your module file, make an association to the module ID which will be used in
 * // this file
 * #define EXEH_CURRENT_MODULE_ID eEXEHModuleID_MyModule_File1
 *
 * // make a single error report with the shorter macro which doesn't specify the module ID
 * EXEH_HANDLE(eEXEHSeverity_Error, (int32_t) eEXEH_MyModule_File1_ERROR1);
 * @endcode
 *
 * @file es_exeh.h
 * @brief Exception storage and handling. Used for storing and reporting basic exceptions.
 *
 * @}
 * @}
 */
#ifndef OBC_ES_EXEH_H
#define OBC_ES_EXEH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "es_cdef.h"
#include "es_exeh_cfg.h"

/** @brief Generic macro used to report exceptions
 *
 *  @note The macro stores the line of code where the exception report occurred automatically.
 *
 *  @param L Exception severity level
 *  @param M Module ID for which to report an exception
 *  @param E Exception ID
*/
#define EXEH_HANDLE_EX(L, M, E) \
{                                            \
    EXEH_InitModuleFileName(M, __FILE__);    \
    EXEH_vException(L, M, E, __LINE__);      \
}

/** @brief Simpler version of the #EXEH_HANDLE_EX(L, M, E) macro where the module ID is not explicitly
  * specified but is assumed to be defined in the same module under the name of `EXEH_CURRENT_MODULE_ID`
  *
  * @param L Exception severity level
  * @param E Exception ID
  *
  * @note The macro stores the line of code where the exception report occurred automatically.
  */
#define EXEH_HANDLE(L, E)                  EXEH_vException(L, EXEH_CURRENT_MODULE_ID, E, __LINE__)

/**
 * @brief Macro used to associate the file name from which the macro is used to the module ID defined by
 * the `EXEH_CURRENT_MODULE_ID` preprocessor symbol.
 *
 * @note `EXEH_CURRENT_MODULE_ID` shall be locally defined in any file after which reporting of exceptions
 * using #EXEH_HANDLE(L, E) macro in the same file can be used without specifying a module ID.
 *
 */
#define EXEH_INIT_MODULE_FILENAME()        EXEH_InitModuleFileName(EXEH_CURRENT_MODULE_ID, __FILE__)

/**
 * @brief Macro used to directly assign a module ID to the name of the file in which the macro was called.
 *
 * @param M Module ID
 */
#define EXEH_INIT_MODULE_FILENAME_EX(M)    EXEH_InitModuleFileName(M, __FILE__)

/**
 * @brief Exception severity level enumeration.
 */
typedef enum
{
    eEXEHSeverity_Warning,          /**< Represents a warning in the system */
    eEXEHSeverity_Error,            /**< Represents an error in the system */
    eEXEHSeverity_Fatal,            /**< Represents an unrecoverable error in the system */
    eEXEHSeverity_Count             /**< The value is used for range checking only */
}eEXEHSeverityLevel_t;

/**
 * @brief Defines the fields stored for a user-exception event
 *
 */
typedef struct
{
#if EXEH_CONFIG_EVENT_TIMESTAMP_ENABLED == 1
    // tick count from system start
    uint32_t u32Timestamp;              /**< Number of ticks from system boot when the event was logged */
#endif
    int32_t  s32Exception;              /**< User-defined exception ID */
    uint32_t u32LineNumber;             /**< Line number where the exception event occurred */
} PACKED sEXEHException_t;

/**
 * @brief Defines the trace data stored for a single module ID
 *
 */
typedef struct
{
#if EXEH_CONFIG_STORE_FILENAME_ENABLED == 1
    char fileName[FNAME_SIZE];          /**< Name of the file where the event was reported */
#endif
    sEXEHException_t warnings[WARN_SLOTS_COUNT];    /**< Last few warning events reported */
    sEXEHException_t errors[ERROR_SLOTS_COUNT];     /**< Last few error events reported */
    sEXEHException_t fatals[FATAL_SLOTS_COUNT];     /**< Last few fatal events reported */
} PACKED sEXEHModuleExceptions_t;

/**
 * @brief Request storing of exception with level and a user supplied ID.
 * @param fp_eLevel Exception severity level ID
 * @param fp_eModuleID  ID of the module reporting the exception
 * @param fp_s32ExceptionID A user defined exception ID <i>(this field does not have any meaning for the EXEH service)</i>
 * @param fp_u32FileLineNo  Line number in the file where the exception was reported
 */
void EXEH_vException(eEXEHSeverityLevel_t fp_eLevel,
                     eEXEHModuleID_t      fp_eModuleID,
                     int32_t              fp_s32ExceptionID,
                     uint32_t             fp_u32FileLineNo);

/**
 * @brief Gets the number of exceptions stored for a give exception level
 * @param fp_eLevel The level to get the count for
 * @return Number of exceptions for the requested #fp_eLevel.
 */
uint32_t EXEH_u32GetExceptionCount(eEXEHSeverityLevel_t fp_eLevel);

/**
 * Copies all stored exceptions to a binary buffer provided by the user
 * @param fp_psOutArray A pointer to the buffer where the exceptions data shall be stored
 * @param fp_u32OutArraySize The size of the provided #fp_psOutArray array
 * @return Number of bytes returned
 */
uint32_t EXEH_u32GetExceptions(const eEXEHModuleID_t fp_eModuleID,
                               uint8_t* const fp_psOutArray,
                               const uint32_t fp_u32OutArraySize);

/**
 * @brief Initializes the service.
 * @return `true` on success, `false` - otherwise
 */
bool EXEH_bInit(void);

/**
 * @brief Start the task which persists the EXEH information to the SD card.
 * @return none
 */
void EXEH_bStartPersistorTask(void);

/**
 * @brief Attempts to immediately persist the currently stored exceptions.
 */
void EXEH_ForcePersistExceptions(void);

/**
 * @brief Associates a file name with a module ID.
 *
 * @param fp_eModuleID Module identifier
 * @param fp_pcFileName File name to associate to #fp_eModuleID
 * @note Should be called only once as subsequent calls do not have any effect.
 */
void EXEH_InitModuleFileName(eEXEHModuleID_t fp_eModuleID, const char* const fp_pcFileName);

#ifdef __cplusplus
}
#endif

#endif //OBC_ES_EXEH_H
