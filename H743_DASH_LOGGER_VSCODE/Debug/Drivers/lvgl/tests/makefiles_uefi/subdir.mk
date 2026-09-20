################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/tests/makefiles_uefi/test.c 

C_DEPS += \
./Drivers/lvgl/tests/makefiles_uefi/test.d 

OBJS += \
./Drivers/lvgl/tests/makefiles_uefi/test.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/tests/makefiles_uefi/%.o Drivers/lvgl/tests/makefiles_uefi/%.su Drivers/lvgl/tests/makefiles_uefi/%.cyclo: ../Drivers/lvgl/tests/makefiles_uefi/%.c Drivers/lvgl/tests/makefiles_uefi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/tasks" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-tests-2f-makefiles_uefi

clean-Drivers-2f-lvgl-2f-tests-2f-makefiles_uefi:
	-$(RM) ./Drivers/lvgl/tests/makefiles_uefi/test.cyclo ./Drivers/lvgl/tests/makefiles_uefi/test.d ./Drivers/lvgl/tests/makefiles_uefi/test.o ./Drivers/lvgl/tests/makefiles_uefi/test.su

.PHONY: clean-Drivers-2f-lvgl-2f-tests-2f-makefiles_uefi

