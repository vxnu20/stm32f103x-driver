ENTRY(_reset_handler);

MEMORY {
    flash(rx) : ORIGIN = 0x08000000, LENGTH = 128K
    sram(rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

_stack = ORIGIN(sram) + LENGTH(sram); /* stack points to the end of SRAM */

SECTIONS {
    
    .vectors :
    {
        KEEP(*(.vectors))
    } > flash

    .text :
    {
        *(.text*)
    } > flash

    .rodata : 
    { 
        *(.rodata*) 
    } > flash

    .data : 
    {
        _sdata = .;     /* Start address of .data in SRAM */
        *(.data)
        _edata = .;     /* End address of .data in SRAM */
    } > sram AT > flash


    _sidata = LOADADDR(.data);
    
    .bss : {

        _sbss = .;              /* .bss section start */
        *(.bss SORT(.bss.*) COMMON)
        _ebss = .;              /* .bss section end */
    } > sram
    
    end = .;
}