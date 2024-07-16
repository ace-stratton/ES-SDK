/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPS_DRV_CONFIG_H
#define ESPS_DRV_CONFIG_H

/**
 * @addtogroup espsi_drv
 * @{
 *
 * @file     esps_drv_config.h
 * @brief    Public interface for the configuration of the ESPS I MAC Driver
 *
 * @}
 */

#include "esps_drv_def.h"
#include "esps_drv_stm32.h"

#include "esps_drv_esps_stack.h"

#include "esps_drv_ct.h"

/**
 * Return MAC Interface enum type
 * @param netIf: network interface as defined in the ESSA Stack
 *
 * @return enumerator value of the driver interface
 */
eMACInterface_t MacCfg_eGetMacDrvIf (ESSASNetInterface netIf);

/**
 * Return ESSA Stack ID
 * @param macIf: enumerator value of the driver interface
 *
 * @return network interface as defined in the ESSA Stack
 */
uint8_t MacCfg_u8GetStackIfId (eMACInterface_t macIf);

/**
 * Return MAC Interface struct information
 * @param macId: enumerator value of the driver interface
 *
 * @return state information of the driver interface
 */
sMACInterfaceState_t *MacCfg_sGetMacInterfaceById (const eMACInterface_t macId);

/**
 * Callback after a received frame ready to dispatch
 * @param eMacIf: enumerator value of the driver interface
 */
void MacCfg_vDispatcherNotifCallback(const eMACInterface_t eMacIf);

/**
 * Called upon processed received message
 * @param fp_eMACId: enumerator value of the driver interface
 * @param fp_psMsg: message that triggered the notification
 */
void MacCfg_vHandleFrameNotifications (eMACInterface_t fp_eMACId, ESSATMAC_Message * fp_psMsg);

/**
 * Get and Set Termination Enable bit for the UART interface.
 * @param eMacIf: enumerator value of the driver interface
 * @param bReadPersistentSetting: read from the persistent settings
 */
bool MacCfg_bGetBusTerminationState (const eMACInterface_t eMacIf, const bool bReadPersistentSetting);

/**
 * Get and Set Termination Enable bit for the UART interface.
 * @param eMacIf: enumerator value of the driver interface
 * @param bNewState: new value to be set
 * @param bPersistSetting: read from the persistent settings
 */
void MacCfg_vSetBusTerminationState (const eMACInterface_t eMacIf, const bool bNewState, const bool bPersistSetting);

/**
 * Get the MAC Address for the interface from the NVM storage
 * @param eMacIf: enumerator value of the driver interface
 *
 * @return MAC address of the interface
 */
uint8_t MacCfg_u8GetMacAddress (const eMACInterface_t eMacIf);

/**
 * Set the MAC Address for the interface from the NVM storage
 * @param eMacIf: enumerator value of the driver interface, <b>unused</b>
 *      (currently, all interfaces share the same address)
 * @param u8MacAddr: new MAC address
 *
 * @retval true: the new address is set successfully
 * @retval false: the new address is not set
 */
bool MacCfg_bSetMacAddress(const eMACInterface_t eMacIf, const uint8_t u8MacAddr);

/**
 * Set the address of the MAC Interface
 * @param eMacIf: enumerator value of the driver interface
 * @param u8MacAddr: new MAC address
 */
void MacCfg_vApplyMacAddrConfig (const eMACInterface_t eMacIf, const uint8_t u8MacAddr);

/**
 * Get the statistics events of the driver for the given interface
 * @see eMACStatId_t
 *
 * @param fp_eMACId: enumerator value of the driver interface
 * @param pu8UserBuf: output buffer to be filled with the statistics
 * @param u32UserBufSize: size of pu8UserBuf
 * @param pu32ResponseSize: size of the copied information
 * @param pu32EventsCount: number of events
 */

void MAC__Stats_getEventsBuffer(eMACInterface_t fp_eMACId,
                                uint8_t * const pu8UserBuf,
                                uint32_t u32UserBufSize,
                                uint32_t * const pu32ResponseSize,
                                uint32_t * const pu32EventsCount);

/**
 * Get the statistics events of the driver for the given interface
 * @see ESSASP_CB_GetDeviceInfo
 * @return MAC address of the primary interface (all interfaces share the same address)
 */
uint8_t ESSATMAC_GetModuleAddr();

#endif /* ESPS_DRV_CONFIG_H */
