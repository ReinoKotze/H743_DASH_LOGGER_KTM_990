################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_animations.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_cache.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_injest.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_mesh.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_primitive.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_shader.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_skin.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_texture.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_model_node.cpp \
../Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_uniform_locations.cpp 

OBJS += \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_animations.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_cache.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_injest.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_mesh.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_primitive.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_shader.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_skin.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_texture.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_model_node.o \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_uniform_locations.o 

CPP_DEPS += \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_animations.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_cache.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_injest.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_mesh.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_primitive.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_shader.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_skin.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_texture.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_model_node.d \
./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_uniform_locations.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/libs/gltf/gltf_data/%.o Drivers/lvgl/src/libs/gltf/gltf_data/%.su Drivers/lvgl/src/libs/gltf/gltf_data/%.cyclo: ../Drivers/lvgl/src/libs/gltf/gltf_data/%.cpp Drivers/lvgl/src/libs/gltf/gltf_data/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Core/Src/UI_LOGIC -I../Core/Inc/User_Libs -I../Core/Src/tasks -I../Core/Src/User_Libs -I../Drivers/lvgl -I../Drivers/UI_Squareline -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-gltf-2f-gltf_data

clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-gltf-2f-gltf_data:
	-$(RM) ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_animations.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_animations.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_animations.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_animations.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_cache.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_cache.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_cache.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_cache.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_injest.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_injest.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_injest.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_injest.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_mesh.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_mesh.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_mesh.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_mesh.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_primitive.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_primitive.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_primitive.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_primitive.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_shader.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_shader.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_shader.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_shader.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_skin.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_skin.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_skin.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_skin.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_texture.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_texture.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_texture.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_data_texture.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_model_node.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_model_node.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_model_node.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_model_node.su ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_uniform_locations.cyclo ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_uniform_locations.d ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_uniform_locations.o ./Drivers/lvgl/src/libs/gltf/gltf_data/lv_gltf_uniform_locations.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-gltf-2f-gltf_data

