################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/dp83848/dp83848.c 

OBJS += \
./Drivers/BSP/Components/dp83848/dp83848.o 

C_DEPS += \
./Drivers/BSP/Components/dp83848/dp83848.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/dp83848/%.o Drivers/BSP/Components/dp83848/%.su Drivers/BSP/Components/dp83848/%.cyclo: ../Drivers/BSP/Components/dp83848/%.c Drivers/BSP/Components/dp83848/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/BSP/Components/dp83848 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Modules/libiec61850/config -I../Modules/libiec61850/hal/Inc -I../Modules/libiec61850/iec61850/Inc -I../Modules/libiec61850/sampled_values -I../Modules/libiec61850/Src/common/Inc -I../Modules/libiec61850/Src/logging -I../Modules/libiec61850/Src/mms/Inc -I../Modules/libiec61850/Src/mms/Inc_private -I"../Modules/SV/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-dp83848

clean-Drivers-2f-BSP-2f-Components-2f-dp83848:
	-$(RM) ./Drivers/BSP/Components/dp83848/dp83848.cyclo ./Drivers/BSP/Components/dp83848/dp83848.d ./Drivers/BSP/Components/dp83848/dp83848.o ./Drivers/BSP/Components/dp83848/dp83848.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-dp83848

