################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := COIL_WINDER
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: COIL_WINDER.axf

# Tool invocations
COIL_WINDER.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\sdkar\Documents\MCUXpressoIDE_11.6.0_8187\w_s_mustafa\nxp_lpcxpresso_11c24_board_lib\Debug" -L"C:\Users\sdkar\Documents\MCUXpressoIDE_11.6.0_8187\w_s_mustafa\lpc_chip_11cxx_lib\Debug" -Xlinker -Map="COIL_WINDER.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "COIL_WINDER_Debug.ld" -o "COIL_WINDER.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) COIL_WINDER.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "COIL_WINDER.axf"; # arm-none-eabi-objcopy -v -O binary "COIL_WINDER.axf" "COIL_WINDER.bin" ; # checksum -p LPC11C24_301 -d "COIL_WINDER.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
