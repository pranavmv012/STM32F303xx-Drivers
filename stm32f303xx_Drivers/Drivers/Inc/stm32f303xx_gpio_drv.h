/*
 *=====================================================================================
 *
 * Name				:stm32f303xx_gpio_drv.h
 * Description:		:This file is GPIO peripheral specific header files
 * Created on       :2022/12/18
 * Author           :Pranav Vasudevan- pranavmv012@gmail.com
 *=====================================================================================
 */
#ifndef INC_STM32F303XX_GPIO_DRV_H_
#define INC_STM32F303XX_GPIO_DRV_H_
#include "stm32f303xx.h"
#include <stdint.h>


typedef struct
{
	uint8_t GPIO_PinNum;		//@GPIO_PIN_NUM
	uint8_t GPIO_PinMode; 		//pin modes it can take is @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed;		//speed @GPIO_OUT_SPEED
	uint8_t GPIO_PinOType; 		//output type @GPIO_OUT_TYPES
	uint8_t GPIO_PinPuPdCntrl;	//pull up pull down @GPIO_PUPDR
	uint8_t GPIO_PinAFmode;		// alternate mode @GPIO_AF_MODES

}GPIO_Pin_Config_t;


typedef struct
{
	GPIO_Reg_Def_t *pGPIOx;  /*To hold the base address of the gpio port which the selected pin belongs to*/
	GPIO_Pin_Config_t GPIO_Pin_Config;

}GPIO_Handle_t;


/*
 * Macros- Driver specific
 */
/*
 * @GPIO_PIN_NUM
 */
#define GPIO_PIN_0			0
#define GPIO_PIN_1			1
#define GPIO_PIN_2			2
#define GPIO_PIN_3			3
#define GPIO_PIN_4			4
#define GPIO_PIN_5			5
#define GPIO_PIN_6			6
#define GPIO_PIN_7			7
#define GPIO_PIN_8			8
#define GPIO_PIN_9			9
#define GPIO_PIN_10			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15
/*
 * @GPIO_PIN_MODES
 */
#define GPIO_MODE_INPUT		0
#define GPIO_MODE_OUTPUT	1
#define GPIO_MODE_AF		2
#define GPIO_MODE_ANALOG	3

/*Macros for Interrupt mode-user defined-not from data sheet*/
#define GPIO_MODE_IT_FET	4 //Falling edge triggered
#define GPIO_MODE_IT_RET	5
#define GPIO_MODE_IT_FRET	6

/*
 * @GPIO_OUT_TYPES
 */
#define GPIO_OUT_TYPE_PP 	0
#define GPIO_OUT_TYPE_OD	1

/*
 * @GPIO_OUT_SPEED
 */
#define GPIO_OUT_SPEED_LOW 	0
#define GPIO_OUT_SPEED_MED	1
#define GPIO_OUT_SPEED_HIGH	3

/*
 *@GPIO_PUPDR
 */
#define GPIO_PUPDR_NPUPD 	0
#define GPIO_PUPDR_PU	 	1
#define GPIO_PUPDR_PD 		2

/*
 * Alternate mode @GPIO_AF_MODES
 */
#define GPIO_AFR_AF0 	0
#define GPIO_AFR_AF1 	1
#define GPIO_AFR_AF2 	2
#define GPIO_AFR_AF3 	3
#define GPIO_AFR_AF4 	4
#define GPIO_AFR_AF5 	5
#define GPIO_AFR_AF6 	6
#define GPIO_AFR_AF7 	7
#define GPIO_AFR_AF8 	8
#define GPIO_AFR_AF9 	9
#define GPIO_AFR_AF10 	10
#define GPIO_AFR_AF11 	11
#define GPIO_AFR_AF12 	12
#define GPIO_AFR_AF13 	13
#define GPIO_AFR_AF14 	14
#define GPIO_AFR_AF15 	15



/*Creating APIs for the user application*/
/*
 * GPIO Initialization APIs
 */
void GPIO_PCLKControl(GPIO_Reg_Def_t *pGPIOx, uint8_t ENorDI);


void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_Reg_Def_t *pGPIOx);

/*
 * Read and write APIs
 */
uint8_t  GPIO_ReadInputPin(GPIO_Reg_Def_t *pGPIOx, uint8_t PinNum);
uint16_t GPIO_ReadInputPort(GPIO_Reg_Def_t *pGPIOx);
void GPIO_WriteOutputPin(GPIO_Reg_Def_t *pGPIOx, uint8_t PinNum, uint8_t Val);
void GPIO_WriteOutputPort(GPIO_Reg_Def_t *pGPIOx, uint16_t Val);
void GPIO_ToggleOutPin(GPIO_Reg_Def_t *pGPIOx, uint8_t pinNum);
/*
 * IRQ APIs
 */
void GPIO_IRQConfig(uint8_t IRQNum, uint8_t IRQPriority, uint8_t ENorDI);
void GPIO_IRQHandler(uint8_t PinNum);


#endif /* INC_STM32F303XX_GPIO_DRV_H_ */
