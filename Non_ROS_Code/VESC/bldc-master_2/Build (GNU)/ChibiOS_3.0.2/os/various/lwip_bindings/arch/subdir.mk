################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/os/various/lwip_bindings/arch/sys_arch.c 

OBJS += \
./ChibiOS_3.0.2/os/various/lwip_bindings/arch/sys_arch.o 

C_DEPS += \
./ChibiOS_3.0.2/os/various/lwip_bindings/arch/sys_arch.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/various/lwip_bindings/arch/%.o: ../ChibiOS_3.0.2/os/various/lwip_bindings/arch/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


