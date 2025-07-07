#ifndef STM32F103X_USART_H
#define STM32F103X_USART_H

/* required header files */
#include <stdint.h>
#include <stdio.h>

/* macros */
#define USART1                  (( usart_regs *) 0x40013800UL)
#define USART_BASE_ADDR         (0x40004400UL)
#define USART2_OFFSET           (0UL)
#define USART3_OFFSET           (0x400UL)
#define USART2                  (( usart_regs *) (USART_BASE_ADDR+USART2_OFFSET))
#define USART3                  (( usart_regs *) (USART_BASE_ADDR+USART3_OFFSET))

#define USART_DEFAULT_BAUD      ((4<<4) | 5)    /* 115200 at default 8MHz */
#define USART_CR1_EN_RE         (1<<2)
#define USART_CR1_EN_TE         (1<<3)
#define USART_CR1_EN_UE         (1<<13)
#define USART_CR3_EN_DMAR       (1<<6)
#define USART_CR3_EN_DMAT       (1<<7)
#define USART_SR_RXNE_SET       (1<<5) 
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
char usart_read(usart_regs*);
void usart_enable_rx_dma(usart_regs*);
void usart_enable_tx_dma(usart_regs*);

#endif // STM32F103X_USART_H