#ifndef STM32F103X_RCC_H
#define STM32F103X_RCC_H

/* required header files for rcc */
#include "stm32f103x_gpio.h"
#include "stm32f103x_usart.h"
#include "stm32f103x_adc.h"
#include "stm32f103x_timer.h"
#include "stm32f103x_afio.h"
#include "stm32f103x_i2c.h"
#include "stm32f103x_spi.h"
#include "stm32f103x_flash.h"

/* clock specific macros */
#define CPU_DEFAULT_FREQ       (8000000UL)

/* macros for reset & clock control RCC*/
#define RCC_BASE_ADDR           (0x40021000UL)
#define RCC                     ((rcc_regs *) RCC_BASE_ADDR)
#define RCC_CFGR_PLLSRC         (1<<16)
#define RCC_CR_HSEON            (1<<16)
#define RCC_CR_HSERDY           (1<<17)
#define RCC_CR_PLLON            (1<<24)
#define RCC_CR_PLLRDY           (1<<25)
#define RCC_CFGR_HPRE_MASK      (0xF0)
#define RCC_CFGR_PPRE1_MASK     (0x700)
#define RCC_CFGR_PPRE2_MASK     (0x3800)
#define RCC_CFGR_PLLMUL_MASK    (0x3C0000U)
#define RCC_CFGR_PLLMUL_SHIFT   (18)
#define RCC_CFGR_SW_MASK        (0x3U)


/* macros for enable APB1, APB2 and AHB bits */
#define APB2ENR_AFIO            (1<<0)
#define APB2ENR_PORTA           (1<<2)
#define APB2ENR_PORTB           (1<<3)
#define APB2ENR_PORTC           (1<<4)
#define APB2ENR_ADC1            (1<<9)
#define APB2ENR_ADC2            (1<<10)
#define APB2ENR_TIM1            (1<<11)
#define APB2ENR_SPI1            (1<<12)
#define APB2ENR_USART1          (1<<14)
#define APB1ENR_TIM2            (1<<0)
#define APB1ENR_TIM3            (1<<1)
#define APB1ENR_TIM4            (1<<2)
#define APB1ENR_SPI2            (1<<14)
#define APB1ENR_USART2          (1<<17)
#define APB1ENR_USART3          (1<<18)
#define APB1ENR_I2C1            (1<<21)
#define APB1ENR_I2C2            (1<<22)
#define AHBENR_DMA              (1<<0)

typedef struct {
    volatile uint32_t CR;               /* clock control register */
    volatile uint32_t CFGR;             /* clock configuration register */
    volatile uint32_t CIR;              /* clock interrupt register */
    volatile uint32_t APB2RSTR;         /* APB2 reset register */
    volatile uint32_t APB1RSTR;         /* APB1 reset register */
    volatile uint32_t AHBENR;           /* AHB clock enable register */
    volatile uint32_t APB2ENR;          /* APB2 clock enable register */
    volatile uint32_t APB1ENR;          /* APB1 clock enable register */
    volatile uint32_t BDCR;             /* backup domain control register */
    volatile uint32_t CSR;              /* control status register */ 
}rcc_regs;

typedef enum {
    CLOCK_SRC_HSI = 0,
    CLOCK_SRC_HSE,
    CLOCK_SRC_PLL
} clock_source_t;

typedef enum {
    AHB_DIV1   = (0x0 << 4),   // HPRE bits = 0000
    AHB_DIV2   = (0x8 << 4),   // HPRE bits = 1000
    AHB_DIV4   = (0x9 << 4),
    AHB_DIV8   = (0xA << 4),
    AHB_DIV16  = (0xB << 4),
    AHB_DIV64  = (0xC << 4),
    AHB_DIV128 = (0xD << 4),
    AHB_DIV256 = (0xE << 4),
    AHB_DIV512 = (0xF << 4),
} ahb_prescaler_t;

typedef enum {
    APB1_DIV1  = (0x0 << 8),   // PPRE1 or PPRE2 bits = 000
    APB1_DIV2  = (0x4 << 8),   // 100
    APB1_DIV4  = (0x5 << 8),   // 101
    APB1_DIV8  = (0x6 << 8),   // 110
    APB1_DIV16 = (0x7 << 8),   // 111
} apb1_prescaler_t;

typedef enum {
    APB2_DIV1  = (0x0 << 11),   // PPRE1 or PPRE2 bits = 000
    APB2_DIV2  = (0x4 << 11),   // 100
    APB2_DIV4  = (0x5 << 11),   // 101
    APB2_DIV8  = (0x6 << 11),   // 110
    APB2_DIV16 = (0x7 << 11),   // 111
} apb2_prescaler_t;

typedef enum {
    PLL_MUL_2  = 2,
    PLL_MUL_3  = 3,
    PLL_MUL_4  = 4,
    PLL_MUL_5  = 5,
    PLL_MUL_6  = 6,
    PLL_MUL_7  = 7,
    PLL_MUL_8  = 8,
    PLL_MUL_9  = 9,
    PLL_MUL_10 = 10,
    PLL_MUL_11 = 11,
    PLL_MUL_12 = 12,
    PLL_MUL_13 = 13,
    PLL_MUL_14 = 14,
    PLL_MUL_15 = 15,
    PLL_MUL_16 = 16
} pll_mul_t;

typedef struct {
    clock_source_t source;
    uint32_t hse_freq;      
    pll_mul_t pll_mul;        
    ahb_prescaler_t ahb_prescaler; 
    apb1_prescaler_t apb1_prescaler;
    apb2_prescaler_t apb2_prescaler;
} clock_config;

// peripheral clock function prototypes
void rcc_enable_gpio_clock(gpio_regs*);
void rcc_enable_usart_clock(usart_regs*);
void rcc_enable_adc_clock(adc_regs*);
void rcc_enable_timer_clock(timer_regs*);
void rcc_enable_afio_clock();
void rcc_enable_dma_clock();
void rcc_enable_i2c_clock(i2c_regs*);
void rcc_enable_spi_clock(spi_regs*);
// system clock config function prototypes
void rcc_sysclk_init(const clock_config*);

#endif // STM32F103X_RCC_H