/*
 * GPIO_Exti.c
 *
 *  Created on: 3 jul. 2022
 *      Author: jeffr
 */
#include "stm32f1xx.h"
#include "GPIO_Exti.h"

void GPIO_EXTI_IQRHandler(uint8_t pinNumber){
	if(EXTI->PR & (1<<pinNumber)){
		//clear
		EXTI->PR |= 1U<<pinNumber;
		GPIO_EXTI_Callback(pinNumber);
	}
}

__WEAK void GPIO_EXTI_Callback(uint8_t pinNumber){
	//todo
	(void)pinNumber;

	return;
}
