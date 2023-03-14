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


/*SPI register bit position macros */
//SPI control register 1
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_CRCL		11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15
//SPI control register 2

#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_NSSP		3
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7
#define SPI_CR2_DS			8
#define SPI_CR2_FRXTH		12
#define SPI_CR2_LDMA_RX	 	13
#define SPI_CR2_LDMA_TX	 	14
//SPI status register
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8
#define SPI_SR_FRLVL		9
#define SPI_SR_FTLVL		11


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
	//updating handle structure for spi interrupt.
	/*spi interrupt fuction just saves the address and data in the user buffer to
	to a global and the place holder for those global are define here as this will
	be an arugument to spi interrupt handler where the data is transferred to tx buffer*/
	uint8_t *pTxBuffer; //to store the app tx buffer address
	uint8_t *pRxBuffer; //to store the app RX buffer address
	uint32_t TxLen; //tx buffer length
	uint32_t RxLen; //tx buffer length
	uint8_t TxState; //to store the state of tx
	uint8_t RxState;//to store the state of tx

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
//spi rx and tx statuses
#define SPI_READY 			0
#define SPI_BUSY_IN_RX 		1
#define SPI_BUSY_IN_TX 		2

/*
 * Possible SPI Application events
 */
#define SPI_EVENT_TX_CMPLT   1
#define SPI_EVENT_RX_CMPLT   2
#define SPI_EVENT_OVR_ERR    3
#define SPI_EVENT_CRC_ERR    4

//masks to obtain flag status.
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
 * Data send and receive with interrupt
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxbuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxbuffer, uint32_t Len);
/*
 * Irq config and irq handling..
 */
void SPI_IRQConfig(uint8_t IRQNum, uint8_t ENorDI);
void SPI_IRQ_PriorityConfig(uint8_t IRQNum, uint32_t IRQPriority);
void SPI_IRQHandler(SPI_Handle_t *pSPIHandle);

uint8_t  SPIgetFlagStatus(SPI_Reg_Def_t *pSPIx, uint32_t FlagName);

/*
 * Other SPI apis
 */
void SPI_peri_control(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI);
void SPI_SSIConfig(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI);
void SPI_SSOEConfig(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI);

/*apis for the application to clear ovr flag and close the spi- used when irq used.*/
void SPI_ClearOVRFlag(SPI_Reg_Def_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);
/*call back function that has to be implemented by the app.*/
void SPI_applicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent);
#endif /* INC_STM32F303XX_SPI_DRV_H_ */
