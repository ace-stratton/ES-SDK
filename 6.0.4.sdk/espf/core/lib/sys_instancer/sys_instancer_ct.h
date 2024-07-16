/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef ESPF_LIB_SYS_INSTANCER_SYS_INSTANCER_CT_H_
#define ESPF_LIB_SYS_INSTANCER_SYS_INSTANCER_CT_H_
/**
 * @addtogroup sys_instancer
 * @{
 *
 * @file    sys_instancer_ct.h
 * @brief   sys instancer c types
 *
 * @}
 *
 */

/** Results from the initialization commands */
typedef enum {
    STATUS_FAILED,          /**> Something did not initialzed as expected */
    STATUS_OK,              /**> Everything initialized properly */
    STATUS_NOT_SUPPORTED,   /**> The module doesn't have this level of initialization */
    MAX_STATUS
} mod_op_status_id_t;

/** Different levels of initialization */
typedef enum {
    INIT_MEM,       /**> Initialize dynamic memory dependencies */
    INIT_HW,        /**> Initialize hardware peripherals */
    INIT_OS,        /**> Initialize OS dependencies */
    MAX_INIT_LEVEL
} sys_init_level_id_t;

#endif /* ESPF_LIB_SYS_INSTANCER_SYS_INSTANCER_CT_H_ */
