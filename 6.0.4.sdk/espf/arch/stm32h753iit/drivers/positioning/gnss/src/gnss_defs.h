/**
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef GNSS_DEFS_H_
#define GNSS_DEFS_H_

/**
 * @addtogroup Drivers
 * @{
 *
 * @defgroup gnss
 * @{
 *
 * @file gnss_defs.h
 *
 *
 * @}
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif


/** @brief flag used to signal for new data coming from the GNSS */
#define GNSS_DATA_FLAG                0x01

/** @brief flag used to signal for powering on the GNSS */
#define GNSS_START_FLAG               0x02

/** @brief flag used to signal for powering off the GNSS */
#define GNSS_STOP_FLAG                0x04

/** @brief GNSS default baudrate */
#define GNSS_DEFAULT_BAUDRATE         9600

/**
 * @brief GNSS desired baudrate
 *
 * @warning If this value is modified @ref GNSS_CMD_SERIALCONFIG crc must also be recalculated
 */
#define GNSS_DESIRED_BAUDRATE         460800

/** @brief */
#define GNSS_NO_RESPONSE_TIMEOUT_MS   30000

/** @brief */
#define GNSS_BOOT_TIMEOUT_MS          10000

/** @brief */
#define GNSS_TO_STR2(x)               #x

/** @brief */
#define GNSS_TO_STR1(x)               GNSS_TO_STR2(x)

/** @brief command to turn off RX status event log */
#define GNSS_CMD_UNLOG_RXSTATUSEVENTA "#UNLOGA,COM1,0,0,UNKNOWN,0,0.0,0,0,0;COM1,RXSTATUSEVENTA*c78f6618\r\n"

/** @brief command to configure UART baudrate */
#define GNSS_CMD_SERIALCONFIG         "#SERIALCONFIG,COM1,0,0,UNKNOWN,0,0.0,0,0,0;COM1," GNSS_TO_STR1(GNSS_DESIRED_BAUDRATE) "*10e3e2d9\r\n"

/** @brief command to configure BESXYZ log */
#define GNSS_CMD_LOG_BESTXYZA         "#LOGA,COM1,0,0,UNKNOWN,0,0.0,0,0,0;COM1,BESTXYZA,ONTIME,1.000000*501b5be4\r\n"

/** @brief abbreviated ASCII BESXYZ log response header */
#define GNSS_RESP_LOG_BESTXYZA_HDR    "#BESTXYZA"

/** @brief command to configure TIME log */
#define GNSS_CMD_LOG_TIMEA            "#LOGA,COM1,0,0,UNKNOWN,0,0.0,0,0,0;COM1,TIMEA,ONTIME,1.000000*87b62eba\r\n"

/** @brief abbreviated ASCII TIME log response header */
#define GNSS_RESP_LOG_TIMEA_HDR       "#TIMEA"

#define GNSS_STATIC_STRLEN(str)       (sizeof(str) - 1)


#ifdef __cplusplus
}
#endif

#endif /* GNSS_DEFS_H_ */
