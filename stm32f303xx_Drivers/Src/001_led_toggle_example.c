/**
 ******************************************************************************
 * @file           : 001_led_toggle_example.c
 * @author         : Pranav Vasudevan- pranavmv012@gmail.com
 * @Date		   : 2022/12/24
 * @brief          : This code implements function to toggle the on board led
 * 					 on NUCLEO-F303RE -PA5
 ******************************************************************************
 */
#include "stm32f303xx.h"
#include <stdint.h>

void delay()
{
	for (int i=0; i<500000; i++)
	{

	}
}
int main(void)
{
	GPIO_Handle_t GpioLed;
	//handle init
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_5;
	GpioLed.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_Pin_Config.GPIO_PinOType = GPIO_OUT_TYPE_PP;
	GpioLed.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
	GpioLed.GPIO_Pin_Config.GPIO_PinPuPdCntrl = GPIO_PUPDR_NPUPD;
	GPIO_PCLKControl(GPIOA, ENABLE);
	GPIO_Init(&GpioLed);
	/* Loop forever */
	while(1)
	{
		GPIO_ToggleOutPin(GPIOA, GPIO_PIN_5);
		delay();
	}
}
