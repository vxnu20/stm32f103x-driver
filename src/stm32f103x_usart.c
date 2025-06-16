#include "stm32f103x_usart.h"

void usart_init(usart_regs* usart, unsigned long baud)
{
    /* set the baud rate */
    usart->BRR = baud;
    usart->CR1 |= (USART_CR1_EN_TE |USART_CR1_EN_RE | USART_CR1_EN_UE);
}

void usart_write(usart_regs* usart, char data)
{
    while(!(usart->SR & USART_SR_TC_SET)){ asm("nop"); }
    usart->DR = data;
}

void usart_write_string(usart_regs* usart, const char *str)
{
    while(*str)
    {
        usart_write(usart, *str++);
    }
}

char usart_read(usart_regs* usart)
{
    while(!(usart->SR & USART_SR_RXNE_SET)){ asm("nop"); }
    return usart->DR;
}
