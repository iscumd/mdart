################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DFRDM_K66F -DFREEDOM -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DCPU_MK66FN2M0VMD18_cm4 -DCPU_MK66FN2M0VMD18 -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/board" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/source" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/drivers" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/CMSIS" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/startup" -I"/home/tony/Documents/Non_ROS_Code/Teensy/Teensy3.6_10/utilities" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


