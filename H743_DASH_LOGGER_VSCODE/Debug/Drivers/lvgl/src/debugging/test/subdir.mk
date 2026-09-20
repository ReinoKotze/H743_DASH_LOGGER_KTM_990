################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/debugging/test/lv_test_display.c \
../Drivers/lvgl/src/debugging/test/lv_test_fs.c \
../Drivers/lvgl/src/debugging/test/lv_test_helpers.c \
../Drivers/lvgl/src/debugging/test/lv_test_indev.c \
../Drivers/lvgl/src/debugging/test/lv_test_indev_gesture.c \
../Drivers/lvgl/src/debugging/test/lv_test_screenshot_compare.c 

C_DEPS += \
./Drivers/lvgl/src/debugging/test/lv_test_display.d \
./Drivers/lvgl/src/debugging/test/lv_test_fs.d \
./Drivers/lvgl/src/debugging/test/lv_test_helpers.d \
./Drivers/lvgl/src/debugging/test/lv_test_indev.d \
./Drivers/lvgl/src/debugging/test/lv_test_indev_gesture.d \
./Drivers/lvgl/src/debugging/test/lv_test_screenshot_compare.d 

OBJS += \
./Drivers/lvgl/src/debugging/test/lv_test_display.o \
./Drivers/lvgl/src/debugging/test/lv_test_fs.o \
./Drivers/lvgl/src/debugging/test/lv_test_helpers.o \
./Drivers/lvgl/src/debugging/test/lv_test_indev.o \
./Drivers/lvgl/src/debugging/test/lv_test_indev_gesture.o \
./Drivers/lvgl/src/debugging/test/lv_test_screenshot_compare.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/debugging/test/%.o Drivers/lvgl/src/debugging/test/%.su Drivers/lvgl/src/debugging/test/%.cyclo: ../Drivers/lvgl/src/debugging/test/%.c Drivers/lvgl/src/debugging/test/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-debugging-2f-test

clean-Drivers-2f-lvgl-2f-src-2f-debugging-2f-test:
	-$(RM) ./Drivers/lvgl/src/debugging/test/lv_test_display.cyclo ./Drivers/lvgl/src/debugging/test/lv_test_display.d ./Drivers/lvgl/src/debugging/test/lv_test_display.o ./Drivers/lvgl/src/debugging/test/lv_test_display.su ./Drivers/lvgl/src/debugging/test/lv_test_fs.cyclo ./Drivers/lvgl/src/debugging/test/lv_test_fs.d ./Drivers/lvgl/src/debugging/test/lv_test_fs.o ./Drivers/lvgl/src/debugging/test/lv_test_fs.su ./Drivers/lvgl/src/debugging/test/lv_test_helpers.cyclo ./Drivers/lvgl/src/debugging/test/lv_test_helpers.d ./Drivers/lvgl/src/debugging/test/lv_test_helpers.o ./Drivers/lvgl/src/debugging/test/lv_test_helpers.su ./Drivers/lvgl/src/debugging/test/lv_test_indev.cyclo ./Drivers/lvgl/src/debugging/test/lv_test_indev.d ./Drivers/lvgl/src/debugging/test/lv_test_indev.o ./Drivers/lvgl/src/debugging/test/lv_test_indev.su ./Drivers/lvgl/src/debugging/test/lv_test_indev_gesture.cyclo ./Drivers/lvgl/src/debugging/test/lv_test_indev_gesture.d ./Drivers/lvgl/src/debugging/test/lv_test_indev_gesture.o ./Drivers/lvgl/src/debugging/test/lv_test_indev_gesture.su ./Drivers/lvgl/src/debugging/test/lv_test_screenshot_compare.cyclo ./Drivers/lvgl/src/debugging/test/lv_test_screenshot_compare.d ./Drivers/lvgl/src/debugging/test/lv_test_screenshot_compare.o ./Drivers/lvgl/src/debugging/test/lv_test_screenshot_compare.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-debugging-2f-test

