################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/lvgl/src/drivers/display/lovyan_gfx/lv_lovyan_gfx.cpp 

OBJS += \
./Drivers/lvgl/src/drivers/display/lovyan_gfx/lv_lovyan_gfx.o 

CPP_DEPS += \
./Drivers/lvgl/src/drivers/display/lovyan_gfx/lv_lovyan_gfx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/drivers/display/lovyan_gfx/%.o Drivers/lvgl/src/drivers/display/lovyan_gfx/%.su Drivers/lvgl/src/drivers/display/lovyan_gfx/%.cyclo: ../Drivers/lvgl/src/drivers/display/lovyan_gfx/%.cpp Drivers/lvgl/src/drivers/display/lovyan_gfx/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/Src/UI_LOGIC -I../Core/Inc/User_Libs -I../Core/Src/tasks -I../Core/Src/User_Libs -I../Drivers/lvgl -I../Drivers/UI_Squareline -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-display-2f-lovyan_gfx

clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-display-2f-lovyan_gfx:
	-$(RM) ./Drivers/lvgl/src/drivers/display/lovyan_gfx/lv_lovyan_gfx.cyclo ./Drivers/lvgl/src/drivers/display/lovyan_gfx/lv_lovyan_gfx.d ./Drivers/lvgl/src/drivers/display/lovyan_gfx/lv_lovyan_gfx.o ./Drivers/lvgl/src/drivers/display/lovyan_gfx/lv_lovyan_gfx.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-display-2f-lovyan_gfx

