################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/UI_LOGIC/Buttons.cpp 

C_SRCS += \
../Core/Src/UI_LOGIC/fastFetcher.c \
../Core/Src/UI_LOGIC/slowFetcher.c 

C_DEPS += \
./Core/Src/UI_LOGIC/fastFetcher.d \
./Core/Src/UI_LOGIC/slowFetcher.d 

OBJS += \
./Core/Src/UI_LOGIC/Buttons.o \
./Core/Src/UI_LOGIC/fastFetcher.o \
./Core/Src/UI_LOGIC/slowFetcher.o 

CPP_DEPS += \
./Core/Src/UI_LOGIC/Buttons.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/UI_LOGIC/%.o Core/Src/UI_LOGIC/%.su Core/Src/UI_LOGIC/%.cyclo: ../Core/Src/UI_LOGIC/%.cpp Core/Src/UI_LOGIC/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/Src/UI_LOGIC -I../Core/Inc/User_Libs -I../Core/Src/tasks -I../Core/Src/User_Libs -I../Drivers/lvgl -I../Drivers/UI_Squareline -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/UI_LOGIC/%.o Core/Src/UI_LOGIC/%.su Core/Src/UI_LOGIC/%.cyclo: ../Core/Src/UI_LOGIC/%.c Core/Src/UI_LOGIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-UI_LOGIC

clean-Core-2f-Src-2f-UI_LOGIC:
	-$(RM) ./Core/Src/UI_LOGIC/Buttons.cyclo ./Core/Src/UI_LOGIC/Buttons.d ./Core/Src/UI_LOGIC/Buttons.o ./Core/Src/UI_LOGIC/Buttons.su ./Core/Src/UI_LOGIC/fastFetcher.cyclo ./Core/Src/UI_LOGIC/fastFetcher.d ./Core/Src/UI_LOGIC/fastFetcher.o ./Core/Src/UI_LOGIC/fastFetcher.su ./Core/Src/UI_LOGIC/slowFetcher.cyclo ./Core/Src/UI_LOGIC/slowFetcher.d ./Core/Src/UI_LOGIC/slowFetcher.o ./Core/Src/UI_LOGIC/slowFetcher.su

.PHONY: clean-Core-2f-Src-2f-UI_LOGIC

