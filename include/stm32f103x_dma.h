#ifndef STM32F103X_DMA_H
#define STM32F103X_DMA_H

/* required header files */
#include <stdint.h>

/* macros for dma */
#define DMA_PERIPH_BASE_ADDR    (0x40020000UL)
#define DMA1_OFFSET             (0x0UL)

/* dma peripherals */
#define DMA1                    (( dma_regs *) (DMA_PERIPH_BASE_ADDR + DMA_OFFSET))

/* sub struct for dma registers */
typedef struct {
    volatile uint32_t CCR;          /* channel x config register */
    volatile uint32_t CNDTR;        /* channel x number of data register */
    volatile uint32_t CPAR;         /* channel x peripheral address register */
    volatile uint32_t CMAR;         /* channel x memory address register */
    volatile uint32_t RESERVED;     /* reserved space */
} dma_channel_regs;

typedef struct {
    volatile uint32_t ISR;          /* interrupt status register */
    volatile uint32_t IFCR;         /* interrupt flag clear register */
    dma_channel_regs CHANNELS[7];
} dma_regs;

#endif // STM32F103X_DMA_H