#include "stm32f103x_gpio.h"
#include "stm32f103x_systick.h"
#include "stm32f103x_usart.h"
#include "stm32f103x_adc.h"
#include "stm32f103x_rcc.h"
#include "stm32f103x_dma.h"
#include "stm32f103x_timer.h"
#include "stm32f103x_wdg.h"
#include <stdio.h>

void rcc_peripheral_test_init()
{
    /* enable clock for peripherals */

    // rcc_enable_adc_clock(ADC1);
    // rcc_enable_adc_clock(ADC2);
    rcc_enable_gpio_clock(GPIO_PORTA);
    rcc_enable_gpio_clock(GPIO_PORTB);
    rcc_enable_gpio_clock(GPIO_PORTC);
    // rcc_enable_timer_clock(TIM1);
    // rcc_enable_timer_clock(TIM2);
    // rcc_enable_timer_clock(TIM3);
    // rcc_enable_timer_clock(TIM4);
    rcc_enable_usart_clock(USART1);
    // rcc_enable_usart_clock(USART2);
    // rcc_enable_i2c_clock(I2C1);
    rcc_enable_spi_clock(SPI1);
    rcc_enable_wwdg_clock();
    // rcc_enable_lsi_clock();
    // rcc_disable_lsi_clock();
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
    // usart_enable_rx_dma(USART2);
    // usart_enable_tx_dma(USART2);
}

#ifdef STM32F103X_ADC_TEST
void adc_peripheral_test_init()
{
    /* adc config example */
    gpio_set_mode(GPIO_PORTA, 0, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 1, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 2, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 3, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 4, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 5, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 6, GPIO_MODE_IN, ANALOG);
    gpio_set_mode(GPIO_PORTA, 7, GPIO_MODE_IN, ANALOG);
    
    adc_config config;
    config.adc = ADC1;
    config.conversion_mode = continuous_conversion;

    config.channel_config[0].channel = channel0;
    config.channel_config[0].sampling_time= adc_sampling239_5;

    config.channel_config[1].channel = channel1;
    config.channel_config[1].sampling_time= adc_sampling239_5;

    config.channel_config[0].channel = channel2;
    config.channel_config[0].sampling_time = adc_sampling239_5;

    config.channel_config[0].channel = channel3;
    config.channel_config[0].sampling_time = adc_sampling239_5;

    config.channel_config[0].channel = channel4;
    config.channel_config[0].sampling_time = adc_sampling71_5;

    config.channel_config[0].channel = channel5;
    config.channel_config[0].sampling_time = adc_sampling71_5;

    config.channel_config[0].channel = channel6;
    config.channel_config[0].sampling_time = adc_sampling71_5;

    config.channel_config[0].channel = channel7;
    config.channel_config[0].sampling_time = adc_sampling71_5;
    
    config.no_of_channels = 2;

    adc_init(config);
    _delay(200);
    adc_start_conversion(config.adc);

    /* adc config end */
}
#endif

#ifdef STM32F103X_TIMER_TEST
void timer_peripheral_test_init()
{
    /* sample timer config for testing purpose */

    gpio_set_mode(GPIO_PORTA, 8, GPIO_MODE_OUT10MHZ, ALT_PUSH_PULL);
    gpio_set_mode(GPIO_PORTB, 7, GPIO_MODE_IN, FLOATING_INPUT);

    timer_config config;
    config.timer = TIM1;
    config.prescalar = TIM_DEFAULT_PRE_SCLAR;
    config.auto_reload = TIM_DEFAULT_AUTO_RELOAD;
    timer_init(config);

    /* timer channel config */
    timer_channel_output_config out_config;
    out_config.channel = t_channel1;
    out_config.mode = t_toggle_mode;
    timer_enable_output_compare(config.timer,out_config);
    timer_start(config.timer);


    timer_config s_config;
    s_config.timer = TIM4;
    s_config.prescalar = TIM_DEFAULT_PRE_SCLAR;
    s_config.auto_reload = TIM_DEFAULT_AUTO_RELOAD;
    timer_init(s_config);
    
    timer_channel_input_config in_config;
    in_config.channel = t_channel2;
    in_config.prescalar = t_no_prescalar;
    in_config.selection = t_channel_ic2_ti1;
    in_config.filter    = no_filter;
    timer_enable_input_capture(s_config.timer, in_config);
    timer_start(s_config.timer);

    /* timer config end */
}
#endif

