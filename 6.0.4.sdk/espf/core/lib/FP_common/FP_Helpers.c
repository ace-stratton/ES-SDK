/*!
********************************************************************************************
* @file FP_Helpers.c
* @brief Protocol helpers implementation
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
* GENERATOR: org.endurosat.generators.macchiato.binders.Gen_C v2.4
*-------------------------------------------------------------------------------------------
* !!! Please note that this code is fully GENERATED and shall not be manually modified as 
* all changes will be overwritten !!!
********************************************************************************************
*/

#include "FP_Helpers.h"

static SeqId_t msgId = 0U;

SeqId_t FP_Helpers_GenMsgId(void)
{
    return msgId++;
}

