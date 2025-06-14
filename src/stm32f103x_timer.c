#include "stm32f103x_timer.h"


void timer_init(timer_config config)
{
    /* enable respective peripheral clock */
    if(config.timer == TIM1)
        RCC->APB2ENR |= APB2ENR_TIM1;
    else if(config.timer == TIM2)
        RCC->APB1ENR |= APB1ENR_TIM2;
    else if(config.timer == TIM3)
        RCC->APB1ENR |= APB1ENR_TIM3;
    else if(config.timer == TIM4)
        RCC->APB1ENR |= APB1ENR_TIM4;
    else
        return;
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