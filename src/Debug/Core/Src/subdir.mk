################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Counter.c \
../Core/Src/encoder.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/motorcontrol.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/task1.c \
../Core/Src/task2.c \
../Core/Src/task3.c \
../Core/Src/task4.c \
../Core/Src/task5.c \
../Core/Src/task6.c 

OBJS += \
./Core/Src/Counter.o \
./Core/Src/encoder.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/motorcontrol.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/task1.o \
./Core/Src/task2.o \
./Core/Src/task3.o \
./Core/Src/task4.o \
./Core/Src/task5.o \
./Core/Src/task6.o 

C_DEPS += \
./Core/Src/Counter.d \
./Core/Src/encoder.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/motorcontrol.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/task1.d \
./Core/Src/task2.d \
./Core/Src/task3.d \
./Core/Src/task4.d \
./Core/Src/task5.d \
./Core/Src/task6.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L471xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Counter.cyclo ./Core/Src/Counter.d ./Core/Src/Counter.o ./Core/Src/Counter.su ./Core/Src/encoder.cyclo ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor.cyclo ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/motorcontrol.cyclo ./Core/Src/motorcontrol.d ./Core/Src/motorcontrol.o ./Core/Src/motorcontrol.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/task1.cyclo ./Core/Src/task1.d ./Core/Src/task1.o ./Core/Src/task1.su ./Core/Src/task2.cyclo ./Core/Src/task2.d ./Core/Src/task2.o ./Core/Src/task2.su ./Core/Src/task3.cyclo ./Core/Src/task3.d ./Core/Src/task3.o ./Core/Src/task3.su ./Core/Src/task4.cyclo ./Core/Src/task4.d ./Core/Src/task4.o ./Core/Src/task4.su ./Core/Src/task5.cyclo ./Core/Src/task5.d ./Core/Src/task5.o ./Core/Src/task5.su ./Core/Src/task6.cyclo ./Core/Src/task6.d ./Core/Src/task6.o ./Core/Src/task6.su

.PHONY: clean-Core-2f-Src

