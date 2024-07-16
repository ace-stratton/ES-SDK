/*
 * Global definition of EnduroSat concept of operations
 * https://endurosat.atlassian.net/wiki/spaces/SPE/pages/1998487565/Platform+general+ConOps+and+transition+logic
 */
#ifndef __ESSAT_CONOPS_H__
#define __ESSAT_CONOPS_H__

#include <stdint.h>

// TCONOPS_ModulesMask may be used to switch on/off individual modules and/or operations
// It may be used between ConOps master (OBC) and modules, EPS will only force it to be 0, 
// if con-ops mode ID is < CONOPS_PAYLOAD_BASE
// Currently ConOps mode is used only, this is for future use if needed
//typedef uint64_t TCONOPS_ModulesMask;	// defined in ESPLATFORM_NETWORK_STACK, to avoid repository dependence

// Current ConOps mode for satellite.
// Those 2 are broadcasted by service protocol.
// EPS will keep and broadcast current mode, and will force CONOPS_HELL, CONOPS_BAT_OVERHEAT and CONOPS_PHENIX if need to.
// If EPS Mode allow CONOPS_SAFE, it will broadcast it, and OBC will need to request higher modes to EPS.
// In case we use third-party EPS, OBC may broadcast ConOps mode instead of EPS.

//typedef uint8_t TCONOPS_ModeID;	// defined in ESPLATFORM_NETWORK_STACK, to avoid repository dependence
#define CONOPS_UNKNOWN			0
#define CONOPS_HELL				1		/* EPS only, all power supply to system are off */
#define CONOPS_BAT_OVERHEAT		2		/* UHF/TMTS and EPS only */
#define CONOPS_PHENIX			3		/* UHF/TMTS and EPS only */
#define CONOPS_SAFE				4
#define CONOPS_IDLE				5
#define CONOPS_DETUMB			6

#define CONOPS_PAYLOAD_BASE		20		/* And up, different payloads working */

// There could be any number of additional modes after last one, depending on mission.
// However, these are mandatory and fixed ones.

#endif // __ESSAT_CONOPS_H__
