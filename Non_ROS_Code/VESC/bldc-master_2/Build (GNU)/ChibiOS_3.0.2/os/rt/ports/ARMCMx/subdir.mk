################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore.c \
../ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore_v6m.c \
../ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore_v7m.c 

OBJS += \
./ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore.o \
./ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore_v6m.o \
./ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore_v7m.o 

C_DEPS += \
./ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore.d \
./ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore_v6m.d \
./ChibiOS_3.0.2/os/rt/ports/ARMCMx/chcore_v7m.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/rt/ports/ARMCMx/%.o: ../ChibiOS_3.0.2/os/rt/ports/ARMCMx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


