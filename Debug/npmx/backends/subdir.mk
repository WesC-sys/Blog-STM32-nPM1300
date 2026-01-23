################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../npmx/backends/npmx_backend.c 

OBJS += \
./npmx/backends/npmx_backend.o 

C_DEPS += \
./npmx/backends/npmx_backend.d 


# Each subdirectory must supply rules for building sources it contributes
npmx/backends/%.o npmx/backends/%.su npmx/backends/%.cyclo: ../npmx/backends/%.c npmx/backends/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNPM1300 -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../npmx/templates -I../npmx -I../npmx/drivers -I../npmx/drivers/src -I../npmx/drivers/include -I../npmx/backends -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-npmx-2f-backends

clean-npmx-2f-backends:
	-$(RM) ./npmx/backends/npmx_backend.cyclo ./npmx/backends/npmx_backend.d ./npmx/backends/npmx_backend.o ./npmx/backends/npmx_backend.su

.PHONY: clean-npmx-2f-backends

