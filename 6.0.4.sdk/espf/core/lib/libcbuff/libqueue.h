/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#if !defined(__QUEUE_H__)
#define __QUEUE_H__

#if defined(__cplusplus)
extern "C" {
#endif /* #if defined(__cplusplus) */

/* -------------------------------------------------------------------------- */
/* Included files to resolve specific definitions in this file                */
/* -------------------------------------------------------------------------- */
#include "deftypes.h"

/* -------------------------------------------------------------------------- */
/* Constant data                                                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Exported types                                                             */
/* -------------------------------------------------------------------------- */

/* Queue structure */
typedef struct _queue_tag_ {
    U8               *data;
    U16              size;
    U16              tail;
    U16              head;
} tQueue;

/* Queue size type */
typedef U16 tQueueSize;

/* Queue data type */
typedef U8 tQueueData;

/* Queue data pointer type */
typedef tQueueData* tQueuePData;

/* -------------------------------------------------------------------------- */
/* Exported data                                                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Constant exported data                                                     */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Exported Macros                                                            */
/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/* ========================    EXPORTED FUNCTIONS    ======================== */
/* ========================================================================== */

/* ========================================================================== */
/* DESCRIPTION                      : queue_flush                             */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Flush queue contents                    */
/* ========================================================================== */
void queue_flush(tQueue *q);

/* ========================================================================== */
/* DESCRIPTION                      : queue_quick_flush                       */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Flush queue without contents wiping     */
/* ========================================================================== */
void queue_quick_flush(tQueue *q);

/* ========================================================================== */
/* DESCRIPTION                      : queue_init                              */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/*                                    tQueuePData pBuf  - buffer pointer      */
/*                                    tQueueSize qSize - buffer size          */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Initialise the queue contents           */
/* ========================================================================== */
void queue_init(tQueue *q, tQueuePData pBuf, tQueueSize qSize);

/* ========================================================================== */
/* DESCRIPTION                      : queue_data_len                          */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : Size of the data in the queue           */
/* DESIGN INFORMATION               : Get data size in the queue              */
/* ========================================================================== */
tQueueSize queue_data_len(tQueue *q);

/* ========================================================================== */
/* DESCRIPTION                      : queue_data_free                         */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : Free space in the queue                 */
/* DESIGN INFORMATION               : Get free space in the queue             */
/* ========================================================================== */
tQueueSize queue_data_free(tQueue *q);

/* ========================================================================== */
/* DESCRIPTION                      : queue_put                               */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/*                                    tQueueData qData - data to store        */
/* RETURN VALUE                     : void (None)                             */
/* DESIGN INFORMATION               : Puts data in the queue                  */
/* ========================================================================== */
void queue_put(tQueue *q, const tQueueData qData);

/* ========================================================================== */
/* DESCRIPTION                      : queue_is_empty                          */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : BOOL - true if there is no data         */
/* DESIGN INFORMATION               : Checks if the queue is empty            */
/* ========================================================================== */
BOOL queue_is_empty(tQueue *q);

/* ========================================================================== */
/* DESCRIPTION                      : queue_is_full                           */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : BOOL - true if queue is full            */
/* DESIGN INFORMATION               : Checks if the queue is full             */
/* ========================================================================== */
BOOL queue_is_full(tQueue *q);

/* ========================================================================== */
/* DESCRIPTION                      : queue_get                               */
/* PARAMETERS (Type,Name,Min,Max)   : tQueue *q - queue context               */
/* RETURN VALUE                     : tQueueData - Data from the queue,       */
/*                                    0xFF if empty                           */
/* DESIGN INFORMATION               : Returns data byte from the queue        */
/* ========================================================================== */
int queue_get(tQueue *q);

#if defined(__cplusplus)
}
#endif /* #if defined(__cplusplus) */

#endif /* #if !defined(__QUEUE_H__) */

/* ========================================================================== */
