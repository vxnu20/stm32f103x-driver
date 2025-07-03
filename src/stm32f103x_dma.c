#include "stm32f103x_dma.h"

void dma_init(dma_config config)
{
    uint8_t channel = config.channel-1;

    /* clock access enable */
    rcc_enable_dma_clock();

    /* disable the channel */
    DMA->CHANNELS[channel].CCR &= ~DMA_CHANNEL_EN;

    /* clear all flags related to the channel */
    /* writing 1 will clear the register */
    DMA->IFCR |= DMA_IFCR_CLEAR_ALL_FLAGS << (channel * 4);

    /* destination address */
    DMA->CHANNELS[channel].CPAR = config.destination;

    /* source address */
    DMA->CHANNELS[channel].CMAR = config.source;

    /* set the length */
    DMA->CHANNELS[channel].CNDTR = config.length;
}