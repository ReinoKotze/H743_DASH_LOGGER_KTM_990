################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/drivers/wayland/lv_wayland.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_egl_backend.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_g2d_backend.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_keyboard.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_pointer.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_seat.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_shm_backend.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_touch.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_window.c \
../Drivers/lvgl/src/drivers/wayland/lv_wl_xdg_shell.c 

C_DEPS += \
./Drivers/lvgl/src/drivers/wayland/lv_wayland.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_egl_backend.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_g2d_backend.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_keyboard.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_pointer.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_seat.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_shm_backend.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_touch.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_window.d \
./Drivers/lvgl/src/drivers/wayland/lv_wl_xdg_shell.d 

OBJS += \
./Drivers/lvgl/src/drivers/wayland/lv_wayland.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_egl_backend.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_g2d_backend.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_keyboard.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_pointer.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_seat.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_shm_backend.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_touch.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_window.o \
./Drivers/lvgl/src/drivers/wayland/lv_wl_xdg_shell.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/drivers/wayland/%.o Drivers/lvgl/src/drivers/wayland/%.su Drivers/lvgl/src/drivers/wayland/%.cyclo: ../Drivers/lvgl/src/drivers/wayland/%.c Drivers/lvgl/src/drivers/wayland/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-wayland

clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-wayland:
	-$(RM) ./Drivers/lvgl/src/drivers/wayland/lv_wayland.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wayland.d ./Drivers/lvgl/src/drivers/wayland/lv_wayland.o ./Drivers/lvgl/src/drivers/wayland/lv_wayland.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_egl_backend.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_egl_backend.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_egl_backend.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_egl_backend.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_g2d_backend.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_g2d_backend.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_g2d_backend.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_g2d_backend.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_keyboard.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_keyboard.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_keyboard.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_keyboard.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_pointer.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_pointer.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_pointer.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_pointer.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_seat.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_seat.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_seat.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_seat.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_shm_backend.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_shm_backend.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_shm_backend.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_shm_backend.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_touch.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_touch.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_touch.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_touch.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_window.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_window.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_window.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_window.su ./Drivers/lvgl/src/drivers/wayland/lv_wl_xdg_shell.cyclo ./Drivers/lvgl/src/drivers/wayland/lv_wl_xdg_shell.d ./Drivers/lvgl/src/drivers/wayland/lv_wl_xdg_shell.o ./Drivers/lvgl/src/drivers/wayland/lv_wl_xdg_shell.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-wayland

