#include "stm32f103x_gpio.h"
#include "stm32f103x_rcc.h"


int main()
{
    /* enable clock for PORT c*/
    RCC->APB2ENR |= APB2ENR_PORTC;
    RCC->APB2ENR |= APB2ENR_PORTB;
    
    gpio_set_mode(GPIO_PORTC, 13, GPIO_MODE_OUT2MHZ, GN_PUSH_PULL);
    gpio_set_mode(GPIO_PORTB, 5, GPIO_MODE_IN, IN_PULLUP_PULLOUT);
    
    while(1)
    {
        if(gpio_pin_read(GPIO_PORTB,5)){
            gpio_pin_set(GPIO_PORTC,13);
        }else{
            gpio_pin_reset(GPIO_PORTC,13);
        }
    }

    return 0;
}