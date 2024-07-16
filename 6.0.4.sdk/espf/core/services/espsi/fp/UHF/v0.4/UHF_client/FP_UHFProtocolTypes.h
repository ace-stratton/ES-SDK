/*!
********************************************************************************************
* @file FP_UHFProtocolTypes.h
* @brief Protocol public type declarations
********************************************************************************************
* @version           interface UHF v0.4
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

#ifndef __FP_UHFPROTOCOLTYPES_H__
#define __FP_UHFPROTOCOLTYPES_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Shared defines
 *
 **********************************************************************/
#define ES_SAT_FUNC_PROTOCOL_ID_UHF ((uint16_t) (0x00000005))

#define UHF_WRITESCW_FUNC_ID ((funcIdType_t) 0x00000001)
#define UHF_READSCW_FUNC_ID ((funcIdType_t) 0x00000002)
#define UHF_WRITERFCONFIG_FUNC_ID ((funcIdType_t) 0x00000003)
#define UHF_READRFCONFIG_FUNC_ID ((funcIdType_t) 0x00000004)
#define UHF_READUPTIME_FUNC_ID ((funcIdType_t) 0x00000005)
#define UHF_READNUMBEROFTXPACKETS_FUNC_ID ((funcIdType_t) 0x00000006)
#define UHF_READNUMBEROFRXPACKETS_FUNC_ID ((funcIdType_t) 0x00000007)
#define UHF_READNUMBEROFRXPACKETSCRCERR_FUNC_ID ((funcIdType_t) 0x00000008)
#define UHF_WRITEBEACONMESSAGETXPERIODCFG_FUNC_ID ((funcIdType_t) 0x00000009)
#define UHF_READBEACONMESSAGETXPERIODCFG_FUNC_ID ((funcIdType_t) 0x0000000A)
#define UHF_WRITEBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNC_ID ((funcIdType_t) 0x0000000B)
#define UHF_READBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNC_ID ((funcIdType_t) 0x0000000C)
#define UHF_RESTOREDEFAULTCONFIG_FUNC_ID ((funcIdType_t) 0x0000000D)
#define UHF_WRITEANTENNARELEASECONFIG_FUNC_ID ((funcIdType_t) 0x0000000E)
#define UHF_READANTENNARELEASECONFIG_FUNC_ID ((funcIdType_t) 0x0000000F)
#define UHF_WRITEANTENNA_FUNC_ID ((funcIdType_t) 0x00000010)
#define UHF_READANTENNA_FUNC_ID ((funcIdType_t) 0x00000011)
#define UHF_ENTERLPM_FUNC_ID ((funcIdType_t) 0x00000012)
#define UHF_READLPM_FUNC_ID ((funcIdType_t) 0x00000013)
#define UHF_WRITEDESTCALLSIGN_FUNC_ID ((funcIdType_t) 0x00000014)
#define UHF_READDESTCALLSIGN_FUNC_ID ((funcIdType_t) 0x00000015)
#define UHF_WRITESRCCALLSIGN_FUNC_ID ((funcIdType_t) 0x00000016)
#define UHF_READSRCCALLSIGN_FUNC_ID ((funcIdType_t) 0x00000017)
#define UHF_WRITEMORSECALLSIGN_FUNC_ID ((funcIdType_t) 0x00000018)
#define UHF_READMORSECALLSIGN_FUNC_ID ((funcIdType_t) 0x00000019)
#define UHF_WRITEMIDIAUDIOBEACON_FUNC_ID ((funcIdType_t) 0x0000001A)
#define UHF_READMIDIAUDIOBEACON_FUNC_ID ((funcIdType_t) 0x0000001B)
#define UHF_READSWVERSION_FUNC_ID ((funcIdType_t) 0x0000001C)
#define UHF_READPAYLOADSIZE_FUNC_ID ((funcIdType_t) 0x0000001D)
#define UHF_WRITEBEACONMESSAGECONTENTCFG_FUNC_ID ((funcIdType_t) 0x0000001E)
#define UHF_READBEACONMESSAGECONTENTCFG_FUNC_ID ((funcIdType_t) 0x0000001F)
#define UHF_WRITEDEVICEADDRCONFIG_FUNC_ID ((funcIdType_t) 0x00000020)
#define UHF_WRITEFRAM_FUNC_ID ((funcIdType_t) 0x00000021)
#define UHF_READFRAM_FUNC_ID ((funcIdType_t) 0x00000022)
#define UHF_WRITETRANSPROPERTY_FUNC_ID ((funcIdType_t) 0x00000023)
#define UHF_READTRANSPROPERTY_FUNC_ID ((funcIdType_t) 0x00000024)
#define UHF_READTEMP_FUNC_ID ((funcIdType_t) 0x00000025)
#define UHF_READRSSI_FUNC_ID ((funcIdType_t) 0x00000026)
#define UHF_WRITERADIORAWDATA_FUNC_ID ((funcIdType_t) 0x00000027)
#define UHF_PING_FUNC_ID ((funcIdType_t) 0x00000028)
#define UHF_EXBEACONSETSEND_FUNC_ID ((funcIdType_t) 0x00000029)
#define UHF_WRITEI2CCONFIG_FUNC_ID ((funcIdType_t) 0x0000002A)
#define UHF_READI2CCONFIG_FUNC_ID ((funcIdType_t) 0x0000002B)
#define UHF_WRITEANTENNACFG_FUNC_ID ((funcIdType_t) 0x0000002C)
#define UHF_READANTENNACFG_FUNC_ID ((funcIdType_t) 0x0000002D)
#define UHF_WRITEEPSCFG_FUNC_ID ((funcIdType_t) 0x0000002E)
#define UHF_READEPSCFG_FUNC_ID ((funcIdType_t) 0x0000002F)
#define UHF_WRITEEPSCONOPSCFG_FUNC_ID ((funcIdType_t) 0x00000030)
#define UHF_READEPSCONOPSCFG_FUNC_ID ((funcIdType_t) 0x00000031)
#define UHF_WRITERS485CONFIG_FUNC_ID ((funcIdType_t) 0x00000032)
#define UHF_READRS485CONFIG_FUNC_ID ((funcIdType_t) 0x00000033)
#define UHF_WRITEOBCCONFIG_FUNC_ID ((funcIdType_t) 0x00000034)
#define UHF_READOBCCONFIG_FUNC_ID ((funcIdType_t) 0x00000035)
#define UHF_WRITESATCONFIG_FUNC_ID ((funcIdType_t) 0x00000036)
#define UHF_READSATCONFIG_FUNC_ID ((funcIdType_t) 0x00000037)
#define UHF_READEPSCFGOUT_FUNC_ID ((funcIdType_t) 0x00000038)
#define UHF_WRITEEPSCFGOUT_FUNC_ID ((funcIdType_t) 0x00000039)
#define UHF_WRITE2UANTENNACFG_FUNC_ID ((funcIdType_t) 0x0000003A)
#define UHF_READ2UANTENNACFG_FUNC_ID ((funcIdType_t) 0x0000003B)
#define UHF_WRITEAUTOMATEDBEACONCFG_FUNC_ID ((funcIdType_t) 0x0000003C)
#define UHF_READAUTOMATEDBEACONCFG_FUNC_ID ((funcIdType_t) 0x0000003D)
#define UHF_WRITEOUTPUTPOWERCFG_FUNC_ID ((funcIdType_t) 0x0000003E)
#define UHF_READOUTPUTPOWERCFG_FUNC_ID ((funcIdType_t) 0x0000003F)
#define UHF_READCOUNTERS_FUNC_ID ((funcIdType_t) 0x00000040)
#define UHF_WRITECIPHERKEYSLOT_FUNC_ID ((funcIdType_t) 0x00000041)
#define UHF_READCIPHERKEYSLOTSTATUS_FUNC_ID ((funcIdType_t) 0x00000042)
#define UHF_ERASECIPHERKEYSLOT_FUNC_ID ((funcIdType_t) 0x00000043)
#define UHF_WRITESCW_FUNCRESP_ID ((funcIdType_t) 0x00000001)
#define UHF_READSCW_FUNCRESP_ID ((funcIdType_t) 0x00000002)
#define UHF_WRITERFCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000003)
#define UHF_READRFCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000004)
#define UHF_READUPTIME_FUNCRESP_ID ((funcIdType_t) 0x00000005)
#define UHF_READNUMBEROFTXPACKETS_FUNCRESP_ID ((funcIdType_t) 0x00000006)
#define UHF_READNUMBEROFRXPACKETS_FUNCRESP_ID ((funcIdType_t) 0x00000007)
#define UHF_READNUMBEROFRXPACKETSCRCERR_FUNCRESP_ID ((funcIdType_t) 0x00000008)
#define UHF_WRITEBEACONMESSAGETXPERIODCFG_FUNCRESP_ID ((funcIdType_t) 0x00000009)
#define UHF_READBEACONMESSAGETXPERIODCFG_FUNCRESP_ID ((funcIdType_t) 0x0000000A)
#define UHF_WRITEBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000B)
#define UHF_READBEACONMESSAGEBETWEEENTXPERIODCONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000C)
#define UHF_RESTOREDEFAULTCONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000D)
#define UHF_WRITEANTENNARELEASECONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000E)
#define UHF_READANTENNARELEASECONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000000F)
#define UHF_WRITEANTENNA_FUNCRESP_ID ((funcIdType_t) 0x00000010)
#define UHF_READANTENNA_FUNCRESP_ID ((funcIdType_t) 0x00000011)
#define UHF_ENTERLPM_FUNCRESP_ID ((funcIdType_t) 0x00000012)
#define UHF_READLPM_FUNCRESP_ID ((funcIdType_t) 0x00000013)
#define UHF_WRITEDESTCALLSIGN_FUNCRESP_ID ((funcIdType_t) 0x00000014)
#define UHF_READDESTCALLSIGN_FUNCRESP_ID ((funcIdType_t) 0x00000015)
#define UHF_WRITESRCCALLSIGN_FUNCRESP_ID ((funcIdType_t) 0x00000016)
#define UHF_READSRCCALLSIGN_FUNCRESP_ID ((funcIdType_t) 0x00000017)
#define UHF_WRITEMORSECALLSIGN_FUNCRESP_ID ((funcIdType_t) 0x00000018)
#define UHF_READMORSECALLSIGN_FUNCRESP_ID ((funcIdType_t) 0x00000019)
#define UHF_WRITEMIDIAUDIOBEACON_FUNCRESP_ID ((funcIdType_t) 0x0000001A)
#define UHF_READMIDIAUDIOBEACON_FUNCRESP_ID ((funcIdType_t) 0x0000001B)
#define UHF_READSWVERSION_FUNCRESP_ID ((funcIdType_t) 0x0000001C)
#define UHF_READPAYLOADSIZE_FUNCRESP_ID ((funcIdType_t) 0x0000001D)
#define UHF_WRITEBEACONMESSAGECONTENTCFG_FUNCRESP_ID ((funcIdType_t) 0x0000001E)
#define UHF_READBEACONMESSAGECONTENTCFG_FUNCRESP_ID ((funcIdType_t) 0x0000001F)
#define UHF_WRITEDEVICEADDRCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000020)
#define UHF_WRITEFRAM_FUNCRESP_ID ((funcIdType_t) 0x00000021)
#define UHF_READFRAM_FUNCRESP_ID ((funcIdType_t) 0x00000022)
#define UHF_WRITETRANSPROPERTY_FUNCRESP_ID ((funcIdType_t) 0x00000023)
#define UHF_READTRANSPROPERTY_FUNCRESP_ID ((funcIdType_t) 0x00000024)
#define UHF_READTEMP_FUNCRESP_ID ((funcIdType_t) 0x00000025)
#define UHF_READRSSI_FUNCRESP_ID ((funcIdType_t) 0x00000026)
#define UHF_WRITERADIORAWDATA_FUNCRESP_ID ((funcIdType_t) 0x00000027)
#define UHF_PING_FUNCRESP_ID ((funcIdType_t) 0x00000028)
#define UHF_EXBEACONSETSEND_FUNCRESP_ID ((funcIdType_t) 0x00000029)
#define UHF_WRITEI2CCONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000002A)
#define UHF_READI2CCONFIG_FUNCRESP_ID ((funcIdType_t) 0x0000002B)
#define UHF_WRITEANTENNACFG_FUNCRESP_ID ((funcIdType_t) 0x0000002C)
#define UHF_READANTENNACFG_FUNCRESP_ID ((funcIdType_t) 0x0000002D)
#define UHF_WRITEEPSCFG_FUNCRESP_ID ((funcIdType_t) 0x0000002E)
#define UHF_READEPSCFG_FUNCRESP_ID ((funcIdType_t) 0x0000002F)
#define UHF_WRITEEPSCONOPSCFG_FUNCRESP_ID ((funcIdType_t) 0x00000030)
#define UHF_READEPSCONOPSCFG_FUNCRESP_ID ((funcIdType_t) 0x00000031)
#define UHF_WRITERS485CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000032)
#define UHF_READRS485CONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000033)
#define UHF_WRITEOBCCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000034)
#define UHF_READOBCCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000035)
#define UHF_WRITESATCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000036)
#define UHF_READSATCONFIG_FUNCRESP_ID ((funcIdType_t) 0x00000037)
#define UHF_READEPSCFGOUT_FUNCRESP_ID ((funcIdType_t) 0x00000038)
#define UHF_WRITEEPSCFGOUT_FUNCRESP_ID ((funcIdType_t) 0x00000039)
#define UHF_WRITE2UANTENNACFG_FUNCRESP_ID ((funcIdType_t) 0x0000003A)
#define UHF_READ2UANTENNACFG_FUNCRESP_ID ((funcIdType_t) 0x0000003B)
#define UHF_WRITEAUTOMATEDBEACONCFG_FUNCRESP_ID ((funcIdType_t) 0x0000003C)
#define UHF_READAUTOMATEDBEACONCFG_FUNCRESP_ID ((funcIdType_t) 0x0000003D)
#define UHF_WRITEOUTPUTPOWERCFG_FUNCRESP_ID ((funcIdType_t) 0x0000003E)
#define UHF_READOUTPUTPOWERCFG_FUNCRESP_ID ((funcIdType_t) 0x0000003F)
#define UHF_READCOUNTERS_FUNCRESP_ID ((funcIdType_t) 0x00000040)
#define UHF_WRITECIPHERKEYSLOT_FUNCRESP_ID ((funcIdType_t) 0x00000041)
#define UHF_READCIPHERKEYSLOTSTATUS_FUNCRESP_ID ((funcIdType_t) 0x00000042)
#define UHF_ERASECIPHERKEYSLOT_FUNCRESP_ID ((funcIdType_t) 0x00000043)

