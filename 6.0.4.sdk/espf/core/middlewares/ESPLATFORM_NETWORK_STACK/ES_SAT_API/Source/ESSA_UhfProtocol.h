/*
 * DiscoveryProtocol.h
 *
 *  Created on: May 16, 2020
 *      Author: Georgi-EnduroSat
 */

#ifndef UHFPROTOCOL_H_
#define UHFPROTOCOL_H_

#include <stdint.h>

#include "../include/ESSA_Stack.h"
#include "../include/ESSA_Uhf.h"

#define ESSA_UHF_REQUEST_VERSION_ID                                   ((uint8_t) 0)
#define ESSA_UHF_REQUEST_WRITE_SCW_ID                                 ((uint8_t) 1)
#define ESSA_UHF_REQUEST_READ_SCW_ID                                  ((uint8_t) 2)
#define ESSA_UHF_REQUEST_WRITE_RFCONFIG_ID                            ((uint8_t) 3)
#define ESSA_UHF_REQUEST_READ_RFCONFIG_ID                             ((uint8_t) 4)
#define ESSA_UHF_REQUEST_READ_UPTIME_ID                               ((uint8_t) 5)
#define ESSA_UHF_REQUEST_READ_NUMBEROFTXPACKETS_ID                    ((uint8_t) 6)
#define ESSA_UHF_REQUEST_READ_NUMBEROFRXPACKETS_ID                    ((uint8_t) 7)
#define ESSA_UHF_REQUEST_READ_NUMBEROFRXPACKETSCRCERR_ID              ((uint8_t) 8)
#define ESSA_UHF_REQUEST_WRITE_BEACONMESSAGETXPERIODCONFIG_ID         ((uint8_t) 9)
#define ESSA_UHF_REQUEST_READ_BEACONMESSAGETXPERIODCONFIG_ID          ((uint8_t) 10)
#define ESSA_UHF_REQUEST_WRITE_BEACONMESSAGEBETWEENTXPERIODCONFIG_ID  ((uint8_t) 11)
#define ESSA_UHF_REQUEST_READ_BEACONMESSAGEBETWEENTXPERIODCONFIG_ID   ((uint8_t) 12)
#define ESSA_UHF_REQUEST_RESTORE_DEFAULTCONFIG_ID                     ((uint8_t) 13)
#define ESSA_UHF_REQUEST_WRITE_ANTENNARELEASECONFIG_ID                ((uint8_t) 14)
#define ESSA_UHF_REQUEST_READ_ANTENNARELEASECONFIG_ID                 ((uint8_t) 15)
#define ESSA_UHF_REQUEST_WRITE_ANTENNA_ID                             ((uint8_t) 16)
#define ESSA_UHF_REQUEST_READ_ANTENNA_ID                              ((uint8_t) 17)
#define ESSA_UHF_REQUEST_ENTER_LOWPOWERMODE_ID                        ((uint8_t) 18)
#define ESSA_UHF_REQUEST_READ_LOWPOWERMODE_ID                         ((uint8_t) 19)
#define ESSA_UHF_REQUEST_WRITE_DESTINATIONCALLSIGN_ID                 ((uint8_t) 20)
#define ESSA_UHF_REQUEST_READ_DESTINATIONCALLSIGN_ID                  ((uint8_t) 21)
#define ESSA_UHF_REQUEST_WRITE_SOURCECALLSIGN_ID                      ((uint8_t) 22)
#define ESSA_UHF_REQUEST_READ_SOURCECALLSIGN_ID                       ((uint8_t) 23)
#define ESSA_UHF_REQUEST_WRITE_MORSECALLSIGN_ID                       ((uint8_t) 24)
#define ESSA_UHF_REQUEST_READ_MORSECALLSIGN_ID                        ((uint8_t) 25)
#define ESSA_UHF_REQUEST_WRITE_MIDIAUDIOBEACON_ID                     ((uint8_t) 26)
#define ESSA_UHF_REQUEST_READ_MIDIAUDIOBEACON_ID                      ((uint8_t) 27)
#define ESSA_UHF_REQUEST_READ_SWVERSIONBUILD_ID                       ((uint8_t) 28)
#define ESSA_UHF_REQUEST_READ_PAYLOADSIZE_ID                          ((uint8_t) 29)
#define ESSA_UHF_REQUEST_WRITE_BEACONMESSAGECONTENTCONFIG_ID          ((uint8_t) 30)
#define ESSA_UHF_REQUEST_READ_BEACONMESSAGECONTENTCONFIG_ID           ((uint8_t) 31)
#define ESSA_UHF_REQUEST_WRITE_DEVICEADDRCONFIG_ID                    ((uint8_t) 32)
#define ESSA_UHF_REQUEST_WRITE_FRAM_ID                                ((uint8_t) 33)
#define ESSA_UHF_REQUEST_READ_FRAM_ID                                 ((uint8_t) 34)
#define ESSA_UHF_REQUEST_WRITE_TRANSCEIVERPROPERTY_ID                 ((uint8_t) 35)
#define ESSA_UHF_REQUEST_READ_TRANSCEIVERPROPERTY_ID                  ((uint8_t) 36)

