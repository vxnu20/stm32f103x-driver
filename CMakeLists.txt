cmake_minimum_required(VERSION 3.12)
project(stm32f103x_driver C)

# Explicitly list only required sources
add_library(stm32f103x_driver STATIC
    src/stm32f103x_gpio.c
    include/stm32f103x_gpio.h
)

# Expose the include folder
target_include_directories(stm32f103x_driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(stm32f103x_driver PROPERTIES C_STANDARD 99)