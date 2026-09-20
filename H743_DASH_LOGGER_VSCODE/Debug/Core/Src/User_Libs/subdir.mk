################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/User_Libs/ADS1115.cpp \
../Core/Src/User_Libs/ALTmain.cpp \
../Core/Src/User_Libs/RAW_DATA_SCREEN.cpp \
../Core/Src/User_Libs/SENSOR_DATA.cpp 

C_SRCS += \
../Core/Src/User_Libs/LVGL_LCD_LINK.c \
../Core/Src/User_Libs/bsp_sdram.c \
../Core/Src/User_Libs/interrupts.c \
../Core/Src/User_Libs/st7365_3.5Inch.c \
../Core/Src/User_Libs/w25q128.c 

C_DEPS += \
./Core/Src/User_Libs/LVGL_LCD_LINK.d \
./Core/Src/User_Libs/bsp_sdram.d \
./Core/Src/User_Libs/interrupts.d \
./Core/Src/User_Libs/st7365_3.5Inch.d \
./Core/Src/User_Libs/w25q128.d 

OBJS += \
./Core/Src/User_Libs/ADS1115.o \
./Core/Src/User_Libs/ALTmain.o \
./Core/Src/User_Libs/LVGL_LCD_LINK.o \
./Core/Src/User_Libs/RAW_DATA_SCREEN.o \
./Core/Src/User_Libs/SENSOR_DATA.o \
./Core/Src/User_Libs/bsp_sdram.o \
./Core/Src/User_Libs/interrupts.o \
./Core/Src/User_Libs/st7365_3.5Inch.o \
./Core/Src/User_Libs/w25q128.o 

CPP_DEPS += \
./Core/Src/User_Libs/ADS1115.d \
./Core/Src/User_Libs/ALTmain.d \
./Core/Src/User_Libs/RAW_DATA_SCREEN.d \
./Core/Src/User_Libs/SENSOR_DATA.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/User_Libs/%.o Core/Src/User_Libs/%.su Core/Src/User_Libs/%.cyclo: ../Core/Src/User_Libs/%.cpp Core/Src/User_Libs/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/Src/UI_LOGIC -I../Core/Inc/User_Libs -I../Core/Src/tasks -I../Core/Src/User_Libs -I../Drivers/lvgl -I../Drivers/UI_Squareline -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/User_Libs/%.o Core/Src/User_Libs/%.su Core/Src/User_Libs/%.cyclo: ../Core/Src/User_Libs/%.c Core/Src/User_Libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-User_Libs

clean-Core-2f-Src-2f-User_Libs:
	-$(RM) ./Core/Src/User_Libs/ADS1115.cyclo ./Core/Src/User_Libs/ADS1115.d ./Core/Src/User_Libs/ADS1115.o ./Core/Src/User_Libs/ADS1115.su ./Core/Src/User_Libs/ALTmain.cyclo ./Core/Src/User_Libs/ALTmain.d ./Core/Src/User_Libs/ALTmain.o ./Core/Src/User_Libs/ALTmain.su ./Core/Src/User_Libs/LVGL_LCD_LINK.cyclo ./Core/Src/User_Libs/LVGL_LCD_LINK.d ./Core/Src/User_Libs/LVGL_LCD_LINK.o ./Core/Src/User_Libs/LVGL_LCD_LINK.su ./Core/Src/User_Libs/RAW_DATA_SCREEN.cyclo ./Core/Src/User_Libs/RAW_DATA_SCREEN.d ./Core/Src/User_Libs/RAW_DATA_SCREEN.o ./Core/Src/User_Libs/RAW_DATA_SCREEN.su ./Core/Src/User_Libs/SENSOR_DATA.cyclo ./Core/Src/User_Libs/SENSOR_DATA.d ./Core/Src/User_Libs/SENSOR_DATA.o ./Core/Src/User_Libs/SENSOR_DATA.su ./Core/Src/User_Libs/bsp_sdram.cyclo ./Core/Src/User_Libs/bsp_sdram.d ./Core/Src/User_Libs/bsp_sdram.o ./Core/Src/User_Libs/bsp_sdram.su ./Core/Src/User_Libs/interrupts.cyclo ./Core/Src/User_Libs/interrupts.d ./Core/Src/User_Libs/interrupts.o ./Core/Src/User_Libs/interrupts.su ./Core/Src/User_Libs/st7365_3.5Inch.cyclo ./Core/Src/User_Libs/st7365_3.5Inch.d ./Core/Src/User_Libs/st7365_3.5Inch.o ./Core/Src/User_Libs/st7365_3.5Inch.su ./Core/Src/User_Libs/w25q128.cyclo ./Core/Src/User_Libs/w25q128.d ./Core/Src/User_Libs/w25q128.o ./Core/Src/User_Libs/w25q128.su

.PHONY: clean-Core-2f-Src-2f-User_Libs

