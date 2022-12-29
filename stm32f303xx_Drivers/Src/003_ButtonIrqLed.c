/**
 ******************************************************************************
 * @file           : 003_ButtonIrqLed.c
 * @author         : Pranav Vasudevan- pranavmv012@gmail.com
 * @Date		   : 2022/12/28
 * @brief          : This code implements function to toggle the on-board led
 * 					 when on board button is pressed as an interrupt.
 ******************************************************************************
 */
#include "stm32f303xx.h"
#include <stdint.h>
#include <string.h>
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
	memset(&GpioLed, 0, sizeof(GpioLed));
	memset(&GpioButton, 0, sizeof(GpioButton));
	//led handle init
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_5;
	GpioLed.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_Pin_Config.GPIO_PinOType = GPIO_OUT_TYPE_PP;
	GpioLed.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
	GpioLed.GPIO_Pin_Config.GPIO_PinPuPdCntrl = GPIO_PUPDR_NPUPD;

	GPIO_PCLKControl(GPIOA, ENABLE);
	GPIO_Init(&GpioLed);
	//Button handle init

	GpioButton.pGPIOx = GPIOC;
	GpioButton.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_13;
	GpioButton.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_IT_FET;
	GpioButton.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
	GpioButton.GPIO_Pin_Config.GPIO_PinPuPdCntrl = GPIO_PUPDR_NPUPD;
	//enable clock
	GPIO_PCLKControl(GPIOC, ENABLE);
	GPIO_Init(&GpioButton);

	GPIO_IRQ_PriorityConfig(IRQ_NUM_EXTI15_10, NVIC_IRQ_PRIO10);
	GPIO_IRQConfig(IRQ_NUM_EXTI15_10, ENABLE);

	/* Loop forever */
	while(1);

}

void EXTI15_10_IRQHandler(void)
{
	delay();
	GPIO_IRQHandler(GPIO_PIN_13);
	GPIO_ToggleOutPin(GPIOA, GPIO_PIN_5);
}
