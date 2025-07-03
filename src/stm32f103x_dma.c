#include "stm32f103x_dma.h"

void dma_init(dma_config config)
{
    /* clock access enable */
    rcc_enable_dma_clock();

    /* disable the channel */
    config.CHANNELS[config.channel-1]->
}