/**********************************************************************
 *
 *  Type definitions
 *
 **********************************************************************/
/*
    General status returned for HW-related communication and/or settings
*/
#define UHF_HWRESULT_SUCCESS ((uint8_t) 0)
#define UHF_HWRESULT_ERROR ((uint8_t) 1)
#define UHF_HWRESULT_DISABLED ((uint8_t) 2)
#define UHF_HWRESULT_MAX_CNT  ((uint8_t) 3)
typedef uint8_t UHF_HwResult_t;

/*
    General status returned for FP commands
*/
#define UHF_EESSA_UHFSTATUS_OK ((uint8_t) 0)
#define UHF_EESSA_UHFSTATUS_ERROR ((uint8_t) 1)
#define UHF_EESSA_UHFSTATUS_ERROR_BAD_DATA ((uint8_t) 2)
#define UHF_EESSA_UHFSTATUS_ERROR_NOT_IMPLEMENTED ((uint8_t) 3)
#define UHF_EESSA_UHFSTATUS_ERROR_I2C_NACK ((uint8_t) 4)
#define UHF_EESSA_UHFSTATUS_UHF_ERR_BUSY ((uint8_t) 5)
#define UHF_EESSA_UHFSTATUS_MAX_CNT  ((uint8_t) 6)
typedef uint8_t UHF_eESSA_UhfStatus_t;

