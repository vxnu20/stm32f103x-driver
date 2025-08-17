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
    // rcc_enable_i2c_clock(I2C1);
    rcc_enable_spi_clock(SPI1);
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

#ifdef MPU6050_TEST

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

#ifdef STM32F103X_I2C_TEST
    i2c_master_write_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_PWR_MGMT_1,0x00U);
    i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_WHO_AM_I, &result);
    if((result) == MPU6050_I2C_ADDR)
    {
        sprintf(buffer, "mpu6050, who ami -> %x\n", result);
        usart_write_string(USART1,buffer);
    }
#endif

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
#ifdef STM32F103X_I2C_TEST
        i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, mpu6050_data_registers[i*2], &high);
        i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, mpu6050_data_registers[(i*2)+1], &low);
#endif
        readed_values[i] = (uint16_t)((high<<8) | low);
    }
}

float mpu6050_get_temperature_celsius()
{
    uint8_t temp_h = 0, temp_l = 0;
    int16_t temp_raw = 0;
    float temp_c = 0.0f;
#ifdef STM32F103X_I2C_TEST
    i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_TEMP_OUT_H, &temp_h);
    i2c_master_read_byte(I2C1, MPU6050_I2C_ADDR, MPU6050_TEMP_OUT_L, &temp_l);
#endif
    temp_raw = (int16_t)((temp_h << 8) | temp_l);
    temp_c = (temp_raw / 340.0f) + 36.53f;

    return temp_c;
}

#endif
#ifdef BMP280_TEST

/* BMP280 Register map */
#define BMP280_ID   0xD0

typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
} bmp280_calib_data_t;

bmp280_calib_data_t bmp280_calib;
int32_t t_fine;  // global or static, needed for pressure calc

void bmp280_read_calibration(void) {
    uint8_t buf[24];
    uint8_t data = 0x88;
    // Read 24 bytes starting from 0x88
    spi_cs_enable(GPIO_PORTA, 4);

    spi_master_transmit(SPI1, &data, 1);
    spi_master_receive(SPI1, buf, 24);

    spi_cs_disable(GPIO_PORTA, 4);

    bmp280_calib.dig_T1 = (uint16_t)(buf[1] << 8 | buf[0]);
    bmp280_calib.dig_T2 = (int16_t)(buf[3] << 8 | buf[2]);
    bmp280_calib.dig_T3 = (int16_t)(buf[5] << 8 | buf[4]);

    bmp280_calib.dig_P1 = (uint16_t)(buf[7] << 8 | buf[6]);
    bmp280_calib.dig_P2 = (int16_t)(buf[9] << 8 | buf[8]);
    bmp280_calib.dig_P3 = (int16_t)(buf[11] << 8 | buf[10]);
    bmp280_calib.dig_P4 = (int16_t)(buf[13] << 8 | buf[12]);
    bmp280_calib.dig_P5 = (int16_t)(buf[15] << 8 | buf[14]);
    bmp280_calib.dig_P6 = (int16_t)(buf[17] << 8 | buf[16]);
    bmp280_calib.dig_P7 = (int16_t)(buf[19] << 8 | buf[18]);
    bmp280_calib.dig_P8 = (int16_t)(buf[21] << 8 | buf[20]);
    bmp280_calib.dig_P9 = (int16_t)(buf[23] << 8 | buf[22]);
}

uint8_t value = 0U;

// Temperature compensation: returns temperature in °C
float bmp280_compensate_temp(int32_t adc_T) {
    int32_t var1, var2;
    var1 = ((((adc_T >> 3) - ((int32_t)bmp280_calib.dig_T1 << 1))) *
            ((int32_t)bmp280_calib.dig_T2)) >> 11;

    var2 = (((((adc_T >> 4) - ((int32_t)bmp280_calib.dig_T1)) *
              ((adc_T >> 4) - ((int32_t)bmp280_calib.dig_T1))) >> 12) *
            ((int32_t)bmp280_calib.dig_T3)) >> 14;

    t_fine = var1 + var2;

    float T = (t_fine * 5 + 128) >> 8;   // in 0.01 °C
    return T / 100.0f;                   // convert to °C
}

// Pressure compensation: returns pressure in hPa (millibar)
float bmp280_compensate_press(int32_t adc_P) {
    int64_t var1, var2, p;
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)bmp280_calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)bmp280_calib.dig_P5) << 17);
    var2 = var2 + (((int64_t)bmp280_calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)bmp280_calib.dig_P3) >> 8) +
           ((var1 * (int64_t)bmp280_calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) *
           ((int64_t)bmp280_calib.dig_P1) >> 33;

    if (var1 == 0) {
        return 0; // avoid div by zero
    }

    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)bmp280_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)bmp280_calib.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)bmp280_calib.dig_P7) << 4);

    return (float)p / 25600.0f;   // convert Pa → hPa (millibar)
}

void bmp280_init()
{
    spi_cs_enable(GPIO_PORTA, 4);
    spi_cs_disable(GPIO_PORTA, 4);

    char buffer[40];
    uint8_t data = BMP280_ID | 0x80;
    uint8_t dummy=0xFF;
    sprintf(buffer, "BMP280 init \n");
    usart_write_string(USART1,buffer);

    spi_cs_enable(GPIO_PORTA, 4);

    spi_master_transmit(SPI1, &data, 1);
    spi_master_receive(SPI1, &value, 1);

    spi_cs_disable(GPIO_PORTA, 4);

    sprintf(buffer, "BMP280 ID 0x%x\n",value);
    usart_write_string(USART1,buffer);

    bmp280_read_calibration();

}
uint32_t bmp280_get_sensor_data()
{
    uint8_t raw[6];
    uint8_t data = 0xF7;
    spi_cs_enable(GPIO_PORTA, 4);

    spi_master_transmit(SPI1, &data, 1);
    spi_master_receive(SPI1, raw, 6);

    spi_cs_disable(GPIO_PORTA, 4);

    int32_t adc_P = (int32_t)(((uint32_t)raw[0] << 12) | ((uint32_t)raw[1] << 4) | (raw[2] >> 4));
    int32_t adc_T = (int32_t)(((uint32_t)raw[3] << 12) | ((uint32_t)raw[4] << 4) | (raw[5] >> 4));

    int32_t temp = bmp280_compensate_temp(adc_T);
    int32_t pres = bmp280_compensate_press(adc_P);

    char buffer[40];
    sprintf(buffer, "temp in C -> %d pressure -> %d \n",temp,pres);
    usart_write_string(USART1,buffer);

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

int main()
{
    /* enable system tick */
    systick_init(CPU_DEFAULT_FREQ/1000);

    rcc_peripheral_test_init();
    usart_logging_test_init();
    user_led_test_init();
    // i2c_peripheral_test_init();
    // dma_peripheral_test_init();
    spi_peripheral_test_init();

#ifdef MPU6050_TEST
    mpu6050_init();
#endif
#ifdef BMP280_TEST
    bmp280_init();
#endif

    while(1)
    {
#if defined(MPU6050_TEST) && defined(STM32F103X_I2C_TEST)
        char buffer[40];
        sprintf(buffer, "temp in C -> %d\n",(uint8_t)mpu6050_get_temperature_celsius());
        usart_write_string(USART1,buffer);
#endif

#if defined(BMP280_TEST) && defined(STM32F103X_SPI_TEST)
    bmp280_get_sensor_data();
#endif
        gpio_pin_toggle(GPIO_PORTC,13);
        _delay(500);
    }

    return 0;
}