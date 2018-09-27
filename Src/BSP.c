#include "BSP.h"

void LED_Init(void)
{
	__HAL_RCC_GPIOF_CLK_ENABLE();
	GPIOF->MODER  |= 0x00140000;              //  GPIOF9, GPIOF10, General Purpose OUTPUT
	GPIOF->OTYPER &= 0x0000f9ff;              //  GPIOF9, GPIOF10, OUTPUT Push-Pull
	GPIOF->OSPEEDR&= 0xffc3ffff;              //  GPIOF9, GPIOF10, 2MHz Speed
  LED0_OFF;
	LED1_OFF;
}


void ADC_Init(void);
void BEEP_Init(void);
void LCD_Init(void);
void Fire_Detect(void);
void Smog_Detect(void);

