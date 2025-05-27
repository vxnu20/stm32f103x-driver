/* header files required */
#include <stdint.h>

/* macros */
#define SYSTICK         ((systick_regs*) 0xE000E010UL)
#define STK_ENABLE      ((1<<0))
#define STK_INT_ENABLE  ((1<<1))
#define STK_CLK_AHB     ((1<<2))
#define MAX_24BIT       (0xFFFFFFUL)

/* registers of STK */
typedef struct {
    volatile uint32_t CTRL; /* systick control and status register */
    volatile uint32_t LOAD; /* reload value register */
    volatile uint32_t VAL;  /* current value register */
    volatile uint32_t CALIB /* calibration value register */
    
} systick_regs;

/*global variables */
volatile uint32_t systick_count;

/* function prototypes */
void systick_init(uint32_t);
