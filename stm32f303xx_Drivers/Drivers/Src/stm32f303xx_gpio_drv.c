/*
 *=====================================================================================
 *
 * Name				:stm32f303xx_gpio_drv.c
 * Description:		:This source file implements the GPIO apis for the user application.
 * Created on       :2022/12/18
 * Author           :Pranav Vasudevan- pranavmv012@gmail.com
 *=====================================================================================
 */
#include "stm32f303xx_gpio_drv.h"
#include <stdio.h>
#include <stdint.h>
/*Use these pointer variable to access each register in a peripheral-GPIO*/
//GPIO_Reg_Def_t *pGPIOA = GPIOA;
//GPIO_Reg_Def_t *pGPIOB = GPIOB;
//GPIO_Reg_Def_t *pGPIOC = GPIOC;
//GPIO_Reg_Def_t *pGPIOD = GPIOD;
//GPIO_Reg_Def_t *pGPIOE = GPIOE;
//GPIO_Reg_Def_t *pGPIOF = GPIOF;
//GPIO_Reg_Def_t *pGPIOG = GPIOG;
//GPIO_Reg_Def_t *pGPIOH = GPIOH;

/*Use these pointer variable to access each register in a peripheral-RCC*/
RCC_Reg_Def_t *pRCC = RCC;
EXTI_Reg_Def_t *pEXTI = EXTI;
SYSCFG_Reg_Def_t *pSYSCFG = SYSCFG;
/*Macros for enabling peripheral clock*/

#define GPIOA_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 17) )
#define GPIOB_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 18) )
#define GPIOC_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 19) )
#define GPIOD_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 20) )
#define GPIOE_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 21) )
#define GPIOF_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 22) )
#define GPIOG_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 23) )
#define GPIOH_PCLK_EN() ( pRCC->RCC_AHBENR |= (1 << 16) )

/*sysconf clock */

#define SYSCFG_PCLK_EN() (RCC->RCC_APB2ENR |= (1<<0) )
#define SYSCFG_PCLK_DI() (RCC->RCC_APB2ENR &= ~(1<<0) )

/*Macros for disabling peripheral clock*/
#define GPIOA_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 17) )
#define GPIOB_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 18) )
#define GPIOC_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 19) )
#define GPIOD_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 20) )
#define GPIOE_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 21) )
#define GPIOF_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 22) )
#define GPIOG_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 23) )
#define GPIOH_PCLK_DI() ( pRCC->RCC_AHBENR &= ~(1 << 16) )

/*Register reset macros*/
#define GPIOA_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 17));	(pRCC->RCC_AHBRSTR &= ~(1 << 17));} while(0)
#define GPIOB_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 18));	(pRCC->RCC_AHBRSTR &= ~(1 << 18));} while(0)
#define GPIOC_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 19));	(pRCC->RCC_AHBRSTR &= ~(1 << 19));} while(0)
#define GPIOD_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 20));	(pRCC->RCC_AHBRSTR &= ~(1 << 20));} while(0)
#define GPIOE_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 21));	(pRCC->RCC_AHBRSTR &= ~(1 << 21));} while(0)
#define GPIOF_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 22));	(pRCC->RCC_AHBRSTR &= ~(1 << 22));} while(0)
#define GPIOG_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 23));	(pRCC->RCC_AHBRSTR &= ~(1 << 23));} while(0)
#define GPIOH_REG_RESET() 	do{(pRCC->RCC_AHBRSTR |= (1 << 16));	(pRCC->RCC_AHBRSTR &= ~(1 << 16));} while(0)
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_PCLKControl
 *   Description:  Function to enable or disable peripheral clock of GPIO
 *   Inputs		:  Pointer to base address of the GPIO port, Enable or disable variable
 * Output/return:  NOne.
 * =====================================================================================
 */
