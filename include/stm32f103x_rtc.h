#ifndef STM32F103X_RTC_H
#define STM32F103X_RTC_H

/* header files */
#include <stdint.h>
#include "stm32f103x_pwr.h"
#include "stm32f103x_rcc.h"

/* macros */
#define RTC                         ((rtc_regs*) 0x40002800UL)
#define RTC_CRL_RSF                 (1<<3)
#define RTC_CRL_CNF                 (1<<4)
#define RTC_CRL_RTOFF               (1<<5)
#define RTC_DEFAULT_LSI_FREQ        39999

typedef struct {
    volatile uint32_t CRH;  /* control register */
    volatile uint32_t CRL;  /* control register */
    volatile uint32_t PRLH; /* prescalar load register */
    volatile uint32_t PRLL; /* prescalar load register */
    volatile uint32_t DIVH; /* prescalar divider register */
    volatile uint32_t DIVL; /* prescalar divider register */
    volatile uint32_t CNTH; /* counter register */
    volatile uint32_t CNTL; /* counter register */
    volatile uint32_t ALRH; /* alarm register */
    volatile uint32_t ALRL; /* alarm register */
} rtc_regs;

typedef struct {
    uint8_t hh;
    uint8_t mm;
    uint8_t ss;
}rtc_time_t;

typedef struct {
    uint32_t prescalar;
    rtc_time_t time;
} rtc_config;

/* function prototypes */
void rtc_init();
uint32_t rtc_get_counter(void);

#endif //STM32F103X_RTC_H