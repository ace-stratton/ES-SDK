/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#include <cubeObc/cubeObc_errorDef.h>
#include <cubeObc/interfaces/cubeObc_canIfc.h>


void cubeObc_canIfc_rxFlush(void)
{
    return;
}


ErrorCode cubeObc_canIfc_rx(CanPacket *packet)
{
    (void)packet;

    return CUBEOBC_ERROR_TODO;
}


ErrorCode cubeObc_canIfc_tx(CONST CanPacket *packet)
{
    (void)packet;

    return CUBEOBC_ERROR_TODO;
}
