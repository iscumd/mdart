################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/app.c \
../applications/app_adc.c \
../applications/app_custom.c \
../applications/app_nunchuk.c \
../applications/app_ppm.c \
../applications/app_sten.c \
../applications/app_uartcomm.c 

OBJS += \
./applications/app.o \
./applications/app_adc.o \
./applications/app_custom.o \
./applications/app_nunchuk.o \
./applications/app_ppm.o \
./applications/app_sten.o \
./applications/app_uartcomm.o 

C_DEPS += \
./applications/app.d \
./applications/app_adc.d \
./applications/app_custom.d \
./applications/app_nunchuk.d \
./applications/app_ppm.d \
./applications/app_sten.d \
./applications/app_uartcomm.d 


# Each subdirectory must supply rules for building sources it contributes
applications/%.o: ../applications/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


