/*
 ******************************************************************************
 * @file           : 006_ArduinoSendReceiveSPI.c
 * @author         : Pranav Vasudevan- pranavmv012@gmail.com
 * @Date		   : 2023/12/06
 * @brief          : Command based send and receive data to Arduino. STM act as
 * 					 master.
 *
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
#include <stdio.h>
/*
 * Pin configure. GPIO alternate function to spi2 pins and init
 */
//command codes
#define COMMAND_LED_CTRL      		0x50
#define COMMAND_SENSOR_READ      	0x51
#define COMMAND_LED_READ      		0x52
#define COMMAND_PRINT      			0x53
#define COMMAND_ID_READ      		0x54

#define LED_ON     1
#define LED_OFF    0

//Arduino analog pins
#define ANALOG_PIN0 	0
#define ANALOG_PIN1 	1
#define ANALOG_PIN2 	2
#define ANALOG_PIN3 	3
#define ANALOG_PIN4 	4

//Arduino led

#define LED_PIN  9
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
//spi2 miso-not used
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
  SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV16;//divid pck as per the need
  SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
  SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_SW_DI;//hardware slave management
  SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
  SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;

  SPI_Init(&SPI2Handle);
}
void gpio_buttonInit()
{	GPIO_Handle_t GpioButton;
	GpioButton.pGPIOx = GPIOC;
	GpioButton.GPIO_Pin_Config.GPIO_PinNum = GPIO_PIN_13;
	GpioButton.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT;
	GpioButton.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
	GpioButton.GPIO_Pin_Config.GPIO_PinPuPdCntrl = GPIO_PUPDR_NPUPD;

	GPIO_Init(&GpioButton);
}
void delay()
{
	for (int i=0; i<500000/2; i++)
	{

	}
}
//function to check whether the SPI received data is Ack or Nack
uint8_t SPI_ResponseVerify( uint8_t ackByte)
{
	if(ackByte == 0xF5)
	{
		return 1;
	}
	return 0;
}

//main function
int main(void)
{
	uint8_t dummyByte = 0xFF;
	uint8_t dummyRead;
	//spi af config
	spi2_gpio_init();
	gpio_buttonInit();
	//spi2 config and init
	spi2_init();
	printf("SPI Init. done\n");
	//spi2 enable.
	//Nss singal interally high to avoid modf error
//	SPI_SSIConfig(SPI2, ENABLE); only needed when software slave management is used
	//before enabling the spi2 peripheral make ssoe enable for the hardware slave management.
	SPI_SSOEConfig(SPI2, ENABLE);
	while(1)
	{
		while( !GPIO_ReadInputPin(GPIOC, GPIO_PIN_13) );
		delay();
		SPI_peri_control(SPI2, ENABLE);
		//Led control
		uint8_t commandCode = COMMAND_LED_CTRL;
		uint8_t ackByte;
		uint8_t arg[2];
		SPI_SendData(SPI2, &commandCode, 1);
		//when send a data it extects a data to be received that will set the rxne bit set.
		//to clear this a dummy read is done
		SPI_ReceiveData(SPI2, &dummyRead, 1);

		//send dummy data of 1 byte to fetch the receive data from the slave
		SPI_SendData(SPI2, &dummyByte, 1);
		SPI_ReceiveData(SPI2, &ackByte, 1);
		//check ackByte.
		if(SPI_ResponseVerify(ackByte))
		{
			arg[0] = LED_PIN;
			arg[1] = LED_ON;
			SPI_SendData(SPI2, arg, 2);
			printf("COMMAND_LED_CTRL Executed\n");

		}
		//analog read.
		while( !GPIO_ReadInputPin(GPIOC, GPIO_PIN_13) );
		delay();
		commandCode = COMMAND_SENSOR_READ;
		SPI_SendData(SPI2, &commandCode, 1);
		SPI_ReceiveData(SPI2, &dummyRead, 1);
		SPI_SendData(SPI2, &dummyByte, 1);
		SPI_ReceiveData(SPI2, &ackByte, 1);
		//check ackByte.
		if(SPI_ResponseVerify(ackByte))
		{
			arg[0] = ANALOG_PIN0;

			SPI_SendData(SPI2, arg, 1);

			SPI_ReceiveData(SPI2, &dummyRead, 1);
			//put delay so that the slave can complete the analog conversion.
			delay();
			SPI_SendData(SPI2, &dummyByte, 1); // to read response on the analog pin
			uint8_t analogRead;
			SPI_ReceiveData(SPI2, &analogRead, 1);
			printf("COMMAND_SENSOR_READ %d\n",analogRead);
		}
		//Led status

		while( !GPIO_ReadInputPin(GPIOC, GPIO_PIN_13) );
		delay();
		commandCode = COMMAND_LED_READ;
		SPI_SendData(SPI2, &commandCode, 1);
		SPI_ReceiveData(SPI2, &dummyRead, 1);
		SPI_SendData(SPI2, &dummyByte, 1);
		SPI_ReceiveData(SPI2, &ackByte, 1);
		//check ackByte.
		if(SPI_ResponseVerify(ackByte))
		{
			arg[0] = LED_PIN;

			SPI_SendData(SPI2, arg, 1);

			SPI_ReceiveData(SPI2, &dummyRead, 1);
			//put delay so that the slave can complete the analog conversion.
			delay();
			SPI_SendData(SPI2, &dummyByte, 1); // to read response on the analog pin
			uint8_t ledStatus;
			SPI_ReceiveData(SPI2, &ledStatus, 1);
			printf("command read led: %d",ledStatus);
		}
		while (SPIgetFlagStatus(SPI2, SPI_BUSY_FLAG));
		SPI_peri_control(SPI2, DISABLE);//close the peripheral
		printf("SPI Communication Closed\n");


	}
}
