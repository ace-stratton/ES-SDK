/*
 * Copyright (c) 2020-2023 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#include <string.h>
#include "arm_fault_handler.h"
#include "stm32h7xx.h"
#include "cmsis_compiler.h"
#include "core_cm7.h"
#include "es_crc32.h"
#include "assert.h"
#include "arm_fault_handler_cfg.h"

extern void Error_Handler(void);

/** @brief It is important that this is a pure-assembly macro because we need full control
 *  over what gets executed first in the ARM CPU exception handler function.
 *  Calling a regular C function will modify the exception stack frame and register capture will be compromised!
 *
 *  The code below does the following:
 *  - checks the active stack prior to the exception occurrence which is encoded as the value
 *    of bit 2 in the EXC_RETURN value pushed to the LR on exception entry.
 *    If the bit is 1: PSP was the active stack, otherwise - MSP was the active stack.
 *  - The active stack address is pushed to the R0 register
 *  - The capture_registers() function is called to process the register values pushed by the CPU on the stack.
 */
#define HANDLE_FAULT()                                                      \
    __asm volatile                                                          \
       (                                                                    \
           " tst lr, #4                                                \n"  \
           " ite eq                                                    \n"  \
           " mrseq r0, msp                                             \n"  \
           " mrsne r0, psp                                             \n"  \
           " b capture_registers \n" \
       );

/** @brief Temporary RAM storage where the exception information will be kept */
static __attribute__((section(".fault_mem"), aligned(4))) persisted_ram_x_frame_t temp_fault_memory_dump;

/** @brief Environment data filled-in externally and stored when a HW exception takes place in
 *  order to avoid execution of complicated operations in the @ref capture_registers function
 */
static arm_fault_handler_env_t env_data =
{
    .rtc_time = 0U,
    .uptime = 0U
};

/** @brief The function copies the CPU registers placed on the stack into the temporary no-init RAM area
 *         for retrieval after reset
 *  @param[in] p_fault_stack_frame_start pointer to the active exception stack frame
 *
 *  @warning Make sure to avoid using local variables in this function because that will modify the
 *           stack frame accessed via the p_fault_stack_frame_start pointer and may result in
 *           different register values captured.
 */
static void __attribute__((used)) capture_registers(uint32_t * const p_fault_stack_frame_start)
{
    // store stack pointer when the exception occurred
    temp_fault_memory_dump.sp = (uint32_t) p_fault_stack_frame_start;

    // for the exact register layout on the stack, refer to ARMv7-M Architecture Reference Manual
    // (https://developer.arm.com/documentation/ddi0403/ee/)
    // - Ch. "Stack Alignment on exception entry"
    // - Ch. "Context state stacking on exception entry with the FP extension"
    temp_fault_memory_dump.hdr.reserved[0] = 0;
    temp_fault_memory_dump.hdr.reserved[1] = 0;
    temp_fault_memory_dump.hdr.reserved[2] = 0;
    temp_fault_memory_dump.hdr.reserved[3] = 0;
    temp_fault_memory_dump.stack_frame_len = sizeof(basic_x_frame_t);

    // copy exception frame register values from stack
    temp_fault_memory_dump.stack_frame.basic_regs.r0  = p_fault_stack_frame_start[0];
    temp_fault_memory_dump.stack_frame.basic_regs.r1  = p_fault_stack_frame_start[1];
    temp_fault_memory_dump.stack_frame.basic_regs.r2  = p_fault_stack_frame_start[2];
    temp_fault_memory_dump.stack_frame.basic_regs.r3  = p_fault_stack_frame_start[3];
    temp_fault_memory_dump.stack_frame.basic_regs.r12 = p_fault_stack_frame_start[4];
    temp_fault_memory_dump.stack_frame.basic_regs.lr  = p_fault_stack_frame_start[5];
    temp_fault_memory_dump.stack_frame.basic_regs.pc  = p_fault_stack_frame_start[6];
    temp_fault_memory_dump.stack_frame.basic_regs.psr = p_fault_stack_frame_start[7];

    // is FP extension enabled
    if (CONTROL_FPCA_Msk == (__get_CONTROL() & CONTROL_FPCA_Msk))
    {
        temp_fault_memory_dump.stack_frame_len = sizeof(extended_x_frame_t);

        // copy extended FP register values from stack
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 0] = p_fault_stack_frame_start[8];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 1] = p_fault_stack_frame_start[9];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 2] = p_fault_stack_frame_start[10];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 3] = p_fault_stack_frame_start[11];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 4] = p_fault_stack_frame_start[12];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 5] = p_fault_stack_frame_start[13];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 6] = p_fault_stack_frame_start[14];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 7] = p_fault_stack_frame_start[15];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 8] = p_fault_stack_frame_start[16];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 9] = p_fault_stack_frame_start[17];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[10] = p_fault_stack_frame_start[18];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[11] = p_fault_stack_frame_start[19];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[12] = p_fault_stack_frame_start[20];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[13] = p_fault_stack_frame_start[21];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[14] = p_fault_stack_frame_start[22];
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[15] = p_fault_stack_frame_start[23];

        temp_fault_memory_dump.stack_frame.fpscr = __get_FPSCR();
    }
    else
    {
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 0] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 1] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 2] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 3] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 4] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 5] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 6] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 7] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 8] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[ 9] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[10] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[11] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[12] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[13] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[14] = 0;
        temp_fault_memory_dump.stack_frame.fp_ext_reg_s[15] = 0;

        temp_fault_memory_dump.stack_frame.fpscr = 0;
    }

    // copy additional CPU registers which may be useful for analyzing the problem (not residing on stack)
    if (NULL != SCB)
    {
        temp_fault_memory_dump.cfsr = SCB->CFSR;
        temp_fault_memory_dump.abfsr = SCB->ABFSR;
        temp_fault_memory_dump.hfsr = SCB->HFSR;
        temp_fault_memory_dump.mmfar = SCB->MMFAR;
        temp_fault_memory_dump.bfar = SCB->BFAR;
        temp_fault_memory_dump.vtor = SCB->VTOR;
    }

    // copy environment data
    temp_fault_memory_dump.hdr.record_type = ARM_FAULT_REC_TYPE_USER;
    temp_fault_memory_dump.hdr.exception_rtc_ts = env_data.rtc_time;
    temp_fault_memory_dump.hdr.uptime = env_data.uptime;

    // calculate CRC but skip the CRC field itself
    temp_fault_memory_dump.crc = crc32(CRC32_INIT_REMAINDER, (uint8_t *) &temp_fault_memory_dump, sizeof(temp_fault_memory_dump) - sizeof(temp_fault_memory_dump.crc));

    // handle stored frame and reset the system...
    Error_Handler();
}

