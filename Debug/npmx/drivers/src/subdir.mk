################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../npmx/drivers/src/npmx_adc.c \
../npmx/drivers/src/npmx_buck.c \
../npmx/drivers/src/npmx_charger.c \
../npmx/drivers/src/npmx_common.c \
../npmx/drivers/src/npmx_core.c \
../npmx/drivers/src/npmx_errlog.c \
../npmx/drivers/src/npmx_gpio.c \
../npmx/drivers/src/npmx_ldsw.c \
../npmx/drivers/src/npmx_led.c \
../npmx/drivers/src/npmx_pof.c \
../npmx/drivers/src/npmx_ship.c \
../npmx/drivers/src/npmx_timer.c \
../npmx/drivers/src/npmx_vbusin.c 

OBJS += \
./npmx/drivers/src/npmx_adc.o \
./npmx/drivers/src/npmx_buck.o \
./npmx/drivers/src/npmx_charger.o \
./npmx/drivers/src/npmx_common.o \
./npmx/drivers/src/npmx_core.o \
./npmx/drivers/src/npmx_errlog.o \
./npmx/drivers/src/npmx_gpio.o \
./npmx/drivers/src/npmx_ldsw.o \
./npmx/drivers/src/npmx_led.o \
./npmx/drivers/src/npmx_pof.o \
./npmx/drivers/src/npmx_ship.o \
./npmx/drivers/src/npmx_timer.o \
./npmx/drivers/src/npmx_vbusin.o 

C_DEPS += \
./npmx/drivers/src/npmx_adc.d \
./npmx/drivers/src/npmx_buck.d \
./npmx/drivers/src/npmx_charger.d \
./npmx/drivers/src/npmx_common.d \
./npmx/drivers/src/npmx_core.d \
./npmx/drivers/src/npmx_errlog.d \
./npmx/drivers/src/npmx_gpio.d \
./npmx/drivers/src/npmx_ldsw.d \
./npmx/drivers/src/npmx_led.d \
./npmx/drivers/src/npmx_pof.d \
./npmx/drivers/src/npmx_ship.d \
./npmx/drivers/src/npmx_timer.d \
./npmx/drivers/src/npmx_vbusin.d 


# Each subdirectory must supply rules for building sources it contributes
npmx/drivers/src/%.o npmx/drivers/src/%.su npmx/drivers/src/%.cyclo: ../npmx/drivers/src/%.c npmx/drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNPM1300 -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../npmx/templates -I../npmx -I../npmx/drivers -I../npmx/drivers/src -I../npmx/drivers/include -I../npmx/backends -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-npmx-2f-drivers-2f-src

clean-npmx-2f-drivers-2f-src:
	-$(RM) ./npmx/drivers/src/npmx_adc.cyclo ./npmx/drivers/src/npmx_adc.d ./npmx/drivers/src/npmx_adc.o ./npmx/drivers/src/npmx_adc.su ./npmx/drivers/src/npmx_buck.cyclo ./npmx/drivers/src/npmx_buck.d ./npmx/drivers/src/npmx_buck.o ./npmx/drivers/src/npmx_buck.su ./npmx/drivers/src/npmx_charger.cyclo ./npmx/drivers/src/npmx_charger.d ./npmx/drivers/src/npmx_charger.o ./npmx/drivers/src/npmx_charger.su ./npmx/drivers/src/npmx_common.cyclo ./npmx/drivers/src/npmx_common.d ./npmx/drivers/src/npmx_common.o ./npmx/drivers/src/npmx_common.su ./npmx/drivers/src/npmx_core.cyclo ./npmx/drivers/src/npmx_core.d ./npmx/drivers/src/npmx_core.o ./npmx/drivers/src/npmx_core.su ./npmx/drivers/src/npmx_errlog.cyclo ./npmx/drivers/src/npmx_errlog.d ./npmx/drivers/src/npmx_errlog.o ./npmx/drivers/src/npmx_errlog.su ./npmx/drivers/src/npmx_gpio.cyclo ./npmx/drivers/src/npmx_gpio.d ./npmx/drivers/src/npmx_gpio.o ./npmx/drivers/src/npmx_gpio.su ./npmx/drivers/src/npmx_ldsw.cyclo ./npmx/drivers/src/npmx_ldsw.d ./npmx/drivers/src/npmx_ldsw.o ./npmx/drivers/src/npmx_ldsw.su ./npmx/drivers/src/npmx_led.cyclo ./npmx/drivers/src/npmx_led.d ./npmx/drivers/src/npmx_led.o ./npmx/drivers/src/npmx_led.su ./npmx/drivers/src/npmx_pof.cyclo ./npmx/drivers/src/npmx_pof.d ./npmx/drivers/src/npmx_pof.o ./npmx/drivers/src/npmx_pof.su ./npmx/drivers/src/npmx_ship.cyclo ./npmx/drivers/src/npmx_ship.d ./npmx/drivers/src/npmx_ship.o ./npmx/drivers/src/npmx_ship.su ./npmx/drivers/src/npmx_timer.cyclo ./npmx/drivers/src/npmx_timer.d ./npmx/drivers/src/npmx_timer.o ./npmx/drivers/src/npmx_timer.su ./npmx/drivers/src/npmx_vbusin.cyclo ./npmx/drivers/src/npmx_vbusin.d ./npmx/drivers/src/npmx_vbusin.o ./npmx/drivers/src/npmx_vbusin.su

.PHONY: clean-npmx-2f-drivers-2f-src

