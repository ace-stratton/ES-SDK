/*!
********************************************************************************************
* @file ESSA_EPS1.h
* @brief Helper header file contains types for MAC protocol of EPS1
********************************************************************************************
* @author            Anton Tkachenko
* @version           1.0.0
* @date              2020.09.08
*
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
* @history
* @revision{         1.0.0  , 2020.09.08, author Anton Tkachenko, Initial revision }
* @endhistory
********************************************************************************************
*/
#ifndef __ES_SAT_API_EPS1_MAC_HEADER_INCLUDED_H_
#define __ES_SAT_API_EPS1_MAC_HEADER_INCLUDED_H_

/*
********************************************************************************************
* INCLUDES
********************************************************************************************
*/
#include <stdint.h>
#include "ESSA_Stack.h"

/*
********************************************************************************************
* EXTERNAL DEFINES
********************************************************************************************
*/

// Word #1, 2 bytes per Cmd, 0b00 - OFF, 0b01 - ON, 0b11 - Do Not Change
#define ESSA_EPS1_CONTROL_S_ON          (0b1001u)
#define ESSA_EPS1_CONTROL_S_OFF         (0b1000u)
#define ESSA_EPS1_CONTROL_H_ON          (0b1011u)
#define ESSA_EPS1_CONTROL_H_OFF         (0b1010u)

/*
********************************************************************************************
* EXTERNAL TYPES DECLARATIONS
********************************************************************************************
*/
typedef uint16_t rbat_t;
typedef uint32_t counter_t;

typedef struct
{
    union __attribute__((__packed__)) {
    // Word #1, I2C Cmds 0x00..0x07
        struct __attribute__((__packed__)) {
            union __attribute__((__packed__)) {
                struct __attribute__((__packed__)) {
                    uint16_t ctlSWSelfLock              :2;
                    uint16_t ctlVBattEn                 :2;
                    uint16_t ctlBCROutEn                :2;
                    uint16_t ctlSHD_3v3                 :2;
                    uint16_t ctlSHD_5V                  :2;
                    uint16_t ctlLUP3v3                  :2;
                    uint16_t ctlLUP5V                   :2;
                    uint16_t ctlSHDChrg                 :2;
                };
                uint16_t word_1;
            };

            // Word #2, I2C Cmds 0x08..0x0F
            union __attribute__((__packed__)) {
                struct __attribute__((__packed__)) {
                    uint16_t ctlChrg_I1                 :2;
                    uint16_t ctlChrg_I2                 :2;
                    uint16_t ctlOUT1                    :2;
                    uint16_t ctlOUT2                    :2;
                    uint16_t ctlOUT3                    :2;
                    uint16_t ctlOUT4                    :2;
                    uint16_t ctlOUT5                    :2;
                    uint16_t ctlOUT6                    :2;
                };
                uint16_t word_2;
            };

            // Word #3, I2C Cmds 0x10..0x05 + 2x2 reserved
            union __attribute__((__packed__)) {
                struct __attribute__((__packed__)) {
                    uint16_t ctlHeater_1                :2;
                    uint16_t ctlHeater_2                :2;
                    uint16_t ctlHeater_3                :2;
                    uint16_t ctl10kOhmPU                :2;
                    uint16_t ctl4k7OhmPU                :2;
                    uint16_t ctlRs485TRes               :2;
                    uint16_t reserved                   :4;
                };
                uint16_t word_3;
            };
        };
        uint16_t words[3];
    };

} __attribute__((__packed__)) ESSA_EPS1_RequestControl_t;

typedef struct
{
    rbat_t resistance;
} __attribute__((__packed__)) ESSA_EPS1_RequestRBattRaw_t;

// Responses
typedef struct
{
    uint8_t  status;
} __attribute__((__packed__)) ESSA_EPS1_ResponseStatus_t;

typedef struct {
    uint8_t  u8VersionMajor;
    uint16_t u16VersionMinor;
} __attribute__((__packed__)) ESSA_EPS1_ResponseVersion_t;

// XXX: here I am working ATM
typedef struct {
    uint16_t volt;
    uint16_t curr;
} __attribute__((__packed__)) Pair_VA_t;

typedef struct {
    uint16_t volt;
    uint16_t curr_neg;
    uint16_t curr_pos;
} __attribute__((__packed__)) Pack_VAA_t;

typedef struct {
    union {
        struct {
            uint8_t major;
            uint8_t minor;
        } ver;
        uint16_t version;
    };
    uint16_t build;
} __attribute__((__packed__)) ESSA_EPS1_ResponseSoftwareVer_t;

