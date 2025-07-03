#ifndef STM32F103X_DMA_H
#define STM32F103X_DMA_H

/* required header files */
#include <stdint.h>

#include "stm32f103x_rcc.h"

/* macros for dma */
#define DMA_PERIPH_BASE_ADDR        (0x40020000UL)
#define DMA_OFFSET                  (0x0UL)
#define DMA_CHANNEL_EN              (1<<0)
#define DMA_IFCR_CLEAR_ALL_FLAGS    (0x03U)

/* dma peripherals */
#define DMA                         (( dma_regs *) (DMA_PERIPH_BASE_ADDR + DMA_OFFSET))

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

/* struct that hold dma config */
typedef struct {
    uint8_t channel;
    uint32_t source;
    uint32_t destination;
    uint16_t length;
    // direction
    // fifo
} dma_config;

/* function prototypes */
void dma_init(dma_config);
#endif // STM32F103X_DMA_H