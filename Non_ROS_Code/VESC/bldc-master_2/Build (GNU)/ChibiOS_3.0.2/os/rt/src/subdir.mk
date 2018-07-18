################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/os/rt/src/chcond.c \
../ChibiOS_3.0.2/os/rt/src/chdebug.c \
../ChibiOS_3.0.2/os/rt/src/chdynamic.c \
../ChibiOS_3.0.2/os/rt/src/chevents.c \
../ChibiOS_3.0.2/os/rt/src/chheap.c \
../ChibiOS_3.0.2/os/rt/src/chmboxes.c \
../ChibiOS_3.0.2/os/rt/src/chmemcore.c \
../ChibiOS_3.0.2/os/rt/src/chmempools.c \
../ChibiOS_3.0.2/os/rt/src/chmsg.c \
../ChibiOS_3.0.2/os/rt/src/chmtx.c \
../ChibiOS_3.0.2/os/rt/src/chqueues.c \
../ChibiOS_3.0.2/os/rt/src/chregistry.c \
../ChibiOS_3.0.2/os/rt/src/chschd.c \
../ChibiOS_3.0.2/os/rt/src/chsem.c \
../ChibiOS_3.0.2/os/rt/src/chstats.c \
../ChibiOS_3.0.2/os/rt/src/chsys.c \
../ChibiOS_3.0.2/os/rt/src/chthreads.c \
../ChibiOS_3.0.2/os/rt/src/chtm.c \
../ChibiOS_3.0.2/os/rt/src/chvt.c 

OBJS += \
./ChibiOS_3.0.2/os/rt/src/chcond.o \
./ChibiOS_3.0.2/os/rt/src/chdebug.o \
./ChibiOS_3.0.2/os/rt/src/chdynamic.o \
./ChibiOS_3.0.2/os/rt/src/chevents.o \
./ChibiOS_3.0.2/os/rt/src/chheap.o \
./ChibiOS_3.0.2/os/rt/src/chmboxes.o \
./ChibiOS_3.0.2/os/rt/src/chmemcore.o \
./ChibiOS_3.0.2/os/rt/src/chmempools.o \
./ChibiOS_3.0.2/os/rt/src/chmsg.o \
./ChibiOS_3.0.2/os/rt/src/chmtx.o \
./ChibiOS_3.0.2/os/rt/src/chqueues.o \
./ChibiOS_3.0.2/os/rt/src/chregistry.o \
./ChibiOS_3.0.2/os/rt/src/chschd.o \
./ChibiOS_3.0.2/os/rt/src/chsem.o \
./ChibiOS_3.0.2/os/rt/src/chstats.o \
./ChibiOS_3.0.2/os/rt/src/chsys.o \
./ChibiOS_3.0.2/os/rt/src/chthreads.o \
./ChibiOS_3.0.2/os/rt/src/chtm.o \
./ChibiOS_3.0.2/os/rt/src/chvt.o 

C_DEPS += \
./ChibiOS_3.0.2/os/rt/src/chcond.d \
./ChibiOS_3.0.2/os/rt/src/chdebug.d \
./ChibiOS_3.0.2/os/rt/src/chdynamic.d \
./ChibiOS_3.0.2/os/rt/src/chevents.d \
./ChibiOS_3.0.2/os/rt/src/chheap.d \
./ChibiOS_3.0.2/os/rt/src/chmboxes.d \
./ChibiOS_3.0.2/os/rt/src/chmemcore.d \
./ChibiOS_3.0.2/os/rt/src/chmempools.d \
./ChibiOS_3.0.2/os/rt/src/chmsg.d \
./ChibiOS_3.0.2/os/rt/src/chmtx.d \
./ChibiOS_3.0.2/os/rt/src/chqueues.d \
./ChibiOS_3.0.2/os/rt/src/chregistry.d \
./ChibiOS_3.0.2/os/rt/src/chschd.d \
./ChibiOS_3.0.2/os/rt/src/chsem.d \
./ChibiOS_3.0.2/os/rt/src/chstats.d \
./ChibiOS_3.0.2/os/rt/src/chsys.d \
./ChibiOS_3.0.2/os/rt/src/chthreads.d \
./ChibiOS_3.0.2/os/rt/src/chtm.d \
./ChibiOS_3.0.2/os/rt/src/chvt.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/os/rt/src/%.o: ../ChibiOS_3.0.2/os/rt/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


