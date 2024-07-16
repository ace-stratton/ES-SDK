/*!
********************************************************************************************
* @file FP_nvm_bpProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface nvm_bp v0.1
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

#ifndef __FP_NVM_BPPROTOCOLTYPES_H__
#define __FP_NVM_BPPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_NVM_BP ((uint16_t) (0x0000001E))

#define NVM_BP_SET_EPS_BP_MAC_ADDRESS_FUNC_ID ((funcIdType_t) 0x00000001)
#define NVM_BP_GET_EPS_BP_MAC_ADDRESS_FUNC_ID ((funcIdType_t) 0x00000002)
#define NVM_BP_SET_EPS_BP_MAC_ADDRESS_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define NVM_BP_GET_EPS_BP_MAC_ADDRESS_FUNCRESP_ID ((funcIdType_t) 0x00000002)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    General status type used for SW-related communication and/or settings.
*/
#define NVM_BP_STANDARDRESULT_SUCCESS ((uint8_t) 0)
#define NVM_BP_STANDARDRESULT_ERROR ((uint8_t) 1)
#define NVM_BP_STANDARDRESULT_INVALID_ARGS ((uint8_t) 2)
#define NVM_BP_STANDARDRESULT_NOT_SUPPORTED ((uint8_t) 3)
#define NVM_BP_STANDARDRESULT_MAX_CNT  ((uint8_t) 4)
typedef uint8_t NVM_BP_StandardResult_t;

/*
    EPS Battery Pack IDs. Here is an extensive list of all possible IDs of the BPs in a system. 
        Depending on count of the EPS BPs in the specific configuration only the first N of those will be used.
*/
#define NVM_BP_EPSBPIDTYPE_EPS_BP_0 ((uint8_t) 0)
#define NVM_BP_EPSBPIDTYPE_EPS_BP_1 ((uint8_t) 1)
#define NVM_BP_EPSBPIDTYPE_EPS_BP_2 ((uint8_t) 2)
#define NVM_BP_EPSBPIDTYPE_MAX_CNT  ((uint8_t) 3)
typedef uint8_t NVM_BP_EpsBpIdType_t;


typedef struct {
    uint8_t u8New_mac_address;
    NVM_BP_EpsBpIdType_t eDevice_id;
} PACKED_STRUCT nvm_bpset_eps_bp_mac_addressRequestData_t;

typedef struct {
    NVM_BP_EpsBpIdType_t eDevice_id;
} PACKED_STRUCT nvm_bpget_eps_bp_mac_addressRequestData_t;


typedef struct {
    NVM_BP_StandardResult_t eOp_result;
} PACKED_STRUCT nvm_bpset_eps_bp_mac_addressResponseData_t;

typedef struct {
    uint8_t u8Mac_address;
    NVM_BP_StandardResult_t eOp_result;
} PACKED_STRUCT nvm_bpget_eps_bp_mac_addressResponseData_t;


#endif  // #ifndef __FP_NVM_BPPROTOCOLTYPES_H__

