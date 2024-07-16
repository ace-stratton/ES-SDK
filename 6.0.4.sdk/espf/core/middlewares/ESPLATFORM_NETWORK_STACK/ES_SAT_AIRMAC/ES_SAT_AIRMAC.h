/*
*		Definition of ES Ground Station to UHF communication ONLY
*/

#ifndef __ES_SAT_AIRMAC_H__
#define __ES_SAT_AIRMAC_H__

#include <stdint.h>

//#include "ES_SAT_MAC_Context.h" FD: This should not be needed in AIR MAC

// Special MAC addresses
// FD: This should not be needed in AIR MAC, we target packets directly to specific UHF
//#define ESSATAIRMAC_ADDR_BROADCAST		((uint8_t) 0xFF)
//#define ESSATAIRMAC_ADDR_GATEWAY_DEV	((uint8_t) 0x01)		/* This should be changed to 01 or something */

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

// Definition of AIR MAC header
//////////////////////////////////////////////////////////////////////////

#define ESSATAIRMAC_MAX_PKT_SIZE                    128

// ESSATAIRMAC_Header::u8Protocol
#define ESSATAIRMAC_PROTOCOL_INIT_HANDSHAKE         1
#define ESSATAIRMAC_PROTOCOL_INIT_HANDSHAKE_RES     2
#define ESSATAIRMAC_PROTOCOL_ESTL_1                 3
#define ESSATAIRMAC_PROTOCOL_RESET                  4
#define ESSATAIRMAC_PROTOCOL_TEXT_BEGIN             0x20        /* Frame is composed with ASCII */
#define ESSATAIRMAC_PROTOCOL_TEXT_END               0x7F

#define ESSATAIRMAC_CRC16_SEED                      ((uint16_t) 0xFFFF)

// Network lowest layer message, as it is serialized over AIR
typedef struct
{
    uint8_t  u8Protocol;                    // Keep first, ESSATAIRMAC_PROTOCOL_...
    uint8_t  u8UHFAddr;                     // Target SAT UHF
    uint8_t  u8DataSize;                    // sizeof data after this header, including last 4 bytes CRC
    uint16_t uHdrCRC16;                     // CRC 16 of above fields - CRC-CCITT-BR (MSP430 cpu 16 bit CRC HW), send LSB first
} ESSATAIRMAC_Header;

#define ESSATAIRMAC_CRC32_SEED                      ((uint32_t) 0xFFFFFFFF)

typedef struct
{
    uint32_t u32CRC;                        // CRC 32 of all message above, including header and it's CRC - CRC32-ISO3309 (MSP430 cpu 32 bit CRC HW), send LSB first
} ESSATAIRMAC_Footer;

#define ESSATAIRMAC_HEADER_SIZE                     sizeof(ESSATAIRMAC_Header)
#define ESSATAIRMAC_FOOTER_SIZE                     sizeof(ESSATAIRMAC_Footer)
#define ESSATAIRMAC_MAX_PAYLOAD_SIZE                (ESSATAIRMAC_MAX_PKT_SIZE - (sizeof(ESSATAIRMAC_Header) + sizeof(ESSATAIRMAC_Footer)))

typedef struct
{
    ESSATAIRMAC_Header hdr;
    uint8_t            au8Data[ESSATAIRMAC_MAX_PAYLOAD_SIZE];
    ESSATAIRMAC_Footer ftr;
} ESSATAIRMAC_Message;

// ESSATAIRMAC_PROTOCOL_INIT_HANDSHAKE
//////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint16_t nVersion;                  // = 1. Version of this structure - backward & forward compatibility should be preserved. i.e. only add fields

    uint64_t nSatId;                    // Satellite ID
    uint64_t nGSID;                     // Ground station ID
    uint64_t nRequestCapFlags;          // Requested connection capability flags (if stream compressed, encrypted, etc) TBD
    uint64_t nSessionID;                // Use != 0
} ESSATAIRMAC_InitHandshake;

typedef struct
{
    ESSATAIRMAC_Header        hdr;
    ESSATAIRMAC_InitHandshake msg;
    ESSATAIRMAC_Footer        ftr;
} ESSATAIRMAC_InitHandshakePkt;

// ESSATAIRMAC_PROTOCOL_INIT_HANDSHAKE_RES
//////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint16_t nVersion;                  // = 1. Version of this structure - backward & forward compatibility should be preserved. i.e. only add fields

    uint16_t nAirMTU;                   //
    uint64_t nAcceptedCapFlags;         // Which flags are accepted from nRequestCapFlags (return 0 for now)
    uint64_t nSessionID;                // return ESSATAIRMAC_InitHandshake::nSessionID
    uint16_t nTLProtocolVersion;        // = 1 currently
} ESSATAIRMAC_InitHandshakeRes;

typedef struct
{
    ESSATAIRMAC_Header           hdr;
    ESSATAIRMAC_InitHandshakeRes msg;
    ESSATAIRMAC_Footer           ftr;
} ESSATAIRMAC_InitHandshakeResPkt;

typedef struct
{
    uint64_t nSatId;
    uint64_t nCmdID;
    uint32_t nCmdType;
    uint8_t  *pCMDPkt;
    uint32_t nCMDPktSize;
} ESSATAIRMAC_ResetAll;

// #pragma pack(1) - end of byte aligned structures
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif      // #ifndef __ES_SAT_MAC_H__
