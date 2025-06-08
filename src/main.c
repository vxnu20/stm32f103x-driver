#include "stm32f103x_gpio.h"
#include "stm32f103x_systick.h"
#include "stm32f013x_usart.h"
#include "stm32f103x_clock.h"
#include "stm32f103x_adc.h"
#include <stdio.h>


int main()
{
    // char buffer[20];

    /* enable clock for PORT c*/
    RCC->APB2ENR |= APB2ENR_PORTC;
    RCC->APB2ENR |= APB2ENR_PORTA;
    
    /* onboard user led */
    gpio_set_mode(GPIO_PORTC, 13, GPIO_MODE_OUT2MHZ, GN_PUSH_PULL);
    
    /* uart1 for logging purpose */
    gpio_set_mode(GPIO_PORTA, 9, GPIO_MODE_OUT2MHZ, ALT_PUSH_PULL);
    gpio_set_mode(GPIO_PORTA, 10, GPIO_MODE_IN, FLOATING_INPUT);
    usart_init(USART1, USART_DEFAULT_BAUD);

    /* enable system tick */
    systick_init(CPU_DEFAULT_FREQ/1000);

    /* adc config example */
    gpio_set_mode(GPIO_PORTA, 0, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 1, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 2, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 3, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 4, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 5, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 6, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 7, GPIO_MODE_IN, ANALOG);
    
    adc_config config;
    config.adc = ADC1;
    config.conversion_mode = continuous_conversion;

    config.channel_config[0].channel = channel0;
    config.channel_config[0].sampling_time= adc_sampling239_5;

    config.channel_config[1].channel = channel1;
    config.channel_config[1].sampling_time= adc_sampling239_5;

    // config.channel_config[0].channel = channel2;
    // config.channel_config[0].sampling_time = adc_sampling239_5;

    // config.channel_config[0].channel = channel3;
    // config.channel_config[0].sampling_time = adc_sampling239_5;

    // config.channel_config[0].channel = channel4;
    // config.channel_config[0].sampling_time = adc_sampling71_5;

    // config.channel_config[0].channel = channel5;
    // config.channel_config[0].sampling_time = adc_sampling71_5;

    // config.channel_config[0].channel = channel6;
    // config.channel_config[0].sampling_time = adc_sampling71_5;

    // config.channel_config[0].channel = channel7;
    // config.channel_config[0].sampling_time = adc_sampling71_5;
    
    config.no_of_channels = 2;

    adc_init(config);
    _delay(200);
    adc_start_conversion(config.adc);

    /* adc config end */
    while(1)
    {
        
        _delay(200);
        uint32_t value = adc_read_value(config.adc);
        // sprintf(buffer, "adc value -> %d \n", value);
        // usart_write_string(USART1,buffer);
        _delay(200);
    }

    return 0;
}