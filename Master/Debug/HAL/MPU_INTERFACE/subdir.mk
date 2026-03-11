################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/MPU_INTERFACE/MPU.c 

OBJS += \
./HAL/MPU_INTERFACE/MPU.o 

C_DEPS += \
./HAL/MPU_INTERFACE/MPU.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/MPU_INTERFACE/%.o: ../HAL/MPU_INTERFACE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


