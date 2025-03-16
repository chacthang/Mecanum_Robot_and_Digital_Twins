################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/kalman/kalman.c 

OBJS += \
./Drivers/kalman/kalman.o 

C_DEPS += \
./Drivers/kalman/kalman.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/kalman/%.o Drivers/kalman/%.su Drivers/kalman/%.cyclo: ../Drivers/kalman/%.c Drivers/kalman/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"E:/232/z Luan Van/stm32f4/f411_test_imu_uwb/f411_test_imu_uwb/simulink" -I"E:/232/z Luan Van/stm32f4/f411_test_imu_uwb/f411_test_imu_uwb/kalman" -I../Core/Inc -I"E:/232/z Luan Van/stm32f4/f411_test_imu_uwb/f411_test_imu_uwb/bno055_stm32-master" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-kalman

clean-Drivers-2f-kalman:
	-$(RM) ./Drivers/kalman/kalman.cyclo ./Drivers/kalman/kalman.d ./Drivers/kalman/kalman.o ./Drivers/kalman/kalman.su

.PHONY: clean-Drivers-2f-kalman

