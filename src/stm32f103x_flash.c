#include "stm32f103x_flash.h"

void flash_set_wait_state(flash_wait_state wait_state)
{
    FLASH_ACR |= FLASH_ACR_PRFTBE;

    FLASH_ACR &= ~ FLASH_ACR_LATENCY_MASK;

    FLASH_ACR |= wait_state;
}