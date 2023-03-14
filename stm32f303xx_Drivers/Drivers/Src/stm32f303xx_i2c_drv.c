/*
 *=====================================================================================
 *
 * Name				:stm32f303xx_i2c_drv.c
 * Description		:This source file implements the I2C apis for the user application
 * 					 for stm32f303xx.
 * Created on       :2022/12/30
 * Author           :Pranav Vasudevan- pranavmv012@gmail.com
 *=====================================================================================
 */

#include "stm32f303xx_i2c_drv.h"
/*
 * Clock enable and disable macros.
 */
RCC_Reg_Def_t *piRCC = RCC;
#define I2C1_PCLK_EN() (piRCC->RCC_APB2ENR |= (1 << 21) )
#define I2C2_PCLK_EN() (piRCC->RCC_APB1ENR |= (1 << 22) )
#define I2C3_PCLK_EN() (piRCC->RCC_APB1ENR |= (1 << 30) )

#define I2C1_PCLK_DI() (piRCC->RCC_APB2ENR &= ~(1 << 21) )
#define I2C2_PCLK_DI() (piRCC->RCC_APB1ENR &= ~(1 << 22) )
#define I2C3_PCLK_DI() (piRCC->RCC_APB1ENR &= ~(1 << 30) )

