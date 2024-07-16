/*
 *  Created on: May 15, 2020
 *      Author: Georgi-EnduroSat
 */

#ifndef __ESSA_UHF_H__
#define __ESSA_UHF_H__

#include <stdint.h>
#include "ESSA_Stack.h"

#define ESSA_UHF_MORSE_CALL_SIGN_MAX_SIZE                ((uint8_t) 37)
#define ESSA_UHF_MIDI_AUDIO_BEACON_MAX_SIZE              ((uint8_t) 37)
#define ESSA_UHF_SW_BUILD_DATETIME_STRING_MAX_SIZE       ((uint8_t) 25)
#define ESSA_UHF_BEACON_MESSAGE_CONTENT_CONFIG_MAX_SIZE  ((uint8_t) 0x62)
#define ESSA_UHF_FRAM_RW_DATA_SIZE                       ((uint8_t) 16)
#define ESSA_UHF_TRANSCEIVER_PROPERTY_RW_DATA_MAX_SIZE   ((uint8_t) 16)

typedef enum
{
    ESSA_UHF_OK,
    ESSA_UHF_ERROR,
    ESSA_UHF_ERROR_BAD_DATA,
    ESSA_UHF_ERROR_NOT_IMPLEMENTED,
    ESSA_UHF_ERROR_I2C_NACK,
    ESSA_UHF_ERR_BUSY,
} eESSA_UhfStatus_t;

typedef struct {
    uint16_t  Radio     :1;
    uint16_t  Fram      :1;
    uint16_t  Secure    :1;
    uint16_t  CTS       :1;
    uint16_t  Boot      :1;
    uint16_t  Pipe      :1;
    uint16_t  BeaconON  :1;
    uint16_t  Echo      :1;

    uint16_t  RfMode    :3;
    uint16_t  Reset     :1;
    uint16_t  UartBaud  :2;
    uint16_t  HFXT      :1;
    uint16_t  res2      :1;

} ESSA_UHF_status_control_word_t;

