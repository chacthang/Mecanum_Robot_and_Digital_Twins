################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/imu/bno055.c 

OBJS += \
./Drivers/imu/bno055.o 

C_DEPS += \
./Drivers/imu/bno055.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/imu/%.o Drivers/imu/%.su Drivers/imu/%.cyclo: ../Drivers/imu/%.c Drivers/imu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/THANH/HK232/DoAnTN/f411_test_imu_uwb/f411_test_imu_uwb/f411_test_imu_uwb/simulink" -I"D:/THANH/HK232/DoAnTN/f411_test_imu_uwb/f411_test_imu_uwb/f411_test_imu_uwb/bno055_stm32-master" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-imu

clean-Drivers-2f-imu:
	-$(RM) ./Drivers/imu/bno055.cyclo ./Drivers/imu/bno055.d ./Drivers/imu/bno055.o ./Drivers/imu/bno055.su

.PHONY: clean-Drivers-2f-imu

