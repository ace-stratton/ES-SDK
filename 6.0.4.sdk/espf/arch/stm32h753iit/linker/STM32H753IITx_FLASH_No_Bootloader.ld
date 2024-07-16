/*
******************************************************************************
**
**  File        : LinkerScript.ld
**
**  Author      : STM32CubeIDE
**
**  Abstract    : Linker script for STM32H7 series
**                2048Kbytes FLASH and 1056Kbytes RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is, without any warranty
**                of any kind.
**
*****************************************************************************
** @attention
**
** <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
** All rights reserved.</center></h2>
**
** This software component is licensed by ST under BSD 3-Clause license,
** the "License"; You may not use this file except in compliance with the
** License. You may obtain a copy of the License at:
**                        opensource.org/licenses/BSD-3-Clause
**
****************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM_D1) + LENGTH(RAM_D1);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
lnk_freertos_heap_size_bytes = 135 * 1024;              /* required amount of heap  */
lnk_user_main_stack_size_bytes = 2 * 1024;              /* required amount of stack */
lnk_user_main_stack_start_addr = _estack - lnk_user_main_stack_size_bytes;

/*
    Memory map (+application):
    Bootloader:
    | ---  | --------- | -----------------------------------
    | Bank | Size (KB) | Allocated to 
    | ---  | --------- | -----------------------------------
    | 0-2  | 128       | Bootloader
    | 3-13 | 128       | Application
    | 14   | 128       | App runtime configuration block
    | 15   | 128       | BL metadata (Application CRC, etc.)
*/
_Flash_Sector_Size = 128K;
_Application_Start_Sector = 3;
_Application_Max_Sector = 13;
_Application_Max_Size = (_Application_Max_Sector - _Application_Start_Sector + 1) * _Flash_Sector_Size;
_Ram_D1_Min_Address = ORIGIN(RAM_D1);
_Ram_D1_Max_Address = ORIGIN(RAM_D1) + LENGTH(RAM_D1) - 1;
_Application_Start_Addr = ORIGIN(FLASH);
_FAULT_MEM_LENGTH = 1K;

/* Specify the memory areas */
MEMORY
{
  FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = _Application_Max_Size
  DTCMRAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K
  RAM_D1 (xrw)   : ORIGIN = 0x24000000, LENGTH = 512K
  RAM_D2 (xrw)   : ORIGIN = 0x30000000, LENGTH = 288K
  RAM_D3 (xrw)   : ORIGIN = 0x38000000, LENGTH = 64K
  ITCMRAM (xrw)  : ORIGIN = 0x00000000, LENGTH = 64K
  /* This is where the last HW fault exception will be stored for retrieval after reset */
  FAULT_RAM (rw): ORIGIN = ORIGIN(DTCMRAM), LENGTH = _FAULT_MEM_LENGTH
}

ETH_STACK_DATA_MEMORY_BASE = ORIGIN(RAM_D2);
RAM_D2_START_ADDRESS = ORIGIN(RAM_D2);

DMA_RX_DESCIPTORS_SIZE = 0x200;
DMA_TX_DESCRIPTORS_SIZE = 0x200;
DMA_DESCRIPTORS_SIZE = DMA_RX_DESCIPTORS_SIZE + DMA_TX_DESCRIPTORS_SIZE;

_LWIP_RX_DESCRIPTOR_START_ = ETH_STACK_DATA_MEMORY_BASE;
_LWIP_TX_DESCRIPTOR_START_ = _LWIP_RX_DESCRIPTOR_START_ + DMA_RX_DESCIPTORS_SIZE;

_LWIP_RX_POOL_AND_HEAP_START_ = ETH_STACK_DATA_MEMORY_BASE + DMA_DESCRIPTORS_SIZE;

LWIP_RX_POOL_SIZE = 0x5000;
_LWIP_RAM_HEAP_SIZE_ = 0x5000;

_LWIP_RAM_HEAP_START_ = _LWIP_RX_POOL_AND_HEAP_START_ + LWIP_RX_POOL_SIZE;

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM_D1 AT> FLASH

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM_D1

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    PROVIDE ( lnk_freertos_heap_start_addr = .);
    . = . + lnk_freertos_heap_size_bytes;
    . = . + lnk_user_main_stack_size_bytes;
    . = ALIGN(8);
  } >RAM_D1

  /*
  ** TX and RX DMA descriptors (defined in ethernetif.c file) should be located in D2 SRAM and
  ** be configured by MPU as Device memory or Strongly-ordered type.
  ** https://community.st.com/s/article/FAQ-Ethernet-not-working-on-STM32H7x3
  */
  .lwip_sec (NOLOAD) :
  {
    . = ABSOLUTE(ETH_STACK_DATA_MEMORY_BASE);
    *(.DMA_Rx_Decr_Section)

    . = ABSOLUTE(_LWIP_TX_DESCRIPTOR_START_);
    *(.DMA_Tx_Decr_Section)

    . = ABSOLUTE(_LWIP_RX_POOL_AND_HEAP_START_);
    *(.LwIP_Rx_PoolSection)
    . = . + _LWIP_RAM_HEAP_SIZE_;
  } >RAM_D2

  .regular_rtos_task_stack (NOLOAD) :
  {
      *(.regular_rtos_task_stack)
      _regular_task_stack_size = ABSOLUTE(.);
  } >RAM_D2

  /* Configuration section, to be read during runtime */
  .moduleConfig 0x81C0000 :
  {
    __MODULE_CONFIG_START = .;
    KEEP(*(.moduleConfig)) /* keep my variable even if not referenced */
  } >FLASH

  .fault_mem (NOLOAD):
  {
      /* place here all symbols in input sections that start with .fault_mem */
      KEEP(*(*.fault_mem*))
  } > FAULT_RAM

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
