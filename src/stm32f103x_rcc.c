#include "stm32f103x_rcc.h"

void rcc_enable_gpio_clock(gpio_regs* gpio)
{
    /* if clock is enabled not needed to set again*/
    if(gpio == GPIO_PORTA && !(RCC->APB2ENR & APB2ENR_PORTA))
    {
        RCC->APB2ENR |= APB2ENR_PORTA;
    }
    else if(gpio == GPIO_PORTB && !(RCC->APB2ENR & APB2ENR_PORTB))
    {
        RCC->APB2ENR |= APB2ENR_PORTB;
    }
    else if(gpio == GPIO_PORTC && !(RCC->APB2ENR & APB2ENR_PORTC))
    {
        RCC->APB2ENR |= APB2ENR_PORTC;
    }
    else
    {
        return;
    }
}

void rcc_enable_usart_clock(usart_regs* usart)
{
    if(usart == USART1 && !(RCC->APB2ENR & APB2ENR_USART1))
    {
        RCC->APB2ENR |= APB2ENR_USART1;
    }
    else if(usart == USART2 && !(RCC->APB1ENR & APB1ENR_USART2))
    {
        RCC->APB1ENR |= APB1ENR_USART2;
    }
    else if(usart == USART3 && !(RCC->APB1ENR & APB1ENR_USART3))
    {
        RCC->APB1ENR |= APB1ENR_USART3;
    }
    else
    {
        return;
    }
}

void rcc_enable_adc_clock(adc_regs* adc)
{
    /* enable the respective clock for ADC */
    if(adc == ADC1)
    {
        RCC->APB2ENR |= APB2ENR_ADC1;
    }
    else if(adc == ADC2)
    {
        RCC->APB2ENR |= APB2ENR_ADC2;
    }
    else
    {
        return;
    }
}

void rcc_enable_timer_clock(timer_regs* timer)
{
    /* enable timer clock */
    if(timer == TIM1 && !(RCC->APB2ENR & APB2ENR_TIM1))
    {
        RCC->APB2ENR |= APB2ENR_TIM1;
    }
    else if(timer == TIM2 && !(RCC->APB1ENR & APB1ENR_TIM2))
    {
        RCC->APB1ENR |= APB1ENR_TIM2;
    }
    else if(timer == TIM3 && !(RCC->APB1ENR & APB1ENR_TIM3))
    {
        RCC->APB1ENR |= APB1ENR_TIM3;
    }
    else if(timer == TIM4 && !(RCC->APB1ENR & APB1ENR_TIM4))
    {
        RCC->APB1ENR |= APB1ENR_TIM4;
    }
    else
    {
        return;
    }
}

void rcc_enable_afio_clock()
{
    RCC->APB2ENR |= APB2ENR_AFIO;
}

void rcc_enable_dma_clock()
{
    if(!(RCC->AHBENR & AHBENR_DMA))
        RCC->AHBENR |= AHBENR_DMA;
}

void rcc_enable_i2c_clock(i2c_regs* i2c)
{
    if(i2c == I2C1 && !(RCC->APB1ENR & APB1ENR_I2C1))
    {
        RCC->APB1ENR |= APB1ENR_I2C1;
    }
    else if(i2c == I2C2 && !(RCC->APB1ENR & APB1ENR_I2C2))
    {
        RCC->APB1ENR |= APB1ENR_I2C2;
    }
    else
    {
        return;
    }
}

void rcc_enable_spi_clock(spi_regs* spi)
{
    if(spi == SPI1 && !(RCC->APB2ENR & APB2ENR_SPI1))
    {
        RCC->APB2ENR |= APB2ENR_SPI1;
    }
    else if(spi == SPI2 && !(RCC->APB1ENR & APB1ENR_SPI2))
    {
        RCC->APB1ENR |= APB1ENR_SPI2;
    }
    else
    {
        return;
    }
}

