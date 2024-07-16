/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libCFB
 * @{
 *
 * @file CircularFlatBuffer.c
 * @brief CFB implementation
 *
 * @}
 */

#include "CircularFlatBuffer.h"
#include "assertions.h"

static inline uint32_t fs_GetFreeBytes(CircularBufCtx_t* const ptBufContext)
{
	CRIT_ASSERT(ptBufContext != NULL);

	if (ptBufContext->bBufferFull)
		return 0U;

	if (ptBufContext->u32TailPos > ptBufContext->u32HeadPos)
		return ptBufContext->u32BufSize - (ptBufContext->u32TailPos - ptBufContext->u32HeadPos);
	else
		if (ptBufContext->u32TailPos < ptBufContext->u32HeadPos)
			return ptBufContext->u32HeadPos - ptBufContext->u32TailPos;
		else	// buffer is empty
			return ptBufContext->u32BufSize;
}

static inline uint32_t fs_GetUsedBytes(CircularBufCtx_t* const ptBufContext)
{
	CRIT_ASSERT(ptBufContext != NULL);

	return (ptBufContext->u32BufSize - fs_GetFreeBytes(ptBufContext));
}

eCircBufOpResult CircularBuf_Init(CircularBufCtx_t* const ptBufContext,
	uint8_t* const pu8UserBuf,
	const uint32_t u32UserBufSize,
	const uint32_t u32CommitBufSize,
	uint8_t* const pu8AuxBuf,
	const uint32_t u32AuxBufSize)
{
    eCircBufOpResult res = ECIRCBUFOPRESULT_INVALID_ARGS;

	if ((ptBufContext != (CircularBufCtx_t*)NULL) &&
	    (pu8UserBuf != NULL) &&
	    (u32CommitBufSize <= u32UserBufSize))
    {
			ptBufContext->pu8Buf = pu8UserBuf;
			ptBufContext->u32BufSize = u32UserBufSize;
			ptBufContext->u32CommitBufSize = u32CommitBufSize;

			ptBufContext->u32HeadPos = 0U;
			ptBufContext->u32TailPos = 0U;
			ptBufContext->u32LastBufPtrSize = 0U;
			ptBufContext->bBufferFull = false;
			ptBufContext->u32MaxByteCountReached = 0U;

			if (pu8AuxBuf != NULL)
			{
				ptBufContext->pu8AuxBuf = pu8AuxBuf;
				ptBufContext->u32AuxBufSize = u32AuxBufSize;
			}
			else
			{
				ptBufContext->pu8AuxBuf = NULL;
				ptBufContext->u32AuxBufSize = 0U;
			}

			ptBufContext->bAuxBufferInUse = false;

			res = ECIRCBUFOPRESULT_OK;
	}

    return res;
}

eCircBufOpResult CircularBuf_Append(CircularBufCtx_t* const ptBufContext,
	uint8_t* const pu8Data,
	const uint32_t u32DataSize)
{
	eCircBufOpResult res = ECIRCBUFOPRESULT_INVALID_ARGS;
	uint32_t u32RemainingBytesUntilEnd;
	uint32_t u32UsedBytes;

	if ((ptBufContext != NULL) &&
		(pu8Data != NULL) &&
		(u32DataSize > 0U))
	{
		if (u32DataSize <= fs_GetFreeBytes(ptBufContext))
		{
			if ((ptBufContext->u32TailPos + u32DataSize) <= ptBufContext->u32BufSize)
			{
				(void)memcpy((void*)&ptBufContext->pu8Buf[ptBufContext->u32TailPos],
					(void*)pu8Data,
					(size_t)u32DataSize);
			}
			// buffer will overflow, so we need to copy in two chunks: 
			// one until end of buffer and one starting from beginning
			else
			{
				u32RemainingBytesUntilEnd = ptBufContext->u32BufSize - ptBufContext->u32TailPos;

				(void)memcpy((void*)&ptBufContext->pu8Buf[ptBufContext->u32TailPos],
					(void*)pu8Data,
					(size_t)u32RemainingBytesUntilEnd);

				if ((u32DataSize - u32RemainingBytesUntilEnd) > 0U)
					(void)memcpy((void*)&ptBufContext->pu8Buf[0],
						(void*) &pu8Data[u32RemainingBytesUntilEnd],
						(size_t)(u32DataSize - u32RemainingBytesUntilEnd));
			}

			ptBufContext->u32TailPos = (ptBufContext->u32TailPos + u32DataSize) % ptBufContext->u32BufSize;

			// if tail reaches the head position after append operation, then the buffer became completely full
			if (ptBufContext->u32TailPos == ptBufContext->u32HeadPos)
				ptBufContext->bBufferFull = true;

			// keep maximum used bytes statistics
			u32UsedBytes = fs_GetUsedBytes(ptBufContext);
			if (ptBufContext->u32MaxByteCountReached < u32UsedBytes)
				ptBufContext->u32MaxByteCountReached = u32UsedBytes;

			res = ECIRCBUFOPRESULT_OK;
		}
		else
			res = ECIRCBUFOPRESULT_BUFFER_FULL;
	}

	return res;
}

