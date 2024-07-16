/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GLOBALCONFIG_H_
#define GLOBALCONFIG_H_

// Communication types to external devices
#define EXT_DEV_COMM_I2C        0
#define EXT_DEV_COMM_RS485_MAC  1

#define ESSASP_SUPPORT_DISCOVERY_CLIENT

#if defined(UHF_II_SUPPORT_ENABLED)
	#define UHF_II_HW_INTERFACE_ID      EXT_DEV_COMM_RS485_MAC
#endif

#endif  // #ifndef GLOBALCONFIG_H_
