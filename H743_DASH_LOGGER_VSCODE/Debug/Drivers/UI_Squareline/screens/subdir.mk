################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI_Squareline/screens/ui_Normal.c \
../Drivers/UI_Squareline/screens/ui_RAWsensor.c 

C_DEPS += \
./Drivers/UI_Squareline/screens/ui_Normal.d \
./Drivers/UI_Squareline/screens/ui_RAWsensor.d 

OBJS += \
./Drivers/UI_Squareline/screens/ui_Normal.o \
./Drivers/UI_Squareline/screens/ui_RAWsensor.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI_Squareline/screens/%.o Drivers/UI_Squareline/screens/%.su Drivers/UI_Squareline/screens/%.cyclo: ../Drivers/UI_Squareline/screens/%.c Drivers/UI_Squareline/screens/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI_Squareline-2f-screens

clean-Drivers-2f-UI_Squareline-2f-screens:
	-$(RM) ./Drivers/UI_Squareline/screens/ui_Normal.cyclo ./Drivers/UI_Squareline/screens/ui_Normal.d ./Drivers/UI_Squareline/screens/ui_Normal.o ./Drivers/UI_Squareline/screens/ui_Normal.su ./Drivers/UI_Squareline/screens/ui_RAWsensor.cyclo ./Drivers/UI_Squareline/screens/ui_RAWsensor.d ./Drivers/UI_Squareline/screens/ui_RAWsensor.o ./Drivers/UI_Squareline/screens/ui_RAWsensor.su

.PHONY: clean-Drivers-2f-UI_Squareline-2f-screens

