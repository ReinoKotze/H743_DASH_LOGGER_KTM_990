################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_render.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_shader.cpp 

OBJS += \
./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view.o \
./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_render.o \
./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_shader.o 

CPP_DEPS += \
./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view.d \
./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_render.d \
./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_shader.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/libs/gltf/gltf_view/%.o Drivers/lvgl/src/libs/gltf/gltf_view/%.su Drivers/lvgl/src/libs/gltf/gltf_view/%.cyclo: ../Drivers/lvgl/src/libs/gltf/gltf_view/%.cpp Drivers/lvgl/src/libs/gltf/gltf_view/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/Src/UI_LOGIC -I../Core/Inc/User_Libs -I../Core/Src/tasks -I../Core/Src/User_Libs -I../Drivers/lvgl -I../Drivers/UI_Squareline -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-gltf-2f-gltf_view

clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-gltf-2f-gltf_view:
	-$(RM) ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view.d ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view.o ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view.su ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_render.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_render.d ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_render.o ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_render.su ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_shader.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_shader.d ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_shader.o ./Drivers/lvgl/src/libs/gltf/gltf_view/lv_gltf_view_shader.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-gltf-2f-gltf_view

