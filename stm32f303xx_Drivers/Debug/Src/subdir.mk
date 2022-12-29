################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/003.ButtonInterruptLed.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/003.ButtonInterruptLed.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/003.ButtonInterruptLed.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"E:/GITHUB repo-personal/Drivers-/local-Drivers/stm32f303xx_Drivers/Drivers/Inc" -I"E:/GITHUB repo-personal/Drivers-/local-Drivers/stm32f303xx_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/003.ButtonInterruptLed.d ./Src/003.ButtonInterruptLed.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o

.PHONY: clean-Src

