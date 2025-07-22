#include "stm32f103x_i2c.h"


void i2c_init(i2c_config config)
{
    /* enter reset mode - required for reinit after lockup */
    config.i2c->CR1 |= I2C_CR1_SWRST;
    /* clear the reset mode */
    config.i2c->CR1 &= ~I2C_CR1_SWRST; 
    /* set the frequency */
    config.i2c->CR2 |= config.pfrequency << I2C_CR2_FREQ_POS;
    /* set the clock speed, SM or FM */
    config.i2c->CCR |= config.clock_frequency << I2C_CCR_CCR_POS;
    /* set the raise time */
    config.i2c->TRISE |= config.rise_time << I2C_TRISE_TRISE_POS;
    /* enable I2C peripheral */
    config.i2c->CR1 |= I2C_CR1_PE;
}

uint8_t i2c_read(i2c_config config)
{

}