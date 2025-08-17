#include "stm32f103x_spi.h"

void spi_init(spi_config config)
{
    /* clear and set the baud rate */
    config.spi->CR1 &= ~(0x38);
    config.spi->CR1 |= config.baud_rate << SPI_CR1_BR_SHIFT;

    /* set clock phase and clock polarity */
    config.spi->CR1 &= ~(0x3U);

    if(config.clock_phase)
    {
        config.spi->CR1 |= SPI_CR1_CPHA;
    }

    if(config.clock_polarity)
    {
        config.spi->CR1 |= SPI_CR1_CPOL;
    }
    
    /* keep it as full duplex */
    config.spi->CR1 &= ~SPI_CR1_RXONLY;

    /* clear and set the frame format */
    config.spi->CR1 &= ~(1<<SPI_CR1_LSBFIRST_SHIFT);
    config.spi->CR1 |= (config.frame_format<<SPI_CR1_LSBFIRST_SHIFT);

    /* set the master slave mode */
    config.spi->CR1 &= ~(1<<SPI_CR1_MSTR_SHIFT);
    config.spi->CR1 |= (config.mode<<SPI_CR1_MSTR_SHIFT);

    /* set the SPI frame format */
    /* set software slave management and internal slave select */
    config.spi->CR1 |= SPI_CR1_SSM;
    config.spi->CR1 |= SPI_CR1_SSI;

    /* enable spi */
    config.spi->CR1 |= SPI_CR1_SPE;
}

void spi_master_transmit(spi_regs* spi, uint8_t* data, uint16_t size)
{
    uint8_t index=0;
    while(index<size)
    {
        /* wait until the TX buffer is cleared */
        while(!(spi->SR & SPI_SR_TXE)){ asm("nop"); };

        spi->DR = data[index];
        
        index++;
    }
    /* wait until the TX buffer is cleared */
    while(!(spi->SR & SPI_SR_TXE)){ asm("nop"); };

    /* wait until the TX buffer is cleared */
    while(spi->SR & SPI_SR_BSY){ asm("nop"); };

    /* Clearing the OVR bit is done by a read operation on the SPI_DR register 
        followed by a read access to the SPI_SR register.*/
    (void)spi->DR;
    (void)spi->SR;
}

void spi_master_receive(spi_regs* spi, uint8_t* data,uint16_t size)
{
    while(size)
    {
        /* write an empty buffer */
        spi->DR = 0;

        /* wait until recieve flag is set */
        while(!(spi->SR & SPI_SR_RXNE)){ asm("nop"); };

        /* read the data */
        *data++ = spi->DR;
        size--;
    }
}

void spi_cs_enable(gpio_regs* gpio, uint8_t pin)
{
    gpio_pin_reset(gpio, pin);
}

void spi_cs_disable(gpio_regs* gpio, uint8_t pin)
{
    gpio_pin_set(gpio, pin);
}