void arm_fault_handler_init(void)
{
    if (NULL != SCB)
    {
        SCB->CCR |= SCB_CCR_DIV_0_TRP_Pos;    // enable zero devision fault
        SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk);
    }
}

void arm_fault_handler_set_env(arm_fault_handler_env_t * const p_env_data)
{
    if (NULL != p_env_data)
    {
        (void) memcpy(&env_data, p_env_data, sizeof(arm_fault_handler_env_t));
    }
}

bool arm_fault_handler_read_last(persisted_ram_x_frame_t * const p_buf)
{
    bool res = false;

    if (NULL != p_buf)
    {
        if (arm_fault_handler_is_frame_valid(&temp_fault_memory_dump))
        {
            (void) memcpy((void *) p_buf, (void *) &temp_fault_memory_dump, sizeof(persisted_ram_x_frame_t));
            (void) memset((void *) &temp_fault_memory_dump, 0U, sizeof(persisted_ram_x_frame_t));
            temp_fault_memory_dump.hdr.record_type = ARM_FAULT_REC_TYPE_EMPTY;  // just mark the region as empty (CRC will not be valid)

            res = true;
        }
    }

    return res;
}

bool arm_fault_handler_is_frame_valid(persisted_ram_x_frame_t * const p_frame)
{
    bool res = false;

    if (NULL != p_frame)
    {
        uint32_t ram_crc = crc32(CRC32_INIT_REMAINDER, (uint8_t *) p_frame, sizeof(temp_fault_memory_dump) - sizeof(temp_fault_memory_dump.crc));

        res = (ram_crc == p_frame->crc);
    }

    return res;
}

void arm_fault_handler_bkpt_if_debug(void)
{
    if ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) == CoreDebug_DHCSR_C_DEBUGEN_Msk)
    {
        __BKPT();
    }
}

void arm_fault_handler_generic(const uint8_t * const p_user_data, const uint32_t user_data_sz)
{
    if ((NULL == p_user_data) || (0U == user_data_sz))
    {
        return;
    }

    static_assert(sizeof(persisted_ram_x_frame_t) == sizeof(persisted_ram_generic_frame_t));

    // the following cast is ok because persisted_ram_generic_frame_t and persisted_ram_x_frame_t are the same size
    persisted_ram_generic_frame_t *p_generic_frame = (persisted_ram_generic_frame_t *) &temp_fault_memory_dump;

    // copy environment data (add 'G' to record type for generic to indicate this fault doesn't contain register capture)
    p_generic_frame->hdr.record_type = ARM_FAULT_REC_TYPE_USER | ('G' << 8);
    p_generic_frame->hdr.exception_rtc_ts = env_data.rtc_time;
    p_generic_frame->hdr.uptime = env_data.uptime;

    uint32_t sz_to_copy = (user_data_sz > sizeof(p_generic_frame->data)) ? sizeof(p_generic_frame->data) : user_data_sz;

    (void) memset(p_generic_frame->data, 0U, sizeof(p_generic_frame->data));
    (void) memcpy(p_generic_frame->data, p_user_data, sz_to_copy);

    p_generic_frame->crc = crc32(CRC32_INIT_REMAINDER, (uint8_t *) p_generic_frame, sizeof(persisted_ram_generic_frame_t) - sizeof(p_generic_frame->crc));
}

void MemManage_Handler(void)
{
    // Note: This must be an assembly macro! Do not call functions here because you will most likely change
    // the exception frame stored on the stack at the time when the exception occurred!
    HANDLE_FAULT();
}

void BusFault_Handler(void)
{
    // Note: This must be an assembly macro! Do not call functions here because you will most likely change
    // the exception frame stored on the stack at the time when the exception occurred!
    HANDLE_FAULT();
}

void UsageFault_Handler(void)
{
    // Note: This must be an assembly macro! Do not call functions here because you will most likely change
    // the exception frame stored on the stack at the time when the exception occurred!
    HANDLE_FAULT();
}

void HardFault_Handler(void)
{
    // Note: This must be an assembly macro! Do not call functions here because you will most likely change
    // the exception frame stored on the stack at the time when the exception occurred!
    HANDLE_FAULT();
}
