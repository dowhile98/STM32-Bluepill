/*
 * USART.c
 *
 *  Created on: 7 ago. 2022
 *      Author: jeffr
 */


#include "USART.h"


void USART_Init(USART_TypeDef *USARTx, uint32_t pclk, uint32_t baud, uint32_t PARAM){
	//Enable clock
	if(USART1 == USARTx){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	}
	else if(USART2 == USARTx){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	}else if(USART3 == USARTx){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	}
	//config parameters
	USARTx->CR1 = PARAM;
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	//USART BAUD CONFIG
	USARTx->BRR = UART_BRR_SAMPLING16(pclk, baud);
	//USART ENABLE
	USARTx->CR1 |= USART_CR1_UE;
}


/**
 * @brief enviar N data por el USART
 */
void USART_SendData(USART_TypeDef * USARTx,uint8_t *pTxBuffer, uint32_t Size){
	uint16_t *pdata;
	for(uint32_t i= 0; i<Size;i++){
		//verificar el flag TXE
		while(!(USARTx->SR & USART_SR_TXE));

		//verificar si se ve transmitir en modo de 8bit o 9bit
		if(USARTx->CR1 & USART_CR1_M){
			//enviar el dato
			pdata = (uint16_t*) pTxBuffer;
			USARTx->DR = (*pdata & (uint16_t)0x1FF);
			//Verificar la paridad
			if(!(USARTx->CR1 & USART_CR1_PCE )){
				pTxBuffer++;
				pTxBuffer++;
			}
			else{
				pTxBuffer++;
			}
		}
		else{		//modo de 8bit
			USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			pTxBuffer++;
		}
	}
	/*esperamos que TC se ponga a 1*/
	while(!(USARTx->SR & USART_SR_TC));

	return;
}

/**
 * @brief enviar N data por el USART
 */
void USART_ReceiveData(USART_TypeDef * USARTx,uint8_t *pRxBuffer, uint32_t Size){
	for(uint32_t i= 0; i<Size;i++){
		//verificar el flag RXNE
		while(!(USARTx->SR & USART_SR_RXNE));
		//verificar si se va recibir en modo de 8bit o 9bit
		if(USARTx->CR1 & USART_CR1_M){

			/*VERIFICAR LA PARIDAD*/
			if(!(USARTx->CR1 & USART_CR1_PCE )){	//sin paridad
				*((uint16_t*) pRxBuffer) = USARTx->DR & (uint16_t) 0x1FF;
				pRxBuffer++;
				pRxBuffer++;
			}
			else{	//paridad
				*pRxBuffer = USARTx->DR & (uint8_t) 0xFF;
				pRxBuffer++;
			}
		}
		else{
			/*VERIFICAR LA PARIDAD*/
			if(!(USARTx->CR1 & USART_CR1_PCE)){
				*pRxBuffer = USARTx->DR & (uint8_t) 0xFF;
			}
			else{
				*pRxBuffer = USARTx->DR & (uint8_t) 0x7F;
			}
			pRxBuffer++;
		}
	}
	return;
}
