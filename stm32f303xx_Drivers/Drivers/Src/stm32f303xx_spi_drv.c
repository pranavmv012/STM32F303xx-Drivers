/*
 *=====================================================================================
 *
 * Name				:stm32f303xx_spi_drv.c
 * Description		:This source file implements the spi apis for the user application.
 * Created on       :2022/12/30
 * Author           :Pranav Vasudevan- pranavmv012@gmail.com
 *=====================================================================================
 */

#include "stm32f303xx_spi_drv.h"
/*
 * Clock enable and disable macros.
 */
RCC_Reg_Def_t *psRCC = RCC;
#define SPI1_PCLK_EN() (psRCC->RCC_APB2ENR |= (1 << 12) )
#define SPI2_PCLK_EN() (psRCC->RCC_APB1ENR |= (1 << 14) )
#define SPI3_PCLK_EN() (psRCC->RCC_APB1ENR |= (1 << 15) )
#define SPI4_PCLK_EN() (psRCC->RCC_APB2ENR |= (1 << 15) )

#define SPI1_PCLK_DI() (psRCC->RCC_APB2ENR &= ~(1 << 12) )
#define SPI2_PCLK_DI() (psRCC->RCC_APB1ENR &= ~(1 << 14) )
#define SPI3_PCLK_DI() (psRCC->RCC_APB1ENR &= ~(1 << 15) )
#define SPI4_PCLK_DI() (psRCC->RCC_APB2ENR &= ~(1 << 15) )
/*
 * spi reset macros
 */
#define SPI1_REG_RESET() 	do{(psRCC->RCC_APB2RSTR |= (1 << 12));	(psRCC->RCC_APB2RSTR &= ~(1 << 12));} while(0)
#define SPI2_REG_RESET() 	do{(psRCC->RCC_APB1RSTR |= (1 << 14));	(psRCC->RCC_APB1RSTR &= ~(1 << 14));} while(0)
#define SPI3_REG_RESET() 	do{(psRCC->RCC_APB1RSTR |= (1 << 15));	(psRCC->RCC_APB1RSTR &= ~(1 << 15));} while(0)
#define SPI4_REG_RESET() 	do{(psRCC->RCC_APB2RSTR |= (1 << 15));	(psRCC->RCC_APB2RSTR &= ~(1 << 25));} while(0)

static void SPITxe_IrqHandle(SPI_Handle_t *pSPIHandle);
static void SPIRxne_IrqHandle(SPI_Handle_t *pSPIHandle);
static void SPIOvr_IrqHandle(SPI_Handle_t *pSPIHandle);

