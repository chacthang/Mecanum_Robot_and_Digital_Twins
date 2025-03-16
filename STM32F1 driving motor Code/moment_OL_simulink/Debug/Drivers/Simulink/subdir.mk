################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Simulink/moment_OL2_genC.c 

OBJS += \
./Drivers/Simulink/moment_OL2_genC.o 

C_DEPS += \
./Drivers/Simulink/moment_OL2_genC.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Simulink/%.o Drivers/Simulink/%.su Drivers/Simulink/%.cyclo: ../Drivers/Simulink/%.c Drivers/Simulink/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/PC/STM32CubeIDE/workspace_1.13.0/moment_OL_simulink/Simulink" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Simulink

clean-Drivers-2f-Simulink:
	-$(RM) ./Drivers/Simulink/moment_OL2_genC.cyclo ./Drivers/Simulink/moment_OL2_genC.d ./Drivers/Simulink/moment_OL2_genC.o ./Drivers/Simulink/moment_OL2_genC.su

.PHONY: clean-Drivers-2f-Simulink

