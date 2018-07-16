################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/demos/STM32/RT-STM32F407-OLIMEX_E407-LWIP-FATFS-USB/web/web.c 

OBJS += \
./ChibiOS_3.0.2/demos/STM32/RT-STM32F407-OLIMEX_E407-LWIP-FATFS-USB/web/web.o 

C_DEPS += \
./ChibiOS_3.0.2/demos/STM32/RT-STM32F407-OLIMEX_E407-LWIP-FATFS-USB/web/web.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/demos/STM32/RT-STM32F407-OLIMEX_E407-LWIP-FATFS-USB/web/%.o: ../ChibiOS_3.0.2/demos/STM32/RT-STM32F407-OLIMEX_E407-LWIP-FATFS-USB/web/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


