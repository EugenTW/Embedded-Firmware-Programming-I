cmake_minimum_required(VERSION 3.20)

# 1️⃣ 先放 cross-compile 變數，讓 project() 走交叉流程
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -fno-use-cxa-atexit")


project(NUCLEO_F411RE LANGUAGES C CXX ASM)

# 2️⃣ 語言標準
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3️⃣ MCU define
add_compile_definitions(STM32F411xE)

# 4️⃣ Include
include_directories(
        ${CMAKE_SOURCE_DIR}/Core/Inc
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
)

# 5️⃣ Source
add_executable(${PROJECT_NAME}
        Core/Src/main.cpp
        Core/Src/system_stm32f4xx.c
        Core/Src/crt_stubs.c
        startup_stm32f411xe.s
        Core/Src/L000_Led_Toggle_Addr.cpp
)

# 6️⃣ 產出 .elf、不讓 CMake 自動加 Windows flag
set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE FALSE
        OUTPUT_NAME "NUCLEO_F411RE"
        SUFFIX ".elf"
)

# 7️⃣ 真正的 linker options —— 只留下你要的
target_link_options(${PROJECT_NAME} PRIVATE
        -T${CMAKE_SOURCE_DIR}/STM32F411XX_FLASH.ld
        -nostartfiles        # 不用 crt0
        -nostdlib            # 不鏈入 host libc
        --specs=nosys.specs  # 提供最小 _sbrk/_exit stub
        --specs=nano.specs   # 輕量 printf
        -Wl,--gc-sections
        -Wl,-Map=${PROJECT_NAME}.map
)
