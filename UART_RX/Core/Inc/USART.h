/*
 * USART.h
 *
 *  Created on: 7 ago. 2022
 *      Author: jeffr
 */

#ifndef INC_USART_H_
#define INC_USART_H_
/*Includes -------------------------------------------------------------------*/
#include <stm32f1xx.h>

/*Defines --------------------------------------------------------------------*/
/*estos macros son para configurar la velocidad en baudios del USART*/
#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            (((_PCLK_)*25U)/(4U*(_BAUD_)))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U) + 50U) / 100U)

/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            (((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U)) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))


/*Function prototype ---------------------------------------------------------*/
/**
 * @brief configura el USARTx con los paremetros que se vayan a pasar
 * @param USARTx: USART1, USART2...  a configurar
 * @param pclk: PCLKx al cual esta conectado el USARTx
 * @param baud: baudios para la comunicacion
 * @param PARAM: tamaño de datos, paridad, bit de stop
 */
void USART_Init(USART_TypeDef *USARTx, uint32_t pclk, uint32_t baud, uint32_t PARAM);

/**
 * @brief envio de datos por el USART
 */
void USART_SendData(USART_TypeDef * USARTx,uint8_t *pTxBuffer, uint32_t Size);

/**
 * @brief enviar N data por el USART
 */
void USART_ReceiveData(USART_TypeDef * USARTx,uint8_t *pRxBuffer, uint32_t Size);
#endif /* INC_USART_H_ */
