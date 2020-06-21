/*
 * MAX7219Driver.c
 *
 * Created: 17.01.2020 08:14:12
 * Author : Joel
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "maxdriver.h"

#define MAXPORT					PORTC
#define CLKPIN					(0)		// Pin 37
#define CSPIN					(1)		// Pin 36
#define DATAPIN					(2)		// Pin 35
#define NRMAX					(4)
#define ROWLENGTH				(8)
#define COLLENGTH				(32)

S_MAX mymax;

void init_io(void){
	DDRC = (1<<DDC0) + (1<<DDC1) + (1<<DDC2);
	initMax(&mymax,&PORTC,CLKPIN,CSPIN,DATAPIN,NRMAX);
}

int main(void)
{
    init_io();
	
	uint8_t ledbuf[ROWLENGTH][COLLENGTH] =	{{1,0,0,0,0,0,0,8,	9,10,11,12,13,14,15,16,		17,18,19,20,21,22,23,24,	25,26,27,28,29,30,31,0},
											{1,0,0,0,0,0,0,8,	9,10,11,12,13,14,15,16,		17,18,19,20,21,22,23,24,	25,26,27,28,29,30,31,0},
											{1,0,0,0,0,0,0,8,	9,10,11,12,13,14,15,16,		17,18,19,20,21,22,23,24,	25,26,27,28,29,30,31,0},
											{1,1,3,4,5,6,7,8,	9,10,11,12,13,14,15,16,		17,18,19,20,21,22,23,24,	25,26,27,28,29,30,31,0},
											{1,1,3,4,5,6,7,8,	9,10,11,12,13,14,15,16,		17,18,19,20,21,22,23,24,	25,26,27,28,29,30,31,0},
											{1,0,0,0,0,0,0,8,	9,10,11,12,13,14,15,16,		17,0,19,20,21,22,23,24,		25,26,27,28,29,30,31,0},
											{1,0,0,0,0,0,0,8,	9,10,11,12,13,14,15,16,		17,18,19,20,21,22,23,24,	25,26,27,28,29,30,31,0},
											{1,0,0,0,0,0,0,8,	9,10,11,12,13,14,15,16,		17,18,19,20,21,22,23,24,	25,26,27,28,29,30,31,0}};
												
	uint8_t *rdptr = &ledbuf[0][0];
	uint8_t *wrptr = &ledbuf[0][0];
												
    while (1) 
    {	
		for (uint8_t i = 0; i < 256; i++)
		{
			*(wrptr + i) = TRUE;
			shiftBufferOut(&mymax,rdptr);
			*(wrptr + i) = FALSE;
		}
    }
}



