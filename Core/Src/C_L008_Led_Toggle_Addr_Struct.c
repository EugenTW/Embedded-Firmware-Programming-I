#include <stdint.h>

// Where is the led connected?
// Port: A
// Pin: 5

#define PERIPH_BASE         (0x40000000UL)
#define AHB1PERIPH_OFFSET   (0x00020000UL)
#define AHB1PERIPH_BASE     (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET        (0x0000UL)
#define GPIOA_BASE          (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET          (0x3800UL)
#define RCC_BASE            (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN             (1U<<0)

#define PIN5                (1U<<5)
#define LED_PIN             PIN5

typedef struct
{
    volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00 */
    volatile uint32_t DUMMY[4];   /*!< GPIO port output type register */
    volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14 */
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t DUMMY[12];   /*!< Reserved, 0x28-0x2c */
    volatile uint32_t AHB1ENR;      /*!< RCC AHB1 peripheral clock register,        Address offset: 0x30 */
} RCC_TypeDef;

#define RCC      ((RCC_TypeDef *)RCC_BASE)
#define GPIOA    ((GPIO_TypeDef *)GPIOA_BASE)


int main(void) {
    // 1. Enable clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;
    // 2. Set PA5 as output
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &=~(1U<<11);

    while (1) {
        // 3. Set PA5 high
        // GPIOA->ODR |= LED_PIN;

        // 4. Toggle PA5
        GPIOA->ODR ^= LED_PIN;
        for (int i=0; i <100000; i++){}
    }
}
