################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/libiec61850/hal/Src/ethernet_stm32.c \
../Modules/libiec61850/hal/Src/lib_memory.c \
../Modules/libiec61850/hal/Src/thread_stm32.c 

OBJS += \
./Modules/libiec61850/hal/Src/ethernet_stm32.o \
./Modules/libiec61850/hal/Src/lib_memory.o \
./Modules/libiec61850/hal/Src/thread_stm32.o 

C_DEPS += \
./Modules/libiec61850/hal/Src/ethernet_stm32.d \
./Modules/libiec61850/hal/Src/lib_memory.d \
./Modules/libiec61850/hal/Src/thread_stm32.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/libiec61850/hal/Src/%.o Modules/libiec61850/hal/Src/%.su Modules/libiec61850/hal/Src/%.cyclo: ../Modules/libiec61850/hal/Src/%.c Modules/libiec61850/hal/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/BSP/Components/dp83848 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Modules/libiec61850/config -I../Modules/libiec61850/hal/Inc -I../Modules/libiec61850/iec61850/Inc -I../Modules/libiec61850/sampled_values -I../Modules/libiec61850/Src/common/Inc -I../Modules/libiec61850/Src/logging -I../Modules/libiec61850/Src/mms/Inc -I../Modules/libiec61850/Src/mms/Inc_private -I"../Modules/SV/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-libiec61850-2f-hal-2f-Src

clean-Modules-2f-libiec61850-2f-hal-2f-Src:
	-$(RM) ./Modules/libiec61850/hal/Src/ethernet_stm32.cyclo ./Modules/libiec61850/hal/Src/ethernet_stm32.d ./Modules/libiec61850/hal/Src/ethernet_stm32.o ./Modules/libiec61850/hal/Src/ethernet_stm32.su ./Modules/libiec61850/hal/Src/lib_memory.cyclo ./Modules/libiec61850/hal/Src/lib_memory.d ./Modules/libiec61850/hal/Src/lib_memory.o ./Modules/libiec61850/hal/Src/lib_memory.su ./Modules/libiec61850/hal/Src/thread_stm32.cyclo ./Modules/libiec61850/hal/Src/thread_stm32.d ./Modules/libiec61850/hal/Src/thread_stm32.o ./Modules/libiec61850/hal/Src/thread_stm32.su

.PHONY: clean-Modules-2f-libiec61850-2f-hal-2f-Src

