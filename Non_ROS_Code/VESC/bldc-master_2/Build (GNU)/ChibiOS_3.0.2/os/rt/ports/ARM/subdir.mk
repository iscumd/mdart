################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/os/rt/ports/ARM/chcore.c 

OBJS += \
./ChibiOS_3.0.2/os/rt/ports/ARM/chcore.o 

C_DEPS += \
./ChibiOS_3.0.2/os/rt/ports/ARM/chcore.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/rt/ports/ARM/%.o: ../ChibiOS_3.0.2/os/rt/ports/ARM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


