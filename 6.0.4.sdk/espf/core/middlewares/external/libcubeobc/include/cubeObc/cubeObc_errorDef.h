/** @file cubeObc_errorDef.h
 *
 * @brief Error Definitions for libCubeObc
 *
 * @par
 * COPYRIGHT NOTICE: (c) 2023 Cubespace ADCS All rights reserved.
 */

#ifndef CUBEOBC_ERROR_DEF__H
#define CUBEOBC_ERROR_DEF__H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** SYSTEM INCLUDES *******************************/

#include "cubeObc_typeDef.h"

/************************ DEPENDENT MODULE INCLUDES **************************/

/***************************** GLOBAL DEFINES ********************************/

#define CUBEOBC_ERROR_OK						((U32)0u)	/**< No error */

#define CUBEOBC_ERROR_NULLPTR					((U32)1u)	/**< NULL pointer */
#define CUBEOBC_ERROR_SIZE						((U32)2u)	/**< Size incorrect */
#define CUBEOBC_ERROR_SIZEL						((U32)3u)	/**< Size too low */
#define CUBEOBC_ERROR_SIZEH						((U32)4u)	/**< Size too high */
#define CUBEOBC_ERROR_OVRRUN					((U32)5u)	/**< Overrun */
#define CUBEOBC_ERROR_PARAM						((U32)6u)	/**< Parameter error (out of range) */
#define CUBEOBC_ERROR_TOUT						((U32)7u)	/**< Timeout */
#define CUBEOBC_ERROR_NACK						((U32)8u)	/**< TCTLM comms Nack */
#define CUBEOBC_ERROR_BUSY						((U32)9u)	/**< Busy */
#define CUBEOBC_ERROR_FRAME						((U32)10u)	/**< Frame */
#define CUBEOBC_ERROR_CRC						((U32)11u)	/**< CRC */
#define CUBEOBC_ERROR_READ						((U32)12u)	/**< Read */
#define CUBEOBC_ERROR_WRITE						((U32)13u)	/**< Write */
#define CUBEOBC_ERROR_CAN_ID					((U32)14u)	/**< CAN ID type error */
#define CUBEOBC_ERROR_CAN_ERR					((U32)15u)	/**< CAN frame error */
#define CUBEOBC_ERROR_UKN_NACK					((U32)16u)	/**< Unknown NACK */
#define CUBEOBC_ERROR_NODE_TYPE					((U32)17u)	/**< Invalid node type */
#define CUBEOBC_ERROR_FTP						((U32)18u)	/**< CubeSpace file upload internal error */
#define CUBEOBC_ERROR_USAGE						((U32)19u)	/**< Usage error */
#define CUBEOBC_ERROR_AUTOD						((U32)20u)	/**< Auto-Discovery error */
#define CUBEOBC_ERROR_IMG						((U32)21u)	/**< Image error */
#define CUBEOBC_ERROR_EXIST						((U32)22u)	/**< Does not exist error */
#define CUBEOBC_ERROR_USER_DATA					((U32)23u)	/**< User data error */
#define CUBEOBC_ERROR_COMMIT					((U32)24u)	/**< Commit error */
#define CUBEOBC_ERROR_TCTLM_PROTOCOL			((U32)25u)	/**< TCTLM protocol error */
#define CUBEOBC_ERROR_UNKNOWN					((U32)26u)	/**< General unexpected/unknown error */
#define CUBEOBC_ERROR_TLM_SIZE					((U32)27u)	/**< Telemetry response size error */
#define CUBEOBC_ERROR_TCTLM_ID					((U32)28u)	/**< TCTLM response ID does not match the request */

#define CUBEOBC_ERROR_TCTLM_INVALID_ID			((U32)50u)	/**< TCTLM Nack - invalid ID */
#define CUBEOBC_ERROR_TCTLM_INVALID_LENGTH		((U32)51u)	/**< TCTLM Nack - invalid length */
#define CUBEOBC_ERROR_TCTLM_INVALID_PARAM		((U32)52u)	/**< TCTLM Nack - invalid parameter data */
#define CUBEOBC_ERROR_TCTLM_CRC					((U32)53u)	/**< TCTLM Nack - CRC failed */
#define CUBEOBC_ERROR_TCTLM_NOT_IMPLEMENTED		((U32)54u)	/**< TCTLM Nack - not implemented */
#define CUBEOBC_ERROR_TCTLM_BUSY				((U32)55u)	/**< TCTLM Nack - busy */
#define CUBEOBC_ERROR_TCTLM_SEQUENCE			((U32)56u)	/**< TCTLM Nack - sequence */
#define CUBEOBC_ERROR_TCTLM_INTERNAL			((U32)57u)	/**< TCTLM Nack - internal */
#define CUBEOBC_ERROR_TCTLM_PASS_TOUT			((U32)58u)	/**< TCTLM Nack - pass-through timeout */
#define CUBEOBC_ERROR_TCTLM_PASS_TARGET			((U32)59u)	/**< TCTLM Nack - pass-through target */

#define CUBEOBC_ERROR_TODO						((U32)-1)	/**< Not implemented / TODO */

/**************************** GLOBAL CONSTANTS *******************************/

/****************************** GLOBAL MACROS ********************************/

/***************************** GLOBAL TYPEDEFS *******************************/

/***************************** GLOBAL VARIABLES ******************************/

/***************************** GLOBAL FUNCTIONS ******************************/

#ifdef __cplusplus
}
#endif
#endif							// CUBEOBC_ERROR_DEF__H
/*** end of file ***/
