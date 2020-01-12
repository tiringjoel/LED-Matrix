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
// macros for Intensity
#define LOW				0x2
#define MEDIUM			0x7
#define HIGH			0xE

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
		_delay_us(0.05);
		digitalWrite(MAXPORT,CLKPIN,FALSE);
		_delay_us(0.05);
	}
}

static void shiftPointerArray(bool **output, uint8_t lsbfirst)
{
	volatile uint8_t command = FALSE;
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
		//_delay_us(0.05);
		digitalWrite(MAXPORT,CLKPIN,FALSE);
		//_delay_us(0.05);
	}
}

static void latchData(void){
	digitalWrite(MAXPORT,CSPIN,TRUE);
	//_delay_us(0.05);
	digitalWrite(MAXPORT,CSPIN,FALSE);
}

static void writeRegisterbyReference(uint8_t address,bool **value)
{
	shiftByte(address, MSBFIRST);
	shiftPointerArray(value, MSBFIRST);
	latchData();
}

void max7219ptrtest(void){
	bool mybuffer[] = {1,1,1,1,0,0,0,0};
	bool mybuffer2[] = {1,0,1,0,1,0,1,0,1};
	volatile bool *myptrarr[] = {&mybuffer[0],&mybuffer2[1],0,0,0,0,0,0};
	// generate assignment of ptr
	for (uint8_t i=2; i<8; i++)
	{
		myptrarr[i] = &mybuffer[i];
	}
	//shiftPointerArray(myptrarr,MSBFIRST)
	writeRegisterbyReference(255,myptrarr);
}
