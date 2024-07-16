#ifndef __ESCP_RESETALLDEF_H__
#define __ESCP_RESETALLDEF_H__

/*
	Workflow of CP commands is to create new command on each change
	TripType = SESCP_CTT_NO_RESPONSE
*/

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

#define ESCP_RESET_ALL_SIGNATURE		0x54FD7AB34FFAD125LL

// ESCP_ResetAllReq::nResetMode
#define ESCP_RESET_ALL_TO_NORMAL		0
#define ESCP_RESET_ALL_TO_FAILSAFE		1

// CP Command request
typedef struct
{
	uint64_t nSignature;				// = ESCP_RESET_ALL_SIGNATURE
	uint8_t nResetMode;					// ESCP_RESET_ALL_TO_...

}  ESCP_ResetAllReq;

#pragma pack(pop)				// #pragma pack(1) - end of byte aligned structures

#endif		// #ifndef __ESCP_RESETALLDEF_H__

