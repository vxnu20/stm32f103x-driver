#include "stm32f103x_systick.h"

static volatile uint32_t systick_counter;

void systick_init(uint32_t tick)
{
    if((tick-1) > MAX_24BIT)
        return;
    SYSTICK->LOAD = tick-1;
    SYSTICK->VAL  = 0;
    SYSTICK->CTRL = STK_ENABLE | STK_INT_ENABLE | STK_CLK_AHB;
}

void _delay(uint32_t ms)
{
    uint32_t until = systick_counter + ms;
    while(systick_counter < until)
    {
        asm("nop");
    }
}

void _systick_handler()
{
    systick_counter++;
}