typedef struct {
    Pair_VA_t batt;
    Pair_VA_t bcr;
    Pair_VA_t bus_3v3;
    Pair_VA_t bus_5v;
} __attribute__((__packed__)) ESSA_EPS1_ResponseBatteryInfo_t;

typedef struct {
    Pack_VAA_t x;
    Pack_VAA_t y;
    Pack_VAA_t z;
} __attribute__((__packed__)) ESSA_EPS1_ResponseSolarPanels_t;

typedef struct {
    uint16_t lup_3v3_volt;
    uint16_t lup_5v_volt;

    struct {
        uint32_t powerOn;        // TODO: uint32_t ?
        uint32_t chargeCycles;   // ?
        uint32_t underVolt;      // TODO: uint32_t ?
        uint32_t shortCircuit;   // TODO: uint32_t ?
        uint32_t overTemp;       // TODO: uint32_t ?
    } __attribute__((__packed__)) counters;

    uint16_t maxTemp[4];        // TODO: uint16_t ?
    uint16_t minTemp[4];        // TODO: uint16_t ?

    struct {
        rbat_t initial;
        rbat_t current;
    } __attribute__((__packed__)) rbat;

    uint16_t   vbat_ideal;

    uint16_t                        :16;    // reserved

    uint32_t   uptime;          // TODO: here? really?
} __attribute__((__packed__)) ESSA_EPS1_ResponseStatistics_t;

typedef struct {
    uint16_t mcu;
    uint16_t batt[8u];          // sensors 1..7, +N8 reserved
} __attribute__((__packed__)) ESSA_EPS1_ResponseTemperatures_t;

// TODO: consider to drop some parts out
typedef struct {
    uint16_t inputConditions;
    uint16_t outputConditions;
    uint16_t outputConditions_2;
    uint16_t defaultLups;
    uint16_t defaultOutputs;
} __attribute__((__packed__)) ESSA_EPS1_ResponseConfiguration_t;

typedef ESSA_EPS1_RequestControl_t ESSA_EPS1_ResponseControl_t;

typedef struct
{
    rbat_t   resistance;                // TODO: check if we need one
} __attribute__((__packed__)) ESSA_EPS1_ResponseRBattRaw_t;

// handlers

typedef void (*pfESSA_EPS1funcReqVersion_t)(ESSA_EPS1_ResponseVersion_t *res);
typedef void (*pfESSA_EPS1funcReqSoftwareVersion_t)(ESSA_EPS1_ResponseSoftwareVer_t *res);
typedef void (*pfESSA_EPS1funcReqBatteryInfo_t)(ESSA_EPS1_ResponseBatteryInfo_t *res);
typedef void (*pfESSA_EPS1funcReqSolarPanelsInfo_t)(ESSA_EPS1_ResponseSolarPanels_t *res);
typedef void (*pfESSA_EPS1funcReqStatistics_t)(ESSA_EPS1_ResponseStatistics_t *res);
typedef void (*pfESSA_EPS1funcReqTemperatures_t)(ESSA_EPS1_ResponseTemperatures_t *res);
typedef void (*pfESSA_EPS1funcReqConfiguration_t)(ESSA_EPS1_ResponseConfiguration_t *res);
typedef void (*pfESSA_EPS1funcReqControl_t)(ESSA_EPS1_RequestControl_t *args, ESSA_EPS1_ResponseControl_t *res);
typedef void (*pfESSA_EPS1funcReqRBattRaw_t)(ESSA_EPS1_RequestRBattRaw_t *args, ESSA_EPS1_ResponseRBattRaw_t *res);

typedef struct
{
    pfESSA_EPS1funcReqSoftwareVersion_t pHandler_SoftwareVersion;
    pfESSA_EPS1funcReqBatteryInfo_t     pHandler_BatteryInfo;
    pfESSA_EPS1funcReqSolarPanelsInfo_t pHandler_SolarPanelsInfo;
    pfESSA_EPS1funcReqStatistics_t      pHandler_Statistics;
    pfESSA_EPS1funcReqTemperatures_t    pHandler_Temperatures;
    pfESSA_EPS1funcReqConfiguration_t   pHandler_Configuration;
    pfESSA_EPS1funcReqControl_t         pHandler_Control;
    pfESSA_EPS1funcReqRBattRaw_t        pHandler_RBattRaw;
} EPS1_Api_t;

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
/* No External routines declarations */

#endif // __ES_SAT_API_EPS1_MAC_HEADER_INCLUDED_H_
/* ******************************************************************************************* */
