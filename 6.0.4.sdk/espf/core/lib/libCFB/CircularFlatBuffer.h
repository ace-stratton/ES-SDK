/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef CIRCULAR_FLAT_BUFFER_H
#define CIRCULAR_FLAT_BUFFER_H

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup libCFB Circular Flat Buffer
 * @{
 *
 * Library to use a circular flat buffer
 *
 * @file CircularFlatBuffer.h
 * @brief CFB definitions
 *
 * @}
 * @}
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct
{
	// main memory region used as a circular buffer
	uint8_t* pu8Buf;
	uint32_t u32BufSize;
	// position of the last read
	uint32_t u32HeadPos;
	// position of the first free slot to put new data to
	uint32_t u32TailPos;
	// size in bytes of the buffers the user wants to read as a continuous region in memory
	uint32_t u32CommitBufSize;
	// Auxilliary buffer to use in case the data rolls over to the beginning of pu8Buf and a pointer to a continuous region of
	// u32CommitBufSize bytes cannot be provided directly;
	uint8_t* pu8AuxBuf;
	uint32_t u32AuxBufSize;
	// the size in bytes of the last region reserved via CircularBuf_GetNextBufferPtr() operation
	uint32_t u32LastBufPtrSize;
	// maximum number of bytes that were present in the buffer for the time of use, i.e. buffer max utilization metrics
	uint32_t u32MaxByteCountReached;
	// indicates that the Aux buffer is in use by the last CircularBuf_GetNextBufferPtr() operation
	bool	 bAuxBufferInUse;
	// the flag indicates when the buffer is actually full because the condition for full and empty is the same -> u32HeadPos = u32TailPos
	bool	 bBufferFull;
} CircularBufCtx_t;

typedef enum
{
	ECIRCBUFOPRESULT_OK,
	ECIRCBUFOPRESULT_INVALID_ARGS,
	ECIRCBUFOPRESULT_ERROR,
	ECIRCBUFOPRESULT_BUFFER_FULL,
} eCircBufOpResult;

eCircBufOpResult CircularBuf_Init(CircularBufCtx_t* const ptBufContext,
	uint8_t* const pu8UserBuf,
	const uint32_t u32UserBufSize,
	const uint32_t u32CommitBufSize,
	uint8_t* const pu8AuxBuf,
	const uint32_t u32AuxBufSize);

eCircBufOpResult CircularBuf_Append(CircularBufCtx_t* const ptBufContext,
	uint8_t* const pu8Data,
	const uint32_t u32DataSize);

uint8_t* CircularBuf_GetNextBufferPtr(CircularBufCtx_t* const ptBufContext, const uint32_t u32BytesRequested, uint32_t* const pu32BytesAvailable);

void CircularBuf_ReleaseLastBufferPtr(CircularBufCtx_t* const ptBufContext, const bool bDiscardLastBufferData);

uint8_t* CircularBuf_ReadNextCommitBuffer(CircularBufCtx_t* const ptBufContext, uint32_t* const pu32BufSize);

uint32_t CircularBuf_GetMaxByteCountReached(CircularBufCtx_t* const ptBufContext);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	// CIRCULAR_FLAT_BUFFER_H