#define ESSA_UHF_RESPONSE_VERSION_ID                                  ((uint8_t) 125 + 0)
#define ESSA_UHF_RESPONSE_WRITE_SCW_ID                                ((uint8_t) 125 + 1)
#define ESSA_UHF_RESPONSE_READ_SCW_ID                                 ((uint8_t) 125 + 2)
#define ESSA_UHF_RESPONSE_WRITE_RFCONFIG_ID                           ((uint8_t) 125 + 3)
#define ESSA_UHF_RESPONSE_READ_RFCONFIG_ID                            ((uint8_t) 125 + 4)
#define ESSA_UHF_RESPONSE_READ_UPTIME_ID                              ((uint8_t) 125 + 5)
#define ESSA_UHF_RESPONSE_READ_NUMBEROFTXPACKETS_ID                   ((uint8_t) 125 + 6)
#define ESSA_UHF_RESPONSE_READ_NUMBEROFRXPACKETS_ID                   ((uint8_t) 125 + 7)
#define ESSA_UHF_RESPONSE_READ_NUMBEROFRXPACKETSCRCERR_ID             ((uint8_t) 125 + 8)
#define ESSA_UHF_RESPONSE_WRITE_BEACONMESSAGETXPERIODCONFIG_ID        ((uint8_t) 125 + 9)
#define ESSA_UHF_RESPONSE_READ_BEACONMESSAGETXPERIODCONFIG_ID         ((uint8_t) 125 + 10)
#define ESSA_UHF_RESPONSE_WRITE_BEACONMESSAGEBETWEENTXPERIODCONFIG_ID ((uint8_t) 125 + 11)
#define ESSA_UHF_RESPONSE_READ_BEACONMESSAGEBETWEENTXPERIODCONFIG_ID  ((uint8_t) 125 + 12)
#define ESSA_UHF_RESPONSE_RESTORE_DEFAULTCONFIG_ID                    ((uint8_t) 125 + 13)
#define ESSA_UHF_RESPONSE_WRITE_ANTENNARELEASECONFIG_ID               ((uint8_t) 125 + 14)
#define ESSA_UHF_RESPONSE_READ_ANTENNARELEASECONFIG_ID                ((uint8_t) 125 + 15)
#define ESSA_UHF_RESPONSE_WRITE_ANTENNA_ID                            ((uint8_t) 125 + 16)
#define ESSA_UHF_RESPONSE_READ_ANTENNA_ID                             ((uint8_t) 125 + 17)
#define ESSA_UHF_RESPONSE_ENTER_LOWPOWERMODE_ID                       ((uint8_t) 125 + 18)
#define ESSA_UHF_RESPONSE_READ_LOWPOWERMODE_ID                        ((uint8_t) 125 + 19)
#define ESSA_UHF_RESPONSE_WRITE_DESTINATIONCALLSIGN_ID                ((uint8_t) 125 + 20)
#define ESSA_UHF_RESPONSE_READ_DESTINATIONCALLSIGN_ID                 ((uint8_t) 125 + 21)
#define ESSA_UHF_RESPONSE_WRITE_SOURCECALLSIGN_ID                     ((uint8_t) 125 + 22)
#define ESSA_UHF_RESPONSE_READ_SOURCECALLSIGN_ID                      ((uint8_t) 125 + 23)
#define ESSA_UHF_RESPONSE_WRITE_MORSECALLSIGN_ID                      ((uint8_t) 125 + 24)
#define ESSA_UHF_RESPONSE_READ_MORSECALLSIGN_ID                       ((uint8_t) 125 + 25)
#define ESSA_UHF_RESPONSE_WRITE_MIDIAUDIOBEACON_ID                    ((uint8_t) 125 + 26)
#define ESSA_UHF_RESPONSE_READ_MIDIAUDIOBEACON_ID                     ((uint8_t) 125 + 27)
#define ESSA_UHF_RESPONSE_READ_SWVERSIONBUILD_ID                      ((uint8_t) 125 + 28)
#define ESSA_UHF_RESPONSE_READ_PAYLOADSIZE_ID                         ((uint8_t) 125 + 29)
#define ESSA_UHF_RESPONSE_WRITE_BEACONMESSAGECONTENTCONFIG_ID         ((uint8_t) 125 + 30)
#define ESSA_UHF_RESPONSE_READ_BEACONMESSAGECONTENTCONFIG_ID          ((uint8_t) 125 + 31)
#define ESSA_UHF_RESPONSE_WRITE_DEVICEADDRCONFIG_ID                   ((uint8_t) 125 + 32)
#define ESSA_UHF_RESPONSE_WRITE_FRAM_ID                               ((uint8_t) 125 + 33)
#define ESSA_UHF_RESPONSE_READ_FRAM_ID                                ((uint8_t) 125 + 34)
#define ESSA_UHF_RESPONSE_WRITE_TRANSCEIVERPROPERTY_ID                ((uint8_t) 125 + 35)
#define ESSA_UHF_RESPONSE_READ_TRANSCEIVERPROPERTY_ID                 ((uint8_t) 125 + 36)

