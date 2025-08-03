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
    rcc_enable_gpio_clock(GPIO_PORTB);
    rcc_enable_gpio_clock(GPIO_PORTC);
    // rcc_enable_timer_clock(TIM1);
    // rcc_enable_timer_clock(TIM2);
    // rcc_enable_timer_clock(TIM3);
    // rcc_enable_timer_clock(TIM4);
    rcc_enable_usart_clock(USART1);
    // rcc_enable_usart_clock(USART2);
    rcc_enable_i2c_clock(I2C1);
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

#ifdef I2C_MPU6050_TEST

#define MPU6050_I2C_ADDR        0x68
#define MPU6050_PWR_MGMT_1      0x6B
#define MPU6050_WHO_AM_I        0x75
// ---------------------- Accelerometer --------------------------
#define MPU6050_ACCEL_XOUT_H     0x3B
#define MPU6050_ACCEL_XOUT_L     0x3C
#define MPU6050_ACCEL_YOUT_H     0x3D
#define MPU6050_ACCEL_YOUT_L     0x3E
#define MPU6050_ACCEL_ZOUT_H     0x3F
#define MPU6050_ACCEL_ZOUT_L     0x40

// ---------------------- Temperature ----------------------------
#define MPU6050_TEMP_OUT_H       0x41
#define MPU6050_TEMP_OUT_L       0x42

// ---------------------- Gyroscope -----------------------------
#define MPU6050_GYRO_XOUT_H      0x43
#define MPU6050_GYRO_XOUT_L      0x44
#define MPU6050_GYRO_YOUT_H      0x45
#define MPU6050_GYRO_YOUT_L      0x46
#define MPU6050_GYRO_ZOUT_H      0x47
#define MPU6050_GYRO_ZOUT_L      0x48

const uint8_t mpu6050_data_registers[14] = {

    MPU6050_ACCEL_XOUT_H, MPU6050_ACCEL_XOUT_L,
    MPU6050_ACCEL_YOUT_H, MPU6050_ACCEL_YOUT_L, 
    MPU6050_ACCEL_ZOUT_H, MPU6050_ACCEL_ZOUT_L,

    MPU6050_TEMP_OUT_H, MPU6050_TEMP_OUT_L,

    MPU6050_GYRO_XOUT_H, MPU6050_GYRO_XOUT_L,
    MPU6050_GYRO_YOUT_H, MPU6050_GYRO_YOUT_L,
    MPU6050_GYRO_ZOUT_H, MPU6050_GYRO_ZOUT_L
};

void mpu6050_init()
{ 
    uint8_t result;
    uint8_t buffer[20];
    /* this step will reset the chip*/
    i2c_master_write_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_PWR_MGMT_1,0x00U);
    i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_WHO_AM_I, &result);

    if((result) == MPU6050_I2C_ADDR)
    {
        sprintf(buffer, "mpu6050, who ami -> %x\n", result);
        usart_write_string(USART1,buffer);
    }
}
/* global variable for storing values */
uint16_t readed_values[17]= {0};
void mpu6050_read_all_raw_values()
{
    uint8_t high, low;
    uint8_t buffer[20];
    // i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_ACCEL_XOUT_H, &result);
    for(uint8_t i =0; i<7; i++)
    {
        i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, mpu6050_data_registers[i*2], &high);
        i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, mpu6050_data_registers[(i*2)+1], &low);
        readed_values[i] = (uint16_t)((high<<8) | low);
    }
}

float mpu6050_get_temperature_celsius()
{
    uint8_t temp_h = 0, temp_l = 0;
    int16_t temp_raw = 0;
    float temp_c = 0.0f;

    i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_TEMP_OUT_H, &temp_h);
    i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_TEMP_OUT_L, &temp_l);

    temp_raw = (int16_t)((temp_h << 8) | temp_l);
    temp_c = (temp_raw / 340.0f) + 36.53f;

    return temp_c;
}

#endif

int main()
{
    /* enable system tick */
    systick_init(CPU_DEFAULT_FREQ/1000);

    rcc_peripheral_test_init();
    usart_logging_test_init();
    user_led_test_init();
    // i2c_peripheral_test_init();
    // dma_peripheral_test_init();

#ifdef I2C_MPU6050_TEST
    mpu6050_init();
#endif

    while(1)
    {
#ifdef I2C_MPU6050_TEST
        char buffer[40];
        sprintf(buffer, "temp in C -> %d\n",(uint8_t)mpu6050_get_temperature_celsius());
        usart_write_string(USART1,buffer);
#endif
        // while(!(config.timer -> SR & TIM_SR_UF));
        gpio_pin_toggle(GPIO_PORTC,13);
        _delay(500);
    }

    return 0;
}