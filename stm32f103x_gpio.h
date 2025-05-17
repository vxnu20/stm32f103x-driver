#define GPIO_PERIPH_BASE_ADDR       (0x40010800UL)
#define GPIO_CRL_REG_OFFSET         (0x00UL)
#define GPIO_CRH_REG_OFFSET         (0x04UL)
#define GPIO_IDR_REG_OFFSET         (0x08UL)
#define GPIO_ODR_REG_OFFSET         (0x0CUL)

/* PORT C  */
#define GPIO_PORTC_OFFSET           (0x800UL)
#define GPIO_PORTC_BASE             (GPIO_PERIPH_BASE_ADDR + GPIO_PORTC_OFFSET)
/* PORT C Registers */
#define GPIO_PORTC_CRL_REG          (*(volatile unsigned int*)(GPIO_PORTC_BASE + GPIO_CRL_REG_OFFSET))
#define GPIO_PORTC_CRH_REG          (*(volatile unsigned int*)(GPIO_PORTC_BASE + GPIO_CRH_REG_OFFSET))
#define GPIO_PORTC_ODR_REG          (*(volatile unsigned int*)(GPIO_PORTC_BASE + GPIO_ODR_REG_OFFSET))