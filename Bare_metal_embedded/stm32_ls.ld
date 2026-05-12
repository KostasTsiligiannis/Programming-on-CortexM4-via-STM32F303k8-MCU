ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 12K
}

__max_heap_size  = 0x0;   /* 1 KB heap */
__max_stack_size = 0x0;   /* 512 B stack */

SECTIONS
{
    /*----------------------------------------------------
     * Code and read-only data in FLASH
     *---------------------------------------------------*/
    .text :
    {
        KEEP(*(.isr_vector))   /* Vector table */
        *(.text)
        *(.text.*)
        *(.init)
        *(.fini)
        *(.rodata)
        *(.rodata.*)

        . = ALIGN(4);
        _etext = .;            /* End of code section */
    } > FLASH

    /* Load address of .data section in FLASH */
    _la_data = LOADADDR(.data);

    /*----------------------------------------------------
     * Initialized data in SRAM
     *---------------------------------------------------*/
    .data :
    {
        . = ALIGN(4);
        _sdata = .;

        *(.data)
        *(.data.*)

        . = ALIGN(4);
        _edata = .;
    } > SRAM AT > FLASH

    /*----------------------------------------------------
     * Uninitialized data in SRAM
     *---------------------------------------------------*/
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        __bss_start__ = _sbss;

        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
        . = ALIGN(4);
		end = .;
		__end__ = .;
    } > SRAM

    /*----------------------------------------------------
     * Heap and stack reservation
     *---------------------------------------------------*/
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE(end = .);
        PROVIDE(_end = .);

        . = . + __max_heap_size;
        . = . + __max_stack_size;

        . = ALIGN(8);
    } > SRAM
}