uint8_t* CircularBuf_GetNextBufferPtr(CircularBufCtx_t* const ptBufContext, const uint32_t u32BytesRequested, uint32_t* const pu32BytesAvailable)
{
	uint8_t* pRetBuf = NULL;
	uint32_t u32RemainingBytesUntilEnd = 0U;
	uint32_t u32DataBytesAvailable = 0U;

	// Aux buffer or any previously reserved buffer has to be free before requesting another buffer, otherwise the bytes could be processed in a wrong sequence, 
	// therefore further reading of the circular buffer is not allowed until last reserved buffer is released via CircularBuf_ReleaseLastBufferPtr()
	if ((ptBufContext != NULL) &&
		(!ptBufContext->bAuxBufferInUse) &&
		(ptBufContext->u32LastBufPtrSize == 0U))
	{
		// calculate actual data bytes in the buffer which are pending to be processed
		u32DataBytesAvailable = fs_GetUsedBytes(ptBufContext);

		// check if we already accumulated enough bytes to fulfill the buffer request
		if (u32DataBytesAvailable >= u32BytesRequested)
		{
			if (ptBufContext->u32TailPos == ptBufContext->u32HeadPos)
			{
				if (!ptBufContext->bBufferFull)
					u32RemainingBytesUntilEnd = ptBufContext->u32BufSize;
			}
			else
				if (ptBufContext->u32TailPos > ptBufContext->u32HeadPos)
					u32RemainingBytesUntilEnd = ptBufContext->u32TailPos - ptBufContext->u32HeadPos;
				else
					// tail position is before head position, hence the buffer overflows to beginning
					u32RemainingBytesUntilEnd = ptBufContext->u32BufSize - ptBufContext->u32HeadPos;

			// can we return a contiguous buffer or the data rolls over to the beginning of the buffer?
			if (u32RemainingBytesUntilEnd >= u32BytesRequested)
			{
				ptBufContext->u32LastBufPtrSize = u32BytesRequested;
				pRetBuf = &ptBufContext->pu8Buf[ptBufContext->u32HeadPos];
			}
			else
			{
				// data rolls over to the beginning of the buffer, check if we can use the Aux buffer to provide a
				// contiguous chunk of memory
				if (ptBufContext->pu8AuxBuf != NULL)
				{
					ptBufContext->bAuxBufferInUse = true;

					// Aux buffer can take the data, hence we need to copy and return a pointer to the Aux buffer
					if (ptBufContext->u32AuxBufSize >= u32BytesRequested)
					{
						// copy first part of the buffer
						(void)memcpy((void*)ptBufContext->pu8AuxBuf,
							(void*)&ptBufContext->pu8Buf[ptBufContext->u32HeadPos],
							(size_t)u32RemainingBytesUntilEnd);

						// ...and remaining bytes
						(void)memcpy((void*)&ptBufContext->pu8AuxBuf[u32RemainingBytesUntilEnd],
							(void*)&ptBufContext->pu8Buf[0],
							(size_t)(u32BytesRequested - u32RemainingBytesUntilEnd));

						// now data is in the Aux buffer, so we can move the head in the circular buffer forward to
						// make room for more data
						ptBufContext->u32HeadPos = (ptBufContext->u32HeadPos + u32BytesRequested) % ptBufContext->u32BufSize;

						// finally, return a pointer to the Aux buffer
						pRetBuf = ptBufContext->pu8AuxBuf;
					}
				}
			}

			u32DataBytesAvailable = u32BytesRequested;
		}

		if (pu32BytesAvailable != NULL)
			*pu32BytesAvailable = u32DataBytesAvailable;
	}

	return pRetBuf;
}

void CircularBuf_ReleaseLastBufferPtr(CircularBufCtx_t* const ptBufContext, const bool bDiscardLastBufferData)
{
	if (ptBufContext != NULL)
	{
		// if Aux buffer was last used, there is nothing to discard in the circular buffer as that was already done in
		// CircularBuf_GetNextBufferPtr() operation
		if (ptBufContext->bAuxBufferInUse)
			ptBufContext->bAuxBufferInUse = false;
		else
		{
			// discard data in the circular buffer because it is not anymore needed by the user
			if (ptBufContext->u32LastBufPtrSize > 0U)
			{
			    // if bDiscardLastBufferData flag is set, then the user has consumed the data, otherwise something may have
			    // happened and the user would like to make another try with the same data
			    if (bDiscardLastBufferData)
			    {
			        ptBufContext->u32HeadPos = (ptBufContext->u32HeadPos + ptBufContext->u32LastBufPtrSize) % ptBufContext->u32BufSize;
                    ptBufContext->bBufferFull = false;
			    }

				ptBufContext->u32LastBufPtrSize = 0;
			}
		}
	}
}

uint8_t* CircularBuf_ReadNextCommitBuffer(CircularBufCtx_t* const ptBufContext, uint32_t* const pu32BufSize)
{
	return CircularBuf_GetNextBufferPtr(ptBufContext,
		(ptBufContext != NULL) ?
		(ptBufContext->u32CommitBufSize) :
		(0U),
		pu32BufSize);
}

uint32_t CircularBuf_GetMaxByteCountReached(CircularBufCtx_t* const ptBufContext)
{
	return (ptBufContext != NULL) ? (ptBufContext->u32MaxByteCountReached) : (0U);
}
