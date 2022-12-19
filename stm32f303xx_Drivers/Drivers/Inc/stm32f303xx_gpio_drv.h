/*
 * stm32f303xx_gpio_drv.h
 *
 *  Created on: 18-Dec-2022
 *      Author: USER
 */

#ifndef INC_STM32F303XX_GPIO_DRV_H_
#define INC_STM32F303XX_GPIO_DRV_H_
#include "stm32f303xx.h"
#include <stdint.h>

typedef struct
{
	uint8_t GPIO_PinNum;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinOType;
	uint8_t GPIO_PinPuPdCntrl;
	uint8_t GPIO_PinAFmode;

}GPIO_Pin_Config_t;


typedef struct
{
	GPIO_Reg_Def_t *pGPIOx;  /*To hold the base address of the gpio port which the selected pin belongs to*/
	GPIO_Pin_Config_t GPIO_Pin_Config;

}GPIO_Handle_t;

#endif /* INC_STM32F303XX_GPIO_DRV_H_ */
