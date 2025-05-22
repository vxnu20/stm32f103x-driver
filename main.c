#include "stm32f103x_gpio.h"
#include "stm32f103x_clock.h"


int main()
{
    /* enable clock for PORT c*/
    RCC->APB2ENR |= (1<<4);
    
    /* blink example */
    GPIO_PORTC->CRH &= ~(0xFF << 20); // clearing Mode and CNF bits
    GPIO_PORTC->CRH |= (0x02 << 20); // setting the mode to output 
    /* keeping CNF as 00 */
    
    while(1)
    {
        GPIO_PORTC->ODR ^= (1<<13);
    }

    return 0;
}