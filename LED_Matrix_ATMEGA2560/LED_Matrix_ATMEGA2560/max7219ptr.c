/*
 * max7219ptr.c
 *
 * Created: 12.01.2020 20:45:52
 *  Author: Joel
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "max7219ptr.h"

//pin assignment
#define MAXPORT		C
#define CLKPIN		(0)
#define CSPIN		(1)
#define DATAPIN		(2)
#define BYTE		(8)
//helper macros
#define FALSE		(0)
#define TRUE		(!FALSE)
#define LSBFIRST	(1)
#define MSBFIRST	(!LSBFIRST)
//port helper macros
#define GLUE(a, b)     a##b
#define PORT(x)        GLUE(PORT, x)
#define PIN(x)         GLUE(PIN, x)
#define DDR(x)         GLUE(DDR, x)
#define OUTPUT		   (1)
#define digitalWrite(port, bitnr, val) {if (val) PORT(port) |= 1<<bitnr; else PORT(port) &= ~(1<<bitnr);}
#define pinMode(port, bitnr, val) {if (val) DDR(port) |= 1<<bitnr; else DDR(port) &= ~(1<<bitnr);}
#define _DELAY			//_delay_ms(0.05)
// macros for Intensity
#define LOW				0x2
#define MEDIUM			0x7
#define HIGH			0xE

#define ROWLENGTH	(8)
#define COLLENGTH	(8)


static void shiftByte(uint8_t byte, uint8_t lsbfirst)
{
	volatile uint8_t command = FALSE;
	for (uint8_t i=0; i<8; i++)
	{
		if (lsbfirst)
		{
			command = byte & 0b00000001;
			byte = byte >> 1;
			}else {
			command = byte & 0b10000000;
			byte = byte << 1;
		}
		digitalWrite(MAXPORT,DATAPIN,command);
		digitalWrite(MAXPORT,CLKPIN,TRUE);
		_DELAY;
		digitalWrite(MAXPORT,CLKPIN,FALSE);
		_DELAY;
	}
}

/*
static void shiftPointerArray(bool **output, uint8_t lsbfirst)
{
	volatile bool command;
	for (uint8_t i=0; i<8; i++)
	{
		if (!lsbfirst)
		{
			command = *(*(output + i));
			}else {
			command = *(*(output + BYTE-i));
		}
		digitalWrite(MAXPORT,DATAPIN,command);
		digitalWrite(MAXPORT,CLKPIN,TRUE);
		_DELAY;
		digitalWrite(MAXPORT,CLKPIN,FALSE);
		_DELAY;
	}
}
*/
static void shiftByteRef(bool *output, uint8_t lsbfirst)
{
	volatile bool command;
	for (uint8_t i=0; i<BYTE; i++)
	{
		if (!lsbfirst)
		{
			command = *(output + i);
			}else {
			command = *(output + (BYTE-i));
		}
		digitalWrite(MAXPORT,DATAPIN,command);
		digitalWrite(MAXPORT,CLKPIN,TRUE);
		_DELAY;
		digitalWrite(MAXPORT,CLKPIN,FALSE);
		_DELAY;
	}
}

static void latchData(void){
	digitalWrite(MAXPORT,CSPIN,TRUE);
	_DELAY;
	digitalWrite(MAXPORT,CSPIN,FALSE);
}

static void writeRegisterbyReference(uint8_t address,bool **value)
{
	shiftByte(address, MSBFIRST);
	shiftPointerArray(value, MSBFIRST);
	latchData();
}

static void writeDatabyReference(uint8_t address ,bool *value, uint8_t NrBytes)
{
	for (uint8_t i=0; i<NrBytes; i++)
	{
		shiftByte(address, MSBFIRST);
		shiftByteRef((value+8*i),LSBFIRST);
	}
	latchData();
}

void writeBufferbyReference(bool buf[ROWLENGTH][COLLENGTH])
{
	//assign Array of Pointer to Bufferrows
	bool *wrptr;
 	//write Data iteratively to Register
 	for (uint8_t i=0; i<COLLENGTH; i++)
 	{
		wrptr = &buf[i][0];
 		writeDatabyReference((reg_digit0 + i),wrptr,1);
 	}
}

void max7219ptrtest(void)
{	
	bool testbuffer[8][8] = {	{false,true,false,true,false,true,false,true},
							{true,false,true,false,true,false,true,false},
							{false,true,false,true,false,true,false,true},
							{true,false,true,false,true,false,true,false},
							{false,true,false,true,false,true,false,true},
							{true,false,true,false,true,false,true,false},
							{false,true,false,true,false,true,false,true},
							{true,false,true,false,true,false,true,false}	};
							
	writeBufferbyReference(testbuffer);
}
