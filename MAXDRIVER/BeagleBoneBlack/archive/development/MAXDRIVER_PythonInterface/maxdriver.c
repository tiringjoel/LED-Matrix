/*
 * max7219.c
 *
 * Created: 08.01.2020 22:35:58
 *  Author: Joel
 */ 

#include <stdint.h>
#include <stdio.h>
// #include <avr/io.h>
// #include <util/delay.h>
#include "maxdriver.h"

#define digitalWrite(port, bitnr, val)	{if (val) port |= 1<<bitnr; else port &= ~(1<<bitnr);}

void shiftByte(S_MAX * max, uint8_t byte, uint8_t lsbfirst)
{
 	// volatile uint8_t command = FALSE;
	// for (uint8_t i=0; i<8; i++)
	// {
	// 	if (lsbfirst)
	// 	{
	// 		command = byte & 0b00000001;
	// 		byte = byte >> 1;
	// 	}else {
	// 		command = byte & 0b10000000;
	// 		byte = byte << 1;
	// 	}
	// 	digitalWrite(*(max->port),max->datapin,command);
	// 	digitalWrite(*(max->port),max->clkpin,TRUE);
	// 	_delay_us(0.05);
	// 	digitalWrite(*(max->port),max->clkpin,FALSE);
	// 	_delay_us(0.05);
	// } 
}

void shiftBit(S_MAX * max, volatile uint8_t bit)
{
	// digitalWrite(*(max->port),max->datapin,bit);
	// digitalWrite(*(max->port),max->clkpin,TRUE);
	// _delay_us(0.05);
	// digitalWrite(*(max->port),max->clkpin,FALSE);
	// _delay_us(0.05);
}

void shiftData(S_MAX * max, uint8_t address, uint8_t value){
	shiftByte(max, address, MSBFIRST);
	shiftByte(max, value, MSBFIRST);
}

void clearDatabus(S_MAX * max){
	for (volatile uint8_t i=0; i<max->nrmax; i++)
	{
		shiftData(max,0,0);
	}
}

void latchData(S_MAX * max){
	printf("latchData called...\n");
	// digitalWrite(*(max->port),max->cspin,TRUE);
	// _delay_us(0.05);
	// digitalWrite(*(max->port),max->cspin,FALSE);
}

void writeMax(S_MAX * max, uint8_t maxItem, uint8_t address, uint8_t value){
	clearDatabus(max);
	volatile uint8_t counter;
	for (counter=0; counter <= maxItem; counter++)
	{
		if (!counter)
		{
			shiftData(max,address,value);
		}else{
			shiftData(max,0,0);
		}
	}
	latchData(max);
	clearDatabus(max);
}

void clearDisplay(S_MAX * max)
{
	printf("clearDisplay called...\n");
	for (uint8_t i=0; i < max->nrmax; i++)
	{
		for (uint8_t j=0; j<8; j++)
		{
			writeMax(max,i,reg_digit0+j,0);
		}
	}
}

void initMax(S_MAX * max, /*volatile uint8_t * port, */uint8_t clkpin, uint8_t cspin, uint8_t datapin, uint8_t nrmax)
{
	printf("initMax called...\n");
	// max->port = port;
	max->clkpin = clkpin;
	max->cspin = cspin;
	max->datapin = datapin;
	max->nrmax = nrmax;
	printf("CLKPIN: %d\n",max->clkpin);
	printf("CSPIN: %d\n",max->cspin);
	printf("DATAPIN: %d\n",max->datapin);
	printf("NRMAX: %d\n",max->nrmax);
	
	for (uint8_t i=0; i<NRMAX; i++)
	{
		writeMax(max,i,reg_displaytest,0x0);
		writeMax(max,i,reg_shutdown,0x1);
		writeMax(max,i,reg_scanlimit,0x7);
		writeMax(max,i,reg_intensity,HIGH);	
	}
	clearDisplay(max);
}

void shiftBufferOut(S_MAX * max, volatile uint8_t * rdptr)
{
	printf("shiftBufferOut called...\n");
	rdptr = (rdptr+255);
	volatile uint8_t registers[8] = {reg_digit0,reg_digit1,reg_digit2,reg_digit3,reg_digit4,reg_digit5,reg_digit6,reg_digit7};
	volatile uint8_t regcounter = 0;
	for (uint16_t i = 0; i < 256; i++)
	{
		if (!(i%8))
		{
			shiftByte(max, registers[regcounter], MSBFIRST);
		}
		shiftBit(max, *(rdptr-i));
		printf("Byte: %d\n",*(rdptr-i));
		if (!((i+1)%32))
		{
			latchData(max);
			regcounter++;
		}
	}
}