#include "ESSAT_ModuleTypes.h"

// Sync with .h file
static const char *const g_DevTypeStrings[ESPCMT_MAX] =
{
	"UNKNOWN",
	"MSP_MAC_GATEWAY_DEV",
	"EPSII_PDM",
	"EPSII_BP",
	"EPSII_BPL",
	"OBC_1O16",
	"OBC2",
	"UHF2",
	"EPS_I",
	"SBAND_TMTC",
};

const char *ESPCMT_GetDevTypeAsString(uint16_t nDevType)
{
	if(nDevType >= ESPCMT_MAX)
		return g_DevTypeStrings[ESPCMT_UNKNOWN];

	return g_DevTypeStrings[nDevType];
}
