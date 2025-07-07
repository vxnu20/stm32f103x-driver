#ifndef STM32F103X_RCC_H
#define STM32F103X_RCC_H

/* required header files for rcc */
#include "stm32f103x_gpio.h"
#include "stm32f103x_usart.h"
#include "stm32f103x_adc.h"
#include "stm32f103x_timer.h"
#include "stm32f103x_afio.h"

/* clock specific macros */
#define CPU_DEFAULT_FREQ       (8000000UL)

/* macros for reset & clock control RCC*/
#define RCC_BASE_ADDR       (0x40021000UL)
#define RCC                 ((rcc_regs *) RCC_BASE_ADDR)

/* macros for enable APB1, APB2 and AHB bits */
#define APB2ENR_AFIO        (1<<0)
#define APB2ENR_PORTA       (1<<2)
#define APB2ENR_PORTB       (1<<3)
#define APB2ENR_PORTC       (1<<4)
#define APB2ENR_ADC1        (1<<9)
#define APB2ENR_ADC2        (1<<10)
#define APB2ENR_TIM1        (1<<11)
#define APB2ENR_USART1      (1<<14)
#define APB1ENR_TIM2        (1<<0)
#define APB1ENR_TIM3        (1<<1)
#define APB1ENR_TIM4        (1<<2)
#define APB1ENR_USART2      (1<<17)
#define APB1ENR_USART3      (1<<18)
#define AHBENR_DMA          (1<<0)

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

// function prototypes
void rcc_enable_gpio_clock(gpio_regs*);
void rcc_enable_usart_clock(usart_regs*);
void rcc_enable_adc_clock(adc_regs*);
void rcc_enable_timer_clock(timer_regs*);
void rcc_enable_afio_clock();
void rcc_enable_dma_clock();

#endif // STM32F103X_RCC_H