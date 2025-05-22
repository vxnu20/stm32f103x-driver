/* Macros for GPIO peripherals */
#define GPIO_PERIPH_BASE_ADDR       (0x40010800UL)
#define GPIO_PORTA_OFFSET           (0x0UL)
#define GPIO_PORTB_OFFSET           (0x400UL)
#define GPIO_PORTC_OFFSET           (0x800UL)

/* Each ports */
#define GPIO_PORTA                  ((struct gpio_regs *) (GPIO_PERIPH_BASE_ADDR + GPIO_PORTA_OFFSET))
#define GPIO_PORTB                  ((struct gpio_regs *) (GPIO_PERIPH_BASE_ADDR + GPIO_PORTB_OFFSET))
#define GPIO_PORTC                  ((struct gpio_regs *) (GPIO_PERIPH_BASE_ADDR + GPIO_PORTC_OFFSET))

struct gpio_regs {
    volatile uint32_t CRL, /* Port config register low */
    CRH,                   /* Port config register high */
    IDR,                   /* Input data register */
    ODR,                   /* Output data register */
    BSSR,                  /* Bit set reset register */
    BRR,                   /* Bit reset register */
    LCKR                   /* lock register     */
};