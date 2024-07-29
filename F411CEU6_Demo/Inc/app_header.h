/*
 * app_header.h
 *
 *  Created on: Jul 24, 2024
 *      Author: bhadula.kishor
 */

#ifndef APP_HEADER_H_
#define APP_HEADER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct{
	volatile bool isReadyToTransmit;
	volatile uint8_t occupiedSize;
	volatile uint8_t txIndex;
	volatile uint8_t rxIndexHead;
	volatile uint8_t rxIndexTail;
	volatile char txBuffer[20];
	volatile char rxBuffer[20];

} USART_BUFFER;


extern USART_BUFFER usart1_buf; // Statically Allocated
extern USART_BUFFER usart2_buf; // Statically Allocated
extern USART_BUFFER usart6_buf; // Statically Allocated

#endif /* APP_HEADER_H_ */
