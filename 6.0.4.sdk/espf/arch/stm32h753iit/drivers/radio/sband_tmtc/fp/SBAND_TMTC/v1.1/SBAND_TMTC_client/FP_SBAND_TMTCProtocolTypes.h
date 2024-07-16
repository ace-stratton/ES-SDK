/*!
********************************************************************************************
* @file FP_SBAND_TMTCProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface SBAND_TMTC v1.1
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

#ifndef __FP_SBAND_TMTCPROTOCOLTYPES_H__
#define __FP_SBAND_TMTCPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_SBAND_TMTC ((uint16_t) (0x00000020))

#define SBAND_TMTC_GETCAPABILITIES_FUNC_ID ((funcIdType_t) 0x00000001)
#define SBAND_TMTC_READUPTIME_FUNC_ID ((funcIdType_t) 0x00000002)
#define SBAND_TMTC_READHWHEALTH_FUNC_ID ((funcIdType_t) 0x00000003)
#define SBAND_TMTC_READEPSCFG_FUNC_ID ((funcIdType_t) 0x00000004)
#define SBAND_TMTC_WRITEEPSCFG_FUNC_ID ((funcIdType_t) 0x00000005)
#define SBAND_TMTC_READAUTOMATEDBEACONSCFG_FUNC_ID ((funcIdType_t) 0x00000006)
#define SBAND_TMTC_WRITEAUTOMATEDBEACONSCFG_FUNC_ID ((funcIdType_t) 0x00000007)
#define SBAND_TMTC_READERRORCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000008)
#define SBAND_TMTC_READPIPEMODECFG_FUNC_ID ((funcIdType_t) 0x00000009)
#define SBAND_TMTC_WRITEPIPEMODECFG_FUNC_ID ((funcIdType_t) 0x0000000A)
#define SBAND_TMTC_READTXTBEACONCONTENTCFG_FUNC_ID ((funcIdType_t) 0x0000000B)
#define SBAND_TMTC_WRITETXTBEACONCONTENTCFG_FUNC_ID ((funcIdType_t) 0x0000000C)
#define SBAND_TMTC_READAX25CFG_FUNC_ID ((funcIdType_t) 0x0000000D)
#define SBAND_TMTC_WRITEAX25CFG_FUNC_ID ((funcIdType_t) 0x0000000E)
#define SBAND_TMTC_WRITECIPHERKEYSLOT_FUNC_ID ((funcIdType_t) 0x0000000F)
#define SBAND_TMTC_READCIPHERKEYSLOTSTATUS_FUNC_ID ((funcIdType_t) 0x00000010)
#define SBAND_TMTC_ERASECIPHERKEYSLOT_FUNC_ID ((funcIdType_t) 0x00000011)
#define SBAND_TMTC_READCONOPS_HYSTCFG_FUNC_ID ((funcIdType_t) 0x00000012)
#define SBAND_TMTC_WRITECONOPS_HYSTCFG_FUNC_ID ((funcIdType_t) 0x00000013)
#define SBAND_TMTC_READPORTCFG_FUNC_ID ((funcIdType_t) 0x00000014)
#define SBAND_TMTC_WRITEPORTCFG_FUNC_ID ((funcIdType_t) 0x00000015)
#define SBAND_TMTC_READLOGGERCFG_FUNC_ID ((funcIdType_t) 0x00000016)
#define SBAND_TMTC_WRITELOGGERCFG_FUNC_ID ((funcIdType_t) 0x00000017)
#define SBAND_TMTC_TRANSMITDATA_FUNC_ID ((funcIdType_t) 0x00000018)
#define SBAND_TMTC_LOADPRESETCFG_FUNC_ID ((funcIdType_t) 0x00000019)
#define SBAND_TMTC_PING_FUNC_ID ((funcIdType_t) 0x0000001A)
#define SBAND_TMTC_SETDUALPAMODE_FUNC_ID ((funcIdType_t) 0x0000001B)
#define SBAND_TMTC_GETDUALPAMODE_FUNC_ID ((funcIdType_t) 0x0000001C)
#define SBAND_TMTC_SETTESTPACKETSTATE_FUNC_ID ((funcIdType_t) 0x0000001D)
#define SBAND_TMTC_READRFFREQCFG_FUNC_ID ((funcIdType_t) 0x0000001E)
#define SBAND_TMTC_WRITERFFREQCFG_FUNC_ID ((funcIdType_t) 0x0000001F)
#define SBAND_TMTC_RESET_FUNC_ID ((funcIdType_t) 0x00000020)
#define SBAND_TMTC_RESETERRORCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000021)
#define SBAND_TMTC_READSATCFG_FUNC_ID ((funcIdType_t) 0x00000022)
#define SBAND_TMTC_WRITESATCFG_FUNC_ID ((funcIdType_t) 0x00000023)
#define SBAND_TMTC_READTC_FUNC_ID ((funcIdType_t) 0x00000024)
#define SBAND_TMTC_CLEARTC_FUNC_ID ((funcIdType_t) 0x00000025)
#define SBAND_TMTC_READTEMPSENSORS_FUNC_ID ((funcIdType_t) 0x00000026)
#define SBAND_TMTC_IGNORE_PA_TS_FUNC_ID ((funcIdType_t) 0x00000027)
#define SBAND_TMTC_READRADIOCRCCFG_FUNC_ID ((funcIdType_t) 0x00000028)
#define SBAND_TMTC_WRITERADIOCRCCFG_FUNC_ID ((funcIdType_t) 0x00000029)
#define SBAND_TMTC_WRITERADIOPACKETFECHDLC_FUNC_ID ((funcIdType_t) 0x0000002A)
#define SBAND_TMTC_READRADIOPACKETFECHDLC_FUNC_ID ((funcIdType_t) 0x0000002B)
#define SBAND_TMTC_GETPACKETCOUNTERS_FUNC_ID ((funcIdType_t) 0x0000002C)
#define SBAND_TMTC_READRADIOERRORS_FUNC_ID ((funcIdType_t) 0x0000002D)
#define SBAND_TMTC_GETMODULATION_FUNC_ID ((funcIdType_t) 0x0000002E)
#define SBAND_TMTC_SETMODULATION_FUNC_ID ((funcIdType_t) 0x0000002F)
#define SBAND_TMTC_GETBAUDRATE_FUNC_ID ((funcIdType_t) 0x00000030)
#define SBAND_TMTC_SETBAUDRATE_FUNC_ID ((funcIdType_t) 0x00000031)
#define SBAND_TMTC_GETFREQSHAPING_FUNC_ID ((funcIdType_t) 0x00000032)
#define SBAND_TMTC_SETFREQSHAPING_FUNC_ID ((funcIdType_t) 0x00000033)
#define SBAND_TMTC_GETSTREAMMODE_FUNC_ID ((funcIdType_t) 0x00000034)
#define SBAND_TMTC_SETSTREAMMODE_FUNC_ID ((funcIdType_t) 0x00000035)
#define SBAND_TMTC_GETTARGETPOWER_FUNC_ID ((funcIdType_t) 0x00000036)
#define SBAND_TMTC_SETTARGETPOWER_FUNC_ID ((funcIdType_t) 0x00000037)
#define SBAND_TMTC_GETPACKETSCRAMBLER_FUNC_ID ((funcIdType_t) 0x00000038)
#define SBAND_TMTC_SETPACKETSCRAMBLER_FUNC_ID ((funcIdType_t) 0x00000039)
#define SBAND_TMTC_GETCAPABILITIES_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define SBAND_TMTC_READUPTIME_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define SBAND_TMTC_READHWHEALTH_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define SBAND_TMTC_READEPSCFG_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define SBAND_TMTC_WRITEEPSCFG_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define SBAND_TMTC_READAUTOMATEDBEACONSCFG_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define SBAND_TMTC_WRITEAUTOMATEDBEACONSCFG_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define SBAND_TMTC_READERRORCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define SBAND_TMTC_READPIPEMODECFG_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define SBAND_TMTC_WRITEPIPEMODECFG_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define SBAND_TMTC_READTXTBEACONCONTENTCFG_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define SBAND_TMTC_WRITETXTBEACONCONTENTCFG_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define SBAND_TMTC_READAX25CFG_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define SBAND_TMTC_WRITEAX25CFG_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define SBAND_TMTC_WRITECIPHERKEYSLOT_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define SBAND_TMTC_READCIPHERKEYSLOTSTATUS_FUNCRESP_ID ((funcIdType_t) 0x00000010)
#define SBAND_TMTC_ERASECIPHERKEYSLOT_FUNCRESP_ID ((funcIdType_t) 0x00000011)
#define SBAND_TMTC_READCONOPS_HYSTCFG_FUNCRESP_ID ((funcIdType_t) 0x00000012)
#define SBAND_TMTC_WRITECONOPS_HYSTCFG_FUNCRESP_ID ((funcIdType_t) 0x00000013)
#define SBAND_TMTC_READPORTCFG_FUNCRESP_ID ((funcIdType_t) 0x00000014)
#define SBAND_TMTC_WRITEPORTCFG_FUNCRESP_ID ((funcIdType_t) 0x00000015)
#define SBAND_TMTC_READLOGGERCFG_FUNCRESP_ID ((funcIdType_t) 0x00000016)
#define SBAND_TMTC_WRITELOGGERCFG_FUNCRESP_ID ((funcIdType_t) 0x00000017)
#define SBAND_TMTC_TRANSMITDATA_FUNCRESP_ID ((funcIdType_t) 0x00000018)
#define SBAND_TMTC_LOADPRESETCFG_FUNCRESP_ID ((funcIdType_t) 0x00000019)
#define SBAND_TMTC_PING_FUNCRESP_ID ((funcIdType_t) 0x0000001A)
#define SBAND_TMTC_SETDUALPAMODE_FUNCRESP_ID ((funcIdType_t) 0x0000001B)
#define SBAND_TMTC_GETDUALPAMODE_FUNCRESP_ID ((funcIdType_t) 0x0000001C)
#define SBAND_TMTC_SETTESTPACKETSTATE_FUNCRESP_ID ((funcIdType_t) 0x0000001D)
#define SBAND_TMTC_READRFFREQCFG_FUNCRESP_ID ((funcIdType_t) 0x0000001E)
#define SBAND_TMTC_WRITERFFREQCFG_FUNCRESP_ID ((funcIdType_t) 0x0000001F)
#define SBAND_TMTC_RESET_FUNCRESP_ID ((funcIdType_t) 0x00000020)
#define SBAND_TMTC_RESETERRORCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000021)
#define SBAND_TMTC_READSATCFG_FUNCRESP_ID ((funcIdType_t) 0x00000022)
#define SBAND_TMTC_WRITESATCFG_FUNCRESP_ID ((funcIdType_t) 0x00000023)
#define SBAND_TMTC_READTC_FUNCRESP_ID ((funcIdType_t) 0x00000024)
#define SBAND_TMTC_CLEARTC_FUNCRESP_ID ((funcIdType_t) 0x00000025)
#define SBAND_TMTC_READTEMPSENSORS_FUNCRESP_ID ((funcIdType_t) 0x00000026)
#define SBAND_TMTC_IGNORE_PA_TS_FUNCRESP_ID ((funcIdType_t) 0x00000027)
#define SBAND_TMTC_READRADIOCRCCFG_FUNCRESP_ID ((funcIdType_t) 0x00000028)
#define SBAND_TMTC_WRITERADIOCRCCFG_FUNCRESP_ID ((funcIdType_t) 0x00000029)
#define SBAND_TMTC_WRITERADIOPACKETFECHDLC_FUNCRESP_ID ((funcIdType_t) 0x0000002A)
#define SBAND_TMTC_READRADIOPACKETFECHDLC_FUNCRESP_ID ((funcIdType_t) 0x0000002B)
#define SBAND_TMTC_GETPACKETCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x0000002C)
#define SBAND_TMTC_READRADIOERRORS_FUNCRESP_ID ((funcIdType_t) 0x0000002D)
#define SBAND_TMTC_GETMODULATION_FUNCRESP_ID ((funcIdType_t) 0x0000002E)
#define SBAND_TMTC_SETMODULATION_FUNCRESP_ID ((funcIdType_t) 0x0000002F)
#define SBAND_TMTC_GETBAUDRATE_FUNCRESP_ID ((funcIdType_t) 0x00000030)
#define SBAND_TMTC_SETBAUDRATE_FUNCRESP_ID ((funcIdType_t) 0x00000031)
#define SBAND_TMTC_GETFREQSHAPING_FUNCRESP_ID ((funcIdType_t) 0x00000032)
#define SBAND_TMTC_SETFREQSHAPING_FUNCRESP_ID ((funcIdType_t) 0x00000033)
#define SBAND_TMTC_GETSTREAMMODE_FUNCRESP_ID ((funcIdType_t) 0x00000034)
#define SBAND_TMTC_SETSTREAMMODE_FUNCRESP_ID ((funcIdType_t) 0x00000035)
#define SBAND_TMTC_GETTARGETPOWER_FUNCRESP_ID ((funcIdType_t) 0x00000036)
#define SBAND_TMTC_SETTARGETPOWER_FUNCRESP_ID ((funcIdType_t) 0x00000037)
#define SBAND_TMTC_GETPACKETSCRAMBLER_FUNCRESP_ID ((funcIdType_t) 0x00000038)
#define SBAND_TMTC_SETPACKETSCRAMBLER_FUNCRESP_ID ((funcIdType_t) 0x00000039)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    Result of an operation performed by the radio
*/
#define SBAND_TMTC_EESSA_TMTCSTATUS_OK ((uint8_t) 0)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR ((uint8_t) 1)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR_NOMEM ((uint8_t) 2)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR_BAD_PARAM ((uint8_t) 3)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR_BAD_DATA ((uint8_t) 4)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR_BUSY ((uint8_t) 5)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR_AUTHENTICATION ((uint8_t) 6)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR_NOT_SUPPORTED ((uint8_t) 7)
#define SBAND_TMTC_EESSA_TMTCSTATUS_ERROR_NOT_IN_CORRECT_STATE ((uint8_t) 8)
#define SBAND_TMTC_EESSA_TMTCSTATUS_MAX_CNT  ((uint8_t) 9)
typedef uint8_t SBAND_TMTC_eESSA_TMTCStatus_t;