/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_PCLKControl
 *   Description:  Function to enable or disable peripheral clock of SPI
 *   Inputs		:  Pointer to base address of the SPI port, Enable or disable variable
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_PCLKControl(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI)
{
	 if(ENorDI == ENABLE)
	  {
		 if(pSPIx == SPI1)
		 {
			SPI1_PCLK_EN();
		 }else if(pSPIx == SPI2)
		 {
			 SPI2_PCLK_EN();

		 }else if(pSPIx == SPI3)
		 {
			 SPI3_PCLK_EN();
		 } else if(pSPIx == SPI4)
		 {
			 SPI4_PCLK_EN();
		 }
	   }
	 else
	 {
		 if(pSPIx == SPI1)
		 {
			SPI1_PCLK_DI();
		 }else if(pSPIx == SPI2)
		 {
			 SPI2_PCLK_DI();

		 }else if(pSPIx == SPI3)
		 {
			 SPI3_PCLK_DI();
		 } else if(pSPIx == SPI4)
		 {
			 SPI4_PCLK_DI();
		 }
	 }
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_Init
 *   Description:  Function to Initialize SPI
 *   Inputs		:  Pointer to SPI handle.
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//Enable the peripheral clock in init to help the user not to declare explicitly
	SPI_PCLKControl(pSPIHandle->pSPIx, ENABLE);
	//configure CR1 reg
	uint32_t tempreg = 0;
	//Configuring device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;
	if((pSPIHandle->SPIConfig.SPI_BusConfig )== SPI_BUS_CONFIG_FD)
	{
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);//clear bidi bit
	}else if((pSPIHandle->SPIConfig.SPI_BusConfig) == SPI_BUS_CONFIG_HD)
	{
		tempreg |= (1 << SPI_CR1_BIDIMODE);
	}else if((pSPIHandle->SPIConfig.SPI_BusConfig) == SPI_BUS_CONFIG_S_RXONLY)
	{
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);//clear bidi and set rx only bit in cr1
		tempreg |= (1 << SPI_CR1_RXONLY);
	}
	//configure clock
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
	//configure DFF DFF is referred as CRC bit , 11.
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_CRCL;
	//configure CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
	//configure CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	pSPIHandle->pSPIx->CR1 = tempreg;
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_DeInit
 *   Description:  Function to de-initialize SPI
 *   Inputs		:  Pointer to the base address of the SPI
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_DeInit(SPI_Reg_Def_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	} else if(pSPIx == SPI4)
	{
		SPI4_REG_RESET();
	}
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_peri_control
 *   Description:  Function to enable or disable SPI peripheral.
 *   Inputs		:  Pointer to base address of the SPI port, Enable or disable variable
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_peri_control(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI)
{
 if(ENorDI == ENABLE)
 {
	 //set the pse bit in cr1 reg
	 pSPIx->CR1 |= (1 << SPI_CR1_SPE);
 }
 else
 {
	 //reset the pse bit in cr1 reg
	 pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
 }
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_SSIConfig
 *   Description:  Function to set or reset SPI ssi.
 *   Inputs		:  Pointer to base address of the SPI port, Enable or disable variable
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_SSIConfig(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI)
{
 if(ENorDI == ENABLE)
 {
	 //set the ssi bit in cr1 reg
	 pSPIx->CR1 |= (1 << SPI_CR1_SSI);
 }
 else
 {
	 //reset the ssi bit in cr1 reg
	 pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
 }
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_SSOEConfig
 *   Description:  Function to set or reset SPI ssoe bit in cr2.This is required when
 *   			   hardware slave management is selected.
 *   Inputs		:  Pointer to base address of the SPI port, Enable or disable variable
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_SSOEConfig(SPI_Reg_Def_t *pSPIx, uint8_t ENorDI)
{
	 if(ENorDI == ENABLE)
	 {
		 //set the ssi bit in cr1 reg
		 pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	 }
	 else
	 {
		 //reset the ssi bit in cr1 reg
		 pSPIx->CR1 &= ~(1 << SPI_CR2_SSOE);
	 }
}

/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_SendData
 *   Description:  Function to send data over SPI. Blockig call. the function wouldn't
 *   			   return until all the bytes in the buffer are sent out.
 *   Inputs		:  Pointer to the base add of the SPI, pointer to the tx data, Data len
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_SendData(SPI_Reg_Def_t *pSPIx, uint8_t *pTxbuffer, uint32_t Len)
{
	//when length is 0, there is not data remaining and exit the funciton.
	while(Len > 0)
	{
//		while(!(pSPIx->SR & (1 << SPI_SR_TXE)));
		while (SPIgetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);//wait for the length is zero
		//check the dff
		if(pSPIx->CR1 & (1 << SPI_CR1_CRCL))
		{
			pSPIx->DR = *((uint16_t* )pTxbuffer);//16bit
			Len--;
			Len--; //2 times as 2 bytes of data is transmitted.
			(uint16_t*)pTxbuffer++; //increment the buffer by 2
		}
		else
		{
			pSPIx->DR = *pTxbuffer;//8bit
			Len--; //1 byte of data sent out
			pTxbuffer++; //increment the buffer by 1
		}
	}
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_ReceiveData
 *   Description:  Function to send data over SPI
 *   Inputs		:  Pointer to the base add of the SPI, pointer to the rx data, Data len
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_ReceiveData(SPI_Reg_Def_t *pSPIx, uint8_t *pRxbuffer, uint32_t Len)
{
	//when length is 0, there is not data remaining and exit the funciton.
	while(Len > 0)
	{
//		while(!(pSPIx->SR & (1 << SPI_SR_TXE)));
		while (SPIgetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);//wait for the length is zero
		//check the dff
		if(pSPIx->CR1 & (1 << SPI_CR1_CRCL))
		{
			*((uint16_t* )pRxbuffer) = pSPIx->DR;// load 16bit data from the dr to buffer
			Len--;
			Len--; //2 times as 2 bytes of data is transmitted.
			(uint16_t*)pRxbuffer++; //increment the buffer by 2
		}
		else
		{
		    *pRxbuffer = pSPIx->DR;//8bit
			Len--; //1 byte of data sent out
			pRxbuffer++; //increment the buffer by 1
		}
	}
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_SendDataIT
 *   Description:  Function to send data over SPI. non blocking call. the function
 *   			   wouldn't return until all the bytes in the buffer are sent out.
 *   Inputs		:  Pointer to the spi handle, pointer to the tx data, Data len
 * Output/return:  None.
 * =====================================================================================
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxbuffer, uint32_t Len)
{
	uint8_t status = pSPIHandle->TxState;

	if(status != SPI_BUSY_IN_TX )
	{
		//store the buffer values to the global
		pSPIHandle->pTxBuffer = pTxbuffer;
		pSPIHandle->TxLen = Len;

		//make the spi status busy so that the other code can take control over this spi

		pSPIHandle->TxState = SPI_BUSY_IN_TX;
		//enable txe flag to generate interrupt.
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);

	}
	return status;
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_ReceiveDataIT
 *   Description:  Function to send data over SPI in non blocking way.
 *   Inputs		:  Pointer to the spi handle, pointer to the rx data, Data len
 * Output/return:  None.
 * =====================================================================================
 */
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxbuffer, uint32_t Len)
{

	uint8_t status = pSPIHandle->RxState;
	if(status != SPI_BUSY_IN_RX )
	{
		//store the buffer values to the global
		pSPIHandle->pRxBuffer = pRxbuffer;
		pSPIHandle->RxLen = Len;

		//make the spi status busy so that the other code can take control over this spi

		pSPIHandle->RxState = SPI_BUSY_IN_RX;
		//enable txe flag to generate interrupt.
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);

	}
	return status;
}
/*
 * Irq config and irq handling..
 */
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_IRQConfig
 *   Description:  Function to configure the SPI interrupt.
 *   Inputs		:  IRQ number, priority and Enable/disable
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_IRQConfig(uint8_t IRQNum, uint8_t ENorDI)
{
	if( ENorDI == ENABLE)
	{
		if(IRQNum <= 31)
		{
			*NVIC_ISER0 |= (1 << IRQNum);
		}else if(IRQNum >31 && IRQNum < 64)
		{
			*NVIC_ISER1 |= (1 << (IRQNum % 32));
		}else if (IRQNum >63 && IRQNum < 96)
		{
			*NVIC_ISER2 |= (1 << (IRQNum % 64));
		}
	}
	else
	{
		if(IRQNum <= 31)
		{
			*NVIC_ICER0 |= (1 << IRQNum);
		}else if(IRQNum >31 && IRQNum < 64)
		{
			*NVIC_ICER1 |= (1 << (IRQNum % 32));
		}else if (IRQNum >63 && IRQNum < 96)
		{
			*NVIC_ICER2 |= (1 << (IRQNum % 64));
		}
	}
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_IRQ_PriorityConfig
 *   Description:  Function to set the priority fo the interrupt.
 *   			   Refer 4.2.7 of ARM DUI 0553B
 *   Inputs		:  Pin number at which interrupt triggers.
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_IRQ_PriorityConfig(uint8_t IRQNum, uint32_t IRQPriority)
{
	uint8_t ipr = IRQNum / 4;
	uint8_t ipr_sec = IRQNum % 4;
	uint8_t shift = (8 * ipr_sec) + (8 - NO_PR_BIT_IMPLEMENTED);
	*(NVIC_IPR_BASE_ADDR + ipr) |= (IRQPriority << shift);
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_IRQHandler
 *   Description:  Function to handle the SPI interrupt.
 *   Inputs		:  pointer to the handle, that contains the spi peri at which interrupt
 *   			   occurred.
 * Output/return:  None.
 * =====================================================================================
 */

/*helper functions for the isr*/
void SPITxe_IrqHandle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_CRCL))
	{
		pSPIHandle->pSPIx->DR = *((uint16_t* )pSPIHandle->pTxBuffer);//16bit
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--; //2 times as 2 bytes of data is transmitted.
		(uint16_t*)pSPIHandle->pTxBuffer++; //increment the buffer by 2
	}
	else
	{
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;//8bit
		pSPIHandle->TxLen--;
		pSPIHandle->pTxBuffer++; //increment the buffer by 1
	}
	if(!pSPIHandle->TxLen)
	{
		//txe is zero , close spi and inform app.
		//prevents interrupts from setting up txeie flag.
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
		//clear the buffer and length
		pSPIHandle->pTxBuffer = NULL;
		pSPIHandle->TxLen = 0;
		pSPIHandle->TxState = SPI_READY;
		//callback
		SPI_applicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}
}
void SPIRxne_IrqHandle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_CRCL))
	{
		pSPIHandle->pSPIx->DR = *((uint16_t* )pSPIHandle->pRxBuffer);//16bit
		pSPIHandle->RxLen--;
		pSPIHandle->RxLen--; //2 times as 2 bytes of data is transmitted.
		(uint16_t*)pSPIHandle->pRxBuffer++; //increment the buffer by 2
	}
	else
	{
		pSPIHandle->pSPIx->DR = *pSPIHandle->pRxBuffer;//8bit
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer++; //increment the buffer by 1
	}
	if(!pSPIHandle->RxLen)
	{
		//txe is zero , close spi and inform app.
		//prevents interrupts from setting up txeie flag.
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
		//clear the buffer and length
		pSPIHandle->pRxBuffer = NULL;
		pSPIHandle->RxLen = 0;
		pSPIHandle->RxState = SPI_READY;
		//callback
		SPI_applicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}
}
void SPIOvr_IrqHandle(SPI_Handle_t *pSPIHandle)
{

}


