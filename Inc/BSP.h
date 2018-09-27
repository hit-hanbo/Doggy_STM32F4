#ifndef __BSP_H
#define __BSP_H

#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"

#define LED0_OFF   GPIOF->ODR |= (1 << 9)
#define LED0_ON  GPIOF->ODR &= 0xfffffdff
#define LED1_OFF   GPIOF->ODR |= (1 << 10)
#define LED1_ON  GPIOF->ODR &= 0xfffffbff
#define LED0_TOGGLE  GPIOF->ODR ^= (1 << 9)
#define LED1_TOGGLE  GPIOF->ODR ^= (1 << 10)

void LED_Init(void);
void ADC_Init(void);
void BEEP_Init(void);
void LCD_Init(void);
void Fire_Detect(void);
void Smog_Detect(void);


#endif