#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_SUCCESS ((uint8_t) 0)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_EMPTY ((uint8_t) 1)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_OCCUPIED ((uint8_t) 2)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR_OUT_OF_RANGE ((uint8_t) 3)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR_IO ((uint8_t) 4)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR_OCCUPIED ((uint8_t) 5)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR_EMPTY ((uint8_t) 6)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR_KEYSIZE ((uint8_t) 7)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR_NOMASTER ((uint8_t) 8)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR_KEYNOTMATCH ((uint8_t) 9)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_ERR ((uint8_t) 10)
#define SBAND_TMTC_ECIPHERKEYSLOTSTATUS_MAX_CNT  ((uint8_t) 11)
typedef uint8_t SBAND_TMTC_eCipherKeySlotStatus_t;

/*
    Physical interfaces
*/
#define SBAND_TMTC_EPORTID_PORT_SERIAL_USB_C ((uint8_t) 0)
#define SBAND_TMTC_EPORTID_PORT_SERIAL_PRIMARY ((uint8_t) 1)
#define SBAND_TMTC_EPORTID_PORT_SERIAL_SECONDARY ((uint8_t) 2)
#define SBAND_TMTC_EPORTID_PORT_CAN ((uint8_t) 3)
#define SBAND_TMTC_EPORTID_MAX_CNT  ((uint8_t) 4)
typedef uint8_t SBAND_TMTC_ePortID_t;

