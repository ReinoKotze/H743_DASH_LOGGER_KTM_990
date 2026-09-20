################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/demos/widgets/lv_demo_widgets.c \
../Drivers/lvgl/demos/widgets/lv_demo_widgets_analytics.c \
../Drivers/lvgl/demos/widgets/lv_demo_widgets_components.c \
../Drivers/lvgl/demos/widgets/lv_demo_widgets_profile.c \
../Drivers/lvgl/demos/widgets/lv_demo_widgets_shop.c 

C_DEPS += \
./Drivers/lvgl/demos/widgets/lv_demo_widgets.d \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_analytics.d \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_components.d \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_profile.d \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_shop.d 

OBJS += \
./Drivers/lvgl/demos/widgets/lv_demo_widgets.o \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_analytics.o \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_components.o \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_profile.o \
./Drivers/lvgl/demos/widgets/lv_demo_widgets_shop.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/demos/widgets/%.o Drivers/lvgl/demos/widgets/%.su Drivers/lvgl/demos/widgets/%.cyclo: ../Drivers/lvgl/demos/widgets/%.c Drivers/lvgl/demos/widgets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-demos-2f-widgets

clean-Drivers-2f-lvgl-2f-demos-2f-widgets:
	-$(RM) ./Drivers/lvgl/demos/widgets/lv_demo_widgets.cyclo ./Drivers/lvgl/demos/widgets/lv_demo_widgets.d ./Drivers/lvgl/demos/widgets/lv_demo_widgets.o ./Drivers/lvgl/demos/widgets/lv_demo_widgets.su ./Drivers/lvgl/demos/widgets/lv_demo_widgets_analytics.cyclo ./Drivers/lvgl/demos/widgets/lv_demo_widgets_analytics.d ./Drivers/lvgl/demos/widgets/lv_demo_widgets_analytics.o ./Drivers/lvgl/demos/widgets/lv_demo_widgets_analytics.su ./Drivers/lvgl/demos/widgets/lv_demo_widgets_components.cyclo ./Drivers/lvgl/demos/widgets/lv_demo_widgets_components.d ./Drivers/lvgl/demos/widgets/lv_demo_widgets_components.o ./Drivers/lvgl/demos/widgets/lv_demo_widgets_components.su ./Drivers/lvgl/demos/widgets/lv_demo_widgets_profile.cyclo ./Drivers/lvgl/demos/widgets/lv_demo_widgets_profile.d ./Drivers/lvgl/demos/widgets/lv_demo_widgets_profile.o ./Drivers/lvgl/demos/widgets/lv_demo_widgets_profile.su ./Drivers/lvgl/demos/widgets/lv_demo_widgets_shop.cyclo ./Drivers/lvgl/demos/widgets/lv_demo_widgets_shop.d ./Drivers/lvgl/demos/widgets/lv_demo_widgets_shop.o ./Drivers/lvgl/demos/widgets/lv_demo_widgets_shop.su

.PHONY: clean-Drivers-2f-lvgl-2f-demos-2f-widgets

