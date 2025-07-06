#include "stm32f103x_dma.h"

void dma_init(dma_config config)
{
    uint8_t channel = config.channel-1;

    /* clock access enable */
    rcc_enable_dma_clock();

    /* disable the channel it is required for writing other registers */
    DMA->CHANNELS[channel].CCR &= ~DMA_CHANNEL_EN;

    /* clear all flags related to the channel */
    /* writing 1 will clear the register */
    DMA->IFCR |= DMA_IFCR_CLEAR_ALL_FLAGS << (channel * 4);

    /* destination address */
    /* TODO - need to handle peripheral as source */
    DMA->CHANNELS[channel].CPAR = config.destination;

    /* source address */
    /* TODO - need to handle peripheral as source */
    DMA->CHANNELS[channel].CMAR = config.source;

    /* set the length */
    DMA->CHANNELS[channel].CNDTR = config.length;

    /* set the direction */
    DMA->CHANNELS[channel].CCR |= (config.direction << DMA_CHANNEL_CCR_DIR);

    /* memory increment */
    DMA->CHANNELS[channel].CCR |= (config.memory_increment <<DMA_CHANNEL_CCR_MINC);

    /* INFO - stm32f103 dosen't support FIFO mode */

    /* enable channel */
    DMA->CHANNELS[channel].CCR |= DMA_CHANNEL_EN;

    /* TODO 

        enable peripheral DMA
        enable interrupt
    */
}

void dma_send_data(dma_config config, uint8_t *data, uint8_t length)
{
    uint8_t channel = config.channel-1;
    while(DMA->CHANNELS[channel].CNDTR !=0 ){ }
    
    /* disable the channel it is required for writing other registers */
    DMA->CHANNELS[channel].CCR &= ~DMA_CHANNEL_EN;

    // send the data
    DMA->CHANNELS[channel].CMAR = (uint32_t)data;
    DMA->CHANNELS[channel].CNDTR = length;

    /* reenable the channel */
    DMA->CHANNELS[channel].CCR |= DMA_CHANNEL_EN;
}