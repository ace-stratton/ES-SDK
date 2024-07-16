/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ARM_FAULT_HANDLER_H
#define ARM_FAULT_HANDLER_H

#include <stdbool.h>
#include <stdint.h>

#define ARM_FAULT_REC_TYPE_EMPTY    ((uint32_t) 'E')       /**< Empty slot */
#define ARM_FAULT_REC_TYPE_APP      ((uint32_t) 'A')       /**< Application slot */
#define ARM_FAULT_REC_TYPE_BOOT     ((uint32_t) 'B')       /**< Bootloader slot */

/** @brief Definition of the basic ARM exception frame */
typedef struct
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;    /**< Link Register */
    uint32_t pc;    /**< Program Counter */
    uint32_t psr;   /**< Program Status Resgister */
} __attribute__((__packed__)) basic_x_frame_t;

/** @brief Definition of the extended ARM exception frame with FP extension */
typedef struct
{
    basic_x_frame_t basic_regs;  /**< Basic registers */
    uint32_t fp_ext_reg_s[16];   /**< Extended FP registers S0..S15 */
    uint32_t fpscr;              /**< Floating Point Status and Control Register */
} __attribute__((__packed__)) extended_x_frame_t;

/** @brief The type defines the common record data collected each exception frame regardless of its type
 *  (e.g. this contains environment and other data)
 * */
typedef struct
{
    uint32_t record_type;                            /**< ASCII symbol indicating whether this is an empty 'E', application 'A' or a bootloader 'B' record */
    uint8_t reserved[4];                             /**< reserved fields for future use - currently set to zero */
    uint32_t exception_rtc_ts;                       /**< RTC timestamp indicating when the exception occurred */
    uint32_t uptime;                                 /**< uptime in milliseconds since last reset */
} __attribute__((__packed__)) x_header_t;

/** @brief Format of the persisted exception frame in RAM */
typedef struct
{
    x_header_t hdr;                                  /**< Exception header */
    uint32_t cfsr;                                   /**< Configurable Fault Status Register */
    uint32_t hfsr;                                   /**< Hard Fault Status Register */
    uint32_t mmfar;                                  /**< MemManage Fault Address Register */
    uint32_t bfar;                                   /**< BusFault Address Register */
    uint32_t abfsr;                                  /**< Auxiliary Bus Fault Status Register */
    uint32_t sp;                                     /**< Stack pointer (MSP or PSP) when the exception occurred */
    uint32_t vtor;                                   /**< Vector table address offset (could be used to distinguish between separate apps in different linker sections) */
    uint32_t stack_frame_len;                        /**< number of actual bytes in the stack_frame field */
    extended_x_frame_t stack_frame;                  /**< exception stack frame data */
    uint32_t crc;                                    /**< CRC of all previous fields */
} __attribute__((__packed__)) persisted_ram_x_frame_t;

/** @brief Format of a generic user fault frame which doesn't need to capture HW context (must be the same size as persisted_ram_x_frame_t */
typedef struct
{
    x_header_t hdr;                                     /**< Exception header */
    uint8_t data[sizeof(persisted_ram_x_frame_t) - sizeof(x_header_t) - sizeof(uint32_t)];  /**< Generic frame data to store (this is fault-specific) */
    uint32_t crc;                                       /**< CRC16 of all previous fields */
} __attribute__((__packed__)) persisted_ram_generic_frame_t;

/** @brief Environment data which is set externally for use when an exception occurs */
typedef struct
{
    uint32_t rtc_time;      /**< Unix timestamp maintained by an RTC */
    uint32_t uptime;        /**< Uptime in milliseconds since last reset */
} __attribute__((__packed__)) arm_fault_handler_env_t;

/** @brief Called to enable all relevant ARM exception fault handlers */
void arm_fault_handler_init(void);

/** @brief Verifies whether the temporary RAM section contains valid exception data and copies the
 *         stored exception to a user-provided buffer after which the temporary RAM section gets invalidated.
 *  @param[out] p_buf a pointer to the buffer which will store the last stored exception in RAM
 *
 *  @warning The function can be used only once after the system is reset. The data is consumed after reading
 *  and will not remain in memory.
 *
 *  @retval true: there is a valid exception in RAM and the copy operation succeeded
 *  @retval false: the user provided buffer is not valid (NULL) or there are no valid exception stored in
 *                 RAM since last reset
 */
bool arm_fault_handler_read_last(persisted_ram_x_frame_t * const p_buf);

/** @brief Validates a frame to contain a valid CRC
 *  @param[in] p_frame frame data to validate
 *  @retval true: the frame CRC validation succeeded
 *  @retval false: the frame CRC validation failed
 */
bool arm_fault_handler_is_frame_valid(persisted_ram_x_frame_t * const p_frame);

/** @brief The call is used to update the environment data used by the fault handler
 *         implementation when a fault occurs.
 *  @param[in] p_env_data environment data to copy in the fault handler RAM when a fault
 *             occurs
 */
void arm_fault_handler_set_env(arm_fault_handler_env_t * const p_env_data);

/** @brief The function stops execution in case a debugger is connected to the CPU when
 *  it is called.
 */
void arm_fault_handler_bkpt_if_debug(void);

/** @brief Used to signal a generic SW failure, e.g. stack overflow, etc.
 *  @param[in] p_user_data Failure-specific data to store
 *  @param[in] user_data_sz size in bytes of the provided user data
 */
void arm_fault_handler_generic(const uint8_t * const p_user_data, const uint32_t user_data_sz);

/** @brief BusFault system handler (mapped by the linker) */
void BusFault_Handler(void);

/** @brief UsageFault system handler (mapped by the linker) */
void UsageFault_Handler(void);

/** @brief MemManage fault system handler (mapped by the linker) */
void MemManage_Handler(void);

/** @brief HardFault system handler (mapped by the linker) */
void HardFault_Handler(void);

#endif /* ARM_FAULT_HANDLER_H */
