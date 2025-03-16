################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/simulink/dynamic_circle_3.c 

OBJS += \
./Drivers/simulink/dynamic_circle_3.o 

C_DEPS += \
./Drivers/simulink/dynamic_circle_3.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/simulink/%.o Drivers/simulink/%.su Drivers/simulink/%.cyclo: ../Drivers/simulink/%.c Drivers/simulink/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/THANH/HK232/DoAnTN/f411_test_imu_uwb/f411_test_imu_uwb/f411_test_imu_uwb/simulink" -I"D:/THANH/HK232/DoAnTN/f411_test_imu_uwb/f411_test_imu_uwb/f411_test_imu_uwb/bno055_stm32-master" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-simulink

clean-Drivers-2f-simulink:
	-$(RM) ./Drivers/simulink/dynamic_circle_3.cyclo ./Drivers/simulink/dynamic_circle_3.d ./Drivers/simulink/dynamic_circle_3.o ./Drivers/simulink/dynamic_circle_3.su

.PHONY: clean-Drivers-2f-simulink

