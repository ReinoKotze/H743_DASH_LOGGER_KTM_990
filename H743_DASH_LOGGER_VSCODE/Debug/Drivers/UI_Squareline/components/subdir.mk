################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI_Squareline/components/ui_comp_hook.c 

C_DEPS += \
./Drivers/UI_Squareline/components/ui_comp_hook.d 

OBJS += \
./Drivers/UI_Squareline/components/ui_comp_hook.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI_Squareline/components/%.o Drivers/UI_Squareline/components/%.su Drivers/UI_Squareline/components/%.cyclo: ../Drivers/UI_Squareline/components/%.c Drivers/UI_Squareline/components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI_Squareline-2f-components

clean-Drivers-2f-UI_Squareline-2f-components:
	-$(RM) ./Drivers/UI_Squareline/components/ui_comp_hook.cyclo ./Drivers/UI_Squareline/components/ui_comp_hook.d ./Drivers/UI_Squareline/components/ui_comp_hook.o ./Drivers/UI_Squareline/components/ui_comp_hook.su

.PHONY: clean-Drivers-2f-UI_Squareline-2f-components

