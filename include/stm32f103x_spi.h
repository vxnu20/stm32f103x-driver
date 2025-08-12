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

/* structure for the config paramters */
typedef struct {
    spi_regs* spi;
}spi_config;

/* function prototypes */
void spi_init(spi_config);

#endif