#ifdef STM32F103X_DMA_TEST
dma_config dconfig;
void dma_peripheral_test_init()
{
    dconfig.channel = 7;
    dconfig.direction = read_from_memory;
    dconfig.memory_increment = mem_inc_enabled;
    dconfig.destination = (uint32_t)&USART2->DR;
    dma_init(dconfig);
}
#endif

#ifdef STM32F103X_I2C_TEST
void i2c_peripheral_test_init()
{
    uint8_t result;
    char buffer[18];
    
    gpio_set_mode(GPIO_PORTB, 6, GPIO_MODE_OUT10MHZ, ALT_OPEN_DRAIN);
    gpio_set_mode(GPIO_PORTB, 7, GPIO_MODE_OUT10MHZ, ALT_OPEN_DRAIN);

    i2c_config i2c_cfg = {
        .i2c = I2C1,
        .pfrequency = 8,        // 8MHz APB1 clock
        .ccr_value = 40,        // CCR value for 100kHz
        .rise_time = 9          // TRISE value for 100kHz
    };

    i2c_init(i2c_cfg);
}
#endif

#ifdef STM32F103X_SPI_TEST
void spi_peripheral_test_init()
{
    /* gpio init for spi */
    gpio_set_mode(GPIO_PORTA, 4, GPIO_MODE_OUT50MHZ, GN_PUSH_PULL);
    gpio_set_mode(GPIO_PORTA, 5, GPIO_MODE_OUT50MHZ, ALT_PUSH_PULL);
    gpio_set_mode(GPIO_PORTA, 6, GPIO_MODE_IN, FLOATING_INPUT);
    gpio_set_mode(GPIO_PORTA, 7, GPIO_MODE_OUT50MHZ, ALT_PUSH_PULL);

    spi_config sconfig;
    sconfig.spi = SPI1;
    sconfig.baud_rate = pclk_2;
    sconfig.clock_phase = 1;
    sconfig.clock_polarity = 1;
    sconfig.frame_format = msb_first;
    sconfig.mode = master_mode;

    spi_init(sconfig);
}

#endif

void clock_test_init()
{
    clock_config clk = {
        .source = CLOCK_SRC_PLL,
        .hse_freq = 8000000,
        .pll_mul = PLL_MUL_16,                       // 8 MHz * 9 = 72 MHz
        .ahb_prescaler = AHB_DIV1,
        .apb1_prescaler = APB1_DIV4,
        .apb2_prescaler = APB2_DIV4,
    };
    rcc_sysclk_init(&clk);
}

#ifdef STM32F103X_WDG_TEST
void check_reset_reason()
{
    rcc_reset_reason_t reason= rcc_get_reset_reason();
    if(reason == WWDGRSTF)
    {
        while(1)
        {
            gpio_pin_toggle(GPIO_PORTC,13);
            _delay(20);
        }
    }
    else if(reason == IWDGRSTF)
    {
        while(1)
        {
            gpio_pin_toggle(GPIO_PORTC,13);
            _delay(50);
        }
    }
}

void wdg_peripheral_test_init()
{
    iwdg_config iwdgconfig = {
        .prescalar_value = pre_div_128,
        .reload_value = 1560
    };
    iwdg_init(iwdgconfig);

    wwdg_config config = {
        .counter = 0x7F,
        .window = 0x5F,
        .prescalar = pre_div_4096_1
    };
    wwdg_init(config);
}
#endif

int main()
{
    /* enable system tick */
    systick_init(CPU_DEFAULT_FREQ/1000);
    // check_reset_reason();
    // clock_test_init();
    rcc_peripheral_test_init();
    usart_logging_test_init();
    user_led_test_init();
    // i2c_peripheral_test_init();
    // dma_peripheral_test_init();
    // spi_peripheral_test_init();
    // wdg_peripheral_test_init()

    while(1)
    {
        gpio_pin_toggle(GPIO_PORTC,13);
        _delay(500);
    }

    return 0;
}