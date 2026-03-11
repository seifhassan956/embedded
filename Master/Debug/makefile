################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/interrupt/subdir.mk
-include MCAL/UART_DRIVER/subdir.mk
-include MCAL/Timer_Driver/subdir.mk
-include MCAL/I2C_DRIVER/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/MPU_INTERFACE/subdir.mk
-include HAL/LCD_interface/subdir.mk
-include HAL/BT/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
NASR88.lss \

FLASH_IMAGE += \
NASR88.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: NASR88.elf secondary-outputs

# Tool invocations
NASR88.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,NASR88.map -mmcu=atmega32 -o "NASR88.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

NASR88.lss: NASR88.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S NASR88.elf  >"NASR88.lss"
	@echo 'Finished building: $@'
	@echo ' '

NASR88.hex: NASR88.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex NASR88.elf  "NASR88.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: NASR88.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 NASR88.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) NASR88.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
