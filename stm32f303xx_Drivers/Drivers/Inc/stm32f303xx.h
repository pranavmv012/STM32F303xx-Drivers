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
#include <stddef.h>
#define __vo	volatile
#define weak 	__attribute__((weak))
/*=====================================================================================
 * Processor side register macros - ARM cortex M4
 *
 * Refer the cortex M4 device generic user guide
 *=====================================================================================*/

/*NVIC marcos*/
/*Interrupt Set-enable Registers base address - ARM DUI 0553B 4-3
 * 81 IRQ number for the mcu. so needed only 3 ISER register. Declaring those regs only.
 */
#define NVIC_ISER0 	((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1 	((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2 	((__vo uint32_t*)0xE000E108)

/*Interrupt Clear-enable Registers*/

#define NVIC_ICER0 	((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1 	((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2 	((__vo uint32_t*)0xE000E188)

/*Interrupt priority setting resgister*/

#define NVIC_IPR_BASE_ADDR		((__vo uint32_t*)0xE000E400)

/*no of priority bits implemented. the lower 4 bits in the 8 bit priority bit field
 * is reserved.
 */
#define NO_PR_BIT_IMPLEMENTED	4
/*=====================================================================================
 * Peripheral side register macros - STM32F303RE
 *
 * Refer reference manual
 *=====================================================================================*/
#define ENABLE 		1
#define DISABLE 	0
#define SET 		ENABLE
#define RESET 		DISABLE
#define PIN_SET 	SET
#define PIN_RESET 	RESET
#define FLAG_SET	SET
#define FLAG_RESET	RESET

/*=====================================================================================
 * Peripheral side register macros - STM32F303RE
 *
 * Refer reference manual
 *=====================================================================================*/
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

/*
 * IRQ number for EXTI line - specific to stm32f303RE
 * Refer the NVIC vector table: RM 289/1141
 *-was done for gpio*/

#define IRQ_NUM_EXTI0 		6
#define IRQ_NUM_EXTI1 		7
#define IRQ_NUM_EXTI2_TS 	8
#define IRQ_NUM_EXTI3 		9
#define IRQ_NUM_EXTI4 		10
#define IRQ_NUM_EXTI9_5 	23
#define IRQ_NUM_EXTI15_10	40
/*
 * IRQ number of spi peripheral-
 * associated with spi global intervals.
 */
#define IRQ_NUM_SPI1		42
#define IRQ_NUM_SPI2		43
#define IRQ_NUM_SPI3		58
#define IRQ_NUM_SPI4		84
/*NVIC IRQ priority*/
#define NVIC_IRQ_PRIO0		0
#define NVIC_IRQ_PRIO1		1
#define NVIC_IRQ_PRIO2		2
#define NVIC_IRQ_PRIO3		3
#define NVIC_IRQ_PRIO4		4
#define NVIC_IRQ_PRIO5		5
#define NVIC_IRQ_PRIO6		6
#define NVIC_IRQ_PRIO7		7
#define NVIC_IRQ_PRIO8		8
#define NVIC_IRQ_PRIO9		9
#define NVIC_IRQ_PRIO10		10
#define NVIC_IRQ_PRIO11		11
#define NVIC_IRQ_PRIO12		12
#define NVIC_IRQ_PRIO13		13
#define NVIC_IRQ_PRIO14		14
#define NVIC_IRQ_PRIO15		15

/*Structures for peripheral registers -GPIO */

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

/*Structures for peripheral registers SPI */

typedef struct
{
__vo uint32_t CR1;
__vo uint32_t CR2;
__vo uint32_t SR;
__vo uint32_t DR;
__vo uint32_t CRCPR;
__vo uint32_t RXCRCR;
__vo uint32_t TXCRCR;
__vo uint32_t I2SCFGR;
__vo uint32_t I2SPR;
}SPI_Reg_Def_t;

/*Structures for peripheral registers RCC */

