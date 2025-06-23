#ifndef STM32F103X_AFIO_H
#define STM32F103X_AFIO_H

/* header files */
#include <stdint.h>

/* macros of afio */
#define AFIO            (( afio_regs *) 0x40010000UL)

/* registers of afio */
typedef struct {
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR1;
    volatile uint32_t EXTICR2;
    volatile uint32_t EXTICR3;
    volatile uint32_t EXTICR4;
    volatile uint32_t MAPR2;
} afio_regs;

#endif // STM32F103X_AFIO_H