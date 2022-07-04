/*
 * delay.c
 *
 *  Created on: 25 jun. 2022
 *      Author: jeffr
 */

#include "delay.h"




/**
 * @brief funcion que inicializa la systick
 */
void delay_init(void){
	uint32_t temp;
	/*actualizar la variable que almacena la frecuencia de funcionamiento del sysclk*/
	SystemCoreClockUpdate();
	/*calculamos el valor del registro LOAD*/
	temp = SystemCoreClock / 1000;
	SysTick->LOAD = temp - 1U;
	/*seleccionar la fuente de reloj para la systick*/
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	/*habilitar el conteo*/
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
/**
 * @brief funcion que genera retardos en ms
 * @param time_ms: retardo en ms deseado
 */
void delay_ms(uint32_t time_ms){
	uint32_t i;

	/*poner el registro val  de la systick a cero*/
	SysTick->VAL = 0;
	for (i = 0;i<time_ms; i++){
		while(!(SysTick->CTRL & 1U<<16));		//Genera un retardo de 1ms
	}
	return;
}


