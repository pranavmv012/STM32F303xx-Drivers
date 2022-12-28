/**
 ******************************************************************************
 * @file           : 002_LedButton.c
 * @author         : Pranav Vasudevan- pranavmv012@gmail.com
 * @Date		   : 2022/12/24
 * @brief          : This code implements function to toggle the on-board led
 * 					 when on board button is pressed.
 ******************************************************************************
 */
#include "stm32f303xx.h"
#include <stdint.h>

#define BUTTON_PRESSED DISABLE

void delay()
{
	for (int i=0; i<500000/2; i++)
	{

	}
}
int main(void)
{
	GPIO_Handle_t GpioLed;   	//handle for led
	GPIO_Handle_t GpioButton;   //handle for button
	//led handle init
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_5;
	GpioLed.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_Pin_Config.GPIO_PinOType = GPIO_OUT_TYPE_PP;
	GpioLed.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
	GpioLed.GPIO_Pin_Config.GPIO_PinPuPdCntrl = GPIO_PUPDR_NPUPD;
	//Button handle init

	GpioButton.pGPIOx = GPIOC;
	GpioButton.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_13;
	GpioButton.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT;
	GpioButton.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
	GpioButton.GPIO_Pin_Config.GPIO_PinPuPdCntrl = GPIO_PUPDR_NPUPD;
	//enable clock
	GPIO_PCLKControl(GPIOC, ENABLE);
	GPIO_PCLKControl(GPIOA, ENABLE);

	GPIO_Init(&GpioButton);
	GPIO_Init(&GpioLed);

	/* Loop forever */
	while(1)
	{
		if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_13) == BUTTON_PRESSED)
		{
			delay();
			GPIO_ToggleOutPin(GPIOA, GPIO_PIN_5); //toggle pin
			/*on and off on button press*/
//			GPIO_WriteOutputPin(GPIOA, GPIO_PIN_5, SET);
//			delay();
//			GPIO_WriteOutputPin(GPIOA, GPIO_PIN_5, RESET);
		}
	}
}
