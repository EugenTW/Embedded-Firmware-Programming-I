extern "C" {
#include "stm32f411xe.h"
}

void L004_Led_Toggle_addr();
void L008_Led_Toggle_addr_Struct();

int main() {
  L004_Led_Toggle_addr();
  L008_Led_Toggle_addr_Struct();


  return 0;
}
