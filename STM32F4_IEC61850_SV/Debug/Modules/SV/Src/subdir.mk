################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/SV/Src/IEC61850_SV.c 

OBJS += \
./Modules/SV/Src/IEC61850_SV.o 

C_DEPS += \
./Modules/SV/Src/IEC61850_SV.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/SV/Src/%.o Modules/SV/Src/%.su Modules/SV/Src/%.cyclo: ../Modules/SV/Src/%.c Modules/SV/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/BSP/Components/dp83848 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Modules/libiec61850/config -I../Modules/libiec61850/hal/Inc -I../Modules/libiec61850/iec61850/Inc -I../Modules/libiec61850/sampled_values -I../Modules/libiec61850/Src/common/Inc -I../Modules/libiec61850/Src/logging -I../Modules/libiec61850/Src/mms/Inc -I../Modules/libiec61850/Src/mms/Inc_private -I"../Modules/SV/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-SV-2f-Src

clean-Modules-2f-SV-2f-Src:
	-$(RM) ./Modules/SV/Src/IEC61850_SV.cyclo ./Modules/SV/Src/IEC61850_SV.d ./Modules/SV/Src/IEC61850_SV.o ./Modules/SV/Src/IEC61850_SV.su

.PHONY: clean-Modules-2f-SV-2f-Src

