#include <stdint.h>
#include "stm32f103x_gpio.h"

void gpio_set_mode(gpio_regs* gpio, uint8_t pin, uint8_t mode, uint8_t cnf)
{
    volatile uint32_t* reg = (pin < 8) ? &gpio->CRL : &gpio->CRH;
    pin = (pin < 8) ? pin : pin - 8;
    
    *reg &= ~(0xFF << (pin * 4));       /* Clear both CNF and mode bits */
    *reg |= (mode << (pin * 4));        /* Set the mode bit */
    *reg |= (cnf << ((pin * 4) + 2));   /* Set the CNF bit */
}

void gpio_pin_toggle(gpio_regs* gpio, uint8_t pin)
{
    gpio->ODR ^= (1<<pin);
}