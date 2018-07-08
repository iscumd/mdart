################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/main.c \
../ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/usbcfg.c 

OBJS += \
./ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/main.o \
./ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/usbcfg.o 

C_DEPS += \
./ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/main.d \
./ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/usbcfg.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/%.o: ../ChibiOS_3.0.2/testhal/STM32/STM32F4xx/USB_CDC_IAD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


