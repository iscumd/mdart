################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/os/hal/src/adc.c \
../ChibiOS_3.0.2/os/hal/src/can.c \
../ChibiOS_3.0.2/os/hal/src/dac.c \
../ChibiOS_3.0.2/os/hal/src/ext.c \
../ChibiOS_3.0.2/os/hal/src/gpt.c \
../ChibiOS_3.0.2/os/hal/src/hal.c \
../ChibiOS_3.0.2/os/hal/src/hal_mmcsd.c \
../ChibiOS_3.0.2/os/hal/src/hal_queues.c \
../ChibiOS_3.0.2/os/hal/src/i2c.c \
../ChibiOS_3.0.2/os/hal/src/i2s.c \
../ChibiOS_3.0.2/os/hal/src/icu.c \
../ChibiOS_3.0.2/os/hal/src/mac.c \
../ChibiOS_3.0.2/os/hal/src/mmc_spi.c \
../ChibiOS_3.0.2/os/hal/src/pal.c \
../ChibiOS_3.0.2/os/hal/src/pwm.c \
../ChibiOS_3.0.2/os/hal/src/rtc.c \
../ChibiOS_3.0.2/os/hal/src/sdc.c \
../ChibiOS_3.0.2/os/hal/src/serial.c \
../ChibiOS_3.0.2/os/hal/src/serial_usb.c \
../ChibiOS_3.0.2/os/hal/src/spi.c \
../ChibiOS_3.0.2/os/hal/src/st.c \
../ChibiOS_3.0.2/os/hal/src/uart.c \
../ChibiOS_3.0.2/os/hal/src/usb.c 

OBJS += \
./ChibiOS_3.0.2/os/hal/src/adc.o \
./ChibiOS_3.0.2/os/hal/src/can.o \
./ChibiOS_3.0.2/os/hal/src/dac.o \
./ChibiOS_3.0.2/os/hal/src/ext.o \
./ChibiOS_3.0.2/os/hal/src/gpt.o \
./ChibiOS_3.0.2/os/hal/src/hal.o \
./ChibiOS_3.0.2/os/hal/src/hal_mmcsd.o \
./ChibiOS_3.0.2/os/hal/src/hal_queues.o \
./ChibiOS_3.0.2/os/hal/src/i2c.o \
./ChibiOS_3.0.2/os/hal/src/i2s.o \
./ChibiOS_3.0.2/os/hal/src/icu.o \
./ChibiOS_3.0.2/os/hal/src/mac.o \
./ChibiOS_3.0.2/os/hal/src/mmc_spi.o \
./ChibiOS_3.0.2/os/hal/src/pal.o \
./ChibiOS_3.0.2/os/hal/src/pwm.o \
./ChibiOS_3.0.2/os/hal/src/rtc.o \
./ChibiOS_3.0.2/os/hal/src/sdc.o \
./ChibiOS_3.0.2/os/hal/src/serial.o \
./ChibiOS_3.0.2/os/hal/src/serial_usb.o \
./ChibiOS_3.0.2/os/hal/src/spi.o \
./ChibiOS_3.0.2/os/hal/src/st.o \
./ChibiOS_3.0.2/os/hal/src/uart.o \
./ChibiOS_3.0.2/os/hal/src/usb.o 

C_DEPS += \
./ChibiOS_3.0.2/os/hal/src/adc.d \
./ChibiOS_3.0.2/os/hal/src/can.d \
./ChibiOS_3.0.2/os/hal/src/dac.d \
./ChibiOS_3.0.2/os/hal/src/ext.d \
./ChibiOS_3.0.2/os/hal/src/gpt.d \
./ChibiOS_3.0.2/os/hal/src/hal.d \
./ChibiOS_3.0.2/os/hal/src/hal_mmcsd.d \
./ChibiOS_3.0.2/os/hal/src/hal_queues.d \
./ChibiOS_3.0.2/os/hal/src/i2c.d \
./ChibiOS_3.0.2/os/hal/src/i2s.d \
./ChibiOS_3.0.2/os/hal/src/icu.d \
./ChibiOS_3.0.2/os/hal/src/mac.d \
./ChibiOS_3.0.2/os/hal/src/mmc_spi.d \
./ChibiOS_3.0.2/os/hal/src/pal.d \
./ChibiOS_3.0.2/os/hal/src/pwm.d \
./ChibiOS_3.0.2/os/hal/src/rtc.d \
./ChibiOS_3.0.2/os/hal/src/sdc.d \
./ChibiOS_3.0.2/os/hal/src/serial.d \
./ChibiOS_3.0.2/os/hal/src/serial_usb.d \
./ChibiOS_3.0.2/os/hal/src/spi.d \
./ChibiOS_3.0.2/os/hal/src/st.d \
./ChibiOS_3.0.2/os/hal/src/uart.d \
./ChibiOS_3.0.2/os/hal/src/usb.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/hal/src/%.o: ../ChibiOS_3.0.2/os/hal/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


