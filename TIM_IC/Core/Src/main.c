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
#include "delay.h"
/*Typedef -------------------------------------------------------------------*/

/*Macros --------------------------------------------------------------------*/
#define LED 			C, 13
#define CH1_PSC			8
#define POLARITY		1

/*Global variables ----------------------------------------------------------*/
float freq;
/*Function prototype --------------------------------------------------------*/
/**
 * @brief configura el TIMER 2 para generar pwm por su canal 2
 * @param [psc]: valor del psc
 * @param [arr]: valor de arr
 */
void TIM2_PWM_Init(uint32_t psc, uint32_t arr);

/**
 * @brief configura el timer como captura de entrada
 */
void TIM3_IC_Init(void);

/**
 * @brief calcula frecuencia de entrada por el canal 1 del timer 3
 * @return freq: frecuencia calculada
 */
static float computeFreq(void);

/*Main Function -------------------------------------------------------------*/

int main(void)
{
	//DELAY INIT
	delay_init();
	/* led init*/
	RCC->APB2ENR |= GPIOX_CLOCK(LED);
	GPIOX_MODE(MODE_PP_OUT_50MHZ, LED);
	//TIMER INIT
	TIM2_PWM_Init(8, 1000);
	TIM2->CCR2 = 500;
	//TIMER 3 INITI
	TIM3_IC_Init();
	//CALCULO DE LA FRECUENCIA
	freq = computeFreq();
    /* Loop forever */
	for(;;){
		freq = computeFreq();
		delay_ms(400);
	}
}

/*Function definition -------------------------------------------------------*/
void TIM2_PWM_Init(uint32_t psc, uint32_t arr){
	/*TIM2/3/4/5_CHx 	->Input capture channel x Input floating
						->Output compare channel x Alternate function push-pull*/
	//enable clock
	RCC->APB2ENR |= GPIOX_CLOCK(TIM2_CH2);
	GPIOX_MODE(MODE_PP_ALTER_50MHZ, TIM2_CH2);
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//configuramos el timer
	TIM2->CR1 = 0;
	TIM2->ARR = arr - 1U;
	TIM2->PSC = psc - 1U;
	//configuracion del canal
	TIM2->CCMR1 &=~ (TIM_CCMR1_CC2S);		//MODO DE COMPARACION DE SALIDA
	TIM2->CCMR1 &=~(TIM_CCMR1_OC2M_2);
	TIM2->CCMR1 |= 6U<<12;					//PWM MODO 1
	TIM2->CCER |= TIM_CCER_CC2E;			//Se habilita el canal como salida

	//Se habilta el conteo
	TIM2->CR1 |= TIM_CR1_CEN;
	TIM2->CCR2 = 0;

	return;
}

void TIM3_IC_Init(void){
	/*habilitar clock*/
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB2ENR |= GPIOX_CLOCK(TIM3_CH1);
	/*Configuracion del pin*/
	GPIOX_MODE(MODE_FF_DIGITAL_INPUT, TIM3_CH1);
	/*configuracion del timer*/
	TIM3->CR1 = 0;
	TIM3->PSC = 0;
	TIM3->ARR = 0xFFFF;
	TIM3->CNT = 0;
	/*Configuracion del canal*/
	TIM3->CCMR1 &=~ (TIM_CCMR1_CC1S);
	TIM3->CCMR1 |= 0x1;							//CH1 input capture
	TIM3->CCMR1 &=~ (TIM_CCMR1_IC1PSC);			//prescaler de 0
	TIM3->CCMR1 |= 0x3U<<2;						//prescaler 8
	TIM3->CCMR1 |= 0x3U<<TIM_CCMR1_IC1F_Pos;	//Fsampling = Fdts/32, N = 8
	//Configurar el flanco que debe detectarse
	TIM3->CCER &=~(TIM_CCER_CC1P);				//rising edge
	/*habilitar el pin para la captura*/
	TIM3->CCER |= TIM_CCER_CC1E;
	/*habilitar el conteo del timer*/
	TIM3->CR1 |= TIM_CR1_CEN;

	return;
}

static float computeFreq(void){
	uint32_t IC[2];
	float diff;
	uint32_t TIM3_CLK = SystemCoreClock;
	float freq;

	/*se detecta el primer flanco*/
	TIM3->SR &=~ TIM_SR_CC1IF;
	while(!(TIM3->SR & TIM_SR_CC1IF));
	TIM3->SR &=~ TIM_SR_CC1IF;
	IC[0] = TIM3->CCR1;
	/*se detecta el segundo flanco*/
	TIM3->SR &=~ TIM_SR_CC1IF;
	while(!(TIM3->SR & TIM_SR_CC1IF));
	TIM3->SR &=~ TIM_SR_CC1IF;
	IC[1] = TIM3->CCR1;
	/*se realiza el calculo*/
	if(IC[1]>= IC[0])
		diff = IC[1] - IC[0];
	else
		diff = TIM3->ARR - IC[0] + IC[1];
	freq = (float)((TIM3_CLK/((TIM3->PSC +1)  * POLARITY)) / diff) * CH1_PSC;

	return freq;
}
