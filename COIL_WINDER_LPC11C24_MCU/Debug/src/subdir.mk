################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/COIL_WINDER.c \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/motordriver.c \
../src/sysinit.c 

C_DEPS += \
./src/COIL_WINDER.d \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/motordriver.d \
./src/sysinit.d 

OBJS += \
./src/COIL_WINDER.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/motordriver.o \
./src/sysinit.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -DCR_INTEGER_PRINTF -DCR_PRINTF_CHAR -D__LPC11XX__ -D__REDLIB__ -I"C:\Users\sdkar\Documents\MCUXpressoIDE_11.6.0_8187\w_s_mustafa\COIL_WINDER\inc" -I"C:\Users\sdkar\Documents\MCUXpressoIDE_11.6.0_8187\w_s_mustafa\nxp_lpcxpresso_11c24_board_lib\inc" -I"C:\Users\sdkar\Documents\MCUXpressoIDE_11.6.0_8187\w_s_mustafa\lpc_chip_11cxx_lib\inc" -I"C:\Users\sdkar\Documents\MCUXpressoIDE_11.6.0_8187\w_s_mustafa\nxp_lpcxpresso_11c24_board_lib\src" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/COIL_WINDER.d ./src/COIL_WINDER.o ./src/cr_startup_lpc11xx.d ./src/cr_startup_lpc11xx.o ./src/crp.d ./src/crp.o ./src/motordriver.d ./src/motordriver.o ./src/sysinit.d ./src/sysinit.o

.PHONY: clean-src

