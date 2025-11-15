#include "stm32f103x_pwr.h"

void pwr_enable_backup_domain_access(void)
{
    PWR->CR |= PWR_CR_DEP;
}

void pwr_disable_backup_domain_access(void)
{
    PWR->CR &= ~PWR_CR_DEP;
}