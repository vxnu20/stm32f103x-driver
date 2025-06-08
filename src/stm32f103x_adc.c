#include "stm32f103x_adc.h"


void adc_init(adc_config config)
{
    /* enable the respective clock for ADC */
    if(config.adc == ADC1)
    {
        RCC->APB2ENR |= APB2ENR_ADC1;
    }
    else if(config.adc == ADC2)
    {
        RCC->APB2ENR |= APB2ENR_ADC2;
    }
    else
    {
        return;
    }
    /* enable adc module */
    config.adc->CR2 |= ADC_CR2_ADON_SET;

    /* set conversion mode */
    /* clear the conversion, by default single conversion */
    config.adc->CR2 &= ~(ADC_CR2_CONT_SET);
    if(config.conversion_mode == continuous_conversion)
    {
        config.adc->CR2 |= ADC_CR2_CONT_SET;
    }

    /* set the conversion sequence */
    adc_internal_set_sequence(config);

    /* set conversion sequence length */
    config.adc->SQR1 &= ~(7 << 20);
    config.adc->SQR1 |= ((config.no_of_channels-1) << 20);

    /* set adc sampling time*/
    adc_internal_set_sampling_time(config);

    /* select ext trigger as as swstart */
    config.adc->CR2 |= ADC_CR2_EXTSEL_SWSTART;
    /* enable external trigger */
    config.adc->CR2 |= ADC_CR2_EXTTRIG_EN;

    /* enable the calib registers */
    config.adc->CR2 |= ADC_CR2_RSTCAL_SET;
    /* wait until the calib is completed */
    while(config.adc->CR2 & ADC_CR2_RSTCAL_SET) {}

    /* start the calibration*/
    config.adc->CR2 |= ADC_CR2_CAL_SET;
    /* wait until the calib is completed */
    while(config.adc->CR2 & ADC_CR2_CAL_SET) {}

    /* start again */
    config.adc->CR2 |= ADC_CR2_ADON_SET;
}

void adc_start_conversion(adc_regs* adc)
{
    /* start adc conversion */
    adc->CR2 |= ADC_CR2_SWSTART_SET;
}

uint32_t adc_read_value(adc_regs* adc)
{
    /* wait until the conversion is completed */
    while(!(adc->SR & ADC_SR_EOC_SET)) { asm("nop"); }
    /* read the converted value */
    return adc->DR;
}

static void adc_internal_set_sequence(adc_config config)
{
    for(uint8_t i = 0; i < config.no_of_channels && i < 16; i++) {
        uint8_t reg_pos = i % 6;  // Position within register (0-5)
        uint32_t channel_bits = config.channel_config[i].channel << (reg_pos * 5);
        
        if(i < 6)
            config.adc->SQR3 |= channel_bits;
        else if(i < 12)
            config.adc->SQR2 |= channel_bits;
        else
            config.adc->SQR1 |= channel_bits;
    }
}

static void adc_internal_set_sampling_time(adc_config config)
{
    for(uint8_t i = 0; i<config.no_of_channels && i< 16; i++)
    {
        uint8_t ch = config.channel_config[i].channel;
        volatile uint32_t* smpr_reg = (ch <= 9) ? &config.adc->SMPR2 : &config.adc->SMPR1;
        uint8_t pos = (ch <=9 ) ? ch : (ch - 10);
        
        *smpr_reg |= (config.channel_config[i].sampling_time << (pos * 3));
    }
}