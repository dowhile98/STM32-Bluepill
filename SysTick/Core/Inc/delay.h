/*
 * delay.h
 *
 *  Created on: 25 jun. 2022
 *      Author: jeffr
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "stm32f1xx.h"

/**
 * @brief funcion que inicializa la systick
 */
void delay_init(void);
/**
 * @brief funcion que genera retardos en ms
 * @param time_ms: retardo en ms deseado
 */
void delay_ms(uint32_t time_ms);


#endif /* INC_DELAY_H_ */
