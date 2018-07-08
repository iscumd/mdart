################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nrf/nrf_driver.c \
../nrf/rf.c \
../nrf/rfhelp.c \
../nrf/spi_sw.c 

OBJS += \
./nrf/nrf_driver.o \
./nrf/rf.o \
./nrf/rfhelp.o \
./nrf/spi_sw.o 

C_DEPS += \
./nrf/nrf_driver.d \
./nrf/rf.d \
./nrf/rfhelp.d \
./nrf/spi_sw.d 


# Each subdirectory must supply rules for building sources it contributes
nrf/%.o: ../nrf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


