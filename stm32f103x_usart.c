#include "stm32f013x_usart.h"

void usart_init(usart_regs* usart, unsigned long baud)
{
    if(usart == USART1)
    {
        /* enable clock access to USART1 */
        RCC->APB2ENR |= APB2ENR_USART1;
    }
    /* set the baud rate */
    usart->BRR = baud;
    usart->CR1 |= (USART_CR1_EN_TE | USART_CR1_EN_UE);
}

void usart_write(usart_regs* usart, char data)
{
    while(!(usart->SR && USART_SR_TC_SET)){ asm("nop"); }
    usart->DR = data;
}

void usart_write_string(usart_regs* usart, const char *str)
{
    while(*str)
    {
        usart_write(usart, *str++);
    }
}
