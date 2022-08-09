/*
 * RCC.h
 *
 *  Created on: Jun 20, 2022
 *      Author: jeffr
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stm32f1xx.h"

#define HSE					1<<16
#define HSI					0<<0

/*Function prototype --------------------------------------------------------*/
/**
 * habilita y selecciona como fuente de reloj del sistema el HSE
 */
void HSE_Sysclk(void);
/**
 * habilita y selecciona como fuente de reloj del sistema el HSE
 */
void HSI_Sysclk(void);
/**
 * @brief configura el PLL
 * @param [pllsrc]: HSI/HSE
 * @param [freq]  : Frecuencia que se quiere configurar el PLL
 */
void PLL_Sysclk(uint32_t pllsrc, uint32_t freq);


#endif /* INC_RCC_H_ */
