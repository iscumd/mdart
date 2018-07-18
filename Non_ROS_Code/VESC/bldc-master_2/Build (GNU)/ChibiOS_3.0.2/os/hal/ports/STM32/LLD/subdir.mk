################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/os/hal/ports/STM32/LLD/can_lld.c \
../ChibiOS_3.0.2/os/hal/ports/STM32/LLD/ext_lld.c \
../ChibiOS_3.0.2/os/hal/ports/STM32/LLD/mac_lld.c \
../ChibiOS_3.0.2/os/hal/ports/STM32/LLD/sdc_lld.c 

OBJS += \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/can_lld.o \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/ext_lld.o \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/mac_lld.o \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/sdc_lld.o 

C_DEPS += \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/can_lld.d \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/ext_lld.d \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/mac_lld.d \
./ChibiOS_3.0.2/os/hal/ports/STM32/LLD/sdc_lld.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/hal/ports/STM32/LLD/%.o: ../ChibiOS_3.0.2/os/hal/ports/STM32/LLD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


