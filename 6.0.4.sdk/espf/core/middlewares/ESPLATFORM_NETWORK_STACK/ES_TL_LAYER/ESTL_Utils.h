#ifndef __ESTL_UTILS_H__
#define __ESTL_UTILS_H__

#include "ESTL_Drv.h"
#include "stdbool.h"

extern void     ESTL_UTILS_Init();
extern void     ESTL_UTILS_CRC32_Seed32(uint32_t nSeed);
extern uint32_t ESTL_UTILS_CRC32_Calc32(const void *pBuff, uint32_t nLen);
extern void     ESTL_UTILS_CopyMemory(uint8_t* pDst, uint8_t* pSrc, uint32_t nSize);
extern uint8_t* ESTL_UTILS_PointerAddition(const uint8_t* ptr, uint32_t n32);
extern bool     ESTL_UTILS_CompareBuffers(void* pFirst, void* pSecond, uint16_t nSize);

typedef uint32_t (*ESTL_UTIL_BinSearch_GetValCbk_t)(uint16_t nPos);
extern uint16_t ESTL_UTILS_BinSearch(int32_t nSearchProtoID, int16_t nLast, ESTL_UTIL_BinSearch_GetValCbk_t pfGetVal);
extern bool ESTL_UTILS_BinSearchEx(int32_t nSearchProtoID, int16_t nLast, ESTL_UTIL_BinSearch_GetValCbk_t pfGetVal, uint16_t * const p_result);

// workaround to spare old function call. it should be in the header, no extra stack usage, no extra flash.
static bool inline __attribute__((always_inline)) ESTL_UTILS_AreBuffsEqual(void* pFirst, void* pSecond, uint16_t nSize)
{
    return ESTL_UTILS_CompareBuffers(pFirst, pSecond, nSize);
}

#endif // __ESTL_UTILS_H__
