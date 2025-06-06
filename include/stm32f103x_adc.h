/* Header files */
#include <stdint.h>

#include "stm32f103x_rcc.h"

/* macros of ADC driver */
#define ADC_BASE_ADDR           (0x40012400UL)
#define ADC_ADC1_OFFSET         (0x0UL)
#define ADC_ADC2_OFFSET         (0x400UL)
#define ADC_CR2_ADON_SET        (1<<0)
#define ADC_CR2_EXTSEL_SWSTART  (7<<17)
#define ADC_CR2_EXTTRIG_EN      (1<<20)
#define ADC_CR2_SWSTART_SET     (1<<22)
#define ADC_SR_EOC_SET          (1<<1)
#define ADC_MAX_CHANNELS        (10)

#define ADC1                (( adc_regs *) (ADC_BASE_ADDR + ADC_ADC1_OFFSET))
#define ADC2                (( adc_regs *) (ADC_BASE_ADDR + ADC_ADC2_OFFSET))

/* ADC registers */
typedef struct {
    volatile uint32_t SR;       /* status register */
    volatile uint32_t CR1;      /* control register 1*/
    volatile uint32_t CR2;      /* control register 2*/
    volatile uint32_t SMPR1;    /* sample time register 1*/
    volatile uint32_t SMPR2;    /* sample time register 2*/
    volatile uint32_t JOFR1;    /* injected channel data offset register 1 */
    volatile uint32_t JOFR2;    /* injected channel data offset register 2 */
    volatile uint32_t JOFR3;    /* injected channel data offset register 3 */
    volatile uint32_t JOFR4;    /* injected channel data offset register 4 */
    volatile uint32_t HTR;      /* watchdog high threshold register */
    volatile uint32_t LTR;      /* watchdog low threshold register */
    volatile uint32_t SQR1;     /* regular sequence register 1*/
    volatile uint32_t SQR2;     /* regular sequence register 2*/
    volatile uint32_t SQR3;     /* regular sequence register 3*/
    volatile uint32_t JSQR;     /* injected sequence register */
    volatile uint32_t JDR1;     /* injected data register 1 */
    volatile uint32_t JDR2;     /* injected data register 2 */
    volatile uint32_t JDR3;     /* injected data register 3 */
    volatile uint32_t JDR4;     /* injected data register 4 */
    volatile uint32_t DR;       /* regular data register */
}adc_regs;

/* 10 adc channels */
typedef enum {
    channel0,
    channel1,
    channel2,
    channel3,
    channel4,
    channel5,
    channel6,
    channel7,
    channel8,
    channel9
}adc_channels;

/* structure to hold the adc configuration */
typedef struct {
    adc_regs* adc;
    uint8_t no_of_channels;
    adc_channels channels[ADC_MAX_CHANNELS];
} adc_config;

/* function prototypes */
void adc_init(adc_config);
void adc_start_conversion(adc_regs*);
uint32_t adc_read_value(adc_regs*);
static void adc_internal_set_sequence(adc_config);