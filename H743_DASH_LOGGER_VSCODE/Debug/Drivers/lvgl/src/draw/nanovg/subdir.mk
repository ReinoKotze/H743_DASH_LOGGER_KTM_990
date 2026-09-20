################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_3d.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_arc.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_border.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_fill.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_grad.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_image.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_label.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_layer.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_line.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.c \
../Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_vector.c \
../Drivers/lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.c \
../Drivers/lvgl/src/draw/nanovg/lv_nanovg_image_cache.c \
../Drivers/lvgl/src/draw/nanovg/lv_nanovg_utils.c 

C_DEPS += \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_3d.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_arc.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_border.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_fill.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_grad.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_image.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_label.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_layer.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_line.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.d \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_vector.d \
./Drivers/lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.d \
./Drivers/lvgl/src/draw/nanovg/lv_nanovg_image_cache.d \
./Drivers/lvgl/src/draw/nanovg/lv_nanovg_utils.d 

OBJS += \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_3d.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_arc.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_border.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_fill.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_grad.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_image.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_label.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_layer.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_line.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.o \
./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_vector.o \
./Drivers/lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.o \
./Drivers/lvgl/src/draw/nanovg/lv_nanovg_image_cache.o \
./Drivers/lvgl/src/draw/nanovg/lv_nanovg_utils.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/draw/nanovg/%.o Drivers/lvgl/src/draw/nanovg/%.su Drivers/lvgl/src/draw/nanovg/%.cyclo: ../Drivers/lvgl/src/draw/nanovg/%.c Drivers/lvgl/src/draw/nanovg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/UI_LOGIC" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Inc/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Core/Src/User_Libs" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/lvgl" -I"C:/Users/reino/git/KTM/H743_DASH_LOGGER_KTM_990/H743_DASH_LOGGER/Drivers/UI_Squareline" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nanovg

clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nanovg:
	-$(RM) ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_3d.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_3d.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_3d.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_3d.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_arc.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_arc.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_arc.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_arc.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_border.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_border.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_border.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_border.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_fill.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_fill.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_fill.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_fill.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_grad.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_grad.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_grad.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_grad.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_image.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_image.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_image.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_image.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_label.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_label.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_label.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_label.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_layer.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_layer.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_layer.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_layer.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_line.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_line.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_line.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_line.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.su ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_vector.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_vector.d ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_vector.o ./Drivers/lvgl/src/draw/nanovg/lv_draw_nanovg_vector.su ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.d ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.o ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.su ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_image_cache.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_image_cache.d ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_image_cache.o ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_image_cache.su ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_utils.cyclo ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_utils.d ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_utils.o ./Drivers/lvgl/src/draw/nanovg/lv_nanovg_utils.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nanovg

