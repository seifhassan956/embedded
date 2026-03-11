################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/BT/Bluetooth.c \
../HAL/BT/uart_main.c 

OBJS += \
./HAL/BT/Bluetooth.o \
./HAL/BT/uart_main.o 

C_DEPS += \
./HAL/BT/Bluetooth.d \
./HAL/BT/uart_main.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/BT/%.o: ../HAL/BT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


