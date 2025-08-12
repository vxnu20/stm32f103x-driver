#ifndef STM32F103X_SPI_H
#define STM32F103X_SPI_H

/* required header files */
#include <stdint.h>

/* macros of spi */
#define SPI1_BASE_ADDR      (0x40013000UL)
#define SPI2_BASE_ADDR      (0x40003800UL)

/* spi peripherals */
#define SPI1        ((spi_regs*) SPI1_BASE_ADDR)
#define SPI2        ((spi_regs*) SPI2_BASE_ADDR)

/* structure for spi registers */
typedef struct {
    volatile uint32_t CR1;      /* control register 1 */
    volatile uint32_t CR2;      /* control register 2 */
    volatile uint32_t SR;       /* status register */
    volatile uint32_t DR;       /* data register 2 */
    volatile uint32_t CRCPR;    /* CRC polynomial register */
    volatile uint32_t RXCRCR;   /* Rx CRC register */
    volatile uint32_t TXCRCR;   /* Tx CRC register */
    volatile uint32_t I2SCFGR;  /* I2S config register */
    volatile uint32_t I2SPR;    /* I2S pre-scalar register */   
}spi_regs;

typedef enum {
    /* pclock divided by prescalar */
    pclk_2 = 0x00,
    pclk_4,
    pclk_8,
    pclk_16,
    pclk_32,
    pclk_64,
    pclk_128,
    pclk_256
}spi_baud_rate;

/* structure for the config paramters */
typedef struct {
    spi_regs* spi;
    spi_baud_rate baud_rate;
    uint8_t clock_polarity;
    uint8_t clock_phase;
}spi_config;


/* function prototypes */
void spi_init(spi_config);

#endif