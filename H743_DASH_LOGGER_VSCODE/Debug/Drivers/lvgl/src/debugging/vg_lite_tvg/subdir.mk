################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_tvg.cpp 

C_SRCS += \
../Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_matrix.c 

C_DEPS += \
./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_matrix.d 

OBJS += \
./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_matrix.o \
./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_tvg.o 

CPP_DEPS += \
./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_tvg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/debugging/vg_lite_tvg/%.o Drivers/lvgl/src/debugging/vg_lite_tvg/%.su Drivers/lvgl/src/debugging/vg_lite_tvg/%.cyclo: ../Drivers/lvgl/src/debugging/vg_lite_tvg/%.c Drivers/lvgl/src/debugging/vg_lite_tvg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/lvgl/src/debugging/vg_lite_tvg/%.o Drivers/lvgl/src/debugging/vg_lite_tvg/%.su Drivers/lvgl/src/debugging/vg_lite_tvg/%.cyclo: ../Drivers/lvgl/src/debugging/vg_lite_tvg/%.cpp Drivers/lvgl/src/debugging/vg_lite_tvg/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/Src/UI_LOGIC -I../Core/Inc/User_Libs -I../Core/Src/tasks -I../Core/Src/User_Libs -I../Drivers/lvgl -I../Drivers/UI_Squareline -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-debugging-2f-vg_lite_tvg

clean-Drivers-2f-lvgl-2f-src-2f-debugging-2f-vg_lite_tvg:
	-$(RM) ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_matrix.cyclo ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_matrix.d ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_matrix.o ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_matrix.su ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_tvg.cyclo ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_tvg.d ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_tvg.o ./Drivers/lvgl/src/debugging/vg_lite_tvg/vg_lite_tvg.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-debugging-2f-vg_lite_tvg