typedef struct
{
 __vo uint32_t RCC_CR;
 __vo uint32_t RCC_CFGR;
 __vo uint32_t RCC_CIR;
 __vo uint32_t RCC_APB2RSTR;
 __vo uint32_t RCC_APB1RSTR;
 __vo uint32_t RCC_AHBENR;
 __vo uint32_t RCC_APB2ENR;
 __vo uint32_t RCC_APB1ENR;
 __vo uint32_t RCC_BDCR;
 __vo uint32_t RCC_CSR;
 __vo uint32_t RCC_AHBRSTR;
 __vo uint32_t RCC_CFGR2;
 __vo uint32_t RCC_CFGR3;
}RCC_Reg_Def_t;

/*Structures for peripheral registers EXTI*/

typedef struct

{
__vo uint32_t EXTI_IMR1; //from rm 303/1141
__vo uint32_t EXTI_EMR1;
__vo uint32_t EXTI_RTSR1;
__vo uint32_t EXTI_FTSR1;
__vo uint32_t EXTI_SWIER1;
__vo uint32_t EXTI_PR1;
}EXTI_Reg_Def_t;

/*Structures for peripheral registers Syscfg*/

typedef struct
{
__vo uint32_t SYSCFG_CFGR1;
__vo uint32_t SYSCFG_RCR;
__vo uint32_t SYSCFG_EXTICR[4];
//rest are not included in this app. if you want please add it from RM 261/1141

}SYSCFG_Reg_Def_t;

/*pointer variable to access individual register of a peripheral */
#define GPIOA	(GPIO_Reg_Def_t*)GPIOA_BASE_ADDR
#define GPIOB	(GPIO_Reg_Def_t*)GPIOB_BASE_ADDR
#define GPIOC	(GPIO_Reg_Def_t*)GPIOC_BASE_ADDR
#define GPIOD	(GPIO_Reg_Def_t*)GPIOD_BASE_ADDR
#define GPIOE	(GPIO_Reg_Def_t*)GPIOE_BASE_ADDR
#define GPIOF	(GPIO_Reg_Def_t*)GPIOF_BASE_ADDR
#define GPIOG	(GPIO_Reg_Def_t*)GPIOG_BASE_ADDR
#define GPIOH	(GPIO_Reg_Def_t*)GPIOH_BASE_ADDR


/*Peripheral definitions for SPIs*/
#define SPI1 (SPI_Reg_Def_t*)SPI1_BASE_ADDR
#define SPI2 (SPI_Reg_Def_t*)SPI2_BASE_ADDR
#define SPI3 (SPI_Reg_Def_t*)SPI3_BASE_ADDR
#define SPI4 (SPI_Reg_Def_t*)SPI4_BASE_ADDR


/*Peripheral definitions for RCC*/
#define RCC (RCC_Reg_Def_t*)RCC_BASE_ADDR


#define EXTI (EXTI_Reg_Def_t*)EXTI_BASE_ADDR

#define SYSCFG (SYSCFG_Reg_Def_t*)SYSCFG_BASE_ADDR

/**/
/*EXTI*/
#define EXTI_BASE_ADDR		(APB2_PER_BASE_ADDR + 0x0400UL)
#define SYSCFG_BASE_ADDR	(APB2_PER_BASE_ADDR + 0x0000UL)

/*
 * macro to get the port code. The base address of the peripheral is given to
 * the function and it generates corresponding port code.
 */
#define GET_PORT_CODE(x)	     ((x == GPIOA) ? 0 : \
								  (x == GPIOB) ? 1 : \
								  (x == GPIOC) ? 2 : \
								  (x == GPIOD) ? 3 : \
								  (x == GPIOE) ? 4 : \
								  (x == GPIOF) ? 5 : \
								  (x == GPIOG) ? 6 : \
								  (x == GPIOH) ? 7 : 0)

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

#include "stm32f303xx_spi_drv.h"
#include "stm32f303xx_gpio_drv.h"
#endif /* INC_STM32F303XX_H_ */
