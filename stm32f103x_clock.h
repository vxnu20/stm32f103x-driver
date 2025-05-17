#define RCC_BASE_ADDR       (0x40021000UL)
#define RCC_APB2ENR_OFFSET         (0x18UL)

#define RCC_APB2ENR_BASE            (*(volatile unsigned int*)(RCC_BASE_ADDR + RCC_APB2ENR_OFFSET))