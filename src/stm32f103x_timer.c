#include "stm32f103x_timer.h"


void timer_init(timer_config config)
{
    if(config.timer == TIM1)
        RCC->APB2ENR |= APB2ENR_TIM1;
    else if(config.timer == TIM2)
        RCC->APB1ENR |= APB1ENR_TIM2;
    else if(config.timer == TIM3)
        RCC->APB1ENR |= APB1ENR_TIM3;
    else if(config.timer == TIM4)
        RCC->APB1ENR |= APB1ENR_TIM4;
}