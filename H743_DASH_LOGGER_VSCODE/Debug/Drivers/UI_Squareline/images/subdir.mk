################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI_Squareline/images/ui_img_1414997601.c \
../Drivers/UI_Squareline/images/ui_img_ecu_warning__1_png.c \
../Drivers/UI_Squareline/images/ui_img_fi_orange_png.c \
../Drivers/UI_Squareline/images/ui_img_front_wheel_png.c \
../Drivers/UI_Squareline/images/ui_img_pngegg_png.c \
../Drivers/UI_Squareline/images/ui_img_rear_wheel_png.c 

C_DEPS += \
./Drivers/UI_Squareline/images/ui_img_1414997601.d \
./Drivers/UI_Squareline/images/ui_img_ecu_warning__1_png.d \
./Drivers/UI_Squareline/images/ui_img_fi_orange_png.d \
./Drivers/UI_Squareline/images/ui_img_front_wheel_png.d \
./Drivers/UI_Squareline/images/ui_img_pngegg_png.d \
./Drivers/UI_Squareline/images/ui_img_rear_wheel_png.d 

OBJS += \
./Drivers/UI_Squareline/images/ui_img_1414997601.o \
./Drivers/UI_Squareline/images/ui_img_ecu_warning__1_png.o \
./Drivers/UI_Squareline/images/ui_img_fi_orange_png.o \
./Drivers/UI_Squareline/images/ui_img_front_wheel_png.o \
./Drivers/UI_Squareline/images/ui_img_pngegg_png.o \
./Drivers/UI_Squareline/images/ui_img_rear_wheel_png.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI_Squareline/images/%.o Drivers/UI_Squareline/images/%.su Drivers/UI_Squareline/images/%.cyclo: ../Drivers/UI_Squareline/images/%.c Drivers/UI_Squareline/images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI_Squareline-2f-images

clean-Drivers-2f-UI_Squareline-2f-images:
	-$(RM) ./Drivers/UI_Squareline/images/ui_img_1414997601.cyclo ./Drivers/UI_Squareline/images/ui_img_1414997601.d ./Drivers/UI_Squareline/images/ui_img_1414997601.o ./Drivers/UI_Squareline/images/ui_img_1414997601.su ./Drivers/UI_Squareline/images/ui_img_ecu_warning__1_png.cyclo ./Drivers/UI_Squareline/images/ui_img_ecu_warning__1_png.d ./Drivers/UI_Squareline/images/ui_img_ecu_warning__1_png.o ./Drivers/UI_Squareline/images/ui_img_ecu_warning__1_png.su ./Drivers/UI_Squareline/images/ui_img_fi_orange_png.cyclo ./Drivers/UI_Squareline/images/ui_img_fi_orange_png.d ./Drivers/UI_Squareline/images/ui_img_fi_orange_png.o ./Drivers/UI_Squareline/images/ui_img_fi_orange_png.su ./Drivers/UI_Squareline/images/ui_img_front_wheel_png.cyclo ./Drivers/UI_Squareline/images/ui_img_front_wheel_png.d ./Drivers/UI_Squareline/images/ui_img_front_wheel_png.o ./Drivers/UI_Squareline/images/ui_img_front_wheel_png.su ./Drivers/UI_Squareline/images/ui_img_pngegg_png.cyclo ./Drivers/UI_Squareline/images/ui_img_pngegg_png.d ./Drivers/UI_Squareline/images/ui_img_pngegg_png.o ./Drivers/UI_Squareline/images/ui_img_pngegg_png.su ./Drivers/UI_Squareline/images/ui_img_rear_wheel_png.cyclo ./Drivers/UI_Squareline/images/ui_img_rear_wheel_png.d ./Drivers/UI_Squareline/images/ui_img_rear_wheel_png.o ./Drivers/UI_Squareline/images/ui_img_rear_wheel_png.su

.PHONY: clean-Drivers-2f-UI_Squareline-2f-images

