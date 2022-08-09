/*
 * stm32f1xx_it.c
 *
 *  Created on: 20 jul. 2022
 *      Author: jeffr
 */


#include "stm32f1xx.h"

volatile uint32_t uTick;


void TIM2_IRQHandler(void){
	TIM2->SR &=~ (TIM_SR_UIF);	//CLEAR

	uTick += 1;
	return;
}
