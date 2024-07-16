/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2019 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <string.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "ff.h"
#include "extmod/vfs_fat.h"

#include "sdcard.h"
//#include "stm32h7xx_hal_sd.h"
//#include "stm32h7xx_hal.h"
#include "sd_diskio.h"


#if MICROPY_HW_ENABLE_SDCARD || MICROPY_HW_ENABLE_MMCARD

#if defined(STM32F7) || defined(STM32H7) || defined(STM32L4)

// The H7/F7/L4 have 2 SDMMC peripherals, but at the moment this driver only supports
// using one of them in a given build, selected by MICROPY_HW_SDCARD_SDMMC.

#if MICROPY_HW_SDCARD_SDMMC == 2
#define SDIO SDMMC2
#define SDMMC_IRQHandler SDMMC2_IRQHandler
#define SDMMC_CLK_ENABLE() __HAL_RCC_SDMMC2_CLK_ENABLE()
#define SDMMC_CLK_DISABLE() __HAL_RCC_SDMMC2_CLK_DISABLE()
#define SDMMC_FORCE_RESET() __HAL_RCC_SDMMC2_FORCE_RESET()
#define SDMMC_RELEASE_RESET() __HAL_RCC_SDMMC2_RELEASE_RESET()
#define SDMMC_IRQn SDMMC2_IRQn
#define SDMMC_DMA dma_SDMMC_2
#define STATIC_AF_SDCARD_CK STATIC_AF_SDMMC2_CK
#define STATIC_AF_SDCARD_CMD STATIC_AF_SDMMC2_CMD
#define STATIC_AF_SDCARD_D0 STATIC_AF_SDMMC2_D0
#define STATIC_AF_SDCARD_D1 STATIC_AF_SDMMC2_D1
#define STATIC_AF_SDCARD_D2 STATIC_AF_SDMMC2_D2
#define STATIC_AF_SDCARD_D3 STATIC_AF_SDMMC2_D3
#define STATIC_AF_SDCARD_D4 STATIC_AF_SDMMC2_D4
#define STATIC_AF_SDCARD_D5 STATIC_AF_SDMMC2_D5
#define STATIC_AF_SDCARD_D6 STATIC_AF_SDMMC2_D6
#define STATIC_AF_SDCARD_D7 STATIC_AF_SDMMC2_D7
#else
#define SDIO SDMMC1
#define SDMMC_IRQHandler SDMMC1_IRQHandler
#define SDMMC_CLK_ENABLE() __HAL_RCC_SDMMC1_CLK_ENABLE()
#define SDMMC_CLK_DISABLE() __HAL_RCC_SDMMC1_CLK_DISABLE()
#define SDMMC_FORCE_RESET() __HAL_RCC_SDMMC1_FORCE_RESET()
#define SDMMC_RELEASE_RESET() __HAL_RCC_SDMMC1_RELEASE_RESET()
#define SDMMC_IRQn SDMMC1_IRQn
#define SDMMC_DMA dma_SDIO_0
#define STATIC_AF_SDCARD_CK STATIC_AF_SDMMC1_CK
#define STATIC_AF_SDCARD_CMD STATIC_AF_SDMMC1_CMD
#define STATIC_AF_SDCARD_D0 STATIC_AF_SDMMC1_D0
#define STATIC_AF_SDCARD_D1 STATIC_AF_SDMMC1_D1
#define STATIC_AF_SDCARD_D2 STATIC_AF_SDMMC1_D2
#define STATIC_AF_SDCARD_D3 STATIC_AF_SDMMC1_D3
#define STATIC_AF_SDCARD_D4 STATIC_AF_SDMMC1_D4
#define STATIC_AF_SDCARD_D5 STATIC_AF_SDMMC1_D5
#define STATIC_AF_SDCARD_D6 STATIC_AF_SDMMC1_D6
#define STATIC_AF_SDCARD_D7 STATIC_AF_SDMMC1_D7
#endif

