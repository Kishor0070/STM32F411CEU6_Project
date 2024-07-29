
#include "custom_systick.h"
#include "stm32f411xe.h"
#include "task50.h"
#include "task100.h"
#define SYS_CLOCK					16000000UL

// By default SysTick is enabled for 10 milliseconds interrupt
volatile uint8_t timingCounter;
volatile bool task50msFlag;
volatile bool task100msFlag;

void systick_init(){
	volatile uint32_t reloadValue = ((SYS_CLOCK/100)) - 1;
	SysTick->CTRL = 0;
	SysTick->LOAD = reloadValue;

	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

}

void SysTick_Handler(void){

	// Cycling counter for 2 seconds
	timingCounter++;
	if(timingCounter > 200){
		timingCounter = 1;
	}

	if((timingCounter%5) == 0){
		task50msFlag = true;
	}
	else{
		task50msFlag = false;
	}
	if((timingCounter%10) == 0){
		task100msFlag = true;
	}else{
		task100msFlag = false;
	}

	// Call the dedicated tasks here..
	if(task50msFlag){
		task_50ms();
	}
	if(task100msFlag){
		task_100ms();
	}
}

void task_50ms(void){
	utility();
	//blinkLed500ms();
}
void task_100ms(void){
	utility_t100();
	transmit_over_usart2();
}
