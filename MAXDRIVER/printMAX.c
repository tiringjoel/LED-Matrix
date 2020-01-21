/*
 * printMAX.c
 *
 * Created: 17.01.2020 08:35:47
 *  Author: Joel
 */ 

#include <stdint.h>
#include "maxdriver.h"
#include "printMAX.h"

void printRegister(S_MAX * max, uint8_t Register)
{
	shiftByte(max, Register, MSBFIRST);
}

void printBit(S_MAX * max, uint8_t Bit)
{
	shiftBit(max, Bit);
}

void printByte(S_MAX * max, uint8_t Byte)
{
	shiftByte(max, Byte, MSBFIRST);
}

void printLatch(S_MAX * max)
{
	latchData(max);
}