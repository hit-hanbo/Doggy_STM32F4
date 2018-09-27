/*
 * USART.h
 *
 *  Created on: Aug 31, 2018
 *      Author: hitha
 */

#ifndef PERIPH_USART_H_
#define PERIPH_USART_H_

#include "stm32f4xx.h"

void USART1_Tx_Byte(uint8_t Byte);
void USART1_Tx_Str(uint8_t* Str, uint16_t length);

#endif /* PERIPH_USART_H_ */
