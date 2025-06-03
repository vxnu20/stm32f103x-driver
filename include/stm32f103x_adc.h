/* Header files */
#include <stdint.h>

/* macros of ADC driver */
#define ADC_BASE_ADDR       (0x40012400UL)
#define ADC_ADC1_OFFSET     (0x0UL)
#define ADC_ADC2_OFFSET     (0x400UL)

#define ADC1                (( adc_regs *) (ADC_BASE_ADDR + ADC_ADC1_OFFSET))
#define ADC2                (( adc_regs *) (ADC_BASE_ADDR + ADC_ADC2_OFFSET))

/* ADC registers */
struct typedef {
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