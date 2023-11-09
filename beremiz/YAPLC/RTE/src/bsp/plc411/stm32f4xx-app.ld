/* @page Linker script (APP)
 *       STM32F411CE
 *       ARM Cortex-M4 32-bit RISC
 *       Total memory: 512K Flash, 128K RAM
 *       2022-2023
 */

/* @def Memory regions
 *
 *      RAM   - RAM bank 0
 *      FLASH - flash
 *
 *      ORIGIN - starting address of a region
 *      LENGTH - length of a region
 *
 *      The values below can be addressed in further linker scripts
 *      using functions like 'ORIGIN(RAM)' or 'LENGTH(RAM)'.
 */

MEMORY
{
  flash (rx)  : ORIGIN = 0x08040000, LENGTH = 256K
  ram (rwx)   : ORIGIN = 0x20019000, LENGTH = 28K
  ccm (rwx)   : ORIGIN = 0x00000000, LENGTH = 0
}

__rom_start__	= ORIGIN(flash);
__rom_size__	= LENGTH(flash);
__ram_start__	= ORIGIN(ram);
__ram_size__	= LENGTH(ram);
__ram_end__	    = __ram_start__ + __ram_size__;
_plc_sstart	    = __ram_end__;		/* Top of RAM */

SECTIONS
{
  .text : {
  KEEP(*(.plc_app_abi_sec)) /* PLC APP ABI */
  KEEP(*(.plc_md5_sec))     /* PLC APP ABI */
  *(.text*)				    /* Program code */
  KEEP(*(.rodata*))			/* Read only data */

  . = ALIGN(4);
  _plc_pa_start = .;
  KEEP(*(.preinit_array))	    /* Preinitarray */
  _plc_pa_end = .;

  . = ALIGN(4);
  _plc_ia_start = .;
  KEEP (*(SORT(.init_array.*)))
  KEEP(*(.ctors))			    /*Construcrs*/
  _plc_ia_end = .;

  . = ALIGN(4);
  _plc_fia_start = .;
  KEEP(*(.fini_array))	        /*Destructors */
  KEEP (*(SORT(.fini_array.*)))
  _plc_fia_end = .;

  } >flash

  .data : ALIGN(16) {
  _plc_data_start = .;	    /* Used in PLC startup */
  *(.data*)				    /* Initialized data */
  _plc_data_end = .;	    /* Used in PLC startup */
  } >ram AT > flash
  _plc_data_loadaddr = LOADADDR(.data);

  .bss (NOLOAD) : ALIGN(16) {
  *(.bss*)				    /* Uninitialized data */
  *(COMMON)				    /* Common data */
  _plc_bss_end = .;			/* Used in PLC startup */
  } >ram

  /* C++ exception unwinding stuff--needed by some toolchains */

  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >flash

  __exidx_start = .;
  .ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } >flash
  __exidx_end = .;


  ._plc_check :
  {
  KEEP(*(.plc_check_sec))     /* PLC APP ABI */
  } > flash
}

/* Firmware entry point */

ENTRY(fake_start)

