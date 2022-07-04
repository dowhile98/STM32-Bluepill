/*
 * GPIO_Exti.h
 *
 *  Created on: 3 jul. 2022
 *      Author: jeffr
 */

#ifndef INC_GPIO_EXTI_H_
#define INC_GPIO_EXTI_H_


#include <stdint.h>

/**
 * @brief procesador de interrupciones externas
 * @param pinNumber: Numero de pin que genera la IT
 */
void GPIO_EXTI_IQRHandler(uint8_t pinNumber);
/**
 * @brief callback que se ejecutará cuando se de una interrupcion
 */
void GPIO_EXTI_Callback(uint8_t pinNumber);

#endif /* INC_GPIO_EXTI_H_ */
