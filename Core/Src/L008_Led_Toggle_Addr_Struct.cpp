#include <cstdint>

//=================== Address Base ====================
constexpr uintptr_t PERIPH_BASE        = 0x40000000UL;
constexpr uintptr_t AHB1PERIPH_OFFSET  = 0x00020000UL;
constexpr uintptr_t AHB1PERIPH_BASE    = PERIPH_BASE + AHB1PERIPH_OFFSET;

constexpr uintptr_t GPIOA_OFFSET       = 0x0000UL;
constexpr uintptr_t GPIOA_BASE         = AHB1PERIPH_BASE + GPIOA_OFFSET;

constexpr uintptr_t RCC_OFFSET         = 0x3800UL;
constexpr uintptr_t RCC_BASE           = AHB1PERIPH_BASE + RCC_OFFSET;

//=================== Bitmask 定義 ====================
constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t PIN5    = (1U << 5);
constexpr uint32_t LED_PIN = PIN5;

//=================== Peripheral Struct ====================
struct GPIO_TypeDef {
    volatile uint32_t MODER;     // 0x00
    volatile uint32_t DUMMY[4];  // 0x04 - 0x10
    volatile uint32_t ODR;       // 0x14
};

struct RCC_TypeDef {
    volatile uint32_t DUMMY[12]; // 0x00 - 0x2C
    volatile uint32_t AHB1ENR;   // 0x30
};

//=================== Peripheral Instance ====================
inline GPIO_TypeDef* const GPIOA = reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE);
inline RCC_TypeDef*  const RCC   = reinterpret_cast<RCC_TypeDef*>(RCC_BASE);


void L008_Led_Toggle_addr_Struct() {
    // 1. 開啟 GPIOA 時鐘
    RCC->AHB1ENR |= GPIOAEN;

    // 2. 設定 PA5 為輸出模式（MODER bit10=1, bit11=0）
    GPIOA->MODER &= ~(3U << (5 * 2));  // 清除 bit10,11
    GPIOA->MODER |=  (1U << (5 * 2));  // 設定為輸出

    while (true) {
        // 3. 翻轉 LED 狀態（PA5）
        GPIOA->ODR ^= LED_PIN;

        // 4. 簡易延遲（空迴圈）
        for (volatile int i = 0; i < 100000; ++i) {}
    }

}