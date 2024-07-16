/*!
********************************************************************************************
* @file FP_ProtocolServerCommon.h
* @brief Protocol server common functions header (for use by multiple servers)
********************************************************************************************
* @version           
*
* @copyright         (C) Copyright EnduroSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
*-------------------------------------------------------------------------------------------
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.9
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as
* all changes will be overwritten !!!
********************************************************************************************
*/

#ifndef __FP_PROTOCOLSERVERCOMMON_H__
#define __FP_PROTOCOLSERVERCOMMON_H__

#include <stddef.h>
#include "FP_common/FP_BaseProtocolTypes.h"
#include "FP_common/FP_Helpers.h"

/**********************************************************************
 *
 *  Public methods
 *
 **********************************************************************/
ESSATMAC_ErrCodes ProtocolSendErrorResp(ESSA_Stack_DataDispatchInfo_t *fp_DataInfo, uint8_t errCode);

#endif  // #ifndef __FP_PROTOCOLSERVERCOMMON_H__
