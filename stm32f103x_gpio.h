/* Macros for GPIO peripherals */
#define GPIO_PERIPH_BASE_ADDR       (0x40010800UL)
#define GPIO_PORTA_OFFSET           (0x0UL)
#define GPIO_PORTB_OFFSET           (0x400UL)
#define GPIO_PORTC_OFFSET           (0x800UL)

/* Each ports */
#define GPIO_PORTA                  (( gpio_regs *) (GPIO_PERIPH_BASE_ADDR + GPIO_PORTA_OFFSET))
#define GPIO_PORTB                  (( gpio_regs *) (GPIO_PERIPH_BASE_ADDR + GPIO_PORTB_OFFSET))
#define GPIO_PORTC                  (( gpio_regs *) (GPIO_PERIPH_BASE_ADDR + GPIO_PORTC_OFFSET))

typedef struct {
    volatile uint32_t CRL, /* Port config register low */
    CRH,                   /* Port config register high */
    IDR,                   /* Input data register */
    ODR,                   /* Output data register */
    BSSR,                  /* Bit set reset register */
    BRR,                   /* Bit reset register */
    LCKR                   /* lock register     */
}gpio_regs;

/* pin mode
    00: Input mode (reset state)
    01: Output mode, max speed 10 MHz.
    10: Output mode, max speed 2 MHz.
    11: Output mode, max speed 50 MHz.
*/
enum gpio_mode {
    GPIO_MODE_IN,
    GPIO_MODE_OUT10MHZ,
    GPIO_MODE_OUT2MHZ,
    GPIO_MODE_OUT50MHZ
};

/* input mode 
    00: Analog mode
    01: Floating input (reset state)
    10: Input with pull-up / pull-down
    11: Reserved
*/

enum gpio_in_cnf {
    ANALOG,
    FLOATING_INPUT,
    IN_PULLUP_PULLOUT,
    RESERVED
};

/* output mode
    00: General purpose output push-pull
    01: General purpose output Open-drain
    10: Alternate function output Push-pull
    11: Alternate function output Open-drain
*/
enum gpio_out_cnf {
    GN_PUSH_PULL,
    GN_OPEN_DRAIN,
    ALT_PUSH_PULL,
    ALT_OPEN_DRAIN
};

/* function prototypes */
void gpio_set_mode(gpio_regs*, uint8_t ,uint8_t , uint8_t);
void gpio_pin_toggle(gpio_regs*, uint8_t);