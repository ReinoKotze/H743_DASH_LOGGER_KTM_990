################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_esp_littlefs.cpp \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_sd.cpp 

C_SRCS += \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_cbfs.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_fatfs.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_frogfs.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_littlefs.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_memfs.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_posix.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_stdio.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_uefi.c \
../Drivers/lvgl/src/libs/fsdrv/lv_fs_win32.c 

C_DEPS += \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_cbfs.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_fatfs.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_frogfs.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_littlefs.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_memfs.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_posix.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_stdio.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_uefi.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_win32.d 

OBJS += \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_esp_littlefs.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_sd.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_cbfs.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_fatfs.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_frogfs.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_littlefs.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_memfs.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_posix.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_stdio.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_uefi.o \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_win32.o 

CPP_DEPS += \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_esp_littlefs.d \
./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_sd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/libs/fsdrv/%.o Drivers/lvgl/src/libs/fsdrv/%.su Drivers/lvgl/src/libs/fsdrv/%.cyclo: ../Drivers/lvgl/src/libs/fsdrv/%.cpp Drivers/lvgl/src/libs/fsdrv/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/Src/UI_LOGIC -I../Core/Inc/User_Libs -I../Core/Src/tasks -I../Core/Src/User_Libs -I../Drivers/lvgl -I../Drivers/UI_Squareline -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/lvgl/src/libs/fsdrv/%.o Drivers/lvgl/src/libs/fsdrv/%.su Drivers/lvgl/src/libs/fsdrv/%.cyclo: ../Drivers/lvgl/src/libs/fsdrv/%.c Drivers/lvgl/src/libs/fsdrv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-fsdrv

clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-fsdrv:
	-$(RM) ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_esp_littlefs.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_esp_littlefs.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_esp_littlefs.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_esp_littlefs.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_sd.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_sd.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_sd.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_arduino_sd.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_cbfs.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_cbfs.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_cbfs.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_cbfs.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_fatfs.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_fatfs.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_fatfs.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_fatfs.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_frogfs.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_frogfs.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_frogfs.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_frogfs.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_littlefs.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_littlefs.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_littlefs.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_littlefs.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_memfs.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_memfs.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_memfs.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_memfs.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_posix.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_posix.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_posix.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_posix.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_stdio.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_stdio.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_stdio.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_stdio.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_uefi.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_uefi.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_uefi.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_uefi.su ./Drivers/lvgl/src/libs/fsdrv/lv_fs_win32.cyclo ./Drivers/lvgl/src/libs/fsdrv/lv_fs_win32.d ./Drivers/lvgl/src/libs/fsdrv/lv_fs_win32.o ./Drivers/lvgl/src/libs/fsdrv/lv_fs_win32.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-fsdrv

