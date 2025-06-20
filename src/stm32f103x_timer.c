#include "stm32f103x_timer.h"


void timer_init(timer_config config)
{
    /* set the pre-scalar and auto reload value */
    config.timer->PSC = config.prescalar;
    config.timer->ARR = config.auto_reload;
    /* clear the counter */
    config.timer->CNT = 0;
}

void timer_start(timer_regs* timer)
{
    /* enable the counter */
    timer->CR1 |= TIM_CR1_CEN;
}

void timer_stop(timer_regs* timer)
{
    /* disable the counter */
    timer->CR1 &= ~TIM_CR1_CEN;
}

uint16_t timer_read_count(timer_regs* timer)
{
    return timer->CNT;
}

void timer_enable_output_compare(timer_regs* timer, timer_channel_output_config config)
{
    /* set the compare mode */
    volatile uint32_t *ccmr = (config.channel <= t_channel2) ? &timer->CCMR1 : &timer->CCMR2;

    /* clear the capture compare selection bits*/
    /* shift 0 for channel 1 and 3 and shift shift 12 for 2 and 4 */
    uint8_t shift = (config.channel % 2) ? 0 : 8;
    *ccmr &= ~(TIMx_CCMR_CCS_CLEAR << shift);

    /* set the output compare mode */
    /* shift 4 for 1 and 3 , shift 12 for 2 and 4 */
    shift = (config.channel % 2) ? 4 : 12;
    *ccmr |= (config.mode << shift);

    /* enable respective channel */
    timer->CCER |= (1 << ((config.channel - 1) * 4));
}

void timer_enable_input_capture(timer_regs* timer, timer_channel_input_config config)
{
    /* which ccmr ? */
    volatile uint32_t *ccmr = (config.channel <= t_channel2) ? &timer->CCMR1 : &timer->CCMR2;

    /* set the input capture selection bits*/
    /* shift 0 for channel 1 and 3 and shift 8 for 2 and 4 */
    uint8_t shift = (config.channel % 2) ? 0 : 8;
    *ccmr |= (config.selection << shift);

    /* set the filter */
    /* shift 4 for 1 and 3 and shift 12 for 2 and 4*/
    shift = (config.channel % 2) ? 4 : 12;
    *ccmr |= (config.filter <<shift);

    /* set the prescalar */
    /* shift 2 for channel 1 and 3  and shift 10 for channel 2 and 4 */
    shift = (config.channel % 2) ? 2 : 10;
    *ccmr |= (config.prescalar << shift);

    timer->CCER |= (1 << ((config.channel - 1) * 4));
}