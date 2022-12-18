################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32f303xx_gpio_drv.c 

OBJS += \
./Drivers/Src/stm32f303xx_gpio_drv.o 

C_DEPS += \
./Drivers/Src/stm32f303xx_gpio_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"E:/GITHUB repo-personal/Drivers-/local-Drivers/stm32f303xx_Drivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -nostartfiles -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32f303xx_gpio_drv.d ./Drivers/Src/stm32f303xx_gpio_drv.o

.PHONY: clean-Drivers-2f-Src

