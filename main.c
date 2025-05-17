#include "stm32f103x_gpio.h"
#include "stm32f103x_clock.h"


int main()
{
    /* enable clock for PORT c*/
    RCC_APB2ENR_BASE |= (1<<4);
    
    /* blink example */
    GPIO_PORTC_CRH_REG &= ~(0xFF << 20); // clearing Mode and CNF bits
    GPIO_PORTC_CRH_REG |= (0x02 << 20); // setting the mode to output 
    /* keeping CNF as 00 */
    
    while(1)
    {
        GPIO_PORTC_ODR_REG ^= (1<<13);
    }

    return 0;
}