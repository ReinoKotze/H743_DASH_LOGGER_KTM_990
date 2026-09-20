################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI_Squareline/ui.c \
../Drivers/UI_Squareline/ui_helpers.c 

C_DEPS += \
./Drivers/UI_Squareline/ui.d \
./Drivers/UI_Squareline/ui_helpers.d 

OBJS += \
./Drivers/UI_Squareline/ui.o \
./Drivers/UI_Squareline/ui_helpers.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI_Squareline/%.o Drivers/UI_Squareline/%.su Drivers/UI_Squareline/%.cyclo: ../Drivers/UI_Squareline/%.c Drivers/UI_Squareline/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI_Squareline

clean-Drivers-2f-UI_Squareline:
	-$(RM) ./Drivers/UI_Squareline/ui.cyclo ./Drivers/UI_Squareline/ui.d ./Drivers/UI_Squareline/ui.o ./Drivers/UI_Squareline/ui.su ./Drivers/UI_Squareline/ui_helpers.cyclo ./Drivers/UI_Squareline/ui_helpers.d ./Drivers/UI_Squareline/ui_helpers.o ./Drivers/UI_Squareline/ui_helpers.su

.PHONY: clean-Drivers-2f-UI_Squareline

