/*!
********************************************************************************************
* @file ESSA_EPS1Protocol.h
* @brief Header file for ESSA_EPS1Protocol.c
********************************************************************************************
* @author            Anton Tkachenko
* @version           1.0.0
* @date              2020.09.15
*
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
* @history
* @revision{         1.0.0  , 2020.09.15, author Anton Tkachenko, Initial revision }
* @endhistory
********************************************************************************************
*/
#ifndef __ES_SAT_API_EPS1_PROTOCOL_MAC_HEADER_INCLUDED_H_
#define __ES_SAT_API_EPS1_PROTOCOL_MAC_HEADER_INCLUDED_H_

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include <stdint.h>

#include "../include/ESSA_Stack.h"
#include "../include/ESSA_EPS1.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/
#define ESSA_REQ_RESP_OFFSET                        (0x80u)  // TODO: TBD: 125? 128? Move to Stack?

#define ESSA_EPS1_REQUEST_VERSION_ID                ((uint8_t)  0)
#define ESSA_EPS1_REQUEST_SOFTWARE_VER_ID           ((uint8_t) 50)   // TODO: TBD: leave a gap for sys routines?
#define ESSA_EPS1_REQUEST_BATTERY_ID                ((uint8_t) 51)
#define ESSA_EPS1_REQUEST_SOLARPANELS_ID            ((uint8_t) 52)
#define ESSA_EPS1_REQUEST_STATISTICS_ID             ((uint8_t) 53)
#define ESSA_EPS1_REQUEST_TEMPERATURES_ID           ((uint8_t) 54)
#define ESSA_EPS1_REQUEST_CONFIGURATION_ID          ((uint8_t) 55)
#define ESSA_EPS1_REQUEST_ID_WRITE_FIRST            (ESSA_EPS1_REQUEST_CONFIGURATION_ID + 1u)

#define ESSA_EPS1_REQUEST_CONTROL_ID                (ESSA_EPS1_REQUEST_ID_WRITE_FIRST + 0u)
#define ESSA_EPS1_REQUEST_RBAT_RAW_ID               (ESSA_EPS1_REQUEST_ID_WRITE_FIRST + 1u)

#define ESSA_EPS1_RESPONSE_VERSION_ID               ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_VERSION_ID       ))
#define ESSA_EPS1_RESPONSE_SOFTWARE_VER_ID          ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_SOFTWARE_VER_ID  ))
#define ESSA_EPS1_RESPONSE_BATTERY_ID               ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_BATTERY_ID       ))
#define ESSA_EPS1_RESPONSE_SOLARPANELS_ID           ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_SOLARPANELS_ID   ))
#define ESSA_EPS1_RESPONSE_STATISTICS_ID            ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_STATISTICS_ID    ))
#define ESSA_EPS1_RESPONSE_TEMPERATURES_ID          ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_TEMPERATURES_ID  ))
#define ESSA_EPS1_RESPONSE_CONFIGURATION_ID         ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_CONFIGURATION_ID ))

#define ESSA_EPS1_RESPONSE_CONTROL_ID               ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_CONTROL_ID ))
#define ESSA_EPS1_RESPONSE_RBAT_RAW_ID              ((uint8_t) (ESSA_REQ_RESP_OFFSET + ESSA_EPS1_REQUEST_RBAT_RAW_ID ))

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/

typedef struct
{
    uint8_t u8FuncId;
} __attribute__((__packed__)) ESSA_EPS1Protocol_RequestHdr_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t Hdr;
} __attribute__((__packed__)) ESSA_EPS1Protocol_RequestData_t;

typedef ESSA_EPS1Protocol_RequestData_t ESSA_EPS1Protocol_RequestVersion_t;
typedef ESSA_EPS1Protocol_RequestData_t ESSA_EPS1Protocol_RequestBatteryInfo_t;
typedef ESSA_EPS1Protocol_RequestData_t ESSA_EPS1Protocol_RequestSolarPanelInfo_t;
typedef ESSA_EPS1Protocol_RequestData_t ESSA_EPS1Protocol_RequestStatistics_t;
typedef ESSA_EPS1Protocol_RequestData_t ESSA_EPS1Protocol_RequestTemperatures_t;
typedef ESSA_EPS1Protocol_RequestData_t ESSA_EPS1Protocol_RequestConfiguration_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_RequestControl_t        Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_RequestControl_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_RequestRBattRaw_t       Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_RequestRBattRaw_t;

// Responses
typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseVersion_t       Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseVersion_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseSoftwareVer_t   Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseSoftwareVer_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseBatteryInfo_t   Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseBatteryInfo_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseSolarPanels_t   Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseSolarPanels_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseStatistics_t    Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseStatistics_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseTemperatures_t  Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseTemperatures_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseConfiguration_t Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseConfiguration_t;

typedef struct {
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseControl_t       Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseControl_t;

typedef struct
{
    ESSA_EPS1Protocol_RequestHdr_t    Hdr;
    ESSA_EPS1_ResponseRBattRaw_t      Data;
} __attribute__((__packed__)) ESSA_EPS1Protocol_ResponseRBattRaw_t;

/*
********************************************************************************************
* EXTERNAL VARIABLES DECLARATIONS
********************************************************************************************
*/
/* No External variables declarations */

/*
********************************************************************************************
* EXTERNAL ROUTINES DECLARATIONS
********************************************************************************************
*/

ESSA_pStack_ProtocolInfo_t ESSA_StackEPS1Protocol(void);

#endif // __ES_SAT_API_EPS1_PROTOCOL_MAC_HEADER_INCLUDED_H_
/* ******************************************************************************************* */