typedef struct
{
    uint8_t u8FuncId;
} __attribute__((__packed__)) ESSA_UhfProtocol_RequestHdr_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__)) ESSA_UhfProtocol_RequestVersion_t;

// Req WriteSCW
typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_RequestWriteScw_t    Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteScw_t;

// Req ReadSCW
typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadScw_t;


typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t   Hdr;
    ESSA_Uhf_RequestWriteRfConfig_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteRfConfig_t;

// Req ReadSCW
typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadRfConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadUpTime_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadNumberOfTxPackets_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadNumberOfRxPackets_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadNumberOfRxPacketsCRCerr_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                      Hdr;
    ESSA_Uhf_RequestWriteBeaconMessageTxPeriodConfig_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteBeaconMessageTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadBeaconMessageTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                             Hdr;
    ESSA_Uhf_RequestWriteBeaconMessageBetweenTxPeriodConfig_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteBeaconMessageBetweenTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadBeaconMessageBetweenTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestRestoreDefaultConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t               Hdr;
    ESSA_Uhf_RequestWriteAntennaReleaseConfig_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteAntennaReleaseConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadAntennaReleaseConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t  Hdr;
    ESSA_Uhf_RequestWriteAntenna_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteAntenna_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadAntenna_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestEnterLowPowerMode_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadLowPowerMode_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t              Hdr;
    ESSA_Uhf_RequestWriteDestinationCallSign_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteDestinationCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadDestinationCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t         Hdr;
    ESSA_Uhf_RequestWriteSourceCallSign_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteSourceCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadSourceCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t        Hdr;
    ESSA_Uhf_RequestWriteMorseCallSign_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteMorseCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadMorseCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t          Hdr;
    ESSA_Uhf_RequestWriteMidiAudioBeacon_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteMidiAudioBeacon_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadMidiAudioBeacon_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadSwVersionBuild_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadDevPayloadSize_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                     Hdr;
    ESSA_Uhf_RequestWriteBeaconMessageContentConfig_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteBeaconMessageContentConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadBeaconMessageContentConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t           Hdr;
    ESSA_Uhf_RequestWriteDeviceAddrConfig_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteDeviceAddrConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_RequestWriteFram_t   Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteFram_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_RequestReadFram_t    Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadFram_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t              Hdr;
    ESSA_Uhf_RequestWriteTransceiverProperty_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestWriteTransceiverProperty_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t             Hdr;
    ESSA_Uhf_RequestReadTransceiverProperty_t Data;
} __attribute__((__packed__))   ESSA_UhfProtocol_RequestReadTransceiverProperty_t;

