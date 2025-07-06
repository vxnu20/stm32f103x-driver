#include "stm32f103x_gpio.h"
#include "stm32f103x_systick.h"
#include "stm32f103x_usart.h"
#include "stm32f103x_adc.h"
#include "stm32f103x_rcc.h"
#include "stm32f103x_dma.h"
#include "stm32f103x_timer.h"
#include <stdio.h>

void rcc_peripheral_test_init()
{
    /* enable clock for peripherals */

    // rcc_enable_adc_clock(ADC1);
    // rcc_enable_adc_clock(ADC2);
    rcc_enable_gpio_clock(GPIO_PORTA);
    // rcc_enable_gpio_clock(GPIO_PORTB);
    rcc_enable_gpio_clock(GPIO_PORTC);
    // rcc_enable_timer_clock(TIM1);
    // rcc_enable_timer_clock(TIM2);
    // rcc_enable_timer_clock(TIM3);
    // rcc_enable_timer_clock(TIM4);
    rcc_enable_usart_clock(USART1);

}

void user_led_test_init()
{
    /* onboard user led */
    gpio_set_mode(GPIO_PORTC, 13, GPIO_MODE_OUT2MHZ, GN_PUSH_PULL);
}

void usart_logging_test_init()
{
    /* uart1 for logging purpose */
    gpio_set_mode(GPIO_PORTA, 9, GPIO_MODE_OUT2MHZ, ALT_PUSH_PULL);
    gpio_set_mode(GPIO_PORTA, 10, GPIO_MODE_IN, FLOATING_INPUT);
    usart_init(USART1, USART_DEFAULT_BAUD);
    /* uart config end */
    /* usart dma config */
    usart_enable_rx_dma(USART1);
    usart_enable_tx_dma(USART1);
}

void adc_peripheral_test_init()
{
    /* adc config example */
    // gpio_set_mode(GPIO_PORTA, 0, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 1, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 2, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 3, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 4, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 5, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 6, GPIO_MODE_IN, ANALOG);
    // gpio_set_mode(GPIO_PORTA, 7, GPIO_MODE_IN, ANALOG);
    
    // adc_config config;
    // config.adc = ADC1;
    // config.conversion_mode = continuous_conversion;

    // config.channel_config[0].channel = channel0;
    // config.channel_config[0].sampling_time= adc_sampling239_5;

    // config.channel_config[1].channel = channel1;
    // config.channel_config[1].sampling_time= adc_sampling239_5;

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
    
    // config.no_of_channels = 2;

    // adc_init(config);
    // _delay(200);
    // adc_start_conversion(config.adc);

    /* adc config end */
}

void timer_peripheral_test_init()
{
    /* sample timer config for testing purpose */

    // gpio_set_mode(GPIO_PORTA, 8, GPIO_MODE_OUT10MHZ, ALT_PUSH_PULL);
    // gpio_set_mode(GPIO_PORTB, 7, GPIO_MODE_IN, FLOATING_INPUT);

    // timer_config config;
    // config.timer = TIM1;
    // config.prescalar = TIM_DEFAULT_PRE_SCLAR;
    // config.auto_reload = TIM_DEFAULT_AUTO_RELOAD;
    // timer_init(config);

    // /* timer channel config */
    // timer_channel_output_config out_config;
    // out_config.channel = t_channel1;
    // out_config.mode = t_toggle_mode;
    // timer_enable_output_compare(config.timer,out_config);
    // timer_start(config.timer);


    // timer_config s_config;
    // s_config.timer = TIM4;
    // s_config.prescalar = TIM_DEFAULT_PRE_SCLAR;
    // s_config.auto_reload = TIM_DEFAULT_AUTO_RELOAD;
    // timer_init(s_config);
    
    // timer_channel_input_config in_config;
    // in_config.channel = t_channel2;
    // in_config.prescalar = t_no_prescalar;
    // in_config.selection = t_channel_ic2_ti1;
    // in_config.filter    = no_filter;
    // timer_enable_input_capture(s_config.timer, in_config);
    // timer_start(s_config.timer);

    /* timer config end */
}

dma_config dconfig;
void dma_peripheral_test_init()
{
    dconfig.channel = 4;
    dconfig.direction = read_from_memory;
    dconfig.memory_increment = mem_inc_enabled;
    dconfig.destination = (uint32_t)&USART1->DR;
    dma_init(dconfig);
}

int main()
{
    // char buffer[20];

    /* enable system tick */
    systick_init(CPU_DEFAULT_FREQ/1000);

    rcc_peripheral_test_init();
    usart_logging_test_init();
    user_led_test_init();
    dma_peripheral_test_init();

    while(1)
    {
        
        // while(!(config.timer -> SR & TIM_SR_UF));
        gpio_pin_toggle(GPIO_PORTC,13);
        // config.timer -> SR &= ~TIM_SR_UF;
        // while(!(s_config.timer->SR & (1<<in_config.channel))){}
        // uint32_t value = adc_read_value(config.adc);
        // uint16_t value = s_config.timer->CCR3;
        // sprintf(buffer, "usart dma test\n",);
        _delay(400);
        uint8_t buffer[] = "usart dma test \n";
        // usart_write_string(USART1,buffer);
        dma_send_data(dconfig, buffer, 16);
    }

    return 0;
}