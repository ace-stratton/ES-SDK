/*
 * Global definition of EnduroSat module types
 * Required by discovery and other common functionality
 * https://endurosat.atlassian.net/wiki/spaces/ENDUROSAT/pages/469631140/Product+Codes
 */
#ifndef __ESSAT_MODULETYPES_H__
#define __ESSAT_MODULETYPES_H__

#include <stdint.h>

// uint16_t 
// Sync with .c file
#define ESPCMT_UNKNOWN                              0

#define ESPCMT_MSP_MAC_GATEWAY_DEV                  1       /* Test device to test/control MAC network operation */
#define ESPCMT_EPSII_PDM                            2       /* EPSII Power Distribution Module */
#define ESPCMT_EPSII_BP                             3       /* EPSII Battery Pack */
#define ESPCMT_EPSII_BPL                            4       /* EPSII Battery Pack Light version (4 battery) */
#define ESPCMT_OBC_1O16                             5       /* OBC 1.6 device */
#define ESPCMT_OBC2                                 6       /* OBC 2 device */
#define ESPCMT_UHF2                                 7       /* UHF 2 device */
#define ESPCMT_EPS_I                                8       /* EPS I  device */
#define ESPCMT_SBAND_TMTC                           9       /* SBAND TMTC device */
#define ESPCMT_ANTENNA                             10       /* UHF Antenna */
#define ESPCMT_SOLAR_PANEL                         11       /* Solar Panel */
#define ESPCMT_EPS_III_INSTAGE                     12       /* EPSIII Solar panel input stage*/
#define ESPCMT_EPS_III_PDM_I                       13       /* EPSIII Power Distribution Module I */
#define ESPCMT_EPS_III_PDM_II                      14       /* EPSIII Power Distribution Module II */
#define ESPCMT_EPS_III_PROTECT                     15       /* EPSIII Protective board */
#define ESPCMT_EPS_III_BATTPACK_LI_ION             16       /* EPSIII Battery Pack with Li-Ion battery */
#define ESPCMT_EPS_III_BATTPACK_LIFEPO4            17       /* EPSIII Battery Pack with LiFePo4 battery */

#define ESPCMT_MAX                                 18

#ifdef __cplusplus
extern "C" {
#endif
const char *ESPCMT_GetDevTypeAsString(uint16_t nDevType);

#ifdef __cplusplus
}
#endif

#endif // __ESSAT_MODULETYPES_H__
