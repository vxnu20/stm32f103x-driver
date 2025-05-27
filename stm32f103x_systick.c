#include "stm32f103x_systick.h"

volatile uint32_t systick_count;

void systick_init(uint32_t tick)
{
    if((tick-1) > MAX_24BIT)
        return;
    SYSTICK->LOAD = tick-1;
    SYSTICK->VAL  = 0;
    SYSTICK->CTRL = STK_ENABLE | STK_INT_ENABLE | STK_CLK_AHB;
}

void _systick_handler()
{
    systick_count++;
}