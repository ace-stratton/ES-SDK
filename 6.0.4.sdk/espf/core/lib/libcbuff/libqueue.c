/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/* -------------------------------------------------------------------------- */
/* Included files to resolve specific definitions in this file                */
/* -------------------------------------------------------------------------- */
#include "libqueue.h"
#include "assertions.h"

/* -------------------------------------------------------------------------- */
/* Internal function prototypes                                               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Local constants                                                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Local macros                                                               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Local types                                                                */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Local data                                                                 */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Constant local data                                                        */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Exported data                                                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Constant exported data                                                     */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Local function prototypes                                                  */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* =========================    LOCAL FUNCTIONS    ========================== */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/* ========================    EXPORTED FUNCTIONS    ======================== */
/* ========================================================================== */

/* ========================================================================== */
/* DESCRIPTION                      : queue_flush                             */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Flush queue contents                    */
/* ========================================================================== */
void queue_flush(tQueue *q) {
    int                 index;

    for (index = 0; index < q->size; index++) {
        q->data[index] = 0;
    }
    q->tail = q->head = 0;
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_quick_flush                       */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Flush queue without contents wiping     */
/* ========================================================================== */
void queue_quick_flush(tQueue *q) {
    q->tail = q->head = 0;
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_init                              */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/*                                    tQueuePData pBuf  - buffer pointer      */
/*                                    tQueueSize qSize - buffer size          */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Initialise the queue contents           */
/* ========================================================================== */
void queue_init(tQueue *q, tQueuePData pBuf, tQueueSize qSize) {
    if ((qSize < 1) || (pBuf == NULL)) {
        q->size = 0;
        q->data = NULL;
    } else {
        int                 cnt = (sizeof(tQueueSize) * 8) - 1;
        int                 mask = (1 << ((sizeof(tQueueSize) * 8) - 1));
        int                 size = qSize;

        /* Align buffer size to nearest power of two */
        while (0 == (size & mask)) {
            size <<= 1;
            cnt--;
        }
        q->size = 1 << cnt;;
        q->data = pBuf;
        queue_flush(q);
    }
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_data_len                          */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : Size of the data in the queue           */
/* DESIGN INFORMATION               : Get data size in the queue              */
/* ========================================================================== */
tQueueSize queue_data_len(tQueue *q) {
    tQueueSize          qLen = 0;

    CRIT_ASSERT(q->data != NULL);
    CRIT_ASSERT(q->size != 0);
    if (q->head != q->tail) {
        if (q->tail > q->head)  {
            qLen = q->tail - q->head;
        } else  {
            qLen = q->tail + q->size - q->head;
        }
    } /* else No data in the queue */

    return (qLen);
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_data_free                         */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : Free space in the queue                 */
/* DESIGN INFORMATION               : Get free space in the queue             */
/* ========================================================================== */
tQueueSize queue_data_free(tQueue *q) {
    return (q->size - 1 - queue_data_len(q));
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_put                               */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/*                                    tQueueData qData - data to store        */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Puts data in the queue                  */
/* ========================================================================== */
void queue_put(tQueue *q, const tQueueData qData) {
	CRIT_ASSERT(q->data != NULL);
    CRIT_ASSERT(q->size != 0);
    q->data[q->tail++] = qData;
    q->tail &= (q->size - 1);
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_is_empty                          */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : BOOL - true if there is no data         */
/* DESIGN INFORMATION               : Checks if the queue is empty            */
/* ========================================================================== */
BOOL queue_is_empty(tQueue *q) {
    return (queue_data_len(q) == 0 ? cTrue : cFalse);
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_is_full                           */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : BOOL - true if queue is full            */
/* DESIGN INFORMATION               : Checks if the queue is full             */
/* ========================================================================== */
BOOL queue_is_full(tQueue *q) {
    return (queue_data_free(q) == 0);
}

/* ========================================================================== */
/* DESCRIPTION                      : queue_get                               */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : tQueueData - Data from the queue,       */
/*                                    0xFF if empty                           */
/* DESIGN INFORMATION               : Returns data byte from the queue        */
/* ========================================================================== */
int queue_get(tQueue *q) {
    tQueueData          qData = 0xFF;

    if (!queue_is_empty(q)) {
        qData = q->data[q->head++];
        q->head &= (q->size - 1);
    } /* else No data in the queue */
    else
    	return -1;

    return ((int)qData);
}

/* ========================================================================== */