// Responses
typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_ResponseVersion_t    Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseVersion_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_ResponseWriteScw_t   Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteScw_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_ResponseReadScw_t    Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadScw_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t    Hdr;
    ESSA_Uhf_ResponseWriteRfConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteRfConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t   Hdr;
    ESSA_Uhf_ResponseReadRfConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadRfConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_ResponseReadUpTime_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadUpTime_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t            Hdr;
    ESSA_Uhf_ResponseReadNumberOfTxPackets_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadNumberOfTxPackets_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t            Hdr;
    ESSA_Uhf_ResponseReadNumberOfRxPackets_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadNumberOfRxPackets_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                  Hdr;
    ESSA_Uhf_ResponseReadNumberOfRxPacketsCRCerr_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadNumberOfRxPacketsCRCerr_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                       Hdr;
    ESSA_Uhf_ResponseWriteBeaconMessageTxPeriodConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteBeaconMessageTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                      Hdr;
    ESSA_Uhf_ResponseReadBeaconMessageTxPeriodConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadBeaconMessageTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                              Hdr;
    ESSA_Uhf_ResponseWriteBeaconMessageBetweenTxPeriodConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteBeaconMessageBetweenTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                             Hdr;
    ESSA_Uhf_ResponseReadBeaconMessageBetweenTxPeriodConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadBeaconMessageBetweenTxPeriodConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t           Hdr;
    ESSA_Uhf_ResponseRestoreDefaultConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseRestoreDefaultConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                Hdr;
    ESSA_Uhf_ResponseWriteAntennaReleaseConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteAntennaReleaseConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t               Hdr;
    ESSA_Uhf_ResponseReadAntennaReleaseConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadAntennaReleaseConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t   Hdr;
    ESSA_Uhf_ResponseWriteAntenna_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteAntenna_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t  Hdr;
    ESSA_Uhf_ResponseReadAntenna_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadAntenna_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t        Hdr;
    ESSA_Uhf_ResponseEnterLowPowerMode_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseEnterLowPowerMode_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t       Hdr;
    ESSA_Uhf_ResponseReadLowPowerMode_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadLowPowerMode_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t               Hdr;
    ESSA_Uhf_ResponseWriteDestinationCallSign_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteDestinationCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t              Hdr;
    ESSA_Uhf_ResponseReadDestinationCallSign_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadDestinationCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t          Hdr;
    ESSA_Uhf_ResponseWriteSourceCallSign_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteSourceCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t         Hdr;
    ESSA_Uhf_ResponseReadSourceCallSign_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadSourceCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t         Hdr;
    ESSA_Uhf_ResponseWriteMorseCallSign_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteMorseCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t        Hdr;
    ESSA_Uhf_ResponseReadMorseCallSign_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadMorseCallSign_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t           Hdr;
    ESSA_Uhf_ResponseWriteMidiAudioBeacon_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteMidiAudioBeacon_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t          Hdr;
    ESSA_Uhf_ResponseReadMidiAudioBeacon_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadMidiAudioBeacon_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t         Hdr;
    ESSA_Uhf_ResponseReadSwVersionBuild_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadSwVersionBuild_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t         Hdr;
    ESSA_Uhf_ResponseReadDevPayloadSize_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadDevPayloadSize_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                      Hdr;
    ESSA_Uhf_ResponseWriteBeaconMessageContentConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteBeaconMessageContentConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t                     Hdr;
    ESSA_Uhf_ResponseReadBeaconMessageContentConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadBeaconMessageContentConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t            Hdr;
    ESSA_Uhf_ResponseWriteDeviceAddrConfig_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteDeviceAddrConfig_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_ResponseWriteFram_t  Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteFram_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t Hdr;
    ESSA_Uhf_ResponseReadFram_t   Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseReadFram_t;


typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t               Hdr;
    ESSA_Uhf_ResponseWriteTransceiverProperty_t Data;
} __attribute__((__packed__)) ESSA_UhfProtocol_ResponseWriteTransceiverProperty_t;

typedef struct
{
    ESSA_UhfProtocol_RequestHdr_t              Hdr;
    ESSA_Uhf_ResponseReadTransceiverProperty_t Data;
} __attribute__((__packed__)) UhfProtocol_ResponseReadTransceiverProperty_t;

ESSA_pStack_ProtocolInfo_t ESSA_StackUhfProtocol(void);

#endif /* UHFPROTOCOL_H_ */
