/*
 * defines.h
 *
 *  Created on: 3 jul. 2022
 *      Author: jeffr
 */

#ifndef INC_DEFINES_H_
#define INC_DEFINES_H_
// TIM5 alternate function remapping
#define TIM5_CH4				A , 3

// TIM4 alternate function remapping
#define TIM4_CH1				B , 6 	/* D , 12 */
#define TIM4_CH2				B , 7 	/* D , 13 */
#define TIM4_CH3				B , 8 	/* D , 14 */
#define TIM4_CH4				B , 9	/* D , 15 */

//TIM3 alternate function remapping
#define TIM3_CH1				A , 6 	/* B , 4 */ /* C , 6 */
#define TIM3_CH2				A , 7 	/* B , 5 */	/* C , 7 */
#define TIM3_CH3				B , 0	/* C , 8 */
#define TIM3_CH4				B , 1	/* C , 9 */

//TIM2 alternate function remapping
#define TIM2_CH1				A , 0	/* A , 15 */
#define TIM2_CH2				A , 1	/* B , 3 */
#define TIM2_CH3				A , 2	/* B , 10 */
#define TIM2_CH4				A , 3	/* B , 11 */


//TIM1 alternate function remapping
#define TIM1_ETR				A , 12	/* E , 7 */
#define TIM1_CH1				A , 8	/* E , 8 */
#define TIM1_CH2				A , 9 	/* E , 11 */
#define TIM1_CH3				A , 10	/* E , 13 */
#define TIM1_CH4				A , 11  /* E , 14 */
#define TIM1_BKIN				B , 12	/* A , 6 */ /* E , 15 */
#define TIM1_CH1N				B , 13	/* A , 7 */
#define TIM1_CH2N				B , 14	/* B , 0 */
#define TIM1_CH3N				B , 15 	/* B , 1*/

//USART3 remapping
#define USART3_TX				B , 10	/* C , 10 */
#define USART3_RX				B , 11	/* C , 11 */
#define USART3_CK				B , 12	/* C , 12 */
#define USART3_CTS				B , 13	/* D , 11 */
#define USART3_RTS				B , 14	/* D , 12*/

//USART2 remapping
#define USART2_CTS				A , 0
#define USART2_RTS				A , 1
#define USART2_TX				A , 2
#define USART2_RX				A , 3
#define USART2_CK				A , 4

//USART1 remapping
#define USART1_TX				A , 9	/* B , 6 */
#define USART1_RX				A , 10	/* B , 7 */

//I2C1 remapping
#define I2C1_SCL				B , 6 	/* B , 8 */
#define I2C1_SDA				B , 7	/* B , 9 */

//SPI1 remapping
#define SPI1_NSS				A , 4 	/* A , 15 */
#define SPI1_SCK				A , 5 	/* B , 3 */
#define SPI1_MISO				A , 6 	/* B , 4 */
#define SPI1_MOSI				A , 7 	/* B , 5 */


//SPI2 remapping
#define SPI2_SCK				B , 13
#define SPI2_MISO				B , 14
#define SPI2_MOSI				B , 15
#define SPI2_NSS				B , 12

//I2C2 remapping
#define I2C2_SCL				B , 10
#define I2C2_SDA				B , 11

//ADC channels
#define ADC_CH0					A , 0
#define ADC_CH1					A , 1
#define ADC_CH2					A , 2
#define ADC_CH3					A , 3
#define ADC_CH4					A , 4
#define ADC_CH5					A , 5
#define ADC_CH6					A , 6
#define ADC_CH7					A , 7
#define ADC_CH8					B , 0
#define ADC_CH9					B , 1
//-----------------------------------------------------------------------------
#define BITBAND_ACCESS(a, b)  *(volatile uint32_t*)(((uint32_t)&a & 0xF0000000) + 0x2000000 + (((uint32_t)&a & 0x000FFFFF) << 5) + (b << 2))

/* GPIO mode (PP: push-pull, OD: open drain, FF: input floating) */
#define MODE_ANALOG_INPUT     0x0
#define MODE_PP_OUT_10MHZ     0x1
#define MODE_PP_OUT_2MHZ      0x2
#define MODE_PP_OUT_50MHZ     0x3
#define MODE_FF_DIGITAL_INPUT 0x4
#define MODE_OD_OUT_10MHZ     0x5
#define MODE_OD_OUT_2MHZ      0x6
#define MODE_OD_OUT_50MHZ     0x7
#define MODE_PU_DIGITAL_INPUT 0x8
#define MODE_PP_ALTER_10MHZ   0x9
#define MODE_PP_ALTER_2MHZ    0xA
#define MODE_PP_ALTER_50MHZ   0xB
#define MODE_RESERVED         0xC
#define MODE_OD_ALTER_10MHZ   0xD
#define MODE_OD_ALTER_2MHZ    0xE
#define MODE_OD_ALTER_50MHZ   0xF

#define GPIOX_PORT_(a, b)     GPIO ## a
#define GPIOX_PORT(a)         GPIOX_PORT_(a)

#define GPIOX_PIN_(a, b)      b
#define GPIOX_PIN(a)          GPIOX_PIN_(a)

#define GPIOX_MODE_(a,b,c)    ((GPIO_TypeDef*)(((c & 8) >> 1) + GPIO ## b ## _BASE))->CRL = (((GPIO_TypeDef*)(((c & 8) >> 1) + GPIO ## b ## _BASE))->CRL & ~(0xF << ((c & 7) << 2))) | (a << ((c & 7) << 2))
#define GPIOX_MODE(a, b)      GPIOX_MODE_(a, b)

#define GPIOX_ODR_(a, b)      BITBAND_ACCESS(GPIO ## a ->ODR, b)
#define GPIOX_ODR(a)          GPIOX_ODR_(a)

#define GPIOX_IDR_(a, b)      BITBAND_ACCESS(GPIO ## a ->IDR, b)
#define GPIOX_IDR(a)          GPIOX_IDR_(a)

#define GPIOX_LINE_(a, b)     EXTI_Line ## b
#define GPIOX_LINE(a)         GPIOX_LINE_(a)

#define GPIOX_CLOCK_(a, b)    RCC_APB2ENR_IOP ## a ## EN
#define GPIOX_CLOCK(a)        GPIOX_CLOCK_(a)

#define GPIOX_PORTNUM_A       1
#define GPIOX_PORTNUM_B       2
#define GPIOX_PORTNUM_C       3
#define GPIOX_PORTNUM_D       4
#define GPIOX_PORTNUM_E       5
#define GPIOX_PORTNUM_F       6
#define GPIOX_PORTNUM_G       7
#define GPIOX_PORTNUM_H       8
#define GPIOX_PORTNUM_I       9
#define GPIOX_PORTNUM_J       10
#define GPIOX_PORTNUM_K       11
#define GPIOX_PORTNUM_(a, b)  GPIOX_PORTNUM_ ## a
#define GPIOX_PORTNUM(a)      GPIOX_PORTNUM_(a)

#define GPIOX_PORTNAME_(a, b) a
#define GPIOX_PORTNAME(a)     GPIOX_PORTNAME_(a)

#endif /* INC_DEFINES_H_ */
