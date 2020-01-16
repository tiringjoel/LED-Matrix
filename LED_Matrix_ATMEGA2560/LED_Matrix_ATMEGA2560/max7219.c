/*
 * max7219.c
 *
 * Created: 08.01.2020 22:35:58
 *  Author: Joel
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "max7219.h"

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

static void shiftData(uint8_t address, uint8_t value){
	shiftByte(address, MSBFIRST);
	shiftByte(value, MSBFIRST);
}

static void clearDatabus(void){
	for (volatile uint8_t i=0; i<NRMAX; i++)
	{
		shiftData(0,0);
	}
}

static void latchData(void){
	digitalWrite(MAXPORT,CSPIN,TRUE);
	_delay_us(0.05);
	digitalWrite(MAXPORT,CSPIN,FALSE);
}

static void writeRegister(uint8_t address, uint8_t value)
{
	shiftByte(address, MSBFIRST);
	shiftByte(value, MSBFIRST);
	latchData();
}

void writeMax(uint8_t max, uint8_t address, uint8_t value){
	clearDatabus();
	volatile uint8_t counter;
	for (counter=0; counter<=max; counter++)
	{
		if (!counter)
		{
			shiftData(address,value);
		}else{
			shiftData(0,0);
		}
	}
	latchData();
	clearDatabus();
}

void clearDisplay(void)
{
	for (uint8_t i=0; i<NRMAX; i++)
	{
		for (uint8_t j=0; j<8; j++)
		{
			writeMax(i,reg_digit0+j,0);
		}
	}
}

void initMax(void)
{
	DDR(MAXPORT) |= (1<<CLKPIN) + (1<<DATAPIN) + (1<<CSPIN);		// Set set the DDR Register
	for (uint8_t i=0; i<NRMAX; i++)
	{
		writeMax(i,reg_displaytest,0x0);
		writeMax(i,reg_shutdown,0x1);
		writeMax(i,reg_scanlimit,0x7);
		writeMax(i,reg_intensity,LOW);	
	}
	clearDisplay();
}
