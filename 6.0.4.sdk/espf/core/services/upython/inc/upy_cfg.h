/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup Services
 * @{
 *
 * @defgroup upython
 * @{
 *
 * @file upy_cfg.c
 * @brief upython configuration file
 *
 * @}
 * @}
 */

#ifndef UPYTHON_CFG_H_
#define UPYTHON_CFG_H_

#include "mpconfigport.h"

#define UPY_TASK_PERIOD_MS (5000U)


#define UPY_STACK_SIZE              (5 * 1024)

#define UPY_SCRIPT_QUEUE_LEN (10)

// Micropython rolling filename configuration
/**
 * \def UPY_LOG_MAX_SIZE
 * \brief maximum size of python output files in bytes
 *
 */
#define UPY_LOG_MAX_SIZE ((uint32_t)(20 * 1024))

/** @brief Defines the position of the marker character in the file name
  template
  * @verbatim
  "0:/exeh_btl.d__"
                ^
                |
  @endverbatim
  */
#define UPY_LOG_MARKER_POS ((uint8_t)9)

/** @brief A file name ending with this character is the currently active file
 */
#define UPY_LOG_ACTIVE_MARKER 'o'
/** @brief File names ending with this character indicate older reports */
#define UPY_LOG_INACTIVE_MARKER 'x'

/** @brief Maximum number of preserved files before starting to erase old
 * content */
#define UPY_LOG_SLOTS ((uint8_t)10)

/** @brief Defines the position of the index character in the file name template
  * @verbatim
  "0:/exeh_btl.d__"
               ^
               |
  @endverbatim
  */
#define UPY_LOG_INDEX_POS ((uint8_t)10)

/**
 * \def UPY_LOG_TEMPLATE
 * \brief name used for template of the micropython rolling file name
 *
 */
#define UPY_LOG_TEMPLATE "upy_log.d__"

#endif /* UPYTHON_CFG_H_ */

/***end of file***/