void SPI_IRQHandler(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp1, temp2;
	//txe flag interrupt
	temp1 = (pSPIHandle->pSPIx->SR) & (1 << SPI_SR_TXE);
	temp2 = (pSPIHandle->pSPIx->CR2) & (1 << SPI_CR2_TXEIE);

	if( temp1 && temp2)
	{
		SPITxe_IrqHandle(pSPIHandle); //helper
	}
	//rxe flag interrupt
	temp1 = (pSPIHandle->pSPIx->SR) & (1 << SPI_SR_RXNE);
	temp2 = (pSPIHandle->pSPIx->CR2) & (1 << SPI_CR2_RXNEIE);

	if( temp1 && temp2)
	{
		SPIRxne_IrqHandle(pSPIHandle);
	}
	temp1 = (pSPIHandle->pSPIx->SR) & (1 << SPI_SR_OVR);
	temp2 = (pSPIHandle->pSPIx->CR2) & (1 << SPI_CR2_ERRIE);

	if( temp1 && temp2)
	{
		SPIOvr_IrqHandle(pSPIHandle);
	}

}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPIgetFlagStatus
 *   Description:  Function to check the status. Read the status registers position val.
 *   Inputs		:  pointer to the spi base address. Flag name(which flag has to be read)
 * Output/return:  None.
 * =====================================================================================
 */
uint8_t SPIgetFlagStatus(SPI_Reg_Def_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)//(1 << FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_applicationEventCallback
 *   Description:  Weak implementation of the callback. If the application doesn't
 *   			   implement callback then compiler might throw errors. so this can be
 *   			   overwritten by the user application function implementation.
 *   Inputs		:  pointer to the spi base address. Flag name(which flag has to be read)
 * Output/return:  None.
 * =====================================================================================
 */
weak void SPI_applicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent)
{

}
