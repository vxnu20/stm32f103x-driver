#ifndef STM32F103X_PWR_H
#define STM32F103X_PWR_H

/* header files */
#include <stdint.h>

/* macros */
#define PWR             ((pwr_regs*) 0x40007000UL)
#define PWR_CR_DEP      (1<<8)

typedef struct {
    volatile uint32_t CR;   /* control register */
    volatile uint32_t CSR;  /* control status register */
}pwr_regs;

/* function prototypes*/
void pwr_enable_backup_domain_access(void);
void pwr_disable_backup_domain_access(void);

#endif //STM32F103X_PWR_H