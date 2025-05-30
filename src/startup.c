extern int main(void);
extern void _stack(void);
extern void _systick_handler(void);

__attribute__((naked, noreturn)) void _reset_handler(void)
{

    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

    main();

    for(;;)
    {
        // infinite loop
    }
}

void _hardfault(void)
{
    for(;;)
    {
        // infinite loop
    }
}

// 16 standard and 60 STM32-specific handlers
__attribute__((section(".vectors"))) void (*const isr[16 + 60])(void) = {
  _stack, 
  _reset_handler, 
  0, 
  _hardfault,
  0,0,0,0,0,0,0,0,0,0,0,
  _systick_handler
};