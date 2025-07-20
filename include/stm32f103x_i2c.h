#ifndef STM32F103X_I2C_H
#define STM32F103X_I2C_H

/* required header files for the i2c */
#include <stdint.h>

/* macros of i2c */
#define I2C_BASE_ADDR       (0x40005400UL)
#define I2C1_OFFSET         (0x0UL)
#define I2C2_OFFSET         (0x400UL)
#define I2C_CR1_PE_SET      (1<<0)
#define I2C_CR1_SWRST       (1<<15)


/* i2c peripherals*/
#define I2C1                ((i2c_regs *) (I2C_BASE_ADDR + I2C1_OFFSET))
#define I2C2                ((i2c_regs *) (I2C_BASE_ADDR + I2C2_OFFSET))

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
}i2c_config;

/* function prototypes */
void i2c_init(i2c_config);

#endif