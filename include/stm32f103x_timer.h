/* required header files */
#include <stdint.h>

#include "stm32f103x_rcc.h"

/* macros for timer */
#define AC_TIMER_BASE               (0x40012C00UL)  /* advanced control registers */
#define GN_TIMER_BASE               (0x40000000UL)  /* general purpose register */
#define TIM_CR1_CEN                 (1<<0)
#define TIM_SR_UF                   (1<<0)
#define TIM1_OFFSET                 (0x0UL)
#define TIM2_OFFSET                 (0x0UL)
#define TIM3_OFFSET                 (0x400UL)
#define TIM4_OFFSET                 (0x800UL)

/* default values */
#define TIM_DEFAULT_PRE_SCLAR       (7999UL) /* default pre-scalar value for 8MHz clock */
#define TIM_DEFAULT_AUTO_RELOAD     (999UL)  /* default auto reload value for 1 second */

/* hardware timers */
#define TIM1                        ((timer_regs *) (AC_TIMER_BASE + TIM1_OFFSET))
#define TIM2                        ((timer_regs *) (GN_TIMER_BASE + TIM2_OFFSET))
#define TIM3                        ((timer_regs *) (GN_TIMER_BASE + TIM3_OFFSET))
#define TIM4                        ((timer_regs *) (GN_TIMER_BASE + TIM4_OFFSET))

/* structure to hold the registers */
typedef struct {
    volatile uint32_t CR1;      /* control register 1*/
    volatile uint32_t CR2;      /* control register 2*/
    volatile uint32_t SMCR;     /* slave mode control register */
    volatile uint32_t DIER;     /* DMA/interrupt enable register */
    volatile uint32_t SR;       /* status register */
    volatile uint32_t EGR;      /* event generation register */
    volatile uint32_t CCMR1;    /* capture/compare mode register 1 */
    volatile uint32_t CCMR2;    /* capture/compare mode register 2 */
    volatile uint32_t CCER;     /* capture/compare enable register */
    volatile uint32_t CNT;      /* counter */
    volatile uint32_t PSC;      /* prescalar */
    volatile uint32_t ARR;      /* auto reload register */
    volatile uint32_t RCR;      /* repetition counter register */
    volatile uint32_t CCR1;     /* capture/compare register 1 */
    volatile uint32_t CCR2;     /* capture/compare register 2 */
    volatile uint32_t CCR3;     /* capture/compare register 3 */
    volatile uint32_t CCR4;     /* capture/compare register 4 */
    volatile uint32_t BDTR;     /* break and dead-time register */
    volatile uint32_t DCR;      /* DMA control register */
    volatile uint32_t DMAR;     /* DMA address for full register */
}timer_regs;

typedef struct {
    timer_regs* timer;
    uint16_t prescalar;
    uint16_t auto_reload;
    uint8_t enable_interrupt;
}timer_config;

/* function prototypes */
void timer_init(timer_config);
uint16_t timer_read_count(timer_regs*);