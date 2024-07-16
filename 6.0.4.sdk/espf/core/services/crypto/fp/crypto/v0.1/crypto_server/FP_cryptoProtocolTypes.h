/*!
********************************************************************************************
* @file FP_cryptoProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface crypto v0.1
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.12
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __FP_CRYPTOPROTOCOLTYPES_H__
#define __FP_CRYPTOPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_CRYPTO ((uint16_t) (0x00000104))

#define CRYPTO_UPDATE_KEY_STORE_FUNC_ID ((funcIdType_t) 0x00000000)
#define CRYPTO_PERFORM_CIPHER_OP_FUNC_ID ((funcIdType_t) 0x00000001)
#define CRYPTO_GET_CIPHER_OP_STATUS_FUNC_ID ((funcIdType_t) 0x00000002)
#define CRYPTO_ABORT_FUNC_ID ((funcIdType_t) 0x00000003)
#define CRYPTO_UPDATE_KEY_STORE_FUNCRESP_ID ((funcIdType_t) 0x00000000)
#define CRYPTO_PERFORM_CIPHER_OP_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define CRYPTO_GET_CIPHER_OP_STATUS_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define CRYPTO_ABORT_FUNCRESP_ID ((funcIdType_t) 0x00000003)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
#define CRYPTO_KEY_UPDATE_STATUS_BAD_SIZE ((uint8_t) 0)
#define CRYPTO_KEY_UPDATE_STATUS_STORE_ERROR ((uint8_t) 1)
#define CRYPTO_KEY_UPDATE_STATUS_OK ((uint8_t) 2)
#define CRYPTO_KEY_UPDATE_STATUS_MAX_CNT  ((uint8_t) 3)
typedef uint8_t CRYPTO_key_update_status_t;

#define CRYPTO_CIPHER_OP_TYPE_ENCRYPT ((uint8_t) 0)
#define CRYPTO_CIPHER_OP_TYPE_DECRYPT ((uint8_t) 1)
#define CRYPTO_CIPHER_OP_TYPE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t CRYPTO_cipher_op_type_t;

#define CRYPTO_CIPHER_OP_STATUS_EOS ((uint8_t) 0)
#define CRYPTO_CIPHER_OP_STATUS_INVALID_HEADER ((uint8_t) 1)
#define CRYPTO_CIPHER_OP_STATUS_INVALID_FOOTER ((uint8_t) 2)
#define CRYPTO_CIPHER_OP_STATUS_INVALID_CIPHER_OFS ((uint8_t) 3)
#define CRYPTO_CIPHER_OP_STATUS_FILE_ERROR ((uint8_t) 4)
#define CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_ERROR ((uint8_t) 5)
#define CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_KEY_ERROR ((uint8_t) 6)
#define CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_IV_ERROR ((uint8_t) 7)
#define CRYPTO_CIPHER_OP_STATUS_CRYPTOLIB_AAD_ERROR ((uint8_t) 8)
#define CRYPTO_CIPHER_OP_STATUS_PARTIAL_FILE ((uint8_t) 9)
#define CRYPTO_CIPHER_OP_STATUS_AUTH_ERROR ((uint8_t) 10)
#define CRYPTO_CIPHER_OP_STATUS_BAD_PARAMS ((uint8_t) 11)
#define CRYPTO_CIPHER_OP_STATUS_NO_KEY ((uint8_t) 12)
#define CRYPTO_CIPHER_OP_STATUS_ABORTED ((uint8_t) 13)
#define CRYPTO_CIPHER_OP_STATUS_ERROR ((uint8_t) 14)
#define CRYPTO_CIPHER_OP_STATUS_NO_FILE ((uint8_t) 15)
#define CRYPTO_CIPHER_OP_STATUS_BUSY ((uint8_t) 16)
#define CRYPTO_CIPHER_OP_STATUS_OK ((uint8_t) 17)
#define CRYPTO_CIPHER_OP_STATUS_MAX_CNT  ((uint8_t) 18)
typedef uint8_t CRYPTO_cipher_op_status_t;

#define CRYPTO_ABORT_TYPE_CURRENT_ONLY ((uint8_t) 0)
#define CRYPTO_ABORT_TYPE_ALL ((uint8_t) 1)
#define CRYPTO_ABORT_TYPE_MAX_CNT  ((uint8_t) 2)
typedef uint8_t CRYPTO_abort_type_t;


typedef struct {
    uint8_t u8KeySize;
    uint8_t au8Key[32];
} PACKED_STRUCT cryptoupdate_key_storeRequestData_t;

typedef struct {
    CRYPTO_cipher_op_type_t eCipher_op;
    uint8_t u8Src_file_nameSize;
    char strSrc_file_name[47];
    uint8_t u8Target_file_nameSize;
    char strTarget_file_name[47];
} PACKED_STRUCT cryptoperform_cipher_opRequestData_t;

typedef struct {
    CRYPTO_abort_type_t eOp_type;
} PACKED_STRUCT cryptoabortRequestData_t;


typedef struct {
    CRYPTO_key_update_status_t eOp_result;
} PACKED_STRUCT cryptoupdate_key_storeResponseData_t;

typedef struct {
    CRYPTO_cipher_op_status_t eCipher_req_status;
} PACKED_STRUCT cryptoperform_cipher_opResponseData_t;

typedef struct {
    CRYPTO_cipher_op_status_t eCipher_op_status;
    uint32_t u32Op_time;
} PACKED_STRUCT cryptoget_cipher_op_statusResponseData_t;

typedef struct {
    bool bStatus;
} PACKED_STRUCT cryptoabortResponseData_t;


#endif  // #ifndef __FP_CRYPTOPROTOCOLTYPES_H__

