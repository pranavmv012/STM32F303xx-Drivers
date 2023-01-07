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
	uint8_t SPI_DeviceMode;		//@SPI_DeviceMode
	uint8_t SPI_BusConfig;		//@SPI_BusConfig
	uint8_t SPI_DFF;			//@SPI_DFF
	uint8_t SPI_CPHA;			//@SPI_CPHA
	uint8_t SPI_CPOL;			//@SPI_CPOL
	uint8_t SPI_SSM;			//@SPI_SSM
	uint8_t SPI_SclkSpeed;		//@SPI_SclkSpeed

}SPI_Config_t;


/*Handle for spi*/
typedef struct
{
	SPI_Reg_Def_t *pSPIx; //pointer to hold the base address of the spi line
	SPI_Config_t SPIConfig;
}SPI_Handle_t;

/*
 * Macros- Driver specific
 */
//@SPI_DeviceMode
#define SPI_DEVICE_MODE_SLAVE		0
#define SPI_DEVICE_MODE_MASTER		1
//@SPI_BusConfig
#define SPI_BUS_CONFIG_FD			0
#define SPI_BUS_CONFIG_HD			1
//#define SPI_BUS_CONFIG_S_TXONLY		2 //removing since this is just full duplex.
#define SPI_BUS_CONFIG_S_RXONLY		2

//@SPI_SclkSpeed
#define SPI_SCLK_SPEED_DIV2			0
#define SPI_SCLK_SPEED_DIV4			1
#define SPI_SCLK_SPEED_DIV8			2
#define SPI_SCLK_SPEED_DIV16		3
#define SPI_SCLK_SPEED_DIV32		4
#define SPI_SCLK_SPEED_DIV64		5
#define SPI_SCLK_SPEED_DIV128		6
#define SPI_SCLK_SPEED_DIV256		7
//@SPI_DFF

#define SPI_DFF_8BITS		0
#define SPI_DFF_16BITS		1
//@SPI_CPHA

#define SPI_CPHA_LOW		0
#define SPI_CPHA_HIGH		1
//@SPI_CPOL
#define SPI_CPOL_LOW		0
#define SPI_CPOL_HIGH		1
//@SPI_SSM
#define SPI_SSM_SW_EN		1
#define SPI_SSM_SW_DI		0

#define SPI_TXE_FLAG 	(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG 	(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG 	(1 << SPI_SR_BSY)
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

uint8_t  SPIgetFlagStatus(SPI_Reg_Def_t *pSPIx, uint32_t FlagName);

#endif /* INC_STM32F303XX_SPI_DRV_H_ */
