/*   USART.c
 *    Function : USART Tx & Rx Function
 *    Author   : hit-hanbo
 */

// Include Files
#include "USART.h"

uint8_t USART_rxBuffer[64];     // [BUFFER] * 64
uint8_t RX_Status = 0x00;       // [RX_DONE] [0D_DONE] [Bytes]

/*  Function:  USART1 IRQn Handler
 *  Author  :  HIT-HanBo
 */
void USART1_Tx_Byte(uint8_t Byte)
{
	while((USART1->SR & (1 << 7)) == 0);    //  Wait For Completion Transmit
	USART1->DR = Byte;                    //  Send Byte to USART1
}

/*  Function:  USART1 IRQn Handler
 *  Author  :  HIT-HanBo
 */
void USART1_Tx_Str(uint8_t* Str, uint16_t length)
{
	uint16_t i = 0;
	for(i=0; i<length; i++)
	{
		USART1_Tx_Byte(Str[i]);
	}
}

/*  Function:  USART1 IRQn Handler, Receive Data
 *  Author  :  HIT-HanBo
 *    Note  :  RX Data: [DATA] ... [0x0D] [0x0A]
 */
void USART1_IRQHandler(void)
{
	uint8_t RX_Res    = 0x00;
	if(USART1->SR & 0x0040)         // TC Interrupt <--> Transmit Complete
	{
		USART1->SR &= ~(1 << 6);    // Clear IT Flag
		//  TxD Interrupt
	}
	else if(USART1->SR & (1 << 5))  // RXNE Interrupt<-> Receive Data
	{
		USART1->SR &= ~(1 << 5);    // Clear IT Flag
		//  RxD Interrupt
		RX_Res = USART1->DR;
		if((RX_Status & 0x80) == 0)   // Rx UNcomplete
		{
			if(RX_Status & 0x40)    // [0D] have Received
			{
				if(RX_Res == 0x0a)  // [0A] is coming
					RX_Status |= 0x80;
				else
					RX_Status  = 0x00;//[0A] is missing, RETRY...
			}
			else                    // [0D] have not Received
			{
				if(RX_Res == 0x0d)  // [0D] in Buffer
					RX_Status |= 0x40;
				else                // [DATA] --> [BUFFER]
				{
					USART_rxBuffer[RX_Status & 0x3f] = RX_Res;
					RX_Status ++;
				}
			}
		}
	}
}
