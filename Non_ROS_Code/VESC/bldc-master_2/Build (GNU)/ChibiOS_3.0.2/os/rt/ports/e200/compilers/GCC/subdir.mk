################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../ChibiOS_3.0.2/os/rt/ports/e200/compilers/GCC/ivor.s 

OBJS += \
./ChibiOS_3.0.2/os/rt/ports/e200/compilers/GCC/ivor.o 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/rt/ports/e200/compilers/GCC/%.o: ../ChibiOS_3.0.2/os/rt/ports/e200/compilers/GCC/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	arm-none-eabi-as -mthumb -mfloat-abi=soft -I"C:\Users\Gamer\Desktop\Tony\Work\05_Automotive_Engineering\00_Team_Octagon\01_Software\bldc-master" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


