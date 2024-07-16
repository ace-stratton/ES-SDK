/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef __ESTL_LAYERS_LOCAL_CONF_H__
#define __ESTL_LAYERS_LOCAL_CONF_H__

/**
 * @addtogroup tp
 * @{
 *
 * @file     ESTL_LayersLocalConf.h
 * @brief    TP layer configuration definitions
 *
 * @}
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Local Transport Layers configuration file.
// This file has to be copied on every module firmware
// and should not be included anywhere, just copy it in project dir.
// Configuration should be made depending from module needs.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------------------
// Transport Layer Parameters

// Must be less than ESMAC_MAX_PAYLOAD_SIZE
#define ESTL_MIN_PAYLOAD_SIZE 100

// Timeouts in TL layer are calculated for this value, do not change it
// 1 ms/byte @ 9600 = 24K transfer for 25 sec.
#define ESTL_MAX_PAYLOAD_SIZE               (24 * 1024)

// This should be 25 as stated above, but it is too much
#define ESTL_MAX_COUNT_REPEAT_SYNC_FRAME    15

// In ms TODO: It's best to be calculated dynamically (depending on last send data over 9600 channel (1ms/byte))
#define ESTL_SYNC_FRAME_RESULT_TIMEOUT      2000

// Wait to send SYNC frame (if network/MAC is busy)
#define ESTL_SYNC_FRAME_SEND_TIMEOUT        2500

// Wait to send DATA frame (if network/MAC is busy)
#define ESTL_DATA_FRAME_SEND_TIMEOUT        2500

// Wait to send STATUS frame (if network/MAC is busy)
#define ESTL_STATUS_FRAME_SEND_TIMEOUT      2500

// Give up of TL packet when X transfers failed (with minimum allowed burst packets count/data size)
#define ESTL_MAX_LACK_OF_BURST_SUCCESS      5

// Payload buffer for UHF or other communication module that act as bridge between wireless and internal network
// You can adjust as you like, as minimum ESTL_MIN_PAYLOAD_SIZE
// Practical size is 5 - 10 K
#define ESTL_TL_COM_PAYLOAD_BRIDGE_BUFFER   (230)

#ifdef __ESTL_TL_CPP__

//------------------------------------------------------------------------------------------------------------

// Static layers configuration should be made here.
// To add new layer need to:
// 1. Include the header file of the module
// 2. Add it with ESTL_ADD_LAYER(layerName) macro
// between ESTL_BEGIN_LAYER_LIST() and ESTL_END_LAYER_LIST(itemsCount)

// ESTL_BEGIN_LAYER_LIST() has to be used without arguments

// ESTL_ADD_LAYER(layerName) has to be used with 1 argument - layer name
// usually this is the file name or the prefix of the module interface functions

// ESTL_END_LAYER_LIST(itemsCount) has to be used with one argument:
// number equal to layers added with ESTL_ADD_LAYER + 1.

#include "ES_CP/ESCP_ModDrv.h"
#include "ES_CP/ESCCP_ModDrv.h"
#include "ES_FW_UPD/ESFWUPD_ModDrv.h"

ESTL_BEGIN_LAYER_LIST()
ESTL_ADD_LAYER(ESCP_ModDrv)
ESTL_ADD_LAYER(ESCCP_ModDrv)
ESTL_ADD_LAYER(ESFWUPD_ModDrv)
ESTL_END_LAYER_LIST(4)

#endif // __ESTL_TL_CPP__

//------------------------------------------------------------------------------------------------------------
// If module is UHF and/or acting as router with 2 or more physical network interfaces,
// uncomment the following constant to be able to use bridge driver

//#define ESTL_MOD_USE_BRIDGE_DRV

// End of static configuration
//------------------------------------------------------------------------------------------------------------

#endif // __ESTL_LAYERS_LOCAL_CONF_H__
