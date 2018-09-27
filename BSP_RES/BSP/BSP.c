/*   BSP.c
 *    Function : Periphs on Board's Driver
 *    Author   : hit-hanbo
 */
#define ARM_MATH_CM4

#include "BSP.h"
#include "stm32f4xx_i2c.h"
#include "arm_math.h"

/*  Function:  Init LEDs on Board
 *  Author  :  HIT-HanBo
 */
void LED_Init(void)
{
	RCC->AHB1ENR  |= RCC_AHB1Periph_GPIOF;    //  ENABLE GPIOF Clock
	GPIOF->MODER  |= 0x00140000;              //  GPIOF9, GPIOF10, General Purpose OUTPUT
	GPIOF->OTYPER &= 0x0000f9ff;              //  GPIOF9, GPIOF10, OUTPUT Push-Pull
	GPIOF->OSPEEDR&= 0xffc3ffff;              //  GPIOF9, GPIOF10, 2MHz Speed
	GPIOF->PUPDR  |= (1 << 20) | (1 << 18);
	GPIOF->PUPDR  &= 0xffd7ffff;              //  GPIOF9, GPIOF10, Push-UP
	GPIOF->BSRRH  &= 0x00000000;              //  GPIOF, Default LOW
}
/*  Function:  Init KEYs on Board
 *  Author  :  HIT-HanBo
 */
void KEY_Init(void)
{

}

/*  Function:  Init I2C <--> 24C02
 *  Author  :  HIT-HanBo
 */
void BSP_I2C1_Init(void)
{
	I2C_InitTypeDef I2C_InitStruct;
	// GPIO Setting GPIOB8, GPIOB9
	RCC->AHB1ENR  |= RCC_AHB1Periph_GPIOB;      //  ENABLE GPIOB Clock
	GPIOB->MODER  |= (1 << 17) | (1 << 19);
	GPIOB->MODER  &= ~(1 << 16) | (1 << 18);   //  GPIOB8, GPIOB9, AF
	GPIOB->OTYPER |= 0x00000300;               //  GPIOB8, GPIOB9, OD
	GPIOB->OSPEEDR|= 0x000f0000;               //  GPIOB8, GPIOB9, High-Speed
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
	// I2C Setting I2C1
	/*
		I2C1->CR1     &= ~0x0001;                  //  I2C1, PE=0
		I2C1->CR2     |= (1 << 10) | (1 << 9);     //  ENABLE I2C1 ITBUFEN & ITEVTEN
		I2C1->CR2     |= 0x002a;
		I2C1->CR2     &= ~0x002a;                  //  I2C1, PClk=APB1=42MHz
		I2C1->CCR     &= ~(1 << 15) | (1 << 14);   //  Standard I2C Mode, DUTY=2
		I2C1->CCR     |= 0x00d2;                   //  I2C1, CCR=d2, clk=100kHz
		I2C1->TRISE   |= 0x002a;                   //  I2C1, TRISE=1us
	    I2C1->CR1     |= (1 << 10);                 //  I2C1, HW-ACK
	    I2C1->CR1     |= (1 << 9);                  //  I2C, Gen Stop SIGNAL, MASTER
	    I2C1->CR1     |= 0x0001;                    //  I2C, PE = 1, ENABLE
	    I2C1->CR1     |= (1 << 8);                  //  I2C, Gen Start SIGNAL, MASTER
	*/
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_OwnAddress1 = 0X00;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_InitStruct);
	I2C_Cmd(I2C1, ENABLE);
}

/*  Function:  Init USART <--> SIM800
 *  Author  :  HIT-HanBo
 */
void BSP_UART1_Init(uint32_t Band_Rate)
{
	uint16_t Mantissa, Fraction;               //  Mantissa & Fraction part of BRR
	float32_t BRR_Temp;
	/* GPIO Settings */
	RCC->AHB1ENR  |= RCC_AHB1Periph_GPIOA;     //  ENABLE GPIOA  Clock
	RCC->APB2ENR  |= RCC_APB2Periph_USART1;    //  ENABLE USART1 Clock
	GPIOA->MODER  |= (1 << 21) | (1 << 19);
	GPIOA->MODER  &= ~(1 << 20) | (1 << 18);   //  GPIOA9, GPIOA10, AF
	GPIOA->OTYPER &= 0xfffff900;               //  GPIOA9, GPIOA10, PP
	GPIOA->PUPDR  |= (1 << 20) | (1 << 18);
	GPIOA->PUPDR  &= 0xffd7ffff;               //  GPIOA9, GPIOA10, Pull-UP
	GPIOA->AFR[1]   |= 0x00000770;
	GPIOA->AFR[1]   &= 0xfffff77f;             //  GPIOA9, GPIOA10, AF <--> USART1
	/* USART Settings */
	USART1->CR1   |= (1 << 12);                //  USART1 NO Parity
	USART1->CR1   &= ~(1 << 12);               //  USART1 8-bit Data
	USART1->CR1   |= (1 << 2) | (1 << 5);      //  USART1 RXD & IRQn ENABLE -- RXNEIE, RE
	USART1->CR1   |= (1 << 3) | (1 << 6);      //  USART1 TXD & IRQn ENABLE -- TCIE, TE
	USART1->CR1   |= (1 << 8);                 //  USART1 PEIE  IRQn ENABLE
	USART1->CR1   &= ~(1 << 15);               //  USART1 Over Sample = 0
	BRR_Temp = (float32_t) (84000000) / (16 * Band_Rate);
	                                           //  Calculate BRR
	Mantissa = BRR_Temp;
	Fraction = (BRR_Temp - Mantissa) * 16;
	USART1->BRR    =  (uint16_t) (Mantissa << 4) + Fraction;
	                                           //  Write Baud_Rate to BRR
	USART1->CR1   |= (1 << 13);                //  USART1 ENABLE
	/* IRQn Settings */
	NVIC->ISER[1] |= (1 << 5);                 //  ENABLE NVIC <--> USART1
	NVIC->IP[9]   |= 0x0000ff0000 ;            //  Preemption 2, Sub 2
}

/*  Function:  Init USART <--> Debug
 *  Author  :  HIT-HanBo
 */
void BSP_UART2_Init(void)
{

}
