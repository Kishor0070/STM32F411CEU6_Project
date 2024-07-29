/*
 * usart_lib.c
 *
 *  Created on: Jul 24, 2024
 *      Author: bhadula.kishor
 */

#include "app_header.h"
#include "usart_lib.h"
#include "stm32f411xe.h"
#include <stdlib.h>

USART_BUFFER usart1_buf; // Allocated statically
USART_BUFFER usart2_buf; // Allocated statically
USART_BUFFER usart6_buf; // Allocated statically

uint8_t USART_BUFFERSIZE = 20;
char usart1_recData[21];
char usart2_recData[21];
char usart6_recData[21];
bool firstTimeFlag = true;

// It will initialize the dedicated peripheral depending on the passed USART peripheral from USART1 USART2 and USART6

void usartx_init(USART_TypeDef *usart){
	usart->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	usart->CR1 |= USART_CR1_UE;
	reset_transmit_buffer(usart);
	reset_receive_buffer(usart);

}


// It will set the baud rate for the communication
uint16_t setDiv(uint32_t pCLK, uint32_t baud){
	return (uint16_t)((pCLK+(baud/2U))/baud);
}
void setBaudRate(USART_TypeDef *usart, uint32_t baud, uint32_t pClk){
	usart->BRR = setDiv(pClk, baud);
}



bool transmit_frame(USART_TypeDef *usart, char *frame, uint8_t frameLength){
	if(frameLength > USART_BUFFERSIZE){
		return false;
	}
	volatile USART_BUFFER *buffer = NULL;
	if(usart == USART1){
		buffer = &usart1_buf;
	}else if(usart == USART2){
		buffer = &usart2_buf;
	}else if(usart == USART6){
		buffer = &usart6_buf;
	}else{
		return false;
	}

	// Check if already buffer is occupied by some other transmission
	if(!buffer->isReadyToTransmit){
		return false;
	}

	volatile uint8_t index = 0;
	buffer->occupiedSize = frameLength;
	buffer->txIndex = 0;

	while(frameLength > 0){
		buffer->txBuffer[index] = *frame;
		frame++;
		index++;
		frameLength--;
	}

	// Finally enabling Transmission interrupt
	usart->CR1 |= USART_CR1_TXEIE;

	return true;
}


// Interrupt Handler

void usart_interrupt_commonHandler(USART_TypeDef *usart){
	volatile USART_BUFFER *buffer = NULL;
	if(usart == USART1){
		buffer = &usart1_buf;
	}else if(usart == USART2){
		buffer = &usart2_buf;
	}else if(usart == USART6){
		buffer = &usart6_buf;
	}else{
		return;
	}

	// Handling Transmission Interrupt

	if(usart->SR & USART_SR_TXE){
		if(buffer->txIndex < buffer->occupiedSize){
			usart->DR = buffer->txBuffer[buffer->txIndex];
			buffer->txIndex++;
			buffer->isReadyToTransmit = false;
		}else{
			buffer->isReadyToTransmit = true;
			usart->CR1 &= ~(USART_CR1_TXEIE);
		}
	}


	// Handling Reception of data
	if(usart->SR & USART_SR_RXNE){
		firstTimeFlag = false;
		buffer->rxBuffer[buffer->rxIndexTail] = usart->DR;
		buffer->rxIndexTail = (uint8_t)((buffer->rxIndexTail + 1) % USART_BUFFERSIZE);
	}
}
void reset_transmit_buffer(USART_TypeDef *usart){
	volatile USART_BUFFER *buffer = NULL;
	if(usart == USART1){
		buffer = &usart1_buf;
	}else if(usart == USART2){
		buffer = &usart2_buf;
	}else if(usart == USART6){
		buffer = &usart6_buf;
	}else{
		return;
	}

	buffer->txIndex = 0;
	buffer->isReadyToTransmit = true;
	buffer->occupiedSize = 0;
}

volatile char* read_data_usart(USART_TypeDef *usart){
	volatile char* result = NULL;
	USART_BUFFER *buffer = NULL;
	if(usart==USART1){
		buffer = &usart1_buf;
		result = read_data_usart_helper(buffer, usart1_recData);
	}else if(usart == USART2){
		buffer = &usart2_buf;
		result = read_data_usart_helper(buffer, usart2_recData);
	}else if(usart == USART6){
		buffer = &usart6_buf;
		result = read_data_usart_helper(buffer, usart6_recData);
	}else{
		return NULL;
	}


	return result;
}

volatile char* read_data_usart_helper(USART_BUFFER *buffer, char *data){
	volatile uint8_t traverser = 0;
	if(firstTimeFlag){
		return NULL; // Read this as no change in the data.
	}

	// If new data came over usart then only read the data.
	if(buffer->rxIndexHead != buffer->rxIndexTail){
		while(buffer->rxIndexHead != buffer->rxIndexTail){
			data[traverser] = buffer->rxBuffer[buffer->rxIndexHead];
			buffer->rxIndexHead = (uint8_t)((buffer->rxIndexHead+1) % USART_BUFFERSIZE); //Since the buffer is a ring buffer
			traverser++;
		}
		// Finally marking the end of the data....
		data[traverser] = '\0';
	}else{

	}
	return data;
}
void reset_receive_buffer(USART_TypeDef *usart){
	volatile USART_BUFFER *buffer = NULL;
	if(usart == USART1){
		buffer = &usart1_buf;
	}else if(usart == USART2){
		buffer = &usart2_buf;
	}else if(usart == USART6){
		buffer = &usart6_buf;
	}else{
		return;
	}
	buffer->rxIndexHead = 0;
	buffer->rxIndexTail = 0;

}
void USART1_IRQHandler(void){
	usart_interrupt_commonHandler(USART1);
}

void USART2_IRQHandler(void){
	usart_interrupt_commonHandler(USART2);
}

void USART6_IRQHandler(void){
	usart_interrupt_commonHandler(USART6);
}
