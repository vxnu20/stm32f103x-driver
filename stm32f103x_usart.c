#include "stm32f013x_usart.h"

void usart_init(usart_regs* usart, unsigned long baud)
{
    if(usart == USART1)
    {
        /* enable clock access to USART1 */
        RCC->APB2ENR |= APB2ENR_USART1;
    }
    else if(usart == USART2)
    {
        RCC->APB1ENR |= APB1ENR_USART2;
    }
    else if(usart == USART3)
    {
        RCC->APB1ENR |= APB1ENR_USART3;
    }
    else
    {
        return;
    }

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
