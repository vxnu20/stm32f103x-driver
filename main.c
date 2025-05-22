#include "stm32f103x_gpio.h"
#include "stm32f103x_clock.h"


int main()
{
    /* enable clock for PORT c*/
    RCC->APB2ENR |= (1<<4);
    
    gpio_set_mode(GPIO_PORTC, 13, GPIO_MODE_OUT2MHZ, GN_PUSH_PULL);
    
    while(1)
    {
        gpio_pin_toggle(GPIO_PORTC, 13);
    }

    return 0;
}