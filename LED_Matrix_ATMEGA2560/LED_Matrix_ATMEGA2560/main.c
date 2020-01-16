/*
 * LED_Matrix_ATMEGA2560.c
 *
 * Created: 08.01.2020 22:34:29
 * Author : Joel
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "max7219.h"
#include "ledmatrix.h"

int main(void)
{
	initMax();
	bool buf[ROWLENGTH][COLLENGTH];
    while (1) 
    {
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
}