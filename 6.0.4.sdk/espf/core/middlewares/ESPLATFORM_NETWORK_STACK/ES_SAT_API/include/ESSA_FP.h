/*
 * ESSA_FP.h
 *
 *  Created on: May 27, 2022
 *      Author: Ivan Petrov
 */

#ifndef _ESSA_FP_H_
#define _ESSA_FP_H_

#include "ESSA_Stack.h"
#include "../../ES_SAT_MAC/ES_SAT_MAC_Protocols.h"
#include "../../ES_SAT_MAC/ES_SAT_MAC.h"
#include "../../ES_SAT_MAC/ES_SAT_MAC_Context.h"
#include "../../ES_SAT_AIRMAC/ES_SAT_AIRMAC.h"

typedef ESSA_pStack_FunctionProtocolInfo_t (*ESSA_pfStack_FunctionProtocolInfoCbk)(void);
typedef bool (*ESSA_pfStack_FPDataHandler_Cbk_t)(ESSA_Stack_DataDispatchInfo_t *pDataInfo);

typedef struct _ESSA_Stack_FunctionProtocolInfo_t
{
    uint16_t                         u16ProtocolId;
    ESSA_pfStack_FPDataHandler_Cbk_t pfDataHandlerCbk;
} ESSA_Stack_FunctionProtocolInfo_t;

typedef struct
{
    const ESSA_Stack_FunctionProtocolInfo_t **ppFunctionProtocolCollection;
    uint16_t                            u16FunctionProtocolCollectionSize;
} ESSA_Stack_FP_Ctx_t;

extern const ESSA_Stack_ProtocolInfo_t FP_ProtocolServerInfo;

ESSA_eStack_codes_t ESSA_Stack_FP_Init(const ESSA_Stack_FP_Ctx_t * const pCfg);

#endif /* _ESSA_FP_H_ */