// The F7 & L4 series calls the peripheral SDMMC rather than SDIO, so provide some
// #defines for backwards compatability.

#define SDIO_CLOCK_EDGE_RISING              SDMMC_CLOCK_EDGE_RISING
#define SDIO_CLOCK_EDGE_FALLING             SDMMC_CLOCK_EDGE_FALLING

#define SDIO_CLOCK_BYPASS_DISABLE           SDMMC_CLOCK_BYPASS_DISABLE
#define SDIO_CLOCK_BYPASS_ENABLE            SDMMC_CLOCK_BYPASS_ENABLE

#define SDIO_CLOCK_POWER_SAVE_DISABLE       SDMMC_CLOCK_POWER_SAVE_DISABLE
#define SDIO_CLOCK_POWER_SAVE_ENABLE        SDMMC_CLOCK_POWER_SAVE_ENABLE

#define SDIO_BUS_WIDE_1B                    SDMMC_BUS_WIDE_1B
#define SDIO_BUS_WIDE_4B                    SDMMC_BUS_WIDE_4B
#define SDIO_BUS_WIDE_8B                    SDMMC_BUS_WIDE_8B

#define SDIO_HARDWARE_FLOW_CONTROL_DISABLE  SDMMC_HARDWARE_FLOW_CONTROL_DISABLE
#define SDIO_HARDWARE_FLOW_CONTROL_ENABLE   SDMMC_HARDWARE_FLOW_CONTROL_ENABLE

#if defined(STM32H7)
#define SDIO_TRANSFER_CLK_DIV               SDMMC_NSpeed_CLK_DIV
#define SDIO_USE_GPDMA                      0
#else
#define SDIO_TRANSFER_CLK_DIV               SDMMC_TRANSFER_CLK_DIV
#define SDIO_USE_GPDMA                      1
#endif

#else

// These are definitions for F4 MCUs so there is a common macro across all MCUs.

#define SDMMC_CLK_ENABLE() __SDIO_CLK_ENABLE()
#define SDMMC_CLK_DISABLE() __SDIO_CLK_DISABLE()
#define SDMMC_IRQn SDIO_IRQn
#define SDMMC_IRQHandler SDIO_IRQHandler
#define SDMMC_DMA dma_SDIO_0
#define SDIO_USE_GPDMA 1
#define STATIC_AF_SDCARD_CK STATIC_AF_SDIO_CK
#define STATIC_AF_SDCARD_CMD STATIC_AF_SDIO_CMD
#define STATIC_AF_SDCARD_D0 STATIC_AF_SDIO_D0
#define STATIC_AF_SDCARD_D1 STATIC_AF_SDIO_D1
#define STATIC_AF_SDCARD_D2 STATIC_AF_SDIO_D2
#define STATIC_AF_SDCARD_D3 STATIC_AF_SDIO_D3
#define STATIC_AF_SDCARD_D4 STATIC_AF_SDIO_D4
#define STATIC_AF_SDCARD_D5 STATIC_AF_SDIO_D5
#define STATIC_AF_SDCARD_D6 STATIC_AF_SDIO_D6
#define STATIC_AF_SDCARD_D7 STATIC_AF_SDIO_D7

#endif

// If no custom SDIO pins defined, use the default ones
#ifndef MICROPY_HW_SDCARD_CK
#define MICROPY_HW_SDCARD_D0 (pin_C8)
#define MICROPY_HW_SDCARD_D1 (pin_C9)
#define MICROPY_HW_SDCARD_D2 (pin_C10)
#define MICROPY_HW_SDCARD_D3 (pin_C11)
#define MICROPY_HW_SDCARD_CK (pin_C12)
#define MICROPY_HW_SDCARD_CMD (pin_D2)
#endif

// Define a constant to select the bus width.
#if MICROPY_HW_SDCARD_BUS_WIDTH == 4
#define SDIO_BUS_WIDE_VALUE SDIO_BUS_WIDE_4B
#elif MICROPY_HW_SDCARD_BUS_WIDTH == 8
#define SDIO_BUS_WIDE_VALUE SDIO_BUS_WIDE_8B
#endif

