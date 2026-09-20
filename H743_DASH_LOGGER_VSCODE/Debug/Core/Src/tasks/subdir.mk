################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/tasks/Buttons.c \
../Core/Src/tasks/fastFetcher.c \
../Core/Src/tasks/slowFetcher.c 

C_DEPS += \
./Core/Src/tasks/Buttons.d \
./Core/Src/tasks/fastFetcher.d \
./Core/Src/tasks/slowFetcher.d 

OBJS += \
./Core/Src/tasks/Buttons.o \
./Core/Src/tasks/fastFetcher.o \
./Core/Src/tasks/slowFetcher.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/tasks/%.o Core/Src/tasks/%.su Core/Src/tasks/%.cyclo: ../Core/Src/tasks/%.c Core/Src/tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/tasks" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-tasks

clean-Core-2f-Src-2f-tasks:
	-$(RM) ./Core/Src/tasks/Buttons.cyclo ./Core/Src/tasks/Buttons.d ./Core/Src/tasks/Buttons.o ./Core/Src/tasks/Buttons.su ./Core/Src/tasks/fastFetcher.cyclo ./Core/Src/tasks/fastFetcher.d ./Core/Src/tasks/fastFetcher.o ./Core/Src/tasks/fastFetcher.su ./Core/Src/tasks/slowFetcher.cyclo ./Core/Src/tasks/slowFetcher.d ./Core/Src/tasks/slowFetcher.o ./Core/Src/tasks/slowFetcher.su

.PHONY: clean-Core-2f-Src-2f-tasks

