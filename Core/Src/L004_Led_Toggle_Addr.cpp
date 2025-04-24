#include <cstdint>

// Peripheral base addresses
constexpr uintptr_t PERIPH_BASE        = 0x40000000UL;
constexpr uintptr_t AHB1PERIPH_OFFSET  = 0x00020000UL;
constexpr uintptr_t AHB1PERIPH_BASE    = PERIPH_BASE + AHB1PERIPH_OFFSET;

constexpr uintptr_t GPIOA_OFFSET       = 0x0000UL;
constexpr uintptr_t GPIOA_BASE         = AHB1PERIPH_BASE + GPIOA_OFFSET;

constexpr uintptr_t RCC_OFFSET         = 0x3800UL;
constexpr uintptr_t RCC_BASE           = AHB1PERIPH_BASE + RCC_OFFSET;

// Register offsets
constexpr uintptr_t AHB1ENR_OFFSET     = 0x30UL;
constexpr uintptr_t MODER_OFFSET       = 0x00UL;
constexpr uintptr_t ODR_OFFSET         = 0x14UL;

// Bitmask
constexpr uint32_t GPIOAEN             = (1U << 0);
constexpr uint32_t PIN5                = (1U << 5);
constexpr uint32_t LED_PIN             = PIN5;

// Register references
inline volatile uint32_t& RCC_AHB1ENR  = *reinterpret_cast<volatile uint32_t*>(RCC_BASE + AHB1ENR_OFFSET);
inline volatile uint32_t& GPIOA_MODER  = *reinterpret_cast<volatile uint32_t*>(GPIOA_BASE + MODER_OFFSET);
inline volatile uint32_t& GPIOA_ODR    = *reinterpret_cast<volatile uint32_t*>(GPIOA_BASE + ODR_OFFSET);


void L004_Led_Toggle_addr() {
    // 1. Enable clock access to GPIOA
    RCC_AHB1ENR |= GPIOAEN;

    // 2. Set PA5 as output mode (MODER bits 10~11 = 01)
    GPIOA_MODER &= ~(3U << (5 * 2));  // 清除 bit10~11
    GPIOA_MODER |=  (1U << (5 * 2));  // 設定 bit10 = 1, bit11 = 0 → output

    while (true) {
        // 3. Toggle PA5
        // GPIOA_ODR |= LED_PIN;

        // 4. Simple delay loop
        GPIOA_ODR ^= LED_PIN;
        for (volatile int i = 0; i < 100000; ++i) {}
    }

}