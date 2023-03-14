/*
 *====================================================================================
 *
 * Name				:stm32f303xx_i2c_drv.h
 * Description:		:Peripheral specific header file for i2c of stm32f303xx.
 * Created on       :2023/03/12
 * Author           :Pranav Vasudevan- pranavmv012@gmail.com
 *=====================================================================================
 */

#ifndef INC_STM32F303XX_I2C_DRV_H_
#define INC_STM32F303XX_I2C_DRV_H_
#include "stm32f303xx.h"
#include <stdint.h>
/*I2C register bit position macros */

/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				17
#define I2C_CR1_STOPIE  				 5
#define I2C_NACKIE				 		4
#define I2C_CR1_SWRST  				 	15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_START				 	13
#define I2C_CR2_STOP				 	14
#define I2C_CR2_NACK				 	15
#define I2C_CR2_RD_WRN 			    	10

///*
// * Bit position definitions I2C_OAR1
// */
//#define I2C_OAR1_ADD0    				 0
//#define I2C_OAR1_ADD71 				 	 1
//#define I2C_OAR1_ADD98  			 	 8
//#define I2C_OAR1_ADDMODE   			 	15
//
///*
// * Bit position definitions I2C_SR1
// */
//
//#define I2C_SR1_SB 					 	0
//#define I2C_SR1_ADDR 				 	1
//#define I2C_SR1_BTF 					2
//#define I2C_SR1_ADD10 					3
//#define I2C_SR1_STOPF 					4
//#define I2C_SR1_RXNE 					6
//#define I2C_SR1_TXE 					7
//#define I2C_SR1_BERR 					8
//#define I2C_SR1_ARLO 					9
//#define I2C_SR1_AF 					 	10
//#define I2C_SR1_OVR 					11
//#define I2C_SR1_TIMEOUT 				14
//
///*
// * Bit position definitions I2C_SR2
// */
//#define I2C_SR2_MSL						0
//#define I2C_SR2_BUSY 					1
//#define I2C_SR2_TRA 					2
//#define I2C_SR2_GENCALL 				4
//#define I2C_SR2_DUALF 					7
//
///*
// * Bit position definitions I2C_CCR
// */
//#define I2C_CCR_CCR 					 0
//#define I2C_CCR_DUTY 					14
//#define I2C_CCR_FS  				 	15

/*I2C configuration structure*/
typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress;
	uint8_t  I2C_AckControl;
	uint8_t  I2C_FMDutyCycle;

}I2C_Config_t;


/*Handle for spi*/
typedef struct
{
	I2C_Reg_Def_t *pI2Cx; //pointer to hold the base address of the spi line
	I2C_Config_t I2CConfig;

}I2C_Handle_t;

#endif /* INC_STM32F303XX_I2C_DRV_H_ */
