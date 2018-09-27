/*   main.c
 *    Function : MAIN Function && FUNCTIONN Start Init
 *    Author   : hit-hanbo
 */

// Include Files
#include "stm32f4xx.h"
#include "BSP/BSP.h"
#include "stm32f4xx_rcc.h"
#include "Periph/USART.h"
#include "Periph/I2C.h"

// Private Function
void SysTick_Init(void);
void NVIC_Init_Priority_Group(void);

// EXTERN variables for USART1
extern uint8_t RX_Status;
extern uint8_t USART_rxBuffer[64];

// MAIN ENTRY
int main(void)
{
	uint32_t i;
	//SysTick_Init();
	NVIC_Init_Priority_Group();
	LED_Init();
	BSP_I2C1_Init();
	//BSP_UART1_Init(9600);
	for(;;)
	{
		I2C1_Transmit(0xa0, 0x02);
		for(i=0; i<0xfff; i++);
	}
}

void SysTick_Init(void)
{
	SysTick->LOAD  = 42000000;       //  SysTick Freq = 1KHz
    SysTick->CTRL |= 0x00000003;     //  SysTick ENABLE IRQ, CLK = SYS_CLK / 8
}

/* NVIC Set Priority Group */
/*
 * Function:    Set NVIC Priority Group
 *              2-bit Preemption, 2-bit Sub
 */
void NVIC_Init_Priority_Group(void)
{
	uint32_t tmp_AIRCR = 0x00000000;
	tmp_AIRCR |= 0xfa050000;          //  Set AIRCR_KEY
	tmp_AIRCR |= (1 << 8) | (1 << 10);
	tmp_AIRCR &= ~(1 << 9);           //  Set xx.yy
	SCB->AIRCR = tmp_AIRCR;           //  Set AIRCR
}


/* Interrupt Service Functions */
void SysTick_Handler(void)
{
	/*
	 * Place Holder For SysTick Handler
	 */
}


