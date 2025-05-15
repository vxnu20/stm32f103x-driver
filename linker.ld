ENTRY(_reset);

MEMORY {
    flash(rx) : ORIGIN = 0x08000000, LENGTH = 128k
    sram(rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}

_estack = ORIGIN(sram) + LENGTH(sram); /* stack points to the end of SRAM */

SECTIONS {
.vectors : { KEEP (*(.vectors)) } > flash
.text    : ALIGN(4) { *(.text*) }          > flash
.rodata  : ALIGN(4) { *(.rodata*) }        > flash


.data : ALIGN(4) {
    _sdata = .;   /* .data section start */
    *(.first_data)
    *(.data SORT(.data.*))
    _edata = .;  /* .data section end */
} > sram AT > flash

_sidata = LOADADDR(.data);


.bss : {
    _sbss = .;              /* .bss section start */
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;              /* .bss section end */
}                                   > sram

    . = ALIGN(4);
    _end = .;     /* for cmsis_gcc.h  */
} 