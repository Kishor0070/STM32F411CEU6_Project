/*
 * custom_usart2_library.h
 *
 *  Created on: Jul 19, 2024
 *      Author: bhadula.kishor
 */

#ifndef CUSTOM_USART2_LIBRARY_H_
#define CUSTOM_USART2_LIBRARY_H_

#include "stm32f411xe.h"
#include <stdint.h>
#include <stdbool.h>

//uint16_t setDiv(uint32_t pCLK, uint32_t baud);
void usart2_init(void);
//void transmit_frame(char *frame, uint8_t dataLength);
//void transmit_byte(char data);
//char receiveByte();
//char* receive_frame();

static volatile char txBuffer[100];
static volatile char rxBuffer[100];
static volatile uint8_t txIndex = 0;
static volatile uint8_t rxIndex = 0;
static volatile uint8_t curTxBufSize = 0;
static volatile bool isTransOngoing = false;

#define BUFFER_SIZE										((uint8_t)100)
#define USART2_BAUDRATE									9600UL
#define OperatingClock									16000000UL

/*
void usart2_init(){
	// Enabling clock for the peripheral
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	// Configured PB7 to Alternate function
	GPIOB->MODER |= (3U<<14);
	GPIOB->MODER &= ~(1U<<14);

	// Configured PA2 to Alternate function
	GPIOA->MODER |= (3U<<4);
	GPIOA->MODER &= ~(1U<<4);

	// Configured PB7 to USART1 RX line
	GPIOB->AFR[0] |= (7U<<28);
	GPIOB->AFR[0] &= ~(8U<<28);

	// Configured PA2 to USART2 TX line
	GPIOA->AFR[0] |= (7U<<8);
	GPIOA->AFR[0] &= ~(8U<<8);


	USART2->CR1 |= (USART_CR1_TE);
	USART1->CR1 |= (USART_CR1_RE);

	USART2->CR1 |= USART_CR1_UE;
	USART1->CR1 |= USART_CR1_UE;

	USART2->BRR = setDiv(OperatingClock, USART2_BAUDRATE);
	USART1->BRR = setDiv(OperatingClock, USART2_BAUDRATE);

}
*/

// Implemented Interrupt
//void USART2_IRQHandler(void){
//	// For transmitting
//	if(USART2->SR & USART_SR_TXE){
//		if(txIndex < curTxBufSize){
//			USART2->DR = txBuffer[txIndex];
//			txIndex++;
//			isTransOngoing = true;
//		}else{
//			isTransOngoing = false;
//			USART2->CR1 &= ~(USART_CR1_TXEIE);
//		}
//	}
//
//
//	// For Data Reception
//	/*
//	if(USART2->SR & USART_SR_RXNE){
//
//	}
//	*/
//}


/*
void transmit_frame(char *frame, uint8_t dataLength){
	// Making sure that the buffer fills from the starting index
	if((dataLength > BUFFER_SIZE) | isTransOngoing){
		return;
	}
	volatile uint8_t index = 0;
	curTxBufSize = dataLength;
	txIndex = 0;

	while(dataLength > 0){
		txBuffer[index] = *frame;
		index++;
		frame++;
		dataLength--;
	}

	USART2->CR1 |= USART_CR1_TXEIE;
}
*/
/*
void transmit_byte(char data){
	while(!(USART2->SR & USART_SR_TXE)){

	}
	USART2->DR = data;
}

char receiveByte(){

	while(!(USART2->SR & USART_SR_RXNE)){

	}
	return USART2->DR;
}

char* receive_frame(){

	while(!(USART2->SR & USART_SR_RXNE)){}
	temp = USART2->DR;

	return &buffer;
}
*/
/*
uint16_t setDiv(uint32_t pClk, uint32_t baud){
	// Over sampling by 16
	USART2->CR1 |= ~(USART_CR1_OVER8);
	return (uint16_t)(pClk/(16*baud));
}
*/

/*
uint16_t setDiv(uint32_t pCLK, uint32_t baud){
	return (uint16_t)((pCLK+(baud/2U))/baud);
}
*/

#endif /* CUSTOM_USART2_LIBRARY_H_ */
