/*
 *=====================================================================================
 *
 * Name				:stm32f303xx_spi_drv.h
 * Description:		:This file is SPI peripheral specific header files
 * Created on       :2022/12/30
 * Author           :Pranav Vasudevan- pranavmv012@gmail.com
 *=====================================================================================
 */
#ifndef INC_STM32F303XX_SPI_DRV_H_
#define INC_STM32F303XX_SPI_DRV_H_

#include <stdint.h>
#include "stm32f303xx.h"

/*SPI configuration structure*/
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_DFF;
	uint8_t SPI_CPHA;
	uint8_t SPI_CPOL;
	uint8_t SPI_SSM;
	uint8_t SPI_SclkSpeed;

}SPI_Config_t;


/*Handle for spi*/
typedef struct
{
	SPI_Reg_Def_t *pSPIx; //pointer to hold the base address of the spi line
	SPI_Config_t SPIConfig;
}SPI_Handle_t;

#endif /* INC_STM32F303XX_SPI_DRV_H_ */