/*
    Protocol type assigned to an interface
*/
#define SBAND_TMTC_EPORTPROTOCOLID_DISABLED ((uint8_t) 0)
#define SBAND_TMTC_EPORTPROTOCOLID_DEBUG ((uint8_t) 1)
#define SBAND_TMTC_EPORTPROTOCOLID_LOG ((uint8_t) 2)
#define SBAND_TMTC_EPORTPROTOCOLID_TRANSPARENT ((uint8_t) 3)
#define SBAND_TMTC_EPORTPROTOCOLID_MAC_GW ((uint8_t) 4)
#define SBAND_TMTC_EPORTPROTOCOLID_RS485_ESMAC_MM ((uint8_t) 5)
#define SBAND_TMTC_EPORTPROTOCOLID_RS485_ESMAC_PP ((uint8_t) 6)
#define SBAND_TMTC_EPORTPROTOCOLID_CCSDS ((uint8_t) 7)
#define SBAND_TMTC_EPORTPROTOCOLID_MAX_CNT  ((uint8_t) 8)
typedef uint8_t SBAND_TMTC_ePortProtocolID_t;

/*
    Physical interface secondary function configuration, see manual
*/
#define SBAND_TMTC_EPORTCFGID_AUTO ((uint8_t) 0)
#define SBAND_TMTC_EPORTCFGID_CONFIG_1 ((uint8_t) 1)
#define SBAND_TMTC_EPORTCFGID_CONFIG_2 ((uint8_t) 2)
#define SBAND_TMTC_EPORTCFGID_CONFIG_3 ((uint8_t) 3)
#define SBAND_TMTC_EPORTCFGID_CONFIG_4 ((uint8_t) 4)
#define SBAND_TMTC_EPORTCFGID_MAX_CNT  ((uint8_t) 5)
typedef uint8_t SBAND_TMTC_ePortCfgID_t;

