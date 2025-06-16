#include "stm32f103x_timer.h"


void timer_init(timer_config config)
{
    /* set the pre-scalar and auto reload value */
    config.timer->PSC = config.prescalar;
    config.timer->ARR = config.auto_reload;
    /* clear the counter */
    config.timer->CNT = 0;
    /* enable the counter */
    config.timer->CR1 |= TIM_CR1_CEN;
}

uint16_t timer_read_count(timer_regs* timer)
{
    return timer->CNT;
}