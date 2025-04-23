#include <cstdint>

constexpr uintptr_t PERIPH_BASE        = 0x40000000UL;
constexpr uintptr_t AHB1PERIPH_OFFSET  = 0x00020000UL;
constexpr uintptr_t AHB1PERIPH_BASE    = PERIPH_BASE + AHB1PERIPH_OFFSET;
constexpr uintptr_t GPIOA_OFFSET       = 0x0000UL;
constexpr uintptr_t GPIOA_BASE         = AHB1PERIPH_BASE + GPIOA_OFFSET;

constexpr uintptr_t RCC_OFFSET         = 0x00003800UL;
constexpr uintptr_t RCC_BASE           = AHB1PERIPH_BASE + RCC_OFFSET;


void L000_Led_Toggle_addr() {

}