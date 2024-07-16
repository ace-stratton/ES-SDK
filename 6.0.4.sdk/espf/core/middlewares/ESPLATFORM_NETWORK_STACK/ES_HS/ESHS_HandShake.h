#pragma once 
#ifndef ESHS_HANDSHAKE_H
#define ESHS_HANDSHAKE_H
//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#pragma pack(push)
#pragma pack(1)



typedef struct
{
  uint16_t nProtoVersion; //Handshake protocol version. 
  uint16_t nHeaderSize;
  uint8_t nCmdID; // ID of the current command. Unique.
  uint8_t nCmdType; // Type of the command.
  uint64_t nTime; // Used to calculate trip time. 
  uint64_t nSatID; // ID of the satelate we handshake with.
}  HS_Hdr;


typedef struct
{
  HS_Hdr oHeader;
  uint32_t nMTU; //Wireless MTU value of ES AIR MAC protocol 
  uint64_t nCapFlags; //If various features are supported for up/down link.
  uint8_t nProtocolCount ; //Supported protocol types count
  uint8_t nProtocolList[256] ; //Supported protocol list
}  HS_Resp;


typedef struct
{
  HS_Hdr oHeader;
  uint32_t nMTU; //Wireless MTU value of ES AIR MAC protocol
  uint64_t nCapFlags; //If various features are supported for up/down link.
  uint8_t nProtocolCount ; //Supported protocol types count
  uint8_t nProtocolList[1] ; //Supported protocol list
}HS_Resp_Hdr;

#pragma pack(pop)
#endif //ESHS_HANDSHAKE_H
