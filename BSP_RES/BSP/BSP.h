/*
 * BSP.h
 *
 *  Created on: Aug 31, 2018
 *      Author: hitha
 */

#ifndef BSP_H_
#define BSP_H_

#include "stm32f4xx.h"
/*  Function:  Option LEDs on Board
 *  Author  :  HIT-HanBo
 */
#define LED0_ON   GPIOF->ODR |= (1 << 9)
#define LED0_OFF  GPIOF->ODR &= 0xfffffdff
#define LED1_ON   GPIOF->ODR |= (1 << 10)
#define LED1_OFF  GPIOF->ODR &= 0xfffffbff
#define LED0_TOGGLE  GPIOF->ODR ^= (1 << 9)
#define LED1_TOGGLE  GPIOF->ODR ^= (1 << 10)

void LED_Init(void);
void BSP_UART1_Init(uint32_t Band_Rate);
void BSP_I2C1_Init(void);


#endif /* BSP_H_ */
