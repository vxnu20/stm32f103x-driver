#include "stm32f103x_rtc.h"

/* static functions*/
static void rtc_wait_for_last_operation(void);
static void rtc_enter_config_mode(void);
static void rtc_exit_config_mode(void);

void rtc_init()
{
        /* TODO 
            1. enabled pwr clock
            2. Allow backup domain access
            3. enable lse oscilator
            4. select rtc clock source 
            5 . wait until rtc clocks to be in sync
            6. enter rtc config
            7. set presclar value
            8. set counter 
            9. exit rtc config
        
        */
    rcc_enable_pwr_clock();
    pwr_enable_backup_domain_access();
    rcc_enable_lsi_clock();
    rcc_enable_rtc_clock(lsi_clock);

    RTC->CRL &= ~RTC_CRL_RSF;
    while(!(RTC->CRL & RTC_CRL_RSF)){ asm("nop"); }

    rtc_wait_for_last_operation();
    rtc_enter_config_mode();
    
    RTC->PRLH = (uint16_t)((RTC_DEFAULT_LSI_FREQ >> 16) & 0x0F);
    RTC->PRLL = (uint16_t)(RTC_DEFAULT_LSI_FREQ & 0xFFFF);

    RTC->CNTH = 0UL;
    RTC->CNTL = 0UL;

    rtc_exit_config_mode();
    rtc_wait_for_last_operation();
}

static void rtc_wait_for_last_operation(void)
{
    while(!(RTC->CRL & RTC_CRL_RTOFF)){ asm("nop"); }
}

static void rtc_enter_config_mode(void)
{
    RTC->CRL |= RTC_CRL_CNF;
}

static void rtc_exit_config_mode(void)
{
    RTC->CRL &= ~RTC_CRL_CNF;
}

uint32_t rtc_get_counter(void)
{
    uint16_t high1, low, high2;
    /* Read high → low → high again until stable */
    do {
        high1 = RTC->CNTH;
        low   = RTC->CNTL;
        high2 = RTC->CNTH;
    } while (high1 != high2);

    return ((uint32_t)high1 << 16) | low;
}