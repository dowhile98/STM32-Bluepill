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
#include "USART.h"
#include "delay.h"
#include "RCC.h"
#include <string.h>
#include <stdio.h>
/*Typedef -------------------------------------------------------------------*/

/*Macros --------------------------------------------------------------------*/
#define DEBUG_SERIAL

#ifdef DEBUG_SERIAL
#define SERIAL_PRINTF(...) {printf(__VA_ARGS__);}
#else
#define  SERIAL_PRINTF(...) {}
#endif
/*Global variables ----------------------------------------------------------*/
void USART1_PINConfig(void);
/*Function prototype --------------------------------------------------------*/

/*Main Function -------------------------------------------------------------*/

int main(void)
{
	delay_init();
	USART1_PINConfig();
	USART_Init(USART1, SystemCoreClock, 115200, 0);


    /* Loop forever */
	for(;;){

	}
}

/*Function definition -------------------------------------------------------*/
void USART1_PINConfig(void){
	//PA9 y PA10
	RCC->APB2ENR |= GPIOX_CLOCK(USART1_TX) | GPIOX_CLOCK(USART1_RX);
	//PA9->TX
	GPIOX_MODE(MODE_PP_ALTER_50MHZ, USART1_TX);
	//PA10->RX
	GPIOX_MODE(MODE_FF_DIGITAL_INPUT, USART1_RX);

	return;
}

/*****************************************************************/

int __io_putchar(int ch){
	uint8_t c = ch & 0xFFU;
	USART_SendData(USART1, &c, 1);
	return ch;
}
/*****************************************************************/


