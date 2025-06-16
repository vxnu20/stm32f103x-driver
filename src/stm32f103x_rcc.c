#include "stm32f103x_rcc.h"

void rcc_enable_gpio_clock(gpio_regs* gpio)
{
    /* if clock is enabled not needed to set again*/
    if(gpio == GPIO_PORTA && !(RCC->APB2ENR & APB2ENR_PORTA))
    {
        RCC->APB2ENR |= APB2ENR_PORTA;
    }
    else if(gpio == GPIO_PORTB && !(RCC->APB2ENR & APB2ENR_PORTB))
    {
        RCC->APB2ENR |= APB2ENR_PORTB;
    }
    else if(gpio == GPIO_PORTC && !(RCC->APB2ENR & APB2ENR_PORTC))
    {
        RCC->APB2ENR |= APB2ENR_PORTC;
    }
    else
    {
        return;
    }
}

void rcc_enable_usart_clock(usart_regs* usart)
{
    if(usart == USART1)
    {
        /* enable clock access to USART1 */
        RCC->APB2ENR |= APB2ENR_USART1;
    }
    else if(usart == USART2)
    {
        RCC->APB1ENR |= APB1ENR_USART2;
    }
    else if(usart == USART3)
    {
        RCC->APB1ENR |= APB1ENR_USART3;
    }
    else
    {
        return;
    }
}

void rcc_enable_adc_clock(adc_regs* adc)
{
    /* enable the respective clock for ADC */
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