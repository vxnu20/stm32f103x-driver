#include "stm32f103x_adc.h"


void adc_init(adc_regs* adc)
{
    if(adc == ADC1)
    {
        RCC->APB2ENR |= APB2ENR_ADC1;
    }
    else if(adc == ADC2)
    {
        RCC->APB2ENR |= APB2ENR_ADC2;
    }
    else
    {
        return;
    }
    
}