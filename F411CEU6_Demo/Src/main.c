// #include "STM32F411CEU6_PERIPHERAL.h"
#include "stm32f411xe.h"
#include <stdbool.h>
#include <stdint.h>
#include "task50.h"
#include "custom_systick.h"
#include "usart_lib.h"
#include "app_header.h"
#include <stddef.h>
#include "task100.h"

#define OP_FREQ									16000000U

void application_init(void);
bool isPasswordCorrect(void);

char password[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
volatile char *data = NULL;

int main(void){

	// For testing purpose only
	volatile char *temp = NULL;

	application_init();


	while(1){
		// Continuously check for the data received on USART6 peripheral
		temp = getData();
		if(temp != NULL){
			data = temp;
		}
		if(isPasswordCorrect()){
			GPIOC->ODR &= ~(0x01<<13);
		}else{
			GPIOC->ODR |= (0x01<<13);
		}

	}
}

bool isPasswordCorrect(void){
	volatile uint8_t index = 0;

	if(data == NULL){
		return false;
	}
	while(index < USART_BUFFERSIZE && index < 10){
		if(data[index] == '\0' || data[index] != password[index]){
			return false;
		}
		index++;
	}

	return true;
}


void application_init(void){
	// Provide clock access to the used peripherals
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

	// Configure PA2 for transmitting over USART2 peripheral
	GPIOA->MODER |= GPIO_MODER_MODE2_Msk;
	GPIOA->MODER &= ~(GPIO_MODER_MODE2_0);

	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL2);
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2_3);

	// configure USART2 for the PA2
	usartx_init(USART2);
	setBaudRate(USART2, 9600U, OP_FREQ);

	// Configure PB7 for receiving over USART1 peripheral
	GPIOB->MODER |= GPIO_MODER_MODE7_Msk;
	GPIOB->MODER &= ~(GPIO_MODER_MODE7_0);

	GPIOB->AFR[0] |= GPIO_AFRL_AFRL7;
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL7_3);

	usartx_init(USART1);
	setBaudRate(USART1, 9600U, OP_FREQ);
	// Configure PC13 for output mode to turn on / off led on the board.

	GPIOC->MODER |= GPIO_MODER_MODE13;
	GPIOC->MODER &= ~(GPIO_MODER_MODE13_1);

	// Enable interrupts for the USART peripherals
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_EnableIRQ(USART2_IRQn);

	USART1->CR1	|= USART_CR1_RXNEIE;

	systick_init();

}
