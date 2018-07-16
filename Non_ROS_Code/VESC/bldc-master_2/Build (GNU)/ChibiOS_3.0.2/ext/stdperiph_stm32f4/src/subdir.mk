################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/misc.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_adc.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_dma.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_exti.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_flash.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_rcc.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_syscfg.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_tim.c \
../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_wwdg.c 

OBJS += \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/misc.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_adc.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_dma.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_exti.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_flash.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_rcc.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_syscfg.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_tim.o \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_wwdg.o 

C_DEPS += \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/misc.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_adc.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_dma.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_exti.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_flash.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_rcc.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_syscfg.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_tim.d \
./ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/stm32f4xx_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/%.o: ../ChibiOS_3.0.2/ext/stdperiph_stm32f4/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


