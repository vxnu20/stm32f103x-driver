#include "stm32f103x_gpio.h"
#include "stm32f103x_systick.h"
#include "stm32f013x_usart.h"
#include "stm32f103x_clock.h"
#include <stdio.h>


int main()
{
    /* enable clock for PORT c*/
    RCC->APB2ENR |= APB2ENR_PORTC;
    RCC->APB2ENR |= APB2ENR_PORTA;
    
    /* onboard user led */
    gpio_set_mode(GPIO_PORTC, 13, GPIO_MODE_OUT2MHZ, GN_PUSH_PULL);
    
    /* uart1 for logging purpose */
    gpio_set_mode(GPIO_PORTA, 9, GPIO_MODE_OUT2MHZ, ALT_PUSH_PULL);
    gpio_set_mode(GPIO_PORTA, 10, GPIO_MODE_IN, FLOATING_INPUT);
    usart_init(USART3, USART_DEFAULT_BAUD);
    /* enable system tick */
    systick_init(CPU_DEFAULT_FREQ/1000);

    while(1)
    {
      
    }

    return 0;
}