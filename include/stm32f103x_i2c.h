#ifndef STM32F103X_I2C_H
#define STM32F103X_I2C_H

/* required header files for the i2c */
#include <stdint.h>

/* macros of i2c */
#define I2C_BASE_ADDR           (0x40005400UL)
#define I2C1_OFFSET             (0x0UL)
#define I2C2_OFFSET             (0x400UL)
#define I2C_CR1_PE              (1<<0)
#define I2C_CR1_START           (1<<8)
#define I2C_CR1_STOP            (1<<9)
#define I2C_CR1_ACK             (1<<10)
#define I2C_CR1_SWRST           (1<<15)
#define I2C_SR1_SB              (1<<0)
#define I2C_SR1_ADDR            (1<<1)
#define I2C_SR1_BTF             (1<<2)
#define I2C_SR1_RXNE            (1<<6)
#define I2C_SR1_TXE             (1<<7)
#define I2C_SR2_BUSY            (1<<2)
#define I2C_CR2_FREQ_POS        (0UL)
#define I2C_DEFAULT_FREQ_MHZ    (8UL) /* used for config */
#define I2C_CCR_CCR_POS         (0UL)
#define I2C_TRISE_TRISE_POS     (0UL)

/* i2c peripherals*/
#define I2C1                    ((i2c_regs *) (I2C_BASE_ADDR + I2C1_OFFSET))
#define I2C2                    ((i2c_regs *) (I2C_BASE_ADDR + I2C2_OFFSET))

/* structure for the i2c registers */
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
}i2c_regs;

/* i2c config paramters */
typedef struct {
    i2c_regs* i2c;
    /* freq in mhz */
    uint8_t pfrequency;
    uint8_t ccr_value;
    uint8_t rise_time;
}i2c_config;

/* function prototypes */
void i2c_init(i2c_config);
void i2c_master_read(i2c_regs*, uint8_t, uint8_t, uint8_t, uint8_t*);
void i2c_master_write(i2c_regs*, uint8_t, uint8_t, uint8_t, uint8_t*);
void i2c_master_read_byte(i2c_regs*, uint8_t, uint8_t,uint8_t*);
void i2c_master_write_byte(i2c_regs*, uint8_t, uint8_t,uint8_t*);

#endif