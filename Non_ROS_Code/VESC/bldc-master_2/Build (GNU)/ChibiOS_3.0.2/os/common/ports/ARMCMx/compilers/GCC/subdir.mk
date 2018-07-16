################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/crt0_v6m.s \
../ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/crt0_v7m.s 

C_SRCS += \
../ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/crt1.c \
../ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/vectors.c 

OBJS += \
./ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/crt0_v6m.o \
./ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/crt0_v7m.o \
./ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/crt1.o \
./ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/vectors.o 

C_DEPS += \
./ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/crt1.d \
./ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/vectors.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/%.o: ../ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	arm-none-eabi-as -mthumb -mfloat-abi=soft -I"C:\Users\Gamer\Desktop\Tony\Work\05_Automotive_Engineering\00_Team_Octagon\01_Software\bldc-master" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/%.o: ../ChibiOS_3.0.2/os/common/ports/ARMCMx/compilers/GCC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


