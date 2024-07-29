#include "stm32f411xe.h"
#include "task50.h"


volatile uint8_t task50Counter;
volatile bool blink500ms;
volatile bool blink1000ms;



void blinkLed500ms(void){
	if(blink500ms){
		GPIOC->ODR &= ~(GPIO_ODR_OD13);
	}else{
		GPIOC->ODR |= (GPIO_ODR_OD13);
	}
}

void utility(void){
	task50Counter++; // Goes till 1 second and configurable


	if(task50Counter>20){
		task50Counter = 1;
	}

	if(task50Counter <= 10){
		blink500ms = true;
	}else{
		blink500ms = false;
	}
	if(task50Counter == 20){
		blink1000ms = !blink1000ms;
	}

}
