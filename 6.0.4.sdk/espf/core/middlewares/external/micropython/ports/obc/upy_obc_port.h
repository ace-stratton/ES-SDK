#ifndef UPY_OBC_PORT_H_
#define UPY_OBC_PORT_H_

/**
 * \enum
 * \brief enumerator used for return type of most of the interfaces provided by
 * OBC port of Micropython
 *
 */
typedef enum
{
    UPY_OK,                 /**< UPY_OK */
    UPY_ERROR,              /**< UPY_ERROR */
    UPY_QUEUE_FULL,         /**< UPY_QUEUE_FULL */
    UPY_WRONG_PARAMS,       /**< UPY_WRONG_PARAMS */
    UPY_PROCESSING,         /**< UPY_PROCESSING */
    UPY_PENDING,            /**< UPY_PENDING */
    UPY_SCRIPT_NOT_FOUND,   /**< UPY_SCRIPT_NOT_FOUND */
    UPY_SCRIPT_TIMED_OUT,   /**< UPY_SCRIPT_TIMED_OUT */
    UPY_CNT                 /**< UPY_CNT */
} eObcPortResult_t;

/**
 * \fn eObcPortResult_t uPyRun(const char* const, uint8_t)
 * \brief Interface providing a way to run script in Micropython from C code
 *
 * \param fp_pScriptName - The script file name. It shall be a null terminated
 * string.
 * \param fp_u8NameLen
 * \return
 */
eObcPortResult_t
uPyRun(const char *const fp_pScriptName, uint8_t fp_u8NameLen);

#endif // UPY_OBC_PORT_PORT_H_