#define PYB_SDMMC_FLAG_SD       (0x01)
#define PYB_SDMMC_FLAG_MMC      (0x02)
#define PYB_SDMMC_FLAG_ACTIVE   (0x04)

static uint8_t pyb_sdmmc_flags;


/******************************************************************************/
// MicroPython bindings
//
// Expose the SD card or MMC as an object with the block protocol.

#if !BUILDING_MBOOT

// There are singleton SDCard/MMCard objects
#if MICROPY_HW_ENABLE_SDCARD
const mp_obj_base_t pyb_sdcard_obj = {&pyb_sdcard_type};
#endif
#if MICROPY_HW_ENABLE_MMCARD
const mp_obj_base_t pyb_mmcard_obj = {&pyb_mmcard_type};
#endif

#if MICROPY_HW_ENABLE_SDCARD
STATIC mp_obj_t pyb_sdcard_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 0, 0, false);

    #if MICROPY_HW_ENABLE_MMCARD
    if (pyb_sdmmc_flags & PYB_SDMMC_FLAG_MMC) {
        mp_raise_ValueError(MP_ERROR_TEXT("peripheral used by MMCard"));
    }
    #endif

    pyb_sdmmc_flags |= PYB_SDMMC_FLAG_SD;

    // return singleton object
    return MP_OBJ_FROM_PTR(&pyb_sdcard_obj);
}
#endif

#if MICROPY_HW_ENABLE_MMCARD
STATIC mp_obj_t pyb_mmcard_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 0, 0, false);

    #if MICROPY_HW_ENABLE_SDCARD
    if (pyb_sdmmc_flags & PYB_SDMMC_FLAG_SD) {
        mp_raise_ValueError(MP_ERROR_TEXT("peripheral used by SDCard"));
    }
    #endif

    pyb_sdmmc_flags |= PYB_SDMMC_FLAG_MMC;

    // return singleton object
    return MP_OBJ_FROM_PTR(&pyb_mmcard_obj);
}
#endif

//marian: currently sd_present is removed.
//STATIC mp_obj_t sd_present(mp_obj_t self) {
//    return mp_obj_new_bool(sdcard_is_present());
//}
//STATIC MP_DEFINE_CONST_FUN_OBJ_1(sd_present_obj, sd_present);

//marian: currently sd_power is removed.
//STATIC mp_obj_t sd_power(mp_obj_t self, mp_obj_t state) {
//    bool result;
//    if (mp_obj_is_true(state)) {
//        result = sdcard_power_on();
//    } else {
//        sdcard_power_off();
//        result = true;
//    }
//    return mp_obj_new_bool(result);
//}
//STATIC MP_DEFINE_CONST_FUN_OBJ_2(sd_power_obj, sd_power);

//STATIC mp_obj_t sd_info(mp_obj_t self) {
//    if (!(pyb_sdmmc_flags & PYB_SDMMC_FLAG_ACTIVE)) {
//        return mp_const_none;
//    }
//    uint32_t card_type;
//    uint32_t log_block_nbr;
//    uint32_t log_block_size;
//    #if MICROPY_HW_ENABLE_MMCARD
//    if (pyb_sdmmc_flags & PYB_SDMMC_FLAG_MMC) {
//        card_type = sdmmc_handle.mmc.MmcCard.CardType;
//        log_block_nbr = sdmmc_handle.mmc.MmcCard.LogBlockNbr;
//        log_block_size = sdmmc_handle.mmc.MmcCard.LogBlockSize;
//    } else
//    #endif
//    {
//        card_type = sdmmc_handle.sd.SdCard.CardType;
//        log_block_nbr = sdmmc_handle.sd.SdCard.LogBlockNbr;
//        log_block_size = sdmmc_handle.sd.SdCard.LogBlockSize;
//    }
//    // cardinfo.SD_csd and cardinfo.SD_cid have lots of info but we don't use them
//    mp_obj_t tuple[3] = {
//        mp_obj_new_int_from_ull((uint64_t)log_block_nbr * (uint64_t)log_block_size),
//        mp_obj_new_int_from_uint(log_block_size),
//        mp_obj_new_int(card_type),
//    };
//    return mp_obj_new_tuple(3, tuple);
//}
//STATIC MP_DEFINE_CONST_FUN_OBJ_1(sd_info_obj, sd_info);

