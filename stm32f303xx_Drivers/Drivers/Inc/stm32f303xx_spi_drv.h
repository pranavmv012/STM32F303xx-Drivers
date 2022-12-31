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

/*Function prototypes for the apis supported by this spi driver.*/

/*
 * Peripheral clock setup.
 */
void SPI_PCLKControl(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI);


/*
 * Init and deinit.
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Reg_Def_t *pSPIx);

/*
 * Data send and receive.
 */
void SPI_SendData(SPI_Reg_Def_t *pSPIx, uint8_t *pTxbuffer, uint32_t Len);
void SPI_ReceiveData(SPI_Reg_Def_t *pSPIx, uint8_t *pRxbuffer, uint32_t Len);
/*
 * Irq config and irq handling..
 */
void SPI_IRQConfig(uint8_t IRQNum, uint8_t ENorDI);
void SPI_IRQ_PriorityConfig(uint8_t IRQNum, uint32_t IRQPriority);
void SPI_IRQHandler(SPI_Handle_t *pSPIHandle);


#endif /* INC_STM32F303XX_SPI_DRV_H_ */