typedef struct
{
    ESSA_UHF_status_control_word_t Val;
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteScw_t;

typedef struct
{
    uint8_t au8IntPart[3];
    uint8_t Fractional;
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteRfConfig_t;

typedef struct
{
    uint16_t u16Period;
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteBeaconMessageTxPeriodConfig_t;

typedef struct
{
    uint16_t u16Period;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteBeaconMessageBetweenTxPeriodConfig_t;

typedef struct
{
    uint8_t u8Enable;
    uint8_t u8Time;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteAntennaReleaseConfig_t;

typedef struct
{
    uint8_t u8Algoruthm;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteAntenna_t;

typedef struct
{
    uint8_t au8Signature[6];
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteDestinationCallSign_t;

typedef ESSA_Uhf_RequestWriteDestinationCallSign_t ESSA_Uhf_RequestWriteSourceCallSign_t;

typedef struct
{
    uint8_t u8Size;
    uint8_t au8Signature[ESSA_UHF_MORSE_CALL_SIGN_MAX_SIZE];
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteMorseCallSign_t;

typedef struct
{
    uint8_t u8Size;
    uint8_t au8MIDI[ESSA_UHF_MIDI_AUDIO_BEACON_MAX_SIZE];
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteMidiAudioBeacon_t;

typedef struct
{
    uint8_t u8Size;
    uint8_t au8Message[ESSA_UHF_BEACON_MESSAGE_CONTENT_CONFIG_MAX_SIZE];
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteBeaconMessageContentConfig_t;

typedef struct
{
    uint8_t u8Addr;
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteDeviceAddrConfig_t;

typedef struct
{
    uint32_t u32Addr;
    uint8_t  au8Data[ESSA_UHF_FRAM_RW_DATA_SIZE];
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteFram_t;

typedef struct
{
    uint32_t u32Addr;
} __attribute__((__packed__)) ESSA_Uhf_RequestReadFram_t;

typedef struct
{
    uint8_t u8Group;
    uint8_t u8Offset;
    uint8_t u8Size;
    uint8_t au8Data[ESSA_UHF_TRANSCEIVER_PROPERTY_RW_DATA_MAX_SIZE];
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_RequestWriteTransceiverProperty_t;

typedef struct
{
    uint8_t u8Group;
    uint8_t u8Offset;
    uint8_t u8Size;
} __attribute__((__packed__)) ESSA_Uhf_RequestReadTransceiverProperty_t;

// Responses
typedef struct
{
    uint8_t  u8VersionMajor;
    uint16_t u16VersionMinor;
} __attribute__((__packed__)) ESSA_Uhf_ResponseVersion_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteScw_t;

typedef ESSA_Uhf_RequestWriteScw_t ESSA_Uhf_ResponseReadScw_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteRfConfig_t
;
typedef ESSA_Uhf_RequestWriteRfConfig_t ESSA_Uhf_ResponseReadRfConfig_t;

typedef struct
{
    uint32_t u32UpTime;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadUpTime_t;

typedef struct
{
    uint32_t u32Packets;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadNumberOfTxPackets_t;

typedef struct
{
    uint32_t u32Packets;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadNumberOfRxPackets_t;

typedef struct
{
    uint32_t u32Packets;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadNumberOfRxPacketsCRCerr_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteBeaconMessageTxPeriodConfig_t;

typedef ESSA_Uhf_RequestWriteBeaconMessageTxPeriodConfig_t ESSA_Uhf_ResponseReadBeaconMessageTxPeriodConfig_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteBeaconMessageBetweenTxPeriodConfig_t;

typedef ESSA_Uhf_RequestWriteBeaconMessageBetweenTxPeriodConfig_t ESSA_Uhf_ResponseReadBeaconMessageBetweenTxPeriodConfig_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseRestoreDefaultConfig_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteAntennaReleaseConfig_t;

typedef ESSA_Uhf_RequestWriteAntennaReleaseConfig_t  ESSA_Uhf_ResponseReadAntennaReleaseConfig_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteAntenna_t;

typedef struct
{
    uint32_t u32Status;
    uint8_t  u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadAntenna_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseEnterLowPowerMode_t;

typedef struct
{
    uint8_t u8Status;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadLowPowerMode_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteDestinationCallSign_t;

typedef ESSA_Uhf_RequestWriteDestinationCallSign_t ESSA_Uhf_ResponseReadDestinationCallSign_t;
typedef ESSA_Uhf_ResponseWriteDestinationCallSign_t ESSA_Uhf_ResponseWriteSourceCallSign_t;
typedef ESSA_Uhf_RequestWriteSourceCallSign_t  ESSA_Uhf_ResponseReadSourceCallSign_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteMorseCallSign_t;

typedef ESSA_Uhf_RequestWriteMorseCallSign_t ESSA_Uhf_ResponseReadMorseCallSign_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteMidiAudioBeacon_t;

typedef ESSA_Uhf_RequestWriteMidiAudioBeacon_t ESSA_Uhf_ResponseReadMidiAudioBeacon_t;

typedef struct
{
    uint8_t u8Version;
    uint8_t u8Increment;
    uint8_t au8DateTimeAsciiZ[ESSA_UHF_SW_BUILD_DATETIME_STRING_MAX_SIZE];
    uint8_t u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadSwVersionBuild_t;

typedef struct
{
    uint16_t u16Size;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadDevPayloadSize_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteBeaconMessageContentConfig_t;

typedef ESSA_Uhf_RequestWriteBeaconMessageContentConfig_t ESSA_Uhf_ResponseReadBeaconMessageContentConfig_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteDeviceAddrConfig_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteFram_t;

typedef struct
{
    uint32_t u32Addr;
    uint8_t  au8Data[ESSA_UHF_FRAM_RW_DATA_SIZE];
    uint8_t  u8Validity;
} __attribute__((__packed__)) ESSA_Uhf_ResponseReadFram_t;

typedef struct
{
    eESSA_UhfStatus_t eStatus;
} __attribute__((__packed__)) ESSA_Uhf_ResponseWriteTransceiverProperty_t;

typedef ESSA_Uhf_RequestWriteTransceiverProperty_t ESSA_Uhf_ResponseReadTransceiverProperty_t;

// Request handlers
typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteScwHandler_t)(ESSA_Uhf_RequestWriteScw_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadScw_t (*pfESSA_UhfFuncRequestReadScwHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteRfConfigHandler_t)(ESSA_Uhf_RequestWriteRfConfig_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadRfConfig_t (*pfESSA_UhfFuncRequestReadRfConfigHandler_t)(void);

typedef ESSA_Uhf_ResponseReadUpTime_t (*pfESSA_UhfFuncRequestReadUpTimeHandler_t)(void);

typedef ESSA_Uhf_ResponseReadNumberOfTxPackets_t (*pfESSA_UhfFuncRequestReadNumberOfTxPacketsHandler_t)(void);

typedef ESSA_Uhf_ResponseReadNumberOfRxPackets_t (*pfESSA_UhfFuncRequestReadNumberOfRxPacketsHandler_t)(void);

typedef ESSA_Uhf_ResponseReadNumberOfRxPacketsCRCerr_t (*pfESSA_UhfFuncRequestReadNumberOfRxPacketsCRCerrHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteBeaconMessageTxPeriodConfigHandler_t)(ESSA_Uhf_RequestWriteBeaconMessageTxPeriodConfig_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadBeaconMessageTxPeriodConfig_t (*pfESSA_UhfFuncRequestReadBeaconMessageTxPeriodConfigHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteBeaconMessageBetweenTxPeriodConfigHandler_t)(ESSA_Uhf_RequestWriteBeaconMessageBetweenTxPeriodConfig_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadBeaconMessageBetweenTxPeriodConfig_t (*pfESSA_UhfFuncRequestReadBeaconMessageBetweenTxPeriodConfigHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestRestoreDefaultConfig_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteAntennaReleaseConfigHandler_t)(ESSA_Uhf_RequestWriteAntennaReleaseConfig_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadAntennaReleaseConfig_t (*pfESSA_UhfFuncRequestReadAntennaReleaseConfigHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteAntennaHandler_t)(ESSA_Uhf_RequestWriteAntenna_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadAntenna_t (*pfESSA_UhfFuncRequestReadAntennaHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestEnterLowPowerModeHandler_t)(void);
typedef ESSA_Uhf_ResponseReadLowPowerMode_t (*pfESSA_UhfFuncRequestReadLowPowerModeHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteDestinationCallSignHandler_t)(ESSA_Uhf_RequestWriteDestinationCallSign_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadDestinationCallSign_t (*pfESSA_UhfFuncRequestReadDestinationCallSignHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteSourceCallSignHandler_t)(ESSA_Uhf_RequestWriteSourceCallSign_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadSourceCallSign_t (*pfESSA_UhfFuncRequestReadSourceCallSignHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteMorseCallSignHandler_t)(ESSA_Uhf_RequestWriteMorseCallSign_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadMorseCallSign_t (*pfESSA_UhfFuncRequestReadMorseCallSignHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteMidiAudioBeaconHandler_t)(ESSA_Uhf_RequestWriteMidiAudioBeacon_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadMidiAudioBeacon_t (*pfESSA_UhfFuncRequestReadMidiAudioBeaconHandler_t)(void);

typedef ESSA_Uhf_ResponseReadSwVersionBuild_t (*pfESSA_UhfFuncRequestReadSwVersionBuildHandler_t)(void);

typedef ESSA_Uhf_ResponseReadDevPayloadSize_t (*pfESSA_UhfFuncRequestReadDevPayloadSizeHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteBeaconMessageContentConfigHandler_t)(ESSA_Uhf_RequestWriteBeaconMessageContentConfig_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadBeaconMessageContentConfig_t (*pfESSA_UhfFuncRequestReadBeaconMessageContentConfigHandler_t)(void);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteDeviceAddrConfigHandler_t)(ESSA_Uhf_RequestWriteDeviceAddrConfig_t *fp_pRequestData);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteFramHandler_t)(ESSA_Uhf_RequestWriteFram_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadFram_t (*pfESSA_UhfFuncRequestReadFramHandler_t)(ESSA_Uhf_RequestReadFram_t *fs_Fram);

typedef eESSA_UhfStatus_t (*pfESSA_UhfFuncRequestWriteTransceiverPropertyHandler_t)(ESSA_Uhf_RequestWriteTransceiverProperty_t *fp_pRequestData);
typedef ESSA_Uhf_ResponseReadTransceiverProperty_t (*pfESSA_UhfFuncRequestReadTransceiverPropertyHandler_t)(ESSA_Uhf_RequestReadTransceiverProperty_t *fs_Fram);

// Response handlers
typedef void (*pfESSA_UhfFuncResponseVersionHandler_t)(ESSA_Uhf_ResponseVersion_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteScwHandler_t)(ESSA_Uhf_ResponseWriteScw_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadScwHandler_t)(ESSA_Uhf_ResponseReadScw_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteRfConfigHandler_t)(ESSA_Uhf_ResponseWriteRfConfig_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadRfConfigHandler_t)(ESSA_Uhf_ResponseReadRfConfig_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseReadUpTimeHandler_t)(ESSA_Uhf_ResponseReadUpTime_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseReadNumberOfTxPacketsHandler_t)(ESSA_Uhf_ResponseReadNumberOfTxPackets_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseReadNumberOfRxPacketsHandler_t)(ESSA_Uhf_ResponseReadNumberOfRxPackets_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseReadNumberOfRxPacketsCRCerrHandler_t)(ESSA_Uhf_ResponseReadNumberOfRxPacketsCRCerr_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteBeaconMessageTxPeriodConfigHandler_t)(ESSA_Uhf_ResponseWriteBeaconMessageTxPeriodConfig_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadBeaconMessageTxPeriodConfigHandler_t)(ESSA_Uhf_ResponseReadBeaconMessageTxPeriodConfig_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteBeaconMessageBetweenTxPeriodConfigHandler_t)(ESSA_Uhf_ResponseWriteBeaconMessageBetweenTxPeriodConfig_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadBeaconMessageBetweenTxPeriodConfigHandler_t)(ESSA_Uhf_ResponseReadBeaconMessageBetweenTxPeriodConfig_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseRestoreDefaultConfigHandler_t)(ESSA_Uhf_ResponseRestoreDefaultConfig_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteAntennaReleaseConfigHandler_t)(ESSA_Uhf_ResponseWriteAntennaReleaseConfig_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadAntennaReleaseConfigHandler_t)(ESSA_Uhf_ResponseReadAntennaReleaseConfig_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteAntennaHandler_t)(ESSA_Uhf_ResponseWriteAntenna_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadAntennaHandler_t)(ESSA_Uhf_ResponseReadAntenna_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseEnterLowPowerModeHandler_t)(ESSA_Uhf_ResponseEnterLowPowerMode_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadLowPowerModeHandler_t)(ESSA_Uhf_ResponseReadLowPowerMode_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteDestinationCallSignHandler_t)(ESSA_Uhf_ResponseWriteDestinationCallSign_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadDestinationCallSignHandler_t)(ESSA_Uhf_ResponseReadDestinationCallSign_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteSourceCallSignHandler_t)(ESSA_Uhf_ResponseWriteSourceCallSign_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadSourceCallSignHandler_t)(ESSA_Uhf_ResponseReadSourceCallSign_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteMorseCallSignHandler_t)(ESSA_Uhf_ResponseWriteMorseCallSign_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadMorseCallSignHandler_t)(ESSA_Uhf_ResponseReadMorseCallSign_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteMidiAudioBeaconHandler_t)(ESSA_Uhf_ResponseWriteMidiAudioBeacon_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadMidiAudioBeaconHandler_t)(ESSA_Uhf_ResponseReadMidiAudioBeacon_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseReadSwVersionBuildHandler_t)(ESSA_Uhf_ResponseReadSwVersionBuild_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseReadDevPayloadSizeHandler_t)(ESSA_Uhf_ResponseReadDevPayloadSize_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteBeaconMessageContentConfigHandler_t)(ESSA_Uhf_ResponseWriteBeaconMessageContentConfig_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadBeaconMessageContentConfigHandler_t)(ESSA_Uhf_ResponseReadBeaconMessageContentConfig_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteDeviceAddrConfigHandler_t)(ESSA_Uhf_ResponseWriteDeviceAddrConfig_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteFramHandler_t)(ESSA_Uhf_ResponseWriteFram_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadFramHandler_t)(ESSA_Uhf_ResponseReadFram_t *fp_pResponseData);

typedef void (*pfESSA_UhfFuncResponseWriteTransceiverPropertyHandler_t)(ESSA_Uhf_ResponseWriteTransceiverProperty_t *fp_pResponseData);
typedef void (*pfESSA_UhfFuncResponseReadTransceiverPropertyHandler_t)(ESSA_Uhf_ResponseReadTransceiverProperty_t *fp_pResponseData);


typedef struct
{
    pfESSA_UhfFuncResponseVersionHandler_t                                 RespVersion_Handler;

    pfESSA_UhfFuncRequestWriteScwHandler_t                                 ReqWriteSCW_Handler;
    pfESSA_UhfFuncRequestReadScwHandler_t                                  ReqReadSCW_Handler;

    pfESSA_UhfFuncRequestWriteRfConfigHandler_t                            ReqWriteRfConfig_Handler;
    pfESSA_UhfFuncRequestReadRfConfigHandler_t                             ReqReadRfConfig_Handler;

    pfESSA_UhfFuncRequestReadUpTimeHandler_t                               ReqReadUpTime_Handler;

    pfESSA_UhfFuncRequestReadNumberOfTxPacketsHandler_t                    ReqReadNumberOfTxPackets_Handler;

    pfESSA_UhfFuncRequestReadNumberOfRxPacketsHandler_t                    ReqReadNumberOfRxPackets_Handler;

    pfESSA_UhfFuncRequestReadNumberOfRxPacketsCRCerrHandler_t              ReqReadNumberOfRxPacketsCRCerr_Handler;

    pfESSA_UhfFuncRequestWriteBeaconMessageTxPeriodConfigHandler_t         ReqWriteBeaconMessageTxPeriodConfig_Handler;
    pfESSA_UhfFuncRequestReadBeaconMessageTxPeriodConfigHandler_t          ReqReadBeaconMessageTxPeriodConfig_Handler;

    pfESSA_UhfFuncRequestWriteBeaconMessageBetweenTxPeriodConfigHandler_t  ReqWriteBeaconMessageBetweenTxPeriodConfig_Handler;
    pfESSA_UhfFuncRequestReadBeaconMessageBetweenTxPeriodConfigHandler_t   ReqReadBeaconMessageBetweenTxPeriodConfig_Handler;

    pfESSA_UhfFuncRequestRestoreDefaultConfig_t                            ReqRestoreDefaultConfig_Handler;

    pfESSA_UhfFuncRequestWriteAntennaReleaseConfigHandler_t                ReqWriteAntennaReleaseConfig_Handler;
    pfESSA_UhfFuncRequestReadAntennaReleaseConfigHandler_t                 ReqReadAntennaReleaseConfig_Handler;

    pfESSA_UhfFuncRequestWriteAntennaHandler_t                             ReqWriteAntenna_Handler;
    pfESSA_UhfFuncRequestReadAntennaHandler_t                              ReqReadAntenna_Handler;

    pfESSA_UhfFuncRequestEnterLowPowerModeHandler_t                        ReqEnterLowPowerMode_Handler;
    pfESSA_UhfFuncRequestReadLowPowerModeHandler_t                         ReqReadLowPowerMode_Handler;

    pfESSA_UhfFuncRequestWriteDestinationCallSignHandler_t                 ReqWriteDestinationCallSign_Handler;
    pfESSA_UhfFuncRequestReadDestinationCallSignHandler_t                  ReqReadDestinationCallSign_Handler;

    pfESSA_UhfFuncRequestWriteSourceCallSignHandler_t                      ReqWriteSourceCallSign_Handler;
    pfESSA_UhfFuncRequestReadSourceCallSignHandler_t                       ReqReadSourceCallSign_Handler;

    pfESSA_UhfFuncRequestWriteMorseCallSignHandler_t                       ReqWriteMorseCallSign_Handler;
    pfESSA_UhfFuncRequestReadMorseCallSignHandler_t                        ReqReadMorseCallSign_Handler;

    pfESSA_UhfFuncRequestWriteMidiAudioBeaconHandler_t                     ReqWriteMidiAudioBeacon_Handler;
    pfESSA_UhfFuncRequestReadMidiAudioBeaconHandler_t                      ReqReadMidiAudioBeacon_Handler;

    pfESSA_UhfFuncRequestReadSwVersionBuildHandler_t                       ReqReadSwVersionBuild_Handler;

    pfESSA_UhfFuncRequestReadDevPayloadSizeHandler_t                       ReqReadDevPayloadSize_Handler;

    pfESSA_UhfFuncRequestWriteBeaconMessageContentConfigHandler_t          ReqWriteBeaconMessageContentConfig_Handler;
    pfESSA_UhfFuncRequestReadBeaconMessageContentConfigHandler_t           ReqReadBeaconMessageContentConfig_Handler;

    pfESSA_UhfFuncRequestWriteDeviceAddrConfigHandler_t                    ReqWriteDeviceAddrConfig_Handler;

    pfESSA_UhfFuncRequestWriteFramHandler_t                                ReqWriteFram_Handler;
    pfESSA_UhfFuncRequestReadFramHandler_t                                 ReqReadFram_Handler;

    pfESSA_UhfFuncRequestWriteTransceiverPropertyHandler_t                 ReqWriteTransceiverProperty_Handler;
    pfESSA_UhfFuncRequestReadTransceiverPropertyHandler_t                  ReqReadTransceiverProperty_Handler;

    // Responses
    pfESSA_UhfFuncResponseWriteScwHandler_t                                RespWriteScw_Handler;
    pfESSA_UhfFuncResponseReadScwHandler_t                                 RespReadScw_Handler;

    pfESSA_UhfFuncResponseWriteRfConfigHandler_t                           RespWriteRfConfig_Handler;
    pfESSA_UhfFuncResponseReadRfConfigHandler_t                            RespReadRfConfig_Handler;

    pfESSA_UhfFuncResponseReadUpTimeHandler_t                              RespReadUpTime_Handler;

    pfESSA_UhfFuncResponseReadNumberOfTxPacketsHandler_t                   RespReadNumberOfTxPackets_Handler;

    pfESSA_UhfFuncResponseReadNumberOfRxPacketsHandler_t                   RespReadNumberOfRxPackets_Handler;

    pfESSA_UhfFuncResponseReadNumberOfRxPacketsCRCerrHandler_t             RespReadNumberOfRxPacketsCRCerr_Handler;

    pfESSA_UhfFuncResponseWriteBeaconMessageTxPeriodConfigHandler_t        RespWriteBeaconMessageTxPeriodConfig_Handler;
    pfESSA_UhfFuncResponseReadBeaconMessageTxPeriodConfigHandler_t         RespReadBeaconMessageTxPeriodConfig_Handler;

    pfESSA_UhfFuncResponseWriteBeaconMessageBetweenTxPeriodConfigHandler_t RespWriteBeaconMessageBetweenTxPeriodConfig_Handler;
    pfESSA_UhfFuncResponseReadBeaconMessageBetweenTxPeriodConfigHandler_t  RespReadBeaconMessageBetweenTxPeriodConfig_Handler;

    pfESSA_UhfFuncResponseRestoreDefaultConfigHandler_t                    RespRestoreDefaultConfig_Handler;

    pfESSA_UhfFuncResponseWriteAntennaReleaseConfigHandler_t               RespWriteAntennaReleaseConfig_Handler;
    pfESSA_UhfFuncResponseReadAntennaReleaseConfigHandler_t                RespReadAntennaReleaseConfig_Handler;

    pfESSA_UhfFuncResponseWriteAntennaHandler_t                            RespWriteAntenna_Handler;
    pfESSA_UhfFuncResponseReadAntennaHandler_t                             RespReadAntenna_Handler;

    pfESSA_UhfFuncResponseEnterLowPowerModeHandler_t                       RespEnterLowPowerMode_Handler;
    pfESSA_UhfFuncResponseReadLowPowerModeHandler_t                        RespReadLowPowerMode_Handler;

    pfESSA_UhfFuncResponseWriteDestinationCallSignHandler_t                RespWriteDestinationCallSign_Handler;
    pfESSA_UhfFuncResponseReadDestinationCallSignHandler_t                 RespReadDestinationCallSign_Handler;

    pfESSA_UhfFuncResponseWriteSourceCallSignHandler_t                     RespWriteSourceCallSign_Handler;
    pfESSA_UhfFuncResponseReadSourceCallSignHandler_t                      RespReadSourceCallSign_Handler;

    pfESSA_UhfFuncResponseWriteMorseCallSignHandler_t                      RespWriteMorseCallSign_Handler;
    pfESSA_UhfFuncResponseReadMorseCallSignHandler_t                       RespReadMorseCallSign_Handler;

    pfESSA_UhfFuncResponseWriteMidiAudioBeaconHandler_t                    RespWriteMidiAudioBeacon_Handler;
    pfESSA_UhfFuncResponseReadMidiAudioBeaconHandler_t                     RespReadMidiAudioBeacon_Handler;

    pfESSA_UhfFuncResponseReadSwVersionBuildHandler_t                      RespReadSwVersionBuild_Handler;

    pfESSA_UhfFuncResponseReadDevPayloadSizeHandler_t                      RespReadDevPayloadSize_Handler;

    pfESSA_UhfFuncResponseWriteBeaconMessageContentConfigHandler_t         RespWriteBeaconMessageContentConfig_Handler;
    pfESSA_UhfFuncResponseReadBeaconMessageContentConfigHandler_t          RespReadBeaconMessageContentConfig_Handler;

    pfESSA_UhfFuncResponseWriteDeviceAddrConfigHandler_t                   RespWriteDeviceAddrConfig_Handler;

    pfESSA_UhfFuncResponseWriteFramHandler_t                               RespWriteFram_Handler;
    pfESSA_UhfFuncResponseReadFramHandler_t                                RespReadFram_Handler;

    pfESSA_UhfFuncResponseWriteTransceiverPropertyHandler_t                RespWriteTransceiverProperty_Handler;
    pfESSA_UhfFuncResponseReadTransceiverPropertyHandler_t                 RespReadTransceiverProperty_Handler;

    pfESSA_Stack_StatusHandler_Cbk_t                                       Error_Handler;
} Uhf_Api;

#endif // __ESSA_UHF_H__
