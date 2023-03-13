################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Ind_Wrapper.c \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/motordriver.c \
../src/sysinit.c 

C_DEPS += \
./src/Ind_Wrapper.d \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/motordriver.d \
./src/sysinit.d 

OBJS += \
./src/Ind_Wrapper.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/motordriver.o \
./src/sysinit.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -DCR_INTEGER_PRINTF -D__LPC11XX__ -D__REDLIB__ -I"D:\MERT FILE\LPC11C24\Ind_Wrapper\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Ind_Wrapper.d ./src/Ind_Wrapper.o ./src/cr_startup_lpc11xx.d ./src/cr_startup_lpc11xx.o ./src/crp.d ./src/crp.o ./src/motordriver.d ./src/motordriver.o ./src/sysinit.d ./src/sysinit.o

.PHONY: clean-src