void GPIO_PCLKControl(GPIO_Reg_Def_t *pGPIOx, uint8_t ENorDI)
{
 if(ENorDI == ENABLE)
  {
	 if(pGPIOx ==GPIOA)
	 {
		GPIOA_PCLK_EN();
	 }else if(pGPIOx == GPIOB)
	 {
		GPIOB_PCLK_EN();

	 }else if(pGPIOx == GPIOC)
	 {
		GPIOC_PCLK_EN();
	 } else if(pGPIOx == GPIOD)
	 {
		GPIOD_PCLK_EN();
	 }else if(pGPIOx == GPIOE)
	 {
	    GPIOE_PCLK_EN();
	  }else if(pGPIOx == GPIOF)
	  {
		GPIOF_PCLK_EN();
	  }else if(pGPIOx == GPIOG)
	  {
	      GPIOG_PCLK_EN();
	  }else if(pGPIOx == GPIOH)
	  {
	      GPIOH_PCLK_EN();
	  }
	}
 else
 {
	 if(pGPIOx ==GPIOA)
	 {
		GPIOA_PCLK_DI();
	 }else if(pGPIOx == GPIOB)
	 {
		GPIOB_PCLK_DI();

	 }else if(pGPIOx == GPIOC)
	 {
		GPIOC_PCLK_DI();
	 } else if(pGPIOx == GPIOD)
	 {
		GPIOD_PCLK_DI();
	 }else if(pGPIOx == GPIOE)
	 {
	    GPIOE_PCLK_DI();
	  }else if(pGPIOx == GPIOF)
	  {
		GPIOF_PCLK_DI();
	  }else if(pGPIOx == GPIOG)
	  {
	      GPIOG_PCLK_DI();
	  }else if(pGPIOx == GPIOH)
	  {
	      GPIOH_PCLK_DI();
	  }
 }
}

/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_Init
 *   Description:  Function to Initialize GPIO
 *   Inputs		:  Pointer to GPIO handle.
 * Output/return:  None.
 * =====================================================================================
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0;
//configure the mode

	if(pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//non interrupt mode
		temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum));
		pGPIOHandle->pGPIOx->MODER &= ~ (0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum) );
		pGPIOHandle->pGPIOx->MODER |= temp;
		temp=0;
	}
	else
	{
		//interrupt mode
		if(pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_IT_FET)
		{
		//configure the falling edge of interrupt on extiregister. FTSR reg
			pEXTI->EXTI_FTSR1 |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum);
			//clear corresponding rtsr reg
			pEXTI->EXTI_RTSR1 &= ~(1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum);

		}else if(pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_IT_RET)
		{
		//configure the falling edge of interrupt on exti reg. RTSR reg
			pEXTI->EXTI_RTSR1 |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum);
			//clear corresponding rtsr reg
			pEXTI->EXTI_FTSR1 &= ~(1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum);

		}else if(pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_IT_FRET)
		{
		//configure the falling edge of interrupt on exti register. FTSR and RTSR reg
			pEXTI->EXTI_RTSR1 |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum);
			pEXTI->EXTI_FTSR1 |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum);
		}
		//Enable the port selection in sysconfig exticr: 4 exti regs. and each pin/exti is 4bit wide.

		uint8_t temp1 = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum) / 4;
		uint8_t temp2 = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum) % 4;
		uint8_t portCode = GET_PORT_CODE(pGPIOHandle->pGPIOx);
		pSYSCFG->SYSCFG_EXTICR[temp1] |= (portCode << (4 * temp2));

		//Enable the interrupt delivery to the processor by setting exti IMR register.
		pEXTI->EXTI_IMR1 |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum);
	}
	temp = 0;
//configure the speed
	temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~ (0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum) );
	pGPIOHandle->pGPIOx->OSPEEDR |= temp; //setting
	temp=0;
