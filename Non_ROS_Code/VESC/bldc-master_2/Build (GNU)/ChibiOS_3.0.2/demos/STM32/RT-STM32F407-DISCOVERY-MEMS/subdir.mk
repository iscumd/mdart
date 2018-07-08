################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/main.c \
../ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/usbcfg.c 

OBJS += \
./ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/main.o \
./ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/usbcfg.o 

C_DEPS += \
./ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/main.d \
./ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/usbcfg.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/%.o: ../ChibiOS_3.0.2/demos/STM32/RT-STM32F407-DISCOVERY-MEMS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


