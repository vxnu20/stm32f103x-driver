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

uint8_t i2c_master_read(i2c_regs* i2c, uint8_t s_addr, uint8_t m_addr, uint8_t no_of_bytes,uint8_t* data)
{
    /* wait until the busy state */
    while(i2c->SR2 & I2C_SR2_BUSY){ asm("nop"); }

    /* generate a start condition */
    i2c->CR1 |= I2C_CR1_START;

    /* wait until the start bit flag is set */
    while(!(i2c->SR1 & I2C_SR1_SB)){ asm("nop"); }

    /* transmit slave address + write */
    /* msb is sending first 0( write) + address */
    i2c->DR = s_addr<<1;

    /* wait until the address flag is set */
    while(!(i2c->SR1 & I2C_SR1_ADDR)){ asm("nop"); }

    /* clear the address flag */
    /* just reading the register will clear the register */
    (void)i2c->SR2;

    /* wait until the transmitter empty */
    while(!(i2c->SR1 & I2C_SR1_TXE)){ asm("nop"); }

    /* send memory address */
    i2c->DR = m_addr;

    /* wait until the transmitter empty */
    while(!(i2c->SR1 & I2C_SR1_TXE)){ asm("nop"); }

    /* generate a restart */
    i2c->CR1 |= I2C_CR1_START;

    /* wait until the start bit flag is set */
    while(!(i2c->SR1 & I2C_SR1_SB)){ asm("nop"); }

    /* transmit slave adderss + read */
    i2c->DR = (s_addr << 1)|1;

    /* wait until the address flag is set */
    while(!(i2c->SR1 & I2C_SR1_ADDR)){ asm("nop"); }

    /* clear the address flag */
    (void)i2c->SR2;

    /* enable the acknowledge */
    i2c->CR1 |= I2C_CR1_ACK;
    
    /* read the data */
    while(no_of_bytes > 0U)
    {
        if(no_of_bytes==1)
        {
            /* disable acknowledge */
            i2c->CR1 &= ~I2C_CR1_ACK;

            /* generate a stop condition */
            i2c->CR1 |= I2C_CR1_STOP;

            /* wait until the recieve flag is set */
            while(!(i2c->SR1 & I2C_SR1_RXNE)){ asm("nop"); }

            /* read the data */
            (*data++) = i2c->DR;
            break;
        }
        else
        {
            /* wait until the recieve flag is set */
            while(!(i2c->SR1 & I2C_SR1_RXNE)){ asm("nop"); }

            /* read the data */
            (*data++) = i2c->DR;

            no_of_bytes--;
        }
    }
}

uint8_t i2c_master_write(i2c_regs* i2c, uint8_t s_addr, uint8_t m_addr, uint8_t no_of_bytes,uint8_t* data)
{
    /* wait until the bus not to be busy */
    while(i2c->SR2 & I2C_SR2_BUSY){ asm("nop"); }

    /* generate a start condition */
    i2c->CR1 |= I2C_CR1_START;

    /* wait for the start flag to set */
    while(!(i2c->SR1 & I2C_SR1_SB)){ asm("nop"); }

    /* transmit the slave address + write */
    i2c->DR = s_addr<<1;

    /* wait until the address flag is set */
    while(!(i2c->SR1 & I2C_SR1_ADDR)){ asm("nop"); }

    /* clear the address flag by reading the register */
    (void)i2c->SR2;

    /* wait until the data register is empty - wait for the Tx flag set*/
    while(!(i2c->SR1 & I2C_SR1_TXE)){ asm("nop"); }

    /* send the memory adderss */
    i2c->DR = m_addr;

    /* read the value */
    for(int i=0; i< no_of_bytes; i++)
    {
        /* wait until the data register is empty - wait for the Tx flag set*/
        while(!(i2c->SR1 & I2C_SR1_TXE)){ asm("nop"); }

        /* write the next byte */
        i2c->DR = (*data++);
    }
    /* wait until the byte transfer is finished */
    while(!(i2c->SR1 & I2C_SR1_BTF)){ asm("nop"); }

    /* generate a stop condition */
    i2c->CR1 |= I2C_CR1_STOP;
}