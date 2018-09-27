/*
 * I2C.c
 *
 *  Created on: Sep 1, 2018
 *      Author: hitha
 */


#include "BSP/BSP.h"
#include "I2C.h"

void delay(void)
{
	uint8_t i = 0x0a;
	for(;i>0;i--);
}

void I2C1_Transmit(uint8_t Address, uint8_t Byte)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	while(I2C1->SR1 && 0x0001);
	I2C_Send7bitAddress(I2C1, Address, I2C_Direction_Transmitter);
	while(I2C1->SR1 && 0x0002);
	I2C_SendData(I2C1, Byte);
	while(I2C1->SR1 && 0x0004);
	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C1->SR2 && 0x0008);
}
