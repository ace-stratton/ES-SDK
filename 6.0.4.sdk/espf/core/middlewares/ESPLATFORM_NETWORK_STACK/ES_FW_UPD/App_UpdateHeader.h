#ifndef __APP_UPDATE_HEADER_H__
#define __APP_UPDATE_HEADER_H__
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Headers for module update bundle. This header is intended to store information 
// for the device that this update has to be aplied and for update bundle integrity.
// This is common file and can be used here and in MSP430 TI CCS, too.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////
// Fixed net structures, aligned to 1 byte
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Software update protocol layer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SESSoftwareUPD_Hdr::nPreamble
#define SESUL_PREAMBLE						0x13579BDF

// SESSoftwareUPD_Hdr::nProtoVersion
#define SESUL_PROTO_VER						1

// Upload protocol command
#define SESUL_CMD_UPLOAD				    0
#define SESUL_CMD_GET_STATUS			    1
#define SESUL_CMD_GO_UPDATE				    2

typedef struct
{
	uint32_t nPreamble;			    // SESUL_PREAMBLE, Used by SAT module. Used to validate start of packet
	uint16_t nProtoVersion;		    // SESUL_PROTO_VER, This structure version (not expected many iterations)
	uint8_t nCmd;					// Command SESUL_CMD_...

} SESSoftwareUPD_Hdr;


// SESSoftwareUPD_Bundle::nSubModule
#define SESUL_SUB_MODULE_NONE				0

// SESSoftwareUPD_Bundle::nModuleType
#define SESUL_MODULE_TYPE_MSP_EXP430_FR5994	1

// SESSoftwareUPD_Bundle::nModuleConfig
#define SESUL_MODULE_CONFIG_EPS2_BP         0
#define SESUL_MODULE_CONFIG_EPS2_PDM        1

// SESSoftwareUPD_Bundle::nBoardRevision
#define SESUL_MODULE_REVISION_EPS2_PDM      1
#define SESUL_MODULE_REVISION_EPS2_BP       2

// Supported CPU types
#define SESUL_CPU_TYPE_MSP430_FR5994		1

// Supported firmware types 
#define SESUL_FW_TYPE_EPS2_BP               1
#define SESUL_FW_TYPE_EPS2_BP_FAIL          2
#define SESUL_FW_TYPE_EPS2_PDM              3
#define SESUL_FW_TYPE_EPS2_PDM_FAIL         4

#define SESUL_FL_NONE                       0x0000000000000000
#define SESUL_FL_INSTALLED                  0x0000000000000001
#define SESUL_FL_ENCRYPTED                  0x0000000000000002
#define SESUL_FL_ARCHIVED                   0x0000000000000004 // Some compression
#define SESUL_FL_HEALTHY                    0x0000000000000008
#define SESUL_FL_DOWNLOADED                 0x0000000000000010
#define SESUL_FL_INSTALL_PENDING            0x0000000000000020
#define SESUL_FL_FILE_SAFE_APP              0x0000000000000040
#define SESUL_FL_FILE_TLE                   0x0000000000000080 // TLE File
#define SESUL_FL_PAYLOAD_SCHEDULE           0x0000000000000100 // Payload scheduler file
#define SESUL_FL_FILE_ZIP                   0x0000000000000200 // zip archive
#define SESUL_FL_FILE_CMD                   0x0000000000000400 // CMD file

typedef struct
{
	SESSoftwareUPD_Hdr hdr;

	uint16_t nSubModule;			// SESUL_SUB_MODULE_..., Which sub-module to be updated if several slaves exist (OBC->S-band)
	uint16_t nModuleType;			// ESPCMT_..., Type of the module from ESPLATFORM_COMMON/ESSAT_ModuleTypes.h
	uint16_t nModuleConfig;		    // SESUL_MODULE_CONFIG_..., If module can be configured with several other sub-boards
	uint16_t nBoardRevision;		// SESUL_MODULE_REVISION, Format TBD
	uint16_t nCPUType;			    // SESUL_CPU_TYPE_..., Type of the processor
	uint16_t nFWType;				// SESUL_FW_TYPE_..., Firmware type
	uint16_t nFWVerMaj;			    // Major Firmware version (if = 0xFFFF, update is invalid)
	uint16_t nFWVerMin;			    // Minor Firmware version (if = 0xFFFF, update is invalid)
    uint64_t nFlags;                // Additional information for update like if compressed / encrypted etc. SESUL_FL_...
	// Payload
	// CRC32
} SESSoftwareUPD_Bundle;


// Data blocks size to calculate CRC for each
#define MSP430_DEV_UPD_CRC_BLOCK_SIZE				1000

typedef struct
{
	uint16_t nCRC_BlockSize;		// Size of the CRC blocks in bytes. MSP430_DEV_UPD_CRC_BLOCK_SIZE.
								    // CRC32 is clculated for each block starting from the beginning of the update bundle including this header
								    // and not including 'SESSoftwareUPD_Hdr' header and the footer.
	                                // If last block is smaller than m_nCRC_BlockSize - Last CRC is calculated for last block size
								    // Every 4 bytes of CRC are appended to m_updateCrcData member, in update footer. Class CFooter;

	uint32_t nUpdateSize;			// Size of the update without this header and without the footer
} SHdr_Update_MSP430;

// Upload protocol status
// SESSoftwareUPD_Status::nStatus
#define SESUL_UPLS_FREE					0		/* No complete upload bundle received */
#define SESUL_UPLS_WAITING				1		/* Upload received ok, and pending for update */
#define SESUL_UPLS_BAD_UPDATE			2		/* Upload received ok, but module validate update as bad */
#define SESUL_UPLS_UPDATE_COMPLETED		3		/* Firmware update performed, error/success code in SESSoftwareUPD_Status::nError */

// Upload protocol error codes
// SESSoftwareUPD_Status::nError
#define SESUL_UPLE_SUCCESS				0		/* No error */

#define SESUL_UPLE_CMD_BAD_CRC			10		/* Command received with bad crc */
#define SESUL_UPLE_CMD_UNKNWON_CMD		11		/* Unknown/Unsupported Command received */
#define SESUL_UPLE_CMD_BAD_PARAMS		12		/* Command received with incorrect parameters */

#define SESUL_UPLE_UPL_BAD_PARAMS		20		/* Bundle received with incorrect parameters */
#define SESUL_UPLE_UPL_BAD_CRC			21		/* Bundle received with bad crc */
#define SESUL_UPLE_UPL_BAD_VER			22		/* Bundle received with bad protocol version */
#define SESUL_UPLE_UPL_INT_ERROR        23      /* Internal error while processing received bundle */
#define SESUL_UPLE_UPL_WRONG_PREAMBLE   24      /* Bundle received with wrong preamble */
#define SESUL_UPLE_UPL_WRONG_CPU_TYPE   25      /* Bundle received with wrong CPU type */
#define SESUL_UPLE_UPL_WRONG_MOD_TYPE   26      /* Bundle received with wrong module type */
#define SESUL_UPLE_UPL_WRONG_CONF_TYPE  27      /* Bundle received with wrong config type */
#define SESUL_UPLE_UPL_WRONG_HW_REV     28      /* Bundle received with wrong hardware revision */

typedef struct
{
	SESSoftwareUPD_Hdr hdr;

	uint8_t nStatus;			// Upload status SESUL_UPLS_...
	uint8_t nError;			    // Error, related to current status SESUL_UPLE_...
	uint32_t nCRC32;
} SESSoftwareUPD_Status;

#pragma pack(pop)

#endif // __APP_UPDATE_HEADER_H__
