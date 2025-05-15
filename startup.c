
/* Startup code */

extern int main(void);


__attribute__((naked, noreturn)) void _reset(void)
{
    // memset .bss to zero, and copy .data section to RAM region
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

    main();

    for(;;) (void) 0; // Infinite loop
}

extern void _estack(void); 

// 16 std and 60 specific handlers
__attribute__((section(".vectors"))) void (*const tab[16+ 60])(void) = {
    _estack, _reset
};