//configure the pupd settings
	temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinPuPdCntrl << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum));
	pGPIOHandle->pGPIOx->PUPDR &= ~ (0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum) );
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp =0;
//configure output type
	temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinOType << (pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum));
	pGPIOHandle->pGPIOx->OTYPER &= ~ (0x1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum );
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp=0;
//configure the alternate functionalities
	if(pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_AF)
	{
		uint8_t temp1, temp2;
		temp1= (pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum)/8;
		temp2= (pGPIOHandle->GPIO_Pin_Config.GPIO_PinNum)%8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~( 0xF << (temp2 * 4 ));
		pGPIOHandle->pGPIOx->AFR[temp1] |= ( pGPIOHandle->GPIO_Pin_Config.GPIO_PinAFmode << (temp2 * 4 ));
	}


}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_DeInit
 *   Description:  Function to de-initialize GPIO
 *   Inputs		:  Pointer to the base address of the gpio
 * Output/return:  None.
 * =====================================================================================
 */
void GPIO_DeInit(GPIO_Reg_Def_t *pGPIOx)
{
	if(pGPIOx ==GPIOA)
	{
		GPIOA_REG_RESET();
	}else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();;
	} else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();;
	}else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
}

/*
 * Read and write APIs
 */
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_ReadInputPin
 *   Description:  Function to read from input pin.
 *   Inputs		:  Pointer to the base address of gpio port, pin number
 * Output/return:  if the pin is high or low. 0 or 1
 * =====================================================================================
 */
uint8_t  GPIO_ReadInputPin(GPIO_Reg_Def_t *pGPIOx, uint8_t PinNum)
{
	uint8_t val;
	val = (uint8_t) (pGPIOx->IDR >>PinNum) & 0x00000001;
	return val;
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_ReadInputPort
 *   Description:  Read from a GPIO port
 *   Inputs		:  Pointer to the base address of the port.
 * Output/return:  16 bit value. Each bit represent the reading of corresponding pin .
 * =====================================================================================
 */
uint16_t GPIO_ReadInputPort(GPIO_Reg_Def_t *pGPIOx)
{
	uint16_t Val;
	Val = (uint16_t) (pGPIOx->IDR);
	return Val;
}

/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_WriteOutputPin
 *   Description:  Function to write a value ot the corresponding GPIO pin
 *   Inputs		:  Pointer to the base address of the port, pin number and value to be
 *   			   written
 * Output/return:  None.
 * =====================================================================================
 */
void GPIO_WriteOutputPin(GPIO_Reg_Def_t *pGPIOx, uint8_t PinNum, uint8_t Val)
{
	if(Val == PIN_SET)
	{
		(pGPIOx->ODR) |= (1 << PinNum);//set the corresponding bit field in the ODR register.
	}
	else
	{
		(pGPIOx->ODR) &= ~(1 << PinNum);//reset the corresponding bit field in the ODR register.
	}
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_WriteOutputPort
 *   Description:  Function to write to the output port
 *   Inputs		:  Pointer to the GPIO base address.
 * Output/return:  None.
 * =====================================================================================
 */
void GPIO_WriteOutputPort(GPIO_Reg_Def_t *pGPIOx, uint16_t Val)
{
	(pGPIOx->ODR) = Val;
}

/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_ToggleOutPin
 *   Description:  Function to toggle a GPIO output pin.
 *   Inputs		:  Pointer to GPIO port base address and pin number.
 * Output/return:  None.
 * =====================================================================================
 */
void GPIO_ToggleOutPin(GPIO_Reg_Def_t *pGPIOx, uint8_t pinNum)
{
	(pGPIOx->ODR) ^= (1 << pinNum);
}
/*
 * IRQ APIs
 */
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_IRQConfig
 *   Description:  Function to configure the gpio interrupt.
 *   Inputs		:  IRQ number, priority and Enable/disable
 * Output/return:  None.
 * =====================================================================================
 */
void GPIO_IRQConfig(uint8_t IRQNum, uint8_t IRQPriority, uint8_t ENorDI)
{

}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  GPIO_IRQHandler
 *   Description:  Function to handle interrupt.
 *   Inputs		:  Pin number at which interrupt triggers.
 * Output/return:  None.
 * =====================================================================================
 */
void GPIO_IRQHandler(uint8_t PinNum)
{

}
