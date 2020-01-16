/*
 * ledmatrix.c
 *
 * Created: 09.01.2020 00:32:13
 *  Author: Joel
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "ledmatrix.h"
#include "max7219.h"

#define NrArrayItems(array)		(sizeof(array)/sizeof(array[0]))
#define NrRows(array)			(sizeof(array)/sizeof(array[0]))
#define NrColumns(array)		(sizeof(array[0])/sizeof(array[0][0]))

void writeBuffer(bool _buf[ROWLENGTH][COLLENGTH]){
	volatile uint8_t bytetowrite;
	for (uint8_t i=0; i<NRMAX; i++)
	{
		for (uint8_t j=0; j<NrColumns(_buf); j++)
		{
			bytetowrite = (_buf[i*8+7][j]<<7)+(_buf[i*8+6][j]<<6)+(_buf[i*8+5][j]<<5)+(_buf[i*8+4][j]<<4)+(_buf[i*8+3][j]<<3)+(_buf[i*8+2][j]<<2)+(_buf[i*8+1][j]<<1)+(_buf[i*8+0][j]<<0);
			if (bytetowrite != 0)
			{
				writeMax(i,reg_digit7 - j,bytetowrite);
			}
		}
	}
}

void clearBuffer(volatile bool _buf[ROWLENGTH][COLLENGTH]){
	for (uint8_t i=0; i<NrRows(_buf); i++)
	{
		for (uint8_t j=0; j<NrColumns(_buf); j++)
		{
			_buf[i][j] = false;
		}
	}
	clearDisplay();
}