void rcc_sysclk_init(const clock_config* config)
{
    flash_wait_state wait_state;

    /* enable HSE */
    if(config->source == CLOCK_SRC_HSE || config->source == CLOCK_SRC_PLL)
    {
        RCC->CR |= RCC_CR_HSEON;
        /* wait until the clock is ready */
        while(!(RCC->CR&RCC_CR_HSERDY)){ asm("nop"); }
    }
    /* configure flash frequency */
    if(config->pll_mul > PLL_MUL_6)
    {
        wait_state = FLASH_LATENCY_2;
    }
    else
    {
        wait_state = FLASH_LATENCY_1;
    }

    flash_set_wait_state(wait_state);

    /* clear all the prescalar values */
    RCC->CFGR &= ~(RCC_CFGR_HPRE_MASK | RCC_CFGR_PPRE1_MASK | RCC_CFGR_PPRE2_MASK);
    /* configure the prescalar value */
    RCC->CFGR |= (config->ahb_prescaler | config->apb1_prescaler | config->apb2_prescaler);

    if(config->source == CLOCK_SRC_PLL)
    {
        /* clear and configure the pll if selected */
        RCC->CFGR &= ~(RCC_CFGR_PLLSRC);
        RCC->CFGR &= ~(RCC_CFGR_PLLMUL_MASK);

        if(config->hse_freq > 0)
        {
            RCC->CFGR |= RCC_CFGR_PLLSRC;
        }
        RCC->CFGR |= ((config->pll_mul-2) << RCC_CFGR_PLLMUL_SHIFT);
        
        /* enable PLL and wait */
        RCC->CR |= RCC_CR_PLLON;
        while(!(RCC->CR&RCC_CR_PLLRDY)){ asm("nop"); }
    }
    /* select the system clock */
    /* clear the clock selection */
    RCC->CFGR &= ~RCC_CFGR_SW_MASK;
    if (config->source == CLOCK_SRC_HSI) 
    {
        RCC->CFGR |= CLOCK_SRC_HSI;
    } 
    else if (config->source == CLOCK_SRC_HSE) 
    {
        RCC->CFGR |= CLOCK_SRC_HSE;
    } 
    else 
    {
        RCC->CFGR |= CLOCK_SRC_PLL;
    }
    while (((RCC->CFGR >> 2) & 0x3) != config->source);

}

void rcc_enable_lsi_clock()
{
    /* enable the LSE clock */
    RCC->CSR |= RCC_CSR_LSION;
    /* wait unitil the clock is ready */
    while(!(RCC->CSR & RCC_CSR_LSIRDY)) {asm("nop");}
}

void rcc_disable_lsi_clock()
{
    /* enable the LSE clock */
    RCC->CSR &= ~RCC_CSR_LSION;
}

rcc_reset_reason_t rcc_get_reset_reason()
{
    rcc_reset_reason_t reset_reason = PORRSTF;
    struct {
        uint32_t flag;
        rcc_reset_reason_t reason;
    } reset_map[] = {
        {RCC_CSR_PINRSTF, PINRSTF},
        {RCC_CSR_PORRSTF, PORRSTF},
        {RCC_CSR_SFTRSTF, SFTRSTF},
        {RCC_CSR_IWDGRSTF, IWDGRSTF},
        {RCC_CSR_WWDGRSTF, WWDGRSTF},
        {RCC_CSR_LPWRRSTF, LPWRRSTF}
    };

    for (unsigned i = 0; i < sizeof(reset_map)/sizeof(reset_map[0]); i++) {
        if (RCC->CSR & reset_map[i].flag) {
            
            reset_reason = reset_map[i].reason;
        }
    }
    /* clear the reason */
    RCC->CSR |= RCC_CSR_RMVF;
    return reset_reason; 
}

void rcc_enable_wwdg_clock()
{
    if(!(RCC->APB1ENR & APB1ENR_WWDGEN))
        RCC->APB1ENR |= APB1ENR_WWDGEN;
}