#define SBAND_TMTC_EPORTCONNTYPECFG_UNDEFINED ((uint8_t) 0)
#define SBAND_TMTC_EPORTCONNTYPECFG_USER_PRI ((uint8_t) 1)
#define SBAND_TMTC_EPORTCONNTYPECFG_USER_SEC ((uint8_t) 2)
#define SBAND_TMTC_EPORTCONNTYPECFG_SYSTEM_PRI ((uint8_t) 3)
#define SBAND_TMTC_EPORTCONNTYPECFG_SYSTEM_SEC ((uint8_t) 4)
#define SBAND_TMTC_EPORTCONNTYPECFG_MAX_CNT  ((uint8_t) 5)
typedef uint8_t SBAND_TMTC_ePortConnTypeCfg_t;

/*
    Digital filter for ConOps hysteresis
*/
#define SBAND_TMTC_ECONOPSHYSTFILTERID_NONE ((uint8_t) 0)
#define SBAND_TMTC_ECONOPSHYSTFILTERID_MAX_CNT  ((uint8_t) 1)
typedef uint8_t SBAND_TMTC_eConOpsHystFilterID_t;

/*
    Slot ID for SBAND TMTC security keys
*/
#define SBAND_TMTC_EKEYSLOTID_MASTER ((uint8_t) 0)
#define SBAND_TMTC_EKEYSLOTID_GP00 ((uint8_t) 1)
#define SBAND_TMTC_EKEYSLOTID_GP01 ((uint8_t) 2)
#define SBAND_TMTC_EKEYSLOTID_GP02 ((uint8_t) 3)
#define SBAND_TMTC_EKEYSLOTID_GP03 ((uint8_t) 4)
#define SBAND_TMTC_EKEYSLOTID_GP04 ((uint8_t) 5)
#define SBAND_TMTC_EKEYSLOTID_GP05 ((uint8_t) 6)
#define SBAND_TMTC_EKEYSLOTID_GP06 ((uint8_t) 7)
#define SBAND_TMTC_EKEYSLOTID_GP07 ((uint8_t) 8)
#define SBAND_TMTC_EKEYSLOTID_GP08 ((uint8_t) 9)
#define SBAND_TMTC_EKEYSLOTID_MAX_CNT  ((uint8_t) 10)
typedef uint8_t SBAND_TMTC_eKeySlotID_t;

/*
    Types of Services assigned to security key
*/
#define SBAND_TMTC_EKEYSERVICEID_NONE ((uint8_t) 0)
#define SBAND_TMTC_EKEYSERVICEID_DYNAMYC_ENCRYPTION ((uint8_t) 1)
#define SBAND_TMTC_EKEYSERVICEID_STATIC_ENCRYPTION ((uint8_t) 2)
#define SBAND_TMTC_EKEYSERVICEID_MAX_CNT  ((uint8_t) 3)
typedef uint8_t SBAND_TMTC_eKeyServiceID_t;

