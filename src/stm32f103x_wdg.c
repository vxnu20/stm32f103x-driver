#include "stm32f103x_wdg.h"

void iwdg_init(iwdg_config config)
{
    /* LSI clock automatically enabled enabled */
    /* enable the write access to PR and RLR */
    IWDG->KR = IWDG_ENABLE_WRITE_ACCESS;
    /* set prescalar and reload value */
    IWDG->PR |= config.prescalar_value;
    IWDG->RLR |= config.reload_value & IWGD_RLR_MASK;
    /* enable the watchdog */
    IWDG->KR = IWDG_START; 
}

void iwdg_refresh()
{
    /* call this periodically to avoid reset */
    IWDG->KR = IWDG_RELOAD;
}

void wwdg_init(wwdg_config config)
{
    /* set the counter value */
    WWDG->CR = ((WWDG->CR & ~WWDG_CR_T_MASK) | ((config.counter & 0x7F) << WWDG_CR_T_POS));
    /* set the watchdog window*/
    WWDG->CFR = ((WWDG->CFR & ~WWDG_CFR_W_MASK) | ((config.window & 0x7F) << WWDG_CFR_W_POS));
    /* set the prescalar */
    WWDG->CFR = ((WWDG->CFR & ~WWDG_CFR_WDGTB_MASK) | ((config.prescalar & 0x3F) << WWDG_CFR_WDGTB_POS));
    /* activate windowed watchdog */
    WWDG->CR |= WWDG_CR_WDGA;
}

void wwdg_refresh(uint8_t counter)
{
    WWDG->CR = ((WWDG->CR & ~WWDG_CR_T_MASK) | ((counter & 0x7F) << WWDG_CR_T_POS));
}