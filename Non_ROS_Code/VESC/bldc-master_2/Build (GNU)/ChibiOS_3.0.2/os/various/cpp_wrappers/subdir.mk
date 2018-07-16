################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ChibiOS_3.0.2/os/various/cpp_wrappers/ch.cpp \
../ChibiOS_3.0.2/os/various/cpp_wrappers/syscalls_cpp.cpp 

OBJS += \
./ChibiOS_3.0.2/os/various/cpp_wrappers/ch.o \
./ChibiOS_3.0.2/os/various/cpp_wrappers/syscalls_cpp.o 

CPP_DEPS += \
./ChibiOS_3.0.2/os/various/cpp_wrappers/ch.d \
./ChibiOS_3.0.2/os/various/cpp_wrappers/syscalls_cpp.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/various/cpp_wrappers/%.o: ../ChibiOS_3.0.2/os/various/cpp_wrappers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	arm-none-eabi-g++ -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


