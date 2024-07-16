/*
 *  Definition of protocol IDs over ES SAT MAC Layer
 */
#ifndef __ES_SAT_MAC_PROTOCOLS__
#define __ES_SAT_MAC_PROTOCOLS__

#define ES_SAT_MAC_PROTOCOL_ID_NULL					((uint8_t) 0x00)	/* Do not use it for anything */

//#define ES_SAT_MAC_PROTOCOL_ID_DISCOVERY			((uint8_t) 0x01)	Obsolete, use ES_SAT_MAC_PROTOCOL_ID_SERVICE
#define ES_SAT_MAC_PROTOCOL_ID_FIRMWARE_UPD			((uint8_t) 0x02)	/* this should be used from Ground station protocol  */
#define ES_SAT_MAC_PROTOCOL_ID_NETWORK_DEBUG		((uint8_t) 0x03)
#define ES_SAT_MAC_PROTOCOL_ID_DIAGNOSTICS			((uint8_t) 0x04)
#define ES_SAT_MAC_PROTOCOL_ID_UHF					((uint8_t) 0x05)
#define ES_SAT_MAC_PROTOCOL_ID_LED					((uint8_t) 0x06)
#define ES_SAT_MAC_PROTOCOL_ID_DEBUG		      	((uint8_t) 0x07)	/* each module unique/private protocol */
//#define ES_SAT_MAC_PROTOCOL_ID_EPSII_PDM			((uint8_t) 0x08)
//#define ES_SAT_MAC_PROTOCOL_ID_EPSII_BP			((uint8_t) 0x09)
#define ES_SAT_MAC_PROTOCOL_ID_EPSI                 ((uint8_t) 0x0A)
#define ES_SAT_MAC_PROTOCOL_ID_TRANSPORT_LAYER      ((uint8_t) 0x0B)
#define ES_SAT_MAC_PROTOCOL_ID_FP_LAYER             ((uint8_t) 0x0C)    /* FunctionProtocol layer inter-module messaging */
#define ES_SAT_MAC_PROTOCOL_ID_SERVICE				((uint8_t) 0x0D)    /* Modules basic/common protocol for discovery, configuration and maintenance */

#define ES_SAT_MAC_PROTOCOL_ID_MAC_TEST             ((uint8_t) 0xFF)    /* Commands to test MAC driver operation, keep this 0xFF required for GW tests */

#endif // __ES_SAT_MAC_PROTOCOLS__
