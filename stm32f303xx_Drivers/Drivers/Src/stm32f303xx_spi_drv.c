/*
 *=====================================================================================
 *
 * Name				:stm32f303xx_spi_drv.c
 * Description:		:This source file implements the spi apis for the user application.
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
void SPI_Init(SPI_Handle_t *pSPIHandle);
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
 *   Name		:  SPI_SendData
 *   Description:  Function to send data over SPI
 *   Inputs		:  Pointer to the base add of the SPI, pointer to the tx data, Data len
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_SendData(SPI_Reg_Def_t *pSPIx, uint8_t *pTxbuffer, uint32_t Len);
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_SendData
 *   Description:  Function to send data over SPI
 *   Inputs		:  Pointer to the base add of the SPI, pointer to the rx data, Data len
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_ReceiveData(SPI_Reg_Def_t *pSPIx, uint8_t *pRxbuffer, uint32_t Len);
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
void SPI_IRQConfig(uint8_t IRQNum, uint8_t ENorDI);
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_IRQ_PriorityConfig
 *   Description:  Function to set the priority fo the interrupt.
 *   			   Refer 4.2.7 of ARM DUI 0553B
 *   Inputs		:  Pin number at which interrupt triggers.
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_IRQ_PriorityConfig(uint8_t IRQNum, uint32_t IRQPriority);
/*
 * ===  FUNCTION  ======================================================================
 *   Name		:  SPI_IRQHandler
 *   Description:  Function to handle the SPI interrupt.
 *   Inputs		:  pointer to the handle, that contains the spi peri at which interrupt
 *   			   occurred.
 * Output/return:  None.
 * =====================================================================================
 */
void SPI_IRQHandler(SPI_Handle_t *pSPIHandle);
