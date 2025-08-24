#ifndef STM32F103X_FLASH_H
#define STM32F103X_FLASH_H

/* required header files */
#include <stdint.h>

/* flash peripheral macro */
#define FLASH_ACR               (*( volatile uint32_t *) 0x40022000UL)
#define FLASH_ACR_PRFTBE        (1<<4)
#define FLASH_ACR_LATENCY_MASK  (0x7)

typedef enum {
    FLASH_LATENCY_0,    /* < 24MHz */
    FLASH_LATENCY_1,    /* 24MHz < SYSCLK < 48MHz */
    FLASH_LATENCY_2     /* 48MHz < SYSCLK < 72MHz */
} flash_wait_state;

/* function prototypes */
void flash_set_wait_state(flash_wait_state);

#endif