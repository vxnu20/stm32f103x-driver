#ifndef STM32F103X_TIMER_H
#define STM32F103X_TIMER_H

/* required header files */
#include <stdint.h>

/* macros for timer */
#define AC_TIMER_BASE               (0x40012C00UL)  /* advanced control registers */
#define GN_TIMER_BASE               (0x40000000UL)  /* general purpose register */
#define TIM_CR1_CEN                 (1<<0)
#define TIM_SR_UF                   (1<<0)
#define TIM1_OFFSET                 (0x0UL)
#define TIM2_OFFSET                 (0x0UL)
#define TIM3_OFFSET                 (0x400UL)
#define TIM4_OFFSET                 (0x800UL)
#define TIMx_CCMR_CCS_CLEAR         (0x03UL)

/* default values */
#define TIM_DEFAULT_PRE_SCLAR       (7999UL) /* default pre-scalar value for 8MHz clock */
#define TIM_DEFAULT_AUTO_RELOAD     (999UL)  /* default auto reload value for 1 second */
#define TIM_MAX_CHANNELS            (4UL)

/* hardware timers */
#define TIM1                        ((timer_regs *) (AC_TIMER_BASE + TIM1_OFFSET))
#define TIM2                        ((timer_regs *) (GN_TIMER_BASE + TIM2_OFFSET))
#define TIM3                        ((timer_regs *) (GN_TIMER_BASE + TIM3_OFFSET))
#define TIM4                        ((timer_regs *) (GN_TIMER_BASE + TIM4_OFFSET))

/* timer channels */
typedef enum {
    t_channel1,
    t_channel2,
    t_channel3,
    t_channel4
}timer_channel;

typedef enum {
    frozen_mode,            /* Generate timing interrupts without affecting output pins. */
    set_active_on_match,    /* When counter reaches the compare value, output goes HIGH and stays HIGH. */
    set_inactive_on_match,  /* When counter reaches compare value, output goes LOW and stays LOW. */
    toggle_mode,            /* Output flips state each time counter matches compare value.*/
    force_inactive,         /* Output is immediately forced LOW regardless of counter value.*/
    force_active,           /* Output is immediately forced HIGH regardless of counter value.*/
    pwm_mode_one,           /* Output is HIGH when counter < compare value & Output is LOW when counter ≥ compare value.*/
    pwm_mode_two            /* Output is LOW when counter < compare value & Output is HIGH when counter ≥ compare value*/
}timer_channel_output_mode;

typedef enum {
    /* 0- channel is configured as output */
    channel_ic2_ti1 = 0x01; /* IC2 is mapped on TI2 */
    channel_i2c_ti2;        /* IC2 is mapped on TI1 */
    channel_i2c_trc;        /*  IC2 is mapped on TRC*/
}timer_input_capture_selection;

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

/* channel output config */
typedef struct {
    timer_channel channel;
    timer_channel_output_mode mode;
}timer_channel_output_config;

/* channel input config */
typedef struct {
    timer_channel channel;
    timer_input_capture_selection selection;
}timer_channel_input_config;

/* init values */
typedef struct {
    timer_regs* timer;
    uint16_t prescalar;
    uint16_t auto_reload;
}timer_config;

/* function prototypes */
void timer_init(timer_config);
void timer_start(timer_regs*);
void timer_stop(timer_regs*);
uint16_t timer_read_count(timer_regs*);
void timer_enable_output_compare(timer_regs*, timer_channel_output_config);
void timer_enable_input_capure(timer_regs*);

#endif // STM32F103X_TIMER_H