/*!
********************************************************************************************
* @file FP_gnssProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface gnss v1.0
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

#ifndef __FP_GNSSPROTOCOLTYPES_H__
#define __FP_GNSSPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_GNSS ((uint16_t) (0x00000017))

#define GNSS_SET_POWER_FUNC_ID ((funcIdType_t) 0x00000001)
#define GNSS_GET_POWER_FUNC_ID ((funcIdType_t) 0x00000003)
#define GNSS_SET_POWER_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define GNSS_GET_POWER_FUNCRESP_ID ((funcIdType_t) 0x00000003)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Operation status
*/
#define GNSS_OPERATION_ERROR ((uint8_t) 0)
#define GNSS_OPERATION_OK ((uint8_t) 1)
#define GNSS_OPERATION_MAX_CNT  ((uint8_t) 2)
typedef uint8_t GNSS_operation_t;

/*
    GNSS power status
*/
#define GNSS_POWER_OFF ((uint8_t) 0)
#define GNSS_POWER_ON ((uint8_t) 1)
#define GNSS_POWER_MAX_CNT  ((uint8_t) 2)
typedef uint8_t GNSS_power_t;


typedef struct {
    GNSS_power_t ePwr_status;
} PACKED_STRUCT gnssset_powerRequestData_t;


typedef struct {
    GNSS_operation_t eOp_status;
} PACKED_STRUCT gnssset_powerResponseData_t;

typedef struct {
    GNSS_operation_t eOp_status;
    GNSS_power_t ePwr_status;
} PACKED_STRUCT gnssget_powerResponseData_t;


#endif  // #ifndef __FP_GNSSPROTOCOLTYPES_H__