// now obsolete, kept for backwards compatibility
STATIC mp_obj_t sd_read(mp_obj_t self, mp_obj_t block_num) {
    uint8_t *dest = m_new(uint8_t, SDCARD_BLOCK_SIZE);
    mp_uint_t ret = SD_read(dest, mp_obj_get_int(block_num), 1);

    if (ret != 0) {
        m_del(uint8_t, dest, SDCARD_BLOCK_SIZE);
        mp_raise_msg_varg(&mp_type_Exception, MP_ERROR_TEXT("sdcard_read_blocks failed [%u]"), ret);
    }

    return mp_obj_new_bytearray_by_ref(SDCARD_BLOCK_SIZE, dest);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(sd_read_obj, sd_read);

// now obsolete, kept for backwards compatibility
STATIC mp_obj_t sd_write(mp_obj_t self, mp_obj_t block_num, mp_obj_t data) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data, &bufinfo, MP_BUFFER_READ);
    if (bufinfo.len % SDCARD_BLOCK_SIZE != 0) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("writes must be a multiple of %d bytes"), SDCARD_BLOCK_SIZE);
    }

    mp_uint_t ret = SD_write(bufinfo.buf, mp_obj_get_int(block_num), bufinfo.len / SDCARD_BLOCK_SIZE);

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_Exception, MP_ERROR_TEXT("sdcard_write_blocks failed [%u]"), ret);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(sd_write_obj, sd_write);

STATIC mp_obj_t pyb_sdcard_readblocks(mp_obj_t self, mp_obj_t block_num, mp_obj_t buf) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf, &bufinfo, MP_BUFFER_WRITE);
    mp_uint_t ret = SD_read(bufinfo.buf, mp_obj_get_int(block_num), bufinfo.len / SDCARD_BLOCK_SIZE);
    return mp_obj_new_bool(ret == 0);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(pyb_sdcard_readblocks_obj, pyb_sdcard_readblocks);

STATIC mp_obj_t pyb_sdcard_writeblocks(mp_obj_t self, mp_obj_t block_num, mp_obj_t buf) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf, &bufinfo, MP_BUFFER_READ);
    mp_uint_t ret = SD_write(bufinfo.buf, mp_obj_get_int(block_num), bufinfo.len / SDCARD_BLOCK_SIZE);
    return mp_obj_new_bool(ret == 0);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(pyb_sdcard_writeblocks_obj, pyb_sdcard_writeblocks);

