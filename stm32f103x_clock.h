
/* macros for reset & clock control RCC*/
#define RCC_BASE_ADDR       (0x40021000UL)

#define RCC                 ((struct rcc_regs *) RCC_BASE_ADDR)


struct rcc_regs {
    volatile uint32_t CR,   /* clock control register */
    CFGR,                   /* clock configuration register */
    CIR,                    /* clock interrupt register */
    APB2RSTR,               /* APB2 reset register */
    APB1RSTR,               /* APB1 reset register */
    AHBENR,                 /* AHB clock enable register */
    APB2ENR,                /* APB2 clock enable register */
    APB1ENR,                /* APB1 clock enable register */
    BDCR,                   /* backup domain control register */
    CSR                     
};