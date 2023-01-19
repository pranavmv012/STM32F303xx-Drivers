/**
 ******************************************************************************
 * @file           : 004_spi_tx_sendDatatest.c
 * @author         : Pranav Vasudevan- pranavmv012@gmail.com
 * @Date		   : 2023/12/06
 * @brief          : main file.Implements spi data send.
 ******************************************************************************
 */

/*
 * SPI pin configuration : referred form AF GPIO pin config Datasheet. 55/173
 *
 *spi2_MOSI		PB15
 *spi2_MISO 	PB14
 *spi2_SCLK		PB13
 *spi2_NSS		PB12
 *Alternate functionality AF5
 */
#include "stm32f303xx.h"
#include <string.h>
#include <stdint.h>
/*
 * Pin configure. GPIO alternate function to spi2 pins and init
 */
void spi2_gpio_init(void)
{
GPIO_Handle_t SPI2pins;
//enable the peripheral clock for gpiob : its done in the init function itself

SPI2pins.pGPIOx = GPIOB;
SPI2pins.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_AF;
SPI2pins.GPIO_Pin_Config.GPIO_PinAFmode = GPIO_AFR_AF5;
SPI2pins.GPIO_Pin_Config.GPIO_PinOType = GPIO_OUT_TYPE_PP; //spi does not need open drain. so pp
SPI2pins.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
SPI2pins.GPIO_Pin_Config.GPIO_PinPuPdCntrl = GPIO_PUPDR_NPUPD;

//spi2 mosi
SPI2pins.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_15;
GPIO_Init(&SPI2pins);
//spi2 miso
SPI2pins.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_14;
GPIO_Init(&SPI2pins);
//spi2 sclk
SPI2pins.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_13;
GPIO_Init(&SPI2pins);
//spi2 nss
SPI2pins.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_12;
GPIO_Init(&SPI2pins);
}
/*
 * spi2 config and init.
 */
void spi2_init()
{
  SPI_Handle_t SPI2Handle;

  SPI2Handle.pSPIx = SPI2;
  SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
  SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
  SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
  SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
  SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_SW_EN;
  SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
  SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;

  SPI_Init(&SPI2Handle);
}
//main function
int main(void)
{
	char DataToSend[] = "Hello Pranav";
	//spi af config
	spi2_gpio_init();
	//spi2 config and init
	spi2_init();
	//spi2 enable.
	//Nss singal interally high to avoid modf error
	SPI_SSIConfig(SPI2, ENABLE);
	SPI_peri_control(SPI2, ENABLE);
	SPI_SendData(SPI2, (uint8_t*)DataToSend, strlen(DataToSend));
	//Checking if the peripheral is busy or not.
	while (SPIgetFlagStatus(SPI2, SPI_BUSY_FLAG));
	SPI_peri_control(SPI2, DISABLE);
	while(1);

}