#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_SUCCESS ((uint8_t) 0)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_EMPTY ((uint8_t) 1)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_OCCUPIED ((uint8_t) 2)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR_OUT_OF_RANGE ((uint8_t) 3)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR_IO ((uint8_t) 4)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR_OCCUPIED ((uint8_t) 5)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR_EMPTY ((uint8_t) 6)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR_KEYSIZE ((uint8_t) 7)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR_NOMASTER ((uint8_t) 8)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR_KEYNOTMATCH ((uint8_t) 9)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_ERR ((uint8_t) 10)
#define UHF_EESSA_UHFSCIPHERKEYSLOTSTATUS_MAX_CNT  ((uint8_t) 11)
typedef uint8_t UHF_eESSA_UhfSCipherKeySlotStatus_t;

/*
    Structure for read/write Status Control Word
*/
typedef struct {
    uint16_t u16SCWBitField;
} PACKED_STRUCT UHF_StatusControlWord_t;

/*
    Structure for read/write UpTime
*/
typedef struct {
    uint32_t u32U32UpTime;
} PACKED_STRUCT UHF_sUpTime_t;

/*
    Structure for read/write RF configuration
*/
typedef struct {
    uint8_t u8RxIntPar;
    uint8_t au8RxFractional[3];
    uint8_t u8TxIntPar;
    uint8_t au8TxFractional[3];
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sRFConfig_t;

/*
    Structure for text beacon period configuration
*/
typedef struct {
    uint16_t u16Period;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sBeaconMessageTxPeriodCfg_t;

/*
    Structure for audio beacon period configuration
*/
typedef struct {
    uint16_t u16Period;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sBeaconMessageBetweenTxPeriodCfg_t;

/*
    Structure for 1U antenna release configuration
*/
typedef struct {
    uint8_t u8Enable;
    uint8_t u8Time;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sAntennaReleaseCfg_t;

/*
    Structure for response of 1U antenna i2c read operation
*/
typedef struct {
    uint32_t u32Data;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sAntennaData_t;

/*
    Structure for AX25 Source Call signature configuration
*/
typedef struct {
    uint8_t au8Signature[6];
    uint8_t u8U8Validity;
} PACKED_STRUCT UHF_sCallSign_t;

/*
    Structure for Morse code content configuration
*/
typedef struct {
    uint8_t u8Size;
    uint8_t au8Signature[37];
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sMorseCallSign_t;

/*
    Structure for Audio beacon contnet configuration
*/
typedef struct {
    uint8_t u8Size;
    uint16_t au16Midi[37];
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sMidiAudioBeacon_t;

/*
    Structure for Firmware version
*/
typedef struct {
    uint8_t u8Version;
    uint8_t u8Increment;
    uint8_t au8DateTimeAsciiZ[25];
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sSwVersionBuild_t;

/*
    Structure for text beacon content configuration
*/
typedef struct {
    uint8_t u8Size;
    uint8_t au8Message[98];
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sBeaconMessageContentCfg_t;

/*
    Structure for module address configuration
*/
typedef struct {
    uint8_t u8Addr;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sAddrCfg_t;

/*
    Structure for external NvM read/write operations
*/
typedef struct {
    uint32_t u32Addr;
    uint8_t au8Data[16];
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sFramData_t;

/*
    Structure for SI4463 property read request according to SI4463 specification
*/
typedef struct {
    uint8_t u8Group;
    uint8_t u8Offset;
    uint8_t u8Size;
} PACKED_STRUCT UHF_sReadTransceiverProperty_t;

/*
    Structure for SI4463 property read request response and write request, according to SI4463 specification
*/
typedef struct {
    uint8_t u8Group;
    uint8_t u8Offset;
    uint8_t u8Size;
    uint8_t au8Data[16];
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sTransceiverProperty_t;

/*
    Structure for SI4463 status according specification
*/
typedef struct {
    uint8_t u8MODEM_PEND;
    uint8_t u8MODEM_STATUS;
    uint8_t u8CURR_RSSI;
    uint8_t u8LATCH_RSSI;
    uint8_t u8ANT1_RSSI;
    uint8_t u8ANT2_RSSI;
    uint16_t u16AFC_FREQ_OFFSET;
} PACKED_STRUCT UHF_sSi4463ModemStatus_t;

/*
    Structure for Radio Raw data write request operation
*/
typedef struct {
    uint8_t u8Size;
    uint8_t au8Data[128];
} PACKED_STRUCT UHF_sRadioRawData_t;

/*
    Structure for module Ping-Pong functionality
*/
typedef struct {
    uint8_t u8Size;
    uint8_t au8Data[16];
} PACKED_STRUCT UHF_sPing_t;

/*
    Structure for Beacon transmission request operation
*/
typedef struct {
    uint8_t u8Size;
    uint8_t au8Data[98];
} PACKED_STRUCT UHF_sExBeacon_t;

/*
    Structure for I2C confiration
*/
typedef struct {
    uint8_t u8Addr;
    uint8_t u8PullUp4_7K;
    uint8_t u8PullUp10K;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sI2cCfg_t;

/*
    Structure for antenna configuration
*/
typedef struct {
    uint8_t u8I2cAddr;
    uint8_t u8AntennaReleaseCheckEnable;
    uint8_t u8AntennaReleaseCheckTime;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sAntennaCfg_t;

/*
    Structure for EPS configuration
*/
typedef struct {
    uint8_t u8Addr;
    uint8_t u8U8Variant;
    uint32_t u32U32RequestTimeMs;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sEpsCfg_t;

/*
    ConOps voltage hysteresis configuration, values from EPS specification
*/
typedef struct {
    uint16_t u16V_low;
    uint16_t u16I_low;
    uint16_t u16V_high;
    uint16_t u16I_high;
    uint16_t u16V_ideal_low;
    uint16_t u16V_ideal_high;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sEpsConOpsCfg_t;

/*
    RS485 line configuration
*/
typedef struct {
    uint8_t u8Termination;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sRS485Cfg_t;

/*
    OBC configuration
*/
typedef struct {
    uint8_t u8Addr1;
    uint8_t u8Variant1;
    uint8_t u8EPSOut1;
    uint8_t u8Addr2;
    uint8_t u8Variant2;
    uint8_t u8EPSOut2;
    uint16_t u16PingTimeoutS;
    uint8_t u8RstRetry;
    uint8_t u8PingPeriod;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sObcCfg_t;

/*
    SatID configuration
*/
typedef struct {
    uint64_t u64SatID;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sSatCfg_t;

/*
    EPS output configartion for Phoenix and Normal ConOps modes
*/
typedef struct {
    uint8_t u8Output_normal;
    uint8_t u8Mask_normal;
    uint8_t u8Output_phoenix;
    uint8_t u8Mask_phoenix;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sEpsOutCfg_t;

/*
    2U Antenna release algorithm states
*/
#define UHF_ANT2U_ALG_STATE_IDLE ((uint8_t) 0)
#define UHF_ANT2U_ALG_STATE_GPO_REQ ((uint8_t) 1)
#define UHF_ANT2U_ALG_STATE_GPO1 ((uint8_t) 2)
#define UHF_ANT2U_ALG_STATE_GPO2 ((uint8_t) 3)
#define UHF_ANT2U_ALG_STATE_GPO3 ((uint8_t) 4)
#define UHF_ANT2U_ALG_STATE_MCU_REQ ((uint8_t) 5)
#define UHF_ANT2U_ALG_STATE_MCU1 ((uint8_t) 6)
#define UHF_ANT2U_ALG_STATE_MCU2 ((uint8_t) 7)
#define UHF_ANT2U_ALG_STATE_GET_STAT ((uint8_t) 8)
#define UHF_ANT2U_ALG_STATE_WAIT_RESP ((uint8_t) 9)
#define UHF_ANT2U_ALG_STATE_TIMEOUT ((uint8_t) 10)
#define UHF_ANT2U_ALG_STATE_END ((uint8_t) 11)
#define UHF_ANT2U_ALG_STATE_MAX_CNT  ((uint8_t) 12)
typedef uint8_t UHF_Ant2U_Alg_State_t;

/*
    Antenna 2U Deployment state
*/
#define UHF_ANT2U_DEPLOYMENT_Enabled ((uint8_t) 90)
#define UHF_ANT2U_DEPLOYMENT_Disabled ((uint8_t) 0)
#define UHF_ANT2U_DEPLOYMENT_MAX_CNT  ((uint8_t) 91)
typedef uint8_t UHF_Ant2U_deployment_t;

/*
    Antenna 2U configuration
*/
typedef struct {
    UHF_Ant2U_deployment_t eEnable;
    uint8_t u8MACAddr;
    uint8_t u8Robust;
    uint8_t u8AlgCheckDelay;
    uint16_t u16AlgTimeout;
    uint16_t u16RemainingBootCount;
    UHF_Ant2U_Alg_State_t eState;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_s2UAntennaCfg_t;

/*
    Atomated beacon configuraton
*/
typedef struct {
    uint64_t u64EnPhoenix;
    uint64_t u64EnNormal;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sAutomatedBeaconCfg_t;

/*
    Structure for transceiver output power configuraton
*/
typedef struct {
    uint8_t u8Value;
    uint32_t u32Reserved;
    uint8_t u8Validity;
} PACKED_STRUCT UHF_sOutputPowerCfg_t;

/*
    Structure for statistical counters
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
} PACKED_STRUCT UHF_sCounters_t;

/*
    Structure for cipher key slot
*/
typedef struct {
    uint8_t u8ServiceID;
    uint8_t u8SlotID;
    uint8_t au8Data[32];
    uint8_t u8Size;
} PACKED_STRUCT UHF_sCipherKeySlot_t;


typedef struct {
    UHF_StatusControlWord_t sScw;
} PACKED_STRUCT UHFWriteSCWRequestData_t;

typedef struct {
    UHF_sRFConfig_t sRfConfig;
} PACKED_STRUCT UHFWriteRfConfigRequestData_t;

typedef struct {
    UHF_sBeaconMessageTxPeriodCfg_t sCfg;
} PACKED_STRUCT UHFWriteBeaconMessageTxPeriodCfgRequestData_t;

typedef struct {
    UHF_sBeaconMessageBetweenTxPeriodCfg_t sCfg;
} PACKED_STRUCT UHFWriteBeaconMessageBetweeenTxPeriodConfigRequestData_t;

typedef struct {
    UHF_sAntennaReleaseCfg_t sCfg;
} PACKED_STRUCT UHFWriteAntennaReleaseConfigRequestData_t;

typedef struct {
    uint8_t u8Algorithm;
} PACKED_STRUCT UHFWriteAntennaRequestData_t;

typedef struct {
    UHF_sCallSign_t sCallSign;
} PACKED_STRUCT UHFWriteDestCallSignRequestData_t;

typedef struct {
    UHF_sCallSign_t sCallSign;
} PACKED_STRUCT UHFWriteSrcCallSignRequestData_t;

typedef struct {
    UHF_sMorseCallSign_t sMorseCallSign;
} PACKED_STRUCT UHFWriteMorseCallSignRequestData_t;

typedef struct {
    UHF_sMidiAudioBeacon_t sMidi;
} PACKED_STRUCT UHFWriteMIDIAudioBeaconRequestData_t;

typedef struct {
    UHF_sBeaconMessageContentCfg_t sCfg;
} PACKED_STRUCT UHFWriteBeaconMessageContentCfgRequestData_t;

typedef struct {
    UHF_sAddrCfg_t sCfg;
} PACKED_STRUCT UHFWriteDeviceAddrConfigRequestData_t;

typedef struct {
    UHF_sFramData_t sFramWriteReq;
} PACKED_STRUCT UHFWriteFRAMRequestData_t;

typedef struct {
    uint32_t u32Addr;
} PACKED_STRUCT UHFReadFRAMRequestData_t;

typedef struct {
    UHF_sTransceiverProperty_t sProperty;
} PACKED_STRUCT UHFWriteTransPropertyRequestData_t;

typedef struct {
    UHF_sReadTransceiverProperty_t sProperty;
} PACKED_STRUCT UHFReadTransPropertyRequestData_t;

typedef struct {
    UHF_sRadioRawData_t sData;
} PACKED_STRUCT UHFWriteRadioRawDataRequestData_t;

typedef struct {
    UHF_sPing_t sData;
} PACKED_STRUCT UHFPingRequestData_t;

typedef struct {
    UHF_sExBeacon_t sData;
} PACKED_STRUCT UHFExBeaconSetSendRequestData_t;

typedef struct {
    UHF_sI2cCfg_t sData;
} PACKED_STRUCT UHFWriteI2cConfigRequestData_t;

typedef struct {
    UHF_sAntennaCfg_t sCfg;
} PACKED_STRUCT UHFWriteAntennaCfgRequestData_t;

typedef struct {
    UHF_sEpsCfg_t sCfg;
} PACKED_STRUCT UHFWriteEpsCfgRequestData_t;

typedef struct {
    UHF_sEpsConOpsCfg_t sCfg;
} PACKED_STRUCT UHFWriteEpsConOpsCfgRequestData_t;

typedef struct {
    UHF_sRS485Cfg_t sCfg;
} PACKED_STRUCT UHFWriteRs485ConfigRequestData_t;

typedef struct {
    UHF_sObcCfg_t sCfg;
} PACKED_STRUCT UHFWriteOBCConfigRequestData_t;

typedef struct {
    UHF_sSatCfg_t sCfg;
} PACKED_STRUCT UHFWriteSatConfigRequestData_t;

typedef struct {
    UHF_sEpsOutCfg_t sCfg;
} PACKED_STRUCT UHFWriteEpsCfgOutRequestData_t;

typedef struct {
    UHF_s2UAntennaCfg_t sCfg;
} PACKED_STRUCT UHFWrite2UAntennaCfgRequestData_t;

typedef struct {
    UHF_sAutomatedBeaconCfg_t sCfg;
} PACKED_STRUCT UHFWriteAutomatedBeaconCfgRequestData_t;

typedef struct {
    UHF_sOutputPowerCfg_t sCfg;
} PACKED_STRUCT UHFWriteOutputPowerCfgRequestData_t;

typedef struct {
    UHF_sCipherKeySlot_t sSKeySlot;
} PACKED_STRUCT UHFWriteCipherKeySlotRequestData_t;

typedef struct {
    uint8_t u8SlotId;
} PACKED_STRUCT UHFReadCipherKeySlotStatusRequestData_t;

typedef struct {
    UHF_sCipherKeySlot_t sSKeySlot;
} PACKED_STRUCT UHFEraseCipherKeySlotRequestData_t;


typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteSCWResponseData_t;

typedef struct {
    UHF_StatusControlWord_t sOpResult;
} PACKED_STRUCT UHFReadSCWResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteRfConfigResponseData_t;

typedef struct {
    UHF_sRFConfig_t sOpResult;
} PACKED_STRUCT UHFReadRfConfigResponseData_t;

typedef struct {
    UHF_sUpTime_t sUpTime;
} PACKED_STRUCT UHFReadUpTimeResponseData_t;

typedef struct {
    uint32_t u32Packets;
} PACKED_STRUCT UHFReadNumberOfTxPacketsResponseData_t;

typedef struct {
    uint32_t u32Packets;
} PACKED_STRUCT UHFReadNumberOfRxPacketsResponseData_t;

typedef struct {
    uint32_t u32Packets;
} PACKED_STRUCT UHFReadNumberOfRxPacketsCRCErrResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteBeaconMessageTxPeriodCfgResponseData_t;

typedef struct {
    UHF_sBeaconMessageTxPeriodCfg_t sOpResult;
} PACKED_STRUCT UHFReadBeaconMessageTxPeriodCfgResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteBeaconMessageBetweeenTxPeriodConfigResponseData_t;

typedef struct {
    UHF_sBeaconMessageBetweenTxPeriodCfg_t sOpResult;
} PACKED_STRUCT UHFReadBeaconMessageBetweeenTxPeriodConfigResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFRestoreDefaultConfigResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteAntennaReleaseConfigResponseData_t;

typedef struct {
    UHF_sAntennaReleaseCfg_t sOpResult;
} PACKED_STRUCT UHFReadAntennaReleaseConfigResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteAntennaResponseData_t;

typedef struct {
    UHF_sAntennaData_t sOpResult;
} PACKED_STRUCT UHFReadAntennaResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFEnterLPMResponseData_t;

typedef struct {
    uint8_t u8Mode;
} PACKED_STRUCT UHFReadLPMResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteDestCallSignResponseData_t;

typedef struct {
    UHF_sCallSign_t sOpResult;
} PACKED_STRUCT UHFReadDestCallSignResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteSrcCallSignResponseData_t;

typedef struct {
    UHF_sCallSign_t sOpResult;
} PACKED_STRUCT UHFReadSRCCallSignResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteMorseCallSignResponseData_t;

typedef struct {
    UHF_sMorseCallSign_t sOpResult;
} PACKED_STRUCT UHFReadMorseCallSignResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteMIDIAudioBeaconResponseData_t;

typedef struct {
    UHF_sMidiAudioBeacon_t sOpResult;
} PACKED_STRUCT UHFReadMIDIAudioBeaconResponseData_t;

typedef struct {
    UHF_sSwVersionBuild_t sOpResult;
} PACKED_STRUCT UHFReadSWVersionResponseData_t;

typedef struct {
    uint16_t u16PayloadSize;
} PACKED_STRUCT UHFReadPayloadSizeResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteBeaconMessageContentCfgResponseData_t;

typedef struct {
    UHF_sBeaconMessageContentCfg_t sOpResult;
} PACKED_STRUCT UHFReadBeaconMessageContentCfgResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteDeviceAddrConfigResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteFRAMResponseData_t;

typedef struct {
    UHF_sFramData_t sOpResult;
} PACKED_STRUCT UHFReadFRAMResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteTransPropertyResponseData_t;

typedef struct {
    UHF_sTransceiverProperty_t sOpResult;
} PACKED_STRUCT UHFReadTransPropertyResponseData_t;

typedef struct {
    int16_t i16OpResult;
} PACKED_STRUCT UHFReadTempResponseData_t;

typedef struct {
    UHF_sSi4463ModemStatus_t sOpResult;
} PACKED_STRUCT UHFReadRSSIResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteRadioRawDataResponseData_t;

typedef struct {
    UHF_sPing_t sOpResult;
} PACKED_STRUCT UHFPingResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFExBeaconSetSendResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteI2cConfigResponseData_t;

typedef struct {
    UHF_sI2cCfg_t sData;
} PACKED_STRUCT UHFReadI2cConfigResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteAntennaCfgResponseData_t;

typedef struct {
    UHF_sAntennaCfg_t sCfg;
} PACKED_STRUCT UHFReadAntennaCfgResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteEpsCfgResponseData_t;

typedef struct {
    UHF_sEpsCfg_t sCfg;
} PACKED_STRUCT UHFReadEpsCfgResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteEpsConOpsCfgResponseData_t;

typedef struct {
    UHF_sEpsConOpsCfg_t sCfg;
} PACKED_STRUCT UHFReadEpsConOpsCfgResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteRs485ConfigResponseData_t;

typedef struct {
    UHF_sRS485Cfg_t sCfg;
} PACKED_STRUCT UHFReadRs485ConfigResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteOBCConfigResponseData_t;

typedef struct {
    UHF_sObcCfg_t sCfg;
} PACKED_STRUCT UHFReadOBCConfigResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteSatConfigResponseData_t;

typedef struct {
    UHF_sSatCfg_t sCfg;
} PACKED_STRUCT UHFReadSatConfigResponseData_t;

typedef struct {
    UHF_sEpsOutCfg_t sCfg;
} PACKED_STRUCT UHFReadEpsCfgOutResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteEpsCfgOutResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWrite2UAntennaCfgResponseData_t;

typedef struct {
    UHF_s2UAntennaCfg_t sCfg;
} PACKED_STRUCT UHFRead2UAntennaCfgResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteAutomatedBeaconCfgResponseData_t;

typedef struct {
    UHF_sAutomatedBeaconCfg_t sCfg;
} PACKED_STRUCT UHFReadAutomatedBeaconCfgResponseData_t;

typedef struct {
    UHF_eESSA_UhfStatus_t eOpResult;
} PACKED_STRUCT UHFWriteOutputPowerCfgResponseData_t;

typedef struct {
    UHF_sOutputPowerCfg_t sCfg;
} PACKED_STRUCT UHFReadOutputPowerCfgResponseData_t;

typedef struct {
    UHF_sCounters_t sCfg;
} PACKED_STRUCT UHFReadCountersResponseData_t;

typedef struct {
    UHF_eESSA_UhfSCipherKeySlotStatus_t eOpResult;
} PACKED_STRUCT UHFWriteCipherKeySlotResponseData_t;

typedef struct {
    UHF_eESSA_UhfSCipherKeySlotStatus_t eESlotStatus;
} PACKED_STRUCT UHFReadCipherKeySlotStatusResponseData_t;

typedef struct {
    UHF_eESSA_UhfSCipherKeySlotStatus_t eOpResult;
} PACKED_STRUCT UHFEraseCipherKeySlotResponseData_t;


#endif  // #ifndef __FP_UHFPROTOCOLTYPES_H__