STATIC mp_obj_t pyb_sdcard_ioctl(mp_obj_t self, mp_obj_t cmd_in, mp_obj_t arg_in) {
    mp_int_t cmd = mp_obj_get_int(cmd_in);
    switch (cmd) {
        case MP_BLOCKDEV_IOCTL_INIT:
//            if (!sdcard_power_on()) {
//                return MP_OBJ_NEW_SMALL_INT(-1); // error
//            }
            return MP_OBJ_NEW_SMALL_INT(0); // success

        case MP_BLOCKDEV_IOCTL_DEINIT:
//            sdcard_power_off();
            return MP_OBJ_NEW_SMALL_INT(0); // success

        case MP_BLOCKDEV_IOCTL_SYNC:
            // nothing to do
            return MP_OBJ_NEW_SMALL_INT(0); // success

        case MP_BLOCKDEV_IOCTL_BLOCK_COUNT:
        {
        	uint32_t* result = 0;
        	(void)SD_GetBlockSize(result);
            return MP_OBJ_NEW_SMALL_INT(result);
        }

        case MP_BLOCKDEV_IOCTL_BLOCK_SIZE:
            return MP_OBJ_NEW_SMALL_INT(SDCARD_BLOCK_SIZE);

        default: // unknown command
            return MP_OBJ_NEW_SMALL_INT(-1); // error
    }
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(pyb_sdcard_ioctl_obj, pyb_sdcard_ioctl);

STATIC const mp_rom_map_elem_t pyb_sdcard_locals_dict_table[] = {
//    { MP_ROM_QSTR(MP_QSTR_present), MP_ROM_PTR(&sd_present_obj) },
//    { MP_ROM_QSTR(MP_QSTR_power), MP_ROM_PTR(&sd_power_obj) },
//    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&sd_info_obj) },
    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&sd_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&sd_write_obj) },
    // block device protocol
    { MP_ROM_QSTR(MP_QSTR_readblocks), MP_ROM_PTR(&pyb_sdcard_readblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_writeblocks), MP_ROM_PTR(&pyb_sdcard_writeblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_ioctl), MP_ROM_PTR(&pyb_sdcard_ioctl_obj) },
};

STATIC MP_DEFINE_CONST_DICT(pyb_sdcard_locals_dict, pyb_sdcard_locals_dict_table);


#if MICROPY_HW_ENABLE_SDCARD
MP_DEFINE_CONST_OBJ_TYPE(
    pyb_sdcard_type,
    MP_QSTR_SDCard,
    MP_TYPE_FLAG_NONE,
    make_new, pyb_sdcard_make_new,
    locals_dict, &pyb_sdcard_locals_dict
    );
#endif

#if MICROPY_HW_ENABLE_MMCARD
MP_DEFINE_CONST_OBJ_TYPE(
    pyb_mmcard_type,
    MP_QSTR_MMCard,
    MP_TYPE_FLAG_NONE,
    make_new, pyb_mmcard_make_new,
    locals_dict, &pyb_sdcard_locals_dict
    );
#endif

void sdcard_init_vfs(fs_user_mount_t *vfs, int part) {
    pyb_sdmmc_flags = (pyb_sdmmc_flags & PYB_SDMMC_FLAG_ACTIVE) | PYB_SDMMC_FLAG_SD; // force SD mode
    vfs->base.type = &mp_fat_vfs_type;
    vfs->blockdev.flags |= MP_BLOCKDEV_FLAG_NATIVE | MP_BLOCKDEV_FLAG_HAVE_IOCTL;
    vfs->fatfs.drv = vfs;
    #if MICROPY_FATFS_MULTI_PARTITION
    vfs->fatfs.part = part;
    #endif
    vfs->blockdev.readblocks[0] = MP_OBJ_FROM_PTR(&pyb_sdcard_readblocks_obj);
    vfs->blockdev.readblocks[1] = MP_OBJ_FROM_PTR(&pyb_sdcard_obj);
    vfs->blockdev.readblocks[2] = MP_OBJ_FROM_PTR(SD_read); // native version
    vfs->blockdev.writeblocks[0] = MP_OBJ_FROM_PTR(&pyb_sdcard_writeblocks_obj);
    vfs->blockdev.writeblocks[1] = MP_OBJ_FROM_PTR(&pyb_sdcard_obj);
    vfs->blockdev.writeblocks[2] = MP_OBJ_FROM_PTR(SD_write); // native version
    vfs->blockdev.u.ioctl[0] = MP_OBJ_FROM_PTR(&pyb_sdcard_ioctl_obj);
    vfs->blockdev.u.ioctl[1] = MP_OBJ_FROM_PTR(&pyb_sdcard_obj);
}

#endif // !BUILDING_MBOOT

#endif // MICROPY_HW_ENABLE_SDCARD || MICROPY_HW_ENABLE_MMCARD
