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
#include <stdint.h>

void spi_gpio_init(void)
{

}
int main(void)
{

	spi_gpio_init();
	while(1);

}
