/*
 *=====================================================================================
 *
 * Name				:stm32f303xx.h
 * Description:		:This device specification file supports GPIO, SPI, I2C and UART
 * 					 peripherals.So the base addresses of the other peripheral on the
 * 					 buses are not declared in this file. Please add the base address
 * 					 if you want to use other peripherals than above mentioned.
 * Created on       :2022/12/12
 * Author           :Pranav Vasudevan- pranavmv012@gmail.com
 *=====================================================================================
 */

#ifndef INC_STM32F303XX_H_
#define INC_STM32F303XX_H_


#include <stdint.h>
#define __vo	volatile

/*some generic macros*/
#define ENABLE 		1
#define DISABLE 	0
#define SET 		ENABLE
#define RESET 		DISABLE
#define PIN_SET 	SET
#define PIN_RESET 	RESET

/*Base addresses of Memory banks*/
#define FLASH_BASE_ADDR		0x08000000UL
#define SRAM1_BASE_ADDR		0x20000000UL
#define CCM_RAM_BASE_ADDR	0x10000000UL
#define ROM_BASE_ADDR		0x1FFFD800UL
#define SRAM_BASE_ADDR		SRAM1_BASE_ADDR

/*Peripheral base addresses- RM page 59*/
#define	PER_BASE_ADDR		0x40000000UL
#define APB1_PER_BASE_ADDR	PER_BASE_ADDR
#define APB2_PER_BASE_ADDR	0x40010000UL
#define AHB1_PER_BASE_ADDR	0x40020000UL
#define AHB2_PER_BASE_ADDR	0x48000000UL
#define AHB3_PER_BASE_ADDR	0x50000000UL
#define AHB4_PER_BASE_ADDR	0x60000000UL

/*RCC*/
#define RCC_BASE_ADDR 		(AHB1_PER_BASE_ADDR+ 0x1000UL)

/*Base addresses of peripherals which are hanging on to AHB2 BUS-GPIO*/
#define GPIOA_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x0000UL)
#define GPIOB_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x0400UL)
#define GPIOC_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x0800UL)
#define GPIOD_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x0C00UL)
#define GPIOE_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x1000UL)
#define GPIOF_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x1400UL)
#define GPIOG_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x1800UL)
#define GPIOH_BASE_ADDR		(AHB2_PER_BASE_ADDR+ 0x1C00UL)

/*Base addresses of peripherals which are hanging on to APB1 BUS-I2c*/

#define I2C1_BASE_ADDR		(APB1_PER_BASE_ADDR + 0x5400UL)
#define I2C2_BASE_ADDR		(APB1_PER_BASE_ADDR + 0x5800UL)
#define I2C3_BASE_ADDR		(APB1_PER_BASE_ADDR + 0x7800UL)

/*SPI base address*/
#define SPI1_BASE_ADDR		(APB2_PER_BASE_ADDR + 0x3000UL)
#define SPI2_BASE_ADDR		(APB1_PER_BASE_ADDR + 0x3800UL)
#define SPI3_BASE_ADDR		(APB1_PER_BASE_ADDR + 0x3C00UL)
#define SPI4_BASE_ADDR		(APB2_PER_BASE_ADDR + 0x3C00UL)

/*UART */
#define USART1_BASE_ADDR	(APB2_PER_BASE_ADDR + 0x3800UL)
#define USART2_BASE_ADDR	(APB1_PER_BASE_ADDR + 0x4400UL)
#define USART3_BASE_ADDR	(APB1_PER_BASE_ADDR + 0x4800UL)
#define UART4_BASE_ADDR		(APB1_PER_BASE_ADDR + 0x4C00UL)
#define UART5_BASE_ADDR		(APB1_PER_BASE_ADDR + 0x5000UL)

/*EXTI*/
#define EXTI_BASE_ADDR		(APB2_PER_BASE_ADDR + 0x0400UL)
#define SYSCFG_BASE_ADDR	(APB2_PER_BASE_ADDR + 0x0000UL)


/*Structures for peripheral registers -GPIO*/

typedef struct
{
 __vo uint32_t MODER;
 __vo uint32_t OTYPER;
 __vo uint32_t OSPEEDR;
 __vo uint32_t PUPDR;
 __vo uint32_t IDR;
 __vo uint32_t ODR;
 __vo uint32_t BSRR;
 __vo uint32_t LCKR;
 __vo uint32_t AFR[2];
 __vo uint32_t BRR;
}GPIO_Reg_Def_t;

/*Structures for peripheral registers -GPIO*/

typedef struct
{
 __vo uint32_t RCC_CR;
 __vo uint32_t RCC_CFGR;
 __vo uint32_t RCC_CIR;
 __vo uint32_t RCC_APB2RSTR;
 __vo uint32_t CC_APB1RSTR;
 __vo uint32_t RCC_AHBENR;
 __vo uint32_t RCC_APB2ENR;
 __vo uint32_t RCC_APB1ENR;
 __vo uint32_t RCC_BDCR;
 __vo uint32_t RCC_CSR;
 __vo uint32_t RCC_AHBRSTR;
 __vo uint32_t RCC_CFGR2;
 __vo uint32_t RCC_CFGR3;
}RCC_Reg_Def_t;

typedef struct

{
__vo uint32_t EXTI_IMR1; //from rm 303/1141
__vo uint32_t EXTI_EMR1;
__vo uint32_t EXTI_RTSR1;
__vo uint32_t EXTI_FTSR1;
__vo uint32_t EXTI_SWIER1;
__vo uint32_t EXTI_PR1;

}EXT_Reg_Def_t;

/*pointer variable to access individual register of a peripheral */
#define GPIOA	(GPIO_Reg_Def_t*)GPIOA_BASE_ADDR
#define GPIOB	(GPIO_Reg_Def_t*)GPIOB_BASE_ADDR
#define GPIOC	(GPIO_Reg_Def_t*)GPIOC_BASE_ADDR
#define GPIOD	(GPIO_Reg_Def_t*)GPIOD_BASE_ADDR
#define GPIOE	(GPIO_Reg_Def_t*)GPIOE_BASE_ADDR
#define GPIOF	(GPIO_Reg_Def_t*)GPIOF_BASE_ADDR
#define GPIOG	(GPIO_Reg_Def_t*)GPIOG_BASE_ADDR
#define GPIOH	(GPIO_Reg_Def_t*)GPIOH_BASE_ADDR

#define RCC (RCC_Reg_Def_t*)RCC_BASE_ADDR


#define EXTI (EXTI_Reg_Def_t*)EXTI_BASE_ADDR



/**/



#endif /* INC_STM32F303XX_H_ */
