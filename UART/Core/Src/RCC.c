/*
 * RCC.c
 *
 *  Created on: Jun 20, 2022
 *      Author: jeffr
 */
#include "RCC.h"

/**
 * habilita y selecciona como fuente de reloj del sistema el HSE
 */
void HSE_Sysclk(void){
	RCC->CR |= RCC_CR_HSEON;			// enciende el HSE
	while(!(RCC->CR & RCC_CR_HSERDY));	// Espera que el HSE se estabilice
	/*seleccionar la fuente de reloj del sysclk*/
	RCC->CFGR &=~ (RCC_CFGR_SW);
	RCC->CFGR |= RCC_CFGR_SW_HSE;		//selecciona el HSE como fuente para el SYSCLK
	while(!(RCC->CFGR & RCC_CFGR_SWS_HSE));
	SystemCoreClockUpdate();
	return;
}
/**
 * habilita y selecciona como fuente de reloj del sistema el HSE
 */
void HSI_Sysclk(void){
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));
	RCC->CFGR &=~(RCC_CFGR_SW);
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	SystemCoreClockUpdate();
	return;
}
/**
 * @brief configura el PLL
 * @param [pllsrc]: HSI/HSE
 * @param [freq]  : Frecuencia que se quiere configurar el PLL
 */
void PLL_Sysclk(uint32_t pllsrc, uint32_t freq){
	uint32_t temp;
	if(pllsrc == HSE){
		HSE_Sysclk();
		RCC->CFGR |= RCC_CFGR_PLLSRC;
	}else{
		HSI_Sysclk();
		RCC->CFGR &=~ RCC_CFGR_PLLSRC;
	}
	//Configurar el PLL
	//Apaga el PLL
	RCC->CR &=~ (RCC_CR_PLLON);
	while(RCC->CR & RCC_CR_PLLRDY);
	//Cambia  los parametros del pll
	if(pllsrc == HSE)
		RCC->CFGR |= RCC_CFGR_PLLXTPRE;		//dividir entre dos
	temp = (freq / 4E+6) - 2U;
	if(temp>15)
		temp = 14;
	RCC->CFGR &=~(RCC_CFGR_PLLMULL);
	RCC->CFGR |= temp<<18;


	if(freq>36E+6){
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	}
	/*Configurar la latencia de la flash*/
	FLASH->ACR &=~ (FLASH_ACR_LATENCY);
	if(freq<24E+6){
		FLASH->ACR &=~ (FLASH_ACR_LATENCY);
	}else if(freq<48E+6){
		FLASH->ACR |= (FLASH_ACR_LATENCY_0);
	}else{
		FLASH->ACR |= (FLASH_ACR_LATENCY_1);
	}
	/*encendemos el PLL*/
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	/*seleccionamos el pll como fuente de reloj*/
	RCC->CFGR &=~(RCC_CFGR_SW);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
	if(freq == 72E+6)
		SystemCoreClock = freq;
	else{
		SystemCoreClockUpdate();
	}

	return;
}
