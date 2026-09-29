# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.20)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

# VS Code CMake Tools can configure build/Debug without forwarding the preset's
# build type. The generated flags.cmake attaches the MCU definitions, compiler
# flags, and linker script to the Debug configuration, so keep that configuration
# as the fallback for single-config generators such as Ninja.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Set target definition variables required by the toolchain file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target.cmake)

# Set the toolchain file for cross-compilation
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)

# Project definition
project(H743_DASH_LOGGER_VSCODE)

# Enable CMake support for ASM and C/CPP languages
enable_language(C CXX ASM)

set(PROJECT_NAME H743_DASH_LOGGER_VSCODE)

# Create an executable object type
add_executable(${PROJECT_NAME})

# Include additional CMake files for flags, components, and files
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/components.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/files.cmake)

# The generated source list includes LVGL's test suite, which is not firmware.
get_target_property(FIRMWARE_SOURCES ${PROJECT_NAME} SOURCES)
list(FILTER FIRMWARE_SOURCES EXCLUDE REGEX "/Drivers/lvgl/tests/")
set_property(TARGET ${PROJECT_NAME} PROPERTY SOURCES "${FIRMWARE_SOURCES}")

# Add sources to executable/library
target_sources(${PROJECT_NAME} PRIVATE
  # CubeMX generated SDMMC2 sources are not currently included by
  # cmake/files.cmake, so keep them in the editable project section.
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/User_Libs/sd_card_writer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/sdmmc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FATFS/App/fatfs.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FATFS/Target/bsp_driver_sd.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FATFS/Target/sd_diskio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FatFs/src/diskio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FatFs/src/ff.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FatFs/src/option/syscall.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c
)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/FATFS/App
  ${CMAKE_CURRENT_SOURCE_DIR}/FATFS/Target
  ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FatFs/src
)

# Compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
  # User defined compiler options
)

# Add additional defined symbols
target_compile_definitions(${PROJECT_NAME} PRIVATE
  # Add additional defined symbols here
)

# Linker options
target_link_options(${PROJECT_NAME} PRIVATE 
  # User defined linker options
)

# Add additional linker search directories
target_link_directories(${PROJECT_NAME} PRIVATE
  # Add additional linker search directories here
)

# Add additional linker libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  # Add additional linker libraries here
)
