################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_flash.c \
../drivers/fsl_flexcan.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_rtc.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_flash.o \
./drivers/fsl_flexcan.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_rtc.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_flash.d \
./drivers/fsl_flexcan.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_rtc.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DFRDM_K66F -DFREEDOM -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DCPU_MK66FN2M0VMD18_cm4 -DCPU_MK66FN2M0VMD18 -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/board" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/source" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/drivers" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/CMSIS" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/startup" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/utilities" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


