#ifndef STM32F103X_SPI_H
#define STM32F103X_SPI_H

/* required header files */
#include <stdint.h>
#include <stm32f103x_gpio.h>

/* macros of spi */
#define SPI1_BASE_ADDR          (0x40013000UL)
#define SPI2_BASE_ADDR          (0x40003800UL)
#define SPI_CR1_MSTR_SHIFT      (2U)
#define SPI_CR1_BR_SHIFT        (3U)
#define SPI_CR1_LSBFIRST_SHIFT  (7U)
#define SPI_CR1_CPHA            (1<<0)
#define SPI_CR1_CPOL            (1<<1)
#define SPI_CR1_SPE             (1<<6)
#define SPI_CR1_SSI             (1<<8)
#define SPI_CR1_SSM             (1<<9)
#define SPI_CR1_RXONLY          (1<<10)
#define SPI_SR_RXNE             (1<<0)
#define SPI_SR_TXE              (1<<1)
#define SPI_SR_BSY              (1<<7)

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

/*frame format */
typedef enum {
    msb_first,
    lsb_first
}spi_frameformat;

/* spi mode */
typedef enum {
    slave_mode,
    master_mode
}spi_mode;

/* structure for the config paramters */
typedef struct {
    spi_regs* spi;
    spi_baud_rate baud_rate;
    uint8_t clock_polarity;
    uint8_t clock_phase;
    spi_frameformat frame_format;
    spi_mode mode;
}spi_config;


/* function prototypes */
void spi_init(spi_config);
void spi_master_transmit(spi_regs*, uint8_t*, uint16_t);
void spi_master_receive(spi_regs*, uint8_t*,uint16_t);
void spi_cs_enable(gpio_regs*, uint8_t);
void spi_cs_disable(gpio_regs*, uint8_t);

#endif