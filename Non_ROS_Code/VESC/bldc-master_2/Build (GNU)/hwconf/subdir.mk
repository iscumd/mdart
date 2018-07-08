################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hwconf/drv8301.c \
../hwconf/drv8305.c \
../hwconf/hw_40.c \
../hwconf/hw_410.c \
../hwconf/hw_45.c \
../hwconf/hw_46.c \
../hwconf/hw_48.c \
../hwconf/hw_49.c \
../hwconf/hw_60.c \
../hwconf/hw_das_rs.c \
../hwconf/hw_palta.c \
../hwconf/hw_r2.c \
../hwconf/hw_rh.c \
../hwconf/hw_tp.c \
../hwconf/hw_victor_r1a.c 

OBJS += \
./hwconf/drv8301.o \
./hwconf/drv8305.o \
./hwconf/hw_40.o \
./hwconf/hw_410.o \
./hwconf/hw_45.o \
./hwconf/hw_46.o \
./hwconf/hw_48.o \
./hwconf/hw_49.o \
./hwconf/hw_60.o \
./hwconf/hw_das_rs.o \
./hwconf/hw_palta.o \
./hwconf/hw_r2.o \
./hwconf/hw_rh.o \
./hwconf/hw_tp.o \
./hwconf/hw_victor_r1a.o 

C_DEPS += \
./hwconf/drv8301.d \
./hwconf/drv8305.d \
./hwconf/hw_40.d \
./hwconf/hw_410.d \
./hwconf/hw_45.d \
./hwconf/hw_46.d \
./hwconf/hw_48.d \
./hwconf/hw_49.d \
./hwconf/hw_60.d \
./hwconf/hw_das_rs.d \
./hwconf/hw_palta.d \
./hwconf/hw_r2.d \
./hwconf/hw_rh.d \
./hwconf/hw_tp.d \
./hwconf/hw_victor_r1a.d 


# Each subdirectory must supply rules for building sources it contributes
hwconf/%.o: ../hwconf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


