/* required header files */
#include <stdio.h>

/* macros for timer */
#define AC_TIMER_BASE               (0x40012C00)  /* advanced control registers */
#define GN_TIMER_BASE               (0x40000000UL)  /* general purpose register */
#define TIM1_OFFSET                 (0UL)
#define TIM2_OFFSET                 (0UL)
#define TIM3_OFFSET                 (400UL)
#define TIM4_OFFSET                 (800UL)

#define TIM1                        ((timer_regs *) AC_TIMER_BASE + TIM1_OFFSET)
#define TIM2                        ((timer_regs *) GN_TIMER_BASE + TIM2_OFFSET)
#define TIM3                        ((timer_regs *) GN_TIMER_BASE + TIM3_OFFSET)
#define TIM4                        ((timer_regs *) GN_TIMER_BASE + TIM4_OFFSET)

/* structure to hold the registers */
typedef struct {
    volatile uint16_t CR1;      /* control register 1*/
    volatile uint16_t CR2;      /* control register 2*/
    volatile uint16_t SMCR;     /* slave mode control register */
    volatile uint16_t DIER;     /* DMA/interrupt enable register */
    volatile uint16_t SR;       /* status register */
    volatile uint16_t EGR;      /* event generation register */
    volatile uint16_t CCMR1;    /* capture/compare mode register 1 */
    volatile uint16_t CCMR2;    /* capture/compare mode register 2 */
    volatile uint16_t CCER;     /* capture/compare enable register */
    volatile uint16_t CNT;      /* counter */
    volatile uint16_t PSC;      /* prescalar */
    volatile uint16_t ARR;      /* auto reload register */
    volatile uint16_t RCR;      /* repetition counter register */
    volatile uint16_t CCR1;     /* capture/compare register 1 */
    volatile uint16_t CCR2;     /* capture/compare register 2 */
    volatile uint16_t CCR3;     /* capture/compare register 3 */
    volatile uint16_t CCR4;     /* capture/compare register 4 */
    volatile uint16_t BDTR;     /* break and dead-time register */
    volatile uint16_t DCR;      /* DMA control register */
    volatile uint16_t DMAR;     /* DMA address for full register */
}timer_regs;