/*
    Types of transmitting data packets
*/
#define SBAND_TMTC_ETXMESSAGETYPE_AUTO ((uint8_t) 0)
#define SBAND_TMTC_ETXMESSAGETYPE_RAW ((uint8_t) 1)
#define SBAND_TMTC_ETXMESSAGETYPE_AX25 ((uint8_t) 2)
#define SBAND_TMTC_ETXMESSAGETYPE_ES_TELEMETRY ((uint8_t) 3)
#define SBAND_TMTC_ETXMESSAGETYPE_MAX_CNT  ((uint8_t) 4)
typedef uint8_t SBAND_TMTC_eTxMessageType_t;

#define SBAND_TMTC_EPRESETCFGTYPE_NONE ((uint8_t) 0)
#define SBAND_TMTC_EPRESETCFGTYPE_DEFAULT ((uint8_t) 1)
#define SBAND_TMTC_EPRESETCFGTYPE_STANDALONE ((uint8_t) 2)
#define SBAND_TMTC_EPRESETCFGTYPE_PLATFORM ((uint8_t) 3)
#define SBAND_TMTC_EPRESETCFGTYPE_MAX_CNT  ((uint8_t) 4)
typedef uint8_t SBAND_TMTC_ePresetCfgType_t;

/*
    Validity flag for a configuration
*/
#define SBAND_TMTC_EVALIDITY_INVALID_CONFIG ((uint8_t) 0)
#define SBAND_TMTC_EVALIDITY_VALID_CONFIG ((uint8_t) 1)
#define SBAND_TMTC_EVALIDITY_MAX_CNT  ((uint8_t) 2)
typedef uint8_t SBAND_TMTC_eValidity_t;

/*
    Dual power amplifier control
*/
#define SBAND_TMTC_EPOWERAMPCONTROL_AUTO ((uint8_t) 0)
#define SBAND_TMTC_EPOWERAMPCONTROL_FORCE_ON ((uint8_t) 1)
#define SBAND_TMTC_EPOWERAMPCONTROL_FORCE_OFF ((uint8_t) 2)
#define SBAND_TMTC_EPOWERAMPCONTROL_AUTO_1_OFF_2 ((uint8_t) 3)
#define SBAND_TMTC_EPOWERAMPCONTROL_OFF_1_AUTO_2 ((uint8_t) 4)
#define SBAND_TMTC_EPOWERAMPCONTROL_MAX_CNT  ((uint8_t) 5)
typedef uint8_t SBAND_TMTC_ePowerAmpControl_t;

/*
    Provided for ledgability
*/
#define SBAND_TMTC_EONOFF_OFF ((uint8_t) 0)
#define SBAND_TMTC_EONOFF_ON ((uint8_t) 1)
#define SBAND_TMTC_EONOFF_MAX_CNT  ((uint8_t) 2)
typedef uint8_t SBAND_TMTC_eOnOff_t;

typedef struct {
    uint32_t u32HSBitField;
} PACKED_STRUCT SBAND_TMTC_sHealthStatus_t;

/*
    Available modulations. Gaussian filter selected separately. Default is FSK. Deviation is treated as the distance of the carrier frequency to the closest symbol frequency.
*/
#define SBAND_TMTC_MODULATION_FSK ((uint8_t) 0)
#define SBAND_TMTC_MODULATION_FSK4 ((uint8_t) 1)
#define SBAND_TMTC_MODULATION_MSK ((uint8_t) 2)
#define SBAND_TMTC_MODULATION_PSK ((uint8_t) 3)
#define SBAND_TMTC_MODULATION_MAX_CNT  ((uint8_t) 4)
typedef uint8_t SBAND_TMTC_Modulation_t;

/*
    Available baudrates, default is 50k. Effective transmission baudrate when using FEC/HDLC is half of the shown.
*/
#define SBAND_TMTC_BAUDRATE_b100 ((uint8_t) 0)
#define SBAND_TMTC_BAUDRATE_b1k ((uint8_t) 1)
#define SBAND_TMTC_BAUDRATE_b10k ((uint8_t) 2)
#define SBAND_TMTC_BAUDRATE_b25k ((uint8_t) 3)
#define SBAND_TMTC_BAUDRATE_b50k ((uint8_t) 4)
#define SBAND_TMTC_BAUDRATE_b75k ((uint8_t) 5)
#define SBAND_TMTC_BAUDRATE_b100k ((uint8_t) 6)
#define SBAND_TMTC_BAUDRATE_b125k ((uint8_t) 7)
#define SBAND_TMTC_BAUDRATE_MAX_CNT  ((uint8_t) 8)
typedef uint8_t SBAND_TMTC_Baudrate_t;

/*
    None or Gaussian filter with BT = 0.3 or 0.5
*/
#define SBAND_TMTC_FILTERING_None ((uint8_t) 0)
#define SBAND_TMTC_FILTERING_BT03 ((uint8_t) 1)
#define SBAND_TMTC_FILTERING_BT05 ((uint8_t) 2)
#define SBAND_TMTC_FILTERING_MAX_CNT  ((uint8_t) 3)
typedef uint8_t SBAND_TMTC_Filtering_t;

/*
    Up-time in seconds
*/
typedef struct {
    uint32_t u32U32UpTime;
} PACKED_STRUCT SBAND_TMTC_sUpTime_t;

/*
    Sattelite configuration
*/
typedef struct {
    uint64_t u64SatID;
} PACKED_STRUCT SBAND_TMTC_sSatCfg_t;

/*
    EPS configuration
*/
typedef struct {
    uint8_t u8U8Type;
    uint8_t u8Addr;
    uint32_t u32PhoenixMask;
    uint32_t u32NormalMask;
    uint16_t u16PhoenixTime;
    uint16_t u16NormalTime;
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sEpsCfg_t;

/*
    Configuration for automatic data beacons
*/
typedef struct {
    uint32_t u32PhoenixPeriod;
    uint32_t u32NormalPeriod;
    uint64_t u64PhoenixMask;
    uint64_t u64NormalMask;
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sAutoBeaconsCfg_t;

/*
    Statistical Counters
*/
typedef struct {
    uint32_t u32POR;
    uint32_t u32MAC_Collisions;
    uint32_t u32MAC_fails;
    uint32_t u32GS_Handshakes;
    uint32_t u32NvMWriteFails;
    uint32_t u32NvMReadFails;
    uint32_t u32NvMDefaultEntry;
    uint32_t u32IntFRAM_corruptions;
    uint32_t u32ExtFRAM_corruptions;
    uint32_t u32ExtFRAM_gone;
} PACKED_STRUCT SBAND_TMTC_sErrCounters_t;

/*
    Radio-ESPS Pipe mode configuration
*/
typedef struct {
    uint16_t u16Duration;
    uint8_t u8PeerAddr;
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sPipeModeCfg_t;

/*
    Text beacon configuration
*/
typedef struct {
    uint8_t u8Size;
    uint8_t au8Message[98];
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sTxtBeaconContentCfg_t;

/*
    Size of the message in bytes before encoding
*/
typedef struct {
    uint8_t u8PeerAddr;
    uint8_t au8Src[6];
    uint8_t au8Dst[6];
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sAx25Cfg_t;

/*
    Input Slot structure for erasing or writing security keys
*/
typedef struct {
    SBAND_TMTC_eKeyServiceID_t eServiceID;
    SBAND_TMTC_eKeySlotID_t eSlotID;
    uint8_t au8Data[32];
    uint8_t u8Size;
} PACKED_STRUCT SBAND_TMTC_sCipherKeySlot_t;

/*
    Hysteresis of ConOps
*/
typedef struct {
    uint16_t u16EnterNormalVoltage;
    uint16_t u16EnterPhoenixVoltage;
    SBAND_TMTC_eConOpsHystFilterID_t eFilterID;
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sConOps_Hysteresis_t;

/*
    Input structure for writing interface configurations
*/
typedef struct {
    SBAND_TMTC_ePortID_t ePortID;
    SBAND_TMTC_ePortProtocolID_t eProtoID;
    SBAND_TMTC_ePortCfgID_t eCfgID;
} PACKED_STRUCT SBAND_TMTC_sCommPortCfgIn_t;

/*
    Output structure for reading interface configurations
*/
typedef struct {
    uint8_t u8PortID;
    SBAND_TMTC_ePortProtocolID_t eProtoID;
    SBAND_TMTC_ePortCfgID_t eCfgID;
    uint32_t u32Capabilities;
    SBAND_TMTC_ePortConnTypeCfg_t eConnectionType;
    uint8_t u8PortMaxCount;
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sCommPortCfgOut_t;

/*
    Logging verbose configuration
    					Bit-masks
    					Bit 0 -> Event data loging enable
    					Bit 1 -> System events loging enable
    					Bit 2 -> App events loging enable
    					Bit 3 -> ESPS loging enable
*/
typedef struct {
    uint32_t u32NvMLogMaskCfg;
    uint32_t u32DebugLogMaskCfg;
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sLogger_Cfg_t;

/*
    Module capabilities
*/
typedef struct {
    uint32_t u32RadioHWCapabilities;
    uint32_t u32Reserved1;
    uint32_t u32RadioProtoCapabilities;
    uint32_t u32Reserved2;
    uint32_t u32TxMessageCapabilities;
    uint32_t u32Reserved3;
    uint32_t u32IFPhyCapabilities;
    uint32_t u32IFProtoCapabilities;
    uint32_t u32Reserved4;
    uint32_t u32Reserved5;
    uint32_t u32Reserved6;
    uint32_t u32Reserved7;
    uint32_t u32Reserved8;
    uint32_t u32Reserved9;
    uint32_t u32Reserved10;
    uint32_t u32Reserved11;
    uint32_t u32Reserved12;
    uint32_t u32Reserved13;
} PACKED_STRUCT SBAND_TMTC_sCapabilities_t;

/*
    Input structure for transmitting data
*/
typedef struct {
    SBAND_TMTC_eTxMessageType_t eType;
    uint8_t u8Size;
    uint8_t au8Data[128];
} PACKED_STRUCT SBAND_TMTC_sTxRadioMsg_t;

/*
    Structure for module Ping-Pong functionality
*/
typedef struct {
    uint8_t u8Size;
    uint8_t au8Data[16];
} PACKED_STRUCT SBAND_TMTC_sPing_t;

/*
    Test packet configuration
*/
typedef struct {
    SBAND_TMTC_eOnOff_t eRun;
    uint8_t u8Pattern;
} PACKED_STRUCT SBAND_TMTC_sTestPacket_t;

/*
    Radio frequency configuration
*/
typedef struct {
    uint32_t u32Rx;
    uint32_t u32Tx;
    SBAND_TMTC_eValidity_t eValidity;
} PACKED_STRUCT SBAND_TMTC_sRfFreqCfg_t;

/*
    Trouble codes structure
*/
typedef struct {
    uint32_t u32MCU;
    uint32_t u32Memory;
    uint32_t u32Interface;
    uint32_t u32Sensor;
    uint32_t u32Radio;
    uint32_t u32Mixer;
} PACKED_STRUCT SBAND_TMTC_sTC_t;

/*
    Data structure for temperature sensors on board. New data is provided at 5s intervals.
*/
typedef struct {
    float fMCUtemp;
    float fPAtemp;
} PACKED_STRUCT SBAND_TMTC_sTempSensors_t;

/*
    default on, CRC-32, seed is 0xFFFFFFFF
*/
typedef struct {
    SBAND_TMTC_eOnOff_t eEnable;
    uint32_t u32Seed;
} PACKED_STRUCT SBAND_TMTC_sRadioCRC_t;

/*
    Counters for the transmitted packets, received packets and crc errors
*/
typedef struct {
    uint32_t u32TransmittedPackets;
    uint32_t u32ReceivedPackets;
    uint32_t u32CRCError;
} PACKED_STRUCT SBAND_TMTC_sRFPacketCounters_t;


typedef struct {
    SBAND_TMTC_sEpsCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteEpsCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sAutoBeaconsCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteAutomatedBeaconsCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sPipeModeCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWritePipeModeCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sTxtBeaconContentCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteTxtBeaconContentCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sAx25Cfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteAx25CfgRequestData_t;

typedef struct {
    SBAND_TMTC_sCipherKeySlot_t sSKeySlot;
} PACKED_STRUCT SBAND_TMTCWriteCipherKeySlotRequestData_t;

typedef struct {
    SBAND_TMTC_eKeySlotID_t eSlotId;
} PACKED_STRUCT SBAND_TMTCReadCipherKeySlotStatusRequestData_t;

typedef struct {
    SBAND_TMTC_sCipherKeySlot_t sSKeySlot;
} PACKED_STRUCT SBAND_TMTCEraseCipherKeySlotRequestData_t;

typedef struct {
    SBAND_TMTC_sConOps_Hysteresis_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteConOps_HystCfgRequestData_t;

typedef struct {
    SBAND_TMTC_ePortID_t ePortID;
} PACKED_STRUCT SBAND_TMTCReadPortCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sCommPortCfgIn_t sCfg;
} PACKED_STRUCT SBAND_TMTCWritePortCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sLogger_Cfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteLoggerCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sTxRadioMsg_t sMsg;
} PACKED_STRUCT SBAND_TMTCTransmitDataRequestData_t;

typedef struct {
    SBAND_TMTC_ePresetCfgType_t eCfg;
} PACKED_STRUCT SBAND_TMTCLoadPresetCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sPing_t sData;
} PACKED_STRUCT SBAND_TMTCPingRequestData_t;

typedef struct {
    SBAND_TMTC_ePowerAmpControl_t eCtl;
} PACKED_STRUCT SBAND_TMTCSetDualPAModeRequestData_t;

typedef struct {
    SBAND_TMTC_sTestPacket_t sTp;
} PACKED_STRUCT SBAND_TMTCSetTestPacketStateRequestData_t;

typedef struct {
    SBAND_TMTC_sRfFreqCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteRfFreqCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sSatCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteSatCfgRequestData_t;

typedef struct {
    SBAND_TMTC_sRadioCRC_t sCfg;
} PACKED_STRUCT SBAND_TMTCWriteRadioCRCCfgRequestData_t;

typedef struct {
    SBAND_TMTC_eOnOff_t eOnoff;
} PACKED_STRUCT SBAND_TMTCWriteRadioPacketFecHdlcRequestData_t;

typedef struct {
    SBAND_TMTC_Modulation_t eM;
} PACKED_STRUCT SBAND_TMTCSetModulationRequestData_t;

typedef struct {
    SBAND_TMTC_Baudrate_t eB;
} PACKED_STRUCT SBAND_TMTCSetBaudrateRequestData_t;

typedef struct {
    SBAND_TMTC_Filtering_t eF;
} PACKED_STRUCT SBAND_TMTCSetFreqShapingRequestData_t;

typedef struct {
    SBAND_TMTC_eOnOff_t eS;
} PACKED_STRUCT SBAND_TMTCSetStreamModeRequestData_t;

typedef struct {
    uint16_t u16Power;
} PACKED_STRUCT SBAND_TMTCSetTargetPowerRequestData_t;

typedef struct {
    SBAND_TMTC_eOnOff_t eS;
} PACKED_STRUCT SBAND_TMTCSetPacketScramblerRequestData_t;


typedef struct {
    SBAND_TMTC_sCapabilities_t sCapabilities;
} PACKED_STRUCT SBAND_TMTCGetCapabilitiesResponseData_t;

typedef struct {
    SBAND_TMTC_sUpTime_t sUpTime;
} PACKED_STRUCT SBAND_TMTCReadUpTimeResponseData_t;

typedef struct {
    SBAND_TMTC_sHealthStatus_t sStatus;
} PACKED_STRUCT SBAND_TMTCReadHWHealthResponseData_t;

typedef struct {
    SBAND_TMTC_sEpsCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadEpsCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteEpsCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sAutoBeaconsCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadAutomatedBeaconsCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteAutomatedBeaconsCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sErrCounters_t sErrCounters;
} PACKED_STRUCT SBAND_TMTCReadErrorCountersResponseData_t;

typedef struct {
    SBAND_TMTC_sPipeModeCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadPipeModeCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWritePipeModeCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sTxtBeaconContentCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadTxtBeaconContentCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteTxtBeaconContentCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sAx25Cfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadAx25CfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteAx25CfgResponseData_t;

typedef struct {
    SBAND_TMTC_eCipherKeySlotStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteCipherKeySlotResponseData_t;

typedef struct {
    SBAND_TMTC_eCipherKeySlotStatus_t eESlotStatus;
} PACKED_STRUCT SBAND_TMTCReadCipherKeySlotStatusResponseData_t;

typedef struct {
    SBAND_TMTC_eCipherKeySlotStatus_t eOpResult;
} PACKED_STRUCT SBAND_TMTCEraseCipherKeySlotResponseData_t;

typedef struct {
    SBAND_TMTC_sConOps_Hysteresis_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadConOps_HystCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteConOps_HystCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sCommPortCfgOut_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadPortCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWritePortCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sLogger_Cfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadLoggerCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteLoggerCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCTransmitDataResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCLoadPresetCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sPing_t sOpResult;
} PACKED_STRUCT SBAND_TMTCPingResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCSetDualPAModeResponseData_t;

typedef struct {
    SBAND_TMTC_ePowerAmpControl_t eCtl;
} PACKED_STRUCT SBAND_TMTCGetDualPAModeResponseData_t;

typedef struct {
    SBAND_TMTC_sRfFreqCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadRfFreqCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteRfFreqCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCResetResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCResetErrorCountersResponseData_t;

typedef struct {
    SBAND_TMTC_sSatCfg_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadSatCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteSatCfgResponseData_t;

typedef struct {
    SBAND_TMTC_sTC_t sTC;
} PACKED_STRUCT SBAND_TMTCReadTCResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCClearTCResponseData_t;

typedef struct {
    SBAND_TMTC_sTempSensors_t sTemp;
} PACKED_STRUCT SBAND_TMTCReadTempSensorsResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCIgnore_PA_TSResponseData_t;

typedef struct {
    SBAND_TMTC_sRadioCRC_t sCfg;
} PACKED_STRUCT SBAND_TMTCReadRadioCRCCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteRadioCRCCfgResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCWriteRadioPacketFecHdlcResponseData_t;

typedef struct {
    SBAND_TMTC_eOnOff_t eOnoff;
} PACKED_STRUCT SBAND_TMTCReadRadioPacketFecHdlcResponseData_t;

typedef struct {
    SBAND_TMTC_sRFPacketCounters_t sCounters;
} PACKED_STRUCT SBAND_TMTCGetPacketCountersResponseData_t;

typedef struct {
    uint32_t u32Errors;
} PACKED_STRUCT SBAND_TMTCReadRadioErrorsResponseData_t;

typedef struct {
    SBAND_TMTC_Modulation_t eM;
} PACKED_STRUCT SBAND_TMTCGetModulationResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCSetModulationResponseData_t;

typedef struct {
    SBAND_TMTC_Baudrate_t eB;
} PACKED_STRUCT SBAND_TMTCGetBaudrateResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCSetBaudrateResponseData_t;

typedef struct {
    SBAND_TMTC_Filtering_t eF;
} PACKED_STRUCT SBAND_TMTCGetFreqShapingResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCSetFreqShapingResponseData_t;

typedef struct {
    SBAND_TMTC_eOnOff_t eS;
} PACKED_STRUCT SBAND_TMTCGetStreamModeResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCSetStreamModeResponseData_t;

typedef struct {
    uint16_t u16Power;
} PACKED_STRUCT SBAND_TMTCGetTargetPowerResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCSetTargetPowerResponseData_t;

typedef struct {
    SBAND_TMTC_eOnOff_t eS;
} PACKED_STRUCT SBAND_TMTCGetPacketScramblerResponseData_t;

typedef struct {
    SBAND_TMTC_eESSA_TMTCStatus_t eStatus;
} PACKED_STRUCT SBAND_TMTCSetPacketScramblerResponseData_t;


#endif  // #ifndef __FP_SBAND_TMTCPROTOCOLTYPES_H__

