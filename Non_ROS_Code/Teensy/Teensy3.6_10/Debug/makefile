################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Teensy3.6_10.axf

# Tool invocations
Teensy3.6_10.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="Teensy3.6_10.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T "Teensy3_6_10_Debug.ld" -o "Teensy3.6_10.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Teensy3.6_10.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Teensy3.6_10.axf" ; arm-none-eabi-objcopy -v -O binary "Teensy3.6_10.axf" "Teensy3.6_10.bin" ; arm-none-eabi-objcopy -v -O ihex "Teensy3.6_10.axf" "Teensy3.6_10.hex" ; # checksum -p MK66FX1M0xxx18 -d "Teensy3.6_10.bin"
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
