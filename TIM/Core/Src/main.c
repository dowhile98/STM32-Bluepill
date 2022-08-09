/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/*Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f1xx.h"
#include "defines.h"
#include "RCC.h"

/*Typedef -------------------------------------------------------------------*/

/*Macros --------------------------------------------------------------------*/
#define LED		C, 13
/*Global variables ----------------------------------------------------------*/
extern volatile uint32_t uTick;
/*Function prototype --------------------------------------------------------*/
void TIM2_Init_IT(uint32_t freq);

uint32_t get_tick_value();
/*Main Function -------------------------------------------------------------*/

int main(void)
{
	uint32_t last_time;

	//LED CONFIG
	RCC->APB2ENR |= GPIOX_CLOCK(LED);
	GPIOX_MODE(MODE_PP_OUT_50MHZ, LED);
	//TIM CONFIG IT

	TIM2_Init_IT(1000);
	last_time = get_tick_value();		//valor inicial
    /* Loop forever */
	for(;;){

		if(get_tick_value() - last_time> 100){

			last_time = get_tick_value();
			GPIOX_ODR(LED) ^= 1;
		}

	}
}

/*Function definition -------------------------------------------------------*/

void TIM2_Init_IT(uint32_t freq){
	uint16_t temp;
	/*enable clock*/
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	/*Configurar los parametros del timer*/
	TIM2->CR1 = 0;
	/*Configurar el registro de ARR y PSC*/
	temp = (8E+6)/(8 * freq) - 1;
	TIM2->ARR = temp;
	TIM2->PSC = 8-1;
	/*configurar la interrupcion*/
	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM2_IRQn);
	//HABILITAR EL CONTEO
	TIM2->CR1 |= TIM_CR1_CEN;
	return;
}

uint32_t get_tick_value(){
	return uTick;
}