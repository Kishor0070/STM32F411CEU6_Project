/*
 * task100_pou.c
 *
 *  Created on: Jul 23, 2024
 *      Author: bhadula.kishor
 */
#include "task100.h"
#include <stdint.h>
#include "stm32f411xe.h"
#include "usart_lib.h"

volatile uint8_t task100Counter = 1;
char txData[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
char txData2[5] = {'K', 'L', 'M', 'N', 'O'};

volatile char *usartData = NULL;

void transmit_over_usart2(void){
	if(task100Counter == 5){
		transmit_frame(USART2, txData, 10);
	}else if(task100Counter == 9){
		transmit_frame(USART2, txData2, 5);
	}
	usartData = read_data_usart(USART1);
}

volatile char* getData(void){
	return usartData;
}
void utility_t100(void){
	task100Counter++;
	if(task100Counter > 10){
		task100Counter = 1;
	}

}

