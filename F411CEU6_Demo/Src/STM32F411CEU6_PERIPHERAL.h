#ifndef STM32F411CEU6_PERIPHERAL

#define STM32F411CEU6_PERIPHERAL

#include <stdint.h>
/* This library is designed just for STMF411 CEU6 Black Pill Board so, all the registers for
STM32F411 series are not defined and not used.
*/

#define PERIPH_BASE										(0x40000000UL)
#define APB1_BASE										(PERIPH_BASE)
#define AHB1_OFFSET										(0x00020000UL)
#define AHB1_BASE										(PERIPH_BASE + AHB1_OFFSET)
#define GPIOA_BASE_OFFSET								(0x00UL)
#define GPIOA_BASE										(AHB1_BASE + GPIOA_BASE_OFFSET)
#define GPIOB_BASE_OFFSET								(0x0400UL)
#define GPIOB_BASE										(AHB1_BASE + GPIOB_BASE_OFFSET)
#define GPIOC_BASE_OFFSET								(0x0800UL)
#define GPIOC_BASE										(AHB1_BASE + GPIOC_BASE_OFFSET)

// RCC Clock Enabling Registers
#define RCC_OFFSET										(0x3800UL)
#define RCC_BASE										(AHB1_BASE + RCC_OFFSET)
#define GPIOA_EN										(0x01UL<<0)
#define GPIOB_EN										(0x01UL<<1)
#define GPIOC_EN										(0x01UL<<2)

#define GPIOC_PIN13										(0x01UL<<26)

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_TypeDef;

typedef struct{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t DCKCFGR;
}RCC_TypeDef;

#define RCC											((RCC_TypeDef*) RCC_BASE)
#define GPIOA										((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB										((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC										((GPIO_TypeDef*) GPIOC_BASE)


#endif
