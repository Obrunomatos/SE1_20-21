################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: Lab_0.axf

dependents:
	-cd C:/Users/obrun/Documents/MCUXpressoIDE_11.2.1_4149/SE1/SE2021/Debug && $(MAKE) all

# Tool invocations
Lab_0.axf: $(OBJS) $(USER_OBJS) C:/Users/obrun/Documents/MCUXpressoIDE_11.2.1_4149/SE1/SE2021/Debug/libSE2021.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\obrun\Documents\MCUXpressoIDE_11.2.1_4149\SE1\SE2021\Debug" -L"C:\Users\obrun\Documents\MCUXpressoIDE_11.2.1_4149\SE1\CMSIS_CORE_LPC17xx\Debug" -Xlinker -Map="Lab_0.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "Lab_0_Release.ld" -o "Lab_0.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Lab_0.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Lab_0.axf"; # arm-none-eabi-objcopy -v -O binary "Lab_0.axf" "Lab_0.bin" ; # checksum -p LPC1769 -d "Lab_0.bin";
	-@echo ' '

.PHONY: all clean dependents post-build
C:/Users/obrun/Documents/MCUXpressoIDE_11.2.1_4149/SE1/SE2021/Debug/libSE2021.a:

-include ../makefile.targets
