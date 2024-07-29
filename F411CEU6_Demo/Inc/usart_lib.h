/*
 * usart_lib.h
 *
 *  Created on: Jul 24, 2024
 *      Author: bhadula.kishor
 */

#ifndef USART_LIB_H_
#define USART_LIB_H_

#include "app_header.h"
#include "stm32f411xe.h"
#include <stdbool.h>
#include <stdint.h>

extern uint8_t USART_BUFFERSIZE;




void usartx_init(USART_TypeDef *usart);
bool transmit_frame(USART_TypeDef *usart, char *frame, uint8_t frameLength);
uint16_t setDiv(uint32_t pCLK, uint32_t baud);
void setBaudRate(USART_TypeDef *usart, uint32_t baud, uint32_t pClk);
void usart_interrupt_commonHandler(USART_TypeDef *usart);
void reset_transmit_buffer(USART_TypeDef *usart);
void reset_receive_buffer(USART_TypeDef *usart);
volatile char* read_data_usart(USART_TypeDef *usart);
volatile char* read_data_usart_helper(USART_BUFFER *buffer, char* data);
#endif /* USART_LIB_H_ */
