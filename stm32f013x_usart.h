/* required header files */
#include <stdint.h>
#include <stdio.h>

#include "stm32f103x_rcc.h"

/* macros */
#define USART1                  (( usart_regs *) 0x40013800UL)
#define USART_DEFAULT_BAUD      ((4<<4) | 5)    /* 115200 at default 8MHz */
#define USART_CR1_EN_TE         (1<<3)
#define USART_CR1_EN_UE         (1<<13)
#define USART_SR_TC_SET         (1<<6)         

/* registers */
typedef struct {
    volatile uint32_t SR;       /* status register */
    volatile uint32_t DR;       /* data register */
    volatile uint32_t BRR;      /* baud rate register */
    volatile uint32_t CR1;      /* control register */
    volatile uint32_t CR2;      /* control register */
    volatile uint32_t CR3;      /* control register */
    volatile uint32_t GPTR;     /* guard time and prescalar register */
} usart_regs;

/* function prototype */
void usart_init(usart_regs*, unsigned long);
void usart_write(usart_regs*, char);
void usart_write_string(usart_regs*, const char *);