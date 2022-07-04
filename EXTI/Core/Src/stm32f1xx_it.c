/*
 * stm32f1xx_it.c
 *
 *  Created on: 3 jul. 2022
 *      Author: jeffr
 */


#include "stm32f1xx.h"
#include "LCD.h"
#include "GPIO_Exti.h"

void EXTI15_10_IRQHandler(void){
	GPIO_EXTI_IQRHandler(11);
	return;
}
