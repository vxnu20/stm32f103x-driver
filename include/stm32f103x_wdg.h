#ifndef STM32F103X_WDG_H
#define STM32F103X_WDG_H

/* required header files */
#include <stdint.h>

/* macros of watchdog peripheral */
#define WDG_BASE_ADDR               (0x40002C00UL)
#define WWDG_OFFSET                 (0x0UL)
#define IWDG_OFFSET                 (0x400Ul)

#define IWDG                        ((iwdg_regs*) (WDG_BASE_ADDR + IWDG_OFFSET))
#define WWDG                        ((wwdg_regs*) (WDG_BASE_ADDR + WWDG_OFFSET))

#define IWDG_ENABLE_WRITE_ACCESS    0x5555
#define IWDG_START                  0xCCCC
#define IWDG_RELOAD                 0xAAAA
#define IWGD_RLR_MASK               0xFFF
#define WWDG_CR_T_POS               0UL
#define WWDG_CR_T_MASK              (0x7F << WWDG_CR_T_POS)
#define WWDG_CR_WDGA                (1<<7)
#define WWDG_CFR_W_POS              0UL
#define WWDG_CFR_W_MASK             (0x7F << WWDG_CFR_W_POS)
#define WWDG_CFR_WDGTB_POS          (8UL)
#define WWDG_CFR_WDGTB_MASK         (0x03 << WWDG_CFR_WDGTB_POS)

typedef struct {
    volatile uint32_t KR;   /* key register */
    volatile uint32_t PR;   /* prescalar register */
    volatile uint32_t RLR;  /* reload register */
    volatile uint32_t SR;   /* status register */
}iwdg_regs;

typedef enum {
    pre_div_4,
    pre_div_8,
    pre_div_16,
    pre_div_32,
    pre_div_64,
    pre_div_128,
    pre_div_256_1,
    pre_div_256_2,
}iwdg_prescalar;

/* config struct */
typedef struct {
    uint16_t reload_value;
    iwdg_prescalar prescalar_value;
}iwdg_config;


typedef struct {
    volatile uint32_t CR;   /* control register */
    volatile uint32_t CFR;  /* configuration register */
    volatile uint32_t SR;   /* status register */ 
}wwdg_regs;

typedef enum {
    /* already prescaled by 4096, 4096 * chosen prescale */
    pre_div_4096_1,
    pre_div_4096_2,
    pre_div_4096_4,
    pre_div_4096_8
}wwdg_prescalar;

typedef struct {
    uint8_t counter;
    uint8_t window;
    wwdg_prescalar prescalar;
}wwdg_config;

/* function prototypes */
void iwdg_init(iwdg_config);
void iwdg_refresh();
void wwdg_init(wwdg_config);
void wwdg_refresh(uint8_t);

#endif // STM32F103X_WDG_H