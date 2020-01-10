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

volatile bool buf[ROWLENGTH][COLLENGTH];

// static void copyBuffer(bool _buffer[ROWLENGTH][COLLENGTH]){
// 	for (uint8_t i=0; i<NrRows(buf); i++)
// 	{
// 		for (uint8_t j=0; j<NrColumns(buf); j++)
// 		{
// 			buf[i][j] = _buffer[i][j];
// 		}
// 	}
// }

// static void copyArray(bool dst[], bool src[]){
// 	if (NrArrayItems(dst) == NrArrayItems(src))
// 	{
// 		for(uint8_t i=0; i<NrArrayItems(src); i++){
// 			dst[i] = src[i];
// 		}
// 	}
// }

void writeBuffer(volatile bool _buf[ROWLENGTH][COLLENGTH]){
	volatile uint8_t bytetowrite;
	for (uint8_t i=0; i<NRMAX; i++)
	{
		for (uint8_t j=0; j<NrColumns(buf); j++)
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
	for (uint8_t i=0; i<NrRows(buf); i++)
	{
		for (uint8_t j=0; j<NrColumns(buf); j++)
		{
			_buf[i][j] = false;
		}
	}
	clearDisplay();
}

void testfncmatrix(void){
	for (uint8_t j=0; j<32; j++)
	{
		for (uint8_t i=0; i<8; i++)
		{
			clearBuffer(buf);
			buf[j][i] = true;
			writeBuffer(buf);
		}
	}
}