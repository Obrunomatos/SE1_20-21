################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adxl345.c \
../src/button.c \
../src/flash.c \
../src/lcd.c \
../src/led.c \
../src/rtc.c \
../src/spi.c \
../src/ui.c \
../src/wait.c 

OBJS += \
./src/adxl345.o \
./src/button.o \
./src/flash.o \
./src/lcd.o \
./src/led.o \
./src/rtc.o \
./src/spi.o \
./src/ui.o \
./src/wait.o 

C_DEPS += \
./src/adxl345.d \
./src/button.d \
./src/flash.d \
./src/lcd.d \
./src/led.d \
./src/rtc.d \
./src/spi.d \
./src/ui.d \
./src/wait.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"C:\Users\obrun\Documents\MCUXpressoIDE_11.2.1_4149\SE1\SE2021\inc" -I"C:\Users\obrun\Documents\MCUXpressoIDE_11.2.1_4149\SE1\CMSIS_CORE_LPC17xx\inc" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


