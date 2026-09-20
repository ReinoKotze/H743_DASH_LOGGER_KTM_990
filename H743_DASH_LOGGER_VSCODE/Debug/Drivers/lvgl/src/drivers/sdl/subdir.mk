################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_egl.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_sw.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_texture.c \
../Drivers/lvgl/src/drivers/sdl/lv_sdl_window.c 

C_DEPS += \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_egl.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_sw.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_texture.d \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.d 

OBJS += \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_egl.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_sw.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_texture.o \
./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/drivers/sdl/%.o Drivers/lvgl/src/drivers/sdl/%.su Drivers/lvgl/src/drivers/sdl/%.cyclo: ../Drivers/lvgl/src/drivers/sdl/%.c Drivers/lvgl/src/drivers/sdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-sdl

clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-sdl:
	-$(RM) ./Drivers/lvgl/src/drivers/sdl/lv_sdl_egl.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_egl.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_egl.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_egl.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_keyboard.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mouse.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_mousewheel.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_sw.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_sw.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_sw.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_sw.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_texture.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_texture.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_texture.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_texture.su ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.cyclo ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.d ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.o ./Drivers/lvgl/src/drivers/sdl/lv_sdl_